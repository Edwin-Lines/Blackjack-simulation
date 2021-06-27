/* 
Programa: Juego de Blackjack
Objetivo: Simular un juego de Blackjack
Programador 1: Edwin Andrade
Programador 2: Esteban Pacheco
Fecha: 29/05/2021 */


/* A hacer:
	-Probar en busca de errores
	-Optimizar programa
*/


#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

//54 cartas en total - 2 jokers = 52 cartas a usar (13 de cada categoría)	
#define MAX 13
#define MIN 1

//Función de números al azar dentro de un rango dado por el usuario
int numeroAzar(int min, int max){
	int numero;
	srand(time(NULL));
	//numero = min + rand() % (max+1 - min);
	numero = rand() % (max-min+1)+min;
	return numero;
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
	
//Cambiar la salida de la carta en caso de ser J, Q, R o As
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
	//Jugador
	int jugador_puntajeCarta1, jugador_puntajeCarta2;
	char jugador_categoriaCarta1, jugador_categoriaCarta2;
	int puntajeCartaExtra[6];
	char categoriaCartaExtra[6];
	//Maquina (crupier)
	int maquina_puntajeCarta1, maquina_puntajeCarta2;
	char maquina_categoriaCarta1, maquina_categoriaCarta2;
	//Valores de impresión de cartas	
	printf("======== Juego de simulación de Blackjack ======== \n\n");
	
	printf("El objetivo del Blackjack es obtener una suma total cerca del 21 o igual a 21 sin que supere esta cantidad\n ");
	printf("Hay un total de 52 cartas, 13 tipos divididos en 4 categorías: \n Diamantes %c \n Tréboles %c \n Picas %c \n Corazones %c \n\n", diamante, trebol ,pica, corazon);
	printf("El valor de las cartas de cualquier categoría esta dada de la siguiente forma: \n");
	
	//Valor de las cartas
	printf( "Carta: As ---> Valor: 1 u 11 puntos de acuerdo al total hasta el momento \n **Si se tiene una cantidad menor o igual a 10, As tendrá un puntaje de 11, de lo contrario, tendra un puntaje de 1** \n");
	for (i=MIN+1;i<=MAX-3;i++){
		printf( "Carta: %i ---> Valor: %i puntos \n", i, i);
	}
	printf( "Carta: J (Jota) ---> Valor: 10 puntos \n");
	printf( "Carta: Q (Reina) ---> Valor: 10 puntos \n");
	printf( "Carta: K (Rey) ---> Valor: 10 puntos \n\n");

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
			jugador_categoriaCarta1 = categoriaAzar(numeroAzar(1,4-j));
			j++;
			
			jugador_puntajeCarta2 = numeroAzar(MIN, MAX-j);
			jugador_categoriaCarta2 = categoriaAzar(numeroAzar(1,4-j));
			j++;
			
			//Generar cartas de máquina
			maquina_puntajeCarta1 = numeroAzar(MIN, MAX-j);
			maquina_categoriaCarta1 = categoriaAzar(numeroAzar(1,4-j));
			j++;
			
			maquina_puntajeCarta2 = numeroAzar(MIN, MAX-j);
			maquina_categoriaCarta2 = categoriaAzar(numeroAzar(1,4-j));
			j++;
	
			//Imprimir cartas para el usuario y las de la maquina (crupier)
			printf("\n\n Cartas del jugador:\n");
			printf("|=================|   |=================|\n");
			printf("|	      | %c |   |   	    | %c |\n", jugador_categoriaCarta1, jugador_categoriaCarta2);
			printf("|  	      ====|   |             ====|\n");
			printf("|		  |   |			|\n");
			printf("|		  |   |			|\n");
			tipoDeValor(jugador_puntajeCarta1); tipoDeValor(jugador_puntajeCarta2);  			
			printf("\n|		  |   |			|\n");
			printf("|		  |   |			|\n");
			printf("|		  |   |			|\n");
			printf("|====	          |   |====		|\n");
			printf("| %c |		  |   | %c |		|\n",jugador_categoriaCarta1, jugador_categoriaCarta2);
			printf("|=================|   |=================|\n\n");
		
			printf("Cartas del crupier:\n");
			printf("|=================|   |=================|\n");
			printf("|	      | %c |   |   	    | X |\n", maquina_categoriaCarta1);
			printf("|  	      ====|   |             ====|\n");
			printf("|		  |   |			|\n");
			printf("|		  |   |			|\n");
			tipoDeValor(maquina_puntajeCarta1);  printf("|        X        |\n");
			printf("|		  |   |			|\n");
			printf("|		  |   |			|\n");
			printf("|		  |   |			|\n");
			printf("|====	          |   |====		|\n");
			printf("| %c |		  |   | X |		|\n",maquina_categoriaCarta1);
			printf("|=================|   |=================|\n\n");
		
		i=1;
		
		//Otorgar valor de 10 para J, Q, R y As en caso de salir
		if (jugador_puntajeCarta1>10){
			jugador_puntajeCarta1 = puntajesAltos(jugador_puntajeCarta1);
		}
		if (jugador_puntajeCarta2>10){
			jugador_puntajeCarta2 = puntajesAltos(jugador_puntajeCarta2);
		}
		
		puntosJugador = jugador_puntajeCarta1+jugador_puntajeCarta2;
		
		//ValorDeAs(jugador_puntajeCarta1, jugador_puntajeCarta2, puntosJugador);(Intento de volver la asignación de as condición)
		
		//Asignación del valor as
		if(jugador_puntajeCarta1==1 || jugador_puntajeCarta2==1){
			if(puntosJugador<10){
				puntosJugador+= 10;
			}
		}
		
		if (maquina_puntajeCarta1>10){
		maquina_puntajeCarta1 = puntajesAltos(maquina_puntajeCarta1);
		}
				
		puntosMaquina = maquina_puntajeCarta1 + maquina_puntajeCarta2;
		
		//ValorDeAs(maquina_puntajeCarta1, maquina_puntajeCarta2,puntosMaquina);(Intento de pasarlo a función)
		
		//Evaluando el caso as para el primer turno
		if(maquina_puntajeCarta1==1 || maquina_puntajeCarta2==1){
			if(puntosMaquina<11){
					puntosMaquina+= 10;
			}
		}
		
		while (puntosJugador<=21 && salida == 0){
			printf("Puntos del jugador: %i \n", puntosJugador);
			printf("Puntos de la crupier: "); tipoDeValor_1(maquina_puntajeCarta1); printf("+ X \n") ;
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
				//En caso de pedir una carta extra
				puntajeCartaExtra[i] = numeroAzar(MIN, MAX-j);
				j++;
				categoriaCartaExtra[i] = categoriaAzar(numeroAzar(1,4));
				if (puntajeCartaExtra[i]>10){
					puntajeCartaExtra[i] = puntajesAltos(puntajeCartaExtra[i]);
				}
				puntosJugador += puntajeCartaExtra[i];
				
				if(puntajeCartaExtra[i] == 1){
					if(puntosJugador< 11){
						puntosJugador += 10;
					}
				} 
				
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
				
				puntajeCartaExtra[i] = numeroAzar(MIN, MAX-j);
				j++;
				categoriaCartaExtra[i] = categoriaAzar(numeroAzar(1,4));
				if (puntajeCartaExtra[i]>10){
					puntajeCartaExtra[i] = puntajesAltos(puntajeCartaExtra[i]);
				}
				puntosJugador += puntajeCartaExtra[i];
				
				if(puntajeCartaExtra[i] == 1){
					if(puntosJugador< 11){
						puntosJugador += 10;
					}
				}
				
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
			printf("Puntaje total de jugador: %i \n",puntosJugador);
			printf("Puntaje total de crupier: %i \n",puntosMaquina);
			
			printf("\n Cartas oculta del crupier:\n");
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
		else{
			printf("\nFichas finales: %i\n", fichas);
			printf("Muchas gracias por jugar!");
			return 0;
			}
			j=0;
	}	
	printf("La cantidad de fichas es menor a la necesaria para entrar a una nueva partida\n");
	if(fichas<0){
		printf("\n Usted debe %i fichas\n", -1*fichas);
	} else{
	printf("Fichas finales: %i\n", fichas);
	}
	
	system("pause");//Evita que el ejecutable se cierre después de la entrada de datos
	return 0;
}
