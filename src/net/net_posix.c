#include "net.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <pthread.h>


net_context_t* net_socket( void) {
    // Implementation for POSIX systems
    net_context_t* ctx = malloc(sizeof(net_context_t));
    
    if (ctx == NULL) {
        perror("Failed to allocate memory for net_context_t");
        return NULL; // Memory allocation failed
    }

    ctx->socket = socket(AF_INET, SOCK_STREAM, 0);
    
    if (ctx->socket < 0) {
        perror("Failed to create socket");
        free(ctx);
        return NULL; // Socket creation failed
    }
    
    return ctx;
}


int net_initialize ( net_context_t* ctx ) {
    // Implementation for POSIX systems
    if (ctx == NULL || ctx->port == NULL) {
        return -1; // Invalid context Missing elements
    }

    struct sockaddr_in address;
    if (memset(&address, 0, sizeof(address)) == NULL) {
        perror("Failed to initialize address structure");
        return -1; // Memory initialization failed
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(*(ctx->port));
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if( bind(ctx->socket, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Failed to bind socket");
        return -1; // Bind failed
    }

    return 0;
}

void net_cleanup( net_context_t* ctx ) {
    if (ctx == NULL) {
        return; // Nothing to clean up
    }
    close(ctx->socket);
    free(ctx->host);
    free(ctx->port);
    free(ctx);
}