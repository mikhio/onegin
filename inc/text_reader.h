#ifndef TEXT_READER_H
#define TEXT_READER_H

#include "../inc/return_codes.h"

struct Text {
  char  *buffer;
  size_t buffer_capacity;
  size_t buffer_size;
  
  char **lines;
  size_t lines_capacity;
  size_t lines_size;
};

ReturnCode readTextData (const char *file_path, Text *text);
ReturnCode readFileLen  (FILE *text_file, Text *text);

ReturnCode splitTextToLines (Text *text);
ReturnCode countLines       (Text *text);

ReturnCode allocateLinesArr (Text *text);
ReturnCode allocateBuffer   (Text *text);

ReturnCode freeAllTextData  (Text *text);


#endif // TEXT_READER_H
