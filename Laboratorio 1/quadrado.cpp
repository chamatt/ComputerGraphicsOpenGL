#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#define TAMANHO_JANELA 500

class Color
{
public:
   float r;
   float g;
   float b;

   Color(float r, float g, float b)
   {
      this->r = r;
      this->g = g;
      this->b = b;
   }
};

class Square
{
public:
   float x = 0;
   float y = 0;
   float xSize = 0.25;
   float ySize = 0.25;

   float anchorX = 0;
   float anchorY = 0;

   bool isDragging = false;

   Square() {}

   Square(float initialX, float initialY, float initialXSize, float initialYSize)
   {
      x = initialX;
      y = initialY;
      xSize = initialXSize;
      ySize = initialYSize;
   }

   bool isWithin(float cx, float cy)
   {
      return cx >= x && cx <= (x + xSize) && cy >= y && cy <= (y + ySize);
   }

   void setIsDragging(bool isDragging)
   {
      this->isDragging = isDragging;
   }

   void setAnchor(float anchorX, float anchorY)
   {
      this->anchorX = anchorX - x;
      this->anchorY = anchorY - y;
   }

   void moveAnchorTo(float destX, float destY)
   {
      x = destX - anchorX;
      y = destY - anchorY;
   }

   void moveCenterTo(float destX, float destY)
   {
      x = destX - (xSize / 2);
      y = destY - (ySize / 2);
   }

   void handleDirectionChange(int xDirection, float yDirection)
   {
      float xVelocity = 0.01, yVelocity = 0.01;
      x += (xDirection * xVelocity);
      y += (yDirection * yVelocity);
   }

   void setColor(Color color)
   {
      glColor3f(color.r, color.g, color.b);
   }

   void draw()
   {
      glBegin(GL_POLYGON);
      glVertex3f(x, y, 0.0);
      glVertex3f(x + xSize, y, 0.0);
      glVertex3f(x + xSize, y + ySize, 0.0);
      glVertex3f(x, y + ySize, 0.0);
      glEnd();
   }
};

Square mainSquare = Square();

int keyStatus[256];

enum MouseButton
{
   LEFT_MOUSE_BUTTON = 0,
   RIGHT_MOUSE_BUTTON = 1,
};

class MouseStatus
{
public:
   bool isPressed = false;

   MouseStatus() {}

   void setIsPressed(bool pressed)
   {
      this->isPressed = pressed;
   }
};

class Mouse
{
public:
   MouseStatus leftButton;
   float x = 0;
   float y = 0;

   Mouse() {}

   Mouse(float x, float y)
   {
      this->x = x;
      this->y = y;
   }

   void setPosition(float x, float y)
   {
      this->x = x;
      this->y = y;
   }
};

Mouse mouse;

void keyUp(unsigned char key, int x, int y)
{
   keyStatus[key] = 0;
}

void keyPress(unsigned char key, int x, int y)
{
   keyStatus[key] = 1;
   glutPostRedisplay();
}

void handleKeyboardMovement()
{
   if (keyStatus[(int)('w')])
      mainSquare.handleDirectionChange(0, 1);
   if (keyStatus[(int)('a')])
      mainSquare.handleDirectionChange(-1, 0);
   if (keyStatus[(int)('s')])
      mainSquare.handleDirectionChange(0, -1);
   if (keyStatus[(int)('d')])
      mainSquare.handleDirectionChange(1, 0);
}

void handleMouseDrag()
{
   if (mouse.leftButton.isPressed && mainSquare.isDragging)
   {
      mainSquare.moveAnchorTo(mouse.x, mouse.y);
   }
}

void idle()
{
   handleKeyboardMovement();
   handleMouseDrag();
   glutPostRedisplay();
}

void mouseEvent(int button, int state, int x, int y)
{
   y = -y + TAMANHO_JANELA;
   if (button == GLUT_LEFT_BUTTON)
   {
      if (state == GLUT_UP)
      {
         mouse.leftButton.setIsPressed(false);
         mainSquare.setIsDragging(false);
      }
      else if (state == GLUT_DOWN)
      {
         mouse.leftButton.setIsPressed(true);
         if (mainSquare.isWithin(mouse.x, mouse.y))
         {
            mainSquare.setIsDragging(true);
            mainSquare.setAnchor(mouse.x, mouse.y);
         }
         else
         {
            mainSquare.setIsDragging(false);
         }
      }
   }
   glutPostRedisplay();
}

void mouseMovement(int x, int y)
{
   y = -y + TAMANHO_JANELA;
   mouse.setPosition((float)x / TAMANHO_JANELA, (float)y / TAMANHO_JANELA);
   glutPostRedisplay();
}

void display(void)
{
   /* Limpar todos os pixels  */
   glClear(GL_COLOR_BUFFER_BIT);

   /* Define cor dos vértices com os valores R, G e B variando de 0.0 a 1.0 */
   mainSquare.setColor(Color(1.0, 1.0, 1.0));
   /* Desenhar um polígono branco (retângulo) */
   mainSquare.draw();

   /* Desenhar no frame buffer! */
   glutSwapBuffers(); //Funcao apropriada para janela double buffer
}

void init(void)
{
   /* selecionar cor de fundo (preto) */
   glClearColor(0.0, 0.0, 0.0, 0.0);

   /* inicializar sistema de visualizacao */
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

   glutKeyboardFunc(keyPress);
   glutKeyboardUpFunc(keyUp);
   glutIdleFunc(idle);
   glutMouseFunc(mouseEvent);
   glutPassiveMotionFunc(mouseMovement);
   glutMotionFunc(mouseMovement);
}

int main(int argc, char **argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(TAMANHO_JANELA, TAMANHO_JANELA);
   glutInitWindowPosition(100, 100);
   glutCreateWindow("Quadrado");
   init();
   glutDisplayFunc(display);

   glutMainLoop();

   return 0;
}
