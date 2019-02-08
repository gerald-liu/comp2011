#include <iostream> // cout, cin
#include <cstdlib>  // srand, rand
#include <ctime>    // time

// uncomment the following line to make std the default namespace and then remove all "std::" in the code
// using namespace std;

const char* msgs[] = { "<Message 1>",
    "<Message 2>",
    "<Message 3>",
    "<Message 4>" };

int main() {
    std::cout << "Fortune Cookie\n";
    srand(time(NULL)); // initialize random seed
    char open = 'y'; // default choice for the first loop

    while (open == 'y') {
        std::cout << "Open a Fortune Cookie\n";

        int msg_idx = rand() % (sizeof(msgs)/sizeof(char*)); // random int in [0, length of message array)
        std::cout << "\"" << msgs[msg_idx] << "\"\n";

        while (true) {
            std::cout << "Crack open another one? (y/n)\n";

            std::cin.width(1); // input accepts only one char
            std::cin >> open;  // get the input
            std::cin.ignore(256, '\n'); // ignore redundant inputs

            if (open == 'y' || open == 'n') // input validation
                break;
        }
    }
}