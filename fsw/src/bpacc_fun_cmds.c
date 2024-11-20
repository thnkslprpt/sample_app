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
 *   This file contains the source code for the BPACC_FUN App Ground Command-handling functions
 */

/*
** Include Files:
*/
#include "bpacc_fun.h"
#include "bpacc_fun_cmds.h"
#include "bpacc_fun_msgids.h"
#include "bpacc_fun_eventids.h"
#include "bpacc_fun_version.h"
#include "bpacc_fun_tbl.h"
#include "bpacc_fun_utils.h"
#include "bpacc_fun_msg.h"

//#include bpaccel.h

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/*  Purpose:                                                                  */
/*         This function is triggered in response to a task telemetry request */
/*         from the housekeeping task. This function will gather the Apps     */
/*         telemetry, packetize it and send it to the housekeeping task via   */
/*         the software bus                                                   */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
CFE_Status_t BPACC_FUN_SendHkCmd(const BPACC_FUN_SendHkCmd_t *Msg)
{
    int i;

    /*
    ** Get command execution counters...
    */
    BPACC_FUN_Data.HkTlm.Payload.CommandErrorCounter = BPACC_FUN_Data.ErrCounter;
    BPACC_FUN_Data.HkTlm.Payload.CommandCounter      = BPACC_FUN_Data.CmdCounter;

    /*
    ** Send housekeeping telemetry packet...
    */
    CFE_SB_TimeStampMsg(CFE_MSG_PTR(BPACC_FUN_Data.HkTlm.TelemetryHeader));
    CFE_SB_TransmitMsg(CFE_MSG_PTR(BPACC_FUN_Data.HkTlm.TelemetryHeader), true);

    /*
    ** Manage any pending table loads, validations, etc.
    */
    for (i = 0; i < BPACC_FUN_NUMBER_OF_TABLES; i++)
    {
        CFE_TBL_Manage(BPACC_FUN_Data.TblHandles[i]);
    }

    return CFE_SUCCESS;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* BPACC_FUN NOOP commands                                                       */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
CFE_Status_t BPACC_FUN_NoopCmd(const BPACC_FUN_NoopCmd_t *Msg)
{
    BPACC_FUN_Data.CmdCounter++;

    CFE_EVS_SendEvent(BPACC_FUN_NOOP_INF_EID, CFE_EVS_EventType_INFORMATION, "BPACC_FUN: NOOP command %s",
                      BPACC_FUN_VERSION);

    return CFE_SUCCESS;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/*  Purpose:                                                                  */
/*         This function resets all the global counter variables that are     */
/*         part of the task telemetry.                                        */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
CFE_Status_t BPACC_FUN_ResetCountersCmd(const BPACC_FUN_ResetCountersCmd_t *Msg)
{
    BPACC_FUN_Data.CmdCounter = 0;
    BPACC_FUN_Data.ErrCounter = 0;

    CFE_EVS_SendEvent(BPACC_FUN_RESET_INF_EID, CFE_EVS_EventType_INFORMATION, "BPACC_FUN: RESET command");

    return CFE_SUCCESS;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/*  Purpose:                                                                  */
/*         This function Process Ground Station Command                       */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
CFE_Status_t BPACC_FUN_ProcessCmd(const BPACC_FUN_ProcessCmd_t *Msg)
{
    CFE_Status_t               status;
    void *                     TblAddr;
    BPACC_FUN_ExampleTable_t *TblPtr;
    const char *               TableName = "BPACC_FUN.ExampleTable";

    /* BPACC_FUN Use of Example Table */

    status = CFE_TBL_GetAddress(&TblAddr, BPACC_FUN_Data.TblHandles[0]);

    if (status < CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("BPACC_FUN App: Fail to get table address: 0x%08lx", (unsigned long)status);
        return status;
    }

    TblPtr = TblAddr;
    CFE_ES_WriteToSysLog("BPACC_FUN App: Example Table Value 1: %d  Value 2: %d", TblPtr->Int1, TblPtr->Int2);

    BPACC_FUN_GetCrc(TableName);

    status = CFE_TBL_ReleaseAddress(BPACC_FUN_Data.TblHandles[0]);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("BPACC_FUN App: Fail to release table address: 0x%08lx", (unsigned long)status);
        return status;
    }

    /* Call BPAccel Here */

    return CFE_SUCCESS;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* A simple example command that displays a passed-in value                   */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
CFE_Status_t BPACC_FUN_DisplayParamCmd(const BPACC_FUN_DisplayParamCmd_t *Msg)
{
    CFE_EVS_SendEvent(BPACC_FUN_VALUE_INF_EID, CFE_EVS_EventType_INFORMATION,
                      "BPACC_FUN: ValU32=%lu, ValI16=%d, ValStr=%s", (unsigned long)Msg->Payload.ValU32,
                      (int)Msg->Payload.ValI16, Msg->Payload.ValStr);

    return CFE_SUCCESS;
}
