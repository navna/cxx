find_package(Qt5 COMPONENTS Core Gui Network Widgets)
set(CMAKE_AUTOMOC ON)

add_library("lecture-16-message" STATIC "common/protocol.cpp" "common/protocol.h")
target_include_directories("lecture-16-message" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/common")

add_executable("lecture-16-message-server" "server/main.cpp" "server/server.cpp" "server/server.h")
add_executable("lecture-16-message-client" "client/main.cpp" "client/main_window.cpp" "client/main_window.h" "client/server_request.cpp" "client/server_request.h")
target_link_libraries("lecture-16-message-server" "lecture-16-message" Qt5::Core Qt5::Network)
target_link_libraries("lecture-16-message-client" "lecture-16-message" Qt5::Core Qt5::Gui Qt5::Network Qt5::Widgets)

if (WIN32)
	#set_property(TARGET "lecture-16-message-client" PROPERTY WIN32_EXECUTABLE true)

	add_custom_command(TARGET "lecture-16-message-server" POST_BUILD COMMAND ${Qt5_DIR}/../../../bin/windeployqt $<TARGET_FILE:lecture-16-message-server>)
	add_custom_command(TARGET "lecture-16-message-client" POST_BUILD COMMAND ${Qt5_DIR}/../../../bin/windeployqt $<TARGET_FILE:lecture-16-message-client>)
endif (WIN32)
