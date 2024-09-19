#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/cli_args_handler.h"
#include "../inc/cli_colors.h"
#include "../inc/text_reader.h"
#include "../inc/text_sorter.h"
#include "../inc/string_compare.h"


int main(int argc, const char *argv[]) {
  CliOptions opts = {};
  Text onegin = {};

  //TODO:defualt opts

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
