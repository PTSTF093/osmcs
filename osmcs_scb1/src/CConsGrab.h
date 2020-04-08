/* 
 * File:   CGprtRec.h
 * Author: marlon.simoni
 *
 * Created on 16 de Março de 2014, 14:34
 */
#include "CCon3270.h"
#include "CMysql.h"




#ifndef CGPRTREC_H
#define	CGPRTREC_H

#include <fstream>
#include <cctype>
#include "Csessao.h"


// trim from start
static inline std::string &ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
        return ltrim(rtrim(s));
}


class CConsGrab : public CCon3270  {
    /*
     implementar alguns metodos a classe principal CCon3270*/
public:
    CConsGrab();
    CConsGrab(const CConsGrab& orig);
    virtual ~CConsGrab();

    void SetFichout(string);

    void GetCons(); //1

    void Next();
    void SetInsist(int x = 0);

    string GetTimestamp() {
        string ts;
        time_t ltime; //calendar time
        char buffer[80];

        ltime = time(NULL); //get current calendar time
        //ts=asctime(localtime(&ltime));
        //
        strftime(buffer, 80, "%d-%m-%Y %X: ", localtime(&ltime));
        ts=buffer;

        return ts;
    }

    //string Informar() {
    //    string info;
    ///    info = GetTimestamp();
    //    info += " (t=" + IntToString(exp_timeout) + "): ";
   //     return info;
    //}

    void DBStart(string h="127.0.0.1",string u="root", string p="", string d="scb1");

    void LimpaTabTemp();//limpar a tabela temp
    void ActTempIntoOrig();//carregar tabela temp na verdadeira
    
    
void EstadoOn() {
        string sql = "update uactualizacao set estado=\'<a class=\"sessok\">O</a>\' where tabela=\'console\'";
        //cout << sql << endl;
        mysql.Exec(sql);
    }

    void EstadoOff() {
        string sql = "update uactualizacao set estado=\'<a class=\"sessnok\">F</a>\' where tabela=\'console\'";

        mysql.Exec(sql);
    }    
    
    void UpdtLoop(int,int);
private:
    ofstream fichout;
    //FILE *fpipe;
    //CCon3270 C;


    int insist;
public:        
    CMysql mysql;
    void loopCaptaConsole(string);
    string smcs;
   
};

#endif	/* CGPRTREC_H */

