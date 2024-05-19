#ifndef GLFW_PRAC_GAME_H
#define GLFW_PRAC_GAME_H

#include "colliding.h"
#include "player.h"
#include "player_bullet.h"
#include "enemy.h"
#include "y0_engine/shader/shader_operator.h"
#include "y0_engine/window/WindowGlfw.h"

#include <algorithm>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>
#include <GLFW/glfw3.h>

/*
 * main class
 */
class game {
  public:
    explicit game();
    void start();
    GLuint create_shader();

    const float kheight_ = 400;
    const float kwidth_ = 600;
    const uint32_t kexpected_min_elapsed_time_per_flame_ = 16;
    const float kmax_delta_time_ = 0.5f;
    const float kplayer_speed_ = 0.02f;
    const float kplayer_bullet_speed_ = 0.08f;
    const float kplayer_height_ = 0.05f;
    const float kplayer_width_ = 2.0f / 20.0f;

  private:
    void init_window();
    void draw_player();
    void draw_player_bullet();
    void draw_enemy();
    void process_input();
    void update_status();
    void update_player_vertex(float delta_time);
    void update_player_bullet_position(float delta_time);
    void shoot_player_bullet();
    void generate_output();
    void main_loop();

    std::unique_ptr<WindowGlfw> window_;
    GLuint program_id_;
    std::unique_ptr<y0_engine::shader_operator> shader_operator_;
    std::unique_ptr<player> player_;
    std::unique_ptr<player_bullet> player_bullet_;
    std::unique_ptr<enemy> enemy_;
    GLfloat player_verteces_[8];
    GLuint player_indices_[8];
    int32_t player_direction_;
    uint32_t ticks_count_;

};
#endif
