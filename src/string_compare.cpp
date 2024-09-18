#include <ctype.h>
#include "../inc/return_codes.h"
#include "../inc/string_compare.h"
#include "../inc/iog_assert.h"
#include "../inc/cli_colors.h"

int strcmp_fwd(const StrLine *first_str, const StrLine *second_str) {
  IOG_ASSERT(first_str);
  IOG_ASSERT(second_str);

  int diff = 0;
  size_t str_index = 0;

  do {
    diff = (int) tolower(first_str->line[str_index]) - (int) tolower(second_str->line[str_index]);
    
    if ((first_str->line[str_index] == '\0') || (second_str->line[str_index] == '\0'))
      break;

    str_index++;

  } while (diff == 0);

  return diff;
}

int mywrap_str_compare(const void *ptr1, const void *ptr2, strcmp_func_t compare_func) {
  IOG_ASSERT(ptr1);
  IOG_ASSERT(ptr2);
  IOG_ASSERT(compare_func);

  StrLine str1 = *(const StrLine *) ptr1;
  StrLine str2 = *(const StrLine *) ptr2;

  skipExtraChars(&str1);
  skipExtraChars(&str2);

  if (!str1.length || !str2.length) {
    // TODO: printf
    return 0;
  }

  int diff = compare_func(&str1, &str2);

  printf(BLUE("[COMPARE] ") BLACK(" (%p) %p, (%p) %p => %d\n"), ptr1, str1.line, ptr2, str2.line, diff);

  return diff;
}

int str_compare_forward(const void *ptr1, const void *ptr2) {
  IOG_ASSERT(ptr1);
  IOG_ASSERT(ptr2);

  return mywrap_str_compare(ptr1, ptr2, strcmp_fwd);
}

ReturnCode skipExtraChars(StrLine *str) {
  IOG_ASSERT(str);

  printf(
      BLUE("[FILTER]  ") BLACK(" %p ") "'%s' size: %lu\n",
      str->line, str->line, str->length
  );

  while (!isalpha(str->line[0]) && !(str->line[0] == '\0')) {
    printf(RED("  [SKIP] ") "'%c' => ", str->line[0]);

    str->line++;
    printf("str->line[0] = '%c', ", str->line[0]);

    str->length--;
    printf("str->length = '%lu'\n", str->length);
  }

  printf(
      GREEN("[FILTERED]") BLACK(" %p ") "'%s' size: %lu\n",
      str->line, str->line, str->length
  );

  return OK;
}
