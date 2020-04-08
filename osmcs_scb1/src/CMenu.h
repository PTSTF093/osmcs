/* 
 * File:   CMenu.h
 * Author: marlon.simoni
 *
 * Created on 8 de Abril de 2014, 15:58
 */

#ifndef CMENU_H
#define	CMENU_H


#include <fstream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string>

#include "CConsGrab.h"
#include "CMysql.h"
#include "CTemporizador.h"
#ifndef YYIBM01
#define SLEEPTIME 1 //segundo
#define RELOGINTIMER 1*60*60*24*30
#else
#define SLEEPTIME 1
#define RELOGINTIMER  1*60*60*24*30
#endif


class CMenu : public CConsGrab  {
public:
    CMenu();
    CMenu(string);//para connectar a db do cemg e não do pipes.
    CMenu(const CMenu& orig);
    virtual ~CMenu();
    
    bool EnterComando();
    void PrintMenu();
    bool SolicitadoSair(){ return sair; }
    bool LoginNetView(string l);
    bool SessaoCaiuLocked(string u, string p);
    /*
     * RTGS
     */
    bool ArrancarMG1PRTGS(string,string);//é passado user e password
    bool ArrancarScmsSYB1(string,string);//é passado user e password
    bool ArrancarScmsSYA1(string,string);//é passado user e password
    bool ArrancarScmsMCFB(string,string);//é passado user e password
    bool ArrancarScmsMCFA(string,string);//é passado user e password

    void Consultar_e_Submeter_comando();

    bool ArrancarScmsMG1D(string,string);//é passado user e password
    bool ArrancarScmsMG1P(string,string);//é passado user e password
    bool ArrancarScmsMG1T(string,string);//é passado user e password

    bool LogonApplid(string,string,string);//applid,user,pass
    bool LogonSMCS(string,string,string,string);//smcs,syb1con3,user e pass
    //void GprtRec(int loops=0,int insist=0);

private:
    time_t Agora;
    time_t Antes;
    string usercgd,usermcf,userbcg,usercemg;
            string passcgd,passmcf,passbcg,passcemg;
    string tso,lpar;
    

    /*Controle de sessao no host*/
    bool OpenPassword();//abrir password encriptada.
    bool LoginNetView();

    bool setTso(string);
    void LogoutAll();
    void Logoff();//desconectar tso
    void Logoff(int);//logoff com parametro de timout s3270
    
    /*opcoes*/
    void Cutoffs();
    void AADFS();
    void GprtAnom();
    void ConsGrab(string);
    void Gspi();
    void Grt();
    void Ftsm();
    void FtsmParam();
    
    void QueyQueuePedidos();
    
    string comando;
    bool sair;
    bool LogedNetView;//esta logado no netview
    bool LoopRec;
    
    bool solicitado_stop();
    bool QueryLoopRec();
    
    bool ElapsedTime(time_t t);//
};

#endif	/* CMENU_H */

