#ifndef PARTS_H
#define PARTS_H

class Parts{
private:
    char db_path[256] = "C:\\users\\water\\desktop\\vscode_gui\\??";
    
    int id = -1;
    char BusinessDiv = 0;
    char Type = 0;  // 0: Assembly 1: Mold, 2: SheetMetal, 3:TurnedParts
    char PartsNo[32] = "";
    char PartsName[64] = "";
    char Rev = 1;
    char Product[32] = "";
    char Unit[32] = "";
    char Quantity = 1;
    char MassPro_BP[64] = "";
    char MassPro_Location[16] = "";
    char MoldShop_BP[64] = "";
    char MoldShop_BP[16] = "";
    char Material[32] = "";
    char MaterialGrade[32] = "";
    char MaterialColor[16] = "";
    double Thickness = -1.0;
    double ShrinkageRatio = -1.0;
    double PartsWeight = -1.0;
    bool PartsNoMarking = false;
    bool CavNoMarking = false;
    bool MaterialMarking = false;
    bool DateMarking = false;
    char MoldNo = 'A';

public:
    Parts();
};

#endif