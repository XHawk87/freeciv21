// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: Freeciv21 and Freeciv Contributors

#pragma once

// utility
#include "support.h" // bool, fc__warn_unused_result

// Qt
#include <QMutex>

// A single element of a genlist, opaque type.
struct genlist_link;

// Function type definitions.
typedef void (*genlist_free_fn_t)(void *);
typedef void *(*genlist_copy_fn_t)(const void *);
typedef bool (*genlist_cond_fn_t)(const void *);
typedef bool (*genlist_comp_fn_t)(const void *, const void *);

/* A genlist, storing the number of elements (for quick retrieval and
 * testing for empty lists), and pointers to the first and last elements
 * of the list. */
struct genlist {
  int nelements;
  QMutex mutex;
  struct genlist_link *head_link;
  struct genlist_link *tail_link;
  genlist_free_fn_t free_data_func;
};

struct genlist *genlist_new() fc__warn_unused_result;
struct genlist *
genlist_new_full(genlist_free_fn_t free_data_func) fc__warn_unused_result;
void genlist_destroy(struct genlist *pgenlist);

struct genlist *
genlist_copy(const struct genlist *pgenlist) fc__warn_unused_result;
struct genlist *
genlist_copy_full(const struct genlist *pgenlist,
                  genlist_copy_fn_t copy_data_func,
                  genlist_free_fn_t free_data_func) fc__warn_unused_result;

void genlist_clear(struct genlist *pgenlist);

void genlist_unique(struct genlist *pgenlist);
void genlist_unique_full(struct genlist *pgenlist,
                         genlist_comp_fn_t comp_data_func);

void genlist_append(struct genlist *pgenlist, void *data);
void genlist_prepend(struct genlist *pgenlist, void *data);
void genlist_insert(struct genlist *pgenlist, void *data, int idx);
void genlist_insert_after(struct genlist *pgenlist, void *data,
                          struct genlist_link *plink);
void genlist_insert_before(struct genlist *pgenlist, void *data,
                           struct genlist_link *plink);

bool genlist_remove(struct genlist *pgenlist, const void *data);
bool genlist_remove_if(struct genlist *pgenlist,
                       genlist_cond_fn_t cond_data_func);
int genlist_remove_all(struct genlist *pgenlist, const void *data);
int genlist_remove_all_if(struct genlist *pgenlist,
                          genlist_cond_fn_t cond_data_func);
void genlist_erase(struct genlist *pgenlist, struct genlist_link *plink);
void genlist_pop_front(struct genlist *pgenlist);
void genlist_pop_back(struct genlist *pgenlist);

int genlist_size(const struct genlist *pgenlist);
void *genlist_get(const struct genlist *pgenlist, int idx);
void *genlist_front(const struct genlist *pgenlist);
void *genlist_back(const struct genlist *pgenlist);
struct genlist_link *genlist_link_get(const struct genlist *pgenlist,
                                      int idx);
inline static struct genlist_link *
genlist_head(const struct genlist *pgenlist)
{
  return (nullptr != pgenlist ? pgenlist->head_link : nullptr);
}
struct genlist_link *genlist_tail(const struct genlist *pgenlist);

struct genlist_link *genlist_search(const struct genlist *pgenlist,
                                    const void *data);
struct genlist_link *genlist_search_if(const struct genlist *pgenlist,
                                       genlist_cond_fn_t cond_data_func);

void genlist_sort(struct genlist *pgenlist,
                  int (*compar)(const void *, const void *));
void genlist_shuffle(struct genlist *pgenlist);
void genlist_reverse(struct genlist *pgenlist);

void genlist_allocate_mutex(struct genlist *pgenlist);
void genlist_release_mutex(struct genlist *pgenlist);

/* A single element of a genlist, storing the pointer to user
 * data, and pointers to the next and previous elements: */
struct genlist_link {
  struct genlist_link *next, *prev;
  void *dataptr;
};

/****************************************************************************
  Returns the pointer of this link.
****************************************************************************/
static inline void *genlist_link_data(const struct genlist_link *plink)
{
  return (nullptr != plink ? plink->dataptr : nullptr);
}

/****************************************************************************
  Returns the previous link.
****************************************************************************/
fc__warn_unused_result static inline struct genlist_link *
genlist_link_prev(const struct genlist_link *plink)
{
  return plink->prev;
}

/****************************************************************************
  Returns the next link.
****************************************************************************/
fc__warn_unused_result static inline struct genlist_link *
genlist_link_next(const struct genlist_link *plink)
{
  return plink->next;
}
