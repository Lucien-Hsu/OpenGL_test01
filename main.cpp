#ifdef __APPLE__ // 若作業系統為macOS系統，則使用下列header檔案
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

//宣告枚舉
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
    //初始化GLUT函式庫
    glutInit(&argc, argv);
    //初始化渲染模式，指定緩存器類型為"顏色RGBA"、"雙緩存"、"深度緩存"
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    //設定視窗位置，螢幕左上方為(0,0)
    glutInitWindowPosition(200, 200);
    //設定視窗寬高
    glutInitWindowSize(400, 400);
    //建立視窗，決定視窗名稱
    glutCreateWindow("glut test");

    
    //建立選單
    int menu_main = glutCreateMenu(My_Menu);
    int menu_entry = glutCreateMenu(My_Menu);

    glutSetMenu(menu_main);
    glutAddSubMenu("Teapot size", menu_entry);
    glutAddMenuEntry("Exit", MENU_EXIT);

    glutSetMenu(menu_entry);
    glutAddMenuEntry("1.0", 1);
    glutAddMenuEntry("2.0", 2);

    glutSetMenu(menu_main);
    //設為滑鼠右鍵按下時出現選單
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    init();
    //////////////////////////////////////////
    //註冊設計者的顯示函式到GLUT
    glutDisplayFunc(display);
    //當程式空閒時回調函式
    //glutIdleFunc(display);
    //註冊當視窗改變大小時的回調函數
    glutReshapeFunc(reshape);
    //鍵盤回調
    glutKeyboardFunc(My_Keyboard);
    //鍵盤特殊鍵回調
    glutSpecialFunc(My_SpecialKeys);
    //計時器回調
    glutTimerFunc(timer_interval, My_Timer, 0);
    //////////////////////////////////////////

    //開啟深度測試，這樣才有深度
    glEnable(GL_DEPTH_TEST);
    //使GLUT不斷運行
    glutMainLoop();

    return 0;
}

void init()
{
    //清除畫面並設定顏色
    glClearColor(0.0, 0.0, 0.0, 0.0);

    //指定目前計算的矩陣，這裡為投影矩陣
    glMatrixMode(GL_PROJECTION);
    //重設為單位矩陣
    glLoadIdentity();
    //設定投影模式為透視，參數為：視野、長寬比、近平面、遠平面
    gluPerspective(60.0f, 1, 0.1f, 200.0f);
    //glOrtho(-5, 5, -5, 5, 5, 15);

    //指定目前計算的矩陣，這裡為模型視圖矩陣
    glMatrixMode(GL_MODELVIEW);
    //重設為單位矩陣
    glLoadIdentity();
    //設定攝影機位置、朝向、與上方
    gluLookAt(
        0, 2.0, 5.0, 
        0, 0, 0, 
        0, 1, 0);
}

void display()
{
    //清除引數中的緩存，這裡清除顏色緩存與深度緩存
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //乘上位移矩陣
    glTranslatef(teapot_posX, teapot_posY, 0.0f);
    //乘上旋轉矩陣
    glRotatef(rotateAngle, 0.0f, 1.0f, 0.0f);
    //指定繪圖使用的RGB顏色，紅色
    if (myColor == Red) {
        glColor3b(125, 0, 0);
    }
    else if (myColor == Green) {
        glColor3b(0, 125, 0);
    }
    else if (myColor == Blue) {
        glColor3b(0, 0, 125);
    }

    //畫出茶壺，這裡尺寸為3
    glutWireTeapot(teapot_size);
    //交替緩存器，用於使用雙緩存器時
    glutSwapBuffers();
}


void reshape(int width, int height)
{
    
    //計算寬高比
    if (height == 0)height = 1;     //避免高度為0
    double aspect = width * 1.0f / height;
    //指定目前計算的矩陣，這裡為投影矩陣
    glMatrixMode(GL_PROJECTION);
    //重設為單位矩陣
    glLoadIdentity();
    //Viewport設定，能將投影對應到視窗座標
    glViewport(0, 0, width, height);
    //設定投影模式為透視，參數為：視野、長寬比、近平面、遠平面
    gluPerspective(60.0f, aspect, 0.1f, 10.0f);

    //指定目前計算的矩陣，這裡為模型視圖矩陣
    glMatrixMode(GL_MODELVIEW);
    //重設為單位矩陣
    glLoadIdentity();
    //設定攝影機位置、朝向、與上方
    gluLookAt(
        0, 2.0, 5.0,
        0, 0, 0,
        0, 1, 0);
        
}

//持續旋轉
void My_Timer(int val) 
{
    //使程式即時更新
    glutPostRedisplay();
    glutTimerFunc(timer_interval, My_Timer, val);
    //根據速度與時間累計旋轉量。
    rotateAngle += rotateSpeed * timer_interval * 0.001;
}

//按鍵移動
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

//按鍵茶壺變色
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

//選單
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



