#include <rapidjsonhelper.h>

std::string RapidJsonHelper::GetFileContent(const char* path)
{
	std::ifstream ifs(path);
	if (!ifs.is_open())
		std::cerr << "CANT OPEN FILE:" << path << std::endl;
	std::string jcontent((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
	ifs.close();
	return jcontent;
}

void RapidJsonHelper::WriteDocToFile(const char* des, rapidjson::Document& document)
{
	rapidjson::StringBuffer buffer;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	std::string temp(buffer.GetString());
	std::ofstream ofs(des);
	if (!ofs.is_open())
		std::cerr << "CANT OPEN FILE:" << des << std::endl;
	ofs << temp;
	ofs.close();
}