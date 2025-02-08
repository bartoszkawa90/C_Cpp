//
//  Client.cpp
//  CController
//
//  Created by Bartosz Kawa on 08/02/2025.
//


#include <bits/stdc++.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT     8080
#define MAXLINE 1024

// Driver code
int main() {
    int sockfd;
    char buffer[MAXLINE];
    const char *message = "Hello from client";
    struct sockaddr_in servaddr;
       
    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
       
    memset(&servaddr, 0, sizeof(servaddr));
       
    // Filling server information
    servaddr.sin_family    = AF_INET; // IPv4
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY; // Set the server's address

    // Send message to server
    sendto(sockfd, (const char *)message, strlen(message),
        MSG_CONFIRM, (const struct sockaddr *) &servaddr,
        sizeof(servaddr));
    std::cout << "Message sent to server." << std::endl;
       
    socklen_t len = sizeof(servaddr);
    int n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                    MSG_WAITALL, (struct sockaddr *) &servaddr,
                    &len);
    buffer[n] = '\0';
    std::cout << "Server: " << buffer << std::endl;

    // Close the socket
    close(sockfd);

    return 0;
}

