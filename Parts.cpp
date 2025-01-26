#include "Parts.h"
#include <typeinfo>

Parts::Parts(){

}

Parts::Parts(char *partsno){
    search_part(partsno);
}

bool Parts::search_part(char *partsno){
    return false;
}

bool Parts::update_part(){
    return false;
}

// 外部からメンバーを設定する関数
bool Parts::set_id(int new_id){
    if(typeid(new_id)==typeid(int)){
        id = new_id;
        return true;
    }else
        return false;
}

bool Parts::set_BusinessDiv(char new_BusinessDiv){
    
}

void set_Type(char new_Type);
void set_PartsNo(const char* new_PartsNo);
void set_PartsName(const char* new_PartsName);
void set_Rev(char new_Rev);
void set_Product(const char* new_Product);
void set_Unit(const char* new_Unit);
void set_Quantity(char new_Quantity);
void set_MassPro_BP(const char* new_MassPro_BP);
void set_MassPro_Location(const char* new_MassPro_Location);
void set_MoldShop_BP(const char* new_MoldShop_BP);
void set_Material(const char* new_Material);
void set_MaterialGrade(const char* new_MaterialGrade);
void set_MaterialColor(const char* new_MaterialColor);
void set_Thickness(double new_Thickness);
void set_ShrinkageRatio(double new_ShrinkageRatio);
void set_PartsWeight(double new_PartsWeight);
void set_PartsNoMarking(bool new_PartsNoMarking);
void set_CavNoMarking(bool new_CavNoMarking);
void set_MaterialMarking(bool new_MaterialMarking);
void set_DateMarking(bool new_DateMarking);
void set_MoldNo(char new_MoldNo);
void set_MachineSize(unsigned short int new_MachineSize);
void set_child_PartsNo(const char* new_child_PartsNo);
void set_Parent_PartsNo(const char* new_Parent_PartsNo);