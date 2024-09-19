#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

#include "../inc/text_reader.h"
#include "../inc/return_codes.h"
#include "../inc/cli_colors.h"
#include "../inc/iog_assert.h"
#include "../inc/cli_args_handler.h"


ReturnCode readTextData(const CliOptions *opts, Text *text) {
  IOG_ASSERT(opts);
  IOG_ASSERT(text);

  FILE *text_file = fopen(opts->file_with_text, "rb");

  if (!text_file) {
    fprintf(stderr, RED("ERROR: ") "Can't open file: " BLACK("%s") "\n", opts->file_with_text);
    return ERR_CANT_READ_FILE;
  }
  
  if (readFileLen(text_file, text) != OK) {
    fprintf(stderr, RED("ERROR: ") "Can't read length of file: " BLACK("%s") "\n", opts->file_with_text);

    fclose(text_file);
    return ERR_CANT_READ_FILE;
  }

  if (allocateBuffer(text) != OK) {
    fprintf(stderr, RED("ERROR: ") "Can't allocate buffer for text" "\n");

    fclose(text_file);
    return ERR_CANT_ALLOCATE;
  }

  if (fread(text->buffer, sizeof(char), text->buffer_size, text_file) < text->buffer_size) {
    fprintf(stderr, RED("ERROR: ") "Can't read text from file: " BLACK("%s") "\n", opts->file_with_text);

    fclose(text_file);
    return ERR_CANT_READ_FILE;
  }

  text->buffer[text->buffer_size] = 0; // TODO: move to function
  
  if (splitTextToLines(text) != OK) {
    fprintf(stderr, MAGENTA("Warrning: ") "Can't split text to lines" "\n");
  }

  fclose(text_file);
  return OK;
}

ReturnCode readFileLen(FILE *text_file, Text *text) { 
  IOG_ASSERT(text); 
  
  int text_fd = fileno(text_file);
  struct stat stat_buf = {};

  if (fstat(text_fd, &stat_buf) != 0)
    return ERR_CANT_READ_FILE;

  printf(BLACK("------ READING FILE STAT ------- \n"));
  printf(BLUE("[INFO]") BLACK(" ST_SIZE:    ")  "%lld" "\n", stat_buf.st_size); 
  printf(BLUE("[INFO]") BLACK(" ST_BLKSIZE: ")  "%d"   "\n", stat_buf.st_blksize); 
  printf(BLUE("[INFO]") BLACK(" ST_BLOCKS:  ")  "%lld" "\n", stat_buf.st_blocks); 
  printf("\n");

  text->buffer_size = stat_buf.st_size;
  text->buffer_capacity = stat_buf.st_size + 1;

  return OK; 
}


ReturnCode splitTextToLines(Text *text) {
  IOG_ASSERT(text);
  
  if (countLines(text) != OK)
    return ERR_CANT_SPLIT;

  if (allocateLinesArr(text) != OK)
    return ERR_CANT_ALLOCATE;
  
  printf(BLACK("------ SPLITING ------- \n"));
  printf(BLUE("[INFO] ") BLACK("lines_size     ") "= %lu\n", text->lines_size);
  printf(BLUE("[INFO] ") BLACK("lines_capacity ") "= %lu\n", text->lines_capacity);
  printf("\n");
  
  text->lines[0].line = text->buffer;

  size_t line_count = 1; 
  for (size_t i = 0; i < text->buffer_size; i++) {
    if (text->buffer[i] == '\n') { 
      if (line_count >= text->lines_size)
        return ERR_CANT_SPLIT;

      /*if (text->buffer[i+1] == '\n' || text->buffer[i+1] == '\0') {
        text->lines_size--;
        text->buffer[i] = '\0';
        printf(RED("[SKIP] ") BLACK("NULL %p") " '%c'\n", &text->buffer[i], text->buffer[i]);
        continue;
      }*/

      text->lines[line_count].line = text->buffer + i + 1;
      text->lines[line_count-1].length = text->lines[line_count].line - text->lines[line_count-1].line - 1;
      text->buffer[i] = '\0';

      printf(GREEN("[READ] ") BLACK("%p %p") " '%s' size: %lu\n", 
          &text->lines[line_count-1].line,
          text->lines[line_count-1].line,
          text->lines[line_count-1].line, 
          text->lines[line_count-1].length
      );
      line_count++;
    }
  }
  
  printf("\n");
  printf(BLUE("[INFO] ") BLACK("line_count") " = %lu -> " BLACK("lines_size") " = %lu\n", line_count, text->lines_size);
  printf("\n");

  return OK;
}

ReturnCode countLines(Text *text) {
  IOG_ASSERT(text);

  if (!text->buffer)
    return ERR_NULL_BUFFER;

  size_t line_count = 0; 
  for (int i = 0; i < text->buffer_size+1; i++) {
    if ((text->buffer[i] == '\n') || (text->buffer[i] == '\0'))
      line_count++;
  }

  text->lines_size = line_count;
  text->lines_capacity = line_count+1;

  return OK;
}

ReturnCode allocateLinesArr(Text *text) {
  IOG_ASSERT(text);
  
  StrLine *tmp = NULL;

  if (!text->lines)
    tmp = (StrLine *) calloc(text->lines_capacity, sizeof(StrLine));
  else
    tmp = (StrLine *) realloc(text->lines, text->lines_capacity * sizeof(StrLine));


  if (tmp == NULL)
    return ERR_CANT_ALLOCATE;

  text->lines = tmp;
  text->lines[text->lines_capacity].line = NULL;
  text->lines[text->lines_capacity].length = 0;

  return OK;
}


ReturnCode allocateBuffer(Text *text) {
  IOG_ASSERT(text);

  char *tmp = NULL;

  if (!text->buffer)
    tmp = (char *) calloc(text->buffer_capacity, sizeof(char));
  else
    tmp = (char *) realloc(text->buffer, text->buffer_capacity * sizeof(char));


  if (tmp == NULL)
    return ERR_CANT_ALLOCATE;

  text->buffer = tmp;
  text->buffer[text->buffer_size] = '\0';

  return OK;
}

ReturnCode freeAllTextData(Text *text) {
  IOG_ASSERT(text);

  free(text->lines);
  text->lines = NULL;
  text->lines_size = 0;
  text->lines_capacity = 0;

  free(text->buffer);
  text->buffer = NULL;
  text->buffer_size = 0;
  text->buffer_capacity = 0;

  return OK;
}
