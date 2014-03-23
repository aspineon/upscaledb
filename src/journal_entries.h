/*
 * Copyright (C) 2005-2011 Christoph Rupp (chris@crupp.de).
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

/*
 * @brief journal entries for insert, erase, begin, commit, abort...
 *
 */

#ifndef HAM_JOURNAL_ENTRIES_H__
#define HAM_JOURNAL_ENTRIES_H__

namespace hamsterdb {

#include "packstart.h"

/*
 * A journal entry for all txn related operations (begin, commit, abort)
 *
 * This structure can be followed by one of the structures below
 * (PJournalEntryInsert or PJournalEntryERASE); the field |followup_size|
 * is the structure size of this follow-up structure.
 */
HAM_PACK_0 struct HAM_PACK_1 PJournalEntry {
  // Constructor - sets all fields to 0
  PJournalEntry()
    : lsn(0), followup_size(0), txn_id(0), type(0),
        dbname(0), _reserved(0) {
  }

  // the lsn of this entry
  ham_u64_t lsn;

  // the size of the follow-up entry in bytes (may be padded)
  ham_u64_t followup_size;

  // the transaction id
  ham_u64_t txn_id;

  // the type of this entry
  ham_u32_t type;

  // the name of the database which is modified by this entry
  ham_u16_t dbname;

  // a reserved value - reqd for padding
  ham_u16_t _reserved;
} HAM_PACK_2;

#include "packstop.h"


#include "packstart.h"

//
// a Journal entry for an 'insert' operation
//
HAM_PACK_0 struct HAM_PACK_1 PJournalEntryInsert {
  // Constructor - sets all fields to 0
  PJournalEntryInsert()
    : key_size(0), compressed_key_size(0), record_size(0),
      compressed_record_size(0), record_partial_size(0),
      record_partial_offset(0), insert_flags(0) {
    data[0] = 0;
  }

  // key size
  ham_u16_t key_size;

  // PRO: compressed key size
  ham_u16_t compressed_key_size;

  // record size
  ham_u32_t record_size;

  // PRO: compressed record size
  ham_u32_t compressed_record_size;

  // record partial size
  ham_u32_t record_partial_size;

  // record partial offset
  ham_u32_t record_partial_offset;

  // flags of ham_insert(), ham_cursor_insert()
  ham_u32_t insert_flags;

  // data follows here - first |key_size| bytes for the key, then
  // |record_size| bytes for the record (and maybe some padding)
  //
  // PRO: this data can be compressed
  ham_u8_t data[1];

  // Returns a pointer to the key data
  ham_u8_t *get_key_data() {
    return (&data[0]);
  }

  // Returns a pointer to the record data
  ham_u8_t *get_record_data() {
    return (&data[key_size]);
  }
} HAM_PACK_2;

#include "packstop.h"


#include "packstart.h"

//
// a Journal entry for 'erase' operations
//
HAM_PACK_0 struct HAM_PACK_1 PJournalEntryErase {
  // Constructor - sets all fields to 0
  PJournalEntryErase()
    : key_size(0), compressed_key_size(0), erase_flags(0), duplicate(0) {
    data[0] = 0;
  }

  // key size
  ham_u16_t key_size;

  // PRO: compressed key size
  ham_u16_t compressed_key_size;

  // flags of ham_erase(), ham_cursor_erase()
  ham_u32_t erase_flags;

  // which duplicate to erase
  ham_u32_t duplicate;

  // the key data
  //
  // PRO: this data can be compressed
  ham_u8_t data[1];

  // Returns a pointer to the key data
  ham_u8_t *get_key_data() {
    return (&data[0]);
  }
} HAM_PACK_2;

#include "packstop.h"


#include "packstart.h"

//
// a Journal entry for a 'changeset' group
//
HAM_PACK_0 struct HAM_PACK_1 PJournalEntryChangeset {
  // Constructor - sets all fields to 0
  PJournalEntryChangeset()
    : num_pages(0) {
  }

  // number of pages in this changeset
  ham_u32_t num_pages;
} HAM_PACK_2;

#include "packstop.h"


#include "packstart.h"

//
// a Journal entry for a single page
//
HAM_PACK_0 struct HAM_PACK_1 PJournalEntryPageHeader {
  // Constructor - sets all fields to 0
  PJournalEntryPageHeader(ham_u64_t _address = 0)
    : address(_address), compressed_size(0) {
  }

  // the page address
  ham_u64_t address;

  // PRO: the compressed size, if compression is enabled
  ham_u32_t compressed_size;
} HAM_PACK_2;

#include "packstop.h"


} // namespace hamsterdb

#endif /* HAM_JOURNAL_ENTRIES_H__ */
