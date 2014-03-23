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

package de.crupp.hamsterdb;

public interface DuplicateCompareCallback {

    /**
     * The compare method compares two records -
     * "left-hand side" (lhs) and the "right-hand side (rhs).
     * <p>
     * More information: <a href="http://hamsterdb.com/public/scripts/html_www/group__ham__Database__cfg__parameters.html#ga7d8cd9266c8e802685ee467d3bb35b3b">C documentation</a>
     *
     * @param lhs The first record
     * @param rhs The second record
     * @return -1 if the first record is smaller, +1 if the first record
     *     is larger, 0 if both records are equal
     */
    public int compare(byte[] lhs, byte[] rhs);
}


