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
    int get_id() { return id; }
    int get_time_coefficient() { return time_coefficient; }

   private:
    int id;
    int time_coefficient;
};

class Stage {
   public:
    void add_worker(int worker_id, int worker_time_coefficient) {
        Worker worker(worker_id, worker_time_coefficient);
        workers.push_back(worker);
    }
    vector<Worker> get_workers() { return workers; }

   private:
    vector<Worker> workers;
    vector<Car> waiting_queue;
};

class Carwash {
   public:
    Carwash() { number_of_workers = 0; }
    void add_stage(Stage stage) { stages.push_back(stage); }
    int get_new_worker_id() {
        number_of_workers += 1;
        return number_of_workers - 1;
    }
    vector<Stage> get_stages() { return stages; }

   private:
    vector<Stage> stages;
    int number_of_workers;
};

Carwash add_stage_command(Carwash carwash) {
    int number_of_stage_workers;
    cin >> number_of_stage_workers;
    Stage stage;
    for (int i = 0; i < number_of_stage_workers; i++) {
        int worker_time_coefficient;
        cin >> worker_time_coefficient;
        stage.add_worker(carwash.get_new_worker_id(), worker_time_coefficient);
    }
    carwash.add_stage(stage);
    return carwash;
}

void print_OK() { cout << "OK" << endl; }

Carwash handle_user_commands(Carwash carwash) {
    string command;
    while (cin >> command) {
        if (!command.compare("add_stage")) {
            carwash = add_stage_command(carwash);
            print_OK();
        }
    }
    return carwash;
}

int main() {
    Carwash carwash;
    carwash = handle_user_commands(carwash);
    // for (Stage s : carwash.get_stages()) {
    //     vector<Worker> workers = s.get_workers();
    //     cout << "stage\t"
    //          << "count: " << workers.size() << endl;
    //     for (Worker w : workers) {
    //         cout << w.get_id() << " " << w.get_time_coefficient() << endl;
    //     }
    // }

    return 0;
}