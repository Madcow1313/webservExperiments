#include "header.hpp"

#define PORT 8000

#ifndef FOREIGN
#define FOREIGN 1
#endif

int main(int argc, char **argv)
{
	(void) argc;
	//(void) argv;
	int addr_len;
	int client_sock;
	struct sockaddr_in address;
	std::string hello;

	addr_len = sizeof(address);
	memset(&address, '0', addr_len);
	address.sin_family = AF_INET;
	address.sin_port = htons(PORT);
	//address.sin_addr.s_addr = INADDR_ANY;
	if(FOREIGN)
		hello = "GET / HTTP/1.1\r\n\r\n";
	else
		hello = "Hello\r\n";
	printf("%d\n", FOREIGN);
    if((!FOREIGN && (inet_pton(AF_INET, "127.0.0.1", &address.sin_addr) <= 0))) //local connections
    {
        printf("\n Invalid address/ Address not supported \n");
        return -1;
    }
	else if (FOREIGN && (inet_pton(AF_INET, argv[1], &address.sin_addr) <= 0))	//foreign connections
	{
		printf("\n Invalid address/ Address not supported \n");
        return -1;
	}
	else
        printf("\n Convertion done, connecting\n");
	if ((client_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		std::cerr << "Can't open socket!\n";
		return 0;
	}

	if ((connect(client_sock, (const sockaddr *) & address, addr_len)) < 0)
	{
		std::cerr << "can't connect\n";
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "Connected\n";
	send(client_sock, hello.c_str(), strlen(hello.c_str()), 0);
	std::cout << "Hello message sent\n";
	char buffer[1024] = {0};
	read(client_sock, buffer, 1024);
	std::cout << buffer << std::endl;
	std::cout << "connection ended\n";
	return 0;
}