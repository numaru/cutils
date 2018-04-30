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
list_get_data(const struct list * self, void ** ret, unsigned index)
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
list_get_length(const struct list * self, unsigned * ret)
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

signed
list_iterator_init(struct list_iterator * self, const struct list * collection)
{
  self->collection = collection;
  self->index = 0;
  self->length = 0;
  return list_get_length(self->collection, &self->length);
}

signed
list_iterator_cleanup(struct list_iterator * self)
{
  return 0;
}

signed
list_iterator_get_data(const struct list_iterator * self, void ** ret)
{
  return list_get_data(self->collection, ret, self->index);
}

signed
list_iterator_get_next(const struct list_iterator * self, struct list_iterator * ret)
{
  unsigned index = self->index;
  if (list_iterator_init(ret, self->collection) != 0) {
    return 1;
  }
  ret->index = index + 1;
  return 0;
}
