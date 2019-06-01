#include <iostream>
#include "Game.hpp"

using namespace std;

// 맵의 크기를 고려해서
// 벽에 부딪쳤는지 안 부딪쳤는지 확인을 함.
bool Human::move_check(int input)
{
    // tmp 변수를 통해 충돌 유무를 판단후
    // 값을 변조를 시킴.
    int tmp;
    switch (input)
    {
            // 왼쪽
        case 1:
            tmp=this->x-this->distance;
            if (tmp < 0)
            {
                cout << "벽에 부딪쳤습니다. 다시 입력해주세요" << endl;
                return  false;
            }
            this->x-=this->distance;
            break;
            // 아래
        case 2:
            tmp=this->y+this->distance;
            if (tmp > 9)
            {
                cout << "벽에 부딪쳤습니다. 다시 입력해주세요" << endl;
                return false;
            }
            this->y += this->distance;
            break;
            // 위
        case 3:
            tmp=this->y-this->distance;
            if (tmp < 0)
            {
                cout << "벽에 부딪쳤습니다. 다시 입력해주세요" << endl;
                return false;
            }
            this->y -= this->distance;
            break;
            // 오른쪽
        case 4:
            tmp=this->x+this->distance;
            if (tmp > 19)
            {
                cout << "벽에 부딪쳤습니다. 다시 입력해주세요" << endl;
                return false;
            }
            this->x +=this->distance;
            break;
        default:
            cout<<"이상한 값을 입력했씁니다. 다시 입력해주세요"<<endl;
            return false;
            break;
    }
    return true;
}

// 맵의 크기를 고려해서
// 벽에 부딪쳤는지 안 부딪쳤는지 확인을 함.
bool Monster::move_check(int input)
{
    // tmp 변수를 통해 충돌 유무를 판단후
    // 값을 변조를 시킴.
    int tmp;
    
    switch (input)
    {
            // 왼쪽
        case 1:
            tmp=this->x-this->distance;
            if (tmp < 0)
            {
                // debug 용 프린트
                cout << "몬스터 벽에 부딪침" << endl;
                return  false;
            }
            this->x -= this->distance;
            break;
            // 아래
        case 2:
            tmp=this->y+this->distance;
            if (tmp > 9)
            {
                // debug 용 프린트
                cout << "몬스터 벽에 부딪침" << endl;
                return false;
            }
            this->y += this->distance;
            break;
            // 위
        case 3:
            tmp=this->y-this->distance;
            if (tmp < 0)
            {
                // debug 용 프린트
                cout << "몬스터 벽에 부딪침" << endl;
                return false;
            }
            this->y -= this->distance;
            break;
            // 오른쪽
        case 4:
            tmp=this->x+this->distance;
            if (tmp > 19)
            {
                // debug 용 프린트
                cout << "몬스터 벽에 부딪침" << endl;
                return false;
            }
            this->x +=this->distance;
            break;
        default:
            break;
    }
    return true;
}

// 맵의 크기를 고려해서
// 벽에 부딪쳤는지 안 부딪쳤는지 확인을 함.
bool Food::move_check(int input)
{
    // tmp 변수를 통해 충돌 유무를 판단후
    // 값을 변조를 시킴.
    int tmp;
    
    switch (input)
    {
            // 왼쪽
        case 1:
            tmp=this->x-this->distance;
            if (tmp < 0)
            {
                // debug용 프린트
                cout << "음식이 벽에 부딪침" << endl;
                return  false;
            }
            this->x -= this->distance;
            break;
            // 아래
        case 2:
            tmp=this->y+this->distance;
            if (tmp > 9)
            {
                // debug용 프린트
                cout << "음식이 벽에 부딪침" << endl;
                return false;
            }
            this->y += this->distance;
            break;
            // 위
        case 3:
            tmp=this->y-this->distance;
            if (tmp < 0)
            {
                // debug용 프린트
                cout << "음식이 벽에 부딪침" << endl;
                return false;
            }
            this->y -= this->distance;
            break;
            // 오른쪽
        case 4:
            tmp=this->x+this->distance;
            if (x > 19)
            {
                // debug용 프린트
                cout << "음식이 벽에 부딪침" << endl;
                return false;
            }
            this->x +=this->distance;
            break;
        default:
            break;
    }
    return true;
}

// 다른 객체와 부딪쳤는지 확인하는 함수.
bool GameObject::collide(GameObject *p)
{
    if (this->x == p->x && this->y == p->y)
        return true;
    else
        return false;
}

// Human 움직임을 구현
void Human::move()
{
    char input;
    int out=0;
    do
    {
        cout << "왼쪽(a), 아래(s), 위(d), 오른쪽(f) >> ";
        cin >> input;
        if(input=='a')
            out=1;
        else if(input=='s')
            out=2;
        else if(input=='d')
            out=3;
        else if(input=='f')
            out=4;
        cin.ignore();
    } while (!move_check(out));
}

// Human의 형태를 리턴함.
char Human::getShape()
{
    return 'H';
}

// Monster 움직임을 구현
void Monster::move()
{
    int ran;
    do {
        ran=rand()%4+1;
    } while(!move_check(ran));
}

// Monster의 형태를 리턴함
char Monster::getShape()
{
    return 'M';
}

// Food 움직임을 구현
void Food::move()
{
    int ran;
    ran=rand()%2;
    
    if(count1+count2==5){
        count1=0; count2=0;
    }
    // 5번중 3번 제자리 체크
    if(ran==0 && count1<3){
        count1++;
        return ;
    }
    // 5번중 2번 움직임 체크
    else{
        if(count2==2){
            count1++;
            return ;
        }
        count2++;
        do{
            ran=rand()%4+1;
        } while(!move_check(ran));
    }
    
}

// Food 형태를 리턴함.
char Food::getShape()
{
    return '@';
}
