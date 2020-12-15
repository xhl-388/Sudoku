#include <sudokugenerator.h>
#include <iostream>
#include <random>
#include <algorithm>

//����һ������
vector<vector<int>> SudokuGenerator::GenerateSudoku(int level)
{
	vector<vector<int>> shudu(9, vector<int>(9, 0));
	//----------------------------------------------
	std::random_device rd;
	int x, y;
	shudu[0][0] = rd() % 9 + 1;

	//�����������ֵ���Ź���
	for (int i = 0; i < 9; i++)
	{
		int a = rd() % 81;
		if (a / 9 != 0 || a % 9 != 0)
			shudu[a / 9][a % 9] = i + 1;
	}

	//���ݷ���������
	bool flag = 1;
	int t = 1;
	while (flag)
	{
		x = t / 9;
		y = t % 9;
		while (flag == 1)
		{
			shudu[x][y]++;
			if (shudu[x][y] > 9)
			{
				shudu[x][y] = 0; //���ݣ��˻ز��Ϸ�����ֵ��������
				t--;
				break;
			}
			else if (ShuduCheck(shudu, x, y))//��ֵ����Ϸ��������һ����
			{
				t++;
				break;
			}
		}
		if (t == 81)
			flag = 0;
	}

	//----------------------------------------------
	DigHoleOnSudoku(shudu, level);
	MixNumbers(shudu);
	return shudu;
}

//�����Ѷȶ�һ�����������ڿ�
void SudokuGenerator::DigHoleOnSudoku(vector<vector<int>>& sudoku, int level)
{
	vector<int> serial;
	if (level == 1)	//���Ѷ�
	{
		serial = { 1,2,6,3,3,3,3,4,4 };
	}
	else if (level == 2)	//�е��Ѷ�
	{
		serial = { 4,5,3,2,4,4,2,6,3 };
	}
	else if (level == 3)	//�����Ѷ�
	{
		serial = { 6,5,6,6,6,6,5,6,6 };
	}
	else
		std::cerr << "NO SUCH DIFFICULTY��:" + level << std::endl;

	std::random_device rd;
	std::mt19937 rng(rd());
	std::shuffle(serial.begin(), serial.end(), rng);
	for (int i = 0; i < 9; i++)
	{
		vector<int> temp = CreateRandomNums(1, 9, serial[i]);
		for (int x : temp)
			sudoku[i][x - 1] = 0;
	}
}

//��������������������
void SudokuGenerator::MixNumbers(vector<vector<int>>& target)
{
	//����һ�����1-9�����ֵ�1-9�����ֵ�ӳ���ϵ�������滻
	vector<int> serial(9);
	for (int i = 0; i < serial.size(); i++)
		serial[i] = i;
	std::random_device rd;
	std::mt19937 rng(rd());
	std::shuffle(serial.begin(), serial.end(), rng);
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			if (target[i][j] != 0)
				target[i][j] = serial[target[i][j] - 1] + 1;
}

//�����������
vector<int> SudokuGenerator::CreateRandomNums(int min, int max, int num)
{
	std::random_device rd;
	vector<int> res;
	res.clear();
	if (max - min + 1 < num)
	{
		return res;
	}
	for (int i = 0; i < num; i++)
	{
		while (true)
		{
			auto temp{ rd() % (max + 1 - min) + min };
			auto iter{ find(res.begin(),res.end(),temp) };
			if (res.end() == iter)
			{
				res.push_back(temp);
				break;
			}
		}
	}
	return res;
}

//������ɵĺϷ���
bool SudokuGenerator::ShuduCheck(const vector<vector<int>>& shudu, int x, int y)
{
	int i, j;
	int temp = shudu[x][y];
	//����ͬһ�����Ƿ����ظ�
	for (i = 0; i < 9; i++)
	{
		if (i != x && shudu[i][y] == temp)
			return false;
	}
	//����ͬһ�����Ƿ����ظ�
	for (j = 0; j < 9; j++)
	{
		if (j != y && shudu[x][j] == temp)
			return false;
	}
	//����С�Ź��������Ƿ����ظ�
	int x0 = (x / 3) * 3;
	int y0 = (y / 3) * 3; //(x0,y0)��(x,y)����С�Ź��������Ͻǵ�һ�������
	for (i = x0; i < x0 + 3; i++)
	{
		for (j = y0; j < y0 + 3; j++)
		{
			if (i != x && j != y && shudu[i][j] == temp)
				return false;
		}
	}
	return true;
}