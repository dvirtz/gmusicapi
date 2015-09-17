#pragma once
#include <boost/python.hpp>
#include <string>

namespace GMusicApi
{

class Mobileclient
{
public:
	Mobileclient(bool debug_logging = true, bool validate = true, bool verify_ssl = true);
	~Mobileclient();

	bool login(const std::string& email,
			   const std::string& password, 
			   const std::string& android_id = std::string()) const;

private:
	boost::python::object m_object;
};


} // namespace GMusicApi
