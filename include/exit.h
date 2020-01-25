#ifndef EXIT_H
#define EXIT_H

#include <err.h>

#define CHECK_MALLOC(result, what)                                             \
	if ((result) == NULL) {                                                    \
		errx(EXIT_OUT_OF_MEMORY, "Unable to allocate memory for %s", what);    \
	}

#define _FILE_ERROR_BITS 0x04       /* 0b000001xx */
#define _RUNTIME_ERROR_BITS 0x08    /* 0b00001xxx */
#define _PROGRAMMER_ERROR_BITS 0x60 /* 0b011xxxxx */

#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif

#ifndef EXIT_FAILURE
#define EXIT_FAILURE 1
#endif

#define EXIT_CANNOT_READ_FILE (0 | _FILE_ERROR_BITS)
#define EXIT_NO_FILE_SPECIFIED (1 | _FILE_ERROR_BITS)
// #define EXIT_ (2 | _FILE_ERROR_BITS)
// #define EXIT_ (3 | _FILE_ERROR_BITS)

#define EXIT_OUT_OF_MEMORY (0 | _RUNTIME_ERROR_BITS)
#define EXIT_SYNTAX_ERROR (1 | _RUNTIME_ERROR_BITS)
// #define EXIT_CRYPTOGRAPHY_ERROR (2 | _RUNTIME_ERROR_BITS)
// #define EXIT_OVER_PRIVILEGED (3 | _RUNTIME_ERROR_BITS)
// #define EXIT_UNABLE_TO_GET_PASSPHRASE (4 | _RUNTIME_ERROR_BITS)

#define EXIT_PROGRAMMER_ERROR (0 | _PROGRAMMER_ERROR_BITS)

#endif
