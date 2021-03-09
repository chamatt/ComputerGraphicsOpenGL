#include "tiro.h"
#include <math.h>
#include <iostream>
#define DISTANCIA_MAX 500

void Tiro::DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B)
{
        float theta;
        glColor3f(R, G, B);
        glBegin(GL_POLYGON);
            for(int i = 0; i < 360/20; i++) {
                theta = i*20*3.14/180;
                glVertex2f(radius*cos(theta), radius*sin(theta));
            }
        glEnd();
}

void Tiro::DesenhaTiro(GLfloat x, GLfloat y)
{
    glPushMatrix();
    std::cout << "que carlaho" << x << "," << y << std::endl;
    glTranslatef(x, y, 0);
    this->DesenhaCirc(radiusTiro, 1,1,1);
    glPopMatrix();
}

void Tiro::Move()
{
    GLfloat dx = sin(gDirectionAng) * gVel;
    GLfloat dy = cos(gDirectionAng) * gVel;
    
    gX += dx;
    gY += dy;
}

bool Tiro::Valido()
{
    GLfloat xDist = abs(gXInit - gX);
    GLfloat yDist = abs(gYInit - gY);
    
    GLfloat distancia = sqrt(pow(xDist, 2) * pow(yDist, 2));
    
    return distancia <= DISTANCIA_MAX;
}

