#pragma once
#ifndef META_UTILITY_COMMENT_H
#define META_UTILITY_COMMENT_H

#include <meta/preprocessor/cat.h>

/*!
 * @brief add a comment in the asm code (convenient to retrieve an assembly section)
 */
#ifndef NDEBUG
#ifdef __GNUC__
#define NASM_COMMENT(X) asm(CAT("#", #X) : : );
#else
#define NASM_COMMENT(X) __asm__(CAT("#", #X));
#endif // __GNUC__
#else
#define NASM_COMMENT(X)
#endif // NDEBUG

#define NASM_STATEMENT(X)           \
    NASM_COMMENT("START " #X)       \
    X;                              \
    NASM_COMMENT("END "   #X)

#endif // META_UTILITY_COMMENT_H
