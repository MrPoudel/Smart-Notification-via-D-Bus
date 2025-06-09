cmake_minimum_required(VERSION 3.10)
project(SmartDBusNotification)

set(CMAKE_CXX_STANDARD 11)

find_package(PkgConfig REQUIRED)
pkg_check_modules(DBUS REQUIRED dbus-1)

include_directories(${DBUS_INCLUDE_DIRS})
link_directories(${DBUS_LIBRARY_DIRS})

add_executable(server server.cpp)
target_link_libraries(server ${DBUS_LIBRARIES})

add_executable(client client.cpp)
target_link_libraries(client ${DBUS_LIBRARIES})
