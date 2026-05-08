#pragma once

#include <nstl/string.h>

namespace nstl::excep {

class exception {
public:
	exception() noexcept {};
	virtual ~exception() {};

	virtual const char* what() const noexcept = 0;
};

class out_of_range : public exception {
public:
	out_of_range(const char* const what_p) : exception() {
		what_msg = what_p;
	}

	out_of_range(const nstl::string& what_p) : exception() {
		what_msg = what_p.c_str();
	}

	const char* what() const noexcept override {
		return what_msg;
	}

private:
	const char* what_msg;
};

}  // namespace nstl::excep