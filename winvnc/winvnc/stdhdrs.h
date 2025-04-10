/////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2002-2024 UltraVNC Team Members. All Rights Reserved.
//  Copyright (C) 2002 RealVNC Ltd. All Rights Reserved.
//  Copyright (C) 1999 AT&T Laboratories Cambridge. All Rights Reserved.
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307,
//  USA.
//
//  If the source code for the program is not available from the place from
//  which you received this file, check
//  https://uvnc.com/
//
////////////////////////////////////////////////////////////////////////////


//need to be added for VS 2005
#define _Gii
#ifdef _Gii
#ifndef WINVER                  // Specifies that the minimum required platform is Windows 7.
#define WINVER 0x0602           // Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINNT            // Specifies that the minimum required platform is Windows 7.
#define _WIN32_WINNT 0x0602     // Change this to the appropriate value to target other versions of Windows.
#endif     

//#ifndef _WIN32_WINDOWS          // Specifies that the minimum required platform is Windows 98.
//#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
//#endif

#ifndef _WIN32_IE                       // Specifies that the minimum required platform is Internet Explorer 7.0.
#define _WIN32_IE 0x0600        // Change this to the appropriate value to target other versions of IE.
#endif
#endif

/*#ifdef _USE_DESKTOPDUPLICATION
#define _WIN32_WINNT 0x0602
#ifndef WINVER
#define WINVER 0x0602
#endif
#else
#define _WIN32_WINDOWS 0x0510
#ifndef WINVER
#define WINVER 0x0500
#endif
#endif*/

#define WIN32_LEAN_AND_MEAN
#ifndef STRICT
#define STRICT
#endif

//compile special case, rfb port is used for java and rfb
#include <ws2tcpip.h>
#include <winsock2.h>
#include <windows.h>
#include <shellapi.h>
//#include <winsock2.h>

#include <malloc.h>
#include <stdio.h>
#include <process.h>
#include <crtdbg.h>
#include "HelperFunctions.h"

//#include "dpi.h"

// LOGGING SUPPORT
void *memcpy_amd(void *dest, const void *src, size_t n);
bool CheckVideoDriver(bool);
#define MAXPATH 256

#include "vnclog.h"
extern VNCLog vnclog;

// No logging at all
#define LL_NONE		0
// Log server startup/shutdown
#define LL_STATE	0
// Log connect/disconnect
#define LL_CLIENTS	1
// Show on Logscreen
#define LL_LOGSCREEN -1
// Log connection errors (wrong pixfmt, etc)
#define LL_CONNERR	0
// Log socket errors
#define LL_SOCKERR	4
// Log internal errors
#define LL_INTERR	0

// Log internal warnings
#define LL_INTWARN	8
// Log internal info
#define LL_INTINFO	9
// Log socket errors
#define LL_SOCKINFO	10
// Log everything, including internal table setup, etc.
#define LL_ALL		10

// Macros for sticking in the current file name
#define VNCLOG(s)	(__FUNCTION__ " : " s)
//#if MSC_VER > 12
#ifndef _X64
#pragma comment(linker,"/manifestdependency:\"type='Win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='X86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='Win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
//#endif
//#define memcpy memcpy_amd
//remove comment to compiler for >=athlon  or >=PIII

extern void WriteLog(char* sender, char *format, ...);
#ifdef _DEBUG
#define OutputDevMessage(...) WriteLog(__FUNCTION__, __VA_ARGS__);
#else
#define OutputDevMessage(...)
#endif

#ifdef HIGH_PRECISION
#define GetTimeFunction timeGetTime
#pragma comment(lib, "winmm.lib")
#else
#define GetTimeFunction GetTickCount
#endif
