//Estela Pillo González

#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdbool.h>

#define ancho 500
#define alto 500

/*ACLARACIONES:
1-0: Para elegir si rotamos toda la extremidad o una parte
2: Cambiar el brazo que se está controlando
p: Controlar pierna/Cambiar pierna que se está controlando
q,a,w,s,e,d: Mover la extremidad seleccionada en distintos ángulos
Click izquierdo del ratón + movimiento: rotar las piernas alrededor del eje X 
Flechas izquierda y derecha: rotar las piernas alrededor del eje Y

En el menú se activa la rotación automática de las piernas y se modifica su velocidad
Para la visualización en modo solid, agregué un borde color negro a los cubos de manera adicional, solo para que se diferenciasen 
bien las distintas extremidades.
*/

GLfloat angulosiz[2][3];       //Para controlar la rotación del brazo izquierdo
GLfloat angulosdch[2][3];      //Brazo derecho
GLfloat angulospi[2][3];       //Pierna izquierda
GLfloat angulospd[2][3];       //Pierna derecha

GLboolean modo = false;         // Variable de control para decidir si movemos todo el brazo o solo una parte
GLboolean mover = true;
GLboolean modovisualizacion = false;

int brazo = 0;
bool temporizadorActivo = false;
bool ratonPresionado = false;


GLint64 i = 0;
GLint64 j = 0;

GLint64 velocidad = 10;

void init()
{
    glClearColor(0.0f,0.0f,0.0f,0.0f); // Color de fondo
}
void extremidades(GLfloat angulos[2][3], float translateX, float translateY, float translateZ, float tamanoEsfera, float tamanoCubo, float tamanoUltimoCubo) 
{ 
    glLoadIdentity();  

    glTranslatef(translateX, translateY, translateZ);

    // Primera esfera
    glColor3f(0.5, 0.5, 1.0);
    if (modovisualizacion) {
        glutSolidSphere(0.5f, 9, 9); 
    } else {
        glutWireSphere(0.5f, 9, 9);
    }

    // Rotaciones para la primera extremidad
    glRotatef(angulos[0][0], 1.0f, 0.0f, 0.0f); 
    glRotatef(angulos[0][1], 0.0f, 1.0f, 0.0f); 
    glRotatef(angulos[0][2], 0.0f, 0.0f, 1.0f); 

    glPushMatrix();
    glTranslatef(0.0, -1.5, 0.0f);
    glScalef(1.0f, 2.0f, 1.0f);

    // Primer cubo
     if (modovisualizacion) {
        glColor3f(135, 206, 235);
        glutSolidCube(1.0f);
        glColor3f(0.0f, 0.0f, 0.0f); 
        glutWireCube(1.0f); // Borde del cubo
    } else {
        glColor3f(135, 206, 235);
        glutWireCube(1.0f); 
    }

    glPopMatrix();
    glTranslatef(0.0f, -3.0f, 0.0f);

    // Segunda esfera
    glColor3f(0.5, 0.5, 1.0);
    if (modovisualizacion) {
        glutSolidSphere(0.5f, 9, 9);
    } else {
        glutWireSphere(0.5f, 9, 9);
    }

    // Rotaciones para la segunda extremidad
    glRotatef(angulos[1][0], 1.0f, 0.0f, 0.0f); 
    glRotatef(angulos[1][1], 0.0f, 1.0f, 0.0f); 
    glRotatef(angulos[1][2], 0.0f, 0.0f, 1.0f); 

    glPushMatrix();
    glTranslatef(0.0f, -1.5f, 0.0f);
    glScalef(1.0f, 2.0f, 1.0f);

    // Segundo cubo
    if (modovisualizacion) {
        glColor3f(135, 206, 235);
        glutSolidCube(1.0f);
        glColor3f(0.0f, 0.0f, 0.0f); 
        glutWireCube(1.0f); 
    } else {
        glColor3f(135, 206, 235);
        glutWireCube(1.0f); // Solo dibuja el cubo en modo wireframe
    }

    glPopMatrix();
    glTranslatef(0.0f, -3.0f, 0.0f);

    // Tercera esfera
    glColor3f(0.5, 0.5, 1.0);
    if (modovisualizacion) {
        glutSolidSphere(0.4, 9, 9);
    } else {
        glutWireSphere(0.4, 9, 9);
    }
}

void brazoIzquierdo(float translateX, float translateY, float translateZ) {
    extremidades(angulosiz, translateX, translateY, translateZ, 0.5f, 1.0f, 0.4f);
}

void brazoDerecho(float translateX, float translateY, float translateZ) {
    extremidades(angulosdch, translateX, translateY, translateZ, 0.5f, 1.0f, 0.4f);
}

void piernadcha(float translateX, float translateY, float translateZ) {
    extremidades(angulospi, translateX, translateY, translateZ, 0.5f, 1.0f, 0.7f);
}

void piernaiz(float translateX, float translateY, float translateZ) {
    extremidades(angulospd, translateX, translateY, translateZ, 0.5f, 1.0f, 0.7f);
}

void cuerpo(){   // Dibujo la cabeza y cuerpo
    glLoadIdentity();

    glTranslatef(-1.0f,2.0f,0.0f);
    glColor3f(0.5, 0.5, 1.0);
    if(modovisualizacion == false){
        glutWireSphere(1.0f,9,9);
    }else{
        glutSolidSphere(1.0f,9,9);
    }

    glTranslatef(0.0f,-1.0f,-0.2f);

    if(modovisualizacion == false){
        glutWireCube(1.0f);
    }else{
        glutSolidCube(1.0f);
    }

    glLoadIdentity();
    glScalef(3.0,8.0,2.0f);
    glTranslatef(-0.35f,-0.4f,0.0f);

     glColor3f(0.75, 0.85, 1.0);
    if(modovisualizacion == false){
        glutWireCube(1.0f);
    }else{
        glutSolidCube(1.0f);
    }
}

void timerRotation(int value) { // Para que las piernas giren solas
    if (mover) {
        angulospd[0][0] += value;
        angulospd[0][0] = ((int)angulospd[0][0]) % 360;
        angulospi[0][0] += value;
        angulospi[0][0] = ((int)angulospi[0][0]) % 360;
    }
    if (temporizadorActivo) {  // Solo llamo a glutTimerFunc si el temporizador está activo
        glutTimerFunc(velocidad, timerRotation, 5);
    }
}

void display(){                 // Dibujamos toda la figura
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    brazoIzquierdo(0.5f,0.5f,1.0f);
    brazoDerecho(-2.5f,0.5f,1.0f);
    cuerpo();
    piernadcha(0.0f,-7.0f,1.0f);
    piernaiz(-2.1f,-7.0f,1.0f);
    glutSwapBuffers();
}

void idle(){                    // Llamamos a display para actualizar la imagen
    display();
}

void menu_1(int id){

    switch (id)
    {
    default:
        break;
    }
}

void menu_2(int id){
    switch (id)
    {
    case 0: 
        velocidad = 10;  // Velocidad rápida
        break;
    case 1:
        velocidad = 100;  // Velocidad media
        break;
    case 2:
        velocidad = 500;  // Velocidad lenta
        break; 
    case 3:
        mover = false;  // Pausar
        break;
    default:
        break;
    }
}

void menu_3(int id){
    switch (id)
    {
    case 0:
        modovisualizacion = true;  // Modo Solid
        break;
    case 1:
        modovisualizacion = false;  // Modo Wire
        break;
    default:
        break;
    }
}

void menu_4(int id) {
    switch (id) {
    case 0:
        mover = true;               // Activar rotación
        temporizadorActivo = true;  // Activar temporizador
        glutTimerFunc(velocidad, timerRotation, 5); 
        break;
    case 1:
        mover = false;              // Detener rotación
        temporizadorActivo = false; 
        break;
    default:
        break;
    }
}
void menu(){

    // Submenú de velocidad 
    int submenu_velocidad;
    submenu_velocidad = glutCreateMenu(menu_2);
    glutAddMenuEntry("Rapido", 0);
    glutAddMenuEntry("Medio", 1);
    glutAddMenuEntry("Lento", 2);
    glutAddMenuEntry("Parar", 3);

    // Submenú de visualización 
    int submenu_visualizacion;
    submenu_visualizacion = glutCreateMenu(menu_3);
    glutAddMenuEntry("Solid", 0);
    glutAddMenuEntry("Wire", 1);


    //Submenú de rotación de las piernas
    int submenu_rotacion = glutCreateMenu(menu_4);
    glutAddMenuEntry("Activar Rotacion", 0);
    glutAddMenuEntry("Detener Rotacion", 1);

    // Menú principal 
    glutCreateMenu(menu_1);
    glutAddSubMenu("Velocidad", submenu_velocidad);          
    glutAddSubMenu("Visualizacion", submenu_visualizacion);  
    glutAddSubMenu("Giro", submenu_rotacion);
    glutAttachMenu(GLUT_RIGHT_BUTTON);                       // Activar menú con el botón derecho
}

void modificarAngulos(GLfloat angulos[2][3], unsigned char key, bool modo) {
    int index = modo ? 1 : 0;  // Seleccionamos si modificar toda la extremidad o solo la parte inferior

    switch (key) {
        case 'q':
            angulos[index][0] += 1;
            break;
        case 'a':
            angulos[index][0] -= 1;
            break;
        case 'w':
            angulos[index][1] += 1;
            break;
        case 's':
            angulos[index][1] -= 1;
            break;
        case 'e':
            angulos[index][2] += 1;
            break;
        case 'd':
            angulos[index][2] -= 1;
            break;
        default:
            break;
    }
}

void keyboardHandler(unsigned char key, int x, int y) {  
    if (key == '1') {                    
        modo = true;  // Modo para rotar solo la parte inferior de la extremidad
    }

    if (key == '0') {                    
        modo = false;  // Modo para rotar toda la extremidad
    }

    if (key == '2') {  // Cambiar el brazo que se está controlando
        brazo = (brazo == 0) ? 1 : 0;
    }

        if (key == 'p') {  // Cambiar a modificar las piernas
        // Elegir qué pierna controlar
        if (brazo == 2) {
            brazo = (brazo == 2) ? 3 : 2;  // Cambia entre 2 (pierna izquierda) y 3 (pierna derecha)
        } else {
            brazo = 2;  // Si no está en modo piernas, cambiar a modo piernas
        }
    }

    if (brazo == 0) {                               // Brazo izquierdo
        modificarAngulos(angulosiz, key, modo);
    } else if (brazo == 1) {                        // Brazo derecho
        modificarAngulos(angulosdch, key, modo);
    } else if (brazo == 2) {                        // Pierna izquierda
        modificarAngulos(angulospi, key, modo);
    } else if (brazo == 3){                         // Pierna derecha
        modificarAngulos(angulospd, key, modo);
    }
}

void reshape(int w, int h) // Tamaño de la ventana, área donde se proyecta...
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);              
    glLoadIdentity();                                   
    glOrtho(-10.0, 10.0, -14.0, 14.0, -14.0, 14.0); 
    glMatrixMode(GL_MODELVIEW);                 

}

void mouseMotionHandler(int x, int y) {  // Para mover las piernas si pulsamos el ratón
    if (ratonPresionado) {
        
        float deltaX = (x - (ancho / 2)) * 0.05; 
        // Mover las piernas alrededor del eje X
        angulospi[0][0] += deltaX;  
        angulospi[1][0] += deltaX;  
        angulospd[0][0] += deltaX;  
        angulospd[1][0] += deltaX;  

        glutPostRedisplay();
    }
}

void mouseButtonHandler(int button, int state, int x, int y) { // Función para detectar si estamos presionando el click
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            ratonPresionado = true;
        } else {
            ratonPresionado = false;
        }
    }
}

void specialKeyHandler(int key, int x, int y) { //Para mover las piernas alrededor del eje X
    switch (key) {
        case GLUT_KEY_LEFT:
            angulospi[0][1] -= 5.0f;
            angulospi[1][1] -= 5.0f;
            angulospd[0][1] -= 5.0f;
            angulospd[1][1] -= 5.0f;
            break;
        case GLUT_KEY_RIGHT:
            angulospi[0][1] += 5.0f;
            angulospi[1][1] += 5.0f;
            angulospd[0][1] += 5.0f;
            angulospd[1][1] += 5.0f;
            break;
    }

    glutPostRedisplay();  
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB| GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(ancho, alto);
    glutCreateWindow("Semana 4");
    glEnable(GL_DEPTH_TEST); 
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboardHandler);
    glutMotionFunc(mouseMotionHandler);  // Para el movimiento del ratón 
    glutMouseFunc(mouseButtonHandler);  // Para detectar movimiento del ratón sin botones presionados
    glutSpecialFunc(specialKeyHandler);  
    menu();
    glutMainLoop();
    return 0;
}
