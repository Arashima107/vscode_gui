#ifndef SEARCHCHART_H
#define SEARCHCHART_H

#include <windows.h>
#include "variable_number.h"
#include "Users.h"

/**
 * @class MainMenu
 * @brief メインメニューウィンドウを管理するクラス
 */
class SearchChart {
private:
    static Users login_user;
    HWND Lab_Title; ///< タイトルラベルのハンドル
    char chart_type[2][16] = { ///< 役職タイプの配列
        "Parts",
        "Material"
    };
    HWND Btn_Search; ///< ユーザーコントロールボタンのハンドル
    HWND Lab_Select_ChartType;
    static HWND Comb_Select_ChartType;
    static HWND Lab_PartsNo, Lab_PartsName, Lab_BusinessDiv;
    static HWND Ent_PartsNo, Ent_PartsName, Comb_BusinessDiv;

public:
    /**
     * @brief コンストラクタ
     * @param hInstance アプリケーションインスタンスのハンドル
     */
    SearchChart(HINSTANCE hInstane, const Users& user);
    

    /**
     * @brief デストラクタ
     */
    ~SearchChart();

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
    static void Btn_click(int wmId, HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, SearchChart& menu_instance, int nCmdShow);
    static void Selected_ChartType(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    static void update_MoldParts(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    static void Close(SearchChart& menu_instance);

    const char* className = "SearchChartClass"; ///< ウィンドウクラス名
};

#endif // MAINMENU_H