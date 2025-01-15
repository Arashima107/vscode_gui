#include "Users.h"
#include "my_functions.h"
#include <Windows.h>
#include <stdio.h>
#include <lmcons.h>

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
    )
    return;
}

const char* Users::get_pandaID(){
    return PandaID;
}

const char* Users::get_username(){
    return UserName;
}

const char* Users::get_userdivision(){
    return UserDivision;
}

const char* Users::get_userposition(){
    return UserPosition;
}

const char* Users::get_authority(){
    printf("Authority : %s\n",Authority);
    return Authority;
}

bool Users::judge_password(const char* users_password){
    return strcmp(Password, users_password) == 0;
}

bool Users::set_pandaID(const char* users_pandaID) {
    if(sizeof(users_pandaID) < sizeof(PandaID)){
        snprintf(PandaID, sizeof(PandaID), "%s",users_pandaID);
        return true;
    }else{
        char countermeasure[128];
        sprintf(countermeasure, "Use less than %d characters, including only alphabet and numbers.", sizeof(PandaID)/size_char);
        error_message("Position : Character count error!", countermeasure);
        return false;
    }
    return false;
}

bool Users::set_UserName(const char* users_username) {
    if(sizeof(users_username) < sizeof(UserName)){
        snprintf(UserName, sizeof(UserName), "%s",users_username);
        return true;
    }else{
        char countermeasure[128];
        sprintf(countermeasure, "Use less than %d characters, including only alphabet and numbers.", sizeof(UserName)/size_char);
        error_message("Position : Character count error!", countermeasure);
        return false;
    }
    return false;
}

bool Users::set_UserDivision(const char* users_division) {
    if(sizeof(users_division) < sizeof(UserDivision)){
        snprintf(UserDivision, sizeof(UserDivision), "%s",users_division);
        return true;
    }else{
        char countermeasure[128];
        sprintf(countermeasure, "Use less than %d characters, including only alphabet and numbers.", sizeof(UserDivision)/size_char);
        error_message("Position : Character count error!", countermeasure);
        return false;
    }
    return false;
}

bool Users::set_Position(const char* users_position) {
    if(sizeof(users_position) < sizeof(UserPosition)){
        snprintf(UserPosition, sizeof(UserPosition), "%s",users_position);
        return true;
    }else{
        char countermeasure[128];
        sprintf(countermeasure, "Use less than %d characters, including only alphabet and numbers.", sizeof(UserPosition)/size_char);
        error_message("Position : Character count error!", countermeasure);
        return false;
    }
    return false;
}

bool Users::set_authority(const char* users_authority) {
    if(sizeof(users_authority) < sizeof(Authority)){
        snprintf(Authority, sizeof(Authority), "%s",users_authority);
        return true;
    }else{
        char countermeasure[128];
        sprintf(countermeasure, "Use less than %d characters, including only alphabet and numbers.", sizeof(Authority)/size_char);
        error_message("Position : Character count error!", countermeasure);
        return false;
    }
}

bool Users::set_Password(const char* users_password) {
    if(sizeof(users_password)/size_char==8){
        snprintf(Password, sizeof(Password), "%s", users_password);
        return true;
    }
    else{
        char countermeasure[128];
        sprintf(countermeasure, "Use %d characters, including only alphabet and numbers.", sizeof(Password)/size_char);
        error_message("Position : Character count error!", countermeasure);
        return false;
    }

    return false;
}