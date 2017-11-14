#include <vector>

#include "Punkty.h"

using namespace std;

class Bezier
{
	public:
		vector<punkt> lista_B;
		int ile_punkt;

		Bezier();
		int factorial(int);
		float binomial_coff(float, float);
		void liczBezier(vector<punkt>, double);
		void generuj();
		void wyswietlListe();
		void wyswietl_punkty();
		void wysietl_figure();
		void czysc();
		void czyscListe();
		void wyswietl_ile();
};