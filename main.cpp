#include <iostream>
#include <vector>
using namespace std;

class Stage;
class Car;
class Worker;

class Stage {
   public:
    void add_worker(Worker* worker) { workers.push_back(worker); }

   private:
    vector<Worker*> workers;
    vector<Car> waiting_queue;
};


class Carwash {
   public:
    void add_stage(Stage stage) { stages.push_back(stage); }
    Worker* add_worker(int worker_time_coefficient) {
        Worker worker=Worker(workers.size(), worker_time_coefficient);
        workers.push_back(worker);
        return &worker;
    }

   private:
    vector<Stage> stages;
    vector<Worker> workers;
};

class Worker {
   public:
    Worker(int worker_id, int worker_time_coefficient) {
        id = worker_id;
        time_coefficient = worker_time_coefficient;
    }

   private:
    int id;
    int time_coefficient;
};

class Car {
   private:
    int id;
    int luxury_coefficient;
    int timeleft;
};

void handle_user_commands(Carwash& carwash) {
    string command;
    while (cin >> command) {
        if (!command.compare("add_stage")) {
            int n;
            Stage stage;
            for (int i = 0; i < n; i++) {
                int worker_time_coefficient;
                cin >> worker_time_coefficient;
                stage.add_worker(carwash.add_worker(worker_time_coefficient));
            }
            carwash.add_stage(stage);
        }
    }
}

int main() {
    Carwash carwash;
    handle_user_commands(carwash);

    return 0;
}