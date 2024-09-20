#ifndef TEXT_READER_H
#define TEXT_READER_H

#include "return_codes.h"
#include "string_compare.h"
#include "cli_args_handler.h"


struct Text {
  char  *buffer;
  size_t buffer_capacity;
  size_t buffer_size;
  
  StrLine *lines;
  size_t lines_capacity;
  size_t lines_size;
};

ReturnCode readTextData (const CliOptions *opts, Text *text);
ReturnCode readFileLen  (FILE *text_file, Text *text);
ReturnCode fillBuffer   (FILE *text_file, Text *text);

ReturnCode splitTextToLines (Text *text);
ReturnCode countLines       (Text *text);

ReturnCode allocateLinesArr (Text *text);
ReturnCode allocateBuffer   (Text *text);

ReturnCode freeAllTextData  (Text *text);


#endif // TEXT_READER_H
