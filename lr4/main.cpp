#include <iostream>
#include <ctime>

using namespace std;

struct Stack
{
    int info;
    Stack *next, *prev;
} *begin, *end, *t;

void createStacks(Stack **begin, Stack **end)
{
    t = new Stack;
    t->info = 0;
    t->next = t->prev = NULL;
    *begin = *end = t;
}

void push(Stack **begin, Stack **end, int value, int direction)
{
    t = new Stack;
    t->info = value;
    if (direction == 0)
    {
        t->prev = NULL;
        t->next = *begin;
        (*begin)->prev = t;
        *begin = t;
    }
    else
    {
        t->next = NULL;
        t->prev = *end;
        (*end)->next = t;
        *end = t;
    }
}

void display(Stack *t, int direction)
{
    while (t != NULL)
    {
        cout << t->info << " ";
        if (direction == 0)
        {
            t = t->next;
        }
        else
        {
            t = t->prev;
        }
    }
    cout << endl;
}

void clear(Stack **p)
{
    Stack *t;
    while (*p != NULL)
    {
        t = *p;
        *p = (*p)->next;
        delete t;
    }
}

void sortByValue(Stack *p)
{
    cout << "- Список до сортировки:" << endl;
    display(p, 0);

    Stack *t = NULL, *t1;
    int temp;
    do
    {
        for (t1 = p; t1->next != t; t1 = t1->next)
            if (t1->info > t1->next->info)
            {
                temp = t1->info;
                t1->info = t1->next->info;
                t1->next->info = temp;
            }
        t = t1;
    } while (p->next != t);

    cout << "- Список после сортировки:" << endl;
    display(p, 0);
}

void task(Stack *p)
{
    cout << "- Список до изменения:" << endl;
    display(p, 0);

    int minValue = p->info, maxValue = p->info;
    int minIndex = -1, maxIndex = -1;
    int currentIndex = 0;
    Stack *current = p;
    while (current != NULL)
    {
        if (current->info < minValue)
        {
            minValue = current->info;
            minIndex = currentIndex;
        }
        if (current->info > maxValue)
        {
            maxValue = current->info;
            maxIndex = currentIndex;
        }
        current = current->next;
        currentIndex++;
    }

    if (minIndex > maxIndex)
    {
        swap(minIndex, maxIndex);
    }

    int count = 0;
    current = p;
    Stack *previous = NULL;
    while (count <= maxIndex)
    {
        if (count >= minIndex && count <= maxIndex)
        {
            if (previous != NULL)
            {
                previous->next = current->next;
            }
            else
            {
                p = current->next;
            }
            Stack *temp = current;
            current = current->next;
            delete temp;
        }
        else
        {
            previous = current;
            current = current->next;
        }
        count++;
    }

    cout << "- Список после изменения:" << endl;
    display(p, 0);
}

int main()
{
    bool isExist = false;
    Stack *begin = NULL;
    Stack *end = NULL;
    srand(time(NULL));

    int action, direction;
    while (true)
    {
        cout << endl;
        cout << "? - Выберите действие:"
             << "\n  1. Создание списка"
             << "\n  2. Добавление значений (с начала/с конца)"
             << "\n  3. Просмотр списка (с начала/с конца)"
             << "\n  4. Удаление списка"
             << "\n  5. Запуск задания"
             << "\n  6. Сортировка обменом значений"
             << "\n  0. Выход"
             << endl;
        cout << ">> ";
        cin >> action;
        switch (action)
        {
        case 1:
            if (!isExist)
            {
                isExist = true;
                createStacks(&begin, &end);
                cout << "! - Новый пустой список создан" << endl;
            }
            else
            {
                cout << "! - Список уже создан" << endl;
            }
            break;
        case 2:
            int n;
            cout << "? - Введите количество значений: " << endl;
            cout << ">> ";
            cin >> n;

            cout << "? - Выберите направление заполнения:"
                 << "\n  0. С начала"
                 << "\n  1. С конца"
                 << endl;
            cout << ">> ";
            cin >> direction;

            for (int i = 1; i <= n; i++)
            {
                int value = rand() % 20 - 10;
                push(&begin, &end, value, direction);
            }
            break;
        case 3:
            if (!isExist)
            {
                cout << "! - Список не создан" << endl;
                break;
            }
            if (begin == NULL)
            {
                cout << "! - Список пустой" << endl;
                break;
            }
            cout << "? - Выберите направление просмотра:"
                 << "\n  0. С начала"
                 << "\n  1. С конца"
                 << endl;
            cout << ">> ";
            cin >> direction;

            if (direction == 0)
            {
                t = begin;
                cout << "- Ваш список с начала:" << endl;
            }
            else
            {
                t = end;
                cout << "- Ваш список с конца:" << endl;
            };

            display(t, direction);
            break;
        case 4:
            if (!isExist)
            {
                cout << "! - Список не создан" << endl;
                break;
            }
            clear(&begin);
            cout << "! - Список удален" << endl;
            isExist = false;
            break;
        case 5:
            task(begin);
            break;
        case 6:
            sortByValue(begin);
            break;
        default:
            return 0;
        }
    }

    return 0;
}