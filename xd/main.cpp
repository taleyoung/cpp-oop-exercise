#include"Header.h"
#include"Class.h"
using namespace std;

int main()
{
    char choice;
    App comp;
    for(;;)
    {
        cout << "**** oop大作业-17130130290 ****" << endl;
        cout<<"请选择你需要的操作:"<<endl;
        cout<<"1.增加数据\t 2.删除数据\t 3.更新数据\t 4.查询数据" << endl;
        cout<<"5.重组文件\t 6.人员统计\t 7.数据存储\t 0.退出" << endl << endl;;
        cin>>choice;
        
        switch(choice){
            case '1': comp.Add(); break;
            case '2': comp.Delete();break;
            case '3': comp.Update();break;
            case '4': comp.Query(); break;
            case '5': comp.Restruct(); break;
            case '6': comp.Acount(); break;
            case '7': comp.Save(); break;
            case '0': exit(0);
            default:    break;
      }
    }
}
