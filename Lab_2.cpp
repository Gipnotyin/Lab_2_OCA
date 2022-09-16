#include <iostream>
#include <string>
#include <fstream>

using namespace std;

enum Field
{
    number, Data
};

struct Library
{
    string first_name;
    string last_name;
    string patronymic;
    int number;
    string name_book;
    int Data;
    bool IsEmpty;
public:
    Library()
    {
        first_name = "";
        last_name = "";
        patronymic = "";
        number = -1;
        name_book = "";
        Data = -1;
        IsEmpty = true;
    }
    void Reset()
    {
        first_name = "";
        last_name = "";
        patronymic = "";
        number = -1;
        name_book = "";
        Data = -1;
        IsEmpty = true;
    }
    void SetKey()
    {
        cout << "Введите имя: "; cin >> first_name;
        cout << "Введите фамилию: "; cin >> last_name;
        cout << "Введите отчество: "; cin >> patronymic;
        cout << "Введите номер читательского билета: "; cin >> number;
        cout << "Введите название книги: "; cin >> name_book;
        cout << "Введите срок возврата(в днях): "; cin >> Data;
        IsEmpty = false;
    }
    void PrintF()
    {
        cout << "ФИО: " << first_name << " "
            << last_name << " " << patronymic << endl
            << "Номер читательского билета: " << number << endl
            << "Название книги: " << name_book << endl
            << "Срок возварата: " << Data << endl;
    }
    bool IsSearc(int number, string name)
    {
        if (first_name == name or last_name == name or patronymic == name or name_book == name)
        {
            return true;
        }
        if (this->number == number or Data == number)
        {
            return true;
        }
        return false;
    }
};

Library* library;

int Count()
{
    cout << "Сколько хотите ввести пользователей?\n";
    int n;
    cin >> n;
    return n;
}

void Clear_One_Element(int index)
{
    library[index].Reset();
}

int Second_empty_element(int size)
{
    for (int i = 0; i < size; i++)
    {
        if (library[i].IsEmpty)
        {
            return i;
        }
    }
    return -1;
}

void SetKey(int index)
{
    library[index].SetKey();
}

void PrintF(int index)
{
    library[index].PrintF();
}

void PrintAll(int size)
{
    for (int i = 0; i < size; i++)
    {
        if (!library[i].IsEmpty)
        {
            cout << "Персона " << i + 1 << endl;
            library[i].PrintF();
        }
    }
}

void Search(int size)
{
    int number;
    string name;
    cout << "Введите либо номер читательского билета, либо срок сдачи: "; cin >> number;
    cout << "Введите либо имя, либо фамилию, либо отчество, либо название книги: "; cin >> name;
    for (int i = 0; i < size; i++)
    {
        if (!library[i].IsEmpty)
        {
            if (library[i].IsSearc(number, name))
            {
                cout << "Нашлось совпадение у " << i + 1 << " персоны\n";
                library[i].PrintF();
            }
        }
    }
}

int SetLoad()
{
    char sim;
    cout << "Выберите поле(n/d): "; cin >> sim;
    switch (sim)
    {
    case 'n':
        return 0;
        break;
    case 'd':
        return 1;
        break;
    default:
        cout << "Нет такой команды!\n";
        return NULL;
        break;
    }
}

void SearcMinField(int size)
{
    int load = SetLoad(), min_data = library[0].Data, min_number = library[0].number, ind;
    switch (load)
    {
    case Field::Data:
        for (int i = 0; i < size; i++)
        {
            if (!library[i].IsEmpty)
            {
                if (library[i].Data < min_data or min_data == -1)
                {
                    min_data = library[i].Data;
                    ind = i + 1;
                }
            }
        }
        cout << "Персона под номером " << ind << " имеет минимальное поле Data\n";
        library[ind - 1].PrintF();
        break;
    case Field::number:
        for (int i = 0; i < size; i++)
        {
            if (!library[i].IsEmpty)
            {
                if (library[i].Data < min_number or min_number == -1)
                {
                    min_number = library[i].number;
                    ind = i + 1;
                }
            }
        }
        cout << "Персона под номером " << ind << " имеет минимальное поле number\n";
        library[ind - 1].PrintF();
        break;
    default:
        cout << "Повторите попытку ввода!\n";
        break;
    }
}

void swap(Library* l, Library* m)
{
    Library object;
    object.Data = l->Data;
    object.first_name = l->first_name;
    object.IsEmpty = l->IsEmpty;
    object.last_name = l->last_name;
    object.name_book = l->name_book;
    object.number = l->number;
    object.patronymic = l->patronymic;
    l->Data = m->Data;
    l->first_name = m->first_name;
    l->IsEmpty = m->IsEmpty;
    l->last_name = m->last_name;
    l->name_book = m->name_book;
    l->number = m->number;
    l->patronymic = m->patronymic;
    m->Data = object.Data;
    m->first_name = object.first_name;
    m->IsEmpty = object.IsEmpty;
    m->last_name = object.last_name;
    m->name_book = object.name_book;
    m->number = object.number;
    m->patronymic = object.patronymic;
}

int partitionNumber(Library l[], int start, int pivot)
{
    int i = start;
    while (i < pivot)
    {
        if (l[i].number > l[i].number && i == pivot - 1)
        {
            swap(l[i], l[pivot]);
            pivot--;
        }
        else if (l[i].number > l[pivot].number)
        {
            swap(l[pivot - 1], l[pivot]);
            swap(l[i], l[pivot]);
            pivot--;
        }
        else
        {
            i++;
        }
    }
    return pivot;
}

void quickSortMAXNumber(Library l[], int start, int end)
{
    if (start < end)
    {
        int pivot = partitionNumber(l, start, end);

        quickSortMAXNumber(l, start, pivot - 1);
        quickSortMAXNumber(l, pivot + 1, end);
    }
}

int partitionData(Library l[], int start, int pivot)
{
    int i = start;
    while (i < pivot)
    {
        if (l[i].Data > l[i].Data && i == pivot - 1)
        {
            swap(l[i], l[pivot]);
            pivot--;
        }
        else if (l[i].Data > l[pivot].Data)
        {
            swap(l[pivot - 1], l[pivot]);
            swap(l[i], l[pivot]);
            pivot--;
        }
        else
        {
            i++;
        }
    }
    return pivot;
}

void quickSortMAXData(Library l[], int start, int end)
{
    if (start < end)
    {
        int pivot = partitionData(l, start, end);

        quickSortMAXData(l, start, pivot - 1);
        quickSortMAXData(l, pivot + 1, end);
    }
}

void SortMAX(int size)
{
    int load = SetLoad();
    switch (load)
    {
    case Field::Data:
        cout << "Массив до сортировки:\n\n";
        PrintAll(size);
        quickSortMAXData(library, 0, size);
        cout << "\n\nСортировка по возрастанию по полю Data:\n\n";
        PrintAll(size);
        break;
    case Field::number:
        cout << "Массив до сортировки:\n\n";
        PrintAll(size);
        quickSortMAXNumber(library, 0, size);
        cout << "\n\nСортировка по возрастанию по полю number:\n\n";
        PrintAll(size);
        break;
    default:
        cout << "Такого поля нет, повторите ввод!\n";
        break;
    }
}

int partitionMINNumber(Library l[], int start, int pivot)
{
    int i = start;
    while (i < pivot)
    {
        if (l[i].number < l[i].number && i == pivot - 1)
        {
            swap(l[i], l[pivot]);
            pivot--;
        }
        else if (l[i].number < l[pivot].number)
        {
            swap(l[pivot - 1], l[pivot]);
            swap(l[i], l[pivot]);
            pivot--;
        }
        else
        {
            i++;
        }
    }
    return pivot;
}

void quickSortMINNumber(Library l[], int start, int end)
{
    if (start < end)
    {
        int pivot = partitionMINNumber(l, start, end);

        quickSortMINNumber(l, start, pivot - 1);
        quickSortMINNumber(l, pivot + 1, end);
    }
}

int partitionMINData(Library l[], int start, int pivot)
{
    int i = start;
    while (i < pivot)
    {
        if (l[i].Data < l[i].Data && i == pivot - 1)
        {
            swap(l[i], l[pivot]);
            pivot--;
        }
        else if (l[i].Data < l[pivot].Data)
        {
            swap(l[pivot - 1], l[pivot]);
            swap(l[i], l[pivot]);
            pivot--;
        }
        else
        {
            i++;
        }
    }
    return pivot;
}

void quickSortMINData(Library l[], int start, int end)
{
    if (start < end)
    {
        int pivot = partitionMINData(l, start, end);

        quickSortMINNumber(l, start, pivot - 1);
        quickSortMINNumber(l, pivot + 1, end);
    }
}

void sortMin(int size)
{
    int load = SetLoad();
    switch (load)
    {
    case Field::Data:
        cout << "Массив до сортировки:\n\n";
        PrintAll(size);
        quickSortMINData(library, 0, size);
        cout << "\n\nСортировка по убыванию по полю Data:\n\n";
        PrintAll(size);
        break;
    case Field::number:
        cout << "\nМассив до сортировки:\n\n";
        PrintAll(size);
        quickSortMINNumber(library, 0, size);
        cout << "\n\nСортировка по убыванию по полю number:\n\n";
        PrintAll(size);
        break;
    default:
        cout << "Такого поля нет, повторите ввод!\n";
        break;
    }
}

void ReadFile()
{
    ifstream in("Library.txt");
    string last_name, first_name, patronymic, name_book;
    int number, Data;
    if (in.is_open())
    {
        while (in >> first_name >> last_name >> patronymic 
            >> number >> name_book >> Data)
        {
            cout << "ФИО" << first_name << ' ' << last_name << ' '
                << patronymic << '\n'
                << "Номер читательского билета: " << number << endl
                << "Название книги: " << name_book << endl
                << "Срок сдачи: " << Data << endl;
        }
    }
    in.close();
}

void WriteFile(int size)
{
    ofstream out("Library.txt");
    if (out.is_open())
    {
        for (int i = 0; i < size; i++)
        {
            if (!library[i].IsEmpty)
            {
                out << library[i].first_name << ' ' << library[i].last_name << ' '
                    << library[i].patronymic << ' ' << library[i].number << ' '
                    << library[i].name_book << ' ' << library[i].Data << '\n';
            }
        }
    }
    out.close();
}

int main()
{
    setlocale(LC_ALL, "rus");
    int size = Count(), index;
    library = new Library[size];
    bool end = true;
    char simbol;
    do
    {
        cout << "Введите команду:\n"
            << "o - очистка структуроной переменной;\n"
            << "s - поиск свободной структурной переменной;\n"
            << "v - ввод элементов структуры с клавиатуры;\n"
            << "p - вывод на экран всех заполненных элементов;\n"
            << "a - вывод на экран всего массива"
            << "z - поиск в массиве структур элемента с заданным значением"
            << "n - поиск в массиве структуры с минимальным значением заданного поля;\n"
            << "M - сортировка массива структур в порядке возрастания;\n"
            << "m - сортировка массива структур в порядке убывания;\n"
            << "r - функция чтения файла с содержимым БД;\n"
            << "w - функция записи в файл содержимого БД;\n"
            << "x - выход из программы.\n";
        cin >> simbol;
        switch (simbol)
        {
        case 'o':
            system("cls");
            cout << "Введите индекс: "; cin >> index;
            Clear_One_Element(index);
            break;
        case 's':
            system("cls");
            if (Second_empty_element(size) != -1)
                cout << "Первый пустой элемент под индексом: " << Second_empty_element(size) << endl;
            else
                cout << "Весь массив полон!\n";
            break;
        case 'v':
            system("cls");
            cout << "Введите индекс: "; cin >> index;
            SetKey(index);
            break;
        case 'p':
            system("cls");
            cout << "Введите индекс: "; cin >> index;
            PrintF(index);
            break;
        case 'a':
            system("cls");
            PrintAll(size);
            break;
        case 'z':
            system("cls");
            Search(size);
            break;
        case 'n':
            system("cls");
            SearcMinField(size);
            break;
        case 'M':
            system("cls");
            SortMAX(size);
            break;
        case 'm':
            system("cls");
            sortMin(size);
            break;
        case 'r':
            system("cls");
            ReadFile();
            break;
        case 'w':
            system("cls");
            WriteFile(size);
            cout << "Данные записаны в файл Library.txt\n";
            break;
        case 'x':
            system("cls");
            cout << "Спасибо за проверку лабы!!\n";
            end = false;
            break;
        default:
            cout << "Такой функции нет, бдуьте внимательнее!\n";
            break;
        }
    } while (end);

    delete[] library;
}
