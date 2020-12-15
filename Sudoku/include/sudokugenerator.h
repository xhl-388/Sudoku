#pragma once

#include <vector>

using std::vector;
 
class SudokuGenerator {
public:
	//����һ������
	static vector<vector<int>> GenerateSudoku(int level);
private:
	//�����Ѷȶ�һ�����������ڿ�
	static void DigHoleOnSudoku(vector<vector<int>>& sudoku, int level);
	//�����������
	static vector<int> CreateRandomNums(int min, int max, int num);
	//������ɺϷ���
	static bool ShuduCheck(const vector<vector<int>>& shudu, int x, int y);
	//��������������������
	static void MixNumbers(vector<vector<int>>& target);
};