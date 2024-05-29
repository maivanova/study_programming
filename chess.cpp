#include <iostream>
#include <vector>

// Функция для расчёта доступных ходов для фигуры ладьи
void calculaterookmoves(std::vector<std::vector<int>>& moves, int row, int col) {
    // Заполняем доступные ходы для ладьи вверх
    for (int i = row - 1; i >= 0; i--) {
        moves[i][col] = 1;
        if (moves[i][col] != 0) break;
    }
    // Заполняем доступные ходы для ладьи вниз
    for (int i = row + 1; i < 8; i++) {
        moves[i][col] = 1;
        if (moves[i][col] != 0) break;
    }
    // Заполняем доступные ходы для ладьи влево
    for (int j = col - 1; j >= 0; j--) {
        moves[row][j] = 1;
        if (moves[row][j] != 0) break;
    }
    // Заполняем доступные ходы для ладьи вправо
    for (int j = col + 1; j < 8; j++) {
        moves[row][j] = 1;
        if (moves[row][j] != 0) break;
    }
}

void calculatekingmoves(std::vector<std::vector<int>>& moves, int row, int col) {
    int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int i = 0; i < 8; i++) {
        int new_row = row + dr[i];
        int new_col = col + dc[i];
        if (new_row >= 0 && new_row < 8 && new_col >= 0 && new_col < 8) {
            moves[new_row][new_col] = 1;
        }
    }
}

// функция для расчёта доступных ходов для фигуры слона
void calculatebishopmoves(std::vector<std::vector<int>>& moves, int row, int col) {
    for (int i = 1; i < 8; i++) {
        // вправо вверх
        if (row - i >= 0 && col + i < 8) {
            moves[row - i][col + i] = 1;
            if (moves[row - i][col + i] != 0) break;
        }
        // влево вверх
        if (row - i >= 0 && col - i >= 0) {
            moves[row - i][col - i] = 1;
            if (moves[row - i][col - i] != 0) break;
        }
        // вправо вниз
        if (row + i < 8 && col + i < 8) {
            moves[row + i][col + i] = 1;
            if (moves[row + i][col + i] != 0) break;
        }
        // влево вниз
        if (row + i < 8 && col - i >= 0) {
            moves[row + i][col - i] = 1;
            if (moves[row + i][col - i] != 0) break;
        }
    }
}

// функция для расчёта доступных ходов для фигуры коня
void calculateknightmoves(std::vector<std::vector<int>>& moves, int row, int col) {
    int dr[] = {-2, -1, 1, 2, 2, 1, -1, -2};
    int dc[] = {1, 2, 2, 1, -1, -2, -2, -1};

    for (int i = 0; i < 8; i++) {
        int new_row = row + dr[i];
        int new_col = col + dc[i];
        if (new_row >= 0 && new_row < 8 && new_col >= 0 && new_col < 8) {
            moves[new_row][new_col] = 1;
        }
    }
}

// функция для расчёта доступных ходов для фигуры ферзя (комбинация ладьи и слона)
void calculatequeenmoves(std::vector<std::vector<int>>& moves, int row, int col) {
    calculaterookmoves(moves, row, col);
    calculatebishopmoves(moves, row, col);
}

// Функция для вывода доступных ходов
void printavailablemoves(const std::vector<std::vector<int>>& moves, int row, int col, std::string figure) {
    std::cout << "Available moves for " << figure << " from position (" << row << "," << col << "):\n";
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            std::cout << moves[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    std::vector<std::vector<int>> moves(8, std::vector<int>(8, 0));

    // расчёт доступных ходов для ладьи из начальной позиции (1,1)
    calculaterookmoves(moves, 1, 1);
    printavailablemoves(moves, 1, 1, "rook");

    // расчёт доступных ходов для короля из начальной позиции (1,1)
    calculatekingmoves(moves, 1, 1);
    printavailablemoves(moves, 1, 1, "king");

    // расчёт доступных ходов для слона из начальной позиции (1,1)
    calculatebishopmoves(moves, 1, 1);
    printavailablemoves(moves, 1, 1, "bishop");

    // расчёт доступных ходов для коня из начальной позиции (1,1)
    calculateknightmoves(moves, 1, 1);
    printavailablemoves(moves, 1, 1, "knight");

    // расчёт доступных ходов для ферзя из начальной позиции (1,1)
    calculatequeenmoves(moves, 1, 1);
    printavailablemoves(moves, 1, 1, "queen");
    return 0;
}