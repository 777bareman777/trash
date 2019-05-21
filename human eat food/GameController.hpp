#ifndef __Game_Controller_HPP__
#define __Game_Controller_HPP__

#include "Game.hpp"

// 게임의 맵과 Gameobject를 관리하는 handler 클래스 
class GameController
{
    private:
        char map[10][20];
    public:
        // main함수에서 GameObject에 직접적인 접근을 하기 위해서
        // public으로 선언을 해줌.
        Human& h;
        Monster& m;
        Food& f;
    public:
        // Human + Monster + Food 객체
        // 맵을 초기화를 시켜줌.
        GameController(Human& hh,Monster& mm, Food& ff)
        : h(hh), m(mm), f(ff)
        {
            for(int i=0;i<10;i++)
                for(int j=0;j<20;j+=4)
                {
                    map[i][j]='-'; map[i][j+1]='-';
                    map[i][j+2]='-'; map[i][j+3]='-';
                }
        }

        bool Check();   // 게임 시작시 각각의 객체들의 위치 확인
        void Start(); // 게임 시작 알림 
        void ChangeMap(); // 맵을 바꿔줌.
        void DrawMap(); // 맵을 그려줌.
};

#endif
