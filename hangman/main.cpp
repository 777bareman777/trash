#include "./gameController.hpp"

int main()
{
    // 시드 초기화
    srand(time(NULL));
    // hangman 클래스 초기화
    hangman h("words.txt");
    // 유저 목록 클래스 초기화
    Linkedlist l;
    // hangmang, 유저 목록 클래스를 관리할 매니저 클래스
    gameController gc(h, l);

    // 게임을 정상적으로 시작할 수 있는지 체크를함.
    // 1번을 통해 게임을 시작할 수 있고,
    // 2번을 통해 게임을 종료 및 명예의 전당을 기록함.
    // 3번을 통해 현재 유저 기록을 확인할 수 있음.
    gc.introduction();
    if (!gc.hm.start())
        return 0;
    while (true)
    {
        cout << "1번 게임시작, 2번 게임종료, 3번 현재 유저 기록" << endl;
        int input=0;
        cin >> input; cin.ignore();
        switch (input)
        {
        case 1:
        {
            cout << "지금부터 시작하겠습니다 " << endl;
            cout << "유저 이름을 입력해주세요 >> ";
            string s;
            getline(cin, s);
            int idx = 0;
            bool check = false;
            gc.hm.createword();
            while (true)
            {
                gc.hm.showword();
                char c = gc.hm.inputword();
                gc.hm.findword(c);
                if (gc.hm.checkword() && gc.hm.getCount() <= 10)
                {
                    cout << "게임 승리" << endl;
                    gc.hm.setCount();
                    check = true;
                    if (gc.ll.findNode(s, idx))
                    {
                        cout << "1" << endl;
                        gc.ll.changeNode(s, idx, check);
                    }
                    else
                    {
                        cout << "2" << endl;
                        gc.ll.addNode(s, check);
                    }
                    break;
                }
                if (gc.hm.getCount() > 9)
                {
                    cout << "정답은 " << gc.hm.getWord() << " 입니다." << endl;
                    cout << "게임 실패" << endl;
                    gc.hm.setCount();
                    check = false;
                    if (gc.ll.findNode(s, idx))
                    {
                        gc.ll.changeNode(s, idx, check);
                    }
                    else
                    {
                        gc.ll.addNode(s, check);
                    }
                    break;
                }
            }
            break;
        }
        case 2:
        {
            gc.ll.calRatio();
            gc.ll.sortList();
            cout << "명예의 전당 파일 기록중" << endl;
            gc.ofstream_open(gc.getString());
            gc.ofstream_write();
            gc.ofstream_close();
            cout<<"명예의 전당 파일 기록 완료"<<endl;
            cout<<"명에의 전당 파일 불러오기"<<endl;
            gc.ifstream_open(gc.getString());
            gc.ifstream_read();
            gc.ifstream_close();
            cout<<"명예의 전당 파일 불러오기 완료"<<endl;
            cout << "게임 종료" << endl;
            return 0;
        }
        case 3:
        {
            gc.ll.calRatio();
            gc.ll.sortList();
            gc.ll.printList();
            break;
        }
        default:
        {
            cin.clear(); cin.ignore();
            break;
        }
        }
    }
}
