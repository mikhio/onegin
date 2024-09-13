#ifndef RETURN_CODES_H
#define RETURN_CODES_H

enum ReturnCode {
  OK                 = 0,
  ERR_CANT_ALLOCATE  = 1,
  ERR_CANT_READ_FILE = 3,
  ERR_CANT_SPLIT     = 4,
  ERR_NULL_BUFFER    = 5,

  NR_RETURN_CODE     = 6,
};

#endif // RETURN_CODES_H
