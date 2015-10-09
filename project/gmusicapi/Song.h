#pragma once

#include <string>
#include <vector>
#include <boost/python/detail/wrap_python.hpp>
#include <boost/python.hpp>
#include <boost/date_time/gregorian/gregorian_types.hpp>
#include <boost/range.hpp>
#include <boost/range/any_range.hpp>
#include <boost/python/stl_iterator.hpp>
#include <chrono>

namespace GMusicApi
{

class Song
{
public:
	using traversal = boost::iterator_traversal<boost::python::stl_input_iterator<Song>>::type;
	using range = boost::any_range<Song, traversal>;

	Song(const boost::python::dict& dict);

	std::string comment();
	size_t rating();
	std::vector<std::string> albumArtRef();
//	std::vector<std::string> artistId();
//	std::string composer();
//	boost::gregorian::greg_year year();
//	std::chrono::time_point creationTimestamp();
//	std::string id();
//	std::string album();
//	size_t totalDiscCount();
//	std::string title();
//	std::chrono::time_point recentTimestamp();
//	std::string albumArtist();
//	size_t trackNumber();
//	size_t discNumber();
//	bool deleted();
//	std::string storeId();
//	std::string nid();
//	size_t totalTrackCount();
//	size_t estimatedSize();
//	std::string albumId();
//	size_t beatsPerMinute();
//	std::string genre();
//	size_t playCount();
//	std::vector<std::string> artistArtRef();
//	std::string kind();
//	std::string artist();
//	std::chrono::time_point lastModifiedTimestamp();
//	std::string clientId();
//	std::chrono::duration duration();

private:
    template<typename Ret>
    Ret extractFromDict(const char* key);

    boost::python::dict m_dict;
};

using SongRange = Song::range;

// used when get_all_songs returns a generator
class SongGeneratorIterator : 
	public boost::iterator_facade<SongGeneratorIterator, Song, Song::traversal>
{
public:
	SongGeneratorIterator()
	{}

	SongGeneratorIterator(boost::python::object& generator)
		: m_generatorIt(generator)
	{
		if (m_generatorIt != m_generatorEnd)
		{
			m_currentIt = song_iterator(*m_generatorIt);
		}
	}

private:
	friend class boost::iterator_core_access;
	
	void increment() 
	{
		if (++m_currentIt == m_currentEnd)
		{
			if (++m_generatorIt != m_generatorEnd)
			{
				m_currentIt = song_iterator(*m_generatorIt);
			}
		}
	}

	bool equal(SongGeneratorIterator const& other) const
	{
		return m_generatorIt == other.m_generatorIt
			&& m_currentIt == other.m_currentIt;
	}

	Song& dereference() const 
	{ 
		return *m_currentIt; 
	}

	using generator_iterator = boost::python::stl_input_iterator<boost::python::list>;
	using song_iterator = boost::python::stl_input_iterator<Song>;
	generator_iterator	m_generatorIt;
	generator_iterator	m_generatorEnd;
	song_iterator m_currentIt;
	song_iterator m_currentEnd;
};

struct pyGeneratorToSongRangeConverter
{
	static void registerConverter()
	{
		boost::python::converter::registry::push_back(
			&convertible,
			&construct,
			boost::python::type_id<SongRange>());
	}

	static void* convertible(PyObject* pObj)
	{
		if (!PyGen_Check(pObj))
			return nullptr;

		return pObj;
	}

	// Convert obj_ptr into a QString
	static void construct(PyObject* pObj,
						  boost::python::converter::rvalue_from_python_stage1_data* data)
	{
		using namespace boost::python;

		// Grab pointer to memory into which to construct the new QString
		void* storage = (
			(converter::rvalue_from_python_storage<SongRange>*)
			data)->storage.bytes;

		// Use borrowed to construct the object so that a reference
		// count will be properly handled.
		handle<> hndl(borrowed(pObj));
		new (storage) SongRange(SongGeneratorIterator(object(hndl)),
								SongGeneratorIterator());

		// Stash the memory chunk pointer for later use by boost.python
		data->convertible = storage;
	}
};

} // namespace GMusicApi