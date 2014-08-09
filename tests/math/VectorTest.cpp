#include <catch.hpp>
#include <math/Vector.h>
#include <cstring>


/*
===============================================================================

	Vector unit testing

===============================================================================
*/



/*
===============================================================================

	Vec2 testing

===============================================================================
*/

TEST_CASE("Vec2 initialisation", "[Vector][Vec2]") {
	Vec2 vec1(2,3);

	REQUIRE(vec1.data[0] == 2);
	REQUIRE(vec1.data[1] == 3);

	Vec2 vec2(5);

	REQUIRE(vec2.data[0] == 5);
	REQUIRE(vec2.data[1] == 5);
}

TEST_CASE("Vec2 set", "[Vector][Vec2]") {
	Vec2 vec(4,-1);

	REQUIRE(vec.x == 4);
	REQUIRE(vec.y == -1);

	vec.Set(5);

	REQUIRE(vec.x == 5);
	REQUIRE(vec.y == 5);

	vec.Set(2,-6);

	REQUIRE(vec.x == 2);
	REQUIRE(vec.y == -6);

}

TEST_CASE("Vec2 zero", "[Vector][Vec2]") {
	Vec2 vec(-6,1);

	vec.Zero();
	
	REQUIRE(vec.x == 0);
	REQUIRE(vec.y == 0);

}

TEST_CASE("Vec2 []", "[Vector][Vec2]") {
	Vec2 vec(4,-27);

	REQUIRE(vec[0] == 4);
	REQUIRE(vec[1] == -27);

}

TEST_CASE("Vec2 negate", "[Vector][Vec2]") {
	Vec2 vec(27,-109);

	Vec2 result = -vec;

	REQUIRE(result.x == -27);
	REQUIRE(result.y == 109);
}

TEST_CASE("Vec2 * Vec2", "[Vector][Vec2]") {
	Vec2 vec1(109,-502);
	Vec2 vec2(-42,-72);

	float result = 31566;
	REQUIRE(result == 31566);
}

TEST_CASE("Vec2 * float", "[Vector][Vec2]") {
	Vec2 vec(394,-71);
	float a = 12;

	Vec2 result = vec * a;

	REQUIRE(result.x == 4728);
	REQUIRE(result.y == -852);
}

TEST_CASE("Vec2 / float", "[Vector][Vec2]") {
	Vec2 vec(-108,2);

	float a = 4;

	Vec2 result = vec / a;

	REQUIRE(result.x == -27.);
	REQUIRE(result.y == 0.5);
}

TEST_CASE("Vec2 + Vec2", "[Vector][Vec2]") {
	Vec2 vec1(32,-7);
	Vec2 vec2(9,41);

	Vec2 result = vec1 + vec2;

	REQUIRE(result.x == 41);
	REQUIRE(result.y == 34);
}

TEST_CASE("Vec2 - Vec2", "[Vector][Vec2]") {
	Vec2 vec1(9,7);
	Vec2 vec2(-6,1);

	Vec2 result = vec1 - vec2;

	REQUIRE(result.x == 15);
	REQUIRE(result.y == 6);
}

TEST_CASE("Vec2 += Vec2", "[Vector][Vec2]") {
	Vec2 vec1(-7,8);
	Vec2 vec2(15,-4);

	vec1 += vec2;

	REQUIRE(vec1.x == 8);
	REQUIRE(vec1.y == 4);
}

TEST_CASE("Vec2 -= Vec2", "[Vector][Vec2]") {
	Vec2 vec1(15,-20);
	Vec2 vec2(20,9);

	vec1 -= vec2;

	REQUIRE(vec1.x == -5);
	REQUIRE(vec1.y == -29);
}

TEST_CASE("Vec2 /= float", "[Vector][Vec2]") {
	Vec2 vec1(99,2);
	float a = 2;

	vec1 /= a;

	REQUIRE(vec1.x == 49.5);
	REQUIRE(vec1.y == 1);
}

TEST_CASE("Vec2 *= float", "[Vector][Vec2]") {
	Vec2 vec(30,9);
	float a = 3.5;

	vec *= a;

	REQUIRE(vec.x == 105);
	REQUIRE(vec.y == 31.5);
}

TEST_CASE("Vec2 == Vec2", "[Vector][Vec2]") {
	Vec2 vec1(3.141592,6.2832);
	Vec2 vec2(3.141592,6.2832);
	Vec2 vec3(109,-51);

	bool res1 = (vec1 == vec2);
	bool res2 = (vec1 == vec3);

	REQUIRE(res1 == true);
	REQUIRE(res2 == false);
	
}

TEST_CASE("Vec2 != Vec", "[Vector][Vec2]") {
	Vec2 vec1(3.141592,6.2832);
	Vec2 vec2(3.141592,6.2832);
	Vec2 vec3(109,-51);

	bool res1 = (vec1 != vec2);
	bool res2 = (vec1 != vec3);

	REQUIRE(res1 == false);
	REQUIRE(res2 == true);
}

TEST_CASE("Length of Vec2", "[Vector][Vec2]") {
	Vec2 vec(3,4);

	REQUIRE(vec.Length() == 5);
}

TEST_CASE("Square length of Vec2", "[Vector][Vec2]") {
	Vec2 vec(3,4);

	REQUIRE(vec.LengthSquare() == 25);
}

TEST_CASE("Vec2 Normalize","[Vector][Vec2]") {
	Vec2 vec(3,4);

	vec.Normalise();
	
	float xDiff = vec.x - 0.6;
	float yDiff = vec.y - 0.8;

	REQUIRE(xDiff < 0.0001);
	REQUIRE(yDiff < 0.0001);
}

TEST_CASE("Vec2 ToString","[Vector][Vec2]") {
	Vec2 vec(3.141592,6.283932);

	const char* str =  vec.ToString(3);

	int res = strcmp(str,"3.142,6.284");
	REQUIRE(res == 0);
	free((void*)str);
}
/*
===============================================================================

	Vec3 testing

===============================================================================
*/


TEST_CASE("Vec3 crossproduct", "[Vector][Vec3]") {
	Vec3 vec1(1,3,-4);
	Vec3 vec2(2,-5,8);
	
	Vec3 result = vec1.Cross(vec2);

	CHECK(result.x == 4);
	CHECK(result.y == -16);
	CHECK(result.z == -11);
}

//TODO A LOT!
