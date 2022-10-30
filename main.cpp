#include <iostream>
//#include <windows.h>
//#include <chrono>

#define SIDE 3

#define COMPUTER 1
#define HUMAN 2

#define COMPUTERMOVE '0'
#define HUMANMOVE 'X'

using namespace std;

char game_board[][SIDE] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
};

//void set_cursor(short x, short y) {
//
//    COORD coordinates;
//    coordinates.X = x;
//    coordinates.Y = y;
//    SetConsoleCursorPosition(GetStdHandle
//                                     (STD_OUTPUT_HANDLE), coordinates);
//
//}

int format_from_xy(int x, int y) {
    return x * 3 + y;
}

bool row_crossed(char board[][SIDE]) {
    for (int i = 0; i < SIDE; i++) {
        if (board[i][0] == board[i][1] &&
            board[i][1] == board[i][2] &&
            board[i][0] != ' ')
            return true;
    }
    return false;
}

bool column_crossed(char board[][SIDE]) {
    for (int i = 0; i < SIDE; i++) {
        if (board[0][i] == board[1][i] &&
            board[1][i] == board[2][i] &&
            board[0][i] != ' ')
            return true;
    }
    return false;
}

bool diagonal_crossed(char board[][SIDE]) {
    if (board[0][0] == board[1][1] &&
        board[1][1] == board[2][2] &&
        board[0][0] != ' ')
        return true;

    if (board[0][2] == board[1][1] &&
        board[1][1] == board[2][0] &&
        board[0][2] != ' ')
        return true;

    return false;
}

bool game_over(char board[][SIDE]) {
    return row_crossed(board) || column_crossed(board) || diagonal_crossed(board);
}

int minimax(char board[SIDE][SIDE], int depth, bool isAI) {
    int score, bestScore;
    if (game_over(board)) {
        if (isAI)
            return -1;
        return +1;
    } else {
        if (depth < 9) {
            if (isAI) {
                bestScore = -999;
                for (int x = 0; x < SIDE; x++) {
                    for (int y = 0; y < SIDE; y++) {
                        if (board[x][y] == ' ') {
                            board[x][y] = COMPUTERMOVE;
                            score = minimax(board, depth + 1, false);
                            board[x][y] = ' ';
                            if (score > bestScore) {
                                bestScore = score;
                            }
                        }
                    }
                }
                return bestScore;
            } else {
                bestScore = 999;
                for (int x = 0; x < SIDE; x++) {
                    for (int y = 0; y < SIDE; y++) {
                        if (board[x][y] == ' ') {
                            board[x][y] = HUMANMOVE;
                            score = minimax(board, depth + 1, true);
                            board[x][y] = ' ';
                            if (score < bestScore) {
                                bestScore = score;
                            }
                        }
                    }
                }
                return bestScore;
            }
        } else {
            return 0;
        }
    }
}

int best_move(char board[][SIDE], int moveIndex) {
    int x = -1, y = -1;
    int score, bestScore = -999;
    for (int i = 0; i < SIDE; i++) {
        for (int j = 0; j < SIDE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = COMPUTERMOVE;
                score = minimax(board, moveIndex + 1, false); // Анализ хода минимаксом
                board[i][j] = ' ';
                if (score > bestScore) {
                    bestScore = score;
                    x = i;
                    y = j;
                }
            }
        }
    }
    return format_from_xy(x, y);
}

//void set_up_move(int x, int y, char c) {
//    game_board[x][y] = c;
//}
//
//void set_up_move(int index, char c) {
//    if (index == 1) {
//        set_up_move(0, 0, c);
//    } else if (index == 2) {
//        set_up_move(1, 0, c);
//    } else if (index == 3) {
//        set_up_move(2, 0, c);
//    } else if (index == 4) {
//        set_up_move(0, 1, c);
//    } else if (index == 5) {
//        set_up_move(1, 1, c);
//    } else if (index == 6) {
//        set_up_move(2, 1, c);
//    } else if (index == 7) {
//        set_up_move(0, 2, c);
//    } else if (index == 8) {
//        set_up_move(1, 2, c);
//    } else if (index == 9) {
//        set_up_move(2, 2, c);
//    }
//}

void draw_board(char board[][SIDE]) {
    cout << "\t\t\t " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
    cout << "\t\t\t-----------\n";
    cout << "\t\t\t " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
    cout << "\t\t\t-----------\n";
    cout << "\t\t\t " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl << endl;
}

int show_instructions() {
    cout << "\nВыберите клетку от 1 до 9 и игра начнётся\n\n";

    cout << ("\t\t\t 1 | 2 | 3 \n");
    cout << ("\t\t\t-----------\n");
    cout << ("\t\t\t 4 | 5 | 6 \n");
    cout << ("\t\t\t-----------\n");
    cout << ("\t\t\t 7 | 8 | 9 \n\n");

    cout << "Введите начальную точку: ";
    int pos;
    cin >> pos;
    return pos;
}

void start_game() {

    int startPos = show_instructions();

    int moveIndex = 0, whoseMove = HUMAN, x, y;

    while (!game_over(game_board) && moveIndex != SIDE * SIDE) {
        int n = -1;
        if (moveIndex == 0) {
            n = startPos;
        }
        if (whoseMove == COMPUTER) {
            n = best_move(game_board, moveIndex);
            x = n / SIDE;
            y = n % SIDE;
            game_board[x][y] = COMPUTERMOVE;
            cout << "Компьютер установил " << COMPUTERMOVE << " в клетку " << (n + 1) << endl << endl;
            draw_board(game_board);
            moveIndex++;
            whoseMove = HUMAN;
        } else if (whoseMove == HUMAN) {
            if (n == -1) {
                cout << "Доступные клетки: ";
                for (int i = 0; i < SIDE; i++)
                    for (int j = 0; j < SIDE; j++)
                        if (game_board[i][j] == ' ')
                            cout << ((i * 3 + j) + 1) << " ";
                cout << endl << "Введите клетку: ";
                cin >> n;
            }
            n--;
            x = n / SIDE;
            y = n % SIDE;
            if (game_board[x][y] == ' ' && n < 9 && n >= 0) {
                game_board[x][y] = HUMANMOVE;
                cout << endl << "Вы установили " << HUMANMOVE << " в клетку " << (n + 1) << endl << endl;
//                draw_board(game_board);
                moveIndex++;
                whoseMove = COMPUTER;
            } else if (game_board[x][y] != ' ' && n < 9 && n >= 0) {
                cout << endl << "Клетка занята, выберите другую " << endl << endl;
            } else if (n < 0 || n > 8) {
                cout << "Неккоректный номер" << endl;
            }
        }
    }

    if(game_over(game_board)){
        cout << "Победил компьютер";
    } else {
        cout << "Ничья!";
    }
}


int main() {
    setlocale(LC_ALL, "UTF-8");
    start_game();
    return 0;
}
