/* Lab 6: Voting - An election system
 * File: lab6_skeleton.cpp
 */

#include<iostream>
using namespace std;

const int MAX_SIZE = 50;
const int MAX_STRING_LENGTH = 20;

// strcpy from <cstring>
char* strcpy(char* dest, const char* src) {
    int i;
    for (i=0; src[i] != '\0'; ++i)
        dest[i] = src[i];
    dest[i]= '\0';
    return dest;
}

// structure definition of Participant 
struct Participant
{
    int id;
    char name[MAX_STRING_LENGTH];
    bool hasVoted; // true if voter has voted, false otherwise
    int numVotes; // number of votes received (if the participant is a candidate

    Participant() = default;
    Participant(int id, char name[], bool hasVoted, int numVotes)
        : id{id}, hasVoted{hasVoted}, numVotes{numVotes} { strcpy(this->name, name); }
};

// structure definition of Election
struct Election
{
    Participant participants[MAX_SIZE];
    int numCandidates;
    int numVoters;
    // the candidates will occupy the first numCandidates elements in the participants array, 
    // while the other voters will occupy the next numVoters elements in the participants array

    int getIdx(int id, bool isCandidate) {
        for(int i=0; i<numCandidates+(isCandidate ? 0 : numVoters); i++) {
            if (participants[i].id == id)
                return i;
        }
        return -1;
    }
};

/* Print the list of candidates
 * Parameter:
 *     - election: the Election struct object
 */
void printCandidates(const Election &election)
{
    cout << "The list of candidates: " << endl; 
    for (int i=0; i<election.numCandidates; i++)
         cout << "Candidate id: " << election.participants[i].id << "\tName:" << election.participants[i].name << endl; 
}

/* Setup the election 
 * - initialize all the member variables of the Election object
 * Parameters:
 *     - election: a Election struct object
 * Note: 
 *     - id for voter/candidate has to be unique
 *     - initialize all the member variables of the Participant elements
 */
void setup(Election &election) {
    int id;
    char name[MAX_STRING_LENGTH];

    for (int i=0; i<election.numCandidates; i++) {
        cout << "Enter the details of the candidates:\nCandidate No. " << i+1 << '\n';
        cout << "\tEnter his/her id: ";
        cin >> id;
        cout << "\tEnter Name: ";
        cin >> name;
        election.participants[i] = Participant(id, name, false, 0);
    }

    for (int i=0; i<election.numVoters; i++) {
        cout << "Enter the details of the voters:\nVoter No. " << i+election.numCandidates+1 << '\n';
        cout << "\tEnter his/her id: ";
        cin >> id;
        cout << "\tEnter Name: ";
        cin >> name;
        election.participants[election.numCandidates+i] = Participant(id, name, false, 0);
    }
}

/* Casting votes to some candidates by a specific voter given the voter id
 * Parameters:
 *     - election: the Election struct object
 *     - voterId: the voter's id
 *     - numVotes: the number of votes the voter wants to cast
 * Note:
 *     validates the following 
 *     - voter id has to be existed
 *     - candidate id has to be existed
 */
void voting(Election& election, int currentId, int numVotes) {
    if (election.getIdx(currentId, false) == -1) {
        cout << "Voter ID not found.\n";
        return;
    }

    int candId;
    for (int i=0; i<numVotes; i++) {
        cout << "Enter the candidate id you want to vote for:";
        cin >> candId;

        int candIdx = election.getIdx(candId, false);
        if (candIdx == -1 || candIdx >= election.numCandidates) {
            cout << "Candidate ID not found.\n";
            i--;
        }
        else {
            election.participants[candIdx].numVotes++;
            cout << "Vote " << i+1 << " done.\n";
        }
    }
}

/* Output the number of votes for each candidate
 * and announce the winner by finding who has the maximum number of votes 
 * Parameters:
 *     - election: the Election struct object
 * Note: if there is more than 1 candidate has the same number of maximum votes, 
 * announce it as a tie election.
 */

void resultTallying(const Election &election) {
    int winnerId;
    int maxVotes = 0;
    int votesDone = 0;

    for (int i=0; i<election.numCandidates; i++) {
        if (election.participants[i].numVotes > maxVotes) {
            winnerId = election.participants[i].id;
            maxVotes = election.participants[i].numVotes;
        }
        else if (election.participants[i].numVotes == maxVotes)
            winnerId = -1; // assume no id is -1

        cout << "The total number of votes for candidate " << election.participants[i].id <<
            ": " << election.participants[i].numVotes << "\n";

        votesDone += election.participants[i].numVotes;
    }

    cout << "The total number of votes cast for the whole election: " << votesDone << "\n";
    
    if (winnerId == -1)
        cout << "It's a tie.\n";
    else
        cout << "The winner is: " << winnerId << "\n";
}

// Main function for the election system
int main()
{
    // Create an election
    Election election;

    cout << "===============================" << endl;
    cout << " Welcome to the voting system! " << endl;
    cout << "===============================" << endl;
    cout << "Preparing ... " << endl;
    do {
        cout << "Enter how many candidates will run for the election: \n";
        cin >> election.numCandidates;
        cout << "Enter how many more voters: \n";
        cin >> election.numVoters;
    } while (((election.numCandidates + election.numVoters) > MAX_SIZE) || (election.numCandidates <= 0));
    cout << "\n";

    // the setup phase
    setup(election);

    int currentId;
    int numVotes = 0;
    // the voting phase
    cout << "Voting starts ..." << endl;
    printCandidates(election);

    char cmd;
    //for (int i = 0; i < (election.numCandidates + election.numVoters); i++)
    do {
        cout << "Enter the voter id to start voting:\n";
        cin >> currentId;

        do {
            cout << "Enter the number of votes to be cast (<" << election.numCandidates+1 << ") :\n";
            cin >> numVotes;
        } while (numVotes > election.numCandidates);

        voting(election, currentId, numVotes);

        cout << "Continue with the next voter? (y/n) ";
        cin >> cmd;
    } while ((cmd == 'y') || (cmd == 'Y'));

    cout << "Tallying votes ..." << endl;
    //the result-tallying phase
    resultTallying(election);

    cout << "End of the election!" << endl;
    return 0;
}
