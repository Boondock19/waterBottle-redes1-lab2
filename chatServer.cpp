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
#define BUFFER_LEN_MINUS 1022
using namespace std;




void sendInfo(int sockFileDescrytor, char * message) {
    printf("Enviando mensaje al cliente ....\n");
    /* Se envian los datos */
    printf("Este es el mensaje que se envia al cliente: %s\n", message);
    write(sockFileDescrytor, message, BUFFER_LEN);
        
    /*Si el mensaje contiene 'end' entonces apagamos el servidor*/
    if (strncmp("end", message, 3) == 0) {
        printf("Server Exit...\n");
        close(sockFileDescrytor);
     }
}


int main(int argc, char *argv[])
{

    int sockfd; /* descriptor para el socket del servidor */
    int sockClientFd;    /* descriptor para el socket del cliente */
    struct sockaddr_in my_addr; /* direccion IP y numero de puerto local */
    struct sockaddr_in their_addr; /* direccion IP y numero de puerto del cliente */
    /* addr_len contendra el taman~o de la estructura sockadd_in y numbytes el
    * numero de bytes recibidos */
    int addr_len, numbytes;
    char buf[BUFFER_LEN]; /* Buffer de recepción */
    /* se crea el socket */
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }
  
    /* Se establece la estructura my_addr para luego llamar a bind() */
    my_addr.sin_family = AF_INET; /* usa host byte order */
    my_addr.sin_port = htons(SERVER_PORT); /* usa network byte order */
    my_addr.sin_addr.s_addr = INADDR_ANY; /* escuchamos en todas las IPs */
    bzero(&(my_addr.sin_zero), 8); /* rellena con ceros el resto de la estructura */
    /* Se le da un nombre al socket (se lo asocia al puerto e IPs) */
    printf("Asignado direccion al socket ....\n");
    int statusBind = bind(sockfd,(struct sockaddr *)&my_addr,sizeof(my_addr));
    if (statusBind < 0) {
        perror("Error al realizar el bind");
        exit(2);
    }
    
    /* Configuramos al servidor/socket para que escuche a solicituces en este caso un maximo de 4 */
    statusBind = listen(sockfd, 4);
    if(statusBind < 0) {
        perror("Error al realizar el listen de solicitudes");
        exit(2);
    }
    /* Se reciben los datos */
    addr_len = sizeof(their_addr);
    /* Aceptamos las solicitudes o conexiones del cliente */
    sockClientFd = accept(sockfd, (struct sockaddr *)&their_addr, (socklen_t*)&addr_len);
    if (sockClientFd < 0) {
        perror("Error al realizar el accept de solicitudes");
        exit(2);
    }
    printf("Esperando datos ....\n");

    /* Se reciben los datos */
    read(sockClientFd, buf, BUFFER_LEN);
    buf[strlen(buf)] = '\0'; // Eliminamos el salto de linea
    printf("Mensaje recibido: %s\n", buf);


    // if ((numbytes=recvfrom(sockfd, buf, BUFFER_LEN, 0, (struct sockaddr *)&their_addr,
    // (socklen_t *)&addr_len)) == -1) {
    //     perror("recvfrom");
    //     exit(3);
    // }

    

    // Separar entrada del cliente para poder crear las Botellas
    char str1Splited [10];
    char str2Splited [10];
    char cpyBuf [1024];
    char * pch;
    strcpy(cpyBuf, buf);
    pch = strtok (cpyBuf," ");
    int i = 0;
    while (pch != NULL)
    {
        if(i == 0){
            strcpy(str1Splited, pch);
        }else{
            strcpy(str2Splited, pch);
        }
        pch = strtok (NULL, " ");
        i++;
    }
    printf("Primera capacidad %d \n", atoi(str1Splited ));
    printf("Segunda capacidad %d \n", atoi(str2Splited ));
    int firstCapacity = atoi(str1Splited);
    int secondCapacity = atoi(str2Splited);
    char message [BUFFER_LEN_MINUS];
    
    /* Se envia informacion al cliente */
    // strcpy(message, "Se recibieron los datos correctamente");
    // sendInfo(sockClientFd, message);
    cout << "Test de las propiedades de esta clase de WaterBottle" << endl;
    cout << "Inicializacion de las botellas de agua:" << endl;
    WaterBottle bottle1(firstCapacity);
    WaterBottle bottle2(secondCapacity);

    cout << "Capacidad de la botella 1: " << bottle1.getCapacity() << endl;
    cout << "Capacidad de la botella 2: " << bottle2.getCapacity() << endl;

    /* Se envia informacion al cliente */
    sprintf(message, "Inician ambas botellas vacias: (%d,%d)", bottle1.getCapacity(),bottle2.getCapacity());
    sendInfo(sockClientFd, message);


    cout << "Vamos a llenar la primera botella para vaciarlo sobre la segunda" << endl;
    /* Se envia informacion al cliente */
    sprintf(message, "Vamos a llenar la primera botella para vaciarlo sobre la segunda");
    sendInfo(sockClientFd, message);
    bottle1.fill();

    /* Se envia informacion al cliente */
    sprintf(message, "Valor actual de la botella 1: %d",bottle1.getCurrentValue());
    sendInfo(sockClientFd, message);
    
/* Se envia informacion al cliente */
    sprintf(message, "Valor actual de la botella 2: %d",bottle2.getCurrentValue());
    sendInfo(sockClientFd, message);
    
    fillOtherBottle(bottle1, bottle2);

    /* Se envia informacion al cliente */
    sprintf(message, "Transvasar de la botella 1 a la botella 2:  Primera vez");
    sendInfo(sockClientFd, message);

   
    
     /* Se envia informacion al cliente */
    sprintf(message, "Valor actual de la botella 1: %d",bottle1.getCurrentValue());
    sendInfo(sockClientFd, message);
    
    
     /* Se envia informacion al cliente */
    sprintf(message, "Valor actual de la botella 2: %d",bottle2.getCurrentValue());
    sendInfo(sockClientFd, message);

    bottle2.empty();
    cout << "Vaciamos la botella 2: Primera vez" << endl;
     /* Se envia informacion al cliente */
    sprintf(message, "Vaciamos la botella 2: Primera vez");
    sendInfo(sockClientFd, message);
    
     /* Se envia informacion al cliente */
    sprintf(message, "Valor actual de la botella 1: %d",bottle1.getCurrentValue());
    sendInfo(sockClientFd, message);
    
     /* Se envia informacion al cliente */
    sprintf(message, "Valor actual de la botella 2: %d",bottle2.getCurrentValue());
    sendInfo(sockClientFd, message);

    cout << "Transvasar de la botella 1 a la botella 2: Segunda vez" << endl;
    fillOtherBottle(bottle1, bottle2);
     /* Se envia informacion al cliente */
    sprintf(message, "Transvasar de la botella 1 a la botella 2:  Segunda vez");
    sendInfo(sockClientFd, message);
     /* Se envia informacion al cliente */
    sprintf(message, "Valor actual de la botella 1: %d",bottle1.getCurrentValue());
    sendInfo(sockClientFd, message);
    
     /* Se envia informacion al cliente */
    sprintf(message, "Valor actual de la botella 2: %d",bottle2.getCurrentValue());
    sendInfo(sockClientFd, message);

    cout << "Llenamos la botella 1: Segunda vez" << endl;
    bottle1.fill();
     /* Se envia informacion al cliente */
    sprintf(message, "Valor actual de la botella 1: %d",bottle1.getCurrentValue());
    sendInfo(sockClientFd, message);
    
     /* Se envia informacion al cliente */
    sprintf(message, "Valor actual de la botella 2: %d",bottle2.getCurrentValue());
    sendInfo(sockClientFd, message);

     /* Se envia informacion al cliente */
    sprintf(message, "Transvasar de la botella 1 a la botella 2:  Tercera vez");
    sendInfo(sockClientFd, message);
    fillOtherBottle(bottle1, bottle2);


   /* Se envia informacion al cliente */
    sprintf(message, "Valor actual de la botella 1: %d",bottle1.getCurrentValue());
    sendInfo(sockClientFd, message);
    
     /* Se envia informacion al cliente */
    sprintf(message, "Valor actual de la botella 2: %d",bottle2.getCurrentValue());
    sendInfo(sockClientFd, message);

    if (bottle1.getCurrentValue() == 4)
    {
        
        /* Se envia informacion al cliente */
        sprintf(message, "Test passed");
        sendInfo(sockClientFd, message);
        /* Se envia informacion al cliente */
        sprintf(message, "end");
        sendInfo(sockClientFd, message);
    }
    else
    {
        
        /* Se envia informacion al cliente */
        sprintf(message, "Test failed");
        sendInfo(sockClientFd, message);
        /* Se envia informacion al cliente */
        sprintf(message, "end");
        sendInfo(sockClientFd, message);
    }

    /* Se visualiza lo recibido */
    printf("paquete proveniente de : %s\n",inet_ntoa(their_addr.sin_addr));
    printf("longitud del paquete en bytes: %d\n",numbytes);
    buf[numbytes] = '\0';
    printf("el paquete contiene: %s\n", buf);
    /* cerramos descriptor del socket */
    close(sockfd);
    exit (0);
}