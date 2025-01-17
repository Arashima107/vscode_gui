#include "my_functions.h"

/*
void error_message(DWORD errorCode, char* error_type, char* error_detail, char* counter_measure){
    char messageBuffer[512];

    // エラーメッセージを取得
    FormatMessage(
        FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        errorCode,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        messageBuffer,
        sizeof(messageBuffer),
        NULL
    );

    MessageBoxEx(
        nullptr,
        messageBuffer,
        "Error",
        MB_ICONERROR | MB_OK
    )
}
void error_message(DWORD errorCode, char* error_type, char* counter_measure);
*/

void error_message(const char* error_type, const char* error_detail, const char* counter_measure) {
    char messageBuffer[512] = "Error : ";

    // 安全な文字列結合
    strncat(messageBuffer, error_type, sizeof(messageBuffer) - strlen(messageBuffer) - 1);
    strncat(messageBuffer, "\nDetail : ", sizeof(messageBuffer) - strlen(messageBuffer) - 1);
    strncat(messageBuffer, error_detail, sizeof(messageBuffer) - strlen(messageBuffer) - 1);
    strncat(messageBuffer, "\n\nCountermeasure : ", sizeof(messageBuffer) - strlen(messageBuffer) - 1);
    strncat(messageBuffer, counter_measure, sizeof(messageBuffer) - strlen(messageBuffer) - 1);

    // ワイド文字への変換
    wchar_t wMessageBuffer[512];
    mbstowcs(wMessageBuffer, messageBuffer, 512);

    // メッセージボックスを表示
    MessageBoxEx(
        NULL,                    // 親ウィンドウのハンドル（NULLで親なし）
        messageBuffer,          // ワイド文字列のメッセージ
        "Error",                // ワイド文字列のタイトル
        MB_ICONERROR | MB_OK,    // アイコンとボタンのスタイル
        0                        // 言語ID（デフォルト）
    );
}

void error_message(const char* error_type, const char* counter_measure){
    char messageBuffer[512] = "Error : ";

    // 安全な文字列結合
    strncat(messageBuffer, error_type, sizeof(messageBuffer) - strlen(messageBuffer) - 1);
    strncat(messageBuffer, "\n\nCountermeasure : ", sizeof(messageBuffer) - strlen(messageBuffer) - 1);
    strncat(messageBuffer, counter_measure, sizeof(messageBuffer) - strlen(messageBuffer) - 1);

    // ワイド文字への変換
    wchar_t wMessageBuffer[512];
    mbstowcs(wMessageBuffer, messageBuffer, 512);

    // メッセージボックスを表示
    MessageBoxEx(
        NULL,                    // 親ウィンドウのハンドル（NULLで親なし）
        messageBuffer,          // ワイド文字列のメッセージ
        "Error",                // ワイド文字列のタイトル
        MB_ICONERROR | MB_OK,    // アイコンとボタンのスタイル
        0                        // 言語ID（デフォルト）
    );
}

void error_message(const char* error_type){
    char messageBuffer[128] = "Error : ";

    // 安全な文字列結合
    strncat(messageBuffer, error_type, sizeof(messageBuffer) - strlen(messageBuffer) - 1);

    // ワイド文字への変換
    wchar_t wMessageBuffer[128];
    mbstowcs(wMessageBuffer, messageBuffer, 128);

    // メッセージボックスを表示
    MessageBoxEx(
        NULL,                    // 親ウィンドウのハンドル（NULLで親なし）
        messageBuffer,          // ワイド文字列のメッセージ
        "Error",                // ワイド文字列のタイトル
        MB_ICONERROR | MB_OK,    // アイコンとボタンのスタイル
        0                        // 言語ID（デフォルト）
    );
}