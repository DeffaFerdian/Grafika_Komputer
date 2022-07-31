#include <GL/glut.h>
#include <windows.h>

void init(void);
void tampil(void);
void keyboard(unsigned char, int, int);
void mouse(int, int, int, int);
void mouseMotion(int, int);
void ukuran(int, int);

int is_depth;

float xrot = 0.0f;
float yrot = 0.0f;
float xdiff = 0.0f;
float ydiff = 0.0f;
bool mouseDown = false;

float xmov = 0.0f;
float ymov = 0.0f;
float zmov = 0.0f;

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1280, 720);
    glutInitWindowPosition(150, 80);
    glutCreateWindow("GEDUNG BARA");
    init();
    glutDisplayFunc(tampil);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);

    glutReshapeFunc(ukuran);
    glutMainLoop();
    return 0;
}
void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    is_depth = 1;
    glMatrixMode(GL_MODELVIEW);
    //glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glPointSize(8.0); //UKURAN TITIK
    glLineWidth(4.0);
}

void tampil(void)
{
    if (is_depth) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    else {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    glRotatef(xrot, 1.0f, 0.0f, 0.0f);
    glRotatef(yrot, 0.0f, 1.0f, 0.0f);

    glTranslatef(xmov, ymov, zmov);
    glPushMatrix();

    //PANCA
    //PANCA
    glBegin(GL_QUADS);
    glColor3f(0.0, 1, 0.0);
    glVertex3f(-70, -8, 15);    //trotoar depan //alas atau rumput
    glVertex3f(-70, -8.0, -25);
    glVertex3f(70, -8.0, -25);
    glVertex3f(70, -8, 15);

    glColor3f(1, 1, 1);
    glVertex3f(-70, -10, 15);    //sisi depan, luar,putih
    glVertex3f(-70, -5.0, 15);
    glVertex3f(70, -5.0, 15);
    glVertex3f(70, -10, 15);
    glColor3f(0, 0, 0);
    glVertex3f(-70, -10, 15.1);    //sisi depan, luar,hitam dari kiri,1
    glVertex3f(-70, -5.0, 15.1);
    glVertex3f(-60, -5.0, 15.1);
    glVertex3f(-60, -10, 15.1);
    glVertex3f(-50, -10, 15.1);    //,2
    glVertex3f(-50, -5.0, 15.1);
    glVertex3f(-40, -5.0, 15.1);
    glVertex3f(-40, -10, 15.1);
    glVertex3f(-30, -10, 15.1);    //,3
    glVertex3f(-30, -5.0, 15.1);
    glVertex3f(-20, -5.0, 15.1);
    glVertex3f(-20, -10, 15.1);
    glVertex3f(-10, -10, 15.1);    //,4
    glVertex3f(-10, -5.0, 15.1);
    glVertex3f(0, -5.0, 15.1);
    glVertex3f(0, -10, 15.1);
    glVertex3f(10, -10, 15.1);    //,5
    glVertex3f(10, -5.0, 15.1);
    glVertex3f(20, -5.0, 15.1);
    glVertex3f(20, -10, 15.1);
    glVertex3f(30, -10, 15.1);    //,6
    glVertex3f(30, -5.0, 15.1);
    glVertex3f(40, -5.0, 15.1);
    glVertex3f(40, -10, 15.1);
    glVertex3f(50, -10, 15.1);    //,7
    glVertex3f(50, -5.0, 15.1);
    glVertex3f(60, -5.0, 15.1);
    glVertex3f(60, -10, 15.1);
    glVertex3f(70, -10, 15.1);    //,8
    glVertex3f(70, -5.0, 15.1);
    glVertex3f(65, -5.0, 15.1);
    glVertex3f(65, -10, 15.1);
    glColor3f(0.6, 0.3, 0);
    glVertex3f(-70, -10, 10);    //sisi depan, dalam
    glVertex3f(-70, -5.0, 10);
    glVertex3f(70, -5.0, 10);
    glVertex3f(70, -10, 10);
    glColor3f(1, 1, 1);
    glVertex3f(-70, -5, 10);    //sisi depan, atas
    glVertex3f(-70, -5.0, 15);
    glVertex3f(70, -5.0, 15);
    glVertex3f(70, -5, 10);
    glColor3f(0, 0, 0);
    glVertex3f(-70, -4.9, 15.2);    //sisi depan, atas,hitam dari kiri,1
    glVertex3f(-70, -4.9, 10);
    glVertex3f(-60, -4.9, 10);
    glVertex3f(-60, -4.9, 15.2);
    glVertex3f(-50, -4.9, 15.2);    //2
    glVertex3f(-50, -4.9, 10);
    glVertex3f(-40, -4.9, 10);
    glVertex3f(-40, -4.9, 15.2);
    glVertex3f(-30, -4.9, 15.2);    //3
    glVertex3f(-30, -4.9, 10);
    glVertex3f(-20, -4.9, 10);
    glVertex3f(-20, -4.9, 15.2);
    glVertex3f(-10, -4.9, 15.2);    //4
    glVertex3f(-10, -4.9, 10);
    glVertex3f(0, -4.9, 10);
    glVertex3f(0, -4.9, 15.2);
    glVertex3f(10, -4.9, 15.2);    //5
    glVertex3f(10, -4.9, 10);
    glVertex3f(20, -4.9, 10);
    glVertex3f(20, -4.9, 15.2);
    glVertex3f(30, -4.9, 15.2);    //6
    glVertex3f(30, -4.9, 10);
    glVertex3f(40, -4.9, 10);
    glVertex3f(40, -4.9, 15.2);
    glVertex3f(50, -4.9, 15.2);    //7
    glVertex3f(50, -4.9, 10);
    glVertex3f(60, -4.9, 10);
    glVertex3f(60, -4.9, 15.2);

    glColor3f(1, 1, 1);
    glVertex3f(-70, -10, -25);    //sisi belakang, luar
    glVertex3f(-70, -5.0, -25);
    glVertex3f(70, -5.0, -25);
    glVertex3f(70, -10, -25);
    glColor3f(0, 0, 0);
    glVertex3f(-70, -10, -25.1);    //sisi belakang, luar,hitam dari kiri,1
    glVertex3f(-70, -5.0, -25.1);
    glVertex3f(-60, -5.0, -25.1);
    glVertex3f(-60, -10, -25.1);
    glVertex3f(-50, -10, -25.1);    //,2
    glVertex3f(-50, -5.0, -25.1);
    glVertex3f(-40, -5.0, -25.1);
    glVertex3f(-40, -10, -25.1);
    glVertex3f(-30, -10, -25.1);    //,3
    glVertex3f(-30, -5.0, -25.1);
    glVertex3f(-20, -5.0, -25.1);
    glVertex3f(-20, -10, -25.1);
    glVertex3f(-10, -10, -25.1);    //,4
    glVertex3f(-10, -5.0, -25.1);
    glVertex3f(0, -5.0, -25.1);
    glVertex3f(0, -10, -25.1);
    glVertex3f(10, -10, -25.1);    //,5
    glVertex3f(10, -5.0, -25.1);
    glVertex3f(20, -5.0, -25.1);
    glVertex3f(20, -10, -25.1);
    glVertex3f(30, -10, -25.1);    //,6
    glVertex3f(30, -5.0, -25.1);
    glVertex3f(40, -5.0, -25.1);
    glVertex3f(40, -10, -25.1);
    glVertex3f(50, -10, -25.1);    //,7
    glVertex3f(50, -5.0, -25.1);
    glVertex3f(60, -5.0, -25.1);
    glVertex3f(60, -10, -25.1);
    glVertex3f(70, -10, -25.1);    //,8
    glVertex3f(70, -5.0, -25.1);
    glVertex3f(65, -5.0, -25.1);
    glVertex3f(65, -10, -25.1);
    glColor3f(0.6, 0.3, 0);
    glVertex3f(-70, -10, -20);    //sisi belakang, dalam
    glVertex3f(-70, -5.0, -20);
    glVertex3f(70, -5.0, -20);
    glVertex3f(70, -10, -20);
    glColor3f(1, 1, 1);
    glVertex3f(-70, -5, -20);    //sisi belakang, atas
    glVertex3f(-70, -5.0, -25);
    glVertex3f(70, -5.0, -25);
    glVertex3f(70, -5, -20);
    glColor3f(0, 0, 0);
    glVertex3f(-70, -4.9, -25.2);    //sisi belakang, atas,hitam dari kiri,1
    glVertex3f(-70, -4.9, -20);
    glVertex3f(-60, -4.9, -20);
    glVertex3f(-60, -4.9, -25.2);
    glVertex3f(-50, -4.9, -25.2);    //2
    glVertex3f(-50, -4.9, -20);
    glVertex3f(-40, -4.9, -20);
    glVertex3f(-40, -4.9, -25.2);
    glVertex3f(-30, -4.9, -25.2);    //3
    glVertex3f(-30, -4.9, -20);
    glVertex3f(-20, -4.9, -20);
    glVertex3f(-20, -4.9, -25.2);
    glVertex3f(-10, -4.9, -25.2);    //4
    glVertex3f(-10, -4.9, -20);
    glVertex3f(0, -4.9, -20);
    glVertex3f(0, -4.9, -25.2);
    glVertex3f(10, -4.9, -25.2);    //5
    glVertex3f(10, -4.9, -20);
    glVertex3f(20, -4.9, -20);
    glVertex3f(20, -4.9, -25.2);
    glVertex3f(30, -4.9, -25.2);    //6
    glVertex3f(30, -4.9, -20);
    glVertex3f(40, -4.9, -20);
    glVertex3f(40, -4.9, -25.2);
    glVertex3f(50, -4.9, -25.2);    //7
    glVertex3f(50, -4.9, -20);
    glVertex3f(60, -4.9, -20);
    glVertex3f(60, -4.9, -25.2);

    glColor3f(1, 1, 1);
    glVertex3f(-70, -10, -25);    //sisi kiri, luar
    glVertex3f(-70, -5.0, -25);
    glVertex3f(-70, -5.0, 15);
    glVertex3f(-70, -10, 15);
    glColor3f(0, 0, 0);
    glVertex3f(-70.1, -10, -25);    //sisi kiri, luar, hitam dari kiri, 1
    glVertex3f(-70.1, -5.2, -25);
    glVertex3f(-70.1, -5.2, -20);
    glVertex3f(-70.1, -10, -20);
    glVertex3f(-70.1, -10, -15);    //2
    glVertex3f(-70.1, -5.2, -15);
    glVertex3f(-70.1, -5.2, -8);
    glVertex3f(-70.1, -10, -8);
    glVertex3f(-70.1, -10, 5);    //3
    glVertex3f(-70.1, -5.2, 5);
    glVertex3f(-70.1, -5.2, -2);
    glVertex3f(-70.1, -10, -2);
    glVertex3f(-70.1, -10, 10);    //4
    glVertex3f(-70.1, -5.2, 10);
    glVertex3f(-70.1, -5.2, 15);
    glVertex3f(-70.1, -10, 15);
    glColor3f(0.6, 0.3, 0);
    glVertex3f(-65, -10, -25);    //sisi kiri, dalam
    glVertex3f(-65, -5.0, -25);
    glVertex3f(-65, -5.0, 15);
    glVertex3f(-65, -10, 15);
    glColor3f(1, 1, 1);
    glVertex3f(-70, -5, 15);    //sisi kiri, atas
    glVertex3f(-70, -5.0, -25);
    glVertex3f(-65, -5.0, -25);
    glVertex3f(-65, -5, 15);
    glColor3f(0, 0, 0);
    glVertex3f(-70, -4.9, -8);    //sisi kiri, atas hitam, 1
    glVertex3f(-70, -4.9, -15);
    glVertex3f(-65, -4.9, -15);
    glVertex3f(-65, -4.9, -8);
    glVertex3f(-70, -4.9, -2);    //2
    glVertex3f(-70, -4.9, 5);
    glVertex3f(-65, -4.9, 5);
    glVertex3f(-65, -4.9, -2);

    glColor3f(1, 1, 1);
    glVertex3f(70, -10, -25);    //sisi kanan, luar
    glVertex3f(70, -5.0, -25);
    glVertex3f(70, -5.0, 15);
    glVertex3f(70, -10, 15);
    glColor3f(0, 0, 0);
    glVertex3f(70.1, -10, -25);    //sisi kanan, luar, hitam dari kiri, 1
    glVertex3f(70.1, -5.2, -25);
    glVertex3f(70.1, -5.2, -20);
    glVertex3f(70.1, -10, -20);
    glVertex3f(70.1, -10, -15);    //2
    glVertex3f(70.1, -5.2, -15);
    glVertex3f(70.1, -5.2, -8);
    glVertex3f(70.1, -10, -8);
    glVertex3f(70.1, -10, 5);    //3
    glVertex3f(70.1, -5.2, 5);
    glVertex3f(70.1, -5.2, -2);
    glVertex3f(70.1, -10, -2);
    glVertex3f(70.1, -10, 10);    //4
    glVertex3f(70.1, -5.2, 10);
    glVertex3f(70.1, -5.2, 15);
    glVertex3f(70.1, -10, 15);
    glColor3f(0.6, 0.3, 0);
    glVertex3f(65, -10, -25);    //sisi kanan, dalam
    glVertex3f(65, -5.0, -25);
    glVertex3f(65, -5.0, 15);
    glVertex3f(65, -10, 15);
    glColor3f(1, 1, 1);
    glVertex3f(70, -5, 15);    //sisi kanan, atas
    glVertex3f(70, -5.0, -25);
    glVertex3f(65, -5.0, -25);
    glVertex3f(65, -5, 15);
    glColor3f(0, 0, 0);
    glVertex3f(70, -4.9, -8);    //sisi kanan,  atas hitam, 1
    glVertex3f(70, -4.9, -15);
    glVertex3f(65, -4.9, -15);
    glVertex3f(65, -4.9, -8);
    glVertex3f(70, -4.9, -2);    //2
    glVertex3f(70, -4.9, 5);
    glVertex3f(65, -4.9, 5);
    glVertex3f(65, -4.9, -2);
    glVertex3f(70, -4.9, -20);    //3
    glVertex3f(70, -4.9, -25);
    glVertex3f(65, -4.9, -25);
    glVertex3f(65, -4.9, -20);
    glVertex3f(70, -4.9, 15);    //4
    glVertex3f(70, -4.9, 10);
    glVertex3f(65, -4.9, 10);
    glVertex3f(65, -4.9, 15);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.7, 0, 0.0);
    glVertex3f(-70, -9.9, -25);    //4
    glVertex3f(-40, -9.9, -50);
    glVertex3f(40, -9.9, -50);
    glVertex3f(70, -9.9, -25);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.7, 0.4, 0.0);
    glVertex3f(-75, 15, -360);    //vertikal kedua//meja belakang kiri, sisi depan
    glVertex3f(-75, -10.0, -360);
    glVertex3f(-80, -10.0, -360);
    glVertex3f(-80, 15, -360);
    glVertex3f(-75, 15, -355.1);    //sisi belakang
    glVertex3f(-75, -10.0, -355.1);
    glVertex3f(-80, -10.0, -355.1);
    glVertex3f(-80, 15, -355.1);
    glVertex3f(-75, 15, -360);    //sisi alas
    glVertex3f(-80, 15.0, -360);
    glVertex3f(-80, 15.0, -355.1);
    glVertex3f(-75, 15, -355.1);

    glVertex3f(-70, 15, -355.1);    //horizontal//meja belakang kiri, sisi depan
    glVertex3f(-70, -10.0, -355.1);
    glVertex3f(-75, -10.0, -355.1);
    glVertex3f(-70, 15, -355.1);
    glVertex3f(-70, 15, -399.9);    //sisi belakang
    glVertex3f(-70, -10.0, -399.9);
    glVertex3f(-75, -10.0, -399.9);
    glVertex3f(-75, 15, -399.9);
    glVertex3f(-70, 15, -355.1);    //sisi kiri
    glVertex3f(-70, -10.0, -355.1);
    glVertex3f(-70, -10.0, -399.9);
    glVertex3f(-70, 15, -399.9);
    glVertex3f(-75, 15, -355.1);    //sisi kanan
    glVertex3f(-75, -10.0, -355.1);
    glVertex3f(-75, -10.0, -399.9);
    glVertex3f(-75, 15, -399.9);
    glVertex3f(-75, 15, -355.1);    //sisi alas
    glVertex3f(-70, 15.0, -355.1);
    glVertex3f(-70, 15.0, -399.9);
    glVertex3f(-75, 15, -399.9);

    glVertex3f(75, 15, -384.9);    //vertikal kedua//meja belakang kanan, sisi depan
    glVertex3f(75, -10.0, -384.9);
    glVertex3f(80, -10.0, -384.9);
    glVertex3f(80, 15, -384.9);
    glVertex3f(75, 15, -380);    //sisi belakang
    glVertex3f(75, -10.0, -380);
    glVertex3f(80, -10.0, -380);
    glVertex3f(80, 15, -380);
    glVertex3f(75, 15, -384.9);    //sisi alas
    glVertex3f(80, 15.0, -384.9);
    glVertex3f(80, 15.0, -380);
    glVertex3f(75, 15, -380);

    glVertex3f(70.1, 15, -335.1);    //horizontal//meja belakang kanan, sisi depan
    glVertex3f(70.1, -10.0, -335.1);
    glVertex3f(75, -10.0, -335.1);
    glVertex3f(70.1, 15, -335.1);
    glVertex3f(70.1, 15, -384.9);    //sisi belakang
    glVertex3f(70.1, -10.0, -384.9);
    glVertex3f(75, -10.0, -384.9);
    glVertex3f(75, 15, -384.9);
    glVertex3f(70.1, 15, -335.1);    //sisi kiri
    glVertex3f(70.1, -10.0, -335.1);
    glVertex3f(70.1, -10.0, -384.9);
    glVertex3f(70.1, 15, -384.9);
    glVertex3f(75, 15, -335.1);    //sisi kanan
    glVertex3f(75, -10.0, -335.1);
    glVertex3f(75, -10.0, -384.9);
    glVertex3f(75, 15, -384.9);
    glVertex3f(75, 15, -335.1);    //sisi alas
    glVertex3f(70.1, 15.0, -335.1);
    glVertex3f(70.1, 15.0, -384.9);
    glVertex3f(75, 15, -384.9);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0,0,0);
    glVertex3f(-40, 30, -114.5);    //pintu//list paling luar
    glVertex3f(40, 30.0, -114.5);
    glVertex3f(40, -5, -114.5);
    glVertex3f(-40, -5, -114.5);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3f(0,0,0);
    glVertex3f(-37, 25, -114.5);    //jendela kiri
    glVertex3f(-20, 25, -114.5);
    glVertex3f(-20, 0, -114.5);
    glVertex3f(-37, 0, -114.5);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3f(0,0,0);
    glVertex3f(37, 25, -114.5);    //jendela kanan
    glVertex3f(20, 25, -114.5);
    glVertex3f(20, 0, -114.5);
    glVertex3f(37, 0, -114.5);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3f(0,0,0);
    glVertex3f(-17, 25, -114.5);    //list luar pintu
    glVertex3f(17, 25, -114.5);
    glVertex3f(17, -5, -114.5);
    glVertex3f(-17, -5, -114.5);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3f(0,0,0);
    glVertex3f(-17.0, 25.0, -115.0);    //list pintu kebuka kiri
    glVertex3f(-17.0, -5.0, -115.0);
    glVertex3f(-25.0, -5.0, -132.0);
    glVertex3f(-25.0, 25.0, -132.0);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3f(0,0,0);
    glVertex3f(17.0, 25.0, -115.0);    //list pintu kebuka kanan
    glVertex3f(17.0, -5.0, -115.0);
    glVertex3f(25.0, -5.0, -132.0);
    glVertex3f(25.0, 25.0, -132.0);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-70.0, 10.0, -115.0);      //jendela DEPAN KIRI 2, list luar
    glVertex3f(-70.0, 30.0, -115.0);
    glVertex3f(-45.0, 30.0, -115.0);
    glVertex3f(-45.0, 10.0, -115.0);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-65.0, 15.0, -115.0);      //jendela DEPAN KIRI 2, list dalam
    glVertex3f(-65.0, 25.0, -115.0);
    glVertex3f(-50.0, 25.0, -115.0);
    glVertex3f(-50.0, 15.0, -115.0);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(70.0, 10.0, -115.0);      //jendela DEPAN KANAN 2, list luar
    glVertex3f(70.0, 30.0, -115.0);
    glVertex3f(45.0, 30.0, -115.0);
    glVertex3f(45.0, 10.0, -115.0);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(65.0, 15.0, -115.0);      //jendela DEPAN KANAN 2, list dalam
    glVertex3f(65.0, 25.0, -115.0);
    glVertex3f(50.0, 25.0, -115.0);
    glVertex3f(50.0, 15.0, -115.0);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(30, 10, -155.0);           //MEJA - Kanan 2
    glVertex3f(30, -8.0, -155.0);
    glVertex3f(30, -8.0, -165.0);
    glVertex3f(30, 10, -165.0);
    glVertex3f(40, 10, -155.0);           //MEJA - Kanan alas
    glVertex3f(40, 10.0, -165.0);
    glVertex3f(30, 10.0, -165.0);
    glVertex3f(30, 10, -155.0);
    glVertex3f(-40.0, 10.0, -155.0);       //MEJA - BELAKANG, alas
    glVertex3f(-40.0, 10.0, -150.0);
    glVertex3f(40.0, 10.0, -150.0);
    glVertex3f(40.0, 10.0, -155.0);
    glVertex3f(-40, 10, -155.0);           //MEJA - KIRI alas
    glVertex3f(-40, 10.0, -165.0);
    glVertex3f(-30, 10.0, -165.0);
    glVertex3f(-30, 10, -155.0);

    glColor3f(0.7, 0.4, 0.0);
    glVertex3f(-15, 15, -165.0);    // kursi pertama //kursi resepsionis sisi belakang
    glVertex3f(-15, -10.0, -165.0);
    glVertex3f(-5, -10.0, -165.0);
    glVertex3f(-5, 15, -165.0);
    glVertex3f(-15, 3, -160.0);    //kursi resepsionis sisi depan
    glVertex3f(-15, -10.0, -160.0);
    glVertex3f(-5, -10.0, -160.0);
    glVertex3f(-5, 3, -160.0);
    glVertex3f(-15, 3, -160.0);    //kursi resepsionis alas
    glVertex3f(-15, 3, -165.0);
    glVertex3f(-5, 3, -165.0);
    glVertex3f(-5, 3, -160.0);

    glVertex3f(15, 15, -165.0);    // kursi pertama //kursi resepsionis sisi belakang
    glVertex3f(15, -10.0, -165.0);
    glVertex3f(5, -10.0, -165.0);
    glVertex3f(5, 15, -165.0);
    glVertex3f(15, 3, -160.0);    //kursi resepsionis sisi depan
    glVertex3f(15, -10.0, -160.0);
    glVertex3f(5, -10.0, -160.0);
    glVertex3f(5, 3, -160.0);
    glVertex3f(15, 3, -160.0);    //kursi resepsionis alas
    glVertex3f(15, 3, -165.0);
    glVertex3f(5, 3, -165.0);
    glVertex3f(5, 3, -160.0);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.80, 0.40, 0.2);
    glVertex3f(-40, 0, -190.0);    //tangga kiri depan //1
    glVertex3f(-40, -10.0, -190.0);
    glVertex3f(-20, -10.0, -190.0);
    glVertex3f(-20, 0, -190.0);
    glVertex3f(-40, 10.0, -195.0);     //2
    glVertex3f(-40, 0.0, -195.0);
    glVertex3f(-20, 0.0, -195.0);
    glVertex3f(-20, 10.0, -195.0);
    glVertex3f(-40, 20.0, -200.0);    //3
    glVertex3f(-40, 10.0, -200.0);
    glVertex3f(-20, 10.0, -200.0);
    glVertex3f(-20, 20.0, -200.0);
    glVertex3f(-40, 30.0, -205.0);    //4
    glVertex3f(-40, 20.0, -205.0);
    glVertex3f(-20, 20.0, -205.0);
    glVertex3f(-20, 30.0, -205.0);
    glVertex3f(-40, 40.0, -210.0);    //5
    glVertex3f(-40, 30.0, -210.0);
    glVertex3f(-20, 30.0, -210.0);
    glVertex3f(-20, 40.0, -210.0);
    glVertex3f(-40, 50.0, -215.0);    //6
    glVertex3f(-40, 40.0, -215.0);
    glVertex3f(-20, 40.0, -215.0);
    glVertex3f(-20, 50.0, -215.0);

    glColor3f(1,1, 1);
    glVertex3f(-40, 0, -190.0);    //tangga kiri,sisi kiri //1
    glVertex3f(-40, -10.0, -190.0);
    glVertex3f(-40, -10.0, -195.0);
    glVertex3f(-40, 0, -195.0);
    glVertex3f(-40, 10.0, -200.0);    //2
    glVertex3f(-40, -10.0, -200.0);
    glVertex3f(-40, -10.0, -195.0);
    glVertex3f(-40, 10.0, -195.0);
    glVertex3f(-40, 20.0, -205.0);    //3
    glVertex3f(-40, -10.0, -205.0);
    glVertex3f(-40, -10.0, -200.0);
    glVertex3f(-40, 20.0, -200.0);
    glVertex3f(-40, 30.0, -210.0);    //4
    glVertex3f(-40, -10.0, -210.0);
    glVertex3f(-40, -10.0, -205.0);
    glVertex3f(-40, 30.0, -205.0);
    glVertex3f(-40, 40.0, -215.0);    //5
    glVertex3f(-40, -10.0, -215.0);
    glVertex3f(-40, -10.0, -210.0);
    glVertex3f(-40, 40.0, -210.0);
    glVertex3f(-40, 50.0, -220.0);    //6
    glVertex3f(-40, -10.0, -220.0);
    glVertex3f(-40, -10.0, -215.0);
    glVertex3f(-40, 50.0, -215.0);

    glColor3f(1,1,1);
    glVertex3f(-20, 0, -190.0);    //tangga kiri,sisi kanan //1
    glVertex3f(-20, -10.0, -190.0);
    glVertex3f(-20, -10.0, -195.0);
    glVertex3f(-20, 0, -195.0);
    glVertex3f(-20, 10.0, -200.0);    //2
    glVertex3f(-20, -10.0, -200.0);
    glVertex3f(-20, -10.0, -195.0);
    glVertex3f(-20, 10.0, -195.0);
    glVertex3f(-20, 20.0, -205.0);    //3
    glVertex3f(-20, -10.0, -205.0);
    glVertex3f(-20, -10.0, -200.0);
    glVertex3f(-20, 20.0, -200.0);
    glVertex3f(-20, 30.0, -210.0);    //4
    glVertex3f(-20, -10.0, -210.0);
    glVertex3f(-20, -10.0, -205.0);
    glVertex3f(-20, 30.0, -205.0);
    glVertex3f(-20, 40.0, -215.0);    //5
    glVertex3f(-20, -10.0, -215.0);
    glVertex3f(-20, -10.0, -210.0);
    glVertex3f(-20, 40.0, -210.0);
    glVertex3f(-20, 50.0, -220.0);    //6
    glVertex3f(-20, -10.0, -220.0);
    glVertex3f(-20, -10.0, -215.0);
    glVertex3f(-20, 50.0, -215.0);

    glColor3f(0.80, 0.40, 0.2);
    glVertex3f(-40, 0, -190.0);    //tangga kiri alas //1
    glVertex3f(-40, 0.0, -195.0);
    glVertex3f(-20, 0.0, -195.0);
    glVertex3f(-20, 0, -190.0);
    glVertex3f(-40, 10.0, -195.0);    //tangga kiri //2
    glVertex3f(-40, 10.0, -200.0);
    glVertex3f(-20, 10.0, -200.0);
    glVertex3f(-20, 10.0, -195.0);
    glVertex3f(-40, 20.0, -200.0);    //tangga kiri //3
    glVertex3f(-40, 20.0, -205.0);
    glVertex3f(-20, 20.0, -205.0);
    glVertex3f(-20, 20.0, -200.0);
    glVertex3f(-40, 30.0, -205.0);    //tangga kiri //4
    glVertex3f(-40, 30.0, -210.0);
    glVertex3f(-20, 30.0, -210.0);
    glVertex3f(-20, 30.0, -205.0);
    glVertex3f(-40, 40.0, -210.0);    //tangga kiri //5
    glVertex3f(-40, 40.0, -215.0);
    glVertex3f(-20, 40.0, -215.0);
    glVertex3f(-20, 40.0, -210.0);
    glVertex3f(-40, 50.0, -215.0);    //tangga kiri //6
    glVertex3f(-40, 50.0, -220.0);
    glVertex3f(-20, 50.0, -220.0);
    glVertex3f(-20, 50.0, -215.0);

    glBegin(GL_QUADS);
    glColor3f(0.80, 0.40, 0.2);
    glVertex3f(40, 0, -190.0);    //tangga kanan depan //1
    glVertex3f(40, -10.0, -190.0);
    glVertex3f(20, -10.0, -190.0);
    glVertex3f(20, 0, -190.0);
    glVertex3f(40, 10.0, -195.0);     //2
    glVertex3f(40, 0.0, -195.0);
    glVertex3f(20, 0.0, -195.0);
    glVertex3f(20, 10.0, -195.0);
    glVertex3f(40, 20.0, -200.0);    //3
    glVertex3f(40, 10.0, -200.0);
    glVertex3f(20, 10.0, -200.0);
    glVertex3f(20, 20.0, -200.0);
    glVertex3f(40, 30.0, -205.0);    //4
    glVertex3f(40, 20.0, -205.0);
    glVertex3f(20, 20.0, -205.0);
    glVertex3f(20, 30.0, -205.0);
    glVertex3f(40, 40.0, -210.0);    //5
    glVertex3f(40, 30.0, -210.0);
    glVertex3f(20, 30.0, -210.0);
    glVertex3f(20, 40.0, -210.0);
    glVertex3f(40, 50.0, -215.0);    //6
    glVertex3f(40, 40.0, -215.0);
    glVertex3f(20, 40.0, -215.0);
    glVertex3f(20, 50.0, -215.0);

    glColor3f(1,1,1);
    glVertex3f(40, 0, -190.0);    //tangga kanan,sisi kiri //1
    glVertex3f(40, -10.0, -190.0);
    glVertex3f(40, -10.0, -195.0);
    glVertex3f(40, 0, -195.0);
    glVertex3f(40, 10.0, -200.0);    //2
    glVertex3f(40, -10.0, -200.0);
    glVertex3f(40, -10.0, -195.0);
    glVertex3f(40, 10.0, -195.0);
    glVertex3f(40, 20.0, -205.0);    //3
    glVertex3f(40, -10.0, -205.0);
    glVertex3f(40, -10.0, -200.0);
    glVertex3f(40, 20.0, -200.0);
    glVertex3f(40, 30.0, -210.0);    //4
    glVertex3f(40, -10.0, -210.0);
    glVertex3f(40, -10.0, -205.0);
    glVertex3f(40, 30.0, -205.0);
    glVertex3f(40, 40.0, -215.0);    //5
    glVertex3f(40, -10.0, -215.0);
    glVertex3f(40, -10.0, -210.0);
    glVertex3f(40, 40.0, -210.0);
    glVertex3f(40, 50.0, -220.0);    //6
    glVertex3f(40, -10.0, -220.0);
    glVertex3f(40, -10.0, -215.0);
    glVertex3f(40, 50.0, -215.0);

    glColor3f(1,1,1);
    glVertex3f(20, 0, -190.0);    //tangga kanan,sisi kanan //1
    glVertex3f(20, -10.0, -190.0);
    glVertex3f(20, -10.0, -195.0);
    glVertex3f(20, 0, -195.0);
    glVertex3f(20, 10.0, -200.0);    //2
    glVertex3f(20, -10.0, -200.0);
    glVertex3f(20, -10.0, -195.0);
    glVertex3f(20, 10.0, -195.0);
    glVertex3f(20, 20.0, -205.0);    //3
    glVertex3f(20, -10.0, -205.0);
    glVertex3f(20, -10.0, -200.0);
    glVertex3f(20, 20.0, -200.0);
    glVertex3f(20, 30.0, -210.0);    //4
    glVertex3f(20, -10.0, -210.0);
    glVertex3f(20, -10.0, -205.0);
    glVertex3f(20, 30.0, -205.0);
    glVertex3f(20, 40.0, -215.0);    //5
    glVertex3f(20, -10.0, -215.0);
    glVertex3f(20, -10.0, -210.0);
    glVertex3f(20, 40.0, -210.0);
    glVertex3f(20, 50.0, -220.0);    //6
    glVertex3f(20, -10.0, -220.0);
    glVertex3f(20, -10.0, -215.0);
    glVertex3f(20, 50.0, -215.0);
    glVertex3f(-40.0, -8.0, -220.0);       //tangga - kiri belakang
    glVertex3f(-40.0, 50.0, -220.0);
    glVertex3f(-20.0, 50.0, -220.0);
    glVertex3f(-20.0, -8.0, -220.0);
    glVertex3f(40.0, -8.0, -220.0);       //tangga - kanan belakang
    glVertex3f(40.0, 50.0, -220.0);
    glVertex3f(20.0, 50.0, -220.0);
    glVertex3f(20.0, -8.0, -220.0);

    glColor3f(0.80, 0.40, 0.2);
    glVertex3f(40, 0, -190.0);    //tangga kanan alas //1
    glVertex3f(40, 0.0, -195.0);
    glVertex3f(20, 0.0, -195.0);
    glVertex3f(20, 0, -190.0);
    glVertex3f(40, 10.0, -195.0);    //tangga kiri //2
    glVertex3f(40, 10.0, -200.0);
    glVertex3f(20, 10.0, -200.0);
    glVertex3f(20, 10.0, -195.0);
    glVertex3f(40, 20.0, -200.0);    //tangga kiri //3
    glVertex3f(40, 20.0, -205.0);
    glVertex3f(20, 20.0, -205.0);
    glVertex3f(20, 20.0, -200.0);
    glVertex3f(40, 30.0, -205.0);    //tangga kiri //4
    glVertex3f(40, 30.0, -210.0);
    glVertex3f(20, 30.0, -210.0);
    glVertex3f(20, 30.0, -205.0);
    glVertex3f(40, 40.0, -210.0);    //tangga kiri //5
    glVertex3f(40, 40.0, -215.0);
    glVertex3f(20, 40.0, -215.0);
    glVertex3f(20, 40.0, -210.0);
    glVertex3f(40, 50.0, -215.0);    //tangga kiri //6
    glVertex3f(40, 50.0, -220.0);
    glVertex3f(20, 50.0, -220.0);
    glVertex3f(20, 50.0, -215.0);

    glColor3f(0.70, 0.70, 0.70);                    //lantai 2, alas
    glVertex3f(-70, 50.0, -240.0);
    glVertex3f(70, 50.0, -240.0);
    glVertex3f(70, 50.0, -220.0);
    glVertex3f(-70, 50.0, -220.0);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0,0,0);
    glVertex3f(-70, 65.0, -240.0); //sisi belakang
    glVertex3f(70, 65.0, -240.0);
    glVertex3f(70, 50.0, -240.0);
    glVertex3f(-70, 50.0, -240.0);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-40, 65.0, -220.0); //sisi depan, kiri 1
    glVertex3f(-40, 65.0, -180.0);
    glVertex3f(-40, 50.0, -180.0);
    glVertex3f(-40, 50.0, -220.0);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-20, 65.0, -220.0); //sisi depan, kiri 2
    glVertex3f(-20, 65.0, -180.0);
    glVertex3f(-20, 50.0, -180.0);
    glVertex3f(-20, 50.0, -220.0);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(40, 65.0, -220.0); //sisi depan, KANAN 2
    glVertex3f(40, 65.0, -180.0);
    glVertex3f(40, 50.0, -180.0);
    glVertex3f(40, 50.0, -220.0);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(20, 65.0, -220.0); //sisi depan, kiri 1
    glVertex3f(20, 65.0, -180.0);
    glVertex3f(20, 50.0, -180.0);
    glVertex3f(20, 50.0, -220.0);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(-40, 65.0, -180.0); //sisi depan, tengah kiri
    glVertex3f(-20, 65.0, -180.0);
    glVertex3f(-20, 50.0, -180.0);
    glVertex3f(-40, 50.0, -180.0);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex3f(40, 65.0, -180.0); //sisi depan, tengah kanan
    glVertex3f(20, 65.0, -180.0);
    glVertex3f(20, 50.0, -180.0);
    glVertex3f(40, 50.0, -180.0);
    glEnd();

    //PANCA
    //PANCA

    //DEFFA
    //DEFFA

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-150, 50, -160.0);           //DINDING - PALING KIRI 1 ( DIHITUNG DARI KIRI )
    glVertex3f(-150, -10.0, -160.0);
    glVertex3f(-150, -10.0, -460.0);
    glVertex3f(-150, 50, -460.0);

    glVertex3f(-150.0, -10.0, -160.0);      //DINDING - DEPAN PALING KIRI 1
    glVertex3f(-150.0, 50.0, -160.0);
    glVertex3f(-110.0, 50.0, -160.0);
    glVertex3f(-110.0, -10.0, -160.0);

    glVertex3f(-110, 50, -100.0);           //DINDING - KIRI 2
    glVertex3f(-110, -10.0, -100.0);
    glVertex3f(-110, -10.0, -160.0);
    glVertex3f(-110, 50, -160.0);

    glVertex3f(-110.0, -10.0, -100.0);      //DINDING - DEPAN KIRI 2
    glVertex3f(-110.0, 50.0, -100.0);
    glVertex3f(-70.0, 50.0, -100.0);
    glVertex3f(-70.0, -10.0, -100.0);
    glVertex3f(-70, 50, -100.0);            //DINDING - DEPAN KIRI DALAM 1 (DARI KIRI)
    glVertex3f(-70, -10.0, -100.0);
    glVertex3f(-70, -10.0, -145.0);
    glVertex3f(-70, 50, -145.0);
    glVertex3f(-45, 50, -100.0);            //DINDING - DEPAN KIRI DALAM 2
    glVertex3f(-45, -10.0, -100.0);
    glVertex3f(-45, -10.0, -115.0);
    glVertex3f(-45, 50, -115.0);
    glVertex3f(-40, 50, -100.0);            //DINDING - DEPAN KIRI DALAM 3
    glVertex3f(-40, -10.0, -100.0);
    glVertex3f(-40, -10.0, -115.0);
    glVertex3f(-40, 50, -115.0);
    glVertex3f(-45.0, -10.0, -100.0);      //DINDING - DEPAN KIRI KECIL 1
    glVertex3f(-45.0, 50.0, -100.0);
    glVertex3f(-40.0, 50.0, -100.0);
    glVertex3f(-40.0, -10.0, -100.0);
    glVertex3f(-45.0, -10.0, -115.0);      //DINDING - DEPAN KIRI KECIL 2
    glVertex3f(-45.0, 50.0, -115.0);
    glVertex3f(-40.0, 50.0, -115.0);
    glVertex3f(-40.0, -10.0, -115.0);
    glVertex3f(-70.0, -10.0, -107.0);      //DINDING - DEPAN KIRI BAWAH 1
    glVertex3f(-70.0, 10.0, -107.0);
    glVertex3f(-45.0, 10.0, -107.0);
    glVertex3f(-45.0, -10.0, -107.0);
    glVertex3f(-70.0, -10.0, -115.0);      //DINDING - DEPAN KIRI BAWAH 2
    glVertex3f(-70.0, 10.0, -115.0);
    glVertex3f(-45.0, 10.0, -115.0);
    glVertex3f(-45.0, -10.0, -115.0);

    glVertex3f(150, 50, -160.0);           //DINDING - PALING KANAN 1 ( DIHITUNG DARI KANAN )
    glVertex3f(150, -10.0, -160.0);
    glVertex3f(150, -10.0, -460.0);
    glVertex3f(150, 50, -460.0);

    glVertex3f(150.0, -10.0, -160.0);      //DINDING - DEPAN PALING KANAN 1
    glVertex3f(150.0, 50.0, -160.0);
    glVertex3f(110.0, 50.0, -160.0);
    glVertex3f(110.0, -10.0, -160.0);

    glVertex3f(110, 50, -100.0);           //DINDING - KANAN 2
    glVertex3f(110, -10.0, -100.0);
    glVertex3f(110, -10.0, -160.0);
    glVertex3f(110, 50, -160.0);

    glVertex3f(110.0, -10.0, -100.0);      //DINDING - DEPAN KANAN 2
    glVertex3f(110.0, 50.0, -100.0);
    glVertex3f(70.0, 50.0, -100.0);
    glVertex3f(70.0, -10.0, -100.0);
    glVertex3f(70, 50, -100.0);            //DINDING - DEPAN KANAN DALAM 1 (DARI KIRI)
    glVertex3f(70, -10.0, -100.0);
    glVertex3f(70, -10.0, -145.0);
    glVertex3f(70, 50, -145.0);
    glVertex3f(45, 50, -100.0);            //DINDING - DEPAN KANAN DALAM 2
    glVertex3f(45, -10.0, -100.0);
    glVertex3f(45, -10.0, -115.0);
    glVertex3f(45, 50, -115.0);
    glVertex3f(40, 50, -100.0);            //DINDING - DEPAN KANAN DALAM 3
    glVertex3f(40, -10.0, -100.0);
    glVertex3f(40, -10.0, -115.0);
    glVertex3f(40, 50, -115.0);
    glVertex3f(45.0, -10.0, -100.0);      //DINDING - DEPAN KANAN KECIL 1
    glVertex3f(45.0, 50.0, -100.0);
    glVertex3f(40.0, 50.0, -100.0);
    glVertex3f(40.0, -10.0, -100.0);
    glVertex3f(45.0, -10.0, -115.0);      //DINDING - DEPAN KANAN KECIL 2
    glVertex3f(45.0, 50.0, -115.0);
    glVertex3f(40.0, 50.0, -115.0);
    glVertex3f(40.0, -10.0, -115.0);
    glVertex3f(70.0, -10.0, -107.0);      //DINDING - DEPAN KANAN BAWAH 1
    glVertex3f(70.0, 10.0, -107.0);
    glVertex3f(45.0, 10.0, -107.0);
    glVertex3f(45.0, -10.0, -107.0);
    glVertex3f(70.0, -10.0, -115.0);      //DINDING - DEPAN KANAN BAWAH 2
    glVertex3f(70.0, 10.0, -115.0);
    glVertex3f(45.0, 10.0, -115.0);
    glVertex3f(45.0, -10.0, -115.0);
    glVertex3f(-70.0, 30.0, -115.0);       //DINDING - DEPAN ATAS
    glVertex3f(-70.0, 50.0, -115.0);
    glVertex3f(70.0, 50.0, -115.0);
    glVertex3f(70.0, 30.0, -115.0);

    glVertex3f(-150.0, -10.0, -460.0);      //DINDING - BELAKANG
    glVertex3f(-150.0, 50.0, -460.0);
    glVertex3f(150.0, 50.0, -460.0);
    glVertex3f(150.0, -10.0, -460.0);

    glVertex3f(-150.0, -10.0, -160.0);       //DINDING - SEKAT KIRI RUANG 1-2
    glVertex3f(-150.0, 50.0, -160.0);
    glVertex3f(-70.0, 50.0, -160.0);
    glVertex3f(-70.0, -10.0, -160.0);
    glVertex3f(-150.0, -10.0, -220.0);       //DINDING - SEKAT KIRI RUANG 2-3
    glVertex3f(-150.0, 50.0, -220.0);
    glVertex3f(-70.0, 50.0, -220.0);
    glVertex3f(-70.0, -10.0, -220.0);
    glVertex3f(-150.0, -10.0, -280.0);       //DINDING - SEKAT KIRI RUANG 3-4
    glVertex3f(-150.0, 50.0, -280.0);
    glVertex3f(-70.0, 50.0, -280.0);
    glVertex3f(-70.0, -10.0, -280.0);
    glVertex3f(-150.0, -10.0, -340.0);       //DINDING - SEKAT KIRI RUANG 4-5
    glVertex3f(-150.0, 50.0, -340.0);
    glVertex3f(-70.0, 50.0, -340.0);
    glVertex3f(-70.0, -10.0, -340.0);
    glVertex3f(-80.0, -10.0, -345.0);       //DINDING - SEKAT KIRI RUANG 5 DEPAN
    glVertex3f(-80.0, 30.0, -345.0);
    glVertex3f(-70.0, 30.0, -345.0);
    glVertex3f(-70.0, -10.0, -345.0);
    glVertex3f(-80.0, -10.0, -355.0);       //DINDING - SEKAT KIRI RUANG 5 BELAKANG
    glVertex3f(-80.0, 30.0, -355.0);
    glVertex3f(-70.0, 30.0, -355.0);
    glVertex3f(-70.0, -10.0, -355.0);
    glVertex3f(-150.0, -10.0, -400.0);      //DINDING - SEKAT KIRI RUANG 5-6
    glVertex3f(-150.0, 50.0, -400.0);
    glVertex3f(50.0, 50.0, -400.0);
    glVertex3f(50.0, -10.0, -400.0);
    glVertex3f(150.0, -10.0, -160.0);       //DINDING - SEKAT KANAN RUANG 1-2
    glVertex3f(150.0, 50.0, -160.0);
    glVertex3f(70.0, 50.0, -160.0);
    glVertex3f(70.0, -10.0, -160.0);
    glVertex3f(150.0, -10.0, -220.0);       //DINDING - SEKAT KANAN RUANG 2-3
    glVertex3f(150.0, 50.0, -220.0);
    glVertex3f(70.0, 50.0, -220.0);
    glVertex3f(70.0, -10.0, -220.0);
    glVertex3f(150.0, -10.0, -280.0);       //DINDING - SEKAT KANAN RUANG 3-4
    glVertex3f(150.0, 50.0, -280.0);
    glVertex3f(70.0, 50.0, -280.0);
    glVertex3f(70.0, -10.0, -280.0);
    glVertex3f(150.0, -10.0, -340.0);       //DINDING - SEKAT KANAN RUANG 4-5
    glVertex3f(150.0, 50.0, -340.0);
    glVertex3f(70.0, 50.0, -340.0);
    glVertex3f(70.0, -10.0, -340.0);
    glVertex3f(80.0, -10.0, -385.0);       //DINDING - SEKAT KANAN RUANG 5 DEPAN
    glVertex3f(80.0, 30.0, -385.0);
    glVertex3f(70.0, 30.0, -385.0);
    glVertex3f(70.0, -10.0, -385.0);
    glVertex3f(80.0, -10.0, -395.0);       //DINDING - SEKAT KANAN RUANG 5 BELAKANG
    glVertex3f(80.0, 30.0, -395.0);
    glVertex3f(70.0, 30.0, -395.0);
    glVertex3f(70.0, -10.0, -395.0);
    glEnd();
    //
    //

    //
    //INTERIOR
    glBegin(GL_QUADS);
    glColor3f(0.7, 0.4, 0.0);
    glVertex3f(-40.0, -8.0, -150.0);       //MEJA - DEPAN
    glVertex3f(-40.0, 15.0, -150.0);
    glVertex3f(40.0, 15.0, -150.0);
    glVertex3f(40.0, -8.0, -150.0);
    glVertex3f(-40.0, -8.0, -155.0);       //MEJA - BELAKANG PANJANG
    glVertex3f(-40.0, 10.0, -155.0);
    glVertex3f(40.0, 10.0, -155.0);
    glVertex3f(40.0, -8.0, -155.0);
    glVertex3f(-40.0, -8.0, -165.0);       //MEJA - BELAKANG PENDEK KIRI
    glVertex3f(-40.0, 10.0, -165.0);
    glVertex3f(-30.0, 10.0, -165.0);
    glVertex3f(-30.0, -8.0, -165.0);
    glVertex3f(40.0, -8.0, -165.0);        //MEJA - BELAKANG PENDEK KANAN
    glVertex3f(40.0, 10.0, -165.0);
    glVertex3f(30.0, 10.0, -165.0);
    glVertex3f(30.0, -8.0, -165.0);
    glVertex3f(-40, 15, -150.0);           //MEJA - KIRI 1
    glVertex3f(-40, -8.0, -150.0);
    glVertex3f(-40, -8.0, -165.0);
    glVertex3f(-40, 15, -165.0);
    glVertex3f(-30, 10, -155.0);           //MEJA - KIRI 2
    glVertex3f(-30, -8.0, -155.0);
    glVertex3f(-30, -8.0, -165.0);
    glVertex3f(-30, 10, -165.0);
    glVertex3f(40, 15, -150.0);            //MEJA - KANAN 1
    glVertex3f(40, -8.0, -150.0);
    glVertex3f(40, -8.0, -165.0);
    glVertex3f(40, 15, -165.0);

    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-40.0, -8.0, -170.0);       //DINDING - DEPAN
    glVertex3f(-40.0, 50.0, -170.0);
    glVertex3f(40.0, 50.0, -170.0);
    glVertex3f(40.0, -8.0, -170.0);
    glVertex3f(-40.0, -8.0, -180.0);       //DINDING - BELAKANG
    glVertex3f(-40.0, 50.0, -180.0);
    glVertex3f(40.0, 50.0, -180.0);
    glVertex3f(40.0, -8.0, -180.0);
    glVertex3f(-40, 50, -170.0);           //DINDING - KIRI
    glVertex3f(-40, -8.0, -170.0);
    glVertex3f(-40, -8.0, -180.0);
    glVertex3f(-40, 50, -180.0);
    glVertex3f(40, 50, -170.0);           //DINDING - KANAN
    glVertex3f(40, -8.0, -170.0);
    glVertex3f(40, -8.0, -180.0);
    glVertex3f(40, 50, -180.0);
    glVertex3f(70, 50, -100.0);            //DINDING - KIRI ATAS
    glVertex3f(70, 30.0, -100.0);
    glVertex3f(70, 30.0, -400.0);
    glVertex3f(70, 50, -400.0);
    glVertex3f(-70, 50, -100.0);           //DINDING - KANAN ATAS
    glVertex3f(-70, 30.0, -100.0);
    glVertex3f(-70, 30.0, -400.0);
    glVertex3f(-70, 50, -400.0);

    //
    //
    glVertex3f(-70, 30, -155.0);            //DINDING - KIRI RUANGAN 2
    glVertex3f(-70, -10.0, -155.0);
    glVertex3f(-70, -10.0, -205.0);
    glVertex3f(-70, 30, -205.0);
    glVertex3f(-70, 30, -215.0);            //DINDING - KIRI RUANGAN 3
    glVertex3f(-70, -10.0, -215.0);
    glVertex3f(-70, -10.0, -265.0);
    glVertex3f(-70, 30, -265.0);
    glVertex3f(-70, 30, -275.0);            //DINDING - KIRI RUANGAN 4
    glVertex3f(-70, -10.0, -275.0);
    glVertex3f(-70, -10.0, -325.0);
    glVertex3f(-70, 30, -325.0);
    glVertex3f(-70, 30, -335.0);            //DINDING - KIRI RUANGAN 5
    glVertex3f(-70, -10.0, -335.0);
    glVertex3f(-70, -10.0, -345.0);
    glVertex3f(-70, 30, -345.0);
    glVertex3f(-80, 30.0, -355.0);          //DINDING - KIRI ATAS PINTU RUANGAN 5
    glVertex3f(-70, 30.0, -355.0);
    glVertex3f(-70, 30.0, -345.0);
    glVertex3f(-80, 30.0, -345.0);
    glVertex3f(70, 30, -155.0);            //DINDING - KANAN RUANGAN 2
    glVertex3f(70, -10.0, -155.0);
    glVertex3f(70, -10.0, -205.0);
    glVertex3f(70, 30, -205.0);
    glVertex3f(70, 30, -215.0);            //DINDING - KANAN RUANGAN 3
    glVertex3f(70, -10.0, -215.0);
    glVertex3f(70, -10.0, -265.0);
    glVertex3f(70, 30, -265.0);
    glVertex3f(70, 30, -275.0);            //DINDING - KANAN RUANGAN 4
    glVertex3f(70, -10.0, -275.0);
    glVertex3f(70, -10.0, -325.0);
    glVertex3f(70, 30, -325.0);
    glVertex3f(70, 30, -335.0);            //DINDING - KANAN RUANGAN 5 DEPAN
    glVertex3f(70, -10.0, -335.0);
    glVertex3f(70, -10.0, -345.0);
    glVertex3f(70, 30, -345.0);
    glVertex3f(70, 50, -395.0);            //DINDING - KANAN RUANGAN 5 BELAKANG
    glVertex3f(70, -10.0, -395.0);
    glVertex3f(70, -10.0, -460.0);
    glVertex3f(70, 50, -460.0);
    glVertex3f(80, 30.0, -395.0);          //DINDING - ATAS PINTU RUANGAN 5
    glVertex3f(70, 30.0, -395.0);
    glVertex3f(70, 30.0, -385.0);
    glVertex3f(80, 30.0, -385.0);
    glVertex3f(50, 50, -400.0);            //DINDING - RUANGAN BELAKANG
    glVertex3f(50, -10.0, -400.0);
    glVertex3f(50, -10.0, -460.0);
    glVertex3f(50, 50, -460.0);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.60, 0.40, 0.0);
    glVertex3f(-70, 30, -145.0);            //PINTU - KIRI RUANGAN 1
    glVertex3f(-70, -10.0, -145.0);
    glVertex3f(-70, -10.0, -155.0);
    glVertex3f(-70, 30, -155.0);
    glVertex3f(-70, 30, -205.0);            //PINTU - KIRI RUANGAN 2
    glVertex3f(-70, -10.0, -205.0);
    glVertex3f(-70, -10.0, -215.0);
    glVertex3f(-70, 30, -215.0);
    glVertex3f(-70, 30, -265.0);            //PINTU - KIRI RUANGAN 3
    glVertex3f(-70, -10.0, -265.0);
    glVertex3f(-70, -10.0, -275.0);
    glVertex3f(-70, 30, -275.0);
    glVertex3f(-70, 30, -325.0);            //PINTU - KIRI RUANGAN 4
    glVertex3f(-70, -10.0, -325.0);
    glVertex3f(-70, -10.0, -335.0);
    glVertex3f(-70, 30, -335.0);
    glVertex3f(-80, 30, -345.0);            //PINTU - KIRI RUANGAN 5
    glVertex3f(-80, -10.0, -345.0);
    glVertex3f(-80, -10.0, -355.0);
    glVertex3f(-80, 30, -355.0);
    glVertex3f(70, 30, -145.0);            //PINTU - KANAN RUANGAN 1
    glVertex3f(70, -10.0, -145.0);
    glVertex3f(70, -10.0, -155.0);
    glVertex3f(70, 30, -155.0);
    glVertex3f(70, 30, -205.0);            //PINTU - KANAN RUANGAN 2
    glVertex3f(70, -10.0, -205.0);
    glVertex3f(70, -10.0, -215.0);
    glVertex3f(70, 30, -215.0);
    glVertex3f(70, 30, -265.0);            //PINTU - KANAN RUANGAN 3
    glVertex3f(70, -10.0, -265.0);
    glVertex3f(70, -10.0, -275.0);
    glVertex3f(70, 30, -275.0);
    glVertex3f(70, 30, -325.0);            //PINTU - KANAN RUANGAN 4
    glVertex3f(70, -10.0, -325.0);
    glVertex3f(70, -10.0, -335.0);
    glVertex3f(70, 30, -335.0);
    glVertex3f(80, 30, -385.0);            //PINTU - KANAN RUANGAN 5
    glVertex3f(80, -10.0, -385.0);
    glVertex3f(80, -10.0, -395.0);
    glVertex3f(80, 30, -395.0);
    glVertex3f(-90.0, -10.0, -399.9);       //PINTU - RUANG BELAKANG
    glVertex3f(-90.0, 30.0, -399.9);
    glVertex3f(-80.0, 30.0, -399.9);
    glVertex3f(-80.0, -10.0, -399.9);

    glColor3f(1, 0, 0);
    glVertex3f(-70, 3.0, -200.0);         //KURSI - KIRI ALAS 1
    glVertex3f(-62, 3.0, -200.0);
    glVertex3f(-62, 3.0, -160.0);
    glVertex3f(-70, 3.0, -160.0);
    glVertex3f(-70, 3.0, -260.0);         //KURSI - KIRI ALAS 2
    glVertex3f(-62, 3.0, -260.0);
    glVertex3f(-62, 3.0, -220.0);
    glVertex3f(-70, 3.0, -220.0);
    glVertex3f(-70, 3.0, -320.0);         //KURSI - KIRI ALAS 3
    glVertex3f(-62, 3.0, -320.0);
    glVertex3f(-62, 3.0, -280.0);
    glVertex3f(-70, 3.0, -280.0);
    glVertex3f(70, 3.0, -200.0);         //KURSI - KANAN ALAS 1
    glVertex3f(62, 3.0, -200.0);
    glVertex3f(62, 3.0, -160.0);
    glVertex3f(70, 3.0, -160.0);
    glVertex3f(70, 3.0, -260.0);         //KURSI - KANAN ALAS 2
    glVertex3f(62, 3.0, -260.0);
    glVertex3f(62, 3.0, -220.0);
    glVertex3f(70, 3.0, -220.0);
    glVertex3f(70, 3.0, -320.0);         //KURSI - KANAN ALAS 3
    glVertex3f(62, 3.0, -320.0);
    glVertex3f(62, 3.0, -280.0);
    glVertex3f(70, 3.0, -280.0);
    glVertex3f(-69.9, 13, -160.0);       //KURSI - KIRI SANDARAN 1
    glVertex3f(-69.9, 3.0, -160.0);
    glVertex3f(-69.9, 3.0, -200.0);
    glVertex3f(-69.9, 13, -200.0);
    glVertex3f(-69.9, 13, -220.0);       //KURSI - KIRI SANDARAN 2
    glVertex3f(-69.9, 3.0, -220.0);
    glVertex3f(-69.9, 3.0, -260.0);
    glVertex3f(-69.9, 13, -260.0);
    glVertex3f(-69.9, 13, -280.0);       //KURSI - KIRI SANDARAN 3
    glVertex3f(-69.9, 3.0, -280.0);
    glVertex3f(-69.9, 3.0, -320.0);
    glVertex3f(-69.9, 13, -320.0);
    glVertex3f(69.9, 13, -160.0);       //KURSI - KANAN SANDARAN 1
    glVertex3f(69.9, 3.0, -160.0);
    glVertex3f(69.9, 3.0, -200.0);
    glVertex3f(69.9, 13, -200.0);
    glVertex3f(69.9, 13, -220.0);       //KURSI - KANAN SANDARAN 2
    glVertex3f(69.9, 3.0, -220.0);
    glVertex3f(69.9, 3.0, -260.0);
    glVertex3f(69.9, 13, -260.0);
    glVertex3f(69.9, 13, -280.0);       //KURSI - KANAN SANDARAN 3
    glVertex3f(69.9, 3.0, -280.0);
    glVertex3f(69.9, 3.0, -320.0);
    glVertex3f(69.9, 13, -320.0);
    glVertex3f(-70.0, -8.0, -160.0);     //KURSI - KIRI 1 DEPAN
    glVertex3f(-70.0, 3.0, -160.0);
    glVertex3f(-68.0, 3.0, -160.0);
    glVertex3f(-68.0, -8.0, -160.0);
    glVertex3f(-64.0, -8.0, -160.0);     //KURSI - KIRI 1 DEPAN
    glVertex3f(-64.0, 3.0, -160.0);
    glVertex3f(-62.0, 3.0, -160.0);
    glVertex3f(-62.0, -8.0, -160.0);
    glVertex3f(-70.0, -8.0, -200.0);     //KURSI - KIRI 1 BELAKANG
    glVertex3f(-70.0, 3.0, -200.0);
    glVertex3f(-68.0, 3.0, -200.0);
    glVertex3f(-68.0, -8.0, -200.0);
    glVertex3f(-64.0, -8.0, -200.0);     //KURSI - KIRI 1 BELAKANG
    glVertex3f(-64.0, 3.0, -200.0);
    glVertex3f(-62.0, 3.0, -200.0);
    glVertex3f(-62.0, -8.0, -200.0);
    glVertex3f(-70.0, -8.0, -220.0);     //KURSI - KIRI 2 DEPAN
    glVertex3f(-70.0, 3.0, -220.0);
    glVertex3f(-68.0, 3.0, -220.0);
    glVertex3f(-68.0, -8.0, -220.0);
    glVertex3f(-64.0, -8.0, -220.0);     //KURSI - KIRI 2 DEPAN
    glVertex3f(-64.0, 3.0, -220.0);
    glVertex3f(-62.0, 3.0, -220.0);
    glVertex3f(-62.0, -8.0, -220.0);
    glVertex3f(-70.0, -8.0, -260.0);     //KURSI - KIRI 2 BELAKANG
    glVertex3f(-70.0, 3.0, -260.0);
    glVertex3f(-68.0, 3.0, -260.0);
    glVertex3f(-68.0, -8.0, -260.0);
    glVertex3f(-64.0, -8.0, -260.0);     //KURSI - KIRI 2 BELAKANG
    glVertex3f(-64.0, 3.0, -260.0);
    glVertex3f(-62.0, 3.0, -260.0);
    glVertex3f(-62.0, -8.0, -260.0);
    glVertex3f(-70.0, -8.0, -280.0);     //KURSI - KIRI 3 DEPAN
    glVertex3f(-70.0, 3.0, -280.0);
    glVertex3f(-68.0, 3.0, -280.0);
    glVertex3f(-68.0, -8.0, -280.0);
    glVertex3f(-64.0, -8.0, -280.0);     //KURSI - KIRI 3 DEPAN
    glVertex3f(-64.0, 3.0, -280.0);
    glVertex3f(-62.0, 3.0, -280.0);
    glVertex3f(-62.0, -8.0, -280.0);
    glVertex3f(-70.0, -8.0, -320.0);     //KURSI - KIRI 3 BELAKANG
    glVertex3f(-70.0, 3.0, -320.0);
    glVertex3f(-68.0, 3.0, -320.0);
    glVertex3f(-68.0, -8.0, -320.0);
    glVertex3f(-64.0, -8.0, -320.0);     //KURSI - KIRI 3 BELAKANG
    glVertex3f(-64.0, 3.0, -320.0);
    glVertex3f(-62.0, 3.0, -320.0);
    glVertex3f(-62.0, -8.0, -320.0);
    glVertex3f(70.0, -8.0, -160.0);     //KURSI - KANAN 1 DEPAN
    glVertex3f(70.0, 3.0, -160.0);
    glVertex3f(68.0, 3.0, -160.0);
    glVertex3f(68.0, -8.0, -160.0);
    glVertex3f(64.0, -8.0, -160.0);     //KURSI - KANAN 1 DEPAN
    glVertex3f(64.0, 3.0, -160.0);
    glVertex3f(62.0, 3.0, -160.0);
    glVertex3f(62.0, -8.0, -160.0);
    glVertex3f(70.0, -8.0, -200.0);     //KURSI - KANAN 1 BELAKANG
    glVertex3f(70.0, 3.0, -200.0);
    glVertex3f(68.0, 3.0, -200.0);
    glVertex3f(68.0, -8.0, -200.0);
    glVertex3f(64.0, -8.0, -200.0);     //KURSI - KANAN 1 BELAKANG
    glVertex3f(64.0, 3.0, -200.0);
    glVertex3f(62.0, 3.0, -200.0);
    glVertex3f(62.0, -8.0, -200.0);
    glVertex3f(70.0, -8.0, -220.0);     //KURSI - KANAN 2 DEPAN
    glVertex3f(70.0, 3.0, -220.0);
    glVertex3f(68.0, 3.0, -220.0);
    glVertex3f(68.0, -8.0, -220.0);
    glVertex3f(64.0, -8.0, -220.0);     //KURSI - KANAN 2 DEPAN
    glVertex3f(64.0, 3.0, -220.0);
    glVertex3f(62.0, 3.0, -220.0);
    glVertex3f(62.0, -8.0, -220.0);
    glVertex3f(70.0, -8.0, -260.0);     //KURSI - KANAN 2 BELAKANG
    glVertex3f(70.0, 3.0, -260.0);
    glVertex3f(68.0, 3.0, -260.0);
    glVertex3f(68.0, -8.0, -260.0);
    glVertex3f(64.0, -8.0, -260.0);     //KURSI - KANAN 2 BELAKANG
    glVertex3f(64.0, 3.0, -260.0);
    glVertex3f(62.0, 3.0, -260.0);
    glVertex3f(62.0, -8.0, -260.0);
    glVertex3f(70.0, -8.0, -280.0);     //KURSI - KANAN 3 DEPAN
    glVertex3f(70.0, 3.0, -280.0);
    glVertex3f(68.0, 3.0, -280.0);
    glVertex3f(68.0, -8.0, -280.0);
    glVertex3f(64.0, -8.0, -280.0);     //KURSI - KANAN 3 DEPAN
    glVertex3f(64.0, 3.0, -280.0);
    glVertex3f(62.0, 3.0, -280.0);
    glVertex3f(62.0, -8.0, -280.0);
    glVertex3f(70.0, -8.0, -320.0);     //KURSI - KANAN 3 BELAKANG
    glVertex3f(70.0, 3.0, -320.0);
    glVertex3f(68.0, 3.0, -320.0);
    glVertex3f(68.0, -8.0, -320.0);
    glVertex3f(64.0, -8.0, -320.0);     //KURSI - KANAN 3 BELAKANG
    glVertex3f(64.0, 3.0, -320.0);
    glVertex3f(62.0, 3.0, -320.0);
    glVertex3f(62.0, -8.0, -320.0);

    glColor3f(0.7, 0.4, 0.0);
    glVertex3f(-5.0, -8.0, -270.0);     //MEJA - PENAHAN 1 DEPAN
    glVertex3f(-5.0, 5.0, -270.0);
    glVertex3f(5.0, 5.0, -270.0);
    glVertex3f(5.0, -8.0, -270.0);
    glVertex3f(-5.0, -8.0, -280.0);     //MEJA - PENAHAN 1 DEPAN
    glVertex3f(-5.0, 5.0, -280.0);
    glVertex3f(5.0, 5.0, -280.0);
    glVertex3f(5.0, -8.0, -280.0);
    glVertex3f(-5.0, 5.0, -280.0);      //MEJA - PENAHAN 1 BELAKANG
    glVertex3f(-5.0, -10.0, -280.0);
    glVertex3f(-5.0, -10.0, -270.0);
    glVertex3f(-5.0, 5.0, -270.0);//
    glVertex3f(5.0, 5.0, -280.0);       //MEJA - PENAHAN 1 BELAKANG
    glVertex3f(5.0, -10.0, -280.0);
    glVertex3f(5.0, -10.0, -270.0);
    glVertex3f(5.0, 5.0, -270.0);//
    glColor3f(0.7, 0.4, 0.0);
    glVertex3f(-5.0, -8.0, -320.0);     //MEJA - PENAHAN 2 DEPAN
    glVertex3f(-5.0, 5.0, -320.0);
    glVertex3f(5.0, 5.0, -320.0);
    glVertex3f(5.0, -8.0, -320.0);
    glVertex3f(-5.0, -8.0, -330.0);     //MEJA - PENAHAN 2 DEPAN
    glVertex3f(-5.0, 5.0, -330.0);
    glVertex3f(5.0, 5.0, -330.0);
    glVertex3f(5.0, -8.0, -330.0);
    glVertex3f(-5.0, 5.0, -330.0);      //MEJA - PENAHAN 2 BELAKANG
    glVertex3f(-5.0, -10.0, -330.0);
    glVertex3f(-5.0, -10.0, -320.0);
    glVertex3f(-5.0, 5.0, -320.0);//
    glVertex3f(5.0, 5.0, -330.0);       //MEJA - PENAHAN 2 BELAKANG
    glVertex3f(5.0, -10.0, -330.0);
    glVertex3f(5.0, -10.0, -320.0);
    glVertex3f(5.0, 5.0, -320.0);//
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.7, 0.4, 0.0);
    glVertex3f(-20, 5.0, -275.0);         //MEJA - ALAS  1 DEPAN
    glVertex3f(-20, 5.0, -265.0);
    glVertex3f(-10, 5.0, -255.0);
    glVertex3f(10, 5.0, -255.0);
    glVertex3f(20, 5.0, -265.0);
    glVertex3f(20, 5.0, -275.0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.7, 0.4, 0.0);
    glVertex3f(-20, 5.0, -275.0);         //MEJA - ALAS 1 BELAKANG
    glVertex3f(-20, 5.0, -285.0);
    glVertex3f(-10, 5.0, -295.0);
    glVertex3f(10, 5.0, -295.0);
    glVertex3f(20, 5.0, -285.0);
    glVertex3f(20, 5.0, -275.0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.7, 0.4, 0.0);
    glVertex3f(-20, 5.0, -325.0);         //MEJA - ALAS 2 DEPAN
    glVertex3f(-20, 5.0, -315.0);
    glVertex3f(-10, 5.0, -305.0);
    glVertex3f(10, 5.0, -305.0);
    glVertex3f(20, 5.0, -315.0);
    glVertex3f(20, 5.0, -325.0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.7, 0.4, 0.0);
    glVertex3f(-20, 5.0, -325.0);         //MEJA - ALAS 2 BELAKANG
    glVertex3f(-20, 5.0, -335.0);
    glVertex3f(-10, 5.0, -345.0);
    glVertex3f(10, 5.0, -345.0);
    glVertex3f(20, 5.0, -335.0);
    glVertex3f(20, 5.0, -325.0);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-50.0, -10.0, -50.0);        //TIANG - 1 BELAKANG
    glVertex3f(-50.0, 60.0, -50.0);
    glVertex3f(-40.0, 60.0, -50.0);
    glVertex3f(-40.0, -10.0, -50.0);//
    glVertex3f(50.0, -10.0, -50.0);         //TIANG - 2 BELAKANG
    glVertex3f(50.0, 60.0, -50.0);
    glVertex3f(40.0, 60.0, -50.0);
    glVertex3f(40.0, -10.0, -50.0);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-50.0, 60.0, -50.0);         //TIANG - 1 KIRI
    glVertex3f(-50.0, -10.0, -50.0);
    glVertex3f(-60.0, -10.0, -35.0);
    glVertex3f(-60.0, 60.0, -35.0);//
    glVertex3f(-40.0, 60.0, -50.0);         //TIANG - 1 KANAN
    glVertex3f(-40.0, -10.0, -50.0);
    glVertex3f(-60.0, -10.0, -35.0);
    glVertex3f(-60.0, 60.0, -35.0);
    glVertex3f(50.0, 60.0, -50.0);          //TIANG - 2 KANAN
    glVertex3f(50.0, -10.0, -50.0);
    glVertex3f(60.0, -10.0, -35.0);
    glVertex3f(60.0, 60.0, -35.0);//
    glVertex3f(40.0, 60.0, -50.0);          //TIANG - 2 KIRI
    glVertex3f(40.0, -10.0, -50.0);
    glVertex3f(60.0, -10.0, -35.0);
    glVertex3f(60.0, 60.0, -35.0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1,1,1);
    glVertex3f(-50.0, 60.0, -50.0);         //TIANG - KECIL ATAS KIRI
    glVertex3f(-60.0, 60.0, -35.0);
    glVertex3f(-40.0, 60.0, -50.0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1,1,1);
    glVertex3f(50.0, 60.0, -50.0);         //TIANG - KECIL ATAS KIRI
    glVertex3f(60.0, 60.0, -35.0);
    glVertex3f(40.0, 60.0, -50.0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1,1,1);
    glVertex3f(-70, 50.0, -460.0);         //PLAFON KIRI
    glVertex3f(-70, 50.0, -100.0);
    glVertex3f(-110, 50.0, -100.0);
    glVertex3f(-110, 50.0, -160.0);
    glVertex3f(-150, 50.0, -160.0);
    glVertex3f(-150, 50.0, -460.0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1,1,1);
    glVertex3f(70, 50.0, -460.0);         //PLAFON KIRI
    glVertex3f(70, 50.0, -100.0);
    glVertex3f(110, 50.0, -100.0);
    glVertex3f(110, 50.0, -160.0);
    glVertex3f(150, 50.0, -160.0);
    glVertex3f(150, 50.0, -460.0);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0, 1.0, 0);                   //ALAS DASAR
    glVertex3f(-160, -10.0, -470.0);
    glVertex3f(160, -10.0, -470.0);
    glVertex3f(160, -10.0, -90.0);
    glVertex3f(-160, -10.0, -90.0);

    glColor3f(0.70, 0.70, 0.70);
    glVertex3f(-110, -6.0, -460.0);         //LANTAI DASAR - INTERIOR TENGAH
    glVertex3f(110, -6.0, -460.0);
    glVertex3f(110, -6.0, -100.0);
    glVertex3f(-110, -6.0, -100.0);
    glVertex3f(-150, -6.0, -460.0);         //LANTAI DASAR - INTERIOR KIRI
    glVertex3f(-110, -6.0, -460.0);
    glVertex3f(-110, -6.0, -160.0);
    glVertex3f(-150, -6.0, -160.0);
    glVertex3f(150, -6.0, -460.0);          //LANTAI DASAR - INTERIOR KANAN
    glVertex3f(110, -6.0, -460.0);
    glVertex3f(110, -6.0, -160.0);
    glVertex3f(150, -6.0, -160.0);

    glColor3f(0.70, 0.70, 0.70);
    glVertex3f(-70, 50.0, -180.0);         //PLAFON - DEPAN BESAR
    glVertex3f(70, 50.0, -180.0);
    glVertex3f(70, 50.0, -100.0);
    glVertex3f(-70, 50.0, -100.0);
    glColor3f(0.70, 0.70, 0.70);
    glVertex3f(-70, 50.0, -220.0);         //PLAFON - DEPAN KIRI
    glVertex3f(-40, 50.0, -220.0);
    glVertex3f(-40, 50.0, -180.0);
    glVertex3f(-70, 50.0, -180.0);
    glVertex3f(-20, 50.0, -220.0);         //PLAFON - DEPAN TENGAH
    glVertex3f(20, 50.0, -220.0);
    glVertex3f(20, 50.0, -180.0);
    glVertex3f(-20, 50.0, -180.0);
    glVertex3f(70, 50.0, -220.0);         //PLAFON - DEPAN KANAN
    glVertex3f(40, 50.0, -220.0);
    glVertex3f(40, 50.0, -180.0);
    glVertex3f(70, 50.0, -180.0);
    glColor3f(1,1,1);
    glVertex3f(-70, 50.0, -460.0);         //PLAFON - BELAKANG
    glVertex3f(70, 50.0, -460.0);
    glVertex3f(70, 50.0, -400.0);
    glVertex3f(-70, 50.0, -400.0);

    glColor3f(0.80, 0.40, 0.2);             //TANGGA ALAS
    glVertex3f(-40, -8, -100.0);
    glVertex3f(40, -8, -100.0);
    glVertex3f(40, -8, -98.0);
    glVertex3f(-40, -8, -98.0);
    glVertex3f(-40.0, -8.0, -100.0);        //TANGGA - KECIL KIRI
    glVertex3f(-40.0, -10.0, -100.0);
    glVertex3f(-40.0, -10.0, -98.0);
    glVertex3f(-40.0, -8.0, -98.0);//
    glVertex3f(40.0, -8.0, -100.0);         //TANGGA - KECIL KIRI
    glVertex3f(40.0, -10.0, -100.0);
    glVertex3f(40.0, -10.0, -98.0);
    glVertex3f(40.0, -8.0, -98.0);//
    glVertex3f(-40.0, -10.0, -100.0);       //TANGGA - KECIL BELAKANG
    glVertex3f(-40.0, -6.0, -100.0);
    glVertex3f(40.0, -6.0, -100.0);
    glVertex3f(40.0, -10.0, -100.0);//
    glVertex3f(-40.0, -10.0, -98.0);        //TANGGA - KECIL DEPAN
    glVertex3f(-40.0, -8.0, -98.0);
    glVertex3f(40.0, -8.0, -98.0);
    glVertex3f(40.0, -10.0, -98.0);//
    glColor3f(0.9, 0.9, 0.9);               //LANTAI DEPAN
    glVertex3f(-40, -9.9, -98.0);
    glVertex3f(40, -9.9, -98.0);
    glVertex3f(50, -9.9, -90.0);
    glVertex3f(-50, -9.9, -90.0);

    glVertex3f(-150, -10, -90.0);           //JALAN DEPAN
    glVertex3f(150, -10, -90.0);
    glVertex3f(150, -10, 50.0);
    glVertex3f(-150, -10, 50.0);

    glColor3f(0.80, 0.40, 0.2);
    glVertex3f(-70.0, -10.0, -100.0);       //PENUTUP - LANTAI BAWAH KIRI
    glVertex3f(-70.0, -6.0, -100.0);
    glVertex3f(-45.0, -6.0, -100.0);
    glVertex3f(-45.0, -10.0, -100.0);//
    glVertex3f(70.0, -10.0, -100.0);       //PENUTUP - LANTAI BAWAH KANAN
    glVertex3f(70.0, -6.0, -100.0);
    glVertex3f(45.0, -6.0, -100.0);
    glVertex3f(45.0, -10.0, -100.0);//

    glColor3f(0.80, 0.40, 0.2);             //PENUTUP - TERAS ATAS
    glVertex3f(-50, 55.0, -110.0);
    glVertex3f(50, 55.0, -110.0);
    glVertex3f(54.5, 55.0, -45.0);
    glVertex3f(-54.5, 55.0, -45.0);
    glVertex3f(-50, 155.0, -250.0);         //ATAP - DEPAN TENGAH
    glVertex3f(50, 155.0, -250.0);
    glVertex3f(50, 50.0, -100.0);
    glVertex3f(-50, 50.0, -100.0);/*
    glVertex3f(-50, 155.0, -250.0);         //ATAP - BELAKANG TENGAH
    glVertex3f(50, 155.0, -250.0);
    glVertex3f(50, 50.0, -460.0);
    glVertex3f(-50, 50.0, -460.0);*/
    glVertex3f(-110, 149.0, -250.0);         //ATAP - BELAKANG KIRI
    glVertex3f(-50, 149.0, -250.0);
    glVertex3f(-50, 50.0, -460.0);
    glVertex3f(-110, 50.0, -460.0);
    glVertex3f(110, 149.0, -250.0);         //ATAP - BELAKANG KANAN
    glVertex3f(50, 149.0, -250.0);
    glVertex3f(50, 50.0, -460.0);
    glVertex3f(110, 50.0, -460.0);
    glVertex3f(-150, 100.0, -310.0);         //ATAP - DEPAN PALING KIRI
    glVertex3f(-110, 100.0, -310.0);
    glVertex3f(-110, 50.0, -160.0);
    glVertex3f(-150, 50.0, -160.0);
    glVertex3f(-150, 100.0, -310.0);         //ATAP - BELAKANG PALING KIRI
    glVertex3f(-110, 100.0, -310.0);
    glVertex3f(-110, 50.0, -460.0);
    glVertex3f(-150, 50.0, -460.0);
    glVertex3f(150, 100.0, -310.0);         //ATAP - DEPAN PALING KANAN
    glVertex3f(110, 100.0, -310.0);
    glVertex3f(110, 50.0, -160.0);
    glVertex3f(150, 50.0, -160.0);
    glVertex3f(150, 100.0, -310.0);         //ATAP - BELAKANG PALING KANAN
    glVertex3f(110, 100.0, -310.0);
    glVertex3f(110, 50.0, -460.0);
    glVertex3f(150, 50.0, -460.0);
    glColor3f(1,1,1);                       //PENUTUP - DEPAN BAWAH
    glVertex3f(-50, 50.0, -100.0);
    glVertex3f(50, 50.0, -100.0);
    glVertex3f(54.5, 50.0, -45.0);
    glVertex3f(-54.5, 50.0, -45.0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.80, 0.40, 0.2);
    glVertex3f(-50, 150.0, -250.0);         //ATAP - DEPAN KIRI
    glVertex3f(-90, 150.0, -250.0);
    glVertex3f(-90, 130.0, -230.0);
    glVertex3f(-110, 130.0, -230.0);
    glVertex3f(-110, 50.0, -100.0);
    glVertex3f(-50, 50.0, -100.0);
    glVertex3f(50, 150.0, -250.0);          //ATAP - DEPAN KANAN
    glVertex3f(90, 150.0, -250.0);
    glVertex3f(90, 130.0, -230.0);
    glVertex3f(110, 130.0, -230.0);
    glVertex3f(110, 50.0, -100.0);
    glVertex3f(50, 50.0, -100.0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.80, 0.40, 0.2);
    glVertex3f(0.0, 155.0, -250.0);         //ATAP - KECIL KIRI
    glVertex3f(0.0, 155.0, -165.0);
    glVertex3f(-70.0, 65.0, -165.0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.80, 0.40, 0.2);
    glVertex3f(0.0, 155.0, -250.0);         //ATAP - KECIL KANAN
    glVertex3f(0.0, 155.0, -165.0);
    glVertex3f(70.0, 65.0, -165.0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-42, 100.0, -175.0);         //DINDING - DEPAN ATAS
    glVertex3f(0, 155.0, -175.0);
    glVertex3f(42, 100.0, -175.0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-150.0, 50.0, -460.0);         //DINDING - ATAS PALING KIRI
    glVertex3f(-150.0, 100.0, -310.0);
    glVertex3f(-150.0, 50.0, -160.0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-110.0, 50.0, -460.0);         //DINDING - ATAS KIRI KEDUA
    glVertex3f(-110.0, 150.0, -250.0);
    glVertex3f(-110.0, 130.0, -250.0);
    glVertex3f(-110.0, 130.0, -230.0);
    glVertex3f(-110.0, 50.0, -100.0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-70.0, 50.0, -460.0);         //DINDING - ATAS KIRI KETIGA
    glVertex3f(-70.0, 144.0, -250.0);
    glVertex3f(-70.0, 50.0, -100.0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-50.0, 155.0, -250.0);         //DINDING - ATAS KIRI KEEMPAT
    glVertex3f(-50.0, 50.0, -460.0);
    glVertex3f(-50.0, 50.0, -455.0);
    glVertex3f(-50.0, 150.0, -245.0);
    glVertex3f(-50.0, 50.0, -105.0);
    glVertex3f(-50.0, 50.0, -100.0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(150.0, 50.0, -460.0);         //DINDING - ATAS KANAN PALING KANAN
    glVertex3f(150.0, 100.0, -310.0);
    glVertex3f(150.0, 50.0, -160.0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(110.0, 50.0, -460.0);         //DINDING - ATAS KANAN KEDUA
    glVertex3f(110.0, 150.0, -250.0);
    glVertex3f(110.0, 130.0, -250.0);
    glVertex3f(110.0, 130.0, -230.0);
    glVertex3f(110.0, 50.0, -100.0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(70.0, 50.0, -460.0);           //DINDING - ATAS KANAN KETIGA
    glVertex3f(70.0, 144.0, -250.0);
    glVertex3f(70.0, 50.0, -100.0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(50.0, 155.0, -250.0);         //DINDING - ATAS KANAN KEEMPAT
    glVertex3f(50.0, 50.0, -460.0);
    glVertex3f(50.0, 50.0, -455.0);
    glVertex3f(50.0, 150.0, -245.0);
    glVertex3f(50.0, 50.0, -105.0);
    glVertex3f(50.0, 50.0, -100.0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-110, 130.0, -250.0);            //DINDING - ATAS POJOK KIRI 1
    glVertex3f(-110, 130.0, -230.0);
    glVertex3f(-90, 130.0, -230.0);
    glVertex3f(-90, 130.0, -250.0);
    glVertex3f(-90, 150.0, -250.0);
    glVertex3f(-110, 150.0, -250.0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(-90.0, 150.0, -250.0);         //DINDING - ATAS POJOK KIRI 2
    glVertex3f(-90.0, 130.0, -250.0);
    glVertex3f(-90.0, 130.0, -230.0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(110, 130.0, -250.0);            //DINDING - ATAS POJOK KANAN 1
    glVertex3f(110, 130.0, -230.0);
    glVertex3f(90, 130.0, -230.0);
    glVertex3f(90, 130.0, -250.0);
    glVertex3f(90, 150.0, -250.0);
    glVertex3f(110, 150.0, -250.0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3f(90.0, 150.0, -250.0);         //DINDING - ATAS POJOK KANAN 2
    glVertex3f(90.0, 130.0, -250.0);
    glVertex3f(90.0, 130.0, -230.0);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.80, 0.40, 0.2);
    glVertex3f(-50.0, 40.0, -99.9);            //PENUTUP - ATAS KIRI 3 (DARI DALAM)
    glVertex3f(-50.0, 60.0, -99.9);
    glVertex3f(-55.0, 60.0, -40.0);
    glVertex3f(-55.0, 40.0, -40.0);
    glVertex3f(-110.1, 40.0, -159.9);          //PENUTUP - ATAS KIRI 2
    glVertex3f(-110.1, 60.0, -159.9);
    glVertex3f(-110.1, 60.0, -99.9);
    glVertex3f(-110.1, 40.0, -99.9);
    glVertex3f(-110.1, -10.0, -159.9);          //PENUTUP - BAWAH KIRI 2
    glVertex3f(-110.1, 0.0, -159.9);
    glVertex3f(-110.1, 0.0, -99.9);
    glVertex3f(-110.1, -10.0, -99.9);
    glVertex3f(-150.1, 40.0, -460.1);           //PENUTUP - ATAS KIRI 1
    glVertex3f(-150.1, 60.0, -460.1);
    glVertex3f(-150.1, 60.0, -159.9);
    glVertex3f(-150.1, 40.0, -159.9);
    glVertex3f(-150.1, -10.0, -460.1);          //PENUTUP - BAWAH KIRI 1
    glVertex3f(-150.1, 0.0, -460.1);
    glVertex3f(-150.1, 0.0, -159.9);
    glVertex3f(-150.1, -10.0, -159.9);
    glVertex3f(50.0, 40.0, -99.9);             //PENUTUP - ATAS KANAN 3
    glVertex3f(50.0, 60.0, -99.9);
    glVertex3f(55.0, 60.0, -40.0);
    glVertex3f(55.0, 40.0, -40.0);
    glVertex3f(110.1, 40.0, -159.9);            //PENUTUP - ATAS KANAN 2
    glVertex3f(110.1, 60.0, -159.9);
    glVertex3f(110.1, 60.0, -99.9);
    glVertex3f(110.1, 40.0, -99.9);
    glVertex3f(110.1, -10.0, -159.9);          //PENUTUP - BAWAH KANAN 2
    glVertex3f(110.1, 0.0, -159.9);
    glVertex3f(110.1, 0.0, -99.9);
    glVertex3f(110.1, -10.0, -99.9);
    glVertex3f(150.1, 40.0, -460.1);            //PENUTUP - ATAS KANAN 1
    glVertex3f(150.1, 60.0, -460.1);
    glVertex3f(150.1, 60.0, -159.9);
    glVertex3f(150.1, 40.0, -159.9);
    glVertex3f(150.1, -10.0, -460.1);          //PENUTUP - BAWAH KANAN 1
    glVertex3f(150.1, 0.0, -460.1);
    glVertex3f(150.1, 0.0, -159.9);
    glVertex3f(150.1, -10.0, -159.9);
    glVertex3f(-50.0, 40.0, -45.0);             //PENUTUP - ATAS DEPAN
    glVertex3f(-50.0, 60.0, -45.0);
    glVertex3f(50.0, 60.0, -45.0);
    glVertex3f(50.0, 40.0, -45.0);//
    glVertex3f(-110.1, 40.0, -99.9);            //PENUTUP - ATAS KIRI 1
    glVertex3f(-110.1, 60.0, -99.9);
    glVertex3f(-50.0, 60.0, -99.9);
    glVertex3f(-50.0, 40.0, -99.9);//
    glVertex3f(-110.1, -10.0, -99.9);            //PENUTUP - BAWAH KIRI 1
    glVertex3f(-110.1, 0.0, -99.9);
    glVertex3f(-70.0, 0.0, -99.9);
    glVertex3f(-70.0, -10.0, -99.9);//
    glVertex3f(-150.1, 40.0, -159.9);           //PENUTUP - ATAS KIRI 2
    glVertex3f(-150.1, 60.0, -159.9);
    glVertex3f(-110.1, 60.0, -159.9);
    glVertex3f(-110.1, 40.0, -159.9);//
    glVertex3f(-150.1, -10.0, -159.9);           //PENUTUP - BAWAH KIRI 2
    glVertex3f(-150.1, 0.0, -159.9);
    glVertex3f(-110.1, 00.0, -159.9);
    glVertex3f(-110.1, -10.0, -159.9);//
    glVertex3f(110.1, 40.0, -99.9);             //PENUTUP - ATAS KANAN 1
    glVertex3f(110.1, 60.0, -99.9);
    glVertex3f(50.0, 60.0, -99.9);
    glVertex3f(50.0, 40.0, -99.9);//
    glVertex3f(110.1, -10.0, -99.9);           //PENUTUP - BAWAH KANAN 1
    glVertex3f(110.1, 0.0, -99.9);
    glVertex3f(70.0, 0.0, -99.9);
    glVertex3f(70.0, -10.0, -99.9);//
    glVertex3f(150.1, 40.0, -159.9);            //PENUTUP - ATAS KANAN 2
    glVertex3f(150.1, 60.0, -159.9);
    glVertex3f(110.1, 60.0, -159.9);
    glVertex3f(110.1, 40.0, -159.9);//
    glVertex3f(150.1, -10.0, -159.9);          //PENUTUP - BAWAH KANAN 2
    glVertex3f(150.1, 0.0, -159.9);
    glVertex3f(110.1, 00.0, -159.9);
    glVertex3f(110.1, -10.0, -159.9);//
    glVertex3f(-150.1, 40.0, -460.1);           //PENUTUP - ATAS BELAKANG
    glVertex3f(-150.1, 60.0, -460.1);
    glVertex3f(150.1, 60.0, -460.1);
    glVertex3f(150.1, 40.0, -460.1);//
    glVertex3f(-150.1, -10.0, -460.1);           //PENUTUP - ATAS BELAKANG
    glVertex3f(-150.1, 0.0, -460.1);
    glVertex3f(150.1, 0.0, -460.1);
    glVertex3f(150.1, -10.0, -460.1);//
    glVertex3f(-45.0, -10.0, -99.9);            //PENUTUP - DEPAN BAWAH KIRI KECIL
    glVertex3f(-45.0, 0.0, -99.9);
    glVertex3f(-40.0, 0.0, -99.9);
    glVertex3f(-40.0, -10.0, -99.9);//
    glVertex3f(45.0, -10.0, -99.9);             //PENUTUP - DEPAN BAWAH KANAN KECIL
    glVertex3f(45.0, 0.0, -99.9);
    glVertex3f(40.0, 0.0, -99.9);
    glVertex3f(40.0, -10.0, -99.9);//
    glVertex3f(-70.0, -10.0, -106.9);            //PENUTUP - DEPAN POT KIRI
    glVertex3f(-70.0, 0.0, -106.9);
    glVertex3f(-45.0, 0.0, -106.9);
    glVertex3f(-45.0, -10.0, -106.9);//
    glVertex3f(70.0, -10.0, -106.9);            //PENUTUP - DEPAN POT KANAN
    glVertex3f(70.0, 0.0, -106.9);
    glVertex3f(45.0, 0.0, -106.9);
    glVertex3f(45.0, -10.0, -106.9);//

    glColor3f(0,0,0);
    glVertex3f(-145.0, 10.0, -460.1);             //JENDELA - BELAKANG 1
    glVertex3f(-145.0, 30.0, -460.1);
    glVertex3f(-125.0, 30.0, -460.1);
    glVertex3f(-125.0, 10.0, -460.1);//
    glVertex3f(-115.0, 10.0, -460.1);             //JENDELA - BELAKANG 2
    glVertex3f(-115.0, 30.0, -460.1);
    glVertex3f(-95.0, 30.0, -460.1);
    glVertex3f(-95.0, 10.0, -460.1);//
    glVertex3f(-85.0, 10.0, -460.1);             //JENDELA - BELAKANG 3
    glVertex3f(-85.0, 30.0, -460.1);
    glVertex3f(-65.0, 30.0, -460.1);
    glVertex3f(-65.0, 10.0, -460.1);//
    glVertex3f(-55.0, 10.0, -460.1);             //JENDELA - BELAKANG 4
    glVertex3f(-55.0, 30.0, -460.1);
    glVertex3f(-35.0, 30.0, -460.1);
    glVertex3f(-35.0, 10.0, -460.1);//
    glVertex3f(-25.0, 10.0, -460.1);             //JENDELA - BELAKANG 5
    glVertex3f(-25.0, 30.0, -460.1);
    glVertex3f(-5, 30.0, -460.1);
    glVertex3f(-5, 10.0, -460.1);//
    glVertex3f(145.0, 10.0, -460.1);            //JENDELA - BELAKANG 6
    glVertex3f(145.0, 30.0, -460.1);
    glVertex3f(125.0, 30.0, -460.1);
    glVertex3f(125.0, 10.0, -460.1);//
    glVertex3f(115.0, 10.0, -460.1);            //JENDELA - BELAKANG 7
    glVertex3f(115.0, 30.0, -460.1);
    glVertex3f(95.0, 30.0, -460.1);
    glVertex3f(95.0, 10.0, -460.1);//
    glVertex3f(85.0, 10.0, -460.1);             //JENDELA - BELAKANG 8
    glVertex3f(85.0, 30.0, -460.1);
    glVertex3f(65.0, 30.0, -460.1);
    glVertex3f(65.0, 10.0, -460.1);//
    glVertex3f(55.0, 10.0, -460.1);             //JENDELA - BELAKANG 9
    glVertex3f(55.0, 30.0, -460.1);
    glVertex3f(35.0, 30.0, -460.1);
    glVertex3f(35.0, 10.0, -460.1);//
    glVertex3f(25.0, 10.0, -460.1);             //JENDELA - BELAKANG 10
    glVertex3f(25.0, 30.0, -460.1);
    glVertex3f(5, 30.0, -460.1);
    glVertex3f(5, 10.0, -460.1);//
    glVertex3f(-150.1, 10.0, -185);             //JENDELA - KIRI 1
    glVertex3f(-150.1, 30.0, -185);
    glVertex3f(-150.1, 30.0, -165);
    glVertex3f(-150.1, 10.0, -165);
    glVertex3f(-150.1, 10.0, -215);             //JENDELA - KIRI 2
    glVertex3f(-150.1, 30.0, -215);
    glVertex3f(-150.1, 30.0, -195);
    glVertex3f(-150.1, 10.0, -195);
    glVertex3f(-150.1, 10.0, -245);             //JENDELA - KIRI 3
    glVertex3f(-150.1, 30.0, -245);
    glVertex3f(-150.1, 30.0, -225);
    glVertex3f(-150.1, 10.0, -225);
    glVertex3f(-150.1, 10.0, -275);             //JENDELA - KIRI 4
    glVertex3f(-150.1, 30.0, -275);
    glVertex3f(-150.1, 30.0, -255);
    glVertex3f(-150.1, 10.0, -255);
    glVertex3f(-150.1, 10.0, -305);             //JENDELA - KIRI 5
    glVertex3f(-150.1, 30.0, -305);
    glVertex3f(-150.1, 30.0, -285);
    glVertex3f(-150.1, 10.0, -285);
    glVertex3f(-150.1, 10.0, -335);             //JENDELA - KIRI 6
    glVertex3f(-150.1, 30.0, -335);
    glVertex3f(-150.1, 30.0, -315);
    glVertex3f(-150.1, 10.0, -315);
    glVertex3f(-150.1, 10.0, -365);             //JENDELA - KIRI 7
    glVertex3f(-150.1, 30.0, -365);
    glVertex3f(-150.1, 30.0, -345);
    glVertex3f(-150.1, 10.0, -345);
    glVertex3f(-150.1, 10.0, -395);             //JENDELA - KIRI 8
    glVertex3f(-150.1, 30.0, -395);
    glVertex3f(-150.1, 30.0, -375);
    glVertex3f(-150.1, 10.0, -375);
    glVertex3f(-150.1, 10.0, -425);             //JENDELA - KIRI 9
    glVertex3f(-150.1, 30.0, -425);
    glVertex3f(-150.1, 30.0, -405);
    glVertex3f(-150.1, 10.0, -405);
    glVertex3f(-150.1, 10.0, -455);             //JENDELA - KIRI 10
    glVertex3f(-150.1, 30.0, -455);
    glVertex3f(-150.1, 30.0, -435);
    glVertex3f(-150.1, 10.0, -435);
    glVertex3f(150.1, 10.0, -185);             //JENDELA - KANAN 1
    glVertex3f(150.1, 30.0, -185);
    glVertex3f(150.1, 30.0, -165);
    glVertex3f(150.1, 10.0, -165);
    glVertex3f(150.1, 10.0, -215);             //JENDELA - KANAN 2
    glVertex3f(150.1, 30.0, -215);
    glVertex3f(150.1, 30.0, -195);
    glVertex3f(150.1, 10.0, -195);
    glVertex3f(150.1, 10.0, -245);             //JENDELA - KANAN 3
    glVertex3f(150.1, 30.0, -245);
    glVertex3f(150.1, 30.0, -225);
    glVertex3f(150.1, 10.0, -225);
    glVertex3f(150.1, 10.0, -275);             //JENDELA - KANAN 4
    glVertex3f(150.1, 30.0, -275);
    glVertex3f(150.1, 30.0, -255);
    glVertex3f(150.1, 10.0, -255);
    glVertex3f(150.1, 10.0, -305);             //JENDELA - KANAN 5
    glVertex3f(150.1, 30.0, -305);
    glVertex3f(150.1, 30.0, -285);
    glVertex3f(150.1, 10.0, -285);
    glVertex3f(150.1, 10.0, -335);             //JENDELA - KANAN 6
    glVertex3f(150.1, 30.0, -335);
    glVertex3f(150.1, 30.0, -315);
    glVertex3f(150.1, 10.0, -315);
    glVertex3f(150.1, 10.0, -365);             //JENDELA - KANAN 7
    glVertex3f(150.1, 30.0, -365);
    glVertex3f(150.1, 30.0, -345);
    glVertex3f(150.1, 10.0, -345);
    glVertex3f(150.1, 10.0, -395);             //JENDELA - KANAN 8
    glVertex3f(150.1, 30.0, -395);
    glVertex3f(150.1, 30.0, -375);
    glVertex3f(150.1, 10.0, -375);
    glVertex3f(150.1, 10.0, -425);             //JENDELA - KANAN 9
    glVertex3f(150.1, 30.0, -425);
    glVertex3f(150.1, 30.0, -405);
    glVertex3f(150.1, 10.0, -405);
    glVertex3f(150.1, 10.0, -455);             //JENDELA - KANAN 10
    glVertex3f(150.1, 30.0, -455);
    glVertex3f(150.1, 30.0, -435);
    glVertex3f(150.1, 10.0, -435);
    glEnd();


    glPopMatrix();
    glutSwapBuffers();
}

void idle() {
    if (!mouseDown) {
        xrot += 0.3f;
        yrot += 0.4f;
    }

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        mouseDown = true;
        xdiff = x - yrot;
        ydiff = -y + xrot;
    }
    else
        mouseDown = false;
}

void mouseMotion(int x, int y) {
    if (mouseDown) {
        yrot = x - xdiff;
        xrot = y + ydiff;

        glutPostRedisplay();
    }
}
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
    case 'W':
        zmov += 3.0;
        break;
    case 'd':
    case 'D':
        xmov += 3.0;
        break;
    case 's':
    case 'S':
        zmov -= 3.0;
        break;
    case 'a':
    case 'A':
        xmov -= 3.0;
        break;
    case '7':
        ymov += 3.0;
        break;
    case '9':
        ymov -= 3.0;
        break;
    case '2':
        glRotatef(2.0, 1.0, 0.0, 0.0);
        break;
    case '8':
        glRotatef(-2.0, 1.0, 0.0, 0.0);
        break;
    case '6':
        glRotatef(2.0, 0.0, 1.0, 0.0);
        break;
    case '4':
        glRotatef(-2.0, 0.0, 1.0, 0.0);
        break;
    case '1':
        glRotatef(2.0, 0.0, 0.0, 1.0);
        break;
    case '3':
        glRotatef(-2.0, 0.0, 0.0, 1.0);
        break;
    case '5':
        if (is_depth)
        {
            is_depth = 0;
            glDisable(GL_DEPTH_TEST);
        }
        else
        {
            is_depth = 1;
            glEnable(GL_DEPTH_TEST);
        }
    }
    tampil();
}

void ukuran(int lebar, int tinggi)
{
    if (tinggi == 0) tinggi = 1;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0, lebar / tinggi, 5.0, 500.0);
    glTranslatef(0.0, -5.0, -150.0);
    glMatrixMode(GL_MODELVIEW);
}
