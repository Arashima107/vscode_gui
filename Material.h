#ifndef MATERIAL_H
#define MATERIAL_H

class Material{
private:
    char db_path[256] = "C:\\users\\water\\desktop\\vscode_gui\\??";
    
    short int id = -1;
    char Type = 0;  // 1: Resin, 2: Metal, 3:TurnedParts
    char MaterialName[32] = "";
    char MaterialGrade[32] = "";
    char MaterialColor[128][16];
    double Thickness = -1.0;
    double ShrinkageRatio = -1.0;
    double MassDensity = -1.0;

public:
    Material();
};

#endif