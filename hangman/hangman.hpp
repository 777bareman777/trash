#ifndef __HANGMAN_HPP__
#define __HANGMAN_HPP__

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class hangman
{
    private:
        int count; // 남은 횟수
        int index; // 단어장 목록의 단어의 인덱스
        int* wordcount; // 단어를 맞춤 체크 
        vector<string> words; // 단어장 목록
        string word; // 맞춰야할 단어
        string fd; // 오픈할 단어장 파일 이름
    public:
        // 생성자
        hangman(string s) : fd(s), count(0), wordcount(NULL) {}
        // 소멸자
        ~hangman(){
            if(wordcount!=NULL)
                delete []wordcount;
        }
        // 남은 횟수 반환 메소드
        inline int getCount() {return count;}
        // 남은 횟수 설정 메소드
        inline void setCount() {this->count=0;}
        // 단어 반환 메소드
        inline string getWord() {return word;}
        // 단어장 목록 초기화 메소드
        bool initwords();
        // 단어장 목록이 정상적으로 만들어졌는지 확인하는 메소드
        bool start();
        // 단어장 목록에서 랜덤으로 하나의 단어 선택
        void createword();
        // 유저가 문자를 입력할 메소드
        char inputword();
        // 유저가 입력한 문자가 단어에 존재하는지 확인하는 메소드
        void findword(char c);
        // 현재 상태를 확인하는 멕소드
        void showword();
        // 단어를 맞췄는지 안 맞췄는지 확인하는 메소드
        bool checkword();
};


#endif
