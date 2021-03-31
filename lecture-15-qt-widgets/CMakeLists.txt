find_package(Qt5 COMPONENTS Core Gui Widgets)
set(CMAKE_AUTOMOC ON)

add_executable("lecture-15-aquarium" "aquarium_window.h" "aquarium_windows.cpp" "main.cpp" "settings.h" "settings.cpp" "settings_window.h" "settings_window.cpp")
target_link_libraries("lecture-15-aquarium" Qt5::Core Qt5::Gui Qt5::Widgets)

# При каждой сборке:
# 1. Удаляем старую папку с ресурсами
add_custom_command(
    TARGET "lecture-15-aquarium" POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_CURRENT_BINARY_DIR}/resources"
)
# 2. Копируем папку с ресурсами из директории с исходным кодом в директорию с исполняемым файлом.
add_custom_command(
    TARGET "lecture-15-aquarium" POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/resources"
    "${CMAKE_CURRENT_BINARY_DIR}/resources"
)

if (WIN32)
    # Чтобы убрать консоль
    #set_property(TARGET "lecture-15-aquarium" PROPERTY WIN32_EXECUTABLE true)

    # Копирование DLL-файлов библиотеки Qt в выходную директорию
    add_custom_command(
        TARGET "lecture-15-aquarium" POST_BUILD
        COMMAND ${Qt5_DIR}/../../../bin/windeployqt $<TARGET_FILE:lecture-15-aquarium>
    )
endif (WIN32)
