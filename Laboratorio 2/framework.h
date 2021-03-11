//#include "robo.h"
//#include <math.h>
//#include <iostream>
//#include <vector>
//
//class Point2D {
//    public:
//        GLfloat x;
//        GLfloat y;
//
//        Point2D(GLfloat x, GLfloat y){
//            this->x = x;
//            this->y = y;
//        };
//};
//
//class Transformation {
//    private:
//        bool shouldLog = false;
//        
//        void log() {
//            if(shouldLog) {
//                cout << "Matrix:" << endl;
//                for(auto c : this->matrix) {
//                    for(auto b : c) {
//                        cout << b << ",";
//                    }
//                    cout << endl;
//                }
//                cout << endl;
//            }
//        }
//        
//        void logTranslate(GLfloat x, GLfloat y) {
//            if(shouldLog){
//                cout << "Translate: " << x << ", " << y << endl;
//                this->log();
//            }
//        }
//    
//        void logRotate(GLfloat angle) {
//            if(shouldLog){
//                cout << "Rotate: " << angle << endl;
//                this->log();
//            }
//        }
//            
//    
//        void matrixMultiply(vector< vector<GLfloat> > mat2)
//        {
//            vector< vector<GLfloat> > mat1 = this->matrix;
//            
//            int i, j, k;
//            for (i = 0; i < 3; i++) {
//                for (j = 0; j < 3; j++) {
//                    this->matrix[i][j] = 0;
//                    for (k = 0; k < 3; k++)
//                        this->matrix[i][j] += mat1[i][k] * mat2[k][j];
//                }
//            }
//            
//           
//        }
//
//        void matrixVectorMultiply(vector< vector<GLfloat> > vet1,
//                                  vector< vector<GLfloat> > &res)
//        {
//            int i, j, k;
//            for (i = 0; i < 3; i++) {
//                for (j = 0; j < 1; j++) {
//                    res[i][j] = 0;
//                    for (k = 0; k < 3; k++){
//                        res[i][j] += this->matrix[i][k] * vet1[k][j];
//                    }
//                }
//            }
//        }
//
//    public:
//        vector< vector<GLfloat> > matrix;
//
//        vector< vector<GLfloat> > getIdentity() {
//            vector< vector<GLfloat> > identity = {
//                {1,0,0},
//                {0,1,0},
//                {0,0,1}
//            };
//
//            return identity;
//        }
//
//        Transformation(){
//            this->matrix = this->getIdentity();
//            this->log();
//        };
//
//        void translate2d(GLfloat x, GLfloat y) {
//            vector< vector<GLfloat> > translateMatrix = {
//                {1, 0, x},
//                {0, 1, y},
//                {0, 0, 1}
//            };
//            matrixMultiply(translateMatrix);
//            this->logTranslate(x, y);
//        }
//
//        void rotate2d(GLfloat angle) {
//            GLfloat rad = angle*PI/180;
//            vector< vector<GLfloat> > rotationMatrix = {
//                {cos(rad), -sin(rad), 0},
//                {sin(rad), cos(rad), 0},
//                {0, 0, 1}
//            };
//            matrixMultiply(rotationMatrix);
//            this->logRotate(angle);
//        }
//
//        void apply(Point2D* point) {
//            vector< vector<GLfloat> > vet = {
//                {point->x},
//                {point->y},
//                {1}
//            };
//            
//            matrixVectorMultiply(vet, vet);
//
//            point->x =vet[0][0];
//            point->y =vet[1][0];
//        }
//    
//    void logMode(bool state) {
//        this->shouldLog = state;
//    }
//};
