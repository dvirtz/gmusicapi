#pragma once
#include "GMusicApiUser.h"
#include "Song.h"
#include <string>
#include <vector>

namespace GMusicApi
{

class Mobileclient : private GMusicApiUser
{
public:
	Mobileclient(bool debug_logging = true, bool validate = true, bool verify_ssl = true);
	~Mobileclient();

	bool login(const std::string& email,
			   const std::string& password, 
			   const std::string& android_id = std::string()) const;

	bool logout() const;

	SongRange get_all_songs(bool incremental = false, bool include_deleted = false);

};


} // namespace GMusicApi
