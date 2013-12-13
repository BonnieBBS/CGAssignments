void drawWiredDoor()
{
    glPushMatrix();                   // door
    glTranslatef(0.35,-0.5,1);
    glColor3f(1,0,0);
    glScalef(0.5,1,0.05);
    glutWireCube(1);
    glPopMatrix();
}
void drawWiredTexturedDoor()
{
    glPushMatrix();                   // door
    glTranslatef(0.35,-0.5,1);
    glScalef(0.5,1,0.05);
    glPushMatrix();
    //glEnable(GL_TEXTURE_2D);
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    //glBindTexture(GL_TEXTURE_2D, texName);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5,0.5,0.51);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5,0.5,0.51);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5,-0.5,0.51);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5,-0.5,0.51);
    glEnd();
    glutWireCube(1);
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}
void drawWiredWindow()
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
    glutWireCube(0.5);
    //glutWireTorus(0.45,0.05,4,4);       
    glPopMatrix();

}

void drawWiredRoof()
{
    glPushMatrix();                   // roof
    glColor3f(1,0,0);
    glRotatef(45,0,1,0);
    glRotatef(-90,1,0,0);
    glutWireCone(1.65,1.5,4,8);
    glPopMatrix();
}
void drawWiredChimney()
{
    glPushMatrix();                   // chimney
    glScalef(1,3,1);
    glColor3f(1,1,0); // yellow 
    glutWireCube(.25);
}
