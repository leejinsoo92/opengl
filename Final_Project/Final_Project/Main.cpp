#include "Main.h"


void main(int argc, char *argv[])
{
	srand((unsigned)time(NULL));
	//초기화 함수들 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정 
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정 
	glutInitWindowSize(Window_Width, Window_Height); // 윈도우의 크기 지정 
	//glutFullScreen();
	glutCreateWindow("Term - Project"); // 윈도우 생성 (윈도우 이름)
	SoundInit();

	glutTimerFunc(20, TimerFunction, 1);
	glutTimerFunc(20, TimerFunction, 2);
	glutTimerFunc(10, TimerFunction, 3);

	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutPassiveMotionFunc(Mousemove);
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(KeyboardUp);
	glutDisplayFunc(DrawScene); // 출력 함수의 지정
	SetCursor(NULL);
	ShowCursor(FALSE);

	glutMainLoop();

	SoundRelease();


}
	


// 윈도우 출력 함수
void DrawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (iGameState == 0){
		glPushMatrix();
		glRotatef(-10, 1.f, 0.f, 0.f);
		glEnable(GL_TEXTURE_2D);
		glColor3ub(255, 255, 255);
		glBindTexture(GL_TEXTURE_2D, itextures[9]);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(-520.f, -520.f, -600.f);
		glTexCoord2f(0, 1);
		glVertex3f(-520.f, 520.f, -600.f);
		glTexCoord2f(1, 1);
		glVertex3f(520.f, 520.f, -600.f);
		glTexCoord2f(1, 0);
		glVertex3f(520.f, -520.f, -600.f);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}
	else if (iGameState == 10){
		glPushMatrix();
		glRotatef(-10, 1.f, 0.f, 0.f);
		glEnable(GL_TEXTURE_2D);
		glColor3ub(255, 255, 255);
		glBindTexture(GL_TEXTURE_2D, itextures[10]);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(-520.f, -520.f, -600.f);
		glTexCoord2f(0, 1);
		glVertex3f(-520.f, 520.f, -600.f);
		glTexCoord2f(1, 1);
		glVertex3f(520.f, 520.f, -600.f);
		glTexCoord2f(1, 0);
		glVertex3f(520.f, -520.f, -600.f);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}

	else if (iGameState == 1){
			glPushMatrix(); { //카메라
				Aim_Point();

				glColor3ub(255, 255, 255);
				glTranslatef(Screen.fX, Screen.fY - 200.f, Screen.fZ + 150);
				glRotated(Screen.fX_Rot, 1, 0, 0);
				glRotated(Screen.fY_Rot, 0, 1, 0);
				glRotated(Screen.fZ_Rot, 0, 0, 1);

				Hero();

				glTranslatef(17.f, 205.f, 0.f);

				// 캐릭터 시점 ----------------------------------------------
				glTranslatef(-Camera.fX, -Camera.fY, -Camera.fZ);
				glRotated(-180.f, 0.f, 0.f, 1.f);
				glRotated(-Camera.fX_Rot, 1, 0, 0);
				glRotated(-Camera.fY_Rot, 0, 1, 0);
				glTranslatef(fMove_X, fMove_Y, fMove_Z);
				CameraMovement();
				//------------------------------------------------------------

				// 포탈 총알 (Enter)
				if (bEnter)
				{
					glPushMatrix();
					glTranslatef(Enter_Bullet.fMove_X, Enter_Bullet.fMove_Y, Enter_Bullet.fMove_Z);
					Auto_Mapping(5, 15, 15, 1);
					glPopMatrix();
				}
				// 포탈 총알 (Exit)
				if (bExit)
				{
					glPushMatrix();
					glTranslatef(Exit_Bullet.fMove_X, Exit_Bullet.fMove_Y, Exit_Bullet.fMove_Z);
					Auto_Mapping(5, 15, 15, 2);
					glPopMatrix();
				}

				glRotated(180.f, 0.f, 0.f, 1.f);
				glTranslatef(-17.f, -205.f, 0.f);

				// Stage1
				Stage1();
				// Trap
				Trap();

				// 포탈 위치
				if (Enter_Check)
				{
					glColor3ub(0, 0, 255);
					DrawEnter();
				}

				if (Exit_Check)
				{
					glColor3ub(255, 0, 0);
					DrawExit();
				}

			}glPopMatrix();//카메라
	}//stage1

	else if (iGameState == 2){
			glPushMatrix(); { //카메라
				Aim_Point();

				glColor3ub(255, 255, 255);
				glTranslatef(Screen.fX, Screen.fY - 200.f, Screen.fZ + 150);
				glRotated(Screen.fX_Rot, 1, 0, 0);
				glRotated(Screen.fY_Rot, 0, 1, 0);
				glRotated(Screen.fZ_Rot, 0, 0, 1);

				Hero();

				glTranslatef(17.f, 205.f, 0.f);

				// 캐릭터 시점 ----------------------------------------------
				glTranslatef(-Camera.fX, -Camera.fY, -Camera.fZ);
				glRotated(-180.f, 0.f, 0.f, 1.f);
				glRotated(-Camera.fX_Rot, 1, 0, 0);
				glRotated(-Camera.fY_Rot, 0, 1, 0);
				glTranslatef(fMove_X, fMove_Y, fMove_Z);
				CameraMovement();
				//------------------------------------------------------------

				// 포탈 총알 (Enter)
				if (bEnter)
				{
					glPushMatrix();
					glTranslatef(Enter_Bullet.fMove_X, Enter_Bullet.fMove_Y, Enter_Bullet.fMove_Z);
					Auto_Mapping(5, 15, 15, 1);
					glPopMatrix();
				}
				// 포탈 총알 (Exit)
				if (bExit)
				{
					glPushMatrix();
					glTranslatef(Exit_Bullet.fMove_X, Exit_Bullet.fMove_Y, Exit_Bullet.fMove_Z);
					Auto_Mapping(5, 15, 15, 2);
					glPopMatrix();
				}

				glRotated(180.f, 0.f, 0.f, 1.f);
				glTranslatef(-17.f, -205.f, 0.f);

				// Stage2
				Stage2();

				// 포탈 위치
				if (Enter_Check)
				{
					glColor3ub(0, 0, 255);
					DrawEnter();
				}

				if (Exit_Check)
				{
					glColor3ub(255, 0, 0);
					DrawExit();
				}

			}glPopMatrix();//카메라
	}//stage2

	glutSwapBuffers();
}

void Reshape(int w, int h)
{
	glGenTextures(11, itextures);
	//
	Mapping_Init("texture/Arm.bmp", 0, 256, 512);
	Mapping_Init("texture/enter.bmp", 1, 64, 64);
	Mapping_Init("texture/exit.bmp", 2, 64, 64);
	Mapping_Init("texture/floor.bmp", 3, 280, 278);
	Mapping_Init("texture/wall.bmp", 4, 128, 128);
	Mapping_Init("texture/out.bmp", 5, 320, 490);
	Mapping_Init("texture/mask.bmp", 6, 512, 512);
	Mapping_Init("texture/entersprite.bmp", 7, 512, 512);
	Mapping_Init("texture/exitsprite.bmp", 8, 512, 512);
	Mapping_Init("texture/title.bmp", 9, 1024, 600);
	Mapping_Init("texture/gameover.bmp", 10, 1024, 600);

	// 텍스처 모드 설정
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0f, w / h, 1.0, 30000.0);
	glTranslatef(0.0, 0.0, -300.0);
	glRotatef(10, 1.f, 0.f, 0.f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);



}


void Keyboard(unsigned char key, int x, int y)
{
	if (bFall)
		return;
	switch (key)
	{
	//
	case '1': temp += 100.f; break;
	case '2': temp -= 100.f; break;
	//
	case 'w':
	case 'W':		bFront = true;	break;
	case 's':
	case 'S':		bBack = true;	break;
	case 'a':
	case 'A':		bLeft = true;	break;
	case 'd':
	case 'D':		bRigth = true;	break;
	case ESC:      glutDestroyWindow(1);      exit(0);
		break;
	case SPACE:
		if (iGameState == 0)
		{
			iGameState = 1;
		}
		else if (iGameState == 10) // 게임 클리어시
		{
			glutDestroyWindow(1);      exit(0);
		}
		if (bJump)
			return;
		bJump = true;
		break;
	}
	glutPostRedisplay();
}

void KeyboardUp(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
	case 'W':      bFront = false;      break;
	case 's':
	case 'S':      bBack = false;      break;
	case 'a':
	case 'A':      bLeft = false;      break;
	case 'd':
	case 'D':      bRigth = false;      break;
	}
	glutPostRedisplay();
}

void TimerFunction(int value)
{
	if (value == 1)
	{
		FMOD_Channel_IsPlaying(g_pTempChannel, &isPlaying);
		if (isPlaying == 0){
			FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Stage1, 0, &g_pTempChannel);
		}
		FMOD_System_Update(g_System);

		if (Camera.fY_Rot < 0 && Camera.fY_Rot > -180.0f)
			Enter_Bullet.fX = -15;

		if (Camera.fY_Rot > 0 && Camera.fY_Rot < 180.0f)
			Enter_Bullet.fX = -15;

		if (bEnter)
			Shoot();
		if (bExit)
			Shoot();

		// 마우스 화면 안나가게
		glutWarpPointer(Window_Width / 2, Window_Height / 2);
		glutTimerFunc(30, TimerFunction, 1);
		glutPostRedisplay();
	}
	else if (value == 2)
	{
		// Core (Jump)
		if (bJump)
		{
			fJump_time += 0.2f;
			fMove_Y -= -GRAVITY + (0.98 * fJump_time * fJump_time) / 2.f;
			if (fMove_Y <= fFloor_Y)
			{
				fJump_time = 0.f;
				bJump = false;
				fMove_Y = fFloor_Y;
			}
		}
		else
			fMove_Y += -GRAVITY - 20  + (0.98f) / 2.f;
		 

		// Stage 1
		if (iGameState == 1)
		{
			// 충돌검사(추락)
			if (fMove_Y <= fFloor_Y &&
				(fMove_Z <= 1000.f || fMove_Z >= 2000.f))
			{
				fMove_Y = 0.f;
				fFloor_Y = 0.f;
			}
			else if (fMove_Y <= -200.f)
			{
				bBack = false;	// 추락시 이동 X
				bFront = false;
				bRigth = false;
				bLeft = false;
				bFall = true; // 추락시 키입력 방지.
			}
			//리스폰
			if (fMove_Y <= -3000.f)
			{
				bHero_die = true;
				bFall = false;	// 추락시 키입력 방지 풀기
				Reset();
			}

			// 포탈 판단
			PotalJudge_1();

			// 포탈 이동
			Potal_Move();

			// Stage2 이동
			if (fMove_X >= -100.f && fMove_X <= 100.f && fMove_Z >= 4000.f)
			{
				iGameState = 2;
				bWow = true;
				Reset();
			}
			// 캐릭터 맵 충돌
			fMove_X = Clamp(-2000.f, fMove_X, 2000.f);
			fMove_Z = Clamp(-1000.f, fMove_Z, 4000.f);

			// 함정 내려오는 모션
			if (fTrap_Move != 2000.f)
				fTrap_Move += 2.f;
		} // Stage1

		else if (iGameState == 2)
		{
			fMove_X = Clamp(-2000.f, fMove_X, 2000.f);

			// 충돌검사(추락)
			if (fMove_Y <= fFloor_Y &&
				(fMove_Z <= 2400.f || fMove_Z >= -860.f))
			{
				fMove_Y = 0.f;
				fFloor_Y = 0.f;
			}

			if (fMove_Y <= fFloor_Y &&
				(fMove_Z <= 5000.f && fMove_Z >= 2600.f))
			{
				fMove_Y = 2000.f;
				fFloor_Y = 2000.f;
			}
			
			// 충돌검사(추락)
			if (fMove_Y <= fFloor_Y &&
				fMove_Z <= -1000.f)
			{
				fMove_Y = 4000.f;
				fFloor_Y = 4000.f;
			}
			else if (fMove_Y <= fFloor_Y &&
				fMove_Z >= 2500.f)
			{
				fMove_Y = 2000.f;
				fFloor_Y = 2000.f;
				stair1 = false;
				stair2 = true;
			}
			else if (fMove_Y <= fFloor_Y)
			{
				fMove_Y = 0.f;
				fFloor_Y = 0.f;
			}

			// 캐릭터 맵 충돌
			fMove_X = Clamp(-2000.f, fMove_X, 2000.f);
			if (fMove_Y == 0)
			{
				fMove_Z = Clamp(-900.f, fMove_Z, 2400.f);
			}
			if (fMove_Y == 2000)
			{
				fMove_Z = Clamp(-900.f, fMove_Z, 4500.f);
			}
			/*if (fMove_Y == 4000)
			{
				fMove_Z = Clamp(-900.f, fMove_Z, -2500.f);
			}
*/
			// 포탈 판단
			PotalJudge_2();

			// 포탈 이동
			Potal_Move();

			// Stage10 이동(종료)
			if (fMove_X >= -100.f && fMove_X <= 100.f && fMove_Z <= -3000.f)
			{
				iGameState = 10;
				bGame_over = true;
			}
		}

		glutTimerFunc(10, TimerFunction, 2);
		glutPostRedisplay();
	}

	else if (value == 3)	// Sound
	{
		if (bHero_die){
			FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_scream, 0, &g_screamChannel);
			bHero_die = false;
		}
		if (bHero_Portal){
			FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_portalin, 0, &g_In);
			bHero_Portal = false;
		}
		if (bGame_over){
			FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_gameover, 0, &g_gameoverChannel);
			bGame_over = false;
		}
		if (bWow){
			FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_wow, 0, &g_wowChannel);
			bWow = false;
		}
		
		glutTimerFunc(10, TimerFunction, 3);
		glutPostRedisplay();
	}
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_shoot, 0, &g_Channel);

		bEnter = true;
		bEnter_Pos = true;

		if (bEnter_Pos)
		{
			Enter_Bullet.fMove_X = -fMove_X;
			Enter_Bullet.fMove_Y = -fMove_Y;
			Enter_Bullet.fMove_Z = -fMove_Z;

			Enter_Bullet.fX_Rot = Camera.fX_Rot;
			Enter_Bullet.fY_Rot = Camera.fY_Rot;
			Enter_Bullet.fZ_Rot = Camera.fZ_Rot;

			bEnter_Pos = false;
		}

	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_shoot, 0, &g_Channel);

		bExit = true;
		bExit_Pos = true;

		if (bExit_Pos)
		{
			Exit_Bullet.fMove_X = -fMove_X;
			Exit_Bullet.fMove_Y = -fMove_Y;
			Exit_Bullet.fMove_Z = -fMove_Z;

			Exit_Bullet.fX_Rot = Camera.fX_Rot;
			Exit_Bullet.fY_Rot = Camera.fY_Rot;
			Exit_Bullet.fZ_Rot = Camera.fZ_Rot;

			bExit_Pos = false;
		}
	}
	glutPostRedisplay();
}

void Mousemove(int x, int y)
{
	GLfloat vertMouseSensitivity = 15.0f;
	GLfloat horizMouseSensitivity = 15.0f;

	int horizMovement = x - midWindowX;
	int vertMovement = y - midWindowY;

	Camera.fX_Rot += vertMovement / vertMouseSensitivity;
	Camera.fY_Rot += horizMovement / horizMouseSensitivity;

	if (Camera.fX_Rot < -90.0f)
	{
		Camera.fX_Rot = -90.0f;
	}
	if (Camera.fX_Rot > 90.0f)
	{
		Camera.fX_Rot = 90.0f;
	}
	if (Camera.fY_Rot < -180.0f)
	{
		Camera.fY_Rot += 360.0f;
	}
	if (Camera.fY_Rot > 180.0f)
	{
		Camera.fY_Rot -= 360.0f;
	}
	glutPostRedisplay();
}

void Hero()
{
	glPushMatrix(); { // Hero
		glTranslatef(0.f, 200.f, 70.f);   // 초기좌표.
		glPushMatrix();// 무기
		{
			glTranslatef(18.f, 0.f, 0.f);   // 1단(흰)
			glColor3ub(220, 220, 220);
			glScalef(0.6f, 0.8f, 3.f);
			glutSolidCube(20);

			glPushMatrix();
			glTranslatef(3.f, 0.f, 100.5f);
			glColor3ub(0, 0, 0);
			glLineWidth(3);
			glBegin(GL_LINES);         // 1단 줄
			glVertex3f(-25.f, 50.f, -85.f);
			glVertex3f(-25.f, 50.f, -80.f);
			glEnd();
			glLineWidth(1);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(1.f, 0.f, -10.f);   // 2단(검)
			glColor3ub(0, 0, 0);
			glScalef(2.f, 1.5f, 1.f);
			glutSolidCube(10);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(1.f, 0.f, -17.f);   // 2단(파)
			glColor3ub(30, 144, 255);
			glScalef(0.7f, 0.6f, 0.2f);
			glutSolidCube(30);
			glPopMatrix();
		}
		glPopMatrix();
		glPushMatrix();// 왼쪽팔
		{
			glTranslatef(5.f, -10.f, 0.f);
			glRotatef(-10.f, 0.f, 1.f, 0.f);
			{   // 텍스처 매핑 활성화
				glScalef(1.f, 1.f, 10.f);
				glEnable(GL_TEXTURE_2D);
				glEnable(GL_TEXTURE_GEN_S);
				glEnable(GL_TEXTURE_GEN_T);
				glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
				glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
				glBindTexture(GL_TEXTURE_2D, itextures[0]);
				glColor3ub(255, 255, 255);
				glutSolidCube(10);
				glDisable(GL_TEXTURE_GEN_S);
				glDisable(GL_TEXTURE_GEN_T);
				glDisable(GL_TEXTURE_2D);
			}
		}
		glPopMatrix();

		glPushMatrix(); {   // 왼주먹
			glTranslatef(15.0f, -5.f, -45.f);
			glRotatef(-20, 0.f, 0.f, 1.f);
			glScalef(1.f, 1.7f, 1.f);
			Auto_Mapping(7, 25, 25,0);
		}glPopMatrix();

	}glPopMatrix(); // Hero
}

void DrawWall(int stepSize, int groundLevel, int _i, int _j, int iType)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, itextures[iType]);
	glColor3ub(255, 255, 255);

	glBegin(GL_QUADS);
	for (int i = -_i; i < _i; i += 1) //장판
	{
		for (int j = -_j; j < _j; j += 1)
		{
			glTexCoord2f(0, 0);
			glVertex3f(i * stepSize, -groundLevel, j * stepSize);
			glTexCoord2f(0, 1);
			glVertex3f(i * stepSize, -groundLevel, j * stepSize + stepSize);
			glTexCoord2f(1, 1);
			glVertex3f(i * stepSize + stepSize, -groundLevel, j * stepSize + stepSize);
			glTexCoord2f(1, 0);
			glVertex3f(i * stepSize + stepSize, -groundLevel, j * stepSize);
		}
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void DrawGround()
{
	GLfloat stepSize = 1000.f;
	GLfloat groundLevel = -50.0f;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, itextures[3]);
	glColor3ub(255, 255, 255);

	glBegin(GL_QUADS);
	for (int i = -2; i < 2; i += 1) //장판
	{
		for (int j = -1; j < 1; j += 1)
		{
			glTexCoord2f(0, 0);
			glVertex3f(i * stepSize, -groundLevel, j * stepSize);
			glTexCoord2f(0, 1);
			glVertex3f(i * stepSize, -groundLevel, j * stepSize + stepSize);
			glTexCoord2f(1, 1);
			glVertex3f(i * stepSize + stepSize, -groundLevel, j * stepSize + stepSize);
			glTexCoord2f(1, 0);
			glVertex3f(i * stepSize + stepSize, -groundLevel, j * stepSize);
		}
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

// 마우스 움직임
float toRads(const float &theAngleInDegrees)
{
	return theAngleInDegrees * TO_RADS;
}

void CameraMovement()
{

	if (bBack == true)
	{
		float pitchFactor = cos(toRads(Camera.fX_Rot));
		fMove_X -= (fMove_Speed * float(sin(toRads(Camera.fY_Rot)))) * pitchFactor;
		float yawFactor = float(cos(toRads(Camera.fX_Rot)));
		fMove_Z += (fMove_Speed * float(cos(toRads(Camera.fY_Rot))) * -1.0f) * yawFactor;
	}

	if (bFront == true)
	{
		float pitchFactor = cos(toRads(Camera.fX_Rot));
		fMove_X -= (fMove_Speed * float(sin(toRads(Camera.fY_Rot))) * -1.0f) * pitchFactor;
		float yawFactor = float(cos(toRads(Camera.fX_Rot)));
		fMove_Z += (fMove_Speed * float(cos(toRads(Camera.fY_Rot)))) * yawFactor;
	}

	if (bRigth == true)
	{
		float yRotRad = toRads(Camera.fY_Rot);

		fMove_X -= -fMove_Speed * float(cos(yRotRad));
		fMove_Z += -fMove_Speed * float(sin(yRotRad));
	}

	if (bLeft == true)
	{
		float yRotRad = toRads(Camera.fY_Rot);

		fMove_X -= fMove_Speed * float(cos(yRotRad));
		fMove_Z += fMove_Speed * float(sin(yRotRad));
	}
	
	Camera.fX_Speed = fMove_X;
	Camera.fY_Speed = fMove_Y;
	Camera.fZ_Speed = fMove_Z;


	if (Camera.fX_Speed > fMove_Speed)
		Camera.fX_Speed = fMove_Speed;

	if (Camera.fX_Speed < -fMove_Speed)
		Camera.fX_Speed = -fMove_Speed;


	if (Camera.fY_Speed > fMove_Speed)
		Camera.fY_Speed = fMove_Speed;

	if (Camera.fY_Speed < -fMove_Speed)
		Camera.fY_Speed = -fMove_Speed;


	if (Camera.fZ_Speed > fMove_Speed)
		Camera.fZ_Speed = fMove_Speed;

	if (Camera.fZ_Speed < -fMove_Speed)
		Camera.fZ_Speed = -fMove_Speed;
}


void Shoot()
{
	if (bEnter)
	{
		float pitchFactor = cos(toRads(Enter_Bullet.fX_Rot));
		Enter_Bullet.fMove_X += (fBullet_Speed * float(sin(toRads(Enter_Bullet.fY_Rot)))* -1.0f) * pitchFactor;

		Enter_Bullet.fMove_Y += fBullet_Speed * float(sin(toRads(Enter_Bullet.fX_Rot)));

		float yawFactor = float(cos(toRads(Enter_Bullet.fX_Rot)));
		Enter_Bullet.fMove_Z -= fBullet_Speed * float(cos(toRads(Enter_Bullet.fY_Rot))) * yawFactor;

		Enter_Bullet.fX_Speed = Enter_Bullet.fMove_X;
		Enter_Bullet.fY_Speed = Enter_Bullet.fMove_Y;
		Enter_Bullet.fZ_Speed = Enter_Bullet.fMove_Z;
	}

	if (bExit)
	{
		float pitchFactor = cos(toRads(Exit_Bullet.fX_Rot));
		Exit_Bullet.fMove_X += (fBullet_Speed * float(sin(toRads(Exit_Bullet.fY_Rot)))* -1.0f) * pitchFactor;

		Exit_Bullet.fMove_Y += fBullet_Speed * float(sin(toRads(Exit_Bullet.fX_Rot)));

		float yawFactor = float(cos(toRads(Enter_Bullet.fX_Rot)));
		Exit_Bullet.fMove_Z -= fBullet_Speed * float(cos(toRads(Exit_Bullet.fY_Rot))) * yawFactor;


		Exit_Bullet.fX_Speed = Exit_Bullet.fMove_X;
		Exit_Bullet.fY_Speed = Exit_Bullet.fMove_Y;
		Exit_Bullet.fZ_Speed = Exit_Bullet.fMove_Z;

	}
}

void Aim_Point()
{
	glPushMatrix();
	glColor3ub(0, 255, 0);
	glLineWidth(3);
	glBegin(GL_LINES);         // 초점 (+)
	glVertex3f(3.f, 34.f, 0.f);
	glVertex3f(9.f, 34.f, 0.f);
	glVertex3f(6.f, 38.f, 0.f);
	glVertex3f(6.f, 30.f, 0.f);
	glEnd();
	glPopMatrix();

}

void Auto_Mapping(int size, int sli, int sta, int textnum)
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glBindTexture(GL_TEXTURE_2D, itextures[textnum]);
	glColor3ub(255, 255, 255);
	glutSolidSphere(size, sli, sta);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);

}

void Mapping_Init(char* name, int textnum, int w, int h)
{
	glBindTexture(GL_TEXTURE_2D, itextures[textnum]);
	pBytes = LoadDIBitmap(name, &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

}

float Clamp(float min, float var, float max)
{
	return max(min, min(var, max));
}

void SetEnter_Pos(float fX, float fY, float fZ)
{
	Enter_Pos.fX = -fX + 17;
	Enter_Pos.fY = -fY + 205;
	Enter_Pos.fZ = fZ;
}

void SetExit_Pos(float fX, float fY, float fZ)
{
	Exit_Pos.fX = -fX + 17;
	Exit_Pos.fY = -fY + 205;
	Exit_Pos.fZ = fZ;
}

void DrawEnter()
{
	glPushMatrix();
	glTranslatef(Enter_Pos.fX, Enter_Pos.fY, Enter_Pos.fZ);
	BlendPortal(ENTER_FRONT, ENTER_SIDE, ENTER_FLOOR, 0, 150, 300, 6, 7);
	glPopMatrix();
}

void DrawExit()
{
	glPushMatrix();
	glTranslatef(Exit_Pos.fX, Exit_Pos.fY, Exit_Pos.fZ);
	BlendPortal(EXIT_FRONT, EXIT_SIDE, EXIT_FLOOR, 1, 150, 300, 6, 8);
	glPopMatrix();
}

void PotalJudge_1()
{
	// 입구 포탈
	// 우
	if (Enter_Bullet.fMove_X <= -2000 + 100)
	{
		Potal_type[0] = ENTER_SIDE;
		bEnter = false;
		SetEnter_Pos(Enter_Bullet.fMove_X, Enter_Bullet.fMove_Y, Enter_Bullet.fMove_Z);
		Enter_Check = true;
	}
	// 좌
	if (Enter_Bullet.fMove_X >= 2000 - 100)
	{
		Potal_type[0] = ENTER_SIDE;
		bEnter = false;
		SetEnter_Pos(Enter_Bullet.fMove_X, Enter_Bullet.fMove_Y, Enter_Bullet.fMove_Z);
		Enter_Check = true;
	}
	// 앞
	if (Enter_Bullet.fMove_Z <= -4000 + 200)
	{
		Potal_type[0] = ENTER_FRONT;
		bEnter = false;
		SetEnter_Pos(Enter_Bullet.fMove_X, Enter_Bullet.fMove_Y, Enter_Bullet.fMove_Z);
		Enter_Check = true;
	}
	// 뒤
	if (Enter_Bullet.fMove_Z >= 1000 - 100)
	{
		Potal_type[0] = ENTER_FRONT;
		bEnter = false;
		SetEnter_Pos(Enter_Bullet.fMove_X, Enter_Bullet.fMove_Y, Enter_Bullet.fMove_Z);
		Enter_Check = true;
	}
	// 바닥
	if (-Enter_Bullet.fMove_Y <= -200
		&& (Enter_Bullet.fMove_Z <= 1000 - 100 && Enter_Bullet.fMove_Z >= -1000)
		|| -Enter_Bullet.fMove_Y <= -200
		&& (Enter_Bullet.fMove_Z <= -2000 && Enter_Bullet.fMove_Z >= -4000))
	{
		Potal_type[0] = ENTER_FLOOR;
		bEnter = false;
		SetEnter_Pos(Enter_Bullet.fMove_X, Enter_Bullet.fMove_Y, Enter_Bullet.fMove_Z);
		Enter_Check = true;
	}

	// 출구 포탈
	// 우
	if (Exit_Bullet.fMove_X <= -2000 + 100)
	{
		Potal_type[1] = EXIT_SIDE;
		bExit = false;
		SetExit_Pos(Exit_Bullet.fMove_X, Exit_Bullet.fMove_Y, Exit_Bullet.fMove_Z);
		Exit_Check = true;
	}
	// 좌
	if (Exit_Bullet.fMove_X >= 2000 - 100)
	{
		Potal_type[1] = EXIT_SIDE;
		bExit = false;
		SetExit_Pos(Exit_Bullet.fMove_X, Exit_Bullet.fMove_Y, Exit_Bullet.fMove_Z);
		Exit_Check = true;
	}
	// 앞
	if (Exit_Bullet.fMove_Z <= -4000 + 200)
	{
		Potal_type[1] = EXIT_FRONT;
		bExit = false;
		SetExit_Pos(Exit_Bullet.fMove_X, Exit_Bullet.fMove_Y, Exit_Bullet.fMove_Z);
		Exit_Check = true;
	}
	// 뒤
	if (Exit_Bullet.fMove_Z >= 1060 - 100)
	{
		Potal_type[1] = EXIT_FRONT;
		bExit = false;
		SetExit_Pos(Exit_Bullet.fMove_X, Exit_Bullet.fMove_Y, Exit_Bullet.fMove_Z);
		Exit_Check = true;
	}
	// 바닥
	if (-Exit_Bullet.fMove_Y <= -200
		&& (Exit_Bullet.fMove_Z <= 1000 - 100 && Exit_Bullet.fMove_Z >= -1000)
		|| -Exit_Bullet.fMove_Y <= -200
		&& (Exit_Bullet.fMove_Z <= -2000 && Exit_Bullet.fMove_Z >= -4000))
	{
		Potal_type[1] = EXIT_FLOOR;
		bExit = false;
		SetExit_Pos(Exit_Bullet.fMove_X, Exit_Bullet.fMove_Y, Exit_Bullet.fMove_Z);
		Exit_Check = true;
	}
}

void PotalJudge_2()
{
	// 입구 포탈
	// 우
	if (Enter_Bullet.fMove_X <= -2000 + 100)
	{
		Potal_type[0] = ENTER_SIDE;
		bEnter = false;
		SetEnter_Pos(Enter_Bullet.fMove_X, Enter_Bullet.fMove_Y, Enter_Bullet.fMove_Z);
		Enter_Check = true;
	}
	// 좌
	if (Enter_Bullet.fMove_X >= 2000 - 100)
	{
		Potal_type[0] = ENTER_SIDE;
		bEnter = false;
		SetEnter_Pos(Enter_Bullet.fMove_X, Enter_Bullet.fMove_Y, Enter_Bullet.fMove_Z);
		Enter_Check = true;
	}
	// 앞 1
	if (Enter_Bullet.fMove_Y >= -1500 && Enter_Bullet.fMove_Z <= -2300)
	{
		Potal_type[0] = ENTER_FRONT;
		bEnter = false;
		SetEnter_Pos(Enter_Bullet.fMove_X, Enter_Bullet.fMove_Y, Enter_Bullet.fMove_Z);
		Enter_Check = true;
	}
	// 앞 2
	if (Enter_Bullet.fMove_Z <= -4600 + 200)
	{
		Potal_type[0] = ENTER_FRONT;
		bEnter = false;
		SetEnter_Pos(Enter_Bullet.fMove_X, Enter_Bullet.fMove_Y, Enter_Bullet.fMove_Z);
		Enter_Check = true;
		fFloor_Y = 2000.f;
	}
	// 뒤 1
	if (Enter_Bullet.fMove_Y >= -3800 && Enter_Bullet.fMove_Z >= 1000 - 100)
	{
		Potal_type[0] = ENTER_FRONT;
		bEnter = false;
		SetEnter_Pos(Enter_Bullet.fMove_X, Enter_Bullet.fMove_Y, Enter_Bullet.fMove_Z);
		Enter_Check = true;
	}
	// 뒤 2
	if (Enter_Bullet.fMove_Z >= 3000 - 300)
	{
		Potal_type[0] = ENTER_FRONT;
		bEnter = false;
		SetEnter_Pos(Enter_Bullet.fMove_X, Enter_Bullet.fMove_Y, Enter_Bullet.fMove_Z);
		fFloor_Y = 4000.f;
		Enter_Check = true;
	}
	// 바닥1
	if (-Enter_Bullet.fMove_Y <= -200
		&& (Enter_Bullet.fMove_Z <= 1000 - 100 && Enter_Bullet.fMove_Z >= -1000)
		|| -Enter_Bullet.fMove_Y <= -200
		&& (Enter_Bullet.fMove_Z <= -2000 && Enter_Bullet.fMove_Z >= -4000))
	{
		Potal_type[0] = ENTER_FLOOR;
		bEnter = false;
		SetEnter_Pos(Enter_Bullet.fMove_X, Enter_Bullet.fMove_Y, Enter_Bullet.fMove_Z);
		Enter_Check = true;
	}
	// 바닥2

	if (Enter_Bullet.fMove_Y >= -1800
		&& Enter_Bullet.fMove_Z <= -2500)
	{
		Potal_type[0] = ENTER_FLOOR;
		bEnter = false;
		SetEnter_Pos(Enter_Bullet.fMove_X, Enter_Bullet.fMove_Y, Enter_Bullet.fMove_Z);
		Enter_Check = true;
	}
	//바닥 3
	if (Enter_Bullet.fMove_Y >= -3800
		&& Enter_Bullet.fMove_Z >= 1100)
	{
		Potal_type[0] = ENTER_FLOOR;
		bEnter = false;
		SetEnter_Pos(Enter_Bullet.fMove_X, Enter_Bullet.fMove_Y, Enter_Bullet.fMove_Z);
		Enter_Check = true;
	}
	

	// 출구 포탈
	// 우
	if (Exit_Bullet.fMove_X <= -2000 + 100)
	{
		Potal_type[1] = EXIT_SIDE;
		bExit = false;
		SetExit_Pos(Exit_Bullet.fMove_X, Exit_Bullet.fMove_Y, Exit_Bullet.fMove_Z);
		Exit_Check = true;
	}
	// 좌
	if (Exit_Bullet.fMove_X >= 2000 - 100)
	{
		Potal_type[1] = EXIT_SIDE;
		bExit = false;
		SetExit_Pos(Exit_Bullet.fMove_X, Exit_Bullet.fMove_Y, Exit_Bullet.fMove_Z);
		Exit_Check = true;
	}
	// 앞1
	if (Exit_Bullet.fMove_Y >= -1500 && Exit_Bullet.fMove_Z <= -2300)
	{
		Potal_type[1] = EXIT_FRONT;
		bExit = false;
		SetExit_Pos(Exit_Bullet.fMove_X, Exit_Bullet.fMove_Y, Exit_Bullet.fMove_Z);
		Exit_Check = true;
	}
	// 앞2
	if (Exit_Bullet.fMove_Z <= -4600 + 200)
	{
		Potal_type[1] = EXIT_FRONT;
		bExit = false;
		SetExit_Pos(Exit_Bullet.fMove_X, Exit_Bullet.fMove_Y, Exit_Bullet.fMove_Z);
		Exit_Check = true;
		fFloor_Y = 2000.f;
	}

	// 뒤 1
	if (Exit_Bullet.fMove_Y >= -3800 && Exit_Bullet.fMove_Z >= 1000 - 100)
	{
		Potal_type[1] = EXIT_FRONT;
		bExit = false;
		SetExit_Pos(Exit_Bullet.fMove_X, Exit_Bullet.fMove_Y, Exit_Bullet.fMove_Z);
		Exit_Check = true;
	}
	// 뒤 2
	if (Exit_Bullet.fMove_Z >= 3000 - 300)
	{
		Potal_type[1] = EXIT_FRONT;
		bExit = false;
		SetExit_Pos(Exit_Bullet.fMove_X, Exit_Bullet.fMove_Y, Exit_Bullet.fMove_Z);
		fFloor_Y = 4000.f;
		Exit_Check = true;
	}
	// 바닥
	if (-Exit_Bullet.fMove_Y <= -200
		&& (Exit_Bullet.fMove_Z <= 1000 - 100 && Exit_Bullet.fMove_Z >= -1000)
		|| -Exit_Bullet.fMove_Y <= -200
		&& (Exit_Bullet.fMove_Z <= -2000 && Exit_Bullet.fMove_Z >= -4000))
	{
		Potal_type[1] = EXIT_FLOOR;
		bExit = false;
		SetExit_Pos(Exit_Bullet.fMove_X, Exit_Bullet.fMove_Y, Exit_Bullet.fMove_Z);
		Exit_Check = true;
	}
	// 바닥2

	if (Exit_Bullet.fMove_Y >= -1800
		&& Exit_Bullet.fMove_Z <= -2500)
	{
		Potal_type[1] = EXIT_FLOOR;
		bExit = false;
		SetExit_Pos(Exit_Bullet.fMove_X, Exit_Bullet.fMove_Y, Exit_Bullet.fMove_Z);
		Exit_Check = true;
	}
	//바닥 3
	if (Exit_Bullet.fMove_Y >= -3800
		&& Exit_Bullet.fMove_Z >= 1100)
	{
		Potal_type[1] = EXIT_FLOOR;
		bExit = false;
		SetExit_Pos(Exit_Bullet.fMove_X, Exit_Bullet.fMove_Y, Exit_Bullet.fMove_Z);
		Exit_Check = true;
	}
}



void Potal_Move()
{
	if (fMove_Z <= -Enter_Pos.fZ
		&& (fMove_X <= Enter_Pos.fX + 100 && fMove_X >= Enter_Pos.fX - 100)
		&& (fMove_Y <= Enter_Pos.fY - 200 && fMove_Y >= Enter_Pos.fY - 300))
	{
		bHero_Portal = true;
		fMove_X = Exit_Pos.fX;
		fMove_Y = Exit_Pos.fY - 100;
		fMove_Z = -Exit_Pos.fZ;
	}

	if (Potal_type[0] == ENTER_FLOOR)
	{
		if ((fMove_Z <= -Enter_Pos.fZ + 100 && fMove_Z >= -Enter_Pos.fZ - 100)
			&& (fMove_X <= Enter_Pos.fX + 100 && fMove_X >= Enter_Pos.fX - 100))
		{
			bHero_Portal = true;
			fMove_X = Exit_Pos.fX;
			fMove_Y = Exit_Pos.fY - 100;
			fMove_Z = -Exit_Pos.fZ;
		}
	}
}


void Stage1()
{
	// Floor 
	glPushMatrix(); {
		glTranslatef(0.0f, -100.0f, 0.0f);
		DrawGround();
	}glPopMatrix();


	glPushMatrix(); {
		glTranslatef(0.0f, -100.0f, -3000.0f);
		DrawGround();
	}glPopMatrix();

	// Wall1
	glPushMatrix(); {
		glTranslatef(0.0f, 950.0f, 950.f);
		glRotatef(90.f, 1.f, 0.f, 0.f);
		DrawWall(500, -50, 4, 2, 4);
	}glPopMatrix();

	// Wall2
	glPushMatrix(); {
		glTranslatef(0.0f, 950.0f, -4050.f);
		glRotatef(90.f, 1.f, 0.f, 0.f);
		DrawWall(500, -50, 4, 2, 4);
	}glPopMatrix();


	// WallSide (1)
	glPushMatrix(); {
		glTranslatef(-2050.f, 950.0f, -1500.f);
		glRotatef(180.f, 1.f, 1.f, 0.f);
		DrawWall(500, -50, 2, 5, 4);

		glTranslatef(0.f, 950.0f + 3050.f, 0.f);
		DrawWall(500, -50, 2, 5, 4);
	}glPopMatrix();

	// WallSide (2)
	glPushMatrix(); {
		glTranslatef(-2050.f, -1050.f, -1500.f);
		glRotatef(180.f, 1.f, 1.f, 0.f);
		DrawWall(500, -50, 2, 1, 4);

		glTranslatef(0.f, 950.0f + 3050.f, 0.f);
		DrawWall(500, -50, 2, 1, 4);
	}glPopMatrix();

	// Out
	glEnable(GL_TEXTURE_2D);
	glPushMatrix(); {
		glTranslatef(0.0f, -50.0f, 0.0f);

		glBindTexture(GL_TEXTURE_2D, itextures[5]);
		glColor3ub(255, 255, 255);

		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(-150.f, 000.f, -3995.f);
		glTexCoord2f(0, 1);
		glVertex3f(-150.f, 600.f, -3995.f);
		glTexCoord2f(1, 1);
		glVertex3f(150.f, 600.f, -3995.f);
		glTexCoord2f(1, 0);
		glVertex3f(150.f, 000.f, -3995.f);
		glEnd();
	}glPopMatrix();

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glBindTexture(GL_TEXTURE_2D, itextures[1]);
	glColor3ub(255, 255, 255);
	glutSolidTeapot(30.f);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void Stage2()
{
	// Floor 
	glPushMatrix(); {
		glTranslatef(0.0f, -100.0f, 0.0f);
		DrawGround();
	}glPopMatrix();
	glPushMatrix(); {
		glTranslatef(0.0f, -100.0f, -1500.f);
		DrawGround();
	}glPopMatrix();
	// 앞벽1
	glPushMatrix(); {
		glTranslatef(0.0f, 950.0f, -2550.f);
		glRotatef(90.f, 1.f, 0.f, 0.f);
		DrawWall(500, -50, 4, 2, 4);
	}glPopMatrix();
	// 앞벽1 - ㅡ
	glPushMatrix(); {
		glTranslatef(0.0f, 1900.f, -3500.f);
		DrawGround();
	}glPopMatrix();
	
	// 뒷벽
	glPushMatrix(); {
		glTranslatef(0.0f, 1950.f, 950.f);
		glRotatef(90.f, 1.f, 0.f, 0.f);
		DrawWall(500, -50, 4, 4, 4);
	}glPopMatrix();
	// 앞벽2
	glPushMatrix(); {
		glTranslatef(0.0f, 3950.f, -4550.f);
		glRotatef(90.f, 1.f, 0.f, 0.f);
		DrawWall(500, -50, 4, 4, 4);
	}glPopMatrix();
	// WallSide
	glPushMatrix(); {
		glTranslatef(-2050.f, 2950.f, -500.f);
		glRotatef(180.f, 1.f, 1.f, 0.f);
		DrawWall(500, -50, 6, 8, 4);

		glTranslatef(0.f, 950.0f + 3050.f, 0.f);
		DrawWall(500, -50, 6, 8, 4);
	}glPopMatrix();
	// Floor 2
	glPushMatrix(); {
		glTranslatef(0.0f, 3900.f, 2000.f);
		DrawGround();
	}glPopMatrix();
	// Floor 2 앞벽
	glPushMatrix(); {
		glTranslatef(0.0f, 4900.f, 2900.f);
		glRotatef(90.f, 1.f, 0.f, 0.f);
		DrawWall(500, -50, 4, 2, 4);
	}glPopMatrix();


	// Out
	glEnable(GL_TEXTURE_2D);
	glPushMatrix(); {
		glTranslatef(0.0f,3950.f, 6940.f);

		glBindTexture(GL_TEXTURE_2D, itextures[5]);
		glColor3ub(255, 255, 255);

		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(-150.f, 000.f, -3995.f);
		glTexCoord2f(0, 1);
		glVertex3f(-150.f, 600.f, -3995.f);
		glTexCoord2f(1, 1);
		glVertex3f(150.f, 600.f, -3995.f);
		glTexCoord2f(1, 0);
		glVertex3f(150.f, 000.f, -3995.f);
		glEnd();
	}glPopMatrix();

	// 주전자
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glBindTexture(GL_TEXTURE_2D, itextures[1]);
	glColor3ub(255, 255, 255);
	glutSolidTeapot(30.f);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void BlendPortal(int type1, int type2,int type3, int index, int w, int h, int text1, int text2)
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	// 앞뒤
	glColor3ub(255, 255, 255);
	if (Potal_type[index] == type1)
	{
		glBlendFunc(GL_DST_COLOR, GL_ZERO);
		glBindTexture(GL_TEXTURE_2D, itextures[text1]);	// mask
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 0);
			glVertex3f(-w, -h, 0);
			glTexCoord2f(0, 1);
			glVertex3f(-w, h, 0);
			glTexCoord2f(1, 1);
			glVertex3f(w, h, 0);
			glTexCoord2f(1, 0);
			glVertex3f(w, -h, 0);
		}
		glEnd();
		glBlendFunc(GL_ONE, GL_ONE);
		glBindTexture(GL_TEXTURE_2D, itextures[text2]);	// sprite
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 0);
			glVertex3f(-w, -h, 0);
			glTexCoord2f(0, 1);
			glVertex3f(-w, h, 0);
			glTexCoord2f(1, 1);
			glVertex3f(w, h, 0);
			glTexCoord2f(1, 0);
			glVertex3f(w, -h, 0);
		}
		glEnd();
	}
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	// 좌우
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);

	glColor3ub(255, 255, 255);
	if (Potal_type[index] == type2)
	{
		glBlendFunc(GL_DST_COLOR, GL_ZERO);
		glBindTexture(GL_TEXTURE_2D, itextures[text1]);	// mask
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 0);
			glVertex3f(0, -h, -w);
			glTexCoord2f(0, 1);
			glVertex3f(0, h, -w);
			glTexCoord2f(1, 1);
			glVertex3f(0, h, w);
			glTexCoord2f(1, 0);
			glVertex3f(0, -h, w);
		}
		glEnd();
		glBlendFunc(GL_ONE, GL_ONE);
		glBindTexture(GL_TEXTURE_2D, itextures[text2]);	// sprite
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 0);
			glVertex3f(0, -h, -w);
			glTexCoord2f(0, 1);
			glVertex3f(0, h, -w);
			glTexCoord2f(1, 1);
			glVertex3f(0, h, w);
			glTexCoord2f(1, 0);
			glVertex3f(0, -h, w);
		}
		glEnd();
	}
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	// 바닥
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);

	glColor3ub(255, 255, 255);
	if (Potal_type[index] == type3)
	{
		glBlendFunc(GL_DST_COLOR, GL_ZERO);
		glBindTexture(GL_TEXTURE_2D, itextures[text1]);	// mask
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 0);
			glVertex3f(-w, 0, -h);
			glTexCoord2f(0, 1);
			glVertex3f(-w, 0, h);
			glTexCoord2f(1, 1);
			glVertex3f(w, 0, h);
			glTexCoord2f(1, 0);
			glVertex3f(w, 0, -h);
		}
		glEnd();
		glBlendFunc(GL_ONE, GL_ONE);
		glBindTexture(GL_TEXTURE_2D, itextures[text2]);	// sprite
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 0);
			glVertex3f(-w, 0, -h);
			glTexCoord2f(0, 1);
			glVertex3f(-w, 0, h);
			glTexCoord2f(1, 1);
			glVertex3f(w, 0, h);
			glTexCoord2f(1, 0);
			glVertex3f(w, 0, -h);
		}
		glEnd();
	}
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

void Trap()
{
	glPushMatrix(); {
		glTranslatef(0.0f, 2000.0f - fTrap_Move, 0.0f);
		DrawGround();
	}glPopMatrix();

	glPushMatrix(); {
		glTranslatef(0.0f, 3000.0f - fTrap_Move, -1000.f);
		glRotatef(90.f, 1.f, 0.f, 0.f);
		DrawWall(500, -50, 4, 2, 4);
	}glPopMatrix();
}

void Reset()
{
	Camera.fX_Rot = 0;
	Camera.fY_Rot = 0;
	fMove_X = 0;
	fMove_Y = 0;
	fMove_Z = 0;

	Enter_Bullet.fMove_X = 0;
	Enter_Bullet.fMove_Y = 0;
	Enter_Bullet.fMove_Z = 0;

	Exit_Bullet.fMove_X = 0;
	Exit_Bullet.fMove_Y = 0;
	Exit_Bullet.fMove_Z = 0;

	fTrap_Move = 0;

	bEnter = false;
	bEnter_Pos = false;
	Enter_Check = false;
	bExit = false;
	bExit_Pos = false;
	Exit_Check = false;

	//for (int i = 0; i < 2; ++i)
	Potal_type[0] = END;
	Potal_type[1] = END;
}
