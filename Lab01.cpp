#include <iostream>
#include <math.h>
#include <string>
#include <cstring>

using namespace std;

// 1.Con trỏ

/*
1. Viết hàm nhập vào một mảng số nguyên gồm n phần tử
• void inputArray(int* a, int n)
2. Viết hàm in các giá trị của mảng ra màn hình.
• void printArray(int* a, int n);
3. Viết hàm tìm giá trị nhỏ nhất trong mảng:
• int FindMin(int* a, int n);
4. Viết hàm tìm phần tử có trị tuyệt đối lớn nhất trong mảng:
• int FindMaxModulus(int* a, int n);
5. Viết hàm đếm số lần xuất hiện của giá trị bất kì trong mảng.
• int countValue(int* a, int n, int key)
6. Viết hàm đảo ngược chuỗi và in ra màn hình.
• void StrRev(char* a)
7. Viết hàm in hoa chữ cái đầu của từng từ và in ra màn hình. VD "Cau TRuC dU liEu" -> "Cau Truc Du Lieu".
• void PrettyStr(char* a)
*/
void inputArray(int *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        cin >> *(a + i);
    }
}
void printArray(int *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << *(a + i) << " ";
    }
}
int FindMin(int *a, int n)
{
    int resMin = a[0];
    for (int i = 1; i < n; i++)
    {
        if (a[i] < resMin)
        {
            resMin = a[i];
        }
    }
    return resMin;
}
int FindMaxModulus(int *a, int n)
{
    int intdexMaxModulus = 0;
    for (int i = 1; i < n; i++)
    {
        if (abs(a[i]) > abs(a[intdexMaxModulus]))
        {
            intdexMaxModulus = i;
        }
    }
    return a[intdexMaxModulus];
}
int countValue(int *a, int n, int key)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (a[i] == key)
        {
            count++;
        }
    }
    return count;
}
void StrRev(char *a)
{
    for (int i = 0; i <= strlen(a) / 2; i++)
    {
        char tmp = a[i];
        a[i] = a[strlen(a) - 1 - i];
        a[strlen(a) - 1 - i] = tmp;
    }
}
void PrettyStr(char *a)
{
    for (int i = 0; i < strlen(a); i++)
    {
        if (i == 0 || a[i - 1] == ' ')
        {
            a[i] = toupper(a[i]);
        }
        else
        {
            a[i] = tolower(a[i]);
        }
    }
}

// 2.Struct
struct Time
{
    int hrs;
    int mins;
    int secs;
    friend istream &operator>>(istream &in, Time &time)
    {
        in >> time.hrs;
        in >> time.mins;
        in >> time.secs;
        return in;
    }
    friend ostream &operator<<(ostream &out, const Time &time)
    {
        out << '"';
        if (time.hrs < 10)
        {
            out << '0' << time.hrs;
        }
        else
        {
            out << time.hrs;
        }
        cout << ":";
        if (time.mins < 10)
        {
            out << '0' << time.mins;
        }
        else
        {
            out << time.mins;
        }
        cout << ":";
        if (time.secs < 10)
        {
            out << '0' << time.secs;
        }
        else
        {
            out << time.secs;
        }
        cout << '"';
        return out;
    }
    Time operator+(const Time &time)
    {
        Time total;
        
        return total;
    }
};

struct fraction
{
    int num;   // the numerator of the fraction
    int denom; // the denominator of the fraction
    friend istream &operator>>(istream &in, fraction &ps)
    {
        in >> ps.num;
        in >> ps.denom;
        return in;
    }

    friend ostream &operator<<(ostream &out, const fraction &ps)
    {
        out << ps.num << "/" << ps.denom;
        return out;
    }

    int GCD(int a, int b)
    {
        while (b != 0)
        {
            int r = a % b;
            a = b;
            b = r;
        }
        return a;
    }
    void RutGon()
    {
        int ucln = GCD(num, denom);
        num /= ucln;
        denom /= ucln;
    }

    fraction operator+(const fraction &ps)
    {
        fraction Sum;
        Sum.num = num * ps.denom + denom * ps.num;
        Sum.denom = denom * ps.denom;
        Sum.RutGon();
        return Sum;
    }
};

// 3.Đệ quy
int sumOfSquares(int n)
{
    if (n == 1)
        return 1;
    return sumOfSquares(n - 1) + n * n;
}
int gcd(int a, int b)
{
    if (b == 0)
    {
        return a;
    }
    return gcd(b, a % b);
}
bool isPalindromeHelper(int a[], int start, int end)
{
    if (start >= end)
    {
        return true;
    }
    if (a[start] != a[end])
    {
        return false;
    }
    return isPalindromeHelper(a, start + 1, end - 1);
}
bool isPalindrome(int a[], int n)
{
    return isPalindromeHelper(a, 0, n - 1);
}
int Factorial(int n)
{
    if (n == 0)
    {
        return 1;
    }
    return n * Factorial(n - 1);
}

int countDigit(int a)
{
    if (a < 10)
    {
        return 1;
    }
    return 1 + countDigit(a / 10);
}
int FIB(int n)
{
    if (n == 1)
    {
        return 1;
    }
    if (n == 2)
    {
        return 1;
    }
    return FIB(n - 1) + FIB(n - 2);
}
int main()
{
    cout << FIB(6);
    return 0;
}