/*
 * File:   main.cpp
 * Author: Marlon
 *
 * Created on 16 de Março de 2014, 21:31
 */
//g++ gprtrec.cpp -o gprtrec -l:libexpect5.45.dll.a -ltcl8.5 -ltclstub8.5 -lm
#include <iostream>
#include <fstream>


//#include <ios>
//#include <cstdlib>
//#include <ctype.h>
//#include <algorithm>
//
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

//#include "CCon3270.h"
#include "CMenu.h"

int main(int argc, char**argv) {
    //CCon3270 conex;

    CMenu menu("scb1");
    //cout<<argv[1]<<" "<<argv[2]<<endl;
    //return 0;
    if(argc!=3){
    	cout<<"Erro na contagem de parâmetros: necessário passar USER PASSWORD"<<endl;
    }
    //menu.LoginNetView("SYB1");
    try {
    	if(!menu.ArrancarScmsSYB1(argv[1],argv[2])){
    		return 200;
    	}
	} catch (const std::out_of_range & e) {
		for(int i=0;i<25;++i){
			cout<<"OCICS TARJETAS MVS2 CAIU !!!!! "<<e.what()<<endl;
		}
	}

    return 0;
}
