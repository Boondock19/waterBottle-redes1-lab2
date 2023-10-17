/*
* Ejemplo de server de chat simple con datagramas (UDP).
*
* Leandro Lucarella - Copyleft 2004
* Basado en otros ejemplos públicos.
*
*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include "waterBottle.hpp"
#define SERVER_PORT 4321
#define BUFFER_LEN 1024
using namespace std;
int main(int argc, char *argv[])
{

    int sockfd; /* descriptor para el socket */
    struct sockaddr_in my_addr; /* direccion IP y numero de puerto local */
    struct sockaddr_in their_addr; /* direccion IP y numero de puerto del cliente */
    /* addr_len contendra el taman~o de la estructura sockadd_in y numbytes el
    * numero de bytes recibidos */
    int addr_len, numbytes;
    char buf[BUFFER_LEN]; /* Buffer de recepción */
    /* se crea el socket */
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }
    // Separar entrada del cliente para poder crear las Botellas
    // char str1Splited [10];
    // char str2Splited [10];
    // char * pch;
    // pch = strtok (str1," ");
    // int i = 0;
    // while (pch != NULL)
    // {
    //     if(i == 0){
    //         strcpy(str1Splited, pch);
    //     }else{
    //         strcpy(str2Splited, pch);
    //     }
    //     pch = strtok (NULL, " ");
    //     i++;
    // }
    // printf("Primera capacidad %d \n", atoi(str1Splited ));
    // printf("Segunda capacidad %d \n", atoi(str2Splited ));
    /* Se establece la estructura my_addr para luego llamar a bind() */
    my_addr.sin_family = AF_INET; /* usa host byte order */
    my_addr.sin_port = htons(SERVER_PORT); /* usa network byte order */
    my_addr.sin_addr.s_addr = INADDR_ANY; /* escuchamos en todas las IPs */
    bzero(&(my_addr.sin_zero), 8); /* rellena con ceros el resto de la estructura */
    /* Se le da un nombre al socket (se lo asocia al puerto e IPs) */
    printf("Asignado direccion al socket ....\n");
    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1) {
        perror("bind");
        exit(2);
    }
    /* Se reciben los datos (directamente, UDP no necesita conexión) */
    addr_len = sizeof(struct sockaddr);
    printf("Esperando datos ....\n");
    if ((numbytes=recvfrom(sockfd, buf, BUFFER_LEN, 0, (struct sockaddr *)&their_addr,
    (socklen_t *)&addr_len)) == -1) {
        perror("recvfrom");
        exit(3);
    }

    // cout << "Test de las propiedades de esta clase de WaterBottle" << endl;
    // cout << "Inicializacion de las botellas de agua:" << endl;
    // WaterBottle bottle1(5);
    // WaterBottle bottle2(3);

    // cout << "Capacidad de la botella 1: " << bottle1.getCapacity() << endl;
    // cout << "Capacidad de la botella 2: " << bottle2.getCapacity() << endl;

    // cout << "Vamos a llenar la primera botella para vaciarlo sobre la segunda" << endl;

    // bottle1.fill();
    // cout << "Valor actual de la botella 1: " << bottle1.getCurrentValue() << endl;
    // cout << "Valor actual de la botella 2: " << bottle2.getCurrentValue() << endl;

    // cout << "Transvasar de la botella 1 a la botella 2:  Primera vez" << endl;
    // fillOtherBottle(bottle1, bottle2);

    // cout << "Valor actual de la botella 1: " << bottle1.getCurrentValue() << endl;
    // cout << "Valor actual de la botella 2: " << bottle2.getCurrentValue() << endl;

    // bottle2.empty();
    // cout << "Vaciamos la botella 2: Primera vez" << endl;
    // cout << "Valor actual de la botella 1: " << bottle1.getCurrentValue() << endl;
    // cout << "Valor actual de la botella 2: " << bottle2.getCurrentValue() << endl;

    // cout << "Transvasar de la botella 1 a la botella 2: Segunda vez" << endl;
    // fillOtherBottle(bottle1, bottle2);
    // cout << "Valor actual de la botella 1: " << bottle1.getCurrentValue() << endl;
    // cout << "Valor actual de la botella 2: " << bottle2.getCurrentValue() << endl;

    // cout << "Llenamos la botella 1: Segunda vez" << endl;
    // bottle1.fill();
    // cout << "Valor actual de la botella 1: " << bottle1.getCurrentValue() << endl;
    // cout << "Valor actual de la botella 2: " << bottle2.getCurrentValue() << endl;

    // cout << "Transvasar de la botella 1 a la botella 2: Tercera vez" << endl;
    // fillOtherBottle(bottle1, bottle2);

    // cout << "Valor actual de la botella 1: " << bottle1.getCurrentValue() << endl;
    // cout << "Valor actual de la botella 2: " << bottle2.getCurrentValue() << endl;

    // if (bottle1.getCurrentValue() == 4)
    // {
    //     cout << "Test passed" << endl;
    // }
    // else
    // {
    //     cout << "Test failed" << endl;
    // }

    /* Se visualiza lo recibido */
    printf("paquete proveniente de : %s\n",inet_ntoa(their_addr.sin_addr));
    printf("longitud del paquete en bytes: %d\n",numbytes);
    buf[numbytes] = '\0';
    printf("el paquete contiene: %s\n", buf);
    /* cerramos descriptor del socket */
    close(sockfd);
    exit (0);
}