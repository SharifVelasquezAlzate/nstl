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

private:
	/* -------------------------------------------------------------------------- */
	/*                                   METHODS                                  */
	/* -------------------------------------------------------------------------- */
public:
	// TODO: DO NOT copy passed cstr, instead, steal it with move semantics?

	string() {
		// Always initialize as a small string
		set_type_flag(Type::SMALL);
		set_size(0);
		_data[0] = '\0';
	}

	string(const char* cstr) {
		size_t csize = nstl::strlen(cstr);
		Type type = (csize > __NSTL_MAX_SS_SIZE__) ? Type::LARGE : Type::SMALL;

		set_type_flag(type);
		set_size(csize);

		if (type == Type::SMALL) {
			nstl::strcpy(_data, cstr);
			return;
		}

		// Defer work: only allocate more space when something is actually appended to this string
		set_capacity(csize);
		ls.data = new char[capacity() + 1];
		nstl::strcpy(ls.data, cstr);
	}

	~string() {
		if (is_small()) {
			return;
		}

		delete[] ls.data;
	}

	void resize(size_t nsize) {
		if (nsize <= size()) {
			set_size(nsize);
			char* data = is_large() ? ls.data : _data;
			data[nsize] = '\0';
			return;
		}

		size_t old_size = size();

		if (is_small() && nsize > capacity()) {
			// Convert to a large string
			char old_data[__NSTL_MAX_SS_SIZE__ + 1];
			nstl::memcpy(old_data, _data, old_size + 1);

			set_type_flag(Type::LARGE);
			set_capacity(nsize);
			char* new_data = new char[capacity() + 1];
			nstl::memcpy(new_data, old_data, old_size + 1);

			ls.data = new_data;
		}

		if (is_large() && nsize > capacity()) {
			set_capacity(nsize);
			char* new_data = new char[capacity() + 1];
			nstl::memcpy(new_data, ls.data, old_size + 1);

			delete[] ls.data;
			ls.data = new_data;
		}

		set_size(nsize);

		char* data = is_large() ? ls.data : _data;
		data[nsize] = '\0';
	}

	void reserve(size_t ncap) {
		if (ncap <= capacity()) {
			return;
		}

		size_t curr_size = size();

		if (is_small()) {
			// Convert to large string
			char old_data[__NSTL_MAX_SS_SIZE__ + 1];
			nstl::memcpy(old_data, _data, curr_size + 1);

			set_type_flag(Type::LARGE);
			set_capacity(ncap);
			set_size(curr_size);
			char* new_data = new char[capacity() + 1];
			nstl::memcpy(new_data, old_data, curr_size + 1);

			ls.data = new_data;
			return;
		}

		set_capacity(ncap);
		char* new_data = new char[capacity() + 1];
		nstl::memcpy(new_data, ls.data, curr_size + 1);

		delete[] ls.data;
		ls.data = new_data;
	}

	void clear() {
		set_size(0);
		char* data = is_large() ? ls.data : _data;
		data[0] = '\0';
	}

	const char* c_str() const noexcept {
		return is_large() ? ls.data : _data;
	}

	const char* data() const noexcept {
		return c_str();
	}

	size_t size() const noexcept {
		return is_large() ? ls.__size : (23 - (size_t)(_data[__NSTL_MAX_SS_SIZE__] >> 2));
	}

	size_t length() const noexcept {
		return size();
	}

	size_t capacity() const noexcept {
		return is_large() ? ls.__capacity : __NSTL_MAX_SS_SIZE__;
	}

private:
	bool is_large() const noexcept {
		return ls.type == Type::LARGE;
	}

	bool is_small() const noexcept {
		return !is_large();
	}

	void set_type_flag(Type type) noexcept {
		ls.type = type;
	}

	void set_size(size_t new_size) {
		if (is_small()) {
			assert(new_size <= 23);
			_data[__NSTL_MAX_SS_SIZE__] &= 0x3;
			_data[__NSTL_MAX_SS_SIZE__] |= (23 - new_size) << 2;
			return;
		}

		ls.__size = new_size;
	};

	// Sets it to the nearest odd number that is bigger or equal to new_capacity
	void set_capacity(size_t new_capacity) {
		assert(is_large());
		ls.__capacity = new_capacity;
	}

	/* -------------------------------------------------------------------------- */
	/*                                 ATTRIBUTES                                 */
	/* -------------------------------------------------------------------------- */
private:
	union {
		large ls;
		char _data[__NSTL_MAX_SS_SIZE__ + 1];
		// [ 23 bytes + (6 bits of size + 1 bit ??? + 1 bit of small/large : 0 -> short, 1 -> large) ]
	};
};

}  // namespace nstl
