/*
 * mysql.cpp
 *
 *  Created on: Jan 31, 2012
 *      Author: ptsca012
 */

#include "CMysql.h"

CMysql::CMysql()
{
	conn = mysql_init ( NULL );
	numInstruc=0;
}

CMysql::~CMysql()
{

	mysql_close ( conn );
	//cout<<"Desconectado da BD"<<endl;
}

bool CMysql::Open(string puser,string ppass,string purl,string pdb)
{//string u="root",h="127.0.0.1",p="pipes",dbps="openpipes";
//my.start(u, dbps, h, p);
	user=puser;
	pass=ppass;
	url=purl;
	db=pdb;
        
//        if(ppass==""){
//            
//        }

	if(mysql_real_connect ( conn, url.c_str(), user.c_str(),
	            pass.c_str(), db.c_str(), 0, NULL, 0 )==NULL)
		return false;

	return true;
}

/*
 * Executar a query sem retornar resultado.
 * true on succes other false
 */
const bool CMysql::Exec(string qry)
{
	int st=mysql_query(conn,qry.c_str());
        erro=mysql_error(conn);
	return st==0;
}

void CMysql::FinishError() {
	cout<<"ERRO: "<<endl<<mysql_error(conn)<<endl;
	//mysql_close(conn);
	//exit(1);
}

/*
 * executar a query e o unico resultado fica em resultado
 *  Steps:

    Create a connection
    Execute query
    Get the result set
    Fetch all available rows
    Free the result set
 *
 */
string CMysql::ExecGetSingle(string qry)
{
	//MYSQL_FIELD *campo;
	MYSQL_ROW row;
	MYSQL_RES * result;//=mysql_use_result(conn);
	int numero_campos;
	string resultado;

	//executar a query.
	if(mysql_query(conn,qry.c_str())){
			FinishError();
			return resultado;
	}

	//get resultset
	result=mysql_use_result(conn);
	if(result==NULL){
		FinishError();
		return resultado;
	}

	//quantos campos?
	numero_campos=mysql_num_fields(result);

	while ((row = mysql_fetch_row(result)))
	{
		for(int i = 0; i < numero_campos; i++)
		{
			//printf("%s ", row[i] ? row[i] : "NULL");
			resultado=row[i];// ? row[i]:"NULL";
		}
		//printf("\n");
	}

	mysql_free_result(result);

	return resultado;
}

void CMysql::Close() {
	mysql_close ( conn );
}

const bool CMysql::Exec() {
	if(numInstruc==0){
		cout<<"0 instruções na transacção."<<endl;
		return true;
	}
	int st=mysql_query(conn,Sql.c_str());
	return st==0;
}

/*
 * executar a query=qry
 * e retornar no vector de strings &resultado
 */
vector< vector<string> > CMysql::ExecGetData(string qry)
{
	//MYSQL_FIELD *campo;
	MYSQL_ROW row;
	MYSQL_RES * result;//=mysql_use_result(conn);
	int numero_campos;
	string resultado;
	vector<string> Linha;
	vector<vector<string> > Resultado;

	//executar a query.
	if(mysql_query(conn,qry.c_str())){
		FinishError();
		return Resultado;
	}

	//get resultset
	result=mysql_use_result(conn);
	if(result==NULL){
		FinishError();
		return Resultado;
	}

	//quantos campos?
	numero_campos=mysql_num_fields(result);

	while ((row = mysql_fetch_row(result)))
	{
		Linha.clear();
		for(int i = 0; i < numero_campos; i++)
		{
			//printf("%s ", row[i] ? row[i] : "NULL");
			resultado=row[i] ? row[i]:"NULL";
			Linha.push_back(resultado);
		}
		//printf("\n");
		Resultado.push_back(Linha);
	}

	mysql_free_result(result);

	return Resultado;
}


//const bool CMariadb::exec_query(string &qry,vector< vector<string> > &resultado,int cols)
//{
//
//	try{
//
//		resultado.clear();
//		vector<string> linha;
//		int row=0;
//		res=stmt->executeQuery(qry);
//
//		while(res->next())
//		{
//			//resultado.at(row).clear();//limpar o vector de strings da linha row
//			linha.clear();
//			//da coluna 0 a cols-1
//			for(int i=1;i<=cols;++i)
//			{
//				//cout<<"dentro do mysql: "<<res->getString(i);
//				linha.push_back(res->getString(i));//sacar string da coluna i e empurrar para o vector de row
//			}
//			resultado.push_back(linha);//empurrar vector correspondente a linha.
//
//			++row;
//		}
//		if(resultado.empty())
//			return false;
//
//	} catch (sql::SQLException &e)
//	{
//		cout << "# ERR: SQLException in " << __FILE__;
//		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
//		/* Use what() (derived from std::runtime_error) to fetch the error message */
//		cout << "# ERR: " << e.what();
//		cout << " (MySQL error code: " << e.getErrorCode();
//		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
//		cout<<endl<<qry<<endl;
//		delete res;
//		return false;
//	}
//	delete res;
//	return true;
//}
//
//const bool CMariadb::exec_query_silent(string &qry)
//{
//
//	try{
//		stmt->execute(qry);
//	} catch (sql::SQLException &e)
//	{
//		cout << "# ERR: SQLException in " << __FILE__;
//		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
//		/* Use what() (derived from std::runtime_error) to fetch the error message */
//		cout << "# ERR: " << e.what();
//		cout << " (MySQL error code: " << e.getErrorCode();
//		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
//
//		cout<<endl<<qry<<endl;
//		return false;
//	}
//	//delete stmt;
//	return true;
//}

//void CMariadb::FreeMem()
//{
//	/* TODO
//	 * implementar meio de limpeza de utilização do mysql
//	 * que tem vindo a ser um comedor de memória!
//	 *
//	 */
//	string qry="connect";
//	try{
//		stmt->close();
//		con->close();
//		driver->threadEnd();
//		delete stmt;
//		delete con;
////		delete res;
//		//delete driver;
//
//		driver = get_driver_instance();
//		con=driver->connect(url, user, pass);
//		con->setSchema(db);
//		stmt=con->createStatement();
//	} catch (sql::SQLException &e)
//	{
//		cout << "# ERR: SQLException in " << __FILE__;
//		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
//		/* Use what() (derived from std::runtime_error) to fetch the error message */
//		cout << "# ERR: " << e.what();
//		cout << " (MySQL error code: " << e.getErrorCode();
//		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
//	}
//
//}

/*
 * devolver um vector de string correspondente a coluna de resultados
 * de uma query
 */
vector<string> CMysql::ExecGetColumn(string qry) {
	vector<string> Coluna;
	//MYSQL_FIELD *campo;
	MYSQL_ROW row;
	MYSQL_RES * result;//=mysql_use_result(conn);
	int numero_campos;
	string resultado;
//	vector<string> Linha;


	//executar a query.
	if(mysql_query(conn,qry.c_str())){
		FinishError();
		return Coluna;
	}
	//get resultset
	result=mysql_use_result(conn);
	if(result==NULL){
		FinishError();
		return Coluna;
	}

	//quantos campos?
	numero_campos=mysql_num_fields(result);

	while ((row = mysql_fetch_row(result)))
	{
		//Linha.clear();
		for(int i = 0; i < numero_campos; i++)
		{
			//printf("%s ", row[i] ? row[i] : "NULL");
			resultado=row[i] ? row[i]:"NULL";
			Coluna.push_back(resultado);
		}
		//printf("\n");
		//Resultado.push_back(Linha);
	}

	mysql_free_result(result);

	return Coluna;

}

int CMysql::CountTable(string allocator) {
	string sCount = ExecGetSingle("select count(*) from " + allocator);
	return StringToInt(sCount);
}
int CMysql::StringToInt(string s)
{
	/*
	 * converter numero em string para int
	 */
	int i;
	istringstream(s) >> i; //converter string para int
	return i;
}

void CMysql::Clear(string table) {
	Exec("delete from "+table);
}
