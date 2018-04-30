#ifndef _TEST_H
#define _TEST_H

#include <stdbool.h>
#include <stdlib.h>
#include <wchar.h>

#define __WIDESTR(string) (L##string)
#define _W(string)        __WIDESTR(string)

#define test_assert(stmt) test_assert_ex(stmt, __func__, __LINE__, _W(__FILE__))
#define test_expect(stmt) test_expect_ex(stmt, __func__, __LINE__, _W(__FILE__))

typedef void (*test_step_t)(void);

void setup(void);
void teardown(void);

static bool error_happend = 0;

static inline signed
test_assert_ex(bool stmt, const char * function, signed line,
               const wchar_t * file)
{
  if (!stmt) {
    wprintf(L"%ls:%d: Wrong assert statement in %s(void)\n", function, file, line);
    exit(1);
  } 
  return 0;
}

static inline signed
test_expect_ex(bool stmt, const char * function, signed line,
               const wchar_t * file)
{
  if (!stmt) {
    wprintf(L"%ls:%d: Wrong expect statement in %s(void)\n", file, line, function);
    error_happend = true;
  } 
  return 0;
}

static inline signed
test_run(const test_step_t * steps, size_t steps_size)
{
  for (size_t i = 0; i < steps_size; i++) {
    setup();
    steps[i]();
    teardown();
  }
  return error_happend;
}

#endif /* _TEST_H */