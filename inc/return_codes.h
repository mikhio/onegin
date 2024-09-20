#ifndef RETURN_CODES_H
#define RETURN_CODES_H

enum ReturnCode {
  OK                   = 0,
  ERR_CANT_ALLOCATE    = 1,
  ERR_CANT_READ_FILE   = 3,
  ERR_CANT_SPLIT       = 4,
  ERR_NULL_BUFFER      = 5,
  ERR_NO_OUTPUT_FILE   = 6,
  ERR_CANT_FILL_BUFFER = 7,

  NR_RETURN_CODE       = 8,
};

#endif // RETURN_CODES_H
