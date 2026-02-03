#include <bn_core.h>
#include <bn_display.h>
#include <bn_log.h>
#include <bn_keypad.h>
#include <bn_random.h>
#include <bn_rect.h>
#include <bn_sprite_ptr.h>
#include <bn_sprite_text_generator.h>
#include <bn_size.h>
#include <bn_string.h>

#include "bn_sprite_items_dot.h"
#include "bn_sprite_items_square.h"
#include "common_fixed_8x16_font.h"
#include "bn_sprite_items_obstacle.h"
#include <bn_backdrop.h>
#include <bn_color.h>

#include "bn_music_items.h"
// #include "bn_sound_item._ file-name.h"



// Pixels / Frame player moves at
static constexpr bn::fixed SPEED = 2;

// Pixels / Frame player moves at with speed boost
static constexpr bn::fixed BOOST = 4;

// Width and height of the the player and treasure bounding boxes
static constexpr bn::size PLAYER_SIZE = {8, 8};
static constexpr bn::size TREASURE_SIZE = {8, 8};
static constexpr bn::size OBSTACLE_SIZE = {8, 8};

// Full bounds of the screen
static constexpr int MIN_Y = -bn::display::height() / 2;
static constexpr int MAX_Y = bn::display::height() / 2;
static constexpr int MIN_X = -bn::display::width() / 2;
static constexpr int MAX_X = bn::display::width() / 2;

// Number of characters required to show the longest numer possible in an int (-2147483647)
static constexpr int MAX_SCORE_CHARS = 11;

// Score location
static constexpr int SCORE_X = 70;
static constexpr int SCORE_Y = -70;

// Player location
static constexpr int PLAYER_X = -50;
static constexpr int PLAYER_Y = 0;

// Treasure location
static constexpr int TREASURE_X = 50;
static constexpr int TREASURE_Y = 0;

// Obstacles location
static constexpr int OBSTACLE1_X = 0;
static constexpr int OBSTACLE1_Y = -20;

static constexpr int OBSTACLE2_X = 0;
static constexpr int OBSTACLE2_Y = 20;

int main()
{
    bn::core::init();

    // Plays music 
    bn::music_items::afternoon_break_1.play();

    bn::random rng = bn::random();
    bn::random obstacle_rng = bn::random();

    // Background Color
    bn::backdrop::set_color(bn::color(10, 10, 22));

    // Will hold the sprites for the score
    bn::vector<bn::sprite_ptr, MAX_SCORE_CHARS> score_sprites = {};
    bn::sprite_text_generator text_generator(common::fixed_8x16_sprite_font);

    int score = 0;

    bn::sprite_ptr player = bn::sprite_items::square.create_sprite(PLAYER_X, PLAYER_Y);
    bn::sprite_ptr treasure = bn::sprite_items::dot.create_sprite(TREASURE_X, TREASURE_Y);
    bn::sprite_ptr obstacle1 = bn::sprite_items::obstacle.create_sprite(OBSTACLE1_X, OBSTACLE1_Y);
    bn::sprite_ptr obstacle2 = bn::sprite_items::obstacle.create_sprite(OBSTACLE2_X, OBSTACLE2_Y);

    // For the speed boost
    int timer = 0;
    int aPressed = 0;

    while (true)
    {

        // Change background color to red
        if (bn::keypad::l_pressed()) {
            bn::backdrop::set_color(bn::color(31, 0, 0));
        }

        // Change background color to blue
        if (bn::keypad::r_pressed()) {
            bn::backdrop::set_color(bn::color(0, 0, 31));
        }

        if (bn::keypad::l_pressed() && bn::keypad::r_pressed()) {
            bn::backdrop::set_color(bn::color(10, 10, 22));
        }

        if (bn::keypad::a_pressed() && aPressed != 3) {
            aPressed++;
            while (timer != 5) {
                timer++;
                if (bn::keypad::left_held()) {
                    player.set_x(player.x() - BOOST);
                }
                if (bn::keypad::right_held()) {
                    player.set_x(player.x() + BOOST);
                }
                if (bn::keypad::up_held()) {
                    player.set_y(player.y() - BOOST);
                }
                if (bn::keypad::down_held()) {
                    player.set_y(player.y() + BOOST);
                }
            }
            timer = 0;
        }

        if (timer == 0) {
            // Move with the d-pad
            if (bn::keypad::left_held()) {
                player.set_x(player.x() - SPEED);
            }
            if (bn::keypad::right_held()) {
                player.set_x(player.x() + SPEED);
            }
            if (bn::keypad::up_held()) {
                player.set_y(player.y() - SPEED);
            }
            if (bn::keypad::down_held()) {
                player.set_y(player.y() + SPEED);
            }
        }
        
        // Resets the game
        if (bn::keypad::start_pressed()) {
            player.set_x(PLAYER_X);
            player.set_y(PLAYER_Y);
            treasure.set_x(TREASURE_X);
            treasure.set_y(TREASURE_Y);
            obstacle1.set_x(OBSTACLE1_X);
            obstacle1.set_y(OBSTACLE1_Y);
            obstacle2.set_x(OBSTACLE2_X);
            obstacle2.set_y(OBSTACLE2_Y);

            score = 0;
            aPressed = 0;
        }
            
        // The bounding boxes of the player and treasure, snapped to integer pixels
        bn::rect player_rect = bn::rect(player.x().round_integer(),
                                        player.y().round_integer(),
                                        PLAYER_SIZE.width(),
                                        PLAYER_SIZE.height());
        bn::rect treasure_rect = bn::rect(treasure.x().round_integer(),
                                          treasure.y().round_integer(),
                                          TREASURE_SIZE.width(),
                                          TREASURE_SIZE.height());
        bn::rect obstacle1_rect = bn::rect(obstacle1.x().round_integer(),
                                          obstacle1.y().round_integer(),
                                          OBSTACLE_SIZE.width(),
                                          OBSTACLE_SIZE.height());
        bn::rect obstacle2_rect = bn::rect(obstacle2.x().round_integer(),
                                          obstacle2.y().round_integer(),
                                          OBSTACLE_SIZE.width(),
                                          OBSTACLE_SIZE.height());

        // If the bounding boxes overlap, set the treasure to a new location an increase score
        if (player_rect.intersects(treasure_rect))
        {
            // Jump to any random point in the screen
            int new_x = rng.get_int(MIN_X, MAX_X);
            int new_y = rng.get_int(MIN_Y, MAX_Y);
            treasure.set_position(new_x, new_y);

            int new_x_2 = obstacle_rng.get_int(MIN_X, MAX_X);
            int new_y_2 = obstacle_rng.get_int(MIN_Y, MAX_Y);
            obstacle1.set_position(new_x_2, new_y_2);

            int new_x_3 = obstacle_rng.get_int(MIN_X, MAX_X);
            int new_y_3 = obstacle_rng.get_int(MIN_Y, MAX_Y);
            obstacle2.set_position(new_x_3, new_y_3);

            score++;
        }

        if (player_rect.intersects(obstacle1_rect) || player_rect.intersects(obstacle2_rect)) {

            int new_x = rng.get_int(MIN_X, MAX_X);
            int new_y = rng.get_int(MIN_Y, MAX_Y);
            treasure.set_position(new_x, new_y);

            int new_x_2 = obstacle_rng.get_int(MIN_X, MAX_X);
            int new_y_2 = obstacle_rng.get_int(MIN_Y, MAX_Y);
            obstacle1.set_position(new_x_2, new_y_2);

            int new_x_3 = obstacle_rng.get_int(MIN_X, MAX_X);
            int new_y_3 = obstacle_rng.get_int(MIN_Y, MAX_Y);
            obstacle2.set_position(new_x_3, new_y_3);

            score--;
        }

        // When user wants to reset level
        if (bn::keypad::b_pressed())
        {
            // Jump to any random point in the screen
            int new_x = rng.get_int(MIN_X, MAX_X);
            int new_y = rng.get_int(MIN_Y, MAX_Y);
            treasure.set_position(new_x, new_y);
        }

        if (player_rect.x() == MIN_X) {
            player.set_x(MAX_X);
        }

        if (player_rect.x() == MAX_X) {
            player.set_x(MIN_X);
        }

        if (player_rect.y() == MIN_Y) {
            player.set_y(MAX_Y);
        }

        if (player_rect.y() == MAX_Y) {
            player.set_y(MIN_Y);
        }

        // Update score display
        bn::string<MAX_SCORE_CHARS> score_string = bn::to_string<MAX_SCORE_CHARS>(score);
        score_sprites.clear();
        text_generator.generate(SCORE_X, SCORE_Y,
                                score_string,
                                score_sprites);

        // Update RNG seed every frame so we don't get the same sequence of positions every time
        rng.update();
        obstacle_rng.update();

        bn::core::update();
    }
}