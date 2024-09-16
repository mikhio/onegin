#ifndef TEXT_SORTER_H
#define TEXT_SORTER_H

#include "../inc/text_reader.h"
#include "../inc/text_sorter.h"
#include "../inc/return_codes.h"
#include "../inc/string_compare.h"

typedef int (*compare_func_t) (void *, void *);

ReturnCode bubbleSort(void *arr, size_t arr_len, compare_func_t compareFunc);
ReturnCode sortText(Text *text, strcmp_func_t compareFunc);
ReturnCode swapPointers(void **first, void **second);

#endif // TEXT_SORTER_H
