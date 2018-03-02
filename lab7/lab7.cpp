/*
 * lab7.cpp
 *
 * Created on: Oct 27, 2017
 *     Author: Weiyang Liu
 */

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_FILENAME_LEN = 32;    // assume the filename consists of less than 32 characters
const int MAX_FILE_LEN = 1000;      // assume the file contains less than 1000 words

class dict{
    public:
        string word;
        int num;
};

char conv(char c){
    if (c==' ' || c =='\n' || (c>='!'&&c<'0') || (c>'9'&&c<'A') || (c>'Z'&&c<'a') || (c>'z'&&c<='~')) return ' ';
    else if (c>='A'&&c<='Z') return c + 'a' - 'A';
    else return c;
}

int getWords(ifstream& ipf, string words[]){
    char c;
    int wordCount = 0;

    ipf.get(c);
    char cPrev = ' ';
    while (!ipf.eof()){
        c = conv(c);
        if (c != ' ') {
            if (cPrev == ' ') {
                wordCount++;
            }
            words[wordCount-1] += c;
        }
        cPrev = c;

        ipf.get(c);
    }
    return wordCount;
}

void getWordsLower(string words[], int fileLen, ofstream& opf){
    opf << "text size: " << fileLen << endl;
    for (int i=0; i<fileLen-1; i++)
        opf << words[i] << endl;
    opf << words[fileLen-1];
}

void getVocabStats(string words[], int fileLen, ofstream& opf){
    // insertion sort
    for (int i=1; i<fileLen; i++){
        string temp = words[i];
        int j = i-1;
        while (temp.compare(words[j])<0 && j>=0){
            words[j+1]=words[j];    // shifts element rightwards
            j--;
        }
        words[j+1]=temp;    // insert element in proper place
    }
    
    dict vocab[MAX_FILE_LEN / 2];
    int vocabIndex = 0;
    vocab[0].word = words[0];
    vocab[0].num = 1;
    for (int i=1; i<fileLen; i++){
        if (words[i].compare(words[i-1]) == 0) vocab[vocabIndex].num++;
        else {
            vocabIndex++;
            vocab[vocabIndex].word = words[i];
            vocab[vocabIndex].num = 1;
        }
    }

    opf << "text size: " << fileLen << endl;
    opf << "vocab size: " << ++ vocabIndex << endl;
    for (int i=0; i<vocabIndex-1; i++)
        opf << vocab[i].word << " " << vocab[i].num << endl;
    opf << vocab[vocabIndex-1].word << " " << vocab[vocabIndex-1].num;
}

int main(){
    int option;
    string ipfName; // input filename
    string opfName; // output filename

    chooseFile:
    cout << "Enter the input filename, or enter -1 to exit: " << endl;
    getline(cin, ipfName);
    if (ipfName == "-1") return -1;
    ifstream ipf(ipfName);
    if (!ipf) {
        cerr << "Error: Can't open \"" + ipfName + "\"\n";
        goto chooseFile;
    }

    string words[MAX_FILE_LEN];
    int fileLen = getWords(ipf, words);

    chooseFunction:
    do {
        cout << "Please select the fuction to run:" << endl;
        cout << "1 for a lower case wordlist, 2 for vocabulary statistics, -1 to exit" << endl;
        cin >> option;
    } while (option != 1 && option != 2 && option != -1);
    if (option == -1) return -1;

    opfName = ipfName;
    opfName.replace(opfName.find('.'), 4, option == 1 ? "_lower.txt" : "_dic.txt");
    ofstream opf(opfName);

    if (option == 1) getWordsLower(words, fileLen, opf);
    else getVocabStats(words, fileLen, opf);
    
    ipf.close();
    opf.close();

    int option2;
    cout << "Operation successful." << endl;
    cout << "Continue with the current file? 1 for yes, -1 to exit:" << endl;
    cin >> option2;
    if (option2 == 1) goto chooseFunction;
    else return 0;
}