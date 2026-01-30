/*
 * launcher.c
 * Author: Matys L'Abbée
 *
 * Purpose:
 *   This program is the main entry point for a blockchain application
 *   intended to create a decentralized asset. The goal of this project
 *   is to develop a blockchain-based system that can serve as a currency
 *   and a store of value, forming a valuable digital asset.
 *
 * Description:
 *   - Initializes the networking layer for peer-to-peer communication.
 *   - Sets up the blockchain environment for nodes and clients.
 *   - Provides a starting point for building decentralized applications.
 *
 * Note:
 *   This is a Linux-focused implementation; platform-specific code
 *   may be added later for Windows or macOS.
 */


#include <stdio.h>
#include <stdlib.h>
#include "net/network.h"

int main( void ) {
    printf("Launcher started.\n");

    printf("Running on Linux platform.\n");

    net_context_t* net_ctx = net_socket();
    if (net_ctx == NULL) {
        fprintf(stderr, "Failed to create network socket.\n");
        return EXIT_FAILURE;
    }

    net_ctx->port = malloc(sizeof(int));
    *(net_ctx->port) = 8000;

    if (net_initialize(net_ctx) != 0) {
        fprintf(stderr, "Failed to initialize network context.\n");
        net_cleanup(net_ctx);
        return EXIT_FAILURE;
    }
    printf("Network initialized on port %d.\n", *(net_ctx->port));
    
    net_cleanup(net_ctx);

    return 0;
}