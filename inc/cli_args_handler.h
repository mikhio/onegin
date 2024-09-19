#ifndef CLI_ARGS_HANDLER_H
#define CLI_ARGS_HANDLER_H

#include "return_codes.h"

struct CliOptions {
  const char *file_with_text;
  const char *output_file;
  int is_back;
  int is_debuging;
};

ReturnCode handleProgramArgs (CliOptions *opts, int argc, const char *argv[]);
ReturnCode printOpts (const CliOptions *opts);

#endif // CLI_ARGS_HANDLER_H
