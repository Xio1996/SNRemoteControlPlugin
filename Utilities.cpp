//========================================================================
//
// TITLE:		UTILITIES.CPP
//
// FACILITY:	Copied from StarryNight SDK Plug-In DLL ASCOM focuser Control
//
// ABSTRACT:	
//
// USING:		
//
// ENVIRONMENT:	Microsoft Windows Windows 95/98/NT/2000/XP
//				Developed under Microsoft Visual C++ Version 6.0
//
// AUTHOR:		Robert B. Denny
//
// Edit Log:
//
// When			Who		What
//----------	---		--------------------------------------------------
// 26-Jul-00	rbd		Initial edit
// 21-Aug-05	mk		Additional Modifications to drvFail
//========================================================================
#include "RemoteControl.h"
#pragma hdrstop


// ---------
// pToCStr() - Convert PString to CString
// ---------
//
void pToCStr(pStr255 p, char *c)
{
	DWORD l = (DWORD)p[0];

	if(l > 0)
		CopyMemory(c, &p[1], l);
	c[l] = '\0';
}

char* pToCStr(pStr255 p)
{
	DWORD l = (DWORD)p[0];
	
	char* c = new char[l];

	if (l > 0)
		CopyMemory(c, &p[1], l);
	c[l] = '\0';

	return c;
}

// ---------
// cToPstr() - Convert CString to PString
// ---------
//
void cToPstr(char *c, pStr255 p)
{
	int l = lstrlen(c);

	p[0] = (unsigned char)(l & 0xFF);
	if(p[0] > 0)
		CopyMemory(&p[1], c, l);
}

// ---------
// pStrCmp() - Compare PStrings
// ---------
//
bool pStrCmp(pStr255 s1, pStr255 s2)
{
	if(s1[0] != s2[0])
		return(false);
	for (short i = 1; i <= s1[0]; i++) {
		if(s1[i] != s2[i])
			return(false);
	}
	return(true);
}

