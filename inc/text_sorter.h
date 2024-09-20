#ifndef TEXT_SORTER_H
#define TEXT_SORTER_H

#include "text_reader.h"
#include "text_sorter.h"
#include "return_codes.h"
#include "string_compare.h"

typedef int (*compare_func_t) (const void *, const void *);

ReturnCode bubbleSort   (void *arr, size_t arr_len, size_t el_size, compare_func_t compareFunc);
ReturnCode sortText     (const CliOptions *opts, Text *text);
ReturnCode swapElements (void *first, void *second, size_t el_size);

#endif // TEXT_SORTER_H
