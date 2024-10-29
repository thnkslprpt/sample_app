/************************************************************************
 * NASA Docket No. GSC-18,719-1, and identified as “core Flight System: Bootes”
 *
 * Copyright (c) 2020 United States Government as represented by the
 * Administrator of the National Aeronautics and Space Administration.
 * All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License. You may obtain
 * a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ************************************************************************/

/**
 * \file
 *   This file contains the source code for the BPACC_FUN App.
 */

/*
** Include Files:
*/
#include "bpacc_fun.h"
#include "bpacc_fun_cmds.h"
#include "bpacc_fun_utils.h"
#include "bpacc_fun_eventids.h"
#include "bpacc_fun_dispatch.h"
#include "bpacc_fun_tbl.h"
#include "bpacc_fun_version.h"

/*
** global data
*/
BPACC_FUN_Data_t BPACC_FUN_Data;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * *  * * * * **/
/*                                                                            */
/* Application entry point and main process loop                              */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * *  * * * * **/
void BPACC_FUN_Main(void)
{
    CFE_Status_t     status;
    CFE_SB_Buffer_t *SBBufPtr;

    /*
    ** Create the first Performance Log entry
    */
    CFE_ES_PerfLogEntry(BPACC_FUN_PERF_ID);

    /*
    ** Perform application-specific initialization
    ** If the Initialization fails, set the RunStatus to
    ** CFE_ES_RunStatus_APP_ERROR and the App will not enter the RunLoop
    */
    status = BPACC_FUN_Init();
    if (status != CFE_SUCCESS)
    {
        BPACC_FUN_Data.RunStatus = CFE_ES_RunStatus_APP_ERROR;
    }

    /*
    ** BPACC_FUN App Runloop
    */
    while (CFE_ES_RunLoop(&BPACC_FUN_Data.RunStatus) == true)
    {
        /*
        ** Performance Log Exit Stamp
        */
        CFE_ES_PerfLogExit(BPACC_FUN_PERF_ID);

        /* Pend on receipt of command packet */
        status = CFE_SB_ReceiveBuffer(&SBBufPtr, BPACC_FUN_Data.CommandPipe, CFE_SB_PEND_FOREVER);

        /*
        ** Performance Log Entry Stamp
        */
        CFE_ES_PerfLogEntry(BPACC_FUN_PERF_ID);

        if (status == CFE_SUCCESS)
        {
            BPACC_FUN_TaskPipe(SBBufPtr);
        }
        else
        {
            CFE_EVS_SendEvent(BPACC_FUN_PIPE_ERR_EID, CFE_EVS_EventType_ERROR,
                              "BPACC_FUN: SB Pipe Read Error, App Will Exit");

            BPACC_FUN_Data.RunStatus = CFE_ES_RunStatus_APP_ERROR;
        }
    }

    /*
    ** Performance Log Exit Stamp
    */
    CFE_ES_PerfLogExit(BPACC_FUN_PERF_ID);

    CFE_ES_ExitApp(BPACC_FUN_Data.RunStatus);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  */
/*                                                                            */
/* Initialization                                                             */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
CFE_Status_t BPACC_FUN_Init(void)
{
    CFE_Status_t status;
    char         VersionString[BPACC_FUN_CFG_MAX_VERSION_STR_LEN];

    /* Zero out the global data structure */
    memset(&BPACC_FUN_Data, 0, sizeof(BPACC_FUN_Data));

    BPACC_FUN_Data.RunStatus = CFE_ES_RunStatus_APP_RUN;

    /*
    ** Initialize app configuration data
    */
    BPACC_FUN_Data.PipeDepth = BPACC_FUN_PIPE_DEPTH;

    strncpy(BPACC_FUN_Data.PipeName, "BPACC_FUN_CMD_PIPE", sizeof(BPACC_FUN_Data.PipeName));
    BPACC_FUN_Data.PipeName[sizeof(BPACC_FUN_Data.PipeName) - 1] = 0;

    /*
    ** Register the events
    */
    status = CFE_EVS_Register(NULL, 0, CFE_EVS_EventFilter_BINARY);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("BPACC_FUN App: Error Registering Events, RC = 0x%08lX\n", (unsigned long)status);
    }
    else
    {
        /*
         ** Initialize housekeeping packet (clear user data area).
         */
        CFE_MSG_Init(CFE_MSG_PTR(BPACC_FUN_Data.HkTlm.TelemetryHeader), CFE_SB_ValueToMsgId(BPACC_FUN_HK_TLM_MID),
                     sizeof(BPACC_FUN_Data.HkTlm));

        /*
         ** Create Software Bus message pipe.
         */
        status = CFE_SB_CreatePipe(&BPACC_FUN_Data.CommandPipe, BPACC_FUN_Data.PipeDepth, BPACC_FUN_Data.PipeName);
        if (status != CFE_SUCCESS)
        {
            CFE_EVS_SendEvent(BPACC_FUN_CR_PIPE_ERR_EID, CFE_EVS_EventType_ERROR,
                              "BPACC_FUN App: Error creating SB Command Pipe, RC = 0x%08lX", (unsigned long)status);
        }
    }

    if (status == CFE_SUCCESS)
    {
        /*
        ** Subscribe to Housekeeping request commands
        */
        status = CFE_SB_Subscribe(CFE_SB_ValueToMsgId(BPACC_FUN_SEND_HK_MID), BPACC_FUN_Data.CommandPipe);
        if (status != CFE_SUCCESS)
        {
            CFE_EVS_SendEvent(BPACC_FUN_SUB_HK_ERR_EID, CFE_EVS_EventType_ERROR,
                              "BPACC_FUN App: Error Subscribing to HK request, RC = 0x%08lX", (unsigned long)status);
        }
    }

    if (status == CFE_SUCCESS)
    {
        /*
        ** Subscribe to ground command packets
        */
        status = CFE_SB_Subscribe(CFE_SB_ValueToMsgId(BPACC_FUN_CMD_MID), BPACC_FUN_Data.CommandPipe);
        if (status != CFE_SUCCESS)
        {
            CFE_EVS_SendEvent(BPACC_FUN_SUB_CMD_ERR_EID, CFE_EVS_EventType_ERROR,
                              "BPACC_FUN App: Error Subscribing to Commands, RC = 0x%08lX", (unsigned long)status);
        }
    }

    if (status == CFE_SUCCESS)
    {
        /*
        ** Register Example Table(s)
        */
        status = CFE_TBL_Register(&BPACC_FUN_Data.TblHandles[0], "ExampleTable", sizeof(BPACC_FUN_ExampleTable_t),
                                  CFE_TBL_OPT_DEFAULT, BPACC_FUN_TblValidationFunc);
        if (status != CFE_SUCCESS)
        {
            CFE_EVS_SendEvent(BPACC_FUN_TABLE_REG_ERR_EID, CFE_EVS_EventType_ERROR,
                              "BPACC_FUN App: Error Registering Example Table, RC = 0x%08lX", (unsigned long)status);
        }
        else
        {
            status = CFE_TBL_Load(BPACC_FUN_Data.TblHandles[0], CFE_TBL_SRC_FILE, BPACC_FUN_TABLE_FILE);
        }

        CFE_Config_GetVersionString(VersionString, BPACC_FUN_CFG_MAX_VERSION_STR_LEN, "BPACC_FUN App", BPACC_FUN_VERSION,
                                    BPACC_FUN_BUILD_CODENAME, BPACC_FUN_LAST_OFFICIAL);

        CFE_EVS_SendEvent(BPACC_FUN_INIT_INF_EID, CFE_EVS_EventType_INFORMATION, "BPACC_FUN App Initialized.%s",
                          VersionString);
    }

    return status;
}
