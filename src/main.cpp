#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/iog_assert.h"

#include "../inc/iog_string.h"

struct Text {
  size_t data_capacity;
  size_t data_size;
  char **data;
};

enum ReturnCode {
  OK                = 0,
  ERR_CANT_ALLOCATE = 1,

  NR_RETURN_CODE    = 2,
};

const size_t ALLOCATION_CHUNK = 20;

ReturnCode allocateMore(Text *text, size_t chunk_size) {
  IOG_ASSERT(text);

  char **tmp = NULL;

  if (text->data_capacity == 0)
    tmp = (char **) calloc(chunk_size, sizeof(char *));
  else
    tmp = (char **) realloc(text->data, text->data_capacity);


  if (tmp == NULL)
    return ERR_CANT_ALLOCATE;

  text->data_capacity += chunk_size;
  text->data = tmp;

  return OK;
}

ReturnCode readTextData(const char *file_path, Text *text) {
  IOG_ASSERT(text);
  IOG_ASSERT(file_path);

  FILE *text_file = fopen(file_path, "rb");
  
  IOG_ASSERT(text_file);

  size_t line_index = 0;
  size_t line_len = 0;
  ssize_t readl = 0;
  
  do {
    if (line_index == text->data_capacity) {
      if (allocateMore(text, ALLOCATION_CHUNK) != OK)
        break;
    }

    readl = getline(&text->data[line_index], &line_len, text_file);

    line_index++;

  } while (readl != -1);

  text->data_size = line_index;

  fclose(text_file);

  return OK;
}


ReturnCode freeAllData(Text *text) {
  IOG_ASSERT(text);

  for (int i = 0; i < text->data_size; i++)
    free(text->data[i]);

  free(text->data);

  return OK;
}

ReturnCode sortText(Text *text) {
  IOG_ASSERT(text);

  qsort(text->data, text->data_size, sizeof(char *), (int (*) (const void *, const void *)) istrcmp);

  return OK;
}

int main(int argc, const char *argv[]) {
  Text text = {};
  
  readTextData("onegin.txt", &text);

  sortText(&text);

  for (int i = 0; i < text.data_size; i++ ) {
    printf("%s", text.data[i]);
  }

  freeAllData(&text);

  return 0;
}
