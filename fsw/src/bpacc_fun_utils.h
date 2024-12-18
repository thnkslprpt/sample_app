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
 *   This file contains the prototypes for the BPACC_FUN App utility functions
 */

#ifndef BPACC_FUN_UTILS_H
#define BPACC_FUN_UTILS_H

/*
** Required header files.
*/
#include "bpacc_fun.h"

CFE_Status_t BPACC_FUN_TblValidationFunc(void *TblData);
void         BPACC_FUN_GetCrc(const char *TableName);

#endif /* BPACC_FUN_UTILS_H */