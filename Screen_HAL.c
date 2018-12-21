/*
 * Screen_HAL.c
 *
 *  Created on: Mar 24, 2018
 *      Author: hungt
 */
#include <Display_HAL.h>
Graphics_Context g_sContext;
extern ironmanbabyPNG8BPP_UNCOMP;
extern mariowalk18BPP_UNCOMP;
extern PlayScreen2568BPP_UNCOMP;
extern Bang18BPP_UNCOMP;
extern Bang28BPP_UNCOMP;
extern ThemeIronman4BPP_UNCOMP;
extern MenuAndInstructionScreen4BPP_UNCOMP;


void ScoreSet(int * HighestScore, int * MidScore, int * LowestScore, int CurrentScore)
{
    if ( CurrentScore > * HighestScore)
    {
        * MidScore = * HighestScore;
        * HighestScore = CurrentScore;
    }
    else if ( CurrentScore >= * MidScore &&   CurrentScore < * HighestScore)
    {
        * LowestScore = * MidScore;
        * MidScore = CurrentScore;
    }
    else if (CurrentScore >= * LowestScore &&  CurrentScore < * MidScore)
        * LowestScore = CurrentScore ;
}

/*
     PrintScore (* HighestScore, 10, 10);
    PrintScore (* MidScore, 11, 11);
    PrintScore (* LowestScore, 12, 12);
 */

void PrintScore (int Score, int x, int y)
{
   char buf[8] = "SCORE XX";
   buf[6] = ((Score/10) % 10) + '0';
   buf[7] = ((Score   ) % 10) + '0';
   LCDDrawChar(x, y, buf[6]);
   LCDDrawChar(x, y+1, buf[7]);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                              SCREEN
void DrawOpeningScreen()
{
    Graphics_drawImage(&g_sContext, &ThemeIronman4BPP_UNCOMP, 0, 0);
    PrintString("IRONMAN vs MARIO", 0, 0);
    PrintString("By", 1, 7);
    PrintString("HUNG TRAN", 2, 3);
}

void DrawMenuScreen()
{
    Graphics_drawImage(&g_sContext, &MenuAndInstructionScreen4BPP_UNCOMP, 0, 0);
    PrintString("GAME MENU", 0, 4);
    PrintString("Play Game", 2, 2);
    PrintString("How to play", 3,2);
    PrintString("Score History", 4,2);
    PrintString(">", 2 , 0);
}

void DrawInstructionScreen()
{
    LCDClearDisplay(MY_YELLOW);
    PrintString("INSTRUCTIONS", 0, 2);
    PrintString("USE THE JOYSTICK", 1, 0);
    PrintString("TO MOVE IRONMAN", 2, 0);
    PrintString("AND DODGE THE", 3, 0);
    PrintString("COMING MARIO.", 4, 0);
    PrintString("BTN1-MENU", 7, 6);
}

void DrawPauseScreen()
{
    LCDClearDisplay(MY_YELLOW);
    PrintString("GAME PAUSE", 0, 3);
    PrintString("Continue", 2, 2);
    PrintString("Menu", 3,2);
    PrintString(">", 2 , 0);
}

void DrawGameOverScreen(int Score)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        Graphics_drawImage(&g_sContext, &Bang18BPP_UNCOMP, 0, 0);
        Graphics_drawImage(&g_sContext, &Bang28BPP_UNCOMP, 0, 0);
    }
    //LCDClearDisplay(MY_YELLOW);
    Graphics_drawImage(&g_sContext, &MenuAndInstructionScreen4BPP_UNCOMP, 0, 0);
    PrintString("GAME OVER", 0, 4);
    PrintString("Score", 2, 0);
    PrintString("GOOD LUCK NEXT", 3,0);
    PrintString("TIME!", 4 , 5);
    PrintString("Wait 3 sec", 7, 3);
    PrintScore (Score, 10, 110);
}

void DrawScoreScreen(int HighestScore, int MidScore, int LowestScore)
{
    Graphics_drawImage(&g_sContext, &MenuAndInstructionScreen4BPP_UNCOMP, 0, 0);
    PrintString("SCORE HISTORY", 0, 1);
    PrintString("1st", 2, 2);
    PrintString("2nd", 3, 2);
    PrintString("3rd", 4, 2);
    PrintScore (HighestScore, 10, 11);
    PrintScore (MidScore, 11, 11);
    PrintScore (LowestScore, 12,11);
    PrintString("BTN1-MENU", 7, 6);
}

void DrawPlayScreen(int *HelloIronMan, int HighScore)
{
    int theline;
    LCDClearDisplay(MY_YELLOW);
    Graphics_drawImage(&g_sContext, &PlayScreen2568BPP_UNCOMP, 0, 0);
    Graphics_drawString(&g_sContext, "SCORE" , -1, 73, 2, true);
    Graphics_drawString(&g_sContext, "HIGH" , -1, 73, 60, true);
    Graphics_drawString(&g_sContext, "SCORE" , -1, 73, 80, true);
    PrintScore (HighScore, 14, 13);
    Graphics_drawImage(&g_sContext, &ironmanbabyPNG8BPP_UNCOMP, *HelloIronMan, 111);
}

void DrawIronMan(int x, int y)
{
    Graphics_drawImage(&g_sContext, &ironmanbabyPNG8BPP_UNCOMP, x, y);
}

void DrawFillCircle (int x, int y, int radius)
{
    Graphics_fillCircle(&g_sContext, x, y, radius);
}

void DrawALineH (int x1, int x2, int y)
{
    Graphics_drawLineH(&g_sContext,x1,x2,y);
}

void DrawALineV (int x, int y1, int y2)
{
    Graphics_drawLineV(&g_sContext,x,y1,y2);
}

void EraseIronMan (int x)
{
    Graphics_drawLineV(&g_sContext,x,111,126);
    Graphics_drawLineV(&g_sContext,x + 15 ,111,126);
}

void DrawEnemy(int x, int y)
{
    Graphics_drawImage(&g_sContext, &mariowalk18BPP_UNCOMP, x, y);
}



