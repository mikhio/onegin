#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cli_args_handler.h"
#include "cli_colors.h"
#include "text_reader.h"
#include "text_sorter.h"
#include "string_compare.h"


int main(int argc, const char *argv[]) {
  CliOptions opts = {};
  Text onegin = {};

  if (handleProgramArgs(&opts, argc, argv) != OK) {
    fprintf(stderr, RED("ERROR: ") "Can't handle args");
    return -1;
  }
  
  if (readTextData(&opts, &onegin) != OK) {
    return -1;
  }

  sortText(&opts, &onegin);

  if (opts.output_file == NULL) {
    printf(BLACK("-------- RESULT ---------\n"));
    for (int i = 0; i < onegin.lines_size; i++ ) {
      printf("'%s'\n", onegin.lines[i].line);
    }
  }

  freeAllTextData(&onegin);

  return 0;
}
