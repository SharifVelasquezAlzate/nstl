#include <gtest/gtest.h>

#include <nstl/string.h>

#include <utils/general.h>
#include <utils/string.h>

TEST(string_assignment, random_cstr) {
	for (int iter = 0; iter < 1000; ++iter) {
		size_t size = generate_random_size_t(10000);
		char* cstr = generate_random_cstr(size);

		nstl::string nstr{cstr};
		std::string str{cstr};

		size_t size2 = generate_random_size_t(10000);
		char* cstr2 = generate_random_cstr(size2);

		nstl::string nstrcpy = cstr2;
		std::string strcpy = cstr2;

		ASSERT_IDENTICAL(nstrcpy, strcpy);
	}
}

TEST(string_assignment, random_nstr_copy) {
	for (int iter = 0; iter < 1000; ++iter) {
		size_t size = generate_random_size_t(10000);
		char* cstr = generate_random_cstr(size);

		nstl::string nstr{cstr};
		std::string str{cstr};

		nstl::string nstrcpy = nstr;
		std::string strcpy = str;

		ASSERT_IDENTICAL(nstrcpy, strcpy);
	}
}

TEST(string_assignment, random_nstr_move) {
	for (int iter = 0; iter < 1000; ++iter) {
		size_t size = generate_random_size_t(10000);
		char* cstr = generate_random_cstr(size);

		nstl::string nstr{cstr};
		std::string str{cstr};

		nstl::string nstrcpy = std::move(nstr);
		std::string strcpy = std::move(str);

		ASSERT_IDENTICAL(nstrcpy, strcpy);
	}
}
