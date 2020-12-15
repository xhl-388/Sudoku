#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <resource_manager.h>
#include <game.h>
#include <string>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void cursor_position_callback(GLFWwindow* window, double x, double y);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

#pragma region 全局变量

const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 800;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

double Xpos, Ypos;

Game Sudoku(SCR_WIDTH, SCR_HEIGHT);
#pragma endregion

int main()
{
#pragma region 初始化
	//初始化和配置
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	//创建窗体
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Sudoku", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	//注册回调函数
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetKeyCallback(window, key_callback);

	//加载所有函数指针
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Sudoku.Init();
#pragma endregion

#pragma region 渲染循环
	while (!glfwWindowShouldClose(window))
	{
		//时间计算
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//游戏更新
		Sudoku.Update(deltaTime);

		//渲染
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		Sudoku.Render();

		//交换缓冲区
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
#pragma endregion

#pragma region 释放资源
	ResourceManager::Clear();
	//关闭窗口
	glfwTerminate();
	return 0;
#pragma endregion
}

#pragma region 回调函数

//窗口改变回调函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//保证视口正确
	glViewport(0, 0, width, height);
}

//指针移动回调函数
void cursor_position_callback(GLFWwindow* window, double x, double y)
{
	Xpos = x;
	Ypos = y;
}

//鼠标指针点击回调函数
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (Sudoku.State == GameState::GAME_MENU)
		return;
	if (action == GLFW_PRESS)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT)
		{
			Sudoku.Input_State = InputState::INPUT_WAIT;
			int X = static_cast<int>(Xpos - Sudoku.OFFSET.x);
			int Y = static_cast<int>(Ypos - Sudoku.OFFSET.y);
			if (X > 0 && X < Sudoku.SIZE.x * 9 && Y>0 && Y < Sudoku.SIZE.y * 9)
			{
				std::cout << "Xpos:" << Xpos << std::endl << "Ypos:" << Ypos << std::endl;
				int indexX = X / static_cast<int>(Sudoku.SIZE.x);
				int indexY = Y / static_cast<int>(Sudoku.SIZE.y);
				if (Sudoku.Origin_Numbers[indexY][indexX] == 0)
				{
					Sudoku.Input_State = InputState::INPUT_ING;
					Sudoku.SetInputIndex(indexX, indexY);
				}
				else
				{
					Sudoku.Input_State = InputState::INPUT_WAIT;
					std::cout << "Input closed,number now:" <<
						Sudoku.Numbers[indexY][indexX].getNumber() << std::endl;
				}
			}
		}
	}
}

//按键回调函数
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (Sudoku.State == GameState::GAME_ACTIVE) {
		if (action == GLFW_PRESS) {
			if (key == GLFW_KEY_Q)
				Sudoku.ExitGame();
			else if (key >= GLFW_KEY_1 && key <= GLFW_KEY_9)
			{
				int number = key - GLFW_KEY_0;
				std::cout << "Pressed Number:" << number << std::endl;
				if (Sudoku.Input_State == InputState::INPUT_ING)
					Sudoku.PlaceNumber(number);
			}
			else if (key == GLFW_KEY_BACKSPACE)
			{
				if (Sudoku.Input_State == InputState::INPUT_ING)
				{
					auto index{ Sudoku.GetInputIndex() };
					Sudoku.Numbers[index.y][index.x].setNumber(0);
					Sudoku.Input_State = InputState::INPUT_WAIT;
				}
			}
		}
	}
	else if (Sudoku.State == GameState::GAME_MENU)
	{
		if (key == GLFW_KEY_ESCAPE) {
			std::cout << "Program Normally Closed" << std::endl;
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		else if (key >= GLFW_KEY_1 && key <= GLFW_KEY_3)
			Sudoku.EnterGame(key - GLFW_KEY_0);
	}
	else if (Sudoku.State == GameState::GAME_WIN)
		if (key == GLFW_KEY_Q) {
			Sudoku.State = GameState::GAME_MENU;
			Sudoku.Time = 0;
			Sudoku.SaveTimeData();
		}
}

#pragma endregion