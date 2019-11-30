//
//  Class.h
//  xd
//
//  Created by tengye on 2019/11/30.
//  Copyright © 2019 taleyoung. All rights reserved.
//

#ifndef Class_h
#define Class_h

#include"Header.h"
using namespace std;

int id;
int Age;
double Amount=0;

class Staff
{
protected:
    int No;
    char Name[20];
    int Age;
    int Post;
    Staff *next;
    

public:
    Staff(char id,char *Name,int Age,int Post)
    {
        this->Post=Post;
        strcpy(this->Name,Name);
        this->No=id;
        this->Age=Age;
    }
    virtual double GetAmount()=0;
    virtual void Output()=0;
    friend class App;
};

class Salesman:virtual public Staff
{
protected:
    double Amount;
public:
    Salesman(char id,char *Name,int Age,int Post,double Amount):Staff(id,Name,Age,Post)
    {
        this->Amount=Amount;
    }

    double GetAmount()
    {
        return Amount;
    }

    void SetAmount(double Amount)
    {
        this->Amount=Amount;
    }

    void Output()
    {
        cout<<No<<"\t"<<Name<<"\t"<<Age<<"\t销售员\t"<<Amount<<endl;
    }
};

class Manager:virtual public Staff
{
public:
    Manager(char id,char *Name,int Age,int Post):Staff(id,Name,Age,Post){}
    void Output()
    {
        cout<<No<<"\t"<<Name<<"\t"<<Age<<"\t经理\t"<<endl;
    }
    double GetAmount()
    {
        return No;
    }
};

class SalesManager:public Manager,public Salesman
{
public:
    SalesManager(char id,char *Name,int Age,int Post):Staff(id,Name,Age,Post),Manager(id,Name,Age,Post),Salesman(id,Name,Age,Post,Amount){}
    
    void Output()
    {
        cout<<No<<"\t"<<Name<<"\t"<<Age<<"\t销售经理\t"<<endl;
    }
    double GetAmount()
    {
        return No;
    }
};


class App
{
private:
    Staff *Worker;
    void Clear();
public:
    App()
    {
        Worker=0;
        Load();
    }
    
    ~App()
    {
        Staff *p;
        p=Worker;
        while(p)
        {
            p=p->next;
            delete Worker;
            Worker=p;
        }
        Worker=0;
    }
    void Add();
    void Delete();
    void Update();
    void Query();
    void Restruct();
    void Acount();
    void Save();
    void Load();
};

void App::Clear()
{
    Staff* p=Worker;
    while(p)
    {
        Worker=p->next;
        delete p;
        p=Worker;
    }
}

void App::Add()
{
    Staff *p;
    int Post;
    char Name[20];
    int Age;
    double Amount;

    cout<<"** 新增员工 **" << endl;
    id++;
    cout<<"输入岗位(1-销售员,2-经理,3-销售经理)：";
    cin>>Post;
    cout<<"输入姓名：";
    cin>>Name;
    cout<<"输入年龄：";
    cin>>Age;
    if(Post==1)
    {
        cout<<"销售额：";
        cin>>Amount;
    }
    switch(Post)
    {
    case 1:p=new Salesman(id,Name,Age,Post,Amount);
        break;
    case 2:p=new Manager(id,Name,Age,Post);
        break;
    case 3:p=new SalesManager(id,Name,Age,Post);
        break;
    }
    p->next=0;

    //新结点加入链表
    if(Worker)
    {
        Staff *p2;
        p2=Worker;
        while(p2->next)
        {
            p2=p2->next;
        }
        p2->next=p;
    }
    else
    {
        Worker=p;
    }
}

void App::Delete()
{
    int No;
    cout<<"** 删除员工 **"<<endl;
    cout<<"id:";
    cin>>No;

    Staff *p1,*p2;
    p1=Worker;

    while(p1)
    {
        if(p1->No==No)
            break;
        else
        {
            p2=p1;
            p1=p1->next;
        }
    }
    if(p1!=NULL)
    {
        p1->Output();
        p1->No=0;
        cout<<"修改成功!"<<endl;
    }
    else
        cout<<"未找到！"<<endl;
}

void App::Update()
{
    int No,Post;
    char Name[20];
    double Amount;

    cout<<"** 修改员工 **" <<endl;;
    cout<<"id:";
    cin>>No;

    //查找要删除的结点
    Staff *p1,*p2;
    p1=Worker;

    while(p1)
    {
        if(p1->No==No)
            break;
        else
        {
            p2=p1;
            p1=p1->next;
        }
    }

    //修改结点
    if(p1!=NULL)
    {
        p1->Output();
        cout<<"修改岗位：(1-销售员,2-经理,3-销售经理)";
        cin>>Post;

        if(p1->Post)
        {
            cout<<"输入姓名：";
            cin>>Name;
            cout<<"输入年龄：";
            cin>>Age;

            if(Post==1)
            {
                cout<<"销售额：";
                cin>>Amount;
            }

            Staff *p3;
            switch(Post)
            {
                case 1:p3=new Salesman(p1->No,Name,Age,Post,Amount);
                break;
                case 2:p3=new Manager(p1->No,Name,Age,Post);
                break;
                case 3:p3=new SalesManager(p1->No,Name,Age,Post);
                break;
            }
            //员工结点替换到链表
            p3->next=p1->next;
            if(p1==Worker)  //若要替换第一个结点
                Worker=p3;
            else //若要删除的结点是后续结点
                p2->next=p3;
        }
        cout<<"修改成功！"<<endl;
    }
    else
        cout<<"未找到！"<<endl;
}

void App::Query()
{
    cout<<"** 查询人员信息 **"<<endl;
    Staff *p=Worker;
    while(p)
    {
        p->Output();
        p=p->next;
    }
}

void App::Restruct()
{
    Staff *p1,*p2;
    p1=Worker;
    while(p1)
    {
        if(p1->No==0)
            break;
        else
        {
            p2=p1;
            p1=p1->next;
        }
    }

    //删除结点
    if(p1!=NULL)
    {
        if(p1==Worker)
        {
            Worker=p1->next;
        }
        else //若要删除的结点是后续结点
        {
            p2->next=p1->next;
        }
        cout<<"重组完成！\n";
    }
    else
        cout<<"重组后没有变化！\n";

}

void App::Acount()
{
    int A=0,B=0,C=0; //A：销售员人数 B：经理人数 C：销售经理人数
    cout<<"** 人员统计 **"<<endl;
    Staff *p=Worker;
    while(p)
    {
        p->Output();
        if(p->Post==1) A++;
        else if(p->Post==2) B++;
        else if(p->Post==3) C++;
        p=p->next;
    }
    cout<<"销售员人数：  "<<setw(3)<<A<<endl;
    cout<<"经理人数：    "<<setw(3)<<B<<endl;
    cout<<"销售经理人数："<<setw(3)<<C<<endl;
}

void App::Save()
{
    ofstream fStaff,fid;
    char c;
    cout<<"保存数据，是否继续？[Y/N]：";
    cin>>c;

    if(toupper(c)!='Y') return;
    //保存人员编号、姓名、年龄、岗位
    fStaff.open("staff.txt",ios::out);
    Staff *p=Worker;
    while(p)
    {
        fStaff<<p->No<<"\t"<<p->Name<<"\t"<<p->Age<<"\t"<<p->Post<<"\t";
        if(p->Post==1)
            fStaff<<p->GetAmount()<<"\t";
        fStaff<<endl;
        p=p->next;
    }
    fStaff.close();
    fid.open("sale.txt",ios::out);
    fid<<"id\t"<<id<<endl;
    fid.close();
    cout<<"\n保存已完成"<<endl;
}

void App::Load()
{
    Clear();
    ifstream fid;
    char buf[20];
    fid.open("id.txt",ios::in);
    fid>>buf>>id;
    fid.close();
    ifstream fStaff;
    Staff *p=Worker;

    int No;
    char Name[20];
    int Age;
    int Post;
    double Amount=0;
    fStaff.open("staff.txt",ios::in);

    //读一条记录
    fStaff>>No>>Name>>Age>>Post;
    if(Post==1)
        fStaff>>Amount;
    while(fStaff.good())
    {
        //创建员工结点
        switch(Post)
        {
            case 1:p=new Salesman(No,Name,Age,Post,Amount);
            break;
            case 2:p=new Manager(No,Name,Age,Post);
            break;
            case 3:p=new SalesManager(No,Name,Age,Post);
            break;
        }
        p->next=0;
        //员工结点加入链表
        if(Worker)
        {
            Staff *p2;
            p2=Worker;
            while(p2->next)
            {
                p2=p2->next;
            }
            p2->next=p;
        }
        else
        {
            Worker=p;
        }

        fStaff>>No>>Name>>Age>>Post;
        if(Post==1)
            fStaff>>Amount;
    }
    fStaff.close();
    cout<<"数据已读出" <<endl;
}


#endif /* Class_h */
