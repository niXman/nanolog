
// Copyright (c) 2015-2016 niXman (i dot nixman dog gmail dot com). All
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

/***************************************************************************/

#if !defined(NNL_USE_PRINTF) && !defined(NNL_USE_BOOST_FORMAT)
#define NNL_USE_PRINTF
#endif

#include <cassert>

#if defined(NNL_USE_PRINTF)
#  include <cstdio>
#  define __NNL_STREAM_TYPE ::std::FILE*
#elif defined(NNL_USE_BOOST_FORMAT)
#  include <boost/format.hpp>
#  include <fstream>
#  define __NNL_STREAM_TYPE ::std::ostream&
#else
#  error please define one of NNL_USE_PRINTF or NNL_USE_BOOST_FORMAT
#endif // NNL_USE_PRINTF

#ifdef NNL_USE_DATETIME
#  include <ctime>

#  define NNL_DATE_FORMAT_DMY (0) // day.month.year
#  define NNL_DATE_FORMAT_YMD (1) // year.month.day
#  define NNL_DATE_FORMAT_MDY (2) // month.day.year

#  ifndef NNL_DATE_FORMAT
#    define NNL_DATE_FORMAT NNL_DATE_FORMAT_YMD
#  endif // NNL_DATE_FORMAT

#  if !(NNL_DATE_FORMAT == NNL_DATE_FORMAT_DMY || \
        NNL_DATE_FORMAT == NNL_DATE_FORMAT_YMD || \
        NNL_DATE_FORMAT == NNL_DATE_FORMAT_MDY)
#    error "bad NNL_DATE_FORMAT"
#  endif
#endif // NNL_USE_DATETIME

#ifdef NNL_THREAD_SAFE
#  if NNL_THREAD_SAFE == 0 // pthread mutex
#    include <pthread.h>
#  elif NNL_THREAD_SAFE == 1 // std::mutex
#    include <mutex>
#  else
#    error bad "NNL_THREAD_SAFE" value == NNL_THREAD_SAFE
#  endif // NNL_THREAD_SAFE
#endif // NNL_THREAD_SAFE

/***************************************************************************/

#define __NNL_ARG16(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, ...) _15
#define __NNL_HAS_COMMA(...) __NNL_ARG16(__VA_ARGS__, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0)
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

/***************************************************************************/

#define ___NNL_STRINGIZE(x) #x
#define __NNL_STRINGIZE(x) ___NNL_STRINGIZE(x)

/***************************************************************************/

#define __NNL_CAT_I(a, b) a ## b
#define __NNL_CAT(a, b) __NNL_CAT_I(a, b)

/***************************************************************************/

#define __NNL_ENUM_0(x) x ## 0
#define __NNL_ENUM_1(x) x ## 0, x ## 1
#define __NNL_ENUM_2(x) x ## 0, x ## 1, x ## 2
#define __NNL_ENUM_3(x) x ## 0, x ## 1, x ## 2, x ## 3
#define __NNL_ENUM_4(x) x ## 0, x ## 1, x ## 2, x ## 3, x ## 4
#define __NNL_ENUM_5(x) x ## 0, x ## 1, x ## 2, x ## 3, x ## 4, x ## 5
#define __NNL_ENUM_6(x) x ## 0, x ## 1, x ## 2, x ## 3, x ## 4, x ## 5, x ## 6
#define __NNL_ENUM_7(x) x ## 0, x ## 1, x ## 2, x ## 3, x ## 4, x ## 5, x ## 6 \
  , x ## 7
#define __NNL_ENUM_8(x) x ## 0, x ## 1, x ## 2, x ## 3, x ## 4, x ## 5, x ## 6 \
  , x ## 7, x ## 8
#define __NNL_ENUM_9(x) x ## 0, x ## 1, x ## 2, x ## 3, x ## 4, x ## 5, x ## 6 \
  , x ## 7, x ## 8, x ## 9

#define __NNL_ENUM(x, n) \
    __NNL_CAT(__NNL_ENUM_, n)(x)

#define __NNL_ENUM_PAIR_0(l, sep, r) l ## 0 sep r ## 0
#define __NNL_ENUM_PAIR_1(l, sep, r) l ## 0 sep r ## 0, l ## 1 sep r ## 1
#define __NNL_ENUM_PAIR_2(l, sep, r) l ## 0 sep r ## 0, l ## 1 sep r ## 1 \
  , l ## 2 sep r ## 2
#define __NNL_ENUM_PAIR_3(l, sep, r) l ## 0 sep r ## 0, l ## 1 sep r ## 1 \
  , l ## 2 sep r ## 2, l ## 3 sep r ## 3
#define __NNL_ENUM_PAIR_4(l, sep, r) l ## 0 sep r ## 0, l ## 1 sep r ## 1 \
  , l ## 2 sep r ## 2, l ## 3 sep r ## 3, l ## 4 sep r ## 4
#define __NNL_ENUM_PAIR_5(l, sep, r) l ## 0 sep r ## 0, l ## 1 sep r ## 1 \
  , l ## 2 sep r ## 2, l ## 3 sep r ## 3, l ## 4 sep r ## 4, l ## 5 sep r ## 5
#define __NNL_ENUM_PAIR_6(l, sep, r) l ## 0 sep r ## 0, l ## 1 sep r ## 1 \
  , l ## 2 sep r ## 2, l ## 3 sep r ## 3, l ## 4 sep r ## 4, l ## 5 sep r ## 5 \
  , l ## 6 sep r ## 6
#define __NNL_ENUM_PAIR_7(l, sep, r) l ## 0 sep r ## 0, l ## 1 sep r ## 1 \
  , l ## 2 sep r ## 2, l ## 3 sep r ## 3, l ## 4 sep r ## 4, l ## 5 sep r ## 5 \
  , l ## 6 sep r ## 6, l ## 7 sep r ## 7
#define __NNL_ENUM_PAIR_8(l, sep, r) l ## 0 sep r ## 0, l ## 1 sep r ## 1 \
  , l ## 2 sep r ## 2, l ## 3 sep r ## 3, l ## 4 sep r ## 4, l ## 5 sep r ## 5 \
  , l ## 6 sep r ## 6, l ## 7 sep r ## 7, l ## 8 sep r ## 8
#define __NNL_ENUM_PAIR_9(l, sep, r) l ## 0 sep r ## 0, l ## 1 sep r ## 1 \
  , l ## 2 sep r ## 2, l ## 3 sep r ## 3, l ## 4 sep r ## 4, l ## 5 sep r ## 5 \
  , l ## 6 sep r ## 6, l ## 7 sep r ## 7, l ## 8 sep r ## 8, l ## 9 sep r ## 9

#define __NNL_ENUM_PAIR(l, sep, r, n) \
  __NNL_CAT(__NNL_ENUM_PAIR_, n)(l, sep, r)

#define __NNL_ENUM_BF_0(x) x ## 0
#define __NNL_ENUM_BF_1(x) x ## 0 % x ## 1
#define __NNL_ENUM_BF_2(x) x ## 0 % x ## 1 % x ## 2
#define __NNL_ENUM_BF_3(x) x ## 0 % x ## 1 % x ## 2 % x ## 3
#define __NNL_ENUM_BF_4(x) x ## 0 % x ## 1 % x ## 2 % x ## 3 % x ## 4
#define __NNL_ENUM_BF_5(x) x ## 0 % x ## 1 % x ## 2 % x ## 3 % x ## 4 \
  % x ## 5
#define __NNL_ENUM_BF_6(x) x ## 0 % x ## 1 % x ## 2 % x ## 3 % x ## 4 \
  % x ## 5 % x ## 6
#define __NNL_ENUM_BF_7(x) x ## 0 % x ## 1 % x ## 2 % x ## 3 % x ## 4 \
  % x ## 5 % x ## 6 % x ## 7
#define __NNL_ENUM_BF_8(x) x ## 0 % x ## 1 % x ## 2 % x ## 3 % x ## 4 \
  % x ## 5 % x ## 6 % x ## 7 % x ## 8
#define __NNL_ENUM_BF_9(x) x ## 0 % x ## 1 % x ## 2 % x ## 3 % x ## 4 \
  % x ## 5 % x ## 6 % x ## 7 % x ## 8 % x ## 9

#define __NNL_ENUM_BF(x, n) \
  __NNL_CAT(__NNL_ENUM_BF_, n)(x)

/***************************************************************************/

#define __NNL_IS_ZERO_0 1
#define __NNL_IS_ZERO_1 0
#define __NNL_IS_ZERO_2 0
#define __NNL_IS_ZERO_3 0
#define __NNL_IS_ZERO_4 0
#define __NNL_IS_ZERO_5 0
#define __NNL_IS_ZERO_6 0
#define __NNL_IS_ZERO_7 0
#define __NNL_IS_ZERO_8 0
#define __NNL_IS_ZERO_9 0

#define __NNL_IS_ZERO(n) \
  __NNL_CAT(__NNL_IS_ZERO_, n)

/***************************************************************************/

#define __NNL_FMT_ERROR_LVL(lvl) \
  (lvl==::NNL::info?'I':lvl==::NNL::debug?'D':lvl==::NNL::warning?'W':'E')

#ifdef NNL_USE_DATETIME
# define  __NNL_MAKE_DATETIME_BUF() \
   char dtbuf[27] = {' '}; \
   dtbuf[26] = 0;
#  if defined(NNL_USE_PRINTF)
#    define  __NNL_MAKE_FMT_STRING() \
       "%s(%-5zu)[%c, %-26s]: "
#    define  __NNL_MAKE_ARGS_STRING(file, line, lvl) \
       file, line, __NNL_FMT_ERROR_LVL(lvl), datetime_str(dtbuf)
#  else // !NNL_USE_PRINTF
#    define  __NNL_MAKE_FMT_STRING() \
       ::boost::format("%s(%-5d)[%c, %-26s]: ") % file % line \
         % __NNL_FMT_ERROR_LVL(lvl) % datetime_str(dtbuf)
#    define  __NNL_MAKE_ARGS_STRING(file, line, lvl)
#  endif // NNL_USE_PRINTF
#else // !NNL_USE_DATETIME
#  define  __NNL_MAKE_DATETIME_BUF()
#  if defined(NNL_USE_PRINTF)
#    define  __NNL_MAKE_FMT_STRING() \
       "%s(%-5zu)[%c]: "
#    define  __NNL_MAKE_ARGS_STRING(file, line, lvl) \
       file, line, __NNL_FMT_ERROR_LVL(lvl)
#  else // !NNL_USE_PRINTF
#    define  __NNL_MAKE_FMT_STRING() \
       ::boost::format("%s(%-5d)[%c]: ") % file % line % __NNL_FMT_ERROR_LVL(lvl)
#    define  __NNL_MAKE_ARGS_STRING(file, line, lvl)
#  endif // NNL_USE_PRINTF
#endif // NNL_USE_DATETIME

#if defined(NNL_USE_PRINTF)
#  define __NNL_MAKE_WRITE_BODY(n) \
  __NNL_MAKE_DATETIME_BUF() \
  ::std::fprintf(os, __NNL_MAKE_FMT_STRING(), \
    __NNL_MAKE_ARGS_STRING(file, line, lvl)); \
  ::std::fprintf(os, fmt, __NNL_ENUM(arg, n));
#else
#  define __NNL_MAKE_WRITE_BODY(n) \
  __NNL_MAKE_DATETIME_BUF() \
  os << __NNL_MAKE_FMT_STRING() << ::boost::format(fmt) % __NNL_ENUM_BF(arg, n);
#endif // NNL_USE_PRINTF

#define __NNL_DECLARE_WRITE(n) \
    template<__NNL_ENUM(typename Arg, n)> \
    void write(__NNL_STREAM_TYPE os, const char *file, std::size_t line, elevel lvl \
               , const char *fmt,__NNL_ENUM_PAIR(const Arg, &, arg, n)) \
    { \
        __NNL_MAKE_WRITE_BODY(n) \
    }

/***************************************************************************/

namespace NNL {

/***************************************************************************/

#ifdef NNL_THREAD_SAFE
#  define __NNL_MUTEX_TYPE(m) ::NNL::mutex m;
#  define __NNL_LOCKGUARD_TYPE(l, m) ::NNL::lock_guard l(m);

#  if NNL_THREAD_SAFE == 0 // pthread

struct mutex {
    mutex() {
        ::pthread_mutex_init(&m, 0);
    }
    ~mutex() {
        unlock();
        ::pthread_mutex_destroy(&m);
    }
    
    void lock() { ::pthread_mutex_lock(&m); }
    void unlock() { ::pthread_mutex_unlock(&m); }

private:
    ::pthread_mutex_t m;
};

#  else // NNL_THREAD_SAFE == 1 // std::mutex

struct mutex {
    mutex()
        :m()
    {}
    ~mutex() {
        unlock();
    }
    
    void lock() { m.lock(); }
    void unlock() { m.unlock(); }

private:
    ::std::mutex m;
};

#  endif // NNL_THREAD_SAFE == 0 || NNL_THREAD_SAFE == 1

struct lock_guard {
    lock_guard(::NNL::mutex &m)
        :m(m)
    { m.lock(); }
    ~lock_guard()
    { m.unlock(); }

private:
    ::NNL::mutex &m;
};

#else
#  define __NNL_MUTEX_TYPE(m)
#  define __NNL_LOCKGUARD_TYPE(l, m)
#endif // NNL_THREAD_SAFE

/***************************************************************************/

#ifdef NNL_USE_DATETIME

struct __init {
  __init() {
    std::time_t t = time(0);
    std::tm *lt = localtime(&t);
    (void)lt;
  }
} __g_init;

inline const char* datetime_str(char *buf) {
  struct ops {
    static long long abs(long long v) { return v < 0 ? -v : v; }

    static std::size_t itoa(char *ptr, long long v) {
      if ( v < 0 ) { *ptr++ = '-'; }
      long long t = v = abs(v);

      std::size_t len = 1;
      if ( t >= 10000000000000000ll ) { len += 16; t /= 10000000000000000ll; }
      if ( t >= 100000000 ) { len += 8; t /= 100000000; }
      if ( t >= 10000 ) { len += 4; t /= 10000; }
      if ( t >= 100 ) { len += 2; t /= 100; }
      if ( t >= 10 ) { len += 1; }

      char *p = ptr+len-1;
      switch ( len ) {
        case 19: *p-- = '0' + (v % 10); v /= 10;
        case 18: *p-- = '0' + (v % 10); v /= 10;
        case 17: *p-- = '0' + (v % 10); v /= 10;
        case 16: *p-- = '0' + (v % 10); v /= 10;
        case 15: *p-- = '0' + (v % 10); v /= 10;
        case 14: *p-- = '0' + (v % 10); v /= 10;
        case 13: *p-- = '0' + (v % 10); v /= 10;
        case 12: *p-- = '0' + (v % 10); v /= 10;
        case 11: *p-- = '0' + (v % 10); v /= 10;
        case 10: *p-- = '0' + (v % 10); v /= 10;
        case 9 : *p-- = '0' + (v % 10); v /= 10;
        case 8 : *p-- = '0' + (v % 10); v /= 10;
        case 7 : *p-- = '0' + (v % 10); v /= 10;
        case 6 : *p-- = '0' + (v % 10); v /= 10;
        case 5 : *p-- = '0' + (v % 10); v /= 10;
        case 4 : *p-- = '0' + (v % 10); v /= 10;
        case 3 : *p-- = '0' + (v % 10); v /= 10;
        case 2 : *p-- = '0' + (v % 10); v /= 10;
        case 1 : *p-- = '0' + (v % 10); v /= 10;
      }
      return len;
    }

#define __NNL_IS_LEAP_YEAR(year) (!(year%4) && ((year%100) || !(year%400)))

    static std::tm* time_t_to_tm(const std::time_t t, std::tm *r) {
      static const short spm[13] = {
         0
        ,(31)
        ,(31+28)
        ,(31+28+31)
        ,(31+28+31+30)
        ,(31+28+31+30+31)
        ,(31+28+31+30+31+30)
        ,(31+28+31+30+31+30+31)
        ,(31+28+31+30+31+30+31+31)
        ,(31+28+31+30+31+30+31+31+30)
        ,(31+28+31+30+31+30+31+31+30+31)
        ,(31+28+31+30+31+30+31+31+30+31+30)
        ,(31+28+31+30+31+30+31+31+30+31+30+31)
      };
      static const int SPD = 24*60*60;
      time_t i, work = t % SPD;
      r->tm_sec = work%60;
      work/=60;
      r->tm_min = work%60;
      r->tm_hour = work/60;
      work = t / SPD;
      r->tm_wday = (4+work) % 7;
      for ( i = 1970; ; ++i ) {
        const time_t k = __NNL_IS_LEAP_YEAR(i) ? 366 : 365;
        if ( work >= k )
          work -= k;
        else
          break;
      }
      r->tm_year = i-1900;
      r->tm_yday = work;

      r->tm_mday = 1;
      if ( __NNL_IS_LEAP_YEAR(i) && (work > 58) ) {
        if ( work == 59 )
          r->tm_mday = 2;
        work -= 1;
      }

      for (i = 11; i && (spm[i] > work); --i )
        ;

      r->tm_mon = i;
      r->tm_mday += work - spm[i];

      return r;
    }

    static std::size_t datetime_str(char *ptr) {
      char *p = ptr;
      struct timespec ts;
      clock_gettime(CLOCK_REALTIME, &ts);
      std::tm tm;
      time_t_to_tm(ts.tv_sec, &tm);
      tm.tm_hour += abs(timezone/(60*60));

#define __NNL_YEAR(p, tm) \
      *p++ = ((tm.tm_year+1900)/1000)%10+'0'; \
      *p++ = ((tm.tm_year+1900)/100)%10+'0'; \
      *p++ = ((tm.tm_year+1900)/10)%10+'0'; \
      *p++ = (tm.tm_year+1900)%10+'0';
#define __NNL_MONTH(p, tm) \
      *p++ = ((tm.tm_mon+1)/10)%10+'0'; \
      *p++ = (tm.tm_mon+1)%10+'0';
#define __NNL_DAY(p, tm) \
      *p++ = (tm.tm_mday/10)%10+'0'; \
      *p++ = tm.tm_mday%10+'0';

#if NNL_DATE_FORMAT == NNL_DATE_FORMAT_DMY // day.month.year
      // day
      __NNL_DAY(p, tm)
      /* sep */
      *p++ = '.';
      // month
      __NNL_MONTH(p, tm)
      /* sep */
      *p++ = '.';
      // year
      __NNL_YEAR(p, tm)
#elif NNL_DATE_FORMAT == NNL_DATE_FORMAT_YMD // year.month.day
      // year
      __NNL_YEAR(p, tm)
      /* sep */
      *p++ = '.';
      // month
      __NNL_MONTH(p, tm)
      /* sep */
      *p++ = '.';
      // day
      __NNL_DAY(p, tm)
#else                                       // month.day.year
      // month
      __NNL_MONTH(p, tm)
      /* sep */
      *p++ = '.';
      // day
      __NNL_DAY(p, tm)
      /* sep */
      *p++ = '.';
      // year
      __NNL_YEAR(p, tm)
#endif // NNL_DATE_FORMAT

#undef __NNL_YEAR
#undef __NNL_MONTH
#undef __NNL_DAY

      /* sep */
      *p++ = '-';
      // hours
      *p++ = (tm.tm_hour/10)%10+'0';
      *p++ = tm.tm_hour%10+'0';
      /* sep */
      *p++ = ':';
      // minutes
      *p++ = (tm.tm_min/10)%10+'0';
      *p++ = tm.tm_min%10+'0';
      /* sep */
      *p++ = ':';
      // seconds
      *p++ = (tm.tm_sec/10)%10+'0';
      *p++ = tm.tm_sec%10+'0';
      /* sep */
      // microseconds
      *p++ = '.';
      p += itoa(p, ts.tv_nsec/1000);

      return p-ptr;
    }
  };

  ops::datetime_str(buf);

  return buf;
}

#endif // NNL_USE_DATETIME

enum elevel {
   info
  ,debug
  ,warning
  ,error
};

void write(__NNL_STREAM_TYPE os, const char *file
    ,std::size_t line, elevel lvl, const char *fmt)
{
    __NNL_MAKE_DATETIME_BUF()
#if defined(NNL_USE_PRINTF)
    ::std::fprintf(
         os
        ,__NNL_MAKE_FMT_STRING() "%s"
        ,__NNL_MAKE_ARGS_STRING(file, line, lvl)
        , fmt
    );
#else // !NNL_USE_PRINTF
    os << __NNL_MAKE_FMT_STRING() << fmt;
#endif // NNL_USE_PRINTF
}

__NNL_DECLARE_WRITE(0)
__NNL_DECLARE_WRITE(1)
__NNL_DECLARE_WRITE(2)
__NNL_DECLARE_WRITE(3)
__NNL_DECLARE_WRITE(4)
__NNL_DECLARE_WRITE(5)
__NNL_DECLARE_WRITE(6)
__NNL_DECLARE_WRITE(7)
__NNL_DECLARE_WRITE(8)
__NNL_DECLARE_WRITE(9)

} // ns NNL

/***************************************************************************/

#if defined(NNL_USE_PRINTF)
#  if defined(NNL_FLUSH_EACH_RECORD)
#    define __NNL_FLUSH_FUNC(os) ::std::fflush(os);
#  else
#    define __NNL_FLUSH_FUNC(os)
#  endif
#  define __NNL_CREATE_LOG_STREAM(oname, path) \
     ::std::FILE *oname = ::std::fopen(path, "a+"); \
     assert(oname != 0);
#else
#  if defined(NNL_FLUSH_EACH_RECORD)
#    define __NNL_FLUSH_FUNC(os) os.flush();
#  else
#    define __NNL_FLUSH_FUNC(os)
#  endif
#  define __NNL_CREATE_LOG_STREAM(oname, path) \
     ::std::ofstream oname(path, ::std::ios::out|::std::ios::app); \
     assert(oname.is_open());
#endif

#define NNL_CREATE_LOG_STREAM(oname, path) \
    __NNL_CREATE_LOG_STREAM(oname, path)

#define __NNL_WITHOUT_ARGS(os, file, line, lvl, fmt, ...) \
  ::NNL::write(os, file, line, lvl, fmt);

#define __NNL_WITH_ARGS(os, file, line, lvl, fmt, ...) \
  ::NNL::write(os, file, line, lvl, fmt, __VA_ARGS__);

#define __NNL_LOG(os, lvl, fmt, ...) \
  do { \
    __NNL_MUTEX_TYPE(mut) \
    __NNL_LOCKGUARD_TYPE(lock, mut) \
    \
    __NNL_IF( \
       __NNL_TUPLE_IS_EMPTY(__VA_ARGS__) \
      ,__NNL_WITHOUT_ARGS \
      ,__NNL_WITH_ARGS \
    )(os, __FILE__, __LINE__, lvl, fmt, __VA_ARGS__) \
    \
    __NNL_FLUSH_FUNC(os) \
  } while(0);

#define NNL_LOGI(os, fmt, ...) __NNL_LOG(os, ::NNL::info, fmt, __VA_ARGS__)
#define NNL_LOGD(os, fmt, ...) __NNL_LOG(os, ::NNL::debug, fmt, __VA_ARGS__)
#define NNL_LOGW(os, fmt, ...) __NNL_LOG(os, ::NNL::warning, fmt, __VA_ARGS__)
#define NNL_LOGE(os, fmt, ...) __NNL_LOG(os, ::NNL::error, fmt, __VA_ARGS__)

/***************************************************************************/

#endif // __NANOLOG__NANOLOG_HPP__INCLUDED
