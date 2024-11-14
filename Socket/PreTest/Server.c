//SERVER
#include <stdio.h>       //std in-out
#include <stdlib.h>      //per utilizzo di certe funzioni:htonl,rand,....
#include <sys/socket.h>  //funz. accept+bind+listen
#include <sys/types.h>   //funz. accept
#include <netinet/in.h>  //definiscono la struttura degli indirizzi 
#include <string.h>      //funz. stringhe
#include <errno.h>       //gestioni errori connessione
#include <ctype.h>       //bind
#include <unistd.h>     // file header che consente l'accesso alle API dello standard POSIX
#include <ctype.h> //per poter utilizzare funzione come isaigit(), isalpha(), islower(), isupper(), tolower(), toupper()

#define SERVERPORT 1313

int main() {
    struct sockaddr_in servizio, addr_remoto; 

    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);

    int socketfd, soa, fromlen = sizeof(servizio);

    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    if (socketfd < 0) {
        perror("Errore nella creazione del socket");
        exit(EXIT_FAILURE);
    }

    if (bind(socketfd, (struct sockaddr*)&servizio, sizeof(servizio)) < 0) {
        perror("Errore nel bind");
        close(socketfd);
        exit(EXIT_FAILURE);
    }

    if (listen(socketfd, 10) < 0) {
        perror("Errore nel listen");
        close(socketfd);
        exit(EXIT_FAILURE);
    }

    for (; ;)
    {
        printf("\n\nServer in ascolto...");
        fflush(stdout);

        soa = accept(socketfd, (struct sockaddr*)&addr_remoto, &fromlen);

        if (soa < 0) {
            perror("Errore nella accept");
            continue; 
        }
        
        /*----------------------------------------------
        PER PASSARE NUMERI

        if(send(soa, &num, sizeof(int), 0)<0){
            printf("Errore nella send di num");
            close(soa);
            continue;
        }

        if(recv(soa, &num, sizeof(int), 0)<0){
            printf("Errore nella recv di num");
            close(soa);
            exit(EXIT_FAILURE);
        }
        
        ----------------------------------------------*/

        /*----------------------------------------------
        PER PASSARE vettori

        if(send(soa, vett, sizeof(vett), 0)<0){
            printf("Errore nella send di vett");
            close(soa);
            continue;
        }

        if(recv(soa, vett, sizeof(vett), 0)<0){
            printf("Errore nella recv di vett");
            close(soa);
            exit(EXIT_FAILURE);
        }
        
        ----------------------------------------------*/

        close(soa);
    }

    close(socketfd);
    return 0;   
}