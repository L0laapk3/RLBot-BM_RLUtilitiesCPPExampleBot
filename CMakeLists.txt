cmake_minimum_required(VERSION 3.8)
project(RLBot-BM_RLUtilitiesCPPExampleBot LANGUAGES CXX)

set(RLBOT-BM_CPP_DIR ${PROJECT_SOURCE_DIR}/RLBot-BM_CPP)
set(RLBOT-BM_DIR ${RLBOT-BM_CPP_DIR}/RLBot-BM)
set(RLUtilities_DIR ${PROJECT_SOURCE_DIR}/RLUtilities)
add_subdirectory(${RLBOT-BM_CPP_DIR})
add_subdirectory(${RLUtilities_DIR})

file(GLOB_RECURSE sources ${PROJECT_SOURCE_DIR}/src/*.cc ${RLBOT-BM_DIR}/src/shared/*.cpp)

add_executable(${PROJECT_NAME} ${sources})
target_include_directories(${PROJECT_NAME} PUBLIC inc)

target_include_directories(${PROJECT_NAME} PRIVATE ${RLBOT-BM_CPP_DIR}/inc ${RLBOT-BM_CPP_DIR}/lib/inc)
target_include_directories(${PROJECT_NAME} PRIVATE ${RLUtilities_DIR}/inc ${RLUtilities_DIR}/inc/*)

if (UNIX)
    target_link_libraries(${PROJECT_NAME} RLBot-BM_CPP pthread)
else (UNIX)
    target_link_libraries(${PROJECT_NAME} RLBot-BM_CPP)
endif (UNIX)

target_link_libraries(${PROJECT_NAME} rlutilities_cpp)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

# Copy port config to output folder
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/port.cfg"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)

# Copy port config to release folder
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/port.cfg"
        ${PROJECT_SOURCE_DIR}/rlbot)

# Copy assets to executable folder
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/RLUtilities/assets"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets)

# Copy assets to release folder
file(COPY ${PROJECT_SOURCE_DIR}/RLUtilities/assets DESTINATION ${PROJECT_SOURCE_DIR}/rlbot)