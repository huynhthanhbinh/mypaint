// 1653006
// Huỳnh Thanh Bình
// 16CLC1

// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#include "targetver.h"
#include "resource.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: reference additional headers your program requires here
#include <CommCtrl.h>
#include <commdlg.h>
#pragma comment(lib,"ComCtl32.Lib") // searches first in the current working directory 
#pragma comment(lib,"ComDlg32.Lib") // and then in the path specified in the LIB environment variable.