#include <GL/glut.h>
#include <windows.h>
#include <stdbool.h>

void init(void);
void tampil(void);
void keyboard(unsigned char, int, int);
void mouse(int, int, int, int);
void mouseMotion(int, int);
void ukuran(int, int);

int is_depth;

float xrot = 0.0f;
float yrot = 0.0f;
float zrot = 0.0f;
float xdiff = 0.0f;
float ydiff = 0.0f;
bool mouseDown = false;

float xmov = 0.0f;
float ymov = 0.0f;
float zmov = 0.0f;

int gerak = 0;
bool atas = true;

void timer(int t)
{
    if (atas) {
    ulang:
        gerak += 1;
    }

    if (gerak > 20) {
        gerak = 0;
        goto ulang;
    }

    glutPostRedisplay();
    //kecepatan mobil berbanding terbalik
    //semakin besar nilai glutTimerFunc jika ingin mengganti kecepatan
    //silahkan ganti angka 50 di bawah ini, misal 100 mobil akan semakin lambat
    //dibawah 50 mobil akan semakin cepat
    glutTimerFunc(100, timer, 0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1280, 720);
    glutInitWindowPosition(150, 80);
    glutCreateWindow("3D");
    init();
    glutDisplayFunc(tampil);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);

    glutReshapeFunc(ukuran);
    glutTimerFunc(1, timer, 0);
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
    glPointSize(15.0); //UKURAN TITIK
    glLineWidth(2.0);
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
    glRotatef(zrot, 0.0f, 0.0f, 1.0f);

    glTranslatef(xmov, ymov, zmov);
    glPushMatrix();


    //update bintang
    //bintang 1
    float a1x = 50, a1y = 210, a2x = 60, a2y = 220, a3x = 42, a3y = 212, a4x = 58, a4y = 212,
        b1x = 50, b1y = 230, b2x = 40, b2y = 220, b3x = 58, b3y = 228, b4x = 42, b4y = 228,
        Ma1b1, Ca1b1, Ma2b2, Ca2b2, Ma3b3, Ca3b3, Ma4b4, Ca4b4,
        px1, py1, px2, py2, px3, py3, px4, py4;
    glBegin(GL_LINES);
    //kuning
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(a1x, a1y, -200);
    glVertex3f(b1x, b1y, -200);
    glEnd();
    glBegin(GL_LINES);
    //biru
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(a2x, a2y, -200);
    glVertex3f(b2x, b2y, -200);
    glEnd();
    glBegin(GL_LINES);
    //hijau
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(a3x, a3y, -200);
    glVertex3f(b3x, b3y, -200);
    glEnd();
    glBegin(GL_LINES);
    //hitam
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(a4x, a4y, -200);
    glVertex3f(b4x, b4y, -200);
    glEnd();
    //rumus perpotongan
        //kuning
    Ma1b1 = (b1y - a1y) / (b1x - a1x);
    Ca1b1 = a1y - (a1x * Ma1b1);
    //biru
    Ma2b2 = (b2y - a2y) / (b2x - a2x);
    Ca2b2 = a2y - (a2x * Ma2b2);
    //hijau
    Ma3b3 = (b3y - a3y) / (b3x - a3x);
    Ca3b3 = a3y - (a3x * Ma3b3);
    //hitam
    Ma4b4 = (b4y - a4y) / (b4x - a4x);
    Ca4b4 = a4y - (a4x * Ma4b4);
    //titik potong
        //kiri bawah
    px1 = (Ca4b4 - Ca1b1) / (Ma1b1 - Ma4b4);
    py1 = (Ma1b1 * px1) + Ca1b1;
    //kiri atas
    px2 = (Ca2b2 - Ca1b1) / (Ma1b1 - Ma2b2);
    py2 = (Ma1b1 * px2) + Ca1b1;
    //kanan atas
    px3 = (Ca3b3 - Ca2b2) / (Ma2b2 - Ma3b3);
    py3 = (Ma2b2 * px3) + Ca2b2;
    //kanan Bawah
    px4 = (Ca4b4 - Ca3b3) / (Ma3b3 - Ma4b4);
    py4 = (Ma3b3 * px4) + Ca3b3;
    //hasil
        //Kiri Bawah
    glBegin(GL_POINTS);
    glColor3f(1, 0, 0);
    glVertex3f(px1, py1, -200);
    glEnd();
    //kiri Atas
    glBegin(GL_POINTS);
    glColor3f(1, 0, 0);
    glVertex3f(px2, py2, -200);
    glEnd();
    //kanan Atas
    glBegin(GL_POINTS);
    glColor3f(1, 0, 0);
    glVertex3f(px3, py3, -200);
    glEnd();
    //Kanan Bawah
    glBegin(GL_POINTS);
    glColor3f(1, 0, 0);
    glVertex3f(px4, py4, -200);
    glEnd();


    //bintang 2
    float za1x = 50, za1y = 210, za2x = 60, za2y = 220, za3x = 42, za3y = 212, za4x = 58, za4y = 212,
        zb1x = 50, zb1y = 230, zb2x = 40, zb2y = 220, zb3x = 58, zb3y = 228, zb4x = 42, zb4y = 228,
        zMa1b1, zCa1b1, zMa2b2, zCa2b2, zMa3b3, zCa3b3, zMa4b4, zCa4b4,
        zpx1, zpy1, zpx2, zpy2, zpx3, zpy3, zpx4, zpy4;
    glBegin(GL_LINES);
    //kuning
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(za1x, za1y, -100);
    glVertex3f(zb1x, zb1y, -100);
    glEnd();
    glBegin(GL_LINES);
    //biru
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(za2x, za2y, -100);
    glVertex3f(zb2x, zb2y, -100);
    glEnd();
    glBegin(GL_LINES);
    //hijau
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(za3x, za3y, -100);
    glVertex3f(zb3x, zb3y, -100);
    glEnd();
    glBegin(GL_LINES);
    //hitam
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(za4x, za4y, -100);
    glVertex3f(zb4x, zb4y, -100);
    glEnd();
    //rumus perpotongan
        //kuning
    zMa1b1 = (zb1y - za1y) / (zb1x - za1x);
    zCa1b1 = za1y - (za1x * zMa1b1);
    //biru
    zMa2b2 = (zb2y - za2y) / (zb2x - za2x);
    zCa2b2 = za2y - (za2x * zMa2b2);
    //hijau
    zMa3b3 = (zb3y - za3y) / (zb3x - za3x);
    zCa3b3 = za3y - (za3x * zMa3b3);
    //hitam
    zMa4b4 = (zb4y - za4y) / (zb4x - za4x);
    zCa4b4 = za4y - (za4x * zMa4b4);
    //titik potong
        //kiri bawah
    zpx1 = (zCa4b4 - zCa1b1) / (zMa1b1 - zMa4b4);
    zpy1 = (zMa1b1 * zpx1) + zCa1b1;
    //kiri atas
    zpx2 = (zCa2b2 - zCa1b1) / (zMa1b1 - zMa2b2);
    zpy2 = (zMa1b1 * zpx2) + zCa1b1;
    //kanan atas
    zpx3 = (zCa3b3 - zCa2b2) / (zMa2b2 - zMa3b3);
    zpy3 = (zMa2b2 * zpx3) + zCa2b2;
    //kanan Bawah
    zpx4 = (zCa4b4 - zCa3b3) / (zMa3b3 - zMa4b4);
    zpy4 = (zMa3b3 * zpx4) + zCa3b3;
    //hasil
        //Kiri Bawah
    glBegin(GL_POINTS);
    glColor3f(1, 0, 0);
    glVertex3f(zpx1, zpy1, -100);
    glEnd();
    //kiri Atas
    glBegin(GL_POINTS);
    glVertex3f(zpx2, zpy2, -100);
    glEnd();
    //kanan Atas
    glBegin(GL_POINTS);
    glVertex3f(zpx3, zpy3, -100);
    glEnd();
    //Kanan Bawah
    glBegin(GL_POINTS);
    glVertex3f(zpx4, zpy4, -100);
    glEnd();

    //bintang 3
    float xa1x = -50, xa1y = 210, xa2x = -60, xa2y = 220, xa3x = -42, xa3y = 212, xa4x = -58, xa4y = 212,
        xb1x = -50, xb1y = 230, xb2x = -40, xb2y = 220, xb3x = -58, xb3y = 228, xb4x = -42, xb4y = 228,
        xMa1b1, xCa1b1, xMa2b2, xCa2b2, xMa3b3, xCa3b3, xMa4b4, xCa4b4,
        xpx1, xpy1, xpx2, xpy2, xpx3, xpy3, xpx4, xpy4;
    glBegin(GL_LINES);
    //kuning
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(xa1x, xa1y, -200);
    glVertex3f(xb1x, xb1y, -200);
    glEnd();
    glBegin(GL_LINES);
    //biru
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(xa2x, xa2y, -200);
    glVertex3f(xb2x, xb2y, -200);
    glEnd();
    glBegin(GL_LINES);
    //hijau
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(xa3x, xa3y, -200);
    glVertex3f(xb3x, xb3y, -200);
    glEnd();
    glBegin(GL_LINES);
    //hitam
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(xa4x, xa4y, -200);
    glVertex3f(xb4x, xb4y, -200);
    glEnd();
    //rumus perpotongan
        //kuning
    xMa1b1 = (xb1y - xa1y) / (xb1x - xa1x);
    xCa1b1 = xa1y - (xa1x * xMa1b1);
    //biru
    xMa2b2 = (xb2y - xa2y) / (xb2x - xa2x);
    xCa2b2 = xa2y - (xa2x * xMa2b2);
    //hijau
    xMa3b3 = (xb3y - xa3y) / (xb3x - xa3x);
    xCa3b3 = xa3y - (xa3x * xMa3b3);
    //hitam
    xMa4b4 = (xb4y - xa4y) / (xb4x - xa4x);
    xCa4b4 = xa4y - (xa4x * xMa4b4);
    //titik potong
        //kiri bawah
    xpx1 = (xCa4b4 - xCa1b1) / (xMa1b1 - xMa4b4);
    xpy1 = (xMa1b1 * xpx1) + xCa1b1;
    //kiri atas
    xpx2 = (xCa2b2 - xCa1b1) / (xMa1b1 - xMa2b2);
    xpy2 = (xMa1b1 * xpx2) + xCa1b1;
    //kanan atas
    xpx3 = (xCa3b3 - xCa2b2) / (xMa2b2 - xMa3b3);
    xpy3 = (xMa2b2 * xpx3) + xCa2b2;
    //kanan Bawah
    xpx4 = (xCa4b4 - xCa3b3) / (xMa3b3 - xMa4b4);
    xpy4 = (xMa3b3 * xpx4) + xCa3b3;
    //hasil
        //Kiri Bawah
    glBegin(GL_POINTS);
    glColor3f(1, 0, 0);
    glVertex3f(xpx1, xpy1, -200);
    glEnd();
    //kiri Atas
    glBegin(GL_POINTS);
    glVertex3f(xpx2, xpy2, -200);
    glEnd();
    //kanan Atas
    glBegin(GL_POINTS);
    glVertex3f(xpx3, xpy3, -200);
    glEnd();
    //Kanan Bawah
    glBegin(GL_POINTS);
    glVertex3f(xpx4, xpy4, -200);
    glEnd();

    //bintang 4
    float sa1x = -50, sa1y = 210, sa2x = -60, sa2y = 220, sa3x = -42, sa3y = 212, sa4x = -58, sa4y = 212,
        sb1x = -50, sb1y = 230, sb2x = -40, sb2y = 220, sb3x = -58, sb3y = 228, sb4x = -42, sb4y = 228,
        sMa1b1, sCa1b1, sMa2b2, sCa2b2, sMa3b3, sCa3b3, sMa4b4, sCa4b4,
        spx1, spy1, spx2, spy2, spx3, spy3, spx4, spy4;
    glBegin(GL_LINES);
    //kuning
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(sa1x, sa1y, -100);
    glVertex3f(sb1x, sb1y, -100);
    glEnd();
    glBegin(GL_LINES);
    //biru
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(sa2x, sa2y, -100);
    glVertex3f(sb2x, sb2y, -100);
    glEnd();
    glBegin(GL_LINES);
    //hijau
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(sa3x, sa3y, -100);
    glVertex3f(sb3x, sb3y, -100);
    glEnd();
    glBegin(GL_LINES);
    //hitam
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(sa4x, sa4y, -100);
    glVertex3f(sb4x, sb4y, -100);
    glEnd();
    //rumus perpotongan
        //kuning
    sMa1b1 = (sb1y - sa1y) / (sb1x - sa1x);
    sCa1b1 = sa1y - (sa1x * sMa1b1);
    //biru
    sMa2b2 = (sb2y - sa2y) / (sb2x - sa2x);
    sCa2b2 = sa2y - (sa2x * sMa2b2);
    //hijau
    sMa3b3 = (sb3y - sa3y) / (sb3x - sa3x);
    sCa3b3 = sa3y - (sa3x * sMa3b3);
    //hitam
    sMa4b4 = (sb4y - sa4y) / (sb4x - sa4x);
    sCa4b4 = sa4y - (sa4x * sMa4b4);
    //titik potong
        //kiri bawah
    spx1 = (sCa4b4 - sCa1b1) / (sMa1b1 - sMa4b4);
    spy1 = (sMa1b1 * spx1) + sCa1b1;
    //kiri atas
    spx2 = (sCa2b2 - sCa1b1) / (sMa1b1 - sMa2b2);
    spy2 = (sMa1b1 * spx2) + sCa1b1;
    //kanan atas
    spx3 = (sCa3b3 - sCa2b2) / (sMa2b2 - sMa3b3);
    spy3 = (sMa2b2 * spx3) + sCa2b2;
    //kanan Bawah
    spx4 = (sCa4b4 - sCa3b3) / (sMa3b3 - sMa4b4);
    spy4 = (sMa3b3 * spx4) + sCa3b3;
    //hasil
        //Kiri Bawah
    glBegin(GL_POINTS);
    glColor3f(1, 0, 0);
    glVertex3f(spx1, spy1, -100);
    glEnd();
    //kiri Atas
    glBegin(GL_POINTS);
    glVertex3f(spx2, spy2, -100);
    glEnd();
    //kanan Atas
    glBegin(GL_POINTS);
    glVertex3f(spx3, spy3, -100);
    glEnd();
    //Kanan Bawah
    glBegin(GL_POINTS);
    glVertex3f(spx4, spy4, -100);
    glEnd();
    //update bintang


    glBegin(GL_QUADS);
    glColor3f(0.6, 0.6, 0.0);//alasdasar
    glVertex3f(-100.0, -10.0, 0.0);
    glVertex3f(100.0, -10.0, 0.0);
    glVertex3f(100.0, -10.0, -300.0);
    glVertex3f(-100.0, -10.0, -300.0);
    glColor3f(0.6, 0.6, 0.6);
    glVertex3f(-20.0, -9.9, 0.0);//jalankiri
    glVertex3f(-10.0, -9.9, 0.0);
    glVertex3f(-10.0, -9.9, -105.0);
    glVertex3f(-20.0, -9.9, -105.0);
    glVertex3f(20.0, -9.9, 0.0);//jalankanan
    glVertex3f(10.0, -9.9, 0.0);
    glVertex3f(10.0, -9.9, -105.0);
    glVertex3f(20.0, -9.9, -105.0);
    glVertex3f(10.0, -9.9, -30.0);//jalan tengah pertama
    glVertex3f(-10.0, -9.9, -30.0);
    glVertex3f(-10.0, -9.9, -40.0);
    glVertex3f(10.0, -9.9, -40.0);
    glVertex3f(5.0, -9.9, -20.0);//alas batu
    glVertex3f(-5.0, -9.9, -20.0);
    glVertex3f(-5.0, -9.9, -25.0);
    glVertex3f(5.0, -9.9, -25.0);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(3.0, -9.8, -22);//depan batu
    glVertex3f(-3.0, -9.8, -22);
    glVertex3f(-3.0, 0, -22);
    glVertex3f(3.0, 0, -22);
    glVertex3f(3.0, -9.8, -24);//belakang batu
    glVertex3f(-3.0, -9.8, -24);
    glVertex3f(-3.0, 0, -24);
    glVertex3f(3.0, 0, -24);
    glVertex3f(3.0, -9.8, -22);//sisikanan batu
    glVertex3f(3.0, -9.8, -24);
    glVertex3f(3.0, 0, -24);
    glVertex3f(3.0, 0, -22);
    glVertex3f(-3.0, -9.8, -24);//sisikiri batu
    glVertex3f(-3.0, -9.8, -22);
    glVertex3f(-3.0, 0, -22);
    glVertex3f(-3.0, 0, -24);
    glVertex3f(-3.0, 0, -24);//tutupatas batu
    glVertex3f(3.0, 0, -24);
    glVertex3f(3.0, 0, -22);
    glVertex3f(-3.0, 0, -22);
    glColor3f(0.0, 1.0, 1.0);
    glVertex3f(-3.0, -9.9, -92);//alas kolam
    glVertex3f(3.0, -9.9, -92);
    glVertex3f(3.0, -9.9, -42);
    glVertex3f(-3.0, -9.9, -42);
    glColor3f(0.4, 0.4, 0.4);
    glVertex3f(-3.0, -9.9, -42);//list depan kolam
    glVertex3f(3.0, -9.9, -42);
    glVertex3f(3.0, -7.9, -42);
    glVertex3f(-3.0, -7.9, -42);
    glVertex3f(-3.0, -9.9, -92);//list belakang kolam
    glVertex3f(3.0, -9.9, -92);
    glVertex3f(3.0, -7.9, -92);
    glVertex3f(-3.0, -7.9, -92);
    glVertex3f(3.0, -9.9, -92);//list kanan kolam
    glVertex3f(3.0, -9.9, -42);
    glVertex3f(3.0, -7.9, -42);
    glVertex3f(3.0, -7.9, -92);
    glVertex3f(-3.0, -9.9, -92);//list kiri kolam
    glVertex3f(-3.0, -9.9, -42);
    glVertex3f(-3.0, -7.9, -42);
    glVertex3f(-3.0, -7.9, -92);
    glColor3f(0.6, 0.6, 0.6);
    glVertex3f(-30.0, -9.9, -105.0);//jalankiri kedua
    glVertex3f(-20.0, -9.9, -105.0);
    glVertex3f(-20.0, -9.9, -165.0);
    glVertex3f(-30.0, -9.9, -165.0);
    glVertex3f(30.0, -9.9, -105.0);//jalankanan kedua
    glVertex3f(20.0, -9.9, -105.0);
    glVertex3f(20.0, -9.9, -165.0);
    glVertex3f(30.0, -9.9, -165.0);

    glColor3f(0.4, 0.4, 0.4);
    glVertex3f(-10.0, -9.9, -115);//list depan airmancur
    glVertex3f(10.0, -9.9, -115);
    glVertex3f(10.0, -5.9, -115);
    glVertex3f(-10.0, -5.9, -115);
    glVertex3f(-10.0, -9.9, -155);//list belakang airmancur
    glVertex3f(10.0, -9.9, -155);
    glVertex3f(10.0, -5.9, -155);
    glVertex3f(-10.0, -5.9, -155);
    glVertex3f(20.0, -9.9, -145);//list kanan airmancur
    glVertex3f(20.0, -9.9, -125);
    glVertex3f(20.0, -5.9, -125);
    glVertex3f(20.0, -5.9, -145);
    glVertex3f(-20.0, -9.9, -145);//list kiri airmancur
    glVertex3f(-20.0, -9.9, -125);
    glVertex3f(-20.0, -5.9, -125);
    glVertex3f(-20.0, -5.9, -145);

    //UPDATE
    //UPDATE

    glVertex3f(-20.0, -9.9, -125);//list DEPAN KIRI
    glVertex3f(-10.0, -9.9, -115);
    glVertex3f(-10.0, -5.9, -115);
    glVertex3f(-20.0, -5.9, -125);
    glVertex3f(20.0, -9.9, -125);//list DEPAN KANAN
    glVertex3f(10.0, -9.9, -115);
    glVertex3f(10.0, -5.9, -115);
    glVertex3f(20.0, -5.9, -125);
    glVertex3f(-20.0, -9.9, -145);//list BELAKANG KIRI
    glVertex3f(-10.0, -9.9, -155);
    glVertex3f(-10.0, -5.9, -155);
    glVertex3f(-20.0, -5.9, -145);
    glVertex3f(20.0, -9.9, -145);//list BELAKANG KANAN
    glVertex3f(10.0, -9.9, -155);
    glVertex3f(10.0, -5.9, -155);
    glVertex3f(20.0, -5.9, -145);

    glColor3f(0.6, 0.6, 0.6);
    glVertex3f(-20.0, -9.9, -165.0);//jalankiri ketiga
    glVertex3f(-10.0, -9.9, -165.0);
    glVertex3f(-10.0, -9.9, -290.0);
    glVertex3f(-20.0, -9.9, -290.0);
    glVertex3f(20.0, -9.9, -165.0);//jalankanan ketiga
    glVertex3f(10.0, -9.9, -165.0);
    glVertex3f(10.0, -9.9, -290.0);
    glVertex3f(20.0, -9.9, -290.0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.0, 1.0, 1.0);
    glVertex3f(-20.0, -9.5, -135);//alas airmancur
    glVertex3f(-20.0, -9.5, -145);
    glVertex3f(-10.0, -9.5, -155);
    glVertex3f(10.0, -9.5, -155);
    glVertex3f(20.0, -9.5, -145);
    glVertex3f(20.0, -9.5, -135);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.0, 1.0, 1.0);
    glVertex3f(-20.0, -9.5, -135);//alas airmancur
    glVertex3f(-20.0, -9.5, -125);
    glVertex3f(-10.0, -9.5, -115);
    glVertex3f(10.0, -9.5, -115);
    glVertex3f(20.0, -9.5, -125);
    glVertex3f(20.0, -9.5, -135);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.6, 0.6);
    glVertex3f(20.0, -9.9, -105.0);//jalan tengah KEDUA
    glVertex3f(20.0, -9.9, -125.0);
    glVertex3f(10.0, -9.9, -115.0);
    glVertex3f(-10.0, -9.9, -115.0);
    glVertex3f(-20.0, -9.9, -125.0);
    glVertex3f(-20.0, -9.9, -105.0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.6, 0.6);
    glVertex3f(-20.0, -9.9, -165.0);//jalan tengah KETIGA
    glVertex3f(20.0, -9.9, -165.0);
    glVertex3f(20.0, -9.9, -145.0);
    glVertex3f(10.0, -9.9, -155.0);
    glVertex3f(-10.0, -9.9, -155.0);
    glVertex3f(-20.0, -9.9, -145.0);
    glEnd();

    //UPDATE
    //UPDATE

    //update
    //update
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(6.5, -6.9, -23.0);//sisikiri pot kanan
    glVertex3f(6.5, -6.9, -25.0);
    glVertex3f(6.5, -9.9, -25.0);
    glVertex3f(6.5, -9.9, -23.0);
    glVertex3f(8.5, -6.9, -23.0);//sisikanan pot kanan
    glVertex3f(8.5, -6.9, -25.0);
    glVertex3f(8.5, -9.9, -25.0);
    glVertex3f(8.5, -9.9, -23.0);
    glVertex3f(6.5, -6.9, -25.0);//sisibelakang pot kanan
    glVertex3f(6.5, -9.9, -25.0);
    glVertex3f(8.5, -9.9, -25.0);
    glVertex3f(8.5, -6.9, -25.0);
    glVertex3f(6.5, -6.9, -23.0);//sisidepan pot kanan
    glVertex3f(6.5, -9.9, -23.0);
    glVertex3f(8.5, -9.9, -23.0);
    glVertex3f(8.5, -6.9, -23.0);
    glColor3f(0.2, 0.2, 0);
    glVertex3f(6.5, -7.5, -23.0);//tanah
    glVertex3f(6.5, -7.5, -25.0);
    glVertex3f(8.5, -7.5, -25.0);
    glVertex3f(8.5, -7.5, -23.0);
    glColor3f(0.0, 1.0, 0);
    glVertex3f(7, -7.4, -23.5);//rumput
    glVertex3f(7, -7.4, -24.5);
    glVertex3f(8, -7.4, -24.5);
    glVertex3f(8, -7.4, -23.5);

    glColor3f(1, 1, 1);
    glVertex3f(-6.5, -6.9, -23.0);//sisikiri pot kiri
    glVertex3f(-6.5, -6.9, -25.0);
    glVertex3f(-6.5, -9.9, -25.0);
    glVertex3f(-6.5, -9.9, -23.0);
    glVertex3f(-8.5, -6.9, -23.0);//sisikanan pot kiri
    glVertex3f(-8.5, -6.9, -25.0);
    glVertex3f(-8.5, -9.9, -25.0);
    glVertex3f(-8.5, -9.9, -23.0);
    glVertex3f(-6.5, -6.9, -25.0);//sisibelakang pot kiri
    glVertex3f(-6.5, -9.9, -25.0);
    glVertex3f(-8.5, -9.9, -25.0);
    glVertex3f(-8.5, -6.9, -25.0);
    glVertex3f(-6.5, -6.9, -23.0);//sisidepan pot kiri
    glVertex3f(-6.5, -9.9, -23.0);
    glVertex3f(-8.5, -9.9, -23.0);
    glVertex3f(-8.5, -6.9, -23.0);
    glColor3f(0.2, 0.2, 0);
    glVertex3f(-6.5, -7.5, -23.0);//tanah
    glVertex3f(-6.5, -7.5, -25.0);
    glVertex3f(-8.5, -7.5, -25.0);
    glVertex3f(-8.5, -7.5, -23.0);
    glColor3f(0.0, 1.0, 0);
    glVertex3f(-7, -7.4, -23.5);//rumput
    glVertex3f(-7, -7.4, -24.5);
    glVertex3f(-8, -7.4, -24.5);
    glVertex3f(-8, -7.4, -23.5);

    glColor3f(1.0, 1.0, 1.0);//pertama
    glVertex3f(6.5, -9.9, -41);//lampu taman bawah kanan
    glVertex3f(6.5, -9.9, -44);
    glVertex3f(9, -9.9, -44);
    glVertex3f(9, -9.9, -41);
    glVertex3f(6.5, -9.9, -171);//lampu taman bawah kanan
    glVertex3f(6.5, -9.9, -174);
    glVertex3f(9, -9.9, -174);
    glVertex3f(9, -9.9, -171);
    glVertex3f(-6.5, -9.9, -41);//lampu taman bawah kiri
    glVertex3f(-6.5, -9.9, -44);
    glVertex3f(-9, -9.9, -44);
    glVertex3f(-9, -9.9, -41);
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(7, -9.8, -41.5);//lampu taman bawah tutup kanan
    glVertex3f(7, -9.8, -43.5);
    glVertex3f(8.5, -9.8, -43.5);
    glVertex3f(8.5, -9.8, -41.5);
    glVertex3f(-7, -9.8, -41.5);//lampu taman bawah tutup kiri
    glVertex3f(-7, -9.8, -43.5);
    glVertex3f(-8.5, -9.8, -43.5);
    glVertex3f(-8.5, -9.8, -41.5);
    glColor3f(1.0, 1.0, 1.0);//kedua
    glVertex3f(6.5, -9.9, -96);//lampu taman bawah kanan
    glVertex3f(6.5, -9.9, -99);
    glVertex3f(9, -9.9, -99);
    glVertex3f(9, -9.9, -96);
    glVertex3f(-6.5, -9.9, -96);//lampu taman bawah kiri
    glVertex3f(-6.5, -9.9, -99);
    glVertex3f(-9, -9.9, -99);
    glVertex3f(-9, -9.9, -96);
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(7, -9.8, -96.5);//lampu taman bawah tutup kanan
    glVertex3f(7, -9.8, -98.5);
    glVertex3f(8.5, -9.8, -98.5);
    glVertex3f(8.5, -9.8, -96.5);
    glVertex3f(-7, -9.8, -96.5);//lampu taman bawah tutup kiri
    glVertex3f(-7, -9.8, -98.5);
    glVertex3f(-8.5, -9.8, -98.5);
    glVertex3f(-8.5, -9.8, -96.5);
    glColor3f(0.8, 0.8, 0.8); //lampu tiang taman kanan
    glVertex3f(7.5, -9.8, -66.5);//sisi kiri
    glVertex3f(7.5, -9.8, -67.5);
    glVertex3f(7.5, 4.8, -67.5);
    glVertex3f(7.5, 4.8, -66.5);
    glVertex3f(8.5, -9.8, -66.5);//sisi kanan
    glVertex3f(8.5, -9.8, -67.5);
    glVertex3f(8.5, 4.8, -67.5);
    glVertex3f(8.5, 4.8, -66.5);
    glVertex3f(7.5, -9.8, -66.5);//sisi depan
    glVertex3f(8.5, -9.8, -66.5);
    glVertex3f(8.5, 4.8, -66.5);
    glVertex3f(7.5, 4.8, -66.5);
    glVertex3f(7.5, -9.8, -67.5);//sisi belakang
    glVertex3f(8.5, -9.8, -67.5);
    glVertex3f(8.5, 4.8, -67.5);
    glVertex3f(7.5, 4.8, -67.5);
    glVertex3f(6.5, 4.9, -68.5);//tutup
    glVertex3f(9.5, 4.9, -68.5);
    glVertex3f(9.5, 4.9, -65.5);
    glVertex3f(6.5, 4.9, -65.5);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(7, 5, -68);//panel surya
    glVertex3f(9, 5, -68);
    glVertex3f(9, 5, -66);
    glVertex3f(7, 5, -66);
    glVertex3f(8.5, 1.8, -66.5);//tiangkekanan
    glVertex3f(12.5, 3.8, -66.5);
    glVertex3f(12.5, 3.8, -67.5);
    glVertex3f(8.5, 1.8, -67.5);
    glColor3f(1, 1, 0);
    glVertex3f(11.5, 3.2, -66.5);//tiangkekanan
    glVertex3f(12.5, 3.7, -66.5);
    glVertex3f(12.5, 3.7, -67.5);
    glVertex3f(11.5, 3.2, -67.5);
    glColor3f(0.8, 0.8, 0.8); //lampu tiang taman kiri
    glVertex3f(-7.5, -9.8, -66.5);//sisi kiri
    glVertex3f(-7.5, -9.8, -67.5);
    glVertex3f(-7.5, 4.8, -67.5);
    glVertex3f(-7.5, 4.8, -66.5);
    glVertex3f(-8.5, -9.8, -66.5);//sisi kanan
    glVertex3f(-8.5, -9.8, -67.5);
    glVertex3f(-8.5, 4.8, -67.5);
    glVertex3f(-8.5, 4.8, -66.5);
    glVertex3f(-7.5, -9.8, -66.5);//sisi depan
    glVertex3f(-8.5, -9.8, -66.5);
    glVertex3f(-8.5, 4.8, -66.5);
    glVertex3f(-7.5, 4.8, -66.5);
    glVertex3f(-7.5, -9.8, -67.5);//sisi belakang
    glVertex3f(-8.5, -9.8, -67.5);
    glVertex3f(-8.5, 4.8, -67.5);
    glVertex3f(-7.5, 4.8, -67.5);
    glVertex3f(-6.5, 4.9, -68.5);//tutup
    glVertex3f(-9.5, 4.9, -68.5);
    glVertex3f(-9.5, 4.9, -65.5);
    glVertex3f(-6.5, 4.9, -65.5);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-7, 5, -68);//panel surya
    glVertex3f(-9, 5, -68);
    glVertex3f(-9, 5, -66);
    glVertex3f(-7, 5, -66);
    glVertex3f(-8.5, 1.8, -66.5);//tiangkekiri
    glVertex3f(-12.5, 3.8, -66.5);
    glVertex3f(-12.5, 3.8, -67.5);
    glVertex3f(-8.5, 1.8, -67.5);
    glColor3f(1, 1, 0);
    glVertex3f(-11.5, 3.2, -66.5);//bohlam
    glVertex3f(-12.5, 3.7, -66.5);
    glVertex3f(-12.5, 3.7, -67.5);
    glVertex3f(-11.5, 3.2, -67.5);
    glColor3f(0.4, 0.0, 0.4);//rumput baris
    glVertex3f(6.5, -7.9, -46);// kanan pertama, sisi alas
    glVertex3f(6.5, -7.9, -64);
    glVertex3f(9, -7.9, -64);
    glVertex3f(9, -7.9, -46);
    glVertex3f(6.5, -9.9, -46);// kanan pertama, sisi kiri
    glVertex3f(6.5, -9.9, -64);
    glVertex3f(6.5, -7.9, -64);
    glVertex3f(6.5, -7.9, -46);
    glVertex3f(9, -9.9, -46);// kanan pertama, sisi kanan
    glVertex3f(9, -9.9, -64);
    glVertex3f(9, -7.9, -64);
    glVertex3f(9, -7.9, -46);
    glVertex3f(6.5, -9.9, -46);// kanan pertama, sisi depan
    glVertex3f(6.5, -7.9, -46);
    glVertex3f(9, -7.9, -46);
    glVertex3f(9, -9.9, -46);
    glVertex3f(6.5, -9.9, -64);// kanan pertama, sisi belakang
    glVertex3f(6.5, -7.9, -64);
    glVertex3f(9, -7.9, -64);
    glVertex3f(9, -9.9, -64);
    glVertex3f(6.5, -7.9, -70);// kanan kedua, sisi alas
    glVertex3f(6.5, -7.9, -94);
    glVertex3f(9, -7.9, -94);
    glVertex3f(9, -7.9, -70);
    glVertex3f(6.5, -9.9, -70);// kanan kedua, sisi kiri
    glVertex3f(6.5, -9.9, -94);
    glVertex3f(6.5, -7.9, -94);
    glVertex3f(6.5, -7.9, -70);
    glVertex3f(9, -9.9, -70);// kanan kedua, sisi kanan
    glVertex3f(9, -9.9, -94);
    glVertex3f(9, -7.9, -94);
    glVertex3f(9, -7.9, -70);
    glVertex3f(6.5, -9.9, -70);// kanan kedua, sisi depan
    glVertex3f(6.5, -7.9, -70);
    glVertex3f(9, -7.9, -70);
    glVertex3f(9, -9.9, -70);
    glVertex3f(6.5, -9.9, -94);// kanan kedua, sisi belakang
    glVertex3f(6.5, -7.9, -94);
    glVertex3f(9, -7.9, -94);
    glVertex3f(9, -9.9, -94);
    glVertex3f(-6.5, -7.9, -46);// kiri pertama, sisi alas
    glVertex3f(-6.5, -7.9, -64);
    glVertex3f(-9, -7.9, -64);
    glVertex3f(-9, -7.9, -46);
    glVertex3f(-6.5, -9.9, -46);// kiri pertama, sisi kiri
    glVertex3f(-6.5, -9.9, -64);
    glVertex3f(-6.5, -7.9, -64);
    glVertex3f(-6.5, -7.9, -46);
    glVertex3f(-9, -9.9, -46);// kiri pertama, sisi kanan
    glVertex3f(-9, -9.9, -64);
    glVertex3f(-9, -7.9, -64);
    glVertex3f(-9, -7.9, -46);
    glVertex3f(-6.5, -9.9, -46);// kiri pertama, sisi depan
    glVertex3f(-6.5, -7.9, -46);
    glVertex3f(-9, -7.9, -46);
    glVertex3f(-9, -9.9, -46);
    glVertex3f(-6.5, -9.9, -64);// kiri pertama, sisi belakang
    glVertex3f(-6.5, -7.9, -64);
    glVertex3f(-9, -7.9, -64);
    glVertex3f(-9, -9.9, -64);
    glVertex3f(-6.5, -7.9, -70);// kiri kedua, sisi alas
    glVertex3f(-6.5, -7.9, -94);
    glVertex3f(-9, -7.9, -94);
    glVertex3f(-9, -7.9, -70);
    glVertex3f(-6.5, -9.9, -70);// kiri kedua, sisi kiri
    glVertex3f(-6.5, -9.9, -94);
    glVertex3f(-6.5, -7.9, -94);
    glVertex3f(-6.5, -7.9, -70);
    glVertex3f(-9, -9.9, -70);// kiri kedua, sisi kanan
    glVertex3f(-9, -9.9, -94);
    glVertex3f(-9, -7.9, -94);
    glVertex3f(-9, -7.9, -70);
    glVertex3f(-6.5, -9.9, -70);// kiri kedua, sisi depan
    glVertex3f(-6.5, -7.9, -70);
    glVertex3f(-9, -7.9, -70);
    glVertex3f(-9, -9.9, -70);
    glVertex3f(-6.5, -9.9, -94);// kiri kedua, sisi belakang
    glVertex3f(-6.5, -7.9, -94);
    glVertex3f(-9, -7.9, -94);
    glVertex3f(-9, -9.9, -94);

    glColor3f(0.3, 0.15, 0);// batang pohon
    glVertex3f(-22, -9.9, -6);// kiri pertama, sisi depan
    glVertex3f(-22, 9.9, -6);
    glVertex3f(-24, 9.9, -6);
    glVertex3f(-24, -9.9, -6);
    glVertex3f(-22, -9.9, -8);// kiri pertama, sisi belakang
    glVertex3f(-22, 9.9, -8);
    glVertex3f(-24, 9.9, -8);
    glVertex3f(-24, -9.9, -8);
    glVertex3f(-22, -9.9, -8);// kiri pertama, sisi kanan
    glVertex3f(-22, 9.9, -8);
    glVertex3f(-22, 9.9, -6);
    glVertex3f(-22, -9.9, -6);
    glVertex3f(-24, -9.9, -8);// kiri pertama, sisi kiri
    glVertex3f(-24, 9.9, -8);
    glVertex3f(-24, 9.9, -6);
    glVertex3f(-24, -9.9, -6);

    glVertex3f(-22, -9.9, -26);// kiri kedua, sisi depan
    glVertex3f(-22, 9.9, -26);
    glVertex3f(-24, 9.9, -26);
    glVertex3f(-24, -9.9, -26);
    glVertex3f(-22, -9.9, -28);// kiri kedua, sisi belakang
    glVertex3f(-22, 9.9, -28);
    glVertex3f(-24, 9.9, -28);
    glVertex3f(-24, -9.9, -28);
    glVertex3f(-22, -9.9, -28);// kiri kedua, sisi kanan
    glVertex3f(-22, 9.9, -28);
    glVertex3f(-22, 9.9, -26);
    glVertex3f(-22, -9.9, -26);
    glVertex3f(-24, -9.9, -28);// kiri kedua, sisi kiri
    glVertex3f(-24, 9.9, -28);
    glVertex3f(-24, 9.9, -26);
    glVertex3f(-24, -9.9, -26);

    glVertex3f(22, -9.9, -6);// kanan pertama, sisi depan
    glVertex3f(22, 9.9, -6);
    glVertex3f(24, 9.9, -6);
    glVertex3f(24, -9.9, -6);
    glVertex3f(22, -9.9, -8);// kanan pertama, sisi belakang
    glVertex3f(22, 9.9, -8);
    glVertex3f(24, 9.9, -8);
    glVertex3f(24, -9.9, -8);
    glVertex3f(22, -9.9, -8);// kanan pertama, sisi kanan
    glVertex3f(22, 9.9, -8);
    glVertex3f(22, 9.9, -6);
    glVertex3f(22, -9.9, -6);
    glVertex3f(24, -9.9, -8);// kanan pertama, sisi kiri
    glVertex3f(24, 9.9, -8);
    glVertex3f(24, 9.9, -6);
    glVertex3f(24, -9.9, -6);

    glVertex3f(22, -9.9, -26);// kanan kedua, sisi depan
    glVertex3f(22, 9.9, -26);
    glVertex3f(24, 9.9, -26);
    glVertex3f(24, -9.9, -26);
    glVertex3f(22, -9.9, -28);// kanan kedua, sisi belakang
    glVertex3f(22, 9.9, -28);
    glVertex3f(24, 9.9, -28);
    glVertex3f(24, -9.9, -28);
    glVertex3f(22, -9.9, -28);// kanan kedua, sisi kanan
    glVertex3f(22, 9.9, -28);
    glVertex3f(22, 9.9, -26);
    glVertex3f(22, -9.9, -26);
    glVertex3f(24, -9.9, -28);// kanan kedua, sisi kiri
    glVertex3f(24, 9.9, -28);
    glVertex3f(24, 9.9, -26);
    glVertex3f(24, -9.9, -26);

    glVertex3f(-42, -9.9, -116);// kiri ketiga, sisi depan
    glVertex3f(-42, 9.9, -116);
    glVertex3f(-44, 9.9, -116);
    glVertex3f(-44, -9.9, -116);
    glVertex3f(-42, -9.9, -118);// kiri ketiga, sisi belakang
    glVertex3f(-42, 9.9, -118);
    glVertex3f(-44, 9.9, -118);
    glVertex3f(-44, -9.9, -118);
    glVertex3f(-42, -9.9, -118);// kiri ketiga, sisi kanan
    glVertex3f(-42, 9.9, -118);
    glVertex3f(-42, 9.9, -116);
    glVertex3f(-42, -9.9, -116);
    glVertex3f(-44, -9.9, -118);// kiri ketiga, sisi kiri
    glVertex3f(-44, 9.9, -118);
    glVertex3f(-44, 9.9, -116);
    glVertex3f(-44, -9.9, -116);

    glVertex3f(42, -9.9, -116);// kanan ketiga, sisi depan
    glVertex3f(42, 9.9, -116);
    glVertex3f(44, 9.9, -116);
    glVertex3f(44, -9.9, -116);
    glVertex3f(42, -9.9, -118);// kanan ketiga, sisi belakang
    glVertex3f(42, 9.9, -118);
    glVertex3f(44, 9.9, -118);
    glVertex3f(44, -9.9, -118);
    glVertex3f(42, -9.9, -118);// kanan ketiga, sisi kanan
    glVertex3f(42, 9.9, -118);
    glVertex3f(42, 9.9, -116);
    glVertex3f(42, -9.9, -116);
    glVertex3f(44, -9.9, -118);// kanan ketiga, sisi kiri
    glVertex3f(44, 9.9, -118);
    glVertex3f(44, 9.9, -116);
    glVertex3f(44, -9.9, -116);

    glVertex3f(-42, -9.9, -136);// kiri keempat, sisi depan
    glVertex3f(-42, 9.9, -136);
    glVertex3f(-44, 9.9, -136);
    glVertex3f(-44, -9.9, -136);
    glVertex3f(-42, -9.9, -138);// kiri keempat, sisi belakang
    glVertex3f(-42, 9.9, -138);
    glVertex3f(-44, 9.9, -138);
    glVertex3f(-44, -9.9, -138);
    glVertex3f(-42, -9.9, -138);// kiri keempat, sisi kanan
    glVertex3f(-42, 9.9, -138);
    glVertex3f(-42, 9.9, -136);
    glVertex3f(-42, -9.9, -136);
    glVertex3f(-44, -9.9, -138);// kiri keempat, sisi kiri
    glVertex3f(-44, 9.9, -138);
    glVertex3f(-44, 9.9, -136);
    glVertex3f(-44, -9.9, -136);

    glVertex3f(42, -9.9, -136);// kanan keempat, sisi depan
    glVertex3f(42, 9.9, -136);
    glVertex3f(44, 9.9, -136);
    glVertex3f(44, -9.9, -136);
    glVertex3f(42, -9.9, -138);// kanan keempat, sisi belakang
    glVertex3f(42, 9.9, -138);
    glVertex3f(44, 9.9, -138);
    glVertex3f(44, -9.9, -138);
    glVertex3f(42, -9.9, -138);// kanan keempat, sisi kanan
    glVertex3f(42, 9.9, -138);
    glVertex3f(42, 9.9, -136);
    glVertex3f(42, -9.9, -136);
    glVertex3f(44, -9.9, -138);// kanan keempat, sisi kiri
    glVertex3f(44, 9.9, -138);
    glVertex3f(44, 9.9, -136);
    glVertex3f(44, -9.9, -136);

    glVertex3f(-42, -9.9, -156);// kiri kelima, sisi depan
    glVertex3f(-42, 9.9, -156);
    glVertex3f(-44, 9.9, -156);
    glVertex3f(-44, -9.9, -156);
    glVertex3f(-42, -9.9, -158);// kiri kelima, sisi belakang
    glVertex3f(-42, 9.9, -158);
    glVertex3f(-44, 9.9, -158);
    glVertex3f(-44, -9.9, -158);
    glVertex3f(-42, -9.9, -158);// kiri kelima, sisi kanan
    glVertex3f(-42, 9.9, -158);
    glVertex3f(-42, 9.9, -156);
    glVertex3f(-42, -9.9, -156);
    glVertex3f(-44, -9.9, -158);// kiri kelima, sisi kiri
    glVertex3f(-44, 9.9, -158);
    glVertex3f(-44, 9.9, -156);
    glVertex3f(-44, -9.9, -156);

    glVertex3f(42, -9.9, -156);// kanan kelima, sisi depan
    glVertex3f(42, 9.9, -156);
    glVertex3f(44, 9.9, -156);
    glVertex3f(44, -9.9, -156);
    glVertex3f(42, -9.9, -158);// kanan kelima, sisi belakang
    glVertex3f(42, 9.9, -158);
    glVertex3f(44, 9.9, -158);
    glVertex3f(44, -9.9, -158);
    glVertex3f(42, -9.9, -158);// kanan kelima, sisi kanan
    glVertex3f(42, 9.9, -158);
    glVertex3f(42, 9.9, -156);
    glVertex3f(42, -9.9, -156);
    glVertex3f(44, -9.9, -158);// kanan kelima, sisi kiri
    glVertex3f(44, 9.9, -158);
    glVertex3f(44, 9.9, -156);
    glVertex3f(44, -9.9, -156);

    // taman ke 3
    glColor3f(1.0, 1.0, 1.0);//pertama
    glVertex3f(6.5, -9.9, -171);//lampu taman bawah kanan
    glVertex3f(6.5, -9.9, -174);
    glVertex3f(9, -9.9, -174);
    glVertex3f(9, -9.9, -171);
    glVertex3f(-6.5, -9.9, -171);//lampu taman bawah kiri
    glVertex3f(-6.5, -9.9, -174);
    glVertex3f(-9, -9.9, -174);
    glVertex3f(-9, -9.9, -171);
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(7, -9.8, -171.5);//lampu taman bawah tutup kanan
    glVertex3f(7, -9.8, -173.5);
    glVertex3f(8.5, -9.8, -173.5);
    glVertex3f(8.5, -9.8, -171.5);
    glVertex3f(-7, -9.8, -171.5);//lampu taman bawah tutup kiri
    glVertex3f(-7, -9.8, -173.5);
    glVertex3f(-8.5, -9.8, -173.5);
    glVertex3f(-8.5, -9.8, -171.5);
    glColor3f(1.0, 1.0, 1.0);//kedua
    glVertex3f(6.5, -9.9, -226);//lampu taman bawah kanan
    glVertex3f(6.5, -9.9, -229);
    glVertex3f(9, -9.9, -229);
    glVertex3f(9, -9.9, -226);
    glVertex3f(-6.5, -9.9, -226);//lampu taman bawah kiri
    glVertex3f(-6.5, -9.9, -229);
    glVertex3f(-9, -9.9, -229);
    glVertex3f(-9, -9.9, -226);
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(7, -9.8, -226.5);//lampu taman bawah tutup kanan
    glVertex3f(7, -9.8, -228.5);
    glVertex3f(8.5, -9.8, -228.5);
    glVertex3f(8.5, -9.8, -226.5);
    glVertex3f(-7, -9.8, -226.5);//lampu taman bawah tutup kiri
    glVertex3f(-7, -9.8, -228.5);
    glVertex3f(-8.5, -9.8, -228.5);
    glVertex3f(-8.5, -9.8, -226.5);
    glColor3f(0.8, 0.8, 0.8); //lampu tiang taman kanan
    glVertex3f(7.5, -9.8, -196.5);//sisi kiri
    glVertex3f(7.5, -9.8, -197.5);
    glVertex3f(7.5, 4.8, -197.5);
    glVertex3f(7.5, 4.8, -196.5);
    glVertex3f(8.5, -9.8, -196.5);//sisi kanan
    glVertex3f(8.5, -9.8, -197.5);
    glVertex3f(8.5, 4.8, -197.5);
    glVertex3f(8.5, 4.8, -196.5);
    glVertex3f(7.5, -9.8, -196.5);//sisi depan
    glVertex3f(8.5, -9.8, -196.5);
    glVertex3f(8.5, 4.8, -196.5);
    glVertex3f(7.5, 4.8, -196.5);
    glVertex3f(7.5, -9.8, -197.5);//sisi belakang
    glVertex3f(8.5, -9.8, -197.5);
    glVertex3f(8.5, 4.8, -197.5);
    glVertex3f(7.5, 4.8, -197.5);
    glVertex3f(6.5, 4.9, -198.5);//tutup
    glVertex3f(9.5, 4.9, -198.5);
    glVertex3f(9.5, 4.9, -195.5);
    glVertex3f(6.5, 4.9, -195.5);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(7, 5, -198);//panel surya
    glVertex3f(9, 5, -198);
    glVertex3f(9, 5, -196);
    glVertex3f(7, 5, -196);
    glVertex3f(8.5, 1.8, -196.5);//tiangkekanan
    glVertex3f(12.5, 3.8, -196.5);
    glVertex3f(12.5, 3.8, -197.5);
    glVertex3f(8.5, 1.8, -197.5);
    glColor3f(1, 1, 0);
    glVertex3f(11.5, 3.2, -196.5);//tiangkekanan
    glVertex3f(12.5, 3.7, -196.5);
    glVertex3f(12.5, 3.7, -197.5);
    glVertex3f(11.5, 3.2, -197.5);
    glColor3f(0.8, 0.8, 0.8); //lampu tiang taman kiri
    glVertex3f(-7.5, -9.8, -196.5);//sisi kiri
    glVertex3f(-7.5, -9.8, -197.5);
    glVertex3f(-7.5, 4.8, -197.5);
    glVertex3f(-7.5, 4.8, -196.5);
    glVertex3f(-8.5, -9.8, -196.5);//sisi kanan
    glVertex3f(-8.5, -9.8, -197.5);
    glVertex3f(-8.5, 4.8, -197.5);
    glVertex3f(-8.5, 4.8, -196.5);
    glVertex3f(-7.5, -9.8, -196.5);//sisi depan
    glVertex3f(-8.5, -9.8, -196.5);
    glVertex3f(-8.5, 4.8, -196.5);
    glVertex3f(-7.5, 4.8, -196.5);
    glVertex3f(-7.5, -9.8, -197.5);//sisi belakang
    glVertex3f(-8.5, -9.8, -197.5);
    glVertex3f(-8.5, 4.8, -197.5);
    glVertex3f(-7.5, 4.8, -197.5);
    glVertex3f(-6.5, 4.9, -198.5);//tutup
    glVertex3f(-9.5, 4.9, -198.5);
    glVertex3f(-9.5, 4.9, -195.5);
    glVertex3f(-6.5, 4.9, -195.5);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-7, 5, -198);//panel surya
    glVertex3f(-9, 5, -198);
    glVertex3f(-9, 5, -196);
    glVertex3f(-7, 5, -196);
    glVertex3f(-8.5, 1.8, -196.5);//tiangkekiri
    glVertex3f(-12.5, 3.8, -196.5);
    glVertex3f(-12.5, 3.8, -197.5);
    glVertex3f(-8.5, 1.8, -197.5);
    glColor3f(1, 1, 0);
    glVertex3f(-11.5, 3.2, -196.5);//bohlam
    glVertex3f(-12.5, 3.7, -196.5);
    glVertex3f(-12.5, 3.7, -197.5);
    glVertex3f(-11.5, 3.2, -197.5);
    glColor3f(0.4, 0.0, 0.4);//rumput baris
    glVertex3f(6.5, -7.9, -176);// kanan pertama, sisi alas
    glVertex3f(6.5, -7.9, -194);
    glVertex3f(9, -7.9, -194);
    glVertex3f(9, -7.9, -176);
    glVertex3f(6.5, -9.9, -176);// kanan pertama, sisi kiri
    glVertex3f(6.5, -9.9, -194);
    glVertex3f(6.5, -7.9, -194);
    glVertex3f(6.5, -7.9, -176);
    glVertex3f(9, -9.9, -176);// kanan pertama, sisi kanan
    glVertex3f(9, -9.9, -194);
    glVertex3f(9, -7.9, -194);
    glVertex3f(9, -7.9, -176);
    glVertex3f(6.5, -9.9, -176);// kanan pertama, sisi depan
    glVertex3f(6.5, -7.9, -176);
    glVertex3f(9, -7.9, -176);
    glVertex3f(9, -9.9, -176);
    glVertex3f(6.5, -9.9, -194);// kanan pertama, sisi belakang
    glVertex3f(6.5, -7.9, -194);
    glVertex3f(9, -7.9, -194);
    glVertex3f(9, -9.9, -194);
    glVertex3f(6.5, -7.9, -200);// kanan kedua, sisi alas
    glVertex3f(6.5, -7.9, -224);
    glVertex3f(9, -7.9, -224);
    glVertex3f(9, -7.9, -200);
    glVertex3f(6.5, -9.9, -200);// kanan kedua, sisi kiri
    glVertex3f(6.5, -9.9, -224);
    glVertex3f(6.5, -7.9, -224);
    glVertex3f(6.5, -7.9, -200);
    glVertex3f(9, -9.9, -200);// kanan kedua, sisi kanan
    glVertex3f(9, -9.9, -224);
    glVertex3f(9, -7.9, -224);
    glVertex3f(9, -7.9, -200);
    glVertex3f(6.5, -9.9, -200);// kanan kedua, sisi depan
    glVertex3f(6.5, -7.9, -200);
    glVertex3f(9, -7.9, -200);
    glVertex3f(9, -9.9, -200);
    glVertex3f(6.5, -9.9, -224);// kanan kedua, sisi belakang
    glVertex3f(6.5, -7.9, -224);
    glVertex3f(9, -7.9, -224);
    glVertex3f(9, -9.9, -224);
    glVertex3f(-6.5, -7.9, -176);// kiri pertama, sisi alas
    glVertex3f(-6.5, -7.9, -194);
    glVertex3f(-9, -7.9, -194);
    glVertex3f(-9, -7.9, -176);
    glVertex3f(-6.5, -9.9, -176);// kiri pertama, sisi kiri
    glVertex3f(-6.5, -9.9, -194);
    glVertex3f(-6.5, -7.9, -194);
    glVertex3f(-6.5, -7.9, -176);
    glVertex3f(-9, -9.9, -176);// kiri pertama, sisi kanan
    glVertex3f(-9, -9.9, -194);
    glVertex3f(-9, -7.9, -194);
    glVertex3f(-9, -7.9, -176);
    glVertex3f(-6.5, -9.9, -176);// kiri pertama, sisi depan
    glVertex3f(-6.5, -7.9, -176);
    glVertex3f(-9, -7.9, -176);
    glVertex3f(-9, -9.9, -176);
    glVertex3f(-6.5, -9.9, -194);// kiri pertama, sisi belakang
    glVertex3f(-6.5, -7.9, -194);
    glVertex3f(-9, -7.9, -194);
    glVertex3f(-9, -9.9, -194);
    glVertex3f(-6.5, -7.9, -200);// kiri kedua, sisi alas
    glVertex3f(-6.5, -7.9, -224);
    glVertex3f(-9, -7.9, -224);
    glVertex3f(-9, -7.9, -200);
    glVertex3f(-6.5, -9.9, -200);// kiri kedua, sisi kiri
    glVertex3f(-6.5, -9.9, -224);
    glVertex3f(-6.5, -7.9, -224);
    glVertex3f(-6.5, -7.9, -200);
    glVertex3f(-9, -9.9, -200);// kiri kedua, sisi kanan
    glVertex3f(-9, -9.9, -224);
    glVertex3f(-9, -7.9, -224);
    glVertex3f(-9, -7.9, -200);
    glVertex3f(-6.5, -9.9, -200);// kiri kedua, sisi depan
    glVertex3f(-6.5, -7.9, -200);
    glVertex3f(-9, -7.9, -200);
    glVertex3f(-9, -9.9, -200);
    glVertex3f(-6.5, -9.9, -224);// kiri kedua, sisi belakang
    glVertex3f(-6.5, -7.9, -224);
    glVertex3f(-9, -7.9, -224);
    glVertex3f(-9, -9.9, -224);
    //pohon pertama
    glColor3f(0.3, 0.15, 0);
    glVertex3f(-1, -9.9, -184);//pertama, sisi depan
    glVertex3f(-1, 9.9, -184);
    glVertex3f(1, 9.9, -184);
    glVertex3f(1, -9.9, -184);
    glVertex3f(-1, -9.9, -186);//pertama, sisi belakang
    glVertex3f(-1, 9.9, -186);
    glVertex3f(1, 9.9, -186);
    glVertex3f(1, -9.9, -186);
    glVertex3f(1, -9.9, -184);//pertama, sisi kanan
    glVertex3f(1, 9.9, -184);
    glVertex3f(1, 9.9, -186);
    glVertex3f(1, -9.9, -186);
    glVertex3f(-1, -9.9, -184);//pertama, sisi kiri
    glVertex3f(-1, 9.9, -184);
    glVertex3f(-1, 9.9, -186);
    glVertex3f(-1, -9.9, -186);
    //pohon kedua
    glVertex3f(-1, -9.9, -211);// kedua, sisi depan
    glVertex3f(-1, 9.9, -211);
    glVertex3f(1, 9.9, -211);
    glVertex3f(1, -9.9, -211);
    glVertex3f(-1, -9.9, -213);// kedua, sisi belakang
    glVertex3f(-1, 9.9, -213);
    glVertex3f(1, 9.9, -213);
    glVertex3f(1, -9.9, -213);
    glVertex3f(1, -9.9, -211);// kedua, sisi kanan
    glVertex3f(1, 9.9, -211);
    glVertex3f(1, 9.9, -213);
    glVertex3f(1, -9.9, -213);
    glVertex3f(-1, -9.9, -211);// kedua, sisi kiri
    glVertex3f(-1, 9.9, -211);
    glVertex3f(-1, 9.9, -213);
    glVertex3f(-1, -9.9, -213);
    //pohon ke 3
    glVertex3f(7, -9.9, -240);// kanan pertama, sisi depan
    glVertex3f(7, 9.9, -240);
    glVertex3f(9, 9.9, -240);
    glVertex3f(9, -9.9, -240);
    glVertex3f(7, -9.9, -242);// kanan pertama, sisi belakang
    glVertex3f(7, 9.9, -242);
    glVertex3f(9, 9.9, -242);
    glVertex3f(9, -9.9, -242);
    glVertex3f(9, -9.9, -240);// kanan pertama, sisi kanan
    glVertex3f(9, 9.9, -240);
    glVertex3f(9, 9.9, -242);
    glVertex3f(9, -9.9, -242);
    glVertex3f(7, -9.9, -240);// kanan pertama, sisi kiri
    glVertex3f(7, 9.9, -240);
    glVertex3f(7, 9.9, -242);
    glVertex3f(7, -9.9, -242);
    //pohon ke 4
    glVertex3f(-7, -9.9, -240);// kiri pertama, sisi depan
    glVertex3f(-7, 9.9, -240);
    glVertex3f(-9, 9.9, -240);
    glVertex3f(-9, -9.9, -240);
    glVertex3f(-7, -9.9, -242);// kiri pertama, sisi belakang
    glVertex3f(-7, 9.9, -242);
    glVertex3f(-9, 9.9, -242);
    glVertex3f(-9, -9.9, -242);
    glVertex3f(-9, -9.9, -240);// kiri pertama, sisi kanan
    glVertex3f(-9, 9.9, -240);
    glVertex3f(-9, 9.9, -242);
    glVertex3f(-9, -9.9, -242);
    glVertex3f(-7, -9.9, -240);// kiri pertama, sisi kiri
    glVertex3f(-7, 9.9, -240);
    glVertex3f(-7, 9.9, -242);
    glVertex3f(-7, -9.9, -242);
    //pohon ke 5
    glVertex3f(7, -9.9, -260);// kanan kedua, sisi depan
    glVertex3f(7, 9.9, -260);
    glVertex3f(9, 9.9, -260);
    glVertex3f(9, -9.9, -260);
    glVertex3f(7, -9.9, -262);// kanan kedua, sisi belakang
    glVertex3f(7, 9.9, -262);
    glVertex3f(9, 9.9, -262);
    glVertex3f(9, -9.9, -262);
    glVertex3f(9, -9.9, -260);// kanan kedua, sisi kanan
    glVertex3f(9, 9.9, -260);
    glVertex3f(9, 9.9, -262);
    glVertex3f(9, -9.9, -262);
    glVertex3f(7, -9.9, -260);// kanan kedua, sisi kiri
    glVertex3f(7, 9.9, -260);
    glVertex3f(7, 9.9, -262);
    glVertex3f(7, -9.9, -262);
    //pohon ke 6
    glVertex3f(-7, -9.9, -260);// kiri kedua, sisi depan
    glVertex3f(-7, 9.9, -260);
    glVertex3f(-9, 9.9, -260);
    glVertex3f(-9, -9.9, -260);
    glVertex3f(-7, -9.9, -262);// kiri kedua, sisi belakang
    glVertex3f(-7, 9.9, -262);
    glVertex3f(-9, 9.9, -262);
    glVertex3f(-9, -9.9, -262);
    glVertex3f(-9, -9.9, -260);// kiri kedua, sisi kanan
    glVertex3f(-9, 9.9, -260);
    glVertex3f(-9, 9.9, -262);
    glVertex3f(-9, -9.9, -262);
    glVertex3f(-7, -9.9, -260);// kiri kedua, sisi kiri
    glVertex3f(-7, 9.9, -260);
    glVertex3f(-7, 9.9, -262);
    glVertex3f(-7, -9.9, -262);
    //pohon ke 7
    glVertex3f(7, -9.9, -280);// kanan ketiga, sisi depan
    glVertex3f(7, 9.9, -280);
    glVertex3f(9, 9.9, -280);
    glVertex3f(9, -9.9, -280);
    glVertex3f(7, -9.9, -282);// kanan ketiga, sisi belakang
    glVertex3f(7, 9.9, -282);
    glVertex3f(9, 9.9, -282);
    glVertex3f(9, -9.9, -282);
    glVertex3f(9, -9.9, -280);// kanan ketiga, sisi kanan
    glVertex3f(9, 9.9, -280);
    glVertex3f(9, 9.9, -282);
    glVertex3f(9, -9.9, -282);
    glVertex3f(7, -9.9, -280);// kanan ketiga, sisi kiri
    glVertex3f(7, 9.9, -280);
    glVertex3f(7, 9.9, -282);
    glVertex3f(7, -9.9, -282);
    //pohon ke 6
    glVertex3f(-7, -9.9, -280);// kiri ketiga, sisi depan
    glVertex3f(-7, 9.9, -280);
    glVertex3f(-9, 9.9, -280);
    glVertex3f(-9, -9.9, -280);
    glVertex3f(-7, -9.9, -282);// kiri ketiga, sisi belakang
    glVertex3f(-7, 9.9, -282);
    glVertex3f(-9, 9.9, -282);
    glVertex3f(-9, -9.9, -282);
    glVertex3f(-9, -9.9, -280);// kiri ketiga, sisi kanan
    glVertex3f(-9, 9.9, -280);
    glVertex3f(-9, 9.9, -282);
    glVertex3f(-9, -9.9, -282);
    glVertex3f(-7, -9.9, -280);// kiri ketiga, sisi kiri
    glVertex3f(-7, 9.9, -280);
    glVertex3f(-7, 9.9, -282);
    glVertex3f(-7, -9.9, -282);

    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0, 1, 0);//daun
    glVertex3f(-17.0, 9.9, -6.0);//kiri pertama, sisi depan
    glVertex3f(-23.0, 20.0, -7.0);
    glVertex3f(-29.0, 9.9, -6.0);
    glVertex3f(-17.0, 9.9, -8.0);//kiri pertama, sisi belakang
    glVertex3f(-23.0, 20.0, -7.0);
    glVertex3f(-29.0, 9.9, -8.0);
    glVertex3f(-29.0, 9.9, -6.0);//kiri pertama, sisi kiri
    glVertex3f(-23.0, 20.0, -7.0);
    glVertex3f(-29.0, 9.9, -8.0);
    glVertex3f(-17.0, 9.9, -6.0);//kiri pertama, sisi kanan
    glVertex3f(-23.0, 20.0, -7.0);
    glVertex3f(-17.0, 9.9, -8.0);

    glVertex3f(17.0, 9.9, -6.0);//kanan pertama, sisi depan
    glVertex3f(23.0, 20.0, -7.0);
    glVertex3f(29.0, 9.9, -6.0);
    glVertex3f(17.0, 9.9, -8.0);//kanan pertama, sisi belakang
    glVertex3f(23.0, 20.0, -7.0);
    glVertex3f(29.0, 9.9, -8.0);
    glVertex3f(29.0, 9.9, -6.0);//kanan pertama, sisi kiri
    glVertex3f(23.0, 20.0, -7.0);
    glVertex3f(29.0, 9.9, -8.0);
    glVertex3f(17.0, 9.9, -6.0);//kanan pertama, sisi kanan
    glVertex3f(23.0, 20.0, -7.0);
    glVertex3f(17.0, 9.9, -8.0);

    glVertex3f(-17.0, 9.9, -26.0);//kiri kedua, sisi depan
    glVertex3f(-23.0, 20.0, -27.0);
    glVertex3f(-29.0, 9.9, -26.0);
    glVertex3f(-17.0, 9.9, -28.0);//kiri kedua, sisi belakang
    glVertex3f(-23.0, 20.0, -27.0);
    glVertex3f(-29.0, 9.9, -28.0);
    glVertex3f(-29.0, 9.9, -26.0);//kiri kedua, sisi kiri
    glVertex3f(-23.0, 20.0, -27.0);
    glVertex3f(-29.0, 9.9, -28.0);
    glVertex3f(-17.0, 9.9, -26.0);//kiri kedua, sisi kanan
    glVertex3f(-23.0, 20.0, -27.0);
    glVertex3f(-17.0, 9.9, -28.0);

    glVertex3f(17.0, 9.9, -26.0);//kanan kedua, sisi depan
    glVertex3f(23.0, 20.0, -27.0);
    glVertex3f(29.0, 9.9, -26.0);
    glVertex3f(17.0, 9.9, -28.0);//kanan kedua, sisi belakang
    glVertex3f(23.0, 20.0, -27.0);
    glVertex3f(29.0, 9.9, -28.0);
    glVertex3f(29.0, 9.9, -26.0);//kanan kedua, sisi kiri
    glVertex3f(23.0, 20.0, -27.0);
    glVertex3f(29.0, 9.9, -28.0);
    glVertex3f(17.0, 9.9, -26.0);//kanan kedua, sisi kanan
    glVertex3f(23.0, 20.0, -27.0);
    glVertex3f(17.0, 9.9, -28.0);

    glVertex3f(-42.0, 9.9, -111.0);//kiri ketiga, sisi depan
    glVertex3f(-43.0, 20.0, -117.0);
    glVertex3f(-44.0, 9.9, -111.0);
    glVertex3f(-42.0, 9.9, -123.0);//kiri ketiga, sisi belakang
    glVertex3f(-43.0, 20.0, -117.0);
    glVertex3f(-44.0, 9.9, -123.0);
    glVertex3f(-44.0, 9.9, -111.0);//kiri ketiga, sisi kiri
    glVertex3f(-43.0, 20.0, -117.0);
    glVertex3f(-44.0, 9.9, -123.0);
    glVertex3f(-42.0, 9.9, -111.0);//kiri ketiga, sisi kanan
    glVertex3f(-43.0, 20.0, -117.0);
    glVertex3f(-42.0, 9.9, -123.0);

    glVertex3f(42.0, 9.9, -111.0);//kanan ketiga, sisi depan
    glVertex3f(43.0, 20.0, -117.0);
    glVertex3f(44.0, 9.9, -111.0);
    glVertex3f(42.0, 9.9, -123.0);//kanan ketiga, sisi belakang
    glVertex3f(43.0, 20.0, -117.0);
    glVertex3f(44.0, 9.9, -123.0);
    glVertex3f(44.0, 9.9, -111.0);//kanan ketiga, sisi kiri
    glVertex3f(43.0, 20.0, -117.0);
    glVertex3f(44.0, 9.9, -123.0);
    glVertex3f(42.0, 9.9, -111.0);//kanan ketiga, sisi kanan
    glVertex3f(43.0, 20.0, -117.0);
    glVertex3f(42.0, 9.9, -123.0);

    glVertex3f(-42.0, 9.9, -131.0);//kiri keempat, sisi depan
    glVertex3f(-43.0, 20.0, -137.0);
    glVertex3f(-44.0, 9.9, -131.0);
    glVertex3f(-42.0, 9.9, -143.0);//kiri keempat, sisi belakang
    glVertex3f(-43.0, 20.0, -137.0);
    glVertex3f(-44.0, 9.9, -143.0);
    glVertex3f(-44.0, 9.9, -131.0);//kiri keempat, sisi kiri
    glVertex3f(-43.0, 20.0, -137.0);
    glVertex3f(-44.0, 9.9, -143.0);
    glVertex3f(-42.0, 9.9, -131.0);//kiri keempat, sisi kanan
    glVertex3f(-43.0, 20.0, -137.0);
    glVertex3f(-42.0, 9.9, -143.0);

    glVertex3f(42.0, 9.9, -131.0);//kanan keempat, sisi depan
    glVertex3f(43.0, 20.0, -137.0);
    glVertex3f(44.0, 9.9, -131.0);
    glVertex3f(42.0, 9.9, -143.0);//kanan keempat, sisi belakang
    glVertex3f(43.0, 20.0, -137.0);
    glVertex3f(44.0, 9.9, -143.0);
    glVertex3f(44.0, 9.9, -131.0);//kanan keempat, sisi kiri
    glVertex3f(43.0, 20.0, -137.0);
    glVertex3f(44.0, 9.9, -143.0);
    glVertex3f(42.0, 9.9, -131.0);//kanan keempat, sisi kanan
    glVertex3f(43.0, 20.0, -137.0);
    glVertex3f(42.0, 9.9, -143.0);

    glVertex3f(-42.0, 9.9, -151.0);//kiri kelima, sisi depan
    glVertex3f(-43.0, 20.0, -157.0);
    glVertex3f(-44.0, 9.9, -151.0);
    glVertex3f(-42.0, 9.9, -163.0);//kiri keempat, sisi belakang
    glVertex3f(-43.0, 20.0, -157.0);
    glVertex3f(-44.0, 9.9, -163.0);
    glVertex3f(-44.0, 9.9, -151.0);//kiri keempat, sisi kiri
    glVertex3f(-43.0, 20.0, -157.0);
    glVertex3f(-44.0, 9.9, -163.0);
    glVertex3f(-42.0, 9.9, -151.0);//kiri keempat, sisi kanan
    glVertex3f(-43.0, 20.0, -157.0);
    glVertex3f(-42.0, 9.9, -163.0);

    glVertex3f(42.0, 9.9, -151.0);//kanan keempat, sisi depan
    glVertex3f(43.0, 20.0, -157.0);
    glVertex3f(44.0, 9.9, -151.0);
    glVertex3f(42.0, 9.9, -163.0);//kanan keempat, sisi belakang
    glVertex3f(43.0, 20.0, -157.0);
    glVertex3f(44.0, 9.9, -163.0);
    glVertex3f(44.0, 9.9, -151.0);//kanan keempat, sisi kiri
    glVertex3f(43.0, 20.0, -157.0);
    glVertex3f(44.0, 9.9, -163.0);
    glVertex3f(42.0, 9.9, -151.0);//kanan keempat, sisi kanan
    glVertex3f(43.0, 20.0, -157.0);
    glVertex3f(42.0, 9.9, -163.0);

    //taman ke 3
    glVertex3f(-6.0, 9.9, -184.0);//pertama, sisi depan
    glVertex3f(0.0, 20.0, -185.0);
    glVertex3f(6.0, 9.9, -184.0);
    glVertex3f(-6.0, 9.9, -186.0);//pertama, sisi belakang
    glVertex3f(0.0, 20.0, -185.0);
    glVertex3f(6.0, 9.9, -186.0);
    glVertex3f(6.0, 9.9, -184.0);//pertama, sisi kiri
    glVertex3f(0.0, 20.0, -185.0);
    glVertex3f(6.0, 9.9, -186.0);
    glVertex3f(-6.0, 9.9, -184.0);//pertama, sisi kanan
    glVertex3f(0.0, 20.0, -185.0);
    glVertex3f(-6.0, 9.9, -186.0);
    glVertex3f(-6.0, 9.9, -211.0);//kedua, sisi depan
    glVertex3f(0.0, 20.0, -212.0);
    glVertex3f(6.0, 9.9, -211.0);
    glVertex3f(-6.0, 9.9, -213.0);//kedua, sisi belakang
    glVertex3f(0.0, 20.0, -212.0);
    glVertex3f(6.0, 9.9, -213.0);
    glVertex3f(6.0, 9.9, -211.0);//kedua, sisi kiri
    glVertex3f(0.0, 20.0, -212.0);
    glVertex3f(6.0, 9.9, -213.0);
    glVertex3f(-6.0, 9.9, -211.0);//kedua, sisi kanan
    glVertex3f(0.0, 20.0, -212.0);
    glVertex3f(-6.0, 9.9, -213.0);
    glVertex3f(7.0, 9.9, -235.0);//kiri ketiga, sisi depan
    glVertex3f(8.0, 20.0, -241.0);
    glVertex3f(9.0, 9.9, -235.0);
    glVertex3f(7.0, 9.9, -247.0);//kiri ketiga, sisi belakang
    glVertex3f(8, 20.0, -241.0);
    glVertex3f(9.0, 9.9, -247.0);
    glVertex3f(7.0, 9.9, -235.0);//kiri ketiga, sisi kiri
    glVertex3f(8.0, 20.0, -241.0);
    glVertex3f(7.0, 9.9, -247.0);
    glVertex3f(9.0, 9.9, -235.0);//kiri ketiga, sisi kanan
    glVertex3f(8.0, 20.0, -241.0);
    glVertex3f(9.0, 9.9, -247.0);
    glVertex3f(-7.0, 9.9, -235.0);//kanan ketiga, sisi depan
    glVertex3f(-8.0, 20.0, -241.0);
    glVertex3f(-9.0, 9.9, -235.0);
    glVertex3f(-7.0, 9.9, -247.0);//kanan ketiga, sisi belakang
    glVertex3f(-8, 20.0, -241.0);
    glVertex3f(-9.0, 9.9, -247.0);
    glVertex3f(-7.0, 9.9, -235.0);//kanan ketiga, sisi kiri
    glVertex3f(-8.0, 20.0, -241.0);
    glVertex3f(-7.0, 9.9, -247.0);
    glVertex3f(-9.0, 9.9, -235.0);//kanan ketiga, sisi kanan
    glVertex3f(-8.0, 20.0, -241.0);
    glVertex3f(-9.0, 9.9, -247.0);
    glVertex3f(7.0, 9.9, -255.0);//kiri keempat, sisi depan
    glVertex3f(8.0, 20.0, -261.0);
    glVertex3f(9.0, 9.9, -255.0);
    glVertex3f(7.0, 9.9, -267.0);//kiri keempat, sisi belakang
    glVertex3f(8, 20.0, -261.0);
    glVertex3f(9.0, 9.9, -267.0);
    glVertex3f(7.0, 9.9, -255.0);//kiri keempat, sisi kiri
    glVertex3f(8.0, 20.0, -261.0);
    glVertex3f(7.0, 9.9, -267.0);
    glVertex3f(9.0, 9.9, -255.0);//kiri keempat, sisi kanan
    glVertex3f(8.0, 20.0, -261.0);
    glVertex3f(9.0, 9.9, -267.0);
    glVertex3f(-7.0, 9.9, -255.0);//kanan keempat, sisi depan
    glVertex3f(-8.0, 20.0, -261.0);
    glVertex3f(-9.0, 9.9, -255.0);
    glVertex3f(-7.0, 9.9, -267.0);//kanan keempat, sisi belakang
    glVertex3f(-8, 20.0, -261.0);
    glVertex3f(-9.0, 9.9, -267.0);
    glVertex3f(-7.0, 9.9, -255.0);//kanan keempat, sisi kiri
    glVertex3f(-8.0, 20.0, -261.0);
    glVertex3f(-7.0, 9.9, -267.0);
    glVertex3f(-9.0, 9.9, -255.0);//kanan keempat, sisi kanan
    glVertex3f(-8.0, 20.0, -261.0);
    glVertex3f(-9.0, 9.9, -267.0);
    glVertex3f(7.0, 9.9, -275.0);//kiri kelima, sisi depan
    glVertex3f(8.0, 20.0, -281.0);
    glVertex3f(9.0, 9.9, -275.0);
    glVertex3f(7.0, 9.9, -287.0);//kiri kelima, sisi belakang
    glVertex3f(8, 20.0, -281.0);
    glVertex3f(9.0, 9.9, -287.0);
    glVertex3f(7.0, 9.9, -275.0);//kiri kelima, sisi kiri
    glVertex3f(8.0, 20.0, -281.0);
    glVertex3f(7.0, 9.9, -287.0);
    glVertex3f(9.0, 9.9, -275.0);//kiri kelima, sisi kanan
    glVertex3f(8.0, 20.0, -281.0);
    glVertex3f(9.0, 9.9, -287.0);
    glVertex3f(-7.0, 9.9, -275.0);//kanan kelima, sisi depan
    glVertex3f(-8.0, 20.0, -281.0);
    glVertex3f(-9.0, 9.9, -275.0);
    glVertex3f(-7.0, 9.9, -287.0);//kanan kelima, sisi belakang
    glVertex3f(-8, 20.0, -281.0);
    glVertex3f(-9.0, 9.9, -287.0);
    glVertex3f(-7.0, 9.9, -275.0);//kanan kelima, sisi kiri
    glVertex3f(-8.0, 20.0, -281.0);
    glVertex3f(-7.0, 9.9, -287.0);
    glVertex3f(-9.0, 9.9, -275.0);//kanan kelima, sisi kanan
    glVertex3f(-8.0, 20.0, -281.0);
    glVertex3f(-9.0, 9.9, -287.0);
    glEnd();


    //update
    //update


    //GEDUNG 1
    glBegin(GL_LINE_LOOP);              //JENDELA KIRI DARI KANAN - LANTAI 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-43.0, -5.0, -51.0);
    glVertex3f(-43.0, 0.0, -51.0);
    glVertex3f(-38.0, 0.0, -51.0);
    glVertex3f(-38.0, -5.0, -51.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-50.0, -5.0, -51.0);
    glVertex3f(-50.0, 0.0, -51.0);
    glVertex3f(-45.0, 0.0, -51.0);
    glVertex3f(-45.0, -5.0, -51.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-57.0, -5.0, -51.0);
    glVertex3f(-57.0, 0.0, -51.0);
    glVertex3f(-52.0, 0.0, -51.0);
    glVertex3f(-52.0, -5.0, -51.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-64.0, -5.0, -51.0);
    glVertex3f(-64.0, 0.0, -51.0);
    glVertex3f(-59.0, 0.0, -51.0);
    glVertex3f(-59.0, -5.0, -51.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-71.0, -5.0, -51.0);
    glVertex3f(-71.0, 0.0, -51.0);
    glVertex3f(-66.0, 0.0, -51.0);
    glVertex3f(-66.0, -5.0, -51.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-78.0, -5.0, -51.0);
    glVertex3f(-78.0, 0.0, -51.0);
    glVertex3f(-73.0, 0.0, -51.0);
    glVertex3f(-73.0, -5.0, -51.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-85.0, -5.0, -51.0);
    glVertex3f(-85.0, 0.0, -51.0);
    glVertex3f(-80.0, 0.0, -51.0);
    glVertex3f(-80.0, -5.0, -51.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-92.0, -5.0, -51.0);
    glVertex3f(-92.0, 0.0, -51.0);
    glVertex3f(-87.0, 0.0, -51.0);
    glVertex3f(-87.0, -5.0, -51.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-99.0, -5.0, -51.0);
    glVertex3f(-99.0, 0.0, -51.0);
    glVertex3f(-94.0, 0.0, -51.0);
    glVertex3f(-94.0, -5.0, -51.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-43.0, 10.0, -51.0);
    glVertex3f(-43.0, 15.0, -51.0);
    glVertex3f(-38.0, 15.0, -51.0);
    glVertex3f(-38.0, 10.0, -51.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-50.0, 10.0, -51.0);
    glVertex3f(-50.0, 15.0, -51.0);
    glVertex3f(-45.0, 15.0, -51.0);
    glVertex3f(-45.0, 10.0, -51.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-57.0, 10.0, -51.0);
    glVertex3f(-57.0, 15.0, -51.0);
    glVertex3f(-52.0, 15.0, -51.0);
    glVertex3f(-52.0, 10.0, -51.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-64.0, 10.0, -51.0);
    glVertex3f(-64.0, 15.0, -51.0);
    glVertex3f(-59.0, 15.0, -51.0);
    glVertex3f(-59.0, 10.0, -51.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-71.0, 10.0, -51.0);
    glVertex3f(-71.0, 15.0, -51.0);
    glVertex3f(-66.0, 15.0, -51.0);
    glVertex3f(-66.0, 10.0, -51.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-78.0, 10.0, -51.0);
    glVertex3f(-78.0, 15.0, -51.0);
    glVertex3f(-73.0, 15.0, -51.0);
    glVertex3f(-73.0, 10.0, -51.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-85.0, 10.0, -51.0);
    glVertex3f(-85.0, 15.0, -51.0);
    glVertex3f(-80.0, 15.0, -51.0);
    glVertex3f(-80.0, 10.0, -51.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-92.0, 10.0, -51.0);
    glVertex3f(-92.0, 15.0, -51.0);
    glVertex3f(-87.0, 15.0, -51.0);
    glVertex3f(-87.0, 10.0, -51.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-99.0, 10.0, -51.0);
    glVertex3f(-99.0, 15.0, -51.0);
    glVertex3f(-94.0, 15.0, -51.0);
    glVertex3f(-94.0, 10.0, -51.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-36.0, 25.0, -45.0);
    glVertex3f(-36.0, 30.0, -45.0);
    glVertex3f(-31.0, 30.0, -45.0);
    glVertex3f(-31.0, 25.0, -45.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-43.0, 25.0, -45.0);
    glVertex3f(-43.0, 30.0, -45.0);
    glVertex3f(-38.0, 30.0, -45.0);
    glVertex3f(-38.0, 25.0, -45.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-50.0, 25.0, -45.0);
    glVertex3f(-50.0, 30.0, -45.0);
    glVertex3f(-45.0, 30.0, -45.0);
    glVertex3f(-45.0, 25.0, -45.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-57.0, 25.0, -45.0);
    glVertex3f(-57.0, 30.0, -45.0);
    glVertex3f(-52.0, 30.0, -45.0);
    glVertex3f(-52.0, 25.0, -45.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-64.0, 25.0, -45.0);
    glVertex3f(-64.0, 30.0, -45.0);
    glVertex3f(-59.0, 30.0, -45.0);
    glVertex3f(-59.0, 25.0, -45.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-71.0, 25.0, -45.0);
    glVertex3f(-71.0, 30.0, -45.0);
    glVertex3f(-66.0, 30.0, -45.0);
    glVertex3f(-66.0, 25.0, -45.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-78.0, 25.0, -45.0);
    glVertex3f(-78.0, 30.0, -45.0);
    glVertex3f(-73.0, 30.0, -45.0);
    glVertex3f(-73.0, 25.0, -45.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-85.0, 25.0, -45.0);
    glVertex3f(-85.0, 30.0, -45.0);
    glVertex3f(-80.0, 30.0, -45.0);
    glVertex3f(-80.0, 25.0, -45.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-92.0, 25.0, -45.0);
    glVertex3f(-92.0, 30.0, -45.0);
    glVertex3f(-87.0, 30.0, -45.0);
    glVertex3f(-87.0, 25.0, -45.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-99.0, 25.0, -45.0);
    glVertex3f(-99.0, 30.0, -45.0);
    glVertex3f(-94.0, 30.0, -45.0);
    glVertex3f(-94.0, 25.0, -45.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-50.0, 40.0, -45.0);
    glVertex3f(-50.0, 45.0, -45.0);
    glVertex3f(-45.0, 45.0, -45.0);
    glVertex3f(-45.0, 40.0, -45.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-57.0, 40.0, -45.0);
    glVertex3f(-57.0, 45.0, -45.0);
    glVertex3f(-52.0, 45.0, -45.0);
    glVertex3f(-52.0, 40.0, -45.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-64.0, 40.0, -45.0);
    glVertex3f(-64.0, 45.0, -45.0);
    glVertex3f(-59.0, 45.0, -45.0);
    glVertex3f(-59.0, 40.0, -45.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-71.0, 40.0, -45.0);
    glVertex3f(-71.0, 45.0, -45.0);
    glVertex3f(-66.0, 45.0, -45.0);
    glVertex3f(-66.0, 40.0, -45.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-78.0, 40.0, -45.0);
    glVertex3f(-78.0, 45.0, -45.0);
    glVertex3f(-73.0, 45.0, -45.0);
    glVertex3f(-73.0, 40.0, -45.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-85.0, 40.0, -45.0);
    glVertex3f(-85.0, 45.0, -45.0);
    glVertex3f(-80.0, 45.0, -45.0);
    glVertex3f(-80.0, 40.0, -45.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-92.0, 40.0, -45.0);
    glVertex3f(-92.0, 45.0, -45.0);
    glVertex3f(-87.0, 45.0, -45.0);
    glVertex3f(-87.0, 40.0, -45.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-99.0, 40.0, -45.0);
    glVertex3f(-99.0, 45.0, -45.0);
    glVertex3f(-94.0, 45.0, -45.0);
    glVertex3f(-94.0, 40.0, -45.0);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 0.0, 0.0);         //JENDELA KANAN DARI KIRI - LANTAI 1
    glVertex3f(-43.0, -5.0, -89.0);
    glVertex3f(-43.0, 0.0, -89.0);
    glVertex3f(-38.0, 0.0, -89.0);
    glVertex3f(-38.0, -5.0, -89.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-50.0, -5.0, -89.0);
    glVertex3f(-50.0, 0.0, -89.0);
    glVertex3f(-45.0, 0.0, -89.0);
    glVertex3f(-45.0, -5.0, -89.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-57.0, -5.0, -89.0);
    glVertex3f(-57.0, 0.0, -89.0);
    glVertex3f(-52.0, 0.0, -89.0);
    glVertex3f(-52.0, -5.0, -89.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-64.0, -5.0, -89.0);
    glVertex3f(-64.0, 0.0, -89.0);
    glVertex3f(-59.0, 0.0, -89.0);
    glVertex3f(-59.0, -5.0, -89.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-71.0, -5.0, -89.0);
    glVertex3f(-71.0, 0.0, -89.0);
    glVertex3f(-66.0, 0.0, -89.0);
    glVertex3f(-66.0, -5.0, -89.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-78.0, -5.0, -89.0);
    glVertex3f(-78.0, 0.0, -89.0);
    glVertex3f(-73.0, 0.0, -89.0);
    glVertex3f(-73.0, -5.0, -89.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-85.0, -5.0, -89.0);
    glVertex3f(-85.0, 0.0, -89.0);
    glVertex3f(-80.0, 0.0, -89.0);
    glVertex3f(-80.0, -5.0, -89.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-92.0, -5.0, -89.0);
    glVertex3f(-92.0, 0.0, -89.0);
    glVertex3f(-87.0, 0.0, -89.0);
    glVertex3f(-87.0, -5.0, -89.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-99.0, -5.0, -89.0);
    glVertex3f(-99.0, 0.0, -89.0);
    glVertex3f(-94.0, 0.0, -89.0);
    glVertex3f(-94.0, -5.0, -89.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-43.0, 10.0, -89.0);
    glVertex3f(-43.0, 15.0, -89.0);
    glVertex3f(-38.0, 15.0, -89.0);
    glVertex3f(-38.0, 10.0, -89.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-50.0, 10.0, -89.0);
    glVertex3f(-50.0, 15.0, -89.0);
    glVertex3f(-45.0, 15.0, -89.0);
    glVertex3f(-45.0, 10.0, -89.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-57.0, 10.0, -89.0);
    glVertex3f(-57.0, 15.0, -89.0);
    glVertex3f(-52.0, 15.0, -89.0);
    glVertex3f(-52.0, 10.0, -89.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-64.0, 10.0, -89.0);
    glVertex3f(-64.0, 15.0, -89.0);
    glVertex3f(-59.0, 15.0, -89.0);
    glVertex3f(-59.0, 10.0, -89.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-71.0, 10.0, -89.0);
    glVertex3f(-71.0, 15.0, -89.0);
    glVertex3f(-66.0, 15.0, -89.0);
    glVertex3f(-66.0, 10.0, -89.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-78.0, 10.0, -89.0);
    glVertex3f(-78.0, 15.0, -89.0);
    glVertex3f(-73.0, 15.0, -89.0);
    glVertex3f(-73.0, 10.0, -89.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-85.0, 10.0, -89.0);
    glVertex3f(-85.0, 15.0, -89.0);
    glVertex3f(-80.0, 15.0, -89.0);
    glVertex3f(-80.0, 10.0, -89.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-92.0, 10.0, -89.0);
    glVertex3f(-92.0, 15.0, -89.0);
    glVertex3f(-87.0, 15.0, -89.0);
    glVertex3f(-87.0, 10.0, -89.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-99.0, 10.0, -89.0);
    glVertex3f(-99.0, 15.0, -89.0);
    glVertex3f(-94.0, 15.0, -89.0);
    glVertex3f(-94.0, 10.0, -89.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-36.0, 25.0, -95.0);
    glVertex3f(-36.0, 30.0, -95.0);
    glVertex3f(-31.0, 30.0, -95.0);
    glVertex3f(-31.0, 25.0, -95.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-43.0, 25.0, -95.0);
    glVertex3f(-43.0, 30.0, -95.0);
    glVertex3f(-38.0, 30.0, -95.0);
    glVertex3f(-38.0, 25.0, -95.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-50.0, 25.0, -95.0);
    glVertex3f(-50.0, 30.0, -95.0);
    glVertex3f(-45.0, 30.0, -95.0);
    glVertex3f(-45.0, 25.0, -95.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-57.0, 25.0, -95.0);
    glVertex3f(-57.0, 30.0, -95.0);
    glVertex3f(-52.0, 30.0, -95.0);
    glVertex3f(-52.0, 25.0, -95.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-64.0, 25.0, -95.0);
    glVertex3f(-64.0, 30.0, -95.0);
    glVertex3f(-59.0, 30.0, -95.0);
    glVertex3f(-59.0, 25.0, -95.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-71.0, 25.0, -95.0);
    glVertex3f(-71.0, 30.0, -95.0);
    glVertex3f(-66.0, 30.0, -95.0);
    glVertex3f(-66.0, 25.0, -95.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-78.0, 25.0, -95.0);
    glVertex3f(-78.0, 30.0, -95.0);
    glVertex3f(-73.0, 30.0, -95.0);
    glVertex3f(-73.0, 25.0, -95.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-85.0, 25.0, -95.0);
    glVertex3f(-85.0, 30.0, -95.0);
    glVertex3f(-80.0, 30.0, -95.0);
    glVertex3f(-80.0, 25.0, -95.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-92.0, 25.0, -95.0);
    glVertex3f(-92.0, 30.0, -95.0);
    glVertex3f(-87.0, 30.0, -95.0);
    glVertex3f(-87.0, 25.0, -95.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-99.0, 25.0, -95.0);
    glVertex3f(-99.0, 30.0, -95.0);
    glVertex3f(-94.0, 30.0, -95.0);
    glVertex3f(-94.0, 25.0, -95.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-50.0, 40.0, -95.0);
    glVertex3f(-50.0, 45.0, -95.0);
    glVertex3f(-45.0, 45.0, -95.0);
    glVertex3f(-45.0, 40.0, -95.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-57.0, 40.0, -95.0);
    glVertex3f(-57.0, 45.0, -95.0);
    glVertex3f(-52.0, 45.0, -95.0);
    glVertex3f(-52.0, 40.0, -95.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-64.0, 40.0, -95.0);
    glVertex3f(-64.0, 45.0, -95.0);
    glVertex3f(-59.0, 45.0, -95.0);
    glVertex3f(-59.0, 40.0, -95.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-71.0, 40.0, -95.0);
    glVertex3f(-71.0, 45.0, -95.0);
    glVertex3f(-66.0, 45.0, -95.0);
    glVertex3f(-66.0, 40.0, -95.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-78.0, 40.0, -95.0);
    glVertex3f(-78.0, 45.0, -95.0);
    glVertex3f(-73.0, 45.0, -95.0);
    glVertex3f(-73.0, 40.0, -95.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-85.0, 40.0, -95.0);
    glVertex3f(-85.0, 45.0, -95.0);
    glVertex3f(-80.0, 45.0, -95.0);
    glVertex3f(-80.0, 40.0, -95.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-92.0, 40.0, -95.0);
    glVertex3f(-92.0, 45.0, -95.0);
    glVertex3f(-87.0, 45.0, -95.0);
    glVertex3f(-87.0, 40.0, -95.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-99.0, 40.0, -95.0);
    glVertex3f(-99.0, 45.0, -95.0);
    glVertex3f(-94.0, 45.0, -95.0);
    glVertex3f(-94.0, 40.0, -95.0);
    glEnd();

    glBegin(GL_LINE_LOOP);              //JENDELA DEPAN DARI KIRI- LANTAI 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-36.0, 0.0, -58.0);
    glVertex3f(-36.0, -5.0, -58.0);
    glVertex3f(-36.0, -5.0, -53.0);
    glVertex3f(-36.0, 0.0, -53.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.D - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-36.0, 0.0, -65.0);
    glVertex3f(-36.0, -5.0, -65.0);
    glVertex3f(-36.0, -5.0, -60.0);
    glVertex3f(-36.0, 0.0, -60.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-36.0, 0.0, -80.0);
    glVertex3f(-36.0, -5.0, -80.0);
    glVertex3f(-36.0, -5.0, -75.0);
    glVertex3f(-36.0, 0.0, -75.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-36.0, 0.0, -87.0);
    glVertex3f(-36.0, -5.0, -87.0);
    glVertex3f(-36.0, -5.0, -82.0);
    glVertex3f(-36.0, 0.0, -82.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-36.0, 15.0, -58.0);
    glVertex3f(-36.0, 10.0, -58.0);
    glVertex3f(-36.0, 10.0, -53.0);
    glVertex3f(-36.0, 15.0, -53.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-36.0, 15.0, -65.0);
    glVertex3f(-36.0, 10.0, -65.0);
    glVertex3f(-36.0, 10.0, -60.0);
    glVertex3f(-36.0, 15.0, -60.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-36.0, 15.0, -73.0);
    glVertex3f(-36.0, 10.0, -73.0);
    glVertex3f(-36.0, 10.0, -67.0);
    glVertex3f(-36.0, 15.0, -67.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-36.0, 15.0, -80.0);
    glVertex3f(-36.0, 10.0, -80.0);
    glVertex3f(-36.0, 10.0, -75.0);
    glVertex3f(-36.0, 15.0, -75.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-36.0, 15.0, -87.0);
    glVertex3f(-36.0, 10.0, -87.0);
    glVertex3f(-36.0, 10.0, -82.0);
    glVertex3f(-36.0, 15.0, -82.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-30.0, 25.0, -51.0);
    glVertex3f(-30.0, 30.0, -51.0);
    glVertex3f(-30.0, 30.0, -46.0);
    glVertex3f(-30.0, 25.0, -46.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-30.0, 25.0, -58.0);
    glVertex3f(-30.0, 30.0, -58.0);
    glVertex3f(-30.0, 30.0, -53.0);
    glVertex3f(-30.0, 25.0, -53.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-30.0, 25.0, -65.0);
    glVertex3f(-30.0, 30.0, -65.0);
    glVertex3f(-30.0, 30.0, -60.0);
    glVertex3f(-30.0, 25.0, -60.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-30.0, 25.0, -73.0);
    glVertex3f(-30.0, 30.0, -73.0);
    glVertex3f(-30.0, 30.0, -67.0);
    glVertex3f(-30.0, 25.0, -67.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-30.0, 25.0, -80.0);
    glVertex3f(-30.0, 30.0, -80.0);
    glVertex3f(-30.0, 30.0, -75.0);
    glVertex3f(-30.0, 25.0, -75.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-30.0, 25.0, -87.0);
    glVertex3f(-30.0, 30.0, -87.0);
    glVertex3f(-30.0, 30.0, -82.0);
    glVertex3f(-30.0, 25.0, -82.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-30.0, 25.0, -94.0);
    glVertex3f(-30.0, 30.0, -94.0);
    glVertex3f(-30.0, 30.0, -89.0);
    glVertex3f(-30.0, 25.0, -89.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-30.0, 45.0, -65.0);
    glVertex3f(-30.0, 40.0, -65.0);
    glVertex3f(-30.0, 40.0, -60.0);
    glVertex3f(-30.0, 45.0, -60.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-30.0, 45.0, -73.0);
    glVertex3f(-30.0, 40.0, -73.0);
    glVertex3f(-30.0, 40.0, -67.0);
    glVertex3f(-30.0, 45.0, -67.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-30.0, 45.0, -80.0);
    glVertex3f(-30.0, 40.0, -80.0);
    glVertex3f(-30.0, 40.0, -75.0);
    glVertex3f(-30.0, 45.0, -75.0);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-100.0, -10.0, -51.0);       //KIRI - LANTAI 1
    glVertex3f(-100.0, -5.0, -51.0);
    glVertex3f(-36.0, -5.0, -51.0);
    glVertex3f(-36.0, -10.0, -51.0);//
    glVertex3f(-38.0, -10.0, -51.0);        //BERDIRI - LANTAI 1-2 DARI KANAN 1
    glVertex3f(-38.0, 20.0, -51.0);
    glVertex3f(-36.0, 20.0, -51.0);
    glVertex3f(-36.0, -10.0, -51.0);//
    glVertex3f(-45.0, -10.0, -51.0);        //BERDIRI 2
    glVertex3f(-45.0, 20.0, -51.0);
    glVertex3f(-43.0, 20.0, -51.0);
    glVertex3f(-43.0, -10.0, -51.0);//
    glVertex3f(-52.0, -10.0, -51.0);        //BERDIRI 3
    glVertex3f(-52.0, 20.0, -51.0);
    glVertex3f(-50.0, 20.0, -51.0);
    glVertex3f(-50.0, -10.0, -51.0);//
    glVertex3f(-59.0, -10.0, -51.0);        //BERDIRI 4
    glVertex3f(-59.0, 20.0, -51.0);
    glVertex3f(-57.0, 20.0, -51.0);
    glVertex3f(-57.0, -10.0, -51.0);//
    glVertex3f(-66.0, -10.0, -51.0);        //BERDIRI 5
    glVertex3f(-66.0, 20.0, -51.0);
    glVertex3f(-64.0, 20.0, -51.0);
    glVertex3f(-64.0, -10.0, -51.0);//
    glVertex3f(-73.0, -10.0, -51.0);        //BERDIRI 6
    glVertex3f(-73.0, 20.0, -51.0);
    glVertex3f(-71.0, 20.0, -51.0);
    glVertex3f(-71.0, -10.0, -51.0);//
    glVertex3f(-80.0, -10.0, -51.0);        //BERDIRI 7
    glVertex3f(-80.0, 20.0, -51.0);
    glVertex3f(-78.0, 20.0, -51.0);
    glVertex3f(-78.0, -10.0, -51.0);//
    glVertex3f(-87.0, -10.0, -51.0);        //BERDIRI 8
    glVertex3f(-87.0, 20.0, -51.0);
    glVertex3f(-85.0, 20.0, -51.0);
    glVertex3f(-85.0, -10.0, -51.0);//
    glVertex3f(-94.0, -10.0, -51.0);        //BERDIRI 9
    glVertex3f(-94.0, 20.0, -51.0);
    glVertex3f(-92.0, 20.0, -51.0);
    glVertex3f(-92.0, -10.0, -51.0);//
    glVertex3f(-100.0, -10.0, -51.0);       //BERDIRI 9
    glVertex3f(-100.0, 20.0, -51.0);
    glVertex3f(-99.0, 20.0, -51.0);
    glVertex3f(-99.0, -10.0, -51.0);//
    glVertex3f(-100.0, 0.0, -51.0);         //KIRI - LANTAI 1-2
    glVertex3f(-100.0, 10.0, -51.0);
    glVertex3f(-36.0, 10.0, -51.0);
    glVertex3f(-36.0, 0.0, -51.0);//
    glVertex3f(-31.0, 20.0, -45.0);         //BERDIRI - LANTAI 2-4 DARI KANAN 1
    glVertex3f(-31.0, 35.0, -45.0);
    glVertex3f(-30.0, 35.0, -45.0);
    glVertex3f(-30.0, 20.0, -45.0);//
    glVertex3f(-38.0, 20.0, -45.0);         //BERDIRI 2
    glVertex3f(-38.0, 35.0, -45.0);
    glVertex3f(-36.0, 35.0, -45.0);
    glVertex3f(-36.0, 20.0, -45.0);//
    glVertex3f(-45.0, 20.0, -45.0);         //BERDIRI 3
    glVertex3f(-45.0, 50.0, -45.0);
    glVertex3f(-43.0, 50.0, -45.0);
    glVertex3f(-43.0, 20.0, -45.0);//
    glVertex3f(-52.0, 20.0, -45.0);         //BERDIRI 4
    glVertex3f(-52.0, 50.0, -45.0);
    glVertex3f(-50.0, 50.0, -45.0);
    glVertex3f(-50.0, 20.0, -45.0);//
    glVertex3f(-59.0, 20.0, -45.0);         //BERDIRI 5
    glVertex3f(-59.0, 50.0, -45.0);
    glVertex3f(-57.0, 50.0, -45.0);
    glVertex3f(-57.0, 20.0, -45.0);//
    glVertex3f(-66.0, 20.0, -45.0);         //BERDIRI 6
    glVertex3f(-66.0, 50.0, -45.0);
    glVertex3f(-64.0, 50.0, -45.0);
    glVertex3f(-64.0, 20.0, -45.0);//
    glVertex3f(-73.0, 20.0, -45.0);         //BERDIRI 7
    glVertex3f(-73.0, 50.0, -45.0);
    glVertex3f(-71.0, 50.0, -45.0);
    glVertex3f(-71.0, 20.0, -45.0);//
    glVertex3f(-80.0, 20.0, -45.0);         //BERDIRI 8
    glVertex3f(-80.0, 50.0, -45.0);
    glVertex3f(-78.0, 50.0, -45.0);
    glVertex3f(-78.0, 20.0, -45.0);//
    glVertex3f(-87.0, 20.0, -45.0);         //BERDIRI 9
    glVertex3f(-87.0, 50.0, -45.0);
    glVertex3f(-85.0, 50.0, -45.0);
    glVertex3f(-85.0, 20.0, -45.0);//
    glVertex3f(-94.0, 20.0, -45.0);         //BERDIRI 10
    glVertex3f(-94.0, 50.0, -45.0);
    glVertex3f(-92.0, 50.0, -45.0);
    glVertex3f(-92.0, 20.0, -45.0);//
    glVertex3f(-100.0, 20.0, -45.0);        //BERDIRI 11
    glVertex3f(-100.0, 50.0, -45.0);
    glVertex3f(-99.0, 50.0, -45.0);
    glVertex3f(-99.0, 20.0, -45.0);//
    glVertex3f(-100.0, 15.0, -51.0);        //KIRI - LANTAI 2
    glVertex3f(-100.0, 20.0, -51.0);
    glVertex3f(-30.0, 20.0, -51.0);
    glVertex3f(-30.0, 15.0, -51.0);//
    glVertex3f(-100.0, 5.0, -45.0);         //KIRI - LANTAI 2
    glVertex3f(-100.0, 10.0, -45.0);
    glVertex3f(-30.0, 10.0, -45.0);
    glVertex3f(-30.0, 5.0, -45.0);//
    glVertex3f(-100.0, 15.0, -45.0);        //KIRI - LANTAI 3
    glVertex3f(-100.0, 25.0, -45.0);
    glVertex3f(-30.0, 25.0, -45.0);
    glVertex3f(-30.0, 15.0, -45.0);//
    glVertex3f(-100.0, 30.0, -45.0);        //KIRI - LANTAI 3-4
    glVertex3f(-100.0, 40.0, -45.0);
    glVertex3f(-43.0, 40.0, -45.0);
    glVertex3f(-43.0, 30.0, -45.0);
    glVertex3f(-100.0, 45.0, -45.0);        //KIRI - LANTAI 4
    glVertex3f(-100.0, 50.0, -45.0);
    glVertex3f(-43.0, 50.0, -45.0);
    glVertex3f(-43.0, 45.0, -45.0);
    glVertex3f(-43.0, 30.0, -45.0);         //KIRI - LANTAI 4
    glVertex3f(-43.0, 38.0, -45.0);
    glVertex3f(-30.0, 38.0, -45.0);
    glVertex3f(-30.0, 30.0, -45.0);
    glVertex3f(-43.0, 40.0, -58.0);        //KIRI - LANTAI 4
    glVertex3f(-43.0, 50.0, -58.0);
    glVertex3f(-30.0, 50.0, -58.0);
    glVertex3f(-30.0, 40.0, -58.0);

    glVertex3f(-32.0, -10.0, -45.0);         //KIRI - PILAR 1
    glVertex3f(-32.0, 5.0, -45.0);
    glVertex3f(-30.0, 5.0, -45.0);
    glVertex3f(-30.0, -10.0, -45.0);
    glVertex3f(-32.0, -10.0, -47.0);         //KIRI - PILAR 1
    glVertex3f(-32.0, 5.0, -47.0);
    glVertex3f(-30.0, 5.0, -47.0);
    glVertex3f(-30.0, -10.0, -47.0);
    glVertex3f(-42.0, -10.0, -45.0);         //KIRI - PILAR 2
    glVertex3f(-42.0, 5.0, -45.0);
    glVertex3f(-40.0, 5.0, -45.0);
    glVertex3f(-40.0, -10.0, -45.0);
    glVertex3f(-42.0, -10.0, -47.0);         //KIRI - PILAR 2
    glVertex3f(-42.0, 5.0, -47.0);
    glVertex3f(-40.0, 5.0, -47.0);
    glVertex3f(-40.0, -10.0, -47.0);
    glVertex3f(-40.0, 5.0, -47.0);           //KIRI - PILAR 2
    glVertex3f(-40.0, -10.0, -47.0);
    glVertex3f(-40.0, -10.0, -45.0);
    glVertex3f(-40.0, 5.0, -45.0);
    glVertex3f(-42.0, 5.0, -47.0);           //KIRI - PILAR 2
    glVertex3f(-42.0, -10.0, -47.0);
    glVertex3f(-42.0, -10.0, -45.0);
    glVertex3f(-42.0, 5.0, -45.0);
    glVertex3f(-52.0, -10.0, -45.0);         //KIRI - PILAR 3
    glVertex3f(-52.0, 5.0, -45.0);
    glVertex3f(-50.0, 5.0, -45.0);
    glVertex3f(-50.0, -10.0, -45.0);
    glVertex3f(-52.0, -10.0, -47.0);         //KIRI - PILAR 3
    glVertex3f(-52.0, 5.0, -47.0);
    glVertex3f(-50.0, 5.0, -47.0);
    glVertex3f(-50.0, -10.0, -47.0);
    glVertex3f(-50.0, 5.0, -47.0);           //KIRI - PILAR 3
    glVertex3f(-50.0, -10.0, -47.0);
    glVertex3f(-50.0, -10.0, -45.0);
    glVertex3f(-50.0, 5.0, -45.0);
    glVertex3f(-52.0, 5.0, -47.0);           //KIRI - PILAR 3
    glVertex3f(-52.0, -10.0, -47.0);
    glVertex3f(-52.0, -10.0, -45.0);
    glVertex3f(-52.0, 5.0, -45.0);
    glVertex3f(-62.0, -10.0, -45.0);         //KIRI - PILAR 4
    glVertex3f(-62.0, 5.0, -45.0);
    glVertex3f(-60.0, 5.0, -45.0);
    glVertex3f(-60.0, -10.0, -45.0);
    glVertex3f(-62.0, -10.0, -47.0);         //KIRI - PILAR 4
    glVertex3f(-62.0, 5.0, -47.0);
    glVertex3f(-60.0, 5.0, -47.0);
    glVertex3f(-60.0, -10.0, -47.0);
    glVertex3f(-60.0, 5.0, -47.0);           //KIRI - PILAR 4
    glVertex3f(-60.0, -10.0, -47.0);
    glVertex3f(-60.0, -10.0, -45.0);
    glVertex3f(-60.0, 5.0, -45.0);
    glVertex3f(-62.0, 5.0, -47.0);           //KIRI - PILAR 4
    glVertex3f(-62.0, -10.0, -47.0);
    glVertex3f(-62.0, -10.0, -45.0);
    glVertex3f(-62.0, 5.0, -45.0);
    glVertex3f(-72.0, -10.0, -45.0);         //KIRI - PILAR 5
    glVertex3f(-72.0, 5.0, -45.0);
    glVertex3f(-70.0, 5.0, -45.0);
    glVertex3f(-70.0, -10.0, -45.0);
    glVertex3f(-72.0, -10.0, -47.0);         //KIRI - PILAR 5
    glVertex3f(-72.0, 5.0, -47.0);
    glVertex3f(-70.0, 5.0, -47.0);
    glVertex3f(-70.0, -10.0, -47.0);
    glVertex3f(-70.0, 5.0, -47.0);           //KIRI - PILAR 5
    glVertex3f(-70.0, -10.0, -47.0);
    glVertex3f(-70.0, -10.0, -45.0);
    glVertex3f(-70.0, 5.0, -45.0);
    glVertex3f(-72.0, 5.0, -47.0);           //KIRI - PILAR 5
    glVertex3f(-72.0, -10.0, -47.0);
    glVertex3f(-72.0, -10.0, -45.0);
    glVertex3f(-72.0, 5.0, -45.0);
    glVertex3f(-82.0, -10.0, -45.0);         //KIRI - PILAR 6
    glVertex3f(-82.0, 5.0, -45.0);
    glVertex3f(-80.0, 5.0, -45.0);
    glVertex3f(-80.0, -10.0, -45.0);
    glVertex3f(-82.0, -10.0, -47.0);         //KIRI - PILAR 6
    glVertex3f(-82.0, 5.0, -47.0);
    glVertex3f(-80.0, 5.0, -47.0);
    glVertex3f(-80.0, -10.0, -47.0);
    glVertex3f(-80.0, 5.0, -47.0);           //KIRI - PILAR 6
    glVertex3f(-80.0, -10.0, -47.0);
    glVertex3f(-80.0, -10.0, -45.0);
    glVertex3f(-80.0, 5.0, -45.0);
    glVertex3f(-82.0, 5.0, -47.0);           //KIRI - PILAR 6
    glVertex3f(-82.0, -10.0, -47.0);
    glVertex3f(-82.0, -10.0, -45.0);
    glVertex3f(-82.0, 5.0, -45.0);
    glVertex3f(-92.0, -10.0, -45.0);         //KIRI - PILAR 7
    glVertex3f(-92.0, 5.0, -45.0);
    glVertex3f(-90.0, 5.0, -45.0);
    glVertex3f(-90.0, -10.0, -45.0);
    glVertex3f(-92.0, -10.0, -47.0);         //KIRI - PILAR 7
    glVertex3f(-92.0, 5.0, -47.0);
    glVertex3f(-90.0, 5.0, -47.0);
    glVertex3f(-90.0, -10.0, -47.0);
    glVertex3f(-90.0, 5.0, -47.0);           //KIRI - PILAR 7
    glVertex3f(-90.0, -10.0, -47.0);
    glVertex3f(-90.0, -10.0, -45.0);
    glVertex3f(-90.0, 5.0, -45.0);
    glVertex3f(-92.0, 5.0, -47.0);           //KIRI - PILAR 7
    glVertex3f(-92.0, -10.0, -47.0);
    glVertex3f(-92.0, -10.0, -45.0);
    glVertex3f(-92.0, 5.0, -45.0);

    glVertex3f(-100.0, -10.0, -89.0);       //KANAN - LANTAI 1
    glVertex3f(-100.0, -5.0, -89.0);
    glVertex3f(-36.0, -5.0, -89.0);
    glVertex3f(-36.0, -10.0, -89.0);//
    glVertex3f(-38.0, -10.0, -89.0);        //BERDIRI - LANTAI 1-2 DARI KIRI 1
    glVertex3f(-38.0, 20.0, -89.0);
    glVertex3f(-36.0, 20.0, -89.0);
    glVertex3f(-36.0, -10.0, -89.0);//
    glVertex3f(-45.0, -10.0, -89.0);        //BERDIRI 2
    glVertex3f(-45.0, 20.0, -89.0);
    glVertex3f(-43.0, 20.0, -89.0);
    glVertex3f(-43.0, -10.0, -89.0);//
    glVertex3f(-52.0, -10.0, -89.0);        //BERDIRI 3
    glVertex3f(-52.0, 20.0, -89.0);
    glVertex3f(-50.0, 20.0, -89.0);
    glVertex3f(-50.0, -10.0, -89.0);//
    glVertex3f(-59.0, -10.0, -89.0);        //BERDIRI 4
    glVertex3f(-59.0, 20.0, -89.0);
    glVertex3f(-57.0, 20.0, -89.0);
    glVertex3f(-57.0, -10.0, -89.0);//
    glVertex3f(-66.0, -10.0, -89.0);        //BERDIRI 5
    glVertex3f(-66.0, 20.0, -89.0);
    glVertex3f(-64.0, 20.0, -89.0);
    glVertex3f(-64.0, -10.0, -89.0);//
    glVertex3f(-73.0, -10.0, -89.0);        //BERDIRI 6
    glVertex3f(-73.0, 20.0, -89.0);
    glVertex3f(-71.0, 20.0, -89.0);
    glVertex3f(-71.0, -10.0, -89.0);//
    glVertex3f(-80.0, -10.0, -89.0);        //BERDIRI 7
    glVertex3f(-80.0, 20.0, -89.0);
    glVertex3f(-78.0, 20.0, -89.0);
    glVertex3f(-78.0, -10.0, -89.0);//
    glVertex3f(-87.0, -10.0, -89.0);        //BERDIRI 8
    glVertex3f(-87.0, 20.0, -89.0);
    glVertex3f(-85.0, 20.0, -89.0);
    glVertex3f(-85.0, -10.0, -89.0);//
    glVertex3f(-94.0, -10.0, -89.0);        //BERDIRI 9
    glVertex3f(-94.0, 20.0, -89.0);
    glVertex3f(-92.0, 20.0, -89.0);
    glVertex3f(-92.0, -10.0, -89.0);//
    glVertex3f(-100.0, -10.0, -89.0);       //BERDIRI 9
    glVertex3f(-100.0, 20.0, -89.0);
    glVertex3f(-99.0, 20.0, -89.0);
    glVertex3f(-99.0, -10.0, -89.0);//
    glVertex3f(-100.0, 0.0, -89.0);         //KANAN - LANTAI 1-2
    glVertex3f(-100.0, 10.0, -89.0);
    glVertex3f(-36.0, 10.0, -89.0);
    glVertex3f(-36.0, 0.0, -89.0);//
    glVertex3f(-31.0, 20.0, -95.0);        //BERDIRI - LANTAI 2-4 DARI KIRI 1
    glVertex3f(-31.0, 35.0, -95.0);
    glVertex3f(-30.0, 35.0, -95.0);
    glVertex3f(-30.0, 20.0, -95.0);//
    glVertex3f(-38.0, 20.0, -95.0);        //BERDIRI 2
    glVertex3f(-38.0, 35.0, -95.0);
    glVertex3f(-36.0, 35.0, -95.0);
    glVertex3f(-36.0, 20.0, -95.0);//
    glVertex3f(-45.0, 20.0, -95.0);        //BERDIRI 3
    glVertex3f(-45.0, 50.0, -95.0);
    glVertex3f(-43.0, 50.0, -95.0);
    glVertex3f(-43.0, 20.0, -95.0);//
    glVertex3f(-52.0, 20.0, -95.0);        //BERDIRI 4
    glVertex3f(-52.0, 50.0, -95.0);
    glVertex3f(-50.0, 50.0, -95.0);
    glVertex3f(-50.0, 20.0, -95.0);//
    glVertex3f(-59.0, 20.0, -95.0);        //BERDIRI 5
    glVertex3f(-59.0, 50.0, -95.0);
    glVertex3f(-57.0, 50.0, -95.0);
    glVertex3f(-57.0, 20.0, -95.0);//
    glVertex3f(-66.0, 20.0, -95.0);        //BERDIRI 6
    glVertex3f(-66.0, 50.0, -95.0);
    glVertex3f(-64.0, 50.0, -95.0);
    glVertex3f(-64.0, 20.0, -95.0);//
    glVertex3f(-73.0, 20.0, -95.0);        //BERDIRI 7
    glVertex3f(-73.0, 50.0, -95.0);
    glVertex3f(-71.0, 50.0, -95.0);
    glVertex3f(-71.0, 20.0, -95.0);//
    glVertex3f(-80.0, 20.0, -95.0);        //BERDIRI 8
    glVertex3f(-80.0, 50.0, -95.0);
    glVertex3f(-78.0, 50.0, -95.0);
    glVertex3f(-78.0, 20.0, -95.0);//
    glVertex3f(-87.0, 20.0, -95.0);        //BERDIRI 9
    glVertex3f(-87.0, 50.0, -95.0);
    glVertex3f(-85.0, 50.0, -95.0);
    glVertex3f(-85.0, 20.0, -95.0);//
    glVertex3f(-94.0, 20.0, -95.0);        //BERDIRI 10
    glVertex3f(-94.0, 50.0, -95.0);
    glVertex3f(-92.0, 50.0, -95.0);
    glVertex3f(-92.0, 20.0, -95.0);//
    glVertex3f(-100.0, 20.0, -95.0);        //BERDIRI 11
    glVertex3f(-100.0, 50.0, -95.0);
    glVertex3f(-99.0, 50.0, -95.0);
    glVertex3f(-99.0, 20.0, -95.0);//
    glVertex3f(-100.0, 15.0, -89.0);        //KANAN - LANTAI 2
    glVertex3f(-100.0, 20.0, -89.0);
    glVertex3f(-36.0, 20.0, -89.0);
    glVertex3f(-36.0, 15.0, -89.0);//
    glVertex3f(-100.0, 5.0, -95.0);         //KANAN - LANTAI 2
    glVertex3f(-100.0, 10.0, -95.0);
    glVertex3f(-38.0, 10.0, -95.0);
    glVertex3f(-38.0, 5.0, -95.0);//
    glVertex3f(-100.0, 15.0, -95.0);        //KANAN - LANTAI 3
    glVertex3f(-100.0, 25.0, -95.0);
    glVertex3f(-30.0, 25.0, -95.0);
    glVertex3f(-30.0, 15.0, -95.0);//
    glVertex3f(-100.0, 30.0, -95.0);        //KANAN - LANTAI 4
    glVertex3f(-100.0, 40.0, -95.0);
    glVertex3f(-43.0, 40.0, -95.0);
    glVertex3f(-43.0, 30.0, -95.0);
    glVertex3f(-100.0, 45.0, -95.0);        //KANAN - LANTAI 4
    glVertex3f(-100.0, 50.0, -95.0);
    glVertex3f(-43.0, 50.0, -95.0);
    glVertex3f(-43.0, 45.0, -95.0);
    glVertex3f(-43.0, 30.0, -95.0);         //KANAN - LANTAI 4 PENDEK DI KIRI
    glVertex3f(-43.0, 38.0, -95.0);
    glVertex3f(-30.0, 38.0, -95.0);
    glVertex3f(-30.0, 30.0, -95.0);
    glVertex3f(-43.0, 35.0, -82.0);         //KANAN - LANTAI 4
    glVertex3f(-43.0, 50.0, -82.0);
    glVertex3f(-30.0, 50.0, -82.0);
    glVertex3f(-30.0, 35.0, -82.0);

    glVertex3f(-32.0, -10.0, -95.0);         //KANAN - PILAR 1
    glVertex3f(-32.0, 5.0, -95.0);
    glVertex3f(-30.0, 5.0, -95.0);
    glVertex3f(-30.0, -10.0, -95.0);
    glVertex3f(-32.0, -10.0, -93.0);         //KANAN - PILAR 1
    glVertex3f(-32.0, 5.0, -93.0);
    glVertex3f(-30.0, 5.0, -93.0);
    glVertex3f(-30.0, -10.0, -93.0);
    glVertex3f(-42.0, -10.0, -95.0);         //KANAN - PILAR 2
    glVertex3f(-42.0, 5.0, -95.0);
    glVertex3f(-40.0, 5.0, -95.0);
    glVertex3f(-40.0, -10.0, -95.0);
    glVertex3f(-42.0, -10.0, -93.0);         //KANAN - PILAR 2
    glVertex3f(-43.0, 5.0, -93.0);
    glVertex3f(-40.0, 5.0, -93.0);
    glVertex3f(-40.0, -10.0, -93.0);
    glVertex3f(-40.0, 5.0, -95.0);           //KANAN - PILAR 2
    glVertex3f(-40.0, -10.0, -95.0);
    glVertex3f(-40.0, -10.0, -93.0);
    glVertex3f(-40.0, 5.0, -93.0);
    glVertex3f(-42.0, 5.0, -95.0);           //KANAN - PILAR 2
    glVertex3f(-42.0, -10.0, -95.0);
    glVertex3f(-42.0, -10.0, -93.0);
    glVertex3f(-42.0, 5.0, -93.0);
    glVertex3f(-52.0, -10.0, -95.0);         //KANAN - PILAR 3
    glVertex3f(-52.0, 5.0, -95.0);
    glVertex3f(-50.0, 5.0, -95.0);
    glVertex3f(-50.0, -10.0, -95.0);
    glVertex3f(-52.0, -10.0, -93.0);         //KANAN - PILAR 3
    glVertex3f(-52.0, 5.0, -93.0);
    glVertex3f(-50.0, 5.0, -93.0);
    glVertex3f(-50.0, -10.0, -93.0);
    glVertex3f(-50.0, 5.0, -95.0);           //KANAN - PILAR 3
    glVertex3f(-50.0, -10.0, -95.0);
    glVertex3f(-50.0, -10.0, -93.0);
    glVertex3f(-50.0, 5.0, -93.0);
    glVertex3f(-52.0, 5.0, -95.0);           //KANAN - PILAR 3
    glVertex3f(-52.0, -10.0, -95.0);
    glVertex3f(-52.0, -10.0, -93.0);
    glVertex3f(-52.0, 5.0, -93.0);
    glVertex3f(-62.0, -10.0, -95.0);         //KANAN - PILAR 4
    glVertex3f(-62.0, 5.0, -95.0);
    glVertex3f(-60.0, 5.0, -95.0);
    glVertex3f(-60.0, -10.0, -95.0);
    glVertex3f(-62.0, -10.0, -93.0);         //KANAN - PILAR 4
    glVertex3f(-62.0, 5.0, -93.0);
    glVertex3f(-60.0, 5.0, -93.0);
    glVertex3f(-60.0, -10.0, -93.0);
    glVertex3f(-60.0, 5.0, -95.0);           //KANAN - PILAR 4
    glVertex3f(-60.0, -10.0, -95.0);
    glVertex3f(-60.0, -10.0, -93.0);
    glVertex3f(-60.0, 5.0, -93.0);
    glVertex3f(-62.0, 5.0, -95.0);           //KANAN - PILAR 4
    glVertex3f(-62.0, -10.0, -95.0);
    glVertex3f(-62.0, -10.0, -93.0);
    glVertex3f(-62.0, 5.0, -93.0);
    glVertex3f(-72.0, -10.0, -95.0);         //KANAN - PILAR 5
    glVertex3f(-72.0, 5.0, -95.0);
    glVertex3f(-70.0, 5.0, -95.0);
    glVertex3f(-70.0, -10.0, -95.0);
    glVertex3f(-72.0, -10.0, -93.0);         //KANAN - PILAR 5
    glVertex3f(-72.0, 5.0, -93.0);
    glVertex3f(-70.0, 5.0, -93.0);
    glVertex3f(-70.0, -10.0, -93.0);
    glVertex3f(-70.0, 5.0, -95.0);           //KANAN - PILAR 5
    glVertex3f(-70.0, -10.0, -95.0);
    glVertex3f(-70.0, -10.0, -93.0);
    glVertex3f(-70.0, 5.0, -93.0);
    glVertex3f(-72.0, 5.0, -95.0);           //KANAN - PILAR 5
    glVertex3f(-72.0, -10.0, -95.0);
    glVertex3f(-72.0, -10.0, -93.0);
    glVertex3f(-72.0, 5.0, -93.0);
    glVertex3f(-82.0, -10.0, -95.0);         //KANAN - PILAR 6
    glVertex3f(-82.0, 5.0, -95.0);
    glVertex3f(-80.0, 5.0, -95.0);
    glVertex3f(-80.0, -10.0, -95.0);
    glVertex3f(-82.0, -10.0, -93.0);         //KANAN - PILAR 6
    glVertex3f(-82.0, 5.0, -93.0);
    glVertex3f(-80.0, 5.0, -93.0);
    glVertex3f(-80.0, -10.0, -93.0);
    glVertex3f(-80.0, 5.0, -95.0);           //KANAN - PILAR 6
    glVertex3f(-80.0, -10.0, -95.0);
    glVertex3f(-80.0, -10.0, -93.0);
    glVertex3f(-80.0, 5.0, -93.0);
    glVertex3f(-82.0, 5.0, -95.0);           //KANAN - PILAR 6
    glVertex3f(-82.0, -10.0, -95.0);
    glVertex3f(-82.0, -10.0, -93.0);
    glVertex3f(-82.0, 5.0, -93.0);
    glVertex3f(-92.0, -10.0, -95.0);         //KANAN - PILAR 7
    glVertex3f(-92.0, 5.0, -95.0);
    glVertex3f(-90.0, 5.0, -95.0);
    glVertex3f(-90.0, -10.0, -95.0);
    glVertex3f(-92.0, -10.0, -93.0);         //KANAN - PILAR 7
    glVertex3f(-92.0, 5.0, -93.0);
    glVertex3f(-90.0, 5.0, -93.0);
    glVertex3f(-90.0, -10.0, -93.0);
    glVertex3f(-90.0, 5.0, -95.0);           //KANAN - PILAR 7
    glVertex3f(-90.0, -10.0, -95.0);
    glVertex3f(-90.0, -10.0, -93.0);
    glVertex3f(-90.0, 5.0, -93.0);
    glVertex3f(-92.0, 5.0, -95.0);           //KANAN - PILAR 7
    glVertex3f(-92.0, -10.0, -95.0);
    glVertex3f(-92.0, -10.0, -93.0);
    glVertex3f(-92.0, 5.0, -93.0);

    glVertex3f(-36.0, -5.0, -67.0);         //DEPAN - LANTAI 1
    glVertex3f(-36.0, -10.0, -67.0);
    glVertex3f(-36.0, -10.0, -51.0);
    glVertex3f(-36.0, -5.0, -51.0);
    glVertex3f(-36.0, -5.0, -89.0);         //DEPAN - LANTAI 1
    glVertex3f(-36.0, -10.0, -89.0);
    glVertex3f(-36.0, -10.0, -73.0);
    glVertex3f(-36.0, -5.0, -73.0);
    glVertex3f(-36.0, 20.0, -53.0);         //BERDIRI - LANTAI 1-2 DARI KIRI 1
    glVertex3f(-36.0, -10.0, -53.0);
    glVertex3f(-36.0, -10.0, -51.0);
    glVertex3f(-36.0, 20.0, -51.0);
    glVertex3f(-36.0, 20.0, -60.0);         //BERDIRI 2
    glVertex3f(-36.0, -10.0, -60.0);
    glVertex3f(-36.0, -10.0, -58.0);
    glVertex3f(-36.0, 20.0, -58.0);
    glVertex3f(-36.0, 20.0, -67.0);         //BERDIRI 3
    glVertex3f(-36.0, -10.0, -67.0);
    glVertex3f(-36.0, -10.0, -65.0);
    glVertex3f(-36.0, 20.0, -65.0);
    glVertex3f(-36.0, 20.0, -75.0);         //BERDIRI 4
    glVertex3f(-36.0, -10.0, -75.0);
    glVertex3f(-36.0, -10.0, -73.0);
    glVertex3f(-36.0, 20.0, -73.0);
    glVertex3f(-36.0, 20.0, -82.0);         //BERDIRI 5
    glVertex3f(-36.0, -10.0, -82.0);
    glVertex3f(-36.0, -10.0, -80.0);
    glVertex3f(-36.0, 20.0, -80.0);
    glVertex3f(-36.0, 20.0, -89.0);         //BERDIRI 6
    glVertex3f(-36.0, -10.0, -89.0);
    glVertex3f(-36.0, -10.0, -87.0);
    glVertex3f(-36.0, 20.0, -87.0);
    glVertex3f(-36.0, 10.0, -89.0);         //DEPAN - LANTAI 2
    glVertex3f(-36.0, 0.0, -89.0);
    glVertex3f(-36.0, 0.0, -51.0);
    glVertex3f(-36.0, 10.0, -51.0);
    glVertex3f(-30.0, 35.0, -46.0);         //BERDIRI - LANTAI 2-4 DARI KIRI 1
    glVertex3f(-30.0, 20.0, -46.0);
    glVertex3f(-30.0, 20.0, -45.0);
    glVertex3f(-30.0, 35.0, -45.0);
    glVertex3f(-30.0, 35.0, -53.0);         //BERDIRI 2
    glVertex3f(-30.0, 20.0, -53.0);
    glVertex3f(-30.0, 20.0, -51.0);
    glVertex3f(-30.0, 35.0, -51.0);
    glVertex3f(-30.0, 50.0, -60.0);         //BERDIRI 3
    glVertex3f(-30.0, 20.0, -60.0);
    glVertex3f(-30.0, 20.0, -58.0);
    glVertex3f(-30.0, 50.0, -58.0);
    glVertex3f(-30.0, 50.0, -67.0);         //BERDIRI 4
    glVertex3f(-30.0, 20.0, -67.0);
    glVertex3f(-30.0, 20.0, -65.0);
    glVertex3f(-30.0, 50.0, -65.0);
    glVertex3f(-30.0, 50.0, -75.0);         //BERDIRI 5
    glVertex3f(-30.0, 20.0, -75.0);
    glVertex3f(-30.0, 20.0, -73.0);
    glVertex3f(-30.0, 50.0, -73.0);
    glVertex3f(-30.0, 50.0, -82.0);         //BERDIRI 6
    glVertex3f(-30.0, 20.0, -82.0);
    glVertex3f(-30.0, 20.0, -80.0);
    glVertex3f(-30.0, 50.0, -80.0);
    glVertex3f(-30.0, 35.0, -89.0);         //BERDIRI 7
    glVertex3f(-30.0, 20.0, -89.0);
    glVertex3f(-30.0, 20.0, -87.0);
    glVertex3f(-30.0, 35.0, -87.0);
    glVertex3f(-30.0, 35.0, -95.0);         //BERDIRI 8
    glVertex3f(-30.0, 20.0, -95.0);
    glVertex3f(-30.0, 20.0, -94.0);
    glVertex3f(-30.0, 35.0, -94.0);
    glVertex3f(-36.0, 20.0, -89.0);         //DEPAN - LANTAI 2
    glVertex3f(-36.0, 15.0, -89.0);
    glVertex3f(-36.0, 15.0, -51.0);
    glVertex3f(-36.0, 20.0, -51.0);
    glVertex3f(-30.0, 10.0, -95.0);         //DEPAN - LANTAI 2
    glVertex3f(-30.0, 5.0, -95.0);
    glVertex3f(-30.0, 5.0, -45.0);
    glVertex3f(-30.0, 10.0, -45.0);
    glVertex3f(-30.0, 25.0, -95.0);         //DEPAN - LANTAI 3
    glVertex3f(-30.0, 15.0, -95.0);
    glVertex3f(-30.0, 15.0, -45.0);
    glVertex3f(-30.0, 25.0, -45.0);
    glVertex3f(-30.0, 40.0, -80.0);         //DEPAN - LANTAI 4
    glVertex3f(-30.0, 30.0, -80.0);
    glVertex3f(-30.0, 30.0, -60.0);
    glVertex3f(-30.0, 40.0, -60.0);
    glVertex3f(-30.0, 50.0, -80.0);         //DEPAN - LANTAI 4
    glVertex3f(-30.0, 45.0, -80.0);
    glVertex3f(-30.0, 45.0, -60.0);
    glVertex3f(-30.0, 50.0, -60.0);
    glVertex3f(-30.0, 37.0, -60.0);         //DEPAN - LANTAI 4
    glVertex3f(-30.0, 30.0, -60.0);
    glVertex3f(-30.0, 30.0, -45.0);
    glVertex3f(-30.0, 37.0, -45.0);
    glVertex3f(-30.0, 37.0, -95.0);         //DEPAN - LANTAI 4
    glVertex3f(-30.0, 30.0, -95.0);
    glVertex3f(-30.0, 30.0, -80.0);
    glVertex3f(-30.0, 37.0, -80.0);
    glVertex3f(-43.0, 50.0, -95.0);         //DEPAN - LANTAI 4 KANAN
    glVertex3f(-43.0, 35.0, -95.0);
    glVertex3f(-43.0, 35.0, -82.0);
    glVertex3f(-43.0, 50.0, -82.0);
    glVertex3f(-43.0, 50.0, -58.0);         //DEPAN - LANTAI 4 KIRI
    glVertex3f(-43.0, 35.0, -58.0);
    glVertex3f(-43.0, 35.0, -45.0);
    glVertex3f(-43.0, 50.0, -45.0);

    glVertex3f(-30.0, 5.0, -47.0);         //DEPAN - PILAR 1
    glVertex3f(-30.0, -10.0, -47.0);
    glVertex3f(-30.0, -10.0, -45.0);
    glVertex3f(-30.0, 5.0, -45.0);
    glVertex3f(-32.0, 5.0, -47.0);         //DEPAN - PILAR 1
    glVertex3f(-32.0, -10.0, -47.0);
    glVertex3f(-32.0, -10.0, -45.0);
    glVertex3f(-32.0, 5.0, -45.0);
    glVertex3f(-30.0, 5.0, -57.0);         //DEPAN - PILAR 2
    glVertex3f(-30.0, -10.0, -57.0);
    glVertex3f(-30.0, -10.0, -55.0);
    glVertex3f(-30.0, 5.0, -55.0);
    glVertex3f(-32.0, 5.0, -57.0);         //DEPAN - PILAR 2
    glVertex3f(-32.0, -10.0, -57.0);
    glVertex3f(-32.0, -10.0, -55.0);
    glVertex3f(-32.0, 5.0, -55.0);
    glVertex3f(-32.0, -10.0, -55.0);       //DEPAN - PILAR 2
    glVertex3f(-32.0, 5.0, -55.0);
    glVertex3f(-30.0, 5.0, -55.0);
    glVertex3f(-30.0, -10.0, -55.0);
    glVertex3f(-32.0, -10.0, -57.0);       //DEPAN - PILAR 2
    glVertex3f(-32.0, 5.0, -57.0);
    glVertex3f(-30.0, 5.0, -57.0);
    glVertex3f(-30.0, -10.0, -57.0);
    glVertex3f(-30.0, 5.0, -66.0);         //DEPAN - PILAR 3
    glVertex3f(-30.0, -10.0, -66.0);
    glVertex3f(-30.0, -10.0, -64.0);
    glVertex3f(-30.0, 5.0, -64.0);
    glVertex3f(-32.0, 5.0, -66.0);         //DEPAN - PILAR 3
    glVertex3f(-32.0, -10.0, -66.0);
    glVertex3f(-32.0, -10.0, -64.0);
    glVertex3f(-32.0, 5.0, -64.0);
    glVertex3f(-32.0, -10.0, -64.0);       //DEPAN - PILAR 3
    glVertex3f(-32.0, 5.0, -64.0);
    glVertex3f(-30.0, 5.0, -64.0);
    glVertex3f(-30.0, -10.0, -64.0);
    glVertex3f(-32.0, -10.0, -66.0);       //DEPAN - PILAR 3
    glVertex3f(-32.0, 5.0, -66.0);
    glVertex3f(-30.0, 5.0, -66.0);
    glVertex3f(-30.0, -10.0, -66.0);
    glVertex3f(-30.0, 5.0, -76.0);         //DEPAN - PILAR 4
    glVertex3f(-30.0, -10.0, -76.0);
    glVertex3f(-30.0, -10.0, -74.0);
    glVertex3f(-30.0, 5.0, -74.0);
    glVertex3f(-32.0, 5.0, -76.0);         //DEPAN - PILAR 4
    glVertex3f(-32.0, -10.0, -76.0);
    glVertex3f(-32.0, -10.0, -74.0);
    glVertex3f(-32.0, 5.0, -74.0);
    glVertex3f(-32.0, -10.0, -74.0);       //DEPAN - PILAR 4
    glVertex3f(-32.0, 5.0, -74.0);
    glVertex3f(-30.0, 5.0, -74.0);
    glVertex3f(-30.0, -10.0, -74.0);
    glVertex3f(-32.0, -10.0, -76.0);       //DEPAN - PILAR 4
    glVertex3f(-32.0, 5.0, -76.0);
    glVertex3f(-30.0, 5.0, -76.0);
    glVertex3f(-30.0, -10.0, -76.0);
    glVertex3f(-30.0, 5.0, -85.0);         //DEPAN - PILAR 5
    glVertex3f(-30.0, -10.0, -85.0);
    glVertex3f(-30.0, -10.0, -83.0);
    glVertex3f(-30.0, 5.0, -83.0);
    glVertex3f(-32.0, 5.0, -85.0);         //DEPAN - PILAR 5
    glVertex3f(-32.0, -10.0, -85.0);
    glVertex3f(-32.0, -10.0, -83.0);
    glVertex3f(-32.0, 5.0, -83.0);
    glVertex3f(-32.0, -10.0, -83.0);       //DEPAN - PILAR 5
    glVertex3f(-32.0, 5.0, -83.0);
    glVertex3f(-30.0, 5.0, -83.0);
    glVertex3f(-30.0, -10.0, -83.0);
    glVertex3f(-32.0, -10.0, -85.0);       //DEPAN - PILAR 5
    glVertex3f(-32.0, 5.0, -85.0);
    glVertex3f(-30.0, 5.0, -85.0);
    glVertex3f(-30.0, -10.0, -85.0);
    glVertex3f(-30.0, 5.0, -95.0);         //DEPAN - PILAR 6
    glVertex3f(-30.0, -10.0, -95.0);
    glVertex3f(-30.0, -10.0, -93.0);
    glVertex3f(-30.0, 5.0, -93.0);
    glVertex3f(-32.0, 5.0, -95.0);         //DEPAN - PILAR 6
    glVertex3f(-32.0, -10.0, -95.0);
    glVertex3f(-32.0, -10.0, -93.0);
    glVertex3f(-32.0, 5.0, -93.0);
    glVertex3f(-32.0, -10.0, -93.0);       //DEPAN - PILAR 6
    glVertex3f(-32.0, 5.0, -93.0);
    glVertex3f(-30.0, 5.0, -93.0);
    glVertex3f(-30.0, -10.0, -93.0);
    glVertex3f(-33.0, -10.0, -95.0);       //DEPAN - PILAR 6
    glVertex3f(-33.0, 5.0, -95.0);
    glVertex3f(-30.0, 5.0, -95.0);
    glVertex3f(-30.0, -10.0, -95.0);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.5, 0.5, 0.5);                 //LANTAI - 1
    glVertex3f(-30, -9.9, -95.0);
    glVertex3f(-100, -9.9, -95.0);
    glVertex3f(-100, -9.9, -45.0);
    glVertex3f(-30, -9.9, -45.0);
    glVertex3f(-30, 5.0, -95.0);            //LANTAI - 2
    glVertex3f(-100, 5.0, -95.0);
    glVertex3f(-100, 5.0, -45.0);
    glVertex3f(-30, 5.0, -45.0);
    glVertex3f(-30, 20.0, -95.0);            //LANTAI - 3
    glVertex3f(-100, 20.0, -95.0);
    glVertex3f(-100, 20.0, -45.0);
    glVertex3f(-30, 20.0, -45.0);
    glVertex3f(-43, 35.0, -95.0);            //LANTAI - 4
    glVertex3f(-100, 35.0, -95.0);
    glVertex3f(-100, 35.0, -45.0);
    glVertex3f(-43, 35.0, -45.0);
    glVertex3f(-30, 50.0, -105.0);            //LANTAI - 4 1
    glVertex3f(-100, 50.0, -105.0);
    glVertex3f(-100, 50.0, -35.0);
    glVertex3f(-30, 50.0, -35.0);
    glVertex3f(-20, 50.0, -85.0);            //LANTAI - 4 2
    glVertex3f(-43, 50.0, -85.0);
    glVertex3f(-43, 50.0, -55.0);
    glVertex3f(-20, 50.0, -55.0);
    glVertex3f(-30, 35.0, -82.0);            //LANTAI - 4
    glVertex3f(-43, 35.0, -82.0);
    glVertex3f(-43, 35.0, -58.0);
    glVertex3f(-30, 35.0, -58.0);
    glVertex3f(-30, 50.0, -82.0);            //LANTAI - 4
    glVertex3f(-43, 50.0, -82.0);
    glVertex3f(-43, 50.0, -58.0);
    glVertex3f(-30, 50.0, -58.0);
    glEnd();

    glBegin(GL_QUADS);                      //PINTU
    glColor3f(0.66, 0.40, 0.0);
    glVertex3f(-36.0, 0.0, -73.0);
    glVertex3f(-36.0, -10.0, -73.0);
    glVertex3f(-36.0, -10.0, -67.0);
    glVertex3f(-36.0, 0.0, -67.0);
    glEnd();

    glBegin(GL_QUADS);                      //ATAP
    glColor3f(0.2, 0.2, 0.2);               //DEPAN - BAWAH PANJANG
    glVertex3f(-30.0, 40.0, -82.0);
    glVertex3f(-20.0, 30.0, -82.0);
    glVertex3f(-20.0, 30.0, -58.0);
    glVertex3f(-30.0, 40.0, -58.0);
    glEnd();
    glBegin(GL_POLYGON);                    //DEPAN - BAWAH KIRI
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-43, 50.0, -58.0);
    glVertex3f(-30, 40.0, -58.0);
    glVertex3f(-20, 30.0, -58.0);
    glVertex3f(-20, 30.0, -45.0);
    glVertex3f(-30, 40.0, -45.0);
    glEnd();
    glBegin(GL_POLYGON);                    //DEPAN - BAWAH UJUNG KIRI
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-30.0, 40.0, -45.0);
    glVertex3f(-20.0, 30.0, -45.0);
    glVertex3f(-20.0, 30.0, -35.0);
    glVertex3f(-30.0, 30.0, -35.0);
    glEnd();
    glBegin(GL_POLYGON);                    //DEPAN - BAWAH KANAN
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-43, 50.0, -82.0);
    glVertex3f(-30, 40.0, -82.0);
    glVertex3f(-20, 30.0, -82.0);
    glVertex3f(-20, 30.0, -95.0);
    glVertex3f(-30, 40.0, -95.0);
    glEnd();
    glBegin(GL_POLYGON);                    //DEPAN - BAWAH UJUNG KANAN
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-30.0, 40.0, -95.0);
    glVertex3f(-20.0, 30.0, -95.0);
    glVertex3f(-20.0, 30.0, -105.0);
    glVertex3f(-30.0, 30.0, -105.0);
    glEnd();
    glBegin(GL_POLYGON);                    //KIRI - KANAN
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-43.0, 50.0, -58.0);
    glVertex3f(-30.0, 40.0, -45.0);
    glVertex3f(-30.0, 30.0, -35.0);
    glVertex3f(-43.0, 30.0, -35.0);
    glVertex3f(-43.0, 40.0, -45.0);
    glEnd();
    glBegin(GL_QUADS);                      //KIRI - SISI SIRIP PANJANG TENGAH
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-43, 40.0, -45.0);
    glVertex3f(-100, 40.0, -45.0);
    glVertex3f(-100, 30.0, -35.0);
    glVertex3f(-43, 30.0, -35.0);
    glEnd();
    glBegin(GL_QUADS);                      //KIRI - SISI SIRIP PANJANG ATAS
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-45, 70.0, -60.0);
    glVertex3f(-100, 70.0, -60.0);
    glVertex3f(-100, 50.0, -35.0);
    glVertex3f(-30, 50.0, -35.0);
    glEnd();
    glBegin(GL_QUADS);                      //KIRI - SISI SIRIP PENDEK BAWAH
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-30, 60.0, -63.0);
    glVertex3f(-40, 60.0, -63.0);
    glVertex3f(-30, 50.0, -55.0);
    glVertex3f(-20, 50.0, -55.0);
    glEnd();
    glBegin(GL_POLYGON);                    //KIRI - SIRIP BESAR ATAS
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-55.0, 90.0, -65.0);
    glVertex3f(-45.0, 110.0, -70.0);
    glVertex3f(-100.0, 110.0, -70.0);
    glVertex3f(-100.0, 70.0, -60.0);
    glVertex3f(-45.0, 70.0, -60.0);
    glEnd();
    glBegin(GL_POLYGON);                    //KIRI - SIRIP KECIL BAWAH
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-40.0, 75.0, -66.0);
    glVertex3f(-30.0, 90.0, -70.0);
    glVertex3f(-55.0, 90.0, -70.0);
    glVertex3f(-40.0, 60.0, -62.0);
    glVertex3f(-30.0, 60.0, -62.0);
    glEnd();
    glBegin(GL_POLYGON);                    //KANAN - KIRI
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-43.0, 50.0, -82.0);
    glVertex3f(-43.0, 40.0, -95.0);
    glVertex3f(-43.0, 30.0, -105.0);
    glVertex3f(-30.0, 30.0, -105.0);
    glVertex3f(-30.0, 40.0, -95.0);
    glEnd();
    glBegin(GL_POLYGON);                    //KANAN - SISI SIRIP PANJANG TENGAH
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-43, 30.0, -105.0);
    glVertex3f(-100, 30.0, -105.0);
    glVertex3f(-100, 40.0, -95.0);
    glVertex3f(-43, 40.0, -95.0);
    glEnd();
    glBegin(GL_POLYGON);                    //KANAN - SISI SIRIP PANJANG ATAS
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-30, 50.0, -105.0);
    glVertex3f(-100, 50.0, -105.0);
    glVertex3f(-100, 70.0, -80.0);
    glVertex3f(-45, 70.0, -80.0);
    glEnd();
    glBegin(GL_POLYGON);                    //KANAN - SISI SIRIP PENDEK BAWAH
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-20, 50.0, -85.0);
    glVertex3f(-30, 50.0, -85.0);
    glVertex3f(-40, 60.0, -77.0);
    glVertex3f(-30, 60.0, -77.0);
    glEnd();
    glBegin(GL_POLYGON);                    //KANAN - SIRIP BESAR ATAS
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-55.0, 90.0, -75.0);
    glVertex3f(-45.0, 110.0, -70.0);
    glVertex3f(-100.0, 110.0, -70.0);
    glVertex3f(-100.0, 70.0, -80.0);
    glVertex3f(-45.0, 70.0, -80.0);
    glEnd();
    glBegin(GL_POLYGON);                    //KANAN - SIRIP KECIL BAWAH
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-40.0, 75.0, -74.0);
    glVertex3f(-30.0, 90.0, -70.0);
    glVertex3f(-55.0, 90.0, -70.0);
    glVertex3f(-40.0, 60.0, -78.0);
    glVertex3f(-30.0, 60.0, -78.0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-45.0, 70.0, -80.0);         //DEPAN - PENUTUP SIRIP BESAR BAWAH
    glVertex3f(-55.0, 90.0, -75.0);
    glVertex3f(-55.0, 90.0, -65.0);
    glVertex3f(-45.0, 70.0, -60.0);
    glVertex3f(-30.0, 50.0, -35.0);
    glVertex3f(-30.0, 50.0, -105.0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-55.0, 90.0, -65.0);         //DEPAN - PENUTUP SIRIP BESAR ATAS
    glVertex3f(-55.0, 90.0, -75.0);
    glVertex3f(-45.0, 110.0, -70.0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-40.0, 75.0, -74.0);         //DEPAN - PENUTUP SIRIP KECIL BAWAH
    glVertex3f(-40.0, 75.0, -66.0);
    glVertex3f(-30.0, 60.0, -62.0);
    glVertex3f(-20.0, 50.0, -55.0);
    glVertex3f(-20.0, 50.0, -85.0);
    glVertex3f(-30.0, 60.0, -78.0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-40.0, 75.0, -74.0);         //DEPAN - PENUTUP SIRIP KECIL ATAS
    glVertex3f(-30.0, 90.0, -70.0);
    glVertex3f(-40.0, 75.0, -66.0);
    glEnd();
    //SAMPAI SINI


    //GEDUNG 4
    glBegin(GL_LINE_LOOP);              //JENDELA KIRI DARI KANAN - LANTAI 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(43.0, -5.0, -51.0);
    glVertex3f(43.0, 0.0, -51.0);
    glVertex3f(38.0, 0.0, -51.0);
    glVertex3f(38.0, -5.0, -51.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(50.0, -5.0, -51.0);
    glVertex3f(50.0, 0.0, -51.0);
    glVertex3f(45.0, 0.0, -51.0);
    glVertex3f(45.0, -5.0, -51.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(57.0, -5.0, -51.0);
    glVertex3f(57.0, 0.0, -51.0);
    glVertex3f(52.0, 0.0, -51.0);
    glVertex3f(52.0, -5.0, -51.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(64.0, -5.0, -51.0);
    glVertex3f(64.0, 0.0, -51.0);
    glVertex3f(59.0, 0.0, -51.0);
    glVertex3f(59.0, -5.0, -51.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(71.0, -5.0, -51.0);
    glVertex3f(71.0, 0.0, -51.0);
    glVertex3f(66.0, 0.0, -51.0);
    glVertex3f(66.0, -5.0, -51.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(78.0, -5.0, -51.0);
    glVertex3f(78.0, 0.0, -51.0);
    glVertex3f(73.0, 0.0, -51.0);
    glVertex3f(73.0, -5.0, -51.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(85.0, -5.0, -51.0);
    glVertex3f(85.0, 0.0, -51.0);
    glVertex3f(80.0, 0.0, -51.0);
    glVertex3f(80.0, -5.0, -51.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(92.0, -5.0, -51.0);
    glVertex3f(92.0, 0.0, -51.0);
    glVertex3f(87.0, 0.0, -51.0);
    glVertex3f(87.0, -5.0, -51.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(99.0, -5.0, -51.0);
    glVertex3f(99.0, 0.0, -51.0);
    glVertex3f(94.0, 0.0, -51.0);
    glVertex3f(94.0, -5.0, -51.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(43.0, 10.0, -51.0);
    glVertex3f(43.0, 15.0, -51.0);
    glVertex3f(38.0, 15.0, -51.0);
    glVertex3f(38.0, 10.0, -51.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(50.0, 10.0, -51.0);
    glVertex3f(50.0, 15.0, -51.0);
    glVertex3f(45.0, 15.0, -51.0);
    glVertex3f(45.0, 10.0, -51.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(57.0, 10.0, -51.0);
    glVertex3f(57.0, 15.0, -51.0);
    glVertex3f(52.0, 15.0, -51.0);
    glVertex3f(52.0, 10.0, -51.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(64.0, 10.0, -51.0);
    glVertex3f(64.0, 15.0, -51.0);
    glVertex3f(59.0, 15.0, -51.0);
    glVertex3f(59.0, 10.0, -51.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(71.0, 10.0, -51.0);
    glVertex3f(71.0, 15.0, -51.0);
    glVertex3f(66.0, 15.0, -51.0);
    glVertex3f(66.0, 10.0, -51.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(78.0, 10.0, -51.0);
    glVertex3f(78.0, 15.0, -51.0);
    glVertex3f(73.0, 15.0, -51.0);
    glVertex3f(73.0, 10.0, -51.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(85.0, 10.0, -51.0);
    glVertex3f(85.0, 15.0, -51.0);
    glVertex3f(80.0, 15.0, -51.0);
    glVertex3f(80.0, 10.0, -51.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(92.0, 10.0, -51.0);
    glVertex3f(92.0, 15.0, -51.0);
    glVertex3f(87.0, 15.0, -51.0);
    glVertex3f(87.0, 10.0, -51.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(99.0, 10.0, -51.0);
    glVertex3f(99.0, 15.0, -51.0);
    glVertex3f(94.0, 15.0, -51.0);
    glVertex3f(94.0, 10.0, -51.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(36.0, 25.0, -45.0);
    glVertex3f(36.0, 30.0, -45.0);
    glVertex3f(31.0, 30.0, -45.0);
    glVertex3f(31.0, 25.0, -45.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(43.0, 25.0, -45.0);
    glVertex3f(43.0, 30.0, -45.0);
    glVertex3f(38.0, 30.0, -45.0);
    glVertex3f(38.0, 25.0, -45.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(50.0, 25.0, -45.0);
    glVertex3f(50.0, 30.0, -45.0);
    glVertex3f(45.0, 30.0, -45.0);
    glVertex3f(45.0, 25.0, -45.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(57.0, 25.0, -45.0);
    glVertex3f(57.0, 30.0, -45.0);
    glVertex3f(52.0, 30.0, -45.0);
    glVertex3f(52.0, 25.0, -45.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(64.0, 25.0, -45.0);
    glVertex3f(64.0, 30.0, -45.0);
    glVertex3f(59.0, 30.0, -45.0);
    glVertex3f(59.0, 25.0, -45.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(71.0, 25.0, -45.0);
    glVertex3f(71.0, 30.0, -45.0);
    glVertex3f(66.0, 30.0, -45.0);
    glVertex3f(66.0, 25.0, -45.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(78.0, 25.0, -45.0);
    glVertex3f(78.0, 30.0, -45.0);
    glVertex3f(73.0, 30.0, -45.0);
    glVertex3f(73.0, 25.0, -45.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(85.0, 25.0, -45.0);
    glVertex3f(85.0, 30.0, -45.0);
    glVertex3f(80.0, 30.0, -45.0);
    glVertex3f(80.0, 25.0, -45.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(92.0, 25.0, -45.0);
    glVertex3f(92.0, 30.0, -45.0);
    glVertex3f(87.0, 30.0, -45.0);
    glVertex3f(87.0, 25.0, -45.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(99.0, 25.0, -45.0);
    glVertex3f(99.0, 30.0, -45.0);
    glVertex3f(94.0, 30.0, -45.0);
    glVertex3f(94.0, 25.0, -45.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(50.0, 40.0, -45.0);
    glVertex3f(50.0, 45.0, -45.0);
    glVertex3f(45.0, 45.0, -45.0);
    glVertex3f(45.0, 40.0, -45.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(57.0, 40.0, -45.0);
    glVertex3f(57.0, 45.0, -45.0);
    glVertex3f(52.0, 45.0, -45.0);
    glVertex3f(52.0, 40.0, -45.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(64.0, 40.0, -45.0);
    glVertex3f(64.0, 45.0, -45.0);
    glVertex3f(59.0, 45.0, -45.0);
    glVertex3f(59.0, 40.0, -45.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(71.0, 40.0, -45.0);
    glVertex3f(71.0, 45.0, -45.0);
    glVertex3f(66.0, 45.0, -45.0);
    glVertex3f(66.0, 40.0, -45.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(78.0, 40.0, -45.0);
    glVertex3f(78.0, 45.0, -45.0);
    glVertex3f(73.0, 45.0, -45.0);
    glVertex3f(73.0, 40.0, -45.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(85.0, 40.0, -45.0);
    glVertex3f(85.0, 45.0, -45.0);
    glVertex3f(80.0, 45.0, -45.0);
    glVertex3f(80.0, 40.0, -45.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(92.0, 40.0, -45.0);
    glVertex3f(92.0, 45.0, -45.0);
    glVertex3f(87.0, 45.0, -45.0);
    glVertex3f(87.0, 40.0, -45.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(99.0, 40.0, -45.0);
    glVertex3f(99.0, 45.0, -45.0);
    glVertex3f(94.0, 45.0, -45.0);
    glVertex3f(94.0, 40.0, -45.0);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 0.0, 0.0);         //JENDELA KANAN DARI KIRI - LANTAI 1
    glVertex3f(43.0, -5.0, -89.0);
    glVertex3f(43.0, 0.0, -89.0);
    glVertex3f(38.0, 0.0, -89.0);
    glVertex3f(38.0, -5.0, -89.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(50.0, -5.0, -89.0);
    glVertex3f(50.0, 0.0, -89.0);
    glVertex3f(45.0, 0.0, -89.0);
    glVertex3f(45.0, -5.0, -89.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(57.0, -5.0, -89.0);
    glVertex3f(57.0, 0.0, -89.0);
    glVertex3f(52.0, 0.0, -89.0);
    glVertex3f(52.0, -5.0, -89.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(64.0, -5.0, -89.0);
    glVertex3f(64.0, 0.0, -89.0);
    glVertex3f(59.0, 0.0, -89.0);
    glVertex3f(59.0, -5.0, -89.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(71.0, -5.0, -89.0);
    glVertex3f(71.0, 0.0, -89.0);
    glVertex3f(66.0, 0.0, -89.0);
    glVertex3f(66.0, -5.0, -89.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(78.0, -5.0, -89.0);
    glVertex3f(78.0, 0.0, -89.0);
    glVertex3f(73.0, 0.0, -89.0);
    glVertex3f(73.0, -5.0, -89.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(85.0, -5.0, -89.0);
    glVertex3f(85.0, 0.0, -89.0);
    glVertex3f(80.0, 0.0, -89.0);
    glVertex3f(80.0, -5.0, -89.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(92.0, -5.0, -89.0);
    glVertex3f(92.0, 0.0, -89.0);
    glVertex3f(87.0, 0.0, -89.0);
    glVertex3f(87.0, -5.0, -89.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(99.0, -5.0, -89.0);
    glVertex3f(99.0, 0.0, -89.0);
    glVertex3f(94.0, 0.0, -89.0);
    glVertex3f(94.0, -5.0, -89.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(43.0, 10.0, -89.0);
    glVertex3f(43.0, 15.0, -89.0);
    glVertex3f(38.0, 15.0, -89.0);
    glVertex3f(38.0, 10.0, -89.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(50.0, 10.0, -89.0);
    glVertex3f(50.0, 15.0, -89.0);
    glVertex3f(45.0, 15.0, -89.0);
    glVertex3f(45.0, 10.0, -89.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(57.0, 10.0, -89.0);
    glVertex3f(57.0, 15.0, -89.0);
    glVertex3f(52.0, 15.0, -89.0);
    glVertex3f(52.0, 10.0, -89.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(64.0, 10.0, -89.0);
    glVertex3f(64.0, 15.0, -89.0);
    glVertex3f(59.0, 15.0, -89.0);
    glVertex3f(59.0, 10.0, -89.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(71.0, 10.0, -89.0);
    glVertex3f(71.0, 15.0, -89.0);
    glVertex3f(66.0, 15.0, -89.0);
    glVertex3f(66.0, 10.0, -89.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(78.0, 10.0, -89.0);
    glVertex3f(78.0, 15.0, -89.0);
    glVertex3f(73.0, 15.0, -89.0);
    glVertex3f(73.0, 10.0, -89.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(85.0, 10.0, -89.0);
    glVertex3f(85.0, 15.0, -89.0);
    glVertex3f(80.0, 15.0, -89.0);
    glVertex3f(80.0, 10.0, -89.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(92.0, 10.0, -89.0);
    glVertex3f(92.0, 15.0, -89.0);
    glVertex3f(87.0, 15.0, -89.0);
    glVertex3f(87.0, 10.0, -89.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(99.0, 10.0, -89.0);
    glVertex3f(99.0, 15.0, -89.0);
    glVertex3f(94.0, 15.0, -89.0);
    glVertex3f(94.0, 10.0, -89.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(36.0, 25.0, -95.0);
    glVertex3f(36.0, 30.0, -95.0);
    glVertex3f(31.0, 30.0, -95.0);
    glVertex3f(31.0, 25.0, -95.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(43.0, 25.0, -95.0);
    glVertex3f(43.0, 30.0, -95.0);
    glVertex3f(38.0, 30.0, -95.0);
    glVertex3f(38.0, 25.0, -95.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(50.0, 25.0, -95.0);
    glVertex3f(50.0, 30.0, -95.0);
    glVertex3f(45.0, 30.0, -95.0);
    glVertex3f(45.0, 25.0, -95.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(57.0, 25.0, -95.0);
    glVertex3f(57.0, 30.0, -95.0);
    glVertex3f(52.0, 30.0, -95.0);
    glVertex3f(52.0, 25.0, -95.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(64.0, 25.0, -95.0);
    glVertex3f(64.0, 30.0, -95.0);
    glVertex3f(59.0, 30.0, -95.0);
    glVertex3f(59.0, 25.0, -95.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(71.0, 25.0, -95.0);
    glVertex3f(71.0, 30.0, -95.0);
    glVertex3f(66.0, 30.0, -95.0);
    glVertex3f(66.0, 25.0, -95.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(78.0, 25.0, -95.0);
    glVertex3f(78.0, 30.0, -95.0);
    glVertex3f(73.0, 30.0, -95.0);
    glVertex3f(73.0, 25.0, -95.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(85.0, 25.0, -95.0);
    glVertex3f(85.0, 30.0, -95.0);
    glVertex3f(80.0, 30.0, -95.0);
    glVertex3f(80.0, 25.0, -95.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(92.0, 25.0, -95.0);
    glVertex3f(92.0, 30.0, -95.0);
    glVertex3f(87.0, 30.0, -95.0);
    glVertex3f(87.0, 25.0, -95.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(99.0, 25.0, -95.0);
    glVertex3f(99.0, 30.0, -95.0);
    glVertex3f(94.0, 30.0, -95.0);
    glVertex3f(94.0, 25.0, -95.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(50.0, 40.0, -95.0);
    glVertex3f(50.0, 45.0, -95.0);
    glVertex3f(45.0, 45.0, -95.0);
    glVertex3f(45.0, 40.0, -95.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(57.0, 40.0, -95.0);
    glVertex3f(57.0, 45.0, -95.0);
    glVertex3f(52.0, 45.0, -95.0);
    glVertex3f(52.0, 40.0, -95.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(64.0, 40.0, -95.0);
    glVertex3f(64.0, 45.0, -95.0);
    glVertex3f(59.0, 45.0, -95.0);
    glVertex3f(59.0, 40.0, -95.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(71.0, 40.0, -95.0);
    glVertex3f(71.0, 45.0, -95.0);
    glVertex3f(66.0, 45.0, -95.0);
    glVertex3f(66.0, 40.0, -95.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(78.0, 40.0, -95.0);
    glVertex3f(78.0, 45.0, -95.0);
    glVertex3f(73.0, 45.0, -95.0);
    glVertex3f(73.0, 40.0, -95.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(85.0, 40.0, -95.0);
    glVertex3f(85.0, 45.0, -95.0);
    glVertex3f(80.0, 45.0, -95.0);
    glVertex3f(80.0, 40.0, -95.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(92.0, 40.0, -95.0);
    glVertex3f(92.0, 45.0, -95.0);
    glVertex3f(87.0, 45.0, -95.0);
    glVertex3f(87.0, 40.0, -95.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(99.0, 40.0, -95.0);
    glVertex3f(99.0, 45.0, -95.0);
    glVertex3f(94.0, 45.0, -95.0);
    glVertex3f(94.0, 40.0, -95.0);
    glEnd();

    glBegin(GL_LINE_LOOP);              //JENDELA DEPAN DARI KIRI- LANTAI 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(36.0, 0.0, -58.0);
    glVertex3f(36.0, -5.0, -58.0);
    glVertex3f(36.0, -5.0, -53.0);
    glVertex3f(36.0, 0.0, -53.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.D - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(36.0, 0.0, -65.0);
    glVertex3f(36.0, -5.0, -65.0);
    glVertex3f(36.0, -5.0, -60.0);
    glVertex3f(36.0, 0.0, -60.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(36.0, 0.0, -80.0);
    glVertex3f(36.0, -5.0, -80.0);
    glVertex3f(36.0, -5.0, -75.0);
    glVertex3f(36.0, 0.0, -75.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(36.0, 0.0, -87.0);
    glVertex3f(36.0, -5.0, -87.0);
    glVertex3f(36.0, -5.0, -82.0);
    glVertex3f(36.0, 0.0, -82.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(36.0, 15.0, -58.0);
    glVertex3f(36.0, 10.0, -58.0);
    glVertex3f(36.0, 10.0, -53.0);
    glVertex3f(36.0, 15.0, -53.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(36.0, 15.0, -65.0);
    glVertex3f(36.0, 10.0, -65.0);
    glVertex3f(36.0, 10.0, -60.0);
    glVertex3f(36.0, 15.0, -60.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(36.0, 15.0, -73.0);
    glVertex3f(36.0, 10.0, -73.0);
    glVertex3f(36.0, 10.0, -67.0);
    glVertex3f(36.0, 15.0, -67.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(36.0, 15.0, -80.0);
    glVertex3f(36.0, 10.0, -80.0);
    glVertex3f(36.0, 10.0, -75.0);
    glVertex3f(36.0, 15.0, -75.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(36.0, 15.0, -87.0);
    glVertex3f(36.0, 10.0, -87.0);
    glVertex3f(36.0, 10.0, -82.0);
    glVertex3f(36.0, 15.0, -82.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(30.0, 25.0, -51.0);
    glVertex3f(30.0, 30.0, -51.0);
    glVertex3f(30.0, 30.0, -46.0);
    glVertex3f(30.0, 25.0, -46.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(30.0, 25.0, -58.0);
    glVertex3f(30.0, 30.0, -58.0);
    glVertex3f(30.0, 30.0, -53.0);
    glVertex3f(30.0, 25.0, -53.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(30.0, 25.0, -65.0);
    glVertex3f(30.0, 30.0, -65.0);
    glVertex3f(30.0, 30.0, -60.0);
    glVertex3f(30.0, 25.0, -60.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(30.0, 25.0, -73.0);
    glVertex3f(30.0, 30.0, -73.0);
    glVertex3f(30.0, 30.0, -67.0);
    glVertex3f(30.0, 25.0, -67.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(30.0, 25.0, -80.0);
    glVertex3f(30.0, 30.0, -80.0);
    glVertex3f(30.0, 30.0, -75.0);
    glVertex3f(30.0, 25.0, -75.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(30.0, 25.0, -87.0);
    glVertex3f(30.0, 30.0, -87.0);
    glVertex3f(30.0, 30.0, -82.0);
    glVertex3f(30.0, 25.0, -82.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(30.0, 25.0, -94.0);
    glVertex3f(30.0, 30.0, -94.0);
    glVertex3f(30.0, 30.0, -89.0);
    glVertex3f(30.0, 25.0, -89.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(30.0, 45.0, -65.0);
    glVertex3f(30.0, 40.0, -65.0);
    glVertex3f(30.0, 40.0, -60.0);
    glVertex3f(30.0, 45.0, -60.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(30.0, 45.0, -73.0);
    glVertex3f(30.0, 40.0, -73.0);
    glVertex3f(30.0, 40.0, -67.0);
    glVertex3f(30.0, 45.0, -67.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(30.0, 45.0, -80.0);
    glVertex3f(30.0, 40.0, -80.0);
    glVertex3f(30.0, 40.0, -75.0);
    glVertex3f(30.0, 45.0, -75.0);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);                 //KIRI - LANTAI 1
    glVertex3f(100.0, -10.0, -51.0);
    glVertex3f(100.0, -5.0, -51.0);
    glVertex3f(36.0, -5.0, -51.0);
    glVertex3f(36.0, -10.0, -51.0);//
    glVertex3f(38.0, -10.0, -51.0);        //BERDIRI - LANTAI 1-2 DARI KANAN 1
    glVertex3f(38.0, 20.0, -51.0);
    glVertex3f(36.0, 20.0, -51.0);
    glVertex3f(36.0, -10.0, -51.0);//
    glVertex3f(45.0, -10.0, -51.0);        //BERDIRI 2
    glVertex3f(45.0, 20.0, -51.0);
    glVertex3f(43.0, 20.0, -51.0);
    glVertex3f(43.0, -10.0, -51.0);//
    glVertex3f(52.0, -10.0, -51.0);        //BERDIRI 3
    glVertex3f(52.0, 20.0, -51.0);
    glVertex3f(50.0, 20.0, -51.0);
    glVertex3f(50.0, -10.0, -51.0);//
    glVertex3f(59.0, -10.0, -51.0);        //BERDIRI 4
    glVertex3f(59.0, 20.0, -51.0);
    glVertex3f(57.0, 20.0, -51.0);
    glVertex3f(57.0, -10.0, -51.0);//
    glVertex3f(66.0, -10.0, -51.0);        //BERDIRI 5
    glVertex3f(66.0, 20.0, -51.0);
    glVertex3f(64.0, 20.0, -51.0);
    glVertex3f(64.0, -10.0, -51.0);//
    glVertex3f(73.0, -10.0, -51.0);        //BERDIRI 6
    glVertex3f(73.0, 20.0, -51.0);
    glVertex3f(71.0, 20.0, -51.0);
    glVertex3f(71.0, -10.0, -51.0);//
    glVertex3f(80.0, -10.0, -51.0);        //BERDIRI 7
    glVertex3f(80.0, 20.0, -51.0);
    glVertex3f(78.0, 20.0, -51.0);
    glVertex3f(78.0, -10.0, -51.0);//
    glVertex3f(87.0, -10.0, -51.0);        //BERDIRI 8
    glVertex3f(87.0, 20.0, -51.0);
    glVertex3f(85.0, 20.0, -51.0);
    glVertex3f(85.0, -10.0, -51.0);//
    glVertex3f(94.0, -10.0, -51.0);        //BERDIRI 9
    glVertex3f(94.0, 20.0, -51.0);
    glVertex3f(92.0, 20.0, -51.0);
    glVertex3f(92.0, -10.0, -51.0);//
    glVertex3f(100.0, -10.0, -51.0);       //BERDIRI 9
    glVertex3f(100.0, 20.0, -51.0);
    glVertex3f(99.0, 20.0, -51.0);
    glVertex3f(99.0, -10.0, -51.0);//
    glVertex3f(100.0, 0.0, -51.0);         //KIRI - LANTAI 1-2
    glVertex3f(100.0, 10.0, -51.0);
    glVertex3f(36.0, 10.0, -51.0);
    glVertex3f(36.0, 0.0, -51.0);//
    glVertex3f(31.0, 20.0, -45.0);         //BERDIRI - LANTAI 2-4 DARI KANAN 1
    glVertex3f(31.0, 35.0, -45.0);
    glVertex3f(30.0, 35.0, -45.0);
    glVertex3f(30.0, 20.0, -45.0);//
    glVertex3f(38.0, 20.0, -45.0);         //BERDIRI 2
    glVertex3f(38.0, 35.0, -45.0);
    glVertex3f(36.0, 35.0, -45.0);
    glVertex3f(36.0, 20.0, -45.0);//
    glVertex3f(45.0, 20.0, -45.0);         //BERDIRI 3
    glVertex3f(45.0, 50.0, -45.0);
    glVertex3f(43.0, 50.0, -45.0);
    glVertex3f(43.0, 20.0, -45.0);//
    glVertex3f(52.0, 20.0, -45.0);         //BERDIRI 4
    glVertex3f(52.0, 50.0, -45.0);
    glVertex3f(50.0, 50.0, -45.0);
    glVertex3f(50.0, 20.0, -45.0);//
    glVertex3f(59.0, 20.0, -45.0);         //BERDIRI 5
    glVertex3f(59.0, 50.0, -45.0);
    glVertex3f(57.0, 50.0, -45.0);
    glVertex3f(57.0, 20.0, -45.0);//
    glVertex3f(66.0, 20.0, -45.0);         //BERDIRI 6
    glVertex3f(66.0, 50.0, -45.0);
    glVertex3f(64.0, 50.0, -45.0);
    glVertex3f(64.0, 20.0, -45.0);//
    glVertex3f(73.0, 20.0, -45.0);         //BERDIRI 7
    glVertex3f(73.0, 50.0, -45.0);
    glVertex3f(71.0, 50.0, -45.0);
    glVertex3f(71.0, 20.0, -45.0);//
    glVertex3f(80.0, 20.0, -45.0);         //BERDIRI 8
    glVertex3f(80.0, 50.0, -45.0);
    glVertex3f(78.0, 50.0, -45.0);
    glVertex3f(78.0, 20.0, -45.0);//
    glVertex3f(87.0, 20.0, -45.0);         //BERDIRI 9
    glVertex3f(87.0, 50.0, -45.0);
    glVertex3f(85.0, 50.0, -45.0);
    glVertex3f(85.0, 20.0, -45.0);//
    glVertex3f(94.0, 20.0, -45.0);         //BERDIRI 10
    glVertex3f(94.0, 50.0, -45.0);
    glVertex3f(92.0, 50.0, -45.0);
    glVertex3f(92.0, 20.0, -45.0);//
    glVertex3f(100.0, 20.0, -45.0);        //BERDIRI 11
    glVertex3f(100.0, 50.0, -45.0);
    glVertex3f(99.0, 50.0, -45.0);
    glVertex3f(99.0, 20.0, -45.0);//
    glVertex3f(100.0, 15.0, -51.0);        //KIRI - LANTAI 2
    glVertex3f(100.0, 20.0, -51.0);
    glVertex3f(30.0, 20.0, -51.0);
    glVertex3f(30.0, 15.0, -51.0);//
    glVertex3f(100.0, 5.0, -45.0);         //KIRI - LANTAI 2
    glVertex3f(100.0, 10.0, -45.0);
    glVertex3f(30.0, 10.0, -45.0);
    glVertex3f(30.0, 5.0, -45.0);//
    glVertex3f(100.0, 15.0, -45.0);        //KIRI - LANTAI 3
    glVertex3f(100.0, 25.0, -45.0);
    glVertex3f(30.0, 25.0, -45.0);
    glVertex3f(30.0, 15.0, -45.0);//
    glVertex3f(100.0, 30.0, -45.0);        //KIRI - LANTAI 3-4
    glVertex3f(100.0, 40.0, -45.0);
    glVertex3f(43.0, 40.0, -45.0);
    glVertex3f(43.0, 30.0, -45.0);
    glVertex3f(100.0, 45.0, -45.0);        //KIRI - LANTAI 4
    glVertex3f(100.0, 50.0, -45.0);
    glVertex3f(43.0, 50.0, -45.0);
    glVertex3f(43.0, 45.0, -45.0);
    glVertex3f(43.0, 30.0, -45.0);         //KIRI - LANTAI 4
    glVertex3f(43.0, 38.0, -45.0);
    glVertex3f(30.0, 38.0, -45.0);
    glVertex3f(30.0, 30.0, -45.0);
    glVertex3f(43.0, 40.0, -58.0);        //KIRI - LANTAI 4
    glVertex3f(43.0, 50.0, -58.0);
    glVertex3f(30.0, 50.0, -58.0);
    glVertex3f(30.0, 40.0, -58.0);

    glVertex3f(33.0, -10.0, -45.0);         //KIRI - PILAR 1
    glVertex3f(33.0, 5.0, -45.0);
    glVertex3f(30.0, 5.0, -45.0);
    glVertex3f(30.0, -10.0, -45.0);
    glVertex3f(33.0, -10.0, -48.0);         //KIRI - PILAR 1
    glVertex3f(33.0, 5.0, -48.0);
    glVertex3f(30.0, 5.0, -48.0);
    glVertex3f(30.0, -10.0, -48.0);
    glVertex3f(43.0, -10.0, -45.0);         //KIRI - PILAR 2
    glVertex3f(43.0, 5.0, -45.0);
    glVertex3f(40.0, 5.0, -45.0);
    glVertex3f(40.0, -10.0, -45.0);
    glVertex3f(43.0, -10.0, -48.0);         //KIRI - PILAR 2
    glVertex3f(43.0, 5.0, -48.0);
    glVertex3f(40.0, 5.0, -48.0);
    glVertex3f(40.0, -10.0, -48.0);
    glVertex3f(40.0, 5.0, -48.0);           //KIRI - PILAR 2
    glVertex3f(40.0, -10.0, -48.0);
    glVertex3f(40.0, -10.0, -45.0);
    glVertex3f(40.0, 5.0, -45.0);
    glVertex3f(43.0, 5.0, -48.0);           //KIRI - PILAR 2
    glVertex3f(43.0, -10.0, -48.0);
    glVertex3f(43.0, -10.0, -45.0);
    glVertex3f(43.0, 5.0, -45.0);
    glVertex3f(53.0, -10.0, -45.0);         //KIRI - PILAR 3
    glVertex3f(53.0, 5.0, -45.0);
    glVertex3f(50.0, 5.0, -45.0);
    glVertex3f(50.0, -10.0, -45.0);
    glVertex3f(53.0, -10.0, -48.0);         //KIRI - PILAR 3
    glVertex3f(53.0, 5.0, -48.0);
    glVertex3f(50.0, 5.0, -48.0);
    glVertex3f(50.0, -10.0, -48.0);
    glVertex3f(50.0, 5.0, -48.0);           //KIRI - PILAR 3
    glVertex3f(50.0, -10.0, -48.0);
    glVertex3f(50.0, -10.0, -45.0);
    glVertex3f(50.0, 5.0, -45.0);
    glVertex3f(53.0, 5.0, -48.0);           //KIRI - PILAR 3
    glVertex3f(53.0, -10.0, -48.0);
    glVertex3f(53.0, -10.0, -45.0);
    glVertex3f(53.0, 5.0, -45.0);
    glVertex3f(63.0, -10.0, -45.0);         //KIRI - PILAR 4
    glVertex3f(63.0, 5.0, -45.0);
    glVertex3f(60.0, 5.0, -45.0);
    glVertex3f(60.0, -10.0, -45.0);
    glVertex3f(63.0, -10.0, -48.0);         //KIRI - PILAR 4
    glVertex3f(63.0, 5.0, -48.0);
    glVertex3f(60.0, 5.0, -48.0);
    glVertex3f(60.0, -10.0, -48.0);
    glVertex3f(60.0, 5.0, -48.0);           //KIRI - PILAR 4
    glVertex3f(60.0, -10.0, -48.0);
    glVertex3f(60.0, -10.0, -45.0);
    glVertex3f(60.0, 5.0, -45.0);
    glVertex3f(63.0, 5.0, -48.0);           //KIRI - PILAR 4
    glVertex3f(63.0, -10.0, -48.0);
    glVertex3f(63.0, -10.0, -45.0);
    glVertex3f(63.0, 5.0, -45.0);
    glVertex3f(73.0, -10.0, -45.0);         //KIRI - PILAR 5
    glVertex3f(73.0, 5.0, -45.0);
    glVertex3f(70.0, 5.0, -45.0);
    glVertex3f(70.0, -10.0, -45.0);
    glVertex3f(73.0, -10.0, -48.0);         //KIRI - PILAR 5
    glVertex3f(73.0, 5.0, -48.0);
    glVertex3f(70.0, 5.0, -48.0);
    glVertex3f(70.0, -10.0, -48.0);
    glVertex3f(70.0, 5.0, -48.0);           //KIRI - PILAR 5
    glVertex3f(70.0, -10.0, -48.0);
    glVertex3f(70.0, -10.0, -45.0);
    glVertex3f(70.0, 5.0, -45.0);
    glVertex3f(73.0, 5.0, -48.0);           //KIRI - PILAR 5
    glVertex3f(73.0, -10.0, -48.0);
    glVertex3f(73.0, -10.0, -45.0);
    glVertex3f(73.0, 5.0, -45.0);
    glVertex3f(83.0, -10.0, -45.0);         //KIRI - PILAR 6
    glVertex3f(83.0, 5.0, -45.0);
    glVertex3f(80.0, 5.0, -45.0);
    glVertex3f(80.0, -10.0, -45.0);
    glVertex3f(83.0, -10.0, -48.0);         //KIRI - PILAR 6
    glVertex3f(83.0, 5.0, -48.0);
    glVertex3f(80.0, 5.0, -48.0);
    glVertex3f(80.0, -10.0, -48.0);
    glVertex3f(80.0, 5.0, -48.0);           //KIRI - PILAR 6
    glVertex3f(80.0, -10.0, -48.0);
    glVertex3f(80.0, -10.0, -45.0);
    glVertex3f(80.0, 5.0, -45.0);
    glVertex3f(83.0, 5.0, -48.0);           //KIRI - PILAR 6
    glVertex3f(83.0, -10.0, -48.0);
    glVertex3f(83.0, -10.0, -45.0);
    glVertex3f(83.0, 5.0, -45.0);
    glVertex3f(93.0, -10.0, -45.0);         //KIRI - PILAR 7
    glVertex3f(93.0, 5.0, -45.0);
    glVertex3f(90.0, 5.0, -45.0);
    glVertex3f(90.0, -10.0, -45.0);
    glVertex3f(93.0, -10.0, -48.0);         //KIRI - PILAR 7
    glVertex3f(93.0, 5.0, -48.0);
    glVertex3f(90.0, 5.0, -48.0);
    glVertex3f(90.0, -10.0, -48.0);
    glVertex3f(90.0, 5.0, -48.0);           //KIRI - PILAR 7
    glVertex3f(90.0, -10.0, -48.0);
    glVertex3f(90.0, -10.0, -45.0);
    glVertex3f(90.0, 5.0, -45.0);
    glVertex3f(93.0, 5.0, -48.0);           //KIRI - PILAR 7
    glVertex3f(93.0, -10.0, -48.0);
    glVertex3f(93.0, -10.0, -45.0);
    glVertex3f(93.0, 5.0, -45.0);

    glVertex3f(100.0, -10.0, -89.0);       //KANAN - LANTAI 1
    glVertex3f(100.0, -5.0, -89.0);
    glVertex3f(36.0, -5.0, -89.0);
    glVertex3f(36.0, -10.0, -89.0);//
    glVertex3f(38.0, -10.0, -89.0);        //BERDIRI - LANTAI 1-2 DARI KIRI 1
    glVertex3f(38.0, 20.0, -89.0);
    glVertex3f(36.0, 20.0, -89.0);
    glVertex3f(36.0, -10.0, -89.0);//
    glVertex3f(45.0, -10.0, -89.0);        //BERDIRI 2
    glVertex3f(45.0, 20.0, -89.0);
    glVertex3f(43.0, 20.0, -89.0);
    glVertex3f(43.0, -10.0, -89.0);//
    glVertex3f(52.0, -10.0, -89.0);        //BERDIRI 3
    glVertex3f(52.0, 20.0, -89.0);
    glVertex3f(50.0, 20.0, -89.0);
    glVertex3f(50.0, -10.0, -89.0);//
    glVertex3f(59.0, -10.0, -89.0);        //BERDIRI 4
    glVertex3f(59.0, 20.0, -89.0);
    glVertex3f(57.0, 20.0, -89.0);
    glVertex3f(57.0, -10.0, -89.0);//
    glVertex3f(66.0, -10.0, -89.0);        //BERDIRI 5
    glVertex3f(66.0, 20.0, -89.0);
    glVertex3f(64.0, 20.0, -89.0);
    glVertex3f(64.0, -10.0, -89.0);//
    glVertex3f(73.0, -10.0, -89.0);        //BERDIRI 6
    glVertex3f(73.0, 20.0, -89.0);
    glVertex3f(71.0, 20.0, -89.0);
    glVertex3f(71.0, -10.0, -89.0);//
    glVertex3f(80.0, -10.0, -89.0);        //BERDIRI 7
    glVertex3f(80.0, 20.0, -89.0);
    glVertex3f(78.0, 20.0, -89.0);
    glVertex3f(78.0, -10.0, -89.0);//
    glVertex3f(87.0, -10.0, -89.0);        //BERDIRI 8
    glVertex3f(87.0, 20.0, -89.0);
    glVertex3f(85.0, 20.0, -89.0);
    glVertex3f(85.0, -10.0, -89.0);//
    glVertex3f(94.0, -10.0, -89.0);        //BERDIRI 9
    glVertex3f(94.0, 20.0, -89.0);
    glVertex3f(92.0, 20.0, -89.0);
    glVertex3f(92.0, -10.0, -89.0);//
    glVertex3f(100.0, -10.0, -89.0);        //BERDIRI 9
    glVertex3f(100.0, 20.0, -89.0);
    glVertex3f(99.0, 20.0, -89.0);
    glVertex3f(99.0, -10.0, -89.0);//
    glVertex3f(100.0, 0.0, -89.0);         //KANAN - LANTAI 1-2
    glVertex3f(100.0, 10.0, -89.0);
    glVertex3f(36.0, 10.0, -89.0);
    glVertex3f(36.0, 0.0, -89.0);//
    glVertex3f(31.0, 20.0, -95.0);        //BERDIRI - LANTAI 2-4 DARI KIRI 1
    glVertex3f(31.0, 35.0, -95.0);
    glVertex3f(30.0, 35.0, -95.0);
    glVertex3f(30.0, 20.0, -95.0);//
    glVertex3f(38.0, 20.0, -95.0);        //BERDIRI 2
    glVertex3f(38.0, 35.0, -95.0);
    glVertex3f(36.0, 35.0, -95.0);
    glVertex3f(36.0, 20.0, -95.0);//
    glVertex3f(45.0, 20.0, -95.0);        //BERDIRI 3
    glVertex3f(45.0, 50.0, -95.0);
    glVertex3f(43.0, 50.0, -95.0);
    glVertex3f(43.0, 20.0, -95.0);//
    glVertex3f(52.0, 20.0, -95.0);        //BERDIRI 4
    glVertex3f(52.0, 50.0, -95.0);
    glVertex3f(50.0, 50.0, -95.0);
    glVertex3f(50.0, 20.0, -95.0);//
    glVertex3f(59.0, 20.0, -95.0);        //BERDIRI 5
    glVertex3f(59.0, 50.0, -95.0);
    glVertex3f(57.0, 50.0, -95.0);
    glVertex3f(57.0, 20.0, -95.0);//
    glVertex3f(66.0, 20.0, -95.0);        //BERDIRI 6
    glVertex3f(66.0, 50.0, -95.0);
    glVertex3f(64.0, 50.0, -95.0);
    glVertex3f(64.0, 20.0, -95.0);//
    glVertex3f(73.0, 20.0, -95.0);        //BERDIRI 7
    glVertex3f(73.0, 50.0, -95.0);
    glVertex3f(71.0, 50.0, -95.0);
    glVertex3f(71.0, 20.0, -95.0);//
    glVertex3f(80.0, 20.0, -95.0);        //BERDIRI 8
    glVertex3f(80.0, 50.0, -95.0);
    glVertex3f(78.0, 50.0, -95.0);
    glVertex3f(78.0, 20.0, -95.0);//
    glVertex3f(87.0, 20.0, -95.0);        //BERDIRI 9
    glVertex3f(87.0, 50.0, -95.0);
    glVertex3f(85.0, 50.0, -95.0);
    glVertex3f(85.0, 20.0, -95.0);//
    glVertex3f(94.0, 20.0, -95.0);        //BERDIRI 10
    glVertex3f(94.0, 50.0, -95.0);
    glVertex3f(92.0, 50.0, -95.0);
    glVertex3f(92.0, 20.0, -95.0);//
    glVertex3f(100.0, 20.0, -95.0);        //BERDIRI 11
    glVertex3f(100.0, 50.0, -95.0);
    glVertex3f(99.0, 50.0, -95.0);
    glVertex3f(99.0, 20.0, -95.0);//
    glVertex3f(100.0, 15.0, -89.0);         //KANAN - LANTAI 2
    glVertex3f(100.0, 20.0, -89.0);
    glVertex3f(36.0, 20.0, -89.0);
    glVertex3f(36.0, 15.0, -89.0);//
    glVertex3f(100.0, 5.0, -95.0);         //KANAN - LANTAI 2
    glVertex3f(100.0, 10.0, -95.0);
    glVertex3f(38.0, 10.0, -95.0);
    glVertex3f(38.0, 5.0, -95.0);//
    glVertex3f(100.0, 15.0, -95.0);        //KANAN - LANTAI 3
    glVertex3f(100.0, 25.0, -95.0);
    glVertex3f(30.0, 25.0, -95.0);
    glVertex3f(30.0, 15.0, -95.0);//
    glVertex3f(100.0, 30.0, -95.0);        //KANAN - LANTAI 4
    glVertex3f(100.0, 40.0, -95.0);
    glVertex3f(43.0, 40.0, -95.0);
    glVertex3f(43.0, 30.0, -95.0);
    glVertex3f(100.0, 45.0, -95.0);        //KANAN - LANTAI 4
    glVertex3f(100.0, 50.0, -95.0);
    glVertex3f(43.0, 50.0, -95.0);
    glVertex3f(43.0, 45.0, -95.0);
    glVertex3f(43.0, 30.0, -95.0);         //KANAN - LANTAI 4 PENDEK DI KIRI
    glVertex3f(43.0, 38.0, -95.0);
    glVertex3f(30.0, 38.0, -95.0);
    glVertex3f(30.0, 30.0, -95.0);
    glVertex3f(43.0, 35.0, -82.0);         //KANAN - LANTAI 4
    glVertex3f(43.0, 50.0, -82.0);
    glVertex3f(30.0, 50.0, -82.0);
    glVertex3f(30.0, 35.0, -82.0);

    glVertex3f(33.0, -10.0, -95.0);         //KANAN - PILAR 1
    glVertex3f(33.0, 5.0, -95.0);
    glVertex3f(30.0, 5.0, -95.0);
    glVertex3f(30.0, -10.0, -95.0);
    glVertex3f(33.0, -10.0, -92.0);         //KANAN - PILAR 1
    glVertex3f(33.0, 5.0, -92.0);
    glVertex3f(30.0, 5.0, -92.0);
    glVertex3f(30.0, -10.0, -92.0);
    glVertex3f(43.0, -10.0, -95.0);         //KANAN - PILAR 2
    glVertex3f(43.0, 5.0, -95.0);
    glVertex3f(40.0, 5.0, -95.0);
    glVertex3f(40.0, -10.0, -95.0);
    glVertex3f(43.0, -10.0, -92.0);         //KANAN - PILAR 2
    glVertex3f(43.0, 5.0, -92.0);
    glVertex3f(40.0, 5.0, -92.0);
    glVertex3f(40.0, -10.0, -92.0);
    glVertex3f(40.0, 5.0, -95.0);           //KANAN - PILAR 2
    glVertex3f(40.0, -10.0, -95.0);
    glVertex3f(40.0, -10.0, -92.0);
    glVertex3f(40.0, 5.0, -92.0);
    glVertex3f(43.0, 5.0, -95.0);           //KANAN - PILAR 2
    glVertex3f(43.0, -10.0, -95.0);
    glVertex3f(43.0, -10.0, -92.0);
    glVertex3f(43.0, 5.0, -92.0);
    glVertex3f(53.0, -10.0, -95.0);         //KANAN - PILAR 3
    glVertex3f(53.0, 5.0, -95.0);
    glVertex3f(50.0, 5.0, -95.0);
    glVertex3f(50.0, -10.0, -95.0);
    glVertex3f(53.0, -10.0, -92.0);         //KANAN - PILAR 3
    glVertex3f(53.0, 5.0, -92.0);
    glVertex3f(50.0, 5.0, -92.0);
    glVertex3f(50.0, -10.0, -92.0);
    glVertex3f(50.0, 5.0, -95.0);           //KANAN - PILAR 3
    glVertex3f(50.0, -10.0, -95.0);
    glVertex3f(50.0, -10.0, -92.0);
    glVertex3f(50.0, 5.0, -92.0);
    glVertex3f(53.0, 5.0, -95.0);           //KANAN - PILAR 3
    glVertex3f(53.0, -10.0, -95.0);
    glVertex3f(53.0, -10.0, -92.0);
    glVertex3f(53.0, 5.0, -92.0);
    glVertex3f(63.0, -10.0, -95.0);         //KANAN - PILAR 4
    glVertex3f(63.0, 5.0, -95.0);
    glVertex3f(60.0, 5.0, -95.0);
    glVertex3f(60.0, -10.0, -95.0);
    glVertex3f(63.0, -10.0, -92.0);         //KANAN - PILAR 4
    glVertex3f(63.0, 5.0, -92.0);
    glVertex3f(60.0, 5.0, -92.0);
    glVertex3f(60.0, -10.0, -92.0);
    glVertex3f(60.0, 5.0, -95.0);           //KANAN - PILAR 4
    glVertex3f(60.0, -10.0, -95.0);
    glVertex3f(60.0, -10.0, -92.0);
    glVertex3f(60.0, 5.0, -92.0);
    glVertex3f(63.0, 5.0, -95.0);           //KANAN - PILAR 4
    glVertex3f(63.0, -10.0, -95.0);
    glVertex3f(63.0, -10.0, -92.0);
    glVertex3f(63.0, 5.0, -92.0);
    glVertex3f(73.0, -10.0, -95.0);         //KANAN - PILAR 5
    glVertex3f(73.0, 5.0, -95.0);
    glVertex3f(70.0, 5.0, -95.0);
    glVertex3f(70.0, -10.0, -95.0);
    glVertex3f(73.0, -10.0, -92.0);         //KANAN - PILAR 5
    glVertex3f(73.0, 5.0, -92.0);
    glVertex3f(70.0, 5.0, -92.0);
    glVertex3f(70.0, -10.0, -92.0);
    glVertex3f(70.0, 5.0, -95.0);           //KANAN - PILAR 5
    glVertex3f(70.0, -10.0, -95.0);
    glVertex3f(70.0, -10.0, -92.0);
    glVertex3f(70.0, 5.0, -92.0);
    glVertex3f(73.0, 5.0, -95.0);           //KANAN - PILAR 5
    glVertex3f(73.0, -10.0, -95.0);
    glVertex3f(73.0, -10.0, -92.0);
    glVertex3f(73.0, 5.0, -92.0);
    glVertex3f(83.0, -10.0, -95.0);         //KANAN - PILAR 6
    glVertex3f(83.0, 5.0, -95.0);
    glVertex3f(80.0, 5.0, -95.0);
    glVertex3f(80.0, -10.0, -95.0);
    glVertex3f(83.0, -10.0, -92.0);         //KANAN - PILAR 6
    glVertex3f(83.0, 5.0, -92.0);
    glVertex3f(80.0, 5.0, -92.0);
    glVertex3f(80.0, -10.0, -92.0);
    glVertex3f(80.0, 5.0, -95.0);           //KANAN - PILAR 6
    glVertex3f(80.0, -10.0, -95.0);
    glVertex3f(80.0, -10.0, -92.0);
    glVertex3f(80.0, 5.0, -92.0);
    glVertex3f(83.0, 5.0, -95.0);           //KANAN - PILAR 6
    glVertex3f(83.0, -10.0, -95.0);
    glVertex3f(83.0, -10.0, -92.0);
    glVertex3f(83.0, 5.0, -92.0);
    glVertex3f(93.0, -10.0, -95.0);         //KANAN - PILAR 7
    glVertex3f(93.0, 5.0, -95.0);
    glVertex3f(90.0, 5.0, -95.0);
    glVertex3f(90.0, -10.0, -95.0);
    glVertex3f(93.0, -10.0, -92.0);         //KANAN - PILAR 7
    glVertex3f(93.0, 5.0, -92.0);
    glVertex3f(90.0, 5.0, -92.0);
    glVertex3f(90.0, -10.0, -92.0);
    glVertex3f(90.0, 5.0, -95.0);           //KANAN - PILAR 7
    glVertex3f(90.0, -10.0, -95.0);
    glVertex3f(90.0, -10.0, -92.0);
    glVertex3f(90.0, 5.0, -92.0);
    glVertex3f(93.0, 5.0, -95.0);           //KANAN - PILAR 7
    glVertex3f(93.0, -10.0, -95.0);
    glVertex3f(93.0, -10.0, -92.0);
    glVertex3f(93.0, 5.0, -92.0);

    glVertex3f(36.0, -5.0, -67.0);         //DEPAN - LANTAI 1
    glVertex3f(36.0, -10.0, -67.0);
    glVertex3f(36.0, -10.0, -51.0);
    glVertex3f(36.0, -5.0, -51.0);
    glVertex3f(36.0, -5.0, -89.0);         //DEPAN - LANTAI 1
    glVertex3f(36.0, -10.0, -89.0);
    glVertex3f(36.0, -10.0, -73.0);
    glVertex3f(36.0, -5.0, -73.0);
    glVertex3f(36.0, 20.0, -53.0);         //BERDIRI - LANTAI 1-2 DARI KIRI 1
    glVertex3f(36.0, -10.0, -53.0);
    glVertex3f(36.0, -10.0, -51.0);
    glVertex3f(36.0, 20.0, -51.0);
    glVertex3f(36.0, 20.0, -60.0);         //BERDIRI 2
    glVertex3f(36.0, -10.0, -60.0);
    glVertex3f(36.0, -10.0, -58.0);
    glVertex3f(36.0, 20.0, -58.0);
    glVertex3f(36.0, 20.0, -67.0);         //BERDIRI 3
    glVertex3f(36.0, -10.0, -67.0);
    glVertex3f(36.0, -10.0, -65.0);
    glVertex3f(36.0, 20.0, -65.0);
    glVertex3f(36.0, 20.0, -75.0);         //BERDIRI 4
    glVertex3f(36.0, -10.0, -75.0);
    glVertex3f(36.0, -10.0, -73.0);
    glVertex3f(36.0, 20.0, -73.0);
    glVertex3f(36.0, 20.0, -82.0);         //BERDIRI 5
    glVertex3f(36.0, -10.0, -82.0);
    glVertex3f(36.0, -10.0, -80.0);
    glVertex3f(36.0, 20.0, -80.0);
    glVertex3f(36.0, 20.0, -89.0);         //BERDIRI 6
    glVertex3f(36.0, -10.0, -89.0);
    glVertex3f(36.0, -10.0, -87.0);
    glVertex3f(36.0, 20.0, -87.0);
    glVertex3f(36.0, 10.0, -89.0);         //DEPAN - LANTAI 2
    glVertex3f(36.0, 0.0, -89.0);
    glVertex3f(36.0, 0.0, -51.0);
    glVertex3f(36.0, 10.0, -51.0);
    glVertex3f(30.0, 35.0, -46.0);         //BERDIRI - LANTAI 2-4 DARI KIRI 1
    glVertex3f(30.0, 20.0, -46.0);
    glVertex3f(30.0, 20.0, -45.0);
    glVertex3f(30.0, 35.0, -45.0);
    glVertex3f(30.0, 35.0, -53.0);         //BERDIRI 2
    glVertex3f(30.0, 20.0, -53.0);
    glVertex3f(30.0, 20.0, -51.0);
    glVertex3f(30.0, 35.0, -51.0);
    glVertex3f(30.0, 50.0, -60.0);         //BERDIRI 3
    glVertex3f(30.0, 20.0, -60.0);
    glVertex3f(30.0, 20.0, -58.0);
    glVertex3f(30.0, 50.0, -58.0);
    glVertex3f(30.0, 50.0, -67.0);         //BERDIRI 4
    glVertex3f(30.0, 20.0, -67.0);
    glVertex3f(30.0, 20.0, -65.0);
    glVertex3f(30.0, 50.0, -65.0);
    glVertex3f(30.0, 50.0, -75.0);         //BERDIRI 5
    glVertex3f(30.0, 20.0, -75.0);
    glVertex3f(30.0, 20.0, -73.0);
    glVertex3f(30.0, 50.0, -73.0);
    glVertex3f(30.0, 50.0, -82.0);         //BERDIRI 6
    glVertex3f(30.0, 20.0, -82.0);
    glVertex3f(30.0, 20.0, -80.0);
    glVertex3f(30.0, 50.0, -80.0);
    glVertex3f(30.0, 35.0, -89.0);         //BERDIRI 7
    glVertex3f(30.0, 20.0, -89.0);
    glVertex3f(30.0, 20.0, -87.0);
    glVertex3f(30.0, 35.0, -87.0);
    glVertex3f(30.0, 35.0, -95.0);         //BERDIRI 8
    glVertex3f(30.0, 20.0, -95.0);
    glVertex3f(30.0, 20.0, -94.0);
    glVertex3f(30.0, 35.0, -94.0);
    glVertex3f(36.0, 20.0, -89.0);         //DEPAN - LANTAI 2
    glVertex3f(36.0, 15.0, -89.0);
    glVertex3f(36.0, 15.0, -51.0);
    glVertex3f(36.0, 20.0, -51.0);
    glVertex3f(30.0, 10.0, -95.0);         //DEPAN - LANTAI 2
    glVertex3f(30.0, 5.0, -95.0);
    glVertex3f(30.0, 5.0, -45.0);
    glVertex3f(30.0, 10.0, -45.0);
    glVertex3f(30.0, 25.0, -95.0);         //DEPAN - LANTAI 3
    glVertex3f(30.0, 15.0, -95.0);
    glVertex3f(30.0, 15.0, -45.0);
    glVertex3f(30.0, 25.0, -45.0);
    glVertex3f(30.0, 40.0, -80.0);         //DEPAN - LANTAI 4
    glVertex3f(30.0, 30.0, -80.0);
    glVertex3f(30.0, 30.0, -60.0);
    glVertex3f(30.0, 40.0, -60.0);
    glVertex3f(30.0, 50.0, -80.0);         //DEPAN - LANTAI 4
    glVertex3f(30.0, 45.0, -80.0);
    glVertex3f(30.0, 45.0, -60.0);
    glVertex3f(30.0, 50.0, -60.0);
    glVertex3f(30.0, 37.0, -60.0);         //DEPAN - LANTAI 4
    glVertex3f(30.0, 30.0, -60.0);
    glVertex3f(30.0, 30.0, -45.0);
    glVertex3f(30.0, 37.0, -45.0);
    glVertex3f(30.0, 37.0, -95.0);         //DEPAN - LANTAI 4
    glVertex3f(30.0, 30.0, -95.0);
    glVertex3f(30.0, 30.0, -80.0);
    glVertex3f(30.0, 37.0, -80.0);
    glVertex3f(43.0, 50.0, -95.0);         //DEPAN - LANTAI 4 KANAN
    glVertex3f(43.0, 35.0, -95.0);
    glVertex3f(43.0, 35.0, -82.0);
    glVertex3f(43.0, 50.0, -82.0);
    glVertex3f(43.0, 50.0, -58.0);         //DEPAN - LANTAI 4 KIRI
    glVertex3f(43.0, 35.0, -58.0);
    glVertex3f(43.0, 35.0, -45.0);
    glVertex3f(43.0, 50.0, -45.0);

    glVertex3f(30.0, 5.0, -48.0);         //DEPAN - PILAR 1
    glVertex3f(30.0, -10.0, -48.0);
    glVertex3f(30.0, -10.0, -45.0);
    glVertex3f(30.0, 5.0, -45.0);
    glVertex3f(33.0, 5.0, -48.0);         //DEPAN - PILAR 1
    glVertex3f(33.0, -10.0, -48.0);
    glVertex3f(33.0, -10.0, -45.0);
    glVertex3f(33.0, 5.0, -45.0);
    glVertex3f(30.0, 5.0, -58.0);         //DEPAN - PILAR 2
    glVertex3f(30.0, -10.0, -58.0);
    glVertex3f(30.0, -10.0, -55.0);
    glVertex3f(30.0, 5.0, -55.0);
    glVertex3f(33.0, 5.0, -58.0);         //DEPAN - PILAR 2
    glVertex3f(33.0, -10.0, -58.0);
    glVertex3f(33.0, -10.0, -55.0);
    glVertex3f(33.0, 5.0, -55.0);
    glVertex3f(33.0, -10.0, -55.0);       //DEPAN - PILAR 2
    glVertex3f(33.0, 5.0, -55.0);
    glVertex3f(30.0, 5.0, -55.0);
    glVertex3f(30.0, -10.0, -55.0);
    glVertex3f(33.0, -10.0, -58.0);       //DEPAN - PILAR 2
    glVertex3f(33.0, 5.0, -58.0);
    glVertex3f(30.0, 5.0, -58.0);
    glVertex3f(30.0, -10.0, -58.0);
    glVertex3f(30.0, 5.0, -67.0);         //DEPAN - PILAR 3
    glVertex3f(30.0, -10.0, -67.0);
    glVertex3f(30.0, -10.0, -64.0);
    glVertex3f(30.0, 5.0, -64.0);
    glVertex3f(33.0, 5.0, -67.0);         //DEPAN - PILAR 3
    glVertex3f(33.0, -10.0, -67.0);
    glVertex3f(33.0, -10.0, -64.0);
    glVertex3f(33.0, 5.0, -64.0);
    glVertex3f(33.0, -10.0, -64.0);       //DEPAN - PILAR 3
    glVertex3f(33.0, 5.0, -64.0);
    glVertex3f(30.0, 5.0, -64.0);
    glVertex3f(30.0, -10.0, -64.0);
    glVertex3f(33.0, -10.0, -67.0);       //DEPAN - PILAR 3
    glVertex3f(33.0, 5.0, -67.0);
    glVertex3f(30.0, 5.0, -67.0);
    glVertex3f(30.0, -10.0, -67.0);
    glVertex3f(30.0, 5.0, -76.0);         //DEPAN - PILAR 4
    glVertex3f(30.0, -10.0, -76.0);
    glVertex3f(30.0, -10.0, -73.0);
    glVertex3f(30.0, 5.0, -73.0);
    glVertex3f(33.0, 5.0, -76.0);         //DEPAN - PILAR 4
    glVertex3f(33.0, -10.0, -76.0);
    glVertex3f(33.0, -10.0, -73.0);
    glVertex3f(33.0, 5.0, -73.0);
    glVertex3f(33.0, -10.0, -73.0);       //DEPAN - PILAR 4
    glVertex3f(33.0, 5.0, -73.0);
    glVertex3f(30.0, 5.0, -73.0);
    glVertex3f(30.0, -10.0, -73.0);
    glVertex3f(33.0, -10.0, -76.0);       //DEPAN - PILAR 4
    glVertex3f(33.0, 5.0, -76.0);
    glVertex3f(30.0, 5.0, -76.0);
    glVertex3f(30.0, -10.0, -76.0);
    glVertex3f(30.0, 5.0, -85.0);         //DEPAN - PILAR 5
    glVertex3f(30.0, -10.0, -85.0);
    glVertex3f(30.0, -10.0, -82.0);
    glVertex3f(30.0, 5.0, -82.0);
    glVertex3f(33.0, 5.0, -85.0);         //DEPAN - PILAR 5
    glVertex3f(33.0, -10.0, -85.0);
    glVertex3f(33.0, -10.0, -82.0);
    glVertex3f(33.0, 5.0, -82.0);
    glVertex3f(33.0, -10.0, -82.0);       //DEPAN - PILAR 5
    glVertex3f(33.0, 5.0, -82.0);
    glVertex3f(30.0, 5.0, -82.0);
    glVertex3f(30.0, -10.0, -82.0);
    glVertex3f(33.0, -10.0, -85.0);       //DEPAN - PILAR 5
    glVertex3f(33.0, 5.0, -85.0);
    glVertex3f(30.0, 5.0, -85.0);
    glVertex3f(30.0, -10.0, -85.0);
    glVertex3f(30.0, 5.0, -95.0);         //DEPAN - PILAR 6
    glVertex3f(30.0, -10.0, -95.0);
    glVertex3f(30.0, -10.0, -92.0);
    glVertex3f(30.0, 5.0, -92.0);
    glVertex3f(33.0, 5.0, -95.0);         //DEPAN - PILAR 6
    glVertex3f(33.0, -10.0, -95.0);
    glVertex3f(33.0, -10.0, -92.0);
    glVertex3f(33.0, 5.0, -92.0);
    glVertex3f(33.0, -10.0, -92.0);       //DEPAN - PILAR 6
    glVertex3f(33.0, 5.0, -92.0);
    glVertex3f(30.0, 5.0, -92.0);
    glVertex3f(30.0, -10.0, -92.0);
    glVertex3f(33.0, -10.0, -95.0);       //DEPAN - PILAR 6
    glVertex3f(33.0, 5.0, -95.0);
    glVertex3f(30.0, 5.0, -95.0);
    glVertex3f(30.0, -10.0, -95.0);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0.5, 0.5, 0.5);                 //LANTAI - 1
    glVertex3f(30, -9.9, -95.0);
    glVertex3f(100, -9.9, -95.0);
    glVertex3f(100, -9.9, -45.0);
    glVertex3f(30, -9.9, -45.0);
    glVertex3f(30, 5.0, -95.0);            //LANTAI - 2
    glVertex3f(100, 5.0, -95.0);
    glVertex3f(100, 5.0, -45.0);
    glVertex3f(30, 5.0, -45.0);
    glVertex3f(30, 20.0, -95.0);            //LANTAI - 3
    glVertex3f(100, 20.0, -95.0);
    glVertex3f(100, 20.0, -45.0);
    glVertex3f(30, 20.0, -45.0);
    glVertex3f(43, 35.0, -95.0);            //LANTAI - 4
    glVertex3f(100, 35.0, -95.0);
    glVertex3f(100, 35.0, -45.0);
    glVertex3f(43, 35.0, -45.0);
    glVertex3f(30, 50.0, -105.0);            //LANTAI - 4 1
    glVertex3f(100, 50.0, -105.0);
    glVertex3f(100, 50.0, -35.0);
    glVertex3f(30, 50.0, -35.0);
    glVertex3f(20, 50.0, -85.0);            //LANTAI - 4 2
    glVertex3f(43, 50.0, -85.0);
    glVertex3f(43, 50.0, -55.0);
    glVertex3f(20, 50.0, -55.0);
    glVertex3f(30, 35.0, -82.0);            //LANTAI - 4
    glVertex3f(43, 35.0, -82.0);
    glVertex3f(43, 35.0, -58.0);
    glVertex3f(30, 35.0, -58.0);
    glVertex3f(30, 50.0, -82.0);            //LANTAI - 4
    glVertex3f(43, 50.0, -82.0);
    glVertex3f(43, 50.0, -58.0);
    glVertex3f(30, 50.0, -58.0);
    glEnd();

    glBegin(GL_QUADS);                      //PINTU
    glColor3f(0.66, 0.40, 0.0);
    glVertex3f(36.0, 0.0, -73.0);
    glVertex3f(36.0, -10.0, -73.0);
    glVertex3f(36.0, -10.0, -67.0);
    glVertex3f(36.0, 0.0, -67.0);
    glEnd();

    glBegin(GL_QUADS);                      //ATAP
    glColor3f(0.2, 0.2, 0.2);               //DEPAN - BAWAH PANJANG
    glVertex3f(30.0, 40.0, -82.0);
    glVertex3f(20.0, 30.0, -82.0);
    glVertex3f(20.0, 30.0, -58.0);
    glVertex3f(30.0, 40.0, -58.0);
    glEnd();
    glBegin(GL_POLYGON);                    //DEPAN - BAWAH KIRI
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(43, 50.0, -58.0);
    glVertex3f(30, 40.0, -58.0);
    glVertex3f(20, 30.0, -58.0);
    glVertex3f(20, 30.0, -45.0);
    glVertex3f(30, 40.0, -45.0);
    glEnd();
    glBegin(GL_POLYGON);                    //DEPAN - BAWAH UJUNG KIRI
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(30.0, 40.0, -45.0);
    glVertex3f(20.0, 30.0, -45.0);
    glVertex3f(20.0, 30.0, -35.0);
    glVertex3f(30.0, 30.0, -35.0);
    glEnd();
    glBegin(GL_POLYGON);                    //DEPAN - BAWAH KANAN
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(43, 50.0, -82.0);
    glVertex3f(30, 40.0, -82.0);
    glVertex3f(20, 30.0, -82.0);
    glVertex3f(20, 30.0, -95.0);
    glVertex3f(30, 40.0, -95.0);
    glEnd();
    glBegin(GL_POLYGON);                    //DEPAN - BAWAH UJUNG KANAN
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(30.0, 40.0, -95.0);
    glVertex3f(20.0, 30.0, -95.0);
    glVertex3f(20.0, 30.0, -105.0);
    glVertex3f(30.0, 30.0, -105.0);
    glEnd();
    glBegin(GL_POLYGON);                    //KIRI - KANAN
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(43.0, 50.0, -58.0);
    glVertex3f(30.0, 40.0, -45.0);
    glVertex3f(30.0, 30.0, -35.0);
    glVertex3f(43.0, 30.0, -35.0);
    glVertex3f(43.0, 40.0, -45.0);
    glEnd();
    glBegin(GL_QUADS);                      //KIRI - SISI SIRIP PANJANG TENGAH
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(43, 40.0, -45.0);
    glVertex3f(100, 40.0, -45.0);
    glVertex3f(100, 30.0, -35.0);
    glVertex3f(43, 30.0, -35.0);
    glEnd();
    glBegin(GL_QUADS);                      //KIRI - SISI SIRIP PANJANG ATAS
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(45, 70.0, -60.0);
    glVertex3f(100, 70.0, -60.0);
    glVertex3f(100, 50.0, -35.0);
    glVertex3f(30, 50.0, -35.0);
    glEnd();
    glBegin(GL_QUADS);                      //KIRI - SISI SIRIP PENDEK BAWAH
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(30, 60.0, -63.0);
    glVertex3f(40, 60.0, -63.0);
    glVertex3f(30, 50.0, -55.0);
    glVertex3f(20, 50.0, -55.0);
    glEnd();
    glBegin(GL_POLYGON);                    //KIRI - SIRIP BESAR ATAS
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(55.0, 90.0, -65.0);
    glVertex3f(45.0, 110.0, -70.0);
    glVertex3f(100.0, 110.0, -70.0);
    glVertex3f(100.0, 70.0, -60.0);
    glVertex3f(45.0, 70.0, -60.0);
    glEnd();
    glBegin(GL_POLYGON);                    //KIRI - SIRIP KECIL BAWAH
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(40.0, 75.0, -66.0);
    glVertex3f(30.0, 90.0, -70.0);
    glVertex3f(55.0, 90.0, -70.0);
    glVertex3f(40.0, 60.0, -62.0);
    glVertex3f(30.0, 60.0, -62.0);
    glEnd();
    glBegin(GL_POLYGON);                    //KANAN - KIRI
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(43.0, 50.0, -82.0);
    glVertex3f(43.0, 40.0, -95.0);
    glVertex3f(43.0, 30.0, -105.0);
    glVertex3f(30.0, 30.0, -105.0);
    glVertex3f(30.0, 40.0, -95.0);
    glEnd();
    glBegin(GL_POLYGON);                    //KANAN - SISI SIRIP PANJANG TENGAH
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(43, 30.0, -105.0);
    glVertex3f(100, 30.0, -105.0);
    glVertex3f(100, 40.0, -95.0);
    glVertex3f(43, 40.0, -95.0);
    glEnd();
    glBegin(GL_POLYGON);                    //KANAN - SISI SIRIP PANJANG ATAS
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(30, 50.0, -105.0);
    glVertex3f(100, 50.0, -105.0);
    glVertex3f(100, 70.0, -80.0);
    glVertex3f(45, 70.0, -80.0);
    glEnd();
    glBegin(GL_POLYGON);                    //KANAN - SISI SIRIP PENDEK BAWAH
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(20, 50.0, -85.0);
    glVertex3f(30, 50.0, -85.0);
    glVertex3f(40, 60.0, -77.0);
    glVertex3f(30, 60.0, -77.0);
    glEnd();
    glBegin(GL_POLYGON);                    //KANAN - SIRIP BESAR ATAS
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(55.0, 90.0, -75.0);
    glVertex3f(45.0, 110.0, -70.0);
    glVertex3f(100.0, 110.0, -70.0);
    glVertex3f(100.0, 70.0, -80.0);
    glVertex3f(45.0, 70.0, -80.0);
    glEnd();
    glBegin(GL_POLYGON);                    //KANAN - SIRIP KECIL BAWAH
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(40.0, 75.0, -74.0);
    glVertex3f(30.0, 90.0, -70.0);
    glVertex3f(55.0, 90.0, -70.0);
    glVertex3f(40.0, 60.0, -78.0);
    glVertex3f(30.0, 60.0, -78.0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(45.0, 70.0, -80.0);         //DEPAN - PENUTUP SIRIP BESAR BAWAH
    glVertex3f(55.0, 90.0, -75.0);
    glVertex3f(55.0, 90.0, -65.0);
    glVertex3f(45.0, 70.0, -60.0);
    glVertex3f(30.0, 50.0, -35.0);
    glVertex3f(30.0, 50.0, -105.0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(55.0, 90.0, -65.0);         //DEPAN - PENUTUP SIRIP BESAR ATAS
    glVertex3f(55.0, 90.0, -75.0);
    glVertex3f(45.0, 110.0, -70.0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(40.0, 75.0, -74.0);         //DEPAN - PENUTUP SIRIP KECIL BAWAH
    glVertex3f(40.0, 75.0, -66.0);
    glVertex3f(30.0, 60.0, -62.0);
    glVertex3f(20.0, 50.0, -55.0);
    glVertex3f(20.0, 50.0, -85.0);
    glVertex3f(30.0, 60.0, -78.0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(40.0, 75.0, -74.0);         //DEPAN - PENUTUP SIRIP KECIL ATAS
    glVertex3f(30.0, 90.0, -70.0);
    glVertex3f(40.0, 75.0, -66.0);
    glEnd();
    //SAMPAI SINI


    //GEDUNG 2
    glBegin(GL_LINE_LOOP);              //JENDELA KIRI DARI KANAN - LANTAI 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-43.0, -5.0, -181.0);
    glVertex3f(-43.0, 0.0, -181.0);
    glVertex3f(-38.0, 0.0, -181.0);
    glVertex3f(-38.0, -5.0, -181.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-50.0, -5.0, -181.0);
    glVertex3f(-50.0, 0.0, -181.0);
    glVertex3f(-45.0, 0.0, -181.0);
    glVertex3f(-45.0, -5.0, -181.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-57.0, -5.0, -181.0);
    glVertex3f(-57.0, 0.0, -181.0);
    glVertex3f(-52.0, 0.0, -181.0);
    glVertex3f(-52.0, -5.0, -181.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-64.0, -5.0, -181.0);
    glVertex3f(-64.0, 0.0, -181.0);
    glVertex3f(-59.0, 0.0, -181.0);
    glVertex3f(-59.0, -5.0, -181.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-71.0, -5.0, -181.0);
    glVertex3f(-71.0, 0.0, -181.0);
    glVertex3f(-66.0, 0.0, -181.0);
    glVertex3f(-66.0, -5.0, -181.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-78.0, -5.0, -181.0);
    glVertex3f(-78.0, 0.0, -181.0);
    glVertex3f(-73.0, 0.0, -181.0);
    glVertex3f(-73.0, -5.0, -181.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-85.0, -5.0, -181.0);
    glVertex3f(-85.0, 0.0, -181.0);
    glVertex3f(-80.0, 0.0, -181.0);
    glVertex3f(-80.0, -5.0, -181.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-92.0, -5.0, -181.0);
    glVertex3f(-92.0, 0.0, -181.0);
    glVertex3f(-87.0, 0.0, -181.0);
    glVertex3f(-87.0, -5.0, -181.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-99.0, -5.0, -181.0);
    glVertex3f(-99.0, 0.0, -181.0);
    glVertex3f(-94.0, 0.0, -181.0);
    glVertex3f(-94.0, -5.0, -181.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-43.0, 10.0, -181.0);
    glVertex3f(-43.0, 15.0, -181.0);
    glVertex3f(-38.0, 15.0, -181.0);
    glVertex3f(-38.0, 10.0, -181.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-50.0, 10.0, -181.0);
    glVertex3f(-50.0, 15.0, -181.0);
    glVertex3f(-45.0, 15.0, -181.0);
    glVertex3f(-45.0, 10.0, -181.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-57.0, 10.0, -181.0);
    glVertex3f(-57.0, 15.0, -181.0);
    glVertex3f(-52.0, 15.0, -181.0);
    glVertex3f(-52.0, 10.0, -181.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-64.0, 10.0, -181.0);
    glVertex3f(-64.0, 15.0, -181.0);
    glVertex3f(-59.0, 15.0, -181.0);
    glVertex3f(-59.0, 10.0, -181.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-71.0, 10.0, -181.0);
    glVertex3f(-71.0, 15.0, -181.0);
    glVertex3f(-66.0, 15.0, -181.0);
    glVertex3f(-66.0, 10.0, -181.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-78.0, 10.0, -181.0);
    glVertex3f(-78.0, 15.0, -181.0);
    glVertex3f(-73.0, 15.0, -181.0);
    glVertex3f(-73.0, 10.0, -181.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-85.0, 10.0, -181.0);
    glVertex3f(-85.0, 15.0, -181.0);
    glVertex3f(-80.0, 15.0, -181.0);
    glVertex3f(-80.0, 10.0, -181.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-92.0, 10.0, -181.0);
    glVertex3f(-92.0, 15.0, -181.0);
    glVertex3f(-87.0, 15.0, -181.0);
    glVertex3f(-87.0, 10.0, -181.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-99.0, 10.0, -181.0);
    glVertex3f(-99.0, 15.0, -181.0);
    glVertex3f(-94.0, 15.0, -181.0);
    glVertex3f(-94.0, 10.0, -181.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-36.0, 25.0, -175.0);
    glVertex3f(-36.0, 30.0, -175.0);
    glVertex3f(-31.0, 30.0, -175.0);
    glVertex3f(-31.0, 25.0, -175.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-43.0, 25.0, -175.0);
    glVertex3f(-43.0, 30.0, -175.0);
    glVertex3f(-38.0, 30.0, -175.0);
    glVertex3f(-38.0, 25.0, -175.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-50.0, 25.0, -175.0);
    glVertex3f(-50.0, 30.0, -175.0);
    glVertex3f(-45.0, 30.0, -175.0);
    glVertex3f(-45.0, 25.0, -175.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-57.0, 25.0, -175.0);
    glVertex3f(-57.0, 30.0, -175.0);
    glVertex3f(-52.0, 30.0, -175.0);
    glVertex3f(-52.0, 25.0, -175.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-64.0, 25.0, -175.0);
    glVertex3f(-64.0, 30.0, -175.0);
    glVertex3f(-59.0, 30.0, -175.0);
    glVertex3f(-59.0, 25.0, -175.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-71.0, 25.0, -175.0);
    glVertex3f(-71.0, 30.0, -175.0);
    glVertex3f(-66.0, 30.0, -175.0);
    glVertex3f(-66.0, 25.0, -175.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-78.0, 25.0, -175.0);
    glVertex3f(-78.0, 30.0, -175.0);
    glVertex3f(-73.0, 30.0, -175.0);
    glVertex3f(-73.0, 25.0, -175.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-85.0, 25.0, -175.0);
    glVertex3f(-85.0, 30.0, -175.0);
    glVertex3f(-80.0, 30.0, -175.0);
    glVertex3f(-80.0, 25.0, -175.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-92.0, 25.0, -175.0);
    glVertex3f(-92.0, 30.0, -175.0);
    glVertex3f(-87.0, 30.0, -175.0);
    glVertex3f(-87.0, 25.0, -175.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-99.0, 25.0, -175.0);
    glVertex3f(-99.0, 30.0, -175.0);
    glVertex3f(-94.0, 30.0, -175.0);
    glVertex3f(-94.0, 25.0, -175.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-50.0, 40.0, -175.0);
    glVertex3f(-50.0, 45.0, -175.0);
    glVertex3f(-45.0, 45.0, -175.0);
    glVertex3f(-45.0, 40.0, -175.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-57.0, 40.0, -175.0);
    glVertex3f(-57.0, 45.0, -175.0);
    glVertex3f(-52.0, 45.0, -175.0);
    glVertex3f(-52.0, 40.0, -175.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-64.0, 40.0, -175.0);
    glVertex3f(-64.0, 45.0, -175.0);
    glVertex3f(-59.0, 45.0, -175.0);
    glVertex3f(-59.0, 40.0, -175.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-71.0, 40.0, -175.0);
    glVertex3f(-71.0, 45.0, -175.0);
    glVertex3f(-66.0, 45.0, -175.0);
    glVertex3f(-66.0, 40.0, -175.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-78.0, 40.0, -175.0);
    glVertex3f(-78.0, 45.0, -175.0);
    glVertex3f(-73.0, 45.0, -175.0);
    glVertex3f(-73.0, 40.0, -175.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-85.0, 40.0, -175.0);
    glVertex3f(-85.0, 45.0, -175.0);
    glVertex3f(-80.0, 45.0, -175.0);
    glVertex3f(-80.0, 40.0, -175.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-92.0, 40.0, -175.0);
    glVertex3f(-92.0, 45.0, -175.0);
    glVertex3f(-87.0, 45.0, -175.0);
    glVertex3f(-87.0, 40.0, -175.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-99.0, 40.0, -175.0);
    glVertex3f(-99.0, 45.0, -175.0);
    glVertex3f(-94.0, 45.0, -175.0);
    glVertex3f(-94.0, 40.0, -175.0);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 0.0, 0.0);         //JENDELA KANAN DARI KIRI - LANTAI 1
    glVertex3f(-43.0, -5.0, -219.0);
    glVertex3f(-43.0, 0.0, -219.0);
    glVertex3f(-38.0, 0.0, -219.0);
    glVertex3f(-38.0, -5.0, -219.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-50.0, -5.0, -219.0);
    glVertex3f(-50.0, 0.0, -219.0);
    glVertex3f(-45.0, 0.0, -219.0);
    glVertex3f(-45.0, -5.0, -219.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-57.0, -5.0, -219.0);
    glVertex3f(-57.0, 0.0, -219.0);
    glVertex3f(-52.0, 0.0, -219.0);
    glVertex3f(-52.0, -5.0, -219.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-64.0, -5.0, -219.0);
    glVertex3f(-64.0, 0.0, -219.0);
    glVertex3f(-59.0, 0.0, -219.0);
    glVertex3f(-59.0, -5.0, -219.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-71.0, -5.0, -219.0);
    glVertex3f(-71.0, 0.0, -219.0);
    glVertex3f(-66.0, 0.0, -219.0);
    glVertex3f(-66.0, -5.0, -219.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-78.0, -5.0, -219.0);
    glVertex3f(-78.0, 0.0, -219.0);
    glVertex3f(-73.0, 0.0, -219.0);
    glVertex3f(-73.0, -5.0, -219.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-85.0, -5.0, -219.0);
    glVertex3f(-85.0, 0.0, -219.0);
    glVertex3f(-80.0, 0.0, -219.0);
    glVertex3f(-80.0, -5.0, -219.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-92.0, -5.0, -219.0);
    glVertex3f(-92.0, 0.0, -219.0);
    glVertex3f(-87.0, 0.0, -219.0);
    glVertex3f(-87.0, -5.0, -219.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-99.0, -5.0, -219.0);
    glVertex3f(-99.0, 0.0, -219.0);
    glVertex3f(-94.0, 0.0, -219.0);
    glVertex3f(-94.0, -5.0, -219.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-43.0, 10.0, -219.0);
    glVertex3f(-43.0, 15.0, -219.0);
    glVertex3f(-38.0, 15.0, -219.0);
    glVertex3f(-38.0, 10.0, -219.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-50.0, 10.0, -219.0);
    glVertex3f(-50.0, 15.0, -219.0);
    glVertex3f(-45.0, 15.0, -219.0);
    glVertex3f(-45.0, 10.0, -219.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-57.0, 10.0, -219.0);
    glVertex3f(-57.0, 15.0, -219.0);
    glVertex3f(-52.0, 15.0, -219.0);
    glVertex3f(-52.0, 10.0, -219.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-64.0, 10.0, -219.0);
    glVertex3f(-64.0, 15.0, -219.0);
    glVertex3f(-59.0, 15.0, -219.0);
    glVertex3f(-59.0, 10.0, -219.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-71.0, 10.0, -219.0);
    glVertex3f(-71.0, 15.0, -219.0);
    glVertex3f(-66.0, 15.0, -219.0);
    glVertex3f(-66.0, 10.0, -219.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-78.0, 10.0, -219.0);
    glVertex3f(-78.0, 15.0, -219.0);
    glVertex3f(-73.0, 15.0, -219.0);
    glVertex3f(-73.0, 10.0, -219.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-85.0, 10.0, -219.0);
    glVertex3f(-85.0, 15.0, -219.0);
    glVertex3f(-80.0, 15.0, -219.0);
    glVertex3f(-80.0, 10.0, -219.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-92.0, 10.0, -219.0);
    glVertex3f(-92.0, 15.0, -219.0);
    glVertex3f(-87.0, 15.0, -219.0);
    glVertex3f(-87.0, 10.0, -219.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-99.0, 10.0, -219.0);
    glVertex3f(-99.0, 15.0, -219.0);
    glVertex3f(-94.0, 15.0, -219.0);
    glVertex3f(-94.0, 10.0, -219.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-36.0, 25.0, -225.0);
    glVertex3f(-36.0, 30.0, -225.0);
    glVertex3f(-31.0, 30.0, -225.0);
    glVertex3f(-31.0, 25.0, -225.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-43.0, 25.0, -225.0);
    glVertex3f(-43.0, 30.0, -225.0);
    glVertex3f(-38.0, 30.0, -225.0);
    glVertex3f(-38.0, 25.0, -225.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-50.0, 25.0, -225.0);
    glVertex3f(-50.0, 30.0, -225.0);
    glVertex3f(-45.0, 30.0, -225.0);
    glVertex3f(-45.0, 25.0, -225.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-57.0, 25.0, -225.0);
    glVertex3f(-57.0, 30.0, -225.0);
    glVertex3f(-52.0, 30.0, -225.0);
    glVertex3f(-52.0, 25.0, -225.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-64.0, 25.0, -225.0);
    glVertex3f(-64.0, 30.0, -225.0);
    glVertex3f(-59.0, 30.0, -225.0);
    glVertex3f(-59.0, 25.0, -225.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-71.0, 25.0, -225.0);
    glVertex3f(-71.0, 30.0, -225.0);
    glVertex3f(-66.0, 30.0, -225.0);
    glVertex3f(-66.0, 25.0, -225.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-78.0, 25.0, -225.0);
    glVertex3f(-78.0, 30.0, -225.0);
    glVertex3f(-73.0, 30.0, -225.0);
    glVertex3f(-73.0, 25.0, -225.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-85.0, 25.0, -225.0);
    glVertex3f(-85.0, 30.0, -225.0);
    glVertex3f(-80.0, 30.0, -225.0);
    glVertex3f(-80.0, 25.0, -225.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-92.0, 25.0, -225.0);
    glVertex3f(-92.0, 30.0, -225.0);
    glVertex3f(-87.0, 30.0, -225.0);
    glVertex3f(-87.0, 25.0, -225.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-99.0, 25.0, -225.0);
    glVertex3f(-99.0, 30.0, -225.0);
    glVertex3f(-94.0, 30.0, -225.0);
    glVertex3f(-94.0, 25.0, -225.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-50.0, 40.0, -225.0);
    glVertex3f(-50.0, 45.0, -225.0);
    glVertex3f(-45.0, 45.0, -225.0);
    glVertex3f(-45.0, 40.0, -225.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-57.0, 40.0, -225.0);
    glVertex3f(-57.0, 45.0, -225.0);
    glVertex3f(-52.0, 45.0, -225.0);
    glVertex3f(-52.0, 40.0, -225.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-64.0, 40.0, -225.0);
    glVertex3f(-64.0, 45.0, -225.0);
    glVertex3f(-59.0, 45.0, -225.0);
    glVertex3f(-59.0, 40.0, -225.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-71.0, 40.0, -225.0);
    glVertex3f(-71.0, 45.0, -225.0);
    glVertex3f(-66.0, 45.0, -225.0);
    glVertex3f(-66.0, 40.0, -225.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-78.0, 40.0, -225.0);
    glVertex3f(-78.0, 45.0, -225.0);
    glVertex3f(-73.0, 45.0, -225.0);
    glVertex3f(-73.0, 40.0, -225.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-85.0, 40.0, -225.0);
    glVertex3f(-85.0, 45.0, -225.0);
    glVertex3f(-80.0, 45.0, -225.0);
    glVertex3f(-80.0, 40.0, -225.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-92.0, 40.0, -225.0);
    glVertex3f(-92.0, 45.0, -225.0);
    glVertex3f(-87.0, 45.0, -225.0);
    glVertex3f(-87.0, 40.0, -225.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-99.0, 40.0, -225.0);
    glVertex3f(-99.0, 45.0, -225.0);
    glVertex3f(-94.0, 45.0, -225.0);
    glVertex3f(-94.0, 40.0, -225.0);
    glEnd();

    glBegin(GL_LINE_LOOP);              //JENDELA DEPAN DARI KIRI- LANTAI 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-36.0, 0.0, -188.0);
    glVertex3f(-36.0, -5.0, -188.0);
    glVertex3f(-36.0, -5.0, -183.0);
    glVertex3f(-36.0, 0.0, -183.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.D - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-36.0, 0.0, -195.0);
    glVertex3f(-36.0, -5.0, -195.0);
    glVertex3f(-36.0, -5.0, -190.0);
    glVertex3f(-36.0, 0.0, -190.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-36.0, 0.0, -210.0);
    glVertex3f(-36.0, -5.0, -210.0);
    glVertex3f(-36.0, -5.0, -205.0);
    glVertex3f(-36.0, 0.0, -205.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-36.0, 0.0, -217.0);
    glVertex3f(-36.0, -5.0, -217.0);
    glVertex3f(-36.0, -5.0, -212.0);
    glVertex3f(-36.0, 0.0, -212.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-36.0, 15.0, -188.0);
    glVertex3f(-36.0, 10.0, -188.0);
    glVertex3f(-36.0, 10.0, -183.0);
    glVertex3f(-36.0, 15.0, -183.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-36.0, 15.0, -195.0);
    glVertex3f(-36.0, 10.0, -195.0);
    glVertex3f(-36.0, 10.0, -190.0);
    glVertex3f(-36.0, 15.0, -190.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-36.0, 15.0, -203.0);
    glVertex3f(-36.0, 10.0, -203.0);
    glVertex3f(-36.0, 10.0, -197.0);
    glVertex3f(-36.0, 15.0, -197.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-36.0, 15.0, -210.0);
    glVertex3f(-36.0, 10.0, -210.0);
    glVertex3f(-36.0, 10.0, -205.0);
    glVertex3f(-36.0, 15.0, -205.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-36.0, 15.0, -217.0);
    glVertex3f(-36.0, 10.0, -217.0);
    glVertex3f(-36.0, 10.0, -212.0);
    glVertex3f(-36.0, 15.0, -212.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-30.0, 25.0, -181.0);
    glVertex3f(-30.0, 30.0, -181.0);
    glVertex3f(-30.0, 30.0, -176.0);
    glVertex3f(-30.0, 25.0, -176.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-30.0, 25.0, -188.0);
    glVertex3f(-30.0, 30.0, -188.0);
    glVertex3f(-30.0, 30.0, -183.0);
    glVertex3f(-30.0, 25.0, -183.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-30.0, 25.0, -195.0);
    glVertex3f(-30.0, 30.0, -195.0);
    glVertex3f(-30.0, 30.0, -190.0);
    glVertex3f(-30.0, 25.0, -190.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-30.0, 25.0, -203.0);
    glVertex3f(-30.0, 30.0, -203.0);
    glVertex3f(-30.0, 30.0, -197.0);
    glVertex3f(-30.0, 25.0, -197.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-30.0, 25.0, -210.0);
    glVertex3f(-30.0, 30.0, -210.0);
    glVertex3f(-30.0, 30.0, -205.0);
    glVertex3f(-30.0, 25.0, -205.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-30.0, 25.0, -217.0);
    glVertex3f(-30.0, 30.0, -217.0);
    glVertex3f(-30.0, 30.0, -212.0);
    glVertex3f(-30.0, 25.0, -212.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-30.0, 25.0, -224.0);
    glVertex3f(-30.0, 30.0, -224.0);
    glVertex3f(-30.0, 30.0, -219.0);
    glVertex3f(-30.0, 25.0, -219.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-30.0, 45.0, -195.0);
    glVertex3f(-30.0, 40.0, -195.0);
    glVertex3f(-30.0, 40.0, -190.0);
    glVertex3f(-30.0, 45.0, -190.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-30.0, 45.0, -203.0);
    glVertex3f(-30.0, 40.0, -203.0);
    glVertex3f(-30.0, 40.0, -197.0);
    glVertex3f(-30.0, 45.0, -197.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(-30.0, 45.0, -210.0);
    glVertex3f(-30.0, 40.0, -210.0);
    glVertex3f(-30.0, 40.0, -205.0);
    glVertex3f(-30.0, 45.0, -205.0);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);                 //KIRI - LANTAI 1
    glVertex3f(-100.0, -10.0, -181.0);
    glVertex3f(-100.0, -5.0, -181.0);
    glVertex3f(-36.0, -5.0, -181.0);
    glVertex3f(-36.0, -10.0, -181.0);//
    glVertex3f(-38.0, -10.0, -181.0);        //BERDIRI - LANTAI 1-2 DARI KANAN 1
    glVertex3f(-38.0, 20.0, -181.0);
    glVertex3f(-36.0, 20.0, -181.0);
    glVertex3f(-36.0, -10.0, -181.0);//
    glVertex3f(-45.0, -10.0, -181.0);        //BERDIRI 2
    glVertex3f(-45.0, 20.0, -181.0);
    glVertex3f(-43.0, 20.0, -181.0);
    glVertex3f(-43.0, -10.0, -181.0);//
    glVertex3f(-52.0, -10.0, -181.0);        //BERDIRI 3
    glVertex3f(-52.0, 20.0, -181.0);
    glVertex3f(-50.0, 20.0, -181.0);
    glVertex3f(-50.0, -10.0, -181.0);//
    glVertex3f(-59.0, -10.0, -181.0);        //BERDIRI 4
    glVertex3f(-59.0, 20.0, -181.0);
    glVertex3f(-57.0, 20.0, -181.0);
    glVertex3f(-57.0, -10.0, -181.0);//
    glVertex3f(-66.0, -10.0, -181.0);        //BERDIRI 5
    glVertex3f(-66.0, 20.0, -181.0);
    glVertex3f(-64.0, 20.0, -181.0);
    glVertex3f(-64.0, -10.0, -181.0);//
    glVertex3f(-73.0, -10.0, -181.0);        //BERDIRI 6
    glVertex3f(-73.0, 20.0, -181.0);
    glVertex3f(-71.0, 20.0, -181.0);
    glVertex3f(-71.0, -10.0, -181.0);//
    glVertex3f(-80.0, -10.0, -181.0);        //BERDIRI 7
    glVertex3f(-80.0, 20.0, -181.0);
    glVertex3f(-78.0, 20.0, -181.0);
    glVertex3f(-78.0, -10.0, -181.0);//
    glVertex3f(-87.0, -10.0, -181.0);        //BERDIRI 8
    glVertex3f(-87.0, 20.0, -181.0);
    glVertex3f(-85.0, 20.0, -181.0);
    glVertex3f(-85.0, -10.0, -181.0);//
    glVertex3f(-94.0, -10.0, -181.0);        //BERDIRI 9
    glVertex3f(-94.0, 20.0, -181.0);
    glVertex3f(-92.0, 20.0, -181.0);
    glVertex3f(-92.0, -10.0, -181.0);//
    glVertex3f(-100.0, -10.0, -181.0);       //BERDIRI 9
    glVertex3f(-100.0, 20.0, -181.0);
    glVertex3f(-99.0, 20.0, -181.0);
    glVertex3f(-99.0, -10.0, -181.0);//
    glVertex3f(-100.0, 0.0, -181.0);         //KIRI - LANTAI 1-2
    glVertex3f(-100.0, 10.0, -181.0);
    glVertex3f(-36.0, 10.0, -181.0);
    glVertex3f(-36.0, 0.0, -181.0);//
    glVertex3f(-31.0, 20.0, -175.0);         //BERDIRI - LANTAI 2-4 DARI KANAN 1
    glVertex3f(-31.0, 35.0, -175.0);
    glVertex3f(-30.0, 35.0, -175.0);
    glVertex3f(-30.0, 20.0, -175.0);//
    glVertex3f(-38.0, 20.0, -175.0);         //BERDIRI 2
    glVertex3f(-38.0, 35.0, -175.0);
    glVertex3f(-36.0, 35.0, -175.0);
    glVertex3f(-36.0, 20.0, -175.0);//
    glVertex3f(-45.0, 20.0, -175.0);         //BERDIRI 3
    glVertex3f(-45.0, 50.0, -175.0);
    glVertex3f(-43.0, 50.0, -175.0);
    glVertex3f(-43.0, 20.0, -175.0);//
    glVertex3f(-52.0, 20.0, -175.0);         //BERDIRI 4
    glVertex3f(-52.0, 50.0, -175.0);
    glVertex3f(-50.0, 50.0, -175.0);
    glVertex3f(-50.0, 20.0, -175.0);//
    glVertex3f(-59.0, 20.0, -175.0);         //BERDIRI 5
    glVertex3f(-59.0, 50.0, -175.0);
    glVertex3f(-57.0, 50.0, -175.0);
    glVertex3f(-57.0, 20.0, -175.0);//
    glVertex3f(-66.0, 20.0, -175.0);         //BERDIRI 6
    glVertex3f(-66.0, 50.0, -175.0);
    glVertex3f(-64.0, 50.0, -175.0);
    glVertex3f(-64.0, 20.0, -175.0);//
    glVertex3f(-73.0, 20.0, -175.0);         //BERDIRI 7
    glVertex3f(-73.0, 50.0, -175.0);
    glVertex3f(-71.0, 50.0, -175.0);
    glVertex3f(-71.0, 20.0, -175.0);//
    glVertex3f(-80.0, 20.0, -175.0);         //BERDIRI 8
    glVertex3f(-80.0, 50.0, -175.0);
    glVertex3f(-78.0, 50.0, -175.0);
    glVertex3f(-78.0, 20.0, -175.0);//
    glVertex3f(-87.0, 20.0, -175.0);         //BERDIRI 9
    glVertex3f(-87.0, 50.0, -175.0);
    glVertex3f(-85.0, 50.0, -175.0);
    glVertex3f(-85.0, 20.0, -175.0);//
    glVertex3f(-94.0, 20.0, -175.0);         //BERDIRI 10
    glVertex3f(-94.0, 50.0, -175.0);
    glVertex3f(-92.0, 50.0, -175.0);
    glVertex3f(-92.0, 20.0, -175.0);//
    glVertex3f(-100.0, 20.0, -175.0);        //BERDIRI 11
    glVertex3f(-100.0, 50.0, -175.0);
    glVertex3f(-99.0, 50.0, -175.0);
    glVertex3f(-99.0, 20.0, -175.0);//
    glVertex3f(-100.0, 15.0, -181.0);        //KIRI - LANTAI 2
    glVertex3f(-100.0, 20.0, -181.0);
    glVertex3f(-30.0, 20.0, -181.0);
    glVertex3f(-30.0, 15.0, -181.0);//
    glVertex3f(-100.0, 5.0, -175.0);         //KIRI - LANTAI 2
    glVertex3f(-100.0, 10.0, -175.0);
    glVertex3f(-38.0, 10.0, -175.0);
    glVertex3f(-38.0, 5.0, -175.0);//
    glVertex3f(-100.0, 15.0, -175.0);        //KIRI - LANTAI 3
    glVertex3f(-100.0, 25.0, -175.0);
    glVertex3f(-30.0, 25.0, -175.0);
    glVertex3f(-30.0, 15.0, -175.0);//
    glVertex3f(-100.0, 30.0, -175.0);        //KIRI - LANTAI 3-4
    glVertex3f(-100.0, 40.0, -175.0);
    glVertex3f(-43.0, 40.0, -175.0);
    glVertex3f(-43.0, 30.0, -175.0);
    glVertex3f(-100.0, 45.0, -175.0);        //KIRI - LANTAI 4
    glVertex3f(-100.0, 50.0, -175.0);
    glVertex3f(-43.0, 50.0, -175.0);
    glVertex3f(-43.0, 45.0, -175.0);
    glVertex3f(-43.0, 30.0, -175.0);         //KIRI - LANTAI 4
    glVertex3f(-43.0, 38.0, -175.0);
    glVertex3f(-30.0, 38.0, -175.0);
    glVertex3f(-30.0, 30.0, -175.0);
    glVertex3f(-43.0, 40.0, -188.0);          //KIRI - LANTAI 4
    glVertex3f(-43.0, 50.0, -188.0);
    glVertex3f(-30.0, 50.0, -188.0);
    glVertex3f(-30.0, 40.0, -188.0);

    glVertex3f(-33.0, -10.0, -175.0);         //KIRI - PILAR 1
    glVertex3f(-33.0, 5.0, -175.0);
    glVertex3f(-30.0, 5.0, -175.0);
    glVertex3f(-30.0, -10.0, -175.0);
    glVertex3f(-33.0, -10.0, -178.0);         //KIRI - PILAR 1
    glVertex3f(-33.0, 5.0, -178.0);
    glVertex3f(-30.0, 5.0, -178.0);
    glVertex3f(-30.0, -10.0, -178.0);
    glVertex3f(-43.0, -10.0, -175.0);         //KIRI - PILAR 2
    glVertex3f(-43.0, 5.0, -175.0);
    glVertex3f(-40.0, 5.0, -175.0);
    glVertex3f(-40.0, -10.0, -175.0);
    glVertex3f(-43.0, -10.0, -178.0);         //KIRI - PILAR 2
    glVertex3f(-43.0, 5.0, -178.0);
    glVertex3f(-40.0, 5.0, -178.0);
    glVertex3f(-40.0, -10.0, -178.0);
    glVertex3f(-40.0, 5.0, -178.0);           //KIRI - PILAR 2
    glVertex3f(-40.0, -10.0, -178.0);
    glVertex3f(-40.0, -10.0, -175.0);
    glVertex3f(-40.0, 5.0, -175.0);
    glVertex3f(-43.0, 5.0, -178.0);           //KIRI - PILAR 2
    glVertex3f(-43.0, -10.0, -178.0);
    glVertex3f(-43.0, -10.0, -175.0);
    glVertex3f(-43.0, 5.0, -175.0);
    glVertex3f(-53.0, -10.0, -175.0);         //KIRI - PILAR 3
    glVertex3f(-53.0, 5.0, -175.0);
    glVertex3f(-50.0, 5.0, -175.0);
    glVertex3f(-50.0, -10.0, -175.0);
    glVertex3f(-53.0, -10.0, -178.0);         //KIRI - PILAR 3
    glVertex3f(-53.0, 5.0, -178.0);
    glVertex3f(-50.0, 5.0, -178.0);
    glVertex3f(-50.0, -10.0, -178.0);
    glVertex3f(-50.0, 5.0, -178.0);           //KIRI - PILAR 3
    glVertex3f(-50.0, -10.0, -178.0);
    glVertex3f(-50.0, -10.0, -175.0);
    glVertex3f(-50.0, 5.0, -175.0);
    glVertex3f(-53.0, 5.0, -178.0);           //KIRI - PILAR 3
    glVertex3f(-53.0, -10.0, -178.0);
    glVertex3f(-53.0, -10.0, -175.0);
    glVertex3f(-53.0, 5.0, -175.0);
    glVertex3f(-63.0, -10.0, -175.0);         //KIRI - PILAR 4
    glVertex3f(-63.0, 5.0, -175.0);
    glVertex3f(-60.0, 5.0, -175.0);
    glVertex3f(-60.0, -10.0, -175.0);
    glVertex3f(-63.0, -10.0, -178.0);         //KIRI - PILAR 4
    glVertex3f(-63.0, 5.0, -178.0);
    glVertex3f(-60.0, 5.0, -178.0);
    glVertex3f(-60.0, -10.0, -178.0);
    glVertex3f(-60.0, 5.0, -178.0);           //KIRI - PILAR 4
    glVertex3f(-60.0, -10.0, -178.0);
    glVertex3f(-60.0, -10.0, -175.0);
    glVertex3f(-60.0, 5.0, -175.0);
    glVertex3f(-63.0, 5.0, -178.0);           //KIRI - PILAR 4
    glVertex3f(-63.0, -10.0, -178.0);
    glVertex3f(-63.0, -10.0, -175.0);
    glVertex3f(-63.0, 5.0, -175.0);
    glVertex3f(-73.0, -10.0, -175.0);         //KIRI - PILAR 5
    glVertex3f(-73.0, 5.0, -175.0);
    glVertex3f(-70.0, 5.0, -175.0);
    glVertex3f(-70.0, -10.0, -175.0);
    glVertex3f(-73.0, -10.0, -178.0);         //KIRI - PILAR 5
    glVertex3f(-73.0, 5.0, -178.0);
    glVertex3f(-70.0, 5.0, -178.0);
    glVertex3f(-70.0, -10.0, -178.0);
    glVertex3f(-70.0, 5.0, -178.0);           //KIRI - PILAR 5
    glVertex3f(-70.0, -10.0, -178.0);
    glVertex3f(-70.0, -10.0, -175.0);
    glVertex3f(-70.0, 5.0, -175.0);
    glVertex3f(-73.0, 5.0, -178.0);           //KIRI - PILAR 5
    glVertex3f(-73.0, -10.0, -178.0);
    glVertex3f(-73.0, -10.0, -175.0);
    glVertex3f(-73.0, 5.0, -175.0);
    glVertex3f(-83.0, -10.0, -175.0);         //KIRI - PILAR 6
    glVertex3f(-83.0, 5.0, -175.0);
    glVertex3f(-80.0, 5.0, -175.0);
    glVertex3f(-80.0, -10.0, -175.0);
    glVertex3f(-83.0, -10.0, -178.0);         //KIRI - PILAR 6
    glVertex3f(-83.0, 5.0, -178.0);
    glVertex3f(-80.0, 5.0, -178.0);
    glVertex3f(-80.0, -10.0, -178.0);
    glVertex3f(-80.0, 5.0, -178.0);           //KIRI - PILAR 6
    glVertex3f(-80.0, -10.0, -178.0);
    glVertex3f(-80.0, -10.0, -175.0);
    glVertex3f(-80.0, 5.0, -175.0);
    glVertex3f(-83.0, 5.0, -178.0);           //KIRI - PILAR 6
    glVertex3f(-83.0, -10.0, -178.0);
    glVertex3f(-83.0, -10.0, -175.0);
    glVertex3f(-83.0, 5.0, -175.0);
    glVertex3f(-93.0, -10.0, -175.0);         //KIRI - PILAR 7
    glVertex3f(-93.0, 5.0, -175.0);
    glVertex3f(-90.0, 5.0, -175.0);
    glVertex3f(-90.0, -10.0, -175.0);
    glVertex3f(-93.0, -10.0, -178.0);         //KIRI - PILAR 7
    glVertex3f(-93.0, 5.0, -178.0);
    glVertex3f(-90.0, 5.0, -178.0);
    glVertex3f(-90.0, -10.0, -178.0);
    glVertex3f(-90.0, 5.0, -178.0);           //KIRI - PILAR 7
    glVertex3f(-90.0, -10.0, -178.0);
    glVertex3f(-90.0, -10.0, -175.0);
    glVertex3f(-90.0, 5.0, -175.0);
    glVertex3f(-93.0, 5.0, -178.0);           //KIRI - PILAR 7
    glVertex3f(-93.0, -10.0, -178.0);
    glVertex3f(-93.0, -10.0, -175.0);
    glVertex3f(-93.0, 5.0, -175.0);

    glVertex3f(-100.0, -10.0, -219.0);       //KANAN - LANTAI 1
    glVertex3f(-100.0, -5.0, -219.0);
    glVertex3f(-36.0, -5.0, -219.0);
    glVertex3f(-36.0, -10.0, -219.0);//
    glVertex3f(-38.0, -10.0, -219.0);        //BERDIRI - LANTAI 1-2 DARI KIRI 1
    glVertex3f(-38.0, 20.0, -219.0);
    glVertex3f(-36.0, 20.0, -219.0);
    glVertex3f(-36.0, -10.0, -219.0);//
    glVertex3f(-45.0, -10.0, -219.0);        //BERDIRI 2
    glVertex3f(-45.0, 20.0, -219.0);
    glVertex3f(-43.0, 20.0, -219.0);
    glVertex3f(-43.0, -10.0, -219.0);//
    glVertex3f(-52.0, -10.0, -219.0);        //BERDIRI 3
    glVertex3f(-52.0, 20.0, -219.0);
    glVertex3f(-50.0, 20.0, -219.0);
    glVertex3f(-50.0, -10.0, -219.0);//
    glVertex3f(-59.0, -10.0, -219.0);        //BERDIRI 4
    glVertex3f(-59.0, 20.0, -219.0);
    glVertex3f(-57.0, 20.0, -219.0);
    glVertex3f(-57.0, -10.0, -219.0);//
    glVertex3f(-66.0, -10.0, -219.0);        //BERDIRI 5
    glVertex3f(-66.0, 20.0, -219.0);
    glVertex3f(-64.0, 20.0, -219.0);
    glVertex3f(-64.0, -10.0, -219.0);//
    glVertex3f(-73.0, -10.0, -219.0);        //BERDIRI 6
    glVertex3f(-73.0, 20.0, -219.0);
    glVertex3f(-71.0, 20.0, -219.0);
    glVertex3f(-71.0, -10.0, -219.0);//
    glVertex3f(-80.0, -10.0, -219.0);        //BERDIRI 7
    glVertex3f(-80.0, 20.0, -219.0);
    glVertex3f(-78.0, 20.0, -219.0);
    glVertex3f(-78.0, -10.0, -219.0);//
    glVertex3f(-87.0, -10.0, -219.0);        //BERDIRI 8
    glVertex3f(-87.0, 20.0, -219.0);
    glVertex3f(-85.0, 20.0, -219.0);
    glVertex3f(-85.0, -10.0, -219.0);//
    glVertex3f(-94.0, -10.0, -219.0);        //BERDIRI 9
    glVertex3f(-94.0, 20.0, -219.0);
    glVertex3f(-92.0, 20.0, -219.0);
    glVertex3f(-92.0, -10.0, -219.0);//
    glVertex3f(-100.0, -10.0, -219.0);        //BERDIRI 9
    glVertex3f(-100.0, 20.0, -219.0);
    glVertex3f(-99.0, 20.0, -219.0);
    glVertex3f(-99.0, -10.0, -219.0);//
    glVertex3f(-100.0, 0.0, -219.0);         //KANAN - LANTAI 1-2
    glVertex3f(-100.0, 10.0, -219.0);
    glVertex3f(-36.0, 10.0, -219.0);
    glVertex3f(-36.0, 0.0, -219.0);//
    glVertex3f(-31.0, 20.0, -225.0);        //BERDIRI - LANTAI 2-4 DARI KIRI 1
    glVertex3f(-31.0, 35.0, -225.0);
    glVertex3f(-30.0, 35.0, -225.0);
    glVertex3f(-30.0, 20.0, -225.0);//
    glVertex3f(-38.0, 20.0, -225.0);        //BERDIRI 2
    glVertex3f(-38.0, 35.0, -225.0);
    glVertex3f(-36.0, 35.0, -225.0);
    glVertex3f(-36.0, 20.0, -225.0);//
    glVertex3f(-45.0, 20.0, -225.0);        //BERDIRI 3
    glVertex3f(-45.0, 50.0, -225.0);
    glVertex3f(-43.0, 50.0, -225.0);
    glVertex3f(-43.0, 20.0, -225.0);//
    glVertex3f(-52.0, 20.0, -225.0);        //BERDIRI 4
    glVertex3f(-52.0, 50.0, -225.0);
    glVertex3f(-50.0, 50.0, -225.0);
    glVertex3f(-50.0, 20.0, -225.0);//
    glVertex3f(-59.0, 20.0, -225.0);        //BERDIRI 5
    glVertex3f(-59.0, 50.0, -225.0);
    glVertex3f(-57.0, 50.0, -225.0);
    glVertex3f(-57.0, 20.0, -225.0);//
    glVertex3f(-66.0, 20.0, -225.0);        //BERDIRI 6
    glVertex3f(-66.0, 50.0, -225.0);
    glVertex3f(-64.0, 50.0, -225.0);
    glVertex3f(-64.0, 20.0, -225.0);//
    glVertex3f(-73.0, 20.0, -225.0);        //BERDIRI 7
    glVertex3f(-73.0, 50.0, -225.0);
    glVertex3f(-71.0, 50.0, -225.0);
    glVertex3f(-71.0, 20.0, -225.0);//
    glVertex3f(-80.0, 20.0, -225.0);        //BERDIRI 8
    glVertex3f(-80.0, 50.0, -225.0);
    glVertex3f(-78.0, 50.0, -225.0);
    glVertex3f(-78.0, 20.0, -225.0);//
    glVertex3f(-87.0, 20.0, -225.0);        //BERDIRI 9
    glVertex3f(-87.0, 50.0, -225.0);
    glVertex3f(-85.0, 50.0, -225.0);
    glVertex3f(-85.0, 20.0, -225.0);//
    glVertex3f(-94.0, 20.0, -225.0);        //BERDIRI 10
    glVertex3f(-94.0, 50.0, -225.0);
    glVertex3f(-92.0, 50.0, -225.0);
    glVertex3f(-92.0, 20.0, -225.0);//
    glVertex3f(-100.0, 20.0, -225.0);        //BERDIRI 11
    glVertex3f(-100.0, 50.0, -225.0);
    glVertex3f(-99.0, 50.0, -225.0);
    glVertex3f(-99.0, 20.0, -225.0);//
    glVertex3f(-100.0, 15.0, -219.0);         //KANAN - LANTAI 2
    glVertex3f(-100.0, 20.0, -219.0);
    glVertex3f(-36.0, 20.0, -219.0);
    glVertex3f(-36.0, 15.0, -219.0);//
    glVertex3f(-100.0, 5.0, -225.0);         //KANAN - LANTAI 2
    glVertex3f(-100.0, 10.0, -225.0);
    glVertex3f(-30.0, 10.0, -225.0);
    glVertex3f(-30.0, 5.0, -225.0);//
    glVertex3f(-100.0, 15.0, -225.0);        //KANAN - LANTAI 3
    glVertex3f(-100.0, 25.0, -225.0);
    glVertex3f(-30.0, 25.0, -225.0);
    glVertex3f(-30.0, 15.0, -225.0);//
    glVertex3f(-100.0, 30.0, -225.0);        //KANAN - LANTAI 4
    glVertex3f(-100.0, 40.0, -225.0);
    glVertex3f(-43.0, 40.0, -225.0);
    glVertex3f(-43.0, 30.0, -225.0);
    glVertex3f(-100.0, 45.0, -225.0);        //KANAN - LANTAI 4
    glVertex3f(-100.0, 50.0, -225.0);
    glVertex3f(-43.0, 50.0, -225.0);
    glVertex3f(-43.0, 45.0, -225.0);
    glVertex3f(-43.0, 30.0, -225.0);         //KANAN - LANTAI 4 PENDEK DI KIRI
    glVertex3f(-43.0, 38.0, -225.0);
    glVertex3f(-30.0, 38.0, -225.0);
    glVertex3f(-30.0, 30.0, -225.0);
    glVertex3f(-43.0, 35.0, -212.0);         //KANAN - LANTAI 4
    glVertex3f(-43.0, 50.0, -212.0);
    glVertex3f(-30.0, 50.0, -212.0);
    glVertex3f(-30.0, 35.0, -212.0);

    glVertex3f(-33.0, -10.0, -225.0);         //KANAN - PILAR 1
    glVertex3f(-33.0, 5.0, -225.0);
    glVertex3f(-30.0, 5.0, -225.0);
    glVertex3f(-30.0, -10.0, -225.0);
    glVertex3f(-33.0, -10.0, -222.0);         //KANAN - PILAR 1
    glVertex3f(-33.0, 5.0, -222.0);
    glVertex3f(-30.0, 5.0, -222.0);
    glVertex3f(-30.0, -10.0, -222.0);
    glVertex3f(-43.0, -10.0, -225.0);         //KANAN - PILAR 2
    glVertex3f(-43.0, 5.0, -225.0);
    glVertex3f(-40.0, 5.0, -225.0);
    glVertex3f(-40.0, -10.0, -225.0);
    glVertex3f(-43.0, -10.0, -222.0);         //KANAN - PILAR 2
    glVertex3f(-43.0, 5.0, -222.0);
    glVertex3f(-40.0, 5.0, -222.0);
    glVertex3f(-40.0, -10.0, -222.0);
    glVertex3f(-40.0, 5.0, -225.0);           //KANAN - PILAR 2
    glVertex3f(-40.0, -10.0, -225.0);
    glVertex3f(-40.0, -10.0, -222.0);
    glVertex3f(-40.0, 5.0, -222.0);
    glVertex3f(-43.0, 5.0, -225.0);           //KANAN - PILAR 2
    glVertex3f(-43.0, -10.0, -225.0);
    glVertex3f(-43.0, -10.0, -222.0);
    glVertex3f(-43.0, 5.0, -222.0);
    glVertex3f(-53.0, -10.0, -225.0);         //KANAN - PILAR 3
    glVertex3f(-53.0, 5.0, -225.0);
    glVertex3f(-50.0, 5.0, -225.0);
    glVertex3f(-50.0, -10.0, -225.0);
    glVertex3f(-53.0, -10.0, -222.0);         //KANAN - PILAR 3
    glVertex3f(-53.0, 5.0, -222.0);
    glVertex3f(-50.0, 5.0, -222.0);
    glVertex3f(-50.0, -10.0, -222.0);
    glVertex3f(-50.0, 5.0, -225.0);           //KANAN - PILAR 3
    glVertex3f(-50.0, -10.0, -225.0);
    glVertex3f(-50.0, -10.0, -222.0);
    glVertex3f(-50.0, 5.0, -222.0);
    glVertex3f(-53.0, 5.0, -225.0);           //KANAN - PILAR 3
    glVertex3f(-53.0, -10.0, -225.0);
    glVertex3f(-53.0, -10.0, -222.0);
    glVertex3f(-53.0, 5.0, -222.0);
    glVertex3f(-63.0, -10.0, -225.0);         //KANAN - PILAR 4
    glVertex3f(-63.0, 5.0, -225.0);
    glVertex3f(-60.0, 5.0, -225.0);
    glVertex3f(-60.0, -10.0, -225.0);
    glVertex3f(-63.0, -10.0, -222.0);         //KANAN - PILAR 4
    glVertex3f(-63.0, 5.0, -222.0);
    glVertex3f(-60.0, 5.0, -222.0);
    glVertex3f(-60.0, -10.0, -222.0);
    glVertex3f(-60.0, 5.0, -225.0);           //KANAN - PILAR 4
    glVertex3f(-60.0, -10.0, -225.0);
    glVertex3f(-60.0, -10.0, -222.0);
    glVertex3f(-60.0, 5.0, -222.0);
    glVertex3f(-63.0, 5.0, -225.0);           //KANAN - PILAR 4
    glVertex3f(-63.0, -10.0, -225.0);
    glVertex3f(-63.0, -10.0, -222.0);
    glVertex3f(-63.0, 5.0, -222.0);
    glVertex3f(-73.0, -10.0, -225.0);         //KANAN - PILAR 5
    glVertex3f(-73.0, 5.0, -225.0);
    glVertex3f(-70.0, 5.0, -225.0);
    glVertex3f(-70.0, -10.0, -225.0);
    glVertex3f(-73.0, -10.0, -222.0);         //KANAN - PILAR 5
    glVertex3f(-73.0, 5.0, -222.0);
    glVertex3f(-70.0, 5.0, -222.0);
    glVertex3f(-70.0, -10.0, -222.0);
    glVertex3f(-70.0, 5.0, -225.0);           //KANAN - PILAR 5
    glVertex3f(-70.0, -10.0, -225.0);
    glVertex3f(-70.0, -10.0, -222.0);
    glVertex3f(-70.0, 5.0, -222.0);
    glVertex3f(-73.0, 5.0, -225.0);           //KANAN - PILAR 5
    glVertex3f(-73.0, -10.0, -225.0);
    glVertex3f(-73.0, -10.0, -222.0);
    glVertex3f(-73.0, 5.0, -222.0);
    glVertex3f(-83.0, -10.0, -225.0);         //KANAN - PILAR 6
    glVertex3f(-83.0, 5.0, -225.0);
    glVertex3f(-80.0, 5.0, -225.0);
    glVertex3f(-80.0, -10.0, -225.0);
    glVertex3f(-83.0, -10.0, -222.0);         //KANAN - PILAR 6
    glVertex3f(-83.0, 5.0, -222.0);
    glVertex3f(-80.0, 5.0, -222.0);
    glVertex3f(-80.0, -10.0, -222.0);
    glVertex3f(-80.0, 5.0, -225.0);           //KANAN - PILAR 6
    glVertex3f(-80.0, -10.0, -225.0);
    glVertex3f(-80.0, -10.0, -222.0);
    glVertex3f(-80.0, 5.0, -222.0);
    glVertex3f(-83.0, 5.0, -225.0);           //KANAN - PILAR 6
    glVertex3f(-83.0, -10.0, -225.0);
    glVertex3f(-83.0, -10.0, -222.0);
    glVertex3f(-83.0, 5.0, -222.0);
    glVertex3f(-93.0, -10.0, -225.0);         //KANAN - PILAR 7
    glVertex3f(-93.0, 5.0, -225.0);
    glVertex3f(-90.0, 5.0, -225.0);
    glVertex3f(-90.0, -10.0, -225.0);
    glVertex3f(-93.0, -10.0, -222.0);         //KANAN - PILAR 7
    glVertex3f(-93.0, 5.0, -222.0);
    glVertex3f(-90.0, 5.0, -222.0);
    glVertex3f(-90.0, -10.0, -222.0);
    glVertex3f(-90.0, 5.0, -225.0);           //KANAN - PILAR 7
    glVertex3f(-90.0, -10.0, -225.0);
    glVertex3f(-90.0, -10.0, -222.0);
    glVertex3f(-90.0, 5.0, -222.0);
    glVertex3f(-93.0, 5.0, -225.0);           //KANAN - PILAR 7
    glVertex3f(-93.0, -10.0, -225.0);
    glVertex3f(-93.0, -10.0, -222.0);
    glVertex3f(-93.0, 5.0, -222.0);

    glVertex3f(-36.0, -5.0, -197.0);         //DEPAN - LANTAI 1
    glVertex3f(-36.0, -10.0, -197.0);
    glVertex3f(-36.0, -10.0, -181.0);
    glVertex3f(-36.0, -5.0, -181.0);
    glVertex3f(-36.0, -5.0, -219.0);         //DEPAN - LANTAI 1
    glVertex3f(-36.0, -10.0, -219.0);
    glVertex3f(-36.0, -10.0, -203.0);
    glVertex3f(-36.0, -5.0, -203.0);
    glVertex3f(-36.0, 20.0, -183.0);         //BERDIRI - LANTAI 1-2 DARI KIRI 1
    glVertex3f(-36.0, -10.0, -183.0);
    glVertex3f(-36.0, -10.0, -181.0);
    glVertex3f(-36.0, 20.0, -181.0);
    glVertex3f(-36.0, 20.0, -190.0);         //BERDIRI 2
    glVertex3f(-36.0, -10.0, -190.0);
    glVertex3f(-36.0, -10.0, -188.0);
    glVertex3f(-36.0, 20.0, -188.0);
    glVertex3f(-36.0, 20.0, -197.0);         //BERDIRI 3
    glVertex3f(-36.0, -10.0, -197.0);
    glVertex3f(-36.0, -10.0, -195.0);
    glVertex3f(-36.0, 20.0, -195.0);
    glVertex3f(-36.0, 20.0, -205.0);         //BERDIRI 4
    glVertex3f(-36.0, -10.0, -205.0);
    glVertex3f(-36.0, -10.0, -203.0);
    glVertex3f(-36.0, 20.0, -203.0);
    glVertex3f(-36.0, 20.0, -212.0);         //BERDIRI 5
    glVertex3f(-36.0, -10.0, -212.0);
    glVertex3f(-36.0, -10.0, -210.0);
    glVertex3f(-36.0, 20.0, -210.0);
    glVertex3f(-36.0, 20.0, -219.0);         //BERDIRI 6
    glVertex3f(-36.0, -10.0, -219.0);
    glVertex3f(-36.0, -10.0, -217.0);
    glVertex3f(-36.0, 20.0, -217.0);
    glVertex3f(-36.0, 10.0, -219.0);         //DEPAN - LANTAI 2
    glVertex3f(-36.0, 0.0, -219.0);
    glVertex3f(-36.0, 0.0, -181.0);
    glVertex3f(-36.0, 10.0, -181.0);
    glVertex3f(-30.0, 35.0, -176.0);         //BERDIRI - LANTAI 2-4 DARI KIRI 1
    glVertex3f(-30.0, 20.0, -176.0);
    glVertex3f(-30.0, 20.0, -175.0);
    glVertex3f(-30.0, 35.0, -175.0);
    glVertex3f(-30.0, 35.0, -183.0);         //BERDIRI 2
    glVertex3f(-30.0, 20.0, -183.0);
    glVertex3f(-30.0, 20.0, -181.0);
    glVertex3f(-30.0, 35.0, -181.0);
    glVertex3f(-30.0, 50.0, -190.0);         //BERDIRI 3
    glVertex3f(-30.0, 20.0, -190.0);
    glVertex3f(-30.0, 20.0, -188.0);
    glVertex3f(-30.0, 50.0, -188.0);
    glVertex3f(-30.0, 50.0, -197.0);         //BERDIRI 4
    glVertex3f(-30.0, 20.0, -197.0);
    glVertex3f(-30.0, 20.0, -195.0);
    glVertex3f(-30.0, 50.0, -195.0);
    glVertex3f(-30.0, 50.0, -205.0);         //BERDIRI 5
    glVertex3f(-30.0, 20.0, -205.0);
    glVertex3f(-30.0, 20.0, -203.0);
    glVertex3f(-30.0, 50.0, -203.0);
    glVertex3f(-30.0, 50.0, -212.0);         //BERDIRI 6
    glVertex3f(-30.0, 20.0, -212.0);
    glVertex3f(-30.0, 20.0, -210.0);
    glVertex3f(-30.0, 50.0, -210.0);
    glVertex3f(-30.0, 35.0, -219.0);         //BERDIRI 7
    glVertex3f(-30.0, 20.0, -219.0);
    glVertex3f(-30.0, 20.0, -217.0);
    glVertex3f(-30.0, 35.0, -217.0);
    glVertex3f(-30.0, 35.0, -225.0);         //BERDIRI 8
    glVertex3f(-30.0, 20.0, -225.0);
    glVertex3f(-30.0, 20.0, -224.0);
    glVertex3f(-30.0, 35.0, -224.0);
    glVertex3f(-36.0, 20.0, -219.0);         //DEPAN - LANTAI 2
    glVertex3f(-36.0, 15.0, -219.0);
    glVertex3f(-36.0, 15.0, -181.0);
    glVertex3f(-36.0, 20.0, -181.0);
    glVertex3f(-30.0, 10.0, -225.0);         //DEPAN - LANTAI 2
    glVertex3f(-30.0, 5.0, -225.0);
    glVertex3f(-30.0, 5.0, -175.0);
    glVertex3f(-30.0, 10.0, -175.0);
    glVertex3f(-30.0, 25.0, -225.0);         //DEPAN - LANTAI 3
    glVertex3f(-30.0, 15.0, -225.0);
    glVertex3f(-30.0, 15.0, -175.0);
    glVertex3f(-30.0, 25.0, -175.0);
    glVertex3f(-30.0, 40.0, -210.0);         //DEPAN - LANTAI 4
    glVertex3f(-30.0, 30.0, -210.0);
    glVertex3f(-30.0, 30.0, -190.0);
    glVertex3f(-30.0, 40.0, -190.0);
    glVertex3f(-30.0, 50.0, -210.0);         //DEPAN - LANTAI 4
    glVertex3f(-30.0, 45.0, -210.0);
    glVertex3f(-30.0, 45.0, -190.0);
    glVertex3f(-30.0, 50.0, -190.0);
    glVertex3f(-30.0, 37.0, -190.0);         //DEPAN - LANTAI 4
    glVertex3f(-30.0, 30.0, -190.0);
    glVertex3f(-30.0, 30.0, -175.0);
    glVertex3f(-30.0, 37.0, -175.0);
    glVertex3f(-30.0, 37.0, -225.0);         //DEPAN - LANTAI 4
    glVertex3f(-30.0, 30.0, -225.0);
    glVertex3f(-30.0, 30.0, -210.0);
    glVertex3f(-30.0, 37.0, -210.0);
    glVertex3f(-43.0, 50.0, -225.0);         //DEPAN - LANTAI 4 KANAN
    glVertex3f(-43.0, 35.0, -225.0);
    glVertex3f(-43.0, 35.0, -212.0);
    glVertex3f(-43.0, 50.0, -212.0);
    glVertex3f(-43.0, 50.0, -188.0);         //DEPAN - LANTAI 4 KIRI
    glVertex3f(-43.0, 35.0, -188.0);
    glVertex3f(-43.0, 35.0, -175.0);
    glVertex3f(-43.0, 50.0, -175.0);

    glVertex3f(-30.0, 5.0, -178.0);         //DEPAN - PILAR 1
    glVertex3f(-30.0, -10.0, -178.0);
    glVertex3f(-30.0, -10.0, -175.0);
    glVertex3f(-30.0, 5.0, -175.0);
    glVertex3f(-33.0, 5.0, -178.0);         //DEPAN - PILAR 1
    glVertex3f(-33.0, -10.0, -178.0);
    glVertex3f(-33.0, -10.0, -175.0);
    glVertex3f(-33.0, 5.0, -175.0);
    glVertex3f(-30.0, 5.0, -188.0);         //DEPAN - PILAR 2
    glVertex3f(-30.0, -10.0, -188.0);
    glVertex3f(-30.0, -10.0, -185.0);
    glVertex3f(-30.0, 5.0, -185.0);
    glVertex3f(-33.0, 5.0, -188.0);         //DEPAN - PILAR 2
    glVertex3f(-33.0, -10.0, -188.0);
    glVertex3f(-33.0, -10.0, -185.0);
    glVertex3f(-33.0, 5.0, -185.0);
    glVertex3f(-33.0, -10.0, -185.0);       //DEPAN - PILAR 2
    glVertex3f(-33.0, 5.0, -185.0);
    glVertex3f(-30.0, 5.0, -185.0);
    glVertex3f(-30.0, -10.0, -185.0);
    glVertex3f(-33.0, -10.0, -188.0);       //DEPAN - PILAR 2
    glVertex3f(-33.0, 5.0, -188.0);
    glVertex3f(-30.0, 5.0, -188.0);
    glVertex3f(-30.0, -10.0, -188.0);
    glVertex3f(-30.0, 5.0, -197.0);         //DEPAN - PILAR 3
    glVertex3f(-30.0, -10.0, -197.0);
    glVertex3f(-30.0, -10.0, -194.0);
    glVertex3f(-30.0, 5.0, -194.0);
    glVertex3f(-33.0, 5.0, -197.0);         //DEPAN - PILAR 3
    glVertex3f(-33.0, -10.0, -197.0);
    glVertex3f(-33.0, -10.0, -194.0);
    glVertex3f(-33.0, 5.0, -194.0);
    glVertex3f(-33.0, -10.0, -194.0);       //DEPAN - PILAR 3
    glVertex3f(-33.0, 5.0, -194.0);
    glVertex3f(-30.0, 5.0, -194.0);
    glVertex3f(-30.0, -10.0, -194.0);
    glVertex3f(-33.0, -10.0, -197.0);       //DEPAN - PILAR 3
    glVertex3f(-33.0, 5.0, -197.0);
    glVertex3f(-30.0, 5.0, -197.0);
    glVertex3f(-30.0, -10.0, -197.0);
    glVertex3f(-30.0, 5.0, -206.0);         //DEPAN - PILAR 4
    glVertex3f(-30.0, -10.0, -206.0);
    glVertex3f(-30.0, -10.0, -203.0);
    glVertex3f(-30.0, 5.0, -203.0);
    glVertex3f(-33.0, 5.0, -206.0);         //DEPAN - PILAR 4
    glVertex3f(-33.0, -10.0, -206.0);
    glVertex3f(-33.0, -10.0, -203.0);
    glVertex3f(-33.0, 5.0, -203.0);
    glVertex3f(-33.0, -10.0, -203.0);       //DEPAN - PILAR 4
    glVertex3f(-33.0, 5.0, -203.0);
    glVertex3f(-30.0, 5.0, -203.0);
    glVertex3f(-30.0, -10.0, -203.0);
    glVertex3f(-33.0, -10.0, -206.0);       //DEPAN - PILAR 4
    glVertex3f(-33.0, 5.0, -206.0);
    glVertex3f(-30.0, 5.0, -206.0);
    glVertex3f(-30.0, -10.0, -206.0);
    glVertex3f(-30.0, 5.0, -215.0);         //DEPAN - PILAR 5
    glVertex3f(-30.0, -10.0, -215.0);
    glVertex3f(-30.0, -10.0, -212.0);
    glVertex3f(-30.0, 5.0, -212.0);
    glVertex3f(-33.0, 5.0, -215.0);         //DEPAN - PILAR 5
    glVertex3f(-33.0, -10.0, -215.0);
    glVertex3f(-33.0, -10.0, -212.0);
    glVertex3f(-33.0, 5.0, -212.0);
    glVertex3f(-33.0, -10.0, -212.0);       //DEPAN - PILAR 5
    glVertex3f(-33.0, 5.0, -212.0);
    glVertex3f(-30.0, 5.0, -212.0);
    glVertex3f(-30.0, -10.0, -212.0);
    glVertex3f(-33.0, -10.0, -215.0);       //DEPAN - PILAR 5
    glVertex3f(-33.0, 5.0, -215.0);
    glVertex3f(-30.0, 5.0, -215.0);
    glVertex3f(-30.0, -10.0, -215.0);
    glVertex3f(-30.0, 5.0, -225.0);         //DEPAN - PILAR 6
    glVertex3f(-30.0, -10.0, -225.0);
    glVertex3f(-30.0, -10.0, -222.0);
    glVertex3f(-30.0, 5.0, -222.0);
    glVertex3f(-33.0, 5.0, -225.0);         //DEPAN - PILAR 6
    glVertex3f(-33.0, -10.0, -225.0);
    glVertex3f(-33.0, -10.0, -222.0);
    glVertex3f(-33.0, 5.0, -222.0);
    glVertex3f(-33.0, -10.0, -222.0);       //DEPAN - PILAR 6
    glVertex3f(-33.0, 5.0, -222.0);
    glVertex3f(-30.0, 5.0, -222.0);
    glVertex3f(-30.0, -10.0, -222.0);
    glVertex3f(-33.0, -10.0, -225.0);       //DEPAN - PILAR 6
    glVertex3f(-33.0, 5.0, -225.0);
    glVertex3f(-30.0, 5.0, -225.0);
    glVertex3f(-30.0, -10.0, -225.0);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.5, 0.5, 0.5);                 //LANTAI - 1
    glVertex3f(-30, -9.9, -225.0);
    glVertex3f(-100, -9.9, -225.0);
    glVertex3f(-100, -9.9, -175.0);
    glVertex3f(-30, -9.9, -175.0);
    glVertex3f(-30, 5.0, -225.0);            //LANTAI - 2
    glVertex3f(-100, 5.0, -225.0);
    glVertex3f(-100, 5.0, -175.0);
    glVertex3f(-30, 5.0, -175.0);
    glVertex3f(-30, 20.0, -225.0);            //LANTAI - 3
    glVertex3f(-100, 20.0, -225.0);
    glVertex3f(-100, 20.0, -175.0);
    glVertex3f(-30, 20.0, -175.0);
    glVertex3f(-43, 35.0, -225.0);            //LANTAI - 4
    glVertex3f(-100, 35.0, -225.0);
    glVertex3f(-100, 35.0, -175.0);
    glVertex3f(-43, 35.0, -175.0);
    glVertex3f(-30, 50.0, -235.0);            //LANTAI - 4 1
    glVertex3f(-100, 50.0, -235.0);
    glVertex3f(-100, 50.0, -165.0);
    glVertex3f(-30, 50.0, -165.0);
    glVertex3f(-20, 50.0, -215.0);            //LANTAI - 4 2
    glVertex3f(-43, 50.0, -215.0);
    glVertex3f(-43, 50.0, -185.0);
    glVertex3f(-20, 50.0, -185.0);
    glVertex3f(-30, 35.0, -212.0);            //LANTAI - 4
    glVertex3f(-43, 35.0, -212.0);
    glVertex3f(-43, 35.0, -188.0);
    glVertex3f(-30, 35.0, -188.0);
    glVertex3f(-30, 50.0, -212.0);            //LANTAI - 4
    glVertex3f(-43, 50.0, -212.0);
    glVertex3f(-43, 50.0, -188.0);
    glVertex3f(-30, 50.0, -188.0);
    glEnd();

    glBegin(GL_QUADS);                       //PINTU
    glColor3f(0.66, 0.40, 0.0);
    glVertex3f(-36.0, 0.0, -203.0);
    glVertex3f(-36.0, -10.0, -203.0);
    glVertex3f(-36.0, -10.0, -197.0);
    glVertex3f(-36.0, 0.0, -197.0);
    glEnd();

    glBegin(GL_QUADS);                      //ATAP
    glColor3f(0.2, 0.2, 0.2);               //DEPAN - BAWAH PANJANG
    glVertex3f(-30.0, 40.0, -212.0);
    glVertex3f(-20.0, 30.0, -212.0);
    glVertex3f(-20.0, 30.0, -188.0);
    glVertex3f(-30.0, 40.0, -188.0);
    glEnd();
    glBegin(GL_POLYGON);                    //DEPAN - BAWAH KIRI
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-43, 50.0, -188.0);
    glVertex3f(-30, 40.0, -188.0);
    glVertex3f(-20, 30.0, -188.0);
    glVertex3f(-20, 30.0, -175.0);
    glVertex3f(-30, 40.0, -175.0);
    glEnd();
    glBegin(GL_POLYGON);                    //DEPAN - BAWAH UJUNG KIRI
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-30.0, 40.0, -175.0);
    glVertex3f(-20.0, 30.0, -175.0);
    glVertex3f(-20.0, 30.0, -165.0);
    glVertex3f(-30.0, 30.0, -165.0);
    glEnd();
    glBegin(GL_POLYGON);                    //DEPAN - BAWAH KANAN
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-43, 50.0, -212.0);
    glVertex3f(-30, 40.0, -212.0);
    glVertex3f(-20, 30.0, -212.0);
    glVertex3f(-20, 30.0, -225.0);
    glVertex3f(-30, 40.0, -225.0);
    glEnd();
    glBegin(GL_POLYGON);                    //DEPAN - BAWAH UJUNG KANAN
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-30.0, 40.0, -225.0);
    glVertex3f(-20.0, 30.0, -225.0);
    glVertex3f(-20.0, 30.0, -235.0);
    glVertex3f(-30.0, 30.0, -235.0);
    glEnd();
    glBegin(GL_POLYGON);                    //KIRI - KANAN
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-43.0, 50.0, -188.0);
    glVertex3f(-30.0, 40.0, -175.0);
    glVertex3f(-30.0, 30.0, -165.0);
    glVertex3f(-43.0, 30.0, -165.0);
    glVertex3f(-43.0, 40.0, -175.0);
    glEnd();
    glBegin(GL_QUADS);                      //KIRI - SISI SIRIP PANJANG TENGAH
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-43, 40.0, -175.0);
    glVertex3f(-100, 40.0, -175.0);
    glVertex3f(-100, 30.0, -165.0);
    glVertex3f(-43, 30.0, -165.0);
    glEnd();
    glBegin(GL_QUADS);                      //KIRI - SISI SIRIP PANJANG ATAS
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-45, 70.0, -190.0);
    glVertex3f(-100, 70.0, -190.0);
    glVertex3f(-100, 50.0, -165.0);
    glVertex3f(-30, 50.0, -165.0);
    glEnd();
    glBegin(GL_QUADS);                      //KIRI - SISI SIRIP PENDEK BAWAH
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-30, 60.0, -193.0);
    glVertex3f(-40, 60.0, -193.0);
    glVertex3f(-30, 50.0, -185.0);
    glVertex3f(-20, 50.0, -185.0);
    glEnd();
    glBegin(GL_POLYGON);                    //KIRI - SIRIP BESAR ATAS
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-55.0, 90.0, -195.0);
    glVertex3f(-45.0, 110.0, -200.0);
    glVertex3f(-100.0, 110.0, -200.0);
    glVertex3f(-100.0, 70.0, -190.0);
    glVertex3f(-45.0, 70.0, -190.0);
    glEnd();
    glBegin(GL_POLYGON);                    //KIRI - SIRIP KECIL BAWAH
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-40.0, 75.0, -196.0);
    glVertex3f(-30.0, 90.0, -200.0);
    glVertex3f(-55.0, 90.0, -200.0);
    glVertex3f(-40.0, 60.0, -192.0);
    glVertex3f(-30.0, 60.0, -192.0);
    glEnd();
    glBegin(GL_POLYGON);                    //KANAN - KIRI
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-43.0, 50.0, -212.0);
    glVertex3f(-43.0, 40.0, -225.0);
    glVertex3f(-43.0, 30.0, -235.0);
    glVertex3f(-30.0, 30.0, -235.0);
    glVertex3f(-30.0, 40.0, -225.0);
    glEnd();
    glBegin(GL_POLYGON);                    //KANAN - SISI SIRIP PANJANG TENGAH
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-43, 30.0, -235.0);
    glVertex3f(-100, 30.0, -235.0);
    glVertex3f(-100, 40.0, -225.0);
    glVertex3f(-43, 40.0, -225.0);
    glEnd();
    glBegin(GL_POLYGON);                    //KANAN - SISI SIRIP PANJANG ATAS
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-30, 50.0, -235.0);
    glVertex3f(-100, 50.0, -235.0);
    glVertex3f(-100, 70.0, -210.0);
    glVertex3f(-45, 70.0, -210.0);
    glEnd();
    glBegin(GL_POLYGON);                    //KANAN - SISI SIRIP PENDEK BAWAH
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-20, 50.0, -215.0);
    glVertex3f(-30, 50.0, -215.0);
    glVertex3f(-40, 60.0, -207.0);
    glVertex3f(-30, 60.0, -207.0);
    glEnd();
    glBegin(GL_POLYGON);                    //KANAN - SIRIP BESAR ATAS
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-55.0, 90.0, -205.0);
    glVertex3f(-45.0, 110.0, -200.0);
    glVertex3f(-100.0, 110.0, -200.0);
    glVertex3f(-100.0, 70.0, -210.0);
    glVertex3f(-45.0, 70.0, -210.0);
    glEnd();
    glBegin(GL_POLYGON);                    //KANAN - SIRIP KECIL BAWAH
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-40.0, 75.0, -204.0);
    glVertex3f(-30.0, 90.0, -200.0);
    glVertex3f(-55.0, 90.0, -200.0);
    glVertex3f(-40.0, 60.0, -208.0);
    glVertex3f(-30.0, 60.0, -208.0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-45.0, 70.0, -210.0);         //DEPAN - PENUTUP SIRIP BESAR BAWAH
    glVertex3f(-55.0, 90.0, -205.0);
    glVertex3f(-55.0, 90.0, -195.0);
    glVertex3f(-45.0, 70.0, -190.0);
    glVertex3f(-30.0, 50.0, -165.0);
    glVertex3f(-30.0, 50.0, -235.0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-55.0, 90.0, -195.0);         //DEPAN - PENUTUP SIRIP BESAR ATAS
    glVertex3f(-55.0, 90.0, -205.0);
    glVertex3f(-45.0, 110.0, -200.0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-40.0, 75.0, -204.0);         //DEPAN - PENUTUP SIRIP KECIL BAWAH
    glVertex3f(-40.0, 75.0, -196.0);
    glVertex3f(-30.0, 60.0, -182.0);
    glVertex3f(-20.0, 50.0, -185.0);
    glVertex3f(-20.0, 50.0, -215.0);
    glVertex3f(-30.0, 60.0, -208.0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-40.0, 75.0, -204.0);         //DEPAN - PENUTUP SIRIP KECIL ATAS
    glVertex3f(-30.0, 90.0, -200.0);
    glVertex3f(-40.0, 75.0, -196.0);
    glEnd();
    //SAMPAI SINI


    //GEDUNG 3
    glBegin(GL_LINE_LOOP);              //JENDELA KIRI DARI KANAN - LANTAI 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(43.0, -5.0, -181.0);
    glVertex3f(43.0, 0.0, -181.0);
    glVertex3f(38.0, 0.0, -181.0);
    glVertex3f(38.0, -5.0, -181.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(50.0, -5.0, -181.0);
    glVertex3f(50.0, 0.0, -181.0);
    glVertex3f(45.0, 0.0, -181.0);
    glVertex3f(45.0, -5.0, -181.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(57.0, -5.0, -181.0);
    glVertex3f(57.0, 0.0, -181.0);
    glVertex3f(52.0, 0.0, -181.0);
    glVertex3f(52.0, -5.0, -181.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(64.0, -5.0, -181.0);
    glVertex3f(64.0, 0.0, -181.0);
    glVertex3f(59.0, 0.0, -181.0);
    glVertex3f(59.0, -5.0, -181.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(71.0, -5.0, -181.0);
    glVertex3f(71.0, 0.0, -181.0);
    glVertex3f(66.0, 0.0, -181.0);
    glVertex3f(66.0, -5.0, -181.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(78.0, -5.0, -181.0);
    glVertex3f(78.0, 0.0, -181.0);
    glVertex3f(73.0, 0.0, -181.0);
    glVertex3f(73.0, -5.0, -181.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(85.0, -5.0, -181.0);
    glVertex3f(85.0, 0.0, -181.0);
    glVertex3f(80.0, 0.0, -181.0);
    glVertex3f(80.0, -5.0, -181.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(92.0, -5.0, -181.0);
    glVertex3f(92.0, 0.0, -181.0);
    glVertex3f(87.0, 0.0, -181.0);
    glVertex3f(87.0, -5.0, -181.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(99.0, -5.0, -181.0);
    glVertex3f(99.0, 0.0, -181.0);
    glVertex3f(94.0, 0.0, -181.0);
    glVertex3f(94.0, -5.0, -181.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(43.0, 10.0, -181.0);
    glVertex3f(43.0, 15.0, -181.0);
    glVertex3f(38.0, 15.0, -181.0);
    glVertex3f(38.0, 10.0, -181.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(50.0, 10.0, -181.0);
    glVertex3f(50.0, 15.0, -181.0);
    glVertex3f(45.0, 15.0, -181.0);
    glVertex3f(45.0, 10.0, -181.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(57.0, 10.0, -181.0);
    glVertex3f(57.0, 15.0, -181.0);
    glVertex3f(52.0, 15.0, -181.0);
    glVertex3f(52.0, 10.0, -181.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(64.0, 10.0, -181.0);
    glVertex3f(64.0, 15.0, -181.0);
    glVertex3f(59.0, 15.0, -181.0);
    glVertex3f(59.0, 10.0, -181.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(71.0, 10.0, -181.0);
    glVertex3f(71.0, 15.0, -181.0);
    glVertex3f(66.0, 15.0, -181.0);
    glVertex3f(66.0, 10.0, -181.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(78.0, 10.0, -181.0);
    glVertex3f(78.0, 15.0, -181.0);
    glVertex3f(73.0, 15.0, -181.0);
    glVertex3f(73.0, 10.0, -181.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(85.0, 10.0, -181.0);
    glVertex3f(85.0, 15.0, -181.0);
    glVertex3f(80.0, 15.0, -181.0);
    glVertex3f(80.0, 10.0, -181.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(92.0, 10.0, -181.0);
    glVertex3f(92.0, 15.0, -181.0);
    glVertex3f(87.0, 15.0, -181.0);
    glVertex3f(87.0, 10.0, -181.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(99.0, 10.0, -181.0);
    glVertex3f(99.0, 15.0, -181.0);
    glVertex3f(94.0, 15.0, -181.0);
    glVertex3f(94.0, 10.0, -181.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(36.0, 25.0, -175.0);
    glVertex3f(36.0, 30.0, -175.0);
    glVertex3f(31.0, 30.0, -175.0);
    glVertex3f(31.0, 25.0, -175.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(43.0, 25.0, -175.0);
    glVertex3f(43.0, 30.0, -175.0);
    glVertex3f(38.0, 30.0, -175.0);
    glVertex3f(38.0, 25.0, -175.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(50.0, 25.0, -175.0);
    glVertex3f(50.0, 30.0, -175.0);
    glVertex3f(45.0, 30.0, -175.0);
    glVertex3f(45.0, 25.0, -175.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(57.0, 25.0, -175.0);
    glVertex3f(57.0, 30.0, -175.0);
    glVertex3f(52.0, 30.0, -175.0);
    glVertex3f(52.0, 25.0, -175.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(64.0, 25.0, -175.0);
    glVertex3f(64.0, 30.0, -175.0);
    glVertex3f(59.0, 30.0, -175.0);
    glVertex3f(59.0, 25.0, -175.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(71.0, 25.0, -175.0);
    glVertex3f(71.0, 30.0, -175.0);
    glVertex3f(66.0, 30.0, -175.0);
    glVertex3f(66.0, 25.0, -175.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(78.0, 25.0, -175.0);
    glVertex3f(78.0, 30.0, -175.0);
    glVertex3f(73.0, 30.0, -175.0);
    glVertex3f(73.0, 25.0, -175.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(85.0, 25.0, -175.0);
    glVertex3f(85.0, 30.0, -175.0);
    glVertex3f(80.0, 30.0, -175.0);
    glVertex3f(80.0, 25.0, -175.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(92.0, 25.0, -175.0);
    glVertex3f(92.0, 30.0, -175.0);
    glVertex3f(87.0, 30.0, -175.0);
    glVertex3f(87.0, 25.0, -175.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(99.0, 25.0, -175.0);
    glVertex3f(99.0, 30.0, -175.0);
    glVertex3f(94.0, 30.0, -175.0);
    glVertex3f(94.0, 25.0, -175.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(50.0, 40.0, -175.0);
    glVertex3f(50.0, 45.0, -175.0);
    glVertex3f(45.0, 45.0, -175.0);
    glVertex3f(45.0, 40.0, -175.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(57.0, 40.0, -175.0);
    glVertex3f(57.0, 45.0, -175.0);
    glVertex3f(52.0, 45.0, -175.0);
    glVertex3f(52.0, 40.0, -175.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(64.0, 40.0, -175.0);
    glVertex3f(64.0, 45.0, -175.0);
    glVertex3f(59.0, 45.0, -175.0);
    glVertex3f(59.0, 40.0, -175.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(71.0, 40.0, -175.0);
    glVertex3f(71.0, 45.0, -175.0);
    glVertex3f(66.0, 45.0, -175.0);
    glVertex3f(66.0, 40.0, -175.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(78.0, 40.0, -175.0);
    glVertex3f(78.0, 45.0, -175.0);
    glVertex3f(73.0, 45.0, -175.0);
    glVertex3f(73.0, 40.0, -175.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(85.0, 40.0, -175.0);
    glVertex3f(85.0, 45.0, -175.0);
    glVertex3f(80.0, 45.0, -175.0);
    glVertex3f(80.0, 40.0, -175.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(92.0, 40.0, -175.0);
    glVertex3f(92.0, 45.0, -175.0);
    glVertex3f(87.0, 45.0, -175.0);
    glVertex3f(87.0, 40.0, -175.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KI - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(99.0, 40.0, -175.0);
    glVertex3f(99.0, 45.0, -175.0);
    glVertex3f(94.0, 45.0, -175.0);
    glVertex3f(94.0, 40.0, -175.0);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 0.0, 0.0);         //JENDELA KANAN DARI KIRI - LANTAI 1
    glVertex3f(43.0, -5.0, -219.0);
    glVertex3f(43.0, 0.0, -219.0);
    glVertex3f(38.0, 0.0, -219.0);
    glVertex3f(38.0, -5.0, -219.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(50.0, -5.0, -219.0);
    glVertex3f(50.0, 0.0, -219.0);
    glVertex3f(45.0, 0.0, -219.0);
    glVertex3f(45.0, -5.0, -219.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(57.0, -5.0, -219.0);
    glVertex3f(57.0, 0.0, -219.0);
    glVertex3f(52.0, 0.0, -219.0);
    glVertex3f(52.0, -5.0, -219.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(64.0, -5.0, -219.0);
    glVertex3f(64.0, 0.0, -219.0);
    glVertex3f(59.0, 0.0, -219.0);
    glVertex3f(59.0, -5.0, -219.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(71.0, -5.0, -219.0);
    glVertex3f(71.0, 0.0, -219.0);
    glVertex3f(66.0, 0.0, -219.0);
    glVertex3f(66.0, -5.0, -219.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(78.0, -5.0, -219.0);
    glVertex3f(78.0, 0.0, -219.0);
    glVertex3f(73.0, 0.0, -219.0);
    glVertex3f(73.0, -5.0, -219.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(85.0, -5.0, -219.0);
    glVertex3f(85.0, 0.0, -219.0);
    glVertex3f(80.0, 0.0, -219.0);
    glVertex3f(80.0, -5.0, -219.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(92.0, -5.0, -219.0);
    glVertex3f(92.0, 0.0, -219.0);
    glVertex3f(87.0, 0.0, -219.0);
    glVertex3f(87.0, -5.0, -219.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(99.0, -5.0, -219.0);
    glVertex3f(99.0, 0.0, -219.0);
    glVertex3f(94.0, 0.0, -219.0);
    glVertex3f(94.0, -5.0, -219.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(43.0, 10.0, -219.0);
    glVertex3f(43.0, 15.0, -219.0);
    glVertex3f(38.0, 15.0, -219.0);
    glVertex3f(38.0, 10.0, -219.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(50.0, 10.0, -219.0);
    glVertex3f(50.0, 15.0, -219.0);
    glVertex3f(45.0, 15.0, -219.0);
    glVertex3f(45.0, 10.0, -219.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(57.0, 10.0, -219.0);
    glVertex3f(57.0, 15.0, -219.0);
    glVertex3f(52.0, 15.0, -219.0);
    glVertex3f(52.0, 10.0, -219.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(64.0, 10.0, -219.0);
    glVertex3f(64.0, 15.0, -219.0);
    glVertex3f(59.0, 15.0, -219.0);
    glVertex3f(59.0, 10.0, -219.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(71.0, 10.0, -219.0);
    glVertex3f(71.0, 15.0, -219.0);
    glVertex3f(66.0, 15.0, -219.0);
    glVertex3f(66.0, 10.0, -219.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(78.0, 10.0, -219.0);
    glVertex3f(78.0, 15.0, -219.0);
    glVertex3f(73.0, 15.0, -219.0);
    glVertex3f(73.0, 10.0, -219.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(85.0, 10.0, -219.0);
    glVertex3f(85.0, 15.0, -219.0);
    glVertex3f(80.0, 15.0, -219.0);
    glVertex3f(80.0, 10.0, -219.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(92.0, 10.0, -219.0);
    glVertex3f(92.0, 15.0, -219.0);
    glVertex3f(87.0, 15.0, -219.0);
    glVertex3f(87.0, 10.0, -219.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(99.0, 10.0, -219.0);
    glVertex3f(99.0, 15.0, -219.0);
    glVertex3f(94.0, 15.0, -219.0);
    glVertex3f(94.0, 10.0, -219.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(36.0, 25.0, -225.0);
    glVertex3f(36.0, 30.0, -225.0);
    glVertex3f(31.0, 30.0, -225.0);
    glVertex3f(31.0, 25.0, -225.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(43.0, 25.0, -225.0);
    glVertex3f(43.0, 30.0, -225.0);
    glVertex3f(38.0, 30.0, -225.0);
    glVertex3f(38.0, 25.0, -225.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(50.0, 25.0, -225.0);
    glVertex3f(50.0, 30.0, -225.0);
    glVertex3f(45.0, 30.0, -225.0);
    glVertex3f(45.0, 25.0, -225.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(57.0, 25.0, -225.0);
    glVertex3f(57.0, 30.0, -225.0);
    glVertex3f(52.0, 30.0, -225.0);
    glVertex3f(52.0, 25.0, -225.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(64.0, 25.0, -225.0);
    glVertex3f(64.0, 30.0, -225.0);
    glVertex3f(59.0, 30.0, -225.0);
    glVertex3f(59.0, 25.0, -225.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(71.0, 25.0, -225.0);
    glVertex3f(71.0, 30.0, -225.0);
    glVertex3f(66.0, 30.0, -225.0);
    glVertex3f(66.0, 25.0, -225.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(78.0, 25.0, -225.0);
    glVertex3f(78.0, 30.0, -225.0);
    glVertex3f(73.0, 30.0, -225.0);
    glVertex3f(73.0, 25.0, -225.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(85.0, 25.0, -225.0);
    glVertex3f(85.0, 30.0, -225.0);
    glVertex3f(80.0, 30.0, -225.0);
    glVertex3f(80.0, 25.0, -225.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(92.0, 25.0, -225.0);
    glVertex3f(92.0, 30.0, -225.0);
    glVertex3f(87.0, 30.0, -225.0);
    glVertex3f(87.0, 25.0, -225.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(99.0, 25.0, -225.0);
    glVertex3f(99.0, 30.0, -225.0);
    glVertex3f(94.0, 30.0, -225.0);
    glVertex3f(94.0, 25.0, -225.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(50.0, 40.0, -225.0);
    glVertex3f(50.0, 45.0, -225.0);
    glVertex3f(45.0, 45.0, -225.0);
    glVertex3f(45.0, 40.0, -225.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(57.0, 40.0, -225.0);
    glVertex3f(57.0, 45.0, -225.0);
    glVertex3f(52.0, 45.0, -225.0);
    glVertex3f(52.0, 40.0, -225.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(64.0, 40.0, -225.0);
    glVertex3f(64.0, 45.0, -225.0);
    glVertex3f(59.0, 45.0, -225.0);
    glVertex3f(59.0, 40.0, -225.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(71.0, 40.0, -225.0);
    glVertex3f(71.0, 45.0, -225.0);
    glVertex3f(66.0, 45.0, -225.0);
    glVertex3f(66.0, 40.0, -225.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(78.0, 40.0, -225.0);
    glVertex3f(78.0, 45.0, -225.0);
    glVertex3f(73.0, 45.0, -225.0);
    glVertex3f(73.0, 40.0, -225.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(85.0, 40.0, -225.0);
    glVertex3f(85.0, 45.0, -225.0);
    glVertex3f(80.0, 45.0, -225.0);
    glVertex3f(80.0, 40.0, -225.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(92.0, 40.0, -225.0);
    glVertex3f(92.0, 45.0, -225.0);
    glVertex3f(87.0, 45.0, -225.0);
    glVertex3f(87.0, 40.0, -225.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.KA - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(99.0, 40.0, -225.0);
    glVertex3f(99.0, 45.0, -225.0);
    glVertex3f(94.0, 45.0, -225.0);
    glVertex3f(94.0, 40.0, -225.0);
    glEnd();

    glBegin(GL_LINE_LOOP);              //JENDELA DEPAN DARI KIRI- LANTAI 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(36.0, 0.0, -188.0);
    glVertex3f(36.0, -5.0, -188.0);
    glVertex3f(36.0, -5.0, -183.0);
    glVertex3f(36.0, 0.0, -183.0);
    glEnd();
    glBegin(GL_LINE_LOOP);              //J.D - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(36.0, 0.0, -195.0);
    glVertex3f(36.0, -5.0, -195.0);
    glVertex3f(36.0, -5.0, -190.0);
    glVertex3f(36.0, 0.0, -190.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(36.0, 0.0, -210.0);
    glVertex3f(36.0, -5.0, -210.0);
    glVertex3f(36.0, -5.0, -205.0);
    glVertex3f(36.0, 0.0, -205.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 1
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(36.0, 0.0, -217.0);
    glVertex3f(36.0, -5.0, -217.0);
    glVertex3f(36.0, -5.0, -212.0);
    glVertex3f(36.0, 0.0, -212.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(36.0, 15.0, -188.0);
    glVertex3f(36.0, 10.0, -188.0);
    glVertex3f(36.0, 10.0, -183.0);
    glVertex3f(36.0, 15.0, -183.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(36.0, 15.0, -195.0);
    glVertex3f(36.0, 10.0, -195.0);
    glVertex3f(36.0, 10.0, -190.0);
    glVertex3f(36.0, 15.0, -190.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(36.0, 15.0, -203.0);
    glVertex3f(36.0, 10.0, -203.0);
    glVertex3f(36.0, 10.0, -197.0);
    glVertex3f(36.0, 15.0, -197.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(36.0, 15.0, -210.0);
    glVertex3f(36.0, 10.0, -210.0);
    glVertex3f(36.0, 10.0, -205.0);
    glVertex3f(36.0, 15.0, -205.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 2
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(36.0, 15.0, -217.0);
    glVertex3f(36.0, 10.0, -217.0);
    glVertex3f(36.0, 10.0, -212.0);
    glVertex3f(36.0, 15.0, -212.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(30.0, 25.0, -181.0);
    glVertex3f(30.0, 30.0, -181.0);
    glVertex3f(30.0, 30.0, -176.0);
    glVertex3f(30.0, 25.0, -176.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(30.0, 25.0, -188.0);
    glVertex3f(30.0, 30.0, -188.0);
    glVertex3f(30.0, 30.0, -183.0);
    glVertex3f(30.0, 25.0, -183.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(30.0, 25.0, -195.0);
    glVertex3f(30.0, 30.0, -195.0);
    glVertex3f(30.0, 30.0, -190.0);
    glVertex3f(30.0, 25.0, -190.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(30.0, 25.0, -203.0);
    glVertex3f(30.0, 30.0, -203.0);
    glVertex3f(30.0, 30.0, -197.0);
    glVertex3f(30.0, 25.0, -197.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(30.0, 25.0, -210.0);
    glVertex3f(30.0, 30.0, -210.0);
    glVertex3f(30.0, 30.0, -205.0);
    glVertex3f(30.0, 25.0, -205.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(30.0, 25.0, -217.0);
    glVertex3f(30.0, 30.0, -217.0);
    glVertex3f(30.0, 30.0, -212.0);
    glVertex3f(30.0, 25.0, -212.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 3
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(30.0, 25.0, -224.0);
    glVertex3f(30.0, 30.0, -224.0);
    glVertex3f(30.0, 30.0, -219.0);
    glVertex3f(30.0, 25.0, -219.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(30.0, 45.0, -195.0);
    glVertex3f(30.0, 40.0, -195.0);
    glVertex3f(30.0, 40.0, -190.0);
    glVertex3f(30.0, 45.0, -190.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(30.0, 45.0, -203.0);
    glVertex3f(30.0, 40.0, -203.0);
    glVertex3f(30.0, 40.0, -197.0);
    glVertex3f(30.0, 45.0, -197.0);
    glEnd();
    glBegin(GL_LINE_LOOP);               //J.D - L 4
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(30.0, 45.0, -210.0);
    glVertex3f(30.0, 40.0, -210.0);
    glVertex3f(30.0, 40.0, -205.0);
    glVertex3f(30.0, 45.0, -205.0);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);                 //KIRI - LANTAI 1
    glVertex3f(100.0, -10.0, -181.0);
    glVertex3f(100.0, -5.0, -181.0);
    glVertex3f(36.0, -5.0, -181.0);
    glVertex3f(36.0, -10.0, -181.0);//
    glVertex3f(38.0, -10.0, -181.0);        //BERDIRI - LANTAI 1-2 DARI KANAN 1
    glVertex3f(38.0, 20.0, -181.0);
    glVertex3f(36.0, 20.0, -181.0);
    glVertex3f(36.0, -10.0, -181.0);//
    glVertex3f(45.0, -10.0, -181.0);        //BERDIRI 2
    glVertex3f(45.0, 20.0, -181.0);
    glVertex3f(43.0, 20.0, -181.0);
    glVertex3f(43.0, -10.0, -181.0);//
    glVertex3f(52.0, -10.0, -181.0);        //BERDIRI 3
    glVertex3f(52.0, 20.0, -181.0);
    glVertex3f(50.0, 20.0, -181.0);
    glVertex3f(50.0, -10.0, -181.0);//
    glVertex3f(59.0, -10.0, -181.0);        //BERDIRI 4
    glVertex3f(59.0, 20.0, -181.0);
    glVertex3f(57.0, 20.0, -181.0);
    glVertex3f(57.0, -10.0, -181.0);//
    glVertex3f(66.0, -10.0, -181.0);        //BERDIRI 5
    glVertex3f(66.0, 20.0, -181.0);
    glVertex3f(64.0, 20.0, -181.0);
    glVertex3f(64.0, -10.0, -181.0);//
    glVertex3f(73.0, -10.0, -181.0);        //BERDIRI 6
    glVertex3f(73.0, 20.0, -181.0);
    glVertex3f(71.0, 20.0, -181.0);
    glVertex3f(71.0, -10.0, -181.0);//
    glVertex3f(80.0, -10.0, -181.0);        //BERDIRI 7
    glVertex3f(80.0, 20.0, -181.0);
    glVertex3f(78.0, 20.0, -181.0);
    glVertex3f(78.0, -10.0, -181.0);//
    glVertex3f(87.0, -10.0, -181.0);        //BERDIRI 8
    glVertex3f(87.0, 20.0, -181.0);
    glVertex3f(85.0, 20.0, -181.0);
    glVertex3f(85.0, -10.0, -181.0);//
    glVertex3f(94.0, -10.0, -181.0);        //BERDIRI 9
    glVertex3f(94.0, 20.0, -181.0);
    glVertex3f(92.0, 20.0, -181.0);
    glVertex3f(92.0, -10.0, -181.0);//
    glVertex3f(100.0, -10.0, -181.0);       //BERDIRI 9
    glVertex3f(100.0, 20.0, -181.0);
    glVertex3f(99.0, 20.0, -181.0);
    glVertex3f(99.0, -10.0, -181.0);//
    glVertex3f(100.0, 0.0, -181.0);         //KIRI - LANTAI 1-2
    glVertex3f(100.0, 10.0, -181.0);
    glVertex3f(36.0, 10.0, -181.0);
    glVertex3f(36.0, 0.0, -181.0);//
    glVertex3f(31.0, 20.0, -175.0);         //BERDIRI - LANTAI 2-4 DARI KANAN 1
    glVertex3f(31.0, 35.0, -175.0);
    glVertex3f(30.0, 35.0, -175.0);
    glVertex3f(30.0, 20.0, -175.0);//
    glVertex3f(38.0, 20.0, -175.0);         //BERDIRI 2
    glVertex3f(38.0, 35.0, -175.0);
    glVertex3f(36.0, 35.0, -175.0);
    glVertex3f(36.0, 20.0, -175.0);//
    glVertex3f(45.0, 20.0, -175.0);         //BERDIRI 3
    glVertex3f(45.0, 50.0, -175.0);
    glVertex3f(43.0, 50.0, -175.0);
    glVertex3f(43.0, 20.0, -175.0);//
    glVertex3f(52.0, 20.0, -175.0);         //BERDIRI 4
    glVertex3f(52.0, 50.0, -175.0);
    glVertex3f(50.0, 50.0, -175.0);
    glVertex3f(50.0, 20.0, -175.0);//
    glVertex3f(59.0, 20.0, -175.0);         //BERDIRI 5
    glVertex3f(59.0, 50.0, -175.0);
    glVertex3f(57.0, 50.0, -175.0);
    glVertex3f(57.0, 20.0, -175.0);//
    glVertex3f(66.0, 20.0, -175.0);         //BERDIRI 6
    glVertex3f(66.0, 50.0, -175.0);
    glVertex3f(64.0, 50.0, -175.0);
    glVertex3f(64.0, 20.0, -175.0);//
    glVertex3f(73.0, 20.0, -175.0);         //BERDIRI 7
    glVertex3f(73.0, 50.0, -175.0);
    glVertex3f(71.0, 50.0, -175.0);
    glVertex3f(71.0, 20.0, -175.0);//
    glVertex3f(80.0, 20.0, -175.0);         //BERDIRI 8
    glVertex3f(80.0, 50.0, -175.0);
    glVertex3f(78.0, 50.0, -175.0);
    glVertex3f(78.0, 20.0, -175.0);//
    glVertex3f(87.0, 20.0, -175.0);         //BERDIRI 9
    glVertex3f(87.0, 50.0, -175.0);
    glVertex3f(85.0, 50.0, -175.0);
    glVertex3f(85.0, 20.0, -175.0);//
    glVertex3f(94.0, 20.0, -175.0);         //BERDIRI 10
    glVertex3f(94.0, 50.0, -175.0);
    glVertex3f(92.0, 50.0, -175.0);
    glVertex3f(92.0, 20.0, -175.0);//
    glVertex3f(100.0, 20.0, -175.0);        //BERDIRI 11
    glVertex3f(100.0, 50.0, -175.0);
    glVertex3f(99.0, 50.0, -175.0);
    glVertex3f(99.0, 20.0, -175.0);//
    glVertex3f(100.0, 15.0, -181.0);        //KIRI - LANTAI 2
    glVertex3f(100.0, 20.0, -181.0);
    glVertex3f(30.0, 20.0, -181.0);
    glVertex3f(30.0, 15.0, -181.0);//
    glVertex3f(100.0, 5.0, -175.0);         //KIRI - LANTAI 2
    glVertex3f(100.0, 10.0, -175.0);
    glVertex3f(38.0, 10.0, -175.0);
    glVertex3f(38.0, 5.0, -175.0);//
    glVertex3f(100.0, 15.0, -175.0);        //KIRI - LANTAI 3
    glVertex3f(100.0, 25.0, -175.0);
    glVertex3f(30.0, 25.0, -175.0);
    glVertex3f(30.0, 15.0, -175.0);//
    glVertex3f(100.0, 30.0, -175.0);        //KIRI - LANTAI 3-4
    glVertex3f(100.0, 40.0, -175.0);
    glVertex3f(43.0, 40.0, -175.0);
    glVertex3f(43.0, 30.0, -175.0);
    glVertex3f(100.0, 45.0, -175.0);        //KIRI - LANTAI 4
    glVertex3f(100.0, 50.0, -175.0);
    glVertex3f(43.0, 50.0, -175.0);
    glVertex3f(43.0, 45.0, -175.0);
    glVertex3f(43.0, 30.0, -175.0);         //KIRI - LANTAI 4
    glVertex3f(43.0, 38.0, -175.0);
    glVertex3f(30.0, 38.0, -175.0);
    glVertex3f(30.0, 30.0, -175.0);
    glVertex3f(43.0, 40.0, -188.0);          //KIRI - LANTAI 4
    glVertex3f(43.0, 50.0, -188.0);
    glVertex3f(30.0, 50.0, -188.0);
    glVertex3f(30.0, 40.0, -188.0);

    glVertex3f(33.0, -10.0, -175.0);         //KIRI - PILAR 1
    glVertex3f(33.0, 5.0, -175.0);
    glVertex3f(30.0, 5.0, -175.0);
    glVertex3f(30.0, -10.0, -175.0);
    glVertex3f(33.0, -10.0, -178.0);         //KIRI - PILAR 1
    glVertex3f(33.0, 5.0, -178.0);
    glVertex3f(30.0, 5.0, -178.0);
    glVertex3f(30.0, -10.0, -178.0);
    glVertex3f(43.0, -10.0, -175.0);         //KIRI - PILAR 2
    glVertex3f(43.0, 5.0, -175.0);
    glVertex3f(40.0, 5.0, -175.0);
    glVertex3f(40.0, -10.0, -175.0);
    glVertex3f(43.0, -10.0, -178.0);         //KIRI - PILAR 2
    glVertex3f(43.0, 5.0, -178.0);
    glVertex3f(40.0, 5.0, -178.0);
    glVertex3f(40.0, -10.0, -178.0);
    glVertex3f(40.0, 5.0, -178.0);           //KIRI - PILAR 2
    glVertex3f(40.0, -10.0, -178.0);
    glVertex3f(40.0, -10.0, -175.0);
    glVertex3f(40.0, 5.0, -175.0);
    glVertex3f(43.0, 5.0, -178.0);           //KIRI - PILAR 2
    glVertex3f(43.0, -10.0, -178.0);
    glVertex3f(43.0, -10.0, -175.0);
    glVertex3f(43.0, 5.0, -175.0);
    glVertex3f(53.0, -10.0, -175.0);         //KIRI - PILAR 3
    glVertex3f(53.0, 5.0, -175.0);
    glVertex3f(50.0, 5.0, -175.0);
    glVertex3f(50.0, -10.0, -175.0);
    glVertex3f(53.0, -10.0, -178.0);         //KIRI - PILAR 3
    glVertex3f(53.0, 5.0, -178.0);
    glVertex3f(50.0, 5.0, -178.0);
    glVertex3f(50.0, -10.0, -178.0);
    glVertex3f(50.0, 5.0, -178.0);           //KIRI - PILAR 3
    glVertex3f(50.0, -10.0, -178.0);
    glVertex3f(50.0, -10.0, -175.0);
    glVertex3f(50.0, 5.0, -175.0);
    glVertex3f(53.0, 5.0, -178.0);           //KIRI - PILAR 3
    glVertex3f(53.0, -10.0, -178.0);
    glVertex3f(53.0, -10.0, -175.0);
    glVertex3f(53.0, 5.0, -175.0);
    glVertex3f(63.0, -10.0, -175.0);         //KIRI - PILAR 4
    glVertex3f(63.0, 5.0, -175.0);
    glVertex3f(60.0, 5.0, -175.0);
    glVertex3f(60.0, -10.0, -175.0);
    glVertex3f(63.0, -10.0, -178.0);         //KIRI - PILAR 4
    glVertex3f(63.0, 5.0, -178.0);
    glVertex3f(60.0, 5.0, -178.0);
    glVertex3f(60.0, -10.0, -178.0);
    glVertex3f(60.0, 5.0, -178.0);           //KIRI - PILAR 4
    glVertex3f(60.0, -10.0, -178.0);
    glVertex3f(60.0, -10.0, -175.0);
    glVertex3f(60.0, 5.0, -175.0);
    glVertex3f(63.0, 5.0, -178.0);           //KIRI - PILAR 4
    glVertex3f(63.0, -10.0, -178.0);
    glVertex3f(63.0, -10.0, -175.0);
    glVertex3f(63.0, 5.0, -175.0);
    glVertex3f(73.0, -10.0, -175.0);         //KIRI - PILAR 5
    glVertex3f(73.0, 5.0, -175.0);
    glVertex3f(70.0, 5.0, -175.0);
    glVertex3f(70.0, -10.0, -175.0);
    glVertex3f(73.0, -10.0, -178.0);         //KIRI - PILAR 5
    glVertex3f(73.0, 5.0, -178.0);
    glVertex3f(70.0, 5.0, -178.0);
    glVertex3f(70.0, -10.0, -178.0);
    glVertex3f(70.0, 5.0, -178.0);           //KIRI - PILAR 5
    glVertex3f(70.0, -10.0, -178.0);
    glVertex3f(70.0, -10.0, -175.0);
    glVertex3f(70.0, 5.0, -175.0);
    glVertex3f(73.0, 5.0, -178.0);           //KIRI - PILAR 5
    glVertex3f(73.0, -10.0, -178.0);
    glVertex3f(73.0, -10.0, -175.0);
    glVertex3f(73.0, 5.0, -175.0);
    glVertex3f(83.0, -10.0, -175.0);         //KIRI - PILAR 6
    glVertex3f(83.0, 5.0, -175.0);
    glVertex3f(80.0, 5.0, -175.0);
    glVertex3f(80.0, -10.0, -175.0);
    glVertex3f(83.0, -10.0, -178.0);         //KIRI - PILAR 6
    glVertex3f(83.0, 5.0, -178.0);
    glVertex3f(80.0, 5.0, -178.0);
    glVertex3f(80.0, -10.0, -178.0);
    glVertex3f(80.0, 5.0, -178.0);           //KIRI - PILAR 6
    glVertex3f(80.0, -10.0, -178.0);
    glVertex3f(80.0, -10.0, -175.0);
    glVertex3f(80.0, 5.0, -175.0);
    glVertex3f(83.0, 5.0, -178.0);           //KIRI - PILAR 6
    glVertex3f(83.0, -10.0, -178.0);
    glVertex3f(83.0, -10.0, -175.0);
    glVertex3f(83.0, 5.0, -175.0);
    glVertex3f(93.0, -10.0, -175.0);         //KIRI - PILAR 7
    glVertex3f(93.0, 5.0, -175.0);
    glVertex3f(90.0, 5.0, -175.0);
    glVertex3f(90.0, -10.0, -175.0);
    glVertex3f(93.0, -10.0, -178.0);         //KIRI - PILAR 7
    glVertex3f(93.0, 5.0, -178.0);
    glVertex3f(90.0, 5.0, -178.0);
    glVertex3f(90.0, -10.0, -178.0);
    glVertex3f(90.0, 5.0, -178.0);           //KIRI - PILAR 7
    glVertex3f(90.0, -10.0, -178.0);
    glVertex3f(90.0, -10.0, -175.0);
    glVertex3f(90.0, 5.0, -175.0);
    glVertex3f(93.0, 5.0, -178.0);           //KIRI - PILAR 7
    glVertex3f(93.0, -10.0, -178.0);
    glVertex3f(93.0, -10.0, -175.0);
    glVertex3f(93.0, 5.0, -175.0);

    glVertex3f(100.0, -10.0, -219.0);       //KANAN - LANTAI 1
    glVertex3f(100.0, -5.0, -219.0);
    glVertex3f(36.0, -5.0, -219.0);
    glVertex3f(36.0, -10.0, -219.0);//
    glVertex3f(38.0, -10.0, -219.0);        //BERDIRI - LANTAI 1-2 DARI KIRI 1
    glVertex3f(38.0, 20.0, -219.0);
    glVertex3f(36.0, 20.0, -219.0);
    glVertex3f(36.0, -10.0, -219.0);//
    glVertex3f(45.0, -10.0, -219.0);        //BERDIRI 2
    glVertex3f(45.0, 20.0, -219.0);
    glVertex3f(43.0, 20.0, -219.0);
    glVertex3f(43.0, -10.0, -219.0);//
    glVertex3f(52.0, -10.0, -219.0);        //BERDIRI 3
    glVertex3f(52.0, 20.0, -219.0);
    glVertex3f(50.0, 20.0, -219.0);
    glVertex3f(50.0, -10.0, -219.0);//
    glVertex3f(59.0, -10.0, -219.0);        //BERDIRI 4
    glVertex3f(59.0, 20.0, -219.0);
    glVertex3f(57.0, 20.0, -219.0);
    glVertex3f(57.0, -10.0, -219.0);//
    glVertex3f(66.0, -10.0, -219.0);        //BERDIRI 5
    glVertex3f(66.0, 20.0, -219.0);
    glVertex3f(64.0, 20.0, -219.0);
    glVertex3f(64.0, -10.0, -219.0);//
    glVertex3f(73.0, -10.0, -219.0);        //BERDIRI 6
    glVertex3f(73.0, 20.0, -219.0);
    glVertex3f(71.0, 20.0, -219.0);
    glVertex3f(71.0, -10.0, -219.0);//
    glVertex3f(80.0, -10.0, -219.0);        //BERDIRI 7
    glVertex3f(80.0, 20.0, -219.0);
    glVertex3f(78.0, 20.0, -219.0);
    glVertex3f(78.0, -10.0, -219.0);//
    glVertex3f(87.0, -10.0, -219.0);        //BERDIRI 8
    glVertex3f(87.0, 20.0, -219.0);
    glVertex3f(85.0, 20.0, -219.0);
    glVertex3f(85.0, -10.0, -219.0);//
    glVertex3f(94.0, -10.0, -219.0);        //BERDIRI 9
    glVertex3f(94.0, 20.0, -219.0);
    glVertex3f(92.0, 20.0, -219.0);
    glVertex3f(92.0, -10.0, -219.0);//
    glVertex3f(100.0, -10.0, -219.0);        //BERDIRI 9
    glVertex3f(100.0, 20.0, -219.0);
    glVertex3f(99.0, 20.0, -219.0);
    glVertex3f(99.0, -10.0, -219.0);//
    glVertex3f(100.0, 0.0, -219.0);         //KANAN - LANTAI 1-2
    glVertex3f(100.0, 10.0, -219.0);
    glVertex3f(36.0, 10.0, -219.0);
    glVertex3f(36.0, 0.0, -219.0);//
    glVertex3f(31.0, 20.0, -225.0);        //BERDIRI - LANTAI 2-4 DARI KIRI 1
    glVertex3f(31.0, 35.0, -225.0);
    glVertex3f(30.0, 35.0, -225.0);
    glVertex3f(30.0, 20.0, -225.0);//
    glVertex3f(38.0, 20.0, -225.0);        //BERDIRI 2
    glVertex3f(38.0, 35.0, -225.0);
    glVertex3f(36.0, 35.0, -225.0);
    glVertex3f(36.0, 20.0, -225.0);//
    glVertex3f(45.0, 20.0, -225.0);        //BERDIRI 3
    glVertex3f(45.0, 50.0, -225.0);
    glVertex3f(43.0, 50.0, -225.0);
    glVertex3f(43.0, 20.0, -225.0);//
    glVertex3f(52.0, 20.0, -225.0);        //BERDIRI 4
    glVertex3f(52.0, 50.0, -225.0);
    glVertex3f(50.0, 50.0, -225.0);
    glVertex3f(50.0, 20.0, -225.0);//
    glVertex3f(59.0, 20.0, -225.0);        //BERDIRI 5
    glVertex3f(59.0, 50.0, -225.0);
    glVertex3f(57.0, 50.0, -225.0);
    glVertex3f(57.0, 20.0, -225.0);//
    glVertex3f(66.0, 20.0, -225.0);        //BERDIRI 6
    glVertex3f(66.0, 50.0, -225.0);
    glVertex3f(64.0, 50.0, -225.0);
    glVertex3f(64.0, 20.0, -225.0);//
    glVertex3f(73.0, 20.0, -225.0);        //BERDIRI 7
    glVertex3f(73.0, 50.0, -225.0);
    glVertex3f(71.0, 50.0, -225.0);
    glVertex3f(71.0, 20.0, -225.0);//
    glVertex3f(80.0, 20.0, -225.0);        //BERDIRI 8
    glVertex3f(80.0, 50.0, -225.0);
    glVertex3f(78.0, 50.0, -225.0);
    glVertex3f(78.0, 20.0, -225.0);//
    glVertex3f(87.0, 20.0, -225.0);        //BERDIRI 9
    glVertex3f(87.0, 50.0, -225.0);
    glVertex3f(85.0, 50.0, -225.0);
    glVertex3f(85.0, 20.0, -225.0);//
    glVertex3f(94.0, 20.0, -225.0);        //BERDIRI 10
    glVertex3f(94.0, 50.0, -225.0);
    glVertex3f(92.0, 50.0, -225.0);
    glVertex3f(92.0, 20.0, -225.0);//
    glVertex3f(100.0, 20.0, -225.0);        //BERDIRI 11
    glVertex3f(100.0, 50.0, -225.0);
    glVertex3f(99.0, 50.0, -225.0);
    glVertex3f(99.0, 20.0, -225.0);//
    glVertex3f(100.0, 15.0, -219.0);         //KANAN - LANTAI 2
    glVertex3f(100.0, 20.0, -219.0);
    glVertex3f(36.0, 20.0, -219.0);
    glVertex3f(36.0, 15.0, -219.0);//
    glVertex3f(100.0, 5.0, -225.0);         //KANAN - LANTAI 2
    glVertex3f(100.0, 10.0, -225.0);
    glVertex3f(30.0, 10.0, -225.0);
    glVertex3f(30.0, 5.0, -225.0);//
    glVertex3f(100.0, 15.0, -225.0);        //KANAN - LANTAI 3
    glVertex3f(100.0, 25.0, -225.0);
    glVertex3f(30.0, 25.0, -225.0);
    glVertex3f(30.0, 15.0, -225.0);//
    glVertex3f(100.0, 30.0, -225.0);        //KANAN - LANTAI 4
    glVertex3f(100.0, 40.0, -225.0);
    glVertex3f(43.0, 40.0, -225.0);
    glVertex3f(43.0, 30.0, -225.0);
    glVertex3f(100.0, 45.0, -225.0);        //KANAN - LANTAI 4
    glVertex3f(100.0, 50.0, -225.0);
    glVertex3f(43.0, 50.0, -225.0);
    glVertex3f(43.0, 45.0, -225.0);
    glVertex3f(43.0, 30.0, -225.0);         //KANAN - LANTAI 4 PENDEK DI KIRI
    glVertex3f(43.0, 38.0, -225.0);
    glVertex3f(30.0, 38.0, -225.0);
    glVertex3f(30.0, 30.0, -225.0);
    glVertex3f(43.0, 35.0, -212.0);         //KANAN - LANTAI 4
    glVertex3f(43.0, 50.0, -212.0);
    glVertex3f(30.0, 50.0, -212.0);
    glVertex3f(30.0, 35.0, -212.0);

    glVertex3f(33.0, -10.0, -225.0);         //KANAN - PILAR 1
    glVertex3f(33.0, 5.0, -225.0);
    glVertex3f(30.0, 5.0, -225.0);
    glVertex3f(30.0, -10.0, -225.0);
    glVertex3f(33.0, -10.0, -222.0);         //KANAN - PILAR 1
    glVertex3f(33.0, 5.0, -222.0);
    glVertex3f(30.0, 5.0, -222.0);
    glVertex3f(30.0, -10.0, -222.0);
    glVertex3f(43.0, -10.0, -225.0);         //KANAN - PILAR 2
    glVertex3f(43.0, 5.0, -225.0);
    glVertex3f(40.0, 5.0, -225.0);
    glVertex3f(40.0, -10.0, -225.0);
    glVertex3f(43.0, -10.0, -222.0);         //KANAN - PILAR 2
    glVertex3f(43.0, 5.0, -222.0);
    glVertex3f(40.0, 5.0, -222.0);
    glVertex3f(40.0, -10.0, -222.0);
    glVertex3f(40.0, 5.0, -225.0);           //KANAN - PILAR 2
    glVertex3f(40.0, -10.0, -225.0);
    glVertex3f(40.0, -10.0, -222.0);
    glVertex3f(40.0, 5.0, -222.0);
    glVertex3f(43.0, 5.0, -225.0);           //KANAN - PILAR 2
    glVertex3f(43.0, -10.0, -225.0);
    glVertex3f(43.0, -10.0, -222.0);
    glVertex3f(43.0, 5.0, -222.0);
    glVertex3f(53.0, -10.0, -225.0);         //KANAN - PILAR 3
    glVertex3f(53.0, 5.0, -225.0);
    glVertex3f(50.0, 5.0, -225.0);
    glVertex3f(50.0, -10.0, -225.0);
    glVertex3f(53.0, -10.0, -222.0);         //KANAN - PILAR 3
    glVertex3f(53.0, 5.0, -222.0);
    glVertex3f(50.0, 5.0, -222.0);
    glVertex3f(50.0, -10.0, -222.0);
    glVertex3f(50.0, 5.0, -225.0);           //KANAN - PILAR 3
    glVertex3f(50.0, -10.0, -225.0);
    glVertex3f(50.0, -10.0, -222.0);
    glVertex3f(50.0, 5.0, -222.0);
    glVertex3f(53.0, 5.0, -225.0);           //KANAN - PILAR 3
    glVertex3f(53.0, -10.0, -225.0);
    glVertex3f(53.0, -10.0, -222.0);
    glVertex3f(53.0, 5.0, -222.0);
    glVertex3f(63.0, -10.0, -225.0);         //KANAN - PILAR 4
    glVertex3f(63.0, 5.0, -225.0);
    glVertex3f(60.0, 5.0, -225.0);
    glVertex3f(60.0, -10.0, -225.0);
    glVertex3f(63.0, -10.0, -222.0);         //KANAN - PILAR 4
    glVertex3f(63.0, 5.0, -222.0);
    glVertex3f(60.0, 5.0, -222.0);
    glVertex3f(60.0, -10.0, -222.0);
    glVertex3f(60.0, 5.0, -225.0);           //KANAN - PILAR 4
    glVertex3f(60.0, -10.0, -225.0);
    glVertex3f(60.0, -10.0, -222.0);
    glVertex3f(60.0, 5.0, -222.0);
    glVertex3f(63.0, 5.0, -225.0);           //KANAN - PILAR 4
    glVertex3f(63.0, -10.0, -225.0);
    glVertex3f(63.0, -10.0, -222.0);
    glVertex3f(63.0, 5.0, -222.0);
    glVertex3f(73.0, -10.0, -225.0);         //KANAN - PILAR 5
    glVertex3f(73.0, 5.0, -225.0);
    glVertex3f(70.0, 5.0, -225.0);
    glVertex3f(70.0, -10.0, -225.0);
    glVertex3f(73.0, -10.0, -222.0);         //KANAN - PILAR 5
    glVertex3f(73.0, 5.0, -222.0);
    glVertex3f(70.0, 5.0, -222.0);
    glVertex3f(70.0, -10.0, -222.0);
    glVertex3f(70.0, 5.0, -225.0);           //KANAN - PILAR 5
    glVertex3f(70.0, -10.0, -225.0);
    glVertex3f(70.0, -10.0, -222.0);
    glVertex3f(70.0, 5.0, -222.0);
    glVertex3f(73.0, 5.0, -225.0);           //KANAN - PILAR 5
    glVertex3f(73.0, -10.0, -225.0);
    glVertex3f(73.0, -10.0, -222.0);
    glVertex3f(73.0, 5.0, -222.0);
    glVertex3f(83.0, -10.0, -225.0);         //KANAN - PILAR 6
    glVertex3f(83.0, 5.0, -225.0);
    glVertex3f(80.0, 5.0, -225.0);
    glVertex3f(80.0, -10.0, -225.0);
    glVertex3f(83.0, -10.0, -222.0);         //KANAN - PILAR 6
    glVertex3f(83.0, 5.0, -222.0);
    glVertex3f(80.0, 5.0, -222.0);
    glVertex3f(80.0, -10.0, -222.0);
    glVertex3f(80.0, 5.0, -225.0);           //KANAN - PILAR 6
    glVertex3f(80.0, -10.0, -225.0);
    glVertex3f(80.0, -10.0, -222.0);
    glVertex3f(80.0, 5.0, -222.0);
    glVertex3f(83.0, 5.0, -225.0);           //KANAN - PILAR 6
    glVertex3f(83.0, -10.0, -225.0);
    glVertex3f(83.0, -10.0, -222.0);
    glVertex3f(83.0, 5.0, -222.0);
    glVertex3f(93.0, -10.0, -225.0);         //KANAN - PILAR 7
    glVertex3f(93.0, 5.0, -225.0);
    glVertex3f(90.0, 5.0, -225.0);
    glVertex3f(90.0, -10.0, -225.0);
    glVertex3f(93.0, -10.0, -222.0);         //KANAN - PILAR 7
    glVertex3f(93.0, 5.0, -222.0);
    glVertex3f(90.0, 5.0, -222.0);
    glVertex3f(90.0, -10.0, -222.0);
    glVertex3f(90.0, 5.0, -225.0);           //KANAN - PILAR 7
    glVertex3f(90.0, -10.0, -225.0);
    glVertex3f(90.0, -10.0, -222.0);
    glVertex3f(90.0, 5.0, -222.0);
    glVertex3f(93.0, 5.0, -225.0);           //KANAN - PILAR 7
    glVertex3f(93.0, -10.0, -225.0);
    glVertex3f(93.0, -10.0, -222.0);
    glVertex3f(93.0, 5.0, -222.0);

    glVertex3f(36.0, -5.0, -197.0);         //DEPAN - LANTAI 1
    glVertex3f(36.0, -10.0, -197.0);
    glVertex3f(36.0, -10.0, -181.0);
    glVertex3f(36.0, -5.0, -181.0);
    glVertex3f(36.0, -5.0, -219.0);         //DEPAN - LANTAI 1
    glVertex3f(36.0, -10.0, -219.0);
    glVertex3f(36.0, -10.0, -203.0);
    glVertex3f(36.0, -5.0, -203.0);
    glVertex3f(36.0, 20.0, -183.0);         //BERDIRI - LANTAI 1-2 DARI KIRI 1
    glVertex3f(36.0, -10.0, -183.0);
    glVertex3f(36.0, -10.0, -181.0);
    glVertex3f(36.0, 20.0, -181.0);
    glVertex3f(36.0, 20.0, -190.0);         //BERDIRI 2
    glVertex3f(36.0, -10.0, -190.0);
    glVertex3f(36.0, -10.0, -188.0);
    glVertex3f(36.0, 20.0, -188.0);
    glVertex3f(36.0, 20.0, -197.0);         //BERDIRI 3
    glVertex3f(36.0, -10.0, -197.0);
    glVertex3f(36.0, -10.0, -195.0);
    glVertex3f(36.0, 20.0, -195.0);
    glVertex3f(36.0, 20.0, -205.0);         //BERDIRI 4
    glVertex3f(36.0, -10.0, -205.0);
    glVertex3f(36.0, -10.0, -203.0);
    glVertex3f(36.0, 20.0, -203.0);
    glVertex3f(36.0, 20.0, -212.0);         //BERDIRI 5
    glVertex3f(36.0, -10.0, -212.0);
    glVertex3f(36.0, -10.0, -210.0);
    glVertex3f(36.0, 20.0, -210.0);
    glVertex3f(36.0, 20.0, -219.0);         //BERDIRI 6
    glVertex3f(36.0, -10.0, -219.0);
    glVertex3f(36.0, -10.0, -217.0);
    glVertex3f(36.0, 20.0, -217.0);
    glVertex3f(36.0, 10.0, -219.0);         //DEPAN - LANTAI 2
    glVertex3f(36.0, 0.0, -219.0);
    glVertex3f(36.0, 0.0, -181.0);
    glVertex3f(36.0, 10.0, -181.0);
    glVertex3f(30.0, 35.0, -176.0);         //BERDIRI - LANTAI 2-4 DARI KIRI 1
    glVertex3f(30.0, 20.0, -176.0);
    glVertex3f(30.0, 20.0, -175.0);
    glVertex3f(30.0, 35.0, -175.0);
    glVertex3f(30.0, 35.0, -183.0);         //BERDIRI 2
    glVertex3f(30.0, 20.0, -183.0);
    glVertex3f(30.0, 20.0, -181.0);
    glVertex3f(30.0, 35.0, -181.0);
    glVertex3f(30.0, 50.0, -190.0);         //BERDIRI 3
    glVertex3f(30.0, 20.0, -190.0);
    glVertex3f(30.0, 20.0, -188.0);
    glVertex3f(30.0, 50.0, -188.0);
    glVertex3f(30.0, 50.0, -197.0);         //BERDIRI 4
    glVertex3f(30.0, 20.0, -197.0);
    glVertex3f(30.0, 20.0, -195.0);
    glVertex3f(30.0, 50.0, -195.0);
    glVertex3f(30.0, 50.0, -205.0);         //BERDIRI 5
    glVertex3f(30.0, 20.0, -205.0);
    glVertex3f(30.0, 20.0, -203.0);
    glVertex3f(30.0, 50.0, -203.0);
    glVertex3f(30.0, 50.0, -212.0);         //BERDIRI 6
    glVertex3f(30.0, 20.0, -212.0);
    glVertex3f(30.0, 20.0, -210.0);
    glVertex3f(30.0, 50.0, -210.0);
    glVertex3f(30.0, 35.0, -219.0);         //BERDIRI 7
    glVertex3f(30.0, 20.0, -219.0);
    glVertex3f(30.0, 20.0, -217.0);
    glVertex3f(30.0, 35.0, -217.0);
    glVertex3f(30.0, 35.0, -225.0);         //BERDIRI 8
    glVertex3f(30.0, 20.0, -225.0);
    glVertex3f(30.0, 20.0, -224.0);
    glVertex3f(30.0, 35.0, -224.0);
    glVertex3f(36.0, 20.0, -219.0);         //DEPAN - LANTAI 2
    glVertex3f(36.0, 15.0, -219.0);
    glVertex3f(36.0, 15.0, -181.0);
    glVertex3f(36.0, 20.0, -181.0);
    glVertex3f(30.0, 10.0, -225.0);         //DEPAN - LANTAI 2
    glVertex3f(30.0, 5.0, -225.0);
    glVertex3f(30.0, 5.0, -175.0);
    glVertex3f(30.0, 10.0, -175.0);
    glVertex3f(30.0, 25.0, -225.0);         //DEPAN - LANTAI 3
    glVertex3f(30.0, 15.0, -225.0);
    glVertex3f(30.0, 15.0, -175.0);
    glVertex3f(30.0, 25.0, -175.0);
    glVertex3f(30.0, 40.0, -210.0);         //DEPAN - LANTAI 4
    glVertex3f(30.0, 30.0, -210.0);
    glVertex3f(30.0, 30.0, -190.0);
    glVertex3f(30.0, 40.0, -190.0);
    glVertex3f(30.0, 50.0, -210.0);         //DEPAN - LANTAI 4
    glVertex3f(30.0, 45.0, -210.0);
    glVertex3f(30.0, 45.0, -190.0);
    glVertex3f(30.0, 50.0, -190.0);
    glVertex3f(30.0, 37.0, -190.0);         //DEPAN - LANTAI 4
    glVertex3f(30.0, 30.0, -190.0);
    glVertex3f(30.0, 30.0, -175.0);
    glVertex3f(30.0, 37.0, -175.0);
    glVertex3f(30.0, 37.0, -225.0);         //DEPAN - LANTAI 4
    glVertex3f(30.0, 30.0, -225.0);
    glVertex3f(30.0, 30.0, -210.0);
    glVertex3f(30.0, 37.0, -210.0);
    glVertex3f(43.0, 50.0, -225.0);         //DEPAN - LANTAI 4 KANAN
    glVertex3f(43.0, 35.0, -225.0);
    glVertex3f(43.0, 35.0, -212.0);
    glVertex3f(43.0, 50.0, -212.0);
    glVertex3f(43.0, 50.0, -188.0);         //DEPAN - LANTAI 4 KIRI
    glVertex3f(43.0, 35.0, -188.0);
    glVertex3f(43.0, 35.0, -175.0);
    glVertex3f(43.0, 50.0, -175.0);

    glVertex3f(30.0, 5.0, -178.0);         //DEPAN - PILAR 1
    glVertex3f(30.0, -10.0, -178.0);
    glVertex3f(30.0, -10.0, -175.0);
    glVertex3f(30.0, 5.0, -175.0);
    glVertex3f(33.0, 5.0, -178.0);         //DEPAN - PILAR 1
    glVertex3f(33.0, -10.0, -178.0);
    glVertex3f(33.0, -10.0, -175.0);
    glVertex3f(33.0, 5.0, -175.0);
    glVertex3f(30.0, 5.0, -188.0);         //DEPAN - PILAR 2
    glVertex3f(30.0, -10.0, -188.0);
    glVertex3f(30.0, -10.0, -185.0);
    glVertex3f(30.0, 5.0, -185.0);
    glVertex3f(33.0, 5.0, -188.0);         //DEPAN - PILAR 2
    glVertex3f(33.0, -10.0, -188.0);
    glVertex3f(33.0, -10.0, -185.0);
    glVertex3f(33.0, 5.0, -185.0);
    glVertex3f(33.0, -10.0, -185.0);       //DEPAN - PILAR 2
    glVertex3f(33.0, 5.0, -185.0);
    glVertex3f(30.0, 5.0, -185.0);
    glVertex3f(30.0, -10.0, -185.0);
    glVertex3f(33.0, -10.0, -188.0);       //DEPAN - PILAR 2
    glVertex3f(33.0, 5.0, -188.0);
    glVertex3f(30.0, 5.0, -188.0);
    glVertex3f(30.0, -10.0, -188.0);
    glVertex3f(30.0, 5.0, -197.0);         //DEPAN - PILAR 3
    glVertex3f(30.0, -10.0, -197.0);
    glVertex3f(30.0, -10.0, -194.0);
    glVertex3f(30.0, 5.0, -194.0);
    glVertex3f(33.0, 5.0, -197.0);         //DEPAN - PILAR 3
    glVertex3f(33.0, -10.0, -197.0);
    glVertex3f(33.0, -10.0, -194.0);
    glVertex3f(33.0, 5.0, -194.0);
    glVertex3f(33.0, -10.0, -194.0);       //DEPAN - PILAR 3
    glVertex3f(33.0, 5.0, -194.0);
    glVertex3f(30.0, 5.0, -194.0);
    glVertex3f(30.0, -10.0, -194.0);
    glVertex3f(33.0, -10.0, -197.0);       //DEPAN - PILAR 3
    glVertex3f(33.0, 5.0, -197.0);
    glVertex3f(30.0, 5.0, -197.0);
    glVertex3f(30.0, -10.0, -197.0);
    glVertex3f(30.0, 5.0, -206.0);         //DEPAN - PILAR 4
    glVertex3f(30.0, -10.0, -206.0);
    glVertex3f(30.0, -10.0, -203.0);
    glVertex3f(30.0, 5.0, -203.0);
    glVertex3f(33.0, 5.0, -206.0);         //DEPAN - PILAR 4
    glVertex3f(33.0, -10.0, -206.0);
    glVertex3f(33.0, -10.0, -203.0);
    glVertex3f(33.0, 5.0, -203.0);
    glVertex3f(33.0, -10.0, -203.0);       //DEPAN - PILAR 4
    glVertex3f(33.0, 5.0, -203.0);
    glVertex3f(30.0, 5.0, -203.0);
    glVertex3f(30.0, -10.0, -203.0);
    glVertex3f(33.0, -10.0, -206.0);       //DEPAN - PILAR 4
    glVertex3f(33.0, 5.0, -206.0);
    glVertex3f(30.0, 5.0, -206.0);
    glVertex3f(30.0, -10.0, -206.0);
    glVertex3f(30.0, 5.0, -215.0);         //DEPAN - PILAR 5
    glVertex3f(30.0, -10.0, -215.0);
    glVertex3f(30.0, -10.0, -212.0);
    glVertex3f(30.0, 5.0, -212.0);
    glVertex3f(33.0, 5.0, -215.0);         //DEPAN - PILAR 5
    glVertex3f(33.0, -10.0, -215.0);
    glVertex3f(33.0, -10.0, -212.0);
    glVertex3f(33.0, 5.0, -212.0);
    glVertex3f(33.0, -10.0, -212.0);       //DEPAN - PILAR 5
    glVertex3f(33.0, 5.0, -212.0);
    glVertex3f(30.0, 5.0, -212.0);
    glVertex3f(30.0, -10.0, -212.0);
    glVertex3f(33.0, -10.0, -215.0);       //DEPAN - PILAR 5
    glVertex3f(33.0, 5.0, -215.0);
    glVertex3f(30.0, 5.0, -215.0);
    glVertex3f(30.0, -10.0, -215.0);
    glVertex3f(30.0, 5.0, -225.0);         //DEPAN - PILAR 6
    glVertex3f(30.0, -10.0, -225.0);
    glVertex3f(30.0, -10.0, -222.0);
    glVertex3f(30.0, 5.0, -222.0);
    glVertex3f(33.0, 5.0, -225.0);         //DEPAN - PILAR 6
    glVertex3f(33.0, -10.0, -225.0);
    glVertex3f(33.0, -10.0, -222.0);
    glVertex3f(33.0, 5.0, -222.0);
    glVertex3f(33.0, -10.0, -222.0);       //DEPAN - PILAR 6
    glVertex3f(33.0, 5.0, -222.0);
    glVertex3f(30.0, 5.0, -222.0);
    glVertex3f(30.0, -10.0, -222.0);
    glVertex3f(33.0, -10.0, -225.0);       //DEPAN - PILAR 6
    glVertex3f(33.0, 5.0, -225.0);
    glVertex3f(30.0, 5.0, -225.0);
    glVertex3f(30.0, -10.0, -225.0);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.5, 0.5, 0.5);                 //LANTAI - 1
    glVertex3f(30, -9.9, -225.0);
    glVertex3f(100, -9.9, -225.0);
    glVertex3f(100, -9.9, -175.0);
    glVertex3f(30, -9.9, -175.0);
    glVertex3f(30, 5.0, -225.0);            //LANTAI - 2
    glVertex3f(100, 5.0, -225.0);
    glVertex3f(100, 5.0, -175.0);
    glVertex3f(30, 5.0, -175.0);
    glVertex3f(30, 20.0, -225.0);            //LANTAI - 3
    glVertex3f(100, 20.0, -225.0);
    glVertex3f(100, 20.0, -175.0);
    glVertex3f(30, 20.0, -175.0);
    glVertex3f(43, 35.0, -225.0);            //LANTAI - 4
    glVertex3f(100, 35.0, -225.0);
    glVertex3f(100, 35.0, -175.0);
    glVertex3f(43, 35.0, -175.0);
    glVertex3f(30, 50.0, -235.0);            //LANTAI - 4 1
    glVertex3f(100, 50.0, -235.0);
    glVertex3f(100, 50.0, -165.0);
    glVertex3f(30, 50.0, -165.0);
    glVertex3f(20, 50.0, -215.0);            //LANTAI - 4 2
    glVertex3f(43, 50.0, -215.0);
    glVertex3f(43, 50.0, -185.0);
    glVertex3f(20, 50.0, -185.0);
    glVertex3f(30, 35.0, -212.0);            //LANTAI - 4
    glVertex3f(43, 35.0, -212.0);
    glVertex3f(43, 35.0, -188.0);
    glVertex3f(30, 35.0, -188.0);
    glVertex3f(30, 50.0, -212.0);            //LANTAI - 4
    glVertex3f(43, 50.0, -212.0);
    glVertex3f(43, 50.0, -188.0);
    glVertex3f(30, 50.0, -188.0);
    glEnd();

    glBegin(GL_QUADS);                       //PINTU
    glColor3f(0.66, 0.40, 0.0);
    glVertex3f(36.0, 0.0, -203.0);
    glVertex3f(36.0, -10.0, -203.0);
    glVertex3f(36.0, -10.0, -197.0);
    glVertex3f(36.0, 0.0, -197.0);
    glEnd();

    glBegin(GL_QUADS);                      //ATAP
    glColor3f(0.2, 0.2, 0.2);               //DEPAN - BAWAH PANJANG
    glVertex3f(30.0, 40.0, -212.0);
    glVertex3f(20.0, 30.0, -212.0);
    glVertex3f(20.0, 30.0, -188.0);
    glVertex3f(30.0, 40.0, -188.0);
    glEnd();
    glBegin(GL_POLYGON);                    //DEPAN - BAWAH KIRI
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(43, 50.0, -188.0);
    glVertex3f(30, 40.0, -188.0);
    glVertex3f(20, 30.0, -188.0);
    glVertex3f(20, 30.0, -175.0);
    glVertex3f(30, 40.0, -175.0);
    glEnd();
    glBegin(GL_POLYGON);                    //DEPAN - BAWAH UJUNG KIRI
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(30.0, 40.0, -175.0);
    glVertex3f(20.0, 30.0, -175.0);
    glVertex3f(20.0, 30.0, -165.0);
    glVertex3f(30.0, 30.0, -165.0);
    glEnd();
    glBegin(GL_POLYGON);                    //DEPAN - BAWAH KANAN
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(43, 50.0, -212.0);
    glVertex3f(30, 40.0, -212.0);
    glVertex3f(20, 30.0, -212.0);
    glVertex3f(20, 30.0, -225.0);
    glVertex3f(30, 40.0, -225.0);
    glEnd();
    glBegin(GL_POLYGON);                    //DEPAN - BAWAH UJUNG KANAN
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(30.0, 40.0, -225.0);
    glVertex3f(20.0, 30.0, -225.0);
    glVertex3f(20.0, 30.0, -235.0);
    glVertex3f(30.0, 30.0, -235.0);
    glEnd();
    glBegin(GL_POLYGON);                    //KIRI - KANAN
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(43.0, 50.0, -188.0);
    glVertex3f(30.0, 40.0, -175.0);
    glVertex3f(30.0, 30.0, -165.0);
    glVertex3f(43.0, 30.0, -165.0);
    glVertex3f(43.0, 40.0, -175.0);
    glEnd();
    glBegin(GL_QUADS);                      //KIRI - SISI SIRIP PANJANG TENGAH
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(43, 40.0, -175.0);
    glVertex3f(100, 40.0, -175.0);
    glVertex3f(100, 30.0, -165.0);
    glVertex3f(43, 30.0, -165.0);
    glEnd();
    glBegin(GL_QUADS);                      //KIRI - SISI SIRIP PANJANG ATAS
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(45, 70.0, -190.0);
    glVertex3f(100, 70.0, -190.0);
    glVertex3f(100, 50.0, -165.0);
    glVertex3f(30, 50.0, -165.0);
    glEnd();
    glBegin(GL_QUADS);                      //KIRI - SISI SIRIP PENDEK BAWAH
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(30, 60.0, -193.0);
    glVertex3f(40, 60.0, -193.0);
    glVertex3f(30, 50.0, -185.0);
    glVertex3f(20, 50.0, -185.0);
    glEnd();
    glBegin(GL_POLYGON);                    //KIRI - SIRIP BESAR ATAS
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(55.0, 90.0, -195.0);
    glVertex3f(45.0, 110.0, -200.0);
    glVertex3f(100.0, 110.0, -200.0);
    glVertex3f(100.0, 70.0, -190.0);
    glVertex3f(45.0, 70.0, -190.0);
    glEnd();
    glBegin(GL_POLYGON);                    //KIRI - SIRIP KECIL BAWAH
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(40.0, 75.0, -196.0);
    glVertex3f(30.0, 90.0, -200.0);
    glVertex3f(55.0, 90.0, -200.0);
    glVertex3f(40.0, 60.0, -192.0);
    glVertex3f(30.0, 60.0, -192.0);
    glEnd();
    glBegin(GL_POLYGON);                    //KANAN - KIRI
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(43.0, 50.0, -212.0);
    glVertex3f(43.0, 40.0, -225.0);
    glVertex3f(43.0, 30.0, -235.0);
    glVertex3f(30.0, 30.0, -235.0);
    glVertex3f(30.0, 40.0, -225.0);
    glEnd();
    glBegin(GL_POLYGON);                    //KANAN - SISI SIRIP PANJANG TENGAH
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(43, 30.0, -235.0);
    glVertex3f(100, 30.0, -235.0);
    glVertex3f(100, 40.0, -225.0);
    glVertex3f(43, 40.0, -225.0);
    glEnd();
    glBegin(GL_POLYGON);                    //KANAN - SISI SIRIP PANJANG ATAS
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(30, 50.0, -235.0);
    glVertex3f(100, 50.0, -235.0);
    glVertex3f(100, 70.0, -210.0);
    glVertex3f(45, 70.0, -210.0);
    glEnd();
    glBegin(GL_POLYGON);                    //KANAN - SISI SIRIP PENDEK BAWAH
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(20, 50.0, -215.0);
    glVertex3f(30, 50.0, -215.0);
    glVertex3f(40, 60.0, -207.0);
    glVertex3f(30, 60.0, -207.0);
    glEnd();
    glBegin(GL_POLYGON);                    //KANAN - SIRIP BESAR ATAS
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(55.0, 90.0, -205.0);
    glVertex3f(45.0, 110.0, -200.0);
    glVertex3f(100.0, 110.0, -200.0);
    glVertex3f(100.0, 70.0, -210.0);
    glVertex3f(45.0, 70.0, -210.0);
    glEnd();
    glBegin(GL_POLYGON);                    //KANAN - SIRIP KECIL BAWAH
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(40.0, 75.0, -204.0);
    glVertex3f(30.0, 90.0, -200.0);
    glVertex3f(55.0, 90.0, -200.0);
    glVertex3f(40.0, 60.0, -208.0);
    glVertex3f(30.0, 60.0, -208.0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(45.0, 70.0, -210.0);         //DEPAN - PENUTUP SIRIP BESAR BAWAH
    glVertex3f(55.0, 90.0, -205.0);
    glVertex3f(55.0, 90.0, -195.0);
    glVertex3f(45.0, 70.0, -190.0);
    glVertex3f(30.0, 50.0, -165.0);
    glVertex3f(30.0, 50.0, -235.0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(55.0, 90.0, -195.0);         //DEPAN - PENUTUP SIRIP BESAR ATAS
    glVertex3f(55.0, 90.0, -205.0);
    glVertex3f(45.0, 110.0, -200.0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(40.0, 75.0, -204.0);         //DEPAN - PENUTUP SIRIP KECIL BAWAH
    glVertex3f(40.0, 75.0, -196.0);
    glVertex3f(30.0, 60.0, -182.0);
    glVertex3f(20.0, 50.0, -185.0);
    glVertex3f(20.0, 50.0, -215.0);
    glVertex3f(30.0, 60.0, -208.0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(40.0, 75.0, -204.0);         //DEPAN - PENUTUP SIRIP KECIL ATAS
    glVertex3f(30.0, 90.0, -200.0);
    glVertex3f(40.0, 75.0, -196.0);
    glEnd();
    //SAMPAI SINI

    //UPDATE
    //UPDATE

    glBegin(GL_QUADS);
    glColor3f(0.5, 0.5, 0.5);
    glVertex3f(-38.0, -9.9, -95.0);         //JALAN PENGHUBUNG GEDUNG 1 DAN 2
    glVertex3f(-30.0, -9.9, -95.0);
    glVertex3f(-30.0, -9.9, -175.0);
    glVertex3f(-38.0, -9.9, -175.0);
    glVertex3f(-38.0, 5, -95.0);            //JALAN PENGHUBUNG GEDUNG 1 DAN 2
    glVertex3f(-30.0, 5, -95.0);
    glVertex3f(-30.0, 5, -175.0);
    glVertex3f(-38.0, 5, -175.0);
    glVertex3f(38.0, -9.9, -95.0);          //JALAN PENGHUBUNG GEDUNG 3 DAN 4
    glVertex3f(30.0, -9.9, -95.0);
    glVertex3f(30.0, -9.9, -175.0);
    glVertex3f(38.0, -9.9, -175.0);
    glVertex3f(38.0, 5, -95.0);             //JALAN PENGHUBUNG GEDUNG 3 DAN 4
    glVertex3f(30.0, 5, -95.0);
    glVertex3f(30.0, 5, -175.0);
    glVertex3f(38.0, 5, -175.0);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-30.0, 10.0, -175.0);         //DINDING JALAN PENGHUBUNG GEDUNG 1 DAN 2 - DEPAN
    glVertex3f(-30.0, 5.0, -175.0);
    glVertex3f(-30.0, 5.0, -95.0);
    glVertex3f(-30.0, 10.0, -95.0);
    glVertex3f(-38.0, 10.0, -175.0);         //DINDING JALAN PENGHUBUNG GEDUNG 1 DAN 2 - BELAKANG
    glVertex3f(-38.0, 5.0, -175.0);
    glVertex3f(-38.0, 5.0, -95.0);
    glVertex3f(-38.0, 10.0, -95.0);
    glVertex3f(30.0, 10.0, -175.0);         //DINDING JALAN PENGHUBUNG GEDUNG 1 DAN 2 - DEPAN
    glVertex3f(30.0, 5.0, -175.0);
    glVertex3f(30.0, 5.0, -95.0);
    glVertex3f(30.0, 10.0, -95.0);
    glVertex3f(38.0, 10.0, -175.0);         //DINDING JALAN PENGHUBUNG GEDUNG 1 DAN 2 - BELAKANG
    glVertex3f(38.0, 5.0, -175.0);
    glVertex3f(38.0, 5.0, -95.0);
    glVertex3f(38.0, 10.0, -95.0);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-30.0, 5.0, -104.0);         //PENGHUBUNG 1-2 - PILAR 1
    glVertex3f(-30.0, -10.0, -104.0);
    glVertex3f(-30.0, -10.0, -102.0);
    glVertex3f(-30.0, 5.0, -102.0);
    glVertex3f(-32.0, 5.0, -104.0);         //PENGHUBUNG 1-2 - PILAR 1
    glVertex3f(-32.0, -10.0, -104.0);
    glVertex3f(-32.0, -10.0, -102.0);
    glVertex3f(-32.0, 5.0, -102.0);
    glVertex3f(-32.0, -10.0, -102.0);        //PENGHUBUNG 1-2 - PILAR 1
    glVertex3f(-32.0, 5.0, -102.0);
    glVertex3f(-30.0, 5.0, -102.0);
    glVertex3f(-30.0, -10.0, -102.0);
    glVertex3f(-32.0, -10.0, -104.0);        //PENGHUBUNG 1-2 - PILAR 1
    glVertex3f(-32.0, 5.0, -104.0);
    glVertex3f(-30.0, 5.0, -104.0);
    glVertex3f(-30.0, -10.0, -104.0);
    glVertex3f(-30.0, 5.0, -113.0);          //PENGHUBUNG 1-2 - PILAR 2
    glVertex3f(-30.0, -10.0, -113.0);
    glVertex3f(-30.0, -10.0, -111.0);
    glVertex3f(-30.0, 5.0, -111.0);
    glVertex3f(-32.0, 5.0, -113.0);          //PENGHUBUNG 1-2 - PILAR 2
    glVertex3f(-32.0, -10.0, -113.0);
    glVertex3f(-32.0, -10.0, -111.0);
    glVertex3f(-32.0, 5.0, -111.0);
    glVertex3f(-32.0, -10.0, -111.0);        //PENGHUBUNG 1-2 - PILAR 2
    glVertex3f(-32.0, 5.0, -111.0);
    glVertex3f(-30.0, 5.0, -111.0);
    glVertex3f(-30.0, -10.0, -111.0);
    glVertex3f(-32.0, -10.0, -113.0);        //PENGHUBUNG 1-2 - PILAR 2
    glVertex3f(-32.0, 5.0, -113.0);
    glVertex3f(-30.0, 5.0, -113.0);
    glVertex3f(-30.0, -10.0, -113.0);
    glVertex3f(-30.0, 5.0, -122.0);         //PENGHUBUNG 1-2 - PILAR 3
    glVertex3f(-30.0, -10.0, -122.0);
    glVertex3f(-30.0, -10.0, -120.0);
    glVertex3f(-30.0, 5.0, -120.0);
    glVertex3f(-32.0, 5.0, -122.0);         //PENGHUBUNG 1-2 - PILAR 3
    glVertex3f(-32.0, -10.0, -122.0);
    glVertex3f(-32.0, -10.0, -120.0);
    glVertex3f(-32.0, 5.0, -120.0);
    glVertex3f(-32.0, -10.0, -120.0);       //PENGHUBUNG 1-2 - PILAR 3
    glVertex3f(-32.0, 5.0, -120.0);
    glVertex3f(-30.0, 5.0, -120.0);
    glVertex3f(-30.0, -10.0, -120.0);
    glVertex3f(-32.0, -10.0, -122.0);       //PENGHUBUNG 1-2 - PILAR 3
    glVertex3f(-32.0, 5.0, -122.0);
    glVertex3f(-30.0, 5.0, -122.0);
    glVertex3f(-30.0, -10.0, -122.0);
    glVertex3f(-30.0, 5.0, -131.0);         //PENGHUBUNG 1-2 - PILAR 4
    glVertex3f(-30.0, -10.0, -131.0);
    glVertex3f(-30.0, -10.0, -129.0);
    glVertex3f(-30.0, 5.0, -129.0);
    glVertex3f(-32.0, 5.0, -131.0);         //PENGHUBUNG 1-2 - PILAR 4
    glVertex3f(-32.0, -10.0, -131.0);
    glVertex3f(-32.0, -10.0, -129.0);
    glVertex3f(-32.0, 5.0, -129.0);
    glVertex3f(-32.0, -10.0, -129.0);       //PENGHUBUNG 1-2 - PILAR 4
    glVertex3f(-32.0, 5.0, -129.0);
    glVertex3f(-30.0, 5.0, -129.0);
    glVertex3f(-30.0, -10.0, -129.0);
    glVertex3f(-32.0, -10.0, -131.0);       //PENGHUBUNG 1-2 - PILAR 4
    glVertex3f(-32.0, 5.0, -131.0);
    glVertex3f(-30.0, 5.0, -131.0);
    glVertex3f(-30.0, -10.0, -131.0);
    glVertex3f(-30.0, 5.0, -140.0);         //PENGHUBUNG 1-2 - PILAR 5
    glVertex3f(-30.0, -10.0, -140.0);
    glVertex3f(-30.0, -10.0, -138.0);
    glVertex3f(-30.0, 5.0, -138.0);
    glVertex3f(-32.0, 5.0, -140.0);         //PENGHUBUNG 1-2 - PILAR 5
    glVertex3f(-32.0, -10.0, -140.0);
    glVertex3f(-32.0, -10.0, -138.0);
    glVertex3f(-32.0, 5.0, -138.0);
    glVertex3f(-32.0, -10.0, -138.0);       //PENGHUBUNG 1-2 - PILAR 5
    glVertex3f(-32.0, 5.0, -138.0);
    glVertex3f(-30.0, 5.0, -138.0);
    glVertex3f(-30.0, -10.0, -138.0);
    glVertex3f(-32.0, -10.0, -140.0);       //PENGHUBUNG 1-2 - PILAR 5
    glVertex3f(-32.0, 5.0, -140.0);
    glVertex3f(-30.0, 5.0, -140.0);
    glVertex3f(-30.0, -10.0, -140.0);
    glVertex3f(-30.0, 5.0, -149.0);         //PENGHUBUNG 1-2 - PILAR 6
    glVertex3f(-30.0, -10.0, -149.0);
    glVertex3f(-30.0, -10.0, -147.0);
    glVertex3f(-30.0, 5.0, -147.0);
    glVertex3f(-32.0, 5.0, -149.0);         //PENGHUBUNG 1-2 - PILAR 6
    glVertex3f(-32.0, -10.0, -149.0);
    glVertex3f(-32.0, -10.0, -147.0);
    glVertex3f(-32.0, 5.0, -147.0);
    glVertex3f(-32.0, -10.0, -147.0);       //PENGHUBUNG 1-2 - PILAR 6
    glVertex3f(-32.0, 5.0, -147.0);
    glVertex3f(-30.0, 5.0, -147.0);
    glVertex3f(-30.0, -10.0, -147.0);
    glVertex3f(-32.0, -10.0, -149.0);       //PENGHUBUNG 1-2 - PILAR 6
    glVertex3f(-32.0, 5.0, -149.0);
    glVertex3f(-30.0, 5.0, -149.0);
    glVertex3f(-30.0, -10.0, -149.0);
    glVertex3f(-30.0, 5.0, -158.0);         //PENGHUBUNG 1-2 - PILAR 7
    glVertex3f(-30.0, -10.0, -158.0);
    glVertex3f(-30.0, -10.0, -156.0);
    glVertex3f(-30.0, 5.0, -156.0);
    glVertex3f(-32.0, 5.0, -158.0);         //PENGHUBUNG 1-2 - PILAR 7
    glVertex3f(-32.0, -10.0, -158.0);
    glVertex3f(-32.0, -10.0, -156.0);
    glVertex3f(-32.0, 5.0, -156.0);
    glVertex3f(-32.0, -10.0, -156.0);       //PENGHUBUNG 1-2 - PILAR 7
    glVertex3f(-32.0, 5.0, -156.0);
    glVertex3f(-30.0, 5.0, -156.0);
    glVertex3f(-30.0, -10.0, -156.0);
    glVertex3f(-32.0, -10.0, -158.0);       //PENGHUBUNG 1-2 - PILAR 7
    glVertex3f(-32.0, 5.0, -158.0);
    glVertex3f(-30.0, 5.0, -158.0);
    glVertex3f(-30.0, -10.0, -158.0);
    glVertex3f(-30.0, 5.0, -167.0);         //PENGHUBUNG 1-2 - PILAR 8
    glVertex3f(-30.0, -10.0, -167.0);
    glVertex3f(-30.0, -10.0, -165.0);
    glVertex3f(-30.0, 5.0, -165.0);
    glVertex3f(-32.0, 5.0, -167.0);         //PENGHUBUNG 1-2 - PILAR 8
    glVertex3f(-32.0, -10.0, -167.0);
    glVertex3f(-32.0, -10.0, -165.0);
    glVertex3f(-32.0, 5.0, -165.0);
    glVertex3f(-32.0, -10.0, -165.0);       //PENGHUBUNG 1-2 - PILAR 8
    glVertex3f(-32.0, 5.0, -165.0);
    glVertex3f(-30.0, 5.0, -165.0);
    glVertex3f(-30.0, -10.0, -165.0);
    glVertex3f(-32.0, -10.0, -167.0);       //PENGHUBUNG 1-2 - PILAR 8
    glVertex3f(-32.0, 5.0, -167.0);
    glVertex3f(-30.0, 5.0, -167.0);
    glVertex3f(-30.0, -10.0, -167.0);
    glVertex3f(-36.0, 5.0, -104.0);         //PENGHUBUNG 1-2 - PILAR 1
    glVertex3f(-36.0, -10.0, -104.0);
    glVertex3f(-36.0, -10.0, -102.0);
    glVertex3f(-36.0, 5.0, -102.0);
    glVertex3f(-38.0, 5.0, -104.0);         //PENGHUBUNG 1-2 - PILAR 1
    glVertex3f(-38.0, -10.0, -104.0);
    glVertex3f(-38.0, -10.0, -102.0);
    glVertex3f(-38.0, 5.0, -102.0);
    glVertex3f(-38.0, -10.0, -102.0);        //PENGHUBUNG 1-2 - PILAR 1
    glVertex3f(-38.0, 5.0, -102.0);
    glVertex3f(-36.0, 5.0, -102.0);
    glVertex3f(-36.0, -10.0, -102.0);
    glVertex3f(-38.0, -10.0, -104.0);        //PENGHUBUNG 1-2 - PILAR 1
    glVertex3f(-38.0, 5.0, -104.0);
    glVertex3f(-36.0, 5.0, -104.0);
    glVertex3f(-36.0, -10.0, -104.0);
    glVertex3f(-36.0, 5.0, -113.0);          //PENGHUBUNG 1-2 - PILAR 2
    glVertex3f(-36.0, -10.0, -113.0);
    glVertex3f(-36.0, -10.0, -111.0);
    glVertex3f(-36.0, 5.0, -111.0);
    glVertex3f(-38.0, 5.0, -113.0);          //PENGHUBUNG 1-2 - PILAR 2
    glVertex3f(-38.0, -10.0, -113.0);
    glVertex3f(-38.0, -10.0, -111.0);
    glVertex3f(-38.0, 5.0, -111.0);
    glVertex3f(-38.0, -10.0, -111.0);        //PENGHUBUNG 1-2 - PILAR 2
    glVertex3f(-38.0, 5.0, -111.0);
    glVertex3f(-36.0, 5.0, -111.0);
    glVertex3f(-36.0, -10.0, -111.0);
    glVertex3f(-38.0, -10.0, -113.0);        //PENGHUBUNG 1-2 - PILAR 2
    glVertex3f(-38.0, 5.0, -113.0);
    glVertex3f(-36.0, 5.0, -113.0);
    glVertex3f(-36.0, -10.0, -113.0);
    glVertex3f(-36.0, 5.0, -122.0);          //PENGHUBUNG 1-2 - PILAR 3
    glVertex3f(-36.0, -10.0, -122.0);
    glVertex3f(-36.0, -10.0, -120.0);
    glVertex3f(-36.0, 5.0, -120.0);
    glVertex3f(-38.0, 5.0, -122.0);          //PENGHUBUNG 1-2 - PILAR 3
    glVertex3f(-38.0, -10.0, -122.0);
    glVertex3f(-38.0, -10.0, -120.0);
    glVertex3f(-38.0, 5.0, -120.0);
    glVertex3f(-38.0, -10.0, -120.0);        //PENGHUBUNG 1-2 - PILAR 3
    glVertex3f(-38.0, 5.0, -120.0);
    glVertex3f(-36.0, 5.0, -120.0);
    glVertex3f(-36.0, -10.0, -120.0);
    glVertex3f(-38.0, -10.0, -122.0);        //PENGHUBUNG 1-2 - PILAR 3
    glVertex3f(-38.0, 5.0, -122.0);
    glVertex3f(-36.0, 5.0, -122.0);
    glVertex3f(-36.0, -10.0, -122.0);
    glVertex3f(-36.0, 5.0, -131.0);          //PENGHUBUNG 1-2 - PILAR 4
    glVertex3f(-36.0, -10.0, -131.0);
    glVertex3f(-36.0, -10.0, -129.0);
    glVertex3f(-36.0, 5.0, -129.0);
    glVertex3f(-38.0, 5.0, -131.0);          //PENGHUBUNG 1-2 - PILAR 4
    glVertex3f(-38.0, -10.0, -131.0);
    glVertex3f(-38.0, -10.0, -129.0);
    glVertex3f(-38.0, 5.0, -129.0);
    glVertex3f(-38.0, -10.0, -129.0);        //PENGHUBUNG 1-2 - PILAR 4
    glVertex3f(-38.0, 5.0, -129.0);
    glVertex3f(-36.0, 5.0, -129.0);
    glVertex3f(-36.0, -10.0, -129.0);
    glVertex3f(-38.0, -10.0, -131.0);        //PENGHUBUNG 1-2 - PILAR 4
    glVertex3f(-38.0, 5.0, -131.0);
    glVertex3f(-36.0, 5.0, -131.0);
    glVertex3f(-36.0, -10.0, -131.0);
    glVertex3f(-36.0, 5.0, -140.0);          //PENGHUBUNG 1-2 - PILAR 5
    glVertex3f(-36.0, -10.0, -140.0);
    glVertex3f(-36.0, -10.0, -138.0);
    glVertex3f(-36.0, 5.0, -138.0);
    glVertex3f(-38.0, 5.0, -140.0);          //PENGHUBUNG 1-2 - PILAR 5
    glVertex3f(-38.0, -10.0, -140.0);
    glVertex3f(-38.0, -10.0, -138.0);
    glVertex3f(-38.0, 5.0, -138.0);
    glVertex3f(-38.0, -10.0, -138.0);        //PENGHUBUNG 1-2 - PILAR 5
    glVertex3f(-36.0, 5.0, -138.0);
    glVertex3f(-36.0, 5.0, -138.0);
    glVertex3f(-36.0, -10.0, -138.0);
    glVertex3f(-38.0, -10.0, -140.0);        //PENGHUBUNG 1-2 - PILAR 5
    glVertex3f(-38.0, 5.0, -140.0);
    glVertex3f(-36.0, 5.0, -140.0);
    glVertex3f(-36.0, -10.0, -140.0);
    glVertex3f(-36.0, 5.0, -149.0);          //PENGHUBUNG 1-2 - PILAR 6
    glVertex3f(-36.0, -10.0, -149.0);
    glVertex3f(-36.0, -10.0, -147.0);
    glVertex3f(-36.0, 5.0, -147.0);
    glVertex3f(-38.0, 5.0, -149.0);          //PENGHUBUNG 1-2 - PILAR 6
    glVertex3f(-38.0, -10.0, -149.0);
    glVertex3f(-38.0, -10.0, -147.0);
    glVertex3f(-38.0, 5.0, -147.0);
    glVertex3f(-38.0, -10.0, -147.0);        //PENGHUBUNG 1-2 - PILAR 6
    glVertex3f(-38.0, 5.0, -147.0);
    glVertex3f(-36.0, 5.0, -147.0);
    glVertex3f(-36.0, -10.0, -147.0);
    glVertex3f(-38.0, -10.0, -149.0);        //PENGHUBUNG 1-2 - PILAR 6
    glVertex3f(-38.0, 5.0, -149.0);
    glVertex3f(-36.0, 5.0, -149.0);
    glVertex3f(-36.0, -10.0, -149.0);
    glVertex3f(-36.0, 5.0, -158.0);          //PENGHUBUNG 1-2 - PILAR 7
    glVertex3f(-36.0, -10.0, -158.0);
    glVertex3f(-36.0, -10.0, -156.0);
    glVertex3f(-36.0, 5.0, -156.0);
    glVertex3f(-38.0, 5.0, -158.0);          //PENGHUBUNG 1-2 - PILAR 7
    glVertex3f(-38.0, -10.0, -158.0);
    glVertex3f(-38.0, -10.0, -156.0);
    glVertex3f(-38.0, 5.0, -156.0);
    glVertex3f(-38.0, -10.0, -156.0);        //PENGHUBUNG 1-2 - PILAR 7
    glVertex3f(-38.0, 5.0, -156.0);
    glVertex3f(-36.0, 5.0, -156.0);
    glVertex3f(-36.0, -10.0, -156.0);
    glVertex3f(-38.0, -10.0, -158.0);        //PENGHUBUNG 1-2 - PILAR 7
    glVertex3f(-38.0, 5.0, -158.0);
    glVertex3f(-36.0, 5.0, -158.0);
    glVertex3f(-36.0, -10.0, -158.0);
    glVertex3f(-36.0, 5.0, -167.0);          //PENGHUBUNG 1-2 - PILAR 8
    glVertex3f(-36.0, -10.0, -167.0);
    glVertex3f(-36.0, -10.0, -165.0);
    glVertex3f(-36.0, 5.0, -165.0);
    glVertex3f(-38.0, 5.0, -167.0);          //PENGHUBUNG 1-2 - PILAR 8
    glVertex3f(-38.0, -10.0, -167.0);
    glVertex3f(-38.0, -10.0, -165.0);
    glVertex3f(-38.0, 5.0, -165.0);
    glVertex3f(-38.0, -10.0, -165.0);        //PENGHUBUNG 1-2 - PILAR 8
    glVertex3f(-38.0, 5.0, -165.0);
    glVertex3f(-36.0, 5.0, -165.0);
    glVertex3f(-36.0, -10.0, -165.0);
    glVertex3f(-38.0, -10.0, -167.0);        //PENGHUBUNG 1-2 - PILAR 8
    glVertex3f(-38.0, 5.0, -167.0);
    glVertex3f(-36.0, 5.0, -167.0);
    glVertex3f(-36.0, -10.0, -167.0);

    glVertex3f(30.0, 5.0, -104.0);         //PENGHUBUNG 3-4 - PILAR 1
    glVertex3f(30.0, -10.0, -104.0);
    glVertex3f(30.0, -10.0, -102.0);
    glVertex3f(30.0, 5.0, -102.0);
    glVertex3f(32.0, 5.0, -104.0);         //PENGHUBUNG 3-4 - PILAR 1
    glVertex3f(32.0, -10.0, -104.0);
    glVertex3f(32.0, -10.0, -102.0);
    glVertex3f(32.0, 5.0, -102.0);
    glVertex3f(32.0, -10.0, -102.0);        //PENGHUBUNG 3-4 - PILAR 1
    glVertex3f(32.0, 5.0, -102.0);
    glVertex3f(30.0, 5.0, -102.0);
    glVertex3f(30.0, -10.0, -102.0);
    glVertex3f(32.0, -10.0, -104.0);        //PENGHUBUNG 3-4 - PILAR 1
    glVertex3f(32.0, 5.0, -104.0);
    glVertex3f(30.0, 5.0, -104.0);
    glVertex3f(30.0, -10.0, -104.0);
    glVertex3f(30.0, 5.0, -113.0);          //PENGHUBUNG 3-4 - PILAR 2
    glVertex3f(30.0, -10.0, -113.0);
    glVertex3f(30.0, -10.0, -111.0);
    glVertex3f(30.0, 5.0, -111.0);
    glVertex3f(32.0, 5.0, -113.0);          //PENGHUBUNG 3-4 - PILAR 2
    glVertex3f(32.0, -10.0, -113.0);
    glVertex3f(32.0, -10.0, -111.0);
    glVertex3f(32.0, 5.0, -111.0);
    glVertex3f(32.0, -10.0, -111.0);        //PENGHUBUNG 3-4 - PILAR 2
    glVertex3f(32.0, 5.0, -111.0);
    glVertex3f(30.0, 5.0, -111.0);
    glVertex3f(30.0, -10.0, -111.0);
    glVertex3f(32.0, -10.0, -113.0);        //PENGHUBUNG 3-4 - PILAR 2
    glVertex3f(32.0, 5.0, -113.0);
    glVertex3f(30.0, 5.0, -113.0);
    glVertex3f(30.0, -10.0, -113.0);
    glVertex3f(30.0, 5.0, -122.0);         //PENGHUBUNG 3-4 - PILAR 3
    glVertex3f(30.0, -10.0, -122.0);
    glVertex3f(30.0, -10.0, -120.0);
    glVertex3f(30.0, 5.0, -120.0);
    glVertex3f(32.0, 5.0, -122.0);         //PENGHUBUNG 3-4 - PILAR 3
    glVertex3f(32.0, -10.0, -122.0);
    glVertex3f(32.0, -10.0, -120.0);
    glVertex3f(32.0, 5.0, -120.0);
    glVertex3f(32.0, -10.0, -120.0);       //PENGHUBUNG 3-4 - PILAR 3
    glVertex3f(32.0, 5.0, -120.0);
    glVertex3f(30.0, 5.0, -120.0);
    glVertex3f(30.0, -10.0, -120.0);
    glVertex3f(32.0, -10.0, -122.0);       //PENGHUBUNG 3-4 - PILAR 3
    glVertex3f(32.0, 5.0, -122.0);
    glVertex3f(30.0, 5.0, -122.0);
    glVertex3f(30.0, -10.0, -122.0);
    glVertex3f(30.0, 5.0, -131.0);         //PENGHUBUNG 3-4 - PILAR 4
    glVertex3f(30.0, -10.0, -131.0);
    glVertex3f(30.0, -10.0, -129.0);
    glVertex3f(30.0, 5.0, -129.0);
    glVertex3f(32.0, 5.0, -131.0);         //PENGHUBUNG 3-4 - PILAR 4
    glVertex3f(32.0, -10.0, -131.0);
    glVertex3f(32.0, -10.0, -129.0);
    glVertex3f(32.0, 5.0, -129.0);
    glVertex3f(32.0, -10.0, -129.0);       //PENGHUBUNG 3-4 - PILAR 4
    glVertex3f(32.0, 5.0, -129.0);
    glVertex3f(30.0, 5.0, -129.0);
    glVertex3f(30.0, -10.0, -129.0);
    glVertex3f(32.0, -10.0, -131.0);       //PENGHUBUNG 3-4 - PILAR 4
    glVertex3f(32.0, 5.0, -131.0);
    glVertex3f(30.0, 5.0, -131.0);
    glVertex3f(30.0, -10.0, -131.0);
    glVertex3f(30.0, 5.0, -140.0);         //PENGHUBUNG 3-4 - PILAR 5
    glVertex3f(30.0, -10.0, -140.0);
    glVertex3f(30.0, -10.0, -138.0);
    glVertex3f(30.0, 5.0, -138.0);
    glVertex3f(32.0, 5.0, -140.0);         //PENGHUBUNG 3-4 - PILAR 5
    glVertex3f(32.0, -10.0, -140.0);
    glVertex3f(32.0, -10.0, -138.0);
    glVertex3f(32.0, 5.0, -138.0);
    glVertex3f(32.0, -10.0, -138.0);       //PENGHUBUNG 3-4 - PILAR 5
    glVertex3f(32.0, 5.0, -138.0);
    glVertex3f(30.0, 5.0, -138.0);
    glVertex3f(30.0, -10.0, -138.0);
    glVertex3f(32.0, -10.0, -140.0);       //PENGHUBUNG 3-4 - PILAR 5
    glVertex3f(32.0, 5.0, -140.0);
    glVertex3f(30.0, 5.0, -140.0);
    glVertex3f(30.0, -10.0, -140.0);
    glVertex3f(30.0, 5.0, -149.0);         //PENGHUBUNG 3-4 - PILAR 6
    glVertex3f(30.0, -10.0, -149.0);
    glVertex3f(30.0, -10.0, -147.0);
    glVertex3f(30.0, 5.0, -147.0);
    glVertex3f(32.0, 5.0, -149.0);         //PENGHUBUNG 3-4 - PILAR 6
    glVertex3f(32.0, -10.0, -149.0);
    glVertex3f(32.0, -10.0, -147.0);
    glVertex3f(32.0, 5.0, -147.0);
    glVertex3f(32.0, -10.0, -147.0);       //PENGHUBUNG 3-4 - PILAR 6
    glVertex3f(32.0, 5.0, -147.0);
    glVertex3f(30.0, 5.0, -147.0);
    glVertex3f(30.0, -10.0, -147.0);
    glVertex3f(32.0, -10.0, -149.0);       //PENGHUBUNG 3-4 - PILAR 6
    glVertex3f(32.0, 5.0, -149.0);
    glVertex3f(30.0, 5.0, -149.0);
    glVertex3f(30.0, -10.0, -149.0);
    glVertex3f(30.0, 5.0, -158.0);         //PENGHUBUNG 3-4 - PILAR 7
    glVertex3f(30.0, -10.0, -158.0);
    glVertex3f(30.0, -10.0, -156.0);
    glVertex3f(30.0, 5.0, -156.0);
    glVertex3f(32.0, 5.0, -158.0);         //PENGHUBUNG 3-4 - PILAR 7
    glVertex3f(32.0, -10.0, -158.0);
    glVertex3f(32.0, -10.0, -156.0);
    glVertex3f(32.0, 5.0, -156.0);
    glVertex3f(32.0, -10.0, -156.0);       //PENGHUBUNG 3-4 - PILAR 7
    glVertex3f(32.0, 5.0, -156.0);
    glVertex3f(30.0, 5.0, -156.0);
    glVertex3f(30.0, -10.0, -156.0);
    glVertex3f(32.0, -10.0, -158.0);       //PENGHUBUNG 3-4 - PILAR 7
    glVertex3f(32.0, 5.0, -158.0);
    glVertex3f(30.0, 5.0, -158.0);
    glVertex3f(30.0, -10.0, -158.0);
    glVertex3f(30.0, 5.0, -167.0);         //PENGHUBUNG 3-4 - PILAR 8
    glVertex3f(30.0, -10.0, -167.0);
    glVertex3f(30.0, -10.0, -165.0);
    glVertex3f(30.0, 5.0, -165.0);
    glVertex3f(32.0, 5.0, -167.0);         //PENGHUBUNG 3-4 - PILAR 8
    glVertex3f(32.0, -10.0, -167.0);
    glVertex3f(32.0, -10.0, -165.0);
    glVertex3f(32.0, 5.0, -165.0);
    glVertex3f(32.0, -10.0, -165.0);       //PENGHUBUNG 3-4 - PILAR 8
    glVertex3f(32.0, 5.0, -165.0);
    glVertex3f(30.0, 5.0, -165.0);
    glVertex3f(30.0, -10.0, -165.0);
    glVertex3f(32.0, -10.0, -167.0);       //PENGHUBUNG 3-4 - PILAR 8
    glVertex3f(32.0, 5.0, -167.0);
    glVertex3f(30.0, 5.0, -167.0);
    glVertex3f(30.0, -10.0, -167.0);
    glVertex3f(36.0, 5.0, -104.0);         //PENGHUBUNG 3-4 - PILAR 1
    glVertex3f(36.0, -10.0, -104.0);
    glVertex3f(36.0, -10.0, -102.0);
    glVertex3f(36.0, 5.0, -102.0);
    glVertex3f(38.0, 5.0, -104.0);         //PENGHUBUNG 3-4 - PILAR 1
    glVertex3f(38.0, -10.0, -104.0);
    glVertex3f(38.0, -10.0, -102.0);
    glVertex3f(38.0, 5.0, -102.0);
    glVertex3f(38.0, -10.0, -102.0);        //PENGHUBUNG 3-4 - PILAR 1
    glVertex3f(38.0, 5.0, -102.0);
    glVertex3f(36.0, 5.0, -102.0);
    glVertex3f(36.0, -10.0, -102.0);
    glVertex3f(38.0, -10.0, -104.0);        //PENGHUBUNG 3-4 - PILAR 1
    glVertex3f(38.0, 5.0, -104.0);
    glVertex3f(36.0, 5.0, -104.0);
    glVertex3f(36.0, -10.0, -104.0);
    glVertex3f(36.0, 5.0, -113.0);          //PENGHUBUNG 3-4 - PILAR 2
    glVertex3f(36.0, -10.0, -113.0);
    glVertex3f(36.0, -10.0, -111.0);
    glVertex3f(36.0, 5.0, -111.0);
    glVertex3f(38.0, 5.0, -113.0);          //PENGHUBUNG 3-4 - PILAR 2
    glVertex3f(38.0, -10.0, -113.0);
    glVertex3f(38.0, -10.0, -111.0);
    glVertex3f(38.0, 5.0, -111.0);
    glVertex3f(38.0, -10.0, -111.0);        //PENGHUBUNG 3-4 - PILAR 2
    glVertex3f(38.0, 5.0, -111.0);
    glVertex3f(36.0, 5.0, -111.0);
    glVertex3f(36.0, -10.0, -111.0);
    glVertex3f(38.0, -10.0, -113.0);        //PENGHUBUNG 3-4 - PILAR 2
    glVertex3f(38.0, 5.0, -113.0);
    glVertex3f(36.0, 5.0, -113.0);
    glVertex3f(36.0, -10.0, -113.0);
    glVertex3f(36.0, 5.0, -122.0);          //PENGHUBUNG 3-4 - PILAR 3
    glVertex3f(36.0, -10.0, -122.0);
    glVertex3f(36.0, -10.0, -120.0);
    glVertex3f(36.0, 5.0, -120.0);
    glVertex3f(38.0, 5.0, -122.0);          //PENGHUBUNG 3-4 - PILAR 3
    glVertex3f(38.0, -10.0, -122.0);
    glVertex3f(38.0, -10.0, -120.0);
    glVertex3f(38.0, 5.0, -120.0);
    glVertex3f(38.0, -10.0, -120.0);        //PENGHUBUNG 3-4 - PILAR 3
    glVertex3f(38.0, 5.0, -120.0);
    glVertex3f(36.0, 5.0, -120.0);
    glVertex3f(36.0, -10.0, -120.0);
    glVertex3f(38.0, -10.0, -122.0);        //PENGHUBUNG 3-4 - PILAR 3
    glVertex3f(38.0, 5.0, -122.0);
    glVertex3f(36.0, 5.0, -122.0);
    glVertex3f(36.0, -10.0, -122.0);
    glVertex3f(36.0, 5.0, -131.0);          //PENGHUBUNG 3-4 - PILAR 4
    glVertex3f(36.0, -10.0, -131.0);
    glVertex3f(36.0, -10.0, -129.0);
    glVertex3f(36.0, 5.0, -129.0);
    glVertex3f(38.0, 5.0, -131.0);          //PENGHUBUNG 3-4 - PILAR 4
    glVertex3f(38.0, -10.0, -131.0);
    glVertex3f(38.0, -10.0, -129.0);
    glVertex3f(38.0, 5.0, -129.0);
    glVertex3f(38.0, -10.0, -129.0);        //PENGHUBUNG 3-4 - PILAR 4
    glVertex3f(38.0, 5.0, -129.0);
    glVertex3f(36.0, 5.0, -129.0);
    glVertex3f(36.0, -10.0, -129.0);
    glVertex3f(38.0, -10.0, -131.0);        //PENGHUBUNG 3-4 - PILAR 4
    glVertex3f(38.0, 5.0, -131.0);
    glVertex3f(36.0, 5.0, -131.0);
    glVertex3f(36.0, -10.0, -131.0);
    glVertex3f(36.0, 5.0, -140.0);          //PENGHUBUNG 3-4 - PILAR 5
    glVertex3f(36.0, -10.0, -140.0);
    glVertex3f(36.0, -10.0, -138.0);
    glVertex3f(36.0, 5.0, -138.0);
    glVertex3f(38.0, 5.0, -140.0);          //PENGHUBUNG 3-4 - PILAR 5
    glVertex3f(38.0, -10.0, -140.0);
    glVertex3f(38.0, -10.0, -138.0);
    glVertex3f(38.0, 5.0, -138.0);
    glVertex3f(38.0, -10.0, -138.0);        //PENGHUBUNG 3-4 - PILAR 5
    glVertex3f(36.0, 5.0, -138.0);
    glVertex3f(36.0, 5.0, -138.0);
    glVertex3f(36.0, -10.0, -138.0);
    glVertex3f(38.0, -10.0, -140.0);        //PENGHUBUNG 3-4 - PILAR 5
    glVertex3f(38.0, 5.0, -140.0);
    glVertex3f(36.0, 5.0, -140.0);
    glVertex3f(36.0, -10.0, -140.0);
    glVertex3f(36.0, 5.0, -149.0);          //PENGHUBUNG 3-4 - PILAR 6
    glVertex3f(36.0, -10.0, -149.0);
    glVertex3f(36.0, -10.0, -147.0);
    glVertex3f(36.0, 5.0, -147.0);
    glVertex3f(38.0, 5.0, -149.0);          //PENGHUBUNG 3-4 - PILAR 6
    glVertex3f(38.0, -10.0, -149.0);
    glVertex3f(38.0, -10.0, -147.0);
    glVertex3f(38.0, 5.0, -147.0);
    glVertex3f(38.0, -10.0, -147.0);        //PENGHUBUNG 3-4 - PILAR 6
    glVertex3f(38.0, 5.0, -147.0);
    glVertex3f(36.0, 5.0, -147.0);
    glVertex3f(36.0, -10.0, -147.0);
    glVertex3f(38.0, -10.0, -149.0);        //PENGHUBUNG 3-4 - PILAR 6
    glVertex3f(38.0, 5.0, -149.0);
    glVertex3f(36.0, 5.0, -149.0);
    glVertex3f(36.0, -10.0, -149.0);
    glVertex3f(36.0, 5.0, -158.0);          //PENGHUBUNG 3-4 - PILAR 7
    glVertex3f(36.0, -10.0, -158.0);
    glVertex3f(36.0, -10.0, -156.0);
    glVertex3f(36.0, 5.0, -156.0);
    glVertex3f(38.0, 5.0, -158.0);          //PENGHUBUNG 3-4 - PILAR 7
    glVertex3f(38.0, -10.0, -158.0);
    glVertex3f(38.0, -10.0, -156.0);
    glVertex3f(38.0, 5.0, -156.0);
    glVertex3f(38.0, -10.0, -156.0);        //PENGHUBUNG 3-4 - PILAR 7
    glVertex3f(38.0, 5.0, -156.0);
    glVertex3f(36.0, 5.0, -156.0);
    glVertex3f(36.0, -10.0, -156.0);
    glVertex3f(38.0, -10.0, -158.0);        //PENGHUBUNG 3-4 - PILAR 7
    glVertex3f(38.0, 5.0, -158.0);
    glVertex3f(36.0, 5.0, -158.0);
    glVertex3f(36.0, -10.0, -158.0);
    glVertex3f(36.0, 5.0, -167.0);          //PENGHUBUNG 3-4 - PILAR 8
    glVertex3f(36.0, -10.0, -167.0);
    glVertex3f(36.0, -10.0, -165.0);
    glVertex3f(36.0, 5.0, -165.0);
    glVertex3f(38.0, 5.0, -167.0);          //PENGHUBUNG 3-4 - PILAR 8
    glVertex3f(38.0, -10.0, -167.0);
    glVertex3f(38.0, -10.0, -165.0);
    glVertex3f(38.0, 5.0, -165.0);
    glVertex3f(38.0, -10.0, -165.0);        //PENGHUBUNG 3-4 - PILAR 8
    glVertex3f(38.0, 5.0, -165.0);
    glVertex3f(36.0, 5.0, -165.0);
    glVertex3f(36.0, -10.0, -165.0);
    glVertex3f(38.0, -10.0, -167.0);        //PENGHUBUNG 3-4 - PILAR 8
    glVertex3f(38.0, 5.0, -167.0);
    glVertex3f(36.0, 5.0, -167.0);
    glVertex3f(36.0, -10.0, -167.0);
    glEnd();


    glTranslatef(0, gerak, 0);

    //Untuk radius titik variabel disini saya menggunakan range 1-9 bukan 0.0-0.9
    //silahkan sesualkan saja bila hasilnya sangat kecil atau sangat besar
    //untuk mengatur besar kecil tampilan dapat diseting kembali di void main

    glBegin(GL_LINES);
    glColor3f(0.2, 0.2, 1);
    glVertex3f(0, -5, -135);
    glVertex3f(0, -10, -135);
    glColor3f(0.2, 0.6, 1);
    glVertex3f(0, 0, -135);
    glVertex3f(0, 5, -135);
    glColor3f(0.2, 1, 1);
    glVertex3f(0, 10, -135);
    glVertex3f(0, 15, -135);
    glColor3f(1, 1, 1);
    glVertex3f(0, 20, -135);
    glVertex3f(0, 25, -135);

    glColor3f(0.2, 0.2, 1);
    glVertex3f(5, -5, -135);
    glVertex3f(5, -10, -135);
    glColor3f(0.2, 0.6, 1);
    glVertex3f(5, 0, -135);
    glVertex3f(5, 5, -135);
    glColor3f(0.2, 1, 1);
    glVertex3f(5, 10, -135);
    glVertex3f(5, 15, -135);
    glColor3f(1, 1, 1);
    glVertex3f(5, 20, -135);
    glVertex3f(5, 25, -135);

    glColor3f(0.2, 0.2, 1);
    glVertex3f(-5, -5, -135);
    glVertex3f(-5, -10, -135);
    glColor3f(0.2, 0.6, 1);
    glVertex3f(-5, 0, -135);
    glVertex3f(-5, 5, -135);
    glColor3f(0.2, 1, 1);
    glVertex3f(-5, 10, -135);
    glVertex3f(-5, 15, -135);
    glColor3f(1, 1, 1);
    glVertex3f(-5, 20, -135);
    glVertex3f(-5, 25, -135);

    glColor3f(0.2, 0.2, 1);
    glVertex3f(0, -5, -140);
    glVertex3f(0, -10, -140);
    glColor3f(0.2, 0.6, 1);
    glVertex3f(0, 0, -140);
    glVertex3f(0, 5, -140);
    glColor3f(0.2, 1, 1);
    glVertex3f(0, 10, -140);
    glVertex3f(0, 15, -140);
    glColor3f(1, 1, 1);
    glVertex3f(0, 20, -140);
    glVertex3f(0, 25, -140);

    glColor3f(0.2, 0.2, 1);
    glVertex3f(2.5, -5, -138);
    glVertex3f(2.5, -10, -138);
    glColor3f(0.2, 0.6, 1);
    glVertex3f(2.5, 0, -138);
    glVertex3f(2.5, 5, -138);
    glColor3f(0.2, 1, 1);
    glVertex3f(2.5, 10, -138);
    glVertex3f(2.5, 15, -138);
    glColor3f(1, 1, 1);
    glVertex3f(2.5, 20, -138);
    glVertex3f(2.5, 25, -138);

    glColor3f(0.2, 0.2, 1);
    glVertex3f(-2.5, -5, -138);
    glVertex3f(-2.5, -10, -138);
    glColor3f(0.2, 0.6, 1);
    glVertex3f(-2.5, 0, -138);
    glVertex3f(-2.5, 5, -138);
    glColor3f(0.2, 1, 1);
    glVertex3f(-2.5, 10, -138);
    glVertex3f(-2.5, 15, -138);
    glColor3f(1, 1, 1);
    glVertex3f(-2.5, 20, -138);
    glVertex3f(-2.5, 25, -138);

    glColor3f(0.2, 0.2, 1);
    glVertex3f(0, -5, -130);
    glVertex3f(0, -10, -130);
    glColor3f(0.2, 0.6, 1);
    glVertex3f(0, 0, -130);
    glVertex3f(0, 5, -130);
    glColor3f(0.2, 1, 1);
    glVertex3f(0, 10, -130);
    glVertex3f(0, 15, -130);
    glColor3f(1, 1, 1);
    glVertex3f(0, 20, -130);
    glVertex3f(0, 25, -130);

    glColor3f(0.2, 0.2, 1);
    glVertex3f(2.5, -5, -132);
    glVertex3f(2.5, -10, -132);
    glColor3f(0.2, 0.6, 1);
    glVertex3f(2.5, 0, -132);
    glVertex3f(2.5, 5, -132);
    glColor3f(0.2, 1, 1);
    glVertex3f(2.5, 10, -132);
    glVertex3f(2.5, 15, -132);
    glColor3f(1, 1, 1);
    glVertex3f(2.5, 20, -132);
    glVertex3f(2.5, 25, -132);

    glColor3f(0.2, 0.2, 1);
    glVertex3f(-2.5, -5, -132);
    glVertex3f(-2.5, -10, -132);
    glColor3f(0.2, 0.6, 1);
    glVertex3f(-2.5, 0, -132);
    glVertex3f(-2.5, 5, -132);
    glColor3f(0.2, 1, 1);
    glVertex3f(-2.5, 10, -132);
    glVertex3f(-2.5, 15, -132);
    glColor3f(1, 1, 1);
    glVertex3f(-2.5, 20, -132);
    glVertex3f(-2.5, 25, -132);
    glEnd();

    glFlush();//untuk membersihkan

    //UPDATE
    //UPDATE

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
        zmov += 5;
        break;
    case 'd':
    case 'D':
        xmov += 5;
        break;
    case 's':
    case 'S':
        zmov -= 5;
        break;
    case 'a':
    case 'A':
        xmov -= 5;
        break;
    case '7':
        ymov += 5;
        break;
    case '9':
        ymov -= 5;
        break;
    case '2':
        xrot += 5;
        break;
    case '8':
        xrot -= 5;
        break;
    case '6':
        yrot += 5;
        break;
    case '4':
        yrot -= 5;
        break;
    case '1':
        zrot += 5;
        break;
    case '3':
        zrot -= 5;
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
