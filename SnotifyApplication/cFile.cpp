#include "cFile.h"
#include <sstream>


std::string cFile::ReadFileToString(const std::string& path)
{
	if(!FileExists(path))
	{
		return std::string();
	}

	// Opening a string stream
	std::ifstream stream(path);

	// Creating a buffer to store the data
	std::stringstream buffer;

	// Storing the stream data into the buffer line by line
	buffer << stream.rdbuf();

	// done with the file, so closing
	stream.close();


	return buffer.str();


}

bool cFile::WriteFileToText(const std::string& path, const std::string text)
{
	std::ofstream stream(path, std::ios::binary | std::ios::trunc);

	if (!stream)
	{
		stream.close();
		return false;
	}

	stream.write((char*)&text[0], (uint32_t)text.size());
	stream.close();


	return true;
}

bool cFile::FileExists(const std::string& path)
{
	std::ifstream f(path);
	return f.good();
		
}
