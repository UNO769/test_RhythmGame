// test_RhythmGame.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "framework.h"
#include "test_RhythmGame.h"
#include <fstream>
#include <iostream>
#include <string>
#include "note.h"
#include <vector>
#include <sstream>

#define MAX_LOADSTRING 100

// グローバル変数:
HINSTANCE hInst;                                // 現在のインターフェイス
WCHAR szTitle[MAX_LOADSTRING];                  // タイトル バーのテキスト
WCHAR szWindowClass[MAX_LOADSTRING];            // メイン ウィンドウ クラス名

bool drawBoxA = false;
bool drawBoxB = false;
bool drawBoxC = false;
bool drawBoxD = false;




// グローバルなノーツリスト
std::vector<Note> notes;




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

    case WM_CREATE:
    {
        SetTimer(hWnd, 1, 16, NULL); // 16msごとに更新（約60FPS）
        // 初回のノーツデータ読み込み
        std::ifstream file("notes_data.txt");

        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) { // 1行ずつ読み込む
                std::istringstream iss(line);
                int x, y, speed;
                char key;

                if (iss >> x >> y >> speed >> key) {
                    // 入力xをレーン位置(1〜4)と仮定してピクセル位置に変換
                    int laneX = 0;
                    if (x == 1) laneX = 5 * width / 18;
                    else if (x == 2) laneX = 7 * width / 18;
                    else if (x == 3) laneX = 9 * width / 18;
                    else if (x == 4) laneX = 11 * width / 18;
                    y = y * -1;

                    notes.push_back(Note{ laneX, y, speed, key });
                }
            }
            file.close();
        }
        else {
        }
    }
    break;


    case WM_TIMER:
    {
        std::cout << "WM_TIMER 発生" << std::endl; // 確認用

        for (auto& note : notes) {
            note.y += note.speed; // ノーツを下へ移動
            std::cout << "ノーツ位置: " << note.y << std::endl; // 確認用
        }

        RECT rectN;

        rectN.left = 5 * width / 18;
        rectN.top = 0;
        rectN.right = 13 * width / 18;
        rectN.bottom = height;

        InvalidateRect(hWnd, &rectN, FALSE); 
    }

    break;

    case WM_ERASEBKGND:
        return 1; // 背景クリアしない → flicker防止

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

        // --- ダブルバッファ用 HDC と Bitmap を作成 ---
        RECT clientRect;
        GetClientRect(hWnd, &clientRect);
        int width = clientRect.right - clientRect.left;
        int height = clientRect.bottom - clientRect.top;

        HDC memDC = CreateCompatibleDC(hdc);
        HBITMAP backBuffer = CreateCompatibleBitmap(hdc, width, height);
        HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, backBuffer);

        // 背景塗りつぶし
        HBRUSH bgBrush = CreateSolidBrush(RGB(255, 255, 255));
        FillRect(memDC, &clientRect, bgBrush);
        DeleteObject(bgBrush);

        // --- 線を描画 ---
        HPEN blackPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
        HPEN oldPen = (HPEN)SelectObject(memDC, blackPen);

        int x1 = 5 * width / 18;
        int x2 = 7 * width / 18;
        int x3 = 9 * width / 18;
        int x4 = 11 * width / 18;
        int x5 = 13 * width / 18;

        MoveToEx(memDC, x1, 0, NULL); LineTo(memDC, x1, height);
        MoveToEx(memDC, x2, 0, NULL); LineTo(memDC, x2, height);
        MoveToEx(memDC, x3, 0, NULL); LineTo(memDC, x3, height);
        MoveToEx(memDC, x4, 0, NULL); LineTo(memDC, x4, height);
        MoveToEx(memDC, x5, 0, NULL); LineTo(memDC, x5, height);

        SelectObject(memDC, oldPen);
        DeleteObject(blackPen);

        // --- ノーツを描画 ---
        for (const auto& note : notes) {
            RECT noteRect = { note.x, note.y, note.x + width / 9, note.y + height / 20 };
            HBRUSH brush = CreateSolidBrush(RGB(50, 50, 50));
            HBRUSH oldBrush = (HBRUSH)SelectObject(memDC, brush);

            Rectangle(memDC, noteRect.left, noteRect.top, noteRect.right, noteRect.bottom);

            SelectObject(memDC, oldBrush);
            DeleteObject(brush);
        }

        // --- 各ボックスを描画 ---
        auto drawColoredBox = [&](bool condition, COLORREF color, int leftMul, int rightMul) {
            if (!condition) return;
            int left = leftMul * width / 18;
            int right = rightMul * width / 18;
            int top = 18 * height / 20;
            int bottom = 19 * height / 20;

            HBRUSH brush = CreateSolidBrush(color);
            HBRUSH oldBrush = (HBRUSH)SelectObject(memDC, brush);

            Rectangle(memDC, left, top, right, bottom);

            SelectObject(memDC, oldBrush);
            DeleteObject(brush);
            };

        drawColoredBox(drawBoxA, RGB(255, 0, 0), 5, 7);
        drawColoredBox(drawBoxB, RGB(0, 255, 0), 7, 9);
        drawColoredBox(drawBoxC, RGB(0, 0, 255), 9, 11);
        drawColoredBox(drawBoxD, RGB(255, 255, 0), 11, 13);

        // --- メモリDCの内容を画面に転送 ---
        BitBlt(hdc, 0, 0, width, height, memDC, 0, 0, SRCCOPY);

        // --- リソース解放 ---
        SelectObject(memDC, oldBitmap);
        DeleteObject(backBuffer);
        DeleteDC(memDC);

        EndPaint(hWnd, &ps);
        return 0;

    }
    break;
    case WM_KEYDOWN:

        switch (wParam)
        {
        case 'D':
            drawBoxA = true; // Dキーを押したらA描画フラグをON

            break;
        case 'F':
            drawBoxB = true; // Fキーを押したらB描画フラグをON

            break;
        case 'J':
            drawBoxC = true; // Jキーを押したらC描画フラグをON

            break;
        case 'K':
            drawBoxD = true; // Kキーを押したらD描画フラグをON

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

			break;
        case 'F':
            drawBoxB = false; // Fキーを離したら四角を消す
            RECT rectB;

            rectB.left = 7 * width / 18;
            rectB.top = 18 * height / 20;
            rectB.right = 9 * width / 18;
            rectB.bottom = 19 * height / 20;

            break;
        case 'J':
            drawBoxC = false; // Jキーを離したら四角を消す
            RECT rectC;

            rectC.left = 9 * width / 18;
            rectC.top = 18 * height / 20;
            rectC.right = 11 * width / 18;
            rectC.bottom = 19 * height / 20;

            break;
        case 'K':
            drawBoxD = false; // Kキーを離したら四角を消す
            RECT rectD;

            rectD.left = 11 * width / 18;
            rectD.top = 18 * height / 20;
            rectD.right = 13 * width / 18;
            rectD.bottom = 19 * height / 20;

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
