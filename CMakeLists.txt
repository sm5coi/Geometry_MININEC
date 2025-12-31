cmake_minimum_required(VERSION 3.16)

project(Geometry_MININEC LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Geometry_MININEC main.cpp
    GeometryInput.hpp
    Connections.hpp
    GeometryOutput.hpp
    Connections.cpp
    GeometryInput.cpp
    GeometryOutput.cpp
    GeometryData.hpp
    SimulationState.hpp
)

include(GNUInstallDirs)
install(TARGETS Geometry_MININEC
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
