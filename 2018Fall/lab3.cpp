#include <iostream>
#include <random>

using std::cin; using std::cout;
using std::random_device; using std::mt19937; using std::uniform_real_distribution;

class PiEstimator {
public:
    void run();

private:
    bool is_in_circle(double x, double y) const;
    void print_start() const;
    void print_end() const;
    bool print_estimate() const;
    int ask_num_trials() const;
    double get_random_num();
    double estimate();

    int num_trials = -1 ;
    int num_success = -1;
    double pi = -1;
    mt19937 gen{ random_device{}() };
    uniform_real_distribution<> dist{ 0, 1 };
};

bool PiEstimator::is_in_circle(double x, double y) const { return x*x + y*y <= 1; }

void PiEstimator::print_start() const {
    cout << " __    ___   _      ___  ___   ___   _   _\n";  
    cout << "/ /`  / / \\ | |\\/| | |_)  ) ) / / \\ / | / |\n";
    cout << "\\_\\_, \\_\\_/ |_|  | |_|   /_/_ \\_\\_/ |_| |_|\n";  
    cout << " ____  __  _____  _   _       __   _____  ____      ___   _ \n";
    cout << "| |_  ( (`  | |  | | | |\\/|  / /\\   | |  | |_      | |_) | |\n";
    cout << "|_|__ _)_)  |_|  |_| |_|  | /_/--\\  |_|  |_|__     |_|   |_|\n\n";

    cout << "Imagine there are raindrops falling on a square with an inscribed circle ...\n\n";
}

void PiEstimator::print_end() const { cout << "Bye Bye!\n"; }

bool PiEstimator::print_estimate() const {
    if (pi != -1) {
        cout << "The number of raindrops inside the circle = " << num_success;
        cout << "\nThe estimated pi = " << pi << "\n\n";
        return true;
    }
    else {
        cout << "Error in estimation, please retry.\n\n";
        return false;
    }
}

int PiEstimator::ask_num_trials() const {
    int n;
    do {
        cout << "How many raindrops are there inside the square?\n";
        cout << "Enter the number (n > 0 and n is integer) (enter 0 to exit):";
        cin >> n; // assume the user only inputs integers
    } while (n < 0);
    return n;
}

double PiEstimator::get_random_num() { return dist(gen); }

double PiEstimator::estimate() {
    if (num_trials <= 0) return -1;
    num_success = 0;
    for (int i = 0; i < num_trials; i++)
        num_success += is_in_circle(get_random_num(), get_random_num());

    return 4.0 * num_success / num_trials;
}

void PiEstimator::run() {
    print_start();
    while (true) {
        num_trials = ask_num_trials();
        if (!num_trials) break;
        pi = estimate();
        print_estimate();
    }
    print_end();
}

int main() {
    PiEstimator estimator;
    estimator.run();
}