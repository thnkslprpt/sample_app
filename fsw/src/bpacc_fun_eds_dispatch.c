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

#include "bpacc_fun_eds_dispatcher.h"
#include "bpacc_fun_eds_dictionary.h"

/*
 * Define a lookup table for BPACC_FUN app command codes
 */
static const EdsDispatchTable_BPACC_FUN_Application_CFE_SB_Telecommand_t BPACC_FUN_TC_DISPATCH_TABLE = {
    .CMD     = {.NoopCmd_indication          = BPACC_FUN_NoopCmd,
            .ResetCountersCmd_indication = BPACC_FUN_ResetCountersCmd,
            .ProcessCmd_indication       = BPACC_FUN_ProcessCmd,
            .DisplayParamCmd_indication  = BPACC_FUN_DisplayParamCmd},
    .SEND_HK = {.indication = BPACC_FUN_SendHkCmd}};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/*  Purpose:                                                                  */
/*     This routine will process any packet that is received on the BPACC_FUN    */
/*     command pipe.                                                          */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
void BPACC_FUN_TaskPipe(const CFE_SB_Buffer_t *SBBufPtr)
{
    CFE_Status_t      Status;
    CFE_SB_MsgId_t    MsgId;
    CFE_MSG_Size_t    MsgSize;
    CFE_MSG_FcnCode_t MsgFc;

    Status = EdsDispatch_BPACC_FUN_Application_Telecommand(SBBufPtr, &BPACC_FUN_TC_DISPATCH_TABLE);

    if (Status != CFE_SUCCESS)
    {
        CFE_MSG_GetMsgId(&SBBufPtr->Msg, &MsgId);
        CFE_MSG_GetSize(&SBBufPtr->Msg, &MsgSize);
        CFE_MSG_GetFcnCode(&SBBufPtr->Msg, &MsgFc);
        ++BPACC_FUN_Data.ErrCounter;

        if (Status == CFE_STATUS_UNKNOWN_MSG_ID)
        {
            CFE_EVS_SendEvent(BPACC_FUN_MID_ERR_EID, CFE_EVS_EventType_ERROR,
                              "BPACC_FUN: invalid command packet,MID = 0x%x", (unsigned int)CFE_SB_MsgIdToValue(MsgId));
        }
        else if (Status == CFE_STATUS_WRONG_MSG_LENGTH)
        {
            CFE_EVS_SendEvent(BPACC_FUN_CMD_LEN_ERR_EID, CFE_EVS_EventType_ERROR,
                              "Invalid Msg length: ID = 0x%X,  CC = %u, Len = %u",
                              (unsigned int)CFE_SB_MsgIdToValue(MsgId), (unsigned int)MsgFc, (unsigned int)MsgSize);
        }
        else
        {
            CFE_EVS_SendEvent(BPACC_FUN_CC_ERR_EID, CFE_EVS_EventType_ERROR,
                              "BPACC_FUN: Invalid ground command code: CC = %d", (int)MsgFc);
        }
    }
}
