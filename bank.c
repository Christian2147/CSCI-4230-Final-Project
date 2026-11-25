#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(void) {
    char *buffer = calloc(BUFFER_SIZE, sizeof(char));

    if (buffer == NULL) {
        perror("calloc");

        return EXIT_FAILURE;
    }

    // Use TCP to establish a reliable connection
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd < 0) {
        perror("socket");
        free(buffer);

        return EXIT_FAILURE;
    }

    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    int bind_value = bind(server_fd, (struct sockaddr *)&address, sizeof(address));

    if (bind_value < 0) {
        perror("bind");
        free(buffer);
        close(server_fd);

        return EXIT_FAILURE;
    }

    int listen_value = listen(server_fd, 1);

    if (listen_value < 0) {
        perror("listen");
        free(buffer);
        close(server_fd);

        return EXIT_FAILURE;
    }

    printf("Bank server listening on port %d...\n", PORT);

    int client_fd = accept(server_fd, NULL, NULL);

    if (client_fd < 0) {
        perror("accept");
        free(buffer);
        close(server_fd);

        return EXIT_FAILURE;
    }

    // Connection success message
    printf("ATM connected!\n");

    // Establish secure channel here

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);

        ssize_t bytes_received = recv(client_fd, buffer, BUFFER_SIZE - 1, 0);
        
        if (bytes_received <= 0) {
            printf("ATM disconnected.\n");

            break;
        }

        printf("ATM: %s\n", buffer);

        // Send test response for now
        const char *response = "Message received by bank.";

        int send_value = send(client_fd, response, strlen(response), 0);

        if (send_value < 0) {
            perror("send");

            break;
        }
    }

    close(client_fd);
    close(server_fd);

    free(buffer);

    return EXIT_SUCCESS;
}
