#include <catch.hpp>
#include <math/Matrix.h>


/*
===============================================================================

	Matrix unit testing

===============================================================================
*/

/*
===============================================================================

	Mat3 testing

===============================================================================
*/

TEST_CASE("Mat3 initialisation", "[Matrix][Mat3]") {
	Mat3 mat(0,1,2,
			 3,4,5,
			 6,7,8);

	REQUIRE(mat.m00 == 0);
	REQUIRE(mat.m01 == 1);
	REQUIRE(mat.m02 == 2);
	REQUIRE(mat.m10 == 3);
	REQUIRE(mat.m11 == 4);
	REQUIRE(mat.m12 == 5);
	REQUIRE(mat.m20 == 6);
	REQUIRE(mat.m21 == 7);
	REQUIRE(mat.m22 == 8);

	//TODO Vec3 constructor
}

//TODO operator[]


TEST_CASE("Mat3 negate", "[Matrix][Mat3]") {
	Mat3 mat(-1,4,7,
			 8,-6,9,
			 3,9,10);
	Mat3 res = -mat;


	REQUIRE(res.m00 == 1);
	REQUIRE(res.m01 == -4);
	REQUIRE(res.m02 == -7);
	REQUIRE(res.m10 == -8);
	REQUIRE(res.m11 == 6);
	REQUIRE(res.m12 == -9);
	REQUIRE(res.m20 == -3);
	REQUIRE(res.m21 == -9);
	REQUIRE(res.m22 == -10);

}

TEST_CASE("Mat3 * Vec3", "[Matrix][Mat3]") {
	Vec3 vec(7,-9,2);
	Mat3 mat(-1,7,3,
			 10,-8,4,
			 49,2,5);

	Vec3 res = mat * vec;

	REQUIRE(res.x == -64);
	REQUIRE(res.y == 150);
	REQUIRE(res.z == 335);

}

TEST_CASE("Mat3 * float","[Matrix][Mat3") {
	Mat3 mat(32,63,-7,
			 86,-42,61,
			 6,15,-3);
	float a = -5;

	Mat3 res1 = mat*a;

	CHECK(res1.m00 == -160);
	CHECK(res1.m01 == -315);
	CHECK(res1.m02 == 35);
	CHECK(res1.m10 == -430);
	CHECK(res1.m11 == 210);
	CHECK(res1.m12 == -305);
	CHECK(res1.m20 == -30);
	CHECK(res1.m21 == -75);
	CHECK(res1.m22 == 15);

}

TEST_CASE("Mat3 * Mat3", "[Matrix][Mat3]") {
	Mat3 mat1(-5,8,9,
			  11,-7,-2,
			  -3,111,12);
	Mat3 mat2(32,63,-7,
			  86,-42,61,
			  6,15,-3);

	Mat3 res1 = mat1 * mat2;
	Mat3 res2 = mat2 * mat1;

	CHECK(res1.m00 == 582);
	CHECK(res1.m01 == -516);
	CHECK(res1.m02 == 496);
	CHECK(res1.m10 == -262);
	CHECK(res1.m11 == 957);
	CHECK(res1.m12 == -498);
	CHECK(res1.m20 == 9522);
	CHECK(res1.m21 == -4671);
	CHECK(res1.m22 == 6756);

	CHECK(res2.m00 == 554);
	CHECK(res2.m01 == -962);
	CHECK(res2.m02 == 78);
	CHECK(res2.m10 == -1075);
	CHECK(res2.m11 == 7753);
	CHECK(res2.m12 == 1590);
	CHECK(res2.m20 == 144);
	CHECK(res2.m21 == -390);
	CHECK(res2.m22 == -12);

}

TEST_CASE("Mat3 + Mat3","[Matrix][Mat3]") {
	Mat3 mat1(-5,8,9,
			  11,-7,-2,
			  -3,111,12);
	Mat3 mat2(32,63,-7,
			  86,-42,61,
			  6,15,-3);

	Mat3 res1 = mat1 + mat2;

	CHECK(res1.m00 == 27);
	CHECK(res1.m01 == 71);
	CHECK(res1.m02 == 2);
	CHECK(res1.m10 == 97);
	CHECK(res1.m11 == -49);
	CHECK(res1.m12 == 59);
	CHECK(res1.m20 == 3);
	CHECK(res1.m21 == 126);
	CHECK(res1.m22 == 9);

}

TEST_CASE("Mat3 - Mat3", "[Matrix][Mat3]") {
	Mat3 mat1(-5,8,9,
			  11,-7,-2,
			  -3,111,12);
	Mat3 mat2(32,63,-7,
			  86,-42,61,
			  6,15,-3);

	Mat3 res1 = mat1 - mat2;

	CHECK(res1.m00 == -37);
	CHECK(res1.m01 == -55);
	CHECK(res1.m02 == 16);
	CHECK(res1.m10 == -75);
	CHECK(res1.m11 == 35);
	CHECK(res1.m12 == -63);
	CHECK(res1.m20 == -9);
	CHECK(res1.m21 == 96);
	CHECK(res1.m22 == 15);

}

//TODO operator +=
//TODO operator -=
//TODO operator *=


TEST_CASE("Mat3 == Mat3", "[Matrix][Mat3]") {
	Mat3 mat1(-5,8,9,
			  11,-7,-2,
			  -3,111,12);
	Mat3 mat2(-5,8,9,
			  11,-7,-2,
			  -3,111,12);

	bool res = mat1 == mat2;

	REQUIRE(res == true);

}

TEST_CASE("Mat3 != Mat3", "[Matrix][Mat3]") {
	Mat3 mat1(-5,8,9,
			  11,-7,-2,
			  -3,111,12);
	Mat3 mat2(32,63,-7,
			  86,-42,61,
			  6,15,-3);

	bool res = mat1 == mat2;

	REQUIRE(res == false);

}

//TODO Trac
//TODO Determinant
//TODO Transpose
//TODO TransposeSelf
//TODO SetZero
//TODO SetIdentity
