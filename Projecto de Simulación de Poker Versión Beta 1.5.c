/* 
Programa: Juego de Blackjack
Objetivo: Simular un juego de Blackjack
Programador: Edwin Andrade
Fecha: 29/05/2021 */


/* A hacer:
	-Terminar el código para que en caso de que salga 2, 11, 12 o 13, se impriman esos caracteres en las cartas y no sus valores (otra parte de tarjetas usando if?)
	-Probar en busca de errores
	-Buscar una forma que cuando el puntaje total sea mayor a 11, si sale As (1) tenga un valor de 1, y el puntaje total es menor, que valga 11
	-Optimizar programa
	-Ver una forma de que las cartas puedan ser mayores que las anteriores, especialmente para las cartas de la máquina o crupier
*/

//54 cartas en total - 2 jokers = 52 cartas a usar (13 de cada categoría)
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
	
#define MAX 13
#define MIN 1

//Función de números al azar dentro de un rango dado por el usuario
int numeroAzar(int min, int max){
	int numero;
	srand(time(NULL));
	//numero = min + rand() % (max+1 - min);
	numero = rand() % (max-min+1)+min;
	if (numero>10){
		numero = 10;
	}
	return numero;
}

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
	letra = 'R';
	break;	
	}
	return letra;
}
	
int puntajesAltos(int num){
	int valor;
	switch(num){
	case 11:
	case 12:
	case 13:
	valor = 10;
	 break;	
	}
	return valor;
}
	
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
	
	//Variable de cartas
	int jugador_puntajeCarta1, jugador_puntajeCarta2;
	char jugador_categoriaCarta1, jugador_categoriaCarta2;
	//char jugador_letraCarta1, jugador_letraCarta2;
	
	int puntajeCartaExtra[5];
	char categoriaCartaExtra[5];
	
	int maquina_puntajeCarta1, maquina_puntajeCarta2;
	char maquina_categoriaCarta1, maquina_categoriaCarta2;
	char maquina_letraCarta1, maquina_letraCarta2;
	
	printf("======== Juego de simulación de Blackjack ======== \n\n");
	
	printf("El objetivo del Blackjack es obtener una suma total cerca del 21 o igual a 21 sin que supere esta cantidad\n ");
	printf("Hay un total de 52 cartas, 13 tipos divididos en 4 categorías: \n Diamantes %c \n Tréboles %c \n Picas %c \n Corazones %c \n\n", diamante, trebol ,pica, corazon);
	printf("El valor de las cartas de cualquier categoría esta dada de la siguiente forma: \n");
	
	//Valor de las cartas
	printf( "Carta: As ---> Valor: 1 u 11 puntos de acuerdo al total hasta el momento \n **Si se tiene una cantidad menor a igual a 10, As tendrá un puntaje de 11, de lo contrario, tendra un puntaje de 1** \n");
	for (i=MIN+1;i<=MAX-3;i++){
		printf( "Carta: %i ---> Valor: %i puntos \n", i, i);
	}
	printf( "Carta: J (Jota) ---> Valor: 10 puntos \n");
	printf( "Carta: Q (Reina) ---> Valor: 10 puntos \n");
	printf( "Carta: K (Rey) ---> Valor: 10 puntos \n\n");

	//Reglas
	printf("---- REGLAS ----\n ");
	printf("1. Al iniciar la partida, el jugador podrá ver sus cartas y solo una carta que tenga el crupier, siendo que la segunda permanezca oculta hasta que el jugador termine de pedir cartas");
	printf("2. El jugador puede pedir la cantidad de cartas que desee una vez haya visto las suyas y las del crupier mientras no se pase de 21\n");
	printf("3. Al inicio del juego, el jugador contará con un total de 500 fichas \n");
	printf("4. Para poder ingresar a la partida, el jugador deberá poner un mínimo de 50 fichas para jugar \n");
	printf("5. Una vez recibida las 2 primeras cartas, el jugador puede decidir si agarrar más o quedarse con las 2 que tiene \n");
	printf("6. El jugador puede incrementar la apuesta antes de iniciar una partida para obtener más fichas si gana \n");
	printf("7. El jugador puede decidir doblar la apuesta al inicio de su turno y automaticamente recibirá una carta más \n");
	printf("8. En caso de que el jugador se quede sin fichas mínimas para entrar a la partida, el juego terminará, por lo que puede decidir retirarse depues de ganar \n\n");
	
	printf("---- FICHAS A GANAR ---- \n");
	printf("En caso de ganar con un Blackjack (21 exactos), se obtendrán el triple de fichas apostadas \n");
	printf("En caso de ganar sin haber doblado la apuesta, se obtendrán las fichas apostadas (las propias y las del crupier\n\n");
	
	while (fichas > 49){
		printf("Total de fichas: %i \n", fichas);
		
		do{
		salida = 0;
		printf("¿Desea ingresar a una nueva partida? (Si/No)  ");
		gets(resp);
		} while ( (strcmp(resp,"No")) && (strcmp(resp,"Si")) );
		//(strcmp(resp,"si"))!=0
		//En caso de aceptar entrar a la partida
			if(strcmp(resp, "Si") == 0){
			do{
			printf("Monto a apostar (Minimo de 50): ");
			fflush (stdin);
			scanf("%i", &apuesta);
			} while (apuesta<50 || apuesta>fichas);
			
			mesaApuesta = apuesta*2;
			//Reiniciar valores de cartas y cartas extra
			j=0;
			
			//Generador de cartas de jugador
			jugador_puntajeCarta1 = numeroAzar(MIN, MAX-j);
			/*if (jugador_puntajeCarta1 == 1 || jugador_puntajeCarta1 > 10){
			jugador_letraCarta1 = valoresAltos(jugador_puntajeCarta1);
			}*/
			jugador_categoriaCarta1 = categoriaAzar(numeroAzar(1,4-j));
			j++;
			
			jugador_puntajeCarta2 = numeroAzar(MIN, MAX-j);
			if(jugador_puntajeCarta2 == 1 && jugador_puntajeCarta1>=11)
			
			/*if (jugador_puntajeCarta2 == 1 || jugador_puntajeCarta2 > 10){
				jugador_letraCarta2 = valoresAltos(jugador_puntajeCarta2);
			}*/
			jugador_categoriaCarta2 = categoriaAzar(numeroAzar(1,4-j));
			j++;
			
			//Generar cartas de máquina
			maquina_puntajeCarta1 = numeroAzar(MIN, MAX-j);
			/*if (maquina_puntajeCarta1 == 1 || maquina_puntajeCarta1 > 10){
				maquina_letraCarta1 = valoresAltos(maquina_puntajeCarta1);
			}*/
			maquina_categoriaCarta1 = categoriaAzar(numeroAzar(1,4-j));
			j++;
			
			maquina_puntajeCarta2 = numeroAzar(MIN, MAX-j);
			/*if (maquina_puntajeCarta2 == 1 || maquina_puntajeCarta2 > 10){
				maquina_letraCarta2 = valoresAltos(maquina_puntajeCarta2);
			}*/
			maquina_categoriaCarta2 = categoriaAzar(numeroAzar(1,4-j));
			j++;
			
			printf("\n\n Cartas del juegador:\n");
			printf("|=================|   |=================|\n");
			printf("|	      | %c |   |   	    | %c |\n", jugador_categoriaCarta1, jugador_categoriaCarta2);
			printf("|  	      ====|   |             ====|\n");
			printf("|		  |   |			|\n");
			printf("|		  |   |			|\n");
			
			
			printf("|       %i	  |   |        %i        |\n", jugador_puntajeCarta1, jugador_puntajeCarta2);
			
			
			printf("|		  |   |			|\n");
			printf("|		  |   |			|\n");
			printf("|		  |   |			|\n");
			printf("|====	          |   |====		|\n");
			printf("| %c |		  |   | %c |		|\n",jugador_categoriaCarta1, jugador_categoriaCarta2);
			printf("|=================|   |=================|\n\n");
		
			
			printf("Cartas de la máquina:\n");
			printf("|=================|   |=================|\n");
			printf("|	      | %c |   |   	    | X |\n", maquina_categoriaCarta1);
			printf("|  	      ====|   |             ====|\n");
			printf("|		  |   |			|\n");
			printf("|		  |   |			|\n");
			
			
			printf("|       %i	  |   |        X        |\n", maquina_puntajeCarta1);
			
			
			printf("|		  |   |			|\n");
			printf("|		  |   |			|\n");
			printf("|		  |   |			|\n");
			printf("|====	          |   |====		|\n");
			printf("| %c |		  |   | X |		|\n",maquina_categoriaCarta1);
			printf("|=================|   |=================|\n\n");
		
		i=1;
		
		if (jugador_categoriaCarta1>10){
			jugador_categoriaCarta1 = puntajesAltos(jugador_categoriaCarta1);
		}
		if (jugador_categoriaCarta2>10){
			jugador_categoriaCarta2 = puntajesAltos(jugador_categoriaCarta2);
		}
		puntosJugador = jugador_puntajeCarta1+jugador_puntajeCarta2;
		
		if (maquina_categoriaCarta2>10){
		maquina_categoriaCarta2 = puntajesAltos(maquina_categoriaCarta2);
		}
		if (maquina_categoriaCarta2>10){
			maquina_categoriaCarta2 = puntajesAltos(maquina_categoriaCarta2);
		}
		puntosMaquina = maquina_puntajeCarta1 + maquina_puntajeCarta2;
		
		while (puntosJugador<=21 && salida == 0){
			printf("Puntos del jugador: %i \n", puntosJugador);
			printf("Puntos de la crupier: %i + X \n", maquina_puntajeCarta1);
			printf("Apuesta en la mesa: %i \n", mesaApuesta);
			
			printf("Opciones: \n 1. Mantenerse con la mano obtenida. \n 2. Pedir otra carta. \n 3. Doblar apuesta y pedir otra carta\n");
			fflush( stdin );
			scanf("%i", &opcion);
			getchar();
			j=0;
			switch(opcion){
			case 1:
				salida++;
				break;
			
			case 2:
				puntajeCartaExtra[i] = numeroAzar(MIN, MAX-j);
				j++;
				categoriaCartaExtra[i] = categoriaAzar(numeroAzar(1,4));
				puntosJugador += puntajeCartaExtra[i];
				
				printf("|=================|\n");
				printf("|	      | %c |\n",categoriaCartaExtra[i]);
				printf("|  	      ====|\n");
				printf("|		  |\n");
				printf("|		  |\n");
				
				
				printf("|       %i	  |\n",puntajeCartaExtra[i]);
				
				
				printf("|		  |\n");
				printf("|		  |\n");
				printf("|		  |\n");
				printf("|====	          |\n");
				printf("| %c |		  |\n",categoriaCartaExtra[i]);
				printf("|=================|\n\n");
				i++;
				break;
				
			case 3:
				apuesta *= 2;
				mesaApuesta *= 2;
				
				puntajeCartaExtra[i] = numeroAzar(MIN, MAX-j);
				j++;
				categoriaCartaExtra[i] = categoriaAzar(numeroAzar(1,4));
				puntosJugador += categoriaCartaExtra[i];
				
				printf("|=================|\n");
				printf("|	      | %c |\n",categoriaCartaExtra[i]);
				printf("|  	      ====|\n");
				printf("|		  |\n");
				printf("|		  |\n");
				
				
				printf("|       %i	  |\n",puntajeCartaExtra[i]);
				
				
				printf("|		  |\n");
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
			printf("Puntaje total de jugador: %i \n",puntosJugador);
			printf("Puntaje total de crupier: %i \n",puntosMaquina);
			
			printf("Cartas oculta del crupier:\n");
			printf("|=================|\n");
			printf("|	      | %c |\n", maquina_categoriaCarta2);
			printf("|  	      ====|\n");
			printf("|		  |\n");
			printf("|		  |\n");
			
			
			printf("|       %i	  |\n", maquina_puntajeCarta2);
			
			
			printf("|		  |\n");
			printf("|		  |\n");
			printf("|		  |\n");
			printf("|====	          |\n");
			printf("| %c |		  |\n",maquina_categoriaCarta2);
			printf("|=================|\n\n");
			
		if(puntosJugador>21){
			printf("Lastima! Has superado el puntaje de 21, has perdido esta mano (apuesta)\n");
			fichas -= apuesta;
		} else {
			if(puntosJugador>puntosMaquina){
				//caso de ganar con Blackjack o 21 exactos
				if (puntosJugador == 21){
					mesaApuesta *= 3;
				}
				
				fichas += (mesaApuesta/4); 
				printf("\nFelicidades! Has ganado esta mano (apuesta)\n");
				printf("Has recuperado tu apuesta de esta ronda y obtenido %i fichas\n", mesaApuesta/4);
				
			}
		else{
				printf("\nLastima! Has perdido esta mano (apuesta)\n");
				printf("Has perdido tu apuesta de %i fichas esta ronda\n", apuesta);
				fichas -= apuesta;
			}
		}
			}
		else{
			printf("\nFichas finales: %i\n", fichas);
			printf("Muchas gracias por jugar!");
			return 0;
			}
	}	
	printf("La cantidad de fichas es menor a la necesaria para entrar a una nueva partida\n");
	printf("Fichas finales: %i", fichas);
	return 0;
}

