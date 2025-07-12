#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <limits>
#include <cmath>
#include <queue>
#include <utility>

enum GameState {
    PLAYING,
    PLAYER_WON,
    BUG_WON
};

// Model 
class BugTrapModel {
public:
    BugTrapModel(int size) : size(size), state(PLAYING), deceptionMode(false) {
        reset();
    }

    void reset() {
        grid.clear();
        grid.resize(size); 
        for (auto& row : grid) {
            row.resize(size, '.'); 
        }
        bugX = size / 2;
        bugY = size / 2;
        grid[bugX][bugY] = 'B';
        state = PLAYING;
        trapsPlaced = 0;
        deceptionMode = false;
        deceptionTarget = std::make_pair(-1, -1);
    }

    bool placeTrap(int x, int y) {
        if (x < 0 || x >= size || y < 0 || y >= size || grid[x][y] != '.') {
            return false;
        }

        grid[x][y] = 'T';
        trapsPlaced++;
        return true;
    }

    void moveBug() {
        if (state != PLAYING) return;

        if (isOnEdge(bugX, bugY)) {
            state = BUG_WON;
            return;
        }

        const int dx[4] = { 0, 0, -1, 1 };
        const int dy[4] = { -1, 1, 0, 0 };
        
        std::vector<std::pair<int, int>> moves;

        for (int i = 0; i < 4; i++) {
            int nx = bugX + dx[i];
            int ny = bugY + dy[i];
            if (nx >= 0 && nx < size && ny >= 0 && ny < size && grid[nx][ny] == '.') {
                moves.push_back(std::make_pair(nx, ny));
            }
        }

        if (moves.empty()) {
            state = PLAYER_WON;
            return;
        }

        
        if (deceptionMode) {
            if ((bugX == deceptionTarget.first && bugY == deceptionTarget.second) ||
                !canReach(deceptionTarget)) {
                deceptionMode = false;
            }
            else {
                std::pair<int, int> bestMove = findMoveTowardsTarget(moves, deceptionTarget);
                moveBugTo(bestMove.first, bestMove.second);
                return;
            }
        }

       
        if (rand() % 100 < 45 && !deceptionMode) {
            activateDeceptionMode();
            if (deceptionMode) { 
                std::pair<int, int> bestMove = findMoveTowardsTarget(moves, deceptionTarget);
                moveBugTo(bestMove.first, bestMove.second);
                return;
            }
        }

        
        std::vector<int> distances;
        for (const auto& move : moves) {
            int dist = std::min({
                move.first,
                size - 1 - move.first,
                move.second,
                size - 1 - move.second
                });
            distances.push_back(dist);
        }

        size_t minIndex = std::min_element(distances.begin(), distances.end()) - distances.begin();
        int minDist = distances[minIndex];
        std::vector<std::pair<int, int>> bestMoves;
        for (size_t i = 0; i < moves.size(); i++) {
            if (distances[i] == minDist) {
                bestMoves.push_back(moves[i]);
            }
        }

       
        if (rand() % 100 < 5 && bestMoves.size() > 1) {
            bestMoves.pop_back(); 
        }

        int idx = rand() % bestMoves.size();
        moveBugTo(bestMoves[idx].first, bestMoves[idx].second);
    }

    void activateDeceptionMode() {
        deceptionMode = true;

       
        int toTop = bugX;
        int toBottom = size - 1 - bugX;
        int toLeft = bugY;
        int toRight = size - 1 - bugY;

        int minDist = std::min({ toTop, toBottom, toLeft, toRight });

       
        if (toTop == minDist) {
            deceptionTarget = std::make_pair(size - 1, bugY); 
        }
        else if (toBottom == minDist) {
            deceptionTarget = std::make_pair(0, bugY); 
        }
        else if (toLeft == minDist) {
            deceptionTarget = std::make_pair(bugX, size - 1); 
        }
        else {
            deceptionTarget = std::make_pair(bugX, 0); 
        }

       
        if (!canReach(deceptionTarget)) {
            deceptionMode = false;
        }
    }

    bool canReach(const std::pair<int, int>& target) {
        std::vector<std::vector<bool>> visited(size, std::vector<bool>(size, false));
        std::queue<std::pair<int, int>> q;
        q.push(std::make_pair(bugX, bugY));
        visited[bugX][bugY] = true;

        while (!q.empty()) {
            auto cell = q.front();
            q.pop();

            if (cell.first == target.first && cell.second == target.second) {
                return true;
            }

            const int dx[4] = { -1, 1, 0, 0 };
            const int dy[4] = { 0, 0, -1, 1 };

            for (int i = 0; i < 4; i++) {
                int nx = cell.first + dx[i];
                int ny = cell.second + dy[i];

                if (nx >= 0 && nx < size && ny >= 0 && ny < size &&
                    !visited[nx][ny] && grid[nx][ny] != 'T') {
                    visited[nx][ny] = true;
                    q.push(std::make_pair(nx, ny));
                }
            }
        }
        return false;
    }

    std::pair<int, int> findMoveTowardsTarget(const std::vector<std::pair<int, int>>& moves,
        const std::pair<int, int>& target) {
        std::pair<int, int> bestMove = moves[0];
        int bestDist = distance(bestMove, target);

        for (const auto& move : moves) {
            int dist = distance(move, target);
            if (dist < bestDist) {
                bestDist = dist;
                bestMove = move;
            }
        }
        return bestMove;
    }

    int distance(const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
        return std::abs(p1.first - p2.first) + std::abs(p1.second - p2.second);
    }

    void moveBugTo(int newX, int newY) {
        grid[bugX][bugY] = '.';
        bugX = newX;
        bugY = newY;
        grid[bugX][bugY] = 'B';

        if (isOnEdge(bugX, bugY)) {
            state = BUG_WON;
        }
    }

    bool isOnEdge(int x, int y) const {
        return (x == 0 || x == size - 1 || y == 0 || y == size - 1);
    }

    int getSize() const { return size; }
    GameState getState() const { return state; }
    char getCell(int x, int y) const { return grid[x][y]; }
    int getTrapsPlaced() const { return trapsPlaced; }

private:
    int size;
    int bugX, bugY;
    GameState state;
    int trapsPlaced;
    std::vector<std::vector<char>> grid;

    bool deceptionMode;
    std::pair<int, int> deceptionTarget;
};

// View
class BugTrapView {
public:
    void display(const BugTrapModel& model) {
        int size = model.getSize();

       
        std::cout << "  ";
        for (int j = 0; j < size; j++) {
            std::cout << j << " ";
        }
        std::cout << "\n";

       
        for (int i = 0; i < size; i++) {
            std::cout << i << " ";
            for (int j = 0; j < size; j++) {
                char c = model.getCell(i, j);
                if (c == 'B') {
                    std::cout << "\033[5;35mB\033[0m";
                }
                else if (c == 'T') {
                    std::cout << "\033[3;33mT\033[0m";
                }
                else {
                    std::cout << c;
                }
                std::cout << " ";
            }
            std::cout << "\n";
        }

        
        std::cout << "Ловушек установлено: " << model.getTrapsPlaced() << "\n";
        
        switch (model.getState()) {
        case PLAYING: std::cout << "Игра продолжается"; break;
        case PLAYER_WON: std::cout << "\033[1;32mЖук пойман,вы победили:)\033[0m"; break;
        case BUG_WON: std::cout << "\033[1;31mЖук сбежал, вы проиграли:(\033[0m"; break;
        }
        std::cout << "\n\n";
    }
};

// Controller
class BugTrapController {
public:
    BugTrapController(int size = 8) : model(size), view() {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
    }

    void run() {
        displayHelp();
        model.reset();

        while (model.getState() == PLAYING) {
            view.display(model);

            int x, y;
            std::cout << "Введите координаты для ловушки : ";
            std::cin >> x >> y;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Ошибка ввода, введите числа\n";
                continue;
            }

            if (!model.placeTrap(x, y)) {
                std::cout << "Недопустимый ход\n";
                continue;
            }

            model.moveBug();
        }

        view.display(model);
        std::cout << "Игра окончена!\n";
    }

private:
    BugTrapModel model;
    BugTrapView view;

    void displayHelp() {
        std::cout << "=== ИГРА 'Поймай жука' ===\n";
        std::cout << "Правила:\n";
        std::cout << "1. Ваша цель - окружить жука (B) ловушками (T)\n";
        std::cout << "2. Устанавливайте ловушки в пустые клетки\n";
        std::cout << "3. Если жук достигнет края - вы проиграли\n";
        std::cout << "4. Если жук не может двигаться - вы победили\n\n";
        std::cout << "   Жук двигается только вверх и вниз, по диагонали он двигаться не может\n\n";
        std::cout << "   Координаты ловушки воодятся в формате 'строка столбец'\n\n";
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    BugTrapController game(9);
    game.run();
    return 0;
}