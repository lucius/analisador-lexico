#include <iostream>

#include "./includes/AnalisadorLexico.h"
#include "./includes/LogErros.h"



int
main(int argc, char* argv[])
{
	AnalisadorLexico*
	analisador;

	if ( argv[2] != NULL )
	{
		analisador = new AnalisadorLexico( argv[1], argv[2] );
	}
	else
	{
		analisador = new AnalisadorLexico( argv[1] );
	}

	LogErros::getInstancia( ).getLog( );
	return (EXIT_SUCCESS);
}
