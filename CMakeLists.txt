cmake_minimum_required(VERSION 3.8)
project(RLBotBM-RLUtilitiesCPPExampleBot LANGUAGES CXX)

add_subdirectory(RLBotBMCPP)
add_subdirectory(RLUtilities)

file(GLOB_RECURSE sources ${PROJECT_SOURCE_DIR}/src/*.cc ${PROJECT_SOURCE_DIR}/RLBotBMCPP/RLBotBMLib/src/shared/*.cpp)

add_executable(RLBotBM-RLUtilitiesCPPExampleBot ${sources})
target_include_directories(RLBotBM-RLUtilitiesCPPExampleBot PUBLIC inc)

target_include_directories(RLBotBM-RLUtilitiesCPPExampleBot PRIVATE RLBotBMCPP/inc RLBotBMCPP/lib/inc)
target_include_directories(RLBotBM-RLUtilitiesCPPExampleBot PRIVATE RLUtilities/inc RLUtilities/inc/*)

if (UNIX)
    target_link_libraries(RLBotBM-RLUtilitiesCPPExampleBot RLBotBMCPP pthread)
else (UNIX)
    target_link_libraries(RLBotBM-RLUtilitiesCPPExampleBot RLBotBMCPP)
endif (UNIX)

target_link_libraries(RLBotBM-RLUtilitiesCPPExampleBot rlutilities_cpp)

target_compile_features(RLBotBM-RLUtilitiesCPPExampleBot PRIVATE cxx_std_17)

# Copy port config to output folder
add_custom_command(TARGET RLBotBM-RLUtilitiesCPPExampleBot POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/port.cfg"
        $<TARGET_FILE_DIR:RLBotBM-RLUtilitiesCPPExampleBot>)

# Copy port config to release folder
add_custom_command(TARGET RLBotBM-RLUtilitiesCPPExampleBot POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/port.cfg"
        ${PROJECT_SOURCE_DIR}/rlbot)

# Copy assets to executable folder
add_custom_command(TARGET RLBotBM-RLUtilitiesCPPExampleBot POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/RLUtilities/assets"
        $<TARGET_FILE_DIR:RLBotBM-RLUtilitiesCPPExampleBot>/assets)

# Copy assets to release folder
file(COPY ${PROJECT_SOURCE_DIR}/RLUtilities/assets DESTINATION ${PROJECT_SOURCE_DIR}/rlbot)