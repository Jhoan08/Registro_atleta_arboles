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

//Estructura de promedios - Arbol
struct promedio{
    int numero;
    double promedioT;
    promedio *izq;
    promedio *der;
};

//Apuntadores de las Estructuras
atleta *cab, *aux, *aux2;
promedio *raiz, *auxP, *aux2P;

int Natletas = 0; //Define el numeros de atletas
int encontrado = 0;

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
            cout<<"\n";

            cab->numero = rand() %100;
            cout<<"El sigiente numero se le asignara al atleta "<<cab->nombre<<": "<<cab->numero<<endl;

            cab->cantidadTiempos = 0;

            cab->rondas = 0;
            cab->sig = NULL;    
        } else{
            //Pide memoria si ya hay un atleta registrado
            aux = (struct atleta *) malloc (sizeof(struct atleta));
                
            cout<<"Ingresa el nombre del siguiente atleta: "<<endl;
            cin>>aux->nombre;
            cout<<"\n";

            aux->numero = rand() % 100;
            cout<<"El sigiente numero se le asignara al atleta "<<aux->nombre<<": "<<aux->numero<<endl;

            aux->rondas = 0;

            aux->cantidadTiempos = 0;
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

//Funcion Posicion
int posicionar(){
    if(auxP->promedioT < aux2P->promedioT){
        if(aux2P->izq!=NULL){
            aux2P = aux2P->izq;
            posicionar();
        }
        else
            aux2P->izq = auxP;
    }
    else if(auxP->promedioT > aux2P->promedioT){
        if(aux2P->der!=NULL){
            aux2P = aux2P->der;
            posicionar();
        }
        else
            aux2P->der = auxP;
    }
}

//Funcion Promedio
int ArbolPromedio(){
    auxP = (struct promedio *) malloc (sizeof(struct promedio));
    auxP->promedioT = aux->promedioT;
    auxP->numero = aux->numero;
    auxP->izq = auxP->der = NULL;
    if(raiz==NULL){
        raiz = auxP;
        auxP = NULL;
        free(auxP);
    }
    else{
        aux2P = raiz;
        posicionar();
    }
}

//Recorrer arbol
int ubicar(promedio *recursive, int N_corredor){
    if(recursive->numero == N_corredor){
        recursive->promedioT = aux->promedioT;
        encontrado = 1;
    }
    else{
        if(recursive->izq!=NULL){
            ubicar(recursive->izq, N_corredor);
        }
        if(recursive->der!=NULL){
            ubicar(recursive->der, N_corredor);
        }
    }
    return 0;
}

//Funcion Registrar Tiempo
int RegistrarTiempo(){
    int volver = 0;
    int buscar = 0;
    int encontrar = 0;
    double tiemposActuales = 0;
    double tiemposVueltas = 0;
    double tiempo = 0;
    int otraVuelta = 0;
    int Nvueltas = 0;
    if(cab != NULL){
        do{
            cout<<"Bienvenido al area de registro del tiempo del atleta"<<endl;
            cout<<"Digita el numero del corredor:"<<endl;
            cin>>buscar;
            aux = cab;
            while (aux!=NULL){
                if(aux->numero == buscar){
                    cout<<"Nombre: "<<aux->nombre<<", Numero: "<<aux->numero<<endl;
                    if(aux->rondas == 0){
                        do{
                            Nvueltas++;
                            cout<<"Ingresa el tiempo que duro el atleta en la vuelta #"<<Nvueltas<<endl;
                            cin>>tiempo;
                            aux->Tvueltas[aux->cantidadTiempos] = tiempo;
                            aux->cantidadTiempos++;
                            tiemposVueltas = tiemposVueltas + tiempo;
                            cout<<"Desea dar otra vuelta? (1.SI/2.NO)"<<endl;
                            cin>>otraVuelta;
                        }while(otraVuelta!=2);
                        aux->rondas = Nvueltas;
                        if(Nvueltas != 1)
                        {
                            aux->promedioT = tiemposVueltas/Nvueltas;
                            Nvueltas = 0;
                            tiemposVueltas = 0;
                            
                            if(raiz != NULL){
                                ubicar(raiz, buscar);
                                if(encontrado == 0){
                                  ArbolPromedio();  
                                }
                            }
                            else{
                                ArbolPromedio();
                            }

                        }
                    }else{
                        do{
                            Nvueltas++;
                            cout<<"Ingresa el tiempo que duro el atleta en esta vuelta:"<<endl;
                            cin>>tiempo;
                            aux->Tvueltas[aux->cantidadTiempos] = tiempo;
                            aux->cantidadTiempos++;
                            cout<<"Desea dar otra vuelta? (1.SI/2.NO)"<<endl;
                            cin>>otraVuelta;
                        }while(otraVuelta!=2);
                        aux->rondas = aux->rondas + Nvueltas;
                        for (int i = 0; i < aux->rondas; i++) 
                        {
                            tiemposActuales = tiemposActuales + aux->Tvueltas[i];
                        }
                        aux->promedioT = tiemposActuales/aux->rondas;
                        Nvueltas = 0;
                        tiemposActuales = 0;
                        
                        if(raiz != NULL){
                            ubicar(raiz, buscar);
                            if(encontrado == 0){
                                ArbolPromedio();  
                            }
                        }
                        else{
                            ArbolPromedio();
                        }

                    }            
                    cout<<"El registro ha sido exitoso"<<endl;
                    system("pause");
                    encontrar = 1;
                }
                aux = aux->sig;
            }
            if(encontrar == 0)
            {
            cout<<"No hay ningun atleta con ese numero..."<<endl;  
            }
            encontrar = 0;
            cout<<"Desea registrar el tiempo de otro atleta? (1.SI/2.NO)"<<endl;
            cin>>volver;
        }while(volver!=2);
    }else{
        cout<<"No Se han registrado atletas..."<<endl;
    }
    return 0;
}

//Funcion Mostrar datos
int mostrar(){
    if(cab!=NULL){
        int Nvueltas = 0;
        cout<<"Bienvenido"<<endl;
        cout<<"Hay "<<Natletas<<" Atletas"<<endl;
        for (aux=cab; aux!=NULL; aux = aux->sig)
        {
            cout<<"Nombre: "<<aux->nombre<<endl;
            cout<<"Numero: "<<aux->numero<<endl;
            if(aux->rondas != 0){
                cout<<"Tiempo: "<<endl;
                for (int i = 0; i < aux->rondas; i++) {
                    Nvueltas++;
                    cout<<"Vuelta #" << Nvueltas << ": " << aux->Tvueltas[i] << endl;
                }
                Nvueltas = 0;
                if(aux->rondas != 1)
                {
                    cout<<"El promedio de sus tiempo es: "<<aux->promedioT<<endl;
                }else{
                    cout<<"Este atleta no tiene promedio, ya que solo hizo una vuelta..."<<endl;
                }
            }else{
                cout<<"Este atleta no ha hecho vueltas..."<<endl;
            }
            
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

int inOrden(promedio *recursive){
    if(recursive->izq!=NULL){
        inOrden(recursive->izq);
    }
    cout<<"-> Atleta Numero: "<<recursive->numero<<" - promedio: "<<recursive->promedioT<<endl;
    if(recursive->der!=NULL){
        inOrden(recursive->der);
    }
    return 0;
}

int recorrer(){
    raiz;
    if(raiz!=NULL){
        inOrden(raiz);
        system("pause");
    }
    else{
        cout<<"Vacio..."<<endl;
        cout<<"No ha comenzado la competencia."<<endl;
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
        cout<<"2. Registrar tiempo de los atletas"<<endl;
        cout<<"3. Mostrar datos"<<endl;
        cout<<"4. Recorrer arbol"<<endl;
        cout<<"5. Salir"<<endl;
        cin>>opc;
        switch (opc)
        {
            case 1: registrar(); break;
            case 2: RegistrarTiempo(); break;
            case 3: mostrar(); break;
            case 4: recorrer(); break;
            case 5: cout<<"Adios"; break;
            default:cout<<"Opcion Invalidad."; break;
        }
    }while(opc!=5);
}