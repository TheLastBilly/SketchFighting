cmake_minimum_required (VERSION 3.0)

project(kingsketchfight)
set(CMAKE_CXX_STANDARD 11)

find_package(PkgConfig REQUIRED)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image)

include_directories(${SDL2_INCLUDE_DIRS})

include_directories("${CMAKE_SOURCE_DIR}/source/engine" "${CMAKE_SOURCE_DIR}/source/game" "${CMAKE_SOURCE_DIR}/source")
file(GLOB SOURCES
    "source/engine/*.cpp"
	"source/game/*.cpp"
)

add_executable(${PROJECT_NAME} 
	${SOURCES}
)

target_link_directories(${PROJECT_NAME} 
	PRIVATE ${SDL2_INCLUDE_DIRS}
	PRIVATE ${SDL2IMAGE_INCLUDE_DIRS}
)

target_compile_definitions(${PROJECT_NAME} PRIVATE APP_NAME="${PROJECT_NAME}")

target_link_libraries(${PROJECT_NAME}  
	${SDL2_LIBRARIES}
	${SDL2IMAGE_LIBRARIES}
)