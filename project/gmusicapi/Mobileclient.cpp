#include "MobileClient.h"
#include "GMusicApi.h"
#include <iostream>

namespace GMusicApi
{

Mobileclient::Mobileclient(bool debug_logging /*= true*/, bool validate /*= true*/, bool verify_ssl /*= true*/)
{
	m_object = GMusicApi::instance().getInstance("Mobileclient", debug_logging, validate, verify_ssl);
}


Mobileclient::~Mobileclient()
{
}

bool Mobileclient::login(const std::string & email, const std::string & password, const std::string & android_id) const
{
	return GMusicApi::instance().callMethod<bool>(m_object, "login", email, password, android_id);
}


} // namespace GMusicApi
