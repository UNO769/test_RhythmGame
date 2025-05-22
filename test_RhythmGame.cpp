// test_RhythmGame.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "framework.h"
#include "test_RhythmGame.h"

#define MAX_LOADSTRING 100

// グローバル変数:
HINSTANCE hInst;                                // 現在のインターフェイス
WCHAR szTitle[MAX_LOADSTRING];                  // タイトル バーのテキスト
WCHAR szWindowClass[MAX_LOADSTRING];            // メイン ウィンドウ クラス名

bool drawCircleA = false;
bool drawCircleB = false;
bool drawCircleC = false;
bool drawCircleD = false;


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


        RECT rect;
        GetClientRect(hWnd, &rect);
        int width = rect.right - rect.left;
        int height = rect.bottom - rect.top;

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


        if (drawCircleA) // フラグが true の場合のみ円を描画
        {
            RECT rect;
            GetClientRect(hWnd, &rect);
            int width = rect.right - rect.left;
            int height = rect.bottom - rect.top;

            int radius = 50;
            int centerX = 3 * width / 9;
            int centerY = 7 * height / 8;

            HBRUSH redBrush = CreateSolidBrush(RGB(255, 0, 0));
            HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, redBrush);

            Ellipse(hdc, centerX - radius, centerY - radius, centerX + radius, centerY + radius);

            SelectObject(hdc, oldBrush);
            DeleteObject(redBrush);
        }
        if (drawCircleB) // フラグが true の場合のみ円を描画
        {
            RECT rect;
            GetClientRect(hWnd, &rect);
            int width = rect.right - rect.left;
            int height = rect.bottom - rect.top;

            int radius = 50;
            int centerX = 4 * width / 9;
            int centerY = 7 * height / 8;

            HBRUSH greenBrush = CreateSolidBrush(RGB(0, 255, 0));
            HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, greenBrush);

            Ellipse(hdc, centerX - radius, centerY - radius, centerX + radius, centerY + radius);

            SelectObject(hdc, oldBrush);
            DeleteObject(greenBrush);
        }
        if (drawCircleC) // フラグが true の場合のみ円を描画
        {
            RECT rect;
            GetClientRect(hWnd, &rect);
            int width = rect.right - rect.left;
            int height = rect.bottom - rect.top;

            int radius = 50;
            int centerX = 5 * width / 9;
            int centerY = 7 * height / 8;

            HBRUSH blueBrush = CreateSolidBrush(RGB(0, 0, 255));
            HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, blueBrush);

            Ellipse(hdc, centerX - radius, centerY - radius, centerX + radius, centerY + radius);

            SelectObject(hdc, oldBrush);
            DeleteObject(blueBrush);
        }
        if (drawCircleD) // フラグが true の場合のみ円を描画
        {
            RECT rect;
            GetClientRect(hWnd, &rect);
            int width = rect.right - rect.left;
            int height = rect.bottom - rect.top;

            int radius = 50;
            int centerX = 6 * width / 9;
            int centerY = 7 * height / 8;

            HBRUSH yellowBrush = CreateSolidBrush(RGB(255, 255, 0));
            HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, yellowBrush);

            Ellipse(hdc, centerX - radius, centerY - radius, centerX + radius, centerY + radius);

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
            drawCircleA = true; // Dキーを押したらA描画フラグをON
            InvalidateRect(hWnd, NULL, TRUE); // 再描画をリクエスト
            break;
        case 'F':
            drawCircleB = true; // Fキーを押したらB描画フラグをON
            InvalidateRect(hWnd, NULL, TRUE); // 再描画をリクエスト
            break;
        case 'J':
            drawCircleC = true; // Jキーを押したらC描画フラグをON
            InvalidateRect(hWnd, NULL, TRUE); // 再描画をリクエスト
            break;
        case 'K':
            drawCircleD = true; // Kキーを押したらD描画フラグをON
            InvalidateRect(hWnd, NULL, TRUE); // 再描画をリクエスト
            break;

        }
        break;



    case WM_KEYUP:
        switch (wParam)
        {
		case 'D':
            drawCircleA = false; // Dキーを離したら円を消す
            InvalidateRect(hWnd, NULL, TRUE); // 再描画
			break;
        case 'F':
            drawCircleB = false; // Fキーを離したら円を消す
            InvalidateRect(hWnd, NULL, TRUE); // 再描画
            break;
        case 'J':
            drawCircleC = false; // Jキーを離したら円を消す
            InvalidateRect(hWnd, NULL, TRUE); // 再描画
            break;
        case 'K':
            drawCircleD = false; // Kキーを離したら円を消す
            InvalidateRect(hWnd, NULL, TRUE); // 再描画
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
