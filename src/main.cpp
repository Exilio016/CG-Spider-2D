#include<GL/glut.h>
#include <spider.h>
#include <cmath>

const GLint WINDOWS_WIDTH = 800, WINDOWS_HEIGHT = 600;


void init(){
    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION);

    gluOrtho2D(0, WINDOWS_WIDTH, 0, WINDOWS_HEIGHT);
}

void callback_display(){
    spider::t_point *p = new spider::t_point;
    p->x = WINDOWS_WIDTH/2;
    p->y = WINDOWS_HEIGHT/2;

    spider *s = new spider(p);
    glClear(GL_COLOR_BUFFER_BIT);
    s->draw();
    glutSwapBuffers();

}

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    GLint screen_width = glutGet(GLUT_SCREEN_WIDTH),
            screen_height = glutGet(GLUT_SCREEN_HEIGHT);

    glutInitWindowPosition((screen_width - WINDOWS_WIDTH)/2, (screen_height - WINDOWS_HEIGHT)/2);
    glutInitWindowSize(WINDOWS_WIDTH, WINDOWS_HEIGHT);
    glutCreateWindow("Aranha 2D");

    init();
    glutDisplayFunc(callback_display);

    glutMainLoop();

    return 0;
}