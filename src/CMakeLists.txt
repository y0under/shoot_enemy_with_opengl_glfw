# add_library(shader_operator
#   STATIC
#     shader_operator/shader_operator.cc)

add_library(circle
  STATIC
    circle.cc)

add_library(enemy
  STATIC
    enemy.cc)

add_library(player
  STATIC
    player.cc)

add_library(player_bullet
  STATIC
    player_bullet.cc)

add_library(game
  STATIC
    game.cc)

# target_include_directories(shader_operator
#   PUBLIC ${PROJECT_SOURCE_DIR}/src)

target_include_directories(enemy
  PUBLIC ${PROJECT_SOURCE_DIR}/src)

target_include_directories(player
  PUBLIC ${PROJECT_SOURCE_DIR}/src)

target_include_directories(player_bullet
  PUBLIC ${PROJECT_SOURCE_DIR}/src)

target_include_directories(circle
  PUBLIC ${PROJECT_SOURCE_DIR}/src)

target_include_directories(game
  PUBLIC ${PROJECT_SOURCE_DIR}/src)

include_directories(${CMAKE_BINARY_DIR}/_deps/y0_engine-src/include)

add_executable(shoot_enemy main.cc)

target_compile_options(shoot_enemy PUBLIC -Wall --pedantic-errors)
target_compile_features(shoot_enemy PUBLIC cxx_std_20)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

target_link_libraries(shoot_enemy
                      #OpenGL::GL
                      #                      glfw
                      #                    GLEW
                      game
                      circle
                      enemy
                      player
                      player_bullet
                      # ${OpenCV_LIBS}
                      # ${Boost_LIBRARIES}
                      # ${CMAKE_THREAD_LIBS_INIT}
                      y0_engine)

