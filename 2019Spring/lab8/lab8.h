#ifndef lab8_hpp
#define lab8_hpp

#include <stdio.h>


#include <string>

const int MAX_PACKAGES = 20;
const int MAX_ROBOTS = 10;

struct Location;
struct Robot;
struct Package;

struct Location {
    double x;
    double y;
};

struct Robot {
    int id;
    Location location;
    Package* package;
    //int speed;

    Robot() = default;
    Robot(int id, const Location& loc, Package* pkg = nullptr) :
        id{id}, location{loc}, package{pkg} {}
};

struct Package {
    int id;
    Location location;
    Location destination;  //This is fixed after the package is instantiated.
    Robot* carrier;
    bool is_delivered;

    Package() = default;
    Package(int id, const Location& loc, const Location& dest, Robot* carrier = nullptr, bool delivered = false) :
        id{id}, location{loc}, destination{dest}, carrier{carrier}, is_delivered{delivered} {}
};


/**
 * load packages information from txt file
 *
 */
void load_packages(Package packages[], int * num_packages, std::string filename);

/**
 * add a new package to packages array
 *
 * @param packages array that stores all packages
 * @param num_packages pointer to integer that stores number of packages stored in packages
 * @param id id of the new package
 * @param location location of the package
 * @param destination destination of the package, i.e. the location of the receiver for the package.
 * @return true if the operation succeeds, false otherwise
 */
bool add_new_package(Package packages[], int * num_packages, int id, Location location, Location destination);

/**
 * load robots information from txt file
 *
 */
void load_robots(Robot robots[], int * num_robots, std::string filename);

/**
 * add a new robot to robots array
 *
 * @param robots array that stores all robots
 * @param num_robots pointer to integer that stores number of robots stored in robots
 * @param id id of the new robot
 * @param location location of the new robot
 * @return true if the operation succeeds, false otherwise
 */
bool add_new_robot(Robot robots[], int * num_robots, int id, Location location);

/**
 * load package robot relationship from txt file
 *
 */
void load_packages_in_robots(Package packages[], int num_packages, Robot robots[], int num_robots, std::string filename);

/**
 * add a new relationship between package and robot
 *
 * @param package_id the id of package to be played in the robot
 * @param robot_id the id of robot to play the package
 * @return true if the operation succeeds, false otherwise
 */
bool new_package_in_robot(Package packages[], int num_packages, Robot robots[], int num_robots, int package_id, int robot_id);

/**
 * get package information by id
 *
 * @return pointer to the package if id is valid, nullptr otherwise.
 */
Package * query_packages_information_by_id(Package packages[], int num_packages, int id);

/**
 * get robot information by id
 *
 * @return pointer to the robot if id is valid, nullptr otherwise.
 */
Robot * query_robots_information_by_id(Robot robots[], int num_robots, int id);

void print_package_information(const Package * package);

void print_robot_information(const Robot * robot);

double euclidean_distance(const Location * l1, const Location * l2);

/**
 * Given package id and location, find the closest robot that plays the package
 *
 * @return pointer to the robot if it exists, nullptr otherwise.
 */
Robot * recommend_robots(Package packages[], int num_packages, int package_id, const Location * location);

/**
 * Given a package, find the nearest robot to it with respect to Euclidean distance.
 *
 * @return pointer to the nearest robot if it exists, nullptr otherwise.
 */
Robot* find_nearest_robot(Package package, Robot robots[], int num_robots);

/**
 * To assign a delivery task, update the state of the package and the robot. Note that you only need to change package->carrier and robot->package after judging the assignment is legal.
 * @param package point to the package to be delivered
 * @param robot point to the robot to be assigned for the delivery task.
 * @return true if the assignment is done, return false if the assignment is not legal (e.g. the robot is not carrying a package.)
 */
bool assign_one_delivery_task(Package *package, Robot *robot);

/**
 * Given a robot, find the nearest package (w.r.t Euclidean distance) which has not been delivered from all existing packages.
 *
 * @return pointer to the package if it exists, nullptr otherwise.
 */
Package* find_nearest_undeliver_package(Robot robot, Package packages[], int num_packages);

//int compute_delivery_time(Package package, Robot robot);

/**
 * Update the current location and carrying package of the robot as the robot has delivered the package to its(i.e. the package's) destination.
 *
 *
 */
void update_state_upon_delivery_finished(Package *package, Robot *robot);

/**
 * task 2 main routine: deliver one package using the nearest robot
 *
 * @param package point to the package to be delivered
 * @param robots available robots
 * @param num_robots number of robots
 * @return robot_id to indicate which robot deliver the package, otherwise -1
 */
int delivery_one_package(Package *package, Robot robots[], int num_robots);


/**
 * Given an available robot and multiple packages to be delivered, compute the route for the robot to delivery all the packages based on greedy algorithm,
 * @param robot the available robot
 * @param packages packages to be delivered
 * @param num_packages number of packages in total (including the delivered packages)
 * @param deliver_order deliver order represented in package ID.
 * @return the number of package ID in the generated delivery plan
 */
int generate_delivery_order_for_one_robot(Robot robot, Package packages[], int num_packages, int deliver_order[]);


//void deliver_all_packages_with_one_robot(Robot robot, Package packages[], int num_packages, int deliver_orders[])
/**
 * task 3 main routine: deliver all packages using the one robot
 */
void deliver_packages_with_one_robot(Robot *robot, Package packages[], int num_packages);

#endif /* lab82_hpp */
