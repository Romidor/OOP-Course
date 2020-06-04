#ifndef ALGOMATCH_H
#define ALGOMATCH_H

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

namespace AlgoMatch
{
enum AlgoID { LINEAR, BLOCK, BINARY, END };
    enum LineInSettings { LOWER_VALUE, HIGHEST_VALUE, VOLUME, ALGORITHMS };

    class Configs	//Синглтон Мэйерса (lazy initialization)
    {
    public:
        static Configs& GetInstance();
        void Save();

        int lowerValue;
        int highestValue;
        int volume;
        int accuracy;
        std::string algorithms;

    private:
        Configs* instance;
        const std::string CONFIGS = "D:\\algomatchconfigs.txt";

        Configs();
        Configs(const Configs&);
        Configs& operator = (Configs&);
    };

    class Algorithm		//Factory Method
    {
    public:
        virtual void Find(long long value, long long* begin, long long* end) = 0;
        virtual ~Algorithm() {}
        std::string GetName();
        typename std::chrono::duration<double, std::micro> GetAtime();
        double GetTime();
        static Algorithm* CreateAlgorythm(AlgoID id);
    protected:
        std::string name;
        std::chrono::duration<double, std::micro> atime;
        double time;
    };

    class LinearSearch : public Algorithm
    {
    public:
        LinearSearch();

        void Find(long long value, long long* begin, long long* end);
    };

    class BlockSearch : public Algorithm
    {
    public:
        BlockSearch();

        void Find(long long value, long long* begin, long long* end);
    };

    class BinarySearch : public Algorithm
    {
    public:
        BinarySearch();

        void Find(long long value, long long* begin, long long* end);
    };

    //string GetString(ifstream& in, LineInSettings line);
    /*{
        string res;
        int l;
        switch (line)
        {
        case LOWER_VALUE: {
            l = 1;
            break;
        }
        case HIGHEST_VALUE: {
            l = 2;
            break;
        }
        case VOLUME: {
            l = 3;
            break;
        }
        case ALGORITHMS: {
            l = 4;
            break;
        }
        default: {
            l = 1;
            break;
        }
        }

        for (int i = 0; i < l; i++)
        {
            getline(in, res);
        }
        return res;
    }*/

    class AlgoMatchContainer
    {
        typedef std::vector<Algorithm*> Container;//this vector contains Algorithm*
        typedef typename std::vector<Algorithm*>::iterator iter; //iterator for moving in Container
    public:
        AlgoMatchContainer();
        AlgoMatchContainer(std::string algos);
        ~AlgoMatchContainer();
        void AddAlgosInList(std::string algo);
        void AddAlgosInList(AlgoID algo);
        //double* GetResults();
        Algorithm* GetAt(unsigned int index);
        unsigned int GetSize();
        void Clear();
    private:
        //double* _results;
        Container _container;
    };
}

#endif // ALGOMATCH_H
