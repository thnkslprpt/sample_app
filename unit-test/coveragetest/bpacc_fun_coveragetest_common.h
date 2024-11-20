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
 * Common definitions for all bpacc_fun coverage tests
 */

#ifndef BPACC_FUN_COVERAGETEST_COMMON_H
#define BPACC_FUN_COVERAGETEST_COMMON_H

/*
 * Includes
 */

#include "utassert.h"
#include "uttest.h"
#include "utstubs.h"

#include "setup.h"
#include "eventcheck.h"

#include "cfe.h"
#include "bpacc_fun_eventids.h"
#include "bpacc_fun.h"
#include "bpacc_fun_dispatch.h"
#include "bpacc_fun_cmds.h"
#include "bpacc_fun_utils.h"
#include "bpacc_fun_msgids.h"
#include "bpacc_fun_msg.h"
#include "bpacc_fun_tbl.h"

/*
 * Macro to add a test case to the list of tests to execute
 */
#define ADD_TEST(test) UtTest_Add((Test_##test), BPACC_FUN_UT_Setup, BPACC_FUN_UT_TearDown, #test)

#endif /* BPACC_FUN_COVERAGETEST_COMMON_H */
