#include <iostream>
#include <string>
#include <sstream>
#include <queue>

#include "./../includes/LogErros.h"



std::queue<std::string>
LogErros::erros;
		
		

/**********************
 *  Métodos Publicos  *
 **********************/

LogErros&
LogErros::getInstancia( )
{
	static LogErros
	log;

	return log;
}

void
LogErros::insereErro( const unsigned int numeroLinha, const std::string erro )
{
	std::stringstream
	linhaErro;

	linhaErro << "[Linha " << numeroLinha << "] - " << erro;

	LogErros::erros.push( linhaErro.str() );
}

void
LogErros::salvaLog( const std::string caminho )
{
	while ( !LogErros::erros.empty() )
	{
		std::cout << LogErros::erros.front() << std::endl;
		LogErros::erros.pop( );
	}
}



/**********************
 * Métodos Protegidos *
 **********************/

LogErros::LogErros( )
{
}

LogErros::~LogErros( )
{
}
/**********************
 *  Métodos Privados  *
 **********************/
