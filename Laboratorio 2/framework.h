#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#ifndef FRAMEWORK_H
#define	FRAMEWORK_H

#include "robo.h"
#include <math.h>
#include <iostream>
#include <vector>

using namespace std;

class Point2D {
    public:
        GLfloat x;
        GLfloat y;

        Point2D(GLfloat x, GLfloat y){
            this->x = x;
            this->y = y;
        };
};

class Transformation {
    private:
        bool shouldLog = false;
        
        void log();
        
        void logTranslate(GLfloat x, GLfloat y);
    
        void logRotate(GLfloat angle);
    
        void matrixMultiply(vector< vector<GLfloat> > mat2);

        void matrixVectorMultiply(vector< vector<GLfloat> > vet1,
                                  vector< vector<GLfloat> > &res);

    public:
        vector< vector<GLfloat> > matrix;

        vector< vector<GLfloat> > getIdentity();
        Transformation(){
            this->matrix = this->getIdentity();
            this->log();
        };

        void translate2d(GLfloat x, GLfloat y);

        void rotate2d(GLfloat angle);

        void apply(Point2D* point);
    
        void logMode(bool state);
};


#endif	/* FRAMEWORK_H */
