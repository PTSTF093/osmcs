/* 
 * File:   Csessao.h
 * Author: marlon.simoni
 *
 * Created on 17 de Dezembro de 2015, 22:46
 */

#ifndef CSESSAO_H
#define	CSESSAO_H

#include <iostream>
#include <string>

class Csessao {
public:
	Csessao();
	//Csessao(const Csessao& orig);
	virtual ~Csessao();

	void Reset();

	bool estaCheia() {
		//janCheia=true;
		return (tj == numJanelasCheias && !cics.empty() && sigla != "        ");
	}

	void setCics(std::string str) {
		cics = str;
	}
	;
	void setSigla(std::string str) {
		sigla = str;
	}
	;
	void setSess(std::string str) {
		sess = str;
	}
	;
	void setTraf(std::string str) {
		traf = str;
	}
	;
	void setTrans(std::string str) {
		trans = str;
	}
	;
	void setTj(int t) {
		tj = t;
	}
	;
	//void setTj(int t){tj=t;};

	//gets
	std::string getCics() {
		return cics;
	}
	;
	std::string getSigla() {
		return sigla;
	}
	;
	int getTj() {
		return tj;
	}
	;
	int getCheias() {
		return numJanelasCheias;
	}
	;

	void Incrementar();

	bool estaOpen() {
		return (sess == "OPEN " && traf == "OPEN " && trans == "ACTIV");
	}
	;

	//se a sigla passada por parametro for diferente,
	bool mesmaSessao(std::string);

	//TARJETAS
	void setElemento(std::string str) {
		elemento = str;
	}
	;
	void setEstelemento(std::string str) {
		est_elemento = str;
	}
	;
	void setEstconex(std::string str) {
		est_conex = str;
	}
	;
	void setNopesaf(std::string str) {
		n_ope_saf = str;
	}
	;
	void setEstadobd(std::string str) {
		estado_bd = str;
	}
	;
	//gets
	std::string getElemento() {
		return elemento;
	}
	;
	bool estaACTIVOA() {
			return (est_elemento == "ACTIVO" && est_conex == "ACTIVA");
		}
	//TARJETAS

private:
	std::string sess;
	std::string traf;
	std::string trans;

	std::string cics;
	std::string sigla;

	//tarjetas
	std::string elemento;
	std::string est_elemento;
	std::string est_conex;
	std::string n_ope_saf;
	std::string estado_bd;
	//tarjetas

	int tj;
	int numJanelasCheias;
};

#endif	/* CSESSAO_H */

