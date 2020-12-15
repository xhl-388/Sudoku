#include <sudokudata.h>

vector<vector<int>> SudokuData::readSudokuFromFile(const std::string& path)
{
	vector<vector<int>> origin(9, vector<int>(9));
	std::ifstream is;
	is.open(path.c_str());
	if (!is.is_open())
		std::cerr << "Fail to open file:" + path << std::endl;
	int num;
	int count = 0;
	while (is >> num)
	{
		origin[count / 9][count % 9] = num;
		count++;
	}
	is.close();
	return origin;
}

void SudokuData::inputSudokuToFile(const vector<vector<int>>& sudoku, const std::string& path)
{
	std::ofstream os;
	os.open(path.c_str());
	if (!os.is_open())
		std::cerr << "Fail to open file:" + path << std::endl;
	for (int i = 0; i < 81; i++)
	{
		os << sudoku[i / 9][i % 9] << " ";
	}
	os.close();
}