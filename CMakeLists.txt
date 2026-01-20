cmake_minimum_required(VERSION 3.16)

project(imtui_programs LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -----------------------------
# Dependencies
# -----------------------------
find_package(Curses REQUIRED)

# imtui as source
add_subdirectory(imtui)

# -----------------------------
# Target
# -----------------------------
add_executable(hello_imtui
    hello_imtui.cpp
)

target_link_libraries(hello_imtui
    PRIVATE
        imtui
        imtui-ncurses
        ${CURSES_LIBRARIES}
)

target_include_directories(hello_imtui
    PRIVATE
        ${CURSES_INCLUDE_DIR}
)

target_include_directories(hello_imtui
    PRIVATE
        ${CMAKE_SOURCE_DIR}/imtui/third-party/imgui/imgui
)


# -----------------------------
# Bouncing Ball Circle Target
# -----------------------------
add_executable(bb-pop
    bb-pop.cpp
)

target_link_libraries(bb-pop
    PRIVATE
        imtui
        imtui-ncurses
        ${CURSES_LIBRARIES}
)

target_include_directories(bb-pop
    PRIVATE
        ${CURSES_INCLUDE_DIR}
)

target_include_directories(bb-pop
    PRIVATE
        ${CMAKE_SOURCE_DIR}/imtui/third-party/imgui/imgui
)


# -----------------------------
# Bouncing Ball Circle Target
# -----------------------------
add_executable(bb-oop
    bb-oop.cpp
)

target_link_libraries(bb-oop
    PRIVATE
        imtui
        imtui-ncurses
        ${CURSES_LIBRARIES}
)

target_include_directories(bb-oop
    PRIVATE
        ${CURSES_INCLUDE_DIR}
)

target_include_directories(bb-oop
    PRIVATE
        ${CMAKE_SOURCE_DIR}/imtui/third-party/imgui/imgui
)
