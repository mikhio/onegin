#ifndef TEXT_SORTER_H
#define TEXT_SORTER_H

#include "../inc/text_reader.h"
#include "../inc/text_sorter.h"
#include "../inc/return_codes.h"
#include "../inc/string_compare.h"

typedef int (*compare_func_t) (const void *, const void *);

ReturnCode bubbleSort   (void *arr, size_t arr_len, size_t el_size, compare_func_t compareFunc);
ReturnCode sortText     (const CliOptions *opts, Text *text);
ReturnCode swapElements (void *first, void *second, size_t el_size);

#endif // TEXT_SORTER_H
