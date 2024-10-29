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
 *   This file contains the prototypes for the BPACC_FUN App Ground Command-handling functions
 */

#ifndef BPACC_FUN_CMDS_H
#define BPACC_FUN_CMDS_H

/*
** Required header files.
*/
#include "cfe_error.h"
#include "bpacc_fun_msg.h"

CFE_Status_t BPACC_FUN_SendHkCmd(const BPACC_FUN_SendHkCmd_t *Msg);
CFE_Status_t BPACC_FUN_ResetCountersCmd(const BPACC_FUN_ResetCountersCmd_t *Msg);
CFE_Status_t BPACC_FUN_ProcessCmd(const BPACC_FUN_ProcessCmd_t *Msg);
CFE_Status_t BPACC_FUN_NoopCmd(const BPACC_FUN_NoopCmd_t *Msg);
CFE_Status_t BPACC_FUN_DisplayParamCmd(const BPACC_FUN_DisplayParamCmd_t *Msg);

#endif /* BPACC_FUN_CMDS_H */
