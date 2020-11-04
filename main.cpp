#include <iostream>
#include <vector>
using namespace std;

void print_error(string message) { cerr << message << endl; }

class Car {
   public:
    Car(int _id, int _luxury_coefficient) {
        id = _id;
        luxury_coefficient = _luxury_coefficient;
    }
    int get_id() { return id; }
    int get_luxury_coefficient() { return luxury_coefficient; }
    int get_timeleft() { return timeleft; }
    void increase_timeleft() { timeleft += 1; }
    void set_timeleft(int worker_time_coefficient) {
        timeleft = worker_time_coefficient * luxury_coefficient;
    }
    void being_washed() {
        if (timeleft > 0) timeleft -= 1;
    }

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
        status = "Free";
    }
    int get_id() { return id; }
    int get_time_coefficient() { return time_coefficient; }
    string get_status() { return status; }
    void toggle_status() {
        if (status == "Free")
            status = "Working";
        else
            status = "Free";
    }
    Car* get_working_car() { return working_car; }
    void set_working_car(Car* _working_car) {
        if (status == "Free") {
            toggle_status();
            working_car = _working_car;
        }
    }
    void wash_the_car() { working_car->being_washed(); }

   private:
    int id;
    int time_coefficient;
    string status;
    Car* working_car;
};

class Stage {
   public:
    void add_worker(int worker_id, int worker_time_coefficient) {
        Worker worker(worker_id, worker_time_coefficient);
        workers.push_back(worker);
    }
    vector<Worker> get_workers() { return workers; }

    void add_car_to_stage(Car* waiting_car) {
        Worker* free_worker = get_free_worker();
        if (free_worker == NULL)
            waiting_queue.push_back(waiting_car);
        else if (waiting_queue.size() == 0) {
            waiting_car->set_timeleft(free_worker->get_time_coefficient());
            free_worker->set_working_car(waiting_car);
        }
    }

    vector<Car*> get_wating_cars() { return waiting_queue; }

    void wash_the_cars() {
        for (int i = 0; i < workers.size(); i++)
            if (workers[i].get_status() == "Working") {
                workers[i].wash_the_car();
            }
    }

    Car* find_finished_car() {
        Worker* finished_worker = find_finished_worker();
        if (finished_worker == NULL) return NULL;
        finished_worker->toggle_status();
        return finished_worker->get_working_car();
    }

   private:
    Worker* find_finished_worker() {
        for (int i = 0; i < workers.size(); i++) {
            if (workers[i].get_status() == "Working" &&
                workers[i].get_working_car()->get_timeleft() == 0) {
                return &workers[i];
            }
        }
        return NULL;
    }

    Worker* get_free_worker() {
        for (int i = 0; i < workers.size(); i++)
            if (workers[i].get_status() == "Free") return &workers[i];
        return NULL;
    }
    vector<Worker> workers;
    vector<Car*> waiting_queue;
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

    void add_car(int car_luxury_coefficient) {
        Car new_car(cars.size(), car_luxury_coefficient);
        cars.push_back(new Car(new_car));
        waiting_queue.push_back(cars.back());
    }

    vector<Car*> get_cars() { return cars; }

    void add_a_car_to_first_stage() {
        stages.front().add_car_to_stage(waiting_queue.front());
        waiting_queue.erase(waiting_queue.begin());
    }

    void add_car_to_finished_cars(Car* finished_car) {
        finished_cars.push_back(finished_car);
    }

    void advance_cars_to_next_step() {
        for (int i = 0; i < stages.size(); i++) {
            Car* finished_car = stages[i].find_finished_car();
            if (finished_car != NULL) {
                if (i == stages.size() - 1)
                    add_car_to_finished_cars(finished_car);
                else {
                    stages[i + 1].add_car_to_stage(finished_car);
                    finished_car->increase_timeleft();
                }
            }
        }
    }

    void advance_time() {
        advance_cars_to_next_step();
        for (int i = 0; i < stages.size(); i++) {
            stages[i].wash_the_cars();
        }
        add_a_car_to_first_stage();
    }

    Stage get_stage_by_id(int stage_id) { return stages[stage_id]; }

   private:
    int number_of_workers;
    vector<Stage> stages;
    vector<Car*> cars;
    vector<Car*> waiting_queue;
    vector<Car*> finished_cars;
};

//****************************************************************

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

Carwash add_car_command(Carwash carwash) {
    int car_luxury_coefficient;
    cin >> car_luxury_coefficient;
    carwash.add_car(car_luxury_coefficient);
    return carwash;
}

Carwash advance_time_command(Carwash carwash) {
    int time_step;
    cin >> time_step;
    while (time_step > 0) {
        carwash.advance_time();
        time_step -= 1;
    }
    return carwash;
}

void show_stage_info_command(Carwash carwash) {
    int stage_id;
    cin >> stage_id;
    Stage the_stage = carwash.get_stage_by_id(stage_id);
    cout << "Stage ID: " << stage_id << endl;
    for (auto worker : the_stage.get_workers()) {
        cout << "Worker ID: " << worker.get_id() << endl;
        if (worker.get_status() == "Free") {
            cout << "Free" << endl;
        } else {
            Car* working_on_car = worker.get_working_car();
            cout << "Car ID: " << working_on_car->get_id() << endl;
            cout << "Luxury coefficient: "
                 << working_on_car->get_luxury_coefficient() << endl;
            cout << "Time left: " << working_on_car->get_timeleft() << endl;
        }
    }
    cout << "Cars in waiting queue:" << endl;
    for (auto waiting_car : the_stage.get_wating_cars()) {
        cout << "Car ID: " << waiting_car->get_id() << endl;
        cout << "Luxury coefficient: " << waiting_car->get_luxury_coefficient()
             << endl;
    }
}

void print_OK() { cout << "OK" << endl; }

Carwash handle_user_commands(Carwash carwash) {
    string command;
    while (cin >> command) {
        if (!command.compare("add_stage")) {
            carwash = add_stage_command(carwash);
            print_OK();
        }
        if (!command.compare("add_car")) {
            carwash = add_car_command(carwash);
            print_OK();
        }
        if (!command.compare("advance_time")) {
            carwash = advance_time_command(carwash);
            print_OK();
        }
        if (!command.compare("show_stage_info")) {
            show_stage_info_command(carwash);
        }
    }
    return carwash;
}

int main() {
    Carwash carwash;
    carwash = handle_user_commands(carwash);
    for (Stage s : carwash.get_stages()) {
        vector<Worker> workers = s.get_workers();
        // cout << "stage\t"
        //      << "count: " << workers.size() << endl;
        // for (Worker w : workers) {
        //     cout << w.get_id() << " " << w.get_time_coefficient() << endl;
        // }
        // for (auto c : s.get_wating_cars()) {
        //     cout << "w: " << c->get_luxury_coefficient() << endl;
        // }
    }
    // for(Car c:carwash.get_cars()){
    //     cout<<c.get_id()<<" : "<<c.get_luxury_coefficient()<<endl;
    // }

    return 0;
}