#include <iostream>
#include <random>
#include <vector>

using std::cin; using std::cout; using std::string;
using std::random_device; using std::default_random_engine; using std::uniform_int_distribution;
using std::vector;

class Nim {
public:
    Nim();
    void play();

private:
    bool game_over() const;
    int nim_sum() const;
    void ask_config();
    void print();
    void player_move();
    void ai_move();

    int num_heaps = 3; // >= 1
    int max_heap_size = 9; // > 1
    string players[2] = { "Player A", "Player B" };
    vector<int> heaps;
    bool is_single_player = true;
    bool is_player_a = true;
    int heap_to_move = 0;
    int num_to_move = 0;
};

Nim::Nim() {
    ask_config();

    random_device rd;
    default_random_engine rd_engine(rd());
    uniform_int_distribution<> dist(1, max_heap_size);

    for (int i = 0; i < num_heaps; i++)
        heaps.push_back(dist(rd_engine));
}

bool Nim::game_over() const {
    for (int i = 0; i < heaps.size(); i++)
        if (heaps[i]) return false;
    return true;
}

int Nim::nim_sum() const {
    int nimsum = heaps[0];
    for (int i = 1; i < heaps.size(); i++) 
        nimsum = nimsum ^ heaps[i]; 
    return nimsum; 
}

void Nim::ask_config() {
    do {
        cout << "Input the number of heaps: (greater than 0)\n";
        cin >> num_heaps;
    } while (num_heaps < 1);

    do {
        cout << "Input the max heap size: (greater than 1)\n";
        cin >> max_heap_size;
    } while (max_heap_size <= 1);
}

void Nim::print() {
    cout << "Current State:\n";
    for (int i = 0; i < heaps.size(); i++) 
        cout << "Heap " << i+1 << " : " << heaps[i] << "\n";
}

void Nim::player_move() {
    do {
        cout << "You're " << players[!is_player_a] << ", please make your move.\n" <<
            "Input the heap and the number of stones you want to remove.\n" <<
            "(e.g. To remove 3 stones from Heap 1, input \"1 3\", separated with SPACE)\n";
        cin >> heap_to_move;
        cin >> num_to_move;
    } while (heap_to_move > num_heaps || heap_to_move < 1 ||
        num_to_move > heaps[heap_to_move - 1] || num_to_move < 1 );

    heaps[heap_to_move - 1] -= num_to_move;
}

void Nim::ai_move() {
    int nimsum = nim_sum();

    // random behaviour when losing can be inevitable, waiting for the opponent to make a error
    if (nimsum == 0) {
        for (int i = 0; i < heaps.size(); i++) {
            if (heaps[i] > 0) {
                heap_to_move = i + 1;
                num_to_move = 1;
                heaps[i] -= num_to_move;
                return;
            }
        }
    }
    // move to reduce the nimsum to zero
    else {
        for (int i = 0; i < heaps.size(); i++) {
            int target_size = heaps[i] ^ nimsum;
            if (target_size < heaps[i] && target_size >= 0) {
                heap_to_move = i + 1;
                num_to_move = heaps[i] - target_size;
                heaps[i] = target_size;
                return;
            }
        }
    }
}

void Nim::play() {
    cout << "Player A's name: \n";
    cin >> players[0];

    do {
        cout << "You're " << players[0] << ". Do you want to play with another player (0) or the AI (1)?\n" <<
            "Input 0 or 1 as the answer.\n";
        cin >> is_single_player;
    } while (is_single_player != 0 && is_single_player != 1);

    if (!is_single_player) {
        cout << "Player B's name: \n";
        cin >> players[1];
    }
    else players[1] = "AI";

    print();

    while (!game_over()) {
        if (is_single_player && !is_player_a)
            ai_move();
        else
            player_move();

        cout << "\n" << players[!is_player_a] << "\'s turn, remove " << num_to_move
            << " stone(s) from Heap " << heap_to_move << ".\n";

        print();
        is_player_a = !is_player_a;
    }

    cout << "Game Over! " << players[is_player_a] << " wins!\n";
}

int main() {
    Nim game;
    game.play();
    return 0;
}