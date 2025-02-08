//
//  main.cpp
//  CController
//
//  Created by Bartosz Kawa on 08/02/2025.
//

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <string.h>

#define PORT     8080
#define MAXLINE 1024

using namespace std;

class Connection{
  
public:
    const char * conn_type;
    int socket_id {};
    const struct sockaddr_in sockaddr;
    socklen_t len;
    Connection(const char * conn_type, int socket_id, struct sockaddr_in sockaddr, socklen_t len) {
        /*
            Constructor, collect all required data and create socket
        */
        conn_type = conn_type;
        socket_id = socket_id;
        sockaddr = sockaddr;
        len = len;
        
        int conn {};
        if (strcmp(conn_type, "TCP") == 1) {
            if ( (socket_id = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
                perror("socket creation failed");
                exit(EXIT_FAILURE);
            }
        }
        else if (strcmp(conn_type, "UDP") == 1){
            if ( (socket_id = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
                perror("socket creation failed");
                exit(EXIT_FAILURE);
            }
        }
        else if (strcmp(conn_type, "SCTP") == 1) {
            if ( (socket_id = socket(AF_INET, SOCK_DGRAM, IPPROTO_SCTP)) < 0 ) {
                perror("socket creation failed");
                exit(EXIT_FAILURE);
            }
        }
        else {
            cout << "Something is wrong with connection type \n";
        }
    }
    
    int connect() {
        /*
            Bind to specific address
        */
        
        
    }
    
    int get_connection_data() {
        
    }
    
    int close() {
        
    }
    
private:
    //
};


int main(int argc, const char * argv[]) {
    
    int socket_id = 0;
    char buffer[MAXLINE];
    const char * message = "Connection to server established";
    struct sockaddr_in servaddr, cliaddr;
       
    // Creating socket file descriptor
    if ( (socket_id = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
       
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
       
    // Filling server information
    servaddr.sin_family    = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);
       
    // Bind the socket with the server address
    if ( bind(socket_id, (const struct sockaddr *)&servaddr,
            sizeof(servaddr)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
       
    socklen_t len;
    int n;
   
    len = sizeof(cliaddr);  //len is value/result
   
    n = recvfrom(socket_id, (char *)buffer, MAXLINE,
                MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                &len);
    buffer[n] = '\0';
    printf("Client : %s\n", buffer);
    sendto(socket_id, (const char *)message, strlen(message),
        MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
            len);
    std::cout<<"Hello message sent."<<std::endl;
    
    
    return 0;
}
