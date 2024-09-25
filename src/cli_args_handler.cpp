#include <string.h>
#include "cli_colors.h"
#include "iog_assert.h"
#include "cli_args_handler.h"
#include "return_codes.h"
#include "iog_debug_out.h"

ReturnCode handleProgramArgs(CliOptions *opts, int argc, const char *argv[]) {
  IOG_ASSERT(opts);
  IOG_ASSERT(argv);
  IOG_ASSERT(argc > 0);

  if (argc == 1)
    return OK;

  for (int i = 1; i < argc; i++) {
    if (!strcmp(argv[i], "-b") || !strcmp(argv[i], "--backward")) {
      opts->is_back = 1;
    } else if (!strcmp(argv[i], "-o") || !strcmp(argv[i], "--output")) {
      if (i+1 >= argc) {
        fprintf(stderr, RED("ERORR: ") "no output file name\n");
        return ERR_NO_OUTPUT_FILE;
      }

      opts->output_file = argv[i];
    } else {
      opts->file_with_text = argv[i];
    }
  }

  printOpts(opts);

  return OK;
}

ReturnCode printOpts(const CliOptions *opts) {
  IOG_ASSERT(opts);

  IF_DEBUGING_THEN( fprintf(stderr, BLACK("-------- CLI OPTIONS ------------" "\n")) );
  IF_DEBUGING_THEN( fprintf(stderr, BLUE("[INFO] ") BLACK("TEXT FILE:   ") "%s\n", opts->file_with_text) );
  IF_DEBUGING_THEN( fprintf(stderr, BLUE("[INFO] ") BLACK("OUTPUT FILE: ") "%s\n", opts->output_file) );
  IF_DEBUGING_THEN( fprintf(stderr, BLUE("[INFO] ") BLACK("IS_BACKWARD: ") "%d\n", opts->is_back) );
  IF_DEBUGING_THEN( fprintf(stderr, "\n") );

  return OK;
}
