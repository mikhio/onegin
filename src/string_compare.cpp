#include <ctype.h>
#include "../inc/string_compare.h"
#include "../inc/iog_string.h"
#include "../inc/iog_assert.h"
#include "../inc/cli_colors.h"

int str_compare_forward  (const char *str1, const char *str2) {
  IOG_ASSERT(str1);
  IOG_ASSERT(str2);

  const char *str1_filtered = skipExtraChars(str1);
  const char *str2_filtered = skipExtraChars(str2);

  printf(GREEN("[FILTER]") BLACK(" %p ") "'%s' ->" BLACK(" %p ") "'%s'\n", str1, str1, str1_filtered, str1_filtered);
  printf(GREEN("[FILTER]") BLACK(" %p ") "'%s' ->" BLACK(" %p ") "'%s'\n", str2, str2, str2_filtered, str2_filtered);

  int res = istrcmp(str1_filtered, str2_filtered);

  printf(GREEN("[COMPARE]") BLACK(" %p %p \n"), str1_filtered, str2_filtered);

  return res;
}

const char *skipExtraChars(const char *str) {
  IOG_ASSERT(str);

  const char *str_filtered = str;

  while (!isalpha(str_filtered[0]) && !(str_filtered[0] == '\0'))
    str_filtered++;

  return str_filtered;
}
