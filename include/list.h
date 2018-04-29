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
list_get_data(struct list * self, void ** ret, unsigned index);

signed
list_get_length(struct list * self, unsigned * ret);

signed
list_append(struct list * self, void * data);

#endif /* _LIST_H */