#include <ctime>
#include <fstream>
#include <iostream>
#include <regex.h>
#include <string>

#include "./../includes/AnalisadorLexico.h"
#include "./../includes/ErrosExecucao.h"



/**********************
 *  Métodos Publicos  *
 **********************/

AnalisadorLexico::AnalisadorLexico( const std::string caminho )
{
	try
	{
		this->carregaCodigo( caminho );
	}
	catch ( ErrosExecucao* erro )
	{
		std::cout << erro->getErro( ) << std::endl;
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

	regex_t
	expressaoRegular;
	
	/* VERIFICA O FORMATO DO ARQUIVO */
	if ( regcomp(&expressaoRegular, ".pas$", REG_EXTENDED|REG_ICASE|REG_NOSUB) )	throw ( new ErrosExecucao("A expressao regular nao pode ser alocada") );
	
	if ( regexec(&expressaoRegular, caminho.c_str(), 0, (regmatch_t *)NULL, 0) ) throw ( new ErrosExecucao("O formato do arquivo nao e valido...") );

	regfree( &expressaoRegular );
	
	/* ABRE O CÓDIGO */
	arquivoCodigo.open( caminho.c_str(), std::ifstream::in );
	if ( arquivoCodigo.bad() ) throw ( new ErrosExecucao("O arquivo de codigo nao pode ser aberto!! Sucesso;;") );

	arquivoCodigo.seekg ( 0, std::ios::beg );
	
	linhaCodigo.clear( );

	while ( !arquivoCodigo.eof() )
	{
		arquivoCodigo.get( bufferCaractere );

		if ( (bufferCaractere != '\n') && (!arquivoCodigo.eof()) )
		{
			if ( bufferCaractere != '\t' )
			{
				linhaCodigo.push_back( bufferCaractere );
			}
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
