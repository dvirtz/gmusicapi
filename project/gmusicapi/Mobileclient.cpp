#include "MobileClient.h"
#include "utility.h"
#include <iostream>

namespace py = boost::python;

namespace GMusicApi
{

Mobileclient::Mobileclient(bool debug_logging /*= true*/, bool validate /*= true*/, bool verify_ssl /*= true*/)
	: GMusicApiUser("Mobileclient", debug_logging, validate, verify_ssl)
{
}


Mobileclient::~Mobileclient()
{
}

bool Mobileclient::login(const std::string & email, const std::string & password, const std::string & android_id) const
{
	return callMethod<bool>("login", email, password, android_id);
}

bool Mobileclient::logout() const
{
	return callMethod<bool>("logout");
}

SongRange Mobileclient::get_all_songs(bool incremental, bool include_deleted)
{
	return callMethod<SongRange>("get_all_songs", incremental, include_deleted);
}


} // namespace GMusicApi
