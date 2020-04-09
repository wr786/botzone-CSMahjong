#pragma once

#ifndef MAHJONG_H
#define MAHJONG_H

#include <string>
#include <string_view>

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
    WANN,        // 万
    BING,        // 筒
    TIAO,        // 条
    FENG,        // 风
    JIAN,        // 箭
    HANA,        // 花
    TILE_T_SIZE  // 以便循环使用
} TILE_T;

class Mahjong {
private:
    TILE innerType;                                                         // 储存麻将对应的类型
public:
    Mahjong(): innerType(0) {}                                              // 未初始化
    Mahjong(const Mahjong& other);                                          // 复制构造函数
    Mahjong(const char* cstrExpr);                                          // 通过字符串常量创建Mahjong，！允许隐式转换
    explicit Mahjong(string_view strExpr);                                  // 通过string直接创建Mahjong

    Mahjong& operator = (const Mahjong& other);

    void resetFromString(string_view strExpr);                              // 由此将string转换为string_view，提高速度

    static TILE_T getTileTypeFromChar(char ch);                             // 从char得到麻将牌的类型
    static int parseTileType(string_view strExpr);                          // 从string得到麻将牌的类型
    static int parseTileNum(string_view strExpr);                           // 从string得到麻将牌的数字
    static TILE parseTile(string_view strExpr);                             // 从string得到麻将牌（用TILE表示）
    [[nodiscard]] char getTileType() const;                                 // 获得麻将牌的类型
    [[nodiscard]] int getTileNum() const;                                   // 获得麻将牌的数字
    [[nodiscard]] bool isFlowerTile() const;                                // 判断当前这张牌是否是花牌

    //todo 这里应有不少实用的方法……有空再写（或者有个人来写也挺好的
};

#endif