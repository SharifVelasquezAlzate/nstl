#include <gtest/gtest.h>
#include <cstddef>
#include <cstring>
#include <string>
#include <iostream>

#include <nstl/exceptions.h>
#include <nstl/string.h>
#include <nstl/algorithm.hpp>

#include "utils/general.h"
#include "utils/string.h"

TEST(algorithm_zalgsuff, basic) {
    nstl::string nstr = "baayaaxbaa";

    for (size_t i = 0; i < nstr.size(); ++i) {
        std::cout << nstr[i] << " ";
    }
    std::cout << std::endl;

    size_t* shifts;
    nstl::algo::shifts(nstr, shifts);

    for (size_t i = 0; i < nstr.size(); ++i) {
        std::cout << shifts[i] << " ";
    }
    std::cout << std::endl;
}

TEST(algorithm_zalgsuff, basic2) {
    nstl::string nstr = "aaaaaaaaaaa";
    
    for (size_t i = 0; i < nstr.size(); ++i) {
        std::cout << nstr[i] << " ";
    }
    std::cout << std::endl;

    size_t* shifts;
    nstl::algo::shifts(nstr, shifts);

    for (size_t i = 0; i < nstr.size(); ++i) {
        std::cout << shifts[i] << " ";
    }
    std::cout << std::endl;
}

TEST(algorithm_zalgsuff, basic3) {
    nstl::string nstr = "ratatatuiintaratua";
    
    for (size_t i = 0; i < nstr.size(); ++i) {
        std::cout << nstr[i] << " ";
    }
    std::cout << std::endl;

    size_t* shifts;
    nstl::algo::shifts(nstr, shifts);

    for (size_t i = 0; i < nstr.size(); ++i) {
        std::cout << shifts[i] << " ";
    }
    std::cout << std::endl;
}
