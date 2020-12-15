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
	//��һ��JSON�ļ��л�ȡ����
	static std::string GetFileContent(const char* path);
	//��һ��DOM����д��JSON�ļ���
	static void WriteDocToFile(const char* des, rapidjson::Document& document);
};