#include "results.h"
#include "ui_results.h"
#include "algomatch.h"
#include <random>
#include <math.h>
#include <omp.h>

Results::Results(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Results)
{
    ui->setupUi(this);
    this->setWindowTitle("Results");
    Calculate();
}

Results::~Results()
{
    this->container.Clear();
    delete ui;
}

void Results::Calculate()
{
    using namespace AlgoMatch;

    Configs &conf = Configs::GetInstance();
    this->container.AddAlgosInList(conf.algorithms);

    std::random_device rd;
    std::mt19937 mersenne(rd());
    std::uniform_int_distribution<> dist(conf.lowerValue, conf.highestValue);
    //int sign[] = {-1, 1};
    long long* arr = new long long[conf.volume];
        //srand(time(0));
        for (int i = 0; i < conf.volume; ++i)
        {
            //arr[i] = dist(mersenne);
            arr[i] = i;
        }

    std::vector<double> atimes;
    std::vector<int> clockTimes;
    //std::sort(arr, arr + conf.volume);

    //std::cout << "value to find: " << valueToFind << '\n';
    int t = clock();

    long long val = dist(mersenne);
    double vals[] = {0.0, 0.0, 0.0};
    for (unsigned int i = 0; i < this->container.GetSize(); i++)
    {

        for (int j = 0; j < conf.accuracy; j++)
        {
            this->container.GetAt(i)->Find(val, arr, arr+conf.volume - 1);
            vals[i] += this->container.GetAt(i)->GetTime();
        }
        //vals[i] /= static_cast<double>(conf.accuracy);
    }
    std::cout << vals[0] << ' ' << vals[1] << ' ' << vals[2];
    /*for (unsigned int i = 0; i < container.GetSize(); ++i)
    {
        atimes.push_back(0.0);
        clockTimes.push_back(clock());

        long long valueToFind = dist(mersenne);
        for (int j = 0; j < conf.accuracy; ++j)
        {
            container.GetAt(i)->Find(valueToFind, arr, arr + conf.volume - 1);
            atimes.back() += (container.GetAt(i)->GetTime());
        }
        clockTimes.back() = clock() - clockTimes.back();
        atimes[i] /= static_cast<double>(conf.accuracy);
        std::cout << container.GetAt(i)->GetName() << '\t';
        std::cout << atimes.back() << '\n';
    }
    for (unsigned int i = 0; i < container.GetSize(); i++)
    {
        std::cout << "ctime" << i << ' ' << clockTimes[i] << '\n';
    }
    t = clock() - t;
    std::cout << "t = " << t << '\n';

    for (unsigned int i = 0; i < container.GetSize(); i++)
    {
        if (container.GetAt(i)->GetName() == "Linear")
            ui->linearValue_label->setNum(atimes[i]);
        else if (container.GetAt(i)->GetName() == "Block")
            ui->blockValue_label->setNum(atimes[i]);
        else if (container.GetAt(i)->GetName() == "Binary")
            ui->binaryValue_label->setNum(atimes[i]);
    }*/
    for (unsigned int i = 0; i < this->container.GetSize(); i++)
    {
        if (this->container.GetAt(i)->GetName() == "Linear")
        {
            ui->linearValue_label->setNum(vals[i]);
        }
        if (this->container.GetAt(i)->GetName() == "Block")
        {
            ui->blockValue_label->setNum(vals[i]);
        }
        if (this->container.GetAt(i)->GetName() == "Binary")
        {
            ui->binaryValue_label->setNum(vals[i]);
        }
    }

    this->container.Clear();
    delete [] arr;
}
