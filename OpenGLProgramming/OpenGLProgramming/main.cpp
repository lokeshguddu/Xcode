//
//  main.cpp
//  OpenGLProgramming
//
//  Created by Lokesh Basu on 09/12/14.
//  Copyright (c) 2014 InHouse. All rights reserved.
//

#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

GLuint program_;
GLint a_Position_;

int initResources()
{
    GLint compileStatus = GL_FALSE, linkStatus = GL_FALSE;
    
    GLuint vertexShaderHandle = glCreateShader(GL_VERTEX_SHADER);
    
    const char *vertexShaderSource =
    "attribute vec2 coord2d;                  "
    "void main(void) {                        "
    "  gl_Position = vec4(coord2d, 0.0, 1.0); "
    "}";
    
    glShaderSource(vertexShaderHandle, 1, &vertexShaderSource, NULL);
    
    glCompileShader(vertexShaderHandle);
    
    glGetShaderiv(vertexShaderHandle, GL_COMPILE_STATUS, &compileStatus);
    
    if (!compileStatus) {
        cout << "Error in vertex shader" << endl;
        return 0;
    }
    
    GLuint fragmentShaderHandle = glCreateShader(GL_VERTEX_SHADER);
    
    const char *fragmentShaderSource =
    "void main(void) {        "
    "  gl_FragColor[0] = 0.0; "
    "  gl_FragColor[1] = 0.0; "
    "  gl_FragColor[2] = 1.0; "
    "}";
    
    glShaderSource(fragmentShaderHandle, 1, &fragmentShaderSource, NULL);
    
    glCompileShader(fragmentShaderHandle);
    
    glGetShaderiv(fragmentShaderHandle, GL_COMPILE_STATUS, &compileStatus);
    
    if (!compileStatus) {
        cout << "Error in fragment shader" << endl;
        return 0;
    }
    
    program_ = glCreateProgram();
    glAttachShader(program_, vertexShaderHandle);
    glAttachShader(program_, fragmentShaderHandle);
    glLinkProgram(program_);
    glGetProgramiv(program_, GL_LINK_STATUS, &linkStatus);
    if (!linkStatus) {
        cout << "glLinkProgram:" << endl;
        return 0;
    }
    
    const char* a_Position = "coord2d";
    a_Position_ = glGetAttribLocation(program_, a_Position);
    if (a_Position_ == -1) {
        cout << "Could not bind attribute " << a_Position << endl;
        return 0;
    }
    
    return 1;
}

void onDisplay()
{
    /* Clear the background as white */
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    
}

int main (int argc, char **argv)
{
    glutInit (&argc, argv);
    
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_3_2_CORE_PROFILE);
    
    glutInitWindowSize(600, 600);
    
    glutCreateWindow("Tutorial 01");

    return 0;
}