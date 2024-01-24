#include <iostream>
#include <ctime>

using namespace std;

struct Stack
{
    int info;
    Stack *next;
} *t;

Stack *push(Stack *p, int value)
{
    Stack *t = new Stack;
    t->info = value;
    t->next = p;
    return t;
}

void display(Stack *p)
{
    Stack *t = p;
    while (t != NULL)
    {
        cout << t->info << " ";
        t = t->next;
    }
    cout << endl;
}

void clear(Stack **p)
{
    while (*p != NULL)
    {
        t = *p;
        *p = (*p)->next;
        delete t;
    }
}

void sortByAdress(Stack **p)
{
    cout << "- Список до сортировки:" << endl;
    display(*p);

    *p = push(*p, 1000);
    Stack *temp;

    Stack *t = NULL, *t1, *r;
    if ((*p)->next->next == NULL)
        return;
    do
    {
        for (t1 = *p; t1->next->next != t; t1 = t1->next)
            if (t1->next->info > t1->next->next->info)
            {
                r = t1->next->next;
                t1->next->next = r->next;
                r->next = t1->next;
                t1->next = r;
            }
        t = t1->next;
    } while ((*p)->next->next != t);

    temp = *p;
    *p = (*p)->next;
    delete temp;

    cout << "- Список после сортировки:" << endl;
    display(*p);
}

void sortByValue(Stack *p)
{
    cout << "- Список до сортировки:" << endl;
    display(p);

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
    display(p);
}

void task(Stack *p)
{
    cout << "- Список до изменения:" << endl;
    display(p);

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
    display(p);
}

int main()
{
    bool isExist = false;
    Stack *begin = new Stack;
    srand(time(NULL));

    int action;
    while (true)
    {
        cout << endl;
        cout << "? - Выберите действие:"
             << "\n  1. Создание списка"
             << "\n  2. Добавление значений"
             << "\n  3. Просмотр списка"
             << "\n  4. Удаление списка"
             << "\n  5. Запуск задания"
             << "\n  6. Сортировка обменом адресов"
             << "\n  7. Сортировка обменом значений"
             << "\n  0. Выход"
             << endl;
        cout << ">> ";
        cin >> action;
        switch (action)
        {
        case (1):
            if (!isExist)
            {
                isExist = true;
                begin = NULL;
                cout << "! - Новый пустой список создан" << endl;
            }
            if (begin != NULL)
            {
                cout << "! - Список уже создан" << endl;
                break;
            }
            break;
        case (2):
            int n;
            cout << "? - Введите количество значений: " << endl;
            cout << ">> ";
            cin >> n;
            for (int i = 1; i <= n; i++)
            {
                int value = rand() % 20 - 10;
                begin = push(begin, value);
            }
            break;
        case (3):
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
            cout << "- Ваш список:" << endl;
            display(begin);
            break;
        case (4):
            if (!isExist)
            {
                cout << "! - Список не создан" << endl;
                break;
            }
            clear(&begin);
            cout << "! - Список удален" << endl;
            isExist = false;
            break;
        case (5):
            task(begin);
            break;
        case (6):
            sortByAdress(&begin);
            break;
        case (7):
            sortByValue(begin);
            break;
        default:
            return 0;
        }
    }

    system("pause");
    return 0;
}
