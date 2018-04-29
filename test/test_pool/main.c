#include "test.h"

#include "pool.h"

struct poolable {
  enum pool_node_state state;
  signed dummy_signed;
  char dummy_string[4];
};

static void
test_pool_init_and_cleanup(void)
{
  struct pool pool;
  struct poolable poolables[8];
  test_expect(pool_init(&pool, poolables, sizeof(poolables),
                        sizeof(poolables[0])) == 0);
  test_expect(pool_cleanup(&pool) == 0);
}

static void 
test_pool_create(void)
{
  struct pool pool;
  struct poolable poolables[4];
  struct poolable * poolable;
  test_expect(pool_init(&pool, poolables, sizeof(poolables),
                        sizeof(poolables[0])) == 0);
  test_expect(pool_create(&pool, (void**)&poolable) == 0);
  test_expect(poolable == &poolables[0]);
  test_expect(pool_create(&pool, (void**)&poolable) == 0);
  test_expect(poolable == &poolables[1]);
  test_expect(pool_create(&pool, (void**)&poolable) == 0);
  test_expect(poolable == &poolables[2]);
  test_expect(pool_create(&pool, (void**)&poolable) == 0);
  test_expect(poolable == &poolables[3]);
  test_expect(pool_create(&pool, (void**)&poolable) == 1);
  test_expect(poolable == NULL);
  test_expect(pool_create(&pool, (void**)&poolable) == 1);
  test_expect(poolable == NULL);
  test_expect(pool_cleanup(&pool) == 0);
}


static void
test_pool_delete(void)
{
  struct pool pool;
  struct poolable poolables[4];
  struct poolable * poolable;
  test_expect(pool_init(&pool, poolables, sizeof(poolables),
                        sizeof(poolables[0])) == 0);
  test_expect(pool_create(&pool, (void**)&poolable) == 0);
  test_expect(poolable == &poolables[0]);
  test_expect(pool_create(&pool, (void**)&poolable) == 0);
  test_expect(poolable == &poolables[1]);
  test_expect(pool_create(&pool, (void**)&poolable) == 0);
  test_expect(poolable == &poolables[2]);
  test_expect(pool_delete(&pool, (void**)&poolable) == 0);
  test_expect(poolable == NULL);
  test_expect(pool_create(&pool, (void**)&poolable) == 0);
  test_expect(poolable == &poolables[2]);
  test_expect(pool_create(&pool, (void**)&poolable) == 0);
  test_expect(poolable == &poolables[3]);
  test_expect(pool_create(&pool, (void**)&poolable) == 1);
  test_expect(poolable == NULL);
  test_expect(pool_cleanup(&pool) == 0);
}

static const test_step_t test_steps[] = {
  &test_pool_init_and_cleanup,
  &test_pool_create,
  &test_pool_delete
};

void
setup(void)
{
}

void
teardown(void)
{
}

signed
main(signed argc, char * argv[])
{
  return test_run(test_steps, sizeof(test_steps) / sizeof(test_steps[0]));
}