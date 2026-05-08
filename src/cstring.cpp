#include <nstl/cstring.h>
#include <sys/types.h>
#include <cstdint>

namespace nstl {

// I once read the implementation for strlen from glibc: This is inspired on some tricks I think I remember.
// My memory is faulty, as every human's, so it might differ on some things. This is my approach:

/**
If you look at the ASCII table, you'll notice that most of the symbols one would expect to be in a string (a, #, $, g,
Z, D, etc.) have the second-to-last and third-to-last bits set to 1 (for example, A = 01000001 -- it's second to last
bit is set!) thus, we can have a "probabilistic" approach to finding a null terminator: we evaluate sizeof(long)
characters at a time (I'll assume sizeof(long) = 4 from now on to simplify explanation and drawings) and grab, from
each character it's second-to-last bit (MAGIC_HIGH) and it's third-to-last bit (MAGIC_LOW), then, we OR them together:

01000011 00101011 00101011 00000000
                |
                v
00100000 00100000 00100000 ->00000000<- This guy does not have it's second-to-last bit set: may be the null terminator

Notice that, if for a given character the result is a 0, it means both bits were zero, so it is highly likely it is the
null terminator.
*/
size_t strlen(const char* cstr) {
	constexpr unsigned long MAGIC_HIGH = 0x40UL * (~0UL / 0xFFUL);
	constexpr unsigned long MAGIC_LOW = 0x20UL * (~0UL / 0xFFUL);

	size_t len = 0;
	// Advance pointer until long aligned
	while ((uintptr_t)cstr % sizeof(unsigned long) != 0 && *cstr != '\0') {
		++len;
		++cstr;
	}

	if (*cstr == '\0') {
		return len;
	}

	const unsigned long* ptr = reinterpret_cast<const unsigned long*>(cstr);

	while (true) {
		unsigned long probtest = (((*ptr & MAGIC_HIGH) >> 1) | (*ptr & MAGIC_LOW));
		if (probtest == MAGIC_LOW) {
			++ptr;
			len += sizeof(unsigned long);
			continue;
		}

		// See if the null terminator is here
		const char* cptr = reinterpret_cast<const char*>(ptr);
		for (uint i = 0; i < sizeof(unsigned long); ++i) {
			if (cptr[i] == '\0') {
				return len;
			}
			++len;
		}
		++ptr;
	}

	return len;
}

// We copy sizeof(long) characters at a time in a similar fashion to strlen
void strcpy(char* dest, const char* src) {
	constexpr unsigned long MAGIC_HIGH = 0x40UL * (~0UL / 0xFFUL);
	constexpr unsigned long MAGIC_LOW = 0x20UL * (~0UL / 0xFFUL);

	size_t curr_pos = 0;

	// Advance pointer until long aligned
	while ((uintptr_t)src[curr_pos] % sizeof(unsigned long) != 0 && src[curr_pos] != '\0') {
		dest[curr_pos] = src[curr_pos];
		++curr_pos;
	}

	if (src[curr_pos] == '\0') {
		dest[curr_pos] = '\0';
		return;
	}

	unsigned long* destptr = reinterpret_cast<unsigned long*>(dest + curr_pos);
	const unsigned long* srcptr = reinterpret_cast<const unsigned long*>(src + curr_pos);

	while (true) {
		unsigned long probtest = (((*srcptr & MAGIC_HIGH) >> 1) | (*srcptr & MAGIC_LOW));
		if (probtest == MAGIC_LOW) {
			*destptr = *srcptr;
			++srcptr;
			++destptr;
			continue;
		}

		// See if the null terminator is here
		char* cdestptr = reinterpret_cast<char*>(destptr);
		const char* csrcptr = reinterpret_cast<const char*>(srcptr);
		for (uint i = 0; i < sizeof(unsigned long); ++i) {
			cdestptr[i] = csrcptr[i];
			if (csrcptr[i] == '\0') {
				return;
			}
		}
		++srcptr;
		++destptr;
	}
}

void memcpy(void* dest, const void* src, size_t num_bytes) {
	if (num_bytes <= 0) {
		return;
	}

	char* cdest = reinterpret_cast<char*>(dest);
	const char* csrc = reinterpret_cast<const char*>(src);

	size_t bytes_cpd = 0;

	// Advance pointer until long aligned
	while ((uintptr_t)(csrc + bytes_cpd) % sizeof(unsigned long) != 0 && bytes_cpd < num_bytes) {
		cdest[bytes_cpd] = csrc[bytes_cpd];
		++bytes_cpd;
	}

	if (bytes_cpd == num_bytes) {
		return;
	}

	unsigned long* ldest = reinterpret_cast<unsigned long*>(cdest + bytes_cpd);
	const unsigned long* lsrc = reinterpret_cast<const unsigned long*>(csrc + bytes_cpd);

	size_t num_hops = (num_bytes - bytes_cpd) / sizeof(unsigned long);
	for (size_t i = 0; i < num_hops; ++i) {
		ldest[i] = lsrc[i];
		bytes_cpd += sizeof(unsigned long);
	}

	if (bytes_cpd == num_bytes) {
		return;
	}

	// num_bytes was not long aligned, so copy the remaining bytes
	for (size_t i = bytes_cpd; i < num_bytes; ++i) {
		cdest[i] = csrc[i];
	}
}

}  // namespace nstl
