// このヘッダーファイルは、Windowsアプリケーションで使用される定数とグローバル変数を定義します。

#define MAX_LINE_LENGTH 16384
#define MAX_FIELD_LENGTH 256

// Btn_Close: 閉じるボタンの識別子を定義します。
#define Btn_programClose 0001

// ボタンの識別子を定義
#define Btn_MainMenu_UserControl 1001
#define Btn_MainMenu_SearchChart 1002
#define Btn_MainMenu_IssueChart 1003

#define Btn_UserControl_SearchUser 2001
#define Btn_UserControl_UpdateUser 2002
#define Btn_UserControl_CsvInclude 2003

#define Btn_SearchChart_Search 3001
#define Btn_SearchChart_Clear 3002
#define Comb_SearchChart_ChartType 3101

//const char *user_db_path = "C:\\users\\water\\desktop\\vscode_gui\\??";
//const char *parts_db_path = "C:\\users\\water\\desktop\\vscode_gui\\??";
//const char *assemble_db_path = "C:\\users\\water\\desktop\\vscode_gui\\??";
//const char *selectitem_db_path = "C:\\users\\water\\desktop\\vscode_gui\\??";

// グローバル変数としてフォントハンドルを保持
// hFont_windowtitle: CreateFontを使用して作成されたカスタムフォントのハンドル
extern HFONT hFont_windowtitle;

extern HFONT hFont_others;

extern HBRUSH hBrush; // 背景色用のブラシ

// ここに新しい定数やグローバル変数を追加できます。
// 例: #define Btn_NewButton 1004
// 例: extern int g_someGlobalVariable;

extern char Business_div[2][16];

extern char position_type[4][16];

extern char authority_type[6][32];

