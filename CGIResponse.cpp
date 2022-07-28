#include "CGIresponse.hpp"

CGIResponse::CGIResponse(std::string name, char **argv, char **envp) :
	_name(name), _envp(envp), _argv(argv), _is_CGI(false)
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

	if ((fdOut = open("temp_fileOut", O_CREAT | O_TRUNC | O_RDWR, 0777)) < 0)
	{
		std::cerr << "can't open or create file\n";
		return ;
	}
	pid = fork();

	if (pid < 0)
	{
		std::cerr << "Fork failed\n";
	}
	if (pid == 0)
	{
		if (dup2(fdOut, STDOUT_FILENO) < 0)
			std::cerr << "can't dup\n";
		std::cout << _firstHeader;
		if (execve(_name.c_str(), _argv, _envp) < 0)
		{
			std::cerr << "execve failed\n";
		}
	}
	else
	{
		waitpid(-1, NULL, 0);
	}
	dup2(OldFds[1], STDOUT_FILENO);
	close(fdOut);
}

std::string CGIResponse::GetName()
{
	return _name;
}

bool CGIResponse::GetIsCGI()
{
	return _is_CGI;
}