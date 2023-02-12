
// Copyright (c) 2015-2023 niXman (i dot nixman dog gmail dot com). All
// rights reserved.
//
// This file is part of NANOLOG(https://github.com/niXman/nanolog) project.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//
//
// Boost Software License - Version 1.0 - August 17th, 2003
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#include <nanolog/nanolog.hpp>

#ifdef NNL_USE_STDIO
#   define NNL_TEST_STREAM stdout
#else
#   include <iostream>
#   define NNL_TEST_STREAM std::cout
#endif

/***************************************************************************/

int main() {
    NNL_LOGI(NNL_TEST_STREAM, "message without args\n")
    NNL_LOGI(NNL_TEST_STREAM, "message with one arg: \"{}\"\n", "arg0")
    NNL_LOGI(NNL_TEST_STREAM, "message with two args: \"{}\"-\"{}\"\n", "arg0", "arg1")
    NNL_LOGI(NNL_TEST_STREAM, "message with three args: \"{}\"-\"{}\"-\"{}\"\n", "arg0", "arg1", 33)

    NNL_LOGD(NNL_TEST_STREAM, "message without args\n")
    NNL_LOGD(NNL_TEST_STREAM, "message with one arg: \"{}\"\n", "arg0")
    NNL_LOGD(NNL_TEST_STREAM, "message with two args: \"{}\"-\"{}\"\n", "arg0", "arg1")
    NNL_LOGD(NNL_TEST_STREAM, "message with three args: \"{}\"-\"{}\"-\"{}\"\n", "arg0", "arg1", 33)

    NNL_LOGW(NNL_TEST_STREAM, "message without args\n")
    NNL_LOGW(NNL_TEST_STREAM, "message with one arg: \"{}\"\n", "arg0")
    NNL_LOGW(NNL_TEST_STREAM, "message with two args: \"{}\"-\"{}\"\n", "arg0", "arg1")
    NNL_LOGW(NNL_TEST_STREAM, "message with three args: \"{}\"-\"{}\"-\"{}\"\n", "arg0", "arg1", 33)

    NNL_LOGE(NNL_TEST_STREAM, "message without args\n")
    NNL_LOGE(NNL_TEST_STREAM, "message with one arg: \"{}\"\n", "arg0")
    NNL_LOGE(NNL_TEST_STREAM, "message with two args: \"{}\"-\"{}\"\n", "arg0", "arg1")
    NNL_LOGE(NNL_TEST_STREAM, "message with three args: \"{}\"-\"{}\"-\"{}\"\n", "arg0", "arg1", 33)

    NNL_LOGI_IF(0, NNL_TEST_STREAM, "message without args\n")
    NNL_LOGI_IF(0, NNL_TEST_STREAM, "message with one arg: \"{}\"\n", "arg0")
    NNL_LOGI_IF(0, NNL_TEST_STREAM, "message with two args: \"{}\"-\"{}\"\n", "arg0", "arg1")
    NNL_LOGI_IF(0, NNL_TEST_STREAM, "message with three args: \"{}\"-\"{}\"-\"{}\"\n", "arg0", "arg1", 33)
    NNL_LOGI_IF(1, NNL_TEST_STREAM, "message without args\n")
    NNL_LOGI_IF(1, NNL_TEST_STREAM, "message with one arg: \"{}\"\n", "arg0")
    NNL_LOGI_IF(1, NNL_TEST_STREAM, "message with two args: \"{}\"-\"{}\"\n", "arg0", "arg1")
    NNL_LOGI_IF(1, NNL_TEST_STREAM, "message with three args: \"{}\"-\"{}\"-\"{}\"\n", "arg0", "arg1", 33)

    NNL_LOGD_IF(0, NNL_TEST_STREAM, "message without args\n")
    NNL_LOGD_IF(0, NNL_TEST_STREAM, "message with one arg: \"{}\"\n", "arg0")
    NNL_LOGD_IF(0, NNL_TEST_STREAM, "message with two args: \"{}\"-\"{}\"\n", "arg0", "arg1")
    NNL_LOGD_IF(0, NNL_TEST_STREAM, "message with three args: \"{}\"-\"{}\"-\"{}\"\n", "arg0", "arg1", 33)
    NNL_LOGD_IF(1, NNL_TEST_STREAM, "message without args\n")
    NNL_LOGD_IF(1, NNL_TEST_STREAM, "message with one arg: \"{}\"\n", "arg0")
    NNL_LOGD_IF(1, NNL_TEST_STREAM, "message with two args: \"{}\"-\"{}\"\n", "arg0", "arg1")
    NNL_LOGD_IF(1, NNL_TEST_STREAM, "message with three args: \"{}\"-\"{}\"-\"{}\"\n", "arg0", "arg1", 33)

    NNL_LOGW_IF(0, NNL_TEST_STREAM, "message without args\n")
    NNL_LOGW_IF(0, NNL_TEST_STREAM, "message with one arg: \"{}\"\n", "arg0")
    NNL_LOGW_IF(0, NNL_TEST_STREAM, "message with two args: \"{}\"-\"{}\"\n", "arg0", "arg1")
    NNL_LOGW_IF(0, NNL_TEST_STREAM, "message with three args: \"{}\"-\"{}\"-\"{}\"\n", "arg0", "arg1", 33)
    NNL_LOGW_IF(1, NNL_TEST_STREAM, "message without args\n")
    NNL_LOGW_IF(1, NNL_TEST_STREAM, "message with one arg: \"{}\"\n", "arg0")
    NNL_LOGW_IF(1, NNL_TEST_STREAM, "message with two args: \"{}\"-\"{}\"\n", "arg0", "arg1")
    NNL_LOGW_IF(1, NNL_TEST_STREAM, "message with three args: \"{}\"-\"{}\"-\"{}\"\n", "arg0", "arg1", 33)

    NNL_LOGE_IF(0, NNL_TEST_STREAM, "message without args\n")
    NNL_LOGE_IF(0, NNL_TEST_STREAM, "message with one arg: \"{}\"\n", "arg0")
    NNL_LOGE_IF(0, NNL_TEST_STREAM, "message with two args: \"{}\"-\"{}\"\n", "arg0", "arg1")
    NNL_LOGE_IF(0, NNL_TEST_STREAM, "message with three args: \"{}\"-\"{}\"-\"{}\"\n", "arg0", "arg1", 33)
    NNL_LOGE_IF(1, NNL_TEST_STREAM, "message without args\n")
    NNL_LOGE_IF(1, NNL_TEST_STREAM, "message with one arg: \"{}\"\n", "arg0")
    NNL_LOGE_IF(1, NNL_TEST_STREAM, "message with two args: \"{}\"-\"{}\"\n", "arg0", "arg1")
    NNL_LOGE_IF(1, NNL_TEST_STREAM, "message with three args: \"{}\"-\"{}\"-\"{}\"\n", "arg0", "arg1", 33)

//    NNL_TRY_CATCH(NNL_TEST_STREAM, throw 1;) // will be catched and logged
//    NNL_TRY_CATCH_RETHROW(NNL_TEST_STREAM, throw 1;) // will be logged and rethrow`ed
//    NNL_TRY_CATCH_ABORT(NNL_TEST_STREAM, throw 1;) // will be logged and abort`ed

    NNL_CREATE_LOG_STREAM(log0, "log0.txt")
    NNL_LOGE(log0, "message with three args: \"{}\"-\"{}\"-\"{}\"\n", "arg0", "arg1", 66)
    NNL_CLOSE_LOG_STREAM(log0)
}

/***************************************************************************/
