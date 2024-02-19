#ifndef _cFILE_HG
#define _cFILE_HG
#include <fstream>
#include <string>
using FileStream = std::fstream;


class cFile
{
public:
	cFile() = default;


	static std::string ReadFileToString(const std::string& path);
	static bool WriteFileToText(const std::string& path, const std::string text);
	inline static bool FileExists(const std::string& path);
};



#endif // !_cFILE_HG
