#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <port> <server IP> <message>\n", argv[0]);
        return -1;
    }
	
    int socket_fd = 0; // Descripteur de fichier de la nouvelle socket
    struct sockaddr_in server_address; // Structure pour l’adresse IP et le port de connexion du server

    // Création de la socket
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("la création de la socket a echoué");
        exit(-1);
    }
	//initialisation des valeurs de la structure server_address
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(atoi(argv[1]));

    // conversion de l'@ ip en binaire
    if (inet_pton(AF_INET, argv[2], &server_address.sin_addr) <= 0) {
        perror("adresse ip invalide ou non supportée");
        exit(-2);
    }

    // connexion au serveur
    if (connect(socket_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Echec de la connexion");
        exit(-3);
    }

    // Envoi des données au serveur
    send(socket_fd, argv[3], strlen(argv[3]), 0);
    printf("Message envoyé !!!\n");


    // fermeture de la socket
    close(socket_fd);
    
    return 0;
}

