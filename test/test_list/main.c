#include "test.h"

#include "list.h"

static void
test_list_init_and_cleanup(void)
{
  struct pool pool;
  struct list_node nodes[4];
  struct list list;
  test_expect(pool_init(&pool, nodes, sizeof(nodes), sizeof(nodes[0])) == 0);
  test_expect(list_init(&list, &pool) == 0);
  test_expect(list_cleanup(&list) == 0);
  test_expect(pool_cleanup(&pool) == 0);
}

static void
test_list_get_data(void)
{
  struct pool pool;
  struct list_node nodes[4];
  struct list list;
  signed variable = 0xAA;
  signed * input = &variable;
  signed * output = input + 0xBB;
  test_expect(pool_init(&pool, nodes, sizeof(nodes), sizeof(nodes[0])) == 0);
  test_expect(list_init(&list, &pool) == 0);
  test_expect(list_append(&list, input) == 0);
  test_expect(list_get_data(&list, (void**)&output, 0) == 0);
  test_expect(input == output);
  test_expect(list_get_data(&list, (void**)&output, 1) == 1);
  test_expect(output == NULL);
  test_expect(list_cleanup(&list) == 0);
  test_expect(pool_cleanup(&pool) == 0);
}

static void
test_list_get_length(void)
{
  struct pool pool;
  struct list_node nodes[4];
  struct list list;
  signed variable = 0xAA;
  unsigned length = 0xBB;
  test_expect(pool_init(&pool, nodes, sizeof(nodes), sizeof(nodes[0])) == 0);
  test_expect(list_init(&list, &pool) == 0);
  test_expect(list_get_length(&list, &length) == 0);
  test_expect(length == 0);
  test_expect(list_append(&list, &variable) == 0);
  test_expect(list_get_length(&list, &length) == 0);
  test_expect(length == 1);
  test_expect(list_append(&list, &variable) == 0);
  test_expect(list_get_length(&list, &length) == 0);
  test_expect(length == 2);
  test_expect(list_append(&list, &variable) == 0);
  test_expect(list_get_length(&list, &length) == 0);
  test_expect(length == 3);
  test_expect(list_append(&list, &variable) == 0);
  test_expect(list_get_length(&list, &length) == 0);
  test_expect(length == 4);
  test_expect(list_append(&list, &variable) == 1);
  test_expect(list_get_length(&list, &length) == 0);
  test_expect(length == 4);
  test_expect(list_cleanup(&list) == 0);
  test_expect(pool_cleanup(&pool) == 0);
}

static void
test_list_append()
{
  struct pool pool;
  struct list_node nodes[4];
  struct list list;
  int variable = 0xAA;
  test_expect(pool_init(&pool, nodes, sizeof(nodes), sizeof(nodes[0])) == 0);
  test_expect(list_init(&list, &pool) == 0);
  test_expect(list_append(&list, &variable) == 0);
  test_expect(list_append(&list, &variable) == 0);
  test_expect(list_append(&list, &variable) == 0);
  test_expect(list_append(&list, &variable) == 0);
  test_expect(list_append(&list, &variable) == 1);
  test_expect(list_cleanup(&list) == 0);
  test_expect(pool_cleanup(&pool) == 0);
}

static void
test_list_iterator_init_and_cleanup(void)
{
  struct pool pool;
  struct list_node nodes[4];
  struct list list;
  struct list_iterator it;
  signed variable = 0xAA;
  test_expect(pool_init(&pool, nodes, sizeof(nodes), sizeof(nodes[0])) == 0);
  test_expect(list_init(&list, &pool) == 0);
  test_expect(list_iterator_init(&it, &list) == 0);
  test_expect(list_append(&list, &variable) == 0);
  test_expect(list_iterator_init(&it, &list) == 0);
  test_expect(list_iterator_cleanup(&it) == 0);
  test_expect(list_cleanup(&list) == 0);
  test_expect(pool_cleanup(&pool) == 0);
}

static void
test_list_iterator_get_data(void)
{
  struct pool pool;
  struct list_node nodes[4];
  struct list list;
  struct list_iterator it;
  signed variable = 0xAA;
  signed * input = &variable;
  signed * output = input + 0xBB;
  test_expect(pool_init(&pool, nodes, sizeof(nodes), sizeof(nodes[0])) == 0);
  test_expect(list_init(&list, &pool) == 0);
  test_expect(list_iterator_init(&it, &list) == 0);
  test_expect(list_iterator_get_data(&it, (void**)&output) == 1);
  test_expect(output == NULL);
  test_expect(list_append(&list, input) == 0);
  test_expect(list_iterator_get_data(&it, (void**)&output) == 0);
  test_expect(output == input);
  test_expect(list_iterator_init(&it, &list) == 0);
  test_expect(list_iterator_cleanup(&it) == 0);
  test_expect(list_cleanup(&list) == 0);
  test_expect(pool_cleanup(&pool) == 0);
}

static void
test_list_iterator_get_next(void)
{
  struct pool pool;
  struct list_node nodes[4];
  struct list list;
  struct list_iterator first_it;
  struct list_iterator second_it;
  signed variables[3] = {0xAA, 0xBB, 0xCC};
  signed * output = &variables[0] + 0xBB;
  test_expect(pool_init(&pool, nodes, sizeof(nodes), sizeof(nodes[0])) == 0);
  test_expect(list_init(&list, &pool) == 0);
  test_expect(list_iterator_init(&first_it, &list) == 0);
  test_expect(list_append(&list, &variables[0]) == 0);
  test_expect(list_append(&list, &variables[1]) == 0);
  test_expect(list_append(&list, &variables[2]) == 0);
  test_expect(list_iterator_get_data(&first_it, (void**)&output) == 0);
  test_expect(output == &variables[0]);
  test_expect(list_iterator_get_next(&first_it, &second_it) == 0);
  test_expect(list_iterator_get_data(&first_it, (void**)&output) == 0);
  test_expect(output == &variables[0]);
  test_expect(list_iterator_get_data(&second_it, (void**)&output) == 0);
  test_expect(output == &variables[1]);
  test_expect(list_iterator_get_next(&second_it, &second_it) == 0);
  test_expect(list_iterator_get_data(&second_it, (void**)&output) == 0);
  test_expect(output == &variables[2]);
  test_expect(list_iterator_get_data(&first_it, (void**)&output) == 0);
  test_expect(output == &variables[0]);
  test_expect(list_iterator_cleanup(&first_it) == 0);
  test_expect(list_iterator_cleanup(&second_it) == 0);
  test_expect(list_cleanup(&list) == 0);
  test_expect(pool_cleanup(&pool) == 0);
}

static const test_step_t test_steps[] = {
  &test_list_init_and_cleanup,
  &test_list_get_data,
  &test_list_get_length,
  &test_list_append,
  &test_list_iterator_init_and_cleanup,
  &test_list_iterator_get_data,
  &test_list_iterator_get_next
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