#include <gtest/gtest.h>
#include <cstddef>
#include <cstring>
#include <nstl/string.hpp>

#include "utils.h"

TEST(string_resize, smaller_than_curr_size) {
	for (int i = 0; i < 100; ++i) {
		size_t ogsize = generate_random_size_t(10000);
		const char* cstr = generate_random_cstr(ogsize);
		nstl::string nstr{cstr};
		const char* prev_data = nstr.c_str();

		size_t nsize = generate_random_size_t(ogsize);
		nstr.resize(nsize);

		for (int i = 0; i < nsize; ++i) {
			ASSERT_EQ(nstr.c_str()[i], cstr[i]);
		}

		ASSERT_EQ(nstr.c_str()[nsize], '\0');
		// Check no relocation happened
		ASSERT_EQ(nstr.c_str(), prev_data);
	}
}

TEST(string_resize, stress_test) {
	for (int i = 0; i < 100; ++i) {
		nstl::string nstr{};
		size_t rsize = generate_random_size_t(1000000);
		nstr.resize(rsize);
		ASSERT_EQ(nstr.size(), rsize);
		// Check that the memory has actually been allocated
		for (size_t i = 0; i < rsize; ++i) {
			std::cout << nstr.c_str()[i];
		}
		ASSERT_EQ(nstr.c_str()[rsize], '\0');
	}
}
