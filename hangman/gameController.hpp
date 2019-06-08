#ifndef __GAME_CONTROLLER_HPP__
#define __GAME_CONTROLLER_HPP__

#include "./hangman.hpp"
#include "./SinglerLinkedList.hpp"

class gameController
{
    private:
        string file; // 파일 이름
        ifstream fin; // 입력스트림
        ofstream fout; // 출력스트림
    public:
        hangman hm; // hangman class
        Linkedlist ll; // 유저수 관리 class
    public:
        // 생성자
        gameController(hangman& h, Linkedlist& l) : hm(h), ll(l) {
            this->file="record.txt";
        }
        // 소멸자
        ~gameController() {}
        // 소개메소드
        void introduction();
        // 스트링 반환 함수
        inline string getString() {return file;}
        // 입력스트림 오픈
        void ifstream_open(string s) {fin.open(file,ios::in);}
        // 출력스트림 오픈
        void ofstream_open(string s) {fout.open(file,ios::out);}
        // 입력스트림 닫기
        void ifstream_close() {fin.close();}
        // 출력스트림 닫기
        void ofstream_close() {fout.close();}
        // 출력스트림 쓰기
        void ofstream_write();
        // 입력스트림 읽기
        void ifstream_read();

};

// 소개 메소드
void gameController::introduction()
{
    cout<<"이 프로그램은 hangman 게임입니다"<<endl;
    cout<<"hangman 게임은 영어 단어장에서 하나의 단어를 임의로 골라 전체 글자 수를 보여주고 사용자가 단어에 포함된 글자를 하나씩 맞추는 게임입니다."<<endl;
    cout<<"성공율을 기준으로 상위 득점자 5명의 이름을 명예의 전당에 기록합니다"<<endl;
    cout<<"명예의 전당에 오르시길 바랍니다"<<endl;
    cout<<"프로그램 문의는 777bareman777@gmail.com으로 해주시기 바랍니다."<<endl;
}

// 출력스트림 쓰기 
void gameController::ofstream_write()
{
    int i=1;
    Node* cur=ll.head;
    while(cur && i<=5){
        fout<<"**********************"<<endl;
        fout<<i<<" 등"<<endl;
        fout<<"유저 이름 : "<<cur->name;
        fout<<"횟수 : "<<cur->total_count<<endl;
        fout<<"성공 횟수 : "<<cur->success_count<<endl;
        fout<<"실패 횟수 : "<<cur->fail_count<<endl;
        fout<<"성공률 : "<<cur->ratio<<endl;
        i++;
        cur=cur->next;
    }
}

// 입력스트림 읽기
void gameController::ifstream_read()
{
    string s;
    while(!fin.eof()){
        getline(fin,s);
        cout<<s<<endl;
    }
}

#endif
