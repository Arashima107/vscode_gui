#include <Windows.h>
#include "variable_number.h"

// グローバル変数の定義
HFONT hFont_windowtitle = CreateFont(
    36,                // フォントの高さ（ポイント単位）
    0,                 // フォントの幅（0で高さに合わせて調整）
    0,                 // フォントの傾き（通常は0）
    0,                 // フォントの傾斜角度（通常は0）
    FW_BOLD,           // 太字（FW_BOLD）を指定
    FALSE,             // イタリック体（FALSEでイタリックではない）
    FALSE,             // 下線（FALSEで下線なし）
    FALSE,             // 打ち消し線（FALSEで打ち消し線なし）
    DEFAULT_CHARSET,   // 文字セット（デフォルトの文字セットを指定）
    OUT_DEFAULT_PRECIS,// 精度（デフォルト精度を指定）
    CLIP_DEFAULT_PRECIS,// クリッピング精度（デフォルト）
    DEFAULT_QUALITY,   // 品質（デフォルト）
    DEFAULT_PITCH | FF_SWISS, // ピッチ（デフォルトのピッチ）およびファミリ（FF_SWISSはサンセリフ）
    "Times New Roman"  // 使用するフォント名（ここではTimes New Roman）
);

// グローバル変数の定義
HFONT hFont_others = CreateFont(
    24,                // フォントの高さ（ポイント単位）
    0,                 // フォントの幅（0で高さに合わせて調整）
    0,                 // フォントの傾き（通常は0）
    0,                 // フォントの傾斜角度（通常は0）
    FW_BOLD,           // 太字（FW_BOLD）を指定
    FALSE,             // イタリック体（FALSEでイタリックではない）
    FALSE,             // 下線（FALSEで下線なし）
    FALSE,             // 打ち消し線（FALSEで打ち消し線なし）
    DEFAULT_CHARSET,   // 文字セット（デフォルトの文字セットを指定）
    OUT_DEFAULT_PRECIS,// 精度（デフォルト精度を指定）
    CLIP_DEFAULT_PRECIS,// クリッピング精度（デフォルト）
    DEFAULT_QUALITY,   // 品質（デフォルト）
    DEFAULT_PITCH | FF_SWISS, // ピッチ（デフォルトのピッチ）およびファミリ（FF_SWISSはサンセリフ）
    "Times New Roman"  // 使用するフォント名（ここではTimes New Roman）
);
