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
#include "bpacc_fun_dispatch.h"
#include "bpacc_fun_cmds.h"
#include "bpacc_fun_eventids.h"
#include "bpacc_fun_msgids.h"
#include "bpacc_fun_msg.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* Verify command packet length                                               */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
bool BPACC_FUN_VerifyCmdLength(const CFE_MSG_Message_t *MsgPtr, size_t ExpectedLength)
{
    bool              result       = true;
    size_t            ActualLength = 0;
    CFE_SB_MsgId_t    MsgId        = CFE_SB_INVALID_MSG_ID;
    CFE_MSG_FcnCode_t FcnCode      = 0;

    CFE_MSG_GetSize(MsgPtr, &ActualLength);

    /*
    ** Verify the command packet length.
    */
    if (ExpectedLength != ActualLength)
    {
        CFE_MSG_GetMsgId(MsgPtr, &MsgId);
        CFE_MSG_GetFcnCode(MsgPtr, &FcnCode);

        CFE_EVS_SendEvent(BPACC_FUN_CMD_LEN_ERR_EID, CFE_EVS_EventType_ERROR,
                          "Invalid Msg length: ID = 0x%X,  CC = %u, Len = %u, Expected = %u",
                          (unsigned int)CFE_SB_MsgIdToValue(MsgId), (unsigned int)FcnCode, (unsigned int)ActualLength,
                          (unsigned int)ExpectedLength);

        result = false;

        BPACC_FUN_Data.ErrCounter++;
    }

    return result;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* BPACC_FUN ground commands                                                     */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
void BPACC_FUN_ProcessGroundCommand(const CFE_SB_Buffer_t *SBBufPtr)
{
    CFE_MSG_FcnCode_t CommandCode = 0;

    CFE_MSG_GetFcnCode(&SBBufPtr->Msg, &CommandCode);

    /*
    ** Process BPACC_FUN app ground commands
    */
    switch (CommandCode)
    {
        case BPACC_FUN_NOOP_CC:
            if (BPACC_FUN_VerifyCmdLength(&SBBufPtr->Msg, sizeof(BPACC_FUN_NoopCmd_t)))
            {
                BPACC_FUN_NoopCmd((const BPACC_FUN_NoopCmd_t *)SBBufPtr);
            }
            break;

        case BPACC_FUN_RESET_COUNTERS_CC:
            if (BPACC_FUN_VerifyCmdLength(&SBBufPtr->Msg, sizeof(BPACC_FUN_ResetCountersCmd_t)))
            {
                BPACC_FUN_ResetCountersCmd((const BPACC_FUN_ResetCountersCmd_t *)SBBufPtr);
            }
            break;

        case BPACC_FUN_PROCESS_CC:
            if (BPACC_FUN_VerifyCmdLength(&SBBufPtr->Msg, sizeof(BPACC_FUN_ProcessCmd_t)))
            {
                BPACC_FUN_ProcessCmd((const BPACC_FUN_ProcessCmd_t *)SBBufPtr);
            }
            break;

        case BPACC_FUN_DISPLAY_PARAM_CC:
            if (BPACC_FUN_VerifyCmdLength(&SBBufPtr->Msg, sizeof(BPACC_FUN_DisplayParamCmd_t)))
            {
                BPACC_FUN_DisplayParamCmd((const BPACC_FUN_DisplayParamCmd_t *)SBBufPtr);
            }
            break;

        /* default case already found during FC vs length test */
        default:
            CFE_EVS_SendEvent(BPACC_FUN_CC_ERR_EID, CFE_EVS_EventType_ERROR, "Invalid ground command code: CC = %d",
                              CommandCode);
            break;
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/*  Purpose:                                                                  */
/*     This routine will process any packet that is received on the BPACC_FUN    */
/*     command pipe.                                                          */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
void BPACC_FUN_TaskPipe(const CFE_SB_Buffer_t *SBBufPtr)
{
    CFE_SB_MsgId_t MsgId = CFE_SB_INVALID_MSG_ID;

    CFE_MSG_GetMsgId(&SBBufPtr->Msg, &MsgId);

    switch (CFE_SB_MsgIdToValue(MsgId))
    {
        case BPACC_FUN_CMD_MID:
            BPACC_FUN_ProcessGroundCommand(SBBufPtr);
            break;

        case BPACC_FUN_SEND_HK_MID:
            BPACC_FUN_SendHkCmd((const BPACC_FUN_SendHkCmd_t *)SBBufPtr);
            break;

        default:
            CFE_EVS_SendEvent(BPACC_FUN_MID_ERR_EID, CFE_EVS_EventType_ERROR,
                              "BPACC_FUN: invalid command packet,MID = 0x%x", (unsigned int)CFE_SB_MsgIdToValue(MsgId));
            break;
    }
}
