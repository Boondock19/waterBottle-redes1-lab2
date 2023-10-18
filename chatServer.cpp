/*
* 
* Archivo para crear un socket Servidor con protocolo TCP
* se tomo parte del codigo suministrado de  Leandro Lucarella.
* 
*   Redes de computacion I

    José González 15-10627
    Ana Santos. 17-10602
    Amaranta Villegas 16-11247

*
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
    
    /* Se envian los datos */
   
    write(sockFileDescrytor, message, BUFFER_LEN);
        
    /*Si el mensaje contiene 'end' entonces apagamos el servidor*/
    if (strncmp("end", message, 3) == 0) {
        printf("Se cierra la comunicación con el cliente\n");
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
    int addr_len;
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
    printf("Se ha establecido la comunicacion con el cliente ....\n");
    printf("Esperando datos ....\n");

    /* Se reciben los datos */
    read(sockClientFd, buf, BUFFER_LEN);
    buf[strlen(buf)] = '\0'; // Eliminamos el salto de linea
    
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
   
    
    int firstCapacity = atoi(str1Splited);
    int secondCapacity = atoi(str2Splited);
    char message [BUFFER_LEN_MINUS];
    
 
    WaterBottle bottle1(firstCapacity);
    WaterBottle bottle2(secondCapacity);

    
    /* Se envia informacion al cliente */
    sprintf(message, "Inician ambas botellas vacias botella 1: %s, botella 2: %s", bottle1.toString(),bottle2.toString());
    sendInfo(sockClientFd, message);


    /* Se envia informacion al cliente */
    sprintf(message, "Se llena la botella 1");
    sendInfo(sockClientFd, message);
    bottle1.fill();

    /* Se envia informacion al cliente */
    sprintf(message, "Valor actual de la botella 1: %s",bottle1.toString());
    sendInfo(sockClientFd, message);
    
/* Se envia informacion al cliente */
    sprintf(message, "Valor actual de la botella 2: %s",bottle2.toString());
    sendInfo(sockClientFd, message);
    
    fillOtherBottle(bottle1, bottle2);

    /* Se envia informacion al cliente */
    sprintf(message, "Transvasar de la botella 1 a la botella 2:  ");
    sendInfo(sockClientFd, message);

   
    
     /* Se envia informacion al cliente */
    sprintf(message, "Valor actual de la botella 1: %s",bottle1.toString());
    sendInfo(sockClientFd, message);
    
    
     /* Se envia informacion al cliente */
    sprintf(message, "Valor actual de la botella 2: %s",bottle2.toString());
    sendInfo(sockClientFd, message);

    bottle2.empty();
    
     /* Se envia informacion al cliente */
    sprintf(message, "Vaciamos la botella 2: ");
    sendInfo(sockClientFd, message);
    
     /* Se envia informacion al cliente */
    sprintf(message, "Valor actual de la botella 1: %s",bottle1.toString());
    sendInfo(sockClientFd, message);
    
     /* Se envia informacion al cliente */
    sprintf(message, "Valor actual de la botella 2: %s",bottle2.toString());
    sendInfo(sockClientFd, message);

    
    fillOtherBottle(bottle1, bottle2);
     /* Se envia informacion al cliente */
    sprintf(message, "Transvasar de la botella 1 a la botella 2:  ");
    sendInfo(sockClientFd, message);
     /* Se envia informacion al cliente */
    sprintf(message, "Valor actual de la botella 1: %s",bottle1.toString());
    sendInfo(sockClientFd, message);
    
     /* Se envia informacion al cliente */
    sprintf(message, "Valor actual de la botella 2: %s",bottle2.toString());
    sendInfo(sockClientFd, message);

    /* Se envia informacion al cliente */
    
    sprintf(message, "Llenamos la botella 1 ");
    sendInfo(sockClientFd, message);
    
    bottle1.fill();
     
    sprintf(message, "Valor actual de la botella 1: %s",bottle1.toString());
    sendInfo(sockClientFd, message);
    
     /* Se envia informacion al cliente */
    sprintf(message, "Valor actual de la botella 2: %s",bottle2.toString());
    sendInfo(sockClientFd, message);

     /* Se envia informacion al cliente */
    sprintf(message, "Transvasar de la botella 1 a la botella 2 ");
    sendInfo(sockClientFd, message);
    fillOtherBottle(bottle1, bottle2);


   /* Se envia informacion al cliente */
    sprintf(message, "Valor actual de la botella 1: %s",bottle1.toString());
    sendInfo(sockClientFd, message);
    
     /* Se envia informacion al cliente */
    sprintf(message, "Valor actual de la botella 2: %s",bottle2.toString());
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

    /* cerramos descriptor del socket */
    close(sockfd);
    exit (0);
}