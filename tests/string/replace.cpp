#include <gtest/gtest.h>
#include <cstddef>
#include <cstring>
#include <string>

#include <nstl/exceptions.h>
#include <nstl/string.h>

#include "utils/general.h"
#include "utils/string.h"

TEST(string_replace, nothing) {
	nstl::string nstr{"Hello"};
	std::string str{"Hello"};

	const char* cstr = "";

	nstr.replace(0, 0, cstr);

	ASSERT_IDENTICAL(nstr, str);
}

TEST(string_replace, cstr_random) {
	for (int i = 0; i < 10000; ++i) {
		size_t size = 1 + generate_random_size_t(1000);
		char* cstr = generate_random_cstr(size);

		nstl::string nstr{cstr};
		std::string str{cstr};

		size_t pos = generate_random_size_t(size - 1);
		size_t len = generate_random_size_t(size);

		char* cstr2 = generate_random_cstr(len);

		nstr.replace(pos, len, cstr2);
		str.replace(pos, len, cstr2);

		ASSERT_IDENTICAL(nstr, str);

		delete[] cstr;
	}
}

TEST(string_replace, nstr_random) {
	for (int i = 0; i < 10000; ++i) {
		size_t size = 1 + generate_random_size_t(1000);
		char* cstr = generate_random_cstr(size);

		nstl::string nstr{cstr};
		std::string str{cstr};

		size_t pos = generate_random_size_t(size - 1);
		size_t len = generate_random_size_t(size);

		char* cstr2 = generate_random_cstr(len);
		nstl::string nstr2{cstr2};
		std::string str2{cstr2};

		nstr.replace(pos, len, nstr2);
		str.replace(pos, len, str2);

		ASSERT_IDENTICAL(nstr, str);

		delete[] cstr;
	}
}
