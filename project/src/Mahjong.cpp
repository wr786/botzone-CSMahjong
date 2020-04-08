#include "Mahjong.h"
#include <cassert>

// 没有注释的函数大多都是易于理解的
// 每个函数都可以在Mahjong.h的声明处找到简要的注释

/*
 * static工具函数区
 */

TILE_T Mahjong::getTileTypeFromChar(char ch) {
    // 这里是比较固定的，所以直接采用switch
    switch(ch) {
        case 'W': return WANN;
        case 'B': return BING;
        case 'T': return TIAO;
        case 'F': return FENG;
        case 'J': return JIAN;
        case 'H': return HANA;
        default:  return NILL;
    }
}

int Mahjong::parseTileType(string_view strExpr) {
    return getTileTypeFromChar(strExpr[0]);
}

int Mahjong::parseTileNum(string_view strExpr) {
    return strExpr[1] - '0';
}

TILE Mahjong::parseTile(string_view strExpr) {
    assert(strExpr.length() == 2);  // 麻将牌只能有二位
    return parseTileType(strExpr) * 10 + parseTileNum(strExpr);
}

/*
 * 构造函数区
 */

Mahjong::Mahjong(const Mahjong &other) : innerType(other.innerType) {}

Mahjong::Mahjong(const char *cstrExpr) {
    innerType = getTileTypeFromChar(cstrExpr[0]) * 10 + cstrExpr[1] - '0';
}

// 通过string直接创建Mahjong
// 比如Mahjong(H1),创建的即为61
Mahjong::Mahjong(string_view strExpr) {
    innerType = parseTile(strExpr);
}

/*
 * 运算符重载区
 */

Mahjong& Mahjong::operator = (const Mahjong& other) {
    if(&other == this) { return *this; } // self-assignment
    innerType = other.innerType;
    return *this;
}


/*
 * 其他方法区
 */

void Mahjong::resetFromString(string_view strExpr) {
    innerType = parseTile(strExpr);
}

char Mahjong::getTileType() const {
    switch(auto tile_t = TILE_T(innerType / 10); tile_t) {
        case WANN: return 'W';
        case BING: return 'B';
        case TIAO: return 'T';
        case FENG: return 'F';
        case JIAN: return 'J';
        case HANA: return 'H';
        default: return 'N';        //? 一般应该不会运行到这里吧……或者可以写个错误处理？
    }
}

int Mahjong::getTileNum() const {
    return innerType % 10;
}

bool Mahjong::isFlowerTile() const {
    return getTileType() == 'H';
}


