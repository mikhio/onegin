#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/iog_assert.h"

#include "../inc/iog_string.h"
#include "../inc/text_reader.h"
#include "../inc/text_sorter.h"


int main(int argc, const char *argv[]) {
  Text onegin = {};
  
  readTextData("onegin.txt", &onegin);

  sortText(&onegin, &istrcmp);

  for (int i = 0; i < onegin.lines_size; i++ ) {
    printf("'%s'\n", onegin.lines[i]);
  }

  freeAllTextData(&onegin);

  return 0;
}
