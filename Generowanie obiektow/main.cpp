//#define GLEW_STATIC
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
using namespace std;

//#include "Punkty.h"
#include "Bezier.h"


GLuint shaderVert, shaderFrag;	// Shadery
GLuint shaderProg;	// Program
GLboolean dodaj_punkt = true;

char *loadTextFile(const char *fileName) {
	// Otwarcie pliku:
	FILE *plix = fopen(fileName, "rb");
	if(!plix)	return(NULL);

	// Zbadanie rozmiaru pliku:
	unsigned long fSize;
	fseek(plix, 0, SEEK_END);
	fSize = ftell(plix);
	fseek(plix, 0, SEEK_SET);

	// Utworzenie bufora:
	char *buff = (char*)malloc(fSize + 1);
	if(!buff)	return(NULL);

	// Odczyt danych:
	fread(buff, 1, fSize, plix);
	buff[fSize] = 0;	// Terminator
	// Koniec:
	return(buff);
}

bool checkErrors(GLuint object) {
	int res, logLen;
	char buff[1024];

	// SHADER check:
	glGetShaderiv(object, GL_COMPILE_STATUS, &res);
	if(res == GL_FALSE) {	// Sprawdzenie InfoLog
		cout<<"GL_COMPILE_STATUS ERROR!";
		glGetShaderInfoLog(object, 1024, &logLen, buff);
		cout<<buff;
	}

	// PROGRAM check:
	glGetProgramiv(object, GL_LINK_STATUS, &res);
	if(res == GL_FALSE) {
		cout<<"GL_LINK_STATUS ERROR!";
		glGetProgramInfoLog(object, 1024, &logLen, buff);
		cout<<buff;
	}

	return(true);
}

void setupShaders() {
	char *strVert, *strFrag;
	shaderVert = glCreateShader(GL_VERTEX_SHADER);
	shaderFrag = glCreateShader(GL_FRAGMENT_SHADER);

	// Odczyt kodu shaderow z pliku:
	strVert = loadTextFile( "C:\\Users\\DidkowSky\\Desktop\\ProjektyVS12\\Generowanie obiektow\\perpixel_vert.c" );
	if(!strVert) {
		cout<<"** Blad ladowania pliku *.vert"<<endl;
		system("pause");
		exit(EXIT_FAILURE);
	}
	strFrag = loadTextFile( "C:\\Users\\DidkowSky\\Desktop\\ProjektyVS12\\Generowanie obiektow\\perpixel_frag.c" );
	if(!strFrag) {
		cout<<"** Blad ladowania pliku *.frag"<<endl;
		system("pause");
		exit(EXIT_FAILURE);
	}
	// Podanie z kodem zrodlowym:
	glShaderSource(shaderVert, 1, (const GLchar**)(&strVert), NULL);
	glShaderSource(shaderFrag, 1, (const GLchar**)(&strFrag), NULL);
	// Usuniecie kodow:
	free(strVert);free(strFrag);

	// Kompilacja:
	glCompileShader(shaderVert);
	glCompileShader(shaderFrag);

	// Przygotowanie programu:
	shaderProg = glCreateProgram();
	glAttachShader(shaderProg, shaderVert);
	glAttachShader(shaderProg, shaderFrag);
	// Linkowanie i aktywacja:
	glLinkProgram(shaderProg);
	//glUseProgram(shaderProg);

	checkErrors(shaderVert);
	checkErrors(shaderFrag);
}


//===========================================================================================================

GLfloat kat = 0;
GLfloat dodaj_kat = 0.22;
GLfloat katX=0;
GLfloat katY=0;
GLfloat katZ=0;

GLboolean obrot=false;
GLboolean wyswietl_figure = false;

Bezier *bezier = new Bezier();
extern Punkty *punkty;

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,0,0);

    glLoadIdentity();
    gluLookAt (0.0, 0.0, 90.0, 0.0, 0.0, 0.0, 0.0, 2.0, 0.0);

    glPushMatrix();

        glColor3d(0,0,0);
        glBegin(GL_LINES);
            glVertex3d(0, 50, 0);
            glVertex3d(0, -50, 0);
        glEnd();
        glBegin(GL_LINES);
            glVertex3d(50, 0, 0);
            glVertex3d(-50, 0, 0);
        glEnd();
        glPointSize(3);
        glColor3d(1.0,0,0);
        glPushMatrix();
            glRotatef(katX,1,0,0);
            glRotatef(katY,0,1,0);
            glRotatef(katZ,0,0,1);
            glBegin(GL_POINTS);
                punkty->wyswietl_punkty();
				bezier->wyswietl_punkty();
            glEnd();
            glBegin(GL_POINTS);
				bezier->wyswietl_punkty();
            glEnd();
			/*glBegin(GL_LINES);
				punkty->wyswietl_linie();
            glEnd();*/
        if(wyswietl_figure){
			glUseProgram(shaderProg);
            glBegin(GL_QUADS);
                //punkty->wysietl_figure();
				bezier->wysietl_figure();
            glEnd();
			glUseProgram(0);
        }
        glPopMatrix();


    glPopMatrix();

    glutSwapBuffers();
}

// funkcja akcji przyciskow myszy
void mouseClicks(int button, int state, int x, int y) {
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && dodaj_punkt){
        GLfloat x_=(x/(glutGet(GLUT_WINDOW_WIDTH)/100.0))-50;
        GLfloat y_=-(y/(glutGet(GLUT_WINDOW_HEIGHT)/100.0))+50;
        cout<<"x: "<<x_<<" y: "<<y_<<" width: "<<glutGet(GLUT_WINDOW_WIDTH)<<" width: "<<glutGet(GLUT_WINDOW_HEIGHT)<<endl;
        punkty->dodajPunkt(x_,y_);
		//bezier->generujTabliceList();
		bezier->czyscListe();
		for(double i=0; i<1; i+=0.02){
			bezier->liczBezier(punkty->lista, i);
		}
		bezier->wyswietlListe();
        display();
    }
}
static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'x':
			exit(EXIT_SUCCESS);
            break;
        case '+':			
			dodaj_punkt = false;
            if(obrot==false)
                //punkty->generuj();
				bezier->generuj();
            wyswietl_figure = true;
            //punkty.wyswietl();
            obrot=true;
            break;
        case '-':			
			dodaj_punkt = true;
            obrot=false;
            //punkty->czysc();
			bezier->czysc();
            break;
        //obracanie
        case 'w':
            katX+=4;
            break;
        case 'e':
            katY+=4;
            break;
        case 'd':
            katZ+=4;
            break;
        case 's':
            katX-=4;
            break;
        case 'q':
            katY-=4;
            break;
        case 'a':
            katZ-=4;
            break;
        case 'g':
            wyswietl_figure = true;
            break;
        case 'h':
            wyswietl_figure = false;
            break;
        case 'c':            
            punkty->czyscListe();
            break;
        case '9':
            if ((dodaj_kat - 0.1) > 0) {
                dodaj_kat -=0.1;
                cout<<"\nKat: "<< (dodaj_kat/3.14) *180;
                punkty->czysc();
                punkty->generuj();
            }
            break;
        case '0':
            if ((dodaj_kat + 0.1) < 6.27) {
                dodaj_kat +=0.1;
                cout<<"\nKat: "<< (dodaj_kat/3.14) *180;
                punkty->czysc();
                punkty->generuj();
            }
            break;
    }

    glutPostRedisplay();
}

static void resize(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
	glOrtho(-50,50, -50, 50, 2.0, 300.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity() ;
	display();
}

void idle(){
    glutSwapBuffers();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */

int main(int argc, char *argv[])
{

    glutInit(&argc, argv);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(700,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Projekt");
	//punkty->wypelnijPrzykladowe();

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    //glutIdleFunc(idle);
    glutMouseFunc(mouseClicks);
    glutKeyboardFunc(key);


    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);


    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);


    GLenum err = glewInit();
//sprawdzenie glew
    if(GLEW_OK != err) {
		cout<<"*** Brak wsparcia dla OpenGL w wersji 3.1!";
		exit(0);
	}

    // Ustawienia OpenGL
	setupShaders();

    glutMainLoop();

    return EXIT_SUCCESS;
}
