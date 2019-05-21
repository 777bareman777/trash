#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include "Game.hpp"
#include "GameController.hpp"

using namespace std;

int main()
{
    int randX, randY;
    // Human, Monster, Food의 위치를 항상 랜덤하게 나타나게 만듬.
    srand(time(NULL));
    
    // human 위치 초기화
    randX=rand()%20;randY=rand()%10;
    Human h1(randX,randY);

    // monster 위치 초기화
    randX=rand()%20;randY=rand()%10;
    Monster m1(randX,randY);

    // food 위치 초기화
    randX=rand()%20;randY=rand()%10;
    Food f1(randX,randY);

    // GameController 생성
    GameController gc(h1,m1,f1);

    // 게임 시작 부분
    if(!gc.Check())
        return 0;
    gc.Start();
    while(1){
        // 맵의 정보를 바구고 맵을 그림.
        gc.ChangeMap();
        gc.DrawMap();
        // 게임 오버
        if(gc.h.collide(&gc.m) || gc.m.collide(&gc.f))
        {
            cout<<"Monster is winner!!"<<endl;
            return 0;
        }
        // 게임 승리
        else if (gc.h.collide(&gc.f))
        {
            cout<<"Human is winnder!!"<<endl;
            return 0;
        }
        // 각각 객체들이 human, monster, food 순으로 움직임.
        gc.h.move();
        gc.m.move();
        gc.f.move();
    }
}
