//
//  ch2_move.cpp
//  proj.mac
//
//  Created by zuowu on 2018/8/15.
//


#include <GLTools.h>

#include <math.h>
#ifdef __APPLE__
#include <GLUT/GLUT.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

GLShaderManager shaderManager;
GLBatch squareBatch;

GLfloat blockSize = 0.1f;
GLfloat vVerts[] = {
    -blockSize, -blockSize, 0.0f,
     blockSize, -blockSize, 0.0f,
     blockSize,  blockSize, 0.0f,
    -blockSize,  blockSize, 0.0f
};

typedef struct {
    GLfloat x;
    GLfloat y;
}Point;
typedef struct {
    GLfloat w;
    GLfloat h;
}Size;
class Cube {
public:
    Cube(GLfloat x, GLfloat y, GLfloat w, GLfloat h){
        _center.x = x;
        _center.y = y;
        _size.w = w;
        _size.h = h;
        makeCube(x,y,w,h);
    };

    void makeCube(GLfloat x, GLfloat y, GLfloat w, GLfloat h){
//        GLfloat vv[12] = {
//            x - w/2, y - h/2, 0.0f,
//            x + w/2, y - h/2, 0.0f,
//            x - w/2, y + h/2, 0.0f,
//            x + w/2, y - h/2, 0.0f
//        };
//        _verts[12] = {
//            x - w/2, y - h/2, 0.0f,
//            x + w/2, y - h/2, 0.0f,
//            x - w/2, y + h/2, 0.0f,
//            x + w/2, y - h/2, 0.0f
//        };
    };
    GLfloat * getVerts(){
        return _verts;
    }
private:
    GLfloat _verts[12];
    Point _center;
    Size _size;
};


void SetupRC(){
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    shaderManager.InitializeStockShaders();
    squareBatch.Begin(GL_TRIANGLE_FAN, 4);
    Cube cube = Cube(0, 0, 0.1, 0.1);
    squareBatch.CopyVertexData3f(vVerts);
    squareBatch.End();
}

void SpeialKey(int key, int x, int y) {
    if (key == 27) {
        exit(0);
    }
    
    GLfloat stepSize = 0.025;
    GLfloat blockX = vVerts[0];
    GLfloat blockY = vVerts[7];
    
    if (key == GLUT_KEY_UP) {
        blockY += stepSize;
    }else if (key == GLUT_KEY_DOWN) {
        blockY -= stepSize;
    }else if (key == GLUT_KEY_LEFT) {
        blockX -= stepSize;
    }else if (key == GLUT_KEY_RIGHT) {
        blockX += stepSize;
    }
    
    vVerts[0] = blockX;
    vVerts[1] = blockY - blockSize * 2;
    
    vVerts[3] = blockX + blockSize * 2;
    vVerts[4] = blockY - blockSize * 2;
    
    vVerts[6] = blockX + blockSize * 2;
    vVerts[7] = blockY;
    
    vVerts[9] = blockX;
    vVerts[10] = blockY;
    
    squareBatch.CopyVertexData3f(vVerts);
    glutPostRedisplay();
}

void RenderScene(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    GLfloat vRed[] = {1.0f, 0.0f, 0.0f, 1.0f};
    shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed);
    squareBatch.Draw();
    glutSwapBuffers();
}

void ChangeSize(int w, int h) {
    glViewport(0, 0, w, h);
}

int main(int argc, char ** argv){
    gltSetWorkingDirectory(argv[0]);
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow(argv[0]);
    
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return 1;
    }
    
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    glutSpecialFunc(SpeialKey);
    
    SetupRC();
    glutMainLoop();
    return 0;
}












