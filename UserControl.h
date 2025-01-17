#ifndef USERCONTROL_H
#define USERCONTROL_H

#include <windows.h>
#include "variable_number.h"
#include "Users.h"

/**
 * @class MainMenu
 * @brief メインメニューウィンドウを管理するクラス
 */
/**
 * @class UserControl
 * @brief ユーザーコントロールウィンドウを管理するクラス
 */
class UserControl {
private:
    static Users login_user; ///< ログインユーザー情報
    static Users control_user; ///< コントロールユーザー情報
    char username[32] = ""; ///< ユーザー名を格納する文字配列
    char authority[32] = ""; ///< 権限情報を格納する文字配列
    char position_type[4][16] = { ///< 役職タイプの配列
        "General",
        "STL",
        "TM/TL",
        "GM"
    };
    char authority_type[6][32] = { ///< 権限タイプの配列
        "View",
        "Administrator",
        "General Designer",
        "General Manufacturer",
        "Manager Designer",
        "Manager Manufacturer"
    };
    bool can_edit_manager = false; ///< マネージャー編集権限
    bool can_edit_general = false; ///< 一般編集権限
    bool can_edit_viewer = false; ///< ビューアー編集権限
    static HWND Lab_Title; ///< タイトルラベルのハンドル
    static HWND Lab_UserInformation; ///< ユーザー情報ラベルのハンドル
    static HWND Lab_PandaID, Lab_UserName, Lab_UserDiv, Lab_UserEmail, Lab_UserPosition, Lab_Authority, Lab_UserPW; ///< 各種ラベルのハンドル
    HWND Ent_PandaID, Ent_UserName, Ent_UserDiv, Ent_UserEmail, Comb_UserPosition, Comb_Authority, Ent_UserPW; ///< 各種エントリとコンボボックスのハンドル
    HWND Btn_SearchUser; ///< ユーザー検索ボタンのハンドル
    HWND Btn_UpdateUser; ///< ユーザー更新ボタンのハンドル

public:
    /**
     * @brief コンストラクタ
     * @param hInstance アプリケーションインスタンスのハンドル
     * @param user ユーザー情報
     */
    UserControl(HINSTANCE hInstance, const Users& user);

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

#endif // USERCONTROL_H