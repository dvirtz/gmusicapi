set(HEADERS GMusicApi.h Mobileclient.h Webclient.h)
set(SOURCES GMusicApi.cpp Mobileclient.cpp Webclient.cpp)

add_library(GMusicApi ${SOURCES} ${HEADERS})

target_include_directories(GMusicApi PUBLIC
	${Boost_INCLUDE_DIR}
	${PYTHON_INCLUDE_DIRS}
	${CMAKE_CURRENT_SOURCE_DIR})