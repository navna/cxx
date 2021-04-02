find_package(Qt5 COMPONENTS Core Gui Network Widgets)
set(CMAKE_AUTOMOC ON)

add_executable("lecture-16-lambda" "lambda.cpp")
add_executable("lecture-16-simple-server" "simple_server.cpp")
target_link_libraries("lecture-16-simple-server" Qt5::Core Qt5::Network)

add_subdirectory(message)

if (WIN32)
	add_custom_command(TARGET "lecture-16-simple-server" POST_BUILD COMMAND ${Qt5_DIR}/../../../bin/windeployqt $<TARGET_FILE:lecture-16-simple-server>)
endif (WIN32)
