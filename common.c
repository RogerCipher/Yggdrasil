#include <stdlib.h>
#include <stdio.h>

void error(const char *msg) 
{
	//para apanhar mensagens de erro e dar exit do programa
    perror(msg);
    exit(1);
}

void limparEcra()
{
    //dar clear da console para unix based systems
    printf("\033[H\033[J");
}

void mostrarBanner()
{
    printf("\n----------------------------------");
    printf("\n");
    printf("     __ __           _             _ _ \n");
    printf("    |  |  |___ ___ _| |___ ___ ___|_| |\n");
    printf("    |_   _| . | . | . |  _| .'|_ -| | |\n");
    printf("      |_| |_  |_  |___|_| |__,|___|_|_|\n");
    printf("          |___|___|                    \n");
    printf("\n");
    printf("* Version: Alpha\n");
    printf("-----------\n");
}