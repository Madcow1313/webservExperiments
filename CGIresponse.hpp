#pragma once
#include "header.hpp"

class CGIResponse
{
private:
	std::string _name;
	std::string _firstHeader;
	char **_envp;
	char **_argv;
	bool _is_CGI;
public:
	CGIResponse(std::string name,  char **argv, char **envp);
	~CGIResponse();
	void ExecuteCGIAndRedirect();
	void SetFirstHeader();
	std::string GetFirstHeader();
	std::string GetName();
	bool GetIsCGI();
};
