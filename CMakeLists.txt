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
# Bouncing Ball Target
# -----------------------------
add_executable(bouncing_ball_imtui
    bouncing_ball_imtui.cpp
)

target_link_libraries(bouncing_ball_imtui
    PRIVATE
        imtui
        imtui-ncurses
        ${CURSES_LIBRARIES}
)

target_include_directories(bouncing_ball_imtui
    PRIVATE
        ${CURSES_INCLUDE_DIR}
)

target_include_directories(bouncing_ball_imtui
    PRIVATE
        ${CMAKE_SOURCE_DIR}/imtui/third-party/imgui/imgui
)

# -----------------------------
# Bouncing Ball Circle Target
# -----------------------------
add_executable(bouncing_ball_imtui_circle
    bouncing_ball_imtui_circle.cpp
)

target_link_libraries(bouncing_ball_imtui_circle
    PRIVATE
        imtui
        imtui-ncurses
        ${CURSES_LIBRARIES}
)

target_include_directories(bouncing_ball_imtui_circle
    PRIVATE
        ${CURSES_INCLUDE_DIR}
)

target_include_directories(bouncing_ball_imtui_circle
    PRIVATE
        ${CMAKE_SOURCE_DIR}/imtui/third-party/imgui/imgui
)
