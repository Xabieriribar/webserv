#include <sys/socket.h> // pour socket, listen
#include <stdio.h> // pour perror
#include <netinet/in.h> // pour bind
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h> // pour htons, htonl, INADDR_ANY

/* struct sockaddr_in
{
    __uint8_t         sin_len;
    sa_family_t       sin_family;
    in_port_t         sin_port;
    struct in_addr    sin_addr;
    char              sin_zero[8];
};
*/

int main()
{
  int socketfd;
  int new_socket;
  struct sockaddr_in address;
  socklen_t address_len = sizeof(address);
  const int PORT = 9999;

  if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    perror("cannot create socket");
    return 1;
  }
  memset((char*)&address, 0, sizeof(address));
  // htonl = convert a long int (address) to a network representation
  // htons = convert a short int (port) to a network representation
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = htonl(INADDR_ANY);
  address.sin_port = htons(PORT);

  if (bind(socketfd,(struct sockaddr*)&address, sizeof(address)) < 0)
  {
    perror("bind failed");
    return 1;
  }
  if ((listen(socketfd, 3)) < 0)
  {
    perror("listen failed");
    return 1;
  }
  if ((new_socket = accept(socketfd, (struct sockaddr*)&address, &address_len)) < 0)
  {
    perror("accept error");
    return 1;
  }

  char buffer[1024] = {0};
  int valread = read(new_socket, buffer, sizeof(buffer) - 1);
  if (valread < 0)
  {
    perror("read");
  }
  else 
  {
    buffer[valread] = '\0';
    printf("%s\n", buffer);

  }
  char *hello = "Hello from the server";
  write(new_socket, hello, strlen(hello));
  close(new_socket);



  return 0;
}
