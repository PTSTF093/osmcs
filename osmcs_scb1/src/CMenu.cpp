/* 
 * File:   CMenu.cpp
 * Author: marlon.simoni
 * 
 * Created on 8 de Abril de 2014, 15:58
 */

#include "CMenu.h"

CMenu::CMenu() {
	//cout << PIPESPASS << endl;
	time(&Antes);
	time(&Agora);
	sair = false;
	LogedNetView = false; //esta logado no netview
	LoopRec = false;
	tso = lpar = "";
	CConsGrab::DBStart("127.0.0.1", "root", "openpipes", "sca1"); //arrancar o mysql
	//Cftsm::mysql = CGrt::mysql = CGspi::mysql = Ccutoffs::mysql = CGprtAnom::mysql = CGprtRec::mysql = CGprtRec::mysql;
	//CGprtRec::mysql.Exec("update run set parar=0");
	//OpenPassword();
}

CMenu::CMenu(string database) {
	cout << PIPESPASS << endl;
	time(&Antes);
	time(&Agora);
	sair = false;
	LogedNetView = false; //esta logado no netview
	LoopRec = false;
	tso = lpar = "";
	CConsGrab::DBStart("127.0.0.1", "root", "openpipes", database); //arrancar o mysql
	//Cftsm::mysql = CGrt::mysql = CGspi::mysql = Ccutoffs::mysql = CGprtAnom::mysql = CGprtRec::mysql = CGprtRec::mysql;
	//CGprtRec::mysql.Exec("update run set parar=0");
	//OpenPassword();
}

CMenu::CMenu(const CMenu& orig) {
	time(&Antes);
	time(&Agora);
	sair = false;
	tso = lpar = "";
	LogedNetView = false; //esta logado no netview
	LoopRec = false;
	//OpenPassword();
}

CMenu::~CMenu() {
}

void CMenu::PrintMenu() {
	/*
	 despejar um menu com opcoes e recolher num prompt*/
	cout << endl;
	cout << "****       Motor-Opipes  **** TSO:" << tso << " ****" << endl;
	if (!LogedNetView) {
		cout << "    1. Login NetView" << endl;
	} else {
		if (tso == "") {
			cout << "    2. Login TSO SYA1" << endl;
			cout << "    3. Login TSO SYB1" << endl;
			cout << "    4. Login TSO SYB2" << endl;
			cout << "    5. Login TSO MCFA" << endl;
			cout << "    6. Login TSO MCFB" << endl;
			cout << "    7. Login TSO MVS2" << endl;
		} else {
			cout << "    8. Logoff: " << tso << endl;
			//cout << "   10. Start Pipes: "<< tso << endl;
		}
	}
	cout << "    9. ShowScreen(Debug)" << endl;
	cout << "    X. Sair" << endl;
	cout << "opipes > ";
	cin >> comando;
}

bool CMenu::EnterComando() {
	/*executar a opcao solicitada*/

	if (comando == "1") {
		LoginNetView("SYA1");
	} else if (comando == "2") {
		//ArrancarSYA1();
		//LoginAllCics();
	} else if (comando == "3") {
		//ArrancarSYB1();
	} else if (comando == "4") {
		//ArrancarSYB2();
		//Cutoffs();
	} else if (comando == "5") {
		//ArrancarMCFA();
		//GprtAnom();
	} else if (comando == "6") {
		//ArrancarMCFB();
		//GprtRec(loops, insist);
	} else if (comando == "7") {
		//ArrancarMVS2();

	} else if (comando == "8") {
		Logoff();
	} else if (comando == "9") {
		string comandoDebug = "n";
		while (comandoDebug != "x") {

			CConsGrab::ShowThisScreen();
			cout << "debugging(x=sair,s=string,i=3270):=>";
			cin >> comandoDebug;
			if (comandoDebug == "s") {
				cout << "putString<enter>:";
				cin >> comandoDebug;
				CConsGrab::EnterString(comandoDebug);
			} else if (comandoDebug == "i") {
				cout << "comando 3270<enter>:";
				cin >> comandoDebug;
				CConsGrab::Executar3270(comandoDebug);
			}
			//comandoDebug=" ";

		}
	} else if (comando == "x" || comando == "X") {
		sair = true;
		if (LogedNetView) {
			Executar3270("Disconnect");
		}

	} else if (comando == "10") {
		/*
		 * Arrancar com o motor
		 */
	} else {
		cout << endl << "Comando invalido" << endl;
	}
	return true;
}

bool CMenu::LoginNetView(string l) {
	if (LogedNetView) {
		cout << endl << "Sessão já iniciada." << endl;
		return false;
	}
	//1Start("192.168.19.38", "nmb");
	//ifstream fichPass;
	//namespace já é CCon3270!!!
	cout << endl << "...";
	CConsGrab::Start(l);
	cout << ".";
	//Executar3270("ascii");
	/*
	 Entrar no MAI
	 */
	//string user, pass;
	//utilizar o ficheiro encriptado pipespass
	//fichPass.open("ps.txt");
	/*
	 Ler o ficheiro ps.txt que está em My Documents*/
//	if (fichPass.is_open()) {
//		getline(fichPass, user);
//		getline(fichPass, pass);
//		//        user << fichPass;
//		//        pass << fichPass;
//
//		fichPass.close();
//		CGprtRec::SetUserPass(user, pass);
//	} else {
//		cout << "erro com o ficheiro ps.txt" << endl;
//		return false;
//	}
	cout << ".";
	sleep(5);
	cout << ".";
	//CAADF::Clear();
	//CAADF::Enter();
	cout << ".";
	if (CConsGrab::SeApareceu("PRETENDIDA")) {
		//EnterString("nma");
		cout << ".";
		CConsGrab::EnterString("a");
		cout << ".";
		sleep(2);
		cout << ".";
	} else {
		CConsGrab::Informar("Não foi possivel seguir login");
		CConsGrab::ShowThisScreen();
		return false;
	}

	cout << ".";
	if (CConsGrab::SeApareceu("LOGON")) {
		//string user,pass;

		//GetUserPass();
		cout << ".";
		CConsGrab::PutString(usercgd);
		cout << ".";
		CConsGrab::NewLine();
		cout << ".";
		//sleep(5);
		CConsGrab::EnterString(passcgd);
		cout << ".";
		sleep(2);
		cout << ".";
	} else {
		CConsGrab::ShowThisScreen();
		cout << ".";
		return false;
	}
	cout << ".";
	/*
	 se aparecer RECONNECTED, estou a roubar uma sessao ja logada!
	 */
	if (CConsGrab::SeApareceu("Application Selection")) {
		cout << ".";
		CConsGrab::Enter();
		cout << ".";
		CConsGrab::Pa2();
		cout << ".";
		/*
		 Se apareceu Primary Menu estamos bem senao, pf24
		 */    //TODO alterar isso que veio da sibs
		/*
		 if (CAADF::Apareceu("Primary Menu")) {
		 cout << ".";
		 //ShowThisScreen();
		 } else {
		 CAADF::Pf24();
		 cout << ".";
		 //ShowThisScreen();
		 }
		 */
	} else {
		CConsGrab::Informar("Não foi possivel seguir login");
		CConsGrab::ShowThisScreen();
		return false;
	}
	cout << ".";
	//Cftsm::fpipe = CGrt::fpipe = CGspi::fpipe = Ccutoffs::fpipe = CGprtAnom::fpipe = CGprtRec::fpipe = CGprtRec::fpipe;
	//LogedCics;//esta logado nos cics
	LogedNetView = true; //esta logado no netview
	cout << "done" << endl;
	return true;

}

void CMenu::LogoutAll() {

}

void CMenu::Cutoffs() {
	/*
	 Percorrer os cics todos
	 */
	//cutoffs = new Ccutoffs();
	if (!LogedNetView) {
		cout << endl << "sessão não iniciada." << endl;
		return;
	}
	//Ccutoffs cutoffs(* this->fpipe, * this->interp);
	//Ccutoffs cutoffs;
	//Ccutoffs *x=new CAADF();
	//Ccutoffs::fpipe=CAADF::fpipe;
	cout << endl << ".";
	if (solicitado_stop())
		return;
	//Ccutoffs::SetFichout("cutoffs.txt");
	//Ccutoffs::DBStart();
	//Ccutoffs::EstadoOn();
	cout << ".";
	if (solicitado_stop())
		return;
	//Ccutoffs::LimpaTabTemp(); //inicio de ciclo
	cout << ".";
	if (solicitado_stop())
		return;
	//Ccutoffs::GetCics("PRDINT01");
	cout << ".";
	if (solicitado_stop())
		return;
	//Ccutoffs::ActTempIntoOrig(); //fim de ciclo, registos novos na tabela
	cout << ".";
	if (solicitado_stop())
		return;
	//Ccutoffs::EstadoOff();
	cout << ".done" << endl;
}

bool CMenu::solicitado_stop() {

	string sdisc = CConsGrab::mysql.ExecGetSingle("select parar from run");
	if (sdisc == "1") {
		cout << endl << "Foi solicitado STOP ao MOTOR" << endl;
	}
	return sdisc == "1";
}

bool CMenu::QueryLoopRec() {
	string str_devolvida = CConsGrab::mysql.ExecGetSingle(
			"select doloop from looprec");
	if (str_devolvida == "1")
		return true;
	else
		return false;
}

void CMenu::Logoff() {
	int bkp_exp_timeout = exp_timeout, rc;	//salvaguardar o exp_timeout default
	exp_timeout = 2;
	cout << "...logoff " << lpar << " .";
	Pf3();
	while (1) {
		cout << ".";
//		sleep(1);
//		Home();Eeof();EnterString("=x");Pf3();
//		EnterString("logoff");
//		sleep(1);

		fprintf(fpipe, "ascii\r");
		rc = exp_fexpectl(fpipe, exp_glob,
				" READY                                 ", 1, exp_glob,
				"CAIXA GERAL DE DEPOSITOS, S.A.", 2, exp_glob, "IKJ56247I", 3,
				exp_glob, "Specify Disposition of Log Data Set", 4, exp_glob,
				"UNSUPPORTED FUNCTION", 5, exp_glob,
				"PONER CODIGO DE APLICACION Y PULSAR INTRO", 6, exp_glob,
				"IKJ56247I", 7, exp_glob,
				"C A I X A   E C O N O M I C A   M O N T E P I O   G E R A L",
				8, exp_glob, "FUNCAO NAO SUPORTADA", 9, exp_glob,
				"Specify Disposition of Log Data Set", 10,

				/******/
				exp_end);
		switch (rc) {
		//case 0:

		case 1:

			cout << "apareceu READY" << endl;
			EnterString("logoff");
			cout << "dado logoff" << endl;
			continue;
			break;
		case 9:
		case 5:
			Clear();
			continue;
			break;
		case 6:
		case 2:
		case 8:
			//sucesso
			cout << "logoff com sucesso" << endl;
			exp_timeout = bkp_exp_timeout;
			cout << ".";
			sleep(5);
			Stop();
			sleep(5);
			cout << ".feito stop";

			//CGprtRec::Pf3();
			//cout << ".";
			//EnterString("logoff");
			//EnterString("logoff");
			CConsGrab::mysql.Exec("replace into lpar3270 "
					"(activo3270,solicitadoDisconnect,lpar) "
					"values( 'n', 'n', '" + lpar + "')");
			cout << ".done" << endl;
			return;
			break;
		case 3:
			Enter();
			continue;
			break;
		case 4:
		case 7:
			Enter();
			continue;
			break;
		case 10:
			EnterString("2");
			continue;
			break;
		case EXP_TIMEOUT:
			//cout<<"timeout, continuar loop"<<endl;
			Home();
			Eeof();
			Pf3();
			//cout<<"dado Home();Eeof();Pf3();"<<endl;
			continue;
			break;
		}

	}

}

/*
 Executar sql e verificar 
 se existem pedidos em queue para ser satisfeitos
 */
void CMenu::QueyQueuePedidos() {
	/*
	 FIFO
	 Fazer o pop do primeiro a entrar na fila de pedidos
	 */
	vector<vector<string> > Pedido;
	Pedido = CConsGrab::mysql.ExecGetData(
			"select pedido,chegada from queuepedidos order by chegada asc");

	/*
	 Interromper caso nao haja nada*/
	if (Pedido.empty()) {
		return;
	}
	//dizer qual esta em execucao agora neste momento.
	CConsGrab::mysql.Exec("delete from estou_executando_agora");
	CConsGrab::mysql.Exec(
			"insert into estou_executando_agora(pedido,chegada) values(\'"
					+ Pedido[0][0] + "\',\'" + Pedido[0][1] + "\')");
	CConsGrab::mysql.Exec(
			"delete from queuepedidos where pedido=\'" + Pedido[0][0]
					+ "\' and chegada=\'" + Pedido[0][1] + "\'");

	if (Pedido[0][0] == "AADF") {
		//AADFS();
	} else if (Pedido[0][0] == "CUTOFFS") {
		//Cutoffs();
	} else if (Pedido[0][0] == "ANOMALIAS") {
		//GprtAnom();
	} else if (Pedido[0][0] == "GSPI_PORTUGAL") {
		//Gspi();
	} else if (Pedido[0][0] == "GRT") {
		//Grt();
	} else if (Pedido[0][0] == "FTSM_DIRENV_TRF") {
		//Ftsm();
	} else if (Pedido[0][0] == "FTSM_PARAM") {
		//FtsmParam();
	} else if (Pedido[0][0] == "FTSM") {
		// Ftsm();     GprtRec(1, 3)
	} else if (Pedido[0][0] == "REC") {
		//GprtRec(1, 3);
	} else if (Pedido[0][0] == "REC_ON") {
		CConsGrab::mysql.Exec("update looprec set doloop=1");
	} else if (Pedido[0][0] == "REC_OFF") {
		CConsGrab::mysql.Exec("update looprec set doloop=0");
	} else {
	}
	//pedido executado, limpar informacao
	CConsGrab::mysql.Exec("delete from estou_executando_agora");
}

bool CMenu::setTso(string stso) {

	tso = stso;
	/*
	 * implementar o processo todo de entrar no tso pe: TSOSYA1, pelo nome não pelo número
	 */

	return true;
}

bool CMenu::OpenPassword() {
	CTxtCrptDecript *ficheiro;
	vector<string> regs;
	ficheiro = new CTxtCrptDecript(PIPESPASS);
	regs = ficheiro->VirtualDecript();
	for (size_t i = 0; i < regs.size(); ++i) {
		switch (i) {
		case 0:
			usercgd = regs.at(i);
			Informar("usercgd=" + usercgd);
			break;
		case 1:
			passcgd = regs.at(i);
			break;
		case 2:
			usermcf = regs.at(i);
			Informar("usermcf=" + usermcf);
			break;
		case 3:
			passmcf = regs.at(i);
			break;
		case 4:
			userbcg = regs.at(i);
			Informar("userbcg=" + userbcg);
			break;
		case 5:
			passbcg = regs.at(i);
			break;
		}
	}
	ficheiro = new CTxtCrptDecript(PIPESPASSCEMG);
	regs = ficheiro->VirtualDecript();
	for (size_t i = 0; i < regs.size(); ++i) {
		switch (i) {
		case 0:
			usercemg = regs.at(i);
			Informar("usercemg=" + usercemg);
			break;
		case 1:
			passcemg = regs.at(i);
			break;

		}
	}
	return true;
}

bool CMenu::ElapsedTime(time_t t) {
	//devolver TRUE se t for maior que o difftime entre Agora e Antes
	time(&Agora);
	if (difftime(Agora, Antes) > t) {
		//reset ao timer
		Antes = Agora;
		return true;
	}
	return false;

}

bool CMenu::SessaoCaiuLocked(string u, string p) {
	int bk = exp_timeout;
	exp_timeout = 2;
	fprintf(fpipe, "ascii\r");
	int rc = exp_fexpectl(fpipe, exp_glob, "INDIQUE A OPÇÃO PRETENDIDA", 0,
			exp_glob, "INVALID COMMAND SINTAX", 1, exp_glob,
			"COMMAND UNRECOGNIZED", 2, exp_glob, "IVALID SWAP COMMAND SINTAX",
			3, exp_glob, "UNSUPORTED FUNCTION", 4, exp_glob,
			"COMANDO SWAP NO RECONOCIDO", 5, exp_glob,
			"C A I X A   E C O N O M I C A   M O N T E P I O   G E R A L", 6,

			exp_glob, "FUNCAO NAO SUPORTADA", 9, exp_glob,
			"Specify Disposition of Log Data Set", 10, exp_glob,
			"ISPF processor ended abnormally", 11,
//				exp_glob,"",1,
//				exp_glob,"",1,
//				exp_glob,"",1,

			exp_end);
	if (rc == 10) {
		EnterString("2");
	}
	if (rc == EXP_TIMEOUT) {
		Ok();
	}

	if (IsLocked() || rc != EXP_TIMEOUT) {
		Stop();
		Start(lpar);
		if (lpar == "MVS2") {
			//LoginTso(tso, u, p, 90);
		} else if (lpar.substr(0, 2) == "MG") {
			//LoginTsoCEMG(tso, u, p);

		} else {
			//LoginTso(tso, u, p);
		}
		exp_timeout = bk;
		return true;
	}
	exp_timeout = bk;
	return false;
}

void CMenu::Logoff(int int1) {
	int bkp_exp_timeout = exp_timeout, rc;	//salvaguardar o exp_timeout default
	exp_timeout = int1;
	cout << endl << "...logoff " << lpar << " .";
	Pf3();
	LimparBuffer();
	while (1) {
		cout << ".";
//		sleep(1);
//		Home();Eeof();EnterString("=x");Pf3();
//		EnterString("logoff");
//		sleep(1);
		LimparBuffer();
		Pf3();
		fprintf(fpipe, "ascii\r");
		rc = exp_fexpectl(fpipe, exp_glob,
				" READY                                 ", 1, exp_glob,
				"CAIXA GERAL DE DEPOSITOS, S.A.", 2, exp_glob, "IKJ56247I", 3,
				exp_glob, "Specify Disposition of Log Data Set", 4, exp_glob,
				"UNSUPPORTED FUNCTION", 5, exp_glob,
				"PONER CODIGO DE APLICACION Y PULSAR INTRO", 6, exp_glob,
				"IKJ56247I", 7, exp_glob, "SDSF DA MVS2", 8, exp_glob,
				"SDSF PRIMARY OPTION MENU", 9, exp_glob,
				"ISPF Primary Option Menu", 10, exp_glob,
				"BROWSING OPERATIONS ENDED IN ERROR", 11, exp_glob,
				"SPECIFYING ENDED IN ERROR LIST CRITERIA", 12, exp_glob,
				"TIVOLI WORKLOAD SCHEDULER FOR Z/OS", 13, exp_glob,
				"CO Control-D", 14, exp_glob, "BROWSING ACTIVE CRITICAL JOBS",
				15, exp_glob, "DEFINING TWSz PARAMETERS AND OPTIONS", 16,
				exp_glob, "TWSz CONTROLLERS AND SERVER LU NAMES", 17, exp_glob,
				"CURRENT PLAN AND STATUS INQUIRY", 18,
//				exp_glob,"",19,
//				exp_glob,"",20,
//				exp_glob,"",21,
//				exp_glob,"",22,
//				exp_glob,"",23,
//				exp_glob,"",24,
//				exp_glob,"",25,
//				exp_glob,"",26,
//				exp_glob,"",27,
//				exp_glob,"",28,
//				exp_glob,"",29,
//				exp_glob,"",30,
//				exp_glob,"",31,
//				exp_glob,"",32,

				exp_end);
		switch (rc) {
		//case 0:

		case 1:

			cout << "apareceu READY" << endl;
			EnterString("logoff");
			cout << "dado logoff" << endl;
			continue;
			break;
		case 5:
			Clear();
			continue;
			break;
		case 6:
		case 2:
			//sucesso
			cout << "logoff com sucesso" << endl;
			exp_timeout = bkp_exp_timeout;
			cout << ".";
			sleep(5);
			Stop();
			sleep(5);
			cout << ".feito stop";

			//CGprtRec::Pf3();
			//cout << ".";
			//EnterString("logoff");
			//EnterString("logoff");
			CConsGrab::mysql.Exec("replace into lpar3270 "
					"(activo3270,solicitadoDisconnect,lpar) "
					"values( 'n', 'n', '" + lpar + "')");
			cout << ".done" << endl;
			return;
			break;
		case 3:
			Enter();
			continue;
			break;
		case 4:
		case 7:
			Enter();
			continue;
			break;
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
		case 17:
		case 18:
		case EXP_TIMEOUT:
			//cout<<"timeout, continuar loop"<<endl;
			cout << ".";
			Home();
			Eeof();
			Pf3();
			//cout<<"dado Home();Eeof();Pf3();"<<endl;
			continue;
			break;
		}

	}

}


bool CMenu::LogonApplid(string applid, string u, string p) {
	int bkp_exp_timeout = exp_timeout, rc;	//salvaguardar o exp_timeout default

	exp_timeout = 5;
	//Pa2();
	//MoverCursor(22, 13);
	//Eeof();
	sleep(5);	//translation table
	//tsoname = applid;
	EnterString("logon applid(" + applid + ")");
	sleep(1);
	//IKJ56700A ENTER USERID - meter user
	cout << endl << ".logon applid(" << applid << ")." << endl;
	Clear();
	sleep(1);
	EnterString("cesn");
	sleep(1);

	//a partir daqui existem diversas possibilidades
	/*
	 * login puro, entrando com user e password até cair no painel do ispf
	 * login parcial onde falta introduzir o user / ou password / ou dar enter no ***
	 * login já completo mas com ecrã inexperado no tso
	 */
	Ok();
	while (1) {
		sleep(1);
		//Ok();
		fprintf(fpipe, "ascii\r");
		sleep(1);
		rc = exp_fexpectl(fpipe, exp_glob, "INDIQUE A OPÇÃO PRETENDIDA",
				0, //entrar com logon applid
				exp_glob, "CAIXA GERAL DE DEPOSITOS, S.A.",
				1, //entrar com logon applid
				exp_glob, "APPLD PARAMETER EXTRANEOUS",
				2, //fazer clear e entrar com logon applid
				exp_glob, "Type your userid and password",
				3, //entrar user e pass
				exp_glob, "(R)", 36, exp_glob, "DFHCE3549 SIGN-ON IS COMPLETE",
				38, exp_end);
		switch (rc) {
		case 2:
			Ok();
			Clear();
		case 0:
		case 1:
			Ok();
			EnterString("logon applid(" + applid + ")");
			//Clear();
			//Executar3270("Clear()");
			fprintf(fpipe, "clear\r");
			EnterString("cesn");
			continue;
			break;
		case 3:
			Ok();
			PutString(u);
			MoverCursor(10, 25);
			EnterString(p);
			continue;
			break;
		case 36:
			Ok();
			Clear();
			EnterString("cesn");
			continue;
			break;
		case 38:
			Ok();
			Clear();
			return true;
			break;
		case EXP_TIMEOUT:
			Ok();
			ShowThisScreen();
			Informar("Logon applid - ecra inexperado no tso, gerou timeout");
			Informar(
					"Vou executar lf e relogin neste applid n(" + applid + ")");
			//Pa2();
			sleep(1);
			Stop();
			Start(lpar);
			//EnterString("lf " + applid);
			sleep(1);
			EnterString("logon applid(" + applid + ")");
			Clear();
			EnterString("cesn");
			continue;
			//return false;
			break;
		}
		//break;
	}
	exp_timeout = bkp_exp_timeout;
	return true;
}

void CMenu::ConsGrab(string smcs) {

	cout << endl << ".";
	if (solicitado_stop())
		return;
	CConsGrab::SetFichout("smcs.txt");
	cout << ".";
	if (solicitado_stop())
		return;
	//CAADF::DBStart();

	CConsGrab::EstadoOn();
	cout << ".";
	if (solicitado_stop())
		return;
	//SetInsist(insist);
	cout << ".";
	if (solicitado_stop())
		return;

		CConsGrab::LimpaTabTemp(); //inicio de ciclo
		cout << ".";
		if (solicitado_stop())
			return;
		CConsGrab::loopCaptaConsole(smcs);
		cout << ".";
		if (solicitado_stop())
			return;
		CConsGrab::ActTempIntoOrig(); //fim de ciclo, registos novos na tabela

		//CGprtRec::ActTempIntoOrig(); //fim de ciclo, registos novos na tabela

	CConsGrab::EstadoOff();
	cout << ".done" << endl;
}

bool CMenu::ArrancarScmsSYB1(string user, string pass) {
	//AADFS();
	CTemporizador Timer;

	lpar = "SYB1";
	string con="syb1con3",smcs="scb1";
	//CGprtRec::setLpar(lpar);
	Start(lpar);
	CConsGrab::mysql.Exec("update run set parar=0");
	CConsGrab::smcs=smcs;

	/*
	 * Registar em ficheiro de log quem está a fazer login quando solicitado conforme checklist
	 */
	ofstream fichlog;
	string estampa_hora=GetStrTimestamp();
	string fich = "/var/www/html/checklist/arquivo/OSMCS_LOG.txt";
	fichlog.open(fich.c_str(), std::fstream::app);		//abrir em MOD!
	if (fichlog.is_open()) {
		fichlog << estampa_hora << ": "<<user<<" FEZ LOGIN SMCS "<<lpar<<con<<smcs<<endl;
	}

	if(!LogonSMCS(smcs,con, user, pass)){
		return false;
	}
	/*
	 * Enttrou no cics, e voltou com ecra limpo, pronto para se entrar com a transacção RTGS
	 *
	 */
	//EnterString("rtgs");
	Timer.Iniciar();
	while (!solicitado_stop()) {
		/*
		 * Verificar se o teclado está locked
		 * ou se a sessão caiu
		 */
		if (SessaoCaiuLocked(user, pass)) {
			continue;
		}

		//Clear();
		//EnterString("rtgs");
		//capturar ecrã
		/*
		 * Todo WTO aparece com * na posicao 0 x 5
		 *
		 * consola presa se ficar com * em 23 x 5
		 */
		ConsGrab(smcs);
		Consultar_e_Submeter_comando();

		if (solicitado_stop())
			break;

		Informar("sleep " + IntToString(SLEEPTIME));
		//Informar("Esperar "+IntToString(SLEEPTIME));
		sleep(SLEEPTIME);
		LimparBuffer();
		if (solicitado_stop())
			break;
		//relogin timer
		Informar(
				"falta " + IntToString((RELOGINTIMER - Timer.Instante()) / 60)
						+ " minutos de " + IntToString(RELOGINTIMER / 60)
						+ " minutos para 0 minutos para re-login");
		//Informar("falta "+IntToString(Timer.Instante())+" para "+IntToString(RELOGINTIMER)));
		if (Timer.Instante() > RELOGINTIMER) {
			//CGprtRec::mysql.Exec("update run set parar=1");
			Informar("Relogin ");
			Timer.Iniciar();			//reset
			//Logoff();
			Stop();
			if (solicitado_stop())
				break;
			//setTso("TSOSYB1");
			Start(lpar);
			//LogedNetView=false;
			//LoginNetView(lpar);
			if(!LogonSMCS(smcs,con, user, pass)){
					return false;
				}

			CConsGrab::mysql.Exec("update run set parar=0");

		}
	}
	CConsGrab::mysql.Exec("update run set parar=1");
	return true;
}


bool CMenu::ArrancarScmsSYA1(string user, string pass) {
	//AADFS();
	CTemporizador Timer;

	lpar = "SYA1";
	string con="sya1con3",smcs="sca1";
	//CGprtRec::setLpar(lpar);
	Start(lpar);
	CConsGrab::mysql.Exec("update run set parar=0");
	CConsGrab::smcs=smcs;

	/*
	 * Registar em ficheiro de log quem está a fazer login quando solicitado conforme checklist
	 */
	ofstream fichlog;
	string estampa_hora=GetStrTimestamp();
	string fich = "/var/www/html/checklist/arquivo/OSMCS_LOG.txt";
	fichlog.open(fich.c_str(), std::fstream::app);		//abrir em MOD!
	if (fichlog.is_open()) {
		fichlog << estampa_hora << ": "<<user<<" FEZ LOGIN SMCS "<<lpar<<con<<smcs<<endl;
	}

	if(!LogonSMCS(smcs,con, user, pass)){
		return false;
	}
	/*
	 * Enttrou no cics, e voltou com ecra limpo, pronto para se entrar com a transacção RTGS
	 *
	 */
	//EnterString("rtgs");
	Timer.Iniciar();
	while (!solicitado_stop()) {
		/*
		 * Verificar se o teclado está locked
		 * ou se a sessão caiu
		 */
		if (SessaoCaiuLocked(user, pass)) {
			continue;
		}

		//Clear();
		//EnterString("rtgs");
		//capturar ecrã
		/*
		 * Todo WTO aparece com * na posicao 0 x 5
		 *
		 * consola presa se ficar com * em 23 x 5
		 */
		ConsGrab(smcs);
		Consultar_e_Submeter_comando();

		if (solicitado_stop())
			break;

		Informar("sleep " + IntToString(SLEEPTIME));
		//Informar("Esperar "+IntToString(SLEEPTIME));
		sleep(SLEEPTIME);
		LimparBuffer();
		if (solicitado_stop())
			break;
		//relogin timer
		Informar(
				"falta " + IntToString((RELOGINTIMER - Timer.Instante()) / 60)
						+ " minutos de " + IntToString(RELOGINTIMER / 60)
						+ " minutos para 0 minutos para re-login");
		//Informar("falta "+IntToString(Timer.Instante())+" para "+IntToString(RELOGINTIMER)));
		if (Timer.Instante() > RELOGINTIMER) {
			//CGprtRec::mysql.Exec("update run set parar=1");
			Informar("Relogin ");
			Timer.Iniciar();			//reset
			//Logoff();
			Stop();
			if (solicitado_stop())
				break;
			//setTso("TSOSYB1");
			Start(lpar);
			//LogedNetView=false;
			//LoginNetView(lpar);
			if(!LogonSMCS(smcs,con, user, pass)){
					return false;
				}

			CConsGrab::mysql.Exec("update run set parar=0");

		}
	}
	CConsGrab::mysql.Exec("update run set parar=1");
	return true;
}



bool CMenu::ArrancarScmsMCFB(string user, string pass) {
	//AADFS();
	CTemporizador Timer;

	lpar = "MCFB";
	string con="mcfbcon3",smcs="scmb";
	//CGprtRec::setLpar(lpar);
	Start(lpar);
	CConsGrab::mysql.Exec("update run set parar=0");
	CConsGrab::smcs=smcs;

	/*
	 * Registar em ficheiro de log quem está a fazer login quando solicitado conforme checklist
	 */
	ofstream fichlog;
	string estampa_hora=GetStrTimestamp();
	string fich = "/var/www/html/checklist/arquivo/OSMCS_LOG.txt";
	fichlog.open(fich.c_str(), std::fstream::app);		//abrir em MOD!
	if (fichlog.is_open()) {
		fichlog << estampa_hora << ": "<<user<<" FEZ LOGIN SMCS "<<lpar<<con<<smcs<<endl;
	}

	if(!LogonSMCS(smcs,con, user, pass)){
		return false;
	}
	/*
	 * Enttrou no cics, e voltou com ecra limpo, pronto para se entrar com a transacção RTGS
	 *
	 */
	//EnterString("rtgs");
	Timer.Iniciar();
	while (!solicitado_stop()) {
		/*
		 * Verificar se o teclado está locked
		 * ou se a sessão caiu
		 */
		if (SessaoCaiuLocked(user, pass)) {
			continue;
		}

		//Clear();
		//EnterString("rtgs");
		//capturar ecrã
		/*
		 * Todo WTO aparece com * na posicao 0 x 5
		 *
		 * consola presa se ficar com * em 23 x 5
		 */
		ConsGrab(smcs);
		Consultar_e_Submeter_comando();

		if (solicitado_stop())
			break;

		Informar("sleep " + IntToString(SLEEPTIME));
		//Informar("Esperar "+IntToString(SLEEPTIME));
		sleep(SLEEPTIME);
		LimparBuffer();
		if (solicitado_stop())
			break;
		//relogin timer
		Informar(
				"falta " + IntToString((RELOGINTIMER - Timer.Instante()) / 60)
						+ " minutos de " + IntToString(RELOGINTIMER / 60)
						+ " minutos para 0 minutos para re-login");
		//Informar("falta "+IntToString(Timer.Instante())+" para "+IntToString(RELOGINTIMER)));
		if (Timer.Instante() > RELOGINTIMER) {
			//CGprtRec::mysql.Exec("update run set parar=1");
			Informar("Relogin ");
			Timer.Iniciar();			//reset
			//Logoff();
			Stop();
			if (solicitado_stop())
				break;
			//setTso("TSOSYB1");
			Start(lpar);
			//LogedNetView=false;
			//LoginNetView(lpar);
			if(!LogonSMCS(smcs,con, user, pass)){
					return false;
				}

			CConsGrab::mysql.Exec("update run set parar=0");

		}
	}
	CConsGrab::mysql.Exec("update run set parar=1");
	return true;
}

bool CMenu::ArrancarScmsMCFA(string user, string pass) {
	//AADFS();
	CTemporizador Timer;

	lpar = "MCFA";
	string con="mcfacon3",smcs="scma";
	//CGprtRec::setLpar(lpar);
	Start(lpar);
	CConsGrab::mysql.Exec("update run set parar=0");
	CConsGrab::smcs=smcs;

	/*
	 * Registar em ficheiro de log quem está a fazer login quando solicitado conforme checklist
	 */
	ofstream fichlog;
	string estampa_hora=GetStrTimestamp();
	string fich = "/var/www/html/checklist/arquivo/OSMCS_LOG.txt";
	fichlog.open(fich.c_str(), std::fstream::app);		//abrir em MOD!
	if (fichlog.is_open()) {
		fichlog << estampa_hora << ": "<<user<<" FEZ LOGIN SMCS "<<lpar<<con<<smcs<<endl;
	}

	if(!LogonSMCS(smcs,con, user, pass)){
		return false;
	}
	/*
	 * Enttrou no cics, e voltou com ecra limpo, pronto para se entrar com a transacção RTGS
	 *
	 */
	//EnterString("rtgs");
	Timer.Iniciar();
	while (!solicitado_stop()) {
		/*
		 * Verificar se o teclado está locked
		 * ou se a sessão caiu
		 */
		if (SessaoCaiuLocked(user, pass)) {
			continue;
		}

		//Clear();
		//EnterString("rtgs");
		//capturar ecrã
		/*
		 * Todo WTO aparece com * na posicao 0 x 5
		 *
		 * consola presa se ficar com * em 23 x 5
		 */
		ConsGrab(smcs);
		Consultar_e_Submeter_comando();

		if (solicitado_stop())
			break;

		Informar("sleep " + IntToString(SLEEPTIME));
		//Informar("Esperar "+IntToString(SLEEPTIME));
		sleep(SLEEPTIME);
		LimparBuffer();
		if (solicitado_stop())
			break;
		//relogin timer
		Informar(
				"falta " + IntToString((RELOGINTIMER - Timer.Instante()) / 60)
						+ " minutos de " + IntToString(RELOGINTIMER / 60)
						+ " minutos para 0 minutos para re-login");
		//Informar("falta "+IntToString(Timer.Instante())+" para "+IntToString(RELOGINTIMER)));
		if (Timer.Instante() > RELOGINTIMER) {
			//CGprtRec::mysql.Exec("update run set parar=1");
			Informar("Relogin ");
			Timer.Iniciar();			//reset
			//Logoff();
			Stop();
			if (solicitado_stop())
				break;
			//setTso("TSOSYB1");
			Start(lpar);
			//LogedNetView=false;
			//LoginNetView(lpar);
			if(!LogonSMCS(smcs,con, user, pass)){
					return false;
				}

			CConsGrab::mysql.Exec("update run set parar=0");

		}
	}
	CConsGrab::mysql.Exec("update run set parar=1");
	return true;
}

bool CMenu::ArrancarScmsMG1P(string user, string pass) {
	//AADFS();
	CTemporizador Timer;

	lpar = "MG1P";
	string con="mg1pcon2",smcs="mg1pc";
	//CGprtRec::setLpar(lpar);
	Start(lpar);
	CConsGrab::mysql.Exec("update run set parar=0");
	CConsGrab::smcs=smcs;

	/*
	 * Registar em ficheiro de log quem está a fazer login quando solicitado conforme checklist
	 */
	ofstream fichlog;
	string estampa_hora=GetStrTimestamp();
	string fich = "/var/www/html/checklist/arquivo/OSMCS_LOG.txt";
	fichlog.open(fich.c_str(), std::fstream::app);		//abrir em MOD!
	if (fichlog.is_open()) {
		fichlog << estampa_hora << ": "<<user<<" FEZ LOGIN SMCS "<<lpar<<con<<smcs<<endl;
	}

	if(!LogonSMCS(smcs,con, user, pass)){
		return false;
	}
	/*
	 * Enttrou no cics, e voltou com ecra limpo, pronto para se entrar com a transacção RTGS
	 *
	 */
	//EnterString("rtgs");
	Timer.Iniciar();
	while (!solicitado_stop()) {
		/*
		 * Verificar se o teclado está locked
		 * ou se a sessão caiu
		 */
		if (SessaoCaiuLocked(user, pass)) {
			continue;
		}

		//Clear();
		//EnterString("rtgs");
		//capturar ecrã
		/*
		 * Todo WTO aparece com * na posicao 0 x 5
		 *
		 * consola presa se ficar com * em 23 x 5
		 */
		ConsGrab(smcs);
		Consultar_e_Submeter_comando();

		if (solicitado_stop())
			break;

		Informar("sleep " + IntToString(SLEEPTIME));
		//Informar("Esperar "+IntToString(SLEEPTIME));
		sleep(SLEEPTIME);
		LimparBuffer();
		if (solicitado_stop())
			break;
		//relogin timer
		Informar(
				"falta " + IntToString((RELOGINTIMER - Timer.Instante()) / 60)
						+ " minutos de " + IntToString(RELOGINTIMER / 60)
						+ " minutos para 0 minutos para re-login");
		//Informar("falta "+IntToString(Timer.Instante())+" para "+IntToString(RELOGINTIMER)));
		if (Timer.Instante() > RELOGINTIMER) {
			//CGprtRec::mysql.Exec("update run set parar=1");
			Informar("Relogin ");
			Timer.Iniciar();			//reset
			//Logoff();
			Stop();
			if (solicitado_stop())
				break;
			//setTso("TSOSYB1");
			Start(lpar);
			//LogedNetView=false;
			//LoginNetView(lpar);
			if(!LogonSMCS(smcs,con, user, pass)){
					return false;
				}

			CConsGrab::mysql.Exec("update run set parar=0");

		}
	}
	CConsGrab::mysql.Exec("update run set parar=1");
	return true;
}


bool CMenu::ArrancarScmsMG1T(string user, string pass) {
	//AADFS();
	CTemporizador Timer;

	lpar = "MG1T";
	string con="mg1tcon2",smcs="mg1tc";
	//CGprtRec::setLpar(lpar);
	Start(lpar);
	CConsGrab::mysql.Exec("update run set parar=0");
	CConsGrab::smcs=smcs;

	/*
	 * Registar em ficheiro de log quem está a fazer login quando solicitado conforme checklist
	 */
	ofstream fichlog;
	string estampa_hora=GetStrTimestamp();
	string fich = "/var/www/html/checklist/arquivo/OSMCS_LOG.txt";
	fichlog.open(fich.c_str(), std::fstream::app);		//abrir em MOD!
	if (fichlog.is_open()) {
		fichlog << estampa_hora << ": "<<user<<" FEZ LOGIN SMCS "<<lpar<<con<<smcs<<endl;
	}

	if(!LogonSMCS(smcs,con, user, pass)){
		return false;
	}
	/*
	 * Enttrou no cics, e voltou com ecra limpo, pronto para se entrar com a transacção RTGS
	 *
	 */
	//EnterString("rtgs");
	Timer.Iniciar();
	while (!solicitado_stop()) {
		/*
		 * Verificar se o teclado está locked
		 * ou se a sessão caiu
		 */
		if (SessaoCaiuLocked(user, pass)) {
			continue;
		}

		//Clear();
		//EnterString("rtgs");
		//capturar ecrã
		/*
		 * Todo WTO aparece com * na posicao 0 x 5
		 *
		 * consola presa se ficar com * em 23 x 5
		 */
		ConsGrab(smcs);
		Consultar_e_Submeter_comando();

		if (solicitado_stop())
			break;

		Informar("sleep " + IntToString(SLEEPTIME));
		//Informar("Esperar "+IntToString(SLEEPTIME));
		sleep(SLEEPTIME);
		LimparBuffer();
		if (solicitado_stop())
			break;
		//relogin timer
		Informar(
				"falta " + IntToString((RELOGINTIMER - Timer.Instante()) / 60)
						+ " minutos de " + IntToString(RELOGINTIMER / 60)
						+ " minutos para 0 minutos para re-login");
		//Informar("falta "+IntToString(Timer.Instante())+" para "+IntToString(RELOGINTIMER)));
		if (Timer.Instante() > RELOGINTIMER) {
			//CGprtRec::mysql.Exec("update run set parar=1");
			Informar("Relogin ");
			Timer.Iniciar();			//reset
			//Logoff();
			Stop();
			if (solicitado_stop())
				break;
			//setTso("TSOSYB1");
			Start(lpar);
			//LogedNetView=false;
			//LoginNetView(lpar);
			if(!LogonSMCS(smcs,con, user, pass)){
					return false;
				}

			CConsGrab::mysql.Exec("update run set parar=0");

		}
	}
	CConsGrab::mysql.Exec("update run set parar=1");
	return true;
}

bool CMenu::ArrancarScmsMG1D(string user, string pass) {
	//AADFS();
	CTemporizador Timer;

	lpar = "MG1D";
	string con="mg1dcon2",smcs="mg1dc";
	//CGprtRec::setLpar(lpar);
	Start(lpar);
	CConsGrab::mysql.Exec("update run set parar=0");
	CConsGrab::smcs=smcs;

	/*
	 * Registar em ficheiro de log quem está a fazer login quando solicitado conforme checklist
	 */
	ofstream fichlog;
	string estampa_hora=GetStrTimestamp();
	string fich = "/var/www/html/checklist/arquivo/OSMCS_LOG.txt";
	fichlog.open(fich.c_str(), std::fstream::app);		//abrir em MOD!
	if (fichlog.is_open()) {
		fichlog << estampa_hora << ": "<<user<<" FEZ LOGIN SMCS "<<lpar<<con<<smcs<<endl;
	}

	if(!LogonSMCS(smcs,con, user, pass)){
		return false;
	}
	/*
	 * Enttrou no cics, e voltou com ecra limpo, pronto para se entrar com a transacção RTGS
	 *
	 */
	//EnterString("rtgs");
	Timer.Iniciar();
	while (!solicitado_stop()) {
		/*
		 * Verificar se o teclado está locked
		 * ou se a sessão caiu
		 */
		if (SessaoCaiuLocked(user, pass)) {
			continue;
		}

		//Clear();
		//EnterString("rtgs");
		//capturar ecrã
		/*
		 * Todo WTO aparece com * na posicao 0 x 5
		 *
		 * consola presa se ficar com * em 23 x 5
		 */
		ConsGrab(smcs);
		Consultar_e_Submeter_comando();

		if (solicitado_stop())
			break;

		Informar("sleep " + IntToString(SLEEPTIME));
		//Informar("Esperar "+IntToString(SLEEPTIME));
		sleep(SLEEPTIME);
		LimparBuffer();
		if (solicitado_stop())
			break;
		//relogin timer
		Informar(
				"falta " + IntToString((RELOGINTIMER - Timer.Instante()) / 60)
						+ " minutos de " + IntToString(RELOGINTIMER / 60)
						+ " minutos para 0 minutos para re-login");
		//Informar("falta "+IntToString(Timer.Instante())+" para "+IntToString(RELOGINTIMER)));
		if (Timer.Instante() > RELOGINTIMER) {
			//CGprtRec::mysql.Exec("update run set parar=1");
			Informar("Relogin ");
			Timer.Iniciar();			//reset
			//Logoff();
			Stop();
			if (solicitado_stop())
				break;
			//setTso("TSOSYB1");
			Start(lpar);
			//LogedNetView=false;
			//LoginNetView(lpar);
			if(!LogonSMCS(smcs,con, user, pass)){
					return false;
				}

			CConsGrab::mysql.Exec("update run set parar=0");

		}
	}
	CConsGrab::mysql.Exec("update run set parar=1");
	return true;
}

bool CMenu::LogonSMCS(string smcs,string con,string u, string p) {
	int bkp_exp_timeout = exp_timeout, rc;	//salvaguardar o exp_timeout default

	exp_timeout = 5;
	//Pa2();
	//MoverCursor(22, 13);
	//Eeof();
	//cout << "["<<p<<"]"<<endl;
	//return false;
	sleep(5);		//translation table
	//tsoname = applid;
	EnterString(smcs);
	//EnterString("logon applid("+smcs+")");
	cout << endl << "."<<smcs<<"." << endl;
	sleep(1);
	MoverCursor(4,19);
	EnterString(con);
	cout << endl << "."<<con<<"." << endl;
	sleep(1);
	//IKJ56700A ENTER USERID - meter user



	//a partir daqui existem diversas possibilidades
	/*
	 * login puro, entrando com user e password até cair no painel do ispf
	 * login parcial onde falta introduzir o user / ou password / ou dar enter no ***
	 * login já completo mas com ecrã inexperado no tso
	 */
	//Ok();
	while (1) {
		sleep(1);
		//Ok();
		fprintf(fpipe, "ascii\r");
		sleep(1);
		rc = exp_fexpectl(fpipe,
				exp_glob, "IEE801A",0,
				exp_glob, "IEE802A",1,
				exp_glob, "IEE187I",2,
				exp_glob, "USERID/PASSWORD NOT AUTHORIZED",3,
				exp_glob, "IEE612I",4,
				exp_end);
		switch (rc) {

		case 0:
			Ok();
			MoverCursor(4,19);
			EnterString(con);
			//sleep(10);
			continue;
			break;
		case 1:
			Ok();
			Informar("IEE802A The Console Name is already active. ");
			return false;
			break;
		case 2:
			Ok();
			PutString(u);
			Tab();
			EnterString(p);
			Informar("Entrando com user e password na consola");
			continue;
			break;
		case 3:
			Ok();
			Informar("USERID/PASSWORD NOT AUTHORIZED");
			return false;
			break;
		case 4:
			Ok();
			NewLine();
			EnterString("k s,del=rd");
			Informar("Consola colocada em RD, logon smcs concluido.");
			return true;
			break;
		case EXP_TIMEOUT:
			Ok();
			ShowThisScreen();
			Informar("TIMEOUT");

			//Pa2();
			sleep(1);
			Stop();
			Start(lpar);
			//EnterString("lf " + applid);
			sleep(1);
			continue;
			break;
		}
		//break;
	}
	exp_timeout = bkp_exp_timeout;
	return true;
}

void CMenu::Consultar_e_Submeter_comando() {
	vector<vector<string> > cmd;

	cmd = mysql.ExecGetData("select indice,cmd from cmd where ativo=1 limit 1");
	if(!cmd.empty()){
		//limpar a linha de comando
		Home();
		Eeof();
		EnterString(cmd.at(0).at(1));
		//limpar a linha de comando
		Home();
		Eeof();
		mysql.Exec("update cmd set ativo=0 where indice='"+cmd.at(0).at(0)+"'");
	}

}
