#include <iostream>
#include <conio.h>
#include <stdlib.h>

using namespace std;

struct Nodo{

	int x;
	Nodo* derecha;
	Nodo* izquierda;
	Nodo* padre;
};

void menu();

Nodo* CrearnuevoNodo(int, Nodo *);
void insertarNodo(Nodo *&, int, Nodo *);
void visualizarArbol(Nodo *, int);
bool busqueda(Nodo *, int);

void eliminar(Nodo*, int);
Nodo* minimo(Nodo*);
void eliminarNodo(Nodo *);

void reemplazar(Nodo*, Nodo*);
void destruirNodo(Nodo*);


Nodo* arbol = NULL;


int main(){

	menu();
	return 0;
}


bool BusquedaBinaria(Nodo *arbol, int x)
{
	int numeros[] = { 1,3,6,8,9,15};
	int inf, sup, mitad, i;

	bool band = false;

	inf = 0;
	sup = 6;
	i = 0;
	
	while ((inf <= sup) && (i < 6))
	{
		mitad = (inf + sup) / 2;// mitad

		if (numeros[mitad] == x)
		{
			band = true;
			
			break; //Se encontro el elemento buscado, para no perder tiempo
		}
		if (numeros[mitad] > x)
		{
			sup = mitad;
			mitad = (inf + sup) / 2; //Refrescar la mitad con un nuevo valor del lado superior
		}
		if (numeros[mitad] < x)
		{
			inf = mitad;
			mitad = (inf + sup) / 2; //Refrescar la mitad con un nuevo valor del lado inferior
		}
		i++;
	}

	if (band == true)
	{
		cout << "El numero se encontro en la posicion: " << mitad << endl; // mitad guarda las posiciones
	}
	else
	{
		cout << "El numero no se encontro";
	}
	return 0;
	
}

void menu(){

	int x, opcion, contador = 0, cantidad;

	do{
		cout << "\n MENU" << endl;
		cout << "1. Ingresar un nuevo nodo" << endl;
		cout << "2. Mostrar el arbol" << endl;
		cout << "3. Buscar elemento" << endl;
		cout << "4. Eliminar elemento" << endl;
		cout << "5. Busqueda Binaria" << endl;
		cout << "6. SALIR" << endl;
		cout << "Elige una opcion: " << endl;

		cout << "Opcion ->> ";
		cin >> opcion;

		switch (opcion){
			case 1:
				cout << "Ingresa la cantidad de nodos que tiene el arbol: ";
				cin >> cantidad;
				for(int i = 0; i < cantidad; i++){
					cout << "Ingresa un numero: ";
					cin >> x;
					insertarNodo(arbol,x, NULL);
				}
				system("cls");
				cout << "se agrego el nodo" << endl;
				system("pause");
				break;
	
			case 2:
				cout << "\n Mostrar arbol: \n\n";
				visualizarArbol(arbol, contador);
				cout << "\n";
				system("pause");
				break;
	
			case 3:
				cout << "\nIngresa el elemento a buscar: ";
				cin >> x;
				if (busqueda(arbol,x) == true){
					cout << "\nElemento se encuentra en el arbol";
				}
				else{
					cout << "\nEl elemento no existe";
				}
				cout << "\n";
				system("pause");
				break;

			case 4:
				cout << "ingresa el elemanto que deseas eliminar ";
				cin >> x;
				eliminar(arbol, x);
				break;

			case 5:
				cout << "\nIngresa el elemento a buscar: ";
				cin >> x;
				if (BusquedaSecuencial(arbol,x) == true){
					cout << "\nElemento se encuentra en el arbol";
				}
				else{
					cout << "\nEl elemento no existe";
				}
				cout << "\n";
				system("pause");
				break;
			break;
				//BusquedaSecuencial();
			} 
		system("cls");
	} while (opcion != 6);
}

Nodo* CrearnuevoNodo(int n, Nodo *padre){

	Nodo* nuevo_nodo = new Nodo();

	nuevo_nodo->x = n;
	nuevo_nodo->derecha = NULL;
	nuevo_nodo->izquierda = NULL;

	return nuevo_nodo;
}

void insertarNodo(Nodo*& arbol, int n, Nodo *padre){

	if (arbol == NULL){	

		Nodo* nuevo_nodo = CrearnuevoNodo(n, padre);
		arbol = nuevo_nodo;
	}
	else{	

		int valorRaiz = arbol->x;
		if (n < valorRaiz){ 
			insertarNodo(arbol->izquierda, n, arbol);
		} else{ 
			insertarNodo(arbol->derecha, n, arbol);
		}
	}
}

void visualizarArbol(Nodo *arbol, int cont){

	if (arbol == NULL){
		return;
	} 
	else{

		visualizarArbol(arbol->derecha, cont + 1);
		for (int i = 0; i < cont; i++){ 
			cout << "  ";
		}
		cout << arbol->x << endl;
		visualizarArbol(arbol->izquierda, cont + 1);
	}
}

bool busqueda(Nodo *arbol, int n){

	if (arbol == NULL){ 
		return false;
	}
	else if (arbol->x == n){ 
		return true;
	}
	else if (n < arbol->x){ 
		return busqueda(arbol->izquierda,n);
	}
	else{
		return busqueda(arbol->derecha, n);
	}
}

void eliminar(Nodo* arbol, int n){

	if(arbol == NULL){
		return;
	} 
	else if(n < arbol->x){		
		eliminar(arbol->izquierda, n);
	} 
	else if(n > arbol->x){		
		eliminar(arbol->derecha, n);
	} 
	else{		
		eliminarNodo(arbol);
	}
}

Nodo* minimo(Nodo* arbol){

	if(arbol == NULL){
		return NULL;
	}
	if(arbol->izquierda){
		return minimo(arbol->izquierda);	
	} else{		
		return arbol;	
	}
}

void eliminarNodo(Nodo* nodoEliminar){

	if(nodoEliminar->izquierda && nodoEliminar->derecha){	
		
		Nodo * menor = minimo(nodoEliminar->derecha);	
		nodoEliminar->x = menor->x;
		eliminarNodo(menor);	
	} 
	else if(nodoEliminar->izquierda){	

		reemplazar(nodoEliminar, nodoEliminar->izquierda);
		destruirNodo(nodoEliminar);
	} 
	else if(nodoEliminar->derecha){

		reemplazar(nodoEliminar, nodoEliminar->derecha);
		destruirNodo(nodoEliminar);	
	} else{

		reemplazar(nodoEliminar, nodoEliminar->derecha);
		destruirNodo(nodoEliminar);
	}
}

void reemplazar(Nodo* arbol, Nodo* nuevoNodo){

	if(arbol->padre){	
	
		if(arbol->x == arbol->padre->izquierda->x){
			arbol->padre->izquierda = nuevoNodo;
		} 
		else if(arbol->x == arbol->padre->derecha->x){
			arbol->padre->derecha = nuevoNodo;
		}
	
		if(nuevoNodo){
			nuevoNodo->padre = arbol->padre;
		}
	}
}

void destruirNodo(Nodo* nodo){

	nodo->izquierda = NULL;
	nodo->derecha = NULL;
	delete nodo;
}

/*
* 2°
* Ejercicio 1: para n elementos - Busqueda binaria
* Introduce letras de manera ordenada
* 
* 
* Menu
* Buscar una letra
* Tamaño del arreglo
* Ordenamiento descendente (ordenar el arreglo introducido de manera descedente)
* Ordenamiento ascendente (ordenar el arreglo introducido de manera ascedente)
* 
* 
*/
/*
* 3°
* 
* Ejercicio 1: para n elementos - Busqueda binaria de arboles
* Introduce letras
*
*
* Menu
* Tamaño del arbol / Insertar nodo
* Mostrar recorridos
* Buscar una letra
*
*/