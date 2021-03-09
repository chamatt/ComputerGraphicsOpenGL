#include "robo.h"
#include <math.h>
#include <iostream>
#define PI 3.14

void Robo::DesenhaRect(GLint height, GLint width, GLfloat R, GLfloat G, GLfloat B)
{
    GLint x1 = -width/2, x2 = width/2;
    GLint y1 = 0, y2 = height;
    glBegin(GL_POLYGON);
        glColor3f(R, G, B);
        glVertex2f(x1, y1);
        glVertex2f(x2, y1);
        glVertex2f(x2, y2);
        glVertex2f(x1, y2);
    glEnd();
}

void Robo::DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B)
{
//    glPointSize(2);
//    glColor3f(R, G, B);
//    for(int i = 0; i < 360/20; i++) {
//        glRotatef(20, 0, 0, 1);
//        glBegin(GL_POINTS);
//        glVertex2f(radius, 0);
//        glEnd();
//    }
    glPointSize(2);
    float theta;
    glColor3f(R, G, B);
    glBegin(GL_POINTS);
        for(int i = 0; i < 360/20; i++) {
            theta = i*20*3.14/180;
            glVertex2f(radius*cos(theta), radius*sin(theta));
        }
    glEnd();
}

void Robo::DesenhaRoda(GLfloat x, GLfloat y, GLfloat thetaWheel, GLfloat R, GLfloat G, GLfloat B)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    glRotatef(thetaWheel, 0, 0, 1);
    this->DesenhaCirc(radiusWheel, R, G, B);
    glPopMatrix();
}

void Robo::DesenhaBraco(GLfloat x, GLfloat y, GLfloat theta1, GLfloat theta2, GLfloat theta3)
{
    glPushMatrix();
   
    glTranslatef(x, y, 0); /* Move to first paddle base */
    glRotatef(theta1, 0, 0, 1);
    this->DesenhaRect(paddleHeight, paddleWidth, 0, 0, 1);
    
    glTranslatef(0, paddleHeight, 0);  /* Move to second paddle base */
    glRotatef(theta2, 0, 0, 1);
    this->DesenhaRect(paddleHeight, paddleWidth, 1, 1, 0);
    
    glTranslatef(0, paddleHeight, 0);  /* Move to third paddle base */
    glRotatef(theta3, 0, 0, 1);
    this->DesenhaRect(paddleHeight, paddleWidth, 0, 1, 0);
    
    glPopMatrix();
}

void Robo::DesenhaRobo(GLfloat x, GLfloat y, GLfloat thetaWheel, GLfloat theta1, GLfloat theta2, GLfloat theta3)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    this->DesenhaRect(baseHeight, baseWidth, 1, 0, 0);
    this->DesenhaBraco(0, baseHeight, theta1, theta2, theta3);
    
    this->DesenhaRoda(-baseWidth/2, 0, thetaWheel, 1, 1, 1);
    this->DesenhaRoda(baseWidth/2, 0, thetaWheel, 1, 1, 1);
    
    glPopMatrix();
}

void Robo::RodaBraco1(GLfloat inc)
{
    this->gTheta1 += inc;
}

void Robo::RodaBraco2(GLfloat inc)
{
    this->gTheta2 += inc;
}

void Robo::RodaBraco3(GLfloat inc)
{
    this->gTheta3 += inc;
}

void Robo::MoveEmX(GLfloat dx)
{
    this->gX += dx;
    
    float deltaTheta = - 2 * PI * radiusWheel * dx / 360;
    
    this->gThetaWheel += deltaTheta;
}

void matrixVectorMultiply(GLfloat mat1[3][3],
              GLfloat mat2[3][1],
              GLfloat res[3][1])
{
    int i, j, k;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 1; j++) {
            res[i][j] = 0;
            for (k = 0; k < 3; k++)
                res[i][j] += mat1[i][k] * mat2[k][j];
        }
    }
}

//Funcao auxiliar de rotacao
void RotatePoint(GLfloat x, GLfloat y, GLfloat angle, GLfloat &xOut, GLfloat &yOut){
    GLfloat rotationMatrix[3][3] = {
        {cos(angle), -sin(angle), 0},
        {sin(angle), cos(angle), 0},
        {0, 0, 1}
       };
    
    GLfloat vet[3][1] = {
        {x},
        {y},
        {1}
    };
    
    GLfloat res[3][1];
    
    matrixVectorMultiply(rotationMatrix, vet, res);
    
    std::cout << "RotationMatrix" << std::endl;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++)
            std::cout << rotationMatrix[i][j] << ", ";
        std::cout << std::endl;
    }
    std::cout << std::endl << std::endl;
    
    std::cout << "Point" << std::endl;
    for(int i = 0; i < 3; i++){
            std::cout << vet[i][0] << ", ";
        std::cout << std::endl;
    }
    std::cout << std::endl << std::endl;
    
    std::cout << "Result:" << std::endl;
    for(int i = 0; i < 3; i++){
            std::cout << res[i][0] << ", ";
        std::cout << std::endl;
    }
    std::cout << std::endl << std::endl;
    
    xOut = res[1][0];
    yOut = res[2][0];
}

Tiro* Robo::Atira()
{
    GLfloat x = 0, y = 0;

    GLfloat baseX, baseY, tipX, tipY;

    y += baseHeight;

    RotatePoint(x, y, (GLfloat) -gTheta1, x, y);

    y += paddleHeight;

    RotatePoint(x, y, (GLfloat) -gTheta2, x, y);

    baseX = x + gX; baseY = y + gY;

    y += paddleHeight;

    RotatePoint(x, y, (GLfloat) -gTheta3, x, y);

    tipX = x + gX; tipY = y + gY;

    GLfloat angle = atan2(tipX-baseX, tipY-baseY);
    
    return new Tiro(x, y, angle);
}
