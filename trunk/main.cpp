#include <iostream>

#include "./includes/AnalisadorLexico.h"
#include "./includes/LogErros.h"



int
main(int argc, char* argv[])
{
	AnalisadorLexico
	analisador ( "../AutomatoFD/data/codigo.pas" );

	std::cout << std::endl << std::endl; 

	LogErros::getInstancia( ).salvaLog( "bogaFlame" );
	return (EXIT_SUCCESS);
}
