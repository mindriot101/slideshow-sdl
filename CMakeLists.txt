cmake_minimum_required(VERSION 3.0)

set(PROG main)

if (CMAKE_BUILD_TYPE MATCHES "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
endif()

project(Presenter)

file(GLOB CPP_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB H_FILES ${CMAKE_SOURCE_DIR}/include/*.h)

add_executable(${PROG}
    ${CPP_FILES}
    ${H_FILES}
    )

target_include_directories(${PROG} PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_compile_features(${PROG} PRIVATE cxx_std_14)
target_link_libraries(${PROG} SDL2 SDL2_image SDL2_ttf)

add_custom_target(run COMMAND ./${PROG} DEPENDS ${PROG})
add_custom_target(debug COMMAND lldb ./${PROG} DEPENDS ${PROG})
