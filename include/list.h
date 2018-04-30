#ifndef _LIST_H
#define _LIST_H

#include "pool.h"

struct list_node {
  enum pool_node_state state;
  struct list_node * next;
  void * data;
};

struct list {
  struct pool * pool;
  struct list_node * first;
  struct list_node * last;
};

signed
list_init(struct list * self, struct pool * pool);

signed
list_cleanup(struct list * self);

signed
list_get_data(const struct list * self, void ** ret, unsigned index);

signed
list_get_length(const struct list * self, unsigned * ret);

signed
list_append(struct list * self, void * data);

struct list_iterator {
  const struct list * collection;
  unsigned length;
  unsigned index;
};

signed
list_iterator_init(struct list_iterator * self, const struct list * collection);

signed
list_iterator_cleanup(struct list_iterator * self);

signed
list_iterator_get_data(const struct list_iterator * self, void ** ret);

signed
list_iterator_get_next(const struct list_iterator * self, struct list_iterator * ret);

#endif /* _LIST_H */