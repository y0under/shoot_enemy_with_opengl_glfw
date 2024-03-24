#ifndef GLFW_PRAC_OBJECT
#define GLFW_PRAC_OBJECT

#include <GL/glew.h>
#include <GLFW/glfw3.h>

/*
 * for display target object 
 */
class object {
  public:
    struct vertex
    {
      GLfloat position[2];
    };

    object(GLint dimension, GLsizei vertexcount, const vertex *vertex);
    virtual ~object();
    void bind() const;

  private:
    // forbidden copy by copy constructor
    object(const object &o);
    // forbidden update by operator =
    object &operator=(const object &o);
    // vertex array object
    GLuint vao_;
    // vertex array object name
    GLuint vbo_;
};


#endif
