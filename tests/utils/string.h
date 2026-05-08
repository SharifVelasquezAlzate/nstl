#include <string>

#include <nstl/string.h>

extern void ASSERT_IDENTICAL(const nstl::string& nstr, const std::string& str);

class nstrverf {
public:
	nstrverf();
	nstrverf(const char* cstr);

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
	void operator+=(const nstl::string& other);

	void append(char c);
	void append(const char* cstr);
	void append(const nstl::string& other);

	void push_back(char c);

	void insert(size_t pos, char c);
	void insert(size_t pos, const char* cstr);
	void insert(size_t pos, const nstl::string& nstr);

	const char* c_str() const noexcept;
	const char* data() const noexcept;

	size_t size() const noexcept;
	size_t length() const noexcept;
	size_t capacity() const noexcept;

private:
	nstl::string nstr;
	std::string str;
};
