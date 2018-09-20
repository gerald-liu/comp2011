#include <iostream>
#include <random>
#include <vector>

using namespace std;

class Nim {
public:
    Nim();
    void play();

private:
	bool game_over();
    void print();
    int nim_sum();
    void player_move();
    void ai_move();

    const int NUM_HEAPS = 3; // >= 1
    const int MAX_HEAP_SIZE = 9; // > 1
	const char* players[2] = { "Player A", "Player B" };
    vector<int> heaps;
    bool is_single_player = true;
    bool is_player_a = true;
    int heap_to_move = 0;
    int num_to_move = 0;
};

Nim::Nim() {
	random_device rd;
	default_random_engine rd_engine(rd());
    uniform_int_distribution<> dist(1, MAX_HEAP_SIZE);

    for (int i=0; i<NUM_HEAPS; i++)
        heaps.push_back(dist(rd_engine));
}

bool Nim::game_over() {
	for (int i = 0; i < heaps.size(); i++)
		if (heaps[i]) return false;
	return true;
}

void Nim::print() {
	cout << "Current State:\n";
    for (int i=0; i<heaps.size(); i++) 
        cout << "Heap " << i+1 << " : " << heaps[i] << "\n";
}

int Nim::nim_sum() {
    int nimsum = heaps[0];
    for (int i=1; i<heaps.size(); i++) 
        nimsum = nimsum ^ heaps[i]; 
    return nimsum; 
}

void Nim::player_move() {
    do {
        cout << "Input the heap and the number of stones you want to remove.\n" <<
			"(e.g. To remove 3 stones from Heap 1, input \"1 3\", separated with SPACE)\n";
        cin >> heap_to_move;
        cin >> num_to_move;
    } while (heap_to_move > MAX_HEAP_SIZE || heap_to_move < 1 ||
        num_to_move > heaps[heap_to_move - 1] || num_to_move < 1 );

    heaps[heap_to_move - 1] -= num_to_move;
}

void Nim::ai_move() {
	int nimsum = nim_sum();

    // random behaviour when losing can be inevitable, waiting for the opponent to make a error
    if (nimsum == 0) {
        for (int i=0; i<heaps.size(); i++) {
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
        for (int i=0; i<heaps.size(); i++) {
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
    do {
        cout << "You're Player A. Do you want to play with another player (0) or the AI (1)?\n" <<
			"Input 0 or 1 as the answer.\n";
        cin >> is_single_player;
    } while (is_single_player != 0 && is_single_player != 1);

	print();

    while (!game_over()) {
		if (is_player_a) {
            cout << "You're Player A, please make your move.\n";
            player_move();
        }
        else {
            if (is_single_player) ai_move();
            else {
                cout << "You're Player B, please make your move.\n";
                player_move();
            }
        }

		cout << "\n" << players[!is_player_a] << "\'s turn, remove " << num_to_move
			<< " stones from Heap " << heap_to_move << ".\n";

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