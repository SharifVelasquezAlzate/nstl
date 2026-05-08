#include <gtest/gtest.h>
#include <nstl/cstring.h>
#include <cstring>

#include <utils/general.h>

TEST(memcpy, empty_copy) {
	{
		const char* src = "Hello";
		char dest[21] = "twentycharactershere";
		nstl::memcpy(dest, src, 0);

		ASSERT_STREQ(src, "Hello");
		ASSERT_STREQ(dest, "twentycharactershere");
	}

	{
		const char* src = "";
		char dest[1] = "";
		nstl::memcpy(dest, src, 0);

		ASSERT_EQ(*src, '\0');
		ASSERT_EQ(*dest, '\0');
	}
}

TEST(memcpy, buffers_with_null_terminator) {
	{
		for (size_t size = 0; size < 1000; ++size) {
			char* src = new char[size];
			char* dest = new char[size];

			for (int i = 0; i < size; ++i) {
				src[i] = '\0';
			}

			nstl::memcpy(dest, src, size);

			for (int i = 0; i < size; ++i) {
				ASSERT_EQ(dest[i], src[i]) << size << " " << i;
			}

			delete[] src;
			delete[] dest;
		}
	}

	{
		using namespace std::string_literals;
		std::string ssrc =
		    "Hello!\0I am your friend, and want to catch up\0Please don't mind the null terminators\0- your friend"s;
		char* src = new char[ssrc.size()];
		for (size_t i = 0; i < ssrc.size(); ++i) {
			src[i] = ssrc[i];
		}

		char* dest = new char[ssrc.size()];

		nstl::memcpy(dest, src, ssrc.size());

		for (size_t i = 0; i < ssrc.size(); ++i) {
			ASSERT_EQ(dest[i], src[i]);
		}

		delete[] src;
		delete[] dest;
	}

	// Randomized
	{
		for (size_t iter = 0; iter < 1000; ++iter) {
			size_t size = generate_random_size_t(1000);
			char* src = generate_random_cstr(size);
			// Add null terminators
			size_t start = generate_random_size_t((size / 2) - 1);
			for (size_t i = start; i < size / 2; ++i) {
				src[2 * i] = '\0';
			}

			char* dest = new char[size + 1];
			nstl::memcpy(dest, src, size + 1);

			for (size_t i = 0; i < size + 1; ++i) {
				ASSERT_EQ(dest[i], src[i]);
			}

			delete[] src;
			delete[] dest;
		}
	}
}

TEST(memcpy, structs) {
	struct Message {
		char subject[30];
		char destinatary[255];
		size_t delay_secs;
		char msg[1'048'577];
	};

	Message msg = {"Hello from me", "adam", 10,
	               "Hello dear friend,\nI just wanted to write you this message to let you know that I am testing my "
	               "own version of memcpy!"};
	Message msgcpy;

	nstl::memcpy(&msgcpy, &msg, sizeof(Message));

	ASSERT_EQ(memcmp(&msg, &msgcpy, sizeof(Message)), 0);
}
