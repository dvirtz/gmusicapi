//
// Created by Dvir on 23/09/2015.
//
#include "Song.h"
namespace GMusicApi
{
    Song::Song(const boost::python::dict& dict)
            : m_dict(dict)
    {}


    std::string Song::comment()
    {
        return extractFromDict<std::string>("comment");
    }

    size_t Song::rating()
    {
        return extractFromDict<size_t>("rating");
    }

    std::vector<std::string> Song::albumArtRef()
    {
        return extractFromDict<std::vector<std::string>>("albumArtRef");
    }
//
//    std::vector<std::string> artistId();
//    std::string composer();
//    boost::gregorian::greg_year year();
//    std::chrono::time_point creationTimestamp();
//    std::string id();
//    std::string album();
//    size_t totalDiscCount();
//    std::string title();
//    std::chrono::time_point recentTimestamp();
//    std::string albumArtist();
//    size_t trackNumber();
//    size_t discNumber();
//    bool deleted();
//    std::string storeId();
//    std::string nid();
//    size_t totalTrackCount();
//    size_t estimatedSize();
//    std::string albumId();
//    size_t beatsPerMinute();
//    std::string genre();
//    size_t playCount();
//    std::vector<std::string> artistArtRef();
//    std::string kind();
//    std::string artist();
//    std::chrono::time_point lastModifiedTimestamp();
//    std::string clientId();
//    std::chrono::duration duration();

    template<typename Ret>
    Ret Song::extractFromDict(const char* key)
    {
        return boost::python::extract<Ret>(m_dict[key]);
    };

} // namespace GMusicApi
