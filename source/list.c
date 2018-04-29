#include "list.h"

#include <stddef.h>

signed
list_init(struct list * self, struct pool * pool)
{
  self->pool = pool;
  self->first = NULL;
  self->last = NULL;
  return 0;
}

signed
list_cleanup(struct list * self)
{
  self->pool = NULL;
  self->first = NULL;
  self->last = NULL;
  return 0;
}

signed
list_get_data(struct list * self, void ** ret, unsigned index)
{
  struct list_node * node;
  unsigned i;
  for (node = self->first, i = 0; node != NULL; node = node->next, i++) {
    if (i == index) {
      *ret = node->data;
      return 0;
    }
  }
  *ret = NULL;
  return 1;
}

signed
list_get_length(struct list * self, unsigned * ret)
{
  unsigned length = 0;
  struct list_node * node;
  for (node = self->first; node != NULL; node = node->next) {
    length = length + 1;
  }
  *ret = length;
  return 0;
}

signed
list_append(struct list * self, void * data)
{
  struct list_node * node;
  if (pool_create(self->pool, (void**)&node) == 0) {
    node->next = NULL;
    node->data = data;
    if (self->first == NULL) {
      self->first = node;
    } else {
      self->last->next = node;
    }
    self->last = node;
    return 0;
  }
  return 1;
}