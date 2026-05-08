#include <nstl/exceptions.h>
#include <nstl/string.h>

namespace nstl {

string::string() {
	// Always initialize as a small string
	set_type_flag(Type::SMALL);
	set_size(0);
	_data[0] = '\0';
}

string::string(const char* cstr) {
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

string::~string() {
	if (is_small()) {
		return;
	}

	delete[] ls.data;
}

void string::resize(size_t nsize) {
	if (nsize <= size()) {
		set_size(nsize);
		data()[nsize] = '\0';
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

	data()[nsize] = '\0';
}

void string::reserve(size_t ncap) {
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

void string::clear() {
	set_size(0);
	data()[0] = '\0';
}

bool string::empty() const noexcept {
	return size() == 0;
}

void string::shrink_to_fit() {
	if (is_small()) {
		return;
	}

	size_t curr_size = size();

	if (curr_size <= __NSTL_MAX_SS_SIZE__) {
		// Convert to small string
		nstl::memcpy(_data, ls.data, curr_size + 1);

		set_type_flag(Type::SMALL);
		set_size(curr_size);
		return;
	}

	set_capacity(curr_size);
	char* new_data = new char[capacity() + 1];
	nstl::memcpy(new_data, ls.data, size() + 1);
}

char& string::operator[](size_t pos) {
	return at(pos);
}

const char& string::operator[](size_t pos) const {
	return at(pos);
}

char& string::at(size_t pos) {
	if (pos >= size()) {
		// TODO: Add pos and size() in the error message for improved error detection
		throw excep::out_of_range("position is out of bounds");
	}

	return data()[pos];
}

const char& string::at(size_t pos) const {
	if (pos >= size()) {
		// TODO: Add pos and size() in the error message for improved error detection
		throw excep::out_of_range("position is out of bounds");
	}

	return data()[pos];
}

const char* string::c_str() const noexcept {
	return is_large() ? ls.data : _data;
}

const char* string::data() const noexcept {
	return c_str();
}

char* string::data() noexcept {
	return is_large() ? ls.data : _data;
}

size_t string::size() const noexcept {
	return is_large() ? ls.__size : (23 - (size_t)(_data[__NSTL_MAX_SS_SIZE__] >> 2));
}

size_t string::length() const noexcept {
	return size();
}

size_t string::capacity() const noexcept {
	return is_large() ? ls.__capacity : __NSTL_MAX_SS_SIZE__;
}

/* --------------------------------- PRIVATE -------------------------------- */
bool string::is_large() const noexcept {
	return ls.type == Type::LARGE;
}

bool string::is_small() const noexcept {
	return !is_large();
}

void string::set_type_flag(Type type) noexcept {
	ls.type = type;
}

void string::set_size(size_t new_size) {
	if (is_small()) {
		assert(new_size <= 23);
		_data[__NSTL_MAX_SS_SIZE__] &= 0x3;
		_data[__NSTL_MAX_SS_SIZE__] |= (23 - new_size) << 2;
		return;
	}

	ls.__size = new_size;
};

void string::set_capacity(size_t new_capacity) {
	assert(is_large());
	ls.__capacity = new_capacity;
}

}  // namespace nstl
