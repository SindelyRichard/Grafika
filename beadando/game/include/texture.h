#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/gl.h>

typedef GLubyte Pixel[3];

/**
 * Load texture from file and returns with the texture name.
 */
GLuint load_texture(char* filename); //rgba

GLuint load_texture_rgb(char* filename); //rgb

#endif /* TEXTURE_H */
