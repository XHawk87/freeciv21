// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: Freeciv21 and Freeciv Contributors

// self
#include "bitvector.h"

// utility
#include "log.h"

// Qt
#include <QBitArray>

// std
#include <cstddef> // size_t

/* bv_*  - static bitvectors; used for data which where the length is
           fixed (number of players; flags for enums; ...). They are
           named bv_* and the macros BV_* are defined.
 */

/**
   Return whether two vectors: vec1 and vec2 have common
   bits. I.e. (vec1 & vec2) != 0.

   Don't call this function directly, use BV_CHECK_MASK macro
   instead. Don't call this function with two different bitvectors.
 */
bool bv_check_mask(const unsigned char *vec1, const unsigned char *vec2,
                   size_t size1, size_t size2)
{
  size_t i;
  fc_assert_ret_val(size1 == size2, false);

  for (i = 0; i < size1; i++) {
    if ((vec1[0] & vec2[0]) != 0) {
      return true;
    }
    vec1++;
    vec2++;
  }
  return false;
}

/**
   Compares elements of two bitvectors. Both vectors are expected to have
   same number of elements, i.e. , size1 must be equal to size2.
 */
bool bv_are_equal(const unsigned char *vec1, const unsigned char *vec2,
                  size_t size1, size_t size2)
{
  size_t i;
  fc_assert_ret_val(size1 == size2, false);

  for (i = 0; i < size1; i++) {
    if (vec1[0] != vec2[0]) {
      return false;
    }
    vec1++;
    vec2++;
  }
  return true;
}

/**
   Set everything that is true in vec_from in vec_to. Stuff that already is
   true in vec_to aren't touched. (Bitwise inclusive OR assignment)

   Both vectors are expected to have same number of elements,
   i.e. , size1 must be equal to size2.

   Don't call this function directly, use BV_SET_ALL_FROM macro
   instead.
 */
void bv_set_all_from(unsigned char *vec_to, const unsigned char *vec_from,
                     size_t size_to, size_t size_from)
{
  size_t i;

  fc_assert_ret(size_to == size_from);

  for (i = 0; i < size_to; i++) {
    vec_to[i] |= vec_from[i];
  }
}

/**
   Clear everything that is true in vec_from in vec_to. Stuff that already
   is false in vec_to aren't touched.

   Both vectors are expected to have same number of elements,
   i.e. , size1 must be equal to size2.

   Don't call this function directly, use BV_CLR_ALL_FROM macro
   instead.
 */
void bv_clr_all_from(unsigned char *vec_to, const unsigned char *vec_from,
                     size_t size_to, size_t size_from)
{
  size_t i;

  fc_assert_ret(size_to == size_from);

  for (i = 0; i < size_to; i++) {
    vec_to[i] &= ~vec_from[i];
  }
}

// this is not very fast
bool is_any_set(QBitArray &ba)
{
  for (int i = 0; i < ba.count(); i++) {
    if (ba.testBit(i)) {
      return true;
    }
  }
  return false;
}
