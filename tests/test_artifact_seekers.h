#ifndef TEST_ARTIFACT_SEEKERS_H
#define TEST_ARTIFACT_SEEKERS_H

#include "tests/test_macros.h"
#include <scene/main/node.h>

#include "../src/shared/helpers/basket.hpp"

namespace TestArtskrBasketClass {

TEST_CASE("[Basket Class] General") {
	//Initial setup
    Node* test_node = memnew(Node);
	Basket test_basket(test_node);

	REQUIRE(test_basket.get() == test_node);
	//Node deleted elsewhere - Basket should store nullptr at this point
	memdelete(test_node);

	REQUIRE(test_basket.get() == nullptr);
}

} // namespace TestString

#endif // TEST_ARTIFACT_SEEKERS_H