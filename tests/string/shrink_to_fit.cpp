#include <gtest/gtest.h>
#include <nstl/string.h>
#include <cstddef>
#include <cstring>

#include "utils.h"

TEST(shrink_to_fit, empty) {
	nstl::string nstr{};
	size_t old_capacity = nstr.capacity();
	nstr.shrink_to_fit();
	ASSERT_EQ(nstr.capacity(), old_capacity);
}

TEST(shrink_to_fit, small_strings) {
	for (int i = 0; i < 1000; ++i) {
		size_t size = generate_random_size_t(23);
		char* cstr = generate_random_cstr(size);

		nstl::string nstr{cstr};
		size_t old_capacity = nstr.capacity();
		nstr.shrink_to_fit();
		ASSERT_EQ(nstr.capacity(), old_capacity);
	}
}

TEST(shrink_to_fit, large_strings) {
	for (int i = 0; i < 1000; ++i) {
		size_t size = 24 + generate_random_size_t(10000);
		char* cstr = generate_random_cstr(size);

		nstl::string nstr{cstr};
		nstr.shrink_to_fit();
		ASSERT_TRUE(nstr.capacity() - nstr.size() <= 1);
	}
}
