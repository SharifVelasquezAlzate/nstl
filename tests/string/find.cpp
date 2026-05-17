#include <gtest/gtest.h>
#include <cstddef>
#include <cstring>
#include <string>

#include <nstl/exceptions.h>
#include <nstl/string.h>

#include "utils/general.h"
#include "utils/string.h"

TEST(string_find, basic) {
    nstl::string nstr = "Hello, world!";

    nstl::string s1 = "Hello";
    ASSERT_EQ(nstr.find(s1), 0);

    nstl::string s2 = ",";
    ASSERT_EQ(nstr.find(s2), 5);

    nstl::string s3 = "world";
    ASSERT_EQ(nstr.find(s3), 7);

    nstl::string s4 = "!";
    ASSERT_EQ(nstr.find(s4), 12);

    nstl::string s5 = "Hello, world!";
    ASSERT_EQ(nstr.find(s5), 0);

    ASSERT_EQ(nstr.find(nstr), 0);

    nstl::string s6 = "l";
    ASSERT_EQ(nstr.find(s6), 2);
}
