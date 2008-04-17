#include <iostream>

#include "./includes/AnalisadorLexico.h"
#include "./includes/ErrosExecucao.h"
#include "./includes/LogErros.h"



int
main(int argc, char* argv[])
{
	AnalisadorLexico*
	analisador;

	try
	{
		if ( argv[1] == NULL ) throw ( new ErrosExecucao("Voce Precisa Definir qual arquivo sera compilado") );

		else if ( argv[2] )
		{
			analisador = new AnalisadorLexico( argv[1], argv[2] );
		}
		else
		{
			analisador = new AnalisadorLexico( argv[1] );
		}
	}
	catch ( ErrosExecucao* erro )
	{
		std::cout << erro->getErro( );
	}

	LogErros::getInstancia( ).getLog( );
	return (EXIT_SUCCESS);
}
