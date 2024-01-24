#include <iostream>
#include <cmath>

using namespace std;

double sum_r(int index, int n)
{
    int end = 1;

    if (index == end)
    {
        return sqrt(1.0 + n);
    }
    else
    {
        return sqrt((n - index) + sum_r(index - 1, n));
    }
}

int main()
{
    int n;

    cout << "Введите n: ";
    cin >> n;
    cout << "Результат: " << sum_r(n - 1, n) << endl;

    system("pause");
    return 0;
}
