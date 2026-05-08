#include "string.h"

#include <gtest/gtest.h>
#include <cstring>

void ASSERT_IDENTICAL(const nstl::string& nstr, const std::string& str) {
	assert(nstr.size() == str.size());
	ASSERT_EQ(memcmp(nstr.c_str(), str.c_str(), nstr.size()), 0);
	ASSERT_EQ(nstr.empty(), str.empty());
}
