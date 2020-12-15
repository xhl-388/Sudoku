#pragma once

#include <vector>

using std::vector;
 
class SudokuGenerator {
public:
	//生成一个数独
	static vector<vector<int>> GenerateSudoku(int level);
private:
	//根据难度对一个数独进行挖坑
	static void DigHoleOnSudoku(vector<vector<int>>& sudoku, int level);
	//批生成随机数
	static vector<int> CreateRandomNums(int min, int max, int num);
	//检测生成合法性
	static bool ShuduCheck(const vector<vector<int>>& shudu, int x, int y);
	//对数独矩阵进行随机混淆
	static void MixNumbers(vector<vector<int>>& target);
};