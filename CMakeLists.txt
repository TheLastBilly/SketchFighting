cmake_minimum_required (VERSION 3.0)

project(gutless)
set(CMAKE_CXX_STANDARD 11)


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

include_directories("${CMAKE_SOURCE_DIR}/source")
file(GLOB SOURCES
    "source/*.cpp"
)

add_executable(${PROJECT_NAME} 
	${SOURCES}
)

target_link_libraries(${PROJECT_NAME}  
	${SDL2_LIBRARIES}
)