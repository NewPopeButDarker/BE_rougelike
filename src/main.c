#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "glad/glad.h"
#include <gl/GL.h>

typedef HGLRC WINAPI wglCreateContextAttribsARB_t(HDC hdc, HGLRC hSharedContext, const int *attribList);
wglCreateContextAttribsARB_t *wglCreateContextAttribsARB;

#define WGL_CONTEXT_MAJOR_VERSION_ARB     0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB     0x2092
#define WGL_CONTEXT_PROFILE_MASK_ARB      0x9126

#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB  0x00000001


typedef BOOL WINAPI wglChoosePixelFormatARB_t(HDC hdc, const int *piAttribIList, const float *pfAttribFList, unsigned int nMaxFormats, int *piFormats, unsigned int *nNumFormats);
wglChoosePixelFormatARB_t *wglChoosePixelFormatARB;

#define WGL_DRAW_TO_WINDOW_ARB     0x2001
#define WGL_ACCELERATION_ARB       0x2003
#define WGL_SUPPORT_OPENGL_ARB     0x2010
#define WGL_DOUBLE_BUFFER_ARB      0x2011
#define WGL_PIXEL_TYPE_ARB         0x2013
#define WGL_COLOR_BITS_ARB         0x2014
#define WGL_DEPTH_BITS_ARB         0x2022
#define WGL_STENCIL_BITS_ARB       0x2023

#define WGL_FULL_ACCELERATION_ARB  0x2027
#define WGL_TYPE_RGBA_ARB          0x202B

LRESULT CALLBACK WndProc(HWND hwnd, unsigned int msg, WPARAM wParam, LPARAM lParam);
void* GetAnyGLFuncAddress(const char *name);
HWND CreateMainWindow(const char *title, int width, int height);
HGLRC InitOpenGLContext(HDC hdc);
void LoadOpenGLFunctions(void);
void FatalError(const char *msg);
void PollEvents(BOOL *bWindowShouldClose);
void Setup(void);
void Update(float delatTime);
void Draw(HDC hWindowDC);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
{
  HWND hMainWindow = CreateMainWindow("Main Window", 640, 480);
  HDC hMainWindowDC = GetDC(hMainWindow);
  HGLRC hMainWindowRC = InitOpenGLContext(hMainWindowDC);

  LoadOpenGLFunctions();

  ShowWindow(hMainWindow, nCmdShow);
  UpdateWindow(hMainWindow);

  Setup();

  clock_t start = clock();
  clock_t diff;

  BOOL bWindowShouldClose = FALSE;
  while(!bWindowShouldClose)
  {
    diff = clock() - start;
    float deltaTime = (float)diff / CLOCKS_PER_SEC;
    start = clock();

    PollEvents(&bWindowShouldClose);
    Update(deltaTime);
    Draw(hMainWindowDC);
  }

  return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, unsigned int msg, WPARAM wParam, LPARAM lParam)
{
  switch (msg)
  {
    case WM_CREATE:
      break;

    case WM_CLOSE:
      DestroyWindow(hwnd);
      break;

    case WM_DESTROY:
      PostQuitMessage(0);
      break;


    case WM_SIZING:
      {
        HDC hdc = GetDC(hwnd);
        Draw(hdc);
        RECT rc;
        GetClientRect(hwnd, &rc);
        glViewport(0, 0, rc.right - rc.left, rc.bottom - rc.top);
      }
      break;

    default:
      return DefWindowProc(hwnd, msg, wParam, lParam);
  }
  return 0;
}


void* GetAnyGLFuncAddress(const char *name)
{
  void *p = wglGetProcAddress(name);

  if((p == NULL) || (p == (void*)0x1) || (p == (void*)0x2) || (p == (void*)0x3) || (p == (void*)-1))
  {
    HMODULE hModule = LoadLibrary("opengl32.dll");
    p = GetProcAddress(hModule, name);
  }

  return p;
}


HWND CreateMainWindow(const char *title, int width, int height)
{
  WNDCLASSEX wc;

  wc.cbSize        = sizeof(wc);
  wc.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  wc.lpfnWndProc   = WndProc;
  wc.cbClsExtra    = 0;
  wc.cbWndExtra    = 0;
  wc.hInstance     = GetModuleHandle(NULL);
  wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
  wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = NULL;
  wc.lpszMenuName  = NULL;
  wc.lpszClassName = "MaindWndClass";
  wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

  if(!RegisterClassEx(&wc))
  {
    FatalError("Failed to initialize main window class!");
  }

  RECT rc;
  SetRect(&rc, 0, 0, width, height);
  AdjustWindowRectEx(&rc, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_APPWINDOW | WS_EX_TOPMOST);
  int adjustedWidth  = rc.right  - rc.left;
  int adjustedHeight = rc.bottom - rc.top;

  HWND hwnd = CreateWindowEx(WS_EX_APPWINDOW | WS_EX_TOPMOST, wc.lpszClassName, title, WS_OVERLAPPEDWINDOW,
                             CW_USEDEFAULT, CW_USEDEFAULT, adjustedWidth, adjustedHeight,
                             NULL, NULL, GetModuleHandle(NULL), NULL);

  if(hwnd == NULL)
  {
    FatalError("Failed to create main window!");
  }

  return hwnd;
}

void _InitOpenGLExtensionsForContext(void)
{
  WNDCLASS wc = {0};
  wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  wc.lpfnWndProc = DefWindowProc;
  wc.hInstance = GetModuleHandle(NULL);
  wc.lpszClassName = "DummyWndClass";

  if(!RegisterClass(&wc))
  {
    FatalError("Failed to initialize dummy window class!");
  }

  HWND hDummyWindow = CreateWindow(wc.lpszClassName, NULL, 0,
                                   0, 0, 0, 0,
                                   NULL, NULL, wc.hInstance, NULL);

  if(hDummyWindow == NULL)
  {
    FatalError("Failed to create dummy window!");
  }

  HDC hDummyDC = GetDC(hDummyWindow);

  PIXELFORMATDESCRIPTOR pfd;
 
  pfd.nSize        = sizeof(pfd);
  pfd.nVersion     = 1;
  pfd.iPixelType   = PFD_TYPE_RGBA;
  pfd.dwFlags      = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
  pfd.cColorBits   = 32;
  pfd.cAlphaBits   = 8;
  pfd.iLayerType   = PFD_MAIN_PLANE;
  pfd.cDepthBits   = 24;
  pfd.cStencilBits = 8;

  int pixelFormat = ChoosePixelFormat(hDummyDC, &pfd);
  if(!pixelFormat)
  {
    FatalError("Failed to initialize dummy pixel format!");
  }

  if(!SetPixelFormat(hDummyDC, pixelFormat, &pfd))
  {
    FatalError("Failed to set dummy pixel format!");
  }

  HGLRC hDummyRC = wglCreateContext(hDummyDC);
  if(!hDummyRC)
  {
    FatalError("Failed to create dummy rendering context!");
  }

  if(!wglMakeCurrent(hDummyDC, hDummyRC))
  {
    FatalError("Failed setting current dummy RC!");
  }

  wglCreateContextAttribsARB = GetAnyGLFuncAddress("wglCreateContextAttribsARB");
  wglChoosePixelFormatARB = GetAnyGLFuncAddress("wglChoosePixelFormatARB");

  if(!wglCreateContextAttribsARB || ! wglChoosePixelFormatARB)
  {
    FatalError("Failed loadin context setting functions!");
  }

  wglMakeCurrent(hDummyDC, 0);
  wglDeleteContext(hDummyRC);
  ReleaseDC(hDummyWindow, hDummyDC);
  DestroyWindow(hDummyWindow);
}

HGLRC InitOpenGLContext(HDC hdc)
{
  _InitOpenGLExtensionsForContext();


  int pixelFormatAttribs[] =
    {
      WGL_DRAW_TO_WINDOW_ARB, TRUE,
      WGL_SUPPORT_OPENGL_ARB, TRUE,
      WGL_DOUBLE_BUFFER_ARB,  TRUE,
      WGL_ACCELERATION_ARB,   WGL_FULL_ACCELERATION_ARB,
      WGL_PIXEL_TYPE_ARB,     WGL_TYPE_RGBA_ARB,
      WGL_COLOR_BITS_ARB,     32,
      WGL_DEPTH_BITS_ARB,     24,
      WGL_STENCIL_BITS_ARB,   8,
      0
    };

  int iPixelFormat;
  unsigned int nNumFormats;
  wglChoosePixelFormatARB(hdc, pixelFormatAttribs, 0, 1, &iPixelFormat, &nNumFormats);

  if(!nNumFormats)
  {
    FatalError("Failed to choose pixel format!");
  }

  PIXELFORMATDESCRIPTOR pfd;
  DescribePixelFormat(hdc, iPixelFormat, sizeof(pfd), &pfd);
  if(!SetPixelFormat(hdc, iPixelFormat, &pfd))
  {
    FatalError("Failed to set pixel format!");
  }

  int contextAttribs[] = 
    {
      WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
      WGL_CONTEXT_MINOR_VERSION_ARB, 3,
      WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
      0
    };

  HGLRC hglrc = wglCreateContextAttribsARB(hdc, 0, contextAttribs);
  if(!hglrc)
  {
    FatalError("Failed to create context attributes!");
  }

  if(!wglMakeCurrent(hdc, hglrc))
  {
    FatalError("Failed to set currect rendering context!");
  }

  return hglrc;
}

void LoadOpenGLFunctions(void)
{
  if(!gladLoadGLLoader(GetAnyGLFuncAddress))
  {
    FatalError("Failed to initialize GLAD!");
  }
}

void FatalError(const char *msg)
{
  MessageBox(NULL, msg, "Error!", MB_OK | MB_ICONERROR);
  exit(EXIT_FAILURE);
}

void PollEvents(BOOL *bWindowShouldClose)
{
  static MSG msg;
  (*bWindowShouldClose) = FALSE;
  while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
  {
    if(msg.message == WM_QUIT)
    {
      (*bWindowShouldClose) = TRUE;
    }
    else
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }
}

void Setup(void)
{

}

void Update(float deltaTime)
{

}

void Draw(HDC hWindowDC)
{
  glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  SwapBuffers(hWindowDC);
}
