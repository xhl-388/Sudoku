#pragma once

#include "glad/glad.h"    
#include <GLFW/glfw3.h>
#include <vector>
#include <gameobject.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


// ������Ϸ״̬
enum class GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

//��������״̬
enum class InputState {
    INPUT_ING,
    INPUT_WAIT,
    INPUT_ERROR
};

//��Ϸ�࣬����������Ϸ�Ĺؼ����ݺ��߼�ѭ��
class Game
{
public:
    //��Ϸʱ��
    float Time;
    //��Ϸ״̬
    GameState  State;
    //��Ϸ�Ѷ�
    int difficulty;
    InputState Input_State;
    GLuint Width, Height;
    //����ƫ����
    const glm::vec2   OFFSET = glm::vec2(20, 20);
    //ÿ�����ӵĴ�С
    const glm::vec2   SIZE = glm::vec2(80, 80);
    //�������е�����
    std::vector<std::vector<NumberObject>> Numbers;
    //��������ԭ������(��Ӧ���ڳ�����ʼ�������ʱ�䱻�޸ģ�
    std::vector<std::vector<int>> Origin_Numbers;
    //����/����
    Game(GLuint width, GLuint height);
    ~Game();
    // ��ʼ����Ϸ״̬(����shader��texture��map)
    void Init();
    //��������
    void ProcessInput(GLFWwindow* window);
    //��Ϸ����
    void Update(GLfloat dt);
    //������Ⱦ
    void Render();
    //�ı�����������ͬʱ�ı䱳��ͼƬ��λ��
    void SetInputIndex(int indexX,int indexY);
    //��ȡ��������
    glm::ivec2 GetInputIndex() { return Input_Pos; }
    //������Ϸ
    void EnterGame(int n);
    //�˳���Ϸ
    void ExitGame();
    //д������
    void PlaceNumber(int number);
    //����ʱ����Ϣ
    void SaveTimeData();
private:
    //��
    GameObject dog;
    //���뱳��
    GameObject input_background;
    //ԭ�в����޸����ֵı���
    std::vector<GameObject> origin_background;
    //��̬ͼƬװ��
    std::vector<GameObject> staticPic;
    //������ʾ����
    std::vector<GameObject> errorPic;
    //ʱ����ʾ
    std::vector<NumberObject> timePic;
    //��������
    glm::ivec2 Input_Pos = glm::ivec2(0, 0);
    //�˵�����
    GameObject menu;
    //ʤ������
    GameObject win;
    //��������
    void LoadGameData(int n);
    //ȫ�ֳ�ʼ�����������������ļ���
    void OverallSet();
    //������Ϸ����
    void SaveGameData();
    //�������ɵ�ǰ�Ѷȵ�����
    void RecreateMap();
    //ˢ��ʱ����ʾ
    void RefreshTime();
};