
#include "Majang.h"

#ifndef _PREPROCESS_ONLY
#include <cassert>
#endif

// 没有注释的函数大多都是易于理解的
// 每个函数都可以在Majang.h的声明处找到简要的注释

/*
 * static工具函数区
 */

TILE_T Majang::getTileTypeFromChar(char ch) {
    // 这里是比较固定的，所以直接采用switch
    switch(ch) {
        case 'W': return WANN;
        case 'B': return BING;
        case 'T': return TIAO;
        case 'F': return FENG;
        case 'J': return JIAN;
        case 'H': return HANA;
        case 'D': return DRAW;   // 抽牌
        default:  return NILL;
    }
}

int Majang::parseTileType(const string& strExpr) {
    return getTileTypeFromChar(strExpr[0]);
}

int Majang::parseTileNum(const string& strExpr) {
    return strExpr[1] - '0';
}

TILE Majang::parseTile(const string& strExpr) {
    assert(strExpr.length() == 2);  // 麻将牌只能有二位
    return parseTileType(strExpr) * 10 + parseTileNum(strExpr);
}

/*
 * 构造函数区
 */

Majang::Majang(const Majang &other) : innerType(other.innerType) {}

Majang::Majang(const char *cstrExpr) {
    innerType = getTileTypeFromChar(cstrExpr[0]) * 10 + cstrExpr[1] - '0';
}

// 通过string直接创建Majang
// 比如Majang(H1),创建的即为61
Majang::Majang(const string& strExpr) {
    innerType = parseTile(strExpr);
}

/*
 * 运算符重载区
 */

Majang& Majang::operator = (const Majang& other) {
    if(&other == this) { return *this; } // self-assignment
    innerType = other.innerType;
    return *this;
}

bool Majang::operator == (const Majang &other) {
    return innerType == other.innerType;
}



/*
 * 其他方法区
 */

void Majang::resetFromString(const string& strExpr) {
    innerType = parseTile(strExpr);
}

char Majang::getTileType() const {
    auto tile_t = TILE_T(innerType / 10);
    switch(tile_t) {
        case WANN: return 'W';
        case BING: return 'B';
        case TIAO: return 'T';
        case FENG: return 'F';
        case JIAN: return 'J';
        case HANA: return 'H';
        case DRAW: return 'D';
        default: return 'N';        //? 一般应该不会运行到这里吧……或者可以写个错误处理？
    }
}

int Majang::getTileNum() const {
    return innerType % 10;
}

TILE Majang::getTileInt() const {
    return innerType;
}


bool Majang::isFlowerTile() const {
    return getTileType() == 'H';
}

string Majang::getTileString() const{
    string r="";
    r=r+getTileType()+(char)(getTileNum() + '0');
    return r;
}

Majang Majang::getNxtMajang() const {
    //! 并不保证一定是合法的麻将，这一点在使用时需要注意！一般是在CHI中使用
    return Majang(innerType + 1);
}

Majang Majang::getPrvMajang() const {
    //! 并不保证一定是合法的麻将，这一点在使用时需要注意！一般是在CHI中使用
    return Majang(innerType - 1);
}



