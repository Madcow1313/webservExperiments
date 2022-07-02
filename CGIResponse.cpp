#include "CGIresponse.hpp"

CGIResponse::CGIResponse()
{
}

CGIResponse::~CGIResponse()
{
}

void CGIResponse::SetFirstHeader()
{
	_firstHeader = "HTTP/1.1 200 OK\n";
}

std::string CGIResponse::GetFirstHeader()
{
	return (_firstHeader);
}

void CGIResponse::ExecuteCGIAndRedirect()
{
	SetFirstHeader();
	int pid;
	int fdOut;
	int OldFds[2];

	OldFds[0] = dup(STDIN_FILENO);
	OldFds[1] = dup(STDOUT_FILENO);

	fdOut = open("temp_fileOut", O_CREAT, 777);
	
	pid = fork();

	if (pid < 0)
	{
		std::cerr << "Fork failed\n";
	}
	if (pid == 0)
	{
		dup2(fdOut, STDOUT_FILENO);
		std::cout << GetFirstHeader();
		execve(_name.c_str(), NULL, envp);
	}
	else
	{
		char buffer[1024];
		waitpid(-1, NULL, 0);
		read(fdOut, buffer, 1024);
	}
	dup2(OldFds[1], STDOUT_FILENO);
	close(fdOut);
}