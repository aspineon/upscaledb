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
 * @brief utility functions
 *
 */

#ifndef HAM_UTIL_H__
#define HAM_UTIL_H__

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "ham/hamsterdb.h"

#include "mem.h"

namespace hamsterdb {

/*
 * The ByteArray class is a dynamic, resizable array. The internal memory
 * is released when the ByteArray instance is destructed.
 */
class ByteArray
{
  public:
    ByteArray(ham_u32_t size = 0)
      : m_ptr(0), m_size(0), m_own(true) {
      resize(size);
    }

    ByteArray(ham_u32_t size, ham_u8_t fill_byte)
      : m_ptr(0), m_size(0), m_own(true) {
      resize(size);
      if (m_ptr)
        ::memset(m_ptr, fill_byte, m_size);
    }

    ~ByteArray() {
      clear();
    }

    void append(const void *ptr, ham_u32_t size) {
      ham_u32_t oldsize = m_size;
      char *p = (char *)resize(m_size + size);
      ::memcpy(p + oldsize, ptr, size);
    }

    void copy(const void *ptr, ham_u32_t size) {
      resize(size);
      ::memcpy(m_ptr, ptr, size);
      m_size = size;
    }

    void overwrite(ham_u32_t position, const void *ptr, ham_u32_t size) {
      ::memcpy(((ham_u8_t *)m_ptr) + position, ptr, size);
    }

    void *resize(ham_u32_t size) {
      if (size > m_size) {
        m_ptr = Memory::reallocate<void>(m_ptr, size);
        m_size = size;
      }
      return (m_ptr);
    }

    void *resize(ham_u32_t size, ham_u8_t fill_byte) {
      resize(size);
      if (m_ptr)
        memset(m_ptr, fill_byte, size);
      return (m_ptr);
    }

    ham_u32_t get_size() const {
      return (m_size);
    }

    void set_size(ham_u32_t size) {
      m_size = size;
    }

    void *get_ptr() {
      return (m_ptr);
    }

    const void *get_ptr() const {
      return (m_ptr);
    }

    void assign(void *ptr, ham_u32_t size) {
      clear();
      m_ptr = ptr;
      m_size = size;
    }

    void clear(bool release_memory = true) {
      if (m_own && release_memory)
        Memory::release(m_ptr);
      m_ptr = 0;
      m_size = 0;
    }

    bool is_empty() const {
      return (m_size == 0);
    }

    void disown() {
      m_own = false;
    }

  private:
    void *m_ptr;
    ham_u32_t m_size;
    bool m_own;
};

//
// vsnprintf replacement/wrapper
//
// uses vsprintf on platforms which do not define vsnprintf
//
extern int
util_vsnprintf(char *str, size_t size, const char *format, va_list ap);

//
// snprintf replacement/wrapper
//
// uses sprintf on platforms which do not define snprintf
//
#ifndef HAM_OS_POSIX
#  define util_snprintf _snprintf
#else
#  define util_snprintf snprintf
#endif

} // namespace hamsterdb

#endif /* HAM_UTIL_H__ */
