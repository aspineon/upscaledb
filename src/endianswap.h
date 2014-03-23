/*
 * Copyright (C) 2005-2014 Christoph Rupp (chris@crupp.de).
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

/**
 * @brief This file contains macros for little endian/big endian byte swapping.
 * The database stores little-endian data only.
 */

#ifndef HAM_ENDIANSWAP_H__
#define HAM_ENDIANSWAP_H__

// byte swapping macros - we use little endian
#ifdef HAM_BIG_ENDIAN
#  define ham_h2db16(x)      _ham_byteswap16(x)
#  define ham_h2db32(x)      _ham_byteswap32(x)
#  define ham_h2db64(x)      _ham_byteswap64(x)
#  define ham_h2db_offset(x) _ham_byteswap64(x)
#  define ham_h2db_size(x)   _ham_byteswap32(x)
#  define ham_db2h16(x)      _ham_byteswap16(x)
#  define ham_db2h32(x)      _ham_byteswap32(x)
#  define ham_db2h64(x)      _ham_byteswap64(x)
#  define ham_db2h_offset(x) _ham_byteswap64(x)
#  define ham_db2h_size(x)   _ham_byteswap32(x)
#else // HAM_LITTLE_ENDIAN
#  define ham_h2db16(x)      (x)
#  define ham_h2db32(x)      (x)
#  define ham_h2db64(x)      (x)
#  define ham_h2db_offset(x) (x)
#  define ham_h2db_size(x)   (x)
#  define ham_db2h16(x)      (x)
#  define ham_db2h32(x)      (x)
#  define ham_db2h64(x)      (x)
#  define ham_db2h_offset(x) (x)
#  define ham_db2h_size(x)   (x)
#endif

#define _ham_byteswap16(x)                             \
   ((((x) >> 8) & 0xff) |                              \
    (((x) & 0xff) << 8))

#define _ham_byteswap32(x)                             \
   ((((x) & 0xff000000) >> 24) |                       \
    (((x) & 0x00ff0000) >>  8) |                       \
    (((x) & 0x0000ff00) <<  8) |                       \
    (((x) & 0x000000ff) << 24))

#define _ham_byteswap64(x)                             \
   ((((x) & 0xff00000000000000ull) >> 56) |            \
    (((x) & 0x00ff000000000000ull) >> 40) |            \
    (((x) & 0x0000ff0000000000ull) >> 24) |            \
    (((x) & 0x000000ff00000000ull) >>  8) |            \
    (((x) & 0x00000000ff000000ull) <<  8) |            \
    (((x) & 0x0000000000ff0000ull) << 24) |            \
    (((x) & 0x000000000000ff00ull) << 40) |            \
    (((x) & 0x00000000000000ffull) << 56))

#endif /* HAM_ENDIANSWAP_H__ */
