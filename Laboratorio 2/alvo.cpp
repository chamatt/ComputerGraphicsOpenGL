#include "alvo.h"
#include <math.h>
#include "framework.h"

void Alvo::DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B)
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

void Alvo::DesenhaAlvo(GLfloat x, GLfloat y)
{
    auto p = [=](int colorNum) { return gColor == colorNum ? 1 : 0;};
    
    glPushMatrix();
    glTranslatef(x, y, 0);
    this->DesenhaCirc(radiusAlvo, p(0), p(1), p(2));
    glPopMatrix();
}

void Alvo::Recria(GLfloat x, GLfloat y)
{
//    gX = Random(-250, 250).number;
//    gY = Random(-250, 250).number;
    gX = x;
    gY = y;
    
    gColor = (gColor == 3-1) ? 0 : gColor+1;
}

bool Alvo::Atingido(Tiro *tiro)
{
    GLfloat intersectionRadius = radiusTiro + radiusAlvo;
    
    GLfloat tiroX, tiroY;
    tiro->GetPos(tiroX, tiroY);
    
    Point2D* alvoCenter = new Point2D(gX, gY);
    
    Point2D* tiroCenter = new Point2D(tiroX, tiroY);
    
    return alvoCenter->distanceTo(tiroCenter) < intersectionRadius;
    
}
