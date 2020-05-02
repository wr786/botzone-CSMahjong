#ifndef _BOTZONE_ONLINE
#pragma once
#endif

#ifndef MAJANG_H
#define MAJANG_H

#ifndef _PREPROCESS_ONLY
#include <string>
//#include <string_view>
#endif

using namespace std;

// 为了节省内存，用一个int来存麻将的信息
// 由botzone所给的表示法：
// > “W4”表示“四万”，“B6”表示“六筒”，“T8”表示“8条”
// > “F1”～“F4”表示“东南西北”，“J1”～“J3”表示“中发白”，“H1”～“H8”表示“春夏秋冬梅兰竹菊”
// 注意到数字位最多只会出现1~9，所以可以用个位来存数字位
// 而以十位来存牌的种类，其中:（可直接看下面的enum
// 1 => W, 2 => B, 3 => T
// 4 => F, 5 => J, 6 => H
typedef int TILE;
typedef enum TILETYPE {
    NILL = 0,    // 无，一般出现这个就是没初始化过
    WANN,        // 万 1
    BING,        // 筒 2
    TIAO,        // 条 3
    FENG,        // 风 4
    JIAN,        // 箭 5
    HANA,        // 花 6
    DRAW,        // 抽牌，虚牌
} TILE_T;

class Majang {
private:
    TILE innerType;                                                         // 储存麻将对应的类型
public:
    Majang(): innerType(0) {}                                              // 未初始化
    Majang(const Majang& other);                                          // 复制构造函数
    Majang(const char* cstrExpr);                                          // 通过字符串常量创建Majang，！允许隐式转换
    explicit Majang(const int& intExpr): innerType(intExpr) {}             // 通过int直接创建Majang
    explicit Majang(const string& strExpr);                                  // 通过string直接创建Majang

    Majang& operator = (const Majang& other);
    bool operator == (const Majang& other) const;

    void resetFromString(const string& strExpr);                              // 由此将string转换为string_view，提高速度

    static TILE_T getTileTypeFromChar(char ch);                             // 从char得到麻将牌的类型
    static int parseTileType(const string& strExpr);                          // 从string得到麻将牌的类型
    static int parseTileNum(const string& strExpr);                           // 从string得到麻将牌的数字
    static TILE parseTile(const string& strExpr);                             // 从string得到麻将牌（用TILE表示）
    [[nodiscard]] char getTileType() const;                                 // 获得麻将牌的类型
    [[nodiscard]] int getTileNum() const;                                   // 获得麻将牌的数字
    [[nodiscard]] TILE getTileInt() const;                                  // 获得麻将牌的innerType
    [[nodiscard]] bool isFlowerTile() const;                                // 判断当前这张牌是否是花牌
    [[nodiscard]] string getTileString() const;                             // 获取麻将牌的代码(botzone表示法),用于算番器——wym

    [[nodiscard]] Majang getNxtMajang() const;                                  // 获得下一个麻将，比如W2的下一个麻将就是W3
    [[nodiscard]] Majang getPrvMajang() const;                                  // 获得上一个麻将，比如W2的上一个麻将就是W1
};

#endif