#include <gtest/gtest.h>
#include <nstl/cstring.h>
#include <cstring>

#include "utils.h"

TEST(strlen, basic_test) {
	const char* strs[15];

	strs[0] =
	    "Many years later, as he faced the firing squad, Colonel Aureliano Buendia was to remember that distant "
	    "afternoon when his father took him to discover ice.";
	ASSERT_EQ(nstl::strlen(strs[0]), 154);

	strs[1] = "Aujourd'hui, maman est morte. Ou peut-etre hier, je ne sais pas";
	ASSERT_EQ(nstl::strlen(strs[1]), 63);

	strs[2] = "I love no thai's sweet and spicy chicken";
	ASSERT_EQ(nstl::strlen(strs[2]), 40);

	strs[3] =
	    "I looked up at the mass of signs and stars in the night sky and laid myself open for the first time to the "
	    "benign indifference of the world";
	ASSERT_EQ(nstl::strlen(strs[3]), 139);

	strs[4] = "Encapsulated in their own world, the deaf couldn't help but look at the dancers as if they were maniacs";
	ASSERT_EQ(nstl::strlen(strs[4]), 103);

	strs[5] = "ifbeautywasacrimeiwouldbeinprisonforthemurderof5peopleindecemberof1987";
	ASSERT_EQ(nstl::strlen(strs[5]), 70);
}

TEST(strlen, ascii_characters) {
	const char* str1 =
	    "\x01\x02\x03\x04\x05\x06\x07\x08\t\n\x0b\x0c\r\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d"
	    "\x1e\x1f "
	    "!\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~\x7f";
	ASSERT_EQ(nstl::strlen(str1), 127);

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
	ASSERT_EQ(nstl::strlen(str2), 3 * 127);

	const char* str3 = "hello\nworld";
	ASSERT_EQ(nstl::strlen(str3), 11);

	const unsigned int iterations = 100;
	for (int i = 0; i < iterations; ++i) {
		size_t size = generate_random_size_t(100000);
		const char* str = generate_random_cstr(size, 127);
		ASSERT_EQ(nstl::strlen(str), size) << "str[actual] = " << str[size] << " " << (str[size] == '\0') << " | "
		                                   << str[nstl::strlen(str)] << " " << (str[nstl::strlen(str)] == '\0');
		delete str;
	}
}

TEST(strlen, vs_std_strlen) {
	const unsigned int iterations = 100;
	for (int i = 0; i < iterations; ++i) {
		size_t size = generate_random_size_t(10000000);
		const char* str = generate_random_cstr(size, 255);
		ASSERT_EQ(nstl::strlen(str), strlen(str));
		delete str;
	}
}
