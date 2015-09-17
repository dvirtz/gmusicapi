if ((NOT DEFINED GM_U) OR (NOT DEFINED GM_P))
	message(FATAL_ERROR "Please define Google Music credentials:
	GM_U:	user name
	GM_P:	password")
endif()

set(USER_CRED_H userCredentials.h)
configure_file("${USER_CRED_H}.in" ${CMAKE_CURRENT_BINARY_DIR}/${USER_CRED_H})

set(HEADERS ${CMAKE_CURRENT_BINARY_DIR}/${USER_CRED_H})
set(SOURCES MobileclientTest.cpp TesterMain.cpp WebclientTester.cpp)

include_directories(${CATCH_INCLUDE_DIR} 
	$<TARGET_PROPERTY:GMusicApi,INTERFACE_INCLUDE_DIRECTORIES>
	${CMAKE_CURRENT_BINARY_DIR})

add_executable(Tester ${HEADERS} ${SOURCES})

target_link_libraries(Tester ${Boost_LIBRARIES}
	GMusicApi 
	debug ${PYTHON_LIBRARY_DEBUG} 
	optimized ${PYTHON_LIBRARY_RELEASE})

get_filename_component(PYTHON_PATH ${PYTHON_EXECUTABLE} DIRECTORY)

add_custom_command(TARGET Tester 
	POST_BUILD 
	COMMAND ${CMAKE_COMMAND} -E env "PATH=${PYTHON_PATH}" $<TARGET_FILE:Tester>)