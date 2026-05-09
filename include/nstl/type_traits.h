namespace nstl {

template <typename T>
struct remove_reference {
	typedef T type;
};

template <typename T>
struct remove_reference<T&> {
	typedef T type;
};

template <typename T>
struct remove_reference<T&&> {
	typedef T type;
};

}  // namespace nstl
