#pragma once
#ifndef META_PREPROCESSOR_SIZE_H
#define META_PREPROCESSOR_SIZE_H

#include <boost/preprocessor/seq/size.hpp>

#include <meta/preprocessor/sequence.h>

#define META_SIZE(SEQ) \
	BOOST_PP_SEQ_SIZE(META_SEQ_DOUBLE_PARENS(SEQ));

#endif
