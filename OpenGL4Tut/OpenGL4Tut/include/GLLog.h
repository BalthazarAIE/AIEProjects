#define GL_LOG_FILE "gl.log"
#ifndef __GLLOG_H_
#define __GLLOG_H_
#include <time.h>
#include <fstream>
#include <GL/glew.h>


bool restart_gl_log () ;

bool gl_log (const char* message, const char* filename, int line); 
void printShaderInfoLog(GLuint obj);

void printProgramInfoLog(GLuint obj);


void log_gl_params ();

#endif