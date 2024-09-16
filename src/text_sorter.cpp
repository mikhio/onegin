#include <stdio.h>
#include <stdlib.h>

#include "../inc/cli_colors.h"
#include "../inc/text_sorter.h"
#include "../inc/iog_assert.h"
#include "../inc/string_compare.h"

ReturnCode sortText(Text *text, strcmp_func_t compareFunc) {
  IOG_ASSERT(text);
  IOG_ASSERT(compareFunc);

  // -- qsort doesn't work for array of pointers --
  //qsort(text->lines, text->lines_size, sizeof(char *), (int (*) (const void *, const void *)) compareFunc);
  
  bubbleSort(text->lines, text->lines_size, (compare_func_t) compareFunc);

  return OK;
}


ReturnCode bubbleSort(void *arr, size_t arr_len, compare_func_t compareFunc) {
  IOG_ASSERT(arr);
  IOG_ASSERT(compareFunc);

  printf(BLACK("------SORTING------\n"));

  for (size_t i = 0; i < arr_len-1; i++) {
    for (size_t j = 0; j < arr_len-1-i; j++) {
        printf(BLUE("[SORT] i = %lu, j = %lu\n"), i, j);
        if (compareFunc ((void *) ((void **) arr)[j], (void *) ((void **) arr)[j+1] ) > 0) {
          swapPointers((void **) arr + j,  (void **) arr + j + 1);
        }
        printf("\n");
    }
  }
  printf("\n");

  return OK;
}

ReturnCode swapPointers(void **first, void **second) {  
  IOG_ASSERT(first);
  IOG_ASSERT(second);

  void *tmp = *first;
  *first = *second;
  *second = tmp;

  printf(MAGENTA("[SWAP]") BLACK(" %p <-->  %p \n"), first, second);

  return OK;
}

