#ifndef AUTOMATOFD_H_
#define AUTOMATOFD_H_

#include <iostream>
#include <list>
#include <string>

#include "./../includes/StructToken.h"



class AutomatoFD
{
	public:
		AutomatoFD( std::list<std::string> );

		const std::map<int, StructToken>
		getSaidaAutomato( );

	private:
		virtual
		~AutomatoFD( );

	protected:
		std::list<std::string>
		codigoPascal;

		std::string
		token;

		unsigned int
		numeroLinha;

		unsigned int
		numeroToken;

		std::map<int,StructToken>
		tokensClassificados;

		int
		validaCaractereREGEX( char*, const char*, std::string );

		void
		adicionaCaractereToken(	);

		void
		adicionaTokenArrayAssociativo( );

		void
		adicionaTokenArrayAssociativo( std::string );

		void
		estadoS( );

		void
		estadoA( );

		void
		estadoB( );

		void
		estadoC( );

		void
		estadoD( );

		void
		estadoE( );

		void
		estadoF( );

		void
		estadoG( );

		void
		estadoH( );

		void
		estadoI( );

		void
		estadoJ( );

		void
		estadoK( );

		void
		estadoL( );
		
		void
		estadoM( );
		
		void
		estadoN( );

		void
		estadoO( );
		
		void
		estadoP( );
};

#endif /*AUTOMATOFD_H_*/
