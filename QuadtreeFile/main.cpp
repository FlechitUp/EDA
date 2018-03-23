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

    //Point *pt;
    vector <Point*> cantPoints; //por cantidad de ountos
    vector <quadTree*> sons; //[0]arribaIzq, [1] arrDerec , [2] abajoIzq, [3]abajoDer
    int cont;

    /*quadTree(){
        topLeft = Point(-180,90);
        botRight = Point(180,-90);
        cont = 0;
        //pt = NULL;
        for (int i=0 ; i<4 ; i++ ){
            sons.push_back(NULL);
        }
    }*/
    quadTree(Point topL, Point botR){
        //pt = NULL;
        topLeft = topL;
        botRight = botR;
        //threshold = nro;
        cont = 0;
        for (int i=0 ; i<4 ; i++ ){
            sons.push_back(NULL);
        }
    }

    void insert(Point*);
    bool find(Point);
    bool findPointInvect(Point);
    void readFile();
    void printLimites();
    bool enQuad(Point);
};

void quadTree::printLimites(){
    cout<<"Limit Quad: ("<<topLeft.x<<","<<topLeft.y<<")  ("<<botRight.x<<","<<botRight.y<<" )"<<endl;
}

bool quadTree::enQuad(Point p){
    return (p.x >= topLeft.x &&
        p.x <= botRight.x &&
        p.y <= topLeft.y &&
        p.y >= botRight.y);
}


void quadTree::insert(Point *pointI){

    ///cout<<"Actual Quad: ("<<topLeft.x<<","<<topLeft.y<<")  ("<<botRight.x<<","<<botRight.y<<" )"<<endl;
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

        if(cantPoints.size() > threshold || cont>threshold ){

            ///cout<<"reordenar"<<endl;
            for(int i = 0 ; i < cantPoints.size() ; i++){
                // si esta en el lado izquierd
                if ((topLeft.x + botRight.x) / 2 >= cantPoints[i]->x){   //pointI->x
                    // Indicates topLeftTree
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

                    // Indicates botLeftTree
                    else{
                        ///cout<<"  sons[2] "<<endl;
                        if (sons[2]  == NULL){
                        sons[2]  = new quadTree(  //sons[2] botLeftTree
                            Point(topLeft.x,
                                (topLeft.y + botRight.y) / 2),
                            Point((topLeft.x + botRight.x) / 2,
                                botRight.y));
                        }
                        sons[2] ->insert(cantPoints[i]);
                    }
                }
                else{
                    // Indicates topRightTree
                    if ((topLeft.y + botRight.y) / 2 <= cantPoints[i]->y){
                        ///cout<<"  sons[1] "<<endl;
                        if (sons[1] == NULL){ //sons[1] topRightTree
                            sons[1] = new quadTree(
                            Point((topLeft.x + botRight.x) / 2,topLeft.y),
                            Point(botRight.x,(topLeft.y + botRight.y) / 2));
                        }
                        sons[1]->insert(cantPoints[i]);
                    }

                    // Indicates botRightTree
                    else{
                        if (sons[3] == NULL){
                            ///cout<<"  sons[3] "<<endl;
                            sons[3] = new quadTree( //sons[3] botRightTree
                                Point((topLeft.x + botRight.x) / 2,(topLeft.y + botRight.y) / 2),
                                Point(botRight.x, botRight.y));
                            ///cout<<"  -> ("<< (topLeft.x + botRight.x) / 2<<" , " << (topLeft.y + botRight.y) / 2<<")";
                            ///cout<<" , ("<<botRight.x<<" , "<< botRight.y<<")"<<endl;
                        }
                        sons[3]->insert(cantPoints[i]);
                    }
                }
            }
            cantPoints.clear();
        }

    }

}

bool quadTree::findPointInvect(Point pointI){
    for (int i=0; i< cantPoints.size() ; i++){
        if (cantPoints[i]->x == pointI.x && cantPoints[i]->y == pointI.y){
            return true;
        }
    }
    //cout<<" el punto no existe"<<endl;
    return false;
}

bool quadTree::find(Point pointI){
    if(!enQuad(pointI)){
        cout<<"El punto no esta en los limites"<<endl;
        return false;
    }
    /*if (pt != NULL){
        return pt;
    }*/
    //printLimites();
    //si esta en la izquierda
    if ((topLeft.x + botRight.x) / 2 >= pointI.x){

        if ((topLeft.y + botRight.y) / 2 <= pointI.y){   //esta arriba / en sons[0]
            cout<<" 0 - ";
            printLimites();
            if(sons[0]==NULL){
                if(findPointInvect(pointI)){

                    return true;
                }
                cout<<" no se encontro"<<endl;
                return false;
            }
            return sons[0]->find(pointI);
        }
        else{                                       //esta abajo / en sons[1]
            cout<<" 2 - ";
            printLimites();
            if(sons[2]==NULL){
                if(findPointInvect(pointI)){
                    return true;
                }
                cout<<" no se encontro"<<endl;
                return false;
            }
            return sons[2]->find(pointI);;

        }
    }
    else{  //esta en el lado derecho
        if ((topLeft.y + botRight.y) / 2 <= pointI.y){   //esta arriba / en sons[1]
            cout<<" 1 - ";
            printLimites();
            if (sons[1] == NULL){
                if(findPointInvect(pointI)){
                    return true;
                }
                cout<<" no se encontro"<<endl;
                return false;
            }
            return sons[1]->find(pointI);;
        }
        else{                                           //esta abajo / en sons[3]
            cout<<" 3 - ";
            printLimites();
            if (sons[3] == NULL){
                if(findPointInvect(pointI)){
                    return true;
                }
                cout<<" no se encontro"<<endl;
                return false;
            }
            return sons[3]->find(pointI);
        }
    }
};

int main()
{
    int thrShI = 1;
    setThreshold(threshold, thrShI);
    float Ix,Iy, Lix, Liy, Rdx, Rdy;
    int Ncant, var;
    cin >> Lix>>Liy>> Rdx >>Rdy ;
    cin >> Ncant;
    cout<<"cantidad "<<Ncant<<endl;
    quadTree root(Point(Lix, Liy), Point(Rdx, Rdy));

    while(Ncant--){
        cin >>Ix>> Iy;
        cout<<Ix<<","<<Iy<<endl;
        root.insert(new Point(Ix,Iy));
        //Ncant--;

    }
    cout<<"ok"<<Ncant<<endl;
    Point p1(41.31666667,19.816667);
    root.find(p1);

/*
    char** pEnd;
    for (std::string linea; std::getline(myReadFile, linea); ){
        std::stringstream registro(linea);
        string dato;

        for (int colum=0 ; std::getline(registro, dato, ',');++colum ){
            if (colum ==2){

            stringstream ss(dato);
                Ix = strtof(ss>>dato);
            }
            if (colum ==3){
                Iy = strtof(dato);
            }
            //cout << dato << endl;
        }
        mypoints.push_back(Point(Ix,Iy));
        //cout <<endl;

    }

    myReadFile.close();
*/
    return 0;
}



/****
 int thrShI = 1;
    setThreshold(threshold, thrShI);

    quadTree root(Point(-180, 90), Point(180, -90));
    Point p(170,45);
    Point a(100,50);
    Point c(-30,50);
    Point b(-75,-10);
    Point d(175,40);

    root.insert(&p);
    root.insert(&a);
    root.insert(&c);
    root.insert(&b);
    root.insert(&d);

    cout<<"Buscar p"<<endl;
    root.find(p);
    cout<<endl;

    cout<<"Buscar a"<<endl;
    root.find(a);
    cout<<endl;

    cout<<"Buscar c"<<endl;
    root.find(c);
    cout<<endl;

    cout<<"Buscar b"<<endl;
    root.find(b);
    cout<<endl;

    cout<<"Buscar d"<<endl;
    root.find(d);
    cout<<endl;
**/
