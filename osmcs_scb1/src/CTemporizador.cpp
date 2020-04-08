/*
 * CTemporizador.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: susana
 */

#include "CTemporizador.h"

CTemporizador::CTemporizador()
{
	time(&t_instant);
	time(&t_ini);
	time(&t_fim);
}

CTemporizador::~CTemporizador()
{
	time(&t_fim);
	cout<<"Total de execução do programa = "<<difftime(t_fim,t_instant)<<" segundos"<<endl;
}
void CTemporizador::Iniciar()
{
	time(&t_ini);
}

void CTemporizador::Parar()
{
	time(&t_fim);
	Print();
}
void CTemporizador::Parar(string mensagem)
{
	time(&t_fim);
	Print(mensagem);
}

void CTemporizador::Print()
{
	cout<<"Tempo gasto em segundos: "<<difftime(t_fim,t_ini)<<" s."<<endl;
}

void CTemporizador::Print(string mensagem)
{
	cout<<mensagem<<endl;
	cout<<"Demorou em segundos: "<<difftime(t_fim,t_ini)<<" s."<<endl;
}
/*
 * Calcular diferença entre o inicio
 * e o instante agora e devolver
 * como double a diferenca.
 */
double CTemporizador::Instante()
{
	time(&t_instant);
	return difftime(t_instant,t_ini);
}

/*
 * Calcular quanto tempo
 * falta entre o instante e o fim dado
 * por parâmetro
 */
string CTemporizador::QuantoFaltaPara(int fim)
{
	string falta;
	int instante=(int)this->Instante();
	int time,horas,minutos,segundos;
	time=fim-instante;
	horas=time/3600;
	time=time%3600;
	minutos=time/60;
	time=time%60;
	segundos=time;
	falta=IntToString(horas)+":"+IntToString(minutos)+":"+IntToString(segundos);
	return falta;
}
/*
 * converter strin para int
 */
int CTemporizador::StringToInt(string s)
{
	/*
	 * converter numero em string para int
	 */
	int i;
	std::istringstream(s) >> i; //converter string para int
	return i;
}
/*
 * Converter int para string
 */
string CTemporizador::IntToString(int i)
{
	string s;
	stringstream out;
	out << i;
	return out.str();
}
