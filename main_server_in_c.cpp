#include "header.hpp"
#define PORT 8000

int main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	int server_fd;
	int new_socket = 0;
	int addr_len;
	int valread;
	struct sockaddr_in address;
	std::string hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 18\n\nHello from server!";
	CGIResponse MyResponse("cgi", argv, envp);

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

	int yes = 1;
	setsockopt(server_fd,0,0,&yes, SO_REUSEADDR);
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
		if (MyResponse.GetIsCGI())
		{
			MyResponse.ExecuteCGIAndRedirect();
			std::ifstream cgi_file;
			cgi_file.open("temp_fileOut");
			char buffer2[1024];
			memset(buffer2, '\0', 1024);
			cgi_file.read(buffer2, 1024);
			write(new_socket, buffer2, strlen(buffer2));
		}
		else
		{
			Response ErrorResponce("text/html", 0, "wisdom"); //application/octet-stream
			ErrorResponce.MakeHTTPResponse(403);
			write(new_socket, ErrorResponce.GetResponse().c_str(), ErrorResponce.GetResponse().size());
			std::cout << ErrorResponce.GetResponse();
			// Image MyImage("7.jpg");
			// MyImage.PushToBrowser(new_socket);
		}
		close(new_socket);
        //printf("------------------Hello message sent-------------------\n");
		//str.close();
	}
}