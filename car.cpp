#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <iostream>
#include <string>
// SFML
#include "SFML/Audio.hpp"

#define PI 3.1416

#define MAX 15
#define MIN 5

auto timeUpdate = 100;

int start = 0;
int gv = 0;

int Hour = 0;
int Minute = 0;
int Second = 0;

GLfloat top = 27.0f;
GLfloat oppoY = 0.0f;
GLfloat oppoX = 0.0f;
GLfloat oppo2Y = 0.0f;
GLfloat oppo2X = 0.0f;

GLfloat oppo3Y = 0.0f;
GLfloat oppo3X = 0.0f;
GLfloat positionx = 0.0f;

auto score = 0;

// For Display TEXT
const auto font1 = GLUT_BITMAP_TIMES_ROMAN_24;
const auto font2 = GLUT_BITMAP_HELVETICA_18;
const auto font3 = GLUT_BITMAP_8_BY_13;
const auto font = GLUT_BITMAP_8_BY_13;

char s[30];
void renderBitmapString(float x, float y, void* font, const char* string)
{
    const char* c;
    glRasterPos2f(x, y);
    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void move(int n)
{
    time_t Now = time(nullptr);
    // struct tm
    struct tm* DateTime = localtime(&Now);

    Hour = DateTime->tm_hour;
    Minute = DateTime->tm_min;
    Second = DateTime->tm_sec;

    glutPostRedisplay();
    glutTimerFunc(1000, move, n);
}

void processKeys(unsigned char key, int x, int y)
{
    switch (key) {
    case ' ':
        if (start == 0) {
            start = 1;
            gv = 0;
            score = 0;
            timeUpdate = 100;

            top = 27.0f;
            oppoY = 0.0f;
            oppoX = 0.0f;
            oppo2Y = 0.0f;
            oppo2X = 0.0f;

            oppo3Y = 0.0f;
            oppo3X = 0.0f;
            positionx = 0.0f;
        }
        break;

    case 27:
        exit(0);
        break;
    default:
        break;
    }
}

void dataInfo()
{
    //Print Score
    char buffer[50];
    sprintf(buffer, "SCORE: %d", score);
    glColor3ub(204, 204, 255);
    renderBitmapString(9.5, 15, (void*)font, buffer);

    //Speed Print
    char buffer1[50];
    sprintf(buffer1, "SPEED:%d m/s", (timeUpdate - 200) > 0 ? (timeUpdate - 200) : abs((timeUpdate - 200)));
    glColor3ub(169, 169, 169);
    renderBitmapString(9, 15 - 2, (void*)font, buffer1);

    char buffertime[50];
    sprintf(buffertime, "Clock %d:%d:%d", Hour, Minute, Second);
    glColor3ub(169, 169, 169);
    renderBitmapString(9, 15 - 5, (void*)font, buffertime);

    char buffer2[50];
    sprintf(buffer2, "Drive Safe");
    glColor3f(0.400, 1.000, 0.600);
    renderBitmapString(9.5, -10, (void*)font, buffer2);
}

void tree()
{
    glColor3f(0.133, 0.545, 0.133);
    glBegin(GL_TRIANGLES);
    glVertex3d(-13, 11, 0);
    glVertex3d(-12, 13, 0);
    glVertex3d(-11, 11, 0);
    glEnd();
    glColor3f(0.971, 0.752, 0.429);
    glBegin(GL_TRIANGLES);
    glVertex3d(-12, 11, 0);
    glVertex3d(-11.5, 8, 0);
    glVertex3d(-12.5, 8, 0);
    glEnd();

    glPushMatrix();
    glTranslatef(-1, -17, 0);
    glColor3f(0.133, 0.545, 0.133);
    glBegin(GL_TRIANGLES);
    glVertex3d(-13, 11, 0);
    glVertex3d(-12, 13, 0);
    glVertex3d(-11, 11, 0);
    glEnd();
    glColor3f(0.971, 0.752, 0.429);
    glBegin(GL_TRIANGLES);
    glVertex3d(-12, 11, 0);
    glVertex3d(-11.5, 8, 0);
    glVertex3d(-12.5, 8, 0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1, -16, 0);
    glColor3f(0.133, 0.545, 0.133);
    glBegin(GL_TRIANGLES);
    glVertex3d(-13, 11, 0);
    glVertex3d(-12, 13, 0);
    glVertex3d(-11, 11, 0);
    glEnd();
    glPopMatrix();
}

class Point {
public:
    float x;
    float y;
    Point()
    {
    }

    Point(float X, float Y)
    {
        this->x = X;
        this->y = Y;
    }
};

class Opponent {
public:
    Point A;
    Point B;
    Point C;
    Point D;

    std::string name;
    Opponent()
    {
    }

    Opponent(Point& a, Point& b, Point& c, Point& d,std::string name)
    {
        this->A = a;
        this->B = b;
        this->C = c;
        this->D = d;


        this->name = name;
    }

    void oppocarDraw(int tx, int ty, int r, int g, int b)
    {
        glPushMatrix();
        glTranslatef(tx, ty, 0.0f);
        glColor3ub(r, g, b);
        glBegin(GL_QUADS);
        glVertex3d(D.x + .5, D.y, 0);
        glVertex3d(C.x - .5, C.y, 0);
        glVertex3d(B.x, C.y + 1.5, 0);
        glVertex3d(A.x, D.y + 1.5, 0);
        glEnd();

        //

        glColor3ub(155, 50, 25);
        glBegin(GL_TRIANGLES);
        glVertex3d(C.x , C.y + 1.5, 0);
        glVertex3d(C.x + 0.1 , C.y +1.5, 0);
        glVertex3d(C.x , C.y + 2.1, 0);
        glEnd();

        glColor3ub(155, 50, 25);
        glBegin(GL_TRIANGLES);
        glVertex3d(C.x - 3 , C.y + 1.5, 0);
        glVertex3d(C.x - 3 - 0.1 , C.y +1.5, 0);
        glVertex3d(C.x - 3, C.y + 2.1, 0);
        glEnd();
        //
        glColor3ub(100, 100, 100);
        glBegin(GL_QUADS);
        glVertex3d(D.x, D.y + 1.5, 0);
        glVertex3d(C.x, C.y + 1.5, 0);
        glVertex3d(C.x, C.y + 2.5, 0);
        glVertex3d(D.x, D.y + 2.5, 0);
        glEnd();

        glColor3ub(210, 180, 110);
        glBegin(GL_QUADS);
        glVertex3d(D.x, D.y + 2.5, 0);
        glVertex3d(C.x, C.y + 2.5, 0);
        glVertex3d(C.x, C.y + 4.5, 0);
        glVertex3d(D.x, D.y + 4.5, 0);
        glEnd();

        glColor3ub(155, 155, 155);
        glBegin(GL_QUADS);
        glVertex3d(D.x, D.y + 4.5, 0);
        glVertex3d(C.x, C.y + 4.5, 0);
        glVertex3d(C.x, C.y + 6, 0);
        glVertex3d(D.x, D.y + 6, 0);
        glEnd();

        //
        A.x = A.x + tx;
        B.x = B.x + tx;
        C.x = C.x + tx;
        D.x = D.x + tx;

        A.y = A.y + ty;
        B.y = B.y + ty;
        C.y = C.y + ty;
        D.y = D.y + ty;

        glPopMatrix();
    }

    void ScoreUpdate()
    {
        if (this->C.y <= -17) {
            score++;
        }
    }
};

class carObj {
public:
    Point A;
    Point B;
    Point C;
    Point D;


    carObj()
    {
    }

    carObj(Point& a, Point& b, Point& c, Point& d)
    {
        this->A = a;
        this->B = b;
        this->C = c;
        this->D = d;
    }

    void PlayercarDraw()
    {
        glPushMatrix();

        glTranslatef(positionx, 0.0f, 0.0f);


        glColor3ub(15, 50, 55);
        glBegin(GL_QUADS);
        glVertex3d(A.x + 0.5, A.y, 0);
        glVertex3d(B.x - 0.5, B.y, 0);
        glVertex3d(C.x, B.y  - 1.5, 0);
        glVertex3d(D.x, A.y  - 1.5, 0);

        glEnd();
        //
        //
        glColor3ub(155, 50, 25);
        //
        glBegin(GL_TRIANGLES);
        glVertex3d(A.x , A.y -1.5, 0);
        glVertex3d(A.x - 0.1 , A.y -1.5, 0);
        glVertex3d(A.x , A.y - 2.1, 0);
        //
        glEnd();

        glColor3ub(155, 50, 25);
        //
        glBegin(GL_TRIANGLES);
        glVertex3d(A.x + 3 , A.y -1.5, 0);
        glVertex3d(A.x + 3 + 0.1 , A.y -1.5, 0);
        glVertex3d(A.x + 3 , A.y - 2.1, 0);
        //
        glEnd();

        // draw Glass

        glColor3ub(0, 0, 20);
        glBegin(GL_QUADS);
        glVertex3d(A.x, A.y - 1.5, 0);
        glVertex3d(B.x, B.y - 1.5, 0);
        glVertex3d(C.x, B.y - 2.5, 0);
        glVertex3d(D.x, A.y - 2.5, 0);
        glEnd();

        glColor3ub(100, 100, 100);
        glBegin(GL_QUADS);
        glVertex3d(A.x, A.y - 2.5, 0);
        glVertex3d(B.x, B.y - 2.5, 0);
        glVertex3d(C.x, B.y - 4.5, 0);
        glVertex3d(D.x, A.y - 4.5, 0);
        glEnd();

        glColor3ub(55, 55, 55);
        glBegin(GL_QUADS);
        glVertex3d(A.x, A.y - 4.5, 0);
        glVertex3d(B.x, B.y - 4.5, 0);
        glVertex3d(C.x, B.y - 7, 0);
        glVertex3d(D.x, A.y - 7, 0);
        glEnd();


        A.x = A.x + positionx;
        B.x = B.x + positionx;
        C.x = C.x + positionx;
        D.x = D.x + positionx;

        glPopMatrix();
    }
};

carObj c;
Opponent cO;
Opponent c1;
Opponent c2;

void collisionCheck(carObj& o, Opponent& p)
{
    float yFaceToFaceCollide = abs(o.A.y - p.D.y);
    float yDownToFaceCollide = abs(o.C.y - p.D.y);
    float xLeftPlayerCollide = abs(o.A.x - p.D.x);
    // std::cout << xLeftPlayerCollide << std::endl;
    float xRightPlayerCollide = abs(o.B.x - p.C.x);
    // std::cout << xRightPlayerCollide << std::endl;

    if ((yFaceToFaceCollide <= 0 || yDownToFaceCollide <= 5) && (xLeftPlayerCollide < 3 || xRightPlayerCollide < 3)) {

        start = 0;
        gv = 1;
        std::cout << "COLLIDED " << p.name << " " << std::endl;
    } else {
        /* std::cout << "NOT COLLIDED" << std::endl; */
        std::cout << timeUpdate << std::endl;

        // std::cout << score << std::endl;
    }
}

int randGen(int min, int max)
{
    srand(time(NULL));
    return ((float)rand() / (float)RAND_MAX) * (max - min) + min;
}

void init()
{
    glClearColor(1, 1, 1, 0.0);
    // glMatrixMode(GL_PROJECTION | GL_MODELVIEW);
    glLoadIdentity();
    gluOrtho2D(-14, 14, -17, 17);
}

template <typename T>
void showPoint(T& c)
{
    std::cout << "p1: "
              << "x: " << c.A.x << " y: " << c.A.y << std::endl;
    std::cout << "p2: "
              << "x: " << c.B.x << " y: " << c.B.y << std::endl;
    std::cout << "p3: "
              << "x: " << c.C.x << " y: " << c.C.y << std::endl;
    std::cout << "p4: "
              << "x: " << c.D.x << " y: " << c.D.y << std::endl;
}

void timer(int value)
{
    if (timeUpdate >= 20) {
        timeUpdate = timeUpdate - 0.15;
    }
    // std::cout << timeUpdate << std::endl;

    // std::cout << score << std::endl;

    glutTimerFunc(1000, timer, 0);
}

void updateOppo(int value)
{
    if (oppoY <= -27) {
        oppoY = randGen(MIN, MAX);
        oppoX = randGen(-13, -8);
        oppoX++;
    }

    oppoY--;
    // std::cout << oppoY << std::endl;
    //
    //
    //

    glutPostRedisplay();
    glutTimerFunc(timeUpdate, updateOppo, 0);
}

void update2Oppo(int value)
{
    if (oppo2Y <= -42) {
        oppo2Y = randGen(MIN, MAX);
        oppo2X = randGen(-2, 0);

        oppo2X++;
    }

    oppo2Y--;
    // std::cout << oppoY << std::endl;
    glutPostRedisplay();
    glutTimerFunc(timeUpdate, update2Oppo, 0);
}

void update3Oppo(int value)
{
    if (oppo3Y <= -39) {
        oppo3Y = randGen(MIN, MAX);
        oppo3X = randGen(3, 7);
        oppo3X++;
    }

    oppo3Y--;
    // std::cout << oppoY << std::endl;
    glutPostRedisplay();
    glutTimerFunc(timeUpdate, update3Oppo, 0);
}

void update(int value)
{

    if (top <= 13) {
        top = 27.0f;
    }
    top--;

    glutPostRedisplay();
    glutTimerFunc(100, update, 0);
}

void middleBar()
{

    glPushMatrix();
    glColor3ub(255, 255, 255);
    glBegin(GL_QUADS);
    glVertex3d(-0.5, top + 12, 0);
    glVertex3d(0.5, top + 12, 0);
    glVertex3d(0.5, top - 2, 0);
    glVertex3d(-0.5, top - 2, 0);
    glEnd();

    glColor3ub(255, 255, 255);
    glBegin(GL_QUADS);
    glVertex3d(-0.5, top, 0);
    glVertex3d(0.5, top, 0);
    glVertex3d(0.5, top - 10, 0);
    glVertex3d(-0.5, top - 10, 0);
    glEnd();

    glColor3ub(255, 255, 255);
    glBegin(GL_QUADS);
    glVertex3d(-0.5, top - 12, 0);
    glVertex3d(0.5, top - 12, 0);
    glVertex3d(0.5, top - 22, 0);
    glVertex3d(-0.5, top - 22, 0);
    glEnd();

    glColor3ub(255, 255, 255);
    glBegin(GL_QUADS);
    glVertex3d(-0.5, top - 24, 0);
    glVertex3d(0.5, top - 24, 0);
    glVertex3d(0.5, top - 34, 0);
    glVertex3d(-0.5, top - 34, 0);
    glEnd();
    glPopMatrix();
}

void road()
{
    glPushMatrix();

    glColor3ub(0, 30, 0);
    glBegin(GL_LINES);
    glVertex3d(-8, +17, 0);
    glVertex3d(-8, -17, 0);
    glEnd();
    glColor3ub(0, 30, 0);
    glBegin(GL_LINES);
    glVertex3d(+8, +17, 0);
    glVertex3d(+8, -17, 0);
    glEnd();
    glPopMatrix();

    glPushMatrix();

    glColor3ub(0, 30, 0);
    glBegin(GL_LINES);
    glVertex3d(-9, +17, 0);
    glVertex3d(-9, -17, 0);
    glEnd();
    glColor3ub(0, 30, 0);
    glBegin(GL_LINES);
    glVertex3d(+9, +17, 0);
    glVertex3d(+9, -17, 0);
    glEnd();
    glPopMatrix();
}

void roadSpace()
{
    glPushMatrix();

    glColor3ub(101, 115, 126);
    glBegin(GL_QUADS);
    glVertex3d(-8, +17, 0);
    glVertex3d(+8, +17, 0);
    glVertex3d(+8, -17, 0);
    glVertex3d(-8, -17, 0);
    glEnd();
    glPopMatrix();
}

void processSpecialKeys(int key, int mx, int my)
{
    switch (key) {
    case GLUT_KEY_LEFT:
        if (positionx >= -3) {
            positionx -= 1.0;
        }
        glutPostRedisplay();
        break;
    case GLUT_KEY_RIGHT:
        if (positionx <= +8) {
            positionx += 1.0;
        }
        glutPostRedisplay();
        break;
    case GLUT_KEY_DOWN:
        if (timeUpdate <= 200) {
            timeUpdate++;
        }
        glutPostRedisplay();
        break;
    case GLUT_KEY_UP:
        if (timeUpdate >= 20) {
            timeUpdate--;
        }
        glutPostRedisplay();
        break;
    default:
        break;
    }
}

void sideBorder()
{
    glPushMatrix();
    glColor3ub(52, 61, 70);
    glBegin(GL_QUADS);
    glVertex3d(-9, 17, 0);
    glVertex3d(-8, 17, 0);
    glVertex3d(-8, -17, 0);
    glVertex3d(-9, -17, 0);
    glEnd();
    glColor3ub(52, 61, 70);
    glBegin(GL_QUADS);
    glVertex3d(+9, 17, 0);
    glVertex3d(+8, 17, 0);
    glVertex3d(+8, -17, 0);
    glVertex3d(+9, -17, 0);
    glEnd();
    glPopMatrix();
}

void car()
{
    Point p1 = Point(-4, -11);
    Point p2 = Point(-1, -11);
    Point p3 = Point(-1, -17);
    Point p4 = Point(-4, -17);

    c = carObj(p1, p2, p3, p4);
    c.PlayercarDraw();
    // showPoint(c);
}

void carOppo()
{
    Point p1 = Point(-4 + 7, -11 + 22);
    Point p2 = Point(-1 + 7, -11 + 22);
    Point p3 = Point(-1 + 7, -17 + 22);
    Point p4 = Point(-4 + 7, -17 + 22);


    cO = Opponent(p1, p2, p3, p4, "first Opponent");
    cO.oppocarDraw(oppoX, oppoY, 122, 143, 222);
    cO.ScoreUpdate();
    // showPoint(cO);
}

void car2Oppo()
{
    Point p1 = Point(-4 + 7 - 5, -11 + 22 + 4 + 10);
    Point p2 = Point(-1 + 7 - 5, -11 + 22 + 4 + 10);
    Point p3 = Point(-1 + 7 - 5, -17 + 22 + 4 + 10);
    Point p4 = Point(-4 + 7 - 5, -17 + 22 + 4 + 10);

    c1 = Opponent(p1, p2, p3, p4, "second Opponent");
    c1.oppocarDraw(oppo2X, oppo2Y, 255, 40, 0);
    c1.ScoreUpdate();
    // showPoint(c1);
}

void car3Oppo()
{
    Point p1 = Point(-4 + 7 - 5, -11 + 22 + 4);
    Point p2 = Point(-1 + 7 - 5, -11 + 22 + 4);
    Point p3 = Point(-1 + 7 - 5, -17 + 22 + 4);
    Point p4 = Point(-4 + 7 - 5, -17 + 22 + 4);

    c2 = Opponent(p1, p2, p3, p4, "third Opponent");
    c2.oppocarDraw(oppo3X, oppo3Y, 72,209,204);
    c2.ScoreUpdate();
    // showPoint(c2);
}

void padestrian()
{
    glPushMatrix();
    glColor3ub(139, 69, 19);
    glBegin(GL_QUADS);
    glVertex3d(-14, 17, 0);
    glVertex3d(-9, 17, 0);
    glVertex3d(-9, -17, 0);
    glVertex3d(-14, -17, 0);
    glEnd();
    glColor3ub(139, 69, 19);
    glBegin(GL_QUADS);
    glVertex3d(+14, 17, 0);
    glVertex3d(+9, 17, 0);
    glVertex3d(+9, -17, 0);
    glVertex3d(+14, -17, 0);
    glEnd();
    glPopMatrix();
}

void startGame()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    padestrian();
    sideBorder();

    glPushMatrix();
    road();
    glPopMatrix();

    glPushMatrix();
    roadSpace();
    glPopMatrix();

    middleBar();

    glPushMatrix();
    car();
    glPopMatrix();
    glPushMatrix();
    carOppo();
    glPopMatrix();

    glPushMatrix();
    car2Oppo();
    glPopMatrix();

    // car3
    glPushMatrix();
    car3Oppo();
    glPopMatrix();

    tree();

    collisionCheck(c, cO);
    collisionCheck(c, c1);
    collisionCheck(c, c2);
    dataInfo();

    glutSwapBuffers();
    // glutPostRedisplay();
    glFlush();
}

void frontPage()
{
    //Text Information in Frist Page
    if (gv == 1) {
        glColor3ub(204, 204, 255);
        renderBitmapString(-7, -5, (void*)font1, "GAME OVER");
        glColor3ub(128, 128, 128);
        char buffer2[50];
        sprintf(buffer2, "Your Score is : %d", score);
        renderBitmapString(-7, -7, (void*)font1, buffer2);
    }

    glColor3ub(169, 169, 169);
    renderBitmapString(-8, 10, (void*)font1, "2D Car Racing obstacle survivor ");

    glColor3ub(128, 128, 128);
    renderBitmapString(-7, 8, (void*)font2, "Press SPACE to START");
    renderBitmapString(-7, 6, (void*)font2, "Press ESC to Exit");

    glColor3ub(52, 61, 70);
    renderBitmapString(-7, 4, (void*)font3, "Press UP to increase Speed");
    renderBitmapString(-7, 2, (void*)font3, "Press DWON to decrease Speed");
    renderBitmapString(-7, 0, (void*)font3, "Press RIGHT to turn Right");
    renderBitmapString(-7, -2, (void*)font3, "Press LEFT to turn Left");

    glColor3f(0, 0, 30);
    renderBitmapString(-8, -10, (void*)font3, "Project By:");
    renderBitmapString(-8, -12, (void*)font3, "Zawad, Emrul Hasan    -> 15-30142-2");
    renderBitmapString(-8, -13, (void*)font3, "Mahmud, MD. Tanzin    -> 15-30433-3");
    renderBitmapString(-8, -14, (void*)font3, "Alam, Novera Binte    -> 15-28781-1");
    renderBitmapString(-8, -15, (void*)font3, "Dipu, MD.Saiful Islam -> 13-23101-1");
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (start == 1) {
        startGame();
    }

    else {
        frontPage();
        //glClearColor(0.184, 0.310, 0.310,1);
    }

    glFlush();
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(2.2 * 280, 2.1 * 340);
    glutCreateWindow("Racing with obstacles");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(1000, timer, 0);
    glutTimerFunc(100, update, 0);
    glutTimerFunc(100, updateOppo, 0);
    glutTimerFunc(100, update2Oppo, 0);
    glutTimerFunc(100, update3Oppo, 0);
    glutTimerFunc(1000, move, 0);
    glutSpecialFunc(processSpecialKeys);
    glutKeyboardFunc(processKeys);

    // GLUT Thread management sucks
    // SFML sound functionality
    sf::Music music;
    if (!music.openFromFile("music.ogg")) {
        return -1;
    }
    music.setVolume(50);
    music.play();
    glutMainLoop();
    return 0;
}
