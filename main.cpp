#include <iostream>
#include <vector>
using namespace std;

class Stage;
class Car;
class Worker;

class Stage{
    vector<Worker> workers;
};

class Carwah{

    vector<Car> queue;
};

class Worker{
    private:
    int id;
    int sloth;

};

class Car{
    private:
    int id;
    int difficulty;

};

int main()
{
    cout << "Hello Wolrd!" << endl;

    return 0;
}