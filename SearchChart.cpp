#include "SearchChart.h"
#include "UserControl.h"
#include "my_functions.h"
#include <stdio.h>

Users SearchChart::login_user;
HWND SearchChart::Comb_Select_ChartType;
HWND SearchChart::Lab_PartsNo;
HWND SearchChart::Lab_PartsName;
HWND SearchChart::Lab_BusinessDiv;
HWND SearchChart::Ent_PartsNo;
HWND SearchChart::Ent_PartsName;
HWND SearchChart::Comb_BusinessDiv;
//char SearchChart::chart_type[2][16] = {"Part", "Material"};

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
            //PostQuitMessage(0);
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
    
    int x=20, dx=100, y=100, dy=40;
    if (HIWORD(wParam) == CBN_SELCHANGE && LOWORD(wParam) == Comb_SearchChart_ChartType) {
        int index = SendMessage(Comb_Select_ChartType, CB_GETCURSEL, 0, 0);
        update_MoldParts(hwnd, msg, wParam, lParam);
    }
}

void SearchChart::update_MoldParts(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
    
    int width_Lab = 120, width_edit = 250;
    int x_lab=20, x_edit=x_lab+width_Lab, y=100, dy=50;

    static HFONT hFont_Entry = CreateFont(
        -MulDiv(12, GetDeviceCaps(GetDC(hwnd), LOGPIXELSY), 72), 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
        SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_DONTCARE, "MS UI Gothic"
    );

    SafeDestroyWindow(Lab_PartsNo);
    SafeDestroyWindow(Ent_PartsNo);// ハンドルをクリア
    
    SafeDestroyWindow(Lab_PartsName);
    SafeDestroyWindow(Ent_PartsName);
    
    SafeDestroyWindow(Lab_BusinessDiv);
    SafeDestroyWindow(Comb_BusinessDiv);

    int selected_ChartType = SendMessage(Comb_Select_ChartType, CB_GETCURSEL, 0, 0);
    if (selected_ChartType!= CB_ERR){
        switch(selected_ChartType){
            case 0:
            // 
            {
                Lab_PartsNo = CreateWindowEx(
                    0,
                    "STATIC",
                    "Parts No",
                    WS_CHILD | WS_VISIBLE | ES_CENTER, 
                    x_lab, y, width_Lab, 30,
                    hwnd,
                    (HMENU)1,
                    GetModuleHandle(NULL),
                    NULL
                );
                SendMessage(Lab_PartsNo, WM_SETFONT, (WPARAM)hFont_Entry, TRUE);

                Ent_PartsNo = CreateWindowEx(
                    WS_EX_CLIENTEDGE,
                    "EDIT",
                    "",
                    WS_CHILD | WS_VISIBLE | ES_LEFT,
                    x_edit, y, width_edit, 30,
                    hwnd,
                    (HMENU)1,
                    GetModuleHandle(NULL),
                    NULL
                );
                SendMessage(Ent_PartsNo, WM_SETFONT, (WPARAM)hFont_Entry, TRUE);
                
                y+=dy;
            }
            
            {
                Lab_PartsName = CreateWindowEx(
                    0,
                    "STATIC",
                    "Parts Name",
                    WS_CHILD | WS_VISIBLE | ES_CENTER, 
                    x_lab, y, width_Lab, 30,
                    hwnd,
                    (HMENU)1,
                    GetModuleHandle(NULL),
                    NULL
                );
                SendMessage(Lab_PartsName, WM_SETFONT, (WPARAM)hFont_Entry, TRUE);

                Ent_PartsName = CreateWindowEx(
                    WS_EX_CLIENTEDGE,
                    "EDIT",
                    "",
                    WS_CHILD | WS_VISIBLE | ES_LEFT,
                    x_edit, y, width_edit, 30,
                    hwnd,
                    (HMENU)1,
                    GetModuleHandle(NULL),
                    NULL
                );
                SendMessage(Ent_PartsName, WM_SETFONT, (WPARAM)hFont_Entry, TRUE);
                
                y+=dy;
            }
            // UserPositionのTEXTボックスとラベルの作成
            {
                short int count_Business_div = sizeof(Business_div)/sizeof(Business_div[0]);    
                Lab_BusinessDiv = CreateWindowEx(
                    0,
                    "STATIC",
                    "Business Div",
                    WS_CHILD | WS_VISIBLE | ES_CENTER, 
                    x_lab, y, width_Lab, 30,
                    hwnd,
                    (HMENU)1,
                    GetModuleHandle(NULL),
                    NULL
                );
                SendMessage(Lab_BusinessDiv, WM_SETFONT, (WPARAM)hFont_Entry, TRUE);

                Comb_BusinessDiv = CreateWindowEx(
                    WS_EX_CLIENTEDGE,
                    "COMBOBOX",       // ウィンドウクラス名
                    "",               // 初期表示するテキスト
                    WS_CHILD | WS_VISIBLE | CBS_DROPDOWN, // スタイル
                    x_edit, y, width_edit, 30*count_Business_div, // 位置とサイズ (x, y, width, height)
                    hwnd,             // 親ウィンドウのハンドル
                    (HMENU)1,         // コントロールID
                    GetModuleHandle(NULL),
                    NULL
                );
                
                // ユーザー情報ラベルにフォントを適用
                SendMessage(Comb_BusinessDiv, WM_SETFONT, (WPARAM)hFont_Entry, TRUE);
                
                y+=dy;
                
                for(int i = 0;i<count_Business_div;i++){
                    SendMessage(Comb_BusinessDiv, CB_ADDSTRING, 0, (LPARAM)Business_div[i]);
                }
            }

        }
    }

    InvalidateRect(hwnd, NULL, TRUE);
}