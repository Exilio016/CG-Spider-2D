#include<GL/glut.h>

const GLint WINDOWS_WIDTH = 800, WINDOWS_HEIGHT = 600;

void init(){
    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION);

    gluOrtho2D(0, WINDOWS_WIDTH, WINDOWS_HEIGHT, 0);
}

void callback_display(){
    glClear(GL_COLOR_BUFFER_BIT);
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