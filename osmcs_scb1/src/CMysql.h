/*
 * mysql.h
 *
 *  Created on: Jan 31, 2012
 *      Author: ptsca012
 */
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <string>
//#include "mysql_driver.h"
//#include "mysql_connection.h"
//#include <cppconn/driver.h>
//#include <cppconn/exception.h>
//#include <cppconn/resultset.h>
//#include <cppconn/statement.h>
//#include <cppconn/prepared_statement.h>
//#include <mariadbclient/include/mysql.h>


//#include <my_global.h>

using namespace std;
using std::string;

#ifndef MYSQL_H_
#define MYSQL_H_
#include <mysql/mysql.h>
class CMysql
{
private:
	//mysqlc++:
	MYSQL *conn;
//	sql::Driver * driver;// = get_driver_instance();
//	sql::Connection * con;//(driver->connect(url, user, pass));
//	sql::Statement * stmt;//sql.
//	sql::ResultSet * res;//resultados.
//	sql::ResultSetMetaData * my_meta;
	string user;
	string pass;
	string url;
	string db;
        string erro;

	string Sql;//código sql a se executado.
	int numInstruc;
	void FinishError();
public:
	CMysql();
	virtual ~CMysql();
	bool Open(string,string,string,string);//user,pass,host,db
	void Close();
	const bool Exec(string);//sem resultado
	const bool Exec();//sem resultado
	string ExecGetSingle(string);//retorna resultado em string &
	/*
	 * com indicação de cols em int, é devolvido um vector de
	 * numero de tuplas registo X cols
	 * vector< vector<string> >
	 */
	//const bool exec_query(string&,vector< vector<string> > &,int);
	vector< vector<string> > ExecGetData(string);
	//devolver uma coluna
	vector<string> ExecGetColumn(string);

	//const bool exec_query_silent(string&);//executa a query sql sem retorno.

	//void FreeMem();
	int CountTable(string);
	int StringToInt(string);
	void Clear(string);//limpar a tabela

	//acumular codigo sql para execução posterior via transacção
	void SqlAdd(string linha){Sql+=linha;Sql+=";\n";numInstruc++;};
	//limpar o conteudo de Sql
	void SqlNew(){Sql.clear();Sql="BEGIN;\n";numInstruc=0;}
	//com o sql acumulado em Sql, adicionar Begin; e commit;
	void SqlFinalize(){Sql+="COMMIT;";}
	void SqlShow(){cout<<endl<<Sql<<endl;}
        
        string Erro(){return erro;}
};

#endif /* MYSQL_H_ */
