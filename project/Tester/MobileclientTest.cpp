#include "Catch.hpp"
#include "Mobileclient.h"
#include "userCredentials.h"
#include "Song.h"

using namespace GMusicApi;

TEST_CASE("Mobileclient constructed", "[Mobileclient]")
{
	REQUIRE_NOTHROW(Mobileclient m);
}

TEST_CASE("empty login failes", "[Mobileclient]")
{
	Mobileclient m;
	REQUIRE_FALSE(m.login("", ""));
}

TEST_CASE("login succeeds", "[Mobileclient]")
{
	Mobileclient m;
	REQUIRE(m.login(gm_user, gm_pass));
}

TEST_CASE("logout succeeds", "[Mobilecleint]")
{
	Mobileclient m;
	REQUIRE(m.logout());
}

TEST_CASE("song list not empty", "[Mobileclient]")
{
	Mobileclient m;
	m.login(gm_user, gm_pass);
	SECTION("incremental")
	{
		REQUIRE_FALSE(m.get_all_songs(true).empty());
	}
	SECTION("non incremental")
	{
		REQUIRE_FALSE(m.get_all_songs().empty());
	}
}