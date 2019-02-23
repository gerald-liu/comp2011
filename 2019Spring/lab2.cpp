#include <iostream>

void print_state(const int start[2], const int end[2], const int move[2], bool boat) {
    // print current state (assume the starting side is the right side)
    std::cout << "Left side --------------------------- Right side\n";
    if (boat) { // moving from the starting side to the destination
        std::cout << end[1] << 'C' << end[0] << "M                                  ";
        std::cout << start[1] << 'C' << start[0] << "M, ";
        std::cout << "Boat(" << move[1] << 'C' << move[0] << "M)\n";
    }
    else {
        std::cout << end[1] << 'C' << end[0] << "M, ";
        std::cout << "Boat(" << move[1] << 'C' << move[0] << "M)                      ";
        std::cout << start[1] << 'C' << start[0] << "M\n";
    }
}

int main() {
    int start[2] = {3, 3}; // number of missionaries and cannibals on the starting side
    int end[2] = {0, 0}; // total number of missionaries and cannibals
    bool boat = true; // the boat is on the starting side
    int boat_size = 2; // the boat can carry at most 2 people
    bool get_on = true; // get on the boat at the beginning
    int move[2] = {0, 0};
    bool loss = false;

    std::cout << "Game Start!\n";
    while (start[0] || start[1] || boat) { // while the starting side has people or boat
        int* this_side;
        if (boat)
            this_side = start;
        else
            this_side = end;
        
        while (!get_on) { // get off the boat first if necessary
            print_state(start, end, move, boat);

            int off[2] = {0, 0};
            char ready = 'n';

            std::cout << "How many missionaries get OFF the boat?\n";
            std::cin >> off[0];
            std::cout << "How many cannibals get OFF the boat?\n";
            std::cin >> off[1];

            if (off[0] > move[0] || off[1] > move[1]) {
                std::cout << "There are not enough people here. Please re-enter.\n";
                continue;
            }

            std::cout << "Ready to get off? (y/n)\n";
            std::cin >> ready;
            while (ready != 'y' && ready != 'n') {
				std::cout << "Please input y/n.";
				std::cin >> ready;
			}
            if (ready == 'n')
                continue;

            move[0] -= off[0];
            move[1] -= off[1];
            this_side[0] += off[0];
            this_side[1] += off[1];
            get_on = true;
        }

        while (get_on) { // get on the boat now
            print_state(start, end, move, boat);

            int on[2] = {0, 0};
            char ready = 'n';

            std::cout << "How many missionaries get ON the boat?\n";
            std::cin >> on[0];
            std::cout << "How many cannibals get ON the boat?\n";
            std::cin >> on[1];

            if (on[0] > this_side[0] || on[1] > this_side[1]) {
                std::cout << "There are not enough people here. Please re-enter.\n";
                continue;
            }

            std::cout << "Ready to go? (y/n)\n";
            std::cin >> ready;
            while (ready != 'y' && ready != 'n') {
				std::cout << "Please input y/n.";
				std::cin >> ready;
			}
            if (ready == 'n')
                continue;

            move[0] += on[0];
            move[1] += on[1];
            this_side[0] -= on[0];
            this_side[1] -= on[1];
            get_on = false;
        }

        boat = !boat;

        if (this_side[0] > 0 && this_side[1] > this_side[0]) { // more cannibals than missionaries
            loss = true;
            break;
        }
    }

    if (loss)
        std::cout << "You lose!\n";
    else
        std::cout << "Congratulations! You manage to move everyone to the destination!\n";
}
