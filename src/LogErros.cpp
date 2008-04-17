#include <iostream>
#include <sstream>
#include <string>
#include <queue>

#include "./../includes/LogErros.h"



std::queue<std::string>
LogErros::erros;



/**********************
 *  Metodos Publicos  *
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
LogErros::getLog( )
{
	if ( !LogErros::erros.empty() )
	{
		while ( !LogErros::erros.empty() )
		{
			std::cout << LogErros::erros.front() << std::endl;
			LogErros::erros.pop( );
		}
	}
	else
	{
		std::cout << "Nao foram encontrados erros..." << std::endl << std::endl;
	}
}



/**********************
 * Metodos Protegidos *
 **********************/

LogErros::LogErros( )
{
}

LogErros::~LogErros( )
{
}



/**********************
 *  Metodos Privados  *
 **********************/
