#include "MainMenu.h"
#include "UserControl.h"
#include "SearchChart.h"
#include "my_functions.h"
#include <stdio.h>

Users MainMenu::login_user;

MainMenu::MainMenu(HINSTANCE hInstane, const Users& user) : hInstance(hInstance), hwnd(NULL) {
    login_user = user;
    strncat(username, login_user.get_pandaID(), sizeof(username) - strlen(username) - 1);
    strncat(authority, login_user.get_authority(), sizeof(authority) - strlen(authority) - 1);

    
    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = MainMenu::WndProc; // ウィンドウプロシージャを設定
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); // アイコンをロード
    wc.hCursor = LoadCursor(NULL, IDC_ARROW); // カーソルをロード
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1); // 背景色を設定
    wc.lpszMenuName = NULL;
    wc.lpszClassName = className; // クラス名を設定
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION); // 小さいアイコンをロード

    RegisterClassEx(&wc); // ウィンドウクラスを登録
}

MainMenu::~MainMenu() {
    UnregisterClass(className, hInstance); // ウィンドウクラスを登録解除
}

bool MainMenu::Create(LPCTSTR lpWindowName) {

    int nWidth = 600, nHeight = 510;
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        className,
        lpWindowName,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, nWidth, nHeight,
        NULL, NULL, hInstance, this
    );

    char login_user_info[128];
    sprintf(login_user_info, "User Name : %s\nAuthority : %s", username, authority);

    if (hwnd != NULL) {
        // タイトル・ユーザー情報ラベルを作成
        {
            // タイトルラベルを作成
            Lab_Title = CreateWindowEx(
                0, 
                "STATIC",              // ボタンクラス名
                "Main Menu",           // ボタンに表示するテキスト
                WS_CHILD | WS_VISIBLE, // 子ウィンドウとして表示
                10, 10, 200, 36,       // ボタンの位置とサイズ (x, y, width, height)
                hwnd,                  // 親ウィンドウのハンドル
                (HMENU)1,              // ボタンID (WM_COMMANDで識別)
                hInstance, 
                NULL
            );
            // タイトルラベルにフォントを適用
            SendMessage(Lab_Title, WM_SETFONT, (WPARAM)hFont_windowtitle, TRUE);

            // ユーザー情報ラベルを作成
            Lab_UserInformation=CreateWindowEx(
                0, 
                "STATIC",              // ボタンクラス名
                login_user_info,           // ボタンに表示するテキスト
                WS_CHILD | WS_VISIBLE, // 子ウィンドウとして表示
                250, 10, 250, 50,       // ボタンの位置とサイズ (x, y, width, height)
                hwnd,                  // 親ウィンドウのハンドル
                (HMENU)1,              // ボタンID (WM_COMMANDで識別)
                hInstance, 
                NULL
            );

            // ユーザー情報ラベルにフォントを適用
            SendMessage(Lab_UserInformation, WM_SETFONT, (WPARAM)hFont_others, TRUE);
        }

        // ユーザー管理ボタンを作成
        {
            // ボタンを作成
            Btn_UserControl=CreateWindowEx(
                0, 
                "BUTTON",              // ボタンクラス名
                "Users Control",           // ボタンに表示するテキスト
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // 子ウィンドウとして表示
                50, 150, 150, 70,       // ボタンの位置とサイズ (x, y, width, height)
                hwnd,                  // 親ウィンドウのハンドル
                (HMENU)Btn_MainMenu_UserControl,              // ボタンID (WM_COMMANDで識別)
                hInstance, 
                NULL
            );

            // ボタンにフォントを適用
                SendMessage(Btn_UserControl, WM_SETFONT, (WPARAM)hFont_others, TRUE);
        }

        // チャート検索ボタンを作成
        {
            // ボタンを作成
            Btn_SearchChart=CreateWindowEx(
                0, 
                "BUTTON",              // ボタンクラス名
                "Search Chart",           // ボタンに表示するテキスト
                WS_CHILD | WS_VISIBLE, // 子ウィンドウとして表示
                280, 150, 150, 70,       // ボタンの位置とサイズ (x, y, width, height)
                hwnd,                  // 親ウィンドウのハンドル
                (HMENU)Btn_MainMenu_SearchChart,              // ボタンID (WM_COMMANDで識別)
                hInstance, 
                NULL
            );

            // ボタンにフォントを適用
                SendMessage(Btn_SearchChart, WM_SETFONT, (WPARAM)hFont_others, TRUE);
        }

        // チャート発行ボタンを作成
        {
            // ボタンを作成
            Btn_IssueChart=CreateWindowEx(
                0, 
                "BUTTON",              // ボタンクラス名
                "Issue Chart",           // ボタンに表示するテキスト
                WS_CHILD | WS_VISIBLE, // 子ウィンドウとして表示
                50, 250, 150, 70,       // ボタンの位置とサイズ (x, y, width, height)
                hwnd,                  // 親ウィンドウのハンドル
                (HMENU)Btn_MainMenu_IssueChart,              // ボタンID (WM_COMMANDで識別)
                hInstance, 
                NULL
            );

            // ボタンにフォントを適用
                SendMessage(Btn_IssueChart, WM_SETFONT, (WPARAM)hFont_others, TRUE);
        }

        // CLOSEボタンを作成
        {
            // ボタンを作成
            Btn_Close=CreateWindowEx(
                0, 
                "BUTTON",              // ボタンクラス名
                "CLOSE",           // ボタンに表示するテキスト
                WS_CHILD | WS_VISIBLE, // 子ウィンドウとして表示
                280, 250, 150, 70,       // ボタンの位置とサイズ (x, y, width, height)
                hwnd,                  // 親ウィンドウのハンドル
                (HMENU)Btn_programClose,              // ボタンID (WM_COMMANDで識別)
                hInstance, 
                NULL
            );

            // ボタンにフォントを適用
                SendMessage(Btn_Close, WM_SETFONT, (WPARAM)hFont_others, TRUE);
        }
    }

    return hwnd != NULL;
}

void MainMenu::Show(int nCmdShow) {
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
}

HWND MainMenu::GetHwnd() const {
    return hwnd;
}

LRESULT CALLBACK MainMenu::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    MainMenu* pThis;

    if (msg == WM_NCCREATE) {
        pThis = static_cast<MainMenu*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
    } else {
        pThis = reinterpret_cast<MainMenu*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }

    switch (msg) {
        case WM_COMMAND:{
            switch(LOWORD(wParam)){
                case Btn_MainMenu_UserControl: 
                    pThis->OnBtnUserControlClick();
                    break;
                
                case Btn_MainMenu_SearchChart:
                    printf("Clicked\n");
                    pThis->OnBtnSearchChartClick();
                    break;
                case Btn_MainMenu_IssueChart:
                    printf("Issue Chart Clicked!\n");
                    break;
                case Btn_programClose:
                    PostQuitMessage(0);
                    break;
            }
            break;
        }
        case WM_CTLCOLORSTATIC: {
            // STATIC コントロールの背景色を設定
            HDC hdcStatic = (HDC)wParam;
            SetBkColor(hdcStatic, RGB(255, 255, 255)); // 背景色を白に設定
            SetTextColor(hdcStatic, RGB(0, 0, 0));    // 文字色を黒に設定
            return (LRESULT)CreateSolidBrush(RGB(255, 255, 255)); // 背景色のブラシを返す
        }
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

void MainMenu::Close(MainMenu& menu_instance) {
    if (menu_instance.hwnd != NULL) {
        DestroyWindow(menu_instance.hwnd);
        menu_instance.hwnd = NULL;
    }
}

void MainMenu::Btn_click(int wmId, HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, MainMenu& menu_instance, int nCmdShow) {
    switch (wmId) {
        case Btn_MainMenu_UserControl: {
            printf("Clicked User Control Btn!\n");
            
            UserControl userControl(menu_instance.hInstance, login_user);
            if (userControl.Create("User Control")) {
                userControl.Show(nCmdShow);
            }
            break;
        }
        case Btn_programClose: {
            PostQuitMessage(0);
            break;
        }
        // 他のボタンの処理を追加する場合はここに書く
        default:
            break;
    }
}

void MainMenu::OnBtnUserControlClick() {
    printf("Clicked User Control Btn!\n");
    UserControl userControl(hInstance, login_user);
    if (userControl.Create("User Control")) {
        userControl.Show(SW_SHOW);
    }
}

void MainMenu::OnBtnSearchChartClick() {
    printf("Clicked Search Chart Btn!\n");
    SearchChart searchchart(hInstance, login_user);
    if (searchchart.Create("Chart Search")) {
        searchchart.Show(SW_SHOW);
    }
}