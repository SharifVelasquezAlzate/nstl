#include <nstl/exceptions.h>
#include <nstl/string.h>
#include <sys/param.h>

static double GROWTH_FACTOR = 2;

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

/* ------------------------ ELEMENT ACCESS OPERATORS ------------------------ */
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

char& string::back() {
	if (size() == 0) {
		// TODO: Add pos and size() in the error message for improved error detection
		throw excep::out_of_range("position is out of bounds");
	}
	return at(size() - 1);
}

const char& string::back() const {
	if (size() == 0) {
		// TODO: Add pos and size() in the error message for improved error detection
		throw excep::out_of_range("position is out of bounds");
	}
	return at(size() - 1);
}

char& string::front() {
	return at(0);
}

const char& string::front() const {
	return at(0);
}

/* -------------------------------- MODIFIERS ------------------------------- */
void string::operator+=(char c) {
	append(c);
}

void string::operator+=(const char* cstr) {
	append(cstr);
}

void string::operator+=(const nstl::string& other) {
	append(other);
}

void string::append(char c) {
	if (size() + 1 > capacity()) {
		reserve(GROWTH_FACTOR * capacity());
	}

	data()[size()] = c;
	data()[size() + 1] = '\0';
	set_size(size() + 1);
}

void string::append(const char* cstr) {
	size_t csize = nstl::strlen(cstr);

	if (size() + csize > capacity()) {
		size_t ncap = (size() + csize <= GROWTH_FACTOR * capacity()) ? GROWTH_FACTOR * capacity() : size() + csize;
		reserve(ncap);
	}

	nstl::strcpy(data() + size(), cstr);
	set_size(size() + csize);
}

void string::append(const nstl::string& other) {
	size_t osize = other.size();

	if (size() + osize > capacity()) {
		size_t ncap = (size() + osize <= GROWTH_FACTOR * capacity()) ? GROWTH_FACTOR * capacity() : size() + osize;
		reserve(ncap);
	}

	nstl::memcpy(data() + size(), other.data(), osize);
	set_size(size() + osize);
}

void string::push_back(char c) {
	append(c);
}

nstl::string& string::insert(size_t pos, char c) {
	size_t isize = 1;

	if (size() + isize > capacity()) {
		// TODO: Optimization: perform the necessary "copy to the back" as we perform the reserve
		size_t ncap = (size() + isize <= GROWTH_FACTOR * capacity()) ? GROWTH_FACTOR * capacity() : size() + isize;
		reserve(ncap);
	}

	// TODO: Could be more efficient with long method?
	// Copy to the back all the things that will be shifted
	for (int i = size() + isize; i >= pos; --i) {
		data()[i] = data()[i - isize];
	}

	data()[pos] = c;
	set_size(size() + isize);

	return *this;
}

nstl::string& string::insert(size_t pos, const char* cstr) {
	size_t isize = nstl::strlen(cstr);

	if (size() + isize > capacity()) {
		// TODO: Optimization: perform the necessary "copy to the back" as we perform the reserve
		size_t ncap = (size() + isize <= GROWTH_FACTOR * capacity()) ? GROWTH_FACTOR * capacity() : size() + isize;
		reserve(ncap);
	}

	// TODO: Could be more efficient with long method?
	// Copy to the back all the things that will be shifted
	for (int i = size() + isize; i >= pos; --i) {
		data()[i] = data()[i - isize];
	}

	nstl::memcpy(data() + pos, cstr, isize);
	set_size(size() + isize);

	return *this;
}

nstl::string& string::insert(size_t pos, const nstl::string& nstr) {
	size_t isize = nstr.size();

	if (size() + isize > capacity()) {
		// TODO: Optimization: perform the necessary "copy to the back" as we perform the reserve
		size_t ncap = (size() + isize <= GROWTH_FACTOR * capacity()) ? GROWTH_FACTOR * capacity() : size() + isize;
		reserve(ncap);
	}

	// TODO: Could be more efficient with long method?
	// Copy to the back all the things that will be shifted
	for (int i = size() + isize; i >= pos; --i) {
		data()[i] = data()[i - isize];
	}

	nstl::memcpy(data() + pos, nstr.data(), isize);
	set_size(size() + isize);

	return *this;
}

nstl::string& string::erase() {
	clear();
	return *this;
}

nstl::string& string::erase(size_t pos) {
	if (pos >= size()) {
		throw excep::out_of_range("position is out of bounds");
	}
	return erase(pos, size() - pos);
}

nstl::string& string::erase(size_t pos, size_t len) {
	if (pos >= size()) {
		throw excep::out_of_range("position is out of bounds");
	}

	len = MIN(len, size() - pos);

	for (size_t i = pos + len; i <= size(); ++i) {
		data()[i - len] = data()[i];
	}
	set_size(size() - len);

	return *this;
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
