#include <fstream>
#include <iostream>
#include <string>

#include "./../includes/AnalisadorLexico.h"



/**********************
 *  Métodos Publicos  *
 **********************/

AnalisadorLexico::AnalisadorLexico( const std::string caminho )
{
	try
	{
		this->carregaCodigo( caminho );
	}
	catch ( std::string erro )
	{
		std::cout << erro << std::endl;
		exit (1);
	}
	
	this->automato = new AutomatoFD( this->codigoFonte );

	this->saidaAnalisadorLexico = this->automato->getSaidaAutomato( );
}

AnalisadorLexico::~AnalisadorLexico( )
{
}

/**********************
 *  Métodos Privados  *
 **********************/

void
AnalisadorLexico::carregaCodigo( const std::string caminho )
{
	std::ifstream
	arquivoCodigo;

	std::string
	linhaCodigo;

	int
	(*pf) (int) = tolower;

	char
	bufferCaractere;

	arquivoCodigo.open( caminho.c_str(), std::ifstream::in );
	if ( arquivoCodigo.bad() ) throw ( "Fuma um cigarro! O arquivoCodigo nao pode ser aberto!! Sucesso;;" );

	arquivoCodigo.seekg ( 0, std::ios::beg );
	
	linhaCodigo.clear( );

	while ( !arquivoCodigo.eof() )
	{
		arquivoCodigo.get( bufferCaractere );

		if ( (bufferCaractere != '\n') && (!arquivoCodigo.eof()) )
		{
			linhaCodigo.push_back( bufferCaractere );
		}
		else
		{
			std::transform(linhaCodigo.begin( ), linhaCodigo.end( ), linhaCodigo.begin( ), pf);

			this->codigoFonte.push_back( linhaCodigo );
			linhaCodigo.clear( );
		}
	}
	arquivoCodigo.close( );
}
