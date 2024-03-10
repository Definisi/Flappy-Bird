
#include <iostream>
#include <windows.h>
#include <ctime>
#include <chrono>
#include <thread>


#include "flappy_bird.hpp"

#include "../utilities/utilities.hpp"

using namespace std;

FlappyBird::FlappyBird() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    screen_width = 79;
    screen_height = 25;
    hurdle_gap = 8;
    between_hurdle_gap = (screen_width / 4) + 10;

    bird_x = 17;
    bird_y = 15;

    jump = 4;
    score = 0;

    for (int i = 0; i < 4; i++) {
        hurdle_pos[i][0] = between_hurdle_gap * (i + 1);
        int break_pos = std::rand() % (screen_height / 3) + hurdle_gap;
        hurdle_pos[i][1] = break_pos;
    }
}

void FlappyBird::play() noexcept {
    print_road();
    int some_delay = 0;
    while (true) {
        if (GetAsyncKeyState(VK_SPACE)) {
            bird_y -= jump;
        }

        print_hurdle();
        print_bird();
        print_score();

        if (collision_check()) {
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        clear_bird();
        bird_y += 1;
    }
    std::thread([] {
        Beep(250, 1000);
    }).detach();
}

void FlappyBird::print_hurdle() const
{
    int count = 0;
    for (int i = 0; i < hurdle_count; i++) {
        for (int j = 0; j < screen_height; j++) {

            if (hurdle_pos[i][1] == j) count = hurdle_gap;

            if (count == 0) {
                if (hurdle_pos[i][0] < screen_width) {
                    go_to_xy(hurdle_pos[i][0] + 1, j);
                    cout << " ";

                    go_to_xy(hurdle_pos[i][0], j);
                    cout << i;
                }
            }
            else {
                if ((count == 1 || count == hurdle_gap) && hurdle_pos[i][0] < screen_width) {
                    if (hurdle_pos[i][0] + 1 > 0) {
                        go_to_xy(hurdle_pos[i][0] + 1, j);
                        cout << "   ";
                    }

                    if (hurdle_pos[i][0] - 1 > 0) {
                        go_to_xy(hurdle_pos[i][0] - 1, j);
                        cout << "===";
                    }
                }

                count--;
            }
        }

        hurdle_pos[i][0]--;

        if (hurdle_pos[i][0] == -1) {
            int prev;
            if (i == 0)
                prev = hurdle_count - 1;
            else
                prev = i - 1;

            hurdle_pos[i][0] = hurdle_pos[prev][0] + between_hurdle_gap;

            int breakPos = rand() % (screen_height / 3) + hurdle_gap;
            hurdle_pos[i][1] = breakPos;

            for (int i = 0; i < screen_height; i++) {
                go_to_xy(0, i);
                cout << " ";
            }
        }
    }
}

bool FlappyBird::collision_check() const noexcept
{
    if (bird_y == 0 || bird_y + 3 == screen_height)
        return true;

    for (int i = 0; i < hurdle_count; i++) {
        int hurdle_x = hurdle_pos[i][0];
        int hurdle_y = hurdle_pos[i][1];

        if (bird_x == hurdle_x && (bird_y >= hurdle_y || bird_y + 3 <= (hurdle_y + hurdle_gap))) {
            score++;
            std::thread([] {
                Beep(500, 250);
            }).detach();
        }

        if (hurdle_x >= bird_x - 5 && hurdle_x <= bird_x &&
            (bird_y <= hurdle_y || bird_y + 3 >= (hurdle_y + hurdle_gap))) {
            return true;
        }
    }

    return false;

}

void FlappyBird::clear_bird() const
{
    go_to_xy(bird_x - 5, bird_y);
    cout << "   ";
    go_to_xy(bird_x - 5, bird_y + 1);
    cout << "      ";
    go_to_xy(bird_x - 5, bird_y + 2);
    cout << "       ";
}

void FlappyBird::print_score() const
{
    go_to_xy(0, screen_height + 4);
    cout << "Score: " << score;
}

void FlappyBird::print_bird() const
{
    go_to_xy(bird_x - 5, bird_y);        cout << " __";
    go_to_xy(bird_x - 5, bird_y + 1);    cout << "/-/o\\";
    go_to_xy(bird_x - 5, bird_y + 2);    cout << "\\_\\-/";
}

void FlappyBird::print_road() const
{
    for (int i = 0; i <= screen_width; i++) {
        go_to_xy(i, screen_height);        cout << "_";
        go_to_xy(i, screen_height + 1);    cout << "/";
        go_to_xy(i, screen_height + 2);    cout << "=";
    }
}
