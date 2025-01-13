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

    search_users(userid);
    return;
}

Users::Users(const char* user_pandaID){
    search_users(user_pandaID);
    return;
}

void Users::search_users(const char* users_pandaID) {
    
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
    return Authority;
}

bool Users::judge_password(const char* users_password){
    return strcmp(password, users_password) == 0;
}

bool Users::set_pandaID(char* users_pandaID) {
    sprintf(PandaID,"%s",users_pandaID);
    return true;
}

bool Users::set_UserName(char* users_username) {
    sprintf(UserName,"%s",users_username);
    return true;
}

bool Users::set_UserDivision(char* users_division) {
    sprintf(UserDivision,"%s",users_division);
    return true;
}

bool Users::set_Position(char* users_position) {
    sprintf(UserPosition,"%s", users_position);
    return true;
}

bool Users::set_authority(char* users_authority) {
    sprintf(Authority,"%s",users_authority);
    return true;
}

bool Users::set_Password(char* users_password) {
    if(sizeof(users_password)/sizeof(char)==8){
        sprintf(password, "%s", users_password);
        return true;
    }
    return true;
    
}