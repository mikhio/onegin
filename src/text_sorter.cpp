#include <stdio.h>
#include <stdlib.h>

#include "../inc/text_sorter.h"
#include "../inc/iog_assert.h"
#include "../inc/string_compare.h"

ReturnCode sortText(Text *text, strcmp_func_t compareFunc) {
  IOG_ASSERT(text);
  IOG_ASSERT(compareFunc);

  //qsort(text->lines, text->lines_size, sizeof(char *), (int (*) (const void *, const void *)) compareFunc);
  bubbleSort(text, compareFunc);

  return OK;
}

ReturnCode bubbleSort(Text *text, strcmp_func_t compareFunc) {
  IOG_ASSERT(text);
  IOG_ASSERT(compareFunc);

  for (size_t i = 0; i < text->lines_size-1; i++) {
    for (size_t j = 0; j < text->lines_size-1-i; j++) {
        if (compareFunc(text->lines[j], text->lines[j+1]) > 0) {
          char *tmp = text->lines[j+1];
          text->lines[j+1] = text->lines[j];
          text->lines[j] = tmp;
        }
    }
  }

  return OK;
}

