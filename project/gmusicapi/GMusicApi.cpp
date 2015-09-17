#include "GMusicApi.h"
#include <iostream>

namespace GMusicApi
{

using namespace boost::python;

GMusicApi& GMusicApi::instance()
{
	static GMusicApi instance;
	return instance;
}

GMusicApi::GMusicApi()
{
	Py_Initialize();
	auto module = import("gmusicapi");
	m_dict = module.attr("__dict__");
}


GMusicApi::~GMusicApi()
{
}

} // namespace GMusicApi