#include <iostream>
#include <string>
#include <vector>

std::vector <int> player1;
std::vector <int> player2;
char gameStart;
bool gameWon = false;
int active_player;

bool checkPlayerAnswerIsValid(int answer) {
    for (int i : player1)
        if (i == answer)
            return false;

    for (int i : player2)
        if (i == answer)
            return false;

    return true;
}

void drawBoard() {
    std::cout << std::endl;
    for (int i = 1; i <= 9; i++) {
        if (!checkPlayerAnswerIsValid(i)) {
            for (int answer : player1)
                if (i == answer)
                    std::cout << "| X ";

            for (int answer : player2)
                if (i == answer)
                    std::cout << "| O ";
        }
        else
            std::cout << "| " << i << " ";
        if (i % 3 == 0)
            std::cout << "|" << std::endl;
    }
    std::cout << std::endl;
}

bool checkSequence(std::vector<int> sequence, std::vector<int> answers) {
    bool matches = true;
    for (int i : sequence) {
        bool i_in_store = false;

        for (int j : answers)
            if (i == j) {
                i_in_store = true;
            }

        if (!i_in_store) {
            matches = false;
            break;
        }
    }
    return matches;
}

bool checkVertical(std::vector<int> answers) {
    return checkSequence({ 1, 4, 7 }, answers) || checkSequence({ 2, 5, 8 }, answers) || checkSequence({ 3, 6, 9 }, answers);
}

bool checkHorizontal(std::vector<int> answers) {
    return checkSequence({ 1, 2, 3 }, answers) || checkSequence({ 4, 5, 6 }, answers) || checkSequence({ 7, 8, 9 }, answers);
}

bool checkDiagonal(std::vector<int> answers) {
    return checkSequence({ 1, 5, 9 }, answers) || checkSequence({ 7, 5, 3 }, answers);
}

bool checkPlayerAnswers(std::vector<int> answers) {
    return checkHorizontal(answers) || checkVertical(answers) || checkDiagonal(answers);
}

int main() {

    std::cout << "Welcome to tic tac toe" << std::endl;
    std::cout << "Will you play a game? y/n : ";
    std::cin >> gameStart;

    while (gameStart == 'y') {
        active_player = 0;
        gameWon = false;
        player1 = {};
        player2 = {};
        std::cout << "  " << std::endl;
        std::cout << "Get 3 in a line to win" << std::endl;

        while (!gameWon) {
            bool answerValid = false;

            drawBoard();

            int answer = 0;

            while (!answerValid) {
                std::cout << "Player " << active_player + 1 << " its your turn : ";
                std::cin >> answer;

                if (answer > 9 || answer < 1) {
                    std::cout << "That is not a valid answer! Only values between 1 and 9 can be chosen!" << std::endl;
                    continue;
                }

                answerValid = checkPlayerAnswerIsValid(answer);
            }

            if (active_player == 0) {
                player1.push_back(answer);
                gameWon = checkPlayerAnswers(player1);
            }
            else {
                player2.push_back(answer);
                gameWon = checkPlayerAnswers(player2);
            }

            if (gameWon || (!gameWon && (player1.size() + player2.size()) >= 9)) {
                break;
            }

            active_player = 1 - active_player;
        }

        drawBoard();

        if ((player1.size() + player2.size()) >= 9)
            std::cout << "There is a stalemate" << std::endl;
        else
            std::cout << "Congratulations player " << active_player + 1 << "! you have won!" << std::endl;


        std::cout << "Would you like to play again? y/n: ";
        std::cin >> gameStart;

    }
}
