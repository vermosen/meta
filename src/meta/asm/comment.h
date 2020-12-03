#pragma once
#ifndef META_ASM_COMMENT_H
#define META_ASM_COMMENT_H

#include <meta/preprocessor/cat.h>

// add a comment that will show up in the resulting asm code
#ifdef __GNUC__
#ifdef NDEBUG
#define ASM_COMMENT(X);
#else
#define ASM_COMMENT(X) asm(CAT("#", #X) : : )
#endif // NDEBUG
#else
#ifdef _MSC_VER
#define ASM_COMMENT(X) X
#else
// TODO: find a way to pass asm instructions in MSVC
//#define ASM_COMMENT(X) __asm__(CAT("#", #X));
#endif // _MSC_VER
#endif

// surround a block with corresponding tags
#define ASM_STATEMENT(X, T)         \
    ASM_COMMENT("START " #T);       \
    X;                              \
    ASM_COMMENT("END " #T)

#endif // META_ASM_COMMENT_H
