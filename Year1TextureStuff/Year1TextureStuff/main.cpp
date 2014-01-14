int main(int argc, char *argv[])
{
	  GLuint v, g, f;
    char *vs,*gs, *fs;
 
    // Create shader handlers
    v = glCreateShader(GL_VERTEX_SHADER);
    f = glCreateShader(GL_FRAGMENT_SHADER); 
 
    // Read source code from files
    vs = textFileRead("example.vert");
    fs = textFileRead("example.frag");
 
    const char * vv = vs;
    const char * ff = fs;
 
    // Set shader source
    glShaderSource(v, 1, &vv,NULL);
    glShaderSource(f, 1, &ff,NULL);
 
    free(vs);free(gs);free(fs);
 
    // Compile all shaders
    glCompileShader(v);
    glCompileShader(g);
    glCompileShader(f);
 
    // Create the program
    p = glCreateProgram();
 
    // Attach shaders to program
    glAttachShader(p,v);
    glAttachShader(p,g);
    glAttachShader(p,f);
 
    // Link and set program to use
    glLinkProgram(p);
    glUseProgram(p);

}

