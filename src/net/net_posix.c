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
        return NULL; // Memory allocation failed
    }

    ctx->socket = socket(AF_INET, SOCK_STREAM, 0);
    
    if (ctx->socket < 0) {
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

    struct sockaddr_in addr;
    address.sin_family = AF_INET;
    address.sin_port = htons(*(ctx->port));
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    
    return 0;
}

void net_cleanup( net_context_t* ctx ) {
    // Implementation for POSIX systems
    // Cleanup resources here
}