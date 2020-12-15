#include "game.h"
#include "resource_manager.h"
#include <spriterenderer.h>
#include <gameobject.h>
#include <vector>
#include <sudokudata.h>
#include <sudokugenerator.h>
#include <rapidjsonhelper.h>

// Ĭ����Ⱦ��
SpriteRenderer* Renderer;

Game::Game(GLuint width, GLuint height)
	: State(GameState::GAME_MENU), Input_State(InputState::INPUT_WAIT), Width(width), Height(height)
{
}

Game::~Game()
{
	delete Renderer;
}

void Game::Init()
{
	//����Shader
	ResourceManager::LoadShader("res/shader/sprite.vs", "res/shader/sprite.fs", nullptr, "sprite");
	//����Shader
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").use();
	ResourceManager::GetShader("sprite").setInt("image", 0);
	ResourceManager::GetShader("sprite").setMat4("projection", projection);
	//����Texture
	ResourceManager::LoadTexture("res/texture/green.png", "green");
	ResourceManager::LoadTexture("res/texture/blue.png", "blue");
	ResourceManager::LoadTexture("res/texture/red.png", "red");
	ResourceManager::LoadTexture("res/texture/purple.png", "purple");
	ResourceManager::LoadTexture("res/texture/awesomeface.png", "empty");
	ResourceManager::LoadTexture("res/texture/background.png", "background");
	ResourceManager::LoadTexture("res/texture/Number0.png", "Number0");
	ResourceManager::LoadTexture("res/texture/Number1.png", "Number1");
	ResourceManager::LoadTexture("res/texture/Number2.png", "Number2");
	ResourceManager::LoadTexture("res/texture/Number3.png", "Number3");
	ResourceManager::LoadTexture("res/texture/Number4.png", "Number4");
	ResourceManager::LoadTexture("res/texture/Number5.png", "Number5");
	ResourceManager::LoadTexture("res/texture/Number6.png", "Number6");
	ResourceManager::LoadTexture("res/texture/Number7.png", "Number7");
	ResourceManager::LoadTexture("res/texture/Number8.png", "Number8");
	ResourceManager::LoadTexture("res/texture/Number9.png", "Number9");
	ResourceManager::LoadTexture("res/texture/menu.png", "menu");
	ResourceManager::LoadTexture("res/texture/win.png", "win");
	//������Ⱦ��
	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
	//����һЩ��̬����
	staticPic.push_back(GameObject(OFFSET, glm::vec2(9 * SIZE.x, 9 * SIZE.y),
		ResourceManager::GetTexture("background")));
	input_background = GameObject(OFFSET, SIZE, ResourceManager::GetTexture("blue"));
	menu = GameObject(glm::vec2(0, 0), glm::vec2(Width, Height), ResourceManager::GetTexture("menu"));
	win = GameObject(glm::vec2(0, 0), glm::vec2(Width, Height), ResourceManager::GetTexture("win"));
	//����ʱ��λ��
	glm::vec2 offset_t = glm::vec2(OFFSET.x + SIZE.x * 9 + 10, OFFSET.y + 10);
	glm::vec2 size_ti = glm::vec2(SIZE.x / 2, SIZE.y / 2);
	for (int i = 0; i < 3; i++)
		timePic.push_back(NumberObject(0, glm::vec2(offset_t.x + size_ti.x * i, offset_t.y), size_ti));
	for (int i = 3; i < 5; i++)
		timePic.push_back(NumberObject(0, glm::vec2(offset_t.x + size_ti.x * i + 10, offset_t.y), size_ti));
	//����ȫ������
	OverallSet();
}

void Game::Update(GLfloat dt)
{
	//����ʱ��
	if (State == GameState::GAME_ACTIVE)
		Time += dt;
	RefreshTime();
}

void Game::ProcessInput(GLFWwindow* window)
{
}

void Game::Render()
{
	//��Ⱦ��Ϸ����
	if (State == GameState::GAME_ACTIVE) {
		for (auto& back : origin_background)
			back.Draw(*Renderer);
		if (Input_State == InputState::INPUT_ERROR)
			for (auto& g : errorPic)
				g.Draw(*Renderer);
		if (Input_State == InputState::INPUT_ING)
			input_background.Draw(*Renderer);
		for (auto& pic : staticPic)
			pic.Draw(*Renderer);
		for (auto& pic : timePic)
			pic.Draw(*Renderer);
		for (auto& vec : Numbers)
			for (auto& obj : vec)
				if (obj.getNumber() != 0)
					obj.Draw(*Renderer);
	}
	else if (State == GameState::GAME_MENU)	//��Ⱦ������
		menu.Draw(*Renderer);
	else if (State == GameState::GAME_WIN)	//��Ⱦʤ������
		win.Draw(*Renderer);
}

void Game::LoadGameData(int n)
{
	vector<vector<int>> origin;
	std::string content = RapidJsonHelper::GetFileContent("config/overall.json");
	rapidjson::Document d;
	d.Parse(content.c_str());
	switch (n)
	{
	case 1:
		origin = SudokuData::readSudokuFromFile("res/data/EasyMap.txt");
		Time = d["EasyTime"].GetFloat();
		break;
	case 2:
		origin = SudokuData::readSudokuFromFile("res/data/MiddleMap.txt");
		Time = d["MiddleTime"].GetFloat();
		break;
	case 3:
		origin = SudokuData::readSudokuFromFile("res/data/HardMap.txt");
		Time = d["HardTime"].GetFloat();
		break;
	default:
		std::cerr << "Invalid input:" << n << std::endl;
		break;
	}
	//����ԭʼ��������
	Origin_Numbers = vector<vector<int>>(9, vector<int>(9));
	Numbers = vector<vector<NumberObject>>(9, vector<NumberObject>(9));
	origin_background.clear();
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
		{
			Origin_Numbers[i][j] = origin[i][j];
			if (origin[i][j] != 0)
				origin_background.push_back(GameObject(glm::vec2(OFFSET.x + j * SIZE.x,
					OFFSET.y + i * SIZE.y), SIZE, ResourceManager::GetTexture("green")));
		}
	//���ظ�����������
	switch (n)
	{
	case 1:
		origin = SudokuData::readSudokuFromFile("res/data/MoreEasyMap.txt");
		break;
	case 2:
		origin = SudokuData::readSudokuFromFile("res/data/MoreMiddleMap.txt");
		break;
	case 3:
		origin = SudokuData::readSudokuFromFile("res/data/MoreHardMap.txt");
		break;
	default:
		std::cerr << "Invalid input:" << n << std::endl;
		break;
	}
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			Numbers[i][j] = NumberObject
			(origin[i][j], glm::vec2(OFFSET.x + j * SIZE.x, OFFSET.y + i * SIZE.y), SIZE);
	Input_State = InputState::INPUT_WAIT;
}

void Game::SetInputIndex(int indexX, int indexY)
{
	Input_Pos.x = indexX;
	Input_Pos.y = indexY;
	input_background.Position = glm::vec2
	(OFFSET.x + Input_Pos.x * SIZE.x, OFFSET.y + Input_Pos.y * SIZE.y);
}

void Game::OverallSet()
{
	std::string jcontent = RapidJsonHelper::GetFileContent("config/overall.json");
	rapidjson::Document doc;
	doc.Parse(jcontent.c_str());
	if (!doc["FirstInit"].GetBool())	//����ǵ�һ�����棬���г�ʼ��
	{
		//���������ļ�
		doc["FirstInit"].SetBool(true);
		doc["EasyTime"].SetFloat(0);
		doc["HardTime"].SetFloat(0);
		doc["MiddleTime"].SetFloat(0);
		RapidJsonHelper::WriteDocToFile("config/overall.json", doc);
		//���������Ѷȵ������ļ�
		vector<vector<int>> temp = SudokuGenerator::GenerateSudoku(1);
		SudokuData::inputSudokuToFile(temp, "res/data/EasyMap.txt");
		SudokuData::inputSudokuToFile(temp, "res/data/MoreEasyMap.txt");
		temp = SudokuGenerator::GenerateSudoku(2);
		SudokuData::inputSudokuToFile(temp, "res/data/MiddleMap.txt");
		SudokuData::inputSudokuToFile(temp, "res/data/MoreMiddleMap.txt");
		temp = SudokuGenerator::GenerateSudoku(3);
		SudokuData::inputSudokuToFile(temp, "res/data/HardMap.txt");
		SudokuData::inputSudokuToFile(temp, "res/data/MoreHardMap.txt");
	}
}

void Game::SaveGameData()
{
	vector<vector<int>> save(9, vector<int>(9));
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			save[i][j] = Numbers[i][j].getNumber();
	//�����ѶȰ��������浽��Ӧ���ļ���
	switch (difficulty)
	{
	case 1:
		SudokuData::inputSudokuToFile(save, "res/data/MoreEasyMap.txt");
		break;
	case 2:
		SudokuData::inputSudokuToFile(save, "res/data/MoreMiddleMap.txt");
		break;
	case 3:
		SudokuData::inputSudokuToFile(save, "res/data/MoreHardMap.txt");
		break;
	default:
		break;
	}
	SaveTimeData();
}

void Game::SaveTimeData()
{
	std::string content = RapidJsonHelper::GetFileContent("config/overall.json");
	rapidjson::Document d;
	d.Parse(content.c_str());
	switch (difficulty)
	{
	case 1:
		d["EasyTime"].SetFloat(Time);
		break;
	case 2:
		d["MiddleTime"].SetFloat(Time);
		break;
	case 3:
		d["HardTime"].SetFloat(Time);
		break;
	default:
		break;
	}
	RapidJsonHelper::WriteDocToFile("config/overall.json", d);
}

void Game::EnterGame(int n)
{
	difficulty = n;
	LoadGameData(n);
	State = GameState::GAME_ACTIVE;
}

void Game::ExitGame()
{
	SaveGameData();
	State = GameState::GAME_MENU;
}

void Game::PlaceNumber(int number)
{
	vector<glm::ivec2> fault;
	//ͬһ��
	for (int i = 0; i < 9; i++)
		if (Numbers[i][Input_Pos.x].getNumber() == number)
			fault.push_back(glm::ivec2(Input_Pos.x, i));
	//ͬһ��
	for (int i = 0; i < 9; i++)
		if (Numbers[Input_Pos.y][i].getNumber() == number)
			fault.push_back(glm::ivec2(i, Input_Pos.y));
	//ͬһ��������
	int x = Input_Pos.x / 3 * 3;
	int y = Input_Pos.y / 3 * 3;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (Numbers[y + i][x + j].getNumber() == number)
				fault.push_back(glm::ivec2(x + j, y + i));
	//�޳�ͻ
	if (fault.empty())
	{
		Numbers[Input_Pos.y][Input_Pos.x].setNumber(number);
		Input_State = InputState::INPUT_WAIT;
		//�ж��Ƿ�ȫ��д����
		bool flag = true;
		for (auto& vec : Numbers)
			for (auto& n : vec)
				if (n.getNumber() == 0)
					flag = false;
		if (flag)
		{
			State = GameState::GAME_WIN;
			RecreateMap();
		}
	}
	else//���ֳ�ͻ
	{
		errorPic.clear();
		for (auto& pos : fault)
			errorPic.push_back(GameObject(glm::vec2(OFFSET.x + pos.x * SIZE.x,
				OFFSET.y + pos.y * SIZE.y), SIZE, ResourceManager::GetTexture("red")));
		Input_State = InputState::INPUT_ERROR;
	}
}

void Game::RecreateMap()
{
	vector<vector<int>> temp = SudokuGenerator::GenerateSudoku(difficulty);
	switch (difficulty)
	{
	case 1:
		SudokuData::inputSudokuToFile(temp, "res/data/EasyMap.txt");
		SudokuData::inputSudokuToFile(temp, "res/data/MoreEasyMap.txt");
		break;
	case 2:
		SudokuData::inputSudokuToFile(temp, "res/data/MiddleMap.txt");
		SudokuData::inputSudokuToFile(temp, "res/data/MoreMiddleMap.txt");
		break;
	case 3:
		SudokuData::inputSudokuToFile(temp, "res/data/HardMap.txt");
		SudokuData::inputSudokuToFile(temp, "res/data/MoreHardMap.txt");
		break;
	default:
		break;
	}
}

void Game::RefreshTime()
{
	int iTime = static_cast<int>(Time);
	//��÷���
	int min = iTime / 60;
	int second = iTime % 60;
	//��������
	timePic[2].setNumber(min % 10);
	min /= 10;
	timePic[1].setNumber(min % 10);
	min /= 10;
	timePic[0].setNumber(min % 10);
	timePic[4].setNumber(second % 10);
	timePic[3].setNumber(second / 10);
}