#pragma once

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstring>

#include <nstl/cstring.h>
#include <nstl/utility.hpp>

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
		char* data = nullptr;
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
	string(const nstl::string& other);
	string(nstl::string&& other);

	~string();

	nstl::string& operator=(const char* cstr);
	nstl::string& operator=(const nstl::string& other);
	nstl::string& operator=(nstl::string&& other);

	/* ------------------------ ELEMENT ACCESS OPERATORS ------------------------ */
	char& at(size_t pos);
	const char& at(size_t pos) const;

	char& operator[](size_t pos);
	const char& operator[](size_t pos) const;

	char& front();
	const char& front() const;

	char& back();
	const char& back() const;

	const char* data() const noexcept;
	const char* c_str() const noexcept;

	/* -------------------------------- CAPACITY -------------------------------- */
	bool empty() const noexcept;
	size_t size() const noexcept;
	size_t length() const noexcept;
	void reserve(size_t ncap);
	size_t capacity() const noexcept;
	void shrink_to_fit();

	/* -------------------------------- MODIFIERS ------------------------------- */
	void clear();

	nstl::string& insert(size_t pos, char c);
	nstl::string& insert(size_t pos, const char* cstr);
	nstl::string& insert(size_t pos, const nstl::string& nstr);

	nstl::string& erase(size_t pos = 0);
	nstl::string& erase(size_t pos, size_t len);

	void push_back(char c);
	void pop_back();

	void append(char c);
	void append(const char* cstr);
	void append(const nstl::string& nstr);

	void operator+=(char c);
	void operator+=(const char* cstr);
	void operator+=(const nstl::string& nstr);

	nstl::string& replace(size_t pos, size_t len, char c);
	nstl::string& replace(size_t pos, size_t len, const char* cstr);
	nstl::string& replace(size_t pos, size_t len, const nstl::string& nstr);

	constexpr size_t copy(char* dest, size_t count, size_t pos = 0) const;

	void resize(size_t nsize);

	void swap(nstl::string& other);

	/* --------------------------------- SEARCH --------------------------------- */
	constexpr size_t find(const nstl::string& nstr, size_t pos = 0) const;
	constexpr size_t find(const char* s, size_t pos, size_t count) const;
	constexpr size_t find(const char* s, size_t pos = 0) const;
	constexpr size_t find(char ch, size_t pos = 0) const;

	constexpr size_t rfind(const nstl::string& nstr, size_t pos = 0) const;
	constexpr size_t rfind(const char* s, size_t pos, size_t count) const;
	constexpr size_t rfind(const char* s, size_t pos = 0) const;
	constexpr size_t rfind(char ch, size_t pos = 0) const;

	constexpr size_t find_first_of(const nstl::string& nstr, size_t pos = 0) const;
	constexpr size_t find_first_of(const char* s, size_t pos, size_t count) const;
	constexpr size_t find_first_of(const char* s, size_t pos = 0) const;
	constexpr size_t find_first_of(char ch, size_t pos = 0) const;

	constexpr size_t find_first_not_of(const nstl::string& nstr, size_t pos = 0) const;
	constexpr size_t find_first_not_of(const char* s, size_t pos, size_t count) const;
	constexpr size_t find_first_not_of(const char* s, size_t pos = 0) const;
	constexpr size_t find_first_not_of(char ch, size_t pos = 0) const;

	constexpr size_t find_last_of(const nstl::string& nstr, size_t pos = 0) const;
	constexpr size_t find_last_of(const char* s, size_t pos, size_t count) const;
	constexpr size_t find_last_of(const char* s, size_t pos = 0) const;
	constexpr size_t find_last_of(char ch, size_t pos = 0) const;

	constexpr size_t find_last_not_of(const nstl::string& nstr, size_t pos = 0) const;
	constexpr size_t find_last_not_of(const char* s, size_t pos, size_t count) const;
	constexpr size_t find_last_not_of(const char* s, size_t pos = 0) const;
	constexpr size_t find_last_not_of(char ch, size_t pos = 0) const;

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
