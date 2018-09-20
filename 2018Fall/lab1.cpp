#include <iostream>

const char* zodiac[] = { "Rat", "Ox", "Tiger", "Rabbit",
    "Dragon", "Snake", "Horse", "Goat",
    "Monkey", "Rooster", "Dog", "Pig" };

const char* get_zodiac(int year) {
    int year_zodiac = (year - 1900) % 12;
    if (year_zodiac < 0) year_zodiac = 12 + year_zodiac; // for years before 1900
    return zodiac[year_zodiac];
}

int main() {
    int year;
    while (true) {
        std::cout << "Which year were you born in?\n";

        // input validation
        while (!(std::cin >> year)  || std::cin.get() != '\n') {
            std::cin.clear();
            std::cin.ignore(256, '\n');
            std::cout << "Which year were you born in?\n";
        }

        if (year < 1900) {
            std::cout << "Take care! Bye!\n";
            return 0;
        }
        else if (year > 2018) {
            std::cout << "You come from the future! I'm scared! Bye!\n";
            return 0;
        }
        else
            std::cout << "You were born in the year of " << get_zodiac(year) << "!\n\n";
    }
}