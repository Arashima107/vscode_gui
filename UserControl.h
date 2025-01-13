#ifndef USERCONTROL_H
#define USERCONTROL_H

#include <windows.h>
#include "variable_number.h"

/**
 * @class MainMenu
 * @brief メインメニューウィンドウを管理するクラス
 */
class UserControl {
private:
    char username[32] = ""; ///< ユーザー名を格納する文字配列
    char authority[16] = ""; ///< 権限情報を格納する文字配列
    bool can_edit_manager = false;
    bool can_edit_general = false;
    bool can_edit_viewer = false;
    HWND Lab_Title; ///< タイトルラベルのハンドル
    HWND Lab_UserInformation; ///< ユーザー情報ラベルのハンドル
    HWND Lab_PandaID, Lab_UserName, Lab_UserDiv, Lab_UserPosition, Lab_Authority, Lab_UserPW;
    HWND Ent_PandaID, Ent_UserName, Ent_UserDiv, Comb_UserPosition, Comb_Authority, Ent_UserPW;
    HWND Btn_UserControl; ///< ユーザーコントロールボタンのハンドル
    HWND Btn_SearchChart; ///< 検索チャートボタンのハンドル
    HWND Btn_IssueChart; ///< 発行チャートボタンのハンドル
    HWND Btn_Close; ///< 閉じるボタンのハンドル

public:
    /**
     * @brief コンストラクタ
     * @param hInstance アプリケーションインスタンスのハンドル
     */
    UserControl(HINSTANCE hInstance);

    /**
     * @brief デストラクタ
     */
    ~UserControl();

    /**
     * @brief ウィンドウを作成する
     * @param lpWindowName ウィンドウの名前
     * @param nWidth ウィンドウの幅
     * @param nHeight ウィンドウの高さ
     * @return 成功した場合はtrue、失敗した場合はfalse
     */
    bool Create(LPCTSTR lpWindowName);

    /**
     * @brief ウィンドウを表示する
     * @param nCmdShow 表示オプション
     */
    void Show(int nCmdShow);

    /**
     * @brief ウィンドウのハンドルを取得する
     * @return ウィンドウのハンドル
     */
    HWND GetHwnd() const;

private:
    /**
     * @brief ウィンドウプロシージャ
     * @param hwnd ウィンドウのハンドル
     * @param msg メッセージ
     * @param wParam メッセージの追加情報
     * @param lParam メッセージの追加情報
     * @return メッセージの処理結果
     */
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    HINSTANCE hInstance; ///< アプリケーションインスタンスのハンドル
    HWND hwnd; ///< ウィンドウのハンドル

    /**
     * @brief ボタンクリックイベントのハンドラ
     * @param wmId ボタンのID
     * @param hwnd ウィンドウのハンドル
     * @param msg メッセージ
     * @param wParam メッセージの追加情報
     * @param lParam メッセージの追加情報
     */
    static void Btn_click(int wmId, HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    const char* className = "UserControlClass"; ///< ウィンドウクラス名
};

#endif // MAINMENU_H