#pragma warning (disable : 4996)
#include <GL/glut.h> // includes gl.h glu.h
#include <iostream>
#include <string>
#include <time.h>
#include <math.h>
#include <windows.h>
#include "define.h"

using namespace std;

void DrawScene();
void Reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void Mousemove(int x, int y);
void SpecialKeyboard(int key, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void KeyboardUp(unsigned char key, int x, int y);
void TimerFunction(int value);
void MenuFunc(int button);
void moveCamera();
void CameraMovement();
float toRads(const float &theAngleInDegrees);

// 초기화 ==================================
const float TO_RADS = 3.141592654f / 180.0f;
const int Window_Width = 1024;
const int Window_Height = 600;
int midWindowX = Window_Width / 2;
int midWindowY = Window_Height / 2;

// 변수 ====================================
Object Screen = {};
Object Camera = {};
// 포탈====================================
Object Enter_Bullet = {};
Object Exit_Bullet = {};
Object Enter_Pos = { 0 };
Object Exit_Pos = { 0 };

float fBullet_Speed = 200.f;
float fMove_Speed = 10.f;
// Hero 이동
float fMove_X = 0.f;
float fMove_Y = 0.f;
float fMove_Z = 0.f;
// Hero Jump
float fFloor_Y = 0.f;
float fJump_time = 0.f;
bool  bJump = false;
// 게임 진행
int iGameState = 0;
// Trap
float fTrap_Move = 0;
// BOOL ====================================
bool bBack = false;
bool bFront = false;
bool bRigth = false;
bool bLeft = false;
// 포탈
bool bFall = false;
bool bEnter = false;
bool bEnter_Pos = false;
bool bExit = false;
bool bExit_Pos = false;
bool Enter_Check = false;
bool Exit_Check = false;
int Potal_type[2] = {};
// 계단
bool stair1 = true;
bool stair2 = false;
bool stair3 = false;
// 함수 ====================================
void Hero();
void Aim_Point();
void Stage1();
void Stage2();
void DrawGround();
void DrawWall(int stepSize, int groundLevel, int _i , int _j);
void Shoot();
void Mapping_Init(char* name,int textnum, int w, int h);
void Auto_Mapping(int size, int sli, int sta, int textnum);
void PotalJudge_1();
void PotalJudge_2();
void SetEnter_Pos(float fX, float fY, float fZ);
void SetExit_Pos(float fX, float fY, float fZ);
void DrawEnter();
void DrawExit();
void Potal_Move();
void BlendPortal(int type1, int type2, int type3, int index, int w, int h, int text1, int text2);
float Clamp(float min, float var, float max);
void Reset();
void Trap();
// 맵핑======================================
GLubyte *pBytes;   // 데이터를 가리킬 포인터
BITMAPINFO *info;   // 비트맵 헤더 저장할 변수
GLuint itextures[11];
// 사운드====================================
FMOD_BOOL isPlaying;
bool bHero_Portal = false;
bool bHero_die = false;
bool bGame_over = false;
bool bWow = false;

float temp;		
