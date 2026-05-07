#include <cassert>
#include <cstddef>

#include <nstl/cstring.h>

#define __NSTL_MAX_SS_SIZE__ (sizeof(large) - 1)

namespace nstl {

class string {
	/* -------------------------------------------------------------------------- */
	/*                              TYPES AND STRUCTS                             */
	/* -------------------------------------------------------------------------- */
   private:
	enum class Type { SMALL, LARGE };

	struct large {
		char* data;
		size_t size = 0;
		size_t capacity = 0;
	};

   private:
	/* -------------------------------------------------------------------------- */
	/*                                   METHODS                                  */
	/* -------------------------------------------------------------------------- */
   public:
	string() {
		// Always initialize as a small string
		set_type_flag(Type::SMALL);
		set_size(0);
	}

	string(const char* cstr) {
		size_t csize = nstl::strlen(cstr);
		Type type = (csize > 23) ? Type::LARGE : Type::SMALL;

		set_type_flag(type);
		set_size(csize);

		if (type == Type::SMALL) {
			return;
		}

		// Defer work: only allocate more space when something is actually appended to this string
		ls.data = new char[csize + 1];
		nstl::strcpy(ls.data, cstr);
	}

	~string() {
		if (is_small())
			return;

		delete ls.data;
	}

	const char* c_str() const noexcept {
		return (is_large()) ? ls.data : _data;
	}

	const char* data() const noexcept {
		return c_str();
	}

	size_t capacity() const noexcept {
		return is_large() ? ls.capacity : __NSTL_MAX_SS_SIZE__;
	}

	size_t size() const noexcept {
		return is_large() ? ls.size : (23 - (size_t)(_data[sizeof(large) - 1] >> 2));
	}

   private:
	bool is_large() const noexcept {
		return _data[sizeof(large) - 1] & 1;
	}

	bool is_small() const noexcept {
		return !is_large();
	}

	void set_type_flag(Type type) noexcept {
		char type_bit = (type == Type::LARGE) ? 1 : 0;
		_data[sizeof(large) - 1] &= 0xFE;
		_data[sizeof(large) - 1] |= type_bit;
	}

	void set_size(size_t new_size) {
		if (is_small()) {
			assert(new_size <= 23);
			_data[sizeof(large) - 1] &= 0x3;
			_data[sizeof(large) - 1] |= (23 - new_size) << 2;
			return;
		}

		ls.size = new_size;
	};

	/* -------------------------------------------------------------------------- */
	/*                                 ATTRIBUTES                                 */
	/* -------------------------------------------------------------------------- */
   private:
	union {
		large ls;
		char _data[sizeof(large)];
		// [ 23 bytes + (6 bits of size + 1 bit ??? + 1 bit of small/large : 0 -> short, 1 -> large) ]
	};
};

}  // namespace nstl
