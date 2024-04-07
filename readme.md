 DESCRIPTION:
 	Mise en place d'une communication client/serveur avec des sockets en C, permettant au client d'envoyer des messages au serveur qui les affiche, avec une mise à jour du serveur pour gérer plusieurs connexions simultanées en utilisant des threads, enregistrant les messages avec les adresses IP dans un fichier pendant que le serveur écoute les connexions.
 	
 
 PRÉREQUIS:
 	- OS: Linux ( UBUNTU 20.04 chez moi ) 
 	- Compilateur : gcc
 	- Bibliothèque : -lpthread
 	- Utilitaire de build : make
 	
 	
 EXÉCUTION:
	0- Dézipper le projet.
	1- Se positionner dans le repertoire du programe : cd /path/sockets_threads
	2- Executer la commande : make
	3- Exécuter le le fichier executable du serveur : ./server << port d'ecoute >> 
	4- Exécuter le le fichier executable du client  : ./client << port d'ecoute du serveur >> << adresse ip du serveur >> << message à envoyé au serveur >>
	
	 Exemple : ./server 8080 
	 	   ./client 8080 127.0.0.1 "hello server i am a client"
	
	4- la commade : make clean permet de supprimer tous les fichiers .log, objets, executables du projet
	
	
ARBORESCENCE DU REPERTOIRE Process_Thread:
	- src/server/ : c'est le reportoire qui contient tous les fichiers sources et fichier entête  du serveur(.c et .h)
	- src/client/ : c'est le reportoire qui contient le fichiers source du client(.c)
	- build: c'est le repertoire qui contient tous les fichiers objets (.o)
	- file: c'est le repertoire qui contient le fichier de log (.log)
	- makefile
	- fichiers exécutable ( server et client)
	
FICHIER DE LOG:
	- ./file/connection_message.log
	
