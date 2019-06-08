#include "SinglerLinkedList.hpp"

// 싱글 링크드 리스트 유저 추가
// check 변수를 통해 성공시 성공 카운트 증가
// 실패시 실패 카운트 증가
void Linkedlist::addNode(const string s,const bool check)
{
    Node *newNode=new Node(s);
    size++;
    if(head==NULL){
        head=newNode;
        if(check)
            head->success_count++;
        else
            head->fail_count++;
        
    }
    else{
        Node* cur=head;
        while(cur){
            if(cur->next==NULL){
                cur->next=newNode;
                if(check)
                    cur->next->success_count++;
                else
                    cur->next->fail_count++;             
                break;
            }
            cur=cur->next;
        }
    }
}

// 싱글 링크드 리스트에서 이미 존재하는 유저 찾기
bool Linkedlist::findNode(const string s,int& idx)
{
    Node* cur=head;
    while(cur){
        if(cur->name==s)
            return true;
        idx++;
        cur=cur->next;
    }
    return false;
}

// 싱글 링크드 리스트에 존재하는 유저의 값 변경
// idx 변수를 통해 유저에 접근 -> findNode에서 얻은 인덱스값 활용
// check 변수를 통해 성공시 성공 카운트 증가, 실패시 실패 카운트 증가
void Linkedlist::changeNode(const string s,const int idx,const bool check)
{
    Node* cur=head;
    for(int i=0;i<idx;i++)
        cur=cur->next;
    cur->total_count++;
    if(check)
        cur->success_count++;
    else
        cur->fail_count++;
}

// 현재 유저 목록 출력
void Linkedlist::printList()
{
    if(head==0) cout<<"유저 목록이 없습니다"<<endl;

    Node* cur=head;
    while(cur){
        cout<<"유저 이름 : "<<cur->name<<endl;
        cout<<"횟수 : "<<cur->total_count<<endl;
        cout<<"성공 횟수 : "<<cur->success_count<<endl;
        cout<<"실패 횟수 : "<<cur->fail_count<<endl;
        cout<<"성공률 : "<<cur->ratio<<endl;
        cur=cur->next;
    }
    cout<<"총 "<<size<<" 명의 유저가 존재"<<endl;
    return ;
}

// 성공률 계산
void Linkedlist::calRatio()
{
    Node* cur=head;
    while(cur){
        cur->ratio=((float)cur->success_count/(float)cur->total_count)*100;
        cur=cur->next;
    }
}

// 유저들을 성공률 기준으로 내림차순 정렬함
void Linkedlist::sortList()
{
    int swapped, i;
    Node* ptr;
    Node* lptr=NULL;

    do{
        swapped=0;
        ptr=head;
        while(ptr->next != lptr){
            if(ptr->ratio<=ptr->next->ratio)
            {
                string n=ptr->name;
                int t=ptr->total_count;
                int s=ptr->success_count;
                int f=ptr->fail_count;
                float r=ptr->ratio;
                ptr->name=ptr->next->name;
                ptr->total_count=ptr->next->total_count;
                ptr->success_count=ptr->next->success_count;
                ptr->fail_count=ptr->next->fail_count;
                ptr->ratio=ptr->next->ratio;
                ptr->next->name=n;
                ptr->next->total_count=t;
                ptr->next->success_count=s;
                ptr->next->fail_count=f;
                ptr->next->ratio=r;
                swapped=1;
            }
            ptr=ptr->next;
        }
        lptr=ptr;
    } while(swapped);
}
