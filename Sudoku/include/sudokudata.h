#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using std::vector;

class SudokuData {
public:
	//从一个指定的文件中读取数独
	static vector<vector<int>> readSudokuFromFile(const std::string& path);

	//将一个数独数据写入到一个指定的文件中
	static void inputSudokuToFile(const vector<vector<int>>& sudoku, const std::string& path);
};