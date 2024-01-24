#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Product
{
    char name[40];
    int count;
    int depNumber;
};

int MAX_PRODUCTS = 100;
int total = 0;

void createFile();
void readFile();
void addProducts();

Product *selectionSort(Product products[], int n)
{
    Product *sortedProducts = new Product[n];
    for (int i = 0; i < n; i++)
    {
        sortedProducts[i] = products[i];
    }

    for (int i = 0; i < n - 1; i++)
    {
        int max_idx = i;
        for (int j = i + 1; j < n; j++)
        {
            if (sortedProducts[j].count > sortedProducts[max_idx].count)
            {
                max_idx = j;
            }
        }
        if (max_idx != i)
        {
            Product tmp = sortedProducts[i];
            sortedProducts[i] = sortedProducts[max_idx];
            sortedProducts[max_idx] = tmp;
        }
    }

    return sortedProducts;
}

Product *quickSort(Product products[], int left, int right)
{
    Product *sortedProducts = new Product[right];
    for (int i = 0; i < right; i++)
    {
        sortedProducts[i] = products[i];
    }

    int i = left, j = right - 1;
    int mid = sortedProducts[(left + right) / 2].count;
    while (i <= j)
    {
        while (products[i].count < mid)
        {
            i++;
        }
        while (products[j].count > mid)
        {
            j--;
        }
        if (i <= j)
        {
            Product tmp = sortedProducts[i];
            sortedProducts[i] = sortedProducts[j];
            sortedProducts[j] = tmp;
            i++;
            j--;
        }
    }

    return sortedProducts;
}

FILE *openFile(const char *fileName, const char *action)
{
    FILE *file = fopen(fileName, action);
    if (file == NULL)
    {
        cout << "! - Что-то пошло не так" << endl;
        return NULL;
    }
    return file;
}

void linearSearch()
{
    int key;
    bool isExist = false;

    cout << "? - Введите количество: " << endl;
    cout << ">> ";
    cin >> key;

    FILE *file = openFile("data.txt", "r");
    if (file == NULL)
        return;

    Product data;
    while (true)
    {
        int n = fread(&data, sizeof(Product), 1, file);
        if (n != 1)
            break;

        if (data.count == key)
        {
            isExist = true;
            cout << endl;
            cout << "- Наименование: " << data.name
                 << "\n- Количество: " << data.count
                 << "\n- Номер цеха: " << data.depNumber << endl;
            return;
        }
    }

    fclose(file);

    if (!isExist)
    {
        cout << "! - Продукт не найден" << endl;
        return;
    }
}

void binarySearch()
{
    int key;
    bool isExist = false;

    cout << "? - Введите количество: " << endl;
    cout << ">> ";
    cin >> key;

    FILE *file = openFile("data.txt", "r");
    if (file == NULL)
        return;

    int count = 0;
    Product data;
    Product products[MAX_PRODUCTS];

    while (true)
    {
        int n = fread(&data, sizeof(Product), 1, file);
        if (n != 1)
            break;

        products[count++] = data;
    }

    Product *sortedProducts = selectionSort(products, count);

    int first = 0, last = count - 1, mid;

    while (first <= last)
    {
        mid = (first + last) / 2;
        /*
         *  '>' - для массива, сортированного по убыванию (100-0),
         *  '<' - для массива, сортированного по возрастанию (0-100)
         */
        if (sortedProducts[mid].count > key)
        {
            first = mid + 1;
        }
        else
        {
            last = mid - 1;
        }
    }
    if (sortedProducts[first].count == key)
    {
        isExist = true;
        cout << endl;
        cout << "- Наименование: " << sortedProducts[first].name
             << "\n- Количество: " << sortedProducts[first].count
             << "\n- Номер цеха: " << sortedProducts[first].depNumber << endl;
    }

    fclose(file);

    if (!isExist)
    {
        cout << "! - Продукт не найден" << endl;
        return;
    }
}

void makeSelectionSort()
{
    FILE *file = openFile("data.txt", "r");
    if (file == NULL)
        return;

    Product data;
    Product products[MAX_PRODUCTS];

    int count = 0;
    while (true)
    {
        int n = fread(&data, sizeof(Product), 1, file);
        if (n != 1)
            break;

        products[count++] = data;
    }

    Product *sortedProducts = selectionSort(products, count);

    for (int i = 0; i < count; i++)
    {
        cout << endl;
        cout << "- Наименование: " << sortedProducts[i].name
             << "\n- Количество: " << sortedProducts[i].count
             << "\n- Номер цеха: " << sortedProducts[i].depNumber << endl;
    }

    fclose(file);
}

void makeQuickSort()
{
    FILE *file = openFile("data.txt", "r");
    if (file == NULL)
        return;

    Product data;
    Product products[MAX_PRODUCTS];

    int count = 0;
    while (true)
    {
        int n = fread(&data, sizeof(Product), 1, file);
        if (n != 1)
            break;

        products[count++] = data;
    }

    Product *sortedProducts = quickSort(products, 0, count);

    for (int i = 0; i < count; i++)
    {
        cout << endl;
        cout << "- Наименование: " << sortedProducts[i].name
             << "\n- Количество: " << sortedProducts[i].count
             << "\n- Номер цеха: " << sortedProducts[i].depNumber << endl;
    }

    fclose(file);
}

void task()
{
    int n, depNumberInfo;
    bool isExist = false;

    cout << "? - Какой цех вас интересует? " << endl;
    cout << ">> ";
    cin >> depNumberInfo;

    FILE *file = openFile("data.txt", "r");
    if (file == NULL)
        return;

    Product data;
    Product products[MAX_PRODUCTS];

    int count = 0;
    while (true)
    {
        int n = fread(&data, sizeof(Product), 1, file);
        if (n != 1)
            break;

        if (data.depNumber == depNumberInfo)
        {
            isExist = true;
            products[count++] = data;
        }
    }
    fclose(file);

    if (!isExist)
    {
        cout << "! - Цех с таким номером не найден" << endl;
        return;
    }

    Product *sortedProducts = selectionSort(products, count);

    for (int i = 0; i < count; i++)
    {
        cout << endl;
        cout << "- Наименование: " << sortedProducts[i].name
             << "\n- Количество: " << sortedProducts[i].count
             << "\n- Номер цеха: " << sortedProducts[i].depNumber << endl;
    }
}

int main()
{
    int action;
    while (true)
    {
        cout << endl;
        cout << "? - Выберите действие:"
             << "\n  1. Создание файла"
             << "\n  2. Просмотр файла"
             << "\n  3. Добавление товаров"
             << "\n  4. Запуск задания"
             << "\n  5. Линейный поиск (ключ: кол-во выпущенных товаров)"
             << "\n  6. Бинарный поиск (ключ: кол-во выпущенных товаров)"
             << "\n  7. Сортировка массива (SelectionSort)"
             << "\n  8. Сортировка массива (QuickSort)"
             << "\n  0. Выход"
             << endl;
        cout << ">> ";
        cin >> action;
        switch (action)
        {
        case (1):
            createFile();
            break;
        case (2):
            readFile();
            break;
        case (3):
            addProducts();
            break;
        case (4):
            task();
            break;
        case (5):
            linearSearch();
            break;
        case (6):
            binarySearch();
            break;
        case (7):
            makeSelectionSort();
            break;
        case (8):
            makeQuickSort();
            break;
        default:
            return 0;
        }
    }

    system("pause");
    return 0;
}

void createFile()
{
    FILE *file = openFile("data.txt", "w");
    if (file == NULL)
        return;
    cout << endl;
    cout << "! - Файл создан" << endl;

    fclose(file);
}
void readFile()
{
    FILE *file = openFile("data.txt", "r");
    if (file == NULL)
        return;

    Product data;

    while (true)
    {
        int n = fread(&data, sizeof(Product), 1, file);
        if (n != 1)
            break;

        cout << endl;
        cout << "- Наименование: " << data.name
             << "\n- Количество: " << data.count
             << "\n- Номер цеха: " << data.depNumber << endl;
    }

    fclose(file);
}
void addProducts()
{
    {
        FILE *file = openFile("data.txt", "a");
        if (file == NULL)
            return;

        int productsCount, depNumber;

        cout << "? - Введите номер цеха: " << endl;
        cout << ">> ";
        cin >> depNumber;
        cout << "? - Количество наименований, выпускаемых цехом " << depNumber << ": " << endl;
        cout << ">> ";
        cin >> productsCount;

        Product products[MAX_PRODUCTS];

        for (int j = 0; j < productsCount; j++)
        {
            cout << "? - Введите наименование: " << endl;
            cout << ">> ";
            cin >> products[j].name;
            cout << "? - Введите количество: " << endl;
            cout << ">> ";
            cin >> products[j].count;
            products[j].depNumber = depNumber;
            total++;
        }

        fwrite(products, sizeof(Product), productsCount, file);

        fclose(file);
    }
}