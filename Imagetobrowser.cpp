#include "Imagetobrowser.hpp"

Image::Image( const std::string &image_name ) : _image_name(image_name)
{
	_file.open(_image_name.c_str());
	if (_file.is_open())
	{
		std::cout << "open success\n";
	}
}
Image::~Image()
{
	_file.close();
}
Image::Image( Image const &other )
{
	*this = other;
}
Image & Image::operator=( Image const &other )
{
	this->_image_name = other._image_name;
	return(*this);
}

void Image::ConvertToChar()
{
	std::string buffer;
	for (;;)
	{
		getline(_file, buffer);
		_image_array.push_back(buffer);
		//std::cout << buffer << std::endl;
		if (!buffer.size())
			break ;
		//buffer = nullptr;
	}
}

void Image::PushToBrowser(int fd)
{
	std::string string_to_push;
	std::string buffer;
	string_to_push.append("HTTP/1.1 200 OK\n");
	string_to_push.append("Content-type: image/jpeg\r\n\r\n");
	//string_to_push.append("Content-Transfer-Encoding: binary\n");
	//string_to_push.append("Content-length: 10000000;charset=ISO-8859-4 \r\n\r\n\n");
	//ConvertToChar();
	// string_to_push.append("<html>\n");
	// string_to_push.append("<body>\n");
	// string_to_push.append("<p>\n");
	// string_to_push.append("<img src=");
	// string_to_push.append(_image_name);
	// string_to_push.append("alt=\"Some picture\">\n");
	// string_to_push.append("</p>\n");
	// string_to_push.append("</body>\n");
	// string_to_push.append("</html>\n");
	// for (size_t i = 0; i < _image_array.size(); i++)
	// {
	// 	string_to_push.append(_image_array[i]);
	// }
	for (;;){
		getline(_file, buffer);
		if (!buffer.size())
			break ;
		string_to_push.append(buffer);
	}
	write(fd, string_to_push.c_str(), string_to_push.size());
}