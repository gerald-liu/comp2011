/* Lab 5: Recursion - Alien Word Parsing */

#include <iostream>
#include <cstring>

using namespace std;

const int MAX_LEN = 256; 

bool correct_word(const char word[], int start, int end) {
    if (start == end)
        return (word[start] - 'a' >= 0 && word[start] - 'a' < 26);
    else if (word[end] == '@' || word[end] == '#')
        return correct_word(word, start, end-1);
    else if (word[end] == '|') {
        for (int i=start; i<end; i++)
            if (correct_word(word, start, i) && correct_word(word, i+1, end-1))
                return true;
        return false;
    }
    else
        return false;
}


int main() {
    char word[MAX_LEN];
    char c;
   
    do {
        cout << "Enter a word: ";
        cin >> word;
        if (correct_word(word, 0, strlen(word) - 1))
            cout << "The word is CORRECT!\n";
        else
            cout << "The word is INCORRECT!\n";
        cout << "Do you want to enter a new word ('Y'/'y' for Yes, 'N'/'n' for No)? ";
        cin >> c; 
    } while (c == 'Y' || c=='y');

    return 0;
}
