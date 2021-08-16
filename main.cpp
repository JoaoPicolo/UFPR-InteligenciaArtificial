#include "board.hpp"

using namespace std;

int main() {
    GameDisplay game = readGame();
    GameState state = getInitialState(game);

    int boardSize = game.boardHeight * game.boardWidth;
    while(state.totalFilled != boardSize) {
        if(state.hasReachedEnd) {
            state = lookaheadNeighboursByFilling(game, state);
        }
        else {
            state = lookaheadNeighboursByDistance(game, state);
        }
    }

    // Print selected path
    cout << state.selectedPath.size() << "\n";
    for(auto path: state.selectedPath) {
        cout << path << " ";
    }
    cout << "\n";

    return 0;
}