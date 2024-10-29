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
 *   Specification for the BPACC_FUN command function codes
 *
 * @note
 *   This file should be strictly limited to the command/function code (CC)
 *   macro definitions.  Other definitions such as enums, typedefs, or other
 *   macros should be placed in the msgdefs.h or msg.h files.
 */
#ifndef BPACC_FUN_FCNCODES_H
#define BPACC_FUN_FCNCODES_H

/************************************************************************
 * Macro Definitions
 ************************************************************************/

/*
** BPACC_FUN App command codes
*/
#define BPACC_FUN_NOOP_CC           0
#define BPACC_FUN_RESET_COUNTERS_CC 1
#define BPACC_FUN_PROCESS_CC        2
#define BPACC_FUN_DISPLAY_PARAM_CC  3

#endif
