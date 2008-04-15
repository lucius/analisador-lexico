#include <fstream>
#include <iostream>
#include <map>
#include <list>
#include <regex.h>
#include <string>

#include "./../includes/AutomatoFD.h"
#include "./../includes/ErrosExecucao.h"
#include "./../includes/LogErros.h"
#include "./../includes/StructToken.h"
#include "./../includes/TabelaSimbolos.h"



/**********************
 *  Métodos Publicos  *
 **********************/

AutomatoFD::AutomatoFD( std::list<std::string> codigoFonte )
{
	this->codigoPascal = codigoFonte;

	this->token.clear( );
	this->estadoS( );
}



/**********************
 * Métodos Protegidos *
 **********************/

AutomatoFD::~AutomatoFD( )
{
}



/**********************
 *  Métodos Privados  *
 **********************/

const std::map<int, StructToken>
AutomatoFD::getSaidaAutomato( )
{
	return ( this->tokensClassificados );
}


int
AutomatoFD::validaCaractereREGEX( char* stringExpressaoRegular, const char* linhaCodigo, std::string transicao )
{
	std::string
	erroExpressaoRegular = "A variável de expressao regular nao pode ser alocada: Transicao " + transicao;

	regex_t
	expressaoRegular;

	int
	status;

	if ( regcomp(&expressaoRegular, stringExpressaoRegular, REG_EXTENDED|REG_ICASE|REG_NOSUB) )	throw ( new ErrosExecucao(erroExpressaoRegular) );
	status = regexec(&expressaoRegular, linhaCodigo, 0, (regmatch_t *)NULL, 0);
	regfree( &expressaoRegular );
	
	return ( !status );
}

void
AutomatoFD::adicionaCaractereToken( )
{
	if ( (*this->codigoPascal.begin()).empty() )
	{
		this->codigoPascal.pop_front( );
		this->numeroLinha++;
		this->adicionaTokenArrayAssociativo( );
	}
	else
	{
		this->token.push_back( (*this->codigoPascal.begin()).at(0) );
		*this->codigoPascal.begin( ) = (*this->codigoPascal.begin()).substr(1);
	
		if ( (*this->codigoPascal.begin()).empty() )
		{
			this->codigoPascal.pop_front( );
			this->numeroLinha++;
			this->adicionaTokenArrayAssociativo( );
		}
	}
}

void
AutomatoFD::adicionaTokenArrayAssociativo( )
{
	StructToken
	bufferToken;
	
	bufferToken.token = this->token;

	bufferToken.classificacao = TabelaSimbolos::getInstancia()->procuraSimbolo( this->token );

	bufferToken.linha = this->numeroLinha;
	bufferToken.coluna = 0;
	
	std::cout << bufferToken.token << " - " << bufferToken.classificacao << std::endl;

	tokensClassificados.insert ( std::pair<const int, const StructToken> (this->numeroToken, bufferToken) );

	++this->numeroToken;

	this->token.clear();
}



/*********************************************
 *											 *
 *  				Estados  				 *
 *					  do					 *
 *					Automato 				 *
 * 											 *
 *********************************************/



void
AutomatoFD::estadoS()
{
	while( !this->codigoPascal.empty() )
	{
		try
		{
			/* Primeira Transicao */
			if ( this->validaCaractereREGEX("^[A-Z]", (*this->codigoPascal.begin()).c_str(), "SA") )
			{
				this->estadoA( );
			}
			else
			{
				/* Segunda Transicao */
				if ( this->validaCaractereREGEX("^[+|*|~|&|||=|;|.|,|-]", (*this->codigoPascal.begin()).c_str(), "SB") )
				{
					this->estadoB( );
				}
				else
				{
					/* Terceira Transicao */
					if ( this->validaCaractereREGEX("^<", (*this->codigoPascal.begin()).c_str(), "SC") )
					{
						this->estadoC( );
					}
					
					else
					{
						/* Quarta Transicao */
						if ( this->validaCaractereREGEX("^>", (*this->codigoPascal.begin()).c_str(), "SD") )
						{
							this->estadoD( );
						}
						else
						{
							/* Quinta Transicao */
							if ( this->validaCaractereREGEX("^[{]", (*this->codigoPascal.begin()).c_str(), "SE") )
							{
								this->estadoE( );
							}
							else
							{
								/* Sexta Transicao */
								if ( this->validaCaractereREGEX("^\\(", (*this->codigoPascal.begin()).c_str(), "SF") )
								{
									this->estadoF( );
								}
								else
								{
									/* Setima Transicao */
									if ( this->validaCaractereREGEX("^\\)", (*this->codigoPascal.begin()).c_str(), "SG") )
									{
										this->estadoG( );
									}
									else
									{
										/* Oitava Transicao */
										if ( this->validaCaractereREGEX("^[0-9]", (*this->codigoPascal.begin()).c_str(), "SH") )
										{
											this->estadoH( );
										}
	
										else
										{
											/* Nona Transicao */
											if ( this->validaCaractereREGEX("^:", (*this->codigoPascal.begin()).c_str(), "SI") )
											{
												this->estadoI( );
											}
											else
											{
												if ( this->validaCaractereREGEX("^[ |	]", (*this->codigoPascal.begin()).c_str(), "ESPACO_BRANCO") )
												{
													*this->codigoPascal.begin( ) = (*this->codigoPascal.begin()).substr(1);
												}
												else
												{

												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		catch ( ErrosExecucao* erro )
		{
			std::cout << erro->getErro( ) << std::endl;
		}
	}
}

void
AutomatoFD::estadoA( )
{
	this->adicionaCaractereToken( );
}

void
AutomatoFD::estadoB( )
{
	this->adicionaCaractereToken( );
}

void
AutomatoFD::estadoC( )
{
	this->adicionaCaractereToken( );
}

void
AutomatoFD::estadoD( )
{
	this->adicionaCaractereToken( );
}

void
AutomatoFD::estadoE( )
{
	this->adicionaCaractereToken( );
}

void
AutomatoFD::estadoF( )
{
	this->adicionaCaractereToken( );
}

void
AutomatoFD::estadoG( )
{
	this->adicionaCaractereToken( );
}

void
AutomatoFD::estadoH( )
{
	this->adicionaCaractereToken( );
}

void
AutomatoFD::estadoI( )
{
	this->adicionaCaractereToken( );
}

void
AutomatoFD::estadoJ( )
{
	this->adicionaCaractereToken( );
}

void
AutomatoFD::estadoK( )
{
	this->adicionaCaractereToken( );
}

void
AutomatoFD::estadoL( )
{
	this->adicionaCaractereToken( );
}

void
AutomatoFD::estadoM( )
{
	this->adicionaCaractereToken( );
}

void
AutomatoFD::estadoN( )
{
	this->adicionaCaractereToken( );
}

void
AutomatoFD::estadoO( )
{
	this->adicionaCaractereToken( );
}

void
AutomatoFD::estadoP( )
{
	this->adicionaCaractereToken( );
}
