/*
 * CTemporizador.h
 *
 *  Created on: Sep 26, 2012
 *      Author: susana
 */

#ifndef CTEMPORIZADOR_H_
#define CTEMPORIZADOR_H_
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <string>
#include <sstream>


using namespace std;
class CTemporizador
{
	time_t t_ini,t_fim,t_instant;
	void Print();
	void Print(string);
	int StringToInt(string); //converte numero string em int;
	string IntToString(int); //converte numero int em string;
public:
	CTemporizador();
	virtual ~CTemporizador();
	void Iniciar();
	void Parar();
	void Parar(string);
	//calcular diferença desde inicio até agora
	double Instante();
	//calcular diferenca desde agora até o fim.
	string QuantoFaltaPara(int);
};

#endif /* CTEMPORIZADOR_H_ */
