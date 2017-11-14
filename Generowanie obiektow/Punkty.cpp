#include "Punkty.h"

extern GLboolean obrot;
extern GLfloat kat;
extern GLfloat dodaj_kat;

Punkty::Punkty(void){
	ile_punkt = 0;
}

void Punkty::dodajPunkt(GLfloat x,GLfloat y){
    punkt p;
    p.x=x;
    p.y=y;
    p.z=0;
    lista.push_back(p);
    ile_punkt++;
}

bool Punkty::isEmpty(){
    return lista.empty();
}

void Punkty::wyswietl_punkty(){
    for(unsigned int i=0; i<lista.size(); i++){
        GLfloat x=lista[i].x;
        GLfloat y=lista[i].y;
        GLfloat z=lista[i].z;
        //cout<<"rysowanie: "<<"x: "<<x<<" y: "<<y<<" z: "<<z<<endl;
        if(obrot==false)
            glVertex2d(x,y);
        else{

            //glVertex3f(x,y,z);
        }
    }
    //cout<<"Dodales "<<ile_punkt<<" punktow."<<endl;
}

void Punkty::wyswietl_linie(){
	//cout<<"wielkosc listy: "<<lista.size()<<endl;
	if (lista.size() < 1)
		return;

    for(GLuint i=0; i<(lista.size()-1); i++){
        GLfloat x=lista[i].x;
        GLfloat y=lista[i].y;
        GLfloat z=lista[i].z;
        GLfloat x2=lista[i+1].x;
        GLfloat y2=lista[i+1].y;
        GLfloat z2=lista[i+1].z;
        //cout<<"rysowanie: "<<"x: "<<x<<" y: "<<y<<" z: "<<z<<endl;
        //cout<<"rysowanie: "<<"x: "<<x2<<" y: "<<y2<<" z: "<<z2<<endl;
        if(obrot==false){
            glVertex2f(x,y);
            glVertex2f(x2,y2);
		}else{

            //glVertex3f(x,y,z);
        }
    }
    //cout<<"Dodales "<<ile_punkt<<" punktow."<<endl;
}
void Punkty::wysietl_figure(){

    for(unsigned long long j = 0; j < lista.size(); j = j + ile_punkt){
        for(GLuint i = 0; i < ile_punkt -1; i++){

            if((i + j + ile_punkt + 1) > lista.size()){


                GLfloat x1=lista[i + j].x;
                GLfloat y1=lista[i + j].y;
                GLfloat z1=lista[i + j].z;

                GLfloat x2=lista[i].x;
                GLfloat y2=lista[i].y;
                GLfloat z2=lista[i].z;

                GLfloat x3=lista[i + j + 1].x;
                GLfloat y3=lista[i + j + 1].y;
                GLfloat z3=lista[i + j + 1].z;

                GLfloat x4=lista[i+ 1].x;
                GLfloat y4=lista[i + 1].y;
                GLfloat z4=lista[i + 1].z;

                glNormal3f(x2,y2,z2);
                glVertex3f(x2, y2, z2);
                glNormal3f(x1,y1,z1);
                glVertex3f(x1, y1, z1);
                glNormal3f(x3,y3,z3);
                glVertex3f(x3, y3, z3);
                glNormal3f(x4,y4,z4);
                glVertex3f(x4, y4, z4);


            }else{

                GLfloat x1=lista[i + j].x;
                GLfloat y1=lista[i + j].y;
                GLfloat z1=lista[i + j].z;

                GLfloat x2=lista[i + j + ile_punkt].x;
                GLfloat y2=lista[i + j + ile_punkt].y;
                GLfloat z2=lista[i + j + ile_punkt].z;

                GLfloat x3=lista[i + j + 1].x;
                GLfloat y3=lista[i + j + 1].y;
                GLfloat z3=lista[i + j + 1].z;

                GLfloat x4=lista[i + j + ile_punkt + 1].x;
                GLfloat y4=lista[i + j + ile_punkt + 1].y;
                GLfloat z4=lista[i + j + ile_punkt + 1].z;

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

void Punkty::generuj(){
    kat = 0;
    while(true){
        kat += dodaj_kat;
        if (kat > 6.27) break;

        for(GLuint i=0; i<ile_punkt; i++){
            GLfloat x=lista[i].x;
            GLfloat y=lista[i].y;
            GLfloat z=lista[i].z;

            punkt p;
            p.x = x *cos(kat) + z *sin(kat);
            p.y = y;
            p.z = -x *sin(kat) + z *cos(kat);
            lista.push_back(p);

            //cout<<"rysowanie: "<<"x: "<<x<<" y: "<<y<<endl;
        }
    }
}

//Wyczyszczenie punktów innych ni¿ wprowadzonych kursorem
void Punkty::czysc(){

    while(lista.size() > ile_punkt){
        lista.pop_back();
    }

}

//wyczyszczenie calej listy
void Punkty::czyscListe(){

	ile_punkt = 0;
    while(lista.size() > 0){
        lista.pop_back();
    }

}

vector<punkt> Punkty::kopiujListe(){
	return lista;
}

void Punkty::wypelnijPrzykladowe(){
	punkt p;

	p.x = 13;
	p.y = 30;
	lista.push_back(p);
	p.x = 33;
	p.y = 5;
	lista.push_back(p);
	p.x = 19;
	p.y = -24;
	lista.push_back(p);
	p.x = 14;
	p.y = -41;
	lista.push_back(p);	
	
}