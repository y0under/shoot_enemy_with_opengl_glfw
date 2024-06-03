cmake_minimum_required(VERSION 3.20)
project(shoot_enemy CXX)

set(CMAKE_CXX_STANDARD 20)
set(BIN_NAME "shoot_enemy")

if(MSVC)
  # Force to always compile with W4
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  # Update if necessary
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-long-long --pedantic-errors")
endif()

include(FetchContent)
FetchContent_Declare(
  y0_engine
  GIT_REPOSITORY https://github.com/y0under/y0_engine.git
  GIT_TAG        develop
)
FetchContent_MakeAvailable(y0_engine)

# add_subdirectory(${y0_engine_SOURCE_DIR})

add_subdirectory(src)
# add_subdirectory(${y0_engine_SOURCE_DIR} ${y0_engine_BINARY_DIR})

add_custom_target(run
  COMMAND ${BIN_NAME}
  DEPENDS ${BIN_NAME}
  # WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  COMMENT "Running"
  )

