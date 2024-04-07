#include "socket_thread_server.h"



int main(int argc, char *argv[]){

    int server_fd, new_socket_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int opt = 1;
    pthread_t thread_id;

    if(argc< 2){
        perror("Utilisation: ./serveur <port>\n [ERREUR]: Port non fournit  !!");
        exit(EXIT_FAILURE);
    }


     // Creation du descripteur de fichier du socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Création du socket échoué !!\n");
        exit(EXIT_FAILURE);
    }

    // Modification des options du socket
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR , &opt, sizeof(opt))) {
        perror("setsockopt error \n");
        exit(EXIT_FAILURE);
    }


    //Configurations du serveur 
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //inet_addr("192.168.1.101");
    address.sin_port = htons(atoi(argv[1]));

     // Attacher la socket au port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Binding échoué !!\n");
        exit(EXIT_FAILURE);
    }


     //Commencer l'écoute des connexions entrantes
    if (listen(server_fd, 3) < 0) {
        perror("Erreur lors de l'initialisation de l'écoute !!\n");
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "Serveur démarré sur le port: %d\n\n", atoi(argv[1]));


     while (1) {
        // Accepter la connexion entrante 
        if ((new_socket_fd= accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
            perror("Erreur lors de l'acceptation de la connexion entrante");
            exit(EXIT_FAILURE);
        }
        
        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &address.sin_addr, client_ip, INET_ADDRSTRLEN); // récuperation de l'@ ip du client 
        

        printf("Nouvelle connexion de %s avec le port %d \n\n", client_ip, ntohs(address.sin_port));
        
        int *nouvelle_socket= malloc(1);
        *nouvelle_socket= new_socket_fd;

        // Creation du thread port recevoir la connexion
        if (pthread_create(&thread_id, NULL, receive_request, (void *)nouvelle_socket) < 0) {
            perror("Création du thread a échoué !!");
            exit(EXIT_FAILURE);
        }

        pthread_detach(thread_id);

    }

    return 0;
}
