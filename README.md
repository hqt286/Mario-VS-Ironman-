Game Overview
A Ironman is shown on the lower side of the display on a road. The player can use the joystick to direct the Ironman to the right or left to avoid obstacles on the screen. The player scores one point for passing each obstacle. Hitting any obstacle ends the game. The remainder of this document describes the game operation in detail.
Screens:
The game uses seven different screens.
1 Introduction Screen
* The Instroduction screen will show up for 3 seconds then move on the meny screen.
2 Menu Screen
* The menu will have three different options, ”Play game,” ”How to play,” and ”Score History.” 
* The arrow is a visual clue on the menu that marks the currently selected option. It will start at the op row of the three options
* The player can move the arrow one position at a time using the jostick. The player has to bend the joystick upward or downward and release it for every single arrow movement.
* If the arrow points to the top-most option and the player tries to move the arrow further up or down, the arrow disappears and appeaers on the opposite side. In other words, the arrow waprs aroud when joystick moves it continuously up or continuously down.
* Once the arrow is on the desired menu item, the user selects the menu by pushing down the joystickinto the Z-axis. This closes the joystick button. If ```Play Game``` is selected, then the actual game is started. If ```Score History``` is selected, score screen is brought up. If ```How tTo Play``` is selected, then the instrucion screen is showed up.
3. Instructions screen.
* This screen lists the instructions for how to play the game. 
* Pushing button-1 on this screen will cause the game to return to the menu Screen. Button 1 refers to the top button of the Booster board. 
4. Score Screen
* On this screen, the three top scores will be listed. Top to botton, from the highest score to the lowest.
*Pushing button 1 on will cause the game to retrn to the menu screen.
5. Game Screen
* When the screen loads, the left half will contain the road with the Ironman and the obstacles, while the
right half will show the current score as well as the highest score from previous rounds.
* The stationary parts of this screen are as follows:
* Road: The road where the Ironman and obstacles move is 48 pixels wide. The road has an edge that you
can customize with your color and design.
* Score: The score shows the number of obstacles dodged so far. After the Ironman successfully dodges
an obstacle, i.e. the obstacle disappears at the bottom of the display, the score is updated on
display.
* High Score: This displays the current highest score listed in the score history.
* The moving parts of this screen are as follows:
* Ironman: A 16 x 16-bit image that will be controlled by the joystick. The Ironman will only move from left to right and vice versa. It will not move forward or backward. When the player is bending the joystick to the left, the Ironman moves one pixel every 50ms to the left until it reaches the left boundary of the road and it stays there regardless of the joystick position. Likewise, if the player bends the joystick toward the right, the Ironman moves one pixel every 50 ms to the right until it reaches the right boundary of the
road.
* Obstacles: Obstacles are 16 x 16-bit images that will cause the Ironman to crash if they come in contact
with one another. The obstacles are generated on a regular basis. The starting vertical position of all obstacles is at the top edge of the road. However, each obstacle is given a random horizontal position on the road. The obstacles move 1 pixel toward the bottom of the screen every 50ms. Obstacles should be 50 pixels apart in the vertical direction.
* Anytime while on this screen, pushing button-1 causes the game to pause. Once the game is
paused, the ​ game screen ​ is wiped off, and the ​ ```pause screen``` ​ is displayed in its place.
* When the Ironman hits an obstacle, the ​ game screen ​ is wiped and the​ ```game-over screen``` ​ is displayed.
6. Pause Screen 
* While paused, a menu will appear with the options ”Continue” and ”Menu.” The instructions for moving the cursor are the same as those listed in the ```menu screen``` section.
* Clicking the continue option will cause the game to go to the ​ game screen ​ and resume from where it left off. On the other hand, the menu option will cause the game to go back to the main menu by displaying the ​ menu screen ​ . If the menu option is selected, the score will not be updated.
7. Game Over Screen
* Once the car has crashed into an obstacle, this screen will appear and display the final score from
the game. An optional message can be shown here as long as it is not offensive.
* This screen will only stay up for 3 seconds before the game returns to the main ​ menu screen ​.