// Triangle.cpp
// Our first OpenGL program that will just draw a triangle on the screen.

#include "GLTools.h"
#include "GLShaderManager.h"

#ifdef __APPLE__
#include <GLUT/glut.h>

#else
#define FREEGLUT_STATIC
#include <GL/glut.h>            // Windows FreeGlut equivalent
#endif


GLBatch    triangleBatch;
GLShaderManager    shaderManager;


void ChangeSize(int w, int h)
{
    glViewport(0, 0, w, h);
}


void SetupRC()
{
    // Blue background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
    shaderManager.InitializeStockShaders();
    GLfloat vVerts[] = {
        -0.95f, 0.95f, 0.0f,
        0.9f, 0.95f, 0.0f,
        -0.95f, -0.9f, 0.0f,
        
        0.95f, -0.95f, 0.0f,
        -0.9f, -0.95f, 0.0f,
        0.95f, 0.9f, 0.0f
    };
    triangleBatch.Begin(GL_TRIANGLES, 6);
    triangleBatch.CopyVertexData3f(vVerts);
    triangleBatch.End();
}


///////////////////////////////////////////////////////////////////////////////
// Called to draw scene
void RenderScene(void)
{
    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    GLfloat vRed[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed);
    triangleBatch.Draw();
    glutSwapBuffers();
}

void keyBoard(unsigned char key, int x, int y) {
    if (key == 27) {
        exit(0);
    }
}


int main(int argc, char* argv[])
{
    gltSetWorkingDirectory(argv[0]);
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    glutKeyboardFunc(keyBoard);
    
    GLenum erra= glGetError();
    printf("%d",erra);
    
    
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
        return 1;
    }
    
    SetupRC();
    
    glutMainLoop();
    return 0;
}
