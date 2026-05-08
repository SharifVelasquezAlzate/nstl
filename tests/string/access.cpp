#include <gtest/gtest.h>
#include <cstddef>
#include <cstring>

#include <nstl/exceptions.h>
#include <nstl/string.h>

#include "utils.h"

TEST(access, random) {
	for (size_t iter = 0; iter < 1000; ++iter) {
		const size_t size = generate_random_size_t(100000);
		const char* cstr = generate_random_cstr(size);
		nstl::string nstr{cstr};

		for (int i = 0; i < size; ++i) {
			ASSERT_EQ(nstr[i], cstr[i]);
			ASSERT_EQ(nstr.at(i), cstr[i]);
		}
	}
}

TEST(access, out_of_range) {
	nstl::string nstr{"Hello"};
	EXPECT_THROW(nstr[5], nstl::excep::out_of_range);
	EXPECT_THROW(nstr.at(5), nstl::excep::out_of_range);
}

TEST(access, out_of_range_random) {
	for (size_t iter = 0; iter < 1000; ++iter) {
		const size_t size = generate_random_size_t(100000);
		const char* cstr = generate_random_cstr(size);
		nstl::string nstr{cstr};

		for (size_t i = size; i < size + 100; ++i) {
			EXPECT_THROW(nstr[i], nstl::excep::out_of_range);
			EXPECT_THROW(nstr.at(i), nstl::excep::out_of_range);
		}
	}
}
