// HashTable.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"


#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cstring>
#include <list>
#include <vector>
#include <queue>
#include <algorithm>
#include <sstream>//int -> string
#include <stdio.h>
#include <stdlib.h>
#define m 127  //tamaño de la tabla
using namespace std;
typedef char TipoH[];
/*
Autores:
Jose Estevez
*/
/*version 0.1*/
/* IMPLEMENTACIÓN
	la clave son placas de la forma ABC123
	tres letras mayusculas seguida de tres numeros

*/
struct elemento
{
	char info[60];//nombre
	char llave[6];
};
typedef struct
{
	int M; //tamaño de la tabla
	elemento tabla[m];
}TTablaH, *TablaH;


int    menu(TablaH T);
TablaH crear();
TablaH insertar(TablaH T, char k[], TipoH x);
TablaH eliminar(TablaH T, char k[]);
string  informacion(TablaH T, char k[]);
bool   esta(TablaH T, char k[]);
void   destruir(TablaH T);
TablaH cargar();
void   salvar(TablaH T);
int    h(TablaH T, char k[]);

int main(int argc, char *argv[])
{
	int operacion;
	char x[60];
	char k[6];
	cout << "Desea cargar  la tabla guardada:  (s) /(n)\t";
	char op;
	cin >> op;
	TablaH  T = (op == 's') ? (cargar()) : (crear());
	if (op == 's')
		cout << "Tabla Restaurada" << endl;

	while (1)
	{ // Presenta el menu de opciones
		operacion = menu(T);
		switch (operacion) {
		case 0:
			cout << "Desea guardar  la tabla:  (s) /(n)\t";
			char op;
			cin >> op;
			if (op == 's') {
				salvar(T);
				cout << "Tabla guardada" << endl;
			}
			destruir(T);
			return 0;
		case 1:
			cout << "Insertar informacion" << endl;
			cout << "Llave: ";
			cin >> k;
			if (strlen(k) != 6)
				continue;
			cout << "Nombre: ";
			gets(x);
			gets(x);
			insertar(T, k, x);
			break;
		case 2:
			cout << "Eliminar informacion" << endl;
			cout << "Placa: ";
			cin >> k;
			eliminar(T, k);
			break;
		case 3:
			cout << "Buscar informacion" << endl;
			cout << "Placa: ";
			cin >> k;
			cout << endl << "Placa:  " << k << "\t";
			cout << "Nombre:  " << informacion(T, k) << endl;
			break;
		case 4:
			cout << "Informar si esta el elemento" << endl;
			cout << "Placa: ";
			cin >> k;
			cout << ((esta(T, k)) ? ("Se encontro") : ("No se encuentra")) << endl;
			break;
		case 5:
			T = cargar();
			cout << "Archivo cargado" << endl;
			break;
		case 6:
			salvar(T);
			cout << "Archivo guardado" << endl;
			break;
		case 7:
			destruir(T);
			T = crear();
			break;
		}
	}
}

int    menu(TablaH T)
{
	int operacion = 0;
	cout << endl << endl;
	cout << "\tNo. MATRICULAS DE TAXIS - TABLA HASH" << endl;
	cout << endl << "       .--------------------------------.";
	cout << endl << "       |   1. Insertar\t\t\t|";
	cout << endl << "       |   2. Eliminar\t\t\t|";
	cout << endl << "       |   3. Informar\t\t\t|";
	cout << endl << "       |   4. Consultar existencia\t|";
	cout << endl << "       |   5. Abrir archivo\t\t|";
	cout << endl << "       |   6. Guardar archivo\t\t|";
	cout << endl << "       |   7. anular\t\t\t|";
	cout << endl << "       .--------------------------------.";
	cout << endl << ": ";
	cout << endl;
	cin >> operacion;
	return operacion;
}
TablaH crear()
{
	TablaH T = (TablaH)malloc(sizeof(TTablaH));
	T->M = m;
	for (int i = 0; i < T->M; i++)
	{
		strcpy(T->tabla[i].llave, "");
		strcpy(T->tabla[i].info, "");
	}
	return T;
}
TablaH insertar(TablaH T, char k[], TipoH x)
{
	int pos = h(T, k);
	while (1) {
		if (strlen(T->tabla[pos].llave) == 0) {
			strcpy(T->tabla[pos].llave, k);
			strcpy(T->tabla[pos].info, x);
			break;
		}
		pos = (pos == T->M - 1) ? (0) : (pos + 1);
	}
	return T;
}
TablaH eliminar(TablaH T, char k[])
{
	int pos = h(T, k);
	int ciclo = 0;
	while (ciclo <= 1)
	{
		if (strcmp(T->tabla[pos].llave, k) == 0) {
			free(T->tabla[pos].llave);
			strcpy(T->tabla[pos].llave, "");
			free(T->tabla[pos].info);
			strcpy(T->tabla[pos].info, "");
		}
		pos = (pos == T->M - 1) ? (0) : (pos + 1);
		ciclo = (pos == 0) ? (ciclo + 1) : (0);
	}
	return T;
}
string  informacion(TablaH T, char k[])
{
	if (esta(T, k)) {
		int pos = h(T, k);
		int ciclo = 0;
		while (ciclo <= 1)
		{
			if (strcmp(T->tabla[pos].llave, k) == 0) {
				return(T->tabla[pos].info);
			}
			pos = (pos == T->M - 1) ? (0) : (pos + 1);
			ciclo = (pos == 0) ? (ciclo + 1) : (0);
		}
		return "-1";
	}
}

bool   esta(TablaH T, char k[])
{
	int pos = h(T, k);
	if (strcmp(T->tabla[pos].llave, k) == 0) {
		return 1;
	}
	else {
		pos++;
		int ciclo = 0;
		while (ciclo <= 1) {
			if (strcmp(T->tabla[pos].llave, k) == 0) {
				return 1;
			}
			pos = (pos == T->M - 1) ? (0) : (pos + 1);
			if (pos == 0)
				ciclo++;
		}
	}
	return 0;
}
void   destruir(TablaH T)
{
	for (int i = 0; i < T->M; i++) {
		if (strlen(T->tabla[i].llave) != 0) {
			free(T->tabla[i].llave);
			free(T->tabla[i].info);
		}
	}
	free(T->tabla);
	free(T);
}

int h(TablaH T, char clave[])
{
	stringstream stream;
	int n = (int)clave[1];
	stream << n;
	string num = "";
	num += stream.str();
	num += clave[3];
	num += clave[4];
	num += clave[5];
	long long d = atoi(num.c_str());
	stream << d * d;
	num = stream.str();
	string valor = "";
	int mitad = (num.size()) / 2;
	if (num.size() % 2 == 0) {
		valor += num[mitad - 1];
		valor += num[mitad];
	}
	else {
		valor += num[mitad];
		valor += num[mitad + 1];
	}
	return atoi(valor.c_str());
}
TablaH cargar()
{
	FILE *fp = fopen("placas-nombre.tax", "r");//nombre del archivo //modo lectura
	struct elemento nuevo[m];
	TablaH T = crear();
	fread(&nuevo, sizeof(struct elemento), m, fp);
	for (int i = 0; i < m; i++) {
		strcpy(T->tabla[i].llave, nuevo[i].llave);
		strcpy(T->tabla[i].info, nuevo[i].info);
	}
	fclose(fp);
	free(nuevo);
	return T;
}
void   salvar(TablaH T)
{
	FILE *fp = fopen("placas-nombre.tax.", "w");//nombre del archivo //modo escritura 
	fwrite(T->tabla, sizeof(struct elemento), m, fp);
	fclose(fp);
}
