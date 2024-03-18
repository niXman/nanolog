
// Copyright (c) 2015-2024 niXman (i dot nixman dog gmail dot com). All
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

#ifndef __NANOLOG__NANOLOG_HPP__INCLUDED
#define __NANOLOG__NANOLOG_HPP__INCLUDED

#ifndef NNL_DISABLE_LOGGING

#if __cplusplus < 202002L
#   error "C++20 is required!"
#endif // __cplusplus <= 202002L

/***************************************************************************/

#include <format>
#include <exception>
#include <cassert>

#if defined(NNL_USE_STDIO)
#   include <cstdio>
#   define __NNL_STREAM_TYPE ::std::FILE*
#   define __NNL_OSTREAM_ITERATOR ::NNL::ostream_iterator
#else
#   include <fstream>
#   include <iterator>
#   define __NNL_STREAM_TYPE ::std::ostream&
#   define __NNL_OSTREAM_ITERATOR ::std::ostream_iterator<char>
#endif // NNL_USE_STDIO

#if !defined(NNL_SHORT_FILEPATH)
#   define __NNL_FILEPATH(file) file
#else
#   define __NNL_FILEPATH(file) ::NNL::search_sep(file, sizeof(file)-1)
#endif // NNL_SHORT_FILEPATH

#if !defined(NNL_DONT_SHOW_DATETIME)
#   include <chrono>
#   define NNL_DATE_FORMAT_DMY (0) // day.month.year
#   define NNL_DATE_FORMAT_YMD (1) // year.month.day
#   define NNL_DATE_FORMAT_MDY (2) // month.day.year
#   ifndef NNL_DATE_FORMAT
#       define NNL_DATE_FORMAT NNL_DATE_FORMAT_YMD
#   endif // NNL_DATE_FORMAT
#   if !(NNL_DATE_FORMAT == NNL_DATE_FORMAT_DMY || \
            NNL_DATE_FORMAT == NNL_DATE_FORMAT_YMD || \
            NNL_DATE_FORMAT == NNL_DATE_FORMAT_MDY)
#       error "bad NNL_DATE_FORMAT"
#   endif
#endif // NNL_DONT_SHOW_DATETIME

/***************************************************************************/

#define __NNL_ARG16(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, ...) _16
#define __NNL_HAS_COMMA(...) __NNL_ARG16(__VA_ARGS__, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0)
#define __NNL__TRIGGER_PARENTHESIS_(...) ,
#define __NNL_PASTE5(_0, _1, _2, _3, _4) _0 ## _1 ## _2 ## _3 ## _4
#define __NNL__IS_EMPTY_CASE_0001 ,
#define __NNL__IS_EMPTY(_0, _1, _2, _3) __NNL_HAS_COMMA(__NNL_PASTE5(__NNL__IS_EMPTY_CASE_, _0, _1, _2, _3))
#define __NNL_TUPLE_IS_EMPTY(...) \
    __NNL__IS_EMPTY( \
        __NNL_HAS_COMMA(__VA_ARGS__), \
        __NNL_HAS_COMMA(__NNL__TRIGGER_PARENTHESIS_ __VA_ARGS__), \
        __NNL_HAS_COMMA(__VA_ARGS__ (/*empty*/)), \
        __NNL_HAS_COMMA(__NNL__TRIGGER_PARENTHESIS_ __VA_ARGS__ (/*empty*/)) \
    )

/***************************************************************************/

#define __NNL_IIF(bit, t, f) __NNL_IIF_I(bit, t, f)
#define __NNL_IIF_I(bit, t, f) __NNL_IIF_ ## bit(t, f)
#define __NNL_IIF_0(t, f) f
#define __NNL_IIF_1(t, f) t
#define __NNL_IF(cond, t, f) __NNL_IIF(cond, t, f)

#define ___NNL_STRINGIZE(x) #x
#define __NNL_STRINGIZE(x) ___NNL_STRINGIZE(x)

#define __NNL_CAT_I(a, b) a ## b
#define __NNL_CAT(a, b) __NNL_CAT_I(a, b)

#define __NNL_NARG(...) \
    __NNL_NARG_(__VA_ARGS__,__NNL_RSEQ_N())
#define __NNL_NARG_(...) \
    __NNL_ARG_N(__VA_ARGS__)
#define __NNL_ARG_N( \
    _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
    _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
    _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
    _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
    _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
    _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
    _61,_62,_63,N,...) N
#define __NNL_RSEQ_N() \
    63,62,61,60,                   \
    59,58,57,56,55,54,53,52,51,50, \
    49,48,47,46,45,44,43,42,41,40, \
    39,38,37,36,35,34,33,32,31,30, \
    29,28,27,26,25,24,23,22,21,20, \
    19,18,17,16,15,14,13,12,11,10, \
    9,8,7,6,5,4,3,2,1,0

#define __NNL_ENUM_ARGS_0()
#define __NNL_ENUM_ARGS_1(_1) ,(_1)
#define __NNL_ENUM_ARGS_2(_1, _2) \
    __NNL_ENUM_ARGS_1(_1) __NNL_ENUM_ARGS_1(_2)
#define __NNL_ENUM_ARGS_3(_1, _2, _3) \
    __NNL_ENUM_ARGS_2(_1, _2) __NNL_ENUM_ARGS_1(_3)
#define __NNL_ENUM_ARGS_4(_1, _2, _3, _4) \
    __NNL_ENUM_ARGS_3(_1, _2, _3) __NNL_ENUM_ARGS_1(_4)
#define __NNL_ENUM_ARGS_5(_1, _2, _3, _4, _5) \
    __NNL_ENUM_ARGS_4(_1, _2, _3, _4) __NNL_ENUM_ARGS_1(_5)
#define __NNL_ENUM_ARGS_6(_1, _2, _3, _4, _5, _6) \
    __NNL_ENUM_ARGS_5(_1, _2, _3, _4, _5) __NNL_ENUM_ARGS_1(_6)
#define __NNL_ENUM_ARGS_7(_1, _2, _3, _4, _5, _6, _7) \
    __NNL_ENUM_ARGS_6(_1, _2, _3, _4, _5, _6) __NNL_ENUM_ARGS_1(_7)
#define __NNL_ENUM_ARGS_8(_1, _2, _3, _4, _5, _6, _7, _8) \
    __NNL_ENUM_ARGS_7(_1, _2, _3, _4, _5, _6, _7) __NNL_ENUM_ARGS_1(_8)
#define __NNL_ENUM_ARGS_9(_1, _2, _3, _4, _5, _6, _7, _8, _9) \
    __NNL_ENUM_ARGS_8(_1, _2, _3, _4, _5, _6, _7, _8) __NNL_ENUM_ARGS_1(_9)
#define __NNL_ENUM_ARGS_10(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10) \
    __NNL_ENUM_ARGS_9(_1, _2, _3, _4, _5, _6, _7, _8, _9) __NNL_ENUM_ARGS_1(_10)
#define __NNL_ENUM_ARGS_11(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) \
    __NNL_ENUM_ARGS_10(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10) __NNL_ENUM_ARGS_1(_11)
#define __NNL_ENUM_ARGS_12(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) \
    __NNL_ENUM_ARGS_11(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) __NNL_ENUM_ARGS_1(_12)
#define __NNL_ENUM_ARGS_13(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) \
    __NNL_ENUM_ARGS_12(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) __NNL_ENUM_ARGS_1(_13)
#define __NNL_ENUM_ARGS_14(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) \
    __NNL_ENUM_ARGS_13(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) __NNL_ENUM_ARGS_1(_14)
#define __NNL_ENUM_ARGS_15(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) \
    __NNL_ENUM_ARGS_14(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) __NNL_ENUM_ARGS_1(_15)
#define __NNL_ENUM_ARGS_16(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) \
    __NNL_ENUM_ARGS_15(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) __NNL_ENUM_ARGS_1(_16)

#define __NNL_ENUM_ARGS_IMPL(n, ...) \
    __NNL_CAT(__NNL_ENUM_ARGS_, n)(__VA_ARGS__)
#define __NNL_ENUM_ARGS(...) \
    __NNL_ENUM_ARGS_IMPL(__NNL_NARG(__VA_ARGS__), __VA_ARGS__)

/***************************************************************************/

#define __NNL_FMT_ERROR_LVL(lvl) static_cast<char>(lvl)

#if !defined(NNL_DONT_SHOW_DATETIME)
#   define  __NNL_MAKE_FMT_STRING() \
        "{}({: >4s})[{:23s}][{:c}]: "
#   define  __NNL_MAKE_FMT_STRING_ARGS(file, line, lvl) \
        __NNL_FILEPATH(file), line, ::NNL::datetime_str(), __NNL_FMT_ERROR_LVL(lvl)
#else // !NNL_DONT_SHOW_DATETIME
#   define  __NNL_MAKE_FMT_STRING() \
        "{}({: >4s})[{:c}]: "
#   define  __NNL_MAKE_FMT_STRING_ARGS(file, line, lvl) \
        __NNL_FILEPATH(file), line, __NNL_FMT_ERROR_LVL(lvl)
#endif // NNL_DONT_SHOW_DATETIME

/***************************************************************************/

namespace NNL {

/***************************************************************************/

#if defined(NNL_SHORT_FILEPATH)
#   ifdef _WIN32
#       define __NNL_FILEPATH_SEP '\\'
#   else
#       define __NNL_FILEPATH_SEP '/'
#   endif // _WIN32

consteval const char* search_sep(const char *fpath, std::size_t len) {
    const char *end = fpath + len;
    for ( ; len && *end != __NNL_FILEPATH_SEP; --len, --end )
        ;

    return end+1;
}

#endif // NNL_SHORT_FILEPATH

/***************************************************************************/

#if defined(NNL_USE_STDIO)

struct ostream_iterator {
    std::FILE *m_fp;

    using difference_type = std::ptrdiff_t;

    ostream_iterator& operator= (const char &ch) noexcept
    { std::putc(ch, m_fp); return *this;}
    ostream_iterator& operator*  () noexcept { return *this; }
    ostream_iterator& operator++ () noexcept { return *this; }
    ostream_iterator& operator++ (int) noexcept { return *this; }
};

#endif // NNL_USE_STDIO

/***************************************************************************/

#if !defined(NNL_DONT_SHOW_DATETIME)

#ifdef NNL_CONSIDER_TIMEZONE
static struct __init {
    __init() {
        std::time_t t = std::time(0);
        std::tm *lt = std::localtime(&t);
        (void)lt;
    }
} __g_init;
#endif // NNL_CONSIDER_TIMEZONE

inline const char* datetime_str() {
    struct ops {
        static std::size_t num_chars(std::size_t v) {
            std::size_t n = 1;
            v = (v >= 100000000000000000ull) ? ((n += 17),v / 100000000000000000ull) : v;
            v = (v >= 100000000ull) ? ((n += 8),v / 100000000ull) : v;
            v = (v >= 10000ull) ? ((n += 4),v / 10000ull) : v;
            v = (v >= 100ull) ? ((n += 2),v / 100ull) : v;
            n = (v >= 10ull) ? n + 1 : n;

            return n;
        }
        static void utoa(char *ptr, std::size_t n, std::size_t v) {
            char *p = ptr + n - 1;
            switch ( n ) {
                case 20: *p-- = static_cast<char>('0'+(v % 10)); v /= 10; // fallthrough
                case 19: *p-- = static_cast<char>('0'+(v % 10)); v /= 10; // fallthrough
                case 18: *p-- = static_cast<char>('0'+(v % 10)); v /= 10; // fallthrough
                case 17: *p-- = static_cast<char>('0'+(v % 10)); v /= 10; // fallthrough
                case 16: *p-- = static_cast<char>('0'+(v % 10)); v /= 10; // fallthrough
                case 15: *p-- = static_cast<char>('0'+(v % 10)); v /= 10; // fallthrough
                case 14: *p-- = static_cast<char>('0'+(v % 10)); v /= 10; // fallthrough
                case 13: *p-- = static_cast<char>('0'+(v % 10)); v /= 10; // fallthrough
                case 12: *p-- = static_cast<char>('0'+(v % 10)); v /= 10; // fallthrough
                case 11: *p-- = static_cast<char>('0'+(v % 10)); v /= 10; // fallthrough
                case 10: *p-- = static_cast<char>('0'+(v % 10)); v /= 10; // fallthrough
                case 9 : *p-- = static_cast<char>('0'+(v % 10)); v /= 10; // fallthrough
                case 8 : *p-- = static_cast<char>('0'+(v % 10)); v /= 10; // fallthrough
                case 7 : *p-- = static_cast<char>('0'+(v % 10)); v /= 10; // fallthrough
                case 6 : *p-- = static_cast<char>('0'+(v % 10)); v /= 10; // fallthrough
                case 5 : *p-- = static_cast<char>('0'+(v % 10)); v /= 10; // fallthrough
                case 4 : *p-- = static_cast<char>('0'+(v % 10)); v /= 10; // fallthrough
                case 3 : *p-- = static_cast<char>('0'+(v % 10)); v /= 10; // fallthrough
                case 2 : *p-- = static_cast<char>('0'+(v % 10)); v /= 10; // fallthrough
                case 1 : *p-- = static_cast<char>('0'+(v % 10)); // fallthrough
                default: break;
            }
        }

        static std::size_t datetime_str(char *ptr) {
            const std::uint64_t ts = std::chrono::duration_cast<
                std::chrono::nanoseconds
            >(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
            const std::size_t ss = (ts / 1'000'000'000ull);
            const std::size_t ms = (ts / 1'000'000ull) % 1000u;

            static const std::size_t SPD = 24 * 60 * 60;
            static const unsigned short spm[13] = {
                 0
                ,(31)
                ,(31 + 28)
                ,(31 + 28 + 31)
                ,(31 + 28 + 31 + 30)
                ,(31 + 28 + 31 + 30 + 31)
                ,(31 + 28 + 31 + 30 + 31 + 30)
                ,(31 + 28 + 31 + 30 + 31 + 30 + 31)
                ,(31 + 28 + 31 + 30 + 31 + 30 + 31 + 31)
                ,(31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30)
                ,(31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31)
                ,(31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30)
                ,(31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30 + 31)
            };
            static const auto is_leap_year = [](std::size_t t) {
                return (!(t % 4) && ((t % 100) || !(t % 400)));
            };

            std::size_t secs{}, mins{}, hours{}, years{}, mons{}, days{};
            std::size_t work = ss % SPD;

            secs = work % 60;
            work /= 60;
            mins = work % 60;
            hours = work / 60;
            work = ss / SPD;

            std::size_t i = 1970;
            for ( ; ; ++i ) {
                std::size_t k = is_leap_year(i) ? 366 : 365;
                if ( work >= k ) {
                    work -= k;
                } else {
                    break;
                }
            }
            years = i;

            days = 1;
            if ( is_leap_year(i) && (work > 58) ) {
                if (work == 59) {
                    days = 2;
                }
                work -= 1;
            }

            for ( i = 11; i && (spm[i] > work); --i )
                ;

            mons = i;
            days += work - spm[i];

            char *p = ptr;

#define __NNL_YEAR(p, v) \
    *p++ = (v / 1000) % 10 + '0'; \
    *p++ = (v / 100) % 10 + '0'; \
    *p++ = (v / 10) % 10 + '0'; \
    *p++ = (v) % 10 + '0';

#define __NNL_MONTH(p, v) \
    *p++ = ((v + 1) / 10) % 10 + '0'; \
    *p++ = ((v + 1)) % 10 + '0';

#define __NNL_DAY(p, v) \
    *p++ = (v / 10) % 10 + '0'; \
    *p++ = (v % 10) + '0';

            __NNL_YEAR(p, years);
            *p++ = '.';
            __NNL_MONTH(p, mons);
            *p++ = '.';
            __NNL_DAY(p, days);

#undef __NNL_YEAR
#undef __NNL_MONTH
#undef __NNL_DAY

            *p++ = '-';

            // 'timezone' is extern, declared in time.h
            hours += std::abs(timezone/(60*60));

#define __NNL_HMS(p, v) \
    *p++ = (v / 10) % 10 + '0'; \
    *p++ = v % 10 + '0';

            __NNL_HMS(p, hours);
            *p++ = ':';
            __NNL_HMS(p, mins);
            *p++ = ':';
            __NNL_HMS(p, secs);

#undef __NNL_HMS

            // milliseconds
            if ( ms ) {
                *p++ = '.';
                std::size_t n = num_chars(ms);
                char *s = p;
                for ( auto i = 0u; i < n; ++i, ++s )
                    *s = '0';
                p += 3 - n;
                utoa(p, n, ms);
                p += n;
            }

            return p-ptr;
        }
    };

    thread_local char buf[24];
    auto len = ops::datetime_str(buf);
    buf[len] = 0;

    return buf;
}

#endif // NNL_DONT_SHOW_DATETIME

enum elevel {
     info    = 'I'
    ,debug   = 'D'
    ,warning = 'W'
    ,error   = 'E'
};

} // ns NNL

/***************************************************************************/

#if defined(NNL_USE_STDIO)
#   if defined(NNL_FLUSH_EACH_RECORD)
#       define __NNL_FLUSH_FUNC(os) ::std::fflush(os);
#   else
#       define __NNL_FLUSH_FUNC(os)
#   endif
#   define __NNL_CREATE_LOG_STREAM(sname, path) \
        __NNL_STREAM_TYPE sname = ::std::fopen(path, "a+b"); \
        assert(sname != nullptr);
#   define __NNL_CLOSE_LOG_STREAM(sname) \
        if ( sname ) { ::std::fclose(sname); sname = nullptr; }
#else
#   if defined(NNL_FLUSH_EACH_RECORD)
#       define __NNL_FLUSH_FUNC(os) os << ::std::flush;
#   else
#       define __NNL_FLUSH_FUNC(os)
#   endif
#   define __NNL_CREATE_LOG_STREAM(sname, path) \
        ::std::ofstream sname(path, ::std::ios::out|::std::ios::app|::std::ios::binary); \
        assert(sname.is_open());
#   define __NNL_CLOSE_LOG_STREAM(sname) \
        if ( sname.is_open() ) { sname.close(); }
#endif

#define __NNL_WITHOUT_ARGS(os, file, line, lvl, fmt, ...) \
    ::std::format_to( \
         __NNL_OSTREAM_ITERATOR(os) \
        ,__NNL_MAKE_FMT_STRING() "{}" \
        ,__NNL_MAKE_FMT_STRING_ARGS(file, line, lvl) \
        ,fmt \
    );

#define __NNL_WITH_ARGS(os, file, line, lvl, fmt, ...) \
    ::std::format_to( \
         __NNL_OSTREAM_ITERATOR(os) \
        ,__NNL_MAKE_FMT_STRING() fmt \
        ,__NNL_MAKE_FMT_STRING_ARGS(file, line, lvl) \
        __NNL_ENUM_ARGS(__VA_ARGS__) \
    );

#define __NNL_LOG(os, lvl, fmt, ...) \
    do { \
        static constexpr const char fname[] = __FILE__; \
        static constexpr const char fline[] = __NNL_STRINGIZE(__LINE__); \
        __NNL_IF( \
             __NNL_TUPLE_IS_EMPTY(__VA_ARGS__) \
            ,__NNL_WITHOUT_ARGS \
            ,__NNL_WITH_ARGS \
        )(os, fname, fline, lvl, fmt, __VA_ARGS__) \
        __NNL_FLUSH_FUNC(os) \
    } while(0);

/***************************************************************************/

#   if !defined(NNL_DISABLE_LOG_INFO)
#       define NNL_LOGI(os, fmt, ...) __NNL_LOG(os, ::NNL::info, fmt, __VA_ARGS__)
#       define NNL_LOG_INFO(os, fmt, ...) NNL_LOGI(os, fmt, __VA_ARGS__)
#       define NNL_LOGI_IF(expr, os, fmt, ...) if (expr) NNL_LOGI(os, fmt, __VA_ARGS__)
#       define NNL_LOG_INFO_IF(expr, os, fmt, ...) if (expr) NNL_LOGI(os, fmt, __VA_ARGS__)
#   else // !NNL_DISABLE_LOG_INFO
#       define NNL_LOGI(os, fmt, ...)
#       define NNL_LOG_INFO(os, fmt, ...)
#       define NNL_LOGI_IF(expr, os, fmt, ...)
#       define NNL_LOG_INFO_IF(expr, os, fmt, ...)
#   endif // NNL_DISABLE_LOG_INFO
#   if !defined(NNL_DISABLE_LOG_DEBUG)
#       define NNL_LOGD(os, fmt, ...) __NNL_LOG(os, ::NNL::debug, fmt, __VA_ARGS__)
#       define NNL_LOG_DEBUG(os, fmt, ...) NNL_LOGD(os, fmt, __VA_ARGS__)
#       define NNL_LOGD_IF(expr, os, fmt, ...) if (expr) NNL_LOGD(os, fmt, __VA_ARGS__)
#       define NNL_LOG_DEBUG_IF(expr, os, fmt, ...) if (expr) NNL_LOGD(os, fmt, __VA_ARGS__)
#   else // !NNL_DISABLE_LOG_DEBUG
#       define NNL_LOGD(os, fmt, ...)
#       define NNL_LOG_DEBUG(os, fmt, ...)
#       define NNL_LOGD_IF(expr, os, fmt, ...)
#       define NNL_LOG_DEBUG_IF(expr, os, fmt, ...)
#   endif // NNL_DISABLE_LOG_DEBUG
#   if !defined(NNL_DISABLE_LOG_WARNING)
#       define NNL_LOGW(os, fmt, ...) __NNL_LOG(os, ::NNL::warning, fmt, __VA_ARGS__)
#       define NNL_LOG_WARNING(os, fmt, ...) NNL_LOGW(os, fmt, __VA_ARGS__)
#       define NNL_LOGW_IF(expr, os, fmt, ...) if (expr) NNL_LOGW(os, fmt, __VA_ARGS__)
#       define NNL_LOG_WARNING_IF(expr, os, fmt, ...) if (expr) NNL_LOGW(os, fmt, __VA_ARGS__)
#   else // !NNL_DISABLE_LOG_WARNING
#       define NNL_LOGW(os, fmt, ...)
#       define NNL_LOG_WARNING(os, fmt, ...)
#       define NNL_LOGW_IF(expr, os, fmt, ...)
#       define NNL_LOG_WARNING_IF(expr, os, fmt, ...)
#   endif // NNL_DISABLE_LOG_WARNING
#   if !defined(NNL_DISABLE_LOG_ERROR)
#       define NNL_LOGE(os, fmt, ...) __NNL_LOG(os, ::NNL::error, fmt, __VA_ARGS__)
#       define NNL_LOG_ERROR(os, fmt, ...) NNL_LOGE(os, fmt, __VA_ARGS__)
#       define NNL_LOGE_IF(expr, os, fmt, ...) if (expr) NNL_LOGE(os, fmt, __VA_ARGS__)
#       define NNL_LOG_ERROR_IF(expr, os, fmt, ...) if (expr) NNL_LOGE(os, fmt, __VA_ARGS__)
#   else // !NNL_DISABLE_LOG_ERROR
#       define NNL_LOGE(os, fmt, ...)
#       define NNL_LOG_ERROR(os, fmt, ...)
#       define NNL_LOGE_IF(expr, os, fmt, ...)
#       define NNL_LOG_ERROR_IF(expr, os, fmt, ...)
#   endif // NNL_DISABLE_LOG_ERROR

#   define NNL_TRY_CATCH(os, ...) \
        try { \
            __VA_ARGS__; \
        } catch (const std::exception &ex) { \
            NNL_LOGE(os, "std::exception: {}\n", ex.what()); \
        } catch (...) { \
            NNL_LOGE(os, "unknown exception\n"); \
        }
#   define NNL_TRY_CATCH_ABORT(os, ...) \
        try { \
            __VA_ARGS__; \
        } catch (const std::exception &ex) { \
            NNL_LOGE(os, "std::exception: {}\n", ex.what()); \
            std::abort(); \
        } catch (...) { \
            NNL_LOGE(os, "unknown exception\n"); \
            std::abort(); \
        }
#   define NNL_TRY_CATCH_RETHROW(os, ...) \
        try { \
            __VA_ARGS__; \
        } catch (const std::exception &ex) { \
            NNL_LOGE(os, "std::exception: {}\n", ex.what()); \
            throw; \
        } catch (...) { \
            NNL_LOGE(os, "unknown exception\n"); \
            throw; \
        }

#   define NNL_CREATE_LOG_STREAM(sname, path) __NNL_CREATE_LOG_STREAM(sname, path)
#   define NNL_CLOSE_LOG_STREAM(sname) __NNL_CLOSE_LOG_STREAM(sname)
#else // NNL_DISABLE_LOGGING
#   define NNL_LOGI(os, fmt, ...)
#   define NNL_LOGD(os, fmt, ...)
#   define NNL_LOGW(os, fmt, ...)
#   define NNL_LOGE(os, fmt, ...)

#   define NNL_LOG_INFO(os, fmt, ...)
#   define NNL_LOG_DEBUG(os, fmt, ...)
#   define NNL_LOG_WARNING(os, fmt, ...)
#   define NNL_LOG_ERROR(os, fmt, ...)

#   define NNL_LOGI_IF(expr, os, fmt, ...)
#   define NNL_LOGD_IF(expr, os, fmt, ...)
#   define NNL_LOGW_IF(expr, os, fmt, ...)
#   define NNL_LOGE_IF(expr, os, fmt, ...)

#   define NNL_LOG_INFO_IF(expr, os, fmt, ...)
#   define NNL_LOG_DEBUG_IF(expr, os, fmt, ...)
#   define NNL_LOG_WARNING_IF(expr, os, fmt, ...)
#   define NNL_LOG_ERROR_IF(expr, os, fmt, ...)

#   define NNL_TRY_CATCH(os, ...) { __VA_ARGS__; }
#   define NNL_TRY_CATCH_ABORT(os, ...) { __VA_ARGS__; }
#   define NNL_TRY_CATCH_RETHROW(os, ...) { __VA_ARGS__; }

#   define NNL_CREATE_LOG_STREAM(sname, path)
#   define NNL_CLOSE_LOG_STREAM(sname)
#endif // NNL_DISABLE_LOGGING

/***************************************************************************/

#endif // __NANOLOG__NANOLOG_HPP__INCLUDED
