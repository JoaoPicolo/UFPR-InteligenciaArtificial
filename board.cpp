#include "board.hpp"

using namespace std;

GameDisplay readGame() {
    int n, m, k;

    cin >> n;
    cin >> m;
    cin >> k;

    vector<int> board(n * m);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> board[i*m + j];
        }
    }

    GameDisplay display;
    display.boardHeight = n;
    display.boardWidth = m;
    display.boardColors = k;
    display.board = board;

    return display;
}

void fillNeighboursByDistance(GameDisplay game, GameState &state) {
    int lines = game.boardHeight, cols = game.boardWidth;
    int index, diffX, diffY;
    double localDistance, minimumDistance = state.distanceFromEnd;

    vector<tuple<int,int>> positions; // Array of coordinates (x,y) on board
    vector<tuple<int,int>> possibleNeighbours;
    vector<bool> visitedLookup(lines * cols);
    positions.push_back(make_tuple(0,0));
    visitedLookup[0] = true;

    for(unsigned int i = 0; i < positions.size(); i++) {
        tuple<int,int> position = positions[i];

        int x = get<0>(position), y = get<1>(position);
    
        if(!state.lookaheadBoard[y*cols + x]) {
            state.lookaheadBoard[y*cols + x] = true;
            state.totalFilled += 1;
        }
    
        // Verifies on x-axis
        if(x == 0) { // Is on left column
            index = y*cols + (x + 1);
            if(game.board[index] == state.selectedColor || state.lookaheadBoard[index]) {
                if(!visitedLookup[index]) {
                    diffX = (x + 1) - (game.boardWidth - 1);
                    diffY = y - (game.boardHeight - 1);
                    localDistance = sqrt(diffX*diffX + diffY*diffY);
                    if(localDistance < minimumDistance)
                        minimumDistance = localDistance;
                    positions.push_back(make_tuple(x + 1, y));
                    visitedLookup[index] = true;
                }
            }
            else {
                if(!visitedLookup[index]) {
                    possibleNeighbours.push_back(make_tuple(x + 1, y));
                    visitedLookup[index] = true;
                }
            }
        }
        else if(x == cols - 1) { // Is on right column
            index = y*cols + (x - 1);
            if(game.board[index] == state.selectedColor || state.lookaheadBoard[index]) {
                if(!visitedLookup[index]) {
                    diffX = (x - 1) - (game.boardWidth - 1);
                    diffY = y - (game.boardHeight - 1);
                    localDistance = sqrt(diffX*diffX + diffY*diffY);
                    if(localDistance < minimumDistance)
                        minimumDistance = localDistance;
                    positions.push_back(make_tuple(x - 1, y));
                    visitedLookup[index] = true;
                }
            }
            else {
                if(!visitedLookup[index]) {
                    possibleNeighbours.push_back(make_tuple(x - 1, y));
                    visitedLookup[index] = true;
                }
            }
        }
        else { // Is on middle of board
            index = y*cols + (x + 1);
            if(game.board[index] == state.selectedColor || state.lookaheadBoard[index]) {
                if(!visitedLookup[index]) {
                    diffX = (x + 1) - (game.boardWidth - 1);
                    diffY = y - (game.boardHeight - 1);
                    localDistance = sqrt(diffX*diffX + diffY*diffY);
                    if(localDistance < minimumDistance)
                        minimumDistance = localDistance;
                    positions.push_back(make_tuple(x + 1, y));
                    visitedLookup[index] = true;
                }
            }
            else {
                if(!visitedLookup[index]) {
                    possibleNeighbours.push_back(make_tuple(x + 1, y));
                    visitedLookup[index] = true;
                }
            }
            
            index = y*cols + (x - 1);
            if(game.board[index] == state.selectedColor || state.lookaheadBoard[index]) {
                if(!visitedLookup[index]) {
                    diffX = (x - 1) - (game.boardWidth - 1);
                    diffY = y - (game.boardHeight - 1);
                    localDistance = sqrt(diffX*diffX + diffY*diffY);
                    if(localDistance < minimumDistance)
                        minimumDistance = localDistance;
                    positions.push_back(make_tuple(x - 1, y));
                    visitedLookup[index] = true;
                }
            }
            else {
                if(!visitedLookup[index]) {
                    possibleNeighbours.push_back(make_tuple(x - 1, y));
                    visitedLookup[index] = true;
                }
            }
        }

        // Verifies on y-axis
        if(y == 0) { // Is on first line
            index = (y + 1)*cols + x;
            if(game.board[index] == state.selectedColor || state.lookaheadBoard[index]) {
                if(!visitedLookup[index]) {
                    diffX = x - (game.boardWidth - 1);
                    diffY = (y + 1) - (game.boardHeight - 1);
                    localDistance = sqrt(diffX*diffX + diffY*diffY);
                    if(localDistance < minimumDistance)
                        minimumDistance = localDistance;
                    positions.push_back(make_tuple(x, y + 1));
                    visitedLookup[index] = true;
                }
            }
            else {
                if(!visitedLookup[index]) {
                    possibleNeighbours.push_back(make_tuple(x, y + 1));
                    visitedLookup[index] = true;
                }
            }
        }
        else if(y == lines - 1) { // Is on last line
            index = (y - 1)*cols + x;
            if(game.board[index] == state.selectedColor || state.lookaheadBoard[index]) {
                if(!visitedLookup[index]) {
                    diffX = x - (game.boardWidth - 1);
                    diffY = (y - 1) - (game.boardHeight - 1);
                    localDistance = sqrt(diffX*diffX + diffY*diffY);
                    if(localDistance < minimumDistance)
                        minimumDistance = localDistance;
                    positions.push_back(make_tuple(x, y - 1));
                    visitedLookup[index] = true;
                }
            }
            else {
                if(!visitedLookup[index]) {
                    possibleNeighbours.push_back(make_tuple(x, y - 1));
                    visitedLookup[index] = true;
                }
            }
        }
        else { // Is on middle of board
            index = (y + 1)*cols + x;
            if(game.board[index] == state.selectedColor || state.lookaheadBoard[index]) {
                if(!visitedLookup[index]) {
                    diffX = x - (game.boardWidth - 1);
                    diffY = (y + 1) - (game.boardHeight - 1);
                    localDistance = sqrt(diffX*diffX + diffY*diffY);
                    if(localDistance < minimumDistance)
                        minimumDistance = localDistance;
                    positions.push_back(make_tuple(x, y + 1));
                    visitedLookup[index] = true;
                }
            }
            else {
                if(!visitedLookup[index]) {
                    possibleNeighbours.push_back(make_tuple(x, y + 1));
                    visitedLookup[index] = true;
                }
            }

            index = (y - 1)*cols + x;
            if(game.board[index] == state.selectedColor || state.lookaheadBoard[index]) {
                if(!visitedLookup[index]) {
                    diffX = x - (game.boardWidth - 1);
                    diffY = (y - 1) - (game.boardHeight - 1);
                    localDistance = sqrt(diffX*diffX + diffY*diffY);
                    if(localDistance < minimumDistance)
                        minimumDistance = localDistance;
                    positions.push_back(make_tuple(x, y - 1));
                    visitedLookup[index] = true;
                }
            }
            else {
                if(!visitedLookup[index]) {
                    possibleNeighbours.push_back(make_tuple(x, y - 1));
                    visitedLookup[index] = true;
                }
            }
        }
    }

    if(minimumDistance == 0) {
        state.hasReachedEnd = true;
    }
    state.distanceFromEnd = minimumDistance;
    getNeighbours(game, state, possibleNeighbours);
}

void fillNeighboursByFilling(GameDisplay game, GameState &state) {
    int lines = game.boardHeight, cols = game.boardWidth;
    int index;

    vector<tuple<int,int>> positions; // Array of coordinates (x,y) on board
    vector<tuple<int,int>> possibleNeighbours;
    vector<bool> visitedLookup(lines * cols);
    positions.push_back(make_tuple(0,0));
    visitedLookup[0] = true;

    for(unsigned int i = 0; i < positions.size(); i++) {
        tuple<int,int> position = positions[i];

        int x = get<0>(position), y = get<1>(position);
    
        if(!state.lookaheadBoard[y*cols + x]) {
            state.lookaheadBoard[y*cols + x] = true;
            state.totalFilled += 1;
        }
    
        // Verifies on x-axis
        if(x == 0) { // Is on left column
            index = y*cols + (x + 1);
            if(game.board[index] == state.selectedColor || state.lookaheadBoard[index]) {
                if(!visitedLookup[index]) {
                    positions.push_back(make_tuple(x + 1, y));
                    visitedLookup[index] = true;
                }
            }
            else {
                if(!visitedLookup[index]) {
                    possibleNeighbours.push_back(make_tuple(x + 1, y));
                    visitedLookup[index] = true;
                }
            }
        }
        else if(x == cols - 1) { // Is on right column
            index = y*cols + (x - 1);
            if(game.board[index] == state.selectedColor || state.lookaheadBoard[index]) {
                if(!visitedLookup[index]) {
                    positions.push_back(make_tuple(x - 1, y));
                    visitedLookup[index] = true;
                }
            }
            else {
                if(!visitedLookup[index]) {
                    possibleNeighbours.push_back(make_tuple(x - 1, y));
                    visitedLookup[index] = true;
                }
            }
        }
        else { // Is on middle of board
            index = y*cols + (x + 1);
            if(game.board[index] == state.selectedColor || state.lookaheadBoard[index]) {
                if(!visitedLookup[index]) {
                    positions.push_back(make_tuple(x + 1, y));
                    visitedLookup[index] = true;
                }
            }
            else {
                if(!visitedLookup[index]) {
                    possibleNeighbours.push_back(make_tuple(x + 1, y));
                    visitedLookup[index] = true;
                }
            }
            
            index = y*cols + (x - 1);
            if(game.board[index] == state.selectedColor || state.lookaheadBoard[index]) {
                if(!visitedLookup[index]) {
                    positions.push_back(make_tuple(x - 1, y));
                    visitedLookup[index] = true;
                }
            }
            else {
                if(!visitedLookup[index]) {
                    possibleNeighbours.push_back(make_tuple(x - 1, y));
                    visitedLookup[index] = true;
                }
            }
        }

        // Verifies on y-axis
        if(y == 0) { // Is on first line
            index = (y + 1)*cols + x;
            if(game.board[index] == state.selectedColor || state.lookaheadBoard[index]) {
                if(!visitedLookup[index]) {
                    positions.push_back(make_tuple(x, y + 1));
                    visitedLookup[index] = true;
                }
            }
            else {
                if(!visitedLookup[index]) {
                    possibleNeighbours.push_back(make_tuple(x, y + 1));
                    visitedLookup[index] = true;
                }
            }
        }
        else if(y == lines - 1) { // Is on last line
            index = (y - 1)*cols + x;
            if(game.board[index] == state.selectedColor || state.lookaheadBoard[index]) {
                if(!visitedLookup[index]) {
                    positions.push_back(make_tuple(x, y - 1));
                    visitedLookup[index] = true;
                }
            }
            else {
                if(!visitedLookup[index]) {
                    possibleNeighbours.push_back(make_tuple(x, y - 1));
                    visitedLookup[index] = true;
                }
            }
        }
        else { // Is on middle of board
            index = (y + 1)*cols + x;
            if(game.board[index] == state.selectedColor || state.lookaheadBoard[index]) {
                if(!visitedLookup[index]) {
                    positions.push_back(make_tuple(x, y + 1));
                    visitedLookup[index] = true;
                }
            }
            else {
                if(!visitedLookup[index]) {
                    possibleNeighbours.push_back(make_tuple(x, y + 1));
                    visitedLookup[index] = true;
                }
            }

            index = (y - 1)*cols + x;
            if(game.board[index] == state.selectedColor || state.lookaheadBoard[index]) {
                if(!visitedLookup[index]) {
                    positions.push_back(make_tuple(x, y - 1));
                    visitedLookup[index] = true;
                }
            }
            else {
                if(!visitedLookup[index]) {
                    possibleNeighbours.push_back(make_tuple(x, y - 1));
                    visitedLookup[index] = true;
                }
            }
        }
    }

    getNeighbours(game, state, possibleNeighbours);
}

void getNeighbours(GameDisplay game, GameState &state, vector<tuple<int,int>> possibleNeighbours) {
    int lines = game.boardHeight, cols = game.boardWidth;
    int index;

    for(auto position: possibleNeighbours) {
        int x = get<0>(position), y = get<1>(position);

        // Verifies on x-axis
        if(x == 0) { // Is on left column
            index = y*cols + (x + 1);
            if(state.lookaheadBoard[index]) {
                state.neighbourColors.insert(game.board[y*cols + x]);
            }
        }
        else if(x == cols - 1) { // Is on right column
            index = y*cols + (x - 1);
            if(state.lookaheadBoard[index]) {
                state.neighbourColors.insert(game.board[y*cols + x]);
            }
        }
        else { // Is on middle of board
            index = y*cols + (x + 1);
            if(state.lookaheadBoard[index]) {
                state.neighbourColors.insert(game.board[y*cols + x]);
            }
            
            index = y*cols + (x - 1);
            if(state.lookaheadBoard[index]) {
                state.neighbourColors.insert(game.board[y*cols + x]);
            }
        }

        // Verifies on y-axis
        if(y == 0) { // Is on first line
            index = (y + 1)*cols + x;
            if(state.lookaheadBoard[index]) {
                state.neighbourColors.insert(game.board[y*cols + x]);
            }
        }
        else if(y == lines - 1) { // Is on last line
            index = (y - 1)*cols + x;
            if(state.lookaheadBoard[index]) {
                state.neighbourColors.insert(game.board[y*cols + x]);
            }
        }
        else { // Is on middle of board
            index = (y + 1)*cols + x;
            if(state.lookaheadBoard[index]) {
                state.neighbourColors.insert(game.board[y*cols + x]);
            }

            index = (y - 1)*cols + x;
            if(state.lookaheadBoard[index]) {
                state.neighbourColors.insert(game.board[y*cols + x]);
            }
        }
    }
}

GameState getInitialState(GameDisplay game) {
    GameState state;

    state.selectedColor = game.board.front();
    state.totalFilled = 0;
    state.hasReachedEnd = false;
    // Initially distance from first cell to last
    state.distanceFromEnd = sqrt((game.boardHeight-1)*(game.boardHeight-1) + (game.boardWidth-1)*(game.boardWidth-1));
    state.lookaheadBoard = vector<bool>(game.boardHeight * game.boardWidth);

    fillNeighboursByDistance(game, state);

    return state;
}

GameState lookaheadNeighboursByDistance(GameDisplay game, GameState state) {
    GameState copyState;
    GameState bestState = state;

    for(auto childColor: state.neighbourColors) {
        copyState = state;
        copyState.selectedColor = childColor;
        copyState.neighbourColors = set<int>();

        fillNeighboursByDistance(game, copyState);
        if(copyState.distanceFromEnd < bestState.distanceFromEnd) {
            copyState.selectedPath.push_back(childColor);
            bestState = copyState;
        }
    }

    return bestState;
}

GameState lookaheadNeighboursByFilling(GameDisplay game, GameState state) {
    GameState copyState;
    GameState bestState = state;

    for(auto childColor: state.neighbourColors) {
        copyState = state;
        copyState.selectedColor = childColor;
        copyState.neighbourColors = set<int>();

        fillNeighboursByFilling(game, copyState);
        if(copyState.totalFilled > bestState.totalFilled) {
            copyState.selectedPath.push_back(childColor);
            bestState = copyState;
        }
    }

    return bestState;
}
