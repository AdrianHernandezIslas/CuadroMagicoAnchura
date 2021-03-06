// CuadroMagicoBusquedaAnchura.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <iostream>
#include <ctime>        
#include <cstdlib>

using namespace std;
queue<vector<int>> cola;
queue<queue<vector<int>>> colaHistorial;
vector<int> nodoMeta;
vector<int> nodoInicial;


bool izquierda(vector<int> arreglo, int posicionCero, int orden) {
	return !(posicionCero % orden == 0) && (posicionCero - 1 >= 0);
}

vector<int> moverIzquierda(vector<int> arreglo, int posicionCero, int orden) {
	arreglo[posicionCero] = arreglo[posicionCero - 1];
	arreglo[posicionCero - 1] = 0;
	return arreglo;
}

bool derecha(vector<int> arreglo, int posicionCero, int orden) {
	return !((posicionCero + 1) % orden == 0) && ((posicionCero + 1) < orden*orden);
}

vector<int> moverDerecha(vector<int> arreglo, int posicionCero, int orden) {
	arreglo[posicionCero] = arreglo[posicionCero + 1];
	arreglo[posicionCero + 1] = 0;
	return arreglo;
}

bool arriba(vector<int> arreglo, int posicionCero, int orden) {
	return posicionCero - orden >= 0;
}

vector<int> moverArriba(vector<int> arreglo, int posicionCero, int orden) {
	arreglo[posicionCero] = arreglo[posicionCero - orden];
	arreglo[posicionCero - orden] = 0;
	return arreglo;
}

bool abajo(vector<int> arreglo, int posicionCero, int orden) {
	return posicionCero + orden < orden*orden;
}

vector<int> moverAbajo(vector<int> arreglo, int posicionCero, int orden) {
	arreglo[posicionCero] = arreglo[posicionCero + orden];
	arreglo[posicionCero + orden] = 0;
	return arreglo;
}

bool sonIguales(vector<int> tableroMeta, vector<int> tableroActual) {

	for (size_t i = 0; i < tableroMeta.size(); i++)
	{
		if (tableroMeta[i] != tableroActual[i]) {
			return false;
		}
	}
	return true;
}

int encontrarEspacio(vector<int> arreglo) {
	for (size_t i = 0; i < arreglo.size(); i++) {
		if (arreglo[i] == 0) {
			return i;
		}
	}
	return -1;
}

void imprimirTablero(vector<int> arreglo) {
	for (size_t i = 0; i < arreglo.size(); i++)
	{
		if (i % ((int)sqrt(arreglo.size())) == 0) {
			cout << "\n" << endl;
		}
		cout << arreglo[i] << " ";
	}
	cout << endl;
}

void imprimirCola(queue<vector<int>> cola) {
	while (!cola.empty())
	{
		imprimirTablero(cola.front());
		cola.pop();
	}
}

void imprimirColaHistorial() {
	queue<queue<vector<int>>> copy = colaHistorial;
	while (!copy.empty())
	{
		cout << copy.size() << " ---------------------------" << endl;
		imprimirCola(copy.front());
		copy.pop();

	}
}


queue<vector<int>> crearNivel(vector<int> arreglo) {
	queue<vector<int>> cola;
	int posicionCero = encontrarEspacio(arreglo);
	int orden = (int)sqrt(arreglo.size());
	if (izquierda(arreglo, posicionCero,orden)) {
		cola.push(moverIzquierda(arreglo,posicionCero,orden));
	}

	if (arriba(arreglo, posicionCero, orden)) {
		cola.push(moverArriba(arreglo, posicionCero, orden));
	}

	if (abajo(arreglo, posicionCero, orden)) {
		cola.push(moverAbajo(arreglo, posicionCero, orden));
	}

	if (derecha(arreglo, posicionCero, orden)) {
		cola.push(moverDerecha(arreglo, posicionCero, orden));
	}

	return cola;
}

queue<vector<int>> crearNodoColaHistorial(queue<vector<int>> colaPadre, vector<int> nodoHijo) {
	queue<vector<int>> cp = colaPadre;
	cp.push(nodoHijo);
	return cp;
}

void agregarColaHistorial(queue<vector<int>> colaPadre, queue<vector<int>> colaHijos) {

	while (!colaHijos.empty())
	{
		colaHistorial.push(crearNodoColaHistorial(colaPadre, colaHijos.front()));
		colaHijos.pop();
	}
	//cout << "hijos: " << colaHistorial.back().size() << endl;
}


bool otroBuscar(queue<vector<int>> colaNodo) {
	colaHistorial.push(colaNodo);
	vector<int> nodo;
	while (!colaHistorial.empty())
	{
		nodo = colaHistorial.front().back();
		if (sonIguales(nodo, nodoMeta)) {
			return true;
		}
		queue<vector<int>> nivel = crearNivel(nodo);
		agregarColaHistorial(colaHistorial.front(), nivel);
		colaHistorial.pop();
		//getchar();
		
		
	}
	return false;
}

bool buscar(queue<vector<int>> colaNodo) {
	colaHistorial.push(colaNodo);
	vector<int> nodo = colaNodo.back();
	if (sonIguales(nodo, nodoMeta)) {
		return true;
	}
	else {
		queue<vector<int>> nivel = crearNivel(nodo);
		colaHistorial.pop();
		agregarColaHistorial(colaNodo, nivel);
		buscar(colaHistorial.front());
	}
}


void llenarArreglos(vector<int>& tableroInicial, vector<int>& tableroMeta, int orden) {
	int donde = orden * orden;
	/*for (size_t i = 1; i < donde; i++) {
		tableroInicial.push_back(i);
	}
	tableroInicial.push_back(0);*/
	//Aqui puede agregar su matriz
	tableroInicial.push_back(1);
	tableroInicial.push_back(2);
	tableroInicial.push_back(3);
	tableroInicial.push_back(0);
	tableroInicial.push_back(4);
	tableroInicial.push_back(5);
	tableroInicial.push_back(7);
	tableroInicial.push_back(8);
	tableroInicial.push_back(6);
	for (size_t i = 1; i < tableroInicial.size(); i++) {
		tableroMeta.push_back(i);
	}
	tableroMeta.push_back(0);
	/*srand(unsigned(time(0)));
	random_shuffle(tableroInicial.begin(), tableroInicial.end());*/
}


int main()
{
	int orden = 0;

	cout << "Ingrese el orden(N x N) del tablero: "; cin >> orden; cout << endl;

	llenarArreglos(nodoInicial, nodoMeta, orden);
	cout << "Tablero Inicial:" << endl;
	imprimirTablero(nodoInicial);
	
	cout << "Procesado sea paciente ..." << endl;
	queue<vector<int>> nInicial;
	nInicial.push(nodoInicial);
	
	if (otroBuscar(nInicial)) {
		cout << "\nSolucion Encontrada..." << endl;
		imprimirCola(colaHistorial.front());
	}
	else {
		cout << "Sin Solucion ..." << endl;
	}
	
	system("pause");
    return 0;
}

