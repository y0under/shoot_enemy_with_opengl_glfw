#include "game.h"

game::game() {
  player_verteces_[0] = { -0.05f, -0.95f };
  player_verteces_[1] = { 0.05f, -0.95f };
  player_verteces_[2] = { 0.05f, -0.9f };
  player_verteces_[3] = { -0.05f, -0.9f };

  player_direction_ = 0;
  ticks_count_ = 0;
} // player_(new player(kwidth, kheight)){}

void game::start() {
  init_window();
  player_ = std::make_unique<player>(2, 4, player_verteces_, kheight_, kwidth_);
  player_bullet_ = std::make_unique<player_bullet>();
  enemy_ = std::make_unique<enemy>(kheight_, kwidth_);
  program_id_ = create_shader();
  char c[256];
  print_shader_info_log(program_id_, c);
  print_program_info_log(program_id_);
  main_loop();
}

/*
 * out put result of compiling shader
 */
GLboolean game::print_shader_info_log(GLuint shader, const char *str)
{
  GLint status;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE) std::cerr << "Compile Error in " << str << std::endl;
  GLsizei bufSize;
  glGetShaderiv(shader, GL_INFO_LOG_LENGTH , &bufSize);
  if (bufSize > 1)
  {
    std::vector<GLchar> infoLog(bufSize);
    GLsizei length;
    glGetShaderInfoLog(shader, bufSize, &length, &infoLog[0]);
    std::cerr << &infoLog[0] << std::endl;
  }
  return static_cast<GLboolean>(status);
}

/*
 * out put linking result of program objedt
 */
GLboolean game::print_program_info_log(GLuint program)
{
  GLint status;
  glGetProgramiv(program, GL_LINK_STATUS, &status);
  if (status == GL_FALSE) std::cerr << "Link Error." << std::endl;
  GLsizei bufSize;
  glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufSize);
  if (bufSize > 1)
  {
    std::vector<GLchar> infoLog(bufSize);
    GLsizei length;
    glGetProgramInfoLog(program, bufSize, &length, &infoLog[0]);
    std::cerr << &infoLog[0] << std::endl;
  }
  return static_cast<GLboolean>(status);
}



GLuint game::create_shader()
{
  // vertex shader
  GLuint vShaderId = glCreateShader(GL_VERTEX_SHADER);
  std::string vertexShader = R"#(
#version 150 core
in vec4 position;
void main()
{
 gl_Position = position;
}
    )#";

  const char* vs = vertexShader.c_str();
  glShaderSource(vShaderId, 1, &vs, NULL);
  glCompileShader(vShaderId);

  // fragment shader
  GLuint fShaderId = glCreateShader(GL_FRAGMENT_SHADER);
  std::string fragmentShader = R"#(
#version 150 core
out vec4 fragment;
void main()
{
 fragment = vec4(1.0, 1.0, 1.0, 1.0);
}
    )#";
  const char* fs = fragmentShader.c_str();
  glShaderSource(fShaderId, 1, &fs, NULL);
  glCompileShader(fShaderId);

  GLuint programId = glCreateProgram();
  glAttachShader(programId,vShaderId);
  glAttachShader(programId,fShaderId);

  glLinkProgram(programId);

  glUseProgram(programId);

  return programId;
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

  GLFWwindow *window(glfwCreateWindow(kwidth_, kheight_, "GLFW test", nullptr, nullptr));
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
  player_->object_->bind();  // bind player's vertex buffer'
  glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(object::vertex), player_verteces_, GL_DYNAMIC_DRAW);  // update buffer
  glDrawArrays(GL_LINE_LOOP, 0, player_->vertex_count_);
  glDisableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
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
  v.y = static_cast<float>(player_verteces_[2].position[1]);
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

  player_verteces_[0].position[0] = player_->position_.x - khalf_player_width;
  player_verteces_[1].position[0] = player_->position_.x + khalf_player_width;
  player_verteces_[2].position[0] = player_->position_.x + khalf_player_width;
  player_verteces_[3].position[0] = player_->position_.x - khalf_player_width;
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
  glUseProgram(program_id_);
  draw_player();
  glUseProgram(program_id_);
  draw_player_bullet();
  glUseProgram(program_id_);
  draw_enemy();
}

void game::main_loop()
{
  while (!glfwWindowShouldClose(window_)) {
    if (glfwGetKey(window_, GLFW_KEY_ESCAPE)) break;
    // define background color
    glClearColor(0.5f, 0.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearDepth(1.0);

    process_input();
    update_status();
    generate_output();
    glfwSwapBuffers(window_);
    glfwPollEvents();
  }
}
