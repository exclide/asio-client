cmake_minimum_required(VERSION 3.26)
project(asio_client)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(OpenSSL REQUIRED)
find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Network
        WebSockets
        REQUIRED)

set(sources main.cpp
        ChatClient.cpp
        ChatWindow.cpp
        LoginWindow.cpp
        HostInfo.h
        DbMessage.h
        User.h)

set(libs OpenSSL::SSL Qt::Core Qt::Gui Qt::Widgets Qt::Network Qt::WebSockets)

add_executable(asio_client ${sources})
target_link_libraries(asio_client ${libs})