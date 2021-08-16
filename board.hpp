#include <set>
#include <tuple>
#include <vector>
#include <cmath>
#include <iostream>

struct GameDisplay {
    int boardWidth, boardHeight, boardColors;
    std::vector<int> board;
};

struct GameState {
    int selectedColor, totalFilled;
    bool hasReachedEnd;
    double distanceFromEnd;

    std::set<int> neighbourColors;
    std::vector<int> selectedPath;
    std::vector<bool> lookaheadBoard;
};

GameDisplay readGame();

void fillNeighboursByDistance(GameDisplay game, GameState &state);
void fillNeighboursByFilling(GameDisplay game, GameState &state);
void getNeighbours(GameDisplay game, GameState &state, std::vector<std::tuple<int,int>> possibleNeighbours);
GameState getInitialState(GameDisplay game);
GameState lookaheadNeighboursByDistance(GameDisplay game, GameState state);
GameState lookaheadNeighboursByFilling(GameDisplay game, GameState state);
