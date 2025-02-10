#pragma once

#include "framework.h"
#include "resource.h"

#include <vector>
#include <list>
#include <map>
#include <string>
#include <typeinfo>
#include <assert.h>
using std::vector;
using std::list;
using std::map;
using std::wstring;

// File Save/Load Dialog
#include <commdlg.h>

// TransparentBlt
#pragma comment(lib, "Msimg32.lib")

#include "Defines.h"
#include "Enums.h"
#include "Structs.h"
#include "Utils.h"
#include "CEngine.h"

// FileSystem
#include <filesystem>
namespace fs = std::filesystem;

// Memory Leak Check
//#define _CRTDEBG_MAP_ALLOC
//#include <cstdlib>
//#include <crtdbg.h>

// Png Loading
#include <objidl.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;

// Sound
#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")

// PEN, BRUSH
#include "CSelectGDI.h"