#include <iostream>
#include <malloc.h>

struct MyListNode
{
    MyListNode *next;
    int data;
};

MyListNode* initMyList();
void printMyList(MyListNode*);
void reverseMyList(MyListNode*&);
void unInitMyList(MyListNode*);

MyListNode* initMyList()
{
    int t_data;
    MyListNode *head = new MyListNode();
    MyListNode *t_cur = head;
    std::cout<<"please input list number:/n"<<std::endl;
    while(std::cin >> t_data)
    {
        if(t_data != '/n')
        {
            std::cout << t_data<<std::endl;
            t_cur->data = t_data;
            t_cur->next = new MyListNode();
            t_cur = t_cur->next;
        }
        else
        {
            break;
        }
    }
    return head;
}

void printMyList(MyListNode *head)
{
    MyListNode *t_cur = head;
    std::cout<<"The List is:";
    while(t_cur)
    {
        std::cout<<t_cur->data<<" ";
        t_cur = t_cur->next;
    }
    std::cout<<std::endl;
}

void unInitMyList(MyListNode *head)
{
    MyListNode *t_del;
    MyListNode *t_cur = head;
    while(t_cur)
    {
        t_del = t_cur;
        std::cout<<"Delete "<<t_del->data<<std::endl;
        t_cur = t_cur -> next;
        delete t_del;
    }
}

/*reverse is cut down old link build new link*/
void reverseMyList(MyListNode *&head)
{
    if (head == NULL or head -> next == NULL)
    {
        return;
    }
    MyListNode *t_pre;
    MyListNode *t_cur;
    MyListNode *t_nex;
    t_cur = head -> next;
    t_pre = head;
    while(t_cur != NULL)
    {
        t_nex = t_cur -> next;
        t_cur -> next = t_pre;
        t_pre = t_cur;
        t_cur = t_nex;
    }
    head -> next = NULL;
    head = t_pre;
}

bool lastNumInList(const MyListNode* const head,int last_num,const MyListNode *&index)
{
    const MyListNode *t_pNum = head;
    index = head;
    while(t_pNum)
    {
        t_pNum = t_pNum -> next;
        last_num -= 1;
        if (last_num == 0)
        {
            break;
        }
    }
    if(last_num != 0) return false;
    while(t_pNum)
    {
        index = index -> next;
        t_pNum = t_pNum ->next;
    }
    return false;
}

/*circle problem*/
/*init a circle*/
bool initCircle(MyListNode* const circle_head)
{
    MyListNode* t_tmp_4;
    MyListNode* t_tmp = const_cast<MyListNode*>(circle_head);
    //circle_head -> next = t_tmp;
    for (int i = 1; i < 10; ++i)
    {
        MyListNode* const t_tmp_1 = (MyListNode*)malloc(sizeof(MyListNode));
        t_tmp_1 -> data = i;
        t_tmp -> next = t_tmp_1;
        t_tmp = t_tmp_1;
        if (4 == i)
        {
            t_tmp_4 = t_tmp_1;
            std::cout << "circle start is " << t_tmp_4 -> data <<std::endl;
        }
    }
    t_tmp -> next = t_tmp_4;
    return true;
}

/*judge circle*/
MyListNode* judgeCircle(const MyListNode* const head)
{
    MyListNode* t_fast = const_cast<MyListNode*>(head);
    MyListNode* t_slow = const_cast<MyListNode*>(head);
    if (head == NULL)
    {
        return NULL;
    }
    while(t_fast -> next -> next)
    {
        t_fast = t_fast ->next -> next;
        //std::cout << "fast" <<t_fast -> data <<std::endl;
        t_slow = t_slow -> next;
        //std::cout << "slow" <<t_slow ->data <<std::endl;
        if (t_fast == t_slow)
        {
            return t_fast;
        }
    }
    return NULL;
}

/*calculation circle length*/
int calCircleLength(MyListNode* const meet_pos)
{
    int t_len = 0;
    MyListNode* t_fast = const_cast<MyListNode*>(meet_pos);
    MyListNode* t_slow = const_cast<MyListNode*>(meet_pos);
    while(t_fast ->next -> next)
    {
        t_fast = t_fast -> next ->next;
        t_slow = t_slow ->next;
        t_len += 1;
        if (t_fast == t_slow)
        {
            return t_len;
        }
    }
    return -1;
}

/*calculation circle start pos*/
MyListNode* calCircleStartNode(MyListNode* circle_head,MyListNode* const meet_pos)
{
    MyListNode* t_fast = const_cast<MyListNode*>(meet_pos);
    MyListNode* t_slow = const_cast<MyListNode*>(circle_head);
    while(meet_pos -> next)
    {
        t_fast = t_fast -> next;
        t_slow = t_slow -> next;
        if (t_fast == t_slow)
        {
            return t_fast;
        }
    }
    return NULL;
}

int main(int argc, char const *argv[])
{
    /* code */
    MyListNode *t_use = initMyList();
    const MyListNode *t_tmp;
    lastNumInList(t_use,2,t_tmp);
    std::cout<<"last_num is "<<(t_tmp->data)<<std::endl;
    reverseMyList(t_use);
    printMyList(t_use);
    unInitMyList(t_use);

    std::cout << "====RING====" << std::endl;
    MyListNode* const circle_head = (MyListNode*)malloc(sizeof(MyListNode));
    circle_head->data = 0;
    initCircle(circle_head);
    //printMyList(circle_head);
    std::cout << "circle meet node is " <<judgeCircle(circle_head) -> data << std::endl;
    std::cout << "circle length is " << calCircleLength(judgeCircle(circle_head)) << std::endl;
    std::cout << "circle start node is " << calCircleStartNode(circle_head,judgeCircle(circle_head)) -> data << std::endl; return 0;
}