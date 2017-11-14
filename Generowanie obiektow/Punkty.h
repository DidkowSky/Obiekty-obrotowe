#include <vector>
#include <iostream>
#include <math.h>
#include <GL/glut.h>

using namespace std;

struct punkt{
    GLfloat x;
    GLfloat y;
    GLfloat z;

	punkt() : x(0.0),
			y(0.0),
			z(0.0){}
};

class Punkty
{
	public:
		vector<punkt> lista;
		GLuint ile_punkt;

		Punkty();
		void dodajPunkt(GLfloat, GLfloat);    
		bool isEmpty();
		void wyswietl_punkty();
		void wyswietl_linie();
		void wysietl_figure();
		void generuj();
		void czysc();
		void czyscListe();
		vector<punkt> kopiujListe();
		void wypelnijPrzykladowe();
};