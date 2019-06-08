#ifndef __SINGLE_LINKED_LIST_HPP__
#define __SINGLE_LINKED_LIST_HPP__

#include <iostream>
#include <string>
using namespace std;

// 노드 클래스
class Node
{
    friend class Linkedlist;
    friend class gameController;
    private:
        string name; // 유저 이름
        int total_count; // 도전 횟수
        int success_count; // 성공 횟수
        int fail_count; // 실패 횟수
        float ratio; // 성공 비율
        Node* next;
    public:
        // 생성자
        Node(string s)
        : name(s), total_count(1), success_count(0), fail_count(0), ratio(0)
        {this->next=NULL;}
        // 소멸자
        ~Node();
};

// 리스트 클래스
class Linkedlist
{
    public:
        Node *head; // 노드의 첫부분
        int size; // 리스트의 크기 
        //생성자
        Linkedlist(){
            head=NULL; size=0;
        }
        // 리스트에 유저 추가
        void addNode(const string n,const bool check);
        // 리스트에서 유저 찾기
        bool findNode(const string n,int& idx);
        // 유저목록 출력
        void printList();
        // 유저 값 변경
        void changeNode(const string n,const int idx, const bool check);
        // 성공율 계산
        void calRatio();
        // 내림차순 정렬
        void sortList();
};

#endif
