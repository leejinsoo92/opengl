#pragma once
#define GRAVITY 18
#define ESC 27
#define SPACE 32
#include "inc/fmod.hpp"
#pragma comment (lib, "fmodex_vc.lib")

typedef struct Object
{
	float fX;
	float fY;
	float fZ;

	float fX_Rot;
	float fY_Rot;
	float fZ_Rot;

	float fX_Speed;
	float fY_Speed;
	float fZ_Speed;

	float fMove_X;
	float fMove_Y;
	float fMove_Z;
}Object;

enum PotalType
{
	ENTER_FRONT = 1,
	ENTER_SIDE,
	EXIT_FRONT,
	EXIT_SIDE,
	ENTER_FLOOR,
	EXIT_FLOOR,
	END
};

GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info)
{
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;
	// 바이너리 읽기 모드로 파일을 연다
	if ((fp = fopen(filename, "rb")) == NULL)
		return NULL;
	// 비트맵 파일 헤더를 읽는다.
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}
	// 파일이 BMP 파일인지 확인한다.
	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}
	// BITMAPINFOHEADER 위치로 간다.
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
	// 비트맵 이미지 데이터를 넣을 메모리 할당을 한다.
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
		fclose(fp);
		exit(0);
		return NULL;
	}
	// 비트맵 인포 헤더를 읽는다.
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// 비트맵의 크기 설정
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth *
		(*info)->bmiHeader.biBitCount + 7) / 8.0 *
		abs((*info)->bmiHeader.biHeight);
	// 비트맵의 크기만큼 메모리를 할당한다.
	if ((bits = (unsigned char *)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// 비트맵 데이터를 bit(GLubyte 타입)에 저장한다.
	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
		free(*info); free(bits);
		fclose(fp);
		return NULL;
	}
	fclose(fp);
	return bits;
}

// 사운드 파트
FMOD_SYSTEM     *g_System;
FMOD_SOUND		*g_Stage1, *g_scream, *g_portalin, *g_shoot, *g_gameover, *g_wow;
FMOD_CHANNEL	*g_pTempChannel, *g_Channel, *g_In, *g_screamChannel, *g_gameoverChannel, *g_wowChannel;

void SoundInit()
{
	// 시스템 오브젝트 생성과 초기화
	FMOD_System_Create(&g_System);
	FMOD_System_Init(g_System, 32, FMOD_INIT_NORMAL, NULL);

	// 효과 사운드
	FMOD_System_CreateSound(g_System, "sound/stage1.ogg", FMOD_DEFAULT, 0, &g_Stage1); //
	FMOD_System_CreateSound(g_System, "sound/scream.wav", FMOD_DEFAULT, 0, &g_scream); // 
	FMOD_System_CreateSound(g_System, "sound/portalin.wav", FMOD_DEFAULT, 0, &g_portalin); // 
	FMOD_System_CreateSound(g_System, "sound/shoot.wav", FMOD_DEFAULT, 0, &g_shoot); // 
	FMOD_System_CreateSound(g_System, "sound/gameover.mp3", FMOD_DEFAULT, 0, &g_gameover); // 
	FMOD_System_CreateSound(g_System, "sound/wow.wav", FMOD_DEFAULT, 0, &g_wow); // 

}

void SoundRelease()
{
	FMOD_Sound_Release(g_Stage1);
	FMOD_Sound_Release(g_scream);
	FMOD_Sound_Release(g_portalin);
	FMOD_Sound_Release(g_shoot);
	FMOD_Sound_Release(g_gameover);
	FMOD_Sound_Release(g_wow);
	FMOD_System_Close(g_System);
	FMOD_System_Release(g_System);
}

