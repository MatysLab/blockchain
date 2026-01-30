#ifndef NET_H
#define NET_H

typedef struct net_context{
    char* host;
    int* port;

    int socket;
}net_context_t;


/**
 * @brief This function checks if the network context has been initialized.
 * 
 * @return int Returns 1 if initialized, 0 otherwise.
 */
net_context_t* net_socket( void );

/**
 * @brief This function initializes the network context.
 * 
 * @return int Returns 0 on success, non-zero on failure.
 */
int net_initialize( net_context_t* ctx );

/**
 * @brief This function clean the network context.
 * 
 * @return int Returns 0 on success, non-zero on failure.
 */
void net_cleanup( net_context_t* ctx );

#endif /* NET_H */