/***********************************************
 * main.cpp                                    *
 *                                             *
 * @author: Evandro Couto Mantese              *
 * @author: Marcus Vinicius Ventura Bortolotti *
 * @author: Rafael de Paula Herrera            *
 *                                             *
 ***********************************************/


/*
 * Includes do Sistema
 */
#include <iostream>

/*
 * Includes do Usuario
 */
#include "./includes/AnalisadorLexico.h"
#include "./includes/ErrosExecucao.h"
#include "./includes/LogErros.h"



int
main(int argc, char* argv[])
{
	/*
	 * Instancia o Analisador Lexico
	 */
	AnalisadorLexico*
	analisador;

	try
	{
		/*
		 * Verifica se foi especificado o nome do arquivo-fonte
		 */
		if ( argv[1] == NULL ) throw ( new ErrosExecucao("Voce Precisa Definir qual arquivo sera compilado") );
		/*
		 * Verifica se foi especificado o arquivo no qual o log do Analisador Lexico será salvo
		 */
		else if ( argv[2] )
		{
			analisador = new AnalisadorLexico( argv[1], argv[2] );
		}
		/*
		 * Se nao foi especificado um nome para o log, o resultado será exibido na saida padrao do sistema
		 */
		else
		{
			analisador = new AnalisadorLexico( argv[1] );
		}
	}
	/*
	 * Se ocorrer algum problema durante a execucao do Analisador Lexico, o erro sera exibido
	 */
	catch ( ErrosExecucao* erro )
	{
		std::cout << erro->getErro( );
	}

	/*
	 * Exibe o log de Erros do Analisador
	 */
	LogErros::getInstancia( ).getLog( );

	return (EXIT_SUCCESS);
}
