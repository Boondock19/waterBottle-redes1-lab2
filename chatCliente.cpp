/*
* 
* Archivo para crear un socket cliente con protocolo TCP
* se tomo parte del codigo suministrado de  Leandro Lucarella.
* 
*   Redes de computacion I

    José González 15-10627
    Ana Santos. 17-10602
    Amaranta Villegas 16-11247

*
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#define SERVER_PORT 4321
#define BUFFER_LEN 1024


void getInfoFromServer(int sockFileDescrytor) {
    char buffer[BUFFER_LEN];
    bzero(buffer, BUFFER_LEN);
    
    for(;;){
        read(sockFileDescrytor, buffer, BUFFER_LEN);
        printf("Respuesta del servidor: %s\n",buffer);
        if (strncmp(buffer,"end",3) == 0) {
            printf("El servidor ha cerrado la comunicación\n");
            break;
        } 
    }
   
}

int main(int argc, char *argv[])
{
    int sockfd; /* descriptor a usar con el socket */
    struct sockaddr_in their_addr; /* almacenara la direccion IP y numero de puerto del servidor */
    struct hostent *he; /* para obtener nombre del host */
    char str1 [10]; /* Variable para enviar al servidor*/
    char str2 [10]; /* variable para tomar el segundo argumento de las botellas */
    if (argc != 4) {
    fprintf(stderr,"\nuso: %s cliente hostname capacidadPrimeraBotella capacidadSegundaBotella\n", argv[0]);
    exit(1);
    }
    /* convertimos el hostname a su direccion IP */
    if ((he=gethostbyname(argv[1])) == NULL) {
    perror("gethostbyname");
    exit(1);
    }
    // logica para poder procesar los argumentos de las botellas para enviarlo al servidor
   
    strcpy(str1, argv[2]);
    strcpy(str2, argv[3]);
    size_t lengthOfFirstCapacity = strlen(str1);
    str1[lengthOfFirstCapacity] = ' '; // overwrite null termination
    str1[lengthOfFirstCapacity+1] = '\0'; // add a new null termination
    strcat(str1, str2);
    printf("Resultado de unir ambas capacidades %s \n", str1 );
  
    /* Creamos el socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error al crear el socket");
        exit(2);
    }
    int status =0;
    /* a donde mandar */
    their_addr.sin_family = AF_INET; /* usa host byte order */
    their_addr.sin_port = htons(SERVER_PORT); /* usa network byte order */
    their_addr.sin_addr = *((struct in_addr *)he->h_addr);
    bzero(&(their_addr.sin_zero), 8); /* pone en cero el resto */

    /* Conectamos el cliente al servidor */
    status = connect(sockfd, (struct sockaddr *)&their_addr, sizeof(their_addr));

    if (status < 0) {
        perror("Error al conectar el cliente al servidor");
        exit(2);
    }
    /* enviamos el mensaje */

    write(sockfd, str1, strlen(str1));

    // if ((numbytes=sendto(sockfd,str1,strlen(str1),0,(struct sockaddr *)&their_addr,
    // sizeof(struct sockaddr))) == -1) {
    // perror("sendto");
    // exit(2);
    // }
   


     getInfoFromServer(sockfd);
    /* cierro socket */
    close(sockfd);
    exit (0);
}