#define WIN32_LEAN_AND_MEAN
#define NOSERVICE
#define NOMCX
#define NOIME
#define NOSOUND
#define NOKANJI
#define NOIMAGE
#define NOTAPE

//#include <afxdisp.h>        // MFC Automation classes

#include <objbase.h>

#include <ole2ver.h>
#include <initguid.h>
#include <stdio.h>
#include <stdlib.h>
#include <climits>

#define TARGET_OS_MAC 0
#define TARGET_OS_WIN32 1

#include "StarryNightPlugins.h"

#define PI 3.14159265359
#define DEG_PER_RAD 57.2957795131
#define HR_PER_RAD (DEG_PER_RAD / 15.0)
#define RAD_PER_DEG 0.0174532925199
#define RAD_PER_HR (RAD_PER_DEG * 15.0)
#define M_PER_AU 1.4959787066E11

#define EXCEP_ABORT 0xE100000F
#define ABORT RaiseException(EXCEP_ABORT, 0, NULL, NULL)

// RemoteControl.cpp
extern HWND _hWndMain;

// Utilities.cpp
extern void pToCStr(pStr255 p, char *c);
extern char* pToCStr(pStr255 p);
extern void cToPstr(char *c, pStr255 p);
extern bool pStrCmp(pStr255 s1, pStr255 s2);


