#include <gtest/gtest.h>
#include <nstl/cstring.h>
#include <cstring>

#include "utils.h"

TEST(strcopy, ascii_characters) {
	const char* str1 =
	    "\x01\x02\x03\x04\x05\x06\x07\x08\t\n\x0b\x0c\r\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d"
	    "\x1e\x1f "
	    "!\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~\x7f";
	char* cpystr1 = new char[nstl::strlen(str1) + 1];
	nstl::strcpy(cpystr1, str1);
	ASSERT_STREQ(cpystr1, str1);

	const char* str2 =
	    "\x01\x02\x03\x04\x05\x06\x07\x08\t\n\x0b\x0c\r\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d"
	    "\x1e\x1f "
	    "!\"#$%&\'()*+,-./"
	    "0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"
	    "\x7f\x01\x02\x03\x04\x05\x06\x07\x08\t\n\x0b\x0c\r\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c"
	    "\x1d\x1e\x1f "
	    "!\"#$%&\'()*+,-./"
	    "0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"
	    "\x7f\x01\x02\x03\x04\x05\x06\x07\x08\t\n\x0b\x0c\r\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c"
	    "\x1d\x1e\x1f "
	    "!\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~\x7f";
	char* cpystr2 = new char[nstl::strlen(str2) + 1];
	nstl::strcpy(cpystr2, str2);
	ASSERT_STREQ(cpystr2, str2);

	const char* str3 = "hello\nworld";
	char* cpystr3 = new char[nstl::strlen(str3) + 1];
	nstl::strcpy(cpystr3, str3);
	ASSERT_STREQ(cpystr3, str3);

	const unsigned int iterations = 100;
	for (int i = 0; i < iterations; ++i) {
		size_t size = generate_random_size_t(100000);
		const char* str = generate_random_cstr(size, 127);
		char* cpystr = new char[nstl::strlen(str) + 1];
		nstl::strcpy(cpystr, str);
		ASSERT_STREQ(cpystr, str);
		delete str;
	}
}

TEST(strcopy, vs_std_strcpy) {
	const unsigned int iterations = 100;
	for (int i = 0; i < iterations; ++i) {
		size_t size = generate_random_size_t(10000000);
		const char* str = generate_random_cstr(size, 255);
		char* cpystr = new char[nstl::strlen(str) + 1];
		char* cpystr_stl = new char[nstl::strlen(str) + 1];
		nstl::strcpy(cpystr, str);
		std::strcpy(cpystr_stl, str);
		ASSERT_STREQ(cpystr, cpystr_stl);
		delete str;
	}
}
