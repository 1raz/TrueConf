#include "trueconf.h"
using namespace std;

//    Выполнил Суворов Д.В.
//    1.заполнить случайными числами от 1 до 9 значения контейнеров vector[i] и map[i];

//    2.удалить случайное число элементов (не более 15) в каждом контейнере;
//    3.после этого провести синхронизацию,
//    чтобы в vector и map остались только имеющиеся в обоих контейнерах элементы (дубликаты не удалять).

TrueConf::TrueConf()

{
    cout << "Enter the number of items in the containers: ";
    size_t sizeOfContainer; // Размер map и vector
    cin >> sizeOfContainer;
    map <int, int> Map;
    vector <int> vec(sizeOfContainer);
    randomFilling(Map, sizeOfContainer, randomNumber(10, 20)); // Заполнение map случайными значениями.
    randomFilling(vec, sizeOfContainer, randomNumber(21, 40)); // Заполнение vector случайными значениями.
    randomDelete(Map, randomNumber(41, 60));     // Удаление случайного количества элементов из контейнера.
    randomDelete(vec, randomNumber(61, 80));
    cout << "Start map: ";
    printMap(Map);
    cout << endl << "Start vector: ";
    printVector(vec);
    cout << endl;
    syncing(vec, Map); // Синхронизация контейнеров.
}
// Удаление из контейнера случайного количества элементов(от 1 до 15)
template<typename T>
void TrueConf::randomDelete(T &container, const int &seed)
{
    int number = 0;
    int sizeOfContainer = static_cast<int>(container.size());
    if(sizeOfContainer < 15)
        number = randomNumber(1, sizeOfContainer - 1, seed);
    else
        number = randomNumber(1, 15);
    for(int i = 0; i < number; ++i)
    {
        container.erase(container.begin());
    }
}
//      Функция синхронизации двух контейнеров.
//      В цикле переменным countMap и countVector присваивается
//      количество повторений каждой цифры, затем удаляются лишние
//      элементы в каждом контейнере.
template<typename T, typename T1>
void TrueConf::syncing(T &Vector, T1 &Map)
{
    int countMap, countVector, result;
    for(int i = 0; i < 10; ++i)
    {
        countMap = static_cast<int>(count_if(Map.begin(), Map.end(),
                                             [i](const pair <int, int> &p)
        {return p.second == i;}));
        countVector = static_cast<int>(count(Vector.begin(), Vector.end(), i));
        result = countVector - countMap;
        if(result > 0) // Количество лишних элементов(result) удаляется из vector.
        {
            for(int j = 0; j < result; ++j)
            {
                auto it = find(Vector.begin(), Vector.end(), i);
                if(it != Vector.end())
                    Vector.erase(it);
            }
        }
        else //Количество лишних элементов(result) удаляется из map.
        {
            for(auto pos = Map.begin(); pos != Map.end();)
            {
                if(result != 0 && pos->second == i)
                {
                    pos = Map.erase(pos);
                    ++result;
                }
                else
                {
                    ++pos;
                }
            }
        }
    }
    cout << "Final map: ";
    printMap(Map);
    cout << endl << "Final vector: ";
    printVector(Vector);
}
//    Заполнение контейнера случайными значениями.
//    map заполняется таким образом - ключ это порядковый номер(0, 1, 2...i), значение - случайное число.
template <typename T>
void TrueConf::randomFilling(T &emptyContainer, const size_t &size, const int &seed)
{
    for(size_t i = 0; i < size; ++i)
    {
        emptyContainer[i] = randomNumber(1, 9, static_cast<int>(i) * seed);
    }
}
//      Получение случайного числа.
//      bottom - нижняя граница числа, top - верхняя, seed - число для повышения случайности.
int TrueConf::randomNumber(const int &bottom, const int &top, const int &seed)
{
    time_t seconds = time(nullptr) + seed;
    mt19937 random(seconds);
    uniform_int_distribution <int> uid(bottom, top); // распределение
    return int(uid(random));
}
//        Функция печати в консоль значений словаря.
void TrueConf::printMap(const map<int, int> &Map)
{
    for(const auto &[f, s]: Map)
    {
        cout  << s << " ";
    }
}
//          Функция печати элементов вектора.
void TrueConf::printVector(const vector<int> &vec)
{
    for(const auto &it: vec)
    {
        cout << it << " ";
    }
}
