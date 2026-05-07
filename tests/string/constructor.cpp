#include <gtest/gtest.h>
#include <cstring>
#include <nstl/string.hpp>

#include "utils.h"

TEST(string_ctr, empty_constructor) {
	nstl::string nstr{};
	ASSERT_EQ(nstr.size(), 0);
	ASSERT_STREQ(nstr.c_str(), "");
}

TEST(string_ctr, cstring_constructor) {
	const char* strs[15];
	nstl::string nstrs[15];

	strs[0] =
	    "Many years later, as he faced the firing squad, Colonel Aureliano Buendia was to remember that distant "
	    "afternoon when his father took him to discover ice.";
	strs[1] = "Aujourd'hui, maman est morte. Ou peut-etre hier, je ne sais pas";
	strs[2] = "I love no thai's sweet and spicy chicken";
	strs[3] =
	    "I looked up at the mass of signs and stars in the night sky and laid myself open for the first time to the "
	    "benign indifference of the world";
	strs[4] = "Encapsulated in their own world, the deaf couldn't help but look at the dancers as if they were maniacs";
	strs[5] = "ifbeautywasacrimeiwouldbeinprisonforthemurderof5peopleindecemberof1987";

	for (int i = 0; i < 6; ++i) {
		nstl::string nstr{strs[i]};
		ASSERT_EQ(nstr.size(), strlen(strs[i]));
		ASSERT_STREQ(nstr.c_str(), strs[i]);
	}
}

TEST(string_ctr, vs_std_string) {
	const unsigned int iterations = 100;
	for (int i = 0; i < iterations; ++i) {
		size_t size = generate_random_size_t(10000000);
		const char* cstr = generate_random_cstr(size, 255);
		std::string str{cstr};
		nstl::string nstr{cstr};

		ASSERT_EQ(nstr.size(), str.size());
		ASSERT_STREQ(nstr.c_str(), str.c_str());

		delete cstr;
	}
}
