#include <iostream>
#include <malloc.h>
#include <cstdlib>

using namespace std;

//Estructura del atleta - Fifo
struct atleta{
    char nombre[30];
    int numero;
    float Tvueltas[100];
    int cantidadTiempos;
    int rondas;
    double promedioT;
    atleta *sig;
};

//Apuntadores de las Estructuras
atleta *cab, *aux, *aux2;

int Natletas = 0; //Define el numeros de atletas

//Funcion Registrar - Fifo
int registrar(){
    int volver = 0;
    cout<<"Bienvenido al area de registro"<<endl;
    cout<<"\n";
    do{
        if (cab==NULL){
            //Pide memoria
            cab = (struct atleta *) malloc (sizeof(struct atleta)); //P
                
            cout<<"Ingresa el nombre del atleta: "<<endl;
            cin>>cab->nombre;
            cab-> sig = NULL;
            cout<<"\n";

            cab->numero = rand() %100;
            cout<<"El sigiente numero se le asignara al atleta "<<cab->nombre<<": "<<cab->numero<<endl;
            cab->sig = NULL;

                
        } else{
            //Pide memoria si ya hay un atleta registrado
            aux = (struct atleta *) malloc (sizeof(struct atleta));
                
            cout<<"Ingresa el nombre del siguiente atleta: "<<endl;
            cin>>aux->nombre;
            aux->sig = NULL;
            cout<<"\n";

            aux->numero = rand() % 100;
            cout<<"El sigiente numero se le asignara al atleta "<<aux->nombre<<": "<<aux->numero<<endl;
            aux->sig = NULL;

            aux2 = cab;
            while (aux2->sig!=NULL)    
                aux2 = aux2->sig;
                aux2->sig = aux;
                aux2 = aux = NULL;
                free(aux);
                free(aux2);
        }
        Natletas ++;
        cout<<"\n";
        cout<<"Atleta Registrado."<<endl;
        cout<<"\n";
        cout<<"Desea registrar otro atleta? (1.SI/2.NO)";
        cin>>volver;
    }while(volver!=2);
    return 0;
}

//Funcion Mostrar datos
int mostrar(){
    if(cab!=NULL){
        cout<<"Bienvenido"<<endl;
        cout<<"Hay "<<Natletas<<" Atletas"<<endl;
        for (aux=cab; aux!=NULL; aux = aux->sig)
        {
            cout<<"Nombre: "<<aux->nombre<<endl;
            cout<<"Numero: "<<aux->numero<<endl;
            cout<<"Este atleta no ha hecho vueltas..."<<endl;
            cout<<"\n";
        }
        system("pause");
    }else{
        cout<<"Vacio..."<<endl;
        cout<<"No Se han registrado atletas..."<<endl;
        system("pause");
    }
    return 0;
}

//Menu
int main(){
    int opc = 0;
    do{
        cout<<"\nMenu"<<endl;
        cout<<"1. Registrar atleta"<<endl;
        cout<<"2. Mostrar datos"<<endl;
        cout<<"3. Salir"<<endl;
        cin>>opc;
        switch (opc)
        {
            case 1: registrar(); break;
            case 2: mostrar(); break;
            case 3: cout<<"Adios"; break;
            default:cout<<"Opcion Invalidad."; break;
        }
    }while(opc!=3);
}