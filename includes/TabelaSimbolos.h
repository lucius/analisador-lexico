#ifndef TABELADESIMBOLOS_H_
#define TABELADESIMBOLOS_H_

#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <vector>

#include "StructSimbolo.h"



class TabelaSimbolos
{
	public:
		static TabelaSimbolos*
		getInstancia( );

		const std::string 
		procuraSimbolo( std::string );

	protected:
		TabelaSimbolos( );

		virtual
		~TabelaSimbolos( );

	private:
		static TabelaSimbolos*
		instanciaTabelaSimbolos;

		std::map<std::string, std::string>
		simbolos;

		const std::vector<std::string>
		carregaArquivoConfiguracao( );

		void
		criaTabela( );
};

#endif /*TABELADESIMBOLOS_H_*/
