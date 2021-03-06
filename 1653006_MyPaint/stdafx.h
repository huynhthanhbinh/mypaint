// 1653006
// Huỳnh Thanh Bình
// 16CLC1

// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_DEPRECATE_MEMORY  // for memset, zeromemory !

#include "targetver.h"
#include "resource.h"

#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <windowsx.h>		// Simplify Windows Message, Dialog... Function !!! 
							// This header is used by Windows Controls. 

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// TODO: reference additional headers your program requires here
using namespace std;

// My Definition

//work_id
#define INSERT              0
#define DELETE              1
#define CHANGE              2
//windowMode
#define CASCADE             1
#define VERTICAL            2
#define HORIZONTAL          3
//sMode_convert function
#define MOVE                0
#define RESIZE_1            1
#define RESIZE_2            2
#define RESIZE_3            3
#define RESIZE_4            4
//myMODE
#define LINE                1
#define ELLIPSE             2
#define RECTANGLE           3
#define SELECT              4
#define INSERTTEXT          5
#define MAX_LOADSTRING		256
//myMENU
#define menuPos_File        0
#define menuPos_Edit        1
#define menuPos_Draw        2
#define menuPos_Toolbar     3
#define menuPos_Window      4
#define menuPos_Help        5

#include <CommCtrl.h>
#include <commdlg.h>
#pragma comment(lib,"ComCtl32.Lib") // searches first in the current working directory 
#pragma comment(lib,"ComDlg32.Lib") // and then in the path specified in the LIB environment variable.
