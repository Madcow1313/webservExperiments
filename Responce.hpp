#pragma once
#include "header.hpp"

class Response
{
	private:
		std::string _response;
		bool _is_error;
		std::map<int, std::string> _codes;
		std::string _content_type;
		std::string _body;
		int _content_length;
	public:
		Response();
		Response(std::string content_type, int content_length, std::string body);
		~Response();
		Response( Response const &other );
		Response & operator=( Response const &other );

		/*http status codes*/
		void FillCodes();

		void MakeHTTPResponse(int code);
		std::string CodeToString(int code);
		std::string GetDateAndTime();
		std::string GetContentType();
		std::string GetContentLength();

		std::string GetResponse();

		void SetContentType(std::string content_type);
		void ClearContents();
};
