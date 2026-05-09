#include <nstl/type_traits.h>

namespace nstl {

template <typename T>
extern constexpr typename nstl::remove_reference<T>::type&& move(T& x) noexcept {
	return static_cast<typename nstl::remove_reference<T>::type&&>(x);
}

template <typename T>
extern constexpr typename nstl::remove_reference<T>::type&& move(T&& x) noexcept {
	return static_cast<typename nstl::remove_reference<T>::type&&>(x);
}

}  // namespace nstl
