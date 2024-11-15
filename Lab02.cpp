#include <iostream>
#include <string>
#include <string.h>

using namespace std;

// I. Danh sách liên kết
/*
struct NODE
{
    int key;
    NODE *p_next;
};

struct List
{
    NODE *p_head;
    NODE *p_tail;
};

// 1. tạo một NODE
NODE *createNODE(int data)
{
    NODE *newNODE = new (nothrow) NODE;
    if (newNODE == nullptr)
    {
        return nullptr;
    }

    newNODE->key = data;
    newNODE->p_next = nullptr;

    return newNODE;
}
// 2. Khởi tạo List
List *createList(NODE *p_NODE)
{
    List *newlist = new (nothrow) List;
    if (newlist == nullptr)
    {
        return nullptr;
    }

    newlist->p_head = p_NODE;
    newlist->p_tail = p_NODE;

    return newlist;
}
// 3. Chèn vào đầu một list
bool addHead(List *&L, int data)
{
    NODE *p = createNODE(data);
    if (p == nullptr)
    {
        return false;
    }
    if (L->p_head == nullptr)
    {
        L->p_head = p;
        L->p_tail = p;
    }
    else
    {
        p->p_next = L->p_head;
        L->p_head = p;
    }
    return true;
}
// 4. Chèn vào cuối List
bool addTail(List *&L, int data)
{
    NODE *p = createNODE(data);
    if (p == nullptr)
    {
        return false;
    }
    if (L->p_head == nullptr)
    {
        L->p_head = p;
        L->p_tail = p;
    }
    else
    {
        L->p_tail->p_next = p;
        L->p_tail = p;
    }
    return true;
}
// 5. Xóa NODE đầu tiên
void removeHead(List *&L)
{
    if (L->p_head == nullptr)
    {
        return;
    }
    if (L->p_head == L->p_tail)
    {
        delete L->p_head;
        L->p_head = nullptr;
        L->p_tail = nullptr;
        return;
    }

    NODE *p = L->p_head;
    L->p_head = p->p_next;
    delete p;
    p = nullptr;
}
// 6. Xóa NODE cuối cùng
void removeTail(List *&L)
{
    if (L->p_head == nullptr)
    {
        return;
    }
    if (L->p_head == L->p_tail)
    {
        delete L->p_head;
        L->p_head == nullptr;
        L->p_tail == nullptr;
        return;
    }

    NODE *p = L->p_head;
    // tìm nút trước nút cuối
    while (p->p_next != L->p_tail)
    {
        p = p->p_next;
    }
    p->p_next = nullptr;
    delete L->p_tail;
    L->p_tail = nullptr;
    L->p_tail = p;
}
// 7. Xóa tất cả các NODE
void removeAll(List *&L)
{
    NODE *p = L->p_head;
    NODE *q = nullptr;
    while (p != nullptr)
    {
        q = p;
        p = p->p_next;
        delete q;
    }
    L->p_head = nullptr;
    L->p_tail = nullptr;
}
// 8. In tất cả các phần tử của một List
void printList(List *L)
{
    for (NODE *p = L->p_head; p != nullptr; p = p->p_next)
    {
        cout << p->key << " ";
    }
}
// 9. Đếm số lượng phần tử
int countElements(List *L)
{
    int cnt = 0;
    NODE *p = L->p_head;
    while (p != nullptr)
    {
        cnt++;
        p = p->p_next;
    }
    return cnt;
}
// 10. Đảo một list cho trước (tạo ra một List mới)
List *reverseList(List *L)
{
    List *newL = new (nothrow) List;
    if (newL == nullptr)
    {
        return nullptr;
    }
    newL->p_head = nullptr;
    newL->p_tail = nullptr;

    NODE *p = L->p_head;

    while (p != nullptr)
    {
        addHead(newL, p->key);
        p = p->p_next;
    }
    return newL;
}
// 11. Xóa tất cả các phần tử trùng của một List
void removeDuplicate(List *&L)
{
    NODE *current = L->p_head;

    while (current != nullptr)
    {
        NODE *runner = current;
        while (runner->p_next != nullptr)
        {
            if (runner->p_next->key == current->key)
            {
                NODE *tmp = runner->p_next;
                runner->p_next = tmp->p_next;
                delete tmp;
                if (runner->p_next == nullptr)
                {
                    L->p_tail == runner;
                }
            }
            else
            {
                runner = runner->p_next;
            }
        }
        current = current->p_next;
    }
}
// 12. Xóa giá trị key khoi một List cho trước
bool removeElement(List *&L, int key)
{
    NODE *runner = L->p_head;
    NODE *follow = nullptr;
    bool found = false;
    while (runner != nullptr)
    {
        if (runner->key == key)
        {
            found = true;
            if (follow == nullptr) // là nút đầu tiên trong danh sách
            {
                NODE *p = runner;
                L->p_head = runner->p_next;
                runner = runner->p_next;
                delete p;
            }
            else
            {
                follow->p_next = runner->p_next;
                if (follow->p_next == nullptr)
                {
                    // đây là nút cuối
                    L->p_tail = follow;
                }
                NODE *p = runner;
                runner = runner->p_next;
                delete p;
            }
        }
        else
        {
            follow = runner;
            runner = runner->p_next;
        }
    }
    return found;
}
// 13. Chèn số nguyên vào vị trí bất kỳ
bool addPos(List *&L, int data, int pos)
{
    int cnt = 0;
    NODE *tmp = L->p_head;
    while (tmp != nullptr)
    {
        cnt++;
        tmp = tmp->p_next;
    }
    if (pos < 0 || pos >= cnt)
    {
        return false;
    }

    if (pos == 0)
    {
        addHead(L, data);
    }

    if (pos == cnt - 1)
    {
        addTail(L, data);
    }

    NODE *NODE = createNODE(data);
    if (NODE == nullptr)
    {
        return false;
    }

    tmp = L->p_head;
    // tìm nút trước vị trí pos
    for (int i = 0; i < pos - 1; i++)
    {
        tmp = tmp->p_next;
    }

    NODE->p_next = tmp->p_next;
    tmp->p_next = NODE;

    return true;
}
// 14. Xóa NODE ở vị trí bất kỳ
void removePos(List *&L, int pos)
{
    int cnt = 0;
    NODE *tmp = L->p_head;
    while (tmp != nullptr)
    {
        cnt++;
        tmp = tmp->p_next;
    }
    if (pos < 0 || pos >= cnt)
    {
        return;
    }

    if (pos == 0)
    {
        removeHead(L);
        return;
    }

    if (pos == cnt - 1)
    {
        removeTail(L);
        return;
    }

    tmp = L->p_head;
    // tìm nút trước vị trí pos
    for (int i = 0; i < pos - 1; i++)
    {
        tmp = tmp->p_next;
    }

    NODE *p = tmp->p_next; // nút ở vị trí pos
    tmp->p_next = p->p_next;
    delete p;
}
// 15. Ghép 2 List tăng dần thành một List mới tăng dần
List *ConcatList(List *L1, List *L2)
{
    List *newlist = createList(nullptr);
    NODE *p = L1->p_head;
    NODE *q = L2->p_head;
    while (p->p_next != nullptr && q->p_next != nullptr)
    {
        if (p->key < q->key)
        {
            addTail(newlist, p->key);
            p = p->p_next;
        }
        else if (p->key > q->key)
        {
            addTail(newlist, q->key);
            q = q->p_next;
        }
        else
        {
            addTail(newlist, p->key);
            addTail(newlist, p->key);
            p = p->p_next;
            q = q->p_next;
        }
    }
    // while (p->p_next != nullptr)
    // {
    //     addTail(newlist, p->key);
    //     p = p->p_next;
    // }
    // while (q->p_next != nullptr)
    // {
    //     addTail(newlist, q->key);
    //     q = q->p_next;
    // }
    if (p->p_next != nullptr)
    {
        newlist->p_tail->p_next = p;
        newlist->p_tail = L1->p_tail;
    }

    if (q->p_next != nullptr)
    {
        newlist->p_tail->p_next = q;
        newlist->p_tail = L2->p_tail;
    }

    return newlist;
}
// 16. Ghép List 2 vào List 1 mà vẫn giữ sắp xếp tăng dần
void MergeList(List *L1, List *L2)
{
    if (L1->p_head == nullptr)
    {
        L1->p_head = L2->p_head;
        L2->p_tail = L2->p_tail;
        return;
    }
    if (L2->p_head == nullptr)
    {
        return;
    }

    NODE *current1 = L1->p_head;
    NODE *current2 = L2->p_head;
    NODE *follow = nullptr;

    // phần tử đầu L2 nhỏ hơn phần tử đầu L1
    if (current1->key > current2->key)
    {
        L1->p_head = current2;
        follow = current2;
        current2 = current2->p_next;
        follow->p_next = current1;
    }

    while (current1 != nullptr || current2 != nullptr)
    {
        if (current2->key >= current1->key)
        {
            follow = current1;
            current1 = current1->p_next;
        }
        else
        {
            follow->p_next = current2;
            NODE* tmp = current2->p_next;
            current2->p_next = current1;
            follow = current2;
            current2 = tmp;
        }
    }
    // trường hợp L2 còn phần tử
    if (current2 != nullptr)
    {
        follow->p_next = current2;
        L1->p_tail = L2->p_tail;
    }
}
*/
// II. Stack - Quece
struct NODE
{
    int key;
    NODE *pNext;
};

struct Stack
{
    NODE *top;
};
NODE *CreadNode(int key)
{
    NODE *node = new (nothrow) NODE;

    if (node == nullptr)
    {
        cout << "Dynamic Allocation Error!";
        return nullptr;
    }
    node->key = key;
    node->pNext = nullptr;

    return node;
}
Stack *CreadStack(NODE *node)
{
    Stack *stack = new (nothrow) Stack;
    if (stack == nullptr)
    {
        return nullptr;
    }
    
    stack->top = node;
    
    return stack;
}
bool isEmpty(const Stack *stack)
{
    return (stack->top == nullptr);
}
void Push(Stack *stack, int val)
{
    NODE *node = CreadNode(val);
    if (isEmpty(stack))
    {
        stack->top = node;
    }
    else
    {
        node->pNext = stack->top;
        stack->top = node;
    }
}
int Pop(Stack *stack)
{
    if (isEmpty(stack))
    {
        return -1;
    }
    int top = stack->top->key;
    NODE *p = stack->top;
    stack->top = p->pNext;
    delete p;
    p = nullptr;
    return top;
}
int countStack(Stack *stack)
{
    int count = 0;
    NODE *p = stack->top;
    while (p != nullptr)
    {
        p = p->pNext;
        count++;
    }

    return count;
}

void ReverseString(char* s)
{
    Stack* stack = CreadStack(nullptr);
    for (int i = 0; i < strlen(s); i++)
    {
        int tmp = (int)s[i];
        Push(stack, tmp);
    }
    while (!isEmpty(stack))
    {
        int tmp = Pop(stack);
        cout << (char)tmp;
    }
}
void DecToBin(int dec)
{
    Stack* stack = CreadStack(nullptr);
    while (dec != 0)
    {
        Push(stack, dec % 2);
        dec = dec / 2;
    }
    int count = countStack(stack);
    for (int i = 0; i < 16 - count; i++)
    {
        cout << "0";
    }
    while (!isEmpty(stack))
    {
        cout << Pop(stack);
    }
}

void CheckBalance(char* s)
{
    Stack* stack = CreadStack(nullptr);
    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] == '(' || s[i] == '{' || s[i] == '[')
        {
            Push(stack, (int)s[i]);
        }
        else if (s[i] == ')')
        {
            if (isEmpty(stack))
            {
                cout << "false";
                return;
            }
            int tmp = Pop(stack);
            if ((char)tmp != '(')
            {
                cout << "false";
                return;
            }
        }
        else if (s[i] == '}')
        {
            if (isEmpty(stack))
            {
                cout << "false";
                return;
            }
            int tmp = Pop(stack);
            if ((char)tmp != '{')
            {
                cout << "false";
                return;
            }
        }
        else if (s[i] == ']')
        {
            if (isEmpty(stack))
            {
                cout << "false";
                return;
            }
            int tmp = Pop(stack);
            if ((char)tmp != '[')
            {
                cout << "false";
                return;
            }
        }
    }
    if (isEmpty(stack))
    {
        cout << "true";
    }
}

int main()
{
    char str[] = "{((ab))}]";
    CheckBalance(str);
    return 0;
}