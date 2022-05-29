#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "la_sombra_de_mac.h"
#include "utiles.h"


#define MAX_POCOS_MOVIMIENTOS 300
#define MIN_MUCHOS_MOVIMIENTOS 400
#define MAX_MOVIMIENTOS_LOGRO 200
#define MIN_PUNTOS_LOGRO 700

#define JUEGO_PERDIDO -1
#define JUEGO_GANADO 1
#define JUGANDO 0

void imprimir_final(juego_t juego, int numero_movimientos){
    if (estado_juego(juego) == JUEGO_PERDIDO){
        if (juego.sombra.esta_viva == true){
            printf("Perdiste. Mac no llegó a salvo a casa y Bloo decidió no volver a jugar este juego nunca más :(. Mirá el lado bueno, vos podés volver a jugarlo, todavía no cobramos por partida jugada, así que a cambiar el destino de ambos!\n");
        }else {
            printf("Perdiste, ni Mac ni Bloo volvieron a casa, en la Mansion Foster los siguen esperando :(. Mirá el lado bueno, vos podés volver a jugarlo, todavía no cobramos por partida jugada, así que a cambiar el destino de ambos!\n");
        }
    }

    if (estado_juego(juego) == JUEGO_GANADO){
        printf(" \
     ######      ###    ##    ##    ###     ######  ######## ########          \n \
    ##    ##    ## ##   ###   ##   ## ##   ##    ##    ##    ##                \n \
    ##         ##   ##  ####  ##  ##   ##  ##          ##    ##                \n \
    ##   #### ##     ## ## ## ## ##     ##  ######     ##    ######            \n \
    ##    ##  ######### ##  #### #########       ##    ##    ##                \n \
    ##    ##  ##     ## ##   ### ##     ## ##    ##    ##    ##       ####     \n \
     ######   ##     ## ##    ## ##     ##  ######     ##    ######## ####     \n \
                                                                       ##      \n \
                                                                      ##       \n \
                                                                               \n \
    ######## ######## ##       ####  ######  #### ########     ###    ########  ########  ######  \n \
    ##       ##       ##        ##  ##    ##  ##  ##     ##   ## ##   ##     ## ##       ##    ## \n \
    ##       ##       ##        ##  ##        ##  ##     ##  ##   ##  ##     ## ##       ##       \n \
    ######   ######   ##        ##  ##        ##  ##     ## ##     ## ##     ## ######    ######  \n \
    ##       ##       ##        ##  ##        ##  ##     ## ######### ##     ## ##             ## \n \
    ##       ##       ##        ##  ##    ##  ##  ##     ## ##     ## ##     ## ##       ##    ## \n \
    ##       ######## ######## ####  ######  #### ########  ##     ## ########  ########  ######  \n \
                                                                                                  \n");

        if (numero_movimientos < MAX_POCOS_MOVIMIENTOS){
            printf("Mac y Bloo llegaron a casa sanos y salvos, y a Bloo le pareció que el juego había sido entretenido a pesar de morir un par de veces, por lo que volverían a jugarlo\n");
        }else if ((numero_movimientos >= MAX_POCOS_MOVIMIENTOS) && (numero_movimientos < MIN_MUCHOS_MOVIMIENTOS)){
            printf("Mac y Bloo llegaron a casa sanos y salvos, pero Bloo decidió que no era una buena idea volver a jugar este juego porque murió unas cuantas veces\n");
        }else {
            printf("Mac y Bloo llegaron a casa sanos y salvos, y a Bloo le pareció un juego aburrido, y sumado a que murió varias veces decidió que no era una buena idea volver a jugar este juego\n");
        }

        int num_logros = 0;

        printf("Logros ganados en esta partida:\n");

        if (numero_movimientos <= MAX_MOVIMIENTOS_LOGRO){
            printf("Rápido y furioso: Logrado tras llegar a la meta en %i movimientos o menos\n", MAX_MOVIMIENTOS_LOGRO);
            num_logros ++;
        }

        if (juego.personaje.puntos < 0){
            printf("En deuda: Logrado tras llegar a la meta con un número de puntos negativo (de dudoso mérito, no suma como logro realmente)\n");
            num_logros ++;
        }

        if (juego.personaje.puntos > MIN_PUNTOS_LOGRO){
            printf("Millonario: Logrado tras llegar a la meta agarrando todas las monedas y con un poco de suerte ;)\n");
            num_logros ++;
        }

        if (num_logros == 0){
            printf("Ninguno :(. Podés volver a jugar e intentar ganar alguno, probá ganando en menos de %i intentos.\n", MAX_MOVIMIENTOS_LOGRO);
        }
    }
}

int main (){

    srand ((unsigned)time(NULL)); // Genera la semilla aleatoria.

    juego_t juego;

    inicializar_juego(&juego);

    printf("                                                                                                             \n \
Contexto: Mac y a Bloo a volver de la mansión luego de haber pasado una tarde explorando la ciudad.              \n \
Deberás guiarlos en su camino ingresando una dirección en la que caminar, para poder encontrar la llave que          \n \
abre la puerta de la mansión. Bloo, para hacer la vuelta de forma divertida, va a caminar en espejo con respecto     \n \
a Mac. Es decir, si Mac se dirige en algun sentido horizontal (izquierda o derecha), Bloo irá en el camino           \n \
contrario. Presione F para empezar\n");

    printf("\n");

    int numero_movimientos = 0;
    while (estado_juego(juego) == JUGANDO){
        realizar_jugada(&juego);
        if ((estado_nivel(juego) == JUEGO_GANADO) && (juego.nivel_actual < MAX_NIVELES)){
            juego.nivel_actual ++;
        }
        printf("%i movimientos\n", numero_movimientos);
        numero_movimientos ++;
    }

    imprimir_final(juego, numero_movimientos);

    return 0;
}