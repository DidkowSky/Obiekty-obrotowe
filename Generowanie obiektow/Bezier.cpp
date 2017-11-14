#include "Bezier.h"

Punkty *punkty = new Punkty();
extern GLboolean obrot;
extern GLfloat kat;
extern GLfloat dodaj_kat;

//vector<ListaB> listaB; //tablica z listami koeljnych prostych do wyliczania punktow 

Bezier::Bezier(void){

}

int Bezier::factorial(int n)
{
    if (n<=1)
        return(1);
    else
        n=n*factorial(n-1);
    return n;
}

float Bezier::binomial_coff(float n,float k)
{
    float ans;
    ans = factorial(n) / (factorial(k)*factorial(n-k));
    return ans;
}

void Bezier::liczBezier(vector<punkt> PT, double t){

	if(PT.size() < 4)
		return;

	punkt P;

	for(int i=0;i<punkty->lista.size();i++)
    {
        P.x = P.x + binomial_coff((float)(punkty->lista.size() - 1), (float)i) * pow(t, (double)i) * pow((1 - t), (punkty->lista.size() - 1 - i)) * PT[i].x;
        P.y = P.y + binomial_coff((float)(punkty->lista.size() - 1), (float)i) * pow(t, (double)i) * pow((1 - t), (punkty->lista.size() - 1 - i)) * PT[i].y;
    }

	lista_B.push_back(P);
	ile_punkt = lista_B.size();
}

void Bezier::generuj(){
    kat = 0;
    while(true){
        kat += dodaj_kat;
        if (kat > 6.27) break;

        for(GLuint i=0; i<ile_punkt; i++){
            GLfloat x=lista_B[i].x;
            GLfloat y=lista_B[i].y;
            GLfloat z=lista_B[i].z;

            punkt p;
            p.x = x *cos(kat) + z *sin(kat);
            p.y = y;
            p.z = -x *sin(kat) + z *cos(kat);
            lista_B.push_back(p);

            //cout<<"rysowanie: "<<"x: "<<x<<" y: "<<y<<endl;
        }
    }
}

void Bezier::wyswietlListe(){
	cout<<"Lista Bezier:"<<endl<<endl;
	for(int i = 0; i < lista_B.size(); i++){
		cout << "x: " << lista_B[i].x << " y: " << lista_B[i].y << " z: " << lista_B[i].z <<endl;
	}
}

void Bezier::wyswietl_punkty(){
    for(unsigned int i=0; i<lista_B.size(); i++){
        GLfloat x=lista_B[i].x;
        GLfloat y=lista_B[i].y;
        GLfloat z=lista_B[i].z;
        //cout<<"rysowanie: "<<"x: "<<x<<" y: "<<y<<" z: "<<z<<endl;
        if(obrot==false)
            glVertex2d(x,y);
        else{

            //glVertex3f(x,y,z);
        }
    }
    //cout<<"Dodales "<<ile_punkt<<" punktow."<<endl;
}

void Bezier::wysietl_figure(){

    for(unsigned long long j = 0; j < lista_B.size(); j = j + ile_punkt){
        for(GLuint i = 0; i < ile_punkt -1; i++){

            if((i + j + ile_punkt + 1) > lista_B.size()){


                GLfloat x1=lista_B[i + j].x;
                GLfloat y1=lista_B[i + j].y;
                GLfloat z1=lista_B[i + j].z;

                GLfloat x2=lista_B[i].x;
                GLfloat y2=lista_B[i].y;
                GLfloat z2=lista_B[i].z;

                GLfloat x3=lista_B[i + j + 1].x;
                GLfloat y3=lista_B[i + j + 1].y;
                GLfloat z3=lista_B[i + j + 1].z;

                GLfloat x4=lista_B[i+ 1].x;
                GLfloat y4=lista_B[i + 1].y;
                GLfloat z4=lista_B[i + 1].z;

                glNormal3f(x2,y2,z2);
                glVertex3f(x2, y2, z2);
                glNormal3f(x1,y1,z1);
                glVertex3f(x1, y1, z1);
                glNormal3f(x3,y3,z3);
                glVertex3f(x3, y3, z3);
                glNormal3f(x4,y4,z4);
                glVertex3f(x4, y4, z4);


            }else{

                GLfloat x1=lista_B[i + j].x;
                GLfloat y1=lista_B[i + j].y;
                GLfloat z1=lista_B[i + j].z;

                GLfloat x2=lista_B[i + j + ile_punkt].x;
                GLfloat y2=lista_B[i + j + ile_punkt].y;
                GLfloat z2=lista_B[i + j + ile_punkt].z;

                GLfloat x3=lista_B[i + j + 1].x;
                GLfloat y3=lista_B[i + j + 1].y;
                GLfloat z3=lista_B[i + j + 1].z;

                GLfloat x4=lista_B[i + j + ile_punkt + 1].x;
                GLfloat y4=lista_B[i + j + ile_punkt + 1].y;
                GLfloat z4=lista_B[i + j + ile_punkt + 1].z;

                glNormal3f(x2,y2,z2);
                glVertex3f(x2, y2, z2);
                glNormal3f(x1,y1,z1);
                glVertex3f(x1, y1, z1);
                glNormal3f(x3,y3,z3);
                glVertex3f(x3, y3, z3);
                glNormal3f(x4,y4,z4);
                glVertex3f(x4, y4, z4);
            }
        }
    }
}

void Bezier::czysc(){
	while(lista_B.size() > ile_punkt){
			lista_B.pop_back();
		}
}

void Bezier::czyscListe(){
	while(lista_B.size() > 0){
        lista_B.pop_back();
    }
}

void Bezier::wyswietl_ile(){
	cout<<"Bezier wyswietl: "<<punkty->ile_punkt<<endl;
}