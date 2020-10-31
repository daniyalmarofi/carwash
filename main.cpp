#include <iostream>
#include <vector>
using namespace std;

class Stage;
class Car;
class Worker;

class Stage {
   public:
    Stage(vector<int> workers_time_coefficient) {
        for (auto worker : workers_time_coefficient)
            workers.push_back(Worker(worker));
    }

   private:
    vector<Worker> workers;
    vector<Car> waiting_queue;
};

class Carwah {
   public:
   void add_stage(Stage stage){
       stages.push_back(stage);
   }
   private:
    vector<Stage> stages;
};

class Worker {
   public:
    Worker(int coefficient) { time_coefficient = coefficient; }

   private:
    int id;
    int time_coefficient;
};

class Car {
   private:
    int id;
    int luxury_coefficient;
};

void handle_user_commands(Carwah& carwash) {
    string command;
    while (cin >> command) {
        if (!command.compare("add_stage")) {
            int n;
            for (int i = 0; i < n; i++) {
                int worker_time_coefficient;
                cin >> worker_time_coefficient;
                // carwash->add_stage();
                // Worker(worker_time_coefficient);
            }
        }
    }
}

int main() {
    Carwah carwah;
    handle_user_commands(carwash);

    return 0;
}