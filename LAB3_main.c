/*
 * You can add more of your own developed *.h files here.
 * However, you are not allowed to include driverlib, grlib, stdio or any other library in this file.
 */

/// reset once timer go to pause
#include <LED_HAL.h>
#include <Buttons_HAL.h>
#include <Timer_HAL.h>
#include <Display_HAL.h>
#include <ADC_HAL.h>
#include <Screen_HAL.h>
typedef enum {up, down, right, left,mid} J_Direction;
typedef enum {INCEPTION, OPENING,IDLE, MENU,INSTRUCTION, SCORE, PLAY, PAUSE, GAMEOVER} Screen;
typedef enum {InitialMid, Rightward, Leftward, UpWard, DownWard} S_state;
#define OPENING_WAIT 3000 // 3 seconds or 3000 ms
#define OSTIME50IRONMAN 50
#define OSTIMEENEMY 20
#define MinUp 15507
#define MinDown 2000
#define MinLeft 785
#define MinRight 15814
#define InitialPosition -1000
Graphics_Context g_sContext;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                              DRAW AND MOVE OPJECT FUNTION


void DrawObjects(int RandomDec, OneShotEnemyTimer *OST30, int *Score, int Enemy[3][2], int *newPic, J_Direction IronmanDirection)
{
        int position;
        static int i = 0;
           // random number will be from 0-3. Depends on which number, it will put opject into the right location
        if (RandomDec == 0)
            position = 5;
        else if (RandomDec == 1)
            position = 21;
        else if (RandomDec == 2)
            position = 37;
        else
            position = 53;

        if (*newPic == 50)  //Every 50 pixels, a new object appear
        {
            if (i == 3)
                i = 0;
            Enemy[i][0] = position;
            Enemy[i][1] = 0;
            i++;
            *newPic = 0;
        }
        LCDSetFgColor(black);
        // if the joystick is up, make the car move up faster or make the obstacle moving down faster
        if (IronmanDirection == up)
        {
            DrawALineH (Enemy [0][0], Enemy [0][0]+15, Enemy [0][1]-1);
            DrawALineH (Enemy [1][0], Enemy [1][0]+15, Enemy [1][1]-1);
            DrawALineH (Enemy [2][0], Enemy [2][0]+15, Enemy [2][1]-1);
            DrawALineH (Enemy [0][0], Enemy [0][0]+15, Enemy [0][1]);
            DrawALineH (Enemy [1][0], Enemy [1][0]+15, Enemy [1][1]);
            DrawALineH (Enemy [2][0], Enemy [2][0]+15, Enemy [2][1]);
            DrawALineH (Enemy [0][0], Enemy [0][0]+15, Enemy [0][1]+1);
            DrawALineH (Enemy [1][0], Enemy [1][0]+15, Enemy [1][1]+1);
            DrawALineH (Enemy [2][0], Enemy [2][0]+15, Enemy [2][1]+1);
        }
        else
        {
        DrawALineH (Enemy [0][0], Enemy [0][0]+15, Enemy [0][1]);
        DrawALineH (Enemy [1][0], Enemy [1][0]+15, Enemy [1][1]);
        DrawALineH (Enemy [2][0], Enemy [2][0]+15, Enemy [2][1]);
        }
        if (IronmanDirection == up)
        {
            Enemy[0][1]+= 2;
            Enemy[1][1]+= 2;
            Enemy[2][1]+= 2;
        }
        else
        {
            Enemy[0][1]++;
            Enemy[1][1]++;
            Enemy[2][1]++;
        }
        // without pulling up the joystick the obtacles will move down 1 pixel per 50 ns
        DrawEnemy(Enemy [0][0] , Enemy[0][1]);
        DrawEnemy(Enemy [1][0] , Enemy[1][1]);
        DrawEnemy(Enemy [2][0] , Enemy[2][1]);
        LCDSetFgColor(black);
        // everything enemy pass through y = 120, increase the score
        if (Enemy[0][1] == 120 ||  Enemy[1][1] == 120 || Enemy[2][1] == 120)
            *Score = *Score + 1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                          RESET THE ENMENY ONE GAME OVER
// Whenever the game over, reset all the position of obstacles to original point
void ResetEnemy (int Enemy[3][2])
{
    int i;
    int z;
    for (i = 0; i <= 3; i++)
    {
        for (z = 0; z <= 2; z++)
        {
            Enemy[i][z] = InitialPosition;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                          FINITE STATE MACHINE FOR MENU SCREEN
// Each screen of the game will be one different state. The function will return to the main function which screen its at
Screen MenuOption(bool pressed, int *ArrowPositionForMenu, Screen ReturnValue, bool TopPress, int * IronManPosition, int *Score, int Enemy[3][2], int *HighestScore, int *MidScore, int *LowestScore)
{
    static Screen CurrentState = INCEPTION; // initial state is inception
    static OneShotSWTimer_t OST; // timer for opening screen.
    InitOneShotSWTimer(&OST, TIMER32_1_BASE, OPENING_WAIT);
    switch(CurrentState)
    {
    case INCEPTION:
            StartOneShotSWTimer(&OST);
            DrawOpeningScreen(); // draw open screen then switch case to the next state
            CurrentState = OPENING;
            ReturnValue = OPENING;
            break;
    case OPENING:
            if (OneShotSWTimerExpired(&OST)) // go to menu after 3 seconds.
            {
                CurrentState = MENU;
                ReturnValue = MENU;
                DrawMenuScreen();
            }
            break;
    case IDLE: // this is the option state for screen menu
        if (pressed && *ArrowPositionForMenu == 3) // if press the button on instruction line, go to instruction screen
        {
            DrawInstructionScreen();
            CurrentState = INSTRUCTION;
            ReturnValue = INSTRUCTION;
        }
        else if (pressed && *ArrowPositionForMenu == 4) // if JTick press at score screen, show up score
        {
            DrawScoreScreen(*HighestScore, * MidScore, * LowestScore);
            CurrentState = SCORE;
            ReturnValue = SCORE;
        }
        else if  (pressed && *ArrowPositionForMenu == 2) // if JTick pressed at play screen, start to play the game
        {
            DrawPlayScreen(IronManPosition, *HighestScore );
            CurrentState = PLAY;
            ReturnValue = PLAY;
        }
        break;
    case INSTRUCTION: // show the instruction in this case and if the top button pressed, go back to menu
        if (TopPress)
        {
            ReturnValue = MENU; // return the screen that you can move the cursor
            CurrentState = MENU;
            DrawMenuScreen();
        }
        break;
    case SCORE: // show 3 last higest score
        if (TopPress)
        {
            ReturnValue = MENU;
            CurrentState = MENU;
            DrawMenuScreen();
        }
        break;
    case PLAY: // in play case, as long as the top button is pressed, it will pause every then go to menu screen
        if (TopPress)
        {
            *ArrowPositionForMenu = 2; // on menu screen the arrow all ways start at second position
            ReturnValue = PAUSE;
            CurrentState = PAUSE;
            DrawPauseScreen();
        }
        // if the total displacement of the car and the object in x and y direction less then 14, 2 things hit each other
        if (( abs(111 - Enemy[0][1]) < 14 && abs(*IronManPosition - Enemy[0][0]) < 14) ||
            ( abs(111 - Enemy[1][1]) < 14 && abs(*IronManPosition - Enemy[1][0]) < 14) ||
            ( abs(111 - Enemy[2][1]) < 14 && abs(*IronManPosition - Enemy[2][0]) < 14))
        {
            DrawGameOverScreen(*Score); // if 2 things hit other, go to game over screen.
            ScoreSet(HighestScore, MidScore, LowestScore, *Score);
            ReturnValue = GAMEOVER;
            CurrentState = GAMEOVER;
            StartOneShotSWTimer(&OST); // game over screen will appear for 3 seconds
        }
        break;
    case PAUSE: // once in pause screen, press menu go back to menu screen then update the score
            if (pressed && *ArrowPositionForMenu == 2)
            {
                DrawPlayScreen(IronManPosition, *HighestScore);
                CurrentState = PLAY;
                ReturnValue = PLAY;
            }
            else if (pressed && *ArrowPositionForMenu == 3)
            {
                ScoreSet(HighestScore, MidScore, LowestScore, *Score);
                *IronManPosition = 5;
                *Score = 0;
                ReturnValue = MENU;
                CurrentState = MENU;
                DrawMenuScreen();
            }
        break;
    case GAMEOVER: // show up game over screen for 3 second then go back to menu screen
        if (OneShotSWTimerExpired(&OST))
        {
            *IronManPosition = 5;
            *Score = 0;
            ReturnValue = MENU;
            CurrentState = MENU;
            DrawMenuScreen();
        }
        break;
    case MENU:// reset everything back to original point
        ResetEnemy (Enemy);
        *ArrowPositionForMenu = 2;
        CurrentState = IDLE;
        break;
    }
    return ReturnValue;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                          FINITE STATE MACHINE FOR JOYSTICK ARROW
// this function get direction of the joystick then pass back to the main funtion to tell the arrow where to go
J_Direction GetDirectionofJoyStickArrow (int CoordinateY, int *Arrow, Screen CurrentScreen)
{
    static S_state S = InitialMid; // initial state is mid
    J_Direction ReturnValue = mid;
    switch (S)
    {
        case InitialMid: // if the joystick go up or go down, go to the next state
            if ( CoordinateY > MinUp )
                S = UpWard;
            else if (CoordinateY < MinDown)
                S = DownWard;
            break;

        case UpWard: // if the joystick move upward then move back, return up to the main function
            if (CoordinateY < MinUp && CoordinateY > MinDown)
            {
                S = InitialMid;
                ReturnValue = up;
                MovingArrow(up, Arrow, CurrentScreen);
            }
            break;

        case DownWard:// if the joystick move downwardd then move back, return up to the main function
            if (CoordinateY > MinDown && CoordinateY < MinUp)
            {
                S = InitialMid;
                ReturnValue = down;
                MovingArrow(down, Arrow, CurrentScreen);
            }
            break;
    }
    return ReturnValue;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                          JOYSTICK IRONMAN
// this function will get the joystick directionof iroman then pass back to the main function.
J_Direction GetDirectionofJoyStickIronMan (int CoordinateX, int CoordinateY)
{
    J_Direction ReturnValue;
    if (CoordinateX > MinRight)
        ReturnValue = right; // return right as long as the jt is right
    else if (CoordinateX < MinLeft)
        ReturnValue = left;// return left as long as the jt is right
    else if (CoordinateY > MinUp)
        ReturnValue = up;// return up as long as the jt is right
    else if (CoordinateY < MinDown)
        ReturnValue = down;// return down as long as the jt is right
    else
        ReturnValue = mid;
    return ReturnValue;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                          MOVING ARROW FOR MENU SCREEN

// this function will take in the direction of the arrow then move it
void MovingArrow(J_Direction input, int *Arrow, Screen CurrentScreen)
{
    if (CurrentScreen == MENU || CurrentScreen == PAUSE)
    {
    LCDSetFgColor(yellow);
    PrintString(">", *Arrow , 0);
        if (input == down)
        {
            if (*Arrow == 4 && CurrentScreen == MENU) // setting pound for the arrow
                *Arrow = 2;
            else if (*Arrow == 3 && CurrentScreen == PAUSE)
                *Arrow = 2;
            else
                *Arrow = *Arrow + 1;
        }
        else if (input == up) // move up depends on which screen
        {
            if (*Arrow == 2 && CurrentScreen == MENU)
                *Arrow = 4;
            else if (*Arrow == 2 && CurrentScreen == PAUSE)
                *Arrow = 3;
            else
            *Arrow = *Arrow - 1;
        }

    LCDSetFgColor(black);
    PrintString(">", *Arrow , 0);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                          MOVING IRONMAN FOR PLAY SCREEN
// this function will move the iron man
void MovingIronMan(J_Direction input, int *Arrow, Screen CurrentScreen)
{
    if (CurrentScreen == PLAY)
    {
    LCDSetFgColor(black);
    EraseIronMan(*Arrow); // erase the car after it moves to the new location
        if (input == left)
        {
            if (*Arrow > 5) // bound for the car
                *Arrow = *Arrow - 1;
        }
        else if (input == right)
        {
            if (*Arrow <= 52)
            *Arrow = *Arrow + 1;
        }
        LCDSetFgColor(black);
        DrawIronMan(*Arrow, 111);
    }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                              RANDOM BITS TO DECIMAL
// this recursive function helps convert binary to decimal
int conversion(int n)
{
    if (n == 0)
    {
        return 1;
    }
    return 2 * conversion (n - 1);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(void) {
    static OneShotEnemyTimer OST30;
    WDT_A_hold(WDT_A_BASE);
    static OneShot50msTimer OST50;
    BSP_Clock_InitFastest();
    InitGraphics();
    InitHWTimers();
    InitButtons();
    InitLEDs();
    initJoyStick();
    initADC_Multi();
    startADC();
    InitOneShot50msTimer(&OST50, TIMER32_1_BASE,OSTIME50IRONMAN);
    InitOneShotEnemyTimer(&OST30, TIMER32_1_BASE,OSTIMEENEMY);

    Screen CurrentScreen = MENU;
    unsigned vx, vy;
    int checker = 0, ones = 0, ArrowPositionForMenu = 2, IronManPosition = 5;
    int BitBinary[2];
    int count = 0;
    int RandomDecimal, Score = 0, HighestScore = 0, LowestScore = 0, MidScore = 0;
    StartOneShot50Timer(&OST50);
    StartOneShotEnemyTimer(&OST30);
    int Enemy[3][2] = {{InitialPosition,InitialPosition},{InitialPosition,InitialPosition},{InitialPosition,InitialPosition}};
    int newPic = 0;

    while (1) {
        // Do not delete this statement. We will use this function to check if your program does not block on anything.
        if (Booster_Bottom_Button_Pushed())
            Toggle_Launchpad_Right_Red_LED();

        getSampleJoyStick(&vx, &vy); // get the coordinate of joystick
        int randBit = (vx%2) ^ (vy%2); // generate random bit
        if (checker >=0 && checker < 2 ) // everything 3 random bit will make up and random decimal
        {
            BitBinary[checker] = randBit; // store all the random bit into an array to transfer to number later on
        }
        if (checker == 1)
            {
                RandomDecimal = 0;
                for ( count = 0; count < 2; count++)
                {
                    RandomDecimal = conversion(count)*BitBinary[count] + RandomDecimal; // generate random number
                }
            }
        checker++;
        if (checker==2)
            checker = 0;
        if (OneShot50TimerExpired(&OST50)) // check the car moving every 50 ms
        {
         if (CurrentScreen == PLAY) // the car only move once the current screen is play, otherwise, its not doing anything
         {
             MovingIronMan(GetDirectionofJoyStickIronMan(vx,vy), &IronManPosition,CurrentScreen); // move the car depends on joystick direction
             DrawObjects(RandomDecimal,&OST30, &Score,Enemy,&newPic,GetDirectionofJoyStickIronMan(vx,vy)); // generate the obstacles and make them move down
             PrintScore (Score,9,109); // update the score whenever it dodge one object
             newPic++; // this is to keep track of create an obstacle every 50 pixels
             StartOneShot50Timer(&OST50); // start timer again after its expired
         }
        }
        GetDirectionofJoyStickArrow(vy, &ArrowPositionForMenu, CurrentScreen); // get the joystick direction for the arrow
        // Current screen tell the main function which screen the user is at
        CurrentScreen = MenuOption(JoyStick_Button_Pushed(),&ArrowPositionForMenu, CurrentScreen,Booster_Top_Button_Pushed(), &IronManPosition, &Score,Enemy,&HighestScore, &MidScore, &LowestScore  );
    }
}

