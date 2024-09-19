#include <string.h>
#include "../inc/cli_colors.h"
#include "../inc/iog_assert.h"
#include "../inc/cli_args_handler.h"
#include "../inc/return_codes.h"

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
    } else if (!strcmp(argv[i], "-d") || !strcmp(argv[i], "--debug")) {
      opts->is_debuging = 1;
    } else {
      opts->file_with_text = argv[i];
    }
  }

  printOpts(opts);

  return OK;
}

ReturnCode printOpts(const CliOptions *opts) {
  IOG_ASSERT(opts);

  fprintf(stderr, BLACK("-------- CLI OPTIONS ------------" "\n"));
  fprintf(stderr, BLUE("[INFO] ") BLACK("TEXT FILE:   ") "%s\n", opts->file_with_text);
  fprintf(stderr, BLUE("[INFO] ") BLACK("OUTPUT FILE: ") "%s\n", opts->output_file);
  fprintf(stderr, BLUE("[INFO] ") BLACK("IS_BACKWARD: ") "%d\n", opts->is_back);
  fprintf(stderr, BLUE("[INFO] ") BLACK("DEBUG:       ") "%d\n", opts->is_debuging);
  fprintf(stderr, "\n");

  return OK;
}
