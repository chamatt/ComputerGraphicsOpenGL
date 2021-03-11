#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif


#ifndef TIRO_H
#define	TIRO_H

#define radiusTiro 5

class Tiro {
    GLfloat gXInit; 
    GLfloat gYInit; 
    GLfloat gX; 
    GLfloat gY; 
    GLfloat gDirectionAng;
    GLfloat gVel;
private:
    void DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B);
    void DesenhaTiro(GLfloat x, GLfloat y);
public:
    Tiro(GLfloat x, GLfloat y, GLfloat directionAng){
        gXInit = x; 
        gYInit = y; 
        gX = x; 
        gY = y; 
        gDirectionAng = directionAng; 
        gVel = 10;
    };
    void Desenha(){ 
        DesenhaTiro(gX, gY);
    };
    void Move();
    bool Valido();
    void GetPos(GLfloat &xOut, GLfloat &yOut){
        xOut = gX;
        yOut = gY;
    };
};

#endif	/* TIRO_H */

