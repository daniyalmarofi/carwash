#include <iostream>
#include <vector>
using namespace std;

class Car {
   private:
    int id;
    int luxury_coefficient;
    int timeleft;
};

class Worker {
   public:
    Worker(int worker_id, int worker_time_coefficient) {
        id = worker_id;
        time_coefficient = worker_time_coefficient;
    }
    int get_id(){
        return id;
    }
    int get_time_coefficient(){
        return time_coefficient;
    }

   private:
    int id;
    int time_coefficient;
};

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
        Worker worker(workers.size(), worker_time_coefficient);
        workers.push_back(worker);
        return &worker;
    }
    vector<Worker> get_workers(){
        return workers;
    }

   private:
    vector<Stage> stages;
    vector<Worker> workers;
};

void handle_user_commands(Carwash& carwash) {
    string command;
    while (cin >> command) {
        if (!command.compare("add_stage")) {
            int number_of_workers;
            cin >> number_of_workers;
            Stage stage;
            for (int i = 0; i < number_of_workers; i++) {
                int worker_time_coefficient;
                cin >> worker_time_coefficient;
                stage.add_worker(carwash.add_worker(worker_time_coefficient));
            }
            carwash.add_stage(stage);
            cout << "OK" << endl;
        }
    }
}

int main() {
    Carwash carwash;
    handle_user_commands(carwash);
    // for(Worker w:carwash.get_workers())
    //     cout<<w.get_id()<<" "<<w.get_time_coefficient()<<endl;

    return 0;
}