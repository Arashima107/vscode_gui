#include "UserControl.h"
#include "my_functions.h"
#include <stdio.h>
#include <commdlg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <xlsxio_read.h>


// 静的メンバー変数の定義
HWND UserControl::Lab_Title = NULL;
HWND UserControl::Lab_UserInformation = NULL;
HWND UserControl::Lab_PandaID = NULL;
HWND UserControl::Lab_UserName = NULL;
HWND UserControl::Lab_UserDiv = NULL;
HWND UserControl::Lab_UserPosition = NULL;
HWND UserControl::Lab_Authority = NULL;
HWND UserControl::Lab_UserPW = NULL;
HWND UserControl::Lab_UserEmail = NULL;
HWND UserControl::Ent_PandaID;
HWND UserControl::Ent_UserDiv;
HWND UserControl::Ent_UserEmail;
HWND UserControl::Ent_UserName;
HWND UserControl::Ent_UserPW;
HWND UserControl::Comb_Authority;
HWND UserControl::Comb_UserPosition;
Users UserControl::login_user;
Users UserControl::control_user;
UserControl* UserControl::instance = nullptr;


UserControl::UserControl(HINSTANCE hInstance, const Users& user) : hInstance(hInstance), hwnd(NULL) {
    login_user = user;
    strncat(username, login_user.get_pandaID(), sizeof(username) - strlen(username) - 1);
    strncat(authority, login_user.get_authority(), sizeof(authority) - strlen(authority) - 1);

    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WndProc; // ウィンドウプロシージャを設定
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

UserControl::~UserControl() {
    UnregisterClass(className, hInstance); // ウィンドウクラスを登録解除
}

bool UserControl::Create(LPCTSTR lpWindowName) {
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

    char login_user_info[128];
    sprintf(login_user_info, "User Name : %s\nAuthority : %s", username, authority);
    // printf("%s\n", login_user_info);

    if (hwnd != NULL) {
        // タイトル・ユーザー情報ラベルを作成
        {
            // タイトルラベルを作成
            Lab_Title = CreateWindowEx(
                0, 
                "STATIC",              // ボタンクラス名
                "User Control",           // ボタンに表示するテキスト
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
        
        // PandaIDのTEXTボックスとラベルの作成
        {
            Lab_PandaID=CreateWindowEx(
                0, 
                "STATIC",              // ボタンクラス名
                "Panda ID",           // ボタンに表示するテキスト
                WS_CHILD | WS_VISIBLE | ES_CENTER, // 子ウィンドウとして表示
                20, 80, 180, 30,       // ボタンの位置とサイズ (x, y, width, height)
                hwnd,                  // 親ウィンドウのハンドル
                (HMENU)1,              // ボタンID (WM_COMMANDで識別)
                hInstance, 
                NULL
            );
            
            // ユーザー情報ラベルにフォントを適用
            SendMessage(Lab_PandaID, WM_SETFONT, (WPARAM)hFont_others, TRUE);

            Ent_PandaID=CreateWindowEx(
                WS_EX_CLIENTEDGE,
                "EDIT",              // ボタンクラス名
                "",           // ボタンに表示するテキスト
                WS_CHILD | WS_VISIBLE | ES_LEFT, // 子ウィンドウとして表示
                20, 100, 180, 30,       // ボタンの位置とサイズ (x, y, width, height)
                hwnd,                  // 親ウィンドウのハンドル
                (HMENU)1,              // ボタンID (WM_COMMANDで識別)
                GetModuleHandle(NULL),
                NULL
            );
            
            // ユーザー情報ラベルにフォントを適用
            SendMessage(Ent_PandaID, WM_SETFONT, (WPARAM)hFont_others, TRUE);
        }

        // UserNameのTEXTボックスとラベルの作成
        {
            Lab_UserName=CreateWindowEx(
                0, 
                "STATIC",              // ボタンクラス名
                "User Name",           // ボタンに表示するテキスト
                WS_CHILD | WS_VISIBLE | ES_CENTER, // 子ウィンドウとして表示
                210, 80, 180, 30,       // ボタンの位置とサイズ (x, y, width, height)
                hwnd,                  // 親ウィンドウのハンドル
                (HMENU)1,              // ボタンID (WM_COMMANDで識別)
                hInstance, 
                NULL
            );
            
            // ユーザー情報ラベルにフォントを適用
            SendMessage(Lab_UserName, WM_SETFONT, (WPARAM)hFont_others, TRUE);

            Ent_UserName=CreateWindowEx(
                WS_EX_CLIENTEDGE,
                "EDIT",              // ボタンクラス名
                "",           // ボタンに表示するテキスト
                WS_CHILD | WS_VISIBLE | ES_LEFT, // 子ウィンドウとして表示
                210, 100, 180, 30,       // ボタンの位置とサイズ (x, y, width, height)
                hwnd,                  // 親ウィンドウのハンドル
                (HMENU)1,              // ボタンID (WM_COMMANDで識別)
                GetModuleHandle(NULL),
                NULL
            );
            
            // ユーザー情報ラベルにフォントを適用
            SendMessage(Ent_UserName, WM_SETFONT, (WPARAM)hFont_Entry, TRUE);
        }

        // UserDivisionのTEXTボックスとラベルの作成
        {
            Lab_UserDiv=CreateWindowEx(
                0, 
                "STATIC",              // ボタンクラス名
                "Division",           // ボタンに表示するテキスト
                WS_CHILD | WS_VISIBLE | ES_CENTER, // 子ウィンドウとして表示
                20, 150, 300, 30,       // ボタンの位置とサイズ (x, y, width, height)
                hwnd,                  // 親ウィンドウのハンドル
                (HMENU)1,              // ボタンID (WM_COMMANDで識別)
                hInstance, 
                NULL
            );
            
            // ユーザー情報ラベルにフォントを適用
            SendMessage(Lab_UserDiv, WM_SETFONT, (WPARAM)hFont_others, TRUE);

            Ent_UserDiv=CreateWindowEx(
                WS_EX_CLIENTEDGE,
                "EDIT",              // ボタンクラス名
                "",           // ボタンに表示するテキスト
                WS_CHILD | WS_VISIBLE | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL, // 子ウィンドウとして表示
                20, 170, 300, 30,       // ボタンの位置とサイズ (x, y, width, height)
                hwnd,                  // 親ウィンドウのハンドル
                (HMENU)1,              // ボタンID (WM_COMMANDで識別)
                GetModuleHandle(NULL),
                NULL
            );
            
            // ユーザー情報ラベルにフォントを適用
            SendMessage(Ent_UserDiv, WM_SETFONT, (WPARAM)hFont_Entry, TRUE);
        }

        // UserPositionのTEXTボックスとラベルの作成
        {
            short int count_position_type = sizeof(position_type)/sizeof(position_type[0]);
            Lab_UserPosition=CreateWindowEx(
                0, 
                "STATIC",              // ボタンクラス名
                "Position",           // ボタンに表示するテキスト
                WS_CHILD | WS_VISIBLE | ES_CENTER, // 子ウィンドウとして表示
                330, 150, 100, 30,       // ボタンの位置とサイズ (x, y, width, height)
                hwnd,                  // 親ウィンドウのハンドル
                (HMENU)1,              // ボタンID (WM_COMMANDで識別)
                hInstance, 
                NULL
            );
            
            // ユーザー情報ラベルにフォントを適用
            SendMessage(Lab_UserPosition, WM_SETFONT, (WPARAM)hFont_others, TRUE);

            Comb_UserPosition = CreateWindowEx(
                WS_EX_CLIENTEDGE,
                "COMBOBOX",       // ウィンドウクラス名
                "",               // 初期表示するテキスト
                WS_CHILD | WS_VISIBLE | CBS_DROPDOWN, // スタイル
                330, 170, 100, 30*count_position_type, // 位置とサイズ (x, y, width, height)
                hwnd,             // 親ウィンドウのハンドル
                (HMENU)1,         // コントロールID
                GetModuleHandle(NULL),
                NULL
            );
            
            // ユーザー情報ラベルにフォントを適用
            SendMessage(Comb_UserPosition, WM_SETFONT, (WPARAM)hFont_Entry, TRUE);

            for(int i = 0;i<count_position_type;i++){
                SendMessage(Comb_UserPosition, CB_ADDSTRING, 0, (LPARAM)position_type[i]);
            }
        }

        // UserDivisionのTEXTボックスとラベルの作成
        {
            Lab_UserEmail=CreateWindowEx(
                0, 
                "STATIC",              // ボタンクラス名
                "Email",           // ボタンに表示するテキスト
                WS_CHILD | WS_VISIBLE | ES_CENTER, // 子ウィンドウとして表示
                20, 220, 300, 30,       // ボタンの位置とサイズ (x, y, width, height)
                hwnd,                  // 親ウィンドウのハンドル
                (HMENU)1,              // ボタンID (WM_COMMANDで識別)
                hInstance, 
                NULL
            );
            
            // ユーザー情報ラベルにフォントを適用
            SendMessage(Lab_UserEmail, WM_SETFONT, (WPARAM)hFont_others, TRUE);

            Ent_UserEmail=CreateWindowEx(
                WS_EX_CLIENTEDGE,
                "EDIT",              // ボタンクラス名
                "",           // ボタンに表示するテキスト
                WS_CHILD | WS_VISIBLE | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL, // 子ウィンドウとして表示
                20, 240, 300, 30,       // ボタンの位置とサイズ (x, y, width, height)
                hwnd,                  // 親ウィンドウのハンドル
                (HMENU)1,              // ボタンID (WM_COMMANDで識別)
                GetModuleHandle(NULL),
                NULL
            );
            
            // ユーザー情報ラベルにフォントを適用
            SendMessage(Ent_UserEmail, WM_SETFONT, (WPARAM)hFont_Entry, TRUE);
        }
        
        // AuthorityのTEXTボックスとラベルの作成
        {
            short int count_authority_type = sizeof(authority_type)/sizeof(authority_type[0]);
            Lab_Authority=CreateWindowEx(
                0, 
                "STATIC",              // ボタンクラス名
                "Authority",           // ボタンに表示するテキスト
                WS_CHILD | WS_VISIBLE | ES_CENTER, // 子ウィンドウとして表示
                20, 290, 200, 30,       // ボタンの位置とサイズ (x, y, width, height)
                hwnd,                  // 親ウィンドウのハンドル
                (HMENU)1,              // ボタンID (WM_COMMANDで識別)
                hInstance, 
                NULL
            );
            
            // ユーザー情報ラベルにフォントを適用
            SendMessage(Lab_Authority, WM_SETFONT, (WPARAM)hFont_others, TRUE);

            Comb_Authority = CreateWindowEx(
                WS_EX_CLIENTEDGE,
                "COMBOBOX",       // ウィンドウクラス名
                "",               // 初期表示するテキスト
                WS_CHILD | WS_VISIBLE | CBS_DROPDOWN, // スタイル
                20, 310, 200, 30*count_authority_type, // 位置とサイズ (x, y, width, height)
                hwnd,             // 親ウィンドウのハンドル
                (HMENU)1,         // コントロールID
                GetModuleHandle(NULL),
                NULL
            );
            
            // ユーザー情報ラベルにフォントを適用
            SendMessage(Comb_Authority, WM_SETFONT, (WPARAM)hFont_Entry, TRUE);

            for(int i = 0;i<count_authority_type;i++){
                SendMessage(Comb_Authority, CB_ADDSTRING, 0, (LPARAM)authority_type[i]);
            }
        }

        // UserPWのTEXTボックスとラベルの作成
        {
            Lab_UserPW=CreateWindowEx(
                0, 
                "STATIC",              // ボタンクラス名
                "Password",           // ボタンに表示するテキスト
                WS_CHILD | WS_VISIBLE | ES_CENTER, // 子ウィンドウとして表示
                230, 290, 100, 30,       // ボタンの位置とサイズ (x, y, width, height)
                hwnd,                  // 親ウィンドウのハンドル
                (HMENU)1,              // ボタンID (WM_COMMANDで識別)
                hInstance, 
                NULL
            );
            
            // ユーザー情報ラベルにフォントを適用
            SendMessage(Lab_UserPW, WM_SETFONT, (WPARAM)hFont_others, TRUE);

            Ent_UserPW = CreateWindowEx(
                WS_EX_CLIENTEDGE,
                "EDIT",              // ボタンクラス名
                "",           // ボタンに表示するテキスト
                WS_CHILD | WS_VISIBLE | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL, // 子ウィンドウとして表示
                230, 310, 100, 30,       // ボタンの位置とサイズ (x, y, width, height)
                hwnd,                  // 親ウィンドウのハンドル
                (HMENU)1,              // ボタンID (WM_COMMANDで識別)
                GetModuleHandle(NULL),
                NULL
            );
            
            // ユーザー情報ラベルにフォントを適用
            SendMessage(Ent_UserPW, WM_SETFONT, (WPARAM)hFont_Entry, TRUE);
        }

        // ユーザー検索ボタンを作成
        {
            // ボタンを作成
            Btn_CsvInclude=CreateWindowEx(
                0, 
                "BUTTON",              // ボタンクラス名
                "CSV File",           // ボタンに表示するテキスト
                WS_CHILD | WS_VISIBLE, // 子ウィンドウとして表示
                190, 400, 100, 50,       // ボタンの位置とサイズ (x, y, width, height)
                hwnd,                  // 親ウィンドウのハンドル
                (HMENU)Btn_UserControl_CsvInclude,              // ボタンID (WM_COMMANDで識別)
                hInstance, 
                NULL
            );

            // ボタンにフォントを適用
                SendMessage(Btn_CsvInclude, WM_SETFONT, (WPARAM)hFont_others, TRUE);
        }


        // ユーザー検索ボタンを作成
        {
            // ボタンを作成
            Btn_SearchUser=CreateWindowEx(
                0, 
                "BUTTON",              // ボタンクラス名
                "Search",           // ボタンに表示するテキスト
                WS_CHILD | WS_VISIBLE, // 子ウィンドウとして表示
                300, 400, 100, 50,       // ボタンの位置とサイズ (x, y, width, height)
                hwnd,                  // 親ウィンドウのハンドル
                (HMENU)Btn_UserControl_SearchUser,              // ボタンID (WM_COMMANDで識別)
                hInstance, 
                NULL
            );

            // ボタンにフォントを適用
                SendMessage(Btn_SearchUser, WM_SETFONT, (WPARAM)hFont_others, TRUE);
        }

        // ユーザー更新ボタンを作成
        {
            // ボタンを作成
            Btn_UpdateUser=CreateWindowEx(
                0, 
                "BUTTON",              // ボタンクラス名
                "Update",           // ボタンに表示するテキスト
                WS_CHILD | WS_VISIBLE, // 子ウィンドウとして表示
                410, 400, 100, 50,       // ボタンの位置とサイズ (x, y, width, height)
                hwnd,                  // 親ウィンドウのハンドル
                (HMENU)Btn_UserControl_UpdateUser,              // ボタンID (WM_COMMANDで識別)
                hInstance, 
                NULL
            );

            // ボタンにフォントを適用
                SendMessage(Btn_UpdateUser, WM_SETFONT, (WPARAM)hFont_others, TRUE);
        }
    }

    return hwnd != NULL;
}

void UserControl::Show(int nCmdShow) {
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
}

HWND UserControl::GetHwnd() const {
    return hwnd;
}

LRESULT CALLBACK UserControl::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CTLCOLORSTATIC:{
            HDC hdcStatic = (HDC)wParam;
            if ((HWND)lParam != Lab_Title && (HWND)lParam != Lab_UserInformation) { // ラベルの背景色を変更

                // 背景色を設定
                SetBkColor(hdcStatic, RGB(230, 230, 255)); // 青
                return (LRESULT)hBrush; // 背景ブラシを返す
            }else{

                SetBkColor(hdcStatic, RGB(255, 255, 255)); // 背景色を白に設定
                SetTextColor(hdcStatic, RGB(0, 0, 0));    // 文字色を黒に設定
                return (LRESULT)CreateSolidBrush(RGB(255, 255, 255)); // 背景色のブラシを返す
            }

            break;
        }
        case WM_COMMAND:{
            int wmId = LOWORD(wParam);
            Btn_click(wmId,hwnd, msg, wParam, lParam);
            break;
        }
        /*case WM_CTLCOLORSTATIC: {
            // STATIC コントロールの背景色を設定
            HDC hdcStatic = (HDC)wParam;
            SetBkColor(hdcStatic, RGB(255, 255, 255)); // 背景色を白に設定
            SetTextColor(hdcStatic, RGB(0, 0, 0));    // 文字色を黒に設定
            return (LRESULT)CreateSolidBrush(RGB(255, 255, 255)); // 背景色のブラシを返す
        }*/
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            printf("Close User Control Window!\n");
            //PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

void UserControl::Btn_click(int wmId,HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
    int result;
    char pandaID[16];     // ユーザーのPanda ID（初期値: "Unknown"）
    char username[32];    // ユーザー名（初期値: "Unknown"）
    char userdivision[128]; // ユーザーの部署（初期値: "Unknown"）
    char userposition[32];  // ユーザーの役職（初期値: "Unknown"）
    char usermail[64];
    char userauthority[32];       // ユーザーの権限（初期値: "View"）
    char userpassword[8];             // ユーザーのパスワード（初期値: ""）

    switch (wmId){
        case Btn_UserControl_SearchUser:
            {
                GetWindowText(Ent_PandaID, pandaID, sizeof(pandaID)/sizeof(pandaID[0]));
                printf("panda ID : %s\n", pandaID);
                control_user.set_pandaID(pandaID);
                //MessageBox(hwnd, "Would you like to update user information?", "User Update", MB_ICONQUESTION | MB_YESNO);
                control_user.search_users();

                printf("Clicked Btn_UserControl_SearchUser!\n");

                snprintf(username, sizeof(username), "%s", control_user.get_username());
                if(IsWindow(Ent_UserName)){
                    SendMessage(Ent_UserName, WM_SETTEXT, 0, (LPARAM)username);
                }

                snprintf(userdivision, sizeof(userdivision), "%s", control_user.get_userdivision());
                if(IsWindow(Ent_UserDiv)){
                    SendMessage(instance->Ent_UserDiv, WM_SETTEXT, 0, (LPARAM)userdivision);
                }

                snprintf(usermail, sizeof(usermail), "%s", control_user.get_usermail());
                if(IsWindow(Ent_UserEmail)){
                    SendMessage(instance->Ent_UserEmail, WM_SETTEXT, 0, (LPARAM)usermail);
                }

                snprintf(userposition, sizeof(userposition), "%s", control_user.get_userposition());
                if(IsWindow(Comb_UserPosition)){
                    SendMessage(Comb_UserPosition, WM_SETTEXT, 0, (LPARAM)userposition);
                }

                snprintf(userauthority, sizeof(userauthority), "%s", control_user.get_authority());
                if(IsWindow(Comb_Authority)){
                    SendMessage(Comb_Authority, WM_SETTEXT, 0, (LPARAM)userauthority);
                }

                break;
            }
        case Btn_UserControl_UpdateUser:
            {
                result = MessageBox(hwnd, "Would you like to update user information?", "User Update", MB_ICONQUESTION | MB_YESNO);
                if(result == IDYES){
                    GetWindowText(Ent_PandaID, pandaID, sizeof(pandaID)/sizeof(pandaID[0]));
                    GetWindowText(Ent_UserName, username, sizeof(username)/sizeof(username[0]));
                    GetWindowText(Ent_UserDiv, userdivision, sizeof(userdivision)/sizeof(userdivision[0]));
                    GetWindowText(Ent_UserEmail, usermail, sizeof(usermail)/sizeof(usermail[0]));
                    GetWindowText(Ent_UserPW, userpassword, sizeof(userpassword)/sizeof(userpassword[0]));
                    int selected_authority = SendMessage(Comb_Authority, CB_GETCURSEL, 0, 0);
                    SendMessage(Comb_Authority, CB_GETLBTEXT, selected_authority, (LPARAM)userauthority);
                    int selected_position = SendMessage(Comb_UserPosition, CB_GETCURSEL, 0, 0);
                    SendMessage(Comb_UserPosition, CB_GETLBTEXT, selected_position, (LPARAM)userposition);

                    control_user.set_pandaID(pandaID);
                    control_user.set_UserName(username);
                    control_user.set_UserDivision(userdivision);
                    control_user.set_UserMail(usermail);
                    control_user.set_Password(userpassword);
                    control_user.set_authority(userauthority);
                    control_user.set_Position(userposition);

                    printf("pandaID : %s\n", pandaID);
                    printf("UserName : %s\n", username);
                    printf("UserDivision : %s\n", userdivision);
                    printf("UserMail : %s\n", usermail);
                    printf("Password : %s\n", userpassword);
                    printf("Authority : %s\n", userauthority);
                    printf("Position : %s\n", userposition);

                    control_user.update_users(login_user.get_edit_userInformation(), login_user.get_edit_approverInformation());
                }
                break;
            }
        case Btn_UserControl_CsvInclude:
            {
                OPENFILENAME ofn;       // 構造体のインスタンス
                char szFile[260];       // ファイル名を格納するバッファ

                // 構造体のメモリをゼロクリア
                ZeroMemory(&ofn, sizeof(ofn));
                ofn.lStructSize = sizeof(ofn);
                ofn.hwndOwner = hwnd;
                ofn.lpstrFile = szFile;
                ofn.lpstrFile[0] = '\0';
                ofn.nMaxFile = sizeof(szFile);
                ofn.lpstrFilter = "Csv(*.csv)\0*.csv\0Text(*.txt)\0*.TXT\0All(*.*)\0*.*\0";
                ofn.nFilterIndex = 1;
                ofn.lpstrFileTitle = NULL;
                ofn.nMaxFileTitle = 0;
                ofn.lpstrInitialDir = NULL;
                ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

                // ファイルダイアログを表示
                if (GetOpenFileName(&ofn) == TRUE) {
                    // 選択されたファイルパスを取得
                    MessageBox(hwnd, ofn.lpstrFile, "Selected File", MB_OK);
                    printf("CSV File Included from %s\n", ofn.lpstrFile);

                    csv_input_user(hwnd, ofn.lpstrFile);
                }
                
            }
        default:
            break;
    }
}

void UserControl::csv_input_user(HWND hwnd, const char* csv_path){
    printf("csv_input_user\n");
    FILE *file = fopen(csv_path, "r");
    if (file != NULL) {
        printf("file open\n");
        char line[MAX_LINE_LENGTH];  // 行を格納するバッファ
        int row=0;
        while (fgets(line, sizeof(line), file) != NULL) {  // 行を1行ずつ読み込む
            if(row!=0){
                // 行の末尾の改行を取り除く
                line[strcspn(line, "\n")] = '\0';

                // カンマで区切られたフィールドを処理する
                char *field = strtok(line, ",");  // 最初のフィールドを取得
                char col = 1;
                Users control_list_user;
                while (field != NULL) {
                    //printf("%d",col);
                    switch(col){
                        case 1:
                        //printf("%s\n",field);
                        break;
                        
                        case 2:
                        //control_list_user.set_pandaID(field);
                        printf("pandaID:%s\n",field);
                        break;

                        case 3:
                        //control_list_user.set_UserName(field);
                        printf("Name:%s\n",field);
                        break;

                        case 4:
                        //control_list_user.set_UserDivision(field);
                        printf("Division:%s\n",field);
                        break;

                        case 5:
                        //control_list_user.set_UserMail(field);
                        printf("Mail:%s\n",field);
                        break;

                        case 6:
                        //control_list_user.set_Position(field);
                        printf("Position:%s\n",field);
                        break;

                        case 7:
                        //control_list_user.set_authority(field);
                        printf("Authority:%s\n",field);
                        break;

                        case 8:
                        //control_list_user.set_Password(field);
                        printf("Password:%s\n",field);
                        break;

                        default:
                        break;
                    }

                    field = strtok(NULL, ",");  // 次のフィールドを取得
                    col++;
                }
                control_list_user.update_users(login_user.get_edit_userInformation(), login_user.get_edit_approverInformation());
            }
            row++;
        }
        fclose(file);
    } else {
        error_message("Failed to open the file.");
    }
}