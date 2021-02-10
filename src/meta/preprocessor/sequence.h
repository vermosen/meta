#pragma once
#ifndef META_PREPROCESSOR_SEQUENCE_H
#define META_PREPROCESSOR_SEQUENCE_H

#include <boost/preprocessor/variadic/to_seq.hpp>
#include <boost/preprocessor/seq/for_each.hpp>

// Doubles the parentheses of a Boost.PP sequence,
// i.e. (a, b)(c, d) becomes ((a, b))((c, d))
#define META_SEQ_DOUBLE_PARENS_0(...) \
     ((__VA_ARGS__)) META_SEQ_DOUBLE_PARENS_1

#define META_SEQ_DOUBLE_PARENS_1(...) \
     ((__VA_ARGS__)) META_SEQ_DOUBLE_PARENS_0

#define META_SEQ_DOUBLE_PARENS_0_END
#define META_SEQ_DOUBLE_PARENS_1_END

#define META_SEQ_DOUBLE_PARENS(SEQ) \
    BOOST_PP_CAT(META_SEQ_DOUBLE_PARENS_0 SEQ, _END)

#endif // META_PREPROCESSOR_SEQUENCE_H
