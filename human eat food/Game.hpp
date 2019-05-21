#ifndef __GAME_HPP__
#define __GAME_HPP__

class GameObject
{
    protected:
        int distance; // 한번 이동 거리
        int x,y; // 현재 위치 x: 왼쪽, 오른쪽 y: 위,아래
    public:
        // 초기 위치와 이동거리 설정
        GameObject(int startX,int startY, int distance)
        : x(startX),y(startY) { this->distance=distance; }
        ~GameObject() {};
        
        // 이동한  후 새로윈 위치로, x,y 변경
        virtual void move()=0;
        // 벽에 충돌 여부를 판단하는 메소드
        virtual bool move_check(int input)=0;
        // 객체의 모양을 아타내는 문자 리턴
        virtual char getShape()=0;

        // x,y값을 리턴하는 함수
        inline int getX() { return x; }
        inline int getY() { return y; }

        // 이 객체가 객체 p와 충돌했으면 true 리턴
        bool collide(GameObject *p);
};

// GameObject 클래스를 상속 받은 Human 클래스
class Human : public GameObject
{
    public:
        // Human 객체는 한번 이동 거리가 1 이므로
        // 다음과 같이 생성자를 만들어줌.
        Human(int startX, int startY) 
        : GameObject(startX,startY,1) {}
        ~Human() {};

        virtual void move();
        virtual bool move_check(int input);
        virtual char getShape();
};

// GameObject 클래스를 상속 받은 Monster 클래스
class Monster : public GameObject
{
    public:
        // Monster 객체는 한번 이동 거리가 2이므로
        // 다음과 같이 생성자를 만들어줌.
        Monster(int startX, int startY) 
        : GameObject(startX,startY,2) {}
        ~Monster() {};

        virtual void move();
        virtual bool move_check(int input);
        virtual char getShape();
};

// GameObject 클래스를 상속 받은 Food 클래스
class Food : public GameObject
{
    private:
        int count1; // 5번중 3번 제자리
        int count2; // 5번중 2번 움직이기
    public:
        // Food 객체는 한번 이동거리가 1이므로
        // 다음과 같이 생성자를 만들어줌.
        Food(int startX, int startY) 
        : GameObject(startX,startY,1), count1(0),count2(0) {}
        ~Food() {};

        virtual void move();
        virtual bool move_check(int input);
        virtual char getShape();
};

#endif
