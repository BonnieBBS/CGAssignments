#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

#define KEY_ESCAPE 27

float SCALE = 1;
float X_ANGLE = 0;
float Y_ANGLE = 0;
float Z_ANGLE = 0;
float X = 0;
float Y = 0;
float Z = 0;

#include "myheader.hpp"


void setTexture(std::string fileName, int width, int height)
{
    FILE * fd;
    GLubyte ch;
    int i,j,k;

    int TEX_WIDTH = width;
    int TEX_HEIGHT = height;
    GLubyte texImage[TEX_WIDTH][TEX_HEIGHT][3];
    GLuint texName[1];

    fd = fopen(fileName.c_str(), "r");
    for(i=0; i<TEX_WIDTH; i++)
    {
        for(j=0; j<TEX_HEIGHT; j++)
        {
            for(k=2; k>=0; k--)
            {
                fread(&ch, 1, 1, fd);
                texImage[i][j][k] = (GLubyte) ch;
                //std::cout << texImage[i][j][k] << " ";
            }
            //std::cout << std::endl;
        }
    }
    
    fclose(fd);

    glEnable(GL_TEXTURE_2D);

    glGenTextures( 1, texName);
    glBindTexture( GL_TEXTURE_2D, texName[0] );
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB8,TEX_WIDTH,TEX_HEIGHT,0,GL_RGB,GL_UNSIGNED_BYTE,texImage);
}

void drawBoard()
{
    glBegin(GL_POLYGON);
    //    glTexCoord2f(0.0, 0.0); glVertex3f(0,0.15,0);
    //    glTexCoord2f(0.0, 1.0); glVertex3f(0.25,0,0);
    //    glTexCoord2f(1.0, 1.0); glVertex3f(0.1,-0.5,0);
    //    glTexCoord2f(1.0, 0.0); glVertex3f(-0.1,-0.5,0);
    //    glTexCoord2f(0.0, 0.0); glVertex3f(-0.25,0,0);
    glVertex3f(0,0.15,0);
    glVertex3f(0.25,0,0);
    glVertex3f(0.1,-0.5,0);
    glVertex3f(-0.1,-0.5,0);
    glVertex3f(-0.25,0,0);
    glEnd(); 
}

void drawBoards(int num, float dis)
{
    for(int i=0; i<num; i++)
    {
        glPushMatrix();
        glTranslatef(i*dis, 0, 0);
        drawBoard();
        glPopMatrix();
    }
}

void drawDoor()
{
    glPushMatrix();                   // door
    glTranslatef(0.35,-0.5,1);
    glColor3f(1,0,0);
    glScalef(0.5,1,0.05);
    glutSolidCube(1);
    glPopMatrix();
}
void drawWindow()
{
    glPushMatrix();                   // window
    glTranslatef(-0.4,0.35,1);

    glPushMatrix();
    glColor3f(1,1,1);
    glBegin(GL_POLYGON);
    glVertex3f(0.02,0.25,0.02);
    glVertex3f(-0.02,0.25,0.02);
    glVertex3f(-0.02,-0.25,0.02);
    glVertex3f(0.02,-0.25,0.02);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(0.25,0.02,0.02);
    glVertex3f(0.25,-0.02,0.02);
    glVertex3f(-0.25,-0.02,0.02);
    glVertex3f(-0.25,0.02,0.02);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(-0.25,0.25,0.02);
    glVertex3f(0.25,0.25,0.02);
    glVertex3f(0.25,0.2,0.02);
    glVertex3f(-0.25,0.2,0.02);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(0.25,0.25,0.02);
    glVertex3f(0.2,0.25,0.02);
    glVertex3f(0.2,-0.25,0.02);
    glVertex3f(0.25,-0.25,0.02);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(0.25,-0.25,0.02);
    glVertex3f(0.25,-0.2,0.02);
    glVertex3f(-0.25,-0.2,0.02);
    glVertex3f(-0.25,-0.25,0.02);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(-0.2,-0.25,0.02);
    glVertex3f(-0.2,0.25,0.02);
    glVertex3f(-0.25,0.25,0.02);
    glVertex3f(-0.25,-0.25,0.02);
    glEnd();
    glPopMatrix();

    glColor3f(0,0,1);
    glScalef(1,1,0.05);
    glutSolidCube(0.5);
    //glutSolidTorus(0.45,0.05,4,4);       
    glPopMatrix();

}
void drawRoof()
{
    glPushMatrix();                   // roof
    glColor3f(1,0,0);
    glRotatef(45,0,1,0);
    glRotatef(-90,1,0,0);
    glutSolidCone(1.65,1.5,4,8);
    glPopMatrix();
}
void drawChimney()
{
    glPushMatrix();                   // chimney
    glScalef(1,3,1);
    glColor3f(1,1,0); // yellow 
    glutSolidCube(.25);
}
void drawTexturedChimney()
{
    glPushMatrix();                   // chimney
    glScalef(1,3,1);
    setTexture("small_brick.raw",128,128);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_POLYGON);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.125,0.125,0.1251); 
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.125,0.125,0.1251);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.125,-0.125,0.1251);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.125,-0.125,0.1251);
    glEnd();
    glBegin(GL_POLYGON);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.125,0.125,-0.1251); 
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.125,0.125,-0.1251);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.125,-0.125,-0.1251);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.125,-0.125,-0.1251);
    glEnd();
    glBegin(GL_POLYGON);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.1251,0.125,0.125); 
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.1251,0.125,-0.125);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.1251,-0.125,-0.125);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.1251,-0.125,0.125);
    glEnd();
    glBegin(GL_POLYGON);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.1251,0.125,0.125); 
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.1251,0.125,-0.125);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.1251,-0.125,-0.125);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.1251,-0.125,0.125);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glColor3f(0,0,0); // yellow 
    glutSolidCube(.25);
}
void drawTexturedBuilding()
{
    glPushMatrix();
    setTexture("brick.raw",700,640);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_POLYGON);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1,1,1.0001); 
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1,1,1.0001);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1,-1,1.0001);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1,-1,1.0001);
    glEnd();
    glBegin(GL_POLYGON);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1,1,-1.0001); 
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1,1,-1.0001);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1,-1,-1.0001);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1,-1,-1.0001);
    glEnd();
    glBegin(GL_POLYGON);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0001,1,1); 
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0001,1,-1);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0001,-1,-1);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0001,-1,1);
    glEnd();
    glBegin(GL_POLYGON);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0001,1,1); 
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0001,1,-1);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0001,-1,-1);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0001,-1,1);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glColor3f(1,0.8,0.4);
    glutSolidCube(2);                 // building
    glPopMatrix();
}

void drawBuilding()
{
    glColor3f(1,0.8,0.4);
    glutSolidCube(2);                 // building
}
void drawTexturedGrass()
{
    glPushMatrix();
    setTexture("grass.raw",700,640);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_POLYGON);              // grass land
    glColor3f(0,1,0);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(5,-1,5);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-5,-1,5);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-5,-1,-5);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(5,-1,-5);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}
void drawGrass()
{
    glBegin(GL_POLYGON);              // grass land
    glColor3f(0,1,0);
    glVertex3f(5,-1,5);
    glVertex3f(-5,-1,5);
    glVertex3f(-5,-1,-5);
    glVertex3f(5,-1,-5);
    glEnd();
}
void display1 () {

    /* clear window */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* future matrix manipulations should affect the modelview matrix */
    glMatrixMode(GL_MODELVIEW);

    glScalef(SCALE, SCALE, SCALE);
    glRotatef(Z_ANGLE, 0, 0, 1);
    glRotatef(Y_ANGLE, 0, 1, 0);
    glRotatef(X_ANGLE, 1, 0, 0);
    glTranslatef(0, 0, Z);
    glTranslatef(0, Y, 0);
    glTranslatef(X, 0, 0);

    /* draw scene */
    glPushMatrix();

    glPushMatrix();                   // boards
    glColor3f(1,1,1);
    glTranslatef(0, -0.5, 0);

    glPushMatrix();
    glTranslatef(0, 0, 3.75);
    drawBoards(8,0.5);
    drawBoards(8,-0.5);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslatef(0, 0, 3.75);
    drawBoards(8,0.5);
    drawBoards(8,-0.5);
    glPopMatrix();

    glPushMatrix();
    glRotatef(180, 0, 1, 0);
    glTranslatef(0, 0, 3.75);
    drawBoards(8,0.5);
    drawBoards(8,-0.5);
    glPopMatrix();

    glPushMatrix();
    glRotatef(-90, 0, 1, 0);
    glTranslatef(0, 0, 3.75);
    drawBoards(8,0.5);
    drawBoards(8,-0.5);
    glPopMatrix();
    glPopMatrix();

    drawGrass(); // textured grass

    // house
    glPushMatrix();
    drawBuilding(); // textured building
    drawDoor(); // textured door
    drawWindow();

    glTranslatef(0,1,0);
    drawRoof();  // textured roof
    glTranslatef(.65,0.8,0.15);         
    drawChimney(); // textured chimney
    glPopMatrix();

    glPopMatrix();

    glTranslatef(-1.5, -0.65, 2);

    // car
    glPushMatrix();
    glPushMatrix();                   // body
    glScalef(2,.5,1);
    glColor3f(0,0,1);
    glutSolidCube(.5);
    glPopMatrix();

    glTranslatef(0,0,.25);
    glColor3f(0,0,0);

    glPushMatrix();
    glTranslatef(-.4,-.2,0);
    glutSolidTorus(.05,.1,8,8);       // wheel
    glTranslatef(.8,0,0);
    glutSolidTorus(.05,.1,8,8);       // wheel
    glPopMatrix();

    glTranslatef(0,0,-.5);

    glPushMatrix();
    glTranslatef(-.4,-.2,0);
    glutSolidTorus(.05,.1,8,8);       // wheel
    glTranslatef(.8,0,0);
    glutSolidTorus(.05,.1,8,8);       // wheel
    glPopMatrix();

    glPopMatrix();

    glPopMatrix();

    /* flush drawing routines to the window */
    glFlush();

}

void display2 () {

    /* clear window */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* future matrix manipulations should affect the modelview matrix */
    glMatrixMode(GL_MODELVIEW);

    glScalef(SCALE, SCALE, SCALE);
    glRotatef(Z_ANGLE, 0, 0, 1);
    glRotatef(Y_ANGLE, 0, 1, 0);
    glRotatef(X_ANGLE, 1, 0, 0);
    glTranslatef(0, 0, Z);
    glTranslatef(0, Y, 0);
    glTranslatef(X, 0, 0);

    /* draw scene */
    glPushMatrix();

    glPushMatrix();                   // boards
    glColor3f(1,1,1);
    glTranslatef(0, -0.5, 0);

    glPushMatrix();
    glTranslatef(0, 0, 3.75);
    drawBoards(8,0.5);
    drawBoards(8,-0.5);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslatef(0, 0, 3.75);
    drawBoards(8,0.5);
    drawBoards(8,-0.5);
    glPopMatrix();

    glPushMatrix();
    glRotatef(180, 0, 1, 0);
    glTranslatef(0, 0, 3.75);
    drawBoards(8,0.5);
    drawBoards(8,-0.5);
    glPopMatrix();

    glPushMatrix();
    glRotatef(-90, 0, 1, 0);
    glTranslatef(0, 0, 3.75);
    drawBoards(8,0.5);
    drawBoards(8,-0.5);
    glPopMatrix();
    glPopMatrix();

    glBegin(GL_POLYGON);              // grass land
    glColor3f(0,1,0);
    glVertex3f(5,-1,5);
    glVertex3f(-5,-1,5);
    glVertex3f(-5,-1,-5);
    glVertex3f(5,-1,-5);
    glEnd();

    // house
    glPushMatrix();
    glColor3f(1,0.8,0.4);
    glutWireCube(2);                 // building

    drawDoor();
    drawWindow();

    glTranslatef(0,1,0);
    drawWiredRoof();
    glTranslatef(.65,0.8,0.15);         
    drawWiredChimney();
    glPopMatrix();

    glPopMatrix();

    glTranslatef(-1.5, -0.65, 2);

    // car
    glPushMatrix();
    glPushMatrix();                   // body
    glScalef(2,.5,1);
    glColor3f(0,0,1);
    glutWireCube(.5);
    glPopMatrix();

    glTranslatef(0,0,.25);
    glColor3f(0,0,0);

    glPushMatrix();
    glTranslatef(-.4,-.2,0);
    glutWireTorus(.05,.1,8,8);       // wheel
    glTranslatef(.8,0,0);
    glutWireTorus(.05,.1,8,8);       // wheel
    glPopMatrix();

    glTranslatef(0,0,-.5);

    glPushMatrix();
    glTranslatef(-.4,-.2,0);
    glutWireTorus(.05,.1,8,8);       // wheel
    glTranslatef(.8,0,0);
    glutWireTorus(.05,.1,8,8);       // wheel
    glPopMatrix();

    glPopMatrix();

    glPopMatrix();

    /* flush drawing routines to the window */
    glFlush();

}

void display3 () {

    /* clear window */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* future matrix manipulations should affect the modelview matrix */
    glMatrixMode(GL_MODELVIEW);

    glScalef(SCALE, SCALE, SCALE);
    glRotatef(Z_ANGLE, 0, 0, 1);
    glRotatef(Y_ANGLE, 0, 1, 0);
    glRotatef(X_ANGLE, 1, 0, 0);
    glTranslatef(0, 0, Z);
    glTranslatef(0, Y, 0);
    glTranslatef(X, 0, 0);

    /* draw scene */
    glPushMatrix();

    glPushMatrix();                   // boards
    glColor3f(1,1,1);
    glTranslatef(0, -0.5, 0);

    glPushMatrix();
    glTranslatef(0, 0, 3.75);
    drawBoards(8,0.5);
    drawBoards(8,-0.5);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslatef(0, 0, 3.75);
    drawBoards(8,0.5);
    drawBoards(8,-0.5);
    glPopMatrix();

    glPushMatrix();
    glRotatef(180, 0, 1, 0);
    glTranslatef(0, 0, 3.75);
    drawBoards(8,0.5);
    drawBoards(8,-0.5);
    glPopMatrix();

    glPushMatrix();
    glRotatef(-90, 0, 1, 0);
    glTranslatef(0, 0, 3.75);
    drawBoards(8,0.5);
    drawBoards(8,-0.5);
    glPopMatrix();
    glPopMatrix();

    drawTexturedGrass(); // textured grass

    // house
    glPushMatrix();
    drawTexturedBuilding(); // textured building
    drawDoor(); // textured door
    drawWindow();

    glTranslatef(0,1,0);
    drawRoof();  // textured roof
    glTranslatef(.65,0.8,0.15);         
    drawTexturedChimney(); // textured chimney
    glPopMatrix();

    glPopMatrix();

    glTranslatef(-1.5, -0.65, 2);

    // car
    glPushMatrix();
    glPushMatrix();                   // body
    glScalef(2,.5,1);
    glColor3f(0,0,1);
    glutSolidCube(.5);
    glPopMatrix();

    glTranslatef(0,0,.25);
    glColor3f(0,0,0);

    glPushMatrix();
    glTranslatef(-.4,-.2,0);
    glutSolidTorus(.05,.1,8,8);       // wheel
    glTranslatef(.8,0,0);
    glutSolidTorus(.05,.1,8,8);       // wheel
    glPopMatrix();

    glTranslatef(0,0,-.5);

    glPushMatrix();
    glTranslatef(-.4,-.2,0);
    glutSolidTorus(.05,.1,8,8);       // wheel
    glTranslatef(.8,0,0);
    glutSolidTorus(.05,.1,8,8);       // wheel
    glPopMatrix();

    glPopMatrix();

    glPopMatrix();

    /* flush drawing routines to the window */
    glFlush();

}

void reshape ( int width, int height ) {

    /* define the viewport transformation */
    glViewport(0,0,width,height);
}

void keyboard ( unsigned char key, int mousePositionX, int mousePositionY )
{
    switch ( key )
    {
        case KEY_ESCAPE:
            exit ( 0 );
            break;
        case 'q':
            X_ANGLE = 1;
            Y_ANGLE = 0;
            Z_ANGLE = 0;
            SCALE = 1;
            X = 0;
            Y = 0;
            Z = 0;
            break;
        case 'w':
            X_ANGLE = -1;
            Y_ANGLE = 0;
            Z_ANGLE = 0;
            SCALE = 1;
            X = 0;
            Y = 0;
            Z = 0;
            break;
        case 'a':
            X_ANGLE = 0;
            Y_ANGLE = 1;
            Z_ANGLE = 0;
            SCALE = 1;
            X = 0;
            Y = 0;
            Z = 0;
            break;
        case 's':
            X_ANGLE = 0;
            Y_ANGLE = -1;
            Z_ANGLE = 0;
            SCALE = 1;
            X = 0;
            Y = 0;
            Z = 0;
            break;
        case 'x':
            X_ANGLE = 0;
            Y_ANGLE = 0;
            Z_ANGLE = 1;
            SCALE = 1;
            X = 0;
            Y = 0;
            Z = 0;
            break;
        case 'z':
            X_ANGLE = 0;
            Y_ANGLE = 0;
            Z_ANGLE = -1;
            SCALE = 1;
            X = 0;
            Y = 0;
            Z = 0;
            break;
        case 'o':
            X_ANGLE = 0;
            Y_ANGLE = 0;
            Z_ANGLE = 0;
            SCALE = 1;
            X = 0.2;
            Y = 0;
            Z = 0;
            break;
        case 'p':
            X_ANGLE = 0;
            Y_ANGLE = 0;
            Z_ANGLE = 0;
            SCALE = 1;
            X = -0.2;
            Y = 0;
            Z = 0;
            break;
        case 'k':
            X_ANGLE = 0;
            Y_ANGLE = 0;
            Z_ANGLE = 0;
            SCALE = 1;
            X = 0;
            Y = 0.2;
            Z = 0;
            break;
        case 'l':
            X_ANGLE = 0;
            Y_ANGLE = 0;
            Z_ANGLE = 0;
            SCALE = 1;
            X = 0;
            Y = -0.2;
            Z = 0;
            break;
        case 'n':
            X_ANGLE = 0;
            Y_ANGLE = 0;
            Z_ANGLE = 0;
            SCALE = 1;
            X = 0;
            Y = 0;
            Z = 0.2;
            break;
        case 'm':
            X_ANGLE = 0;
            Y_ANGLE = 0;
            Z_ANGLE = 0;
            SCALE = 1;
            X = 0;
            Y = 0;
            Z = -0.2;
            break;
        default:
            std::cout << "default\n";
            break;
    }
    glutPostRedisplay();
}

void special(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_DOWN:
            SCALE = 0.9;
            X_ANGLE = 0;
            Y_ANGLE = 0;
            Z_ANGLE = 0;
            X = 0;
            Y = 0;
            Z = 0;
            break;
        case GLUT_KEY_UP:
            SCALE = 1.1;
            X_ANGLE = 0;
            Y_ANGLE = 0;
            Z_ANGLE = 0;
            X = 0;
            Y = 0;
            Z = 0;
            break;
    }
    glutPostRedisplay();
}

void AnimateScene(void)
{
    SCALE = 1;
    X_ANGLE = 0;
    Y_ANGLE = 0.2;
    Z_ANGLE = 0;
    X = 0;
    Y = 0;
    Z = 0;
    glutPostRedisplay();
}
bool mark = true;
void MouseFunction(int button, int state, int x, int y)
{
    if(state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
    {
        if(mark)
            glutIdleFunc(NULL);
        else
            glutIdleFunc(AnimateScene);
        mark = !mark;
    }
}

void mymenu(int value)
{
    if(value == 1)
    {
        glutIdleFunc (AnimateScene);
        //glClear(GL_COLOR_BUFFER_BIT);
        //glFlush();
    }
    if(value == 2)
        glutIdleFunc (NULL);
    if(value == 3)
        glutDisplayFunc(display2);
    if(value == 4)
        glutDisplayFunc(display1);
    if(value == 5)
        glutDisplayFunc(display3);
    if(value == 6)
        exit(0);
}

int main ( int argc, char * argv[] ) {

    /* initialize GLUT, using any commandline parameters passed to the 
     *        program */
    glutInit(&argc,argv);

    /* setup the size, position, and display mode for new windows */
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);

    /* create and set up a window */
    glutCreateWindow("hello, my house!");
    glClearColor(0.24, 0.6, 0.66, 1.0);
    //glClearColor(1, 1, 1, 1.0);

    //texName = loadTextureRAW("bricks.jpg",true);

    /* set up depth-buffering */
    glEnable(GL_DEPTH_TEST);

    /* turn on default lighting */
    GLfloat amb_light[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat diffuse[] = { 0.6, 0.6, 0.6, 1 };
    GLfloat specular[] = { 0.7, 0.7, 0.3, 1 };
 glLightModelfv( GL_LIGHT_MODEL_AMBIENT, amb_light );
 glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuse );
 glLightfv( GL_LIGHT0, GL_SPECULAR, specular );
 glEnable( GL_LIGHT0 );
 glEnable( GL_COLOR_MATERIAL );
 glEnable(GL_LIGHTING);
 glEnable(GL_LIGHT0);

    /* define the projection transformation */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40,1,4,20);

    /* define the viewing transformation */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5.0,5.0,5.0,0.0,0.0,0.0,0.0,1.0,0.0);

    glutMouseFunc(MouseFunction);
    glutKeyboardFunc( keyboard );
    glutSpecialFunc( special );
    glutDisplayFunc(display1);
    glutReshapeFunc(reshape);
    glutIdleFunc (AnimateScene);

    int id = glutCreateMenu(mymenu);
    glutAddMenuEntry("Spin", 1);
    glutAddMenuEntry("Still", 2);
    glutAddMenuEntry("Wire", 3);
    glutAddMenuEntry("Solid", 4);
    glutAddMenuEntry("Textured", 5);
    glutAddMenuEntry("Exit", 6);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    /* tell GLUT to wait for events */
    glutMainLoop();
}

