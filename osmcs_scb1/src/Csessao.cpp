/* 
 * File:   Csessao.cpp
 * Author: marlon.simoni
 * 
 * Created on 17 de Dezembro de 2015, 22:46
 */

#include "Csessao.h"

Csessao::Csessao() {
    tj=0;
    numJanelasCheias=0;
    
    cics.clear();
    sigla="        ";
    sess.clear();
    traf.clear();
    trans.clear();

    elemento.clear();
    est_elemento.clear();
    est_conex.clear();
    n_ope_saf.clear();
    estado_bd.clear();

}
/*
Csessao::Csessao(const Csessao& orig) {
    
}
*/
void Csessao::Reset(){
    tj=0;
    numJanelasCheias=0;
    
    cics.clear();
    sigla="        ";
    sess.clear();
    traf.clear();
    trans.clear();
    elemento.clear();
    est_elemento.clear();
    est_conex.clear();
    n_ope_saf.clear();
    estado_bd.clear();
}

Csessao::~Csessao() {
    /*
    delete cics;
    delete sigla;
    delete sess;
    delete traf;
    delete trans;
    */
}

bool Csessao::mesmaSessao(std::string ssigla){
    //std::cout<<"sigla:"<<sigla<<" ssigla:"<<ssigla<<std::endl;
    return sigla == ssigla;
}

void Csessao::Incrementar(){
    //if(! isnum(numJanelasCheias))
    numJanelasCheias++;
}
