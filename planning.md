A place to write your findings and plans

## Understanding
1. Line 1-14: We need the #include for butano to work.
2. Line 17: This is the fixed speed of the green square we control.
3. Line 20-21: This is for the size of the green square the player controls and the size of the
   circle that represents the treasure.
4. Line 24-27: Full bounds of the screen, the minimum and maximum for the display.
5. Line 30: The maximum amount of pixels used to display the score as an integer.
6. Line 33-34: Code for the location of the score on the screen. In this case it's at the top right.
7. Line 40: the variable represents a random variable that will be used for the location of the treasure when the user reaches it.
8. Line 43-44: A vector holds the sprites for the score integer values and the sprite text generator displays the score on the
   screen.
9. Line 48-49: It creates the sprites for the green square the player controls and the yellow circle that represents the treasure.
10. Line 53-59: Basically the code for the controls.
11. Line 72-79: We think this code is for everytime the player moves.
12. Line 82-90: This code is for everytime the yellow circle treasure gets reached.
13. Line 93-98: The function code to display the score sprites on the screen.
14. Line 100: A randomizer for the location of the yellow circle after the display updates.

## Planning required changes
1. At Line 17, we can change the fixed speed integer to change the speed of the player.
2. Since there's no code the background color, we'll implement it ourselves in the main file.
3. Make new static constexpr int variables for the x and y coordinates of the player and treasure
   and add them in the parentheses of the bn::sprite_ptr variables.

## Brainstorming game ideas

## Plan for implementing game

