#pragma once

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstring>

#include <nstl/cstring.h>

#define __NSTL_MAX_SS_SIZE__ (sizeof(large) - 1)

//! POTENTIAL BUG: We set_capacity(n) to some even number n. Due to the type_flag, the capacity reported is n + 1. We
//! get segfault.

namespace nstl {

class string {
	/* -------------------------------------------------------------------------- */
	/*                              TYPES AND STRUCTS                             */
	/* -------------------------------------------------------------------------- */
private:
	enum class Type : uint8_t { SMALL = 0, LARGE = 1 };

	struct large {
		char* data;
		size_t __size = 0;
		size_t __capacity : (8 * sizeof(size_t)) - 1 = 0;
		Type type : 1;
	};

	/* -------------------------------------------------------------------------- */
	/*                                   METHODS                                  */
	/* -------------------------------------------------------------------------- */
public:
	// TODO: DO NOT copy passed cstr, instead, steal it with move semantics?

	string();
	string(const char* cstr);

	~string();

	void resize(size_t nsize);
	void reserve(size_t ncap);
	void clear();
	bool empty() const noexcept;
	void shrink_to_fit();

	/* ------------------------ ELEMENT ACCESS OPERATORS ------------------------ */
	char& operator[](size_t pos);
	const char& operator[](size_t pos) const;

	char& at(size_t pos);
	const char& at(size_t pos) const;

	char& back();
	const char& back() const;

	char& front();
	const char& front() const;

	/* -------------------------------- MODIFIERS ------------------------------- */
	void operator+=(char c);
	void operator+=(const char* cstr);
	void operator+=(const nstl::string& nstr);

	void append(char c);
	void append(const char* cstr);
	void append(const nstl::string& nstr);

	void push_back(char c);

	nstl::string& insert(size_t pos, char c);
	nstl::string& insert(size_t pos, const char* cstr);
	nstl::string& insert(size_t pos, const nstl::string& nstr);

	nstl::string& erase();
	nstl::string& erase(size_t pos);
	nstl::string& erase(size_t pos, size_t len);

	nstl::string& replace(size_t pos, size_t len, char c);
	nstl::string& replace(size_t pos, size_t len, const char* cstr);
	nstl::string& replace(size_t pos, size_t len, const nstl::string& nstr);

	const char* c_str() const noexcept;
	const char* data() const noexcept;

	size_t size() const noexcept;
	size_t length() const noexcept;
	size_t capacity() const noexcept;

private:
	bool is_large() const noexcept;
	bool is_small() const noexcept;

	void set_type_flag(Type type) noexcept;
	void set_size(size_t new_size);

	// Sets it to the nearest odd number that is bigger or equal to new_capacity
	void set_capacity(size_t new_capacity);

	/* -------------------------------------------------------------------------- */
	/*                                 ATTRIBUTES                                 */
	/* -------------------------------------------------------------------------- */
private:
	char* data() noexcept;

	union {
		large ls;
		char _data[__NSTL_MAX_SS_SIZE__ + 1];
		// [ 23 bytes + (6 bits of size + 1 bit ??? + 1 bit of small/large : 0 -> short, 1 -> large) ]
	};
};

}  // namespace nstl
