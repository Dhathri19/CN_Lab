#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

int main(int argc, char const *argv[]) {
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char filename[1024] = {0};
    char buffer[1024] = {0};
    FILE *fp;

    // Create socket file descriptor
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    // Connect to server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    // Get filename from user
    printf("Enter the filename to send: ");
    scanf("%s", filename);

    // Send filename to server
    send(sock, filename, strlen(filename), 0);

    // Open file for reading
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("File not found\n");
        return -1;
    }

    // Send file contents to server
    while (fgets(buffer, 1024, fp) != NULL) {
        send(sock, buffer, strlen(buffer), 0);
        memset(buffer, 0, sizeof(buffer));
    }

    fclose(fp);
    close(sock);

    return 0;
}

