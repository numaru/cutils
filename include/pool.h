#ifndef _POOL_H
#define _POOL_H

#include <stddef.h>

enum pool_node_state {
  POOL_NODE_STATE_VACANT = 0,
  POOL_NODE_STATE_TAKEN = 1
};

struct pool_node {
  enum pool_node_state state;
};

struct pool {
  void * data;
  size_t data_size;
  size_t node_size;
};

signed
pool_init(struct pool * self, void * data, size_t data_size, size_t node_size);

signed
pool_cleanup(struct pool * self);

signed
pool_create(struct pool * self, void ** ret);

signed
pool_delete(struct pool * self, void ** data);

#endif /* _POOL_H */