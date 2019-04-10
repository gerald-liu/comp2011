#include "lab8.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <cmath>
#include <limits>

using namespace std;

void load_robots(Robot robots[], int* num_robots, string filename)
{
    int id;
    Location location;
    ifstream ifs(filename);
    if (ifs.fail()){
        cout << "Fail in loading txt files" << endl;
        return; }
    //while (!ifs.eof()) {
    while(ifs >> id >> location.x >> location.y){
        add_new_robot(robots, num_robots, id, location);
    }
    ifs.close();
}

//TODO: implement this function
bool add_new_robot(Robot robots[], int* num_robots, int id, Location location) {
    if (*num_robots == MAX_ROBOTS)
        return false;
    robots[*num_robots] = Robot(id, location);
    ++(*num_robots);
}

void load_packages(Package packages[], int *num_packages, string filename)
{
    int id;
    Location location, destination;
    ifstream ifs(filename);
    if (ifs.fail()){
        cout << "Fail in loading txt files" << endl;
        return; }
    //while (!ifs.eof()) {
    while(ifs >> id >> location.x >> location.y >> destination.x >> destination.y){
        add_new_package(packages, num_packages, id, location, destination);
    }
    ifs.close();
}

//TODO: implement this function
bool add_new_package(Package packages[], int* num_packages, int id, Location location, Location destination) {
    if (*num_packages == MAX_PACKAGES)
        return false;
    packages[*num_packages] = Package(id, location, destination);
    ++(*num_packages);
}

Package * query_packages_information_by_id(Package packages[], int num_packages, int id)
{
    for (int i = 0; i < num_packages; ++i) {
        if (packages[i].id == id) {
            return &(packages[i]);
        }
    }
    return nullptr;
}

Robot * query_robots_information_by_id(Robot robots[], int num_robots, int id)
{
    for (int i = 0; i < num_robots; ++i) {
        if (robots[i].id == id) {
            return &(robots[i]);
        }
    }
    return nullptr;
}

void print_package_information(const Package * package)
{
    cout << "Package id: " << setw(3) << package->id << endl;
    cout << "Location: " << package->location.x << ", " << package->location.y<< endl;
    cout << "Destination: " << package->destination.x << ", " << package->destination.y<< endl;
    cout << "Is deliveried?: " << package->is_delivered << endl;
    if (package->carrier == nullptr)
        cout << "Carrier: nullptr" << endl;
    else
        cout << "Carrier id: " << package->carrier->id << endl;
    cout << '\n';
}

void print_robot_information(const Robot * robot)
{
    cout << "Robot id: " << setw(3) << robot->id << endl;
    cout << "Location: (" << robot->location.x << ", " << robot->location.y << ")\n";
    if (robot->package == nullptr){
        cout << "Package loaded: nullptr" << endl;
    }else{
        cout << "Package loaded: id " << robot->package->id <<endl;
    }
    cout << '\n';
}

double euclidean_distance(const Location * l1, const Location * l2)
{
    double x_diff = l1->x - l2->x;
    double y_diff = l1->y - l2->y;
    return sqrt(x_diff * x_diff + y_diff * y_diff);
}

// Comp class
template <typename T>
struct CloserTo {
    CloserTo(const Location& loc) : loc{ &loc } {}
    bool operator() (const T& a, const T& b) {
        return euclidean_distance(&a.location, loc) < euclidean_distance(&b.location, loc);
    }

    const Location* loc;
};

// Comp class
struct UndeliveredPkgCloserTo {
    UndeliveredPkgCloserTo(const Location& loc) : comp{ CloserTo<Package>(loc) } {}
    bool operator() (const Package& a, const Package& b) {
        return !a.is_delivered && !b.is_delivered && comp(a, b);
    }

    CloserTo<Package> comp;
};

// min_element(...) from <algorithm>
template <typename Iter, typename Compare>
Iter min_element(Iter first, Iter last, Compare comp) {
    if (first==last) return last;
    Iter smallest = first;

    while (++first!=last)
        if (comp(*first,*smallest))
            smallest=first;
    return smallest;
}

//TODO: implement this function
Robot* find_nearest_robot(Package package, Robot robots[], int num_robots) {
    if (!num_robots)
        return nullptr;
    // Robot* nearest = &robots[0];
    // for (int i=1; i<num_robots; ++i)
    //     if (euclidean_distance(&robots[i].location, &package.location) <
    //         euclidean_distance(&nearest->location, &package.location))
    //         nearest = &robots[i];
    // return nearest;
    return min_element(&robots[0], &robots[num_robots], CloserTo<Robot>(package.location));
}

//TODO: implement this function. Note: find the nearest package that is NOT delivered yet.
Package* find_nearest_undeliver_package(Robot robot, Package packages[], int num_packages) {
    if (!num_packages)
        return nullptr;
    // Package* nearest = nullptr;
    // for (int i=0; i<num_packages; ++i) {
    //     if (!nearest) {
    //         if (!packages[i].is_delivered) {
    //             nearest = &packages[i];
    //             continue;
    //         }
    //     }
    //     if (!packages[i].is_delivered && (
    //             euclidean_distance(&packages[i].location, &robot.location) <
    //             euclidean_distance(&nearest->location, &robot.location)
    //         ) )
    //         nearest = &packages[i];
    // }
    // return nearest;
    Package* first = nullptr;
    for (int i=0; i<num_packages; ++i) {
        if (!packages[i].is_delivered) {
            first = &packages[i];
            break; // get the first undelivered package
        }
    }
    if (!first)
        return nullptr;
    return min_element(first, &packages[num_packages], UndeliveredPkgCloserTo(robot.location));
}

//TODO: implement this function
// Note: package->is_delivered has already been set to true in generate_delivery_order_for_one_robot(...)
bool assign_one_delivery_task(Package *package, Robot *robot) {
    if (!package || !robot || robot->package || package->carrier)
        return false;
    robot->package = package;
    package->carrier = robot;
    return true;
}

void update_state_upon_delivery_finished(Package *package, Robot *robot){
    package->is_delivered = true;
    package->location = package->destination;

    robot->location = package->destination;
    robot->package = nullptr;
}

int delivery_one_package(Package *package, Robot robots[], int num_robots)
{
    Robot *nearest_robot = nullptr;

    nearest_robot = find_nearest_robot(*package, robots, num_robots);
    if (assign_one_delivery_task(package, nearest_robot)){
        //assume that the delivery is done in a moment
        update_state_upon_delivery_finished(package, nearest_robot);
        return nearest_robot->id;

    }else{
        return -1;
    }

}

int generate_delivery_order_for_one_robot(Robot robot, Package packages[], int num_packages, int deliver_order[]){
    // count the number of packages that are not delivered yet
    int num_packages_to_deliver = 0;
    for (int i=0; i<num_packages; ++i){
        if (packages[i].is_delivered == false)
            num_packages_to_deliver++;
        deliver_order[i] = -1;
    }

    //while (num_packages_delivered < num_packages){
    for (int i=0; i<num_packages_to_deliver; ++i){
        Package *nearest_package=nullptr;
        nearest_package = find_nearest_undeliver_package(robot, packages, num_packages);
        // delivery and update the package state
        robot.location = nearest_package->destination;
        nearest_package->is_delivered = true;
        // record the deliver order
        deliver_order[i] = nearest_package->id;
    }

    return num_packages_to_deliver;
}

void deliver_packages_with_one_robot(Robot *robot, Package packages[], int num_packages)
{
    int deliver_order[MAX_PACKAGES]={0};
    int num_delivery = 0;

    num_delivery = generate_delivery_order_for_one_robot(*robot, packages, num_packages, deliver_order);

    for (int i=0; i<num_delivery; ++i){
        Package *package=nullptr;
        int package_id = deliver_order[i];

        package = query_packages_information_by_id(packages, num_packages, package_id);
        // delivery and update the package state
        assign_one_delivery_task(package, robot);
        update_state_upon_delivery_finished(package, robot);
    }

    cout << "Finish delivering all packages. Delivery order: " << endl;

    for (int i=0; i<num_delivery; ++i){
        cout << "\t" << deliver_order[i];
    }
    cout << endl;
}
