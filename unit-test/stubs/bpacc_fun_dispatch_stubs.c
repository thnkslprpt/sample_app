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
 * @file
 *
 * Auto-Generated stub implementations for functions defined in bpacc_fun_dispatch header
 */

#include "bpacc_fun_dispatch.h"
#include "utgenstub.h"

/*
 * ----------------------------------------------------
 * Generated stub function for BPACC_FUN_ProcessGroundCommand()
 * ----------------------------------------------------
 */
void BPACC_FUN_ProcessGroundCommand(const CFE_SB_Buffer_t *SBBufPtr)
{
    UT_GenStub_AddParam(BPACC_FUN_ProcessGroundCommand, const CFE_SB_Buffer_t *, SBBufPtr);

    UT_GenStub_Execute(BPACC_FUN_ProcessGroundCommand, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for BPACC_FUN_TaskPipe()
 * ----------------------------------------------------
 */
void BPACC_FUN_TaskPipe(const CFE_SB_Buffer_t *SBBufPtr)
{
    UT_GenStub_AddParam(BPACC_FUN_TaskPipe, const CFE_SB_Buffer_t *, SBBufPtr);

    UT_GenStub_Execute(BPACC_FUN_TaskPipe, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for BPACC_FUN_VerifyCmdLength()
 * ----------------------------------------------------
 */
bool BPACC_FUN_VerifyCmdLength(const CFE_MSG_Message_t *MsgPtr, size_t ExpectedLength)
{
    UT_GenStub_SetupReturnBuffer(BPACC_FUN_VerifyCmdLength, bool);

    UT_GenStub_AddParam(BPACC_FUN_VerifyCmdLength, const CFE_MSG_Message_t *, MsgPtr);
    UT_GenStub_AddParam(BPACC_FUN_VerifyCmdLength, size_t, ExpectedLength);

    UT_GenStub_Execute(BPACC_FUN_VerifyCmdLength, Basic, NULL);

    return UT_GenStub_GetReturnValue(BPACC_FUN_VerifyCmdLength, bool);
}
