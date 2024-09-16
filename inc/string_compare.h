#ifndef STRING_COMPARE_H
#define STRING_COMPARE_H

typedef int (*strcmp_func_t) (const char *, const char *);

int str_compare_forward  (const char *str1, const char *str2);
int str_compare_backward (const char *str1, const char *str2);

const char *skipExtraChars (const char *str);

#endif // COMPARE_H
