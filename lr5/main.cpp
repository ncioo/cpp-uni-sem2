#include <iostream>
#include <math.h>
#include <cstring>

using namespace std;

struct Stack
{
    char info;
    Stack *next;
} *top;

double mas[300];
string s = "";
string numStr;

Stack *push(Stack *p, int value)
{
    Stack *t = new Stack;
    t->info = value;
    t->next = p;
    return t;
}

Stack *getTop(Stack *p, char *out)
{
    Stack *t = p;
    Stack *tt;
    if (t != NULL)
    {
        *out = t->info;
        tt = t;
        t = (t)->next;
        delete tt;
    }
    return t;
}

int priority(int a)
{
    switch (a)
    {
    case '^':
        return 4;
    case '*':
    case '/':
        return 3;
    case '-':
    case '+':
        return 2;
    case '(':
        return 1;
    }
    return 0;
}

string insertValues(string str, string numStr)
{
    float a, b, c, d, e;

    cout << "? - Введите значение 'a': " << endl;
    cout << ">> ";
    cin >> a;
    cout << "? - Введите значение 'b': " << endl;
    cout << ">> ";
    cin >> b;
    cout << "? - Введите значение 'c': " << endl;
    cout << ">> ";
    cin >> c;
    cout << "? - Введите значение 'd': " << endl;
    cout << ">> ";
    cin >> d;
    cout << "? - Введите значение 'e': " << endl;
    cout << ">> ";
    cin >> e;

    for (int i = 0; i <= str.length(); i++)
    {
        switch (str[i])
        {
        case 'a':
            mas[int(a)] = a;
            numStr += a;
            break;
        case 'b':
            mas[int(b)] = b;
            numStr += b;
            break;
        case 'c':
            mas[int(c)] = c;
            numStr += c;
            break;
        case 'd':
            mas[int(d)] = d;
            numStr += d;
            break;
        case 'e':
            mas[int(e)] = e;
            numStr += e;
            break;
        case '^':
        case '+':
        case '-':
        case '*':
        case '/':
            numStr += str[i];
            break;
        }
    }
    return numStr;
}

double result(string str, Stack *top)
{
    char ch, ch1, ch2;
    double op1, op2, rez;
    char chr = 'z' + 1;
    for (int i = 0; i <= str.length(); i++)
    {
        ch = str[i];
        if (ch != '*' && ch != '/' && ch != '+' && ch != '-' && ch != '^')
            top = push(top, ch);
        else
        {
            top = getTop(top, &ch1);
            top = getTop(top, &ch2);
            op1 = mas[int(ch1)];
            op2 = mas[int(ch2)];

            switch (ch)
            {
            case '+':
                rez = op2 + op1;
                break;
            case '-':
                rez = op2 - op1;
                break;
            case '*':
                rez = op2 * op1;
                break;
            case '/':
                rez = op2 / op1;
                break;
            case '^':
                rez = pow(op2, op1);
                break;
            }
            mas[int(chr)] = rez;
            top = push(top, chr);
            chr++;
        }
    }
    return rez;
}

Stack *removeOpenBrackets(Stack *p, char ch)
{
    Stack *t = p;
    Stack *tt;
    while (t != NULL && t->info == ch)
    {
        tt = t;
        t = (t)->next;
        delete tt;
    }
    return t;
}
Stack *allValuesToTop(Stack *p)
{
    Stack *t = p;
    Stack *tt;
    while (t != NULL)
    {
        s += t->info;
        tt = t;
        t = (t)->next;
        delete tt;
    }
    return t;
}
Stack *addToOpenBrackets(Stack *p, char ch)
{
    Stack *t = p;
    Stack *tt;
    while (t != NULL && t->info != ch)
    {
        s += t->info;
        tt = t;
        t = (t)->next;
        delete tt;
    }
    return t;
}
Stack *addByProiority(Stack *p, char ch)
{
    Stack *t = p;
    Stack *tt;
    while (t != NULL && priority(t->info) >= priority(ch))
    {
        s += t->info;
        tt = t;
        t = (t)->next;
        delete tt;
    }
    return t;
}

int main()
{
    char expression[30];

    Stack *top = new Stack;
    top = NULL;

    cout << "? - Введите выражение:" << endl;
    cout << ">> ";
    cin >> expression;

    for (int i = 0; i < strlen(expression); i++)
    {
        if (expression[i] == '(')
            top = push(top, expression[i]);
        if (expression[i] == ')')
        {
            top = addToOpenBrackets(top, '(');
            top = removeOpenBrackets(top, '(');
        };
        if (expression[i] >= 'a' && expression[i] <= 'z')
            s += expression[i];
        if (expression[i] == '*' || expression[i] == '/' || expression[i] == '+' || expression[i] == '-' || expression[i] == '^')
        {
            top = addByProiority(top, expression[i]);
            top = push(top, expression[i]);
        }
    }
    while (top != NULL)
    {
        top = allValuesToTop(top);
    }
    numStr = insertValues(s, numStr);

    cout << "- Ваш результат: " << result(numStr, top) << endl;
}