#pragma once
#include <boost/python/detail/wrap_python.hpp>
#include <boost/python.hpp>
#include <string>
#include <sstream>

namespace GMusicApi
{

class GMusicApi
{
public:
	static GMusicApi& instance();

	template<typename... Args>
	boost::python::object getInstance(const std::string& name, Args&&... args) const;

	template<typename R, typename... Args>
	R callMethod(const boost::python::object& object, const std::string& methodName, Args&&... args) const;

private:
	GMusicApi();
	~GMusicApi();
	GMusicApi(const GMusicApi&) = delete;
	GMusicApi& operator=(const GMusicApi&) = delete;

	boost::python::object m_dict;
};

template<typename ...Args>
boost::python::object GMusicApi::getInstance(const std::string & name, Args&& ...args) const
{
	boost::python::object type = m_dict[name];
	return boost::python::call<boost::python::object>(type.ptr(), std::forward<Args>(args)...);
}

template<typename R, typename ...Args>
R GMusicApi::callMethod(const boost::python::object& object, const std::string & methodName, Args && ...args) const
{
	return boost::python::call_method<R>(object.ptr(), methodName.c_str(), std::forward<Args>(args)...);
}

} // namespace GMusicApi