/* 
 * File:   CGprtRec.cpp
 * Author: marlon.simoni
 * 
 * Created on 16 de Março de 2014, 14:34
 */

#include "CConsGrab.h"

CConsGrab::CConsGrab() {
	insist = 0;
}

void CConsGrab::SetFichout(string file) {
	//C=CRemoto;
	//this->fpipe=CRemoto.fpipe;
	fichout.open(file.c_str());
	if (!fichout.is_open()) {
		//fichout.open("ps.txt");
		cout << "Ficheiro nao aberto" << endl;
	}
}

CConsGrab::CConsGrab(const CConsGrab& orig) {
	insist = 0;
}

CConsGrab::~CConsGrab() {
	fichout.close();
	//delete _estaSessao;
	//delete sessoesStats;
}




void CConsGrab::loopCaptaConsole(string smcs) {

	vector<string> ConsoleToda = GrabScreen();
	for (int i=0;i<(int) ConsoleToda.size();++i){

		/*wto*/
		string charwto=ConsoleToda.at(i).substr(5,1);
		if(charwto=="*" or charwto=="@" ){
			string sql = "insert into "
					"wto.log(instante,texto,console) "
					"values(now(),\'" + ConsoleToda.at(i) + "\',\'"+smcs+"\')";

			if (!mysql.Exec(sql)) {
				cout << "erro no sql=" << sql << endl;
				cout << endl;
				cout << mysql.Erro() << endl;
			}
		}



		string sql = "insert into "
				"console_temp "
				"values(now(),\'" + ConsoleToda.at(i) + "\')";

		if (!mysql.Exec(sql)) {
			cout << "erro no sql=" << sql << endl;
			cout << endl;
			cout << mysql.Erro() << endl;
		}
	}
}

void CConsGrab::Next() {
	//marcar fim do loop no ficheiro com um generoi de proxima pagina
	fichout << Informar()
			<< "-------------------------------------------------------"
			<< endl;
}

void CConsGrab::SetInsist(int insist) {
	//numero de vezes a insistir na REC de uma(s) mensagens.
	this->insist = insist;

}

void CConsGrab::DBStart(string h, string u, string p, string d) {
	if (!mysql.Open(u, p, h, d)) {
		cout << "erro ao connectar DB" << endl;
		cout << "h=" << h << endl;
		cout << "u=" << u << endl;
		cout << "o=" << p << endl;
		cout << "d=" << d << endl;
	}
}

void CConsGrab::LimpaTabTemp() {
	mysql.Clear("console_temp");
} //limpar a tabela temp

void CConsGrab::ActTempIntoOrig() {
	//select * from  wto.log where ativo=1 and texto in (select texto from scma.console_temp)
	mysql.Exec("UPDATE  wto.log set ativo=0 WHERE ativo=1 AND console='"+smcs+"' and texto not in (select wto from "+smcs+".console_temp)");
	mysql.Exec("delete from "+smcs+".console"); // where not exists  (select * from gprtrec_temp)");
	mysql.Exec("insert into "+smcs+".console (select * from "+smcs+".console_temp)"); // where not exists (select * from gprtrec))");
} //carregar tabela temp na verdadeira

void CConsGrab::UpdtLoop(int loops, int loop) {
	string sql = "update loops set loops.loops=\'" + IntToString(loops)
			+ "\', loops.loop=\'" + IntToString(loop)
			+ "\' where loops.tabela=\'gprtrec\'";
	//cout << sql << endl;
	mysql.Exec(sql);
}
