/* インクルードガード */
#pragma once
#include "MdWBGTMonitor.h"
#include "M5All-In-One-Gadget.h"

class MdWBGTMonitor // classの定義
{
private: // privateはクラス内からしかアクセスできない

public: // publicはどこからでもアクセス可能
void init();

void getWBGT(double* temperature, double* humidity, WbgtIndex* index);
// WbgtIndex* index→WbgtIndex型の変数indexはアドレスの情報を格納する。データそのものはない。
};
