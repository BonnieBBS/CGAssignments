#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>

#define KEY_ESCAPE 27

float SCALE = 1;
float HORIZON_ANGLE = 0;
float VERTICLE_ANGLE = 0;
float HEIGHT = 0;
float WIDTH = 0;

void drawBoard()
{
    glBegin(GL_POLYGON);
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

void display () {

    /* clear window */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* future matrix manipulations should affect the modelview matrix */
    glMatrixMode(GL_MODELVIEW);

    glScalef(SCALE, SCALE, SCALE);
    glRotatef(HORIZON_ANGLE, 0, 1, 0);
    glRotatef(VERTICLE_ANGLE, 1, 0, 0);
    glTranslatef(0, HEIGHT, 0);
    glTranslatef(WIDTH, 0, 0);

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
    glutSolidCube(2);                 // building

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

    glPushMatrix();                   // door
    glTranslatef(0.35,-0.5,1);
    glColor3f(1,0,0);
    glScalef(0.5,1,0.05);
    glutSolidCube(1);
    glPopMatrix();

    glTranslatef(0,1,0);
    glPushMatrix();                   // roof
    glColor3f(1,0,0);
    glRotatef(45,0,1,0);
    glRotatef(-90,1,0,0);
    glutSolidCone(1.5,1,4,8);
    glPopMatrix();

    glTranslatef(.75,.5,-.75);         
    glPushMatrix();                   // chimney
    glScalef(1,3,1);
    glColor3f(1,1,0); // yellow 
    glutSolidCube(.25);

    glPopMatrix();

    glPopMatrix();

    glTranslatef(0,-.65,2);

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
        case '+':
        case '=':
            SCALE = 1.1;
            HORIZON_ANGLE = 0;
            VERTICLE_ANGLE = 0;
            HEIGHT = 0;
            WIDTH = 0;
            break;
        case '_':
        case '-':
            SCALE = 0.9;
            HORIZON_ANGLE = 0;
            VERTICLE_ANGLE = 0;
            HEIGHT = 0;
            WIDTH = 0;
            break;
        case 'w':
            HORIZON_ANGLE = 0;
            VERTICLE_ANGLE = 1;
            SCALE = 1;
            HEIGHT = 0;
            WIDTH = 0;
            break;
        case 's':
            HORIZON_ANGLE = 0;
            VERTICLE_ANGLE = -1;
            SCALE = 1;
            HEIGHT = 0;
            WIDTH = 0;
            break;
        case 'd':
            HORIZON_ANGLE = 1;
            VERTICLE_ANGLE = 0;
            SCALE = 1;
            HEIGHT = 0;
            WIDTH = 0;
            break;
        case 'a':
            HORIZON_ANGLE = -1;
            VERTICLE_ANGLE = 0;
            SCALE = 1;
            HEIGHT = 0;
            WIDTH = 0;
            break;
        case 'o':
            HEIGHT = 0.2;
            WIDTH = 0;
            HORIZON_ANGLE = 0;
            VERTICLE_ANGLE =0;
            SCALE = 1;
            break;
        case 'l':
            HEIGHT = -0.2;
            WIDTH = 0;
            HORIZON_ANGLE = 0;
            VERTICLE_ANGLE = 0;
            SCALE = 1;
            break;
        case 'k':
            HEIGHT = 0;
            WIDTH = 0.2;
            HORIZON_ANGLE = 0;
            VERTICLE_ANGLE =0;
            SCALE = 1;
            break;
        case ';':
            HEIGHT = 0;
            WIDTH = -0.2;
            HORIZON_ANGLE = 0;
            VERTICLE_ANGLE = 0;
            SCALE = 1;
            break;
        default:
            std::cout << "default\n";
            break;
    }
    glutPostRedisplay();
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

    /* set up depth-buffering */
    glEnable(GL_DEPTH_TEST);

    /* turn on default lighting */
    GLfloat amb_light[] = { 0.1, 0.1, 0.1, 1.0 };
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

    glutKeyboardFunc( keyboard );
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    /* tell GLUT to wait for events */
    glutMainLoop();
}

