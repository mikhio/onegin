#ifndef IOG_ASSERT_H
#define IOG_ASSERT_H

#include <stdio.h>
#include <stdarg.h>


/** @file IOG_Assert.h */

#ifdef IOG_NDEBUG

/// If not debug mode, then ignore asserts
#define IOG_ASSERT(x) ()

#else // IOG_NDEBUG


/// Calling assert macros

#define IOG_ASSERT(x) {\
  iog_assert_func( x ? 0 : 1, #x, __FILE__, __LINE__, __PRETTY_FUNCTION__);\
}

#endif // IOG_NDEBUG

/// My assert function
void iog_assert_func(int x, const char *expr, const char *file, unsigned int line, const char *function);

#endif // IOG_ASSERT_H
