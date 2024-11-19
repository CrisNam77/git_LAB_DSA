#include <iostream>
#include <queue>
#include <math.h>

using namespace std;

struct NODE
{
    int key;
    NODE *p_left;
    NODE *p_right;
    int height;
};
// 1. Khởi tạo một NODE từ một giá trị cho trước:
NODE *createNode(int data)
{
    NODE *newnode = new NODE;
    newnode->key = data;
    newnode->p_left = nullptr;
    newnode->p_right = nullptr;
    newnode->height = 1;
    return newnode;
}

int height(NODE *pRoot)
{
    if (pRoot == nullptr)
    {
        return 0;
    }
    return pRoot->height;
}
int getBalance(NODE *pRoot)
{
    if (pRoot == nullptr)
    {
        return 0;
    }
    return height(pRoot->p_left) - height(pRoot->p_right);
}
void updateHeight(NODE *pRoot)
{
    pRoot->height = 1 + max(height(pRoot->p_left), height(pRoot->p_right));
}
// Hàm quay phải
NODE *rightRotate(NODE *z)
{
    NODE *y = z->p_left;
    NODE *T3 = y->p_right;

    y->p_right = z;
    z->p_left = T3;

    updateHeight(y);
    updateHeight(z);
    return y;
}
// Hàm quay trái
NODE *leftRotate(NODE *z)
{
    NODE *y = z->p_right;
    NODE *T2 = y->p_left;

    y->p_left = z;
    z->p_right = T2;

    updateHeight(y);
    updateHeight(z);
    return y;
}

NODE *Balance(NODE *pRoot)
{
    updateHeight(pRoot);
    int balance = getBalance(pRoot);
    // Left Left
    if (balance > 1 && getBalance(pRoot->p_left) >= 0)
    {
        return rightRotate(pRoot);
    }
    // Left Right
    if (balance > 1 && getBalance(pRoot->p_left) < 0)
    {
        pRoot->p_left = leftRotate(pRoot->p_left);
        return rightRotate(pRoot);
    }
    // Right Right
    if (balance < -1 && getBalance(pRoot->p_right) <= 0)
    {
        return leftRotate(pRoot);
    }
    // Rigth Left
    if (balance < -1 && getBalance(pRoot->p_right) > 0)
    {
        pRoot->p_right = rightRotate(pRoot->p_right);
        return leftRotate(pRoot);
    }
    return pRoot;
}
// 2. Thêm một NODE có giá trị cho trước vào cây AVL cho trước
void Insert(NODE *&pRoot, int x)
{
    if (pRoot == nullptr)
    {
        pRoot = createNode(x);
        return;
    }
    if (pRoot->key == x)
    {
        return;
    }
    else if (pRoot->key > x)
    {
        Insert(pRoot->p_left, x);
    }
    else
    {
        Insert(pRoot->p_right, x);
    }

    pRoot = Balance(pRoot);
}
// 3. Xóa một NODE với giá trị cho trước từ một cây AVL cho trước
void Remove(NODE *&pRoot, int x)
{
    if (pRoot == nullptr)
    {
        return;
    }
    if (pRoot->key == x)
    {
        // Trường hợp nút là lá hoặc có một con
        if (pRoot->p_left == nullptr)
        {
            NODE *tmp = pRoot->p_right;
            delete pRoot;
            pRoot = tmp;
        }
        else if (pRoot->p_right == nullptr)
        {
            NODE *tmp = pRoot->p_left;
            delete pRoot;
            pRoot = tmp;
        }
        // Trường hợp nút có 2 con
        else
        {
            NODE *tmp = pRoot->p_right;
            while (tmp->p_left != nullptr)
            {
                tmp = tmp->p_left;
            }
            pRoot->key = tmp->key;
            Remove(pRoot->p_right, tmp->key);
        }
    }
    else if (pRoot->key > x)
    {
        Remove(pRoot->p_left, x);
    }
    else
    {
        Remove(pRoot->p_right, x);
    }

    pRoot = Balance(pRoot);
}
// 4. Duyệt tiền thứ tự (key và height của NODE được yêu cầu)
void NLR(NODE *pRoot)
{
    if (pRoot == nullptr)
    {
        return;
    }
    cout << pRoot->key << " " << pRoot->height << endl;
    NLR(pRoot->p_left);
    NLR(pRoot->p_right);
}
// 5. Duyệt trung thứ tự (key và height của NODE được yêu cầu)
void LNR(NODE *pRoot)
{
    if (pRoot == nullptr)
    {
        return;
    }
    LNR(pRoot->p_left);
    cout << pRoot->key << " " << pRoot->height << endl;
    LNR(pRoot->p_right);
}
// 6. Duyệt hậu thứ tự (key và height của NODE được yêu cầu)
void LRN(NODE *pRoot)
{
    if (pRoot == nullptr)
    {
        return;
    }
    LNR(pRoot->p_left);
    LNR(pRoot->p_right);
    cout << pRoot->key << " " << pRoot->height << endl;
}
// 7. Duyệt theo tầng (key và height của NODE được yêu cầu)
void LevelOrder(NODE *pRoot)
{
    if (pRoot == nullptr)
        return;
    queue<NODE *> q;
    q.push(pRoot);
    while (!q.empty())
    {
        NODE *current = q.front();
        q.pop();
        cout << current->key << " "; //<< current->height << endl;
        if (current->p_left != nullptr)
        {
            q.push(current->p_left);
        }
        if (current->p_right != nullptr)
        {
            q.push(current->p_right);
        }
    }
}
// 8. * Xác định một cây nhị phân có phải là cây AVL không
bool isAVL(NODE *pRoot)
{
    if (pRoot == nullptr)
    {
        return true;
    }
    if (abs(getBalance(pRoot)) > 1)
    {
        return false;
    }
    if (!isAVL(pRoot->p_left) || !isAVL(pRoot->p_right))
    {
        return false;
    }
    return true;
}

int Floor(NODE *pRoot, int x)
{
    if (pRoot == nullptr)
    {
        return -1;
    }
    if (pRoot->key == x)
    {
        return pRoot->key;
    }
    if (pRoot->key > x)
    {
        return Floor(pRoot->p_left, x);
    }
    int reuslt = Floor(pRoot->p_right, x);
    if (reuslt == -1)
    {
        return pRoot->key;
    }
    return reuslt;
}

void createBackbone(NODE *&pRoot)
{
    if (pRoot == nullptr)
    {
        return;
    }
    while (pRoot->p_left != nullptr)
    {
        pRoot = rightRotate(pRoot);
    }
    createBackbone(pRoot->p_right);
}

int countBackbone(NODE *pRoot)
{
    int count = 0;
    NODE *current = pRoot;
    while (current != nullptr)
    {
        count++;
        current = current->p_right;
    }
    return count;
}
void createCompleteTree(NODE *&pRoot)
{
    createBackbone(pRoot);
    int n = countBackbone(pRoot);
    int h = log2(n + 1);
    int m = pow(2, h) - 1;

    // make n - m left rotations starting form the top of backbone
    NODE *tmp = pRoot;
    NODE *parrent = nullptr;
    for (int i = 0; i < n - m; i++)
    {
        if (tmp && tmp->p_right)
        {
            if (!parrent)
            {
                pRoot = leftRotate(tmp);
                parrent = pRoot;
            }
            else
            {
                parrent->p_right = leftRotate(tmp);
                parrent = parrent->p_right;
            }
            tmp = parrent->p_right;
        }
    }

    while (m > 1)
    {
        m = m / 2;
        tmp = pRoot;
        parrent = nullptr;
        for (int i = 0; i < m; i++)
        {
            if (tmp && tmp->p_right)
            {
                if (!parrent)
                {
                    pRoot = leftRotate(tmp);
                    parrent = pRoot;
                }
                else
                {
                    parrent->p_right = leftRotate(tmp);
                    parrent = parrent->p_right;
                }
                tmp = parrent->p_right;
            }
        }
    }
}



int main()
{
    NODE *pRoot = nullptr;
    Insert(pRoot, 1);
    Insert(pRoot, 2);
    Insert(pRoot, 3);
    Insert(pRoot, 4);
    Insert(pRoot, 5);
    Insert(pRoot, 6);
    LevelOrder(pRoot);
    cout << endl;
    createCompleteTree(pRoot);
    LevelOrder(pRoot);

    return 0;
}
