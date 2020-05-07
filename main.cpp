#ifdef __APPLE__ // �Y�@�~�t�ά�macOS�t�ΡA�h�ϥΤU�Cheader�ɮ�
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <string>

using namespace std;

#define MENU_Entry1 1
#define MENU_Entry2 2
#define MENU_EXIT   3

void init();
void display();
void reshape(int, int);
void My_Timer(int);
void My_Keyboard(unsigned char, int, int);
void My_SpecialKeys(int, int, int);
void My_Menu(int);

//�ŧi�T�|
enum Color { Red = 1, Green, Blue };
enum id { SIZE_1 = 1, SIZE_2 };

Color myColor;

float teapot_posX = 0.0;
float teapot_posY = 0.0;
float timer_interval = 1000.0f;
float teapot_size = 1.0f;
float rotateAngle = 10.0;
double rotateSpeed = 0.1;

int main(int argc, char* argv[])
{
    //��l��GLUT�禡�w
    glutInit(&argc, argv);
    //��l�ƴ�V�Ҧ��A���w�w�s��������"�C��RGBA"�B"���w�s"�B"�`�׽w�s"
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    //�]�w������m�A�ù����W�謰(0,0)
    glutInitWindowPosition(200, 200);
    //�]�w�����e��
    glutInitWindowSize(400, 400);
    //�إߵ����A�M�w�����W��
    glutCreateWindow("glut test");

    
    //�إ߿��
    int menu_main = glutCreateMenu(My_Menu);
    int menu_entry = glutCreateMenu(My_Menu);

    glutSetMenu(menu_main);
    glutAddSubMenu("Teapot size", menu_entry);
    glutAddMenuEntry("Exit", MENU_EXIT);

    glutSetMenu(menu_entry);
    glutAddMenuEntry("1.0", 1);
    glutAddMenuEntry("2.0", 2);

    glutSetMenu(menu_main);
    //�]���ƹ��k����U�ɥX�{���
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    init();
    //////////////////////////////////////////
    //���U�]�p�̪���ܨ禡��GLUT
    glutDisplayFunc(display);
    //��{���Ŷ��ɦ^�ը禡
    //glutIdleFunc(display);
    //���U��������ܤj�p�ɪ��^�ը��
    glutReshapeFunc(reshape);
    //��L�^��
    glutKeyboardFunc(My_Keyboard);
    //��L�S����^��
    glutSpecialFunc(My_SpecialKeys);
    //�p�ɾ��^��
    glutTimerFunc(timer_interval, My_Timer, 0);
    //////////////////////////////////////////

    //�}�Ҳ`�״��աA�o�ˤ~���`��
    glEnable(GL_DEPTH_TEST);
    //��GLUT���_�B��
    glutMainLoop();

    return 0;
}

void init()
{
    //�M���e���ó]�w�C��
    glClearColor(0.0, 0.0, 0.0, 0.0);

    //���w�ثe�p�⪺�x�}�A�o�̬���v�x�}
    glMatrixMode(GL_PROJECTION);
    //���]�����x�}
    glLoadIdentity();
    //�]�w��v�Ҧ����z���A�ѼƬ��G�����B���e��B�񥭭��B������
    gluPerspective(60.0f, 1, 0.1f, 200.0f);
    //glOrtho(-5, 5, -5, 5, 5, 15);

    //���w�ثe�p�⪺�x�}�A�o�̬��ҫ����ϯx�}
    glMatrixMode(GL_MODELVIEW);
    //���]�����x�}
    glLoadIdentity();
    //�]�w��v����m�B�¦V�B�P�W��
    gluLookAt(
        0, 2.0, 5.0, 
        0, 0, 0, 
        0, 1, 0);
}

void display()
{
    //�M���޼Ƥ����w�s�A�o�̲M���C��w�s�P�`�׽w�s
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //���W�첾�x�}
    glTranslatef(teapot_posX, teapot_posY, 0.0f);
    //���W����x�}
    glRotatef(rotateAngle, 0.0f, 1.0f, 0.0f);
    //���wø�ϨϥΪ�RGB�C��A����
    if (myColor == Red) {
        glColor3b(125, 0, 0);
    }
    else if (myColor == Green) {
        glColor3b(0, 125, 0);
    }
    else if (myColor == Blue) {
        glColor3b(0, 0, 125);
    }

    //�e�X�����A�o�̤ؤo��3
    glutWireTeapot(teapot_size);
    //����w�s���A�Ω�ϥ����w�s����
    glutSwapBuffers();
}


void reshape(int width, int height)
{
    
    //�p��e����
    if (height == 0)height = 1;     //�קK���׬�0
    double aspect = width * 1.0f / height;
    //���w�ثe�p�⪺�x�}�A�o�̬���v�x�}
    glMatrixMode(GL_PROJECTION);
    //���]�����x�}
    glLoadIdentity();
    //Viewport�]�w�A��N��v����������y��
    glViewport(0, 0, width, height);
    //�]�w��v�Ҧ����z���A�ѼƬ��G�����B���e��B�񥭭��B������
    gluPerspective(60.0f, aspect, 0.1f, 10.0f);

    //���w�ثe�p�⪺�x�}�A�o�̬��ҫ����ϯx�}
    glMatrixMode(GL_MODELVIEW);
    //���]�����x�}
    glLoadIdentity();
    //�]�w��v����m�B�¦V�B�P�W��
    gluLookAt(
        0, 2.0, 5.0,
        0, 0, 0,
        0, 1, 0);
        
}

//�������
void My_Timer(int val) 
{
    //�ϵ{���Y�ɧ�s
    glutPostRedisplay();
    glutTimerFunc(timer_interval, My_Timer, val);
    //�ھڳt�׻P�ɶ��֭p����q�C
    rotateAngle += rotateSpeed * timer_interval * 0.001;
}

//���䲾��
void My_Keyboard(unsigned char key, int x, int y)
{
    if (key == 'W' || key == 'w') {
        teapot_posY += 0.05f;
    }
    if (key == 'S' || key == 's') {
        teapot_posY -= 0.05f;
    }
    if (key == 'A' || key == 'a') {
        teapot_posX -= 0.05f;
    }
    if (key == 'D' || key == 'd') {
        teapot_posX += 0.05f;
    }
}

//��������ܦ�
void My_SpecialKeys(int key, int x, int y)
{
    if (key == GLUT_KEY_F1) {
        myColor = Red;
    }
    if (key == GLUT_KEY_F2) {
        myColor = Green;
    }
    if (key == GLUT_KEY_F3) {
        myColor = Blue;
    }
}

//���
void My_Menu(int id) 
{
    if (id == SIZE_1) {
        teapot_size = 1.0f;
    }else if (id == SIZE_2) {
        teapot_size = 2.0f;
    }
    else if (id == MENU_EXIT) {
        teapot_size = 2.0f;
    }
}



