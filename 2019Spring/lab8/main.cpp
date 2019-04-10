#include <iostream>
#include <limits>
#include "lab8.h"

using namespace std;

void safe_cin_int(int* option);
void print_all_packages(Package packages[], int num_packages);
void print_all_robots(Robot robots[], int num_robots);

int main(int argc, const char * argv[]) {
    Package packages[MAX_PACKAGES];
    int num_packages = 0;
    Robot robots[MAX_ROBOTS];
    int num_robots = 0;

    cout << "loading txt files...\n";

    //load_robots(robots, &num_robots, "/Users/Samit/Data/HKUST/TA/COMP2011C/design/test/test/test/robots.txt");
    //load_packages(packages, &num_packages, "/Users/Samit/Data/HKUST/TA/COMP2011C/design/test/test/test/packages.txt");
    load_robots(robots, &num_robots, "robots.txt");
    load_packages(packages, &num_packages, "packages.txt");

    int option = 0;
    while (option != -1) {
        cout << "please select one of the following options:\n";
        cout << "0 - add a new robot.\n";
        cout << "1 - add a new package.\n";
        cout << "2 - list all the packages information.\n";
        cout << "3 - list all the robots information.\n";
        cout << "4 - deliver one package.\n";
        cout << "5 - deliver all packages given a robot.\n";
        cout << "-1 - quit the program.\n";
        safe_cin_int(&option);
        switch (option)
        {
            case 0:
            {
                int id;
                Location location;
                cout << "please type in the id, x coordinate, y coordinate for the new robot.\n";
                cin >> id >> location.x >> location.y;
                if (add_new_robot(robots, &num_robots, id, location)) {
                    cout << "the robot is successfully added.\n";
                }
                print_all_robots(robots, num_robots);
            }
                break;
            case 1:
            {
                int id;
                Location location, destination;
                cout << "please type in the id, x coordinate, y coordinate, x coordinate(destination), y coordinate(destination) for the new package.\n";
                cin >> id >> location.x >> location.y >> destination.x >> destination.y;
                if (add_new_package(packages, &num_packages, id, location, destination)) {
                    cout << "robot is successfully added.\n";
                }
            }
                break;
            case 2:
                print_all_packages(packages, num_packages);
                break;
            case 3:
                print_all_robots(robots, num_robots);
                break;
            case 4:
            {
                int package_id, robot_id;
                Package *package = nullptr;
                cout << "please type in the package(id) to be delivered.\n";
                cin >> package_id;

                package = query_packages_information_by_id(packages, num_packages, package_id);
                robot_id = delivery_one_package(package, robots, num_robots);
                if (robot_id != -1) {
                    cout << "package " << package_id << " has been successfully delivered by robot " << robot_id << ".\n";
                }else{
                    cout << "package delivery fails" << endl;
                }
            }
            break;
            case 5:
            {
                int  robot_id;
                Robot *robot = nullptr;
                cout << "please type in the robot(id) to use.\n";
                cin >> robot_id;

                robot = query_robots_information_by_id(robots, num_robots, robot_id);
                deliver_packages_with_one_robot(robot, packages, num_packages);


            }
            break;
            case -1:
                break;
            default:
                cout << "invalid option, please re-select an option.\n";
                break;
        }
    }

    return 0;
}

void safe_cin_int(int* option) {
    cin >> *option;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> *option;
    }
}

void print_all_packages(Package packages[], int num_packages)
{
    for (int i = 0; i < num_packages; ++i) {
        print_package_information(&packages[i]);
    }
}

void print_all_robots(Robot robots[], int num_robots)
{
    for (int i = 0; i < num_robots; ++i) {
        print_robot_information(&robots[i]);
    }
}
