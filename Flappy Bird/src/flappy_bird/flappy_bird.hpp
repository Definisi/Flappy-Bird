#ifndef FLAPPYBIRD_H
#define FLAPPYBIRD_H

class FlappyBird {
public:
    FlappyBird();
    void play() noexcept;

private:
    mutable int hurdle_count = 4;
    mutable int hurdle_pos[4][2];
    mutable int screen_width = 0;
    mutable int screen_height = 0;
    mutable int hurdle_gap = 0;
    mutable int between_hurdle_gap = 0;

    mutable int bird_x = 0;
    mutable int bird_y = 0;

    mutable int jump = 0;
    mutable int score = 0;

    void print_hurdle() const;
    [[nodiscard]] bool collision_check() const noexcept;
    void clear_bird() const;
    void print_score() const;
    void print_bird() const;
    void print_road() const;
};

#endif // FLAPPYBIRD_H
