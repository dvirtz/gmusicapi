#include "Catch.hpp"
#include "Mobileclient.h"
#include "userCredentials.h"

using namespace GMusicApi;

TEST_CASE("Mobileclient constructed", "[Mobileclient]")
{
	REQUIRE_NOTHROW(Mobileclient m);
}

TEST_CASE("empty login failes", "[Mobileclient]")
{
	Mobileclient m;
	REQUIRE(m.login("", "") == false);
}

TEST_CASE("login succeeds", "[Mobileclient]")
{
	Mobileclient m;
	REQUIRE(m.login(gm_user, gm_pass));
}