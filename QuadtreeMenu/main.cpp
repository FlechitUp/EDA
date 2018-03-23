#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <algorithm>

using namespace std;

int threshold;

void setThreshold(int &thrS,int val){
    thrS = val;
}

class Point{
public:
    float x,y;
    Point(float _x, float _y)
	{
		x = _x;
		y = _y;
	}
	Point()
	{
		x = 0;
		y = 0;
	}
};



class quadTree {
public:
    Point topLeft;
    Point botRight;

    vector <Point*> cantPoints; //por cantidad de ountos
    vector <quadTree*> sons;    //[0]arribaIzq, [1] arrDerec , [2] abajoIzq, [3]abajoDer
    int cont;

    quadTree(){
        cont = 0;
        for (int i=0 ; i<4 ; i++ ){
            sons.push_back(NULL);
        }
    }

    quadTree(Point topL, Point botR){
        topLeft = topL;
        botRight = botR;
        cont = 0;
        for (int i=0 ; i<4 ; i++ ){
            sons.push_back(NULL);
        }
    }

    void insert(Point*);
    bool find(Point);
    bool findPointInvect(Point);
    void setParameters(Point,Point);
    void readFile(string);
    void printLimites();
    bool enQuad(Point);
};

void quadTree::printLimites(){
    cout<<"Limit Quad: ("<<topLeft.x<<","<<topLeft.y<<")  ("<<botRight.x<<","<<botRight.y<<" )"<<endl;
}
void quadTree::setParameters(Point a,Point b){
    topLeft = a;
    botRight = b;
}

void quadTree::readFile(string nameFile){
    ifstream infile(nameFile);

    float X,Y, Lx, Ly, Rx, Ry;
    infile>>Lx>>Ly >>Rx >>Ry ;  ///obtengo los puntos limites de todo el mapa
    //quadTree root(Point(Lx, Ly), Point(Rx, Ry));
    setParameters(Point(Lx, Ly), Point(Rx, Ry));
    while(infile >>X >> Y){
        insert(new Point(X,Y));
    }
}

bool quadTree::enQuad(Point p){
    return (p.x >= topLeft.x &&
        p.x <= botRight.x &&
        p.y <= topLeft.y &&
        p.y >= botRight.y);
}


void quadTree::insert(Point *pointI){

    //No pertence a este quad
    if(!enQuad(*pointI)){
        ///cout<<"   punto " <<pointI->x <<","<<pointI->y <<" NO Pertenece a quad"<<endl;
        return;
    }
    else {
        ///cout<<"push "<<endl;
        if(!findPointInvect(*pointI)){
            cantPoints.push_back(pointI);
            cont ++;
        }
        else{
        if(cantPoints.size() > threshold || cont>threshold ){
            ///cout<<"reordenar"<<endl;
            for(int i = 0 ; i < cantPoints.size() ; i++){
                // si esta en el lado izquierd
                if ((topLeft.x + botRight.x) / 2 >= cantPoints[i]->x){   //pointI->x
                    //Si esta arriba a la izquierda
                    if ((topLeft.y + botRight.y) / 2 <= cantPoints[i]->y){
                        ///cout<<"  sons[0] "<<endl;
                        if (sons[0] == NULL){ //sons[0] topLeftTree
                            sons[0] = new quadTree(
                                Point(topLeft.x, topLeft.y),
                                Point((topLeft.x + botRight.x) / 2,
                                    (topLeft.y + botRight.y) / 2));
                        }
                        sons[0] ->insert(cantPoints[i]);
                    }

                    // si esta en la izquierda abajo
                    else{
                        if (sons[2]  == NULL){
                        sons[2]  = new quadTree(  //sons[2] botLeftTree
                            Point(topLeft.x,(topLeft.y + botRight.y) / 2),
                            Point((topLeft.x + botRight.x) / 2,botRight.y));
                        }
                        sons[2] ->insert(cantPoints[i]);
                    }
                }
                else{
                    // si esta arriba a la derecha
                    if ((topLeft.y + botRight.y) / 2 <= cantPoints[i]->y){
                        ///cout<<"  sons[1] "<<endl;
                        if (sons[1] == NULL){ //sons[1] topRightTree
                            sons[1] = new quadTree(
                            Point((topLeft.x + botRight.x) / 2,topLeft.y),
                            Point(botRight.x,(topLeft.y + botRight.y) / 2));
                        }
                        sons[1]->insert(cantPoints[i]);
                    }

                    ///si esta abajo a la derecha
                    else{
                        if (sons[3] == NULL){
                            ///cout<<"  sons[3] "<<endl;
                            sons[3] = new quadTree( //sons[3] botRightTree
                                Point((topLeft.x + botRight.x) / 2,(topLeft.y + botRight.y) / 2),
                                Point(botRight.x, botRight.y));
                        }
                        sons[3]->insert(cantPoints[i]);
                    }
                }
            }
            cantPoints.clear();
        }
        }
    }

}

bool quadTree::findPointInvect(Point pointI){
    for (int i=0; i< cantPoints.size() ; i++){
        if (cantPoints[i]->x == pointI.x && cantPoints[i]->y == pointI.y){
            return true;
        }
    }
    return false;
}

bool quadTree::find(Point pointI){
    if(!enQuad(pointI)){
        cout<<"El punto no esta en los limites"<<endl;
        return false;
    }
    //printLimites();
    //si esta en la izquierda
    if ((topLeft.x + botRight.x) / 2 >= pointI.x){

        if ((topLeft.y + botRight.y) / 2 <= pointI.y){   //esta arriba / en sons[0]
            cout<<" 0 - ";
            //printLimites();
            if(sons[0]==NULL){
                return findPointInvect(pointI);
            }
            return sons[0]->find(pointI);
        }
        else{                                       //esta abajo / en sons[1]
            cout<<" 2 - ";
            //printLimites();
            if(sons[2]==NULL){
                return findPointInvect(pointI);
            }
            return sons[2]->find(pointI);;

        }
    }
    else{  //esta en el lado derecho
        if ((topLeft.y + botRight.y) / 2 <= pointI.y){   //esta arriba / en sons[1]
            cout<<" 1 - ";
            //printLimites();
            if (sons[1] == NULL){
                return findPointInvect(pointI);
            }
            return sons[1]->find(pointI);;
        }
        else{                                           //esta abajo / en sons[3]
            cout<<" 3 - ";
            //printLimites();
            if (sons[3] == NULL){
                return findPointInvect(pointI);
            }
            return sons[3]->find(pointI);
        }
    }
};

void printOptions(){
    cout<<"Elija una opcion"<<endl;
    cout<<"1. Insertar Puntos manualmente"<<endl;
    cout<<"2. Insertar Puntos por archivo"<<endl;
}

int main()
{
    int opI;
    int thrShI = 1;
    float Ix,Iy, Lix, Liy, Rdx, Rdy;
    int Ncant, var;
    cout<<"Quadtreee"<<endl;
    cout<<"Ingrese threshold "<<endl;
    cin >> thrShI;
    setThreshold(threshold, thrShI);

    printOptions();
    cin >> opI;
    if (opI == 1){
        cout<<"Ingresar Limite Izquierdo Arriba "<<endl<<"x = ";
        cin >> Lix;
        cout<<"y =";
        cin >> Liy;
        cout<<"Ingresar Limite Izquierdo Abajo "<<endl<<"x = ";
        cin >> Rdx;
        cout<<"y =";
        cin >> Rdy;
        quadTree root(Point(Lix, Liy), Point(Rdx, Rdy));

        while(true){
            cout<<" 1. Ingresar punto"<<endl;
            cout<<" 2. Buscar punto"<<endl;
            cout<<" 3. Exit"<<endl;
            cin >> opI;
            if(opI == 1){
                cout<<"Ingresar x ";
                cin >>Ix;
                cout<<"Ingresar y ";
                cin >> Iy;
                root.insert(new Point(Ix,Iy));
            }
            if(opI == 2){
                cout<<"Punto a Buscar :"<<endl;
                cout<<"Ingresar x ";
                cin >>Ix;
                cout<<"Ingresar y ";
                cin >> Iy;
                root.find(Point(Ix,Iy));
            }
            if(opI == 3){
                break;
            }

        }


    }
    else{
        if(opI == 2){
            string File;
            cout<<" Ingrese nombre de archivo (ej a1.txt)"<<endl;
            cin >>File;
            quadTree root;
            root.readFile(File);
            //root.
            while(true){
                cout<<endl<<"1. Buscar punto"<<endl;
                cout<<"2. Salir"<<endl;
                cin >> opI;
                if(opI ==1){
                    cout<<"Buscar punto"<<endl<<"x=";
                    cin >> Ix;
                    cout<< "y=";
                    cin >> Iy;
                    if (root.find(Point(Ix,Iy))){
                        cout<<"encontrado "<<endl;
                    }
                    else{cout<<"no encontrado"<<endl;}
                }
                else{
                    break;
                }

            }
        }

    }

    return 0;
}
