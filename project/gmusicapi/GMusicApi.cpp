#include "GMusicApi.h"
#include "Song.h"
#include "utility.h"
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

	registerTypeConverters();
}


GMusicApi::~GMusicApi()
{
}

void GMusicApi::registerTypeConverters()
{
	pySequenceToCppContainerConverter<SongRange>::registerConverter();
	pyGeneratorToSongRangeConverter::registerConverter();
	pyToCppConverter<Song, boost::python::dict>::registerConverter();
	pySequenceToCppContainerConverter<std::vector<std::string>>::registerConverter();
}

} // namespace GMusicApi