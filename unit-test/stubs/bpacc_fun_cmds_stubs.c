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
 * Auto-Generated stub implementations for functions defined in bpacc_fun_cmds header
 */

#include "bpacc_fun_cmds.h"
#include "utgenstub.h"

/*
 * ----------------------------------------------------
 * Generated stub function for BPACC_FUN_DisplayParamCmd()
 * ----------------------------------------------------
 */
CFE_Status_t BPACC_FUN_DisplayParamCmd(const BPACC_FUN_DisplayParamCmd_t *Msg)
{
    UT_GenStub_SetupReturnBuffer(BPACC_FUN_DisplayParamCmd, CFE_Status_t);

    UT_GenStub_AddParam(BPACC_FUN_DisplayParamCmd, const BPACC_FUN_DisplayParamCmd_t *, Msg);

    UT_GenStub_Execute(BPACC_FUN_DisplayParamCmd, Basic, NULL);

    return UT_GenStub_GetReturnValue(BPACC_FUN_DisplayParamCmd, CFE_Status_t);
}

/*
 * ----------------------------------------------------
 * Generated stub function for BPACC_FUN_NoopCmd()
 * ----------------------------------------------------
 */
CFE_Status_t BPACC_FUN_NoopCmd(const BPACC_FUN_NoopCmd_t *Msg)
{
    UT_GenStub_SetupReturnBuffer(BPACC_FUN_NoopCmd, CFE_Status_t);

    UT_GenStub_AddParam(BPACC_FUN_NoopCmd, const BPACC_FUN_NoopCmd_t *, Msg);

    UT_GenStub_Execute(BPACC_FUN_NoopCmd, Basic, NULL);

    return UT_GenStub_GetReturnValue(BPACC_FUN_NoopCmd, CFE_Status_t);
}

/*
 * ----------------------------------------------------
 * Generated stub function for BPACC_FUN_ProcessCmd()
 * ----------------------------------------------------
 */
CFE_Status_t BPACC_FUN_ProcessCmd(const BPACC_FUN_ProcessCmd_t *Msg)
{
    UT_GenStub_SetupReturnBuffer(BPACC_FUN_ProcessCmd, CFE_Status_t);

    UT_GenStub_AddParam(BPACC_FUN_ProcessCmd, const BPACC_FUN_ProcessCmd_t *, Msg);

    UT_GenStub_Execute(BPACC_FUN_ProcessCmd, Basic, NULL);

    return UT_GenStub_GetReturnValue(BPACC_FUN_ProcessCmd, CFE_Status_t);
}

/*
 * ----------------------------------------------------
 * Generated stub function for BPACC_FUN_ResetCountersCmd()
 * ----------------------------------------------------
 */
CFE_Status_t BPACC_FUN_ResetCountersCmd(const BPACC_FUN_ResetCountersCmd_t *Msg)
{
    UT_GenStub_SetupReturnBuffer(BPACC_FUN_ResetCountersCmd, CFE_Status_t);

    UT_GenStub_AddParam(BPACC_FUN_ResetCountersCmd, const BPACC_FUN_ResetCountersCmd_t *, Msg);

    UT_GenStub_Execute(BPACC_FUN_ResetCountersCmd, Basic, NULL);

    return UT_GenStub_GetReturnValue(BPACC_FUN_ResetCountersCmd, CFE_Status_t);
}

/*
 * ----------------------------------------------------
 * Generated stub function for BPACC_FUN_SendHkCmd()
 * ----------------------------------------------------
 */
CFE_Status_t BPACC_FUN_SendHkCmd(const BPACC_FUN_SendHkCmd_t *Msg)
{
    UT_GenStub_SetupReturnBuffer(BPACC_FUN_SendHkCmd, CFE_Status_t);

    UT_GenStub_AddParam(BPACC_FUN_SendHkCmd, const BPACC_FUN_SendHkCmd_t *, Msg);

    UT_GenStub_Execute(BPACC_FUN_SendHkCmd, Basic, NULL);

    return UT_GenStub_GetReturnValue(BPACC_FUN_SendHkCmd, CFE_Status_t);
}
