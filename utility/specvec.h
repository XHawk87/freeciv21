// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: Freeciv21 and Freeciv Contributors

// utility
#include "log.h"
#include "support.h"

// std
#include <cstddef> // size_t
#include <cstdlib> // free

/**
 * specvectors: "specific vectors".
 *
 * This file is used to implement resizable arrays.
 *
 * Before including this file, you must define the following:
 *  - SPECVEC_TAG - this tag will be used to form names for functions etc.
 *    You may also define:
 *  - SPECVEC_TYPE - the typed vector will contain pointers to this type;
 *    If SPECVEC_TYPE is not defined, then 'struct SPECVEC_TAG' is used.
 *  At the end of this file, these (and other defines) are undef-ed.
 *
 * Assuming SPECVEC_TAG were 'foo', and SPECVEC_TYPE were 'foo_t',
 * including this file would provide a struct definition for:
 *    struct foo_vector;
 * and prototypes for the following functions:
 *    void foo_vector_init(struct foo_vector *tthis);
 *    void foo_vector_reserve(struct foo_vector *tthis, int n);
 *    int  foo_vector_size(const struct foo_vector *tthis);
 *    foo_t *foo_vector_get(struct foo_vector *tthis, int svindex);
 *    void foo_vector_copy(struct foo_vector *to,
 *              const struct foo_vector *from);
 *    void foo_vector_free(struct foo_vector *tthis);
 *    void foo_vector_append(struct foo_vector *tthis, foo_t pfoo);
 *    void foo_vector_remove(struct foo_vector *tthis, int svindex);
 */

/**
 * NOTE:
 * This header is NOT protected against multiple inclusions; this is
 * so that you can have multiple different specvectors. For each
 * specvector, this file should be included _once_, inside a .h file
 * which _is_ itself protected against multiple inclusions.
 */

#ifndef SPECVEC_TAG
#error Must define a SPECVEC_TAG to use this header
#endif
#ifndef SPECVEC_TYPE
#define SPECVEC_TYPE struct SPECVEC_TAG
#endif

#define SPECVEC_PASTE_(x, y) x##y
#define SPECVEC_PASTE(x, y) SPECVEC_PASTE_(x, y)

#define SPECVEC_VECTOR struct SPECVEC_PASTE(SPECVEC_TAG, _vector)

#define SPECVEC_FOO(suffix) SPECVEC_PASTE(SPECVEC_TAG, suffix)

SPECVEC_VECTOR
{
  // Users are allowed to access the data pointer directly.
  SPECVEC_TYPE *p;

  size_t size, size_alloc;
};

static inline void SPECVEC_FOO(_vector_init)(SPECVEC_VECTOR *tthis)
{
  tthis->p = nullptr;
  tthis->size = tthis->size_alloc = 0;
}

static inline void SPECVEC_FOO(_vector_reserve)(SPECVEC_VECTOR *tthis,
                                                size_t size)
{
  if (size > tthis->size_alloc) {
    size_t new_size = MAX(size, tthis->size_alloc * 2);

    tthis->p = static_cast<SPECVEC_TYPE *>(
        fc_realloc(tthis->p, new_size * sizeof(*tthis->p)));
    tthis->size_alloc = new_size;
  }
  tthis->size = size;
}

static inline size_t SPECVEC_FOO(_vector_size)(const SPECVEC_VECTOR *tthis)
{
  return tthis->size;
}

static inline SPECVEC_TYPE *
SPECVEC_FOO(_vector_get)(const SPECVEC_VECTOR *tthis, int svindex)
{
  if (svindex == -1 && tthis->size > 0) {
    return tthis->p + tthis->size - 1;
  } else if (svindex >= 0 && static_cast<size_t>(svindex) < tthis->size) {
    return tthis->p + svindex;
  } else {
    return nullptr;
  }
}

// You must _init "*to" before using this function
static inline void SPECVEC_FOO(_vector_copy)(SPECVEC_VECTOR *to,
                                             const SPECVEC_VECTOR *from)
{
  SPECVEC_FOO(_vector_reserve)(to, from->size);
  if (from->size > 0) {
    memcpy(to->p, from->p, from->size * sizeof(*to->p));
  }
}

static inline void SPECVEC_FOO(_vector_free)(SPECVEC_VECTOR *tthis)
{
  if (tthis->p) {
    free(tthis->p);
  }
  SPECVEC_FOO(_vector_init)(tthis);
}

static inline void SPECVEC_FOO(_vector_append)(SPECVEC_VECTOR *tthis,
                                               SPECVEC_TYPE const &pfoo)
{
  SPECVEC_FOO(_vector_reserve)(tthis, tthis->size + 1);
  tthis->p[tthis->size - 1] = pfoo;
}

/**************************************************************************
  Remove element number svindex from the vector.
**************************************************************************/
static inline void SPECVEC_FOO(_vector_remove)(SPECVEC_VECTOR *tthis,
                                               const int svindex)
{
  size_t i;

  /* Be consistent with SPECVEC_FOO_vector_get(): Allow negative element
   * number. */
  const size_t rmpos =
      (svindex < 0 ? SPECVEC_FOO(_vector_size)(tthis) - svindex
                   : static_cast<size_t>(svindex));

  fc_assert_ret(rmpos < SPECVEC_FOO(_vector_size)(tthis));

  for (i = rmpos; (i + 1) < SPECVEC_FOO(_vector_size)(tthis); i++) {
    // Relocate the elements following the deleted element.
    tthis->p[i] = tthis->p[i + 1];
  }

  SPECVEC_FOO(_vector_reserve)(tthis, SPECVEC_FOO(_vector_size)(tthis) - 1);
}

#define TYPED_VECTOR_ITERATE(atype, vector, var)                            \
  {                                                                         \
    unsigned int myiter##var;                                               \
    atype *var;                                                             \
    for (myiter##var = 0; myiter##var < (vector)->size; myiter##var++) {    \
      var = &(vector)->p[myiter##var];

// Balance for above:
#define VECTOR_ITERATE_END                                                  \
  }                                                                         \
  }

#undef SPECVEC_TAG
#undef SPECVEC_TYPE
#undef SPECVEC_PASTE_
#undef SPECVEC_PASTE
#undef SPECVEC_VECTOR
#undef SPECVEC_FOO
