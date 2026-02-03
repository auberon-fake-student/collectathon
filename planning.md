A place to write your findings and plans

## Understanding
1. Lines 1-16: We need the #include for butano to work.
2. Line 21: This is the fixed speed of the green square we control.
3. Lines 27-28: This is for the size of the green square the player controls and the size of the
   circle that represents the treasure.
4. Line 31-34: Full bounds of the screen, the minimum and maximum for the display.
5. Line 37: The maximum amount of pixels used to display the score as an integer.
6. Line 40-41: Code for the location of the score on the screen. In this case it's at the top right.
7. Line 55: the variable represents a random variable that will be used for the location of the
   treasure when the user reaches it.
8. Line 61-62: A vector holds the sprites for the score integer values and the sprite text
   generator displays the score on the screen.
9. Line 66-67: It creates the sprites for the green square the player controls and the yellow
   circle that represents the treasure.
10. Line 97-108: We think this code is for everytime the player moves.
11. Line 132-140: This code is for everytime the yellow circle treasure gets reached.
12. Line 159-164: The function code to display the score sprites on the screen.
13. Line 166: A randomizer for the location of the yellow circle after the display updates.

## Planning required changes
1. We can change the fixed speed variable to a different integer.
2. Since there's no code for the background color, we'll implement it ourselves in the main file.
3. Make new static constexpr int variables for the x and y coordinates of the player and treasure
   and add them in the parentheses of the bn::sprite_ptr variables.
4. Add an if statement for when the start button is pressed. Set the x and y coordinates to the
   previously added x and y integer variables we added in #3.
5. Add if statements for when the player intersects a full bound of a side of the screen, they'll
   appear on the opposite side of the screen (For example, if the player reaches the top of the screen, they'll appear at the bottom of the screen).
6. Create a variable that counts the amount of times the a button is pressed and a timer variable.
   Add an if statement for when the a button is pressed and the aPressed variable does not equal 3.
   In the if statement, increment the aPressed variable by 1. Then add a while loop in the if statement that'll keep going until the timer variable equals 5. In the while loop, increment the timer variable and create another d-pad code that replaces the SPEED variable with a newly created BOOST variable to change the speed of the player, aka the speed boost. Once the timer reaches 5, revert the timer back to 0. Finally, put the d-pad for the original speed in a if statement for when the timer equals 0 so that the boosted speed and original speed overlap each other.

## Brainstorming game ideas
1. Press L or R buttons to change the background color. L for red and R for blue.
2. Press B to randomize the location of the treasure again.
3. Add new sprites that'll represent the obstacle.

## Plan for implementing game
1. if statements when l and r buttons pressed for the background color.
2. if statement when b button pressed for randomizing the treasure location again.
3. Create the obstacle sprites, give it default locations, and make their location randomized for
   every score update.

