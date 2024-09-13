#ifndef TEXT_SORTER_H
#define TEXT_SORTER_H

#include "../inc/text_reader.h"
#include "../inc/text_sorter.h"
#include "../inc/return_codes.h"
#include "../inc/iog_string.h"

ReturnCode bubbleSort(Text *text, strcmp_func_t compareFunc);
ReturnCode sortText(Text *text, strcmp_func_t compareFunc);

#endif // TEXT_SORTER_H
