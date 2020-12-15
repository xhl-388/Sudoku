#pragma once

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/prettywriter.h>
#include <string>
#include <fstream>
#include <iostream>

class RapidJsonHelper
{
public:
	//从一个JSON文件中获取内容
	static std::string GetFileContent(const char* path);
	//将一个DOM对象写入JSON文件中
	static void WriteDocToFile(const char* des, rapidjson::Document& document);
};