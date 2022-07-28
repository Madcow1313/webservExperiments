#pragma once
#include "header.hpp"

class Image
{
	private:
		std::string _image_name;
		std::vector<std::string> _image_array;
		std::ifstream _file;
	public:
		Image(const std::string &image_name);
		~Image();
		Image( Image const &other );
		Image & operator=( Image const &other );

		void ConvertToChar();
		void PushToBrowser(int fd);
};
