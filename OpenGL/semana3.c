//Estela Pillo González

#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdbool.h>

#define ancho 500
#define alto 500


GLfloat angulos[2][3];          //matriz para almacenar los ángulos de rotación de los cubos
GLboolean modo = false;         //variable de control para decidir si movemos toda la pierna o solo una parte

void init()
{
    glClearColor(0.0f,0.0f,0.0f,0.0f); //color de fondo
}

void display(){ 

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //borrar el frame buffer

    glLoadIdentity();  

    glTranslatef(0.0f, 0.0f, -5.0f);
    glColor3f(1.0f, 0.5f, 0.5f);
    glutWireSphere(0.5f, 9, 9);        //esfera de radio 0.5 (cadera)

    glLoadIdentity();                  //restablece la matriz actual a la matriz identidad
 
    glRotatef(angulos[0][0], 1.0f, 0.0f, 0.0f); //rotación sobre eje x
    glRotatef(angulos[0][1], 0.0f, 1.0f, 0.0f); //rotación sobre eje y
    glRotatef(angulos[0][2], 0.0f, 0.0f, 1.0f); //rotación sobre eje z

    glTranslatef(0.0, -1.0, 0.0f);     //trasladamos la escena una unidad más abajo
    
    glColor3f(1.0f, 0.0f, 1.0f);
    glutWireCube(1.0f);                //cubo de lado 1 (muslo)

    glTranslatef(0.0f,-1.0f,0.0f);   
    glColor3f(1.0f, 0.5f, 0.5f);
    glutWireSphere(0.5f, 9, 9);        //dibujamos la segunda esfera (rodilla)

    glRotatef(angulos[1][0], 1.0f, 0.0f, 0.0f);
    glRotatef(angulos[1][1], 0.0f, 1.0f, 0.0f);
    glRotatef(angulos[1][2], 0.0f, 0.0f, 1.0f);

    glTranslatef(0.0f,-1.0f,0.0f); 
    glColor3f(1.0f, 0.0f, 1.0f);
    glutWireCube(1.0f);                //dibujamos el otro cubo (pierna)

    glutSwapBuffers();
 
}

void idle(){                           //llamamos a display para actualizar la imagen
    display();
}

void keyboardHandler(unsigned char key, int x, int y ){     //para manejar las entradas del teclado

    if(key == '1'){                    //cambiamos de modo para mover solo la parte inferior de la pierna
        modo = true;
    }

    if(key == '0'){                    //modo predeterminado: mover toda la pierna
        modo = false;
    }

    if(modo==false){                   //opción 1: rotación de toda la pierna
        switch(key){   
            case 'q':
                angulos[0][0]+=1;
                break;
            case 'a':
                angulos[0][0]-=1;
                break;
            case 'w':
                angulos[0][1]+=1;
                break;
            case 's':
                angulos[0][1]-=1;
                break;
            case 'e':
                angulos[0][2]+=1;
                break;
            case 'd':
                angulos[0][2]-=1;
                break;
            default:
                break;
        }
    }

    if(modo == true){                  //opción 2: rotación solo de la parte inferior
        switch(key){    
            case 'q':
                angulos[1][0]+=1;
                break;
            case 'a':
                angulos[1][0]-=1;
                break;
            case 'w':
                angulos[1][1]+=1;
                break;
            case 's':
                angulos[1][1]-=1;
                break;
            case 'e':
                angulos[1][2]+=1;
                break;
            case 'd':
                angulos[1][2]-=1;
                break;
            default:
                break;
        }
    }
}

void reshape(int w, int h) //tamaño de ventana, área donde proyectamos...
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);              
    glLoadIdentity();                           //restablecer a matriz identidad
    glOrtho(-4.0, 4.0, -4.0, 4.0, -8.0, 8.0);
    glMatrixMode(GL_MODELVIEW);                 

}


int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB| GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(ancho, alto);
    glutCreateWindow("Pierna");
    glEnable(GL_DEPTH_TEST);                    //activar z-buffer
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboardHandler);
    glutMainLoop();
    return 0;
}
