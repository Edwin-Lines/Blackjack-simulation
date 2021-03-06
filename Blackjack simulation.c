/* 
Programa: Juego de Blackjack
Objetivo: Simular un juego de Blackjack
Programador: Edwin Andrade
Programador 2: Esteban Pacheco
Fecha: 29/05/2021 
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

//54 cartas en total - 2 jokers = 52 cartas a usar (13 de cada categoría)	
#define MAX 13
#define MIN 1

//Símbolos de las esquinas de las cartas
char categoriaAzar( int num);

//Letras en caso de salir una carta de J, Q, R o As
char valoresAltos(int num);

//Igualar el valor de las cartas de J,K y Q a 10
int puntajesAltos(int num);

//Cambiar la salida de la carta en caso de ser J, Q, R o As
void tipoDeValor(int num);

//Cambiar la salida de la carta en caso de ser J, Q, R o As para la salida del crupier
void tipoDeValor_1(int num);

//Asignación del valor as
int ValorDeAs(int EntradaCarta_1, int EntradaCarta_2,int puntaje);

//Generador de cartas únicas, el sistema genera cartas con la condición de que sean diferentes
void generadorDeCartas(int valoresAleatorios[], int categoriasAleatorias[]);

int gotoYX (int columna, int linea);
	
		
int main(int argc, char *argv[]) {
	
	//Simbología para las cartas
	char corazon = '';
	char diamante = '';
	char pica = '';
	char trebol = '';
	
	int i,j;
	
	//Variables de fichas
	int fichas = 500;
	char resp[2];
	int apuesta;
	int opcion;
	int puntosJugador;
	int puntosMaquina;
	int salida = 0;
	int mesaApuesta;
	
	//Variable de cartas:
	
	
	//Jugador
	int jugador_puntajeCarta1, jugador_puntajeCarta2;
	char jugador_categoriaCarta1, jugador_categoriaCarta2;
	int puntajeCartaExtra[6];
	char categoriaCartaExtra[6];
	
	//Maquina (crupier)
	int maquina_puntajeCarta1, maquina_puntajeCarta2;
	char maquina_categoriaCarta1, maquina_categoriaCarta2;
	
	
	//Almacenador de las cartas y categorías ya salidas.
	int puntaje_cartas_salidas[15];
	int puntaje_categoria_salidas[15];
	
	//Valor para determinar la posición
	int pscvl,pscvc;
	
	//Instrucciones
	printf("======== Juego de simulación de Blackjack ======== \n\n");
	
	printf("El objetivo del Blackjack es obtener una suma total cerca del 21 o igual a 21 sin que supere esta cantidad\n ");
	printf("Hay un total de 52 cartas, 13 tipos divididos en 4 categorías: \n Diamantes   %c \n Tréboles    %c \n Picas       %c \n Corazones   %c \n\n", diamante, trebol ,pica, corazon);
	printf("El valor de las cartas de cualquier categoría esta dada de la siguiente forma: \n");
	
	//Valor de las cartas
	printf( "Carta: As ---> Valor: 1 u 11 puntos de acuerdo al total hasta el momento \n **Si se tiene una cantidad menor o igual a 10, As tendrá un puntaje de 11, de lo contrario, tendra un puntaje de 1** \n");
	for (i=MIN+1;i<=MAX-4;i++){
		printf( "Carta: %i -----------> Valor: %i puntos \n", i, i);
	}
	printf( "Carta: %i ----------> Valor: %i puntos \n", i, i);
	printf( "Carta: J (Jota) ----> Valor: 10 puntos \n");
	printf( "Carta: Q (Reina) ---> Valor: 10 puntos \n");
	printf( "Carta: K (Rey) -----> Valor: 10 puntos \n\n");

	//Reglas
	printf("---- REGLAS ----\n ");
	printf("1. Al iniciar la partida, el jugador podrá ver sus cartas y solo una carta que tenga el crupier, siendo que la segunda permanezca oculta hasta que el jugador termine de pedir cartas\n");
	printf("2. El jugador puede pedir la cantidad de cartas que desee una vez haya visto las suyas y las del crupier mientras no se pase de 21\n");
	printf("3. Al inicio del juego, el jugador contará con un total de 500 fichas \n");
	printf("4. Para poder ingresar a la partida, el jugador deberá poner un mínimo de 50 fichas para jugar \n");
	printf("5. Una vez recibida las 2 primeras cartas, el jugador puede decidir si agarrar más o quedarse con las 2 que tiene \n");
	printf("6. El jugador puede incrementar la apuesta antes de iniciar una partida para obtener más fichas si gana \n");
	printf("7. El jugador puede decidir doblar la apuesta al inicio de su turno y automaticamente recibirá una carta más \n");
	printf("8. En caso de que el jugador se quede sin fichas mínimas para entrar a la partida, el juego terminará, por lo que puede decidir retirarse depués de ganar \n\n");
	
	printf("---- FICHAS A GANAR ---- \n");
	printf("En caso de ganar con un Blackjack (21 exactos), se obtendrán el triple de fichas apostadas \n");
	printf("En caso de ganar sin haber doblado la apuesta, se obtendrán las fichas apostadas (las propias y las del crupier)\n\n");
	
	//Mientras el jugador tenga el número de fichas necesarias para ingresar a la apuesta.
	while (fichas > 49){
		
		printf("Total de fichas: %i \n", fichas);
		
		do{
			salida = 0;
			printf("¿Desea ingresar a una nueva partida? (Si/No)  ");
			gets(resp);
			system("cls");
		} while ( (strcmp(resp,"No")) && (strcmp(resp,"Si")) && (strcmp(resp,"no")) && (strcmp(resp,"si")) );
		
		//En caso de aceptar entrar a la partida
		if(strcmp(resp, "Si") == 0 || strcmp(resp,"si")== 0){
			do{
				printf("Monto a apostar (Mínimo de 50): ");
				fflush (stdin);
				scanf("%i", &apuesta);
			} while (apuesta<50 || apuesta>fichas);
			
			mesaApuesta = apuesta*2;
			
			//Reiniciar valores de cartas y cartas extra
			j=0;
			i=0;
			
			//Generador de cartas de jugador
			generadorDeCartas(puntaje_cartas_salidas,puntaje_categoria_salidas);
			
			jugador_puntajeCarta1 = puntaje_cartas_salidas[j];
			jugador_categoriaCarta1 = categoriaAzar(puntaje_categoria_salidas[j]);
		
			j++;//Cambio de posiciones
		
			jugador_puntajeCarta2 = puntaje_cartas_salidas[j];
			jugador_categoriaCarta2 = categoriaAzar(puntaje_categoria_salidas[j]);
			
			j++;
		
			
			//Generar cartas de máquina
			maquina_puntajeCarta1 = puntaje_cartas_salidas[j];
			maquina_categoriaCarta1 = categoriaAzar(puntaje_categoria_salidas[j]);
			j++;
			
			maquina_puntajeCarta2 = puntaje_cartas_salidas[j];
			maquina_categoriaCarta2 = categoriaAzar(puntaje_cartas_salidas[j]);
			j++;
			pscvl= 4;
			pscvc= 8;
			
			//Imprimir cartas para el usuario y las de la maquina (crupier)
			gotoYX(pscvl+1,5); printf("Cartas del jugador:\n");
			gotoYX(pscvl+2,pscvc); printf("|=================|   |=================|\n");
			gotoYX(pscvl+3,pscvc); printf("|	      | %c |   |   	    | %c |\n", jugador_categoriaCarta1, jugador_categoriaCarta2);
			gotoYX(pscvl+4,pscvc); printf("|  	      ====|   |             ====|\n");
			gotoYX(pscvl+5,pscvc); printf("|		  |   |			|\n");
			gotoYX(pscvl+6,pscvc); printf("|		  |   |			|\n");
			gotoYX(pscvl+7,pscvc); tipoDeValor(jugador_puntajeCarta1); tipoDeValor(jugador_puntajeCarta2);  			
			gotoYX(pscvl+8,pscvc); printf("|		  |   |			|\n");
			gotoYX(pscvl+9,pscvc); printf("|		  |   |			|\n");
			gotoYX(pscvl+10,pscvc);printf("|		  |   |			|\n");
			gotoYX(pscvl+11,pscvc);printf("|====	          |   |====		|\n");
			gotoYX(pscvl+12,pscvc);printf("| %c |		  |   | %c |		|\n",jugador_categoriaCarta1, jugador_categoriaCarta2);
			gotoYX(pscvl+13,pscvc);printf("|=================|   |=================|\n\n");
		
			gotoYX(pscvl+17,5);printf("Cartas del crupier:\n");
			gotoYX(pscvl+18,pscvc);printf("|=================|   |=================|\n");
			gotoYX(pscvl+19,pscvc);printf("|	      | %c |   |   	    | X |\n", maquina_categoriaCarta1);
			gotoYX(pscvl+20,pscvc);printf("|  	      ====|   |             ====|\n");
			gotoYX(pscvl+21,pscvc);printf("|		  |   |			|\n");
			gotoYX(pscvl+22,pscvc);printf("|		  |   |			|\n");
			gotoYX(pscvl+23,pscvc);tipoDeValor(maquina_puntajeCarta1);  printf("|        X        |\n");
			gotoYX(pscvl+24,pscvc);printf("|		  |   |			|\n");
			gotoYX(pscvl+25,pscvc);printf("|		  |   |			|\n");
			gotoYX(pscvl+26,pscvc);printf("|		  |   |			|\n");
			gotoYX(pscvl+27,pscvc);printf("|====	          |   |====		|\n");
			gotoYX(pscvl+28,pscvc);printf("| %c |		  |   | X |		|\n",maquina_categoriaCarta1);
			gotoYX(pscvl+29,pscvc);printf("|=================|   |=================|\n\n");
		
		i=1;
		
		//Otorgar valor de 10 para J, Q, R y As en caso de salir
		
		if (jugador_puntajeCarta1> 10){
			jugador_puntajeCarta1 = puntajesAltos(jugador_puntajeCarta1);
		}
		
		if (jugador_puntajeCarta2> 10){
			jugador_puntajeCarta2 = puntajesAltos(jugador_puntajeCarta2);
		}
		
		puntosJugador = jugador_puntajeCarta1 + jugador_puntajeCarta2;
		
		
		//Asignación del valor as
		
		if((jugador_puntajeCarta1== 1) || (jugador_puntajeCarta2== 1)){
			if(puntosJugador<11){
				puntosJugador+= 10;
			}
		}
		//Otorgar valor de 10 para J, Q, R y As en caso de salir
		if (maquina_puntajeCarta1>10){
			maquina_puntajeCarta1 = puntajesAltos(maquina_puntajeCarta1);
		}
		
		if (maquina_puntajeCarta2>10){
			maquina_puntajeCarta2 = puntajesAltos(maquina_puntajeCarta2);
		}
				
		puntosMaquina = maquina_puntajeCarta1 + maquina_puntajeCarta2;
		
		
		//Evaluando el caso As para el primer turno
		
		if((maquina_puntajeCarta1 == 1) || (maquina_puntajeCarta2 == 1)){
			if(puntosMaquina <11){
				puntosJugador+= 10;
			}
		}
		
		//Evaluar si los puntos no sobrepasan los máximos para seguir
		while (puntosJugador<=21 && salida == 0){
			printf("Puntos del jugador: %i \n", puntosJugador);
			printf("Puntos de la crupier: "); tipoDeValor_1(maquina_puntajeCarta1); printf("+ X \n") ;
			printf("Apuesta en la mesa: %i \n", mesaApuesta);
			
			printf("Opciones: \n 1. Mantenerse con la mano obtenida. \n 2. Pedir otra carta. \n 3. Doblar apuesta y pedir otra carta\n");
			fflush( stdin );
			scanf("%i", &opcion);
			getchar();
			
			switch(opcion){
			case 1:
				salida++;
				break;
			
			case 2:
		
				//En caso de pedir una carta extra
				puntajeCartaExtra[i] = puntaje_cartas_salidas[j];
				categoriaCartaExtra[i] = categoriaAzar(puntaje_categoria_salidas[j]);
				j++;
				if (puntajeCartaExtra[i]>10){
					puntajeCartaExtra[i] = puntajesAltos(puntajeCartaExtra[i]);
				}
				
				puntosJugador += puntajeCartaExtra[i];
				
				if(puntajeCartaExtra[i] == 1){
					if(puntosJugador< 11){
						puntosJugador += 10;
					}
				} 
				
				system("cls");
				printf("Carta:  \n\n");
				printf("|=================|\n");
				printf("|	      | %c |\n",categoriaCartaExtra[i]);
				printf("|  	      ====|\n");
				printf("|		  |\n");
				printf("|		  |\n");
				tipoDeValor(puntajeCartaExtra[i]);   
				printf("\n|		  |\n");
				printf("|		  |\n");
				printf("|		  |\n");
				printf("|====	          |\n");
				printf("| %c |		  |\n",categoriaCartaExtra[i]);
				printf("|=================|\n\n");
				
				i++;
				
				break;
				
			case 3:
				
				//En caso de pedir una sola carta y doblar la apuesta
				apuesta *= 2;
				mesaApuesta *= 2;
				puntajeCartaExtra[i] = puntaje_cartas_salidas[j];
				categoriaCartaExtra[i] = categoriaAzar(puntaje_categoria_salidas[j]);
				j++;
				
				if (puntajeCartaExtra[i]>10){
					puntajeCartaExtra[i] = puntajesAltos(puntajeCartaExtra[i]);
				}
				
				puntosJugador += puntajeCartaExtra[i];
				
				if(puntajeCartaExtra[i] == 1){
					if(puntosJugador< 11){
						puntosJugador += 10;
					}
				}
				
				printf("Carta: \n\n");
				printf("|=================|\n");
				printf("|	      | %c |\n",categoriaCartaExtra[i]);
				printf("|  	      ====|\n");
				printf("|		  |\n");
				printf("|		  |\n");
				tipoDeValor(puntajeCartaExtra[i]);   
				printf("\n|		  |\n");
				printf("|		  |\n");
				printf("|		  |\n");
				printf("|====	          |\n");
				printf("| %c |		  |\n",categoriaCartaExtra[i]);
				printf("|=================|\n\n");
				
				i++;
				salida++;
				
				break;
			}
		}
		
		//Se muestra carta oculta del crupier o máquina
		printf("Carta oculta del crupier:\n\n");
		printf("|=================|\n");
		printf("|	      | %c |\n", maquina_categoriaCarta2);
		printf("|  	      ====|\n");
		printf("|		  |\n");
		printf("|		  |\n");
		tipoDeValor(maquina_puntajeCarta2);
		printf("\n|		  |\n");
		printf("|		  |\n");
		printf("|		  |\n");
		printf("|====	          |\n");
		printf("| %c |		  |\n",maquina_categoriaCarta2);
		printf("|=================|\n\n");
		
		printf("Puntaje total de jugador: %i \n",puntosJugador);
		printf("Puntaje total de crupier: %i \n",puntosMaquina);	
		
		//Comprobar si el jugador ganó o perdió la apuesta de esta ronda
		
		if(puntosJugador>21){
			printf("Lastima! Has superado el puntaje de 21, has perdido esta mano (apuesta)\n");
			fichas -= apuesta;
		} else {
			if(puntosJugador>puntosMaquina){
				//caso de ganar con Blackjack o 21 exactos
				if (puntosJugador == 21){
					apuesta *= 3;
				}
				
				fichas += apuesta; 
				printf("\nFelicidades! Has ganado esta mano (apuesta)\n");
				printf("Has recuperado tu apuesta de esta ronda y obtenido %i fichas\n\n", apuesta);
				
			}
		
		else{
				printf("\nLastima! Has perdido esta mano (apuesta)\n");
				printf("Has perdido tu apuesta de %i fichas esta ronda\n\n", apuesta);
				fichas -= apuesta;
			}
		}
			}
			//Una vez que el usuario NO desea ingresar a una nueva partida
		else{
				printf("\nFichas finales: %i\n", fichas);
				printf("Muchas gracias por jugar!");
				return 0;
			}
		
			j=0;
	}	
	
	printf("La cantidad de fichas es menor a la necesaria para entrar a una nueva partida\n");
	if(fichas<0){
		//Si el la cantidad perdida es mayor a la cantidad de fichas que se tiene para juego.
		printf("\n Usted debe %i fichas\n", -1*fichas);
	} else{
	printf("Fichas finales: %i\n", fichas);
	}
	system("pause");//Evita que el ejecutable se cierre después de la entrada de datos
	return 0;
}

//Símbolos de las esquinas de las cartas
char categoriaAzar( int num){
	char categoria;
	switch(num){
		
	case 1:
		categoria = '';
		break;
	case 2:
		categoria = '';
		break;
	case 3:
		categoria = '';
		break;
	case 4:
		categoria = '';
		break;
	};
	return categoria;
}
	
//Letras en caso de salir una carta de J, Q, R o As
char valoresAltos(int num){
	char letra;
	switch(num){
		
	case 1:
		letra = 'A';
		break;
			
	case 11:
		letra = 'J';
		break;
			
	case 12:
		letra = 'Q';
		break;
			
	case 13:
		letra = 'K';
		break;	
	}
	return letra;
}
		
//Igualar el valor de las cartas de J,K y Q a 10
int puntajesAltos(int num){
	int valor;
	switch(num){
	case 11:
		valor = 10;
		break;
	case 12:
		valor = 10;
		break;
	case 13:
		valor = 10;
		break;	
	}
	return valor;
}
			
//Cambiar la salida de la carta en caso de ser J, Q, R o As
void tipoDeValor(int num){
	if(num>1 && num<=10)
		printf("|       %3i       |   ", num);
	else
		printf("|       %3c       |   ", valoresAltos(num));
}
		
	
//Cambiar la salida de la carta en caso de ser J, Q, R o As para el caso de la crupier
void tipoDeValor_1(int num){
	if(num>1 && num<=10)
		printf("%i ", num);
	else
		printf("%c ", valoresAltos(num));
}

//Asignación del valor as en el primer turno
int ValorDeAs(int EntradaCarta_1, int EntradaCarta_2,int puntaje){
	
	if((EntradaCarta_1== 1) || (EntradaCarta_2== 1)){
		if(puntaje<11){
			puntaje+= 10;
		}
	}
	return puntaje;
}

//Generador de cartas únicas, el sistema genera cartas con la condición de que sean diferentes
void generadorDeCartas(int valoresAleatorios[], int categoriasAleatorias[]) {
	srand(time(NULL));

	for(int i= 0; i<15; i++){
		valoresAleatorios[i] = MIN + rand()%MAX;
		categoriasAleatorias[i] = MIN + rand()%4;
	}
		for(int i= 0; i<15; i++){
			for(int j=0; j<15; j++){
				if((valoresAleatorios[j] == valoresAleatorios[i]) && (i!=j) && (categoriasAleatorias[j] == categoriasAleatorias[i])){

					do{
						valoresAleatorios[j] = MIN + rand() % MAX;
					} while(valoresAleatorios[j] == valoresAleatorios[i]);

					do{
						categoriasAleatorias[j] = MIN + rand() % 4;
					} while(categoriasAleatorias[j] == categoriasAleatorias[i]);
				}
			}
		}
}

int gotoYX (int columna, int linea){
	COORD coord;
	coord.Y = columna;
	coord.X = linea;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
	return 0;
}
