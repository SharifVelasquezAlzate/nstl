#include <gtest/gtest.h>
#include <nstl/string.h>
#include <cstddef>
#include <cstring>

#include "utils/general.h"

TEST(string_reserve, empty_string) {
	nstl::string nstr{};
	nstr.reserve(20);
}

TEST(string_reserve, smaller_than_curr_capacity) {
	for (int i = 0; i < 1000; ++i) {
		size_t ogsize = generate_random_size_t(10000);
		const char* cstr = generate_random_cstr(ogsize);
		nstl::string nstr{cstr};

		ASSERT_STREQ(nstr.c_str(), cstr);
		ASSERT_EQ(strcmp(nstr.c_str(), cstr), 0);

		const char* prev_data = nstr.c_str();

		size_t ncap = generate_random_size_t(ogsize);
		nstr.reserve(ncap);

		// Check no relocation happened
		ASSERT_EQ(nstr.c_str(), prev_data);
		// Verify the data is still there
		for (int j = 0; j <= ogsize; ++j) {
			ASSERT_EQ(nstr.c_str()[j], cstr[j]) << j << " " << ogsize << " " << ncap << " " << nstr.capacity();
		}
		ASSERT_EQ(strcmp(nstr.c_str(), cstr), 0);
		// Check that the size didn't change
		ASSERT_EQ(nstr.size(), ogsize);

		delete[] cstr;
	}
}

TEST(string_reserve, bigger_than_curr_capacity) {
	for (int i = 0; i < 1000; ++i) {
		size_t ogsize = generate_random_size_t(10000);
		const char* cstr = generate_random_cstr(ogsize);
		nstl::string nstr{cstr};
		ASSERT_EQ(nstr.size(), ogsize);
		const char* prev_data = nstr.c_str();

		size_t ncap = ogsize + 2 + generate_random_size_t(10000);
		nstr.reserve(ncap);

		// Check a relocation happened
		ASSERT_NE(nstr.c_str(), prev_data);
		// Check that the data is still there
		ASSERT_EQ(strcmp(nstr.c_str(), cstr), 0);
		// Check that the size didn't change
		ASSERT_EQ(nstr.size(), ogsize) << ncap;
		// Check that the capacity is at most 1 more than the specified
		ASSERT_TRUE(nstr.capacity() == ncap || nstr.capacity() == ncap + 1);
	}
}
