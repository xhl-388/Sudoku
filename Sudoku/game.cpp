#include "game.h"
#include "resource_manager.h"
#include <spriterenderer.h>
#include <gameobject.h>
#include <vector>
#include <sudokudata.h>
#include <sudokugenerator.h>
#include <rapidjsonhelper.h>

// 默认渲染器
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
	//加载Shader
	ResourceManager::LoadShader("res/shader/sprite.vs", "res/shader/sprite.fs", nullptr, "sprite");
	//配置Shader
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").use();
	ResourceManager::GetShader("sprite").setInt("image", 0);
	ResourceManager::GetShader("sprite").setMat4("projection", projection);
	//加载Texture
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
	//设置渲染器
	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
	//配置一些静态物体
	staticPic.push_back(GameObject(OFFSET, glm::vec2(9 * SIZE.x, 9 * SIZE.y),
		ResourceManager::GetTexture("background")));
	input_background = GameObject(OFFSET, SIZE, ResourceManager::GetTexture("blue"));
	menu = GameObject(glm::vec2(0, 0), glm::vec2(Width, Height), ResourceManager::GetTexture("menu"));
	win = GameObject(glm::vec2(0, 0), glm::vec2(Width, Height), ResourceManager::GetTexture("win"));
	//配置时间位置
	glm::vec2 offset_t = glm::vec2(OFFSET.x + SIZE.x * 9 + 10, OFFSET.y + 10);
	glm::vec2 size_ti = glm::vec2(SIZE.x / 2, SIZE.y / 2);
	for (int i = 0; i < 3; i++)
		timePic.push_back(NumberObject(0, glm::vec2(offset_t.x + size_ti.x * i, offset_t.y), size_ti));
	for (int i = 3; i < 5; i++)
		timePic.push_back(NumberObject(0, glm::vec2(offset_t.x + size_ti.x * i + 10, offset_t.y), size_ti));
	//进行全局设置
	OverallSet();
}

void Game::Update(GLfloat dt)
{
	//更新时间
	if (State == GameState::GAME_ACTIVE)
		Time += dt;
	RefreshTime();
}

void Game::ProcessInput(GLFWwindow* window)
{
}

void Game::Render()
{
	//渲染游戏内容
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
	else if (State == GameState::GAME_MENU)	//渲染主界面
		menu.Draw(*Renderer);
	else if (State == GameState::GAME_WIN)	//渲染胜利画面
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
	//加载原始数独数据
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
	//加载更多数独数据
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
	if (!doc["FirstInit"].GetBool())	//如果是第一个游玩，进行初始化
	{
		//更改配置文件
		doc["FirstInit"].SetBool(true);
		doc["EasyTime"].SetFloat(0);
		doc["HardTime"].SetFloat(0);
		doc["MiddleTime"].SetFloat(0);
		RapidJsonHelper::WriteDocToFile("config/overall.json", doc);
		//生成三个难度的数独文件
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
	//根据难度把数独保存到对应的文件中
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
	//同一列
	for (int i = 0; i < 9; i++)
		if (Numbers[i][Input_Pos.x].getNumber() == number)
			fault.push_back(glm::ivec2(Input_Pos.x, i));
	//同一行
	for (int i = 0; i < 9; i++)
		if (Numbers[Input_Pos.y][i].getNumber() == number)
			fault.push_back(glm::ivec2(i, Input_Pos.y));
	//同一个正方形
	int x = Input_Pos.x / 3 * 3;
	int y = Input_Pos.y / 3 * 3;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (Numbers[y + i][x + j].getNumber() == number)
				fault.push_back(glm::ivec2(x + j, y + i));
	//无冲突
	if (fault.empty())
	{
		Numbers[Input_Pos.y][Input_Pos.x].setNumber(number);
		Input_State = InputState::INPUT_WAIT;
		//判断是否全部写完了
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
	else//出现冲突
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
	//获得分秒
	int min = iTime / 60;
	int second = iTime % 60;
	//配置数字
	timePic[2].setNumber(min % 10);
	min /= 10;
	timePic[1].setNumber(min % 10);
	min /= 10;
	timePic[0].setNumber(min % 10);
	timePic[4].setNumber(second % 10);
	timePic[3].setNumber(second / 10);
}