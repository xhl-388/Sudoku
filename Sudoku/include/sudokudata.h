#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using std::vector;

class SudokuData {
public:
	//��һ��ָ�����ļ��ж�ȡ����
	static vector<vector<int>> readSudokuFromFile(const std::string& path);

	//��һ����������д�뵽һ��ָ�����ļ���
	static void inputSudokuToFile(const vector<vector<int>>& sudoku, const std::string& path);
};