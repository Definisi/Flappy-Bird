#include "flappy_bird/flappy_bird.hpp"
#include "utilities/utilities.hpp"
#include <iostream>

int main() {
    while (true) {
        FlappyBird m_fb;
        m_fb.play();
        go_to_xy(30, 30);
        std::cout << "Do you want to play again? (Y/N)";

        char ch;
        std::cin >> ch;
        if (ch == 'N' || ch == 'n') {
            break;
        }
        system("cls");
    }

    return 0;
}
