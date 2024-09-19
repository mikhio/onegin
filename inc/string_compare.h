#ifndef STRING_COMPARE_H
#define STRING_COMPARE_H

struct StrLine {
  char *line;
  size_t length;
};

typedef int (*strcmp_func_t) (const StrLine *, const StrLine *);

int strcmp_fwd (const StrLine *first_str, const StrLine *second_str);
int strcmp_bwd (const StrLine *first_str, const StrLine *second_str);

int str_compare_forward  (const void *str1, const void *str2);
int str_compare_backward (const void *str1, const void *str2);

int mywrap_str_compare (const void *ptr1, const void *ptr2, strcmp_func_t compare_func);


ReturnCode skipExtraCharsFront (StrLine *str);
ReturnCode skipExtraCharsBack  (StrLine *str);

#endif // COMPARE_H
