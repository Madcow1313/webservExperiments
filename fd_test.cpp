#include "header.hpp"

int main(int argc, char **argv, char **envp)
{
	int pid;
	int fdIn;
	int fdOut;
	int OldFds[2];

	OldFds[0] = dup(STDIN_FILENO);
	OldFds[1] = dup(STDOUT_FILENO);

	fdIn = open("temp_fileIn.txt", O_CREAT | O_RDWR, 777);
	fdOut = open("temp_fileOut.txt", O_CREAT | O_RDWR, 777);
	
	pid = fork();

	if (pid == 0)
	{
		dup2(fdIn, STDIN_FILENO);
		dup2(fdOut, STDOUT_FILENO);
		execve("cgi", argv, envp);
	}
	else
	{
		char buffer[1024];
		waitpid(-1, NULL, 0);
		read(fdOut, buffer, 1024);
	}
	dup2(OldFds[0], STDIN_FILENO);
	dup2(OldFds[1], STDOUT_FILENO);
}