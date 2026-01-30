cmake_minimum_required(VERSION 3.15)
project(launcher C)

# Use C11
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Default to Release when not specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
endif()

# Compiler warning flags
if(MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -pedantic)
endif()

# Sources (root + src/)
file(GLOB SRCS CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/*.c" "${CMAKE_SOURCE_DIR}/src/*.c")

add_executable(${PROJECT_NAME} ${SRCS})

# Put outputs into build/dist
set(DIST_DIR "${CMAKE_BINARY_DIR}/dist")
set_target_properties(${PROJECT_NAME} PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${DIST_DIR}/bin"
  ARCHIVE_OUTPUT_DIRECTORY "${DIST_DIR}/lib"
  LIBRARY_OUTPUT_DIRECTORY "${DIST_DIR}/lib"
)

# Export compile commands for tooling
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Install target
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

# Helpful custom targets
add_custom_target(run
  COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target ${PROJECT_NAME} --config $<CONFIG>
  COMMAND "${DIST_DIR}/bin/${PROJECT_NAME}"
  DEPENDS ${PROJECT_NAME}
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  COMMENT "Build and run ${PROJECT_NAME}"
)

add_custom_target(clean-dist
  COMMAND ${CMAKE_COMMAND} -E remove_directory "${DIST_DIR}"
  COMMENT "Remove generated dist directory"
)

message(STATUS "Configured ${PROJECT_NAME} (C ${CMAKE_C_STANDARD}) - outputs -> ${DIST_DIR}")
