#include <iostream>
#include "GameController.hpp"
using namespace std;

// 게임 시작시 각각의 객체들이 동일한 위치에 생성이 된다면
// 게임을 종료시키는 메소드
bool GameController::Check()
{
    if(h.getX()==m.getX() && h.getY()==m.getY()){
        cout<<"휴먼과 몬스터의 위치가 동일합니다."<<endl;
        cout<<"게임종료"<<endl;
        return false;     
    }
    else if(h.getX()==f.getX() && h.getY()==f.getY()){
        cout<<"휴먼과 음식의 위치가 동일합니다."<<endl;
        cout<<"게임종료"<<endl;
        return false;
    }
    else if(m.getX()==f.getX() && m.getY()==f.getY()){
        cout<<"몬스터와 음식의 위치가 동일합니다."<<endl;
        cout<<"게임종료"<<endl;
        return false;
    }
    return true;
}

// 게임 시작을 알리는 메소드
void GameController::Start()
{
    cout<<"명품 c++ 프로그래밍 책에 있는 Open Challenge 문제입니다"<<endl;
    cout<<"코드 오류 및 수정 사항이 있다면, 777bareman777@gmail.com으로 문의 해주시기 바랍니다."<<endl<<endl;
    cout<<"** Human의 Food 먹기 게임을 시작합니다. **"<<endl;
}

// 각각의 객체들의 위치 정보를 받아서,
// 맵을 바꿔주고 있다.
// loop unrooling을 통해 맵의 정보를 바꾸는 속도를 향상시킴.
void GameController::ChangeMap()
{
    for(int i=0;i<10;i++)
        for(int j=0;j<20;j+=4)
        {
            map[i][j]='-'; map[i][j+1]='-';
            map[i][j+2]='-'; map[i][j+3]='-';
        }
    int x,y; // 행 과 열을 표현할 변수

    // food 위치 설정
    x=f.getX();y=f.getY();
    map[y][x]=f.getShape();

    // human 위치 설정
    x=h.getX(); y=h.getY();
    map[y][x]=h.getShape();

    // monster 위치 설정
    x=m.getX(); y=m.getY();
    map[y][x]=m.getShape();
}

// loop unrooling을 통해 맵을 그리는 속도를 향상시킴.
void GameController::DrawMap()
{
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<20;j+=4)
        {
            cout<<map[i][j]<<map[i][j+1]
            <<map[i][j+2]<<map[i][j+3];
        }
        cout<<endl;
    }
}
