#ifndef MATERIALCHART_H
#define MATERIALCHART_H

#include <windows.h>
#include "variable_number.h"
#include "Users.h"

/**
 * @class MaterialChart
 * @brief メインメニューウィンドウを管理するクラス
 */
class MaterialChart {
private:
    static Users login_user;
    char username[32] = ""; ///< ユーザー名を格納する文字配列
    char authority[16] = ""; ///< 権限情報を格納する文字配列
    static HWND Lab_Title; ///< タイトルラベルのハンドル
    static HWND Lab_UserInformation; ///< ユーザー情報ラベルのハンドル
    static HWND Btn_UserControl; ///< ユーザーコントロールボタンのハンドル
    static HWND Btn_SearchChart; ///< 検索チャートボタンのハンドル
    static HWND Btn_IssueChart; ///< 発行チャートボタンのハンドル
    static HWND Btn_Close; ///< 閉じるボタンのハンドル

public:
    /**
     * @brief コンストラクタ
     * @param hInstance アプリケーションインスタンスのハンドル
     */
    MaterialChart(HINSTANCE hInstane, const Users& user);
    

    /**
     * @brief デストラクタ
     */
    ~MaterialChart();

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
    void OnBtnUserControlClick();

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

    static void Close(MaterialChart& menu_instance);

    const char* className = "MaterialChartClass"; ///< ウィンドウクラス名
};

#endif // MATERIALCHART_H