#include "pool.h"

#include <stddef.h>

signed
pool_init(struct pool * self, void * data, size_t data_size, size_t node_size)
{
  self->data = data;
  self->data_size = data_size;
  self->node_size = node_size;

  size_t begin = (size_t)self->data;
  size_t end = begin + self->data_size;
  for (size_t addr = begin; addr < end; addr += self->node_size) {
    struct pool_node * node = (struct pool_node*)addr;
    node->state = POOL_NODE_STATE_VACANT;
  }
  return 0;
}

signed
pool_cleanup(struct pool * self)
{
  self->data = NULL;
  self->data_size = 0;
  self->node_size = 0;
  return 0;
}

signed
pool_create(struct pool * self, void ** ret)
{
  size_t begin = (size_t)self->data;
  size_t end = begin + self->data_size;
  for (size_t addr = begin; addr < end; addr += self->node_size) {
    struct pool_node * node = (struct pool_node*)addr;
    if (node->state == POOL_NODE_STATE_VACANT) {
      node->state = POOL_NODE_STATE_TAKEN;
      *ret = node;
      return 0;
    }
  }
  *ret = NULL;
  return 1;
}

signed
pool_delete(struct pool * self, void ** data)
{
  struct pool_node * node = (struct pool_node*)(*data);
  node->state = POOL_NODE_STATE_VACANT;
  *data = NULL;
  return 0;
}

