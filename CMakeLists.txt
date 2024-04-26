cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

project(SiPMSim)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

file(GLOB macros ${PROJECT_SOURCE_DIR}/macros/*.mac)

file(COPY ${macros} DESTINATION ${PROJECT_BINARY_DIR})

add_executable(Sim SiPMSim.cc ${sources} ${headers})
target_link_libraries(Sim ${Geant4_LIBRARIES})

add_custom_target(SiPMSim DEPENDS Sim)