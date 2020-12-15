#pragma once

#include "glad/glad.h"    
#include <GLFW/glfw3.h>
#include <vector>
#include <gameobject.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


// 代表游戏状态
enum class GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

//代表输入状态
enum class InputState {
    INPUT_ING,
    INPUT_WAIT,
    INPUT_ERROR
};

//游戏类，控制整个游戏的关键数据和逻辑循环
class Game
{
public:
    //游戏时间
    float Time;
    //游戏状态
    GameState  State;
    //游戏难度
    int difficulty;
    InputState Input_State;
    GLuint Width, Height;
    //棋盘偏移量
    const glm::vec2   OFFSET = glm::vec2(20, 20);
    //每个格子的大小
    const glm::vec2   SIZE = glm::vec2(80, 80);
    //储存所有的棋子
    std::vector<std::vector<NumberObject>> Numbers;
    //储存所有原有棋子(不应该在除被初始化以外的时间被修改）
    std::vector<std::vector<int>> Origin_Numbers;
    //构造/析构
    Game(GLuint width, GLuint height);
    ~Game();
    // 初始化游戏状态(加载shader，texture，map)
    void Init();
    //处理输入
    void ProcessInput(GLFWwindow* window);
    //游戏更新
    void Update(GLfloat dt);
    //画面渲染
    void Render();
    //改变输入索引，同时改变背景图片的位置
    void SetInputIndex(int indexX,int indexY);
    //获取输入索引
    glm::ivec2 GetInputIndex() { return Input_Pos; }
    //进入游戏
    void EnterGame(int n);
    //退出游戏
    void ExitGame();
    //写入数字
    void PlaceNumber(int number);
    //保存时间信息
    void SaveTimeData();
private:
    //狗
    GameObject dog;
    //输入背景
    GameObject input_background;
    //原有不可修改数字的背景
    std::vector<GameObject> origin_background;
    //静态图片装饰
    std::vector<GameObject> staticPic;
    //错误提示背景
    std::vector<GameObject> errorPic;
    //时间显示
    std::vector<NumberObject> timePic;
    //输入索引
    glm::ivec2 Input_Pos = glm::ivec2(0, 0);
    //菜单画面
    GameObject menu;
    //胜利画面
    GameObject win;
    //加载数据
    void LoadGameData(int n);
    //全局初始化（包括生成数独文件）
    void OverallSet();
    //保存游戏数据
    void SaveGameData();
    //重新生成当前难度的数独
    void RecreateMap();
    //刷新时间显示
    void RefreshTime();
};