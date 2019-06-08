#include "hangman.hpp"

// 단어장 초기화 메소드
bool hangman::initwords()
{
    ifstream fin(fd,ios::in);
    try{
        if(!fin.is_open())
            throw "not found file";
    }
    catch(const char* s){
        cout<<s<<": "<<fd<<endl;
        return false;
    }
    string word;
    while(!fin.eof()){
        getline(fin,word);
        words.push_back(word);
    }
    fin.close();
    return true;   
}

// 단어장의 목록중 하나의 단어 선택하는 메소드
void hangman::createword()
{
    index=rand()%words.size();
    word=words.at(index);
    if(wordcount!=NULL){
        delete []wordcount;
    }

   cout<<word<<", "<<word.length()<<endl; // debug

    wordcount=new int[word.length()]();
}

// 단어장 생성이 제대로 됬는지 확인하는 메소드
bool hangman::start()
{
    cout<<"단어장을 생성 중입니다..."<<endl;
    if(initwords()){
        cout<<"단어장을 생성했습니다"<<endl;
        cout<<"단어를 선택했습니다"<<endl;
        cout<<"hangman 게임을 시작합니다"<<endl;
        return true;
    }
    else{
        cout<<"단어장을 생성 실패 했습니다"<<endl;
        cout<<"해당 파일을 찾을 수 없습니다"<<endl;
        cout<<"게임을 종료합니다."<<endl;
        return false;
    }
}

// 유저의 입력을 받는 메소드
char hangman::inputword()
{
    char c;
    while(1){
        try{
            c=cin.get(); cin.ignore();
            if(c>='a' && c<='z')
                break;
            else
                throw "영단어를 입력해주세요";
        }
        catch(const char* s){
            cout<<s<<endl;
        }
    }
    return c;
}

// 유저가 입력한 문자가 단어에 존재하는지 확인하는 메소드
void hangman::findword(char c)
{
    bool check=false;
    int len=word.length();
    for(int i=0;i<len;i++){
        if(c==word[i]){
            check=true;
            wordcount[i]++;
        }  
    }
    if(!check)
        count++;
}

// 현재 상태를 보여주는 메소드
void hangman::showword()
{
    int len=word.length();
    for(int i=0;i<len;i++){
        if(wordcount[i]!=0)
            cout<<word[i];
        else
            cout<<"_";
    }
    cout<<"-> 남은 횟수 : "<<10-count<<", 총 글자 수 : "<<len<<endl;
}

// 단어를 맞췄는지 안 맞췄는지 확인하는 메소드
bool hangman::checkword()
{
    int check=0;
    int len=word.length();
    for(int i=0;i<len;i++){
        if(wordcount[i]!=0)
            check++;
    }
    if(check==word.length())
        return true;
    return false;
}
