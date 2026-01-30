#include <stdio.h>
#include <stdlib.h>

// #include <winsock2.h> // Windows Networking
// // (WSAStartup is called in another module for Windows)
// #include <threads.h> // Threads

// #include <sys/socket.h> // Sockets
// #include <netinet/in.h> // Internet Protocols
// #include <pthread.h> // POSIX Threads


int main( void ) {
    printf("Launcher started.\n");

    #ifdef WINDOWS_BUILD
        printf("Running on Windows platform.\n");
    #elif MAC_BUILD
        printf("Running on macOS platform.\n");
    #elif LINUX_BUILD
        printf("Running on Linux platform.\n");
    #endif
    
    
    return 0;
}