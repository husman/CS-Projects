#ifndef GLOBALS_H_
#define GLOBALS_H_
// To make our codes more cross-platform and without the need to continuously
// rewrite our codes for different platforms, we include this local inttypes
// header to define the standard fix-width data types part of the C99 standard.

// The ISO/IEC 9899:1999 (E), or C99 standard, defines the prototypes for
// 'Format conversion of integer types' on page 197 (page 211 in pdf).
// The implementation for these 'Format conversion of integer types' is
// defined on page 254 (or page 268 of the pdf).

// Microsoft VC compilers, which are based on the C++0x language specification,
// does not support these standard types. These types were later defined. Microsoft
// selectively added support for particular C++11 language specifications, however
// these standard integer types were not the chosen few features Microsoft implemented.
// Therefore, we include this header, which fills in the necessary gap for us to use
// these types by defining them. This header does not make the VC compiler completely
// compatible with the C99 or C++11 standards, however, it will do for this project.

// Reference documents:
// You can find ISO/IEC 9899:1999 (E), aka C99 at:
// http://cs.nyu.edu/courses/spring13/CSCI-GA.2110-001/downloads/C99.pdf

// You can find the ISO/IEC 14882:2003(E), aka C++11 at:
// http://cs.nyu.edu/courses/spring13/CSCI-GA.2110-001/downloads/C++%20Standard%202003.pdf

// Additional references:
// 1. http://msdn.microsoft.com/en-us/library/vstudio/hh567368.aspx
// 2. https://www2.research.att.com/~bs/what-is-2009.pdf
#ifdef WIN32
#include "inttypes.h"
#endif

#endif