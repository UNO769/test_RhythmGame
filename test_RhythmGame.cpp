// test_RhythmGame.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "framework.h"
#include "test_RhythmGame.h"

#define MAX_LOADSTRING 100

// グローバル変数:
HINSTANCE hInst;                                // 現在のインターフェイス
WCHAR szTitle[MAX_LOADSTRING];                  // タイトル バーのテキスト
WCHAR szWindowClass[MAX_LOADSTRING];            // メイン ウィンドウ クラス名

bool drawBoxA = false;
bool drawBoxB = false;
bool drawBoxC = false;
bool drawBoxD = false;


// このコード モジュールに含まれる関数の宣言を転送します:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: ここにコードを挿入してください。

    // グローバル文字列を初期化する
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TESTRHYTHMGAME, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // アプリケーション初期化の実行:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TESTRHYTHMGAME));

    MSG msg;

    // メイン メッセージ ループ:
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



//
//  関数: MyRegisterClass()
//
//  目的: ウィンドウ クラスを登録します。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TESTRHYTHMGAME));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TESTRHYTHMGAME);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   関数: InitInstance(HINSTANCE, int)
//
//   目的: インスタンス ハンドルを保存して、メイン ウィンドウを作成します
//
//   コメント:
//
//        この関数で、グローバル変数でインスタンス ハンドルを保存し、
//        メイン プログラム ウィンドウを作成および表示します。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // グローバル変数にインスタンス ハンドルを格納する

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  関数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: メイン ウィンドウのメッセージを処理します。
//
//  WM_COMMAND  - アプリケーション メニューの処理
//  WM_PAINT    - メイン ウィンドウを描画する
//  WM_DESTROY  - 中止メッセージを表示して戻る
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    RECT rect;
    GetClientRect(hWnd, &rect);
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 選択されたメニューの解析:
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

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        HPEN blackPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0)); // 太さ2pxの黒色の線
        HPEN oldPen = (HPEN)SelectObject(hdc, blackPen);

        // 画面を3分割するためのX座標
        int x1 = 5 * width / 18;
        int x2 = 7 * width / 18;
        int x3 = 9 * width / 18;
        int x4 = 11 * width / 18;
        int x5 = 13 * width / 18;

        MoveToEx(hdc, x1, 0, NULL);
        LineTo(hdc, x1, height);

        MoveToEx(hdc, x2, 0, NULL);
        LineTo(hdc, x2, height);

        MoveToEx(hdc, x3, 0, NULL);
        LineTo(hdc, x3, height);

        MoveToEx(hdc, x4, 0, NULL);
        LineTo(hdc, x4, height);

        MoveToEx(hdc, x5, 0, NULL);
        LineTo(hdc, x5, height);

        SelectObject(hdc, oldPen);
        DeleteObject(blackPen);

        if (drawBoxA)
        {
            int left = 5 * width / 18;
            int top = 18 * height / 20;
            int right = 7 * width / 18;
            int bottom = 19 * height / 20;

            HBRUSH redBrush = CreateSolidBrush(RGB(255, 0, 0)); 
            HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, redBrush);

            Rectangle(hdc, left, top, right, bottom); // 長方形を描画

            SelectObject(hdc, oldBrush);
            DeleteObject(redBrush);
        }
        if (drawBoxB) 
        {
            int left = 7 * width / 18;
            int top = 18 * height / 20;
            int right = 9 * width / 18;
            int bottom = 19 * height / 20;

            HBRUSH greenBrush = CreateSolidBrush(RGB(0, 255, 0));
            HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, greenBrush);

            Rectangle(hdc, left, top, right, bottom); // 長方形を描画

            SelectObject(hdc, oldBrush);
            DeleteObject(greenBrush);
        }
        if (drawBoxC)
        {

            int left = 9 * width / 18;
            int top = 18 * height / 20;
            int right = 11 * width / 18;
            int bottom = 19 * height / 20;

            HBRUSH blueBrush = CreateSolidBrush(RGB(0, 0, 255));
            HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, blueBrush);

            Rectangle(hdc, left, top, right, bottom); // 長方形を描画

            SelectObject(hdc, oldBrush);
            DeleteObject(blueBrush);
        }
        if (drawBoxD) 
        {

            int left = 11 * width / 18;
            int top = 18 * height / 20;
            int right = 13 * width / 18;
            int bottom = 19 * height / 20;

            HBRUSH yellowBrush = CreateSolidBrush(RGB(255, 255, 0));
            HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, yellowBrush);

            Rectangle(hdc, left, top, right, bottom); // 長方形を描画

            SelectObject(hdc, oldBrush);
            DeleteObject(yellowBrush);
        }

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_KEYDOWN:

        switch (wParam)
        {
        case 'D':
            drawBoxA = true; // Dキーを押したらA描画フラグをON
            RECT rectA;

            rectA.left = 5 * width / 18;
            rectA.top = 18 * height / 20;
            rectA.right = 7 * width / 18;
            rectA.bottom = 19 * height / 20;

            InvalidateRect(hWnd, &rectA, TRUE); // 長方形の範囲のみ再描画

            break;
        case 'F':
            drawBoxB = true; // Fキーを押したらB描画フラグをON
            RECT rectB;

            rectB.left = 7 * width / 18;
            rectB.top = 18 * height / 20;
            rectB.right = 9 * width / 18;
            rectB.bottom = 19 * height / 20;

            InvalidateRect(hWnd, &rectB, TRUE); // 長方形の範囲のみ再描画
            break;
        case 'J':
            drawBoxC = true; // Jキーを押したらC描画フラグをON
			RECT rectC;

            rectC.left = 9 * width / 18;
            rectC.top = 18 * height / 20;
            rectC.right = 11 * width / 18;
            rectC.bottom = 19 * height / 20;

            InvalidateRect(hWnd, &rectC, TRUE); // 長方形の範囲のみ再描画
            break;
        case 'K':
            drawBoxD = true; // Kキーを押したらD描画フラグをON
			RECT rectD;

            rectD.left = 11 * width / 18;
            rectD.top = 18 * height / 20;
            rectD.right = 13 * width / 18;
            rectD.bottom = 19 * height / 20;

            InvalidateRect(hWnd, &rectD, TRUE); // 長方形の範囲のみ再描画
            break;

        }
        break;



    case WM_KEYUP:


        switch (wParam)
        {
		case 'D':
            drawBoxA = false; // Dキーを離したら四角を消す
			RECT rectA;

            rectA.left = 5 * width / 18;
            rectA.top = 18 * height / 20;
            rectA.right = 7 * width / 18;
            rectA.bottom = 19 * height / 20;

            InvalidateRect(hWnd, &rectA, TRUE); // 長方形の範囲のみ再描画
			break;
        case 'F':
            drawBoxB = false; // Fキーを離したら四角を消す
            RECT rectB;

            rectB.left = 7 * width / 18;
            rectB.top = 18 * height / 20;
            rectB.right = 9 * width / 18;
            rectB.bottom = 19 * height / 20;

            InvalidateRect(hWnd, &rectB, TRUE); // 長方形の範囲のみ再描画
            break;
        case 'J':
            drawBoxC = false; // Jキーを離したら四角を消す
            RECT rectC;

            rectC.left = 9 * width / 18;
            rectC.top = 18 * height / 20;
            rectC.right = 11 * width / 18;
            rectC.bottom = 19 * height / 20;

            InvalidateRect(hWnd, &rectC, TRUE); // 長方形の範囲のみ再描画
            break;
        case 'K':
            drawBoxD = false; // Kキーを離したら四角を消す
            RECT rectD;

            rectD.left = 11 * width / 18;
            rectD.top = 18 * height / 20;
            rectD.right = 13 * width / 18;
            rectD.bottom = 19 * height / 20;

            InvalidateRect(hWnd, &rectD, TRUE); // 長方形の範囲のみ再描画
            break;

        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// バージョン情報ボックスのメッセージ ハンドラーです。
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
