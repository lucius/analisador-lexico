#include <iostream>

#include "./includes/AnalisadorLexico.h"
#include "./includes/LogErros.h"



int
main(int argc, char* argv[])
{
	AnalisadorLexico
	analisador ( argv[1], argv[2] );

	LogErros::getInstancia( ).getLog( );
	return (EXIT_SUCCESS);
}
