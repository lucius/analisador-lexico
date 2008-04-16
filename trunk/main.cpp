#include <iostream>

#include "./includes/AnalisadorLexico.h"
#include "./includes/LogErros.h"



int
main(int argc, char* argv[])
{
	AnalisadorLexico
	analisador ( "./data/codigo.pas" );

	LogErros::getInstancia( ).salvaLog( "bogaFlame" );
	return (EXIT_SUCCESS);
}
