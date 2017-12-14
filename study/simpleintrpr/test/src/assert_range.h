#ifndef __ASSERT_RANGE_H_INCLUDED__
#define __ASSERT_RANGE_H_INCLUDED__

#include <iostream>

namespace AssertRange {

template<class T, class ActualRange>
static void AreEqual(std::initializer_list<T> expect, const ActualRange &actual) {
	auto actualIter = std::begin(actual);
	auto expectIter = std::begin(expect);


	auto expectDist = std::distance(expectIter, std::end(expect));
	auto actualDist = std::distance(actualIter, std::end(actual));

	if (expectDist != actualDist)
		std::cerr << L"Size differs." << std::endl;
	EXPECT_EQ(expectDist, actualDist);

	for (; expectIter != std::end(expect) && actualIter != std::end(actual);
			++expectIter, ++actualIter) {

		if (*expectIter != *actualIter) {
			std::cout << "some_error" << std::endl;

			auto message = L"Mismatch in position " +
				std::to_wstring(std::distance(std::begin(expect), expectIter));

			std::cerr << message.c_str() << std::endl;
		}

		EXPECT_EQ(*expectIter, *actualIter);
	}
}

} // namespace AssertRange

#endif /*__ASSERT_RANGE_H_INCLUDED__*/
