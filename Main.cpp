#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")


LRESULT CALLBACK GLWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}




INT WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd
)
{
	//注册窗口
	WNDCLASSEX wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = NULL;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = NULL;
	wndClass.hIconSm = NULL;
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = &GLWindowProc;
	wndClass.lpszClassName = L"GLWindow";
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_VREDRAW | CS_HREDRAW;

	ATOM atom = RegisterClassEx(&wndClass);
	if (!atom)
	{
		return 0;
	}


	//创建窗口
	HWND hwnd = CreateWindowEx(NULL, L"GLWindow", L"OpenGL Window", WS_OVERLAPPEDWINDOW, 100, 100, 800, 600, NULL, NULL, hInstance, NULL);



	//创建OPGL上下文
	HDC dc = GetDC(hwnd);
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.nVersion = 1;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 8;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;

	int pixelFormat = ChoosePixelFormat(dc, &pfd);
	SetPixelFormat(dc, pixelFormat, &pfd);

	HGLRC rc = wglCreateContext(dc);
	wglMakeCurrent(dc, rc);//Opengl设置完成


	//opengl 初始化
	glClearColor(0.1, 0.4, 0.6, 1.0); //设置背景的清除颜色

	//设置投影矩阵
	glMatrixMode(GL_PROJECTION);//告诉显卡我们现在要操作我们的投影矩阵
	gluPerspective(50.0f, 800.0f / 600.f, 0.1f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);//设置模型矩阵
	glLoadIdentity();//设置为单位矩阵






	//显示窗口
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	MSG msg;
	while (true)
	{
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}


		//绘制场景
		glClear(GL_COLOR_BUFFER_BIT);


		glColor4ub(0, 0, 255, 255);//设置当前颜色

		//设置线宽度
		glLineWidth(4.0f);

		//开始绘制

		glBegin(GL_TRIANGLES); //GL_LINE_LOOP 首尾相接的绘制线段

		glColor4ub(0, 0, 255, 255);
		glVertex3f(0.0f, 0.0f, -10.0f);

		glColor4ub(255, 0, 0, 0);//设置颜色
		glVertex3f(-5.0f, 0.0f, -10.0f);

		glColor4ub(0, 255, 0, 0);//线段两点之间的颜色会被插值
		glVertex3f(-5.0f, -4.0f, -10.0f);

		glEnd();//绘制结束




		//展示场景
		SwapBuffers(dc);


	}

	return 0;
}