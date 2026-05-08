#include <gtest/gtest.h>
#include <cstddef>
#include <cstring>
#include <string>

#include <nstl/exceptions.h>
#include <nstl/string.h>

#include "utils/general.h"

TEST(string_append, basic_char) {
	nstl::string nstr{"Hello"};
	nstr += 'a';
	std::string expected = "Helloa";
	for (int i = 0; i < nstr.size(); ++i) {
		ASSERT_EQ(nstr[i], expected[i]);
	}

	nstr += '\0';
	for (int i = 0; i < nstr.size(); ++i) {
		ASSERT_EQ(nstr[i], expected[i]);
	}
	ASSERT_EQ(nstr.back(), '\0');
	ASSERT_EQ(nstr.size(), 7);
}

TEST(string_append, cstring) {
	nstl::string nstr{"Pomme"};
	nstr += " - Grandiose";
	char expected[71] = "Pomme - Grandiose";
	ASSERT_EQ(nstr.size(), strlen(expected));
	ASSERT_STREQ(nstr.c_str(), expected);

	nstr += ": it's a great song";
	strcpy(expected + strlen(expected), ": it's a great song");
	ASSERT_EQ(nstr.size(), strlen(expected));
	ASSERT_STREQ(nstr.c_str(), expected);

	nstr += ", you know?... Nah, you surely do!";
	strcpy(expected + strlen(expected), ", you know?... Nah, you surely do!");
	ASSERT_EQ(nstr.size(), strlen(expected));
	ASSERT_STREQ(nstr.c_str(), expected);
}
