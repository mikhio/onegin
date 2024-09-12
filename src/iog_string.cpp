#include "../inc/iog_assert.h"

size_t istrlen(const char *str) {
  IOG_ASSERT(str);

  int len = 0;
  while (str[len] != '\0')
    len++;

  return len;
}

int istrcpy(char *dest, const char *source) {
  IOG_ASSERT(dest);
  IOG_ASSERT(source);

  size_t src_i = 0;
  while (source[src_i] != '\0') {
    dest[src_i] = source[src_i];
    src_i++;
  }
  dest[src_i] = '\0';

  return 0;
}

int istrcat(char *dest, const char *source) {
  IOG_ASSERT(dest); 
  IOG_ASSERT(source); 

  char *dest_end = dest + istrlen(dest);
  istrcpy(dest_end, source);
  
  return 0;
}

int istrcmp(const char *first_str, const char *second_str) {
  IOG_ASSERT(first_str);
  IOG_ASSERT(second_str);

  int diff = 0;
  size_t str_index = 0;

  do {
    diff = (int) first_str[str_index] - (int) second_str[str_index];
    
    if ((first_str[str_index] == '\0') || (second_str[str_index] == '\0'))
      break;

    str_index++;

  } while (diff == 0);

  return diff;
}

const char *istrchr(const char *str, char character) {
  IOG_ASSERT(str);
   
 const char *chr = str;
  while ((*chr != character) && (chr != '\0'))
    chr++;

  return chr;
}

