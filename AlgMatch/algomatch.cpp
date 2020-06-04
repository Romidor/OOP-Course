#include "algomatch.h"
#include <algorithm>
#include <math.h>
#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <string>
#include <fstream>

namespace AlgoMatch
{
    /*файл, в котором хранятся настройки программы
    минимальное значение в выборке
    максимальное значение в выборке
    объем выборки
    точность оценки времени работы алгоритма
    */
    //отсортирован ли массив со случайной выборкой
    static bool isSorted = false;

    AlgoID& operator ++(AlgoID& c)
    {
        using IntType = typename std::underlying_type<AlgoID>::type;
        c = static_cast<AlgoID>(static_cast<IntType>(c) + 1);
        return c;
    }

    Configs& Configs::GetInstance()
    {
        static Configs instance;
        return instance;
    }

    Configs::Configs()
    {
        //забиваем поля данными из файла настроек
        std::ifstream stream(CONFIGS);
        std::string buf;

        std::getline(stream, buf);
        //Configs::lowerValue = stoi(buf);
        this->lowerValue = stoi(buf);

        std::getline(stream, buf);
        //Configs::highestValue = stoi(buf);
        this->highestValue = stoi(buf);

        std::getline(stream, buf);
        //Configs::volume = stoi(buf);
        this->volume = stoi(buf);

        std::getline(stream, buf);
        //Configs::accuracy = stoi(buf);
        this->accuracy = stoi(buf);

        std::getline(stream, this->algorithms);

        stream.close();

//        std::cout << "lower " << this->lowerValue;
//        std::cout << "hightest " << this->highestValue;
//        std::cout << "volume " << this->volume;
//        std::cout << "accuracy " << this->accuracy;
    }

    void Configs::Save()
    {
        //std::ofstream con(this->CONFIGS, std::ios_base::trunc);
        std::ofstream con(CONFIGS);
        con << this->lowerValue << '\n';
        con << this->highestValue << '\n';
        con << this->volume << '\n';
        con << this->accuracy << '\n';
        con << this->algorithms;
        con.close();
    }

    std::string Algorithm::GetName()
    {
        return name;
    }

    typename std::chrono::duration<double, std::micro> Algorithm::GetAtime()
    {
        return this->atime;
    }

    double Algorithm::GetTime()
    {
        return this->atime.count();
    }

    LinearSearch::LinearSearch()
    {
        this->name = "Linear";
    }

    void LinearSearch::Find(long long value, long long* begin, long long* end)
    {
        auto start = std::chrono::high_resolution_clock::now();
        while (begin != end)
        {
            if (*begin == value)
            {
                this->atime = std::chrono::high_resolution_clock::now() - start;
                return;
            }
            else ++begin;
        }
        this->atime = std::chrono::high_resolution_clock::now() - start;
    }

    BlockSearch::BlockSearch()
    {
        this->name = "Block";
    }

    void BlockSearch::Find(long long value, long long* begin, long long* end)
    {
        if (!isSorted)
        {
            std::sort(begin, end);
            isSorted = true;
        }
        auto start = std::chrono::high_resolution_clock::now();
        int step = static_cast<int>(sqrt(end - begin));
//        if (*begin > value)
//        {
//            this->atime = std::chrono::high_resolution_clock::now() - start;
//            return;
//        }
//        else
        {
            for (long long* i = begin + step; i <= end; i += step)
            {
                if (*i == value)
                {
                    this->atime = std::chrono::high_resolution_clock::now() - start;
                    return;
                }
                else if (*i > value)
                {
                    long long* l = i - step;
                    for (; i >= l; i--)
                    {
                        if (*i == value)
                        {
                            this->atime = std::chrono::high_resolution_clock::now() - start;
                            return;
                        }
                    }
                    this->atime = std::chrono::high_resolution_clock::now() - start;
                    return;
                }
            }
            this->atime = std::chrono::high_resolution_clock::now() - start;
            return;
        }
    }

    BinarySearch::BinarySearch()
    {
        this->name = "Binary";
    }

    void BinarySearch::Find(long long value, long long* begin, long long* end)
    {
        if (!isSorted)
        {
            std::sort(begin, end);
            isSorted = true;
        }
        auto start = std::chrono::high_resolution_clock::now();
        long long* mid;
        while (begin < end)
        {
            mid = begin + (end - begin) / 2;
            if (*mid >= value)
            {
                end = mid;
            }
            else
            {
                begin = mid + 1;
            }
        }
        if (*begin == value)
        {
            this->atime = std::chrono::high_resolution_clock::now() - start;
            return;
        }
        else
        {
            this->atime = std::chrono::high_resolution_clock::now() - start;
            return;
        }
    }

    Algorithm* Algorithm::CreateAlgorythm(AlgoID id)
    {
        Algorithm* p;
        switch (id)
        {
        case LINEAR:
        {
            p = new LinearSearch();
            break;
        }
        case BLOCK:
        {
            p = new BlockSearch();
            break;
        }
        case BINARY:
        {
            p = new BinarySearch();
            break;
        }
        default:
            p = nullptr;
            break;
        }

        return p;
    }

    AlgoMatchContainer::AlgoMatchContainer()
    {
        //nothing
    }

    AlgoMatchContainer::AlgoMatchContainer(std::string algos)
    {
        AddAlgosInList(algos);
    }

    void AlgoMatchContainer::AddAlgosInList(std::string algo)
    {
        AlgoID id = LINEAR;
        for (unsigned int i = 0; i < algo.length(); ++id, ++i)
        {
            if (algo[i] == '1')
                _container.push_back(Algorithm::CreateAlgorythm(id));
        }
    }

    void AlgoMatchContainer::AddAlgosInList(AlgoID algo)
    {
        if (algo != AlgoID::END)
            _container.push_back(Algorithm::CreateAlgorythm(algo));
    }

    Algorithm* AlgoMatchContainer::GetAt(unsigned int index)
    {
        return _container[index];
    }

    unsigned int AlgoMatchContainer::GetSize()
    {
        return _container.size();
    }

    void AlgoMatchContainer::Clear()
    {
        for (unsigned int i = 0; i < _container.size(); i++)
        {
            delete _container[i];
        }
        _container.clear();
    }

    AlgoMatchContainer::~AlgoMatchContainer()
    {
        this->Clear();
    }

    /*void AddAlgosInList(Container& cont, std::string algo)
    {
        AlgoID id = LINEAR;
        for (unsigned int i = 0; i < algo.length(); ++id, ++i)
        {
            if (algo[i] == '1')
                cont.push_back(Algorithm::CreateAlgorythm(id));
        }
    }*/
}
