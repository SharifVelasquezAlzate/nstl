#pragma once

#include <cstddef>

namespace nstl {

extern size_t strlen(const char*);
extern void strcpy(char* dest, const char* src);
extern void memcpy(void* dest, const void* src, size_t num_bytes);

};  // namespace nstl
