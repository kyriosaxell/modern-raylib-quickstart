cmake_minimum_required(VERSION 4.2.1)
project(SpaceInvaders)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(SpaceInvaders
    src/main.cpp
	src/spaceship.cpp
	src/spaceship.hpp
	src/game.cpp
	src/game.hpp
	src/laser.cpp
	src/laser.hpp
	src/block.cpp
	src/block.hpp
	src/obstacle.cpp
	src/obstacle.hpp
	src/alien.cpp
	src/alien.hpp
	src/telemetry.cpp
	src/telemetry.hpp
	src/mysteryship.cpp
	src/mysteryship.hpp
)

target_include_directories(SpaceInvaders PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# --- raylib ---
# Preferimos la raylib instalada en el sistema vía pkg-config.
find_package(PkgConfig QUIET)
if(PKG_CONFIG_FOUND)
    pkg_check_modules(RAYLIB QUIET raylib)
endif()

if(RAYLIB_FOUND)
    target_include_directories(SpaceInvaders PRIVATE ${RAYLIB_INCLUDE_DIRS})
    target_link_directories(SpaceInvaders PRIVATE ${RAYLIB_LIBRARY_DIRS})
    target_link_libraries(SpaceInvaders PRIVATE ${RAYLIB_LIBRARIES} m dl pthread)
else()
    # Fallback: intenta enlazar la librería precompilada del repo (por ejemplo, bin/Debug/libraylib.a)
    set(RAYLIB_FALLBACK_LIB "${CMAKE_CURRENT_SOURCE_DIR}/bin/Debug/libraylib.a")
    if(EXISTS "${RAYLIB_FALLBACK_LIB}")
        target_link_libraries(SpaceInvaders PRIVATE "${RAYLIB_FALLBACK_LIB}" m dl pthread)
        target_include_directories(SpaceInvaders PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/build/external/raylib-master/src")
    else()
        message(FATAL_ERROR "No se encontró raylib. Instálala (pkg-config raylib) o añade bin/Debug/libraylib.a")
    endif()
endif()
