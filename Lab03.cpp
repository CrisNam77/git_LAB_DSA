#include <iostream>
#include <queue>

using namespace std;

struct NODE
{
    int key;
    NODE *p_left;
    NODE *p_right;
};
// 1. Khởi tạo một NODE từ một giá trị cho trước:
NODE *createNode(int data)
{
    NODE *newnode = new (nothrow) NODE{data, nullptr, nullptr};
    if (newnode == nullptr)
    {
        return nullptr;
    }
    // newnode->key = data;
    // newnode->p_left = nullptr;
    // newnode->p_right = nullptr;
    return newnode;
}
// 2. Duyệt tiền thứ tự:
void NLR(NODE *pRoot)
{
    if (pRoot == nullptr)
    {
        return;
    }
    cout << pRoot->key << " ";
    NLR(pRoot->p_left);
    NLR(pRoot->p_right);
}
// 3. Duyệt trung thứ tự:
void LNR(NODE *pRoot)
{
    if (pRoot == nullptr)
    {
        return;
    }
    LNR(pRoot->p_left);
    cout << pRoot->key << " ";
    LNR(pRoot->p_right);
}
// 4. Duyệt hậu thứ tự:
void LRN(NODE *pRoot)
{
    if (pRoot == nullptr)
    {
        return;
    }
    LRN(pRoot->p_left);
    LRN(pRoot->p_right);
    cout << pRoot->key << " ";
}
// 5. Duyệt theo mức:
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
        cout << current->key << " ";
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
// 6. Tìm và trả về một NODE với giá trị cho trước từ một cây nhị phân tìm kiếm:
NODE *Search(NODE *pRoot, int x)
{
    if (pRoot == nullptr || pRoot->key == x)
    {
        return pRoot;
    }
    else if (pRoot->key > x)
    {
        return Search(pRoot->p_left, x);
    }
    else
    {
        return Search(pRoot->p_right, x);
    }
}
// 7. Thêm một NODE với giá trị cho trước vào cây nhị phân tìm kiếm:
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
}
// 8. Xoá một NODE với giá trị cho trước từ một cây nhị phân tìm kiếm:
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
}
// 9. Khởi tạo một cây nhị phân tìm kiếm từ một mảng cho trước:
NODE *createTree(int a[], int n)
{
    NODE *pRoot = nullptr;
    for (int i = 0; i < n; i++)
    {
        Insert(pRoot, a[i]);
    }
    return pRoot;
}
// 10. Xóa hoàn toàn một cây nhị phân tìm kiếm:
void removeTree(NODE *&pRoot)
{
    if (pRoot == nullptr)
    {
        return;
    }
    removeTree(pRoot->p_left);
    removeTree(pRoot->p_right);
    delete pRoot;
    pRoot = nullptr;
}
// 11. Tính chiều cao của một cây nhị phân tìm kiếm:
int Height(NODE *pRoot)
{
    if (pRoot == nullptr)
    {
        return -1; // chiều cao ở nút gốc là 0
    }
    int heightL = Height(pRoot->p_left);
    int heightR = Height(pRoot->p_right);
    return 1 + max(heightL, heightR);
}
// 12. Đếm số lượng NODE của một cây nhị phân:
int countNode(NODE *pRoot)
{
    if (pRoot == nullptr)
    {
        return 0;
    }
    return 1 + countNode(pRoot->p_left) + countNode(pRoot->p_right);
}
// 13. Tính tổng giá trị của toàn bộ NODEs trong một cây nhị phân:
int sumNode(NODE *pRoot)
{
    if (pRoot == nullptr)
    {
        return 0;
    }
    return pRoot->key + sumNode(pRoot->p_left) + sumNode(pRoot->p_right);
}
// 14. Tính toán chiều cao của một NODE với giá trị cho trước: (trả về-1 nếu không tồn tại)
int heightNode(NODE *pRoot, int value)
{
    if (pRoot == nullptr)
    {
        return -1;
    }
    if (pRoot->key == value)
    {
        return Height(pRoot);
    }
    int leftres = heightNode(pRoot->p_left, value);
    if (leftres != -1)
    {
        return leftres;
    }
    return heightNode(pRoot->p_right, value);
}
// 15. * Tính toán tầng của một NODE cho trước:
int Level(NODE *pRoot, NODE *p)
{
    if (pRoot == nullptr)
    {
        return -1;
    }
    if (pRoot == p)
    {
        return 0;
    }
    else if (pRoot->key > p->key)
    {
        return 1 + Level(pRoot->p_left, p);
    }
    else
    {
        return 1 + Level(pRoot->p_right, p);
    }
}
// 16. * Đếm số lá của một cây nhị phân:
int countLeaf(NODE *pRoot)
{
    if (pRoot == nullptr)
    {
        return 0;
    }
    int count = 0;
    queue<NODE *> q;
    q.push(pRoot);
    while (!q.empty())
    {
        NODE *p = q.front();
        q.pop();
        if (p->p_left == nullptr && p->p_right == nullptr)
        {
            count++;
        }
        if (p->p_left != nullptr)
        {
            q.push(p->p_left);
        }
        if (p->p_right != nullptr)
        {
            q.push(p->p_right);
        }
    }
    return count;
}
// 17.* Đếm số NODE của một cây nhị phân tìm kiếm mà giá trị key nhỏ hơn giá trị cho trước:
int countLess(NODE *pRoot, int x)
{
    if (pRoot == nullptr)
    {
        return 0;
    }
    int count = 0;
    while (pRoot != nullptr)
    {
        if (pRoot->key < x)
        {
            count += 1 + countNode(pRoot->p_left);
            pRoot = pRoot->p_right;
        }
        else
        {
            pRoot = pRoot->p_left;
        }
    }
    return count;
}
// 18.* Đếm số lượng NODE của một cây nhị phân tìm kiếm mà giá trị key lớn hơn giá trị cho trước:
int countGreater(NODE *pRoot, int x)
{
    if (pRoot == nullptr)
    {
        return 0;
    }
    int count = 0;
    while (pRoot != nullptr)
    {
        if (pRoot->key > x)
        {
            count += 1 + countNode(pRoot->p_right);
            pRoot = pRoot->p_left;
        }
        else
        {
            pRoot = pRoot->p_right;
        }
    }
    return count;
}
// 19.* Xác định cây nhị phân có phải là cây nhị phân tìm kiếm hay không:
int maxleft(NODE *node)
{
    if (node == nullptr)
    {
        return -1e9;
    }
    return max(node->key, max(maxleft(node->p_left), maxleft(node->p_right)));
}
int minright(NODE *node)
{
    if (node == nullptr)
    {
        return 1e9;
    }
    return min(node->key, min(minright(node->p_left), minright(node->p_right)));
}
bool isBST(NODE *pRoot)
{
    if (pRoot == nullptr)
    {
        return true;
    }
    if (pRoot->p_left != nullptr && maxleft(pRoot->p_left) >= pRoot->key)
    {
        return false;
    }
    if (pRoot->p_right != nullptr && minright(pRoot->p_right) <= pRoot->key)
    {
        return false;
    }
    return isBST(pRoot->p_left) && isBST(pRoot->p_right);
}
// 20. * Xác định cây nhị phân có phải là cây nhị phân tìm kiếm đầy đủ hay không:
bool isFullBST(NODE *pRoot)
{
    if (!isBST(pRoot))
    {
        return false;
    }
    queue<NODE *> q;
    q.push(pRoot);
    while (!q.empty())
    {
        NODE *p = q.front();
        q.pop();
        if ((p->p_left != nullptr && p->p_right == nullptr) || (p->p_left == nullptr && p->p_right != nullptr))
        {
            return false;
        }
        if (p->p_left != nullptr)
        {
            q.push(p->p_left);
            q.push(p->p_right);
        }
    }
    return true;
}

// is Complete BST (full + perfect) solvable by level order traversal

int main()
{
    int a[8] = {15, 7, 20, 6, 10, 8, 11, 16};
    NODE *pRoot = createTree(a, 8);
    LevelOrder(pRoot);
    return 0;
}
