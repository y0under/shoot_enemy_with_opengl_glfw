#include "game.h"

game::game() {
  GLfloat player_verteces[] = { -0.05f, -0.95f,
                                0.05f, -0.95f,
                                0.05f, -0.9f,
                                -0.05f, -0.9f };
  for (int i = 0; i < 8; ++i) player_verteces_[i] = player_verteces[i];
  GLuint player_indices[] = { 0, 1,
                              1, 2,
                              2, 3,
                              3, 0 };
  for (int i = 0; i < 8; ++i) player_indices_[i] = player_indices[i];

  player_direction_ = 0;
  ticks_count_ = 0;
} // player_(new player(kwidth, kheight)){}

void game::start() {
  init_window();
  player_ = std::make_unique<player>(2, 8, player_verteces_, 8, player_indices_, kwidth_, kheight_);
  player_bullet_ = std::make_unique<player_bullet>(kwidth_, kheight_);
  enemy_ = std::make_unique<enemy>(kheight_, kwidth_);

  shader_operator_ = std::make_unique<y0_engine::shader_operator>();
  if (!shader_operator_->load_shader("./shader/vertex_shader.vert",
        "./shader/fragment_shader.frag")) {
    std::cerr << "loading shader is failed." << std::endl;
    return;
  }

  main_loop();
}

void game::init_window() {
  if (!glfwInit()) {
    throw std::runtime_error("GLFW is not initialized.");
  }

  // rgist process of ending
  atexit(glfwTerminate);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  // glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window(glfwCreateWindow(kwidth_, kheight_, "shoot enemy", nullptr, nullptr));
  window_ = std::move(window);
  if (!window_) {
    throw std::runtime_error("Failed to create GLFW window.");
  }

  // let active window
  glfwMakeContextCurrent(window_);

  // init glew
  glewExperimental = GL_TRUE;

  if (glewInit() != GLEW_OK)
  {
    glfwDestroyWindow(window_);
    throw std::runtime_error("Can't initialize GLEW");
  }

}

void game::draw_player() {
  player_->draw(player_verteces_);
  // player_->vertex_array_->bind();  // bind player's vertex buffer'
  // glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(GLfloat), player_verteces_, GL_DYNAMIC_DRAW);  // update buffer
  // glDrawArrays(GL_LINES, 0, player_->vertex_count_);
  // glDisableVertexAttribArray(0);
  // glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void game::draw_enemy() {
  enemy_->draw();
}

void game::draw_player_bullet() {
  if (!player_bullet_->is_shoot())
    return;

  player_bullet_->draw();
}

/*
 * processing of input keyboard
 */
void game::process_input() {
  player_direction_ = 0;
  // move player to left
  if (glfwGetKey(window_, GLFW_KEY_A)) {
    --player_direction_;
  }
  // move player to right
  if (glfwGetKey(window_, GLFW_KEY_D)) {
    ++player_direction_;
  }

  // shoot player's bullet
  if (glfwGetKey(window_, GLFW_KEY_K)) {
    if (!player_bullet_->is_shoot()) {
      shoot_player_bullet();
    }
  }
}

void game::shoot_player_bullet() {
  player_bullet_->shoot();
  vector2 v;
  // fixme: dirty code. wanna calc player vertex from center position of player
  v.x = player_->position_.x;
  v.y = static_cast<float>(player_verteces_[7]);
  player_bullet_->set_center(v);
}

/*
 * update elements for display
 */
void game::update_status() {
  // wait until deltatime over minimum.
  while (!(glfwGetTime() - ticks_count_ < kexpected_min_elapsed_time_per_flame_));

  // wait
  float delta_time = (glfwGetTime() - ticks_count_) / 1000.0f;
  // limitation for max delta time
  delta_time = std::max(delta_time, kmax_delta_time_);
  ticks_count_ = glfwGetTime();

  update_player_vertex(delta_time);
  update_player_bullet_position(delta_time);

  vector2 enemy_center = enemy_->get_center();
  vector2 player_bullet_center = player_bullet_->get_center();
  if (enemy_->is_alive() && colliding::is_colliding(enemy_->get_radius(), enemy_->get_center(),
                         player_bullet_->get_radius(), player_bullet_->get_center())) {
    enemy_->kill();
    player_bullet_->land();
  }
}

/*
 * for move player
 */
void game::update_player_vertex(float delta_time) {

  player_->position_.x += player_direction_ * (kplayer_speed_ * delta_time);
  // protect from over flow x position
  const float khalf_player_width = kplayer_width_ / 2.0f;
  player_->position_.x = std::max(-1.0f + khalf_player_width, player_->position_.x);
  player_->position_.x = std::min(player_->position_.x, 1.0f - khalf_player_width);

  player_verteces_[0] = player_->position_.x - khalf_player_width;
  player_verteces_[2] = player_->position_.x + khalf_player_width;
  player_verteces_[4] = player_->position_.x + khalf_player_width;
  player_verteces_[6] = player_->position_.x - khalf_player_width;

}

/*
 * move player's bullet
 */
void game::update_player_bullet_position(float delta_time) {
  if (!player_bullet_->is_shoot())
    return;
  vector2 v = player_bullet_->get_center();
  v.y += kplayer_bullet_speed_ * delta_time;
  // out of display area
  if (v.y > 1.0f) {
    player_bullet_->land();
    return;
  }
  player_bullet_->set_center(v);
}

void game::generate_output() {
  shader_operator_->set_target_shader();
  draw_player();
  shader_operator_->set_target_shader();
  draw_player_bullet();
  shader_operator_->set_target_shader();
  draw_enemy();
}

void game::main_loop()
{
  while (!glfwWindowShouldClose(window_)) {
    if (glfwGetKey(window_, GLFW_KEY_ESCAPE)) break;
    // define background color
    glClearColor(0.2f, 0.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearDepth(1.0);

    process_input();
    update_status();
    generate_output();
    glfwSwapBuffers(window_);
    glfwPollEvents();
  }
}
