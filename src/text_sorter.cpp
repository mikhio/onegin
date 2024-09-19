#include <stdio.h>
#include <stdlib.h>

#include "../inc/cli_colors.h"
#include "../inc/text_sorter.h"
#include "../inc/iog_assert.h"
#include "../inc/string_compare.h"

ReturnCode sortText(Text *text, compare_func_t compareFunc) {
  IOG_ASSERT(text);
  IOG_ASSERT(compareFunc);

  // -- qsort doesn't work for array of pointers --
  //qsort(text->lines, text->lines_size, sizeof(StrLine),  compareFunc);
  
  bubbleSort(text->lines, text->lines_size, sizeof (StrLine), compareFunc);

  return OK;
}


ReturnCode bubbleSort(void *arr, size_t arr_len, size_t el_size, compare_func_t compareFunc) {
  IOG_ASSERT(arr);
  IOG_ASSERT(compareFunc);

  printf(BLACK("------SORTING------\n"));
  printf(BLUE("[INFO] ") BLACK("el_size") " = %lu\n", el_size);
  printf("\n");

  for (size_t i = 0; i < arr_len-1; i++) {
    for (size_t j = 0; j < arr_len-1-i; j++) {
        printf(BLUE("[SORT] i = %lu, j = %lu\n"), i, j);

        void *first_el =  (void *) ((char *) arr + j*el_size);
        void *second_el = (void *) ((char *) arr + (j + 1)*el_size);

        if (compareFunc(first_el, second_el) > 0) {
          swapElements(first_el, second_el, el_size);
        }

        printf("\n");
    }
  }
  printf("\n");

  return OK;
}

ReturnCode swapElements(void *first, void *second, size_t el_size) {  
  IOG_ASSERT(first);
  IOG_ASSERT(second);

  printf(MAGENTA("[SWAP]  ") BLACK(" %p <--> %p  el_size = %lu\n"), first, second, el_size);

  char tmp = 0;
  for (size_t i = 0; i < el_size; i++) {
    char *first_byte  = ((char *) first + i);
    char *second_byte = ((char *) second + i);

    printf(RED("  - (%p) %2x  (%p) %2x\n"), first_byte, (unsigned char) *first_byte, second_byte, (unsigned char) *second_byte);

    tmp = *first_byte;
    *first_byte = *second_byte;
    *second_byte = tmp;

    printf(GREEN("  + (%p) %2x  (%p) %2x\n"), first_byte, (unsigned char) *first_byte, second_byte, (unsigned char) *second_byte);
  }

  printf(MAGENTA("[SWAPED]") BLACK(" %p <--> %p  el_size = %lu\n"), first, second, el_size);

  return OK;
}

