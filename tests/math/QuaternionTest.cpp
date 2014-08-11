#include <catch.hpp>
#include <math/Quaternion.h>


/*
===============================================================================

	Quaternion unit testing

===============================================================================
*/

TEST_CASE("Quaternion * Quaternion", "[Quaternion]") {

	Quaternion q1(0,0,0,1);
	Quaternion q2(0,0,0.3825,0.923);

	Quaternion res = q1 * q2;

	REQUIRE(res.x == 0);
	REQUIRE(res.y == 0);
	REQUIRE(0.1 > std::abs(res.z-0.3825));
	REQUIRE(0.1 > std::abs(res.w-0.923));

}

