#include "SearchChart.h"
#include "UserControl.h"
#include <stdio.h>

Users SearchChart::login_user;
HWND SearchChart::Comb_Select_ChartType;

SearchChart::SearchChart(HINSTANCE hInstane, const Users& user) : hInstance(hInstance), hwnd(NULL) {
    login_user = user;
    
    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = SearchChart::WndProc; // ウィンドウプロシージャを設定
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

SearchChart::~SearchChart() {
    UnregisterClass(className, hInstance); // ウィンドウクラスを登録解除
}

bool SearchChart::Create(LPCTSTR lpWindowName) {

    int nWidth = 600, nHeight = 510;
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        className,
        lpWindowName,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, nWidth, nHeight,
        NULL, NULL, hInstance, this
    );

    // フォントを作成する関数
    HFONT hFont_Entry = CreateFont(
        -MulDiv(12, GetDeviceCaps(GetDC(hwnd), LOGPIXELSY), 72), // フォントの高さ (ポイントサイズからピクセルに変換)
        0,                  // フォントの幅 (0: 自動調整)
        0,                  // テキストの角度 (0: 通常)
        0,                  // ベースラインとX軸の角度 (0: 通常)
        FW_NORMAL,          // フォントの太さ (FW_NORMAL: 標準)
        FALSE,              // イタリック体 (FALSE: 通常)
        FALSE,              // 下線 (FALSE: 無効)
        FALSE,              // 打ち消し線 (FALSE: 無効)
        SHIFTJIS_CHARSET,   // 文字セット (SHIFTJIS_CHARSET: 日本語)
        OUT_DEFAULT_PRECIS, // 出力精度 (OUT_DEFAULT_PRECIS: デフォルト)
        CLIP_DEFAULT_PRECIS,// クリッピング精度 (CLIP_DEFAULT_PRECIS: デフォルト)
        DEFAULT_QUALITY,    // 出力品質 (DEFAULT_QUALITY: デフォルト)
        DEFAULT_PITCH | FF_DONTCARE, // ピッチとファミリー (デフォルト)
        "MS UI Gothic"      // フォント名 (日本語フォント)
    );

    if (hwnd != NULL) {
        // タイトル・ユーザー情報ラベルを作成
        {
            // タイトルラベルを作成
            Lab_Title = CreateWindowEx(
                0, 
                "STATIC",              // ボタンクラス名
                "Search Chart",           // ボタンに表示するテキスト
                WS_CHILD | WS_VISIBLE, // 子ウィンドウとして表示
                10, 10, 200, 36,       // ボタンの位置とサイズ (x, y, width, height)
                hwnd,                  // 親ウィンドウのハンドル
                (HMENU)1,              // ボタンID (WM_COMMANDで識別)
                hInstance, 
                NULL
            );
            // タイトルラベルにフォントを適用
            SendMessage(Lab_Title, WM_SETFONT, (WPARAM)hFont_windowtitle, TRUE);

        }

        // UserPositionのTEXTボックスとラベルの作成
        {
            short int count_chart_type = sizeof(chart_type)/sizeof(chart_type[0]);
            Lab_Select_ChartType=CreateWindowEx(
                0, 
                "STATIC",              // ボタンクラス名
                "Chart Type",           // ボタンに表示するテキスト
                WS_CHILD | WS_VISIBLE | ES_CENTER, // 子ウィンドウとして表示
                300, 20, 100, 30,       // ボタンの位置とサイズ (x, y, width, height)
                hwnd,                  // 親ウィンドウのハンドル
                (HMENU)1,              // ボタンID (WM_COMMANDで識別)
                hInstance, 
                NULL
            );
            
            // ユーザー情報ラベルにフォントを適用
            SendMessage(Lab_Select_ChartType, WM_SETFONT, (WPARAM)hFont_others, TRUE);

            Comb_Select_ChartType = CreateWindowEx(
                WS_EX_CLIENTEDGE,
                "COMBOBOX",       // ウィンドウクラス名
                "",               // 初期表示するテキスト
                WS_CHILD | WS_VISIBLE | CBS_DROPDOWN, // スタイル
                410, 20, 100, 30*count_chart_type, // 位置とサイズ (x, y, width, height)
                hwnd,             // 親ウィンドウのハンドル
                (HMENU)Comb_SearchChart_ChartType,         // コントロールID
                GetModuleHandle(NULL),
                NULL
            );
            
            // ユーザー情報ラベルにフォントを適用
            SendMessage(Comb_Select_ChartType, WM_SETFONT, (WPARAM)hFont_Entry, TRUE);

            for(int i = 0;i<count_chart_type;i++){
                SendMessage(Comb_Select_ChartType, CB_ADDSTRING, 0, (LPARAM)chart_type[i]);
            }
        }
    }

    return hwnd != NULL;
}

void SearchChart::Show(int nCmdShow) {
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
}

HWND SearchChart::GetHwnd() const {
    return hwnd;
}

LRESULT CALLBACK SearchChart::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    //MainMenu* menu_instance = nullptr;
    /*SearchChart* pThis;

    if (msg == WM_NCCREATE) {
        pThis = static_cast<MainMenu*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
    } else {
        pThis = reinterpret_cast<MainMenu*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }
    */

    switch (msg) {
        case WM_COMMAND:{
            if (LOWORD(wParam) == Btn_MainMenu_UserControl) {
                //pThis->OnBtnUserControlClick();
            }
            Selected_ChartType(hwnd, msg, wParam, lParam);
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

void SearchChart::Close(SearchChart& menu_instance) {
    if (menu_instance.hwnd != NULL) {
        DestroyWindow(menu_instance.hwnd);
        menu_instance.hwnd = NULL;
    }
}

void SearchChart::Btn_click(int wmId, HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, SearchChart& menu_instance, int nCmdShow) {
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

void SearchChart::Selected_ChartType(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    HFONT hFont_Entry = CreateFont(
        -MulDiv(12, GetDeviceCaps(GetDC(hwnd), LOGPIXELSY), 72), // フォントの高さ (ポイントサイズからピクセルに変換)
        0,                  // フォントの幅 (0: 自動調整)
        0,                  // テキストの角度 (0: 通常)
        0,                  // ベースラインとX軸の角度 (0: 通常)
        FW_NORMAL,          // フォントの太さ (FW_NORMAL: 標準)
        FALSE,              // イタリック体 (FALSE: 通常)
        FALSE,              // 下線 (FALSE: 無効)
        FALSE,              // 打ち消し線 (FALSE: 無効)
        SHIFTJIS_CHARSET,   // 文字セット (SHIFTJIS_CHARSET: 日本語)
        OUT_DEFAULT_PRECIS, // 出力精度 (OUT_DEFAULT_PRECIS: デフォルト)
        CLIP_DEFAULT_PRECIS,// クリッピング精度 (CLIP_DEFAULT_PRECIS: デフォルト)
        DEFAULT_QUALITY,    // 出力品質 (DEFAULT_QUALITY: デフォルト)
        DEFAULT_PITCH | FF_DONTCARE, // ピッチとファミリー (デフォルト)
        "MS UI Gothic"      // フォント名 (日本語フォント)
    );
    
    HWND hEntryBox;
    if (HIWORD(wParam) == CBN_SELCHANGE && LOWORD(wParam) == Comb_SearchChart_ChartType) {
        int index = SendMessage(Comb_Select_ChartType, CB_GETCURSEL, 0, 0);
        if (index != CB_ERR) {
            // 選択されたチャートタイプに応じてウィンドウ内の配置を変更する処理をここに追加
            switch (index) {
                case 0:
                    printf("Select No. 0\n");
                    DestroyWindow(hEntryBox);
                    hEntryBox=nullptr;
                    UpdateWindow(hwnd);
                    // チャートタイプ0に応じた配置変更
                    break;
                case 1:
                    printf("Select No. 1 \n");
                    // ENTRYボックスを作成
                    hEntryBox = CreateWindowEx(
                        WS_EX_CLIENTEDGE,
                        "EDIT",            // ウィンドウクラス名
                        "",                // 初期表示するテキスト
                        WS_CHILD | WS_VISIBLE | ES_LEFT, // スタイル
                        50, 100, 200, 30,  // 位置とサイズ (x, y, width, height)
                        hwnd,              // 親ウィンドウのハンドル
                        (HMENU)1,          // コントロールID
                        GetModuleHandle(NULL),
                        NULL
                    );
                    // ENTRYボックスにフォントを適用
                    SendMessage(hEntryBox, WM_SETFONT, (WPARAM)hFont_Entry, TRUE);
                    // チャートタイプ1に応じた配置変更
                    break;
                // 他のチャートタイプに応じた処理を追加
                default:
                    break;
            }
        }
    }
}