#ifndef USERS_H
#define USERS_H

class Users {
private:
    char db_path[256] = "C:\\users\\water\\desktop\\vscode_gui\\??";

    // ユーザーの情報を保持するメンバー変数
    int id = -1;                      // ユーザーのID（初期値: -1）
    char PandaID[16] = "Unknown";     // ユーザーのPanda ID（初期値: "Unknown"）
    char UserName[32] = "Unknown";    // ユーザー名（初期値: "Unknown"）
    char UserDivision[128] = "Unknown"; // ユーザーの部署（初期値: "Unknown"）
    char UserPosition[32] = "Unknown";  // ユーザーの役職（初期値: "Unknown"）
    char Authority[32] = "View";       // ユーザーの権限（初期値: "View"）
    char password[8] = "";             // ユーザーのパスワード（初期値: ""）

public:
    // コンストラクタ（デフォルトコンストラクタと引数付きコンストラクタ）
    Users();                           // デフォルトコンストラクタ
    Users(const char* user_pandaID);         // Panda ID を指定するコンストラクタ

    // ユーザー情報の検索
    void search_users(const char* users_pandaID);  // Panda ID でユーザーを検索

    // ユーザー情報の取得関数
    const char* get_pandaID();          // Panda ID を返す
    const char* get_username();         // ユーザー名を返す
    const char* get_userdivision();     // ユーザーの部署を返す
    const char* get_userposition();     // ユーザーの役職を返す
    const char* get_authority();        // ユーザーの権限を返す

    // パスワードの判定
    bool judge_password(const char* users_password);  // パスワードが一致するか判定

    // ユーザー情報の設定関数
    bool set_pandaID(char* users_pandaID);           // Panda ID を設定
    bool set_UserName(char* users_username);         // ユーザー名を設定
    bool set_UserDivision(char* users_division);     // ユーザーの部署を設定
    bool set_Position(char* users_position);         // ユーザーの役職を設定
    bool set_authority(char* users_authority);       // ユーザーの権限を設定
    bool set_Password(char* users_password);         // ユーザーのパスワードを設定
};

#endif // USERS_H