#include <gtest/gtest.h>
#include <cstddef>
#include <cstring>
#include <string>

#include <nstl/exceptions.h>
#include <nstl/string.h>

#include "utils/general.h"
#include "utils/string.h"

TEST(string_insert, nstr_basic) {
	nstl::string nstr{"Hello"};
	std::string str{"Hello"};

	nstr.insert(1, '\0');
	str.insert(1, 1, '\0');

	ASSERT_IDENTICAL(nstr, str);
}

TEST(string_insert, char_random) {
	for (size_t i = 0; i < 1000; ++i) {
		size_t size = generate_random_size_t(100000);
		char* cstr = generate_random_cstr(size);
		nstl::string nstr{cstr};
		std::string str{cstr};

		if (size == 0) {
			continue;
		}

		size_t pos = generate_random_size_t(size - 1);
		unsigned char s = generate_random_size_t(255);
		nstr.insert(pos, s);
		str.insert(pos, 1, s);

		ASSERT_IDENTICAL(nstr, str);

		delete[] cstr;
	}
}

TEST(string_insert, cstr_random) {
	for (size_t i = 0; i < 1000; ++i) {
		size_t size = generate_random_size_t(100000);
		char* cstr = generate_random_cstr(size);
		nstl::string nstr{cstr};
		std::string str{cstr};

		if (size == 0) {
			continue;
		}

		size_t pos = generate_random_size_t(size - 1);
		size_t size2 = generate_random_size_t(100000);
		char* cstr2 = generate_random_cstr(size2);

		nstr.insert(pos, cstr2);
		str.insert(pos, cstr2);

		ASSERT_IDENTICAL(nstr, str);

		delete[] cstr;
		delete[] cstr2;
	}
}

TEST(string_insert, nstr_random) {
	for (size_t i = 0; i < 1000; ++i) {
		size_t size = generate_random_size_t(100000);
		char* cstr = generate_random_cstr(size);
		nstl::string nstr{cstr};
		std::string str{cstr};

		if (size == 0) {
			continue;
		}

		size_t pos = generate_random_size_t(size - 1);
		size_t size2 = generate_random_size_t(100000);
		char* cstr2 = generate_random_cstr(size2);
		nstl::string nstr2{cstr2};
		std::string str2{cstr2};

		nstr.insert(pos, nstr2);
		str.insert(pos, str2);

		ASSERT_IDENTICAL(nstr, str);

		delete[] cstr;
		delete[] cstr2;
	}
}
