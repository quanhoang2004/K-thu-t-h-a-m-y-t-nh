#include "glut.h"
#include <cmath>

float cameraX = 0.0f, cameraZ = 8.0f;
bool lightOn = true;
float doorAngle = 0.0f;

void drawCube(float r, float g, float b, float sx, float sy, float sz, float tx, float ty, float tz) {
    glPushMatrix();
    glColor3f(r, g, b);
    glTranslatef(tx, ty, tz);
    glScalef(sx, sy, sz);
    glutSolidCube(1.0);
    glPopMatrix();
}

void setupLighting() {
    if (lightOn) {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);

        GLfloat ambient[] = { 0.3f, 0.3f, 0.0f, 1.0f };
        GLfloat diffuse[] = { 1.0f, 0.9f, 0.4f, 1.0f };
        GLfloat specular[] = { 1.0f, 0.9f, 0.3f, 1.0f };
        GLfloat position[] = { 0.0f, 5.0f, 0.0f, 1.0f };

        glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
        glLightfv(GL_LIGHT0, GL_POSITION, position);

        glEnable(GL_COLOR_MATERIAL);
        glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
        glShadeModel(GL_SMOOTH);
    }
    else {
        glDisable(GL_LIGHTING);
    }
}

void drawDoor() {
    glPushMatrix();
    glTranslatef(0.0f, 1.0f, 4.01f);
    glRotatef(doorAngle, 0.0f, 1.0f, 0.0f);
    drawCube(0.4f, 0.2f, 0.1f, 1.0f, 2.0f, 0.1f, -0.5f, 0.0f, 0.0f);
    glPopMatrix();
}

void drawWalls() {
    float h = 2.5f;
    drawCube(0.3f, 0.3f, 0.3f, 0.2f, h, 8.0f, -4.0f, h / 2, 0.0f);
    drawCube(0.3f, 0.3f, 0.3f, 0.2f, h, 8.0f, 4.0f, h / 2, 0.0f);
    drawCube(0.3f, 0.3f, 0.3f, 8.0f, h, 0.2f, 0.0f, h / 2, -4.0f);
    drawCube(0.3f, 0.3f, 0.3f, 3.0f, h, 0.2f, -2.5f, h / 2, 4.0f);
    drawCube(0.3f, 0.3f, 0.3f, 3.0f, h, 0.2f, 2.5f, h / 2, 4.0f);
}

void drawRoof() {
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_TRIANGLES);
    glVertex3f(-4.0f, 2.5f, -4.0f);
    glVertex3f(0.0f, 4.5f, -4.0f);
    glVertex3f(4.0f, 2.5f, -4.0f);
    glVertex3f(-4.0f, 2.5f, 4.0f);
    glVertex3f(0.0f, 4.5f, 4.0f);
    glVertex3f(4.0f, 2.5f, 4.0f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-4.0f, 2.5f, -4.0f);
    glVertex3f(0.0f, 4.5f, -4.0f);
    glVertex3f(0.0f, 4.5f, 4.0f);
    glVertex3f(-4.0f, 2.5f, 4.0f);
    glVertex3f(0.0f, 4.5f, -4.0f);
    glVertex3f(4.0f, 2.5f, -4.0f);
    glVertex3f(4.0f, 2.5f, 4.0f);
    glVertex3f(0.0f, 4.5f, 4.0f);
    glEnd();
}

void drawFurniture() {
    drawCube(0.5f, 0.3f, 0.2f, 2.0f, 0.4f, 1.2f, 2.0f, 0.2f, -2.0f);  // bàn
    drawCube(0.6f, 0.4f, 0.2f, 0.5f, 1.5f, 0.5f, 1.0f, 0.75f, -2.0f); // ghế
    drawCube(0.2f, 0.2f, 0.8f, 1.5f, 0.8f, 0.1f, -2.0f, 1.2f, -2.5f); // TV
    drawCube(0.4f, 0.2f, 0.6f, 2.0f, 0.5f, 1.5f, -2.0f, 0.3f, 2.0f);  // giường
    drawCube(0.3f, 0.2f, 0.2f, 1.0f, 2.0f, 0.5f, 3.0f, 1.0f, 2.5f);   // tủ
}

void drawScene() {
    drawCube(0.2f, 0.2f, 0.2f, 8.0f, 0.1f, 8.0f, 0.0f, -0.05f, 0.0f); // nền
    drawFurniture();
    drawWalls();
    drawDoor();
    drawRoof();
}

void updateDoor() {
    float dist = sqrt((cameraX) * (cameraX)+(cameraZ - 4.0f) * (cameraZ - 4.0f));
    if (dist < 3.0f) {
        if (doorAngle < 90.0f) doorAngle += 2.0f;
    }
    else {
        if (doorAngle > 0.0f) doorAngle -= 2.0f;
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(cameraX, 2.0f, cameraZ, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    setupLighting();
    updateDoor();
    drawScene();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    float aspect = (float)w / h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, aspect, 1.0f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(int key, int x, int y) {
    const float speed = 0.3f;
    if (key == GLUT_KEY_UP) cameraZ -= speed;
    if (key == GLUT_KEY_DOWN) cameraZ += speed;
    if (key == GLUT_KEY_LEFT) cameraX -= speed;
    if (key == GLUT_KEY_RIGHT) cameraX += speed;
    glutPostRedisplay();
}

void keyboardNormal(unsigned char key, int x, int y) {
    if (key == 'l' || key == 'L') {
        lightOn = !lightOn;
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Nha mot tang voi noi that, cua tu dong, va den vang");

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(keyboard);
    glutKeyboardFunc(keyboardNormal);
    glutIdleFunc(display);

    glutMainLoop();
    return 0;
}