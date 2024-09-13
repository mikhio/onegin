#include <ctype.h>
#include "../inc/string_compare.h"
#include "../inc/iog_string.h"
#include "../inc/iog_assert.h"

int str_compare_forward  (const char *str1, const char *str2) {
  IOG_ASSERT(str1);
  IOG_ASSERT(str2);

  return istrcmp(skipExtraChars(str1), skipExtraChars(str2));
}

const char *skipExtraChars(const char *str) {
  IOG_ASSERT(str);

  const char *str_filtered = str;

  while (!isalpha(str_filtered[0]) && !(str_filtered[0] == '\0'))
    str_filtered++;

  return str_filtered;
}
