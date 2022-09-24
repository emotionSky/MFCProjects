// MFCBase.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "MFCBase.h"

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,        //应用程序实例句柄
                     _In_opt_ HINSTANCE hPrevInstance, //上一个应用程序实例
                     _In_ LPWSTR    lpCmdLine,         //命令行参数
                     _In_ int       nCmdShow)          //窗口显示的样式
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MFCBASE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MFCBASE));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



/**
 * @brief 注册窗口
 * @param[in] hInstance 应用程序实例句柄
 */
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    //1.设计窗口
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;                          //显示风格
    wcex.lpfnWndProc    = WndProc;                                          //回调函数，处理窗口过程
    wcex.cbClsExtra     = 0;                                                //类的额外的内存
    wcex.cbWndExtra     = 0;                                                //窗口额外的内存
    wcex.hInstance      = hInstance;                                        //应用程序实例句柄，传入形参即可
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MFCBASE));//设置图标，第一个参数为空时，表示使用系统提供的图标
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);                   //设置光标，第一个参数为空时，表示使用系统提供的光标
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);                         //设置背景  (HBRUSH)GetStockObject(WHITE_BRUSH);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MFCBASE);                    //菜单名称
    wcex.lpszClassName  = szWindowClass;                                    //指定窗口类名称
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    //2.注册窗口
    return RegisterClassExW(&wcex);
}

/*
 * @brief 初始化函数
 * @details 保存实例句柄，创建、显示和更新主窗口
 * @param[in] hInstance 应用程序实例句柄
 * @param[in] nCmdShow  窗口显示的样式
 */
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   //3.创建窗口
   HWND hWnd = CreateWindowW(
       szWindowClass,      //类名称
       szTitle,            //窗口标题
       WS_OVERLAPPEDWINDOW,//窗口的样式，一般指定为多种窗口类型的组合类型
       CW_USEDEFAULT,      //窗口左上角的x坐标，指定为CW_USEDEFAULT时，窗口选择左上角坐标并忽略y参数
       0,                  //窗口坐上的y坐标
       CW_USEDEFAULT,      //窗口的宽度，指定为CW_USEDEFAULT时，系统为窗口选择默认的宽高，并忽略nHeight参数
       0,                  //窗口的高度
       nullptr,            //窗口的父窗口句柄
       nullptr,            //窗口菜单的句柄
       hInstance,          //窗口所属应用程序实例的句柄
       nullptr);           //作为WM_CREATE消息的附加参数lParam传入的数据指针。通常设置为NULL。

   if (!hWnd)
   {
      return FALSE;
   }

   //4.显示和更新窗口
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

/*
 * @brief 处理主窗口的消息
 * @param[in] hWnd     窗口句柄
 * @param[in] message  捕捉到的消息
 * @param[in] wParam   
 * @param[in] lParam
 */
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND: //处理应用程序菜单
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT: //绘制主窗口
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY: //发送退出消息并返回
        PostQuitMessage(0);
        break;
    case WM_LBUTTONDOWN: //鼠标左键按下
    {
        int xPos = LOWORD(lParam);
        int yPos = HIWORD(lParam);
        WCHAR buf[200];
        wsprintf(buf, TEXT("x=%d,y=%d"), xPos, yPos);
        MessageBox(hWnd, buf, TEXT("鼠标左键按下"), MB_OK);
        break;
    }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
