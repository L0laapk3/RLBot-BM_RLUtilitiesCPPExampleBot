cmake_minimum_required(VERSION 3.8)
project(RLUtilitiesCPPExampleBot LANGUAGES CXX)

add_subdirectory(RLBotCPP)
add_subdirectory(RLUtilities)

file(GLOB_RECURSE sources ${PROJECT_SOURCE_DIR}/src/*.cc ${PROJECT_SOURCE_DIR}/inc/*.h)

add_executable(RLUtilitiesCPPExampleBot ${sources})
target_include_directories(RLUtilitiesCPPExampleBot PUBLIC inc)

target_include_directories(RLUtilitiesCPPExampleBot PRIVATE RLBotCPP/inc RLBotCPP/lib/inc)
target_include_directories(RLUtilitiesCPPExampleBot PRIVATE RLUtilities/inc RLUtilities/inc/*)

if (UNIX)
    target_link_libraries(RLUtilitiesCPPExampleBot RLBotCPP pthread)
else (UNIX)
    target_link_libraries(RLUtilitiesCPPExampleBot RLBotCPP)
endif (UNIX)

target_link_libraries(RLUtilitiesCPPExampleBot rlutilities_cpp)

target_compile_features(RLUtilitiesCPPExampleBot PRIVATE cxx_std_17)

# Copy port config to output folder
add_custom_command(TARGET RLUtilitiesCPPExampleBot POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/port.cfg"
        $<TARGET_FILE_DIR:RLUtilitiesCPPExampleBot>)

# Copy port config to release folder
add_custom_command(TARGET RLUtilitiesCPPExampleBot POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/port.cfg"
        ${PROJECT_SOURCE_DIR}/rlbot)

# Copy assets to executable folder
add_custom_command(TARGET RLUtilitiesCPPExampleBot POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/RLUtilities/assets"
        $<TARGET_FILE_DIR:RLUtilitiesCPPExampleBot>/assets)

# Copy assets to release folder
file(COPY ${PROJECT_SOURCE_DIR}/RLUtilities/assets DESTINATION ${PROJECT_SOURCE_DIR}/rlbot)