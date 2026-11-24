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

    int client_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (client_socket < 0) {
        perror("socket");
        free(buffer);

        return EXIT_FAILURE;
    }

    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    // Use localhost (127.0.0.1) as the server IP address
    // This whole thing will just be running locally for now
    int address_result = inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);

    if (address_result <= 0) {
        perror("inet_pton");
        free(buffer);
        close(client_socket);

        return EXIT_FAILURE;
    }

    int connect_result = connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address));

    if (connect_result < 0) {
        perror("connect");
        free(buffer);
        close(client_socket);

        return EXIT_FAILURE;
    }

    printf("Connected to bank!\n");

    while(1) {
        // for now just exchange messages:
        printf("\nEnter a message (or 'exit' to quit): ");

        char* value = fgets(buffer, BUFFER_SIZE, stdin);

        if (value == NULL) {
            perror("fgets");
            
            break;
        }

        *(buffer + strcspn(buffer, "\n")) = '\0';

        if (strcmp(buffer, "exit") == 0) {
            break;
        }

        int send_value = send(client_socket, buffer, strlen(buffer), 0);

        if (send_value < 0) {
            perror("send");

            break;
        }

        // Recieve bank response
        memset(buffer, 0, BUFFER_SIZE);

        ssize_t bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);

        if (bytes_received <= 0) {
            printf("Bank disconnected.\n");

            break;
        }

        printf("Bank: %s\n", buffer);
    }

    close(client_socket);
    free(buffer);

    return EXIT_SUCCESS;
}
