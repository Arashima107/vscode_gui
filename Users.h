#ifndef USERS_H
#define USERS_H

#define size_char sizeof(char)

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
    char Password[8] = "";             // ユーザーのパスワード（初期値: ""）
    bool View = true;
    bool Issue_PartsChart = false;
    bool Issue_MaterialChart = false;
    bool Edit_PartsChart_Designer = false;
    bool App_Designer = false;
    bool Edit_PartsChart_Manufacturer = false;
    bool App_Manufacturer = false;
    bool Edit_MaterialChart = false;
    bool Edit_UserInformation = false;
    bool Edit_ApproverInformation = false;

public:
    // コンストラクタ（デフォルトコンストラクタと引数付きコンストラクタ）
    Users();                           // デフォルトコンストラクタ
    Users(const char* user_pandaID);         // Panda ID を指定するコンストラクタ

    // ユーザー情報の検索
    void search_users();  // Panda ID でユーザーを検索
    void search_users(const char* users_pandaID);  // Panda ID でユーザーを検索
    void update_users(bool Edit_UserInfomation, bool Edit_ApproverInformation);

    // ユーザー情報の取得関数
    const char* get_pandaID();          // Panda ID を返す
    const char* get_username();         // ユーザー名を返す
    const char* get_userdivision();     // ユーザーの部署を返す
    const char* get_userposition();     // ユーザーの役職を返す
    const char* get_authority();        // ユーザーの権限を返す
    bool get_view();                     // View 権限を返す
    bool get_issue_partsChart();         // Issue_PartsChart 権限を返す
    bool get_issue_materialChart();      // Issue_MaterialChart 権限を返す
    bool get_edit_partsChart_designer(); // Edit_PartsChart_Designer 権限を返す
    bool get_edit_partsChart_manufacturer(); // Edit_PartsChart_Manufacturer 権限を返す
    bool get_edit_materialChart();       // Edit_MaterialChart 権限を返す
    bool get_edit_userInformation();     // Edit_UserInformation 権限を返す
    bool get_edit_approverInformation(); // Edit_ApproverInformation 権限を返す

    // パスワードの判定
    bool judge_password(const char* users_password);  // パスワードが一致するか判定

    // ユーザー情報の設定関数
    bool authority_set();
    bool set_pandaID(const char* users_pandaID);           // Panda ID を設定
    bool set_UserName(const char* users_username);         // ユーザー名を設定
    bool set_UserDivision(const char* users_division);     // ユーザーの部署を設定
    bool set_Position(const char* users_position);         // ユーザーの役職を設定
    bool set_authority(const char* users_authority);       // ユーザーの権限を設定
    bool set_Password(const char* users_password);         // ユーザーのパスワードを設定

    void user_error_message(const char* error_type, int char_count);

};

#endif // USERS_H