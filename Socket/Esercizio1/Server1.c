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

#define DIM 50
#define SERVERPORT 1313

void upper(char str[DIM])
{
    for(int i = 0; i<strlen(str); i++){
        str[i] = toupper(str[i]);
    }
}

int main()
{
    struct sockaddr_in servizio, addr_remoto;// record con i dati del server e del client

    servizio.sin_family=AF_INET;
    servizio.sin_addr.s_addr=htonl(INADDR_ANY);
    servizio.sin_port=htons(SERVERPORT);

    int socketfd, soa, fromlen=sizeof(servizio);
    char str[DIM];

    socketfd=socket(AF_INET,SOCK_STREAM,0);

    bind(socketfd,(struct sockaddr*)&servizio,sizeof(servizio));

    // poniamo il server in ascolto delle richieste dei client
    listen(socketfd,10);// può attendere fino a 10 client

    // ciclo infinito
    for (; ;)
    {
        printf("\n\nServer in ascolto...");
        fflush(stdout);

        soa=accept(socketfd,(struct sockaddr*)&addr_remoto,&fromlen);

        read(soa, str,sizeof(str));
        printf("\nValore letto: %s\n", str);

        upper(str);
        write(soa, str, sizeof(str));
        close(soa);
    }

    close(socketfd);
    return 0;   
}