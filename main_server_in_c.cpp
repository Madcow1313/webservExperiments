#include "header.hpp"
#define PORT 8000

void do_staff(char **argv, char **envp)
{

}

int main(int argc, char **argv, char **envp)
{
	(void) argc;
	int server_fd;
	int new_socket = 0;
	int addr_len;
	int valread;
	struct sockaddr_in address;
	std::string hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 18\n\nHello from server!";

	address.sin_family = AF_INET;
	address.sin_port = htons(PORT);
	address.sin_addr.s_addr = INADDR_ANY;
	addr_len = sizeof(address);
	//memset(address.sin_zero, '\0', sizeof address.sin_zero);
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		std::cerr << "Can't open socket!\n";
		return 0;
	}
	if ((bind(server_fd, (const sockaddr *) &address, addr_len)) < 0)
	{
		perror(strerror(errno));
		std::cerr << "Bind failed\n";
		return 0;
	}
	if (listen(server_fd, 10) < 0)
	{
		std::cerr << "Can't listen\n";
		exit (EXIT_FAILURE);
	}
	setsockopt(server_fd,0,0,NULL, SO_REUSEADDR);
	while (1)
	{
		std::cout << "Waiting for connection\n";
		if ((new_socket = accept(server_fd, (struct sockaddr *) &address, (socklen_t*) &addr_len)) < 0)
		{
			std::cerr << "Can't accept\n";
			exit (EXIT_FAILURE);			
		}
        char buffer[30000] = {0};
        valread = read( new_socket , buffer, 30000);
		if (!valread)
		{
			std::cerr << "no message\n";
		}
		
		close(new_socket);
        //printf("------------------Hello message sent-------------------\n");
		//str.close();
	}

}