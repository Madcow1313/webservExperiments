#include "Response.hpp"

Response::Response()
{
}

Response::Response(std::string content_type, int content_length, std::string body)
{
	_content_type = content_type;
	_content_length = content_length;
	_body = body;
	SetMethods();
	FillCodes();
}
Response::~Response()
{
}
Response::Response( Response const &other )
{
	*this = other;
}
Response & Response::operator=( Response const &other )
{
	this->_codes = other._codes;
	return(*this);
}

void Response::FillCodes()
{
	/*informational 100 - 103 */
	_codes.insert(std::make_pair(100, "Continue"));
	_codes.insert(std::make_pair(101, "Switching Protocols"));
	_codes.insert(std::make_pair(102, "Processing"));
	_codes.insert(std::make_pair(103, "Early Hints"));

	/*success 200-299*/
	_codes.insert(std::make_pair(200, "OK"));
	_codes.insert(std::make_pair(201, "Created"));
	_codes.insert(std::make_pair(202, "Accepted"));
	_codes.insert(std::make_pair(203, "Non-Authoritative Information"));
	_codes.insert(std::make_pair(204, "No Content"));
	_codes.insert(std::make_pair(205, "Reset Content"));
	_codes.insert(std::make_pair(206, "Partial Content"));
	_codes.insert(std::make_pair(207, "Multi-Status"));
	_codes.insert(std::make_pair(208, "Already Reported"));
	_codes.insert(std::make_pair(226, "IM Used"));

	/*redirection messages*/
	_codes.insert(std::make_pair(300, "Multiple Choices"));
	_codes.insert(std::make_pair(301, "Moved Permanently"));
	_codes.insert(std::make_pair(302, "Found"));
	_codes.insert(std::make_pair(303, "See Other"));
	_codes.insert(std::make_pair(304, "Not Modified"));
	_codes.insert(std::make_pair(305, "Use Proxy"));
	_codes.insert(std::make_pair(306, "unused")); //reserved???
	_codes.insert(std::make_pair(307, "Temporary Redirect"));
	_codes.insert(std::make_pair(308, "Permanent Redirect"));

	/*client error responses*/
	_codes.insert(std::make_pair(400, "Bad Request"));
	_codes.insert(std::make_pair(401, "Unauthorized"));
	_codes.insert(std::make_pair(402, "Payment Required"));
	_codes.insert(std::make_pair(403, "Forbidden"));
	_codes.insert(std::make_pair(404, "Not Found"));
	_codes.insert(std::make_pair(405, "Method Not Allowed"));
	_codes.insert(std::make_pair(406, "Not Acceptable"));
	_codes.insert(std::make_pair(407, "Proxy Authentication Required"));
	_codes.insert(std::make_pair(408, "Request Timeout"));
	_codes.insert(std::make_pair(409, "Conflict"));
	_codes.insert(std::make_pair(410, "Gone"));
	_codes.insert(std::make_pair(411, "Length Required"));
	_codes.insert(std::make_pair(412, "Precondition Failed"));
	_codes.insert(std::make_pair(413, "Payload Too Large"));
	_codes.insert(std::make_pair(414, "URI Too Long"));
	_codes.insert(std::make_pair(415, "Unsupported Media Type"));
	_codes.insert(std::make_pair(416, "Range Not Satisfiable"));
	_codes.insert(std::make_pair(417, "Expectation Failed"));
	_codes.insert(std::make_pair(418, "I'm a teapot"));
	_codes.insert(std::make_pair(421, "Misdirected Request"));
	_codes.insert(std::make_pair(422, "Unprocessable Entity"));
	_codes.insert(std::make_pair(423, "Locked"));
	_codes.insert(std::make_pair(424, "Failed Dependency"));
	_codes.insert(std::make_pair(425, "Too Early"));
	_codes.insert(std::make_pair(426, "Upgrade Required"));
	_codes.insert(std::make_pair(428, "Precondition Required"));
	_codes.insert(std::make_pair(429, "Too Many Requests"));
	_codes.insert(std::make_pair(431, "Request Header Fields Too Large"));
	_codes.insert(std::make_pair(451, "Unavailable For Legal Reasons"));

	/*server error responses*/
	_codes.insert(std::make_pair(500, "Internal Server Error"));
	_codes.insert(std::make_pair(501, "Not Implemented"));
	_codes.insert(std::make_pair(502, "Bad Gateway"));
	_codes.insert(std::make_pair(503, "Service Unavailable"));
	_codes.insert(std::make_pair(504, "Gateway Timeout"));
	_codes.insert(std::make_pair(505, "HTTP Version Not Supported"));
	_codes.insert(std::make_pair(506, "Variant Also Negotiates"));
	_codes.insert(std::make_pair(507, "Insufficient Storage"));
	_codes.insert(std::make_pair(508, "Loop Detected"));
	_codes.insert(std::make_pair(510, "Not Extended"));
	_codes.insert(std::make_pair(511, "Network Authentication Required"));
}

void Response::MakeHTTPResponse(int code)
{
	if (!_response_code)
		_response_code = code;
	_response.append("HTTP/1.1 " + CodeToString(_response_code) + " " + _codes[_response_code] + "\n");
	_response.append("Server: server\n");
	_response.append("Date: " + GetDateAndTime());
	_response.append("Content-Type: " + GetContentType() + "\n");
	if (_response_code >= 400 && _response_code <= 500 )
	{
		_body.clear();
		_body.append("<p style=\"text-align:center;\">");
		_body.append("<b>");
		_body.append("Sorry! Can't load page. Please, contact administrator. Error: ");
		_body.append(_codes[_response_code]);
		_body.append("<b>");
		_body.append("</p>");
		_body.append("\n");
		this->_content_length = _body.size();
	}
	_response.append("Content-Length: " + GetContentLength() + "\n");
	_response.append("Connection: keep-alive\n");
	_response.append("Accept-Ranges: bytes\n");
	_response.append("\n\n");
	_response.append(_body);
}
std::string Response::CodeToString(int code)
{
	int temp = 0;
	std::string ret = "";
	while (code > 0)
	{
		temp = code % 10;
		ret.insert(ret.begin(), temp + '0');
		code /= 10;
	}
	return ret;
}

std::string Response::GetDateAndTime()
{
	std::string	date_and_time;
	std::time_t current_time = std::time(NULL);

	date_and_time = std::string(std::asctime(std::localtime(&current_time)));
	return date_and_time;
}

std::string Response::GetContentType()
{
	return _content_type;
}

std::string Response::GetContentLength()
{
	return CodeToString(_content_length);
}

std::string Response::GetResponse()
{
	return _response;
}

void Response::SetContentType(std::string content_type)
{
	this->_content_type = content_type;
}

void Response::ClearContents()
{
	_response.clear();
	_content_type.clear();
	_content_length = 0;
	_body.clear();
	_response_code = 0;
}

void Response::SetMethods()
{
	_allowed_methods.push_back("GET");
	_allowed_methods.push_back("POST");
	_allowed_methods.push_back("PUT");
	_allowed_methods.push_back("DELETE");
}

void Response::SetContentLength(int length)
{
	_content_length = length;
}


void Response::CheckMethod(std::string &method)
{
	for (size_t i = 0; i < _allowed_methods.size(); i++)
	{
		if (!method.compare(_allowed_methods[i]))
			return ;
	}
	_response_code = 405;
}