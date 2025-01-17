#include "Users.h"
#include "my_functions.h"
#include <Windows.h>
#include <stdio.h>
#include <lmcons.h>

/**
 * @brief Usersクラスのコンストラクタ
 *
 * このコンストラクタは、Windows APIを使用して現在のユーザー名を取得し、
 * それをPandaIDメンバ変数に設定します。
 * 
 * @note ユーザー名の取得に失敗した場合、エラーメッセージを表示し、処理を終了します。
 */
Users::Users(){
    char userid[UNLEN + 1]; // Windows APIの最大ユーザー名長に基づいたバッファ
    DWORD userid_len = sizeof(userid); // バッファのサイズ

    // バッファを初期化
    memset(userid, 0, sizeof(userid));

    // GetUserName関数を使用してユーザー名を取得
    if (GetUserName(userid, &userid_len)) {
        snprintf(PandaID, sizeof(PandaID), "%s", userid);
    } else {
        printf("Error: can't get user name!");
        //error_message("Windows User Error!");
        return;
    }

    //search_users(userid);
    return;
}

Users::Users(const char* user_pandaID){
    search_users(user_pandaID);
    return;
}

/**
 * @brief 指定されたPanda IDに基づいてユーザー情報を検索します。
 * 
 * この関数はユーザー情報フィールドをデフォルト値で初期化し、
 * 指定されたPanda IDを使用してそれらを設定しようとします。
 * フィールドには以下が含まれます:
 * - ユーザー名
 * - ユーザーの部署
 * - ユーザーの役職
 * - ユーザーの権限
 * - ユーザーのパスワード
 * 
 * @param users_pandaID 検索するユーザーのPanda ID。
 * 
 * @return void
 */
void Users::search_users(const char* users_pandaID) {
    
    char users_username[32];    // ユーザー名（初期値: "Unknown"）
    char users_userdivision[128]; // ユーザーの部署（初期値: "Unknown"）
    char users_userposition[32];  // ユーザーの役職（初期値: "Unknown"）
    char users_authority[32];       // ユーザーの権限（初期値: "View"）
    char users_password[8];             // ユーザーのパスワード（初期値: ""）

    if(set_pandaID(users_pandaID) &&
        set_UserName(users_username) &&
        set_UserDivision(users_userdivision) &&
        set_Position(users_userposition) &&
        set_authority(users_authority) && 
        set_Password(users_password)
    ){
        
    }
    return;
}

void Users::search_users() {
    
    char users_username[32] = "Unknown";    // ユーザー名（初期値: "Unknown"）
    char users_userdivision[128] = "Unknown"; // ユーザーの部署（初期値: "Unknown"）
    char users_userposition[32] = "General";  // ユーザーの役職（初期値: "Unknown"）
    char users_authority[32] = "View";       // ユーザーの権限（初期値: "View"）
    char users_password[8] = "";             // ユーザーのパスワード（初期値: ""）

    if( set_UserName(users_username) &&
        set_UserDivision(users_userdivision) &&
        set_Position(users_userposition) &&
        set_authority(users_authority) && 
        set_Password(users_password)
    )
    return;
}

void Users::update_users(bool Edit_UserInfomation, bool Edit_ApproverInformation){
    return;
}

/**
 * @brief Panda IDを取得します。
 * 
 * @return const char* Panda ID
 */
const char* Users::get_pandaID(){
    return PandaID;
}

/**
 * @brief ユーザー名を取得します。
 * 
 * @return const char* ユーザー名
 */
const char* Users::get_username(){
    return UserName;
}

/**
 * @brief ユーザーの部署を取得します。
 * 
 * @return const char* ユーザーの部署
 */
const char* Users::get_userdivision(){
    return UserDivision;
}

/**
 * @brief ユーザーの役職を取得します。
 * 
 * @return const char* ユーザーの役職
 */
const char* Users::get_userposition(){
    return UserPosition;
}

/**
 * @brief ユーザーの権限を取得します。
 * 
 * @return const char* ユーザーの権限
 */
const char* Users::get_authority(){
    printf("Authority : %s\n",Authority);
    return Authority;
}

/**
 * @brief ユーザーがView権限を持っているかを取得します。
 * 
 * @return true ユーザーがView権限を持っている場合
 * @return false ユーザーがView権限を持っていない場合
 */
bool Users::get_view(){
    return View;
}

/**
 * @brief ユーザーが部品表の発行権限を持っているかを取得します。
 * 
 * @return true ユーザーが部品表の発行権限を持っている場合
 * @return false ユーザーが部品表の発行権限を持っていない場合
 */
bool Users::get_issue_partsChart(){
    return Issue_PartsChart;
}

/**
 * @brief ユーザーが材料表の発行権限を持っているかを取得します。
 * 
 * @return true ユーザーが材料表の発行権限を持っている場合
 * @return false ユーザーが材料表の発行権限を持っていない場合
 */
bool Users::get_issue_materialChart(){
    return Issue_MaterialChart;
}

/**
 * @brief ユーザーが設計者として部品表を編集する権限を持っているかを取得します。
 * 
 * @return true ユーザーが設計者として部品表を編集する権限を持っている場合
 * @return false ユーザーが設計者として部品表を編集する権限を持っていない場合
 */
bool Users::get_edit_partsChart_designer(){
    return Edit_PartsChart_Designer;
}

/**
 * @brief ユーザーが製造者として部品表を編集する権限を持っているかを取得します。
 * 
 * @return true ユーザーが製造者として部品表を編集する権限を持っている場合
 * @return false ユーザーが製造者として部品表を編集する権限を持っていない場合
 */
bool Users::get_edit_partsChart_manufacturer(){
    return Edit_PartsChart_Manufacturer;
}

/**
 * @brief ユーザーが材料表を編集する権限を持っているかを取得します。
 * 
 * @return true ユーザーが材料表を編集する権限を持っている場合
 * @return false ユーザーが材料表を編集する権限を持っていない場合
 */
bool Users::get_edit_materialChart(){
    return Edit_MaterialChart;
}

/**
 * @brief ユーザーがユーザー情報を編集する権限を持っているかを取得します。
 * 
 * @return true ユーザーがユーザー情報を編集する権限を持っている場合
 * @return false ユーザーがユーザー情報を編集する権限を持っていない場合
 */
bool Users::get_edit_userInformation(){
    return Edit_UserInformation;
}

/**
 * @brief ユーザーが承認者情報を編集する権限を持っているかを取得します。
 * 
 * @return true ユーザーが承認者情報を編集する権限を持っている場合
 * @return false ユーザーが承認者情報を編集する権限を持っていない場合
 */
bool Users::get_edit_approverInformation(){
    return Edit_ApproverInformation;
}

/**
 * @brief パスワードが一致するかを判定します。
 * 
 * @param users_password 確認するパスワード
 * @return true パスワードが一致する場合
 * @return false パスワードが一致しない場合
 */
bool Users::judge_password(const char* users_password){
    return strcmp(Password, users_password) == 0;
}

bool Users::authority_set(){
    if(strcmp(Authority, "View")==0){
        View = true;
        Issue_PartsChart = false;
        Issue_MaterialChart = false;
        Edit_PartsChart_Designer = false;
        App_Designer = false;
        Edit_PartsChart_Manufacturer = false;
        App_Manufacturer = false;
        Edit_MaterialChart = false;
        Edit_UserInformation = false;
        Edit_ApproverInformation = false;
        return true;
    }else if(strcmp(Authority, "G_Designer")==0){
        View = true;
        Issue_PartsChart = true;
        Issue_MaterialChart = false;
        App_Designer = false;
        Edit_PartsChart_Manufacturer = false;
        App_Manufacturer = false;
        Edit_MaterialChart = false;
        Edit_UserInformation = false;
        Edit_ApproverInformation = false;
        return true;
    }else if(strcmp(Authority, "M_Designer")==0){
        View = true;
        Issue_PartsChart = true;
        Issue_MaterialChart = false;
        Edit_PartsChart_Designer = true;
        App_Designer = true;
        Edit_PartsChart_Manufacturer = false;
        App_Manufacturer = false;
        Edit_MaterialChart = false;
        Edit_UserInformation = true;
        Edit_ApproverInformation = false;
        return true;
    }else if(strcmp(Authority, "G_Manufacturer")==0){
        View = true;
        Issue_PartsChart = true;
        Issue_MaterialChart = true;
        Edit_PartsChart_Designer = false;
        App_Designer = false;
        Edit_PartsChart_Manufacturer = true;
        App_Manufacturer = false;
        Edit_MaterialChart = true;
        Edit_UserInformation = false;
        Edit_ApproverInformation = false;
        return true;
    }else if(strcmp(Authority, "M_Manufacturer")==0){
        View = true;
        Issue_PartsChart = true;
        Issue_MaterialChart = true;
        Edit_PartsChart_Designer = true;
        App_Designer = false;
        Edit_PartsChart_Manufacturer = true;
        App_Manufacturer = true;
        Edit_MaterialChart = true;
        Edit_UserInformation = true;
        Edit_ApproverInformation = true;
        return true;
    }else if(strcmp(Authority, "Administrator")==0){
        View = true;
        Issue_PartsChart = true;
        Issue_MaterialChart = true;
        Edit_PartsChart_Designer = true;
        App_Designer = true;
        Edit_PartsChart_Manufacturer = true;
        App_Manufacturer = true;
        Edit_MaterialChart = true;
        Edit_UserInformation = true;
        Edit_ApproverInformation = true;
        return true;
    }

    return false;
}

/**
 * @brief Panda IDを設定します。
 * 
 * @param users_pandaID 設定するPanda ID
 * @return true 設定が成功した場合
 * @return false 設定が失敗した場合
 */
bool Users::set_pandaID(const char* users_pandaID) {
    if(sizeof(users_pandaID) < sizeof(PandaID)){
        snprintf(PandaID, sizeof(PandaID), "%s",users_pandaID);
        return true;
    }else{
        user_error_message("Panda-ID",sizeof(PandaID)/size_char);
        return false;
    }
    return false;
}

/**
 * @brief ユーザー名を設定します。
 * 
 * @param users_username 設定するユーザー名
 * @return true 設定が成功した場合
 * @return false 設定が失敗した場合
 */
bool Users::set_UserName(const char* users_username) {
    if(sizeof(users_username) < sizeof(UserName)){
        snprintf(UserName, sizeof(UserName), "%s",users_username);
        return true;
    }else{
        user_error_message("User Name",sizeof(UserName)/size_char);
        return false;
    }
    return false;
}

/**
 * @brief ユーザーの部署を設定します。
 * 
 * @param users_division 設定する部署
 * @return true 設定が成功した場合
 * @return false 設定が失敗した場合
 */
bool Users::set_UserDivision(const char* users_division) {
    if(sizeof(users_division) < sizeof(UserDivision)){
        snprintf(UserDivision, sizeof(UserDivision), "%s",users_division);
        return true;
    }else{
        user_error_message("User Division",sizeof(UserDivision)/size_char);
        return false;
    }
    return false;
}

/**
 * @brief ユーザーの役職を設定します。
 * 
 * @param users_position 設定する役職
 * @return true 設定が成功した場合
 * @return false 設定が失敗した場合
 */
bool Users::set_Position(const char* users_position) {
    if(sizeof(users_position) < sizeof(UserPosition)){
        snprintf(UserPosition, sizeof(UserPosition), "%s",users_position);
        return true;
    }else{
        user_error_message("Position",sizeof(UserPosition)/size_char);
        return false;
    }
    return false;
}

/**
 * @brief ユーザーの権限を設定します。
 * 
 * @param users_authority 設定する権限
 * @return true 設定が成功した場合
 * @return false 設定が失敗した場合
 */
bool Users::set_authority(const char* users_authority) {
    unsigned char num=0;
    
    num+=(strcmp(users_authority, "View")==0);
    num+=(strcmp(users_authority, "G_Designer")==0);
    num+=(strcmp(users_authority, "M_Designer")==0);
    num+=(strcmp(users_authority, "G_Manufacturer")==0);
    num+=(strcmp(users_authority, "M_Manufacturer")==0);
    num+=(strcmp(users_authority, "Administrator")==0);
    
    if(sizeof(users_authority) < sizeof(Authority) && num == 1){
        snprintf(Authority, sizeof(Authority), "%s",users_authority);
        return true;
    }else{
        user_error_message("Authority",sizeof(Authority)/size_char);
        return false;
    }
}

/**
 * @brief ユーザーのパスワードを設定します。
 * 
 * @param users_password 設定するパスワード
 * @return true 設定が成功した場合
 * @return false 設定が失敗した場合
 */
bool Users::set_Password(const char* users_password) {
    if(sizeof(users_password)/size_char==8){
        snprintf(Password, sizeof(Password), "%s", users_password);
        return true;
    }
    else{
        user_error_message("Password",sizeof(Password)/size_char);
        return false;
    }

    return false;
}

void Users::user_error_message(const char* error_type, int char_count){
    char error_type_message[128];
    char countermeasure[128];
    printf("error:%s\n",error_type);
    printf("counter:%d\n",char_count);
    snprintf(error_type_message, sizeof(error_type_message), "%s: Character count error!", error_type);
    sprintf(countermeasure, "Use %d characters, including only alphabet and numbers.", char_count);
    error_message(error_type_message, countermeasure);
}