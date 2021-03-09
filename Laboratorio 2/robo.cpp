#include "robo.h"
#include <math.h>
#include <iostream>
#include <vector>
#define PI 3.14

using namespace std;

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




void matrixMultiply(vector< vector<GLfloat> > mat1,
              vector< vector<GLfloat> > mat2,
              vector< vector<GLfloat> > &res)
{
    int i, j, k;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            res[i][j] = 0;
            for (k = 0; k < 3; k++)
                res[i][j] += mat1[i][k] * mat2[k][j];
        }
    }
}

void matrixVectorMultiply(vector< vector<GLfloat> > mat1,
                          vector< vector<GLfloat> > vet1,
                          vector< vector<GLfloat> > &res)
{
    int i, j, k;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 1; j++) {
            res[i][j] = 0;
            for (k = 0; k < 3; k++){
                cout << i << "," << j << ": " << res[i][j] << " += " << mat1[i][k] << " " << vet1[k][j] << endl;
                res[i][j] += mat1[i][k] * vet1[k][j];
            }
        }
    }
}

void rotate2d(vector< vector<GLfloat> > &mat1, GLfloat angle) {
    GLfloat rad = angle*PI/180;
    vector< vector<GLfloat> > rotationMatrix = {
        {cos(rad), -sin(rad), 0},
        {sin(rad), cos(rad), 0},
        {0, 0, 1}
    };
    matrixMultiply(mat1, rotationMatrix, mat1);
}

void translate2d(vector< vector<GLfloat> > &mat1, GLfloat x, GLfloat y) {
    vector< vector<GLfloat> > translateMatrix = {
        {1, 0, x},
        {0, 1, y},
        {0, 0, 1}
    };
    matrixMultiply(mat1, translateMatrix, mat1);
}

////Funcao auxiliar de rotacao
//void RotatePoint(GLfloat x, GLfloat y, GLfloat angle, GLfloat &xOut, GLfloat &yOut){
//    GLfloat rad = angle*PI/180;
//
//    vector<GLfloat> rotationMatrix = {
//        {cos(rad), -sin(rad), 0},
//        {sin(rad), cos(rad), 0},
//        {0, 0, 1}
//       };
//
//    vector< vector<GLfloat >> vet = {
//        {x},
//        {y},
//        {1}
//    };
//
//    GLfloat res[3][1];
//
//    matrixVectorMultiply(rotationMatrix, vet, res);
//
//    std::cout << "RotationMatrix" << std::endl;
//    for(int i = 0; i < 3; i++){
//        for(int j = 0; j < 3; j++)
//            std::cout << rotationMatrix[i][j] << ", ";
//        std::cout << std::endl;
//    }
//    std::cout << std::endl << std::endl;
//
//    std::cout << "Point" << std::endl;
//    for(int i = 0; i < 3; i++){
//            std::cout << vet[i][0] << ", ";
//        std::cout << std::endl;
//    }
//    std::cout << std::endl << std::endl;
//
//    std::cout << "Result:" << std::endl;
//    for(int i = 0; i < 3; i++){
//            std::cout << res[i][0] << ", ";
//        std::cout << std::endl;
//    }
//    std::cout << std::endl << std::endl;
//
//    xOut = res[0][0];
//    yOut = res[1][0];
//}

Tiro* Robo::Atira()
{
    GLfloat x = 0, y = 0;

    
    vector< vector<GLfloat> > identity = {
        {1,0,0},
        {0,1,0},
        {0,0,1}
    };
    
    vector< vector<GLfloat> > base = {
        {0},
        {0},
        {1}
    };
    
    vector< vector<GLfloat> > tip = {
        {0},
        {0},
        {1}
    };
    
    std::cout << "Point Before" << std::endl;
    for(int i = 0; i < 2; i++){
            std::cout << tip[i][0] << ", ";
        std::cout << std::endl;
    }
    std::cout << std::endl << std::endl;
    
    translate2d(identity, gX, gY);
    translate2d(identity, 0, baseHeight);
    rotate2d(identity, gTheta1);
    translate2d(identity, 0, paddleHeight);
    rotate2d(identity, gTheta2);
    translate2d(identity, 0, paddleHeight);
    rotate2d(identity, gTheta3);
    matrixVectorMultiply(identity, base, base);
    translate2d(identity, 0, paddleHeight);
    matrixVectorMultiply(identity, tip, tip);
    
//
//    std::cout << "Identify" << std::endl;
//    for(int i = 0; i < 3; i++){
//        for(int j = 0; j < 3; j++)
//            std::cout << identity[i][j] << ", ";
//        std::cout << std::endl;
//    }
//    std::cout << std::endl << std::endl;
//
//    matrixVectorMultiply(identity, res, res);
//
//    std::cout << "Point After" << std::endl;
//    for(int i = 0; i < 2; i++){
//            std::cout << res[i][0] << ", ";
//        std::cout << std::endl;
//    }
//    std::cout << std::endl << std::endl;

    
//    GLfloat baseX, baseY, tipX, tipY;
//
//    y += paddleHeight;
//
//    RotatePoint(x, y, -gTheta1, x, y);
//
//    y += paddleHeight;
//
//    RotatePoint(x, y, -gTheta2, x, y);
//
//    baseX = gX - x;
//    baseY = y + gY + baseHeight;
//
//    y += paddleHeight;
//
//    RotatePoint(x, y, - gTheta3, x, y);
//
//
//    tipX = gX - x;
//    tipY = y + gY + baseHeight;
//
//
//
//
//
////
////    baseX = x + gX; baseY = y + gY + baseHeight;
////
//
//
//    tipX = x + gX; tipY = y + gY + baseHeight;
//
    GLfloat angle = atan2(tip[0][0]-tip[0][0], tip[1][0]-tip[1][0]);
    
    return new Tiro(tip[0][0],tip[1][0], angle);
}
