#pragma once
#include "header.hpp"

class CGIResponse
{
private:
	std::string _name;
	std::string _firstHeader;
	char **envp;
public:
	CGIResponse();
	~CGIResponse();
	void ExecuteCGIAndRedirect();
	void SetFirstHeader();
	std::string GetFirstHeader();
};


