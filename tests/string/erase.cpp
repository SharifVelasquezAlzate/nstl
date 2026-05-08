#include <gtest/gtest.h>
#include <cstddef>
#include <cstring>
#include <string>

#include <nstl/exceptions.h>
#include <nstl/string.h>

#include "utils/general.h"
#include "utils/string.h"

TEST(string_erase, nothing) {
	nstl::string nstr{"Hello"};
	std::string str{"Hello"};

	nstr.erase(0, 0);

	ASSERT_IDENTICAL(nstr, str);
}

TEST(string_erase, random) {
	for (int i = 0; i < 10000; ++i) {
		size_t size = 1 + generate_random_size_t(1000);
		char* cstr = generate_random_cstr(size);

		nstl::string nstr{cstr};
		std::string str{cstr};

		size_t pos = generate_random_size_t(size - 1);
		size_t len = generate_random_size_t(size);

		nstr.erase(pos, len);
		str.erase(pos, len);

		ASSERT_IDENTICAL(nstr, str);

		delete[] cstr;
	}
}
