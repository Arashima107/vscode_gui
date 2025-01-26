#ifndef PARTS_H
#define PARTS_H

// Partsクラスの宣言
class Parts {
private:
    // データベースパス
    char db_path[256] = "C:\\users\\water\\desktop\\vscode_gui\\??";
    
    // 各種部品情報のメンバ変数
    int id = -1;                           // 部品ID
    char BusinessDiv = 0;                  // ビジネス区分
    char Type = 0;                         // 部品タイプ (0: Assembly, 1: Mold, 2: SheetMetal, 3: TurnedParts)
    char PartsNo[32] = "";                // 部品番号
    char PartsName[64] = "";              // 部品名
    char Rev = 1;                          // リビジョン番号
    char Product[32] = "";                // 製品名
    char Unit[32] = "";                   // 単位
    char Quantity = 1;                     // 数量
    char MassPro_BP[64] = "";            // 大量生産のBP
    char MassPro_Location[16] = "";      // 大量生産の場所
    char MoldShop_BP[64] = "";           // 金型ショップのBP
    char MoldShop_BP[16] = "";           // 金型ショップの場所（重複に注意）
    char Material[32] = "";              // 材料名
    char MaterialGrade[32] = "";         // 材料のグレード
    char MaterialColor[16] = "";         // 材料の色
    double Thickness = -1.0;              // 厚さ
    double ShrinkageRatio = -1.0;         // 収縮率
    double PartsWeight = -1.0;            // 部品重量

    // マーキングに関するフラグ
    bool PartsNoMarking = false;          // 部品番号マーキング
    bool CavNoMarking = false;            // キャビティ番号マーキング
    bool MaterialMarking = false;         // 材料マーキング
    bool DateMarking = false;             // 日付マーキング

    // その他の情報
    char MoldNo = 'A';                    // 金型番号
    unsigned short int MachineSize = 0;   // 機械サイズ

    // 部品の親子関係
    char child_PartsNo[32];               // 子部品番号
    char Parent_PartsNo[32];              // 親部品番号

public:
    // コンストラクタ
    Parts();                              // デフォルトコンストラクタ
    Parts(char *partsno);                 // 部品番号を指定するコンストラクタ

    // 部品を検索するメソッド
    bool search_part(char *partsno);      // 指定した部品番号で部品を検索

    // 部品情報を更新するメソッド
    bool update_part();                   // 部品情報を更新

    // 外部からメンバーを設定する関数
    bool set_id(int new_id);
    bool set_BusinessDiv(char new_BusinessDiv);
    bool set_Type(char new_Type);
    bool set_PartsNo(const char* new_PartsNo);
    bool set_PartsName(const char* new_PartsName);
    bool set_Rev(char new_Rev);
    bool set_Product(const char* new_Product);
    bool set_Unit(const char* new_Unit);
    bool set_Quantity(char new_Quantity);
    bool set_MassPro_BP(const char* new_MassPro_BP);
    bool set_MassPro_Location(const char* new_MassPro_Location);
    bool set_MoldShop_BP(const char* new_MoldShop_BP);
    bool set_Material(const char* new_Material);
    bool set_MaterialGrade(const char* new_MaterialGrade);
    bool set_MaterialColor(const char* new_MaterialColor);
    bool set_Thickness(double new_Thickness);
    bool set_ShrinkageRatio(double new_ShrinkageRatio);
    bool set_PartsWeight(double new_PartsWeight);
    bool set_PartsNoMarking(bool new_PartsNoMarking);
    bool set_CavNoMarking(bool new_CavNoMarking);
    bool set_MaterialMarking(bool new_MaterialMarking);
    bool set_DateMarking(bool new_DateMarking);
    bool set_MoldNo(char new_MoldNo);
    bool set_MachineSize(unsigned short int new_MachineSize);
    bool set_child_PartsNo(const char* new_child_PartsNo);
    bool set_Parent_PartsNo(const char* new_Parent_PartsNo);
};

#endif
