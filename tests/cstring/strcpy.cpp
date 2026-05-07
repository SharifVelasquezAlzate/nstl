#include <gtest/gtest.h>
#include <nstl/cstring.h>
#include <cstring>

#include "utils.h"

TEST(strcpy, basic_test) {
	char* strs[15];
	char* cpystrs[15];

	for (int i = 0; i < 15; ++i) {
		strs[i] = new char[500];
		cpystrs[i] = new char[500];
	}

	strcpy(strs[0],
	       "Many years later, as he faced the firing squad, Colonel Aureliano Buendia was to remember that distant "
	       "afternoon when his father took him to discover ice.");
	nstl::strcpy(cpystrs[0], strs[0]);
	ASSERT_STREQ(cpystrs[0], strs[0]);

	strcpy(strs[1], "Aujourd'hui, maman est morte. Ou peut-etre hier, je ne sais pas");
	nstl::strcpy(cpystrs[1], strs[1]);
	ASSERT_STREQ(cpystrs[1], strs[1]);

	strcpy(strs[2], "I love no thai's sweet and spicy chicken");
	nstl::strcpy(cpystrs[2], strs[2]);
	ASSERT_STREQ(cpystrs[2], strs[2]);

	strcpy(strs[3],
	       "I looked up at the mass of signs and stars in the night sky and laid myself open for the first time to the "
	       "benign indifference of the world");
	nstl::strcpy(cpystrs[3], strs[3]);
	ASSERT_STREQ(cpystrs[3], strs[3]);

	strcpy(strs[4],
	       "Encapsulated in their own world, the deaf couldn't help but look at the dancers as if they were maniacs");
	nstl::strcpy(cpystrs[4], strs[4]);
	ASSERT_STREQ(cpystrs[4], strs[4]);

	strcpy(strs[5], "ifbeautywasacrimeiwouldbeinprisonforthemurderof5peopleindecemberof1993");
	nstl::strcpy(cpystrs[5], strs[5]);
	ASSERT_STREQ(cpystrs[5], strs[5]);

	for (int i = 0; i < 15; ++i) {
		delete strs[i];
		delete cpystrs[i];
	}
}

TEST(strcpy, ascii_characters) {
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

TEST(strcpy, vs_std_strcpy) {
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
