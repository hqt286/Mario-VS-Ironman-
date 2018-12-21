/*
 * Screen_HAL.h
 *
 *  Created on: Mar 24, 2018
 *      Author: hungt
 */

#ifndef SCREEN_HAL_H_
#define SCREEN_HAL_H_

void DrawOpeningScreen();
void DrawMenuScreen();
void DrawInstructionScreen();
void DrawPauseScreen();
void DrawGameOverScreen(int Score);
void DrawScoreScreen(int HighestScore, int MidScore, int LowestScore);
void DrawPlayScreen(int *HelloIronMan, int HighScore);
void LCDSetBgColor(color_t c);
void LCDSetFgColor(color_t c);
void DrawIronMan(int x, int y);
void DrawFillCircle (int x, int y, int radius);
void DrawALineH (int x1, int x2, int y);
void DrawALineV (int x, int y1, int y2);
void EraseIronMan (int x);
void DrawEnemy(int x, int y);
void PrintScore (int Score, int x, int y);
void ScoreSet(int * HighestScore, int * MidScore, int * LowestScore, int CurrentScore);
#endif /* SCREEN_HAL_H_ */
