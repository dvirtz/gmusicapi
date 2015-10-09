set(HEADERS GMusicApi.h GMusicApiUser.h Mobileclient.h Webclient.h Song.h utility.h)
set(SOURCES GMusicApi.cpp Mobileclient.cpp Webclient.cpp Song.cpp GMusicApiUser.cpp)

add_library(GMusicApi ${SOURCES} ${HEADERS})

target_include_directories(GMusicApi SYSTEM PUBLIC
	${Boost_INCLUDE_DIR}
	${PYTHON_INCLUDE_DIRS})