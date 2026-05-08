#include <gtest/gtest.h>
#include <cstddef>
#include <cstring>
#include <nstl/string.hpp>

#include "utils.h"

TEST(string_resize, small_to_large_with_null_terminators) {
	// using namespace std::string_literals;

	// std::string str = "Hello\0\0Joy"s;
	// nstl::string nstr {"Hello"};
	// nstr += '\0';
	// nstr += '\0';
	// nstr += "Joy";
	// Trigger resize
	// nstr.resize(30);
	//
	// ASSERT_EQ(nstr.size(), 30);
	//
	// for (int i = 0; i < 10; ++i) {
	// 	ASSERT_EQ(nstr[i], str[i]);
	// }
}

/* ---------------------------- RANDOMIZED TESTS ---------------------------- */
TEST(string_resize, smaller_than_curr_size) {
	for (int i = 0; i < 10000; ++i) {
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

		delete cstr;
	}
}

TEST(string_resize, bigger_than_curr_size) {
	for (int i = 0; i < 10000; ++i) {
		size_t ogsize = generate_random_size_t(10000);
		const char* cstr = generate_random_cstr(ogsize);
		nstl::string nstr{cstr};

		size_t nsize = ogsize + 1 + generate_random_size_t(10000);
		nstr.resize(nsize);

		for (int i = 0; i < ogsize; ++i) {
			ASSERT_EQ(nstr.c_str()[i], cstr[i]) << i << " " << nsize << " " << ogsize;
		}
		ASSERT_EQ(nstr.c_str()[nsize], '\0');

		ASSERT_TRUE(nstr.capacity() > ogsize);

		delete cstr;
	}
}

TEST(string_resize, stress_test) {
	for (int i = 0; i < 10000; ++i) {
		nstl::string nstr{};
		size_t rsize = generate_random_size_t(1000000);
		nstr.resize(rsize);
		ASSERT_EQ(nstr.size(), rsize);
		ASSERT_EQ(nstr.c_str()[rsize], '\0');
	}
}
