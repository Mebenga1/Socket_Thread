#include "socket_thread_server.h"

void *receive_request(void *args ){ // Définition de la fonction pour recevoir les requêtes des connexion clientes 

    int new_socket_fd = *(int *)args; // Descripteur de fichier de la nouvelle socket
    struct sockaddr_in client_address ; // Structure pour l’adresse IP et le port de connexion du client
    
    int size_message_content= 1024;
    char *message_content = calloc(size_message_content, sizeof(char)); // Allocation de mémoire pour le contenu du message

    socklen_t client_address_size = sizeof(client_address); // Taille de la structure de l'adresse client

    // Récupération de l'adresse IP du client
    getpeername(new_socket_fd, (struct sockaddr *)&client_address, &client_address_size);

    // Réception du message de la requête
    recv(new_socket_fd, message_content, size_message_content, 0); 

    // Écrire le message dans le fichier log
    int writing_file = open("./file/connection_message.log", O_APPEND | O_CREAT | O_WRONLY, 0644); 
    
    char *log_message = malloc(sizeof(char ) * 1200);
    
    pthread_t id_thread = pthread_self(); // Identifiant du thread actuel
    time_t date ; 
    time(&date); 
    
    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &client_address.sin_addr, client_ip, INET_ADDRSTRLEN); // Conversion de l'IP client en IP humainement compréhensible

    // Formatage du message à écrire dans le fichier log
    sprintf(log_message, "[ %s ] Client IP: %s, Message: \"%s\", thread id: %ld  \n",  ctime(&date), client_ip, message_content, id_thread); 
    
    write(writing_file, log_message, strlen(log_message)); // Écriture du message dans le fichier log
    
    free(log_message); // Libération de la mémoire allouée pour le message
    free(message_content);
    close(writing_file); // Fermeture du fichier
    
    pthread_exit(NULL); // Sortie du thread
}

