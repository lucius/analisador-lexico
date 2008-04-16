#include <iostream>
#include <string>
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
LogErros::insereErro( const int numeroLinha, const std::string erro )
{
	std::string
	linhaErro;

	linhaErro = "[ " + linhaErro + " ] - " + erro;	

	LogErros::erros.push( linhaErro );
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
