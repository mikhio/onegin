#include <ctype.h>
#include "../inc/return_codes.h"
#include "../inc/string_compare.h"
#include "../inc/iog_assert.h"
#include "../inc/cli_colors.h"

int strcmp_fwd(const StrLine *first_str, const StrLine *second_str) {
  IOG_ASSERT(first_str);
  IOG_ASSERT(second_str);

  StrLine first_filt = *first_str;
  StrLine second_filt = *second_str;

  skipExtraCharsFront(&first_filt);
  skipExtraCharsFront(&second_filt);

  int diff = 0;
  size_t str_index = 0;

  do {
    diff = (int) tolower(first_filt.line[str_index]) - (int) tolower(second_filt.line[str_index]);
    
    if ((first_filt.line[str_index] == '\0') || (second_filt.line[str_index] == '\0'))
      break;

    str_index++;

  } while (diff == 0);

  return diff;
}

int strcmp_bwd(const StrLine *first_str, const StrLine *second_str) {
  IOG_ASSERT(first_str);
  IOG_ASSERT(second_str);

  StrLine first_filt = *first_str;
  StrLine second_filt = *second_str;

  skipExtraCharsBack(&first_filt);
  skipExtraCharsBack(&second_filt);

  int diff = 0;

  const char *first = first_filt.line + first_filt.length;
  const char *second = second_filt.line + second_filt.length;

  do {
    diff = (int) tolower(*first) - (int) tolower(*second);

    printf(MAGENTA(" [COMPARE CHARS] '%c' - '%c' = %d\n"), *first, *second, diff);
    
    if ((first <= first_filt.line) || (second <= second_filt.line))
      break;

    first--;
    second--;

  } while (diff == 0);

  return diff;
}

int mywrap_str_compare(const void *ptr1, const void *ptr2, strcmp_func_t compare_func) {
  IOG_ASSERT(ptr1);
  IOG_ASSERT(ptr2);
  IOG_ASSERT(compare_func);

  const StrLine *str1 = (const StrLine *) ptr1;
  const StrLine *str2 = (const StrLine *) ptr2;

  printf(BLUE("[COMPARE] ") BLACK(" (%p) %p, (%p) %p \n"), ptr1, str1->line, ptr2, str2->line);

  int diff = compare_func(str1, str2);

  if (!str1->length || !str2->length) {
    return -diff;
  }

  printf(GREEN("[COMPARED]") BLACK(" (%p) %p, (%p) %p => %d\n"), ptr1, str1->line, ptr2, str2->line, diff);
  printf("\n");

  return diff;
}

int str_compare_forward(const void *ptr1, const void *ptr2) {
  IOG_ASSERT(ptr1);
  IOG_ASSERT(ptr2);

  return mywrap_str_compare(ptr1, ptr2, strcmp_fwd);
}

int str_compare_backward(const void *ptr1, const void *ptr2) {
  IOG_ASSERT(ptr1);
  IOG_ASSERT(ptr2);

  return mywrap_str_compare(ptr1, ptr2, strcmp_bwd);
}

ReturnCode skipExtraCharsFront(StrLine *str) {
  IOG_ASSERT(str);

  printf(
      BLUE("[FILTER]  ") BLACK(" %p ") "'%s' size: %lu\n",
      str->line, str->line, str->length
  );


  while (!isalpha(*str->line) && !(*str->line == '\0')) {
    printf(RED("  [SKIP] ") "'%c' => ", str->line[0]);

    str->line++;
    printf("str->line+len = '%c', ", str->line[0]);

    str->length--;
    printf("str->length = '%lu'\n", str->length);
  }

  printf(
      GREEN("[FILTERED]") BLACK(" %p ") "'%s' size: %lu\n",
      str->line, str->line, str->length
  );

  return OK;
}

ReturnCode skipExtraCharsBack(StrLine *str) {
  IOG_ASSERT(str);

  printf(
      BLUE("[FILTER]  ") BLACK(" %p ") "'%s' size: %lu\n",
      str->line, str->line, str->length
  );

  char *last_char = str->line + str->length;

  while (!isalpha(*last_char) && (str->length > 0)) {
    printf(RED("  [SKIP] ") "'%c' => ", *last_char);

    last_char--;
    printf("last_char = '%c', ", *last_char);

    str->length--;
    printf("str->length = '%lu'\n", str->length);
  }

  printf(GREEN("[FILTERED]") BLACK(" %p ") "'", str->line);

  for (int i = 0; i <= str->length; i++) {
    printf("%c", str->line[i]);
  }

  printf("' size: %lu\n", str->length);


  return OK;
}
