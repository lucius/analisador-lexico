#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <regex.h>
#include <sstream>
#include <string>

#include "./../includes/AnalisadorLexico.h"
#include "./../includes/ErrosExecucao.h"
#include "./../includes/StructToken.h"



/**********************
 *  Métodos Publicos  *
 **********************/

AnalisadorLexico::AnalisadorLexico( const std::string caminhoCodigo, const std::string caminhoLog )
{
	try
	{
		this->carregaCodigo( caminhoCodigo );

		this->automato = new AutomatoFD( this->codigoFonte );
		this->saidaAnalisadorLexico = this->automato->getSaidaAutomato( );

		this->salvaLog( caminhoLog );
	}
	catch ( ErrosExecucao* erro )
	{
		std::cout << erro->getErro( ) << std::endl;
		exit (1);
	}
}

AnalisadorLexico::AnalisadorLexico( const std::string caminhoCodigo )
{
	try
	{
		this->carregaCodigo( caminhoCodigo );
	}
	catch ( ErrosExecucao* erro )
	{
		std::cout << erro->getErro( ) << std::endl;
		exit (1);
	}
	
	this->automato = new AutomatoFD( this->codigoFonte );
	this->saidaAnalisadorLexico = this->automato->getSaidaAutomato( );

	this->ImprimeLog( );
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

void
AnalisadorLexico::salvaLog( const std::string caminhoLog )
{
	std::map<int, StructToken>::iterator
	iteradorLog;

	std::stringstream
	buffer[ this->saidaAnalisadorLexico.size() ];
	
	std::string
	bufferString;

	unsigned int
	contadorBuffer = 0;

	std::ofstream
	arquivoLog;
	
	arquivoLog.open( caminhoLog.c_str(), std::ifstream::out );
	if ( arquivoLog.bad() ) throw ( new ErrosExecucao("O arquivo de log nao pode ser salvo!! Sucesso;;") );

	for( iteradorLog = this->saidaAnalisadorLexico.begin(); iteradorLog != this->saidaAnalisadorLexico.end(); ++iteradorLog )
	{
		buffer[ contadorBuffer ] << '[' << iteradorLog->first << "] [" << iteradorLog->second.linha << "] [" << iteradorLog->second.token << "] [" << iteradorLog->second.classificacao << ']';

		bufferString = buffer[contadorBuffer].str();
		bufferString.push_back( '\n' );

		arquivoLog.write( bufferString.c_str(), bufferString.size() );
		
		++contadorBuffer;
	}
	arquivoLog.close( );
}

void
AnalisadorLexico::ImprimeLog( )
{
	std::map<int, StructToken>::iterator
	iteradorLog;

	std::stringstream
	buffer[ this->saidaAnalisadorLexico.size() ];

	unsigned int
	contadorBuffer = 0;

	for( iteradorLog = this->saidaAnalisadorLexico.begin(); iteradorLog != this->saidaAnalisadorLexico.end(); ++iteradorLog )
	{
		buffer[ contadorBuffer ] << '[' << iteradorLog->first << "] [" << iteradorLog->second.linha << "] [" << iteradorLog->second.token << "] [" << iteradorLog->second.classificacao << ']'; 
		std::cout << buffer[ contadorBuffer ].str( ) << std::endl;
		
		++contadorBuffer;
	}
}
