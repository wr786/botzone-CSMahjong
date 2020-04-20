#ifdef _MSC_VER
#pragma warning(disable:4819)
#endif

#ifdef _BOTZONE_ONLINE
#include "MahjongGB/MahjongGB.h"
#endif


/*** Start of inlined file: Majang.h ***/
#ifndef _BOTZONE_ONLINE
#pragma once
#endif

#ifndef MAJANG_H
#define MAJANG_H

#include <string>
//#include <string_view>

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
	TILE_T_SIZE  // 以便循环使用
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
	bool operator == (const Majang& other);

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
/*** End of inlined file: Majang.h ***/


/*** Start of inlined file: Majang.cpp ***/

/*** Start of inlined file: Majang.h ***/
#ifndef _BOTZONE_ONLINE
#pragma once
#endif

#ifndef MAJANG_H
#define MAJANG_H

#include <string>
//#include <string_view>

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
	TILE_T_SIZE  // 以便循环使用
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
	bool operator == (const Majang& other);

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
/*** End of inlined file: Majang.h ***/

#include <cassert>

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

/*** End of inlined file: Majang.cpp ***/


/*** Start of inlined file: StateContainer.h ***/
#ifndef _BOTZONE_ONLINE
#pragma once
#endif

#ifndef STATECONTAINER_H
#define STATECONTAINER_H

#include <valarray>
#include <vector>
#include <algorithm>

// 使用Majang类

/*** Start of inlined file: Majang.h ***/
#ifndef _BOTZONE_ONLINE
#pragma once
#endif

#ifndef MAJANG_H
#define MAJANG_H

#include <string>
//#include <string_view>

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
	TILE_T_SIZE  // 以便循环使用
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
	bool operator == (const Majang& other);

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
/*** End of inlined file: Majang.h ***/


using namespace std;

//typedef pair<char, int> Majang; // 所有麻将牌均以“大写字母+数字”组合表示

// 从题目的输入request的0~9可知，在输入环节我们可以得到的信息有：
// 0. 我们的位置、当前的风圈
// 1. 我们的起始手牌、四名玩家各人的花牌
// 2. 当前是哪个玩家的回合（可以通过各个摸牌操作来判断）
// 3. 各个玩家的鸣牌（可以通过吃碰杠来获得）
// 4. "弃牌堆"中的牌（被打出之后没有被吃碰杠、点炮的牌）

// 用于存放当前的局面
// 由于该部分很多函数很简单，就不费笔墨写注释了，也没有将实现分离到cpp中
class StateContainer {
private:
	int curPosition;                    // “我们”所处的位置，0是庄家。同样也可以在博弈树节点使用以判断敌我
	int curTurnPlayer;                  // 当前是哪个玩家的回合
//    valarray<Majang> inHand;           // 用于存储手牌
//    valarray<Majang> flowerTilesOf[4]; // 用于存储花牌，分别对应4个玩家
//    valarray<Majang> chiOf[4];         // 某个玩家鸣牌中的所有“吃”,存放中间那张牌即可
//    valarray<Majang> pengOf[4];        // 某个玩家鸣牌中的所有“碰”，存放其中一张即可（因为三张一模一样
//    valarray<Majang> gangOf[4];        // 某个玩家鸣牌中的所有“杠”，存放其中一张即可
////    valarray<Majang> discards;       // 用于存放弃牌堆
//    valarray<Majang> tilePlayedOf[4];  // 用于记录某个玩家曾经都打出过哪些卡牌，无论是否被吃、碰还是杠
	vector<Majang> inHand;           // 用于存储手牌
	vector<Majang> flowerTilesOf[4]; // 用于存储花牌，分别对应4个玩家
	vector<Majang> chiOf[4];         // 某个玩家鸣牌中的所有“吃”,存放中间那张牌即可
	vector<Majang> pengOf[4];        // 某个玩家鸣牌中的所有“碰”，存放其中一张即可（因为三张一模一样
	vector<Majang> gangOf[4];        // 某个玩家鸣牌中的所有“杠”，存放其中一张即可
//    valarray<Majang> discards;       // 用于存放弃牌堆
	vector<Majang> tilePlayedOf[4];  // 用于记录某个玩家曾经都打出过哪些卡牌，无论是否被吃、碰还是杠
	int secretGangCntOf[4];           // 用于记录"暗杠"的数量，通过输入数据我们可以判断出某名玩家有几个暗杠，但我们不知道暗杠的是什么
	// 下面这个lastPlayed还没确定好到底怎么用，想好的时候再改吧
	Majang lastPlayed;                 // 用于记录上个回合被打出的麻将牌，如果不是麻将牌类型的话则为其他操作（具体见RequestReader::readRequest
	int tileLeft[70];                   // 用于记录各种类型牌所剩余的没出现的数量
	int totalLeft;                      // 没出现过的牌的总数（初始144）
	int inHandCnt[4];                   // 用于记录四名玩家的手牌数量(虽然不知道有没有用)

public:
	static int quan;                    // 圈风。因为在一把botzone游戏中，只考虑国标麻将的一局游戏，所以圈风应该是不变的
	static int lastRequest;             // 上回合的操作,用于算番器的isGANG,采取博弈算法时应换一种存储方式

	explicit StateContainer(int curP=0, int curT=0);
	StateContainer(const StateContainer& other);

//    [[nodiscard]] valarray<Majang>& getInHand();                               // 获取手牌
//    [[nodiscard]] valarray<Majang>& getFlowerTilesOf(int idx);                 // 获取花牌
//    [[nodiscard]] valarray<Majang>& getChiOf(int idx);                         // 获取鸣牌中的“吃"
//    [[nodiscard]] valarray<Majang>& getPengOf(int idx);                        // 获取鸣牌中的“碰"
//    [[nodiscard]] valarray<Majang>& getGangOf(int idx);                        // 获取鸣牌中的“杠”
////    [[nodiscard]] valarray<Majang>& getDiscards();                             // 获取弃牌堆
//    [[nodiscard]] valarray<Majang>& getTilePlayedOf(int idx);                  // 获取某名玩家打过的所有牌
//
//    [[nodiscard]] const valarray<Majang>& getInHand() const;                   //  获取手牌的常引用，下同上
//    [[nodiscard]] const valarray<Majang>& getFlowerTilesOf(int idx) const;
//    [[nodiscard]] const valarray<Majang>& getChiOf(int idx) const;
//    [[nodiscard]] const valarray<Majang>& getPengOf(int idx) const;
//    [[nodiscard]] const valarray<Majang>& getGangOf(int idx) const;
////    [[nodiscard]] const valarray<Majang>& getDiscards() const;
//    [[nodiscard]] const valarray<Majang>& getTilePlayedOf(int idx) const;

	[[nodiscard]] vector<Majang>& getInHand();                               // 获取手牌
	[[nodiscard]] vector<Majang>& getFlowerTilesOf(int idx);                 // 获取花牌
	[[nodiscard]] vector<Majang>& getChiOf(int idx);                         // 获取鸣牌中的“吃"
	[[nodiscard]] vector<Majang>& getPengOf(int idx);                        // 获取鸣牌中的“碰"
	[[nodiscard]] vector<Majang>& getGangOf(int idx);                        // 获取鸣牌中的“杠”
	[[nodiscard]] vector<Majang>& getTilePlayedOf(int idx);                  // 获取某名玩家打过的所有牌

	[[nodiscard]] const vector<Majang>& getInHand() const;                   //  获取手牌的常引用，下同上
	[[nodiscard]] const vector<Majang>& getFlowerTilesOf(int idx) const;
	[[nodiscard]] const vector<Majang>& getChiOf(int idx) const;
	[[nodiscard]] const vector<Majang>& getPengOf(int idx) const;
	[[nodiscard]] const vector<Majang>& getGangOf(int idx) const;
	[[nodiscard]] const vector<Majang>& getTilePlayedOf(int idx) const;

	void decTileLeft(int idx);                                                  // 在减少idx对应的牌的数量的同时，减少总数的数量
	void decTileLeft(Majang mj);                                               // 同上
	[[nodiscard]] const int & getTileLeft(int idx) const;                       // 获得idx对应的牌的剩余数量
	[[nodiscard]] const int & getTotalLeft() const;                             // 获得所有牌的剩余数量

	void incSecretGangCntOf(int idx);                                           // 给某名玩家的暗杠数量+1
	[[nodiscard]] int getSecretGangCntOf(int idx) const;                        // 获取某名玩家的暗杠数量

	void setCurPosition(int curP);                                              // 设置“我们"当前的编号（座位
	[[nodiscard]] int getCurPosition() const;                                   // 获得我们当前的编号
	void setCurTurnPlayer(int curTP);                                           // 设置当前回合行动的玩家
	[[nodiscard]] int getCurTurnPlayer() const;                                 // 获得当前回合行动的玩家的编号
	void setLastPlayed(const Majang& lastTile);                                // 设置上一个被打出来的麻将
	[[nodiscard]] const Majang& getLastPlayed() const;                         // 获得上一个被打出来的麻将的常引用
	void setInHandCntOf(int idx, int cnt);                                      // 将idx号玩家的手牌数量设置为cnt
	[[nodiscard]] int getInHandCntOf(int idx) const;                            // 获取idx号玩家的手牌数量
	void incInHandCntOf(int idx);                                               // 给idx号玩家的手牌数量+1
	void decInHandCntOf(int idx);                                               // 给idx号玩家的手牌数量-1

	void deleteFromInHand(const Majang& toDelete);                             // 从手牌中去除toDelete   //? 可能是一个优化点

	void nxtPosition();                                                         // 将当前的编号（座位）移动到下一个，！应该不常用
	void nxtTurn();                                                             // 进入下一回合
};

#endif
/*** End of inlined file: StateContainer.h ***/


/*** Start of inlined file: StateContainer.cpp ***/

/*** Start of inlined file: StateContainer.h ***/
#ifndef _BOTZONE_ONLINE
#pragma once
#endif

#ifndef STATECONTAINER_H
#define STATECONTAINER_H

#include <valarray>
#include <vector>
#include <algorithm>

// 使用Majang类

/*** Start of inlined file: Majang.h ***/
#ifndef _BOTZONE_ONLINE
#pragma once
#endif

#ifndef MAJANG_H
#define MAJANG_H

#include <string>
//#include <string_view>

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
	TILE_T_SIZE  // 以便循环使用
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
	bool operator == (const Majang& other);

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
/*** End of inlined file: Majang.h ***/


using namespace std;

//typedef pair<char, int> Majang; // 所有麻将牌均以“大写字母+数字”组合表示

// 从题目的输入request的0~9可知，在输入环节我们可以得到的信息有：
// 0. 我们的位置、当前的风圈
// 1. 我们的起始手牌、四名玩家各人的花牌
// 2. 当前是哪个玩家的回合（可以通过各个摸牌操作来判断）
// 3. 各个玩家的鸣牌（可以通过吃碰杠来获得）
// 4. "弃牌堆"中的牌（被打出之后没有被吃碰杠、点炮的牌）

// 用于存放当前的局面
// 由于该部分很多函数很简单，就不费笔墨写注释了，也没有将实现分离到cpp中
class StateContainer {
private:
	int curPosition;                    // “我们”所处的位置，0是庄家。同样也可以在博弈树节点使用以判断敌我
	int curTurnPlayer;                  // 当前是哪个玩家的回合
//    valarray<Majang> inHand;           // 用于存储手牌
//    valarray<Majang> flowerTilesOf[4]; // 用于存储花牌，分别对应4个玩家
//    valarray<Majang> chiOf[4];         // 某个玩家鸣牌中的所有“吃”,存放中间那张牌即可
//    valarray<Majang> pengOf[4];        // 某个玩家鸣牌中的所有“碰”，存放其中一张即可（因为三张一模一样
//    valarray<Majang> gangOf[4];        // 某个玩家鸣牌中的所有“杠”，存放其中一张即可
////    valarray<Majang> discards;       // 用于存放弃牌堆
//    valarray<Majang> tilePlayedOf[4];  // 用于记录某个玩家曾经都打出过哪些卡牌，无论是否被吃、碰还是杠
	vector<Majang> inHand;           // 用于存储手牌
	vector<Majang> flowerTilesOf[4]; // 用于存储花牌，分别对应4个玩家
	vector<Majang> chiOf[4];         // 某个玩家鸣牌中的所有“吃”,存放中间那张牌即可
	vector<Majang> pengOf[4];        // 某个玩家鸣牌中的所有“碰”，存放其中一张即可（因为三张一模一样
	vector<Majang> gangOf[4];        // 某个玩家鸣牌中的所有“杠”，存放其中一张即可
//    valarray<Majang> discards;       // 用于存放弃牌堆
	vector<Majang> tilePlayedOf[4];  // 用于记录某个玩家曾经都打出过哪些卡牌，无论是否被吃、碰还是杠
	int secretGangCntOf[4];           // 用于记录"暗杠"的数量，通过输入数据我们可以判断出某名玩家有几个暗杠，但我们不知道暗杠的是什么
	// 下面这个lastPlayed还没确定好到底怎么用，想好的时候再改吧
	Majang lastPlayed;                 // 用于记录上个回合被打出的麻将牌，如果不是麻将牌类型的话则为其他操作（具体见RequestReader::readRequest
	int tileLeft[70];                   // 用于记录各种类型牌所剩余的没出现的数量
	int totalLeft;                      // 没出现过的牌的总数（初始144）
	int inHandCnt[4];                   // 用于记录四名玩家的手牌数量(虽然不知道有没有用)

public:
	static int quan;                    // 圈风。因为在一把botzone游戏中，只考虑国标麻将的一局游戏，所以圈风应该是不变的
	static int lastRequest;             // 上回合的操作,用于算番器的isGANG,采取博弈算法时应换一种存储方式

	explicit StateContainer(int curP=0, int curT=0);
	StateContainer(const StateContainer& other);

//    [[nodiscard]] valarray<Majang>& getInHand();                               // 获取手牌
//    [[nodiscard]] valarray<Majang>& getFlowerTilesOf(int idx);                 // 获取花牌
//    [[nodiscard]] valarray<Majang>& getChiOf(int idx);                         // 获取鸣牌中的“吃"
//    [[nodiscard]] valarray<Majang>& getPengOf(int idx);                        // 获取鸣牌中的“碰"
//    [[nodiscard]] valarray<Majang>& getGangOf(int idx);                        // 获取鸣牌中的“杠”
////    [[nodiscard]] valarray<Majang>& getDiscards();                             // 获取弃牌堆
//    [[nodiscard]] valarray<Majang>& getTilePlayedOf(int idx);                  // 获取某名玩家打过的所有牌
//
//    [[nodiscard]] const valarray<Majang>& getInHand() const;                   //  获取手牌的常引用，下同上
//    [[nodiscard]] const valarray<Majang>& getFlowerTilesOf(int idx) const;
//    [[nodiscard]] const valarray<Majang>& getChiOf(int idx) const;
//    [[nodiscard]] const valarray<Majang>& getPengOf(int idx) const;
//    [[nodiscard]] const valarray<Majang>& getGangOf(int idx) const;
////    [[nodiscard]] const valarray<Majang>& getDiscards() const;
//    [[nodiscard]] const valarray<Majang>& getTilePlayedOf(int idx) const;

	[[nodiscard]] vector<Majang>& getInHand();                               // 获取手牌
	[[nodiscard]] vector<Majang>& getFlowerTilesOf(int idx);                 // 获取花牌
	[[nodiscard]] vector<Majang>& getChiOf(int idx);                         // 获取鸣牌中的“吃"
	[[nodiscard]] vector<Majang>& getPengOf(int idx);                        // 获取鸣牌中的“碰"
	[[nodiscard]] vector<Majang>& getGangOf(int idx);                        // 获取鸣牌中的“杠”
	[[nodiscard]] vector<Majang>& getTilePlayedOf(int idx);                  // 获取某名玩家打过的所有牌

	[[nodiscard]] const vector<Majang>& getInHand() const;                   //  获取手牌的常引用，下同上
	[[nodiscard]] const vector<Majang>& getFlowerTilesOf(int idx) const;
	[[nodiscard]] const vector<Majang>& getChiOf(int idx) const;
	[[nodiscard]] const vector<Majang>& getPengOf(int idx) const;
	[[nodiscard]] const vector<Majang>& getGangOf(int idx) const;
	[[nodiscard]] const vector<Majang>& getTilePlayedOf(int idx) const;

	void decTileLeft(int idx);                                                  // 在减少idx对应的牌的数量的同时，减少总数的数量
	void decTileLeft(Majang mj);                                               // 同上
	[[nodiscard]] const int & getTileLeft(int idx) const;                       // 获得idx对应的牌的剩余数量
	[[nodiscard]] const int & getTotalLeft() const;                             // 获得所有牌的剩余数量

	void incSecretGangCntOf(int idx);                                           // 给某名玩家的暗杠数量+1
	[[nodiscard]] int getSecretGangCntOf(int idx) const;                        // 获取某名玩家的暗杠数量

	void setCurPosition(int curP);                                              // 设置“我们"当前的编号（座位
	[[nodiscard]] int getCurPosition() const;                                   // 获得我们当前的编号
	void setCurTurnPlayer(int curTP);                                           // 设置当前回合行动的玩家
	[[nodiscard]] int getCurTurnPlayer() const;                                 // 获得当前回合行动的玩家的编号
	void setLastPlayed(const Majang& lastTile);                                // 设置上一个被打出来的麻将
	[[nodiscard]] const Majang& getLastPlayed() const;                         // 获得上一个被打出来的麻将的常引用
	void setInHandCntOf(int idx, int cnt);                                      // 将idx号玩家的手牌数量设置为cnt
	[[nodiscard]] int getInHandCntOf(int idx) const;                            // 获取idx号玩家的手牌数量
	void incInHandCntOf(int idx);                                               // 给idx号玩家的手牌数量+1
	void decInHandCntOf(int idx);                                               // 给idx号玩家的手牌数量-1

	void deleteFromInHand(const Majang& toDelete);                             // 从手牌中去除toDelete   //? 可能是一个优化点

	void nxtPosition();                                                         // 将当前的编号（座位）移动到下一个，！应该不常用
	void nxtTurn();                                                             // 进入下一回合
};

#endif
/*** End of inlined file: StateContainer.h ***/

#include <cassert>

StateContainer::StateContainer(int curP, int curT) :  curPosition(curP), curTurnPlayer(curT), inHand(13),  totalLeft(144) {
	for(int i = 1; i < 10; i++) {
		tileLeft[10 + i] = 4;   // WANN
		tileLeft[20 + i] = 4;   // BING
		tileLeft[30 + i] = 4;   // TIAO
	}
	for(int i = 1; i < 5; i++) {
		tileLeft[40 + i] = 4;   // JIAN
		tileLeft[50 + i] = 4;   // FENG
	}
	for(int i = 1; i < 9; i++) {
		tileLeft[60 + i] = 1;   // 花牌只有一张
	}
	lastPlayed = Majang("N0");
	for(int& i : inHandCnt) { // 初始化手牌数量
		i = 13;
	}
}

StateContainer::StateContainer(const StateContainer &other) {
	curPosition = other.curPosition;
	inHand = other.inHand;
	curTurnPlayer = other.curTurnPlayer;
	lastPlayed = other.lastPlayed;
	totalLeft = other.totalLeft;
	for (int i = 0; i < 4; i++) {
		flowerTilesOf[i] = other.flowerTilesOf[i];
		chiOf[i] = other.chiOf[i];
		pengOf[i] = other.pengOf[i];
		gangOf[i] = other.gangOf[i];
//        discards[i] = other.discards[i];
		tilePlayedOf[i] = other.tilePlayedOf[i];
		secretGangCntOf[i] = other.secretGangCntOf[i];
		inHandCnt[i] = other.inHandCnt[i];
	}
	for (int i = 0; i < 70; i++) {
		tileLeft[i] = other.tileLeft[i];
	}
}

//valarray<Majang> &StateContainer::getInHand() { return inHand; }
//valarray<Majang> &StateContainer::getFlowerTilesOf(int idx) { return flowerTilesOf[idx]; }
//valarray<Majang> &StateContainer::getChiOf(int idx) { return chiOf[idx]; }
//valarray<Majang> &StateContainer::getPengOf(int idx) { return pengOf[idx]; }
//valarray<Majang> &StateContainer::getGangOf(int idx) { return gangOf[idx]; }
////valarray<Majang> &StateContainer::getDiscards() { return discards; }
//valarray<Majang> &StateContainer::getTilePlayedOf(int idx) { return tilePlayedOf[idx]; }
//
//const valarray<Majang> &StateContainer::getInHand() const { return inHand; }
//const valarray<Majang> &StateContainer::getFlowerTilesOf(int idx) const { return flowerTilesOf[idx]; }
//const valarray<Majang> &StateContainer::getChiOf(int idx) const { return chiOf[idx]; }
//const valarray<Majang> &StateContainer::getPengOf(int idx) const { return pengOf[idx]; }
//const valarray<Majang> &StateContainer::getGangOf(int idx) const { return gangOf[idx]; }
////const valarray<Majang> &StateContainer::getDiscards() const { return discards; }
//const valarray<Majang> &StateContainer::getTilePlayedOf(int idx) const { return tilePlayedOf[idx]; }

vector<Majang> &StateContainer::getInHand() { return inHand; }
vector<Majang> &StateContainer::getFlowerTilesOf(int idx) { return flowerTilesOf[idx]; }
vector<Majang> &StateContainer::getChiOf(int idx) { return chiOf[idx]; }
vector<Majang> &StateContainer::getPengOf(int idx) { return pengOf[idx]; }
vector<Majang> &StateContainer::getGangOf(int idx) { return gangOf[idx]; }
vector<Majang> &StateContainer::getTilePlayedOf(int idx) { return tilePlayedOf[idx]; }

const vector<Majang> &StateContainer::getInHand() const { return inHand; }
const vector<Majang> &StateContainer::getFlowerTilesOf(int idx) const { return flowerTilesOf[idx]; }
const vector<Majang> &StateContainer::getChiOf(int idx) const { return chiOf[idx]; }
const vector<Majang> &StateContainer::getPengOf(int idx) const { return pengOf[idx]; }
const vector<Majang> &StateContainer::getGangOf(int idx) const { return gangOf[idx]; }
const vector<Majang> &StateContainer::getTilePlayedOf(int idx) const { return tilePlayedOf[idx]; }

void StateContainer::decTileLeft(int idx) { tileLeft[idx]--; totalLeft--; }
void StateContainer::decTileLeft(Majang mj) {
	tileLeft[mj.getTileInt()]--;
	totalLeft--;
}
const int & StateContainer::getTileLeft(int idx) const {return tileLeft[idx];}
const int & StateContainer::getTotalLeft() const {return totalLeft;}

void StateContainer::incSecretGangCntOf(int idx) {secretGangCntOf[idx]++;}
int StateContainer::getSecretGangCntOf(int idx) const { return secretGangCntOf[idx]; }

void StateContainer::setCurPosition(int curP) { curPosition = curP; }
int StateContainer::getCurPosition() const { return curPosition; }
void StateContainer::setCurTurnPlayer(int curTP) { curTurnPlayer = curTP; }
int StateContainer::getCurTurnPlayer() const { return curTurnPlayer; }
void StateContainer::setLastPlayed(const Majang &lastTile) { lastPlayed = lastTile; }
const Majang &StateContainer::getLastPlayed() const { return lastPlayed; }
void StateContainer::setInHandCntOf(int idx, int cnt) { inHandCnt[idx] = cnt; }
int StateContainer::getInHandCntOf(int idx) const { return inHandCnt[idx]; }
void StateContainer::incInHandCntOf(int idx) { inHandCnt[idx]++; }
void StateContainer::decInHandCntOf(int idx) { inHandCnt[idx]--; }

void StateContainer::deleteFromInHand(const Majang &toDelete) {
	int lim = inHand.size();
	for(int i=0; i<lim; i++) {
		if(inHand[i] == toDelete) {
			swap(inHand[i], inHand[lim-1]);
			break;
		}
	}
	inHand.resize(lim-1);
}

void StateContainer::nxtPosition() { curPosition = (curPosition + 1) % 4; }
void StateContainer::nxtTurn() { curTurnPlayer = (curTurnPlayer + 1) % 4; }

/*** End of inlined file: StateContainer.cpp ***/


/*** Start of inlined file: RequestReader.h ***/
#ifndef _BOTZONE_ONLINE
#pragma once
#endif

#ifndef REQUESTREADER_H
#define REQUESTREADER_H

#include <cstdio>
#include <cctype>
#include <string>
#include <cstring>
#include <valarray>
#include <cassert>

/*** Start of inlined file: Majang.h ***/
#ifndef _BOTZONE_ONLINE
#pragma once
#endif

#ifndef MAJANG_H
#define MAJANG_H

#include <string>
//#include <string_view>

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
	TILE_T_SIZE  // 以便循环使用
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
	bool operator == (const Majang& other);

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
/*** End of inlined file: Majang.h ***/



/*** Start of inlined file: StateContainer.h ***/
#ifndef _BOTZONE_ONLINE
#pragma once
#endif

#ifndef STATECONTAINER_H
#define STATECONTAINER_H

#include <valarray>
#include <vector>
#include <algorithm>

// 使用Majang类

/*** Start of inlined file: Majang.h ***/
#ifndef _BOTZONE_ONLINE
#pragma once
#endif

#ifndef MAJANG_H
#define MAJANG_H

#include <string>
//#include <string_view>

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
	TILE_T_SIZE  // 以便循环使用
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
	bool operator == (const Majang& other);

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
/*** End of inlined file: Majang.h ***/


using namespace std;

//typedef pair<char, int> Majang; // 所有麻将牌均以“大写字母+数字”组合表示

// 从题目的输入request的0~9可知，在输入环节我们可以得到的信息有：
// 0. 我们的位置、当前的风圈
// 1. 我们的起始手牌、四名玩家各人的花牌
// 2. 当前是哪个玩家的回合（可以通过各个摸牌操作来判断）
// 3. 各个玩家的鸣牌（可以通过吃碰杠来获得）
// 4. "弃牌堆"中的牌（被打出之后没有被吃碰杠、点炮的牌）

// 用于存放当前的局面
// 由于该部分很多函数很简单，就不费笔墨写注释了，也没有将实现分离到cpp中
class StateContainer {
private:
	int curPosition;                    // “我们”所处的位置，0是庄家。同样也可以在博弈树节点使用以判断敌我
	int curTurnPlayer;                  // 当前是哪个玩家的回合
//    valarray<Majang> inHand;           // 用于存储手牌
//    valarray<Majang> flowerTilesOf[4]; // 用于存储花牌，分别对应4个玩家
//    valarray<Majang> chiOf[4];         // 某个玩家鸣牌中的所有“吃”,存放中间那张牌即可
//    valarray<Majang> pengOf[4];        // 某个玩家鸣牌中的所有“碰”，存放其中一张即可（因为三张一模一样
//    valarray<Majang> gangOf[4];        // 某个玩家鸣牌中的所有“杠”，存放其中一张即可
////    valarray<Majang> discards;       // 用于存放弃牌堆
//    valarray<Majang> tilePlayedOf[4];  // 用于记录某个玩家曾经都打出过哪些卡牌，无论是否被吃、碰还是杠
	vector<Majang> inHand;           // 用于存储手牌
	vector<Majang> flowerTilesOf[4]; // 用于存储花牌，分别对应4个玩家
	vector<Majang> chiOf[4];         // 某个玩家鸣牌中的所有“吃”,存放中间那张牌即可
	vector<Majang> pengOf[4];        // 某个玩家鸣牌中的所有“碰”，存放其中一张即可（因为三张一模一样
	vector<Majang> gangOf[4];        // 某个玩家鸣牌中的所有“杠”，存放其中一张即可
//    valarray<Majang> discards;       // 用于存放弃牌堆
	vector<Majang> tilePlayedOf[4];  // 用于记录某个玩家曾经都打出过哪些卡牌，无论是否被吃、碰还是杠
	int secretGangCntOf[4];           // 用于记录"暗杠"的数量，通过输入数据我们可以判断出某名玩家有几个暗杠，但我们不知道暗杠的是什么
	// 下面这个lastPlayed还没确定好到底怎么用，想好的时候再改吧
	Majang lastPlayed;                 // 用于记录上个回合被打出的麻将牌，如果不是麻将牌类型的话则为其他操作（具体见RequestReader::readRequest
	int tileLeft[70];                   // 用于记录各种类型牌所剩余的没出现的数量
	int totalLeft;                      // 没出现过的牌的总数（初始144）
	int inHandCnt[4];                   // 用于记录四名玩家的手牌数量(虽然不知道有没有用)

public:
	static int quan;                    // 圈风。因为在一把botzone游戏中，只考虑国标麻将的一局游戏，所以圈风应该是不变的
	static int lastRequest;             // 上回合的操作,用于算番器的isGANG,采取博弈算法时应换一种存储方式

	explicit StateContainer(int curP=0, int curT=0);
	StateContainer(const StateContainer& other);

//    [[nodiscard]] valarray<Majang>& getInHand();                               // 获取手牌
//    [[nodiscard]] valarray<Majang>& getFlowerTilesOf(int idx);                 // 获取花牌
//    [[nodiscard]] valarray<Majang>& getChiOf(int idx);                         // 获取鸣牌中的“吃"
//    [[nodiscard]] valarray<Majang>& getPengOf(int idx);                        // 获取鸣牌中的“碰"
//    [[nodiscard]] valarray<Majang>& getGangOf(int idx);                        // 获取鸣牌中的“杠”
////    [[nodiscard]] valarray<Majang>& getDiscards();                             // 获取弃牌堆
//    [[nodiscard]] valarray<Majang>& getTilePlayedOf(int idx);                  // 获取某名玩家打过的所有牌
//
//    [[nodiscard]] const valarray<Majang>& getInHand() const;                   //  获取手牌的常引用，下同上
//    [[nodiscard]] const valarray<Majang>& getFlowerTilesOf(int idx) const;
//    [[nodiscard]] const valarray<Majang>& getChiOf(int idx) const;
//    [[nodiscard]] const valarray<Majang>& getPengOf(int idx) const;
//    [[nodiscard]] const valarray<Majang>& getGangOf(int idx) const;
////    [[nodiscard]] const valarray<Majang>& getDiscards() const;
//    [[nodiscard]] const valarray<Majang>& getTilePlayedOf(int idx) const;

	[[nodiscard]] vector<Majang>& getInHand();                               // 获取手牌
	[[nodiscard]] vector<Majang>& getFlowerTilesOf(int idx);                 // 获取花牌
	[[nodiscard]] vector<Majang>& getChiOf(int idx);                         // 获取鸣牌中的“吃"
	[[nodiscard]] vector<Majang>& getPengOf(int idx);                        // 获取鸣牌中的“碰"
	[[nodiscard]] vector<Majang>& getGangOf(int idx);                        // 获取鸣牌中的“杠”
	[[nodiscard]] vector<Majang>& getTilePlayedOf(int idx);                  // 获取某名玩家打过的所有牌

	[[nodiscard]] const vector<Majang>& getInHand() const;                   //  获取手牌的常引用，下同上
	[[nodiscard]] const vector<Majang>& getFlowerTilesOf(int idx) const;
	[[nodiscard]] const vector<Majang>& getChiOf(int idx) const;
	[[nodiscard]] const vector<Majang>& getPengOf(int idx) const;
	[[nodiscard]] const vector<Majang>& getGangOf(int idx) const;
	[[nodiscard]] const vector<Majang>& getTilePlayedOf(int idx) const;

	void decTileLeft(int idx);                                                  // 在减少idx对应的牌的数量的同时，减少总数的数量
	void decTileLeft(Majang mj);                                               // 同上
	[[nodiscard]] const int & getTileLeft(int idx) const;                       // 获得idx对应的牌的剩余数量
	[[nodiscard]] const int & getTotalLeft() const;                             // 获得所有牌的剩余数量

	void incSecretGangCntOf(int idx);                                           // 给某名玩家的暗杠数量+1
	[[nodiscard]] int getSecretGangCntOf(int idx) const;                        // 获取某名玩家的暗杠数量

	void setCurPosition(int curP);                                              // 设置“我们"当前的编号（座位
	[[nodiscard]] int getCurPosition() const;                                   // 获得我们当前的编号
	void setCurTurnPlayer(int curTP);                                           // 设置当前回合行动的玩家
	[[nodiscard]] int getCurTurnPlayer() const;                                 // 获得当前回合行动的玩家的编号
	void setLastPlayed(const Majang& lastTile);                                // 设置上一个被打出来的麻将
	[[nodiscard]] const Majang& getLastPlayed() const;                         // 获得上一个被打出来的麻将的常引用
	void setInHandCntOf(int idx, int cnt);                                      // 将idx号玩家的手牌数量设置为cnt
	[[nodiscard]] int getInHandCntOf(int idx) const;                            // 获取idx号玩家的手牌数量
	void incInHandCntOf(int idx);                                               // 给idx号玩家的手牌数量+1
	void decInHandCntOf(int idx);                                               // 给idx号玩家的手牌数量-1

	void deleteFromInHand(const Majang& toDelete);                             // 从手牌中去除toDelete   //? 可能是一个优化点

	void nxtPosition();                                                         // 将当前的编号（座位）移动到下一个，！应该不常用
	void nxtTurn();                                                             // 进入下一回合
};

#endif
/*** End of inlined file: StateContainer.h ***/

#ifdef _BOTZONE_ONLINE
#include "MahjongGB/MahjongGB.h"
#endif

using namespace std;

class Reader{
public:
	static void readIn(string& str);                            // 读取string
	static void readIn(int& x);                                 // 读取int
	static void readIn(Majang& tile);                          // 读取Majang

	// 能根据对应编号读入不同的信息并存放到StateContainer
	// 返回值为int，代表这条request读取到了什么操作
	// 其中我们规定:
	// 0 -> 0, 1 -> 1, 2 -> 2 这三条就像原来一样，两个初始化，一个抽牌
	// 30 -> BUHUA, 31 -> DRAW, 32 -> PLAY
	// 33 -> PENG, 34 -> CHI, 35 -> GANG, 36 -> BUGANG
	static int readRequest(StateContainer& state);              // 用于读取一条request
};

#endif

/*** End of inlined file: RequestReader.h ***/


/*** Start of inlined file: RequestReader.cpp ***/

/*** Start of inlined file: RequestReader.h ***/
#ifndef _BOTZONE_ONLINE
#pragma once
#endif

#ifndef REQUESTREADER_H
#define REQUESTREADER_H

#include <cstdio>
#include <cctype>
#include <string>
#include <cstring>
#include <valarray>
#include <cassert>

/*** Start of inlined file: Majang.h ***/
#ifndef _BOTZONE_ONLINE
#pragma once
#endif

#ifndef MAJANG_H
#define MAJANG_H

#include <string>
//#include <string_view>

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
	TILE_T_SIZE  // 以便循环使用
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
	bool operator == (const Majang& other);

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
/*** End of inlined file: Majang.h ***/



/*** Start of inlined file: StateContainer.h ***/
#ifndef _BOTZONE_ONLINE
#pragma once
#endif

#ifndef STATECONTAINER_H
#define STATECONTAINER_H

#include <valarray>
#include <vector>
#include <algorithm>

// 使用Majang类

/*** Start of inlined file: Majang.h ***/
#ifndef _BOTZONE_ONLINE
#pragma once
#endif

#ifndef MAJANG_H
#define MAJANG_H

#include <string>
//#include <string_view>

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
	TILE_T_SIZE  // 以便循环使用
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
	bool operator == (const Majang& other);

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
/*** End of inlined file: Majang.h ***/


using namespace std;

//typedef pair<char, int> Majang; // 所有麻将牌均以“大写字母+数字”组合表示

// 从题目的输入request的0~9可知，在输入环节我们可以得到的信息有：
// 0. 我们的位置、当前的风圈
// 1. 我们的起始手牌、四名玩家各人的花牌
// 2. 当前是哪个玩家的回合（可以通过各个摸牌操作来判断）
// 3. 各个玩家的鸣牌（可以通过吃碰杠来获得）
// 4. "弃牌堆"中的牌（被打出之后没有被吃碰杠、点炮的牌）

// 用于存放当前的局面
// 由于该部分很多函数很简单，就不费笔墨写注释了，也没有将实现分离到cpp中
class StateContainer {
private:
	int curPosition;                    // “我们”所处的位置，0是庄家。同样也可以在博弈树节点使用以判断敌我
	int curTurnPlayer;                  // 当前是哪个玩家的回合
//    valarray<Majang> inHand;           // 用于存储手牌
//    valarray<Majang> flowerTilesOf[4]; // 用于存储花牌，分别对应4个玩家
//    valarray<Majang> chiOf[4];         // 某个玩家鸣牌中的所有“吃”,存放中间那张牌即可
//    valarray<Majang> pengOf[4];        // 某个玩家鸣牌中的所有“碰”，存放其中一张即可（因为三张一模一样
//    valarray<Majang> gangOf[4];        // 某个玩家鸣牌中的所有“杠”，存放其中一张即可
////    valarray<Majang> discards;       // 用于存放弃牌堆
//    valarray<Majang> tilePlayedOf[4];  // 用于记录某个玩家曾经都打出过哪些卡牌，无论是否被吃、碰还是杠
	vector<Majang> inHand;           // 用于存储手牌
	vector<Majang> flowerTilesOf[4]; // 用于存储花牌，分别对应4个玩家
	vector<Majang> chiOf[4];         // 某个玩家鸣牌中的所有“吃”,存放中间那张牌即可
	vector<Majang> pengOf[4];        // 某个玩家鸣牌中的所有“碰”，存放其中一张即可（因为三张一模一样
	vector<Majang> gangOf[4];        // 某个玩家鸣牌中的所有“杠”，存放其中一张即可
//    valarray<Majang> discards;       // 用于存放弃牌堆
	vector<Majang> tilePlayedOf[4];  // 用于记录某个玩家曾经都打出过哪些卡牌，无论是否被吃、碰还是杠
	int secretGangCntOf[4];           // 用于记录"暗杠"的数量，通过输入数据我们可以判断出某名玩家有几个暗杠，但我们不知道暗杠的是什么
	// 下面这个lastPlayed还没确定好到底怎么用，想好的时候再改吧
	Majang lastPlayed;                 // 用于记录上个回合被打出的麻将牌，如果不是麻将牌类型的话则为其他操作（具体见RequestReader::readRequest
	int tileLeft[70];                   // 用于记录各种类型牌所剩余的没出现的数量
	int totalLeft;                      // 没出现过的牌的总数（初始144）
	int inHandCnt[4];                   // 用于记录四名玩家的手牌数量(虽然不知道有没有用)

public:
	static int quan;                    // 圈风。因为在一把botzone游戏中，只考虑国标麻将的一局游戏，所以圈风应该是不变的
	static int lastRequest;             // 上回合的操作,用于算番器的isGANG,采取博弈算法时应换一种存储方式

	explicit StateContainer(int curP=0, int curT=0);
	StateContainer(const StateContainer& other);

//    [[nodiscard]] valarray<Majang>& getInHand();                               // 获取手牌
//    [[nodiscard]] valarray<Majang>& getFlowerTilesOf(int idx);                 // 获取花牌
//    [[nodiscard]] valarray<Majang>& getChiOf(int idx);                         // 获取鸣牌中的“吃"
//    [[nodiscard]] valarray<Majang>& getPengOf(int idx);                        // 获取鸣牌中的“碰"
//    [[nodiscard]] valarray<Majang>& getGangOf(int idx);                        // 获取鸣牌中的“杠”
////    [[nodiscard]] valarray<Majang>& getDiscards();                             // 获取弃牌堆
//    [[nodiscard]] valarray<Majang>& getTilePlayedOf(int idx);                  // 获取某名玩家打过的所有牌
//
//    [[nodiscard]] const valarray<Majang>& getInHand() const;                   //  获取手牌的常引用，下同上
//    [[nodiscard]] const valarray<Majang>& getFlowerTilesOf(int idx) const;
//    [[nodiscard]] const valarray<Majang>& getChiOf(int idx) const;
//    [[nodiscard]] const valarray<Majang>& getPengOf(int idx) const;
//    [[nodiscard]] const valarray<Majang>& getGangOf(int idx) const;
////    [[nodiscard]] const valarray<Majang>& getDiscards() const;
//    [[nodiscard]] const valarray<Majang>& getTilePlayedOf(int idx) const;

	[[nodiscard]] vector<Majang>& getInHand();                               // 获取手牌
	[[nodiscard]] vector<Majang>& getFlowerTilesOf(int idx);                 // 获取花牌
	[[nodiscard]] vector<Majang>& getChiOf(int idx);                         // 获取鸣牌中的“吃"
	[[nodiscard]] vector<Majang>& getPengOf(int idx);                        // 获取鸣牌中的“碰"
	[[nodiscard]] vector<Majang>& getGangOf(int idx);                        // 获取鸣牌中的“杠”
	[[nodiscard]] vector<Majang>& getTilePlayedOf(int idx);                  // 获取某名玩家打过的所有牌

	[[nodiscard]] const vector<Majang>& getInHand() const;                   //  获取手牌的常引用，下同上
	[[nodiscard]] const vector<Majang>& getFlowerTilesOf(int idx) const;
	[[nodiscard]] const vector<Majang>& getChiOf(int idx) const;
	[[nodiscard]] const vector<Majang>& getPengOf(int idx) const;
	[[nodiscard]] const vector<Majang>& getGangOf(int idx) const;
	[[nodiscard]] const vector<Majang>& getTilePlayedOf(int idx) const;

	void decTileLeft(int idx);                                                  // 在减少idx对应的牌的数量的同时，减少总数的数量
	void decTileLeft(Majang mj);                                               // 同上
	[[nodiscard]] const int & getTileLeft(int idx) const;                       // 获得idx对应的牌的剩余数量
	[[nodiscard]] const int & getTotalLeft() const;                             // 获得所有牌的剩余数量

	void incSecretGangCntOf(int idx);                                           // 给某名玩家的暗杠数量+1
	[[nodiscard]] int getSecretGangCntOf(int idx) const;                        // 获取某名玩家的暗杠数量

	void setCurPosition(int curP);                                              // 设置“我们"当前的编号（座位
	[[nodiscard]] int getCurPosition() const;                                   // 获得我们当前的编号
	void setCurTurnPlayer(int curTP);                                           // 设置当前回合行动的玩家
	[[nodiscard]] int getCurTurnPlayer() const;                                 // 获得当前回合行动的玩家的编号
	void setLastPlayed(const Majang& lastTile);                                // 设置上一个被打出来的麻将
	[[nodiscard]] const Majang& getLastPlayed() const;                         // 获得上一个被打出来的麻将的常引用
	void setInHandCntOf(int idx, int cnt);                                      // 将idx号玩家的手牌数量设置为cnt
	[[nodiscard]] int getInHandCntOf(int idx) const;                            // 获取idx号玩家的手牌数量
	void incInHandCntOf(int idx);                                               // 给idx号玩家的手牌数量+1
	void decInHandCntOf(int idx);                                               // 给idx号玩家的手牌数量-1

	void deleteFromInHand(const Majang& toDelete);                             // 从手牌中去除toDelete   //? 可能是一个优化点

	void nxtPosition();                                                         // 将当前的编号（座位）移动到下一个，！应该不常用
	void nxtTurn();                                                             // 进入下一回合
};

#endif
/*** End of inlined file: StateContainer.h ***/

#ifdef _BOTZONE_ONLINE
#include "MahjongGB/MahjongGB.h"
#endif

using namespace std;

class Reader{
public:
	static void readIn(string& str);                            // 读取string
	static void readIn(int& x);                                 // 读取int
	static void readIn(Majang& tile);                          // 读取Majang

	// 能根据对应编号读入不同的信息并存放到StateContainer
	// 返回值为int，代表这条request读取到了什么操作
	// 其中我们规定:
	// 0 -> 0, 1 -> 1, 2 -> 2 这三条就像原来一样，两个初始化，一个抽牌
	// 30 -> BUHUA, 31 -> DRAW, 32 -> PLAY
	// 33 -> PENG, 34 -> CHI, 35 -> GANG, 36 -> BUGANG
	static int readRequest(StateContainer& state);              // 用于读取一条request
};

#endif

/*** End of inlined file: RequestReader.h ***/

#include <cassert>

void Reader::readIn(string &str) {
	str = ""; // 初始化
	unsigned char c = getchar();
	while(isspace(c)) c = getchar();
	while(!isspace(c)) {
		str += c;
		c = getchar();
	}
}

void Reader::readIn(int &x) {
	x = 0;
	unsigned char c = getchar();
	while(isspace(c)) c = getchar();
	while(!isspace(c)) {
		x = x * 10 + c - '0';
		c = getchar();
	}
}

void Reader::readIn(Majang &tile) {
	string tmp;
	readIn(tmp);
	tile.resetFromString(tmp);
}

// 每次使用可以读取一条request
int Reader::readRequest(StateContainer &state) {
	int requestID, tmp;
	int ret = 0;
	readIn(requestID);
	// 这里因为request只有四种，所以直接上switch了
	switch (requestID) {
		case 0: { // 初始化
			readIn(tmp);
			state.setCurPosition(tmp);
			readIn(StateContainer::quan);
			state.setLastPlayed("I0"); // I0 -> Initialize 0
			ret = 0;
			break;
		}
		case 1: { // 初始手牌
			// 读取花牌数量
			for (int i = 0; i < 4; i++) {
				readIn(tmp);
				state.getFlowerTilesOf(i).resize(tmp);
			}
			// 读取手牌
			assert(state.getInHand().size() == 13);
			for (int i = 0; i < 13; i++) {
				Majang tmpM;
				readIn(tmpM);
				state.getInHand()[i] = tmpM;
//                readIn(state.getInHand()[i]);
				state.decTileLeft(state.getInHand()[i]);
			}
			// 读取花牌
			for (int i = 0; i < 4; i++) {
				int lim = state.getFlowerTilesOf(i).size();
				for (int j = 0; j < lim; j++) {
					readIn(state.getFlowerTilesOf(i)[j]);
					state.decTileLeft(state.getFlowerTilesOf(i)[j]);
				}
			}
			state.setLastPlayed("I1"); // I1 -> Initialize 1
			ret = 1;
			break;
		}
		case 2: { // 我们抽牌
			vector<Majang>& tmpInHand = state.getInHand();
			Majang tmpM; readIn(tmpM);
			tmpInHand.push_back(tmpM);
			state.setLastPlayed("D6"); // D6 -> Draw!
			state.incInHandCntOf(state.getCurPosition());
			state.setCurTurnPlayer(state.getCurPosition());
			state.decTileLeft(tmpM);
			ret = 2;
			break;
		}
		case 3: { // 其他情况
			ret = 30;
			int playerID; readIn(playerID);
			state.setCurTurnPlayer(playerID); // 这条request谁进行了操作，谁就是curTurnPlayer
			string op; readIn(op);
			if (op == "BUHUA") {
				ret += 0;
				vector<Majang> &tmpHana = state.getFlowerTilesOf(playerID);
				Majang tmpM; readIn(tmpM);
				tmpHana.push_back(tmpM);
				state.decTileLeft(tmpM);
				state.setLastPlayed("D8");  // D8 -> 补花（8 => HAna)
			} else if (op == "DRAW") {
				ret += 1;
				state.incInHandCntOf(playerID);
				state.setLastPlayed("D0");  // D0 -> 其他玩家抽牌
			} else if (op == "PLAY") {
				Majang tmpPlayed; readIn(tmpPlayed);
				state.setLastPlayed(tmpPlayed);
				vector<Majang>& tmpTilePlayed = state.getTilePlayedOf(playerID);
				tmpTilePlayed.push_back(tmpPlayed);
				state.decInHandCntOf(playerID);
				if(playerID == state.getCurPosition()) {
					// 是我们打出的这张牌,这时需要从我们的手牌中去除这张牌
					state.deleteFromInHand(tmpPlayed);
				} else {
					state.decTileLeft(tmpPlayed); // 如果不是我们打出的，才需要dec
				}
				ret += 2;
			} else if (op == "PENG") {
				Majang tmpPlayed; readIn(tmpPlayed);
				Majang pengTile = state.getLastPlayed();   // 碰的牌为上一回合打出的牌
				vector<Majang>& tmpPengOf = state.getPengOf(playerID);
				tmpPengOf.push_back(pengTile);
				vector<Majang>& tmpTilePlayed = state.getTilePlayedOf(playerID);
				tmpTilePlayed.push_back(tmpPlayed);
				state.setLastPlayed(tmpPlayed);
				state.setInHandCntOf(playerID, state.getInHandCntOf(playerID)-3);  // 减少了三张牌
				if(playerID == state.getCurPosition()) {
					// 是我们进行的碰的操作,这时需要从我们的手牌中去除这三张牌
					state.deleteFromInHand(pengTile);
					state.deleteFromInHand(pengTile);
					state.deleteFromInHand(tmpPlayed);
				} else {
					state.decTileLeft(pengTile);    // 被碰的牌又会打出两张
					state.decTileLeft(pengTile);
					state.decTileLeft(tmpPlayed);     // 打出的牌也是知道的
				}
				ret += 3;
			} else if (op == "CHI") {
				Majang tmpCHI, tmpPlayed;
				readIn(tmpCHI); readIn(tmpPlayed);
				vector<Majang>& tmpChiOf = state.getChiOf(playerID);
				tmpChiOf.push_back(tmpCHI);
				// 这里需要判断出该玩家为了吃打出来的是哪两张牌
				Majang tmpCHIprv = tmpCHI.getPrvMajang();
				Majang tmpCHInxt = tmpCHI.getNxtMajang();
				const Majang& lastPlayed = state.getLastPlayed();
				vector<Majang>& tmpTilePlayed = state.getTilePlayedOf(playerID);
				tmpTilePlayed.push_back(tmpPlayed);
				state.setInHandCntOf(playerID, state.getInHandCntOf(playerID)-3);  // 减少了三张牌
				if(playerID == state.getCurPosition()) {
					// 再来一次判断
					if(tmpCHIprv == lastPlayed) {
						state.deleteFromInHand(tmpCHI);
						state.deleteFromInHand(tmpCHInxt);
					} else if(tmpCHI == lastPlayed) {
						state.deleteFromInHand(tmpCHIprv);
						state.deleteFromInHand(tmpCHInxt);
					} else if(tmpCHInxt == lastPlayed) {
						state.deleteFromInHand(tmpCHIprv);
						state.deleteFromInHand(tmpCHI);
					} else {
						assert(strcmp("[ERROR] remove CHI tiles from inHand failed!",""));
					}
					state.deleteFromInHand(tmpPlayed);  // 以及打出的牌
				} else {
					if(tmpCHIprv == lastPlayed) {
						state.decTileLeft(tmpCHI);
						state.decTileLeft(tmpCHInxt);
					} else if(tmpCHI == lastPlayed) {
						state.decTileLeft(tmpCHIprv);
						state.decTileLeft(tmpCHInxt);
					} else if(tmpCHInxt == lastPlayed) {
						state.decTileLeft(tmpCHIprv);
						state.decTileLeft(tmpCHI);
					} else {
						assert(strcmp("[ERROR] judge CHI failed!",""));
					}
					state.decTileLeft(tmpPlayed);
				}
				state.setLastPlayed(tmpPlayed);
				ret += 4;
			} else if (op == "GANG") {
				if(state.getLastPlayed().getTileType() == 'D') {
					// 如果上一回合是摸牌，表示进行暗杠
					state.incSecretGangCntOf(playerID);
					state.setInHandCntOf(playerID, state.getInHandCntOf(playerID) - 4);
				} else {
					// 明杠，这里假设抽牌操作和打牌操作会在之后以draw和play的request呈现
					const Majang& gangTile = state.getLastPlayed();
					vector<Majang>& tmpGangOf = state.getGangOf(playerID);
					tmpGangOf.push_back(gangTile);
					// 因为要打出三张gangTile
					if(playerID == state.getCurPosition()) {
						state.deleteFromInHand(gangTile);
						state.deleteFromInHand(gangTile);
						state.deleteFromInHand(gangTile);
					} else {
						state.decTileLeft(gangTile);
						state.decTileLeft(gangTile);
						state.decTileLeft(gangTile);
					}
				}
				ret += 5;
			} else if (op == "BUGANG") {
				Majang tmpBuGang; readIn(tmpBuGang);
				vector<Majang>& tmpGangOf = state.getGangOf(playerID);
				tmpGangOf.push_back(tmpBuGang);
				// 同时还要从碰中去除
				vector<Majang>& tmpPengOf = state.getPengOf(playerID);
				int lim = tmpPengOf.size();
				for(int i=0; i<lim; i++) {
					if(tmpPengOf[i] == tmpBuGang) {
						swap(tmpPengOf[i], tmpPengOf[lim-1]);
						break;
					}
				}
//                tmpPengOf.resize(lim-1);
				tmpPengOf.pop_back(); // 换成这个了，但是显然有更好的做法，是优化的一个点
				if(playerID == state.getCurPosition()) {
					state.deleteFromInHand(tmpBuGang);
				} else {
					state.decTileLeft(tmpBuGang);
				}
				ret += 6;
			} else {
				assert(strcmp("[ERROR] readOP failed!",""));
			}
			break;
		}
		default: {
			assert(strcmp("[ERROR] readRequestID failed!",""));
			break;
		}
	}
	return ret;
}

/*** End of inlined file: RequestReader.cpp ***/


/*** Start of inlined file: ScoreCalculator.h ***/
#ifndef _BOTZONE_ONLINE
#pragma once
#endif

#ifndef SCORECALCULATOR_H
#define SCORECALCULATOR_H

#include <string>
#include <cstring>
#include <vector>
#include <utility>


/*** Start of inlined file: Majang.h ***/
#ifndef _BOTZONE_ONLINE
#pragma once
#endif

#ifndef MAJANG_H
#define MAJANG_H

#include <string>
//#include <string_view>

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
	TILE_T_SIZE  // 以便循环使用
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
	bool operator == (const Majang& other);

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
/*** End of inlined file: Majang.h ***/


/*** Start of inlined file: StateContainer.h ***/
#ifndef _BOTZONE_ONLINE
#pragma once
#endif

#ifndef STATECONTAINER_H
#define STATECONTAINER_H

#include <valarray>
#include <vector>
#include <algorithm>

// 使用Majang类

/*** Start of inlined file: Majang.h ***/
#ifndef _BOTZONE_ONLINE
#pragma once
#endif

#ifndef MAJANG_H
#define MAJANG_H

#include <string>
//#include <string_view>

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
	TILE_T_SIZE  // 以便循环使用
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
	bool operator == (const Majang& other);

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
/*** End of inlined file: Majang.h ***/


using namespace std;

//typedef pair<char, int> Majang; // 所有麻将牌均以“大写字母+数字”组合表示

// 从题目的输入request的0~9可知，在输入环节我们可以得到的信息有：
// 0. 我们的位置、当前的风圈
// 1. 我们的起始手牌、四名玩家各人的花牌
// 2. 当前是哪个玩家的回合（可以通过各个摸牌操作来判断）
// 3. 各个玩家的鸣牌（可以通过吃碰杠来获得）
// 4. "弃牌堆"中的牌（被打出之后没有被吃碰杠、点炮的牌）

// 用于存放当前的局面
// 由于该部分很多函数很简单，就不费笔墨写注释了，也没有将实现分离到cpp中
class StateContainer {
private:
	int curPosition;                    // “我们”所处的位置，0是庄家。同样也可以在博弈树节点使用以判断敌我
	int curTurnPlayer;                  // 当前是哪个玩家的回合
//    valarray<Majang> inHand;           // 用于存储手牌
//    valarray<Majang> flowerTilesOf[4]; // 用于存储花牌，分别对应4个玩家
//    valarray<Majang> chiOf[4];         // 某个玩家鸣牌中的所有“吃”,存放中间那张牌即可
//    valarray<Majang> pengOf[4];        // 某个玩家鸣牌中的所有“碰”，存放其中一张即可（因为三张一模一样
//    valarray<Majang> gangOf[4];        // 某个玩家鸣牌中的所有“杠”，存放其中一张即可
////    valarray<Majang> discards;       // 用于存放弃牌堆
//    valarray<Majang> tilePlayedOf[4];  // 用于记录某个玩家曾经都打出过哪些卡牌，无论是否被吃、碰还是杠
	vector<Majang> inHand;           // 用于存储手牌
	vector<Majang> flowerTilesOf[4]; // 用于存储花牌，分别对应4个玩家
	vector<Majang> chiOf[4];         // 某个玩家鸣牌中的所有“吃”,存放中间那张牌即可
	vector<Majang> pengOf[4];        // 某个玩家鸣牌中的所有“碰”，存放其中一张即可（因为三张一模一样
	vector<Majang> gangOf[4];        // 某个玩家鸣牌中的所有“杠”，存放其中一张即可
//    valarray<Majang> discards;       // 用于存放弃牌堆
	vector<Majang> tilePlayedOf[4];  // 用于记录某个玩家曾经都打出过哪些卡牌，无论是否被吃、碰还是杠
	int secretGangCntOf[4];           // 用于记录"暗杠"的数量，通过输入数据我们可以判断出某名玩家有几个暗杠，但我们不知道暗杠的是什么
	// 下面这个lastPlayed还没确定好到底怎么用，想好的时候再改吧
	Majang lastPlayed;                 // 用于记录上个回合被打出的麻将牌，如果不是麻将牌类型的话则为其他操作（具体见RequestReader::readRequest
	int tileLeft[70];                   // 用于记录各种类型牌所剩余的没出现的数量
	int totalLeft;                      // 没出现过的牌的总数（初始144）
	int inHandCnt[4];                   // 用于记录四名玩家的手牌数量(虽然不知道有没有用)

public:
	static int quan;                    // 圈风。因为在一把botzone游戏中，只考虑国标麻将的一局游戏，所以圈风应该是不变的
	static int lastRequest;             // 上回合的操作,用于算番器的isGANG,采取博弈算法时应换一种存储方式

	explicit StateContainer(int curP=0, int curT=0);
	StateContainer(const StateContainer& other);

//    [[nodiscard]] valarray<Majang>& getInHand();                               // 获取手牌
//    [[nodiscard]] valarray<Majang>& getFlowerTilesOf(int idx);                 // 获取花牌
//    [[nodiscard]] valarray<Majang>& getChiOf(int idx);                         // 获取鸣牌中的“吃"
//    [[nodiscard]] valarray<Majang>& getPengOf(int idx);                        // 获取鸣牌中的“碰"
//    [[nodiscard]] valarray<Majang>& getGangOf(int idx);                        // 获取鸣牌中的“杠”
////    [[nodiscard]] valarray<Majang>& getDiscards();                             // 获取弃牌堆
//    [[nodiscard]] valarray<Majang>& getTilePlayedOf(int idx);                  // 获取某名玩家打过的所有牌
//
//    [[nodiscard]] const valarray<Majang>& getInHand() const;                   //  获取手牌的常引用，下同上
//    [[nodiscard]] const valarray<Majang>& getFlowerTilesOf(int idx) const;
//    [[nodiscard]] const valarray<Majang>& getChiOf(int idx) const;
//    [[nodiscard]] const valarray<Majang>& getPengOf(int idx) const;
//    [[nodiscard]] const valarray<Majang>& getGangOf(int idx) const;
////    [[nodiscard]] const valarray<Majang>& getDiscards() const;
//    [[nodiscard]] const valarray<Majang>& getTilePlayedOf(int idx) const;

	[[nodiscard]] vector<Majang>& getInHand();                               // 获取手牌
	[[nodiscard]] vector<Majang>& getFlowerTilesOf(int idx);                 // 获取花牌
	[[nodiscard]] vector<Majang>& getChiOf(int idx);                         // 获取鸣牌中的“吃"
	[[nodiscard]] vector<Majang>& getPengOf(int idx);                        // 获取鸣牌中的“碰"
	[[nodiscard]] vector<Majang>& getGangOf(int idx);                        // 获取鸣牌中的“杠”
	[[nodiscard]] vector<Majang>& getTilePlayedOf(int idx);                  // 获取某名玩家打过的所有牌

	[[nodiscard]] const vector<Majang>& getInHand() const;                   //  获取手牌的常引用，下同上
	[[nodiscard]] const vector<Majang>& getFlowerTilesOf(int idx) const;
	[[nodiscard]] const vector<Majang>& getChiOf(int idx) const;
	[[nodiscard]] const vector<Majang>& getPengOf(int idx) const;
	[[nodiscard]] const vector<Majang>& getGangOf(int idx) const;
	[[nodiscard]] const vector<Majang>& getTilePlayedOf(int idx) const;

	void decTileLeft(int idx);                                                  // 在减少idx对应的牌的数量的同时，减少总数的数量
	void decTileLeft(Majang mj);                                               // 同上
	[[nodiscard]] const int & getTileLeft(int idx) const;                       // 获得idx对应的牌的剩余数量
	[[nodiscard]] const int & getTotalLeft() const;                             // 获得所有牌的剩余数量

	void incSecretGangCntOf(int idx);                                           // 给某名玩家的暗杠数量+1
	[[nodiscard]] int getSecretGangCntOf(int idx) const;                        // 获取某名玩家的暗杠数量

	void setCurPosition(int curP);                                              // 设置“我们"当前的编号（座位
	[[nodiscard]] int getCurPosition() const;                                   // 获得我们当前的编号
	void setCurTurnPlayer(int curTP);                                           // 设置当前回合行动的玩家
	[[nodiscard]] int getCurTurnPlayer() const;                                 // 获得当前回合行动的玩家的编号
	void setLastPlayed(const Majang& lastTile);                                // 设置上一个被打出来的麻将
	[[nodiscard]] const Majang& getLastPlayed() const;                         // 获得上一个被打出来的麻将的常引用
	void setInHandCntOf(int idx, int cnt);                                      // 将idx号玩家的手牌数量设置为cnt
	[[nodiscard]] int getInHandCntOf(int idx) const;                            // 获取idx号玩家的手牌数量
	void incInHandCntOf(int idx);                                               // 给idx号玩家的手牌数量+1
	void decInHandCntOf(int idx);                                               // 给idx号玩家的手牌数量-1

	void deleteFromInHand(const Majang& toDelete);                             // 从手牌中去除toDelete   //? 可能是一个优化点

	void nxtPosition();                                                         // 将当前的编号（座位）移动到下一个，！应该不常用
	void nxtTurn();                                                             // 进入下一回合
};

#endif
/*** End of inlined file: StateContainer.h ***/

// 直接使用botzone上的内置算番器（因为我实在不知道怎么配置了
#ifdef _BOTZONE_ONLINE
#include "MahjongGB/MahjongGB.h"
#else

/*** Start of inlined file: MahjongGB.h ***/
#ifndef MAHJONG_H
#define MAHJONG_H

#include <utility>
#include <vector>
#include <string>

//CPP

/*** Start of inlined file: MahjongGB.cpp ***/
#include <algorithm>
#include <utility>
#include <vector>
#include <string>
#include <unordered_map>

/*** Start of inlined file: fan_calculator.h ***/
#ifndef __MAHJONG_ALGORITHM__FAN_CALCULATOR_H__
#define __MAHJONG_ALGORITHM__FAN_CALCULATOR_H__


/*** Start of inlined file: tile.h ***/
#ifndef __MAHJONG_ALGORITHM__TILE_H__
#define __MAHJONG_ALGORITHM__TILE_H__

#include <stddef.h>
#include <stdint.h>

 // force inline
#ifndef FORCE_INLINE
#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#define FORCE_INLINE __forceinline
#elif defined(__GNUC__) && ((__GNUC__ << 8 | __GNUC_MINOR__) >= 0x301)
#define FORCE_INLINE __inline__ __attribute__((__always_inline__))
#else
#define FORCE_INLINE inline
#endif
#endif

 // unreachable
#ifndef UNREACHABLE
#if defined(_MSC_VER) && (_MSC_VER >= 1300)
#define UNREACHABLE() __assume(0)
#elif defined(__clang__) || (defined(__GNUC__) && ((__GNUC__ << 8 | __GNUC_MINOR__) >= 0x405))
#define UNREACHABLE() __builtin_unreachable()
#else
#define UNREACHABLE() assert(0)
#endif
#endif

namespace mahjong {

/**
 * @brief 代码注释中用到的术语简介
 * - 顺子：数牌中，花色相同序数相连的3张牌。
 * - 刻子：三张相同的牌。碰出的为明刻，未碰出的为暗刻。俗称坎。杠也算刻子，明杠算明刻，暗杠算暗刻。
 * - 面子：顺子和刻子的统称。俗称一句话、一坎牌。
 * - 雀头：基本和牌形式中，单独组合的对子，也叫将、眼。
 * - 基本和型：4面子1雀头的和牌形式。
 * - 特殊和型：非4面子1雀头的和牌形式，在国标规则中，有七对、十三幺、全不靠等特殊和型。
 * - 门清：也叫门前清，指不吃、不碰、不明杠的状态。特殊和型必然是门清状态。暗杠虽然不破门清，但会暴露出手牌不是特殊和型的信息。
 * - 副露：吃牌、碰牌、杠牌的统称，即利用其他选手打出的牌完成自己手牌面子的行为，一般不包括暗杠，也叫鸣牌，俗称动牌。
 *     副露有时候也包括暗杠，此时将暗杠称为之暗副露，而吃、碰、明杠称为明副露。
 * - 立牌：整个手牌除去吃、碰、杠之后的牌。
 * - 手牌：包括立牌和吃、碰、杠的牌，有时仅指立牌。
 * - 听牌：只差所需要的一张牌即能和牌的状态。俗称下叫、落叫、叫和（糊）。
 * - 一上听：指差一张就能听牌的状态，也叫一向听、一入听。以此类推有二上听、三上听、N上听。
 * - 上听数：达到听牌状态需要牌的张数。
 * - 有效牌：能使上听数减少的牌，也称进张牌、上张牌。
 * - 改良牌：能使有效牌增加的牌。通俗来说就是能使进张面变宽的牌。
 * - 对子：两张相同的牌。雀头一定是对子，但对子不一定是雀头。
 * - 两面：数牌中，花色相同数字相邻的两张牌，如45m，与两侧的牌都构成顺子。也叫两头。
 * - 嵌张：数牌中，花色相同数字相隔1的两张牌，如57s，只能与中间的牌构成顺子，中间的这张牌称为嵌张。
 * - 边张：也是数字相邻的两张牌，但由于处在边界位置，只能与一侧的牌能构成顺子，如12只能与3构成顺子、89只能与7构成顺子，这张3或者7便称为边张。
 * - 搭子：指差一张牌就能构成1组面子的两张牌。其形态有刻子搭子（即对子）、两面搭子、嵌张搭子、边张搭子。
 * - 复合搭子：多张牌构成的搭子。常见的有：连嵌张、两面带对子、嵌张带对子、边张带对子等等形态。
 * - 对倒：听牌时，其他牌都已经构成面子，剩余两对，只需任意一对成刻即可和牌，此时另一对充当雀头，这种听牌形态叫对倒，也叫双碰、对碰、对杵。
 */

/**
 * @addtogroup tile
 * @{
 */

/**
 * @brief 花色
 */
typedef uint8_t suit_t;

/**
 * @brief 点数
 */
typedef uint8_t rank_t;

#define TILE_SUIT_NONE          0  ///< 无效
#define TILE_SUIT_CHARACTERS    1  ///< 万子（CHARACTERS）
#define TILE_SUIT_BAMBOO        2  ///< 条子（BAMBOO）
#define TILE_SUIT_DOTS          3  ///< 饼子（DOTS）
#define TILE_SUIT_HONORS        4  ///< 字牌（HONORS）

/**
 * @brief 牌\n
 * 内存结构：
 * - 0-3 4bit 牌的点数
 * - 4-7 4bit 牌的花色
 * 合法的牌为：
 * - 0x11 - 0x19 万子（CHARACTERS）
 * - 0x21 - 0x29 条子（BAMBOO）
 * - 0x31 - 0x39 饼子（DOTS）
 * - 0x41 - 0x47 字牌（HONORS）
 * - 0x51 - 0x58 花牌（FLOWER）
 */
typedef uint8_t tile_t;

/**
 * @brief 生成一张牌
 *  函数不检查输入的合法性。如果输入不合法的值，将无法保证合法返回值的合法性
 * @param [in] suit 花色
 * @param [in] rank 点数
 * @return tile_t 牌
 */
static FORCE_INLINE tile_t make_tile(suit_t suit, rank_t rank) {
	return (((suit & 0xF) << 4) | (rank & 0xF));
}

/**
 * @brief 获取牌的花色
 *  函数不检查输入的合法性。如果输入不合法的值，将无法保证合法返回值的合法性
 * @param [in] tile 牌
 * @return suit_t 花色
 */
static FORCE_INLINE suit_t tile_get_suit(tile_t tile) {
	return ((tile >> 4) & 0xF);
}

/**
 * @brief 判断是否为花牌
 *  函数不检查输入的合法性。如果输入不合法的值，将无法保证合法返回值的合法性
 * @param [in] tile 牌
 * @return bool
 */
static FORCE_INLINE bool is_flower(tile_t tile) {
	return ((tile >> 4) & 0xF) == 5;
}

/**
 * @brief 获取牌的点数
 *  函数不检查输入的合法性。如果输入不合法的值，将无法保证合法返回值的合法性
 * @param [in] tile 牌
 * @return rank_t 点数
 */
static FORCE_INLINE rank_t tile_get_rank(tile_t tile) {
	return (tile & 0xF);
}

/**
 * @brief 所有牌的值，不包括花牌
 */
enum tile_value_t {
	TILE_1m = 0x11, TILE_2m, TILE_3m, TILE_4m, TILE_5m, TILE_6m, TILE_7m, TILE_8m, TILE_9m,
	TILE_1s = 0x21, TILE_2s, TILE_3s, TILE_4s, TILE_5s, TILE_6s, TILE_7s, TILE_8s, TILE_9s,
	TILE_1p = 0x31, TILE_2p, TILE_3p, TILE_4p, TILE_5p, TILE_6p, TILE_7p, TILE_8p, TILE_9p,
	TILE_E  = 0x41, TILE_S , TILE_W , TILE_N , TILE_C , TILE_F , TILE_P ,
	TILE_TABLE_SIZE
};

/**
 * @brief 所有合法的牌，不包括花牌
 */
static const tile_t all_tiles[] = {
	TILE_1m, TILE_2m, TILE_3m, TILE_4m, TILE_5m, TILE_6m, TILE_7m, TILE_8m, TILE_9m,
	TILE_1s, TILE_2s, TILE_3s, TILE_4s, TILE_5s, TILE_6s, TILE_7s, TILE_8s, TILE_9s,
	TILE_1p, TILE_2p, TILE_3p, TILE_4p, TILE_5p, TILE_6p, TILE_7p, TILE_8p, TILE_9p,
	TILE_E , TILE_S , TILE_W , TILE_N , TILE_C , TILE_F , TILE_P
};

/**
 * @brief 牌表类型
 *
 * 说明：在判断听牌、计算上听数等算法中，主流的对于牌有两种存储方式：
 * - 一种是用牌表，各索引表示各种牌拥有的枚数，这种存储方式的优点是在递归计算时削减面子只需要修改表中相应下标的值，缺点是一手牌的总数不方便确定
 * - 另一种是直接用牌的数组，这种存储方式的优点是很容易确定一手牌的总数，缺点是在递归计算时削减面子不方便，需要进行数组删除元素操作
 */
typedef uint16_t tile_table_t[TILE_TABLE_SIZE];

#define PACK_TYPE_NONE 0  ///< 无效
#define PACK_TYPE_CHOW 1  ///< 顺子
#define PACK_TYPE_PUNG 2  ///< 刻子
#define PACK_TYPE_KONG 3  ///< 杠
#define PACK_TYPE_PAIR 4  ///< 雀头

/**
 * @brief 牌组
 *  用于表示一组面子或者雀头
 *
 * 内存结构：
 * - 0-7 8bit tile 牌（对于顺子，则表示中间那张牌，比如234p，那么牌为3p）
 * - 8-11 4bit type 牌组类型，使用PACK_TYPE_xxx宏
 * - 12-13 2bit offer 供牌信息，取值范围为0123\n
 * - 14 1bit promoted 是否为加杠
 *       0表示暗手（暗顺、暗刻、暗杠），非0表示明手（明顺、明刻、明杠）
 *
 *       对于牌组是刻子和杠时，123分别来表示是上家/对家/下家供的\n
 *       对于牌组为顺子时，由于吃牌只能是上家供，这里用123分别来表示第几张是上家供的
 */
typedef uint16_t pack_t;

/**
 * @brief 生成一个牌组
 *  函数不检查输入的合法性。如果输入不合法的值，将无法保证合法返回值的合法性
 * @param [in] offer 供牌信息
 * @param [in] type 牌组类型
 * @param [in] tile 牌（对于顺子，为中间那张牌）
 */
static FORCE_INLINE pack_t make_pack(uint8_t offer, uint8_t type, tile_t tile) {
	return (offer << 12 | (type << 8) | tile);
}

/**
 * @brief 牌组是否为明的
 *  函数不检查输入的合法性。如果输入不合法的值，将无法保证合法返回值的合法性
 * @param [in] pack 牌组
 * @return bool
 */
static FORCE_INLINE bool is_pack_melded(pack_t pack) {
	return !!(pack & 0x3000);
}

/**
 * @brief 牌组是否为加杠
 *  当牌组不是PACK_TYPE_KONG时，结果是无意义的
 *  函数不检查输入的合法性。如果输入不合法的值，将无法保证合法返回值的合法性
 * @param [in] pack 牌组
 * @return bool
 */
static FORCE_INLINE bool is_promoted_kong(pack_t pack) {
	return !!(pack & 0x4000);
}

/**
 * @brief 碰的牌组转换为加杠
 *  当牌组不是PACK_TYPE_PUNG时，结果是无意义的
 *  函数不检查输入的合法性。如果输入不合法的值，将无法保证合法返回值的合法性
 * @param [in] pack 碰的牌组
 * @return pack_t 加杠的牌组
 */
static FORCE_INLINE pack_t promote_pung_to_kong(pack_t pack) {
	return pack | 0x4300;
}

/**
 * @brief 牌组的供牌信息
 *  函数不检查输入的合法性。如果输入不合法的值，将无法保证合法返回值的合法性
 * @param [in] pack 牌组
 * @return uint8_t
 */
static FORCE_INLINE uint8_t pack_get_offer(pack_t pack) {
	return ((pack >> 12) & 0x3);
}

/**
 * @brief 获取牌组的类型
 *  函数不检查输入的合法性。如果输入不合法的值，将无法保证合法返回值的合法性
 * @param [in] pack 牌组
 * @return uint8_t 牌组类型
 */
static FORCE_INLINE uint8_t pack_get_type(pack_t pack) {
	return ((pack >> 8) & 0xF);
}

/**
 * @brief 获取牌的点数
 *  函数不检查输入的合法性。如果输入不合法的值，将无法保证合法返回值的合法性
 * @param [in] pack 牌组
 * @return tile_t 牌（对于顺子，为中间那张牌）
 */
static FORCE_INLINE tile_t pack_get_tile(pack_t pack) {
	return (pack & 0xFF);
}

/**
 * @brief 手牌结构
 *  手牌结构一定满足等式：3*副露的牌组数+立牌数=13
 */
struct hand_tiles_t {
	pack_t fixed_packs[5];      ///< 副露的牌组（面子），包括暗杠
	intptr_t pack_count;        ///< 副露的牌组（面子）数，包括暗杠
	tile_t standing_tiles[13];  ///< 立牌
	intptr_t tile_count;        ///< 立牌数
};

/**
 * @brief 判断是否为绿一色构成牌
 *  函数不检查输入的合法性。如果输入不合法的值，将无法保证合法返回值的合法性
 * @param [in] tile 牌
 * @return bool
 */
static FORCE_INLINE bool is_green(tile_t tile) {
	// 最基本的逐个判断，23468s及发财为绿一色构成牌
	//return (tile == TILE_2s || tile == TILE_3s || tile == TILE_4s || tile == TILE_6s || tile == TILE_8s || tile == TILE_F);

	// 算法原理：
	// 0x48-0x11=0x37=55刚好在一个64位整型的范围内，
	// 用uint64_t的每一位表示一张牌的标记，事先得到一个魔数，
	// 然后每次测试相应位即可
	return !!(0x0020000000AE0000ULL & (1ULL << (tile - TILE_1m)));
}

/**
 * @brief 判断是否为推不倒构成牌
 *  函数不检查输入的合法性。如果输入不合法的值，将无法保证合法返回值的合法性
 * @param [in] tile 牌
 * @return bool
 */
static FORCE_INLINE bool is_reversible(tile_t tile) {
	// 最基本的逐个判断：245689s、1234589p及白板为推不倒构成牌
	//return (tile == TILE_2s || tile == TILE_4s || tile == TILE_5s || tile == TILE_6s || tile == TILE_8s || tile == TILE_9s ||
	//    tile == TILE_1p || tile == TILE_2p || tile == TILE_3p || tile == TILE_4p || tile == TILE_5p || tile == TILE_8p || tile == TILE_9p ||
	//    tile == TILE_P);

	// 算法原理同绿一色构成牌判断函数
	return !!(0x0040019F01BA0000ULL & (1ULL << (tile - TILE_1m)));
}

/**
 * @brief 判断是否为数牌幺九（老头牌）
 *  函数不检查输入的合法性。如果输入不合法的值，将无法保证合法返回值的合法性
 * @param [in] tile 牌
 * @return bool
 */
static FORCE_INLINE bool is_terminal(tile_t tile) {
	// 最基本的逐个判断
	//return (tile == TILE_1m || tile == TILE_9m || tile == TILE_1s || tile == TILE_9s || tile == TILE_1p || tile == TILE_9p);

	// 算法原理：观察数牌幺九的二进制位：
	// 0x11：0001 0001
	// 0x19：0001 1001
	// 0x21：0010 0001
	// 0x29：0010 1001
	// 0x31：0011 0001
	// 0x39：0011 1001
	// 所有牌的低4bit只会出现在0001到1001之间，跟0111位与，只有0001和1001的结果为1
	// 所有数牌的高4bit只会出现在0001到0011之间，跟1100位与，必然为0
	// 于是构造魔数0xC7（1100 0111）跟牌位与，结果为1的，就为数牌幺九
	// 缺陷：低4bit的操作会对0xB、0xD、0xF产生误判，高4bit的操作会对0x01和0x09产生误判
	return ((tile & 0xC7) == 1);
}

/**
 * @brief 判断是否为风牌
 * @param [in] tile 牌
 * @return bool
 */
static FORCE_INLINE bool is_winds(tile_t tile) {
	return (tile > 0x40 && tile < 0x45);
}

/**
 * @brief 判断是否为箭牌（三元牌）
 * @param [in] tile 牌
 * @return bool
 */
static FORCE_INLINE bool is_dragons(tile_t tile) {
	return (tile > 0x44 && tile < 0x48);
}

/**
 * @brief 判断是否为字牌
 * @param [in] tile 牌
 * @return bool
 */
static FORCE_INLINE bool is_honor(tile_t tile) {
	return (tile > 0x40 && tile < 0x48);
}

/**
 * @brief 判断是否为数牌
 * @param [in] tile 牌
 * @return bool
 */
static FORCE_INLINE bool is_numbered_suit(tile_t tile) {
	if (tile < 0x1A) return (tile > 0x10);
	if (tile < 0x2A) return (tile > 0x20);
	if (tile < 0x3A) return (tile > 0x30);
	return false;
}

/**
 * @brief 判断是否为数牌（更快）
 *  函数不检查输入的合法性。如果输入不合法的值，将无法保证合法返回值的合法性
 * @see is_numbered_suit
 * @param [in] tile 牌
 * @return bool
 */
static FORCE_INLINE bool is_numbered_suit_quick(tile_t tile) {
	// 算法原理：数牌为0x11-0x19，0x21-0x29，0x31-0x39，跟0xC0位与，结果为0
	return !(tile & 0xC0);
}

/**
 * @brief 判断是否为幺九牌（包括数牌幺九和字牌）
 * @param [in] tile 牌
 * @return bool
 */
static FORCE_INLINE bool is_terminal_or_honor(tile_t tile) {
	return is_terminal(tile) || is_honor(tile);
}

/**
 * @brief 判断两张牌花色是否相同（更快）
 *  函数不检查输入的合法性。如果输入不合法的值，将无法保证合法返回值的合法性
 * @param [in] tile0 牌0
 * @param [in] tile1 牌1
 * @return bool
 */
static FORCE_INLINE bool is_suit_equal_quick(tile_t tile0, tile_t tile1) {
	// 算法原理：高4bit表示花色
	return ((tile0 & 0xF0) == (tile1 & 0xF0));
}

/**
 * @brief 判断两张牌点数是否相同（更快）
 *  函数不检查输入的合法性。如果输入不合法的值，将无法保证合法返回值的合法性
 * @param [in] tile0 牌0
 * @param [in] tile1 牌1
 * @return bool
 */
static FORCE_INLINE bool is_rank_equal_quick(tile_t tile0, tile_t tile1) {
	// 算法原理：低4bit表示花色。高4bit设置为C是为了过滤掉字牌
	return ((tile0 & 0xCF) == (tile1 & 0xCF));
}

/**
 * end group
 * @}
 */

}

#endif

/*** End of inlined file: tile.h ***/

#define SUPPORT_CONCEALED_KONG_AND_MELDED_KONG 1  // 支持明暗杠

namespace mahjong {

/**
 * @addtogroup calculator
 * @{
 */

/**
 * @brief 番种
 */
enum fan_t {
	FAN_NONE = 0,                       ///< 无效
	BIG_FOUR_WINDS,                     ///< 大四喜
	BIG_THREE_DRAGONS,                  ///< 大三元
	ALL_GREEN,                          ///< 绿一色
	NINE_GATES,                         ///< 九莲宝灯
	FOUR_KONGS,                         ///< 四杠
	SEVEN_SHIFTED_PAIRS,                ///< 连七对
	THIRTEEN_ORPHANS,                   ///< 十三幺

	ALL_TERMINALS,                      ///< 清幺九
	LITTLE_FOUR_WINDS,                  ///< 小四喜
	LITTLE_THREE_DRAGONS,               ///< 小三元
	ALL_HONORS,                         ///< 字一色
	FOUR_CONCEALED_PUNGS,               ///< 四暗刻
	PURE_TERMINAL_CHOWS,                ///< 一色双龙会

	QUADRUPLE_CHOW,                     ///< 一色四同顺
	FOUR_PURE_SHIFTED_PUNGS,            ///< 一色四节高

	FOUR_PURE_SHIFTED_CHOWS,            ///< 一色四步高
	THREE_KONGS,                        ///< 三杠
	ALL_TERMINALS_AND_HONORS,           ///< 混幺九

	SEVEN_PAIRS,                        ///< 七对
	GREATER_HONORS_AND_KNITTED_TILES,   ///< 七星不靠
	ALL_EVEN_PUNGS,                     ///< 全双刻
	FULL_FLUSH,                         ///< 清一色
	PURE_TRIPLE_CHOW,                   ///< 一色三同顺
	PURE_SHIFTED_PUNGS,                 ///< 一色三节高
	UPPER_TILES,                        ///< 全大
	MIDDLE_TILES,                       ///< 全中
	LOWER_TILES,                        ///< 全小

	PURE_STRAIGHT,                      ///< 清龙
	THREE_SUITED_TERMINAL_CHOWS,        ///< 三色双龙会
	PURE_SHIFTED_CHOWS,                 ///< 一色三步高
	ALL_FIVE,                           ///< 全带五
	TRIPLE_PUNG,                        ///< 三同刻
	THREE_CONCEALED_PUNGS,              ///< 三暗刻

	LESSER_HONORS_AND_KNITTED_TILES,    ///< 全不靠
	KNITTED_STRAIGHT,                   ///< 组合龙
	UPPER_FOUR,                         ///< 大于五
	LOWER_FOUR,                         ///< 小于五
	BIG_THREE_WINDS,                    ///< 三风刻

	MIXED_STRAIGHT,                     ///< 花龙
	REVERSIBLE_TILES,                   ///< 推不倒
	MIXED_TRIPLE_CHOW,                  ///< 三色三同顺
	MIXED_SHIFTED_PUNGS,                ///< 三色三节高
	CHICKEN_HAND,                       ///< 无番和
	LAST_TILE_DRAW,                     ///< 妙手回春
	LAST_TILE_CLAIM,                    ///< 海底捞月
	OUT_WITH_REPLACEMENT_TILE,          ///< 杠上开花
	ROBBING_THE_KONG,                   ///< 抢杠和

	ALL_PUNGS,                          ///< 碰碰和
	HALF_FLUSH,                         ///< 混一色
	MIXED_SHIFTED_CHOWS,                ///< 三色三步高
	ALL_TYPES,                          ///< 五门齐
	MELDED_HAND,                        ///< 全求人
	TWO_CONCEALED_KONGS,                ///< 双暗杠
	TWO_DRAGONS_PUNGS,                  ///< 双箭刻

	OUTSIDE_HAND,                       ///< 全带幺
	FULLY_CONCEALED_HAND,               ///< 不求人
	TWO_MELDED_KONGS,                   ///< 双明杠
	LAST_TILE,                          ///< 和绝张

	DRAGON_PUNG,                        ///< 箭刻
	PREVALENT_WIND,                     ///< 圈风刻
	SEAT_WIND,                          ///< 门风刻
	CONCEALED_HAND,                     ///< 门前清
	ALL_CHOWS,                          ///< 平和
	TILE_HOG,                           ///< 四归一
	DOUBLE_PUNG,                        ///< 双同刻
	TWO_CONCEALED_PUNGS,                ///< 双暗刻
	CONCEALED_KONG,                     ///< 暗杠
	ALL_SIMPLES,                        ///< 断幺

	PURE_DOUBLE_CHOW,                   ///< 一般高
	MIXED_DOUBLE_CHOW,                  ///< 喜相逢
	SHORT_STRAIGHT,                     ///< 连六
	TWO_TERMINAL_CHOWS,                 ///< 老少副
	PUNG_OF_TERMINALS_OR_HONORS,        ///< 幺九刻
	MELDED_KONG,                        ///< 明杠
	ONE_VOIDED_SUIT,                    ///< 缺一门
	NO_HONORS,                          ///< 无字
	EDGE_WAIT,                          ///< 边张
	CLOSED_WAIT,                        ///< 嵌张
	SINGLE_WAIT,                        ///< 单钓将
	SELF_DRAWN,                         ///< 自摸

	FLOWER_TILES,                       ///< 花牌

#if SUPPORT_CONCEALED_KONG_AND_MELDED_KONG
	CONCEALED_KONG_AND_MELDED_KONG,     ///< 明暗杠
#endif

	FAN_TABLE_SIZE
};

/**
 * @brief 风（用来表示圈风门风）
 */
enum class wind_t {
	EAST, SOUTH, WEST, NORTH
};

/**
 * @brief 和牌标记
 */
typedef uint8_t win_flag_t;

/**
 * @name win flag
 * @{
 */
#define WIN_FLAG_DISCARD    0   ///< 点和
#define WIN_FLAG_SELF_DRAWN 1   ///< 自摸
#define WIN_FLAG_4TH_TILE   2   ///< 绝张
#define WIN_FLAG_ABOUT_KONG 4   ///< 关于杠，复合点和时为枪杠和，复合自摸则为杠上开花
#define WIN_FLAG_WALL_LAST  8   ///< 牌墙最后一张，复合点和时为海底捞月，复合自摸则为妙手回春
#define WIN_FLAG_INIT       16  ///< 起手，复合点和时为地和，复合自摸则为天和

/**
 * @}
 */

/**
 * @name error codes
 * @{
 */
#define ERROR_WRONG_TILES_COUNT -1              ///< 错误的张数
#define ERROR_TILE_COUNT_GREATER_THAN_4 -2      ///< 某张牌出现超过4枚
#define ERROR_NOT_WIN -3                        ///< 没和牌
/**
 * @}
 */

/**
 * @brief 检查算番的输入是否合法
 *
 * @param [in] hand_tiles 手牌
 * @param [in] win_tile 和牌张
 * @retval 0 成功
 * @retval ERROR_WRONG_TILES_COUNT 错误的张数
 * @retval ERROR_TILE_COUNT_GREATER_THAN_4 某张牌出现超过4枚
 */
int check_calculator_input(const hand_tiles_t *hand_tiles, tile_t win_tile);

/**
 * @brief 算番参数
 */
struct calculate_param_t {
	hand_tiles_t hand_tiles;    ///< 手牌
	tile_t win_tile;            ///< 和牌张
	uint8_t flower_count;       ///< 花牌数
	win_flag_t win_flag;        ///< 和牌标记
	wind_t prevalent_wind;      ///< 圈风
	wind_t seat_wind;           ///< 门风
};

/**
 * @brief 番表
 */
typedef uint16_t fan_table_t[FAN_TABLE_SIZE];

/**
 * @brief 算番
 *
 * @param [in] calculate_param 算番参数
 * @param [out] fan_table 番表，当有某种番时，相应的会设置为这种番出现的次数
 * @retval >0 番数
 * @retval ERROR_WRONG_TILES_COUNT 错误的张数
 * @retval ERROR_TILE_COUNT_GREATER_THAN_4 某张牌出现超过4枚
 * @retval ERROR_NOT_WIN 没和牌
 */
int calculate_fan(const calculate_param_t *calculate_param, fan_table_t *fan_table);

#if 0

/**
 * @brief 番名（英文）
 */
static const char *fan_name[] = {
	"None",
	"Big Four Winds", "Big Three Dragons", "All Green", "Nine Gates", "Four Kongs", "Seven Shifted Pairs", "Thirteen Orphans",
	"All Terminals", "Little Four Winds", "Little Three Dragons", "All Honors", "Four Concealed Pungs", "Pure Terminal Chows",
	"Quadruple Chow", "Four Pure Shifted Pungs",
	"Four Pure Shifted Chows", "Three Kongs", "All Terminals and Honors",
	"Seven Pairs", "Greater Honors and Knitted Tiles", "All Even Pungs", "Full Flush", "Pure Triple Chow", "Pure Shifted Pungs", "Upper Tiles", "Middle Tiles", "Lower Tiles",
	"Pure Straight", "Three-Suited Terminal Chows", "Pure Shifted Chows", "All Five", "Triple Pung", "Three Concealed Pungs",
	"Lesser Honors and Knitted Tiles", "Knitted Straight", "Upper Four", "Lower Four", "Big Three Winds",
	"Mixed Straight", "Reversible Tiles", "Mixed Triple Chow", "Mixed Shifted Pungs", "Chicken Hand", "Last Tile Draw", "Last Tile Claim", "Out with Replacement Tile", "Robbing The Kong",
	"All Pungs", "Half Flush", "Mixed Shifted Chows", "All Types", "Melded Hand", "Two Concealed Kongs", "Two Dragons Pungs",
	"Outside Hand", "Fully Concealed Hand", "Two Melded Kongs", "Last Tile",
	"Dragon Pung", "Prevalent Wind", "Seat Wind", "Concealed Hand", "All Chows", "Tile Hog", "Double Pung",
	"Two Concealed Pungs", "Concealed Kong", "All Simples",
	"Pure Double Chow", "Mixed Double Chow", "Short Straight", "Two Terminal Chows", "Pung of Terminals or Honors", "Melded Kong", "One Voided Suit", "No Honors", "Edge Wait", "Closed Wait", "Single Wait", "Self-Drawn",
	"Flower Tiles"
#if SUPPORT_CONCEALED_KONG_AND_MELDED_KONG
	, "Concealed Kong and Melded Kong"
#endif
};

#else

#ifdef _MSC_VER
#pragma execution_character_set("utf-8")
#endif

// u8 literal prefix
#ifndef __UTF8_TEXT
// VS2015 GCC4.7 Clang5.0
#if (defined(_MSC_VER) && (_MSC_VER >= 1900)) || (defined(__GNUC__) && ((__GNUC__ << 8 | __GNUC_MINOR__) >= 0x407)) || (defined(__clang__) && (__clang_major__ >= 5))
#define __UTF8_TEXT(quote) u8 ## quote
#else
#define __UTF8_TEXT(quote) quote
#endif
#endif

#ifndef __UTF8
#define __UTF8(quote) __UTF8_TEXT(quote)
#endif

/**
 * @brief 番名（简体中文）
 */
static const char *fan_name[] = {
	__UTF8("无"),
	__UTF8("大四喜"), __UTF8("大三元"), __UTF8("绿一色"), __UTF8("九莲宝灯"), __UTF8("四杠"), __UTF8("连七对"), __UTF8("十三幺"),
	__UTF8("清幺九"), __UTF8("小四喜"), __UTF8("小三元"), __UTF8("字一色"), __UTF8("四暗刻"), __UTF8("一色双龙会"),
	__UTF8("一色四同顺"), __UTF8("一色四节高"),
	__UTF8("一色四步高"), __UTF8("三杠"), __UTF8("混幺九"),
	__UTF8("七对"), __UTF8("七星不靠"), __UTF8("全双刻"), __UTF8("清一色"), __UTF8("一色三同顺"), __UTF8("一色三节高"), __UTF8("全大"), __UTF8("全中"), __UTF8("全小"),
	__UTF8("清龙"), __UTF8("三色双龙会"), __UTF8("一色三步高"), __UTF8("全带五"), __UTF8("三同刻"), __UTF8("三暗刻"),
	__UTF8("全不靠"), __UTF8("组合龙"), __UTF8("大于五"), __UTF8("小于五"), __UTF8("三风刻"),
	__UTF8("花龙"), __UTF8("推不倒"), __UTF8("三色三同顺"), __UTF8("三色三节高"), __UTF8("无番和"), __UTF8("妙手回春"), __UTF8("海底捞月"), __UTF8("杠上开花"), __UTF8("抢杠和"),
	__UTF8("碰碰和"), __UTF8("混一色"), __UTF8("三色三步高"), __UTF8("五门齐"), __UTF8("全求人"), __UTF8("双暗杠"), __UTF8("双箭刻"),
	__UTF8("全带幺"), __UTF8("不求人"), __UTF8("双明杠"), __UTF8("和绝张"),
	__UTF8("箭刻"), __UTF8("圈风刻"), __UTF8("门风刻"), __UTF8("门前清"), __UTF8("平和"), __UTF8("四归一"), __UTF8("双同刻"), __UTF8("双暗刻"), __UTF8("暗杠"), __UTF8("断幺"),
	__UTF8("一般高"), __UTF8("喜相逢"), __UTF8("连六"), __UTF8("老少副"), __UTF8("幺九刻"), __UTF8("明杠"), __UTF8("缺一门"), __UTF8("无字"), __UTF8("边张"), __UTF8("嵌张"), __UTF8("单钓将"), __UTF8("自摸"),
	__UTF8("花牌")
#if SUPPORT_CONCEALED_KONG_AND_MELDED_KONG
	, __UTF8("明暗杠")
#endif
};

#endif

/**
 * @brief 番值
 */
static const uint16_t fan_value_table[FAN_TABLE_SIZE] = {
	0,
	88, 88, 88, 88, 88, 88, 88,
	64, 64, 64, 64, 64, 64,
	48, 48,
	32, 32, 32,
	24, 24, 24, 24, 24, 24, 24, 24, 24,
	16, 16, 16, 16, 16, 16,
	12, 12, 12, 12, 12,
	8, 8, 8, 8, 8, 8, 8, 8, 8,
	6, 6, 6, 6, 6, 6, 6,
	4, 4, 4, 4,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1
#if SUPPORT_CONCEALED_KONG_AND_MELDED_KONG
	, 5
#endif
};

/**
 * @brief 判断立牌是否包含和牌
 * 如果是，则必然不是和绝张
 *
 * @param [in] standing_tiles 立牌
 * @param [in] standing_cnt 立牌数
 * @param [in] win_tile 和牌张
 * @return bool
 */
bool is_standing_tiles_contains_win_tile(const tile_t *standing_tiles, intptr_t standing_cnt, tile_t win_tile);

/**
 * @brief 统计和牌在副露牌组中出现的张数
 * 如果出现3张，则必然和绝张
 *
 * @param [in] fixed_packs 副露牌组
 * @param [in] fixed_cnt 副露牌组数
 * @param [in] win_tile 和牌张
 * @return size_t
 */
size_t count_win_tile_in_fixed_packs(const pack_t *fixed_packs, intptr_t fixed_cnt, tile_t win_tile);

/**
 * @brief 判断副露牌组是否包含杠
 *
 * @param [in] fixed_packs 副露牌组
 * @param [in] fixed_cnt 副露牌组数
 * @return bool
 */
bool is_fixed_packs_contains_kong(const pack_t *fixed_packs, intptr_t fixed_cnt);

/**
 * end group
 * @}
 */

}

#endif

/*** End of inlined file: fan_calculator.h ***/


#include <cstring>
#include <iostream>

using namespace std;

static unordered_map<string, mahjong::tile_t> str2tile;

vector<pair<int, string> > MahjongFanCalculator(
	vector<pair<string, pair<string, int> > > pack,
	vector<string> hand,
	string winTile,
	int flowerCount,
	bool isZIMO,
	bool isJUEZHANG,
	bool isGANG,
	bool isLAST,
	int menFeng,
	int quanFeng)
{
	vector<pair<int,string>> ans;
	mahjong::calculate_param_t calculate_param;
	mahjong::fan_table_t fan_table;
	memset(&calculate_param, 0, sizeof(mahjong::calculate_param_t));
	memset(&fan_table, 0, sizeof(mahjong::fan_table_t));
	calculate_param.hand_tiles.tile_count = hand.size();
	for(unsigned int i = 0; i < hand.size(); i++) {
		if(str2tile.find(hand[i]) == str2tile.end()){
			throw string("ERROE_WRONG_TILE_CODE");
		}
		calculate_param.hand_tiles.standing_tiles[i] = str2tile[hand[i]];
	}
	calculate_param.hand_tiles.pack_count = pack.size();
	for(unsigned int i = 0; i < pack.size(); i++) {
		pair<string, pair<string, int>> &sPack = pack[i];
		mahjong::pack_t &dPack = calculate_param.hand_tiles.fixed_packs[i];
		if(sPack.first == "PENG") {
			dPack = mahjong::make_pack(sPack.second.second, PACK_TYPE_PUNG, str2tile[sPack.second.first]);
		} else if(sPack.first == "GANG") {
			dPack = mahjong::make_pack(sPack.second.second, PACK_TYPE_KONG, str2tile[sPack.second.first]);
		} else if(sPack.first == "CHI"){
			dPack = mahjong::make_pack(sPack.second.second, PACK_TYPE_CHOW, str2tile[sPack.second.first]);
		} else {
			throw string("ERROE_WRONG_PACK_CODE");
		}
	}
	calculate_param.win_tile = str2tile[winTile];
	calculate_param.flower_count = flowerCount;
	if(isZIMO) {
		calculate_param.win_flag |= WIN_FLAG_SELF_DRAWN;
	}
	if(isLAST) {
		calculate_param.win_flag |= WIN_FLAG_WALL_LAST;
	}
	if(isJUEZHANG) {
		calculate_param.win_flag |= WIN_FLAG_4TH_TILE;
	}
	if(isGANG) {
		calculate_param.win_flag |= WIN_FLAG_ABOUT_KONG;
	}
	calculate_param.prevalent_wind = (mahjong::wind_t)quanFeng;
	calculate_param.seat_wind = (mahjong::wind_t)menFeng;
	int re = mahjong::calculate_fan(&calculate_param, &fan_table);
	if(re == -1) {
		throw string("ERROR_WRONG_TILES_COUNT");
	}else if(re == -2) {
		throw string("ERROR_TILE_COUNT_GREATER_THAN_4");
	}else if(re == -3) {
		throw string("ERROR_NOT_WIN");
	}
	for(int i = 0; i < mahjong::FAN_TABLE_SIZE; i++) {
		if(fan_table[i] > 0) {
			ans.push_back(make_pair(fan_table[i]*mahjong::fan_value_table[i],mahjong::fan_name[i]));
		}
	}
	return ans;
}

void MahjongInit()
{
	for(int i = 1; i <= 9; i++) {
		str2tile["W" + to_string(i)] = mahjong::make_tile(TILE_SUIT_CHARACTERS, i);
		str2tile["B" + to_string(i)] = mahjong::make_tile(TILE_SUIT_DOTS, i);
		str2tile["T" + to_string(i)] = mahjong::make_tile(TILE_SUIT_BAMBOO, i);
	}
	for(int i = 1; i <= 4; i++) {
		str2tile["F" + to_string((i))] = mahjong::make_tile(TILE_SUIT_HONORS, i);
	}
	for(int i = 1; i <= 3; i++) {
		str2tile["J" + to_string((i))] = mahjong::make_tile(TILE_SUIT_HONORS, i + 4);
	}
}
/*** End of inlined file: MahjongGB.cpp ***/



/*** Start of inlined file: fan_calculator.cpp ***/
#include <assert.h>
#include <stddef.h>
#include <string.h>
#include <algorithm>
#include <iterator>

/*** Start of inlined file: standard_tiles.h ***/
#ifndef __MAHJONG_ALGORITHM__STANDARD_TILES_H__
#define __MAHJONG_ALGORITHM__STANDARD_TILES_H__

namespace mahjong {

// 十三幺13面听
static const tile_t standard_thirteen_orphans[13] = {
	TILE_1m, TILE_9m, TILE_1s, TILE_9s, TILE_1p, TILE_9p, TILE_E, TILE_S, TILE_W, TILE_N, TILE_C, TILE_F, TILE_P
};

// 组合龙只有如下6种
// 147m 258s 369p
// 147m 369s 258p
// 258m 147s 369p
// 258m 369s 147p
// 369m 147s 258p
// 369m 258s 147p
static const tile_t standard_knitted_straight[6][9] = {
	{ TILE_1m, TILE_4m, TILE_7m, TILE_2s, TILE_5s, TILE_8s, TILE_3p, TILE_6p, TILE_9p },
	{ TILE_1m, TILE_4m, TILE_7m, TILE_3s, TILE_6s, TILE_9s, TILE_2p, TILE_5p, TILE_8p },
	{ TILE_2m, TILE_5m, TILE_8m, TILE_1s, TILE_4s, TILE_7s, TILE_3p, TILE_6p, TILE_9p },
	{ TILE_2m, TILE_5m, TILE_8m, TILE_3s, TILE_6s, TILE_9s, TILE_1p, TILE_4p, TILE_7p },
	{ TILE_3m, TILE_6m, TILE_9m, TILE_1s, TILE_4s, TILE_7s, TILE_2p, TILE_5p, TILE_8p },
	{ TILE_3m, TILE_6m, TILE_9m, TILE_2s, TILE_5s, TILE_8s, TILE_1p, TILE_4p, TILE_7p },
};

}

#endif

/*** End of inlined file: standard_tiles.h ***/



/*** Start of inlined file: shanten.h ***/
#ifndef __MAHJONG_ALGORITHM__SHANTEN_H__
#define __MAHJONG_ALGORITHM__SHANTEN_H__

namespace mahjong {

/**
 * @brief 牌组转换成牌
 *
 * @param [in] packs 牌组
 * @param [in] pack_cnt 牌组的数量
 * @param [out] tiles 牌
 * @param [in] tile_cnt 牌的最大数量
 * @return intptr_t 牌的实际数量
 */
intptr_t packs_to_tiles(const pack_t *packs, intptr_t pack_cnt, tile_t *tiles, intptr_t tile_cnt);

/**
 * @brief 将牌打表
 *
 * @param [in] tiles 牌
 * @param [in] cnt 牌的数量
 * @param [out] cnt_table 牌的数量表
 */
void map_tiles(const tile_t *tiles, intptr_t cnt, tile_table_t *cnt_table);

/**
 * @brief 将手牌打表
 *
 * @param [in] hand_tiles 手牌
 * @param [out] cnt_table 牌的数量表
 * @return bool 手牌结构是否正确。即是否符合：副露组数*3+立牌数=13
 */
bool map_hand_tiles(const hand_tiles_t *hand_tiles, tile_table_t *cnt_table);

/**
 * @brief 将表转换成牌
 *
 * @param [in] cnt_table 牌的数量表
 * @param [out] tiles 牌
 * @param [in] max_cnt 牌的最大数量
 * @return intptr_t 牌的实际数量
 */
intptr_t table_to_tiles(const tile_table_t &cnt_table, tile_t *tiles, intptr_t max_cnt);

/**
 * @brief 有效牌标记表类型
 */
typedef bool useful_table_t[TILE_TABLE_SIZE];

/**
 * @addtogroup shanten
 * @{
 */

/**
 * @addtogroup basic_form
 * @{
 */

/**
 * @brief 基本和型上听数
 *
 * @param [in] standing_tiles 立牌
 * @param [in] standing_cnt 立牌数
 * @param [out] useful_table 有效牌标记表（可为null）
 * @return int 上听数
 */
int basic_form_shanten(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *useful_table);

/**
 * @brief 基本和型是否听牌
 *
 * @param [in] standing_tiles 立牌
 * @param [in] standing_cnt 立牌数
 * @param [out] waiting_table 听牌标记表（可为null）
 * @return bool 是否听牌
 */
bool is_basic_form_wait(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *waiting_table);

/**
 * @brief 基本和型是否和牌
 *
 * @param [in] standing_tiles 立牌
 * @param [in] standing_cnt 立牌数
 * @param [in] test_tile 测试的牌
 * @return bool 是否和牌
 */
bool is_basic_form_win(const tile_t *standing_tiles, intptr_t standing_cnt, tile_t test_tile);

/**
 * end group
 * @}
 */

/**
 * @addtogroup seven_pairs
 * @{
 */

/**
 * @brief 七对上听数
 *
 * @param [in] standing_tiles 立牌
 * @param [in] standing_cnt 立牌数
 * @param [out] useful_table 有效牌标记表（可为null）
 * @return int 上听数
 */
int seven_pairs_shanten(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *useful_table);

/**
 * @brief 七对是否听牌
 *
 * @param [in] standing_tiles 立牌
 * @param [in] standing_cnt 立牌数
 * @param [out] waiting_table 听牌标记表（可为null）
 * @return bool 是否听牌
 */
bool is_seven_pairs_wait(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *waiting_table);

/**
 * @brief 七对是否和牌
 *
 * @param [in] standing_tiles 立牌
 * @param [in] standing_cnt 立牌数
 * @param [in] test_tile 测试的牌
 * @return bool 是否和牌
 */
bool is_seven_pairs_win(const tile_t *standing_tiles, intptr_t standing_cnt, tile_t test_tile);

/**
 * end group
 * @}
 */

/**
 * @addtogroup thirteen_orphans
 * @{
 */

/**
 * @brief 十三幺上听数
 *
 * @param [in] standing_tiles 立牌
 * @param [in] standing_cnt 立牌数
 * @param [out] useful_table 有效牌标记表（可为null）
 * @return int 上听数
 */
int thirteen_orphans_shanten(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *useful_table);

/**
 * @brief 十三幺是否听牌
 *
 * @param [in] standing_tiles 立牌
 * @param [in] standing_cnt 立牌数
 * @param [out] waiting_table 听牌标记表（可为null）
 * @return bool 是否听牌
 */
bool is_thirteen_orphans_wait(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *waiting_table);

/**
 * @brief 十三幺是否和牌
 *
 * @param [in] standing_tiles 立牌
 * @param [in] standing_cnt 立牌数
 * @param [in] test_tile 测试的牌
 * @return bool 是否和牌
 */
bool is_thirteen_orphans_win(const tile_t *standing_tiles, intptr_t standing_cnt, tile_t test_tile);

/**
 * end group
 * @}
 */

/**
 * @addtogroup knitted_straight
 * @{
 */

/**
 * @brief 组合龙上听数
 *
 * @param [in] standing_tiles 立牌
 * @param [in] standing_cnt 立牌数
 * @param [out] useful_table 有效牌标记表（可为null）
 * @return int 上听数
 */
int knitted_straight_shanten(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *useful_table);

/**
 * @brief 组合龙是否听牌
 *
 * @param [in] standing_tiles 立牌
 * @param [in] standing_cnt 立牌数
 * @param [out] waiting_table 听牌标记表（可为null）
 * @return bool 是否听牌
 */
bool is_knitted_straight_wait(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *waiting_table);

/**
 * @brief 组合龙是否和牌
 *
 * @param [in] standing_tiles 立牌
 * @param [in] standing_cnt 立牌数
 * @param [in] test_tile 测试的牌
 * @return bool 是否和牌
 */
bool is_knitted_straight_win(const tile_t *standing_tiles, intptr_t standing_cnt, tile_t test_tile);

/**
 * end group
 * @}
 */

/**
 * @addtogroup honors_and_knitted_tiles
 * @{
 */

/**
 * @brief 全不靠上听数
 *
 * @param [in] standing_tiles 立牌
 * @param [in] standing_cnt 立牌数
 * @param [out] useful_table 有效牌标记表（可为null）
 * @return int 上听数
 */
int honors_and_knitted_tiles_shanten(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *useful_table);

/**
 * @brief 全不靠是否听牌
 *
 * @param [in] standing_tiles 立牌
 * @param [in] standing_cnt 立牌数
 * @param [out] waiting_table 听牌标记表（可为null）
 * @return bool 是否听牌
 */
bool is_honors_and_knitted_tiles_wait(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *waiting_table);

/**
 * @brief 全不靠是否和牌
 *
 * @param [in] standing_tiles 立牌
 * @param [in] standing_cnt 立牌数
 * @param [in] test_tile 测试的牌
 * @return bool 是否和牌
 */
bool is_honors_and_knitted_tiles_win(const tile_t *standing_tiles, intptr_t standing_cnt, tile_t test_tile);

/**
 * end group
 * @}
 */

/**
 * @brief 是否听牌
 *
 * @param [in] hand_tiles 手牌结构
 * @param [out] useful_table 有效牌标记表（可为null）
 * @return bool 是否听牌
 */
bool is_waiting(const hand_tiles_t &hand_tiles, useful_table_t *useful_table);

/**
 * end group
 * @}
 */

/**
 * @name form flags
 * @{
 *  和型
 */
#define FORM_FLAG_BASIC_FORM                0x01  ///< 基本和型
#define FORM_FLAG_SEVEN_PAIRS               0x02  ///< 七对
#define FORM_FLAG_THIRTEEN_ORPHANS          0x04  ///< 十三幺
#define FORM_FLAG_HONORS_AND_KNITTED_TILES  0x08  ///< 全不靠
#define FORM_FLAG_KNITTED_STRAIGHT          0x10  ///< 组合龙
#define FORM_FLAG_ALL                       0xFF  ///< 全部和型
/**
 * @}
 */

/**
 * @brief 枚举打哪张牌的计算结果信息
 */
struct enum_result_t {
	tile_t discard_tile;                    ///< 打这张牌
	uint8_t form_flag;                      ///< 和牌形式
	int shanten;                            ///< 上听数
	useful_table_t useful_table;            ///< 有效牌标记表
};

/**
 * @brief 枚举打哪张牌的计算回调函数
 *
 * @param [in] context 从enum_discard_tile传过来的context原样传回
 * @param [in] result 计算结果
 * @retval true 继续枚举
 * @retval false 结束枚举
 */
typedef bool (*enum_callback_t)(void *context, const enum_result_t *result);

/**
 * @brief 枚举打哪张牌
 *
 * @param [in] hand_tiles 手牌结构
 * @param [in] serving_tile 上牌（可为0，此时仅计算手牌的信息）
 * @param [in] form_flag 计算哪些和型
 * @param [in] context 用户自定义参数，将原样从回调函数传回
 * @param [in] enum_callback 回调函数
 */
void enum_discard_tile(const hand_tiles_t *hand_tiles, tile_t serving_tile, uint8_t form_flag,
	void *context, enum_callback_t enum_callback);

}

/**
 * end group
 * @}
 */

#endif

/*** End of inlined file: shanten.h ***/

/**
 * 算番流程概述：
 * 1. 判断特殊和型
 *   (1) 门清状态——七对、十三幺、组合龙、全不靠
 *   (2) 1副露状态——组合龙
 * 2. 按基本和型划分（留意七对）
 * 3. 对第2步中的划分结果进行算番，取最大值

 * 对划分后的结果算番流程：
 * 1. 计数顺子个数和刻子个数，对刻子自身算番（涉及：幺九刻、箭刻）
 * 2. 分情况对面子算番
 *   (1) 4顺——先判断三色/一色双龙会，没有再计算4顺的番
 *   (2) 3顺1刻——计算3顺的番
 *   (3) 2顺2刻——计算2顺的番，计算2刻的番
 *   (4) 1顺3刻——计算3刻的番
 * 3. 九莲宝灯判断
 * 4. 根据和牌方式调整——涉及：不求人、全求人
 * 5. 根据雀头调整——涉及：平和、小三元、小四喜
 * 6. 根据牌组特征调整——涉及：全带幺、全带五、全双刻
 * 7. 根据花色调整——涉及：无字、缺一门、混一色、清一色、五门齐
 * 8. 根据牌特性调整——涉及：断幺、推不倒、绿一色、字一色、清幺九、混幺九
 * 9. 根据数牌的范围调整——涉及：大于五、小于五、全大、全中、全小
 * 10. 计算四归一
 * 11. 根据听牌方式调整——涉及：边张、嵌张、单钓将
 * 12. 统一调整规则中规定不计的
 * 13. 最后调整圈风门风
 * 14. 以上流程走完，得到算番结果。如果为0番，则调整为无番和
 */

#define MAX_DIVISION_CNT 20  // 一副牌最多也没有20种划分吧，够用了

#if 0
#define LOG(fmt_, ...) printf(fmt_, ##__VA_ARGS__)
#else
#define LOG(...) ((void)0)
#endif

//#define STRICT_98_RULE

namespace mahjong {

#if 0  // Debug
extern intptr_t packs_to_string(const pack_t *packs, intptr_t pack_cnt, char *str, intptr_t max_size);
#endif

//-------------------------------- 划分 --------------------------------

namespace {

	// 划分
	struct division_t {
		pack_t packs[5];  // 牌组。4面子1雀头，共5组
	};

	// 划分结果
	struct division_result_t {
		division_t divisions[MAX_DIVISION_CNT];  // 每一种划分
		intptr_t count;  // 划分方式总数
	};
}

// 递归划分算法的最后一步，添加划分
static void divide_tail_add_division(intptr_t fixed_cnt, const division_t *work_division, division_result_t *result) {
	// 拷贝一份当前的划分出来的面子，并排序暗手的面子
	// 这里不能直接在work_division->packs上排序，否则会破坏递归外层的数据
	division_t temp;
	memcpy(&temp, work_division, sizeof(temp));
	std::sort(temp.packs + fixed_cnt, temp.packs + 4);

	// 如果这种划分是否已经存在了
	if (std::none_of(&result->divisions[0], &result->divisions[result->count],
		[&temp, fixed_cnt](const division_t &od) {
		return std::equal(&od.packs[fixed_cnt], &od.packs[4], &temp.packs[fixed_cnt]);
	})) {
		// 写入划分结果里
		memcpy(&result->divisions[result->count], &temp, sizeof(temp));
		++result->count;
	}
	else {
		LOG("same case");
	}
}

// 递归划分的最后一步
static bool divide_tail(tile_table_t &cnt_table, intptr_t fixed_cnt, division_t *work_division, division_result_t *result) {
	for (int i = 0; i < 34; ++i) {
		tile_t t = all_tiles[i];
		if (cnt_table[t] < 2) {
			continue;
		}

		cnt_table[t] -= 2;  // 削减
		// 所有牌全部使用完毕
		if (std::all_of(std::begin(cnt_table), std::end(cnt_table), [](int n) { return n == 0; })) {
			cnt_table[t] += 2;  // 还原

			// 这2张作为雀头
			work_division->packs[4] = make_pack(0, PACK_TYPE_PAIR, t);
			divide_tail_add_division(fixed_cnt, work_division, result);  // 记录
			return true;
		}
		cnt_table[t] += 2;  // 还原
	}

	return false;
}

// 判断一条划分分支是否来过
static bool is_division_branch_exist(intptr_t fixed_cnt, intptr_t step, const division_t *work_division, const division_result_t *result) {
	// 没有划分时，以及划分步骤小于3时，不检测，因为至少要有3步递归才会产生不同划分
	if (result->count <= 0 || step < 3) {
		return false;
	}

	// std::includes要求有序
	// 这里不能直接在work_division->packs上排序，否则会破坏递归外层的数据
	division_t temp;
	memcpy(&temp.packs[fixed_cnt], &work_division->packs[fixed_cnt], step * sizeof(pack_t));
	std::sort(&temp.packs[fixed_cnt], &temp.packs[fixed_cnt + step]);

	// 只需要比较面子是否重复分支，雀头不参与比较，所以下标是4
	return std::any_of(&result->divisions[0], &result->divisions[result->count],
		[&temp, fixed_cnt, step](const division_t &od) {
		return std::includes(&od.packs[fixed_cnt], &od.packs[4], &temp.packs[fixed_cnt], &temp.packs[fixed_cnt + step]);
	});
}

// 递归划分
static bool divide_recursively(tile_table_t &cnt_table, intptr_t fixed_cnt, intptr_t step, division_t *work_division, division_result_t *result) {
	const intptr_t idx = step + fixed_cnt;
	if (idx == 4) {  // 4组面子都有了
		return divide_tail(cnt_table, fixed_cnt, work_division, result);
	}

	bool ret = false;

	// 按牌表张遍历牌
	for (int i = 0; i < 34; ++i) {
		tile_t t = all_tiles[i];
		if (cnt_table[t] < 1) {
			continue;
		}

		// 刻子
		if (cnt_table[t] > 2) {
			work_division->packs[idx] = make_pack(0, PACK_TYPE_PUNG, t);  // 记录刻子
			if (!is_division_branch_exist(fixed_cnt, step + 1, work_division, result)) {
				// 削减这组刻子，递归
				cnt_table[t] -= 3;
				if (divide_recursively(cnt_table, fixed_cnt, step + 1, work_division, result)) {
					ret = true;
				}
				// 还原
				cnt_table[t] += 3;
			}
		}

		// 顺子（只能是数牌）
		if (is_numbered_suit(t)) {
			if (tile_get_rank(t) < 8 && cnt_table[t + 1] && cnt_table[t + 2]) {
				work_division->packs[idx] = make_pack(0, PACK_TYPE_CHOW, static_cast<tile_t>(t + 1));  // 记录顺子
				if (!is_division_branch_exist(fixed_cnt, step + 1, work_division, result)) {
					// 削减这组顺子，递归
					--cnt_table[t];
					--cnt_table[t + 1];
					--cnt_table[t + 2];
					if (divide_recursively(cnt_table, fixed_cnt, step + 1, work_division, result)) {
						ret = true;
					}
					// 还原
					++cnt_table[t];
					++cnt_table[t + 1];
					++cnt_table[t + 2];
				}
			}
		}
	}

	return ret;
}

// 划分一手牌
static bool divide_win_hand(const tile_t *standing_tiles, const pack_t *fixed_packs, intptr_t fixed_cnt, division_result_t *result) {
	intptr_t standing_cnt = 14 - fixed_cnt * 3;

	// 对立牌的种类进行打表
	tile_table_t cnt_table;
	map_tiles(standing_tiles, standing_cnt, &cnt_table);

	result->count = 0;

	// 复制副露的面子
	division_t work_division;
	memcpy(work_division.packs, fixed_packs, fixed_cnt * sizeof(pack_t));
	return divide_recursively(cnt_table, fixed_cnt, 0, &work_division, result);
}

//-------------------------------- 算番 --------------------------------

// 4组递增1
static FORCE_INLINE bool is_four_shifted_1(rank_t r0, rank_t r1, rank_t r2, rank_t r3) {
	return (r0 + 1 == r1 && r1 + 1 == r2 && r2 + 1 == r3);
}

// 4组递增2
static FORCE_INLINE bool is_four_shifted_2(rank_t r0, rank_t r1, rank_t r2, rank_t r3) {
	return (r0 + 2 == r1 && r1 + 2 == r2 && r2 + 2 == r3);
}

// 3组递增1
static FORCE_INLINE bool is_shifted_1(rank_t r0, rank_t r1, rank_t r2) {
	return (r0 + 1 == r1 && r1 + 1 == r2);
}

// 3组递增2
static FORCE_INLINE bool is_shifted_2(rank_t r0, rank_t r1, rank_t r2) {
	return (r0 + 2 == r1 && r1 + 2 == r2);
}

// 三色
static FORCE_INLINE bool is_mixed(suit_t s0, suit_t s1, suit_t s2) {
	return (s0 != s1 && s0 != s2 && s1 != s2);
}

// 3组递增1无序
static FORCE_INLINE bool is_shifted_1_unordered(rank_t r0, rank_t r1, rank_t r2) {
	return is_shifted_1(r1, r0, r2) || is_shifted_1(r2, r0, r1) || is_shifted_1(r0, r1, r2)
		|| is_shifted_1(r2, r1, r0) || is_shifted_1(r0, r2, r1) || is_shifted_1(r1, r2, r0);
}

// 4组顺子的番
static fan_t get_4_chows_fan(tile_t t0, tile_t t1, tile_t t2, tile_t t3) {
	// 按出现频率顺序

	// 一色四步高
	if (is_four_shifted_2(t0, t1, t2, t3) || is_four_shifted_1(t0, t1, t2, t3)) {
		return FOUR_PURE_SHIFTED_CHOWS;
	}
	// 一色四同顺
	if (t0 == t1 && t0 == t2 && t0 == t3) {
		return QUADRUPLE_CHOW;
	}
	// 以上都没有
	return FAN_NONE;
}

// 3组顺子的番
static fan_t get_3_chows_fan(tile_t t0, tile_t t1, tile_t t2) {
	suit_t s0 = tile_get_suit(t0);
	suit_t s1 = tile_get_suit(t1);
	suit_t s2 = tile_get_suit(t2);

	rank_t r0 = tile_get_rank(t0);
	rank_t r1 = tile_get_rank(t1);
	rank_t r2 = tile_get_rank(t2);

	// 按出现频率顺序

	if (is_mixed(s0, s1, s2)) {  // 三色
		// 三色三步高
		if (is_shifted_1_unordered(r1, r0, r2)) {
			return MIXED_SHIFTED_CHOWS;
		}
		// 三色三同顺
		if (r0 == r1 && r1 == r2) {
			return MIXED_TRIPLE_CHOW;
		}
		// 花龙
		if ((r0 == 2 && r1 == 5 && r2 == 8) || (r0 == 2 && r1 == 8 && r2 == 5)
			|| (r0 == 5 && r1 == 2 && r2 == 8) || (r0 == 5 && r1 == 8 && r2 == 2)
			|| (r0 == 8 && r1 == 2 && r2 == 5) || (r0 == 8 && r1 == 5 && r2 == 2)) {
			return MIXED_STRAIGHT;
		}
	}
	else {  // 一色
		// 清龙
		if (t0 + 3 == t1 && t1 + 3 == t2) {
			return PURE_STRAIGHT;
		}
		// 一色三步高
		if (is_shifted_2(t0, t1, t2) || is_shifted_1(t0, t1, t2)) {
			return PURE_SHIFTED_CHOWS;
		}
		// 一色三同顺
		if (t0 == t1 && t0 == t2) {
			return PURE_TRIPLE_CHOW;
		}
	}
	// 以上都没有
	return FAN_NONE;
}

// 2组顺子的番
static fan_t get_2_chows_fan_unordered(tile_t t0, tile_t t1) {
	// 按出现频率顺序

	if (!is_suit_equal_quick(t0, t1)) {  // 两色
		// 喜相逢
		if (is_rank_equal_quick(t0, t1)) {
			return MIXED_DOUBLE_CHOW;
		}
	}
	else {  // 一色
		// 连六
		if (t0 + 3 == t1 || t1 + 3 == t0) {
			return SHORT_STRAIGHT;
		}
		// 老少副
		rank_t r0 = tile_get_rank(t0);
		rank_t r1 = tile_get_rank(t1);
		if ((r0 == 2 && r1 == 8) || (r0 == 8 && r1 == 2)) {
			return TWO_TERMINAL_CHOWS;
		}
		// 一般高
		if (t0 == t1) {
			return PURE_DOUBLE_CHOW;
		}
	}
	// 以上都没有
	return FAN_NONE;
}

// 4组刻子的番
static fan_t get_4_pungs_fan(tile_t t0, tile_t t1, tile_t t2, tile_t t3) {
	// 一色四节高
	if (is_numbered_suit_quick(t0) && t0 + 1 == t1 && t1 + 1 == t2 && t2 + 1 == t3) {
		return FOUR_PURE_SHIFTED_PUNGS;
	}
	// 大四喜
	if (t0 == TILE_E && t1 == TILE_S && t2 == TILE_W && t3 == TILE_N) {
		return BIG_FOUR_WINDS;
	}
	// 以上都没有
	return FAN_NONE;
}

// 3组刻子的番
static fan_t get_3_pungs_fan(tile_t t0, tile_t t1, tile_t t2) {
	// 按出现频率顺序

	if (is_numbered_suit_quick(t0) && is_numbered_suit_quick(t1) && is_numbered_suit_quick(t2)) {  // 数牌
		suit_t s0 = tile_get_suit(t0);
		suit_t s1 = tile_get_suit(t1);
		suit_t s2 = tile_get_suit(t2);

		rank_t r0 = tile_get_rank(t0);
		rank_t r1 = tile_get_rank(t1);
		rank_t r2 = tile_get_rank(t2);

		if (is_mixed(s0, s1, s2)) {  // 三色
			// 三色三节高
			if (is_shifted_1_unordered(r1, r0, r2)) {
				return MIXED_SHIFTED_PUNGS;
			}
			// 三同刻
			if (r0 == r1 && r1 == r2) {
				return TRIPLE_PUNG;
			}
		}
		else {
			// 一色三节高
			if (t0 + 1 == t1 && t1 + 1 == t2) {
				return PURE_SHIFTED_PUNGS;
			}
		}
	}
	else {
		// 三风刻
		if ((t0 == TILE_E && t1 == TILE_S && t2 == TILE_W)
			|| (t0 == TILE_E && t1 == TILE_S && t2 == TILE_N)
			|| (t0 == TILE_E && t1 == TILE_W && t2 == TILE_N)
			|| (t0 == TILE_S && t1 == TILE_W && t2 == TILE_N)) {
			return BIG_THREE_WINDS;
		}
		// 大三元
		if (t0 == TILE_C && t1 == TILE_F && t2 == TILE_P) {
			return BIG_THREE_DRAGONS;
		}
	}

	// 以上都没有
	return FAN_NONE;
}

// 2组刻子的番
static fan_t get_2_pungs_fan_unordered(tile_t t0, tile_t t1) {
	// 按出现频率顺序
	if (is_numbered_suit_quick(t0) && is_numbered_suit_quick(t1)) {  // 数牌
		// 双同刻
		if (is_rank_equal_quick(t0, t1)) {
			return DOUBLE_PUNG;
		}
	}
	else {
		// 双箭刻
		if (is_dragons(t0) && is_dragons(t1)) {
			return TWO_DRAGONS_PUNGS;
		}
	}
	// 以上都没有
	return FAN_NONE;
}

// 1组刻子的番
static fan_t get_1_pung_fan(tile_t mid_tile) {
	// 箭刻
	if (is_dragons(mid_tile)) {
		return DRAGON_PUNG;
	}
	// 幺九刻
	if (is_terminal(mid_tile) || is_winds(mid_tile)) {
		return PUNG_OF_TERMINALS_OR_HONORS;
	}
	// 以上都没有
	return FAN_NONE;
}

// 存在3组顺子的番种时，余下的第4组顺子最多算1番
static fan_t get_1_chow_extra_fan(tile_t tile0, tile_t tile1, tile_t tile2, tile_t tile_extra) {
	fan_t fan0 = get_2_chows_fan_unordered(tile0, tile_extra);
	fan_t fan1 = get_2_chows_fan_unordered(tile1, tile_extra);
	fan_t fan2 = get_2_chows_fan_unordered(tile2, tile_extra);

	// 按以下顺序返回
	// 一般高
	if (fan0 == PURE_DOUBLE_CHOW || fan1 == PURE_DOUBLE_CHOW || fan2 == PURE_DOUBLE_CHOW) {
		return PURE_DOUBLE_CHOW;
	}
	// 喜相逢
	if (fan0 == MIXED_DOUBLE_CHOW || fan1 == MIXED_DOUBLE_CHOW || fan2 == MIXED_DOUBLE_CHOW) {
		return MIXED_DOUBLE_CHOW;
	}
	// 连六
	if (fan0 == SHORT_STRAIGHT || fan1 == SHORT_STRAIGHT || fan2 == SHORT_STRAIGHT) {
		return SHORT_STRAIGHT;
	}
	// 老少副
	if (fan0 == TWO_TERMINAL_CHOWS || fan1 == TWO_TERMINAL_CHOWS || fan2 == TWO_TERMINAL_CHOWS) {
		return TWO_TERMINAL_CHOWS;
	}

	return FAN_NONE;
}

// 套算一次原则：
// 如果有尚未组合过的一副牌，只可同已组合过的相应的一副牌套算一次
//
// 不得相同原则：
// 凡已经合过某一番种的牌，不能再同其他一副牌组成相同的番种计分
//
// 根据套算一次原则，234567s234567p，只能计为“喜相逢*2 连六*1”或者“喜相逢*1 连六*2”，而不是“喜相逢*2 连六*2”
// 根据以上两点，234s223344567p，只能计为：“一般高、喜相逢、连六”，而不是“喜相逢*2、连六”
//
// 直接按规则来写，差不多是图的算法，太过复杂
// 这里简便处理：先统计有多少番，当超过时规则允许的数目时，从重复的开始削减
static void exclusionary_rule(const fan_t *all_fans, long fan_cnt, long max_cnt, fan_table_t &fan_table) {
	// 统计有多少番
	uint16_t table[4] = { 0 };
	long cnt = 0;
	for (long i = 0; i < fan_cnt; ++i) {
		if (all_fans[i] != FAN_NONE) {
			++cnt;
			++table[all_fans[i] - PURE_DOUBLE_CHOW];
		}
	}

	// 当超过时，从重复的开始削减
	int limit_cnt = 1;
	// 第一轮先削减剩下1，第二轮削减剩下0
	while (cnt > max_cnt && limit_cnt >= 0) {
		int idx = 4;  // 从老少副开始削减
		while (cnt > max_cnt && idx-- > 0) {
			while (static_cast<int>(table[idx]) > limit_cnt && cnt > max_cnt) {
				--table[idx];
				--cnt;
			}
		}
		--limit_cnt;
	}

	fan_table[PURE_DOUBLE_CHOW] = table[0];
	fan_table[MIXED_DOUBLE_CHOW] = table[1];
	fan_table[SHORT_STRAIGHT] = table[2];
	fan_table[TWO_TERMINAL_CHOWS] = table[3];
}

// 4组顺子算番
static void calculate_4_chows(const tile_t (&mid_tiles)[4], fan_table_t &fan_table) {
	fan_t fan;
	// 存在4组顺子的番种时，不再检测其他的了
	if ((fan = get_4_chows_fan(mid_tiles[0], mid_tiles[1], mid_tiles[2], mid_tiles[3])) != FAN_NONE) {
		fan_table[fan] = 1;
		return;
	}

	// 3组顺子判断
	// 012构成3组顺子的番种
	if ((fan = get_3_chows_fan(mid_tiles[0], mid_tiles[1], mid_tiles[2])) != FAN_NONE) {
		fan_table[fan] = 1;
		// 计算与第4组顺子构成的番
		if ((fan = get_1_chow_extra_fan(mid_tiles[0], mid_tiles[1], mid_tiles[2], mid_tiles[3])) != FAN_NONE) {
			fan_table[fan] = 1;
		}
		return;
	}
	// 013构成3组顺子的番种
	else if ((fan = get_3_chows_fan(mid_tiles[0], mid_tiles[1], mid_tiles[3])) != FAN_NONE) {
		fan_table[fan] = 1;
		// 计算与第4组顺子构成的番
		if ((fan = get_1_chow_extra_fan(mid_tiles[0], mid_tiles[1], mid_tiles[3], mid_tiles[2])) != FAN_NONE) {
			fan_table[fan] = 1;
		}
		return;
	}
	// 023构成3组顺子的番种
	else if ((fan = get_3_chows_fan(mid_tiles[0], mid_tiles[2], mid_tiles[3])) != FAN_NONE) {
		fan_table[fan] = 1;
		// 计算与第4组顺子构成的番
		if ((fan = get_1_chow_extra_fan(mid_tiles[0], mid_tiles[2], mid_tiles[3], mid_tiles[1])) != FAN_NONE) {
			fan_table[fan] = 1;
		}
		return;
	}
	// 123构成3组顺子的番种
	else if ((fan = get_3_chows_fan(mid_tiles[1], mid_tiles[2], mid_tiles[3])) != FAN_NONE) {
		fan_table[fan] = 1;
		// 计算与第4组顺子构成的番
		if ((fan = get_1_chow_extra_fan(mid_tiles[1], mid_tiles[2], mid_tiles[3], mid_tiles[0])) != FAN_NONE) {
			fan_table[fan] = 1;
		}
		return;
	}

	// 不存在3组顺子的番种时，4组顺子最多3番
	fan_t all_fans[6] = {
		get_2_chows_fan_unordered(mid_tiles[0], mid_tiles[1]),
		get_2_chows_fan_unordered(mid_tiles[0], mid_tiles[2]),
		get_2_chows_fan_unordered(mid_tiles[0], mid_tiles[3]),
		get_2_chows_fan_unordered(mid_tiles[1], mid_tiles[2]),
		get_2_chows_fan_unordered(mid_tiles[1], mid_tiles[3]),
		get_2_chows_fan_unordered(mid_tiles[2], mid_tiles[3])
	};

	int max_cnt = 3;

	// 0与其他3组顺子无任何关系
	if (all_fans[0] == FAN_NONE && all_fans[1] == FAN_NONE && all_fans[2] == FAN_NONE) {
		--max_cnt;
	}

	// 1与其他3组顺子无任何关系
	if (all_fans[0] == FAN_NONE && all_fans[3] == FAN_NONE && all_fans[4] == FAN_NONE) {
		--max_cnt;
	}

	// 2与其他3组顺子无任何关系
	if (all_fans[1] == FAN_NONE && all_fans[3] == FAN_NONE && all_fans[5] == FAN_NONE) {
		--max_cnt;
	}

	// 3与其他3组顺子无任何关系
	if (all_fans[2] == FAN_NONE && all_fans[4] == FAN_NONE && all_fans[5] == FAN_NONE) {
		--max_cnt;
	}

	if (max_cnt > 0) {
		exclusionary_rule(all_fans, 6, max_cnt, fan_table);
	}
}

// 3组顺子算番
static void calculate_3_chows(const tile_t (&mid_tiles)[3], fan_table_t &fan_table) {
	fan_t fan;

	// 存在3组顺子的番种时，不再检测其他的
	if ((fan = get_3_chows_fan(mid_tiles[0], mid_tiles[1], mid_tiles[2])) != FAN_NONE) {
		fan_table[fan] = 1;
		return;
	}

	// 不存在上述番种时，3组顺子最多2番
	fan_t all_fans[3] = {
		get_2_chows_fan_unordered(mid_tiles[0], mid_tiles[1]),
		get_2_chows_fan_unordered(mid_tiles[0], mid_tiles[2]),
		get_2_chows_fan_unordered(mid_tiles[1], mid_tiles[2])
	};
	exclusionary_rule(all_fans, 3, 2, fan_table);
}

// 2组顺子算番
static void calculate_2_chows_unordered(const tile_t (&mid_tiles)[2], fan_table_t &fan_table) {
	fan_t fan;
	if ((fan = get_2_chows_fan_unordered(mid_tiles[0], mid_tiles[1])) != FAN_NONE) {
		++fan_table[fan];
	}
}

// 刻子（杠）算番
static void calculate_kongs(const pack_t *pung_packs, intptr_t pung_cnt, fan_table_t &fan_table) {
	// 统计明杠 暗杠 明刻 暗刻
	int melded_kong_cnt = 0;
	int concealed_kong_cnt = 0;
	int concealed_pung_cnt = 0;
	for (intptr_t i = 0; i < pung_cnt; ++i) {
		if (is_pack_melded(pung_packs[i])) {
			if (pack_get_type(pung_packs[i]) == PACK_TYPE_KONG) {
				++melded_kong_cnt;
			}
		}
		else {
			if (pack_get_type(pung_packs[i]) == PACK_TYPE_KONG) {
				++concealed_kong_cnt;
			}
			else {
				++concealed_pung_cnt;
			}
		}
	}

	// 规则
	// 三杠
	// 明杠 明杠 暗杠 暗刻 -> 三杠+双暗刻+碰碰和
	// 明杠 暗杠 暗杠 明刻 -> 三杠+双暗刻+碰碰和
	// 明杠 暗杠 暗杠 暗刻 -> 三杠+三暗刻+碰碰和
	// 暗杠 暗杠 暗杠 明刻 -> 三杠+三暗刻+碰碰和
	// 暗杠 暗杠 暗杠 暗刻 -> 三杠+四暗刻
	//
	// 四杠
	// 暗杠 明杠 明杠 明杠 -> 四杠
	// 暗杠 暗杠 明杠 明杠 -> 四杠+双暗刻
	// 暗杠 暗杠 暗杠 明杠 -> 四杠+三暗刻
	// 暗杠 暗杠 暗杠 暗杠 -> 四杠+四暗刻
	//

	int kong_cnt = melded_kong_cnt + concealed_kong_cnt;
	switch (kong_cnt) {
	case 0:  // 0个杠
		switch (concealed_pung_cnt) {  // 暗刻的个数
		case 2: fan_table[TWO_CONCEALED_PUNGS] = 1; break;
		case 3: fan_table[THREE_CONCEALED_PUNGS] = 1; break;
		case 4: fan_table[FOUR_CONCEALED_PUNGS] = 1; break;
		default: break;
		}
		break;
	case 1:  // 1个杠
		if (melded_kong_cnt == 1) {  // 明杠
			fan_table[MELDED_KONG] = 1;
			switch (concealed_pung_cnt) {  // 暗刻的个数
			case 2: fan_table[TWO_CONCEALED_PUNGS] = 1; break;
			case 3: fan_table[THREE_CONCEALED_PUNGS] = 1; break;
			default: break;
			}
		}
		else {  // 暗杠
			fan_table[CONCEALED_KONG] = 1;
			switch (concealed_pung_cnt) {  // 暗刻的个数
			case 1: fan_table[TWO_CONCEALED_PUNGS] = 1; break;
			case 2: fan_table[THREE_CONCEALED_PUNGS] = 1; break;
			case 3: fan_table[FOUR_CONCEALED_PUNGS] = 1; break;
			default: break;
			}
		}
		break;
	case 2:  // 2个杠
		switch (concealed_kong_cnt) {
		case 0:  // 双明杠
			fan_table[TWO_MELDED_KONGS] = 1;
			switch (concealed_pung_cnt) {  // 暗刻的个数
			case 2: fan_table[TWO_CONCEALED_PUNGS] = 1; break;
			default: break;
			}
			break;
		case 1:  // 明暗杠
#if SUPPORT_CONCEALED_KONG_AND_MELDED_KONG
			fan_table[CONCEALED_KONG_AND_MELDED_KONG] = 1;
#else
			fan_table[MELDED_KONG] = 1;
			fan_table[CONCEALED_KONG] = 1;
#endif
			switch (concealed_pung_cnt) {  // 暗刻的个数
			case 1: fan_table[TWO_CONCEALED_PUNGS] = 1; break;
			case 2: fan_table[THREE_CONCEALED_PUNGS] = 1; break;
			default: break;
			}
			break;
		case 2:  // 双暗杠
			fan_table[TWO_CONCEALED_KONGS] = 1;
			switch (concealed_pung_cnt) {  // 暗刻的个数
			case 1: fan_table[THREE_CONCEALED_PUNGS] = 1; break;
			case 2: fan_table[FOUR_CONCEALED_PUNGS] = 1; break;
			default: break;
			}
			break;
		default:
			break;
		}
		break;
	case 3:  // 3个杠
		fan_table[THREE_KONGS] = 1;
		switch (concealed_kong_cnt) {  // 暗刻的个数
		case 0:  // 3明杠
			break;
		case 1:  // 1暗杠2明杠
			if (concealed_pung_cnt > 0) {
				fan_table[TWO_CONCEALED_PUNGS] = 1;
			}
			break;
		case 2:  // 2暗杠1明杠
			if (concealed_pung_cnt == 0) {
				fan_table[TWO_CONCEALED_PUNGS] = 1;
			}
			else {
				fan_table[THREE_CONCEALED_PUNGS] = 1;
			}
			break;
		case 3:  // 3暗杠
			if (concealed_pung_cnt == 0) {
				fan_table[THREE_CONCEALED_PUNGS] = 1;
			}
			else {
				fan_table[FOUR_CONCEALED_PUNGS] = 1;
			}
			break;
		default:
			break;
		}
		break;
	case 4:  // 4个杠
		fan_table[FOUR_KONGS] = 1;
		switch (concealed_kong_cnt) {
		case 2: fan_table[TWO_CONCEALED_PUNGS] = 1; break;
		case 3: fan_table[THREE_CONCEALED_PUNGS] = 1; break;
		case 4: fan_table[FOUR_CONCEALED_PUNGS] = 1; break;
		default: break;
		}
		break;
	default:
		UNREACHABLE();
		break;
	}

	// 四杠和四暗刻不计碰碰和，其他先加上碰碰和的番
	if (pung_cnt == 4) {
		if (fan_table[FOUR_KONGS] == 0 && fan_table[FOUR_CONCEALED_PUNGS] == 0) {
			fan_table[ALL_PUNGS] = 1;
		}
	}

	// 逐组刻子的番（箭刻、幺九刻）
	for (intptr_t i = 0; i < pung_cnt; ++i) {
		fan_t fan = get_1_pung_fan(pack_get_tile(pung_packs[i]));
		if (fan != FAN_NONE) {
			++fan_table[fan];
		}
	}
}

// 4组刻子算番
static void calculate_4_pungs(const tile_t (&mid_tiles)[4], fan_table_t &fan_table) {
	fan_t fan;
	// 存在4组刻子的番种时，不再检测其他的了
	if ((fan = get_4_pungs_fan(mid_tiles[0], mid_tiles[1], mid_tiles[2], mid_tiles[3])) != FAN_NONE) {
		fan_table[fan] = 1;
		return;
	}

	// 3组刻子判断
	bool _3_pungs_has_fan = false;
	int free_pack_idx = -1;  // 未使用的1组刻子
	// 012构成3组刻子的番种
	if ((fan = get_3_pungs_fan(mid_tiles[0], mid_tiles[1], mid_tiles[2])) != FAN_NONE) {
		fan_table[fan] = 1;
		free_pack_idx = 3;
		_3_pungs_has_fan = true;
	}
	// 013构成3组刻子的番种
	else if ((fan = get_3_pungs_fan(mid_tiles[0], mid_tiles[1], mid_tiles[3])) != FAN_NONE) {
		fan_table[fan] = 1;
		free_pack_idx = 2;
		_3_pungs_has_fan = true;
	}
	// 023构成3组刻子的番种
	else if ((fan = get_3_pungs_fan(mid_tiles[0], mid_tiles[2], mid_tiles[3])) != FAN_NONE) {
		fan_table[fan] = 1;
		free_pack_idx = 1;
		_3_pungs_has_fan = true;
	}
	// 123构成3组刻子的番种
	else if ((fan = get_3_pungs_fan(mid_tiles[1], mid_tiles[2], mid_tiles[3])) != FAN_NONE) {
		fan_table[fan] = 1;
		free_pack_idx = 0;
		_3_pungs_has_fan = true;
	}

	// 存在3组刻子的番种时，余下的第4组刻子只能组合一次
	if (_3_pungs_has_fan) {
		for (int i = 0; i < 4; ++i) {
			if (i == free_pack_idx) {
				continue;
			}
			// 依次与未使用的这组刻子测试番种
			if ((fan = get_2_pungs_fan_unordered(mid_tiles[i], mid_tiles[free_pack_idx])) != FAN_NONE) {
				++fan_table[fan];
				break;
			}
		}
		return;
	}

	// 不存在3组刻子的番种时，两两计算番种
	if ((fan = get_2_pungs_fan_unordered(mid_tiles[0], mid_tiles[1])) != FAN_NONE) {
		++fan_table[fan];
	}
	if ((fan = get_2_pungs_fan_unordered(mid_tiles[0], mid_tiles[2])) != FAN_NONE) {
		++fan_table[fan];
	}
	if ((fan = get_2_pungs_fan_unordered(mid_tiles[0], mid_tiles[3])) != FAN_NONE) {
		++fan_table[fan];
	}
	if ((fan = get_2_pungs_fan_unordered(mid_tiles[1], mid_tiles[2])) != FAN_NONE) {
		++fan_table[fan];
	}
	if ((fan = get_2_pungs_fan_unordered(mid_tiles[1], mid_tiles[3])) != FAN_NONE) {
		++fan_table[fan];
	}
	if ((fan = get_2_pungs_fan_unordered(mid_tiles[2], mid_tiles[3])) != FAN_NONE) {
		++fan_table[fan];
	}
}

// 3组刻子算番
static void calculate_3_pungs(const tile_t (&mid_tiles)[3], fan_table_t &fan_table) {
	fan_t fan;

	// 存在3组刻子的番种（三节高 三同刻 三风刻 大三元）时，不再检测其他的
	if ((fan = get_3_pungs_fan(mid_tiles[0], mid_tiles[1], mid_tiles[2])) != FAN_NONE) {
		fan_table[fan] = 1;
		return;
	}

	// 不存在3组刻子的番种时，两两计算番种
	if ((fan = get_2_pungs_fan_unordered(mid_tiles[0], mid_tiles[1])) != FAN_NONE) {
		++fan_table[fan];
	}
	if ((fan = get_2_pungs_fan_unordered(mid_tiles[0], mid_tiles[2])) != FAN_NONE) {
		++fan_table[fan];
	}
	if ((fan = get_2_pungs_fan_unordered(mid_tiles[1], mid_tiles[2])) != FAN_NONE) {
		++fan_table[fan];
	}
}

// 2组刻子算番
static void calculate_2_pungs_unordered(const tile_t (&mid_tiles)[2], fan_table_t &fan_table) {
	fan_t fan = get_2_pungs_fan_unordered(mid_tiles[0], mid_tiles[1]);
	if (fan != FAN_NONE) {
		++fan_table[fan];
	}
}

// 九莲宝灯
static bool is_nine_gates(const tile_t *tiles) {
	// 对立牌的种类进行打表
	tile_table_t cnt_table;
	map_tiles(tiles, 13, &cnt_table);

	// 1、9各三枚，2~8各一枚
	return (cnt_table[0x11] == 3 && cnt_table[0x19] == 3 && std::all_of(cnt_table + 0x12, cnt_table + 0x19, [](int n) { return n == 1; }))
		|| (cnt_table[0x21] == 3 && cnt_table[0x29] == 3 && std::all_of(cnt_table + 0x22, cnt_table + 0x29, [](int n) { return n == 1; }))
		|| (cnt_table[0x31] == 3 && cnt_table[0x39] == 3 && std::all_of(cnt_table + 0x32, cnt_table + 0x39, [](int n) { return n == 1; }));
}

// 一色双龙会
static bool is_pure_terminal_chows(const pack_t (&chow_packs)[4], pack_t pair_pack) {
	if (tile_get_rank(pack_get_tile(pair_pack)) != 5) {  // 5作雀头
		return false;
	}

	int _123_cnt = 0, _789_cnt = 0;
	suit_t pair_suit = tile_get_suit(pack_get_tile(pair_pack));
	for (int i = 0; i < 4; ++i) {
		suit_t suit = tile_get_suit(pack_get_tile(chow_packs[i]));
		if (suit != pair_suit) {  // 花色与雀头相同
			return false;
		}
		rank_t rank = tile_get_rank(pack_get_tile(chow_packs[i]));
		switch (rank) {
		case 2: ++_123_cnt; break;
		case 8: ++_789_cnt; break;
		default: return false;
		}
	}
	return (_123_cnt == 2 && _789_cnt == 2);  // 123和789各2组
}

// 三色双龙会
static bool is_three_suited_terminal_chows(const pack_t (&chow_packs)[4], pack_t pair_pack) {
	if (tile_get_rank(pack_get_tile(pair_pack)) != 5) {  // 5作雀头
		return false;
	}

	int _123_suit_table[4] = { 0 };
	int _789_suit_table[4] = { 0 };
	suit_t pair_suit = tile_get_suit(pack_get_tile(pair_pack));
	for (int i = 0; i < 4; ++i) {
		suit_t suit = tile_get_suit(pack_get_tile(chow_packs[i]));
		if (suit == pair_suit) {  // 花色与雀头不相同
			return false;
		}
		rank_t rank = tile_get_rank(pack_get_tile(chow_packs[i]));
		switch (rank) {
		case 2: ++_123_suit_table[suit]; break;
		case 8: ++_789_suit_table[suit]; break;
		default: return false;
		}
	}

	// 与雀头花色不同的两色123和789各一组
	switch (pair_suit) {
	case 1: return (_123_suit_table[2] && _123_suit_table[3] && _789_suit_table[2] && _789_suit_table[3]);
	case 2: return (_123_suit_table[1] && _123_suit_table[3] && _789_suit_table[1] && _789_suit_table[3]);
	case 3: return (_123_suit_table[1] && _123_suit_table[2] && _789_suit_table[1] && _789_suit_table[2]);
	default: return false;
	}
}

// 根据和牌方式调整——涉及番种：不求人、全求人
static void adjust_by_self_drawn(const pack_t (&packs)[5], intptr_t fixed_cnt, bool self_drawn, fan_table_t &fan_table) {
	ptrdiff_t melded_cnt = std::count_if(&packs[0], &packs[fixed_cnt], &is_pack_melded);  // 明副露的组数

	switch (melded_cnt) {
	case 0:  // 0组明的，自摸为不求人，点和为门前清
		fan_table[self_drawn ? FULLY_CONCEALED_HAND : CONCEALED_HAND] = 1;
		break;
	case 4:
		// 4组明的，自摸还是自摸，点和为全求人
		fan_table[self_drawn ? SELF_DRAWN : MELDED_HAND] = 1;
		break;
	default:
		if (self_drawn) {
			fan_table[SELF_DRAWN] = 1;
		}
		break;
	}
}

// 根据雀头调整——涉及番种：平和、小三元、小四喜
static void adjust_by_pair_tile(tile_t pair_tile, intptr_t chow_cnt, fan_table_t &fan_table) {
	if (chow_cnt == 4) {  // 4组都是顺子
		if (is_numbered_suit_quick(pair_tile)) {  // 数牌雀头
			fan_table[ALL_CHOWS] = 1;  // 平和
		}
		return;
	}

	// 在双箭刻的基础上，如果雀头是箭牌，则修正为小三元
	if (fan_table[TWO_DRAGONS_PUNGS]) {
		if (is_dragons(pair_tile)) {
			fan_table[LITTLE_THREE_DRAGONS] = 1;
			fan_table[TWO_DRAGONS_PUNGS] = 0;
		}
		return;
	}
	// 在三风刻的基础上，如果雀头是风牌，则修正为小四喜
	if (fan_table[BIG_THREE_WINDS]) {
		if (is_winds(pair_tile)) {
			fan_table[LITTLE_FOUR_WINDS] = 1;
			fan_table[BIG_THREE_WINDS] = 0;
		}
		return;
	}
}

// 根据花色调整——涉及番种：无字、缺一门、混一色、清一色、五门齐
static void adjust_by_suits(const tile_t *tiles, intptr_t tile_cnt, fan_table_t &fan_table) {
	// 打表标记有哪些花色，用bit操作
	uint8_t suit_flag = 0;
	for (intptr_t i = 0; i < tile_cnt; ++i) {
		suit_flag |= (1 << tile_get_suit(tiles[i]));
	}

	// 1111 0001
	if (!(suit_flag & 0xF1U)) {
		fan_table[NO_HONORS] = 1;  // 无字
	}

	// 1110 0011
	if (!(suit_flag & 0xE3U)) {
		++fan_table[ONE_VOIDED_SUIT];  // 缺一门（万）
	}
	// 1110 0101
	if (!(suit_flag & 0xE5U)) {
		++fan_table[ONE_VOIDED_SUIT];  // 缺一门（条）
	}
	// 1110 1001
	if (!(suit_flag & 0xE9U)) {
		++fan_table[ONE_VOIDED_SUIT];  // 缺一门（饼）
	}

	// 当缺2门时，根据有字和无字，修正为混一色和清一色
	if (fan_table[ONE_VOIDED_SUIT] == 2) {
		fan_table[ONE_VOIDED_SUIT] = 0;
		fan_table[suit_flag & 0xF1U ? HALF_FLUSH : FULL_FLUSH] = 1;
	}

	// 0001 1110
	if (suit_flag == 0x1EU) {  // 三门数牌和字牌都有
		if (std::any_of(tiles, tiles + tile_cnt, &is_winds)
			&& std::any_of(tiles, tiles + tile_cnt, &is_dragons)) {
			fan_table[ALL_TYPES] = 1;  // 五门齐
		}
	}
}

// 根据数牌的范围调整——涉及番种：大于五、小于五、全大、全中、全小
static void adjust_by_rank_range(const tile_t *tiles, intptr_t tile_cnt, fan_table_t &fan_table) {
#ifdef STRICT_98_RULE
	if (fan_table[SEVEN_PAIRS]) {
		return;  // 严格98规则的七对不支持叠加这些
	}
#endif

	// 打表标记有哪些数
	uint16_t rank_flag = 0;
	for (intptr_t i = 0; i < tile_cnt; ++i) {
		if (!is_numbered_suit_quick(tiles[i])) {
			return;
		}
		rank_flag |= (1 << tile_get_rank(tiles[i]));
	}

	// 1111 1111 1110 0001
	// 检测是否只包含1234
	if (!(rank_flag & 0xFFE1)) {
		// 包含4为小于五，否则为全小
		fan_table[rank_flag & 0x0010 ? LOWER_FOUR : LOWER_TILES] = 1;
		return;
	}
	// 1111 1100 0011 1111
	// 检测是否只包含6789
	if (!(rank_flag & 0xFC3F)) {
		// 包含6为大于五，否则为全大
		fan_table[rank_flag & 0x0040 ? UPPER_FOUR : UPPER_TILES] = 1;
		return;
	}
	// 1111 1111 1000 1111
	// 检测是否只包含456
	if (!(rank_flag & 0xFF8F)) {
		// 全中
		fan_table[MIDDLE_TILES] = 1;
	}
}

// 根据牌组特征调整——涉及番种：全带幺、全带五、全双刻
static void adjust_by_packs_traits(const pack_t (&packs)[5], fan_table_t &fan_table) {
	// 统计包含数牌19、字牌、5、双数牌的组数
	int terminal_pack = 0;
	int honor_pack = 0;
	int _5_pack = 0;
	int even_pack = 0;
	for (int i = 0; i < 5; ++i) {
		tile_t tile = pack_get_tile(packs[i]);
		if (is_numbered_suit_quick(tile)) {  // 数牌
			rank_t rank = tile_get_rank(tile);
			if (pack_get_type(packs[i]) == PACK_TYPE_CHOW) {  // 顺子
				switch (rank) {
				case 2: case 8: ++terminal_pack; break;  // 数牌19
				case 4: case 5: case 6: ++_5_pack; break;  // 带五
				default: break;
				}
			}
			else {  // 刻子或雀头
				switch (rank) {
				case 1: case 9: ++terminal_pack; break;  // 数牌19
				case 5: ++_5_pack; break;  // 带五
				case 2: case 4: case 6: case 8: ++even_pack; break;  // 双刻
				default: break;
				}
			}
		}
		else {
			++honor_pack;  // 字牌
		}
	}

	// 5组牌都包含数牌19和字牌，先暂时计为全带幺
	if (terminal_pack + honor_pack == 5) {
		fan_table[OUTSIDE_HAND] = 1;
		return;
	}
	// 全带五
	if (_5_pack == 5) {
		fan_table[ALL_FIVE] = 1;
		return;
	}
	// 全双刻
	if (even_pack == 5) {
		fan_table[ALL_EVEN_PUNGS] = 1;
	}
}

// 根据牌特性调整——涉及番种：断幺、推不倒、绿一色、字一色、清幺九、混幺九
static void adjust_by_tiles_traits(const tile_t *tiles, intptr_t tile_cnt, fan_table_t &fan_table) {
	// 断幺
	if (std::none_of(tiles, tiles + tile_cnt, &is_terminal_or_honor)) {
		fan_table[ALL_SIMPLES] = 1;
	}

	// 推不倒
	if (std::all_of(tiles, tiles + tile_cnt, &is_reversible)) {
		fan_table[REVERSIBLE_TILES] = 1;
	}

#ifdef STRICT_98_RULE
	if (fan_table[SEVEN_PAIRS]) {
		return;  // 严格98规则的七对不支持绿一色、字一色、清幺九、混幺九
	}
#endif

	// 绿一色
	if (std::all_of(tiles, tiles + tile_cnt, &is_green)) {
		fan_table[ALL_GREEN] = 1;
	}

	// 如果断幺了就没必要检测字一色、清幺九、混幺九了
	if (fan_table[ALL_SIMPLES] != 0) {
		return;
	}

	// 字一色
	if (std::all_of(tiles, tiles + tile_cnt, &is_honor)) {
		fan_table[ALL_HONORS] = 1;
		return;
	}
	// 清幺九
	if (std::all_of(tiles, tiles + tile_cnt, &is_terminal)) {
		fan_table[ALL_TERMINALS] = 1;
		return;
	}
	// 混幺九
	if (std::all_of(tiles, tiles + tile_cnt, &is_terminal_or_honor)) {
		fan_table[ALL_TERMINALS_AND_HONORS] = 1;
	}
}

// 四归一调整
static void adjust_by_tiles_hog(const tile_t *tiles, intptr_t tile_cnt, fan_table_t &fan_table) {
	intptr_t kong_cnt = tile_cnt - 14;  // 标准和牌14张，多出几张就说明有几个杠
	tile_table_t cnt_table;
	map_tiles(tiles, tile_cnt, &cnt_table);
	// 有多少种已经用去4张的牌减去杠的数量，即为四归一的数量
	intptr_t _4_cnt = std::count(std::begin(cnt_table), std::end(cnt_table), 4);
	fan_table[TILE_HOG] = static_cast<uint8_t>(_4_cnt - kong_cnt);
}

// 根据听牌方式调整——涉及番种：边张、嵌张、单钓将
static void adjust_by_waiting_form(const pack_t *concealed_packs, intptr_t pack_cnt, const tile_t *standing_tiles, intptr_t standing_cnt,
	tile_t win_tile, fan_table_t &fan_table) {
	// 全求人和四杠不计单钓将，也不可能有边张、嵌张
	if (fan_table[MELDED_HAND] || fan_table[FOUR_KONGS]) {
		return;
	}

	useful_table_t waiting_table;  // 听牌标记表
	if (!is_basic_form_wait(standing_tiles, standing_cnt, &waiting_table)) {
		return;
	}

	if (pack_cnt == 5) {  // 门清状态
		// 判断是否为七对听牌
		useful_table_t temp_table;
		if (is_seven_pairs_wait(standing_tiles, standing_cnt, &temp_table)) {
			// 合并听牌标记表
			std::transform(std::begin(temp_table), std::end(temp_table), std::begin(waiting_table),
				std::begin(waiting_table), [](bool w, bool t) { return w || t; });
		}
	}

	// 统计听牌张数，听牌数大于1张，不计边张、嵌张、单钓将
	if (1 != std::count(std::begin(waiting_table), std::end(waiting_table), true)) {
		return;
	}

	// 听1张的情况，看和牌张处于什么位置
	// 边张0x01 嵌张0x02 单钓将0x04
	uint8_t pos_flag = 0;

	for (intptr_t i = 0; i < pack_cnt; ++i) {
		switch (pack_get_type(concealed_packs[i])) {
		case PACK_TYPE_CHOW: {
			tile_t mid_tile = pack_get_tile(concealed_packs[i]);
			if (mid_tile == win_tile) {
				pos_flag |= 0x02U;  // 嵌张
			}
			else if (mid_tile + 1 == win_tile || mid_tile - 1 == win_tile) {
				pos_flag |= 0x01U;  // 边张
			}
			break;
		}
		case PACK_TYPE_PAIR: {
			tile_t mid_tile = pack_get_tile(concealed_packs[i]);
			if (mid_tile == win_tile) {
				pos_flag |= 0x04U;  // 单钓将
			}
			break;
		}
		default:
			break;
		}
	}

	// 当多种可能存在时，只能计其中一种
	if (pos_flag & 0x01U) {
		fan_table[EDGE_WAIT] = 1;
	}
	else if (pos_flag & 0x02U) {
		fan_table[CLOSED_WAIT] = 1;
	}
	else if (pos_flag & 0x04U) {
		fan_table[SINGLE_WAIT] = 1;
	}
}

// 统一调整一些不计的
static void adjust_fan_table(fan_table_t &fan_table) {
	// 大四喜不计三风刻、碰碰和、圈风刻、门风刻、幺九刻
	if (fan_table[BIG_FOUR_WINDS]) {
		fan_table[BIG_THREE_WINDS] = 0;
		fan_table[ALL_PUNGS] = 0;
		fan_table[PUNG_OF_TERMINALS_OR_HONORS] = 0;
	}
	// 大三元不计双箭刻、箭刻（严格98规则不计缺一门）
	if (fan_table[BIG_THREE_DRAGONS]) {
		fan_table[TWO_DRAGONS_PUNGS] = 0;
		fan_table[DRAGON_PUNG] = 0;
#ifdef STRICT_98_RULE
		fan_table[ONE_VOIDED_SUIT] = 0;
#endif
	}
	// 绿一色不计混一色、缺一门
	if (fan_table[ALL_GREEN]) {
		fan_table[HALF_FLUSH] = 0;
		fan_table[ONE_VOIDED_SUIT] = 0;
	}
	// 九莲宝灯不计清一色、门前清、缺一门、无字，减计1个幺九刻，把不求人修正为自摸
	if (fan_table[NINE_GATES]) {
		fan_table[FULL_FLUSH] = 0;
		fan_table[CONCEALED_HAND] = 0;
		--fan_table[PUNG_OF_TERMINALS_OR_HONORS];
		fan_table[ONE_VOIDED_SUIT] = 0;
		fan_table[NO_HONORS] = 0;
		if (fan_table[FULLY_CONCEALED_HAND]) {
			fan_table[FULLY_CONCEALED_HAND] = 0;
			fan_table[SELF_DRAWN] = 1;
		}
	}
	// 四杠不计单钓将
	if (fan_table[FOUR_KONGS]) {
		fan_table[SINGLE_WAIT] = 0;
	}
	// 连七对不计七对、清一色、门前清、缺一门、无字
	if (fan_table[SEVEN_SHIFTED_PAIRS]) {
		fan_table[SEVEN_PAIRS] = 0;
		fan_table[FULL_FLUSH] = 0;
		fan_table[CONCEALED_HAND] = 0;
		fan_table[ONE_VOIDED_SUIT] = 0;
		fan_table[NO_HONORS] = 0;
	}
	// 十三幺不计五门齐、门前清、单钓将
	if (fan_table[THIRTEEN_ORPHANS]) {
		fan_table[ALL_TYPES] = 0;
		fan_table[CONCEALED_HAND] = 0;
		fan_table[SINGLE_WAIT] = 0;
	}

	// 清幺九不计混幺九、碰碰胡、全带幺、幺九刻、无字（严格98规则不计双同刻、不计三同刻）
	if (fan_table[ALL_TERMINALS]) {
		fan_table[ALL_TERMINALS_AND_HONORS] = 0;
		fan_table[ALL_PUNGS] = 0;
		fan_table[OUTSIDE_HAND] = 0;
		fan_table[PUNG_OF_TERMINALS_OR_HONORS] = 0;
		fan_table[NO_HONORS] = 0;
		fan_table[DOUBLE_PUNG] = 0;  // 通行计法不计双同刻
#ifdef STRICT_98_RULE
		fan_table[TRIPLE_PUNG] = 0;
		fan_table[DOUBLE_PUNG] = 0;
#endif
	}

	// 小四喜不计三风刻
	if (fan_table[LITTLE_FOUR_WINDS]) {
		fan_table[BIG_THREE_WINDS] = 0;
		// 小四喜的第四组牌如果是19的刻子，则是混幺九；如果是箭刻则是字一色；这两种都是不计幺九刻的
		// 如果是顺子或者2-8的刻子，则不存在多余的幺九刻
		// 所以这里将幺九刻置为0
		fan_table[PUNG_OF_TERMINALS_OR_HONORS] = 0;
	}

	// 小三元不计双箭刻、箭刻（严格98规则不计缺一门）
	if (fan_table[LITTLE_THREE_DRAGONS]) {
		fan_table[TWO_DRAGONS_PUNGS] = 0;
		fan_table[DRAGON_PUNG] = 0;
#ifdef STRICT_98_RULE
		fan_table[ONE_VOIDED_SUIT] = 0;
#endif
	}

	// 字一色不计混幺九、碰碰胡、全带幺、幺九刻、缺一门
	if (fan_table[ALL_HONORS]) {
		fan_table[ALL_TERMINALS_AND_HONORS] = 0;
		fan_table[ALL_PUNGS] = 0;
		fan_table[OUTSIDE_HAND] = 0;
		fan_table[PUNG_OF_TERMINALS_OR_HONORS] = 0;
		fan_table[ONE_VOIDED_SUIT] = 0;
	}
	// 四暗刻不计碰碰和、门前清，把不求人修正为自摸
	if (fan_table[FOUR_CONCEALED_PUNGS]) {
		fan_table[ALL_PUNGS] = 0;
		fan_table[CONCEALED_HAND] = 0;
		if (fan_table[FULLY_CONCEALED_HAND]) {
			fan_table[FULLY_CONCEALED_HAND] = 0;
			fan_table[SELF_DRAWN] = 1;
		}
	}
	// 一色双龙会不计七对、清一色、平和、一般高、老少副、缺一门、无字
	if (fan_table[PURE_TERMINAL_CHOWS]) {
		fan_table[SEVEN_PAIRS] = 0;
		fan_table[FULL_FLUSH] = 0;
		fan_table[ALL_CHOWS] = 0;
		fan_table[PURE_DOUBLE_CHOW] = 0;
		fan_table[TWO_TERMINAL_CHOWS] = 0;
		fan_table[ONE_VOIDED_SUIT] = 0;
		fan_table[NO_HONORS] = 0;
	}

	// 一色四同顺不计一色三同顺、一般高、四归一（严格98规则不计缺一门）
	if (fan_table[QUADRUPLE_CHOW]) {
		fan_table[PURE_SHIFTED_PUNGS] = 0;
		fan_table[TILE_HOG] = 0;
		fan_table[PURE_DOUBLE_CHOW] = 0;
#ifdef STRICT_98_RULE
		fan_table[ONE_VOIDED_SUIT] = 0;
#endif
	}
	// 一色四节高不计一色三节高、碰碰和（严格98规则不计缺一门）
	if (fan_table[FOUR_PURE_SHIFTED_PUNGS]) {
		fan_table[PURE_TRIPLE_CHOW] = 0;
		fan_table[ALL_PUNGS] = 0;
#ifdef STRICT_98_RULE
		fan_table[ONE_VOIDED_SUIT] = 0;
#endif
	}

	// 一色四步高不计一色三步高、老少副、连六（严格98规则不计缺一门）
	if (fan_table[FOUR_PURE_SHIFTED_CHOWS]) {
		fan_table[PURE_SHIFTED_CHOWS] = 0;
		fan_table[TWO_TERMINAL_CHOWS] = 0;
		fan_table[SHORT_STRAIGHT] = 0;
#ifdef STRICT_98_RULE
		fan_table[ONE_VOIDED_SUIT] = 0;
#endif
	}

	// 混幺九不计碰碰和、全带幺、幺九刻
	if (fan_table[ALL_TERMINALS_AND_HONORS]) {
		fan_table[ALL_PUNGS] = 0;
		fan_table[OUTSIDE_HAND] = 0;
		fan_table[PUNG_OF_TERMINALS_OR_HONORS] = 0;
	}

	// 七对不计门前清、单钓将
	if (fan_table[SEVEN_PAIRS]) {
		fan_table[CONCEALED_HAND] = 0;
		fan_table[SINGLE_WAIT] = 0;
	}
	// 七星不靠不计五门齐、门前清
	if (fan_table[GREATER_HONORS_AND_KNITTED_TILES]) {
		fan_table[ALL_TYPES] = 0;
		fan_table[CONCEALED_HAND] = 0;
	}
	// 全双刻不计碰碰胡、断幺、无字
	if (fan_table[ALL_EVEN_PUNGS]) {
		fan_table[ALL_PUNGS] = 0;
		fan_table[ALL_SIMPLES] = 0;
		fan_table[NO_HONORS] = 0;
	}
	// 清一色不计缺一门、无字
	if (fan_table[FULL_FLUSH]) {
		fan_table[ONE_VOIDED_SUIT] = 0;
		fan_table[NO_HONORS] = 0;
	}
	// 一色三同顺不计一色三节高、一般高
	if (fan_table[PURE_TRIPLE_CHOW]) {
		fan_table[PURE_SHIFTED_PUNGS] = 0;
		fan_table[PURE_DOUBLE_CHOW] = 0;
	}
	// 一色三节高不计一色三同顺
	if (fan_table[PURE_SHIFTED_PUNGS]) {
		fan_table[PURE_TRIPLE_CHOW] = 0;
	}
	// 全大不计大于五、无字
	if (fan_table[UPPER_TILES]) {
		fan_table[UPPER_FOUR] = 0;
		fan_table[NO_HONORS] = 0;
	}
	// 全中不计断幺
	if (fan_table[MIDDLE_TILES]) {
		fan_table[ALL_SIMPLES] = 0;
		fan_table[NO_HONORS] = 0;
	}
	// 全小不计小于五、无字
	if (fan_table[LOWER_TILES]) {
		fan_table[LOWER_FOUR] = 0;
		fan_table[NO_HONORS] = 0;
	}

	// 三色双龙会不计平和、无字、喜相逢、老少副
	if (fan_table[THREE_SUITED_TERMINAL_CHOWS]) {
		fan_table[ALL_CHOWS] = 0;
		fan_table[NO_HONORS] = 0;
		fan_table[MIXED_DOUBLE_CHOW] = 0;
		fan_table[TWO_TERMINAL_CHOWS] = 0;
	}
	// 全带五不计断幺、无字
	if (fan_table[ALL_FIVE]) {
		fan_table[ALL_SIMPLES] = 0;
		fan_table[NO_HONORS] = 0;
	}

	// 七星不靠不计五门齐、门前清
	if (fan_table[LESSER_HONORS_AND_KNITTED_TILES]) {
		fan_table[ALL_TYPES] = 0;
		fan_table[CONCEALED_HAND] = 0;
	}
	// 大于五不计无字
	if (fan_table[UPPER_FOUR]) {
		fan_table[NO_HONORS] = 0;
	}
	// 小于五不计无字
	if (fan_table[LOWER_FOUR]) {
		fan_table[NO_HONORS] = 0;
	}
	// 三风刻内部不再计幺九刻（严格98规则不计缺一门）
	if (fan_table[BIG_THREE_WINDS]) {
		// 如果不是字一色或混幺九，则要减去3个幺九刻
		if (!fan_table[ALL_HONORS] && !fan_table[ALL_TERMINALS_AND_HONORS]) {
			assert(fan_table[PUNG_OF_TERMINALS_OR_HONORS] >= 3);
			fan_table[PUNG_OF_TERMINALS_OR_HONORS] -= 3;
		}
#ifdef STRICT_98_RULE
		fan_table[ONE_VOIDED_SUIT] = 0;
#endif
	}

	// 推不倒不计缺一门
	if (fan_table[REVERSIBLE_TILES]) {
		fan_table[ONE_VOIDED_SUIT] = 0;
	}
	// 妙手回春不计自摸
	if (fan_table[LAST_TILE_DRAW]) {
		fan_table[SELF_DRAWN] = 0;
	}
	// 杠上开花不计自摸
	if (fan_table[OUT_WITH_REPLACEMENT_TILE]) {
		fan_table[SELF_DRAWN] = 0;
	}
	// 抢杠和不计和绝张
	if (fan_table[ROBBING_THE_KONG]) {
		fan_table[LAST_TILE] = 0;
	}
	// 双暗杠不计暗杠
	if (fan_table[TWO_CONCEALED_KONGS]) {
		fan_table[CONCEALED_KONG] = 0;
	}

	// 混一色不计缺一门
	if (fan_table[HALF_FLUSH]) {
		fan_table[ONE_VOIDED_SUIT] = 0;
	}
	// 全求人不计单钓将
	if (fan_table[MELDED_HAND]) {
		fan_table[SINGLE_WAIT] = 0;
	}
	// 双箭刻不计箭刻
	if (fan_table[TWO_DRAGONS_PUNGS]) {
		fan_table[DRAGON_PUNG] = 0;
	}

	// 不求人不计自摸
	if (fan_table[FULLY_CONCEALED_HAND]) {
		fan_table[SELF_DRAWN] = 0;
	}
	// 双明杠不计明杠
	if (fan_table[TWO_MELDED_KONGS]) {
		fan_table[MELDED_KONG] = 0;
	}

	// 平和不计无字
	if (fan_table[ALL_CHOWS]) {
		fan_table[NO_HONORS] = 0;
	}
	// 断幺不计无字
	if (fan_table[ALL_SIMPLES]) {
		fan_table[NO_HONORS] = 0;
	}
}

// 调整圈风刻、门风刻
static void adjust_by_winds(tile_t tile, wind_t prevalent_wind, wind_t seat_wind, fan_table_t &fan_table) {
	// 三风刻、混幺九、字一色、小四喜，这些番种已经扣除过幺九刻了
	bool is_deducted = (fan_table[BIG_THREE_WINDS] || fan_table[ALL_TERMINALS_AND_HONORS] || fan_table[ALL_HONORS] || fan_table[LITTLE_FOUR_WINDS]);

	rank_t delta = tile - TILE_E;
	if (delta == static_cast<int>(prevalent_wind) - static_cast<int>(wind_t::EAST)) {
		fan_table[PREVALENT_WIND] = 1;
		if (!is_deducted) {
			--fan_table[PUNG_OF_TERMINALS_OR_HONORS];
		}
	}
	if (delta == static_cast<int>(seat_wind) - static_cast<int>(wind_t::EAST)) {
		fan_table[SEAT_WIND] = 1;
		// 当圈风门风相同时，已经扣除过幺九刻了
		if (seat_wind != prevalent_wind && !is_deducted) {
			--fan_table[PUNG_OF_TERMINALS_OR_HONORS];
		}
	}
}

// 根据和牌标记调整——涉及番种：和绝张、妙手回春、海底捞月、自摸
static void adjust_by_win_flag(win_flag_t win_flag, fan_table_t &fan_table) {
	if (win_flag & WIN_FLAG_4TH_TILE) {
		fan_table[LAST_TILE] = 1;
	}
	if (win_flag & WIN_FLAG_WALL_LAST) {
		fan_table[win_flag & WIN_FLAG_SELF_DRAWN ? LAST_TILE_DRAW : LAST_TILE_CLAIM] = 1;
	}
	if (win_flag & WIN_FLAG_ABOUT_KONG) {
		fan_table[win_flag & WIN_FLAG_SELF_DRAWN ? OUT_WITH_REPLACEMENT_TILE : ROBBING_THE_KONG] = 1;
	}
	if (win_flag & WIN_FLAG_SELF_DRAWN) {
		fan_table[SELF_DRAWN] = 1;
	}
}

// 基本和型算番
static void calculate_basic_form_fan(const pack_t (&packs)[5], const calculate_param_t *calculate_param, win_flag_t win_flag, fan_table_t &fan_table) {
	pack_t pair_pack = 0;
	pack_t chow_packs[4];
	pack_t pung_packs[4];
	intptr_t chow_cnt = 0;
	intptr_t pung_cnt = 0;
	for (int i = 0; i < 5; ++i) {
		switch (pack_get_type(packs[i])) {
		case PACK_TYPE_CHOW: chow_packs[chow_cnt++] = packs[i]; break;
		case PACK_TYPE_PUNG:
		case PACK_TYPE_KONG: pung_packs[pung_cnt++] = packs[i]; break;
		case PACK_TYPE_PAIR: pair_pack = packs[i]; break;
		default: UNREACHABLE(); return;
		}
	}

	if (pair_pack == 0 || chow_cnt + pung_cnt != 4) {
		return;
	}

	tile_t win_tile = calculate_param->win_tile;

	// 根据和牌标记调整——涉及番种：和绝张、妙手回春、海底捞月、自摸
	adjust_by_win_flag(win_flag, fan_table);

	// 点和的牌张，如果不能解释为顺子中的一张，那么将其解释为刻子，并标记这个刻子为明刻
	if ((win_flag & WIN_FLAG_SELF_DRAWN) == 0) {
		// 和牌不能解释为顺子中的一张
		if (std::none_of(chow_packs, chow_packs + chow_cnt, [win_tile](pack_t chow_pack) {
			tile_t tile = pack_get_tile(chow_pack);
			return !is_pack_melded(chow_pack)
				&& (tile - 1 == win_tile || tile == win_tile || tile + 1 == win_tile);
		})) {
			for (intptr_t i = 0; i < pung_cnt; ++i) {
				if (pack_get_tile(pung_packs[i]) == win_tile && !is_pack_melded(pung_packs[i])) {
					pung_packs[i] |= (1 << 12);  // 标记为明副露
				}
			}
		}
	}

	if (pung_cnt > 0) { // 有刻子
		calculate_kongs(pung_packs, pung_cnt, fan_table);
	}

	switch (chow_cnt) {
	case 4: {  // 4组顺子
		// 检测三色/一色双龙会
		if (is_three_suited_terminal_chows(chow_packs, pair_pack)) {
			fan_table[THREE_SUITED_TERMINAL_CHOWS] = 1;
			break;
		}
		if (is_pure_terminal_chows(chow_packs, pair_pack)) {
			fan_table[PURE_TERMINAL_CHOWS] = 1;
			break;
		}

		tile_t mid_tiles[4];
		mid_tiles[0] = pack_get_tile(chow_packs[0]);
		mid_tiles[1] = pack_get_tile(chow_packs[1]);
		mid_tiles[2] = pack_get_tile(chow_packs[2]);
		mid_tiles[3] = pack_get_tile(chow_packs[3]);
		std::sort(std::begin(mid_tiles), std::end(mid_tiles));

		calculate_4_chows(mid_tiles, fan_table);
		break;
	}
	case 3: {  // 3组顺子+1组刻子
		tile_t mid_tiles[3];
		mid_tiles[0] = pack_get_tile(chow_packs[0]);
		mid_tiles[1] = pack_get_tile(chow_packs[1]);
		mid_tiles[2] = pack_get_tile(chow_packs[2]);
		std::sort(std::begin(mid_tiles), std::end(mid_tiles));

		calculate_3_chows(mid_tiles, fan_table);
		break;
	}
	case 2: {  // 2组顺子+2组刻子
		tile_t mid_tiles_chow[2];
		mid_tiles_chow[0] = pack_get_tile(chow_packs[0]);
		mid_tiles_chow[1] = pack_get_tile(chow_packs[1]);

		tile_t mid_tiles_pung[2];
		mid_tiles_pung[0] = pack_get_tile(pung_packs[0]);
		mid_tiles_pung[1] = pack_get_tile(pung_packs[1]);

		calculate_2_chows_unordered(mid_tiles_chow, fan_table);
		calculate_2_pungs_unordered(mid_tiles_pung, fan_table);
		break;
	}
	case 1: {  // 1组顺子+3组刻子
		tile_t mid_tiles[3];
		mid_tiles[0] = pack_get_tile(pung_packs[0]);
		mid_tiles[1] = pack_get_tile(pung_packs[1]);
		mid_tiles[2] = pack_get_tile(pung_packs[2]);
		std::sort(std::begin(mid_tiles), std::end(mid_tiles));

		calculate_3_pungs(mid_tiles, fan_table);
		break;
	}
	case 0: {  // 4组刻子
		tile_t mid_tiles[4];
		mid_tiles[0] = pack_get_tile(pung_packs[0]);
		mid_tiles[1] = pack_get_tile(pung_packs[1]);
		mid_tiles[2] = pack_get_tile(pung_packs[2]);
		mid_tiles[3] = pack_get_tile(pung_packs[3]);
		std::sort(std::begin(mid_tiles), std::end(mid_tiles));

		calculate_4_pungs(mid_tiles, fan_table);
		break;
	}
	default:
		UNREACHABLE();
		break;
	}

	intptr_t fixed_cnt = calculate_param->hand_tiles.pack_count;
	const tile_t *standing_tiles = calculate_param->hand_tiles.standing_tiles;
	intptr_t standing_cnt = calculate_param->hand_tiles.tile_count;
	wind_t prevalent_wind = calculate_param->prevalent_wind;
	wind_t seat_wind = calculate_param->seat_wind;

	bool heaven_win = (win_flag & (WIN_FLAG_INIT | WIN_FLAG_SELF_DRAWN)) == (WIN_FLAG_INIT | WIN_FLAG_SELF_DRAWN);

	// 九莲宝灯
	if (!heaven_win && standing_cnt == 13) {
		if (is_nine_gates(standing_tiles)) {
			fan_table[NINE_GATES] = 1;
		}
	}

	// 根据和牌方式调整——涉及番种：不求人、全求人
	adjust_by_self_drawn(packs, fixed_cnt, (win_flag & WIN_FLAG_SELF_DRAWN) != 0, fan_table);
	// 根据雀头调整——涉及番种：平和、小三元、小四喜
	adjust_by_pair_tile(pack_get_tile(pair_pack), chow_cnt, fan_table);
	// 根据牌组特征调整——涉及番种：全带幺、全带五、全双刻
	adjust_by_packs_traits(packs, fan_table);

	tile_t tiles[18];
	memcpy(tiles, standing_tiles, standing_cnt * sizeof(tile_t));
	intptr_t tile_cnt = packs_to_tiles(packs, fixed_cnt, &tiles[standing_cnt], 18 - standing_cnt);
	tile_cnt += standing_cnt;
	tiles[tile_cnt++] = win_tile;

	// 根据花色调整——涉及番种：无字、缺一门、混一色、清一色、五门齐
	adjust_by_suits(tiles, tile_cnt, fan_table);
	// 根据牌特性调整——涉及番种：断幺、推不倒、绿一色、字一色、清幺九、混幺九
	adjust_by_tiles_traits(tiles, tile_cnt, fan_table);
	// 根据数牌的范围调整——涉及番种：大于五、小于五、全大、全中、全小
	adjust_by_rank_range(tiles, tile_cnt, fan_table);
	// 四归一调整
	adjust_by_tiles_hog(tiles, tile_cnt, fan_table);

	if (!heaven_win) {
		// 根据听牌方式调整——涉及番种：边张、嵌张、单钓将
		adjust_by_waiting_form(packs + fixed_cnt, 5 - fixed_cnt, standing_tiles, standing_cnt, win_tile, fan_table);
	}

	// 统一调整一些不计的
	adjust_fan_table(fan_table);

	// 调整圈风刻、门风刻（大四喜不计圈风刻、门风刻）
	if (fan_table[BIG_FOUR_WINDS] == 0) {
		for (intptr_t i = 0; i < pung_cnt; ++i) {
			tile_t tile = pack_get_tile(pung_packs[i]);
			if (is_winds(tile)) {
				adjust_by_winds(tile, prevalent_wind, seat_wind, fan_table);
			}
		}
	}

	// 如果什么番都没有，则计为无番和
	if (std::all_of(std::begin(fan_table), std::end(fan_table), [](uint16_t p) { return p == 0; })) {
		fan_table[CHICKEN_HAND] = 1;
	}
}

// “组合龙+面子+雀头”和型算番
static bool calculate_knitted_straight_fan(const calculate_param_t *calculate_param, win_flag_t win_flag, fan_table_t &fan_table) {
	const hand_tiles_t *hand_tiles = &calculate_param->hand_tiles;
	tile_t win_tile = calculate_param->win_tile;
	wind_t prevalent_wind = calculate_param->prevalent_wind;
	wind_t seat_wind = calculate_param->seat_wind;

	intptr_t fixed_cnt = hand_tiles->pack_count;
	if (fixed_cnt > 1) {
		return false;
	}

	const pack_t *fixed_packs = hand_tiles->fixed_packs;
	intptr_t standing_cnt = hand_tiles->tile_count;

	// 对立牌和和牌的种类进行打表
	tile_table_t cnt_table;
	map_tiles(hand_tiles->standing_tiles, standing_cnt, &cnt_table);
	++cnt_table[win_tile];

	// 匹配组合龙
	const tile_t (*matched_seq)[9] = std::find_if(&standard_knitted_straight[0], &standard_knitted_straight[6],
		[&cnt_table](const tile_t (&seq)[9]) {
		return std::all_of(std::begin(seq), std::end(seq), [&cnt_table](tile_t t) { return cnt_table[t] > 0; });
	});

	if (matched_seq == &standard_knitted_straight[6]) {
		return false;
	}

	// 剔除组合龙
	std::for_each(std::begin(*matched_seq), std::end(*matched_seq), [&cnt_table](tile_t t) { --cnt_table[t]; });

	// 按基本和型划分
	division_result_t result;
	result.count = 0;
	division_t work_division;
	memset(&work_division, 0, sizeof(work_division));

	// 此处逻辑为：将组合龙9张牌当作是已经完成的3组面子，空出0 1 2下标处的3组
	// 如果第4组是副露的，将其放在下标3处
	// 然后按基本和型从从fixed_cnt + 3开始递归
	// 划分后的结果，下标3处为第四组面子，下标4处为雀头
	if (fixed_cnt == 1) {
		work_division.packs[3] = fixed_packs[0];
	}
	divide_recursively(cnt_table, fixed_cnt + 3, 0, &work_division, &result);
	if (result.count != 1) {
		return false;
	}

	const pack_t *packs = result.divisions[0].packs;  // packs的0 1 2下标都是没用的

	// 标记番
	fan_table[KNITTED_STRAIGHT] = 1;  // 组合龙
	if (pack_get_type(packs[3]) == PACK_TYPE_CHOW) {  // 第4组是顺子
		if (is_numbered_suit_quick(pack_get_tile(packs[4]))) {
			fan_table[ALL_CHOWS] = 1;  // 雀头是数牌时，为平和
		}
	}
	else {
		calculate_kongs(&packs[3], 1, fan_table);
	}

	adjust_by_win_flag(win_flag, fan_table);
	// 门前清（暗杠不影响）
	if (fixed_cnt == 0 || (pack_get_type(packs[3]) == PACK_TYPE_KONG && !is_pack_melded(packs[3]))) {
		if (win_flag & WIN_FLAG_SELF_DRAWN) {
			fan_table[FULLY_CONCEALED_HAND] = 1;
		}
		else {
			fan_table[CONCEALED_HAND] = 1;
		}
	}

	// 还原牌
	tile_t tiles[15];  // 第四组可能为杠，所以最多为15张
	memcpy(tiles, matched_seq, sizeof(*matched_seq));  // 组合龙的部分
	intptr_t tile_cnt = packs_to_tiles(&packs[3], 2, tiles + 9, 6);  // 一组面子+一对雀头 最多6张牌
	tile_cnt += 9;

	// 根据花色调整——涉及番种：无字、缺一门、混一色、清一色、五门齐
	adjust_by_suits(tiles, tile_cnt, fan_table);
	// 牌组以及牌特征就不需要调整了，有组合龙的存在绝对不可能存在全带幺、全带五、全双刻，断幺、推不倒、绿一色、字一色、清幺九、混幺九
	// 四归一调整
	adjust_by_tiles_hog(tiles, tile_cnt, fan_table);

	// 和牌张是组合龙范围的牌，不计边张、嵌张、单钓将
	if (std::none_of(std::begin(*matched_seq), std::end(*matched_seq), [win_tile](tile_t t) { return t == win_tile; })) {
		if (fixed_cnt == 0) {  // 门清的牌有可能存在边张、嵌张、单钓将
			// 将除去组合龙的部分恢复成牌
			--cnt_table[win_tile];
			tile_t temp[4];
			intptr_t cnt = table_to_tiles(cnt_table, temp, 4);

			// 根据听牌方式调整——涉及番种：边张、嵌张、单钓将
			adjust_by_waiting_form(packs + 3, 2, temp, cnt, win_tile, fan_table);
		}
		else {
			// 非门清状态如果听牌不在组合龙范围内，必然是单钓将
			fan_table[SINGLE_WAIT] = 1;
		}
	}

	// 统一调整一些不计的
	adjust_fan_table(fan_table);

	// 调整圈风刻、门风刻
	tile_t tile = pack_get_tile(packs[3]);
	if (is_winds(tile)) {
		adjust_by_winds(tile, prevalent_wind, seat_wind, fan_table);
	}

	return true;
}

// 十三幺
static FORCE_INLINE bool is_thirteen_orphans(const tile_t (&tiles)[14]) {
	return std::all_of(std::begin(tiles), std::end(tiles), &is_terminal_or_honor)
		&& std::includes(std::begin(tiles), std::end(tiles),
		std::begin(standard_thirteen_orphans), std::end(standard_thirteen_orphans));
}

// 全不靠/七星不靠算番
static bool calculate_honors_and_knitted_tiles(const tile_t (&standing_tiles)[14], fan_table_t &fan_table) {
	const tile_t *honor_begin = std::find_if(std::begin(standing_tiles), std::end(standing_tiles), &is_honor);
	int numbered_cnt = static_cast<int>(honor_begin - standing_tiles);
	// 数牌张数大于9或者小于7必然不可能是全不靠
	if (numbered_cnt > 9 || numbered_cnt < 7) {
		return false;
	}

	// 匹配组合龙
	if (std::none_of(&standard_knitted_straight[0], &standard_knitted_straight[6],
		[&standing_tiles, honor_begin](const tile_t (&seq)[9]) {
		return std::includes(std::begin(seq), std::end(seq), std::begin(standing_tiles), honor_begin);
	})) {
		return false;
	}

	if (numbered_cnt == 7 && std::equal(std::begin(standard_thirteen_orphans) + 6, std::end(standard_thirteen_orphans), standing_tiles + 7)) {
		// 七种字牌齐，为七星不靠
		fan_table[GREATER_HONORS_AND_KNITTED_TILES] = 1;
		return true;
	}
	else if (std::includes(std::begin(standard_thirteen_orphans) + 6, std::end(standard_thirteen_orphans), honor_begin, std::end(standing_tiles))) {
		// 全不靠
		fan_table[LESSER_HONORS_AND_KNITTED_TILES] = 1;
		if (numbered_cnt == 9) {  // 有9张数牌，为带组合龙的全不靠
			fan_table[KNITTED_STRAIGHT] = 1;
		}
		return true;
	}

	return false;
}

// 特殊和型算番
static bool calculate_special_form_fan(const tile_t (&standing_tiles)[14], win_flag_t win_flag, fan_table_t &fan_table) {
	// 七对
	if (standing_tiles[0] == standing_tiles[1]
		&& standing_tiles[2] == standing_tiles[3]
		&& standing_tiles[4] == standing_tiles[5]
		&& standing_tiles[6] == standing_tiles[7]
		&& standing_tiles[8] == standing_tiles[9]
		&& standing_tiles[10] == standing_tiles[11]
		&& standing_tiles[12] == standing_tiles[13]) {

		if (is_numbered_suit_quick(standing_tiles[0])
			&& standing_tiles[0] + 1 == standing_tiles[2]
			&& standing_tiles[2] + 1 == standing_tiles[4]
			&& standing_tiles[4] + 1 == standing_tiles[6]
			&& standing_tiles[6] + 1 == standing_tiles[8]
			&& standing_tiles[8] + 1 == standing_tiles[10]
			&& standing_tiles[10] + 1 == standing_tiles[12]) {
			// 连七对
			fan_table[SEVEN_SHIFTED_PAIRS] = 1;
			adjust_by_tiles_traits(standing_tiles, 14, fan_table);
		}
		else {
			// 普通七对
			fan_table[SEVEN_PAIRS] = 1;

			// 根据花色调整——涉及番种：无字、缺一门、混一色、清一色、五门齐
			adjust_by_suits(standing_tiles, 14, fan_table);
			// 根据牌特性调整——涉及番种：断幺、推不倒、绿一色、字一色、清幺九、混幺九
			adjust_by_tiles_traits(standing_tiles, 14, fan_table);
			// 根据数牌的范围调整——涉及番种：大于五、小于五、全大、全中、全小
			adjust_by_rank_range(standing_tiles, 14, fan_table);
			// 四归一调整
			adjust_by_tiles_hog(standing_tiles, 14, fan_table);
		}
	}
	// 十三幺
	else if (is_thirteen_orphans(standing_tiles)) {
		fan_table[THIRTEEN_ORPHANS] = 1;
	}
	// 全不靠/七星不靠
	else if (calculate_honors_and_knitted_tiles(standing_tiles, fan_table)) {
	}
	else {
		return false;
	}

	adjust_by_win_flag(win_flag, fan_table);
	// 统一调整一些不计的，根据风调整就没必要了，这些特殊和型都没有面子，不存在圈风刻、门风刻
	adjust_fan_table(fan_table);

	return true;
}

// 从番表计算番数
static int get_fan_by_table(const fan_table_t &fan_table) {
	int fan = 0;
	for (int i = 1; i < FAN_TABLE_SIZE; ++i) {
		if (fan_table[i] == 0) {
			continue;
		}
		fan += fan_value_table[i] * fan_table[i];
#if 0  // Debug
		if (fan_table[i] == 1) {
			LOG("%s %hu\n", fan_name[i], fan_value_table[i]);
		}
		else {
			LOG("%s %hu*%hu\n", fan_name[i], fan_value_table[i], fan_table[i]);
		}
#endif
	}
	return fan;
}

// 判断立牌是否包含和牌
bool is_standing_tiles_contains_win_tile(const tile_t *standing_tiles, intptr_t standing_cnt, tile_t win_tile) {
	return std::any_of(standing_tiles, standing_tiles + standing_cnt,
		[win_tile](tile_t tile) { return tile == win_tile; });
}

// 统计和牌在副露牌组中出现的张数
size_t count_win_tile_in_fixed_packs(const pack_t *fixed_packs, intptr_t fixed_cnt, tile_t win_tile) {
	tile_table_t cnt_table = { 0 };
	for (intptr_t i = 0; i < fixed_cnt; ++i) {
		pack_t pack = fixed_packs[i];
		tile_t tile = pack_get_tile(pack);
		switch (pack_get_type(pack)) {
		case PACK_TYPE_CHOW: ++cnt_table[tile - 1]; ++cnt_table[tile]; ++cnt_table[tile + 1]; break;
		case PACK_TYPE_PUNG: cnt_table[tile] += 3; break;
		case PACK_TYPE_KONG: cnt_table[tile] += 4; break;
		default: break;
		}
	}
	return cnt_table[win_tile];
}

// 判断副露牌组是否包含杠
bool is_fixed_packs_contains_kong(const pack_t *fixed_packs, intptr_t fixed_cnt) {
	return std::any_of(fixed_packs, fixed_packs + fixed_cnt,
		[](pack_t pack) { return pack_get_type(pack) == PACK_TYPE_KONG; });
}

// 检查算番的输入是否合法
int check_calculator_input(const hand_tiles_t *hand_tiles, tile_t win_tile) {
	// 打表
	tile_table_t cnt_table;
	if (!map_hand_tiles(hand_tiles, &cnt_table)) {
		return ERROR_WRONG_TILES_COUNT;
	}
	if (win_tile != 0) {
		++cnt_table[win_tile];
	}

	// 如果某张牌超过4
	if (std::any_of(std::begin(cnt_table), std::end(cnt_table), [](int cnt) { return cnt > 4; })) {
		return ERROR_TILE_COUNT_GREATER_THAN_4;
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// 算番
//
int calculate_fan(const calculate_param_t *calculate_param, fan_table_t *fan_table) {
	const hand_tiles_t *hand_tiles = &calculate_param->hand_tiles;
	tile_t win_tile = calculate_param->win_tile;
	win_flag_t win_flag = calculate_param->win_flag;

	if (int ret = check_calculator_input(hand_tiles, win_tile)) {
		return ret;
	}

	intptr_t fixed_cnt = hand_tiles->pack_count;
	intptr_t standing_cnt = hand_tiles->tile_count;

	// 校正和牌标记
	// 如果立牌包含和牌，则必然不是和绝张
	const bool standing_tiles_contains_win_tile = is_standing_tiles_contains_win_tile(hand_tiles->standing_tiles, standing_cnt, win_tile);
	if (standing_tiles_contains_win_tile) {
		win_flag &= ~WIN_FLAG_4TH_TILE;
	}

	// 如果和牌在副露中出现3张，则必然为和绝张
	const size_t win_tile_in_fixed_packs = count_win_tile_in_fixed_packs(hand_tiles->fixed_packs, fixed_cnt, win_tile);
	if (3 == win_tile_in_fixed_packs) {
		win_flag |= WIN_FLAG_4TH_TILE;
	}

	// 附加杠标记
	if (win_flag & WIN_FLAG_ABOUT_KONG) {
		if (win_flag & WIN_FLAG_SELF_DRAWN) {  // 自摸
			// 如果手牌没有杠，则必然不是杠上开花
			if (!is_fixed_packs_contains_kong(hand_tiles->fixed_packs, fixed_cnt)) {
				win_flag &= ~WIN_FLAG_ABOUT_KONG;
			}
		}
		else {  // 点和
			// 如果和牌在手牌范围内出现过，则必然不是抢杠和
			if (win_tile_in_fixed_packs > 0 || standing_tiles_contains_win_tile) {
				win_flag &= ~WIN_FLAG_ABOUT_KONG;
			}
		}
	}

	// 合并立牌与和牌，并排序，最多为14张
	tile_t standing_tiles[14];
	memcpy(standing_tiles, hand_tiles->standing_tiles, standing_cnt * sizeof(tile_t));
	standing_tiles[standing_cnt] = win_tile;
	std::sort(standing_tiles, standing_tiles + standing_cnt + 1);

	// 最大番标记
	int max_fan = 0;
	const fan_table_t *selected_fan_table = nullptr;

	// 特殊和型的番
	fan_table_t special_fan_table = { 0 };

	// 先判断各种特殊和型
	if (fixed_cnt == 0) {  // 门清状态，有可能是基本和型组合龙
		if (calculate_knitted_straight_fan(calculate_param, win_flag, special_fan_table)) {
			max_fan = get_fan_by_table(special_fan_table);
			selected_fan_table = &special_fan_table;
			LOG("fan = %d\n\n", max_fan);
		}
		else if (calculate_special_form_fan(standing_tiles, win_flag, special_fan_table)) {
			max_fan = get_fan_by_table(special_fan_table);
			selected_fan_table = &special_fan_table;
			LOG("fan = %d\n\n", max_fan);
		}
	}
	else if (fixed_cnt == 1) {  // 1副露状态，有可能是基本和型组合龙
		if (calculate_knitted_straight_fan(calculate_param, win_flag, special_fan_table)) {
			max_fan = get_fan_by_table(special_fan_table);
			selected_fan_table = &special_fan_table;
			LOG("fan = %d\n\n", max_fan);
		}
	}

	// 无法构成特殊和型或者为七对
	// 七对也要按基本和型划分，因为极端情况下，基本和型的番会超过七对的番
	if (selected_fan_table == nullptr || special_fan_table[SEVEN_PAIRS] == 1) {
		// 划分
		division_result_t result;
		if (divide_win_hand(standing_tiles, hand_tiles->fixed_packs, fixed_cnt, &result)) {
			fan_table_t fan_tables[MAX_DIVISION_CNT] = { { 0 } };

			// 遍历各种划分方式，分别算番，找出最大的番的划分方式
			for (intptr_t i = 0; i < result.count; ++i) {
#if 0  // Debug
				char str[64];
				packs_to_string(result.divisions[i].packs, 5, str, sizeof(str));
				puts(str);
#endif
				calculate_basic_form_fan(result.divisions[i].packs, calculate_param, win_flag, fan_tables[i]);
				int current_fan = get_fan_by_table(fan_tables[i]);
				if (current_fan > max_fan) {
					max_fan = current_fan;
					selected_fan_table = &fan_tables[i];
				}
				LOG("fan = %d\n\n", current_fan);
			}
		}
	}

	if (selected_fan_table == nullptr) {
		return ERROR_NOT_WIN;
	}

	// 加花牌
	max_fan += calculate_param->flower_count;

	if (fan_table != nullptr) {
		memcpy(*fan_table, *selected_fan_table, sizeof(*fan_table));
		(*fan_table)[FLOWER_TILES] = calculate_param->flower_count;
	}

	return max_fan;
}

}

/*** End of inlined file: fan_calculator.cpp ***/


/*** Start of inlined file: shanten.cpp ***/
#include <assert.h>
#include <string.h>
#include <limits>
#include <algorithm>
#include <iterator>

namespace mahjong {

// 牌组转换成牌
intptr_t packs_to_tiles(const pack_t *packs, intptr_t pack_cnt, tile_t *tiles, intptr_t tile_cnt) {
	if (packs == nullptr || tiles == nullptr) {
		return 0;
	}

	intptr_t cnt = 0;
	for (int i = 0; i < pack_cnt && cnt < tile_cnt; ++i) {
		tile_t tile = pack_get_tile(packs[i]);
		switch (pack_get_type(packs[i])) {
		case PACK_TYPE_CHOW:
			if (cnt < tile_cnt) tiles[cnt++] = static_cast<tile_t>(tile - 1);
			if (cnt < tile_cnt) tiles[cnt++] = tile;
			if (cnt < tile_cnt) tiles[cnt++] = static_cast<tile_t>(tile + 1);
			break;
		case PACK_TYPE_PUNG:
			if (cnt < tile_cnt) tiles[cnt++] = tile;
			if (cnt < tile_cnt) tiles[cnt++] = tile;
			if (cnt < tile_cnt) tiles[cnt++] = tile;
			break;
		case PACK_TYPE_KONG:
			if (cnt < tile_cnt) tiles[cnt++] = tile;
			if (cnt < tile_cnt) tiles[cnt++] = tile;
			if (cnt < tile_cnt) tiles[cnt++] = tile;
			if (cnt < tile_cnt) tiles[cnt++] = tile;
			break;
		case PACK_TYPE_PAIR:
			if (cnt < tile_cnt) tiles[cnt++] = tile;
			if (cnt < tile_cnt) tiles[cnt++] = tile;
			break;
		default:
			UNREACHABLE();
			break;
		}
	}
	return cnt;
}

// 将牌打表
void map_tiles(const tile_t *tiles, intptr_t cnt, tile_table_t *cnt_table) {
	memset(*cnt_table, 0, sizeof(*cnt_table));
	for (intptr_t i = 0; i < cnt; ++i) {
		++(*cnt_table)[tiles[i]];
	}
}

// 将手牌打表
bool map_hand_tiles(const hand_tiles_t *hand_tiles, tile_table_t *cnt_table) {
	// 将每一组副露当作3张牌来算，那么总张数=13
	if (hand_tiles->tile_count <= 0 || hand_tiles->pack_count < 0 || hand_tiles->pack_count > 4
		|| hand_tiles->pack_count * 3 + hand_tiles->tile_count != 13) {
		return false;
	}

	// 将副露恢复成牌
	tile_t tiles[18];
	intptr_t tile_cnt = 0;
	if (hand_tiles->pack_count == 0) {
		memcpy(tiles, hand_tiles->standing_tiles, 13 * sizeof(tile_t));
		tile_cnt = 13;
	}
	else {
		tile_cnt = packs_to_tiles(hand_tiles->fixed_packs, hand_tiles->pack_count, tiles, 18);
		memcpy(tiles + tile_cnt, hand_tiles->standing_tiles, hand_tiles->tile_count * sizeof(tile_t));
		tile_cnt += hand_tiles->tile_count;
	}

	// 打表
	map_tiles(tiles, tile_cnt, cnt_table);
	return true;
}

// 将表转换成牌
intptr_t table_to_tiles(const tile_table_t &cnt_table, tile_t *tiles, intptr_t max_cnt) {
	intptr_t cnt = 0;
	for (int i = 0; i < 34; ++i) {
		tile_t t = all_tiles[i];
		for (int n = 0; n < cnt_table[t]; ++n) {
			*tiles++ = t;
			++cnt;
			if (cnt == max_cnt) {
				return max_cnt;
			}
		}
	}
	return cnt;
}

namespace {

	// 路径单元，单元有面子、雀头、搭子等种类，见下面的宏
	// 高8位表示类型，低8位表示牌
	// 对于顺子和顺子搭子，牌指的是最小的一张牌，
	// 例如在顺子123万中，牌为1万，在两面搭子45条中，牌为4条等等
	typedef uint16_t path_unit_t;

#define UNIT_TYPE_CHOW 1                // 顺子
#define UNIT_TYPE_PUNG 2                // 刻子
#define UNIT_TYPE_PAIR 4                // 雀头
#define UNIT_TYPE_CHOW_OPEN_END 5       // 两面或者边张搭子
#define UNIT_TYPE_CHOW_CLOSED 6         // 嵌张搭子
#define UNIT_TYPE_INCOMPLETE_PUNG 7     // 刻子搭子

#define MAKE_UNIT(type_, tile_) static_cast<path_unit_t>(((type_) << 8) | (tile_))
#define UNIT_TYPE(unit_) (((unit_) >> 8) & 0xFF)
#define UNIT_TILE(unit_) ((unit_) & 0xFF)

#define MAX_STATE 512
#define UNIT_SIZE 7

	// 一条路径
	struct work_path_t {
		path_unit_t units[UNIT_SIZE];  // 14/2=7最多7个搭子
		uint16_t depth;  // 当前路径深度
	};

	// 当前工作状态
	struct work_state_t {
		work_path_t paths[MAX_STATE];  // 所有路径
		intptr_t count;  // 路径数量
	};
}

// 路径是否来过了
static bool is_basic_form_branch_exist(const intptr_t fixed_cnt, const work_path_t *work_path, const work_state_t *work_state) {
	if (work_state->count <= 0 || work_path->depth == 0) {
		return false;
	}

	// depth处有信息，所以按stl风格的end应该要+1
	const uint16_t depth = static_cast<uint16_t>(work_path->depth + 1);

	// std::includes要求有序，但又不能破坏当前数据
	work_path_t temp;
	std::copy(&work_path->units[fixed_cnt], &work_path->units[depth], &temp.units[fixed_cnt]);
	std::sort(&temp.units[fixed_cnt], &temp.units[depth]);

	return std::any_of(&work_state->paths[0], &work_state->paths[work_state->count],
		[&temp, fixed_cnt, depth](const work_path_t &path) {
		return std::includes(&path.units[fixed_cnt], &path.units[path.depth], &temp.units[fixed_cnt], &temp.units[depth]);
	});
}

// 保存路径
static void save_work_path(const intptr_t fixed_cnt, const work_path_t *work_path, work_state_t *work_state) {
	// 复制一份数据，不破坏当前数据
	work_path_t temp;
	temp.depth = work_path->depth;
	std::copy(&work_path->units[fixed_cnt], &work_path->units[temp.depth + 1], &temp.units[fixed_cnt]);
	std::sort(&temp.units[fixed_cnt], &temp.units[temp.depth + 1]);

	// 判断是否重复
	if (std::none_of(&work_state->paths[0], &work_state->paths[work_state->count],
		[&temp, fixed_cnt](const work_path_t &path) {
		return (path.depth == temp.depth && std::equal(&path.units[fixed_cnt], &path.units[path.depth + 1], &temp.units[fixed_cnt]));
	})) {
		if (work_state->count < MAX_STATE) {
			work_path_t &path = work_state->paths[work_state->count++];
			path.depth = temp.depth;
			std::copy(&temp.units[fixed_cnt], &temp.units[temp.depth + 1], &path.units[fixed_cnt]);
		}
		else {
			assert(0 && "too many state!");
		}
	}
}

// 递归计算基本和型上听数
// 参数说明：
//   cnt_table牌表
//   has_pair是否有雀头
//   pack_cnt完成的面子数
//   incomplete_cnt搭子数
// 最后三个参数为优化性能用的，
// work_path保存当前正在计算的路径，
// work_state保存了所有已经计算过的路径，
// 从0到fixed_cnt的数据是不使用的，这些保留给了副露的面子
static int basic_form_shanten_recursively(tile_table_t &cnt_table, const bool has_pair, const unsigned pack_cnt, const unsigned incomplete_cnt,
	const intptr_t fixed_cnt, work_path_t *work_path, work_state_t *work_state) {
	if (fixed_cnt == 4) {  // 4副露
		for (int i = 0; i < 34; ++i) {
			tile_t t = all_tiles[i];
			if (cnt_table[t] > 1) {
				return -1;
			}
		}
		return 0;
	}

	if (pack_cnt == 4) {  // 已经有4组面子
		return has_pair ? -1 : 0;  // 如果有雀头，则和了；如果无雀头，则是听牌
	}

	int max_ret;  // 当前状态能返回的最大上听数

	// 算法说明：
	// 缺少的面子数=4-完成的面子数
	// 缺少的搭子数=缺少的面子数-已有的搭子数
	// 两式合并：缺少的搭子数=4-完成的面子数-已有的搭子数
	int incomplete_need = 4 - pack_cnt - incomplete_cnt;
	if (incomplete_need > 0) {  // 还需要搭子的情况
		// 有雀头时，上听数=已有的搭子数+缺少的搭子数*2-1
		// 无雀头时，上听数=已有的搭子数+缺少的搭子数*2
		max_ret = incomplete_cnt + incomplete_need * 2 - (has_pair ? 1 : 0);
	}
	else {  // 搭子齐了的情况
		// 有雀头时，上听数=3-完成的面子数
		// 无雀头时，上听数=4-完成的面子数
		max_ret = (has_pair ? 3 : 4) - pack_cnt;
	}

	// 当前路径深度
	const unsigned depth = pack_cnt + incomplete_cnt + has_pair;
	work_path->depth = static_cast<uint16_t>(depth);

	int result = max_ret;

	if (pack_cnt + incomplete_cnt > 4) {  // 搭子超载
		save_work_path(fixed_cnt, work_path, work_state);
		return max_ret;
	}

	for (int i = 0; i < 34; ++i) {
		tile_t t = all_tiles[i];
		if (cnt_table[t] < 1) {
			continue;
		}

		// 雀头
		if (!has_pair && cnt_table[t] > 1) {
			work_path->units[depth] = MAKE_UNIT(UNIT_TYPE_PAIR, t);  // 记录雀头
			if (!is_basic_form_branch_exist(fixed_cnt, work_path, work_state)) {
				// 削减雀头，递归
				cnt_table[t] -= 2;
				int ret = basic_form_shanten_recursively(cnt_table, true, pack_cnt, incomplete_cnt,
					fixed_cnt, work_path, work_state);
				result = std::min(ret, result);
				// 还原
				cnt_table[t] += 2;
			}
		}

		// 刻子
		if (cnt_table[t] > 2) {
			work_path->units[depth] = MAKE_UNIT(UNIT_TYPE_PUNG, t);  // 记录刻子
			if (!is_basic_form_branch_exist(fixed_cnt, work_path, work_state)) {
				// 削减这组刻子，递归
				cnt_table[t] -= 3;
				int ret = basic_form_shanten_recursively(cnt_table, has_pair, pack_cnt + 1, incomplete_cnt,
					fixed_cnt, work_path, work_state);
				result = std::min(ret, result);
				// 还原
				cnt_table[t] += 3;
			}
		}

		// 顺子（只能是数牌）
		bool is_numbered = is_numbered_suit(t);
		// 顺子t t+1 t+2，显然t不能是8点以上的数牌
		if (is_numbered && tile_get_rank(t) < 8 && cnt_table[t + 1] && cnt_table[t + 2]) {
			work_path->units[depth] = MAKE_UNIT(UNIT_TYPE_CHOW, t);  // 记录顺子
			if (!is_basic_form_branch_exist(fixed_cnt, work_path, work_state)) {
				// 削减这组顺子，递归
				--cnt_table[t];
				--cnt_table[t + 1];
				--cnt_table[t + 2];
				int ret = basic_form_shanten_recursively(cnt_table, has_pair, pack_cnt + 1, incomplete_cnt,
					fixed_cnt, work_path, work_state);
				result = std::min(ret, result);
				// 还原
				++cnt_table[t];
				++cnt_table[t + 1];
				++cnt_table[t + 2];
			}
		}

		// 如果已经通过削减雀头/面子降低了上听数，再按搭子计算的上听数肯定不会更少
		if (result < max_ret) {
			continue;
		}

		// 刻子搭子
		if (cnt_table[t] > 1) {
			work_path->units[depth] = MAKE_UNIT(UNIT_TYPE_INCOMPLETE_PUNG, t);  // 记录刻子搭子
			if (!is_basic_form_branch_exist(fixed_cnt, work_path, work_state)) {
				// 削减刻子搭子，递归
				cnt_table[t] -= 2;
				int ret = basic_form_shanten_recursively(cnt_table, has_pair, pack_cnt, incomplete_cnt + 1,
					fixed_cnt, work_path, work_state);
				result = std::min(ret, result);
				// 还原
				cnt_table[t] += 2;
			}
		}

		// 顺子搭子（只能是数牌）
		if (is_numbered) {
			// 两面或者边张搭子t t+1，显然t不能是9点以上的数牌
			if (tile_get_rank(t) < 9 && cnt_table[t + 1]) {  // 两面或者边张
				work_path->units[depth] = MAKE_UNIT(UNIT_TYPE_CHOW_OPEN_END, t);  // 记录两面或者边张搭子
				if (!is_basic_form_branch_exist(fixed_cnt, work_path, work_state)) {
					// 削减搭子，递归
					--cnt_table[t];
					--cnt_table[t + 1];
					int ret = basic_form_shanten_recursively(cnt_table, has_pair, pack_cnt, incomplete_cnt + 1,
						fixed_cnt, work_path, work_state);
					result = std::min(ret, result);
					// 还原
					++cnt_table[t];
					++cnt_table[t + 1];
				}
			}
			// 嵌张搭子t t+2，显然t不能是8点以上的数牌
			if (tile_get_rank(t) < 8 && cnt_table[t + 2]) {  // 嵌张
				work_path->units[depth] = MAKE_UNIT(UNIT_TYPE_CHOW_CLOSED, t);  // 记录嵌张搭子
				if (!is_basic_form_branch_exist(fixed_cnt, work_path, work_state)) {
					// 削减搭子，递归
					--cnt_table[t];
					--cnt_table[t + 2];
					int ret = basic_form_shanten_recursively(cnt_table, has_pair, pack_cnt, incomplete_cnt + 1,
						fixed_cnt, work_path, work_state);
					result = std::min(ret, result);
					// 还原
					++cnt_table[t];
					++cnt_table[t + 2];
				}
			}
		}
	}

	if (result == max_ret) {
		save_work_path(fixed_cnt, work_path, work_state);
	}

	return result;
}

// 数牌是否有搭子
static bool numbered_tile_has_neighbor(const tile_table_t &cnt_table, tile_t t) {
	rank_t r = tile_get_rank(t);
	if (r < 9) { if (cnt_table[t + 1]) return true; }
	if (r < 8) { if (cnt_table[t + 2]) return true; }
	if (r > 1) { if (cnt_table[t - 1]) return true; }
	if (r > 2) { if (cnt_table[t - 2]) return true; }
	return false;
}

// 以表格为参数计算基本和型上听数
static int basic_form_shanten_from_table(tile_table_t &cnt_table, intptr_t fixed_cnt, useful_table_t *useful_table) {
	// 计算上听数
	work_path_t work_path;
	work_state_t work_state;
	work_state.count = 0;
	int result = basic_form_shanten_recursively(cnt_table, false, static_cast<uint16_t>(fixed_cnt), 0,
		fixed_cnt, &work_path, &work_state);

	if (useful_table == nullptr) {
		return result;
	}

	// 穷举所有的牌，获取能减少上听数的牌
	for (int i = 0; i < 34; ++i) {
		tile_t t = all_tiles[i];
		if (cnt_table[t] == 4 && result > 0) {
			continue;
		}

		if (cnt_table[t] == 0) {
			// 跳过孤张字牌和不靠张的数牌，这些牌都无法减少上听数
			if (is_honor(t) || !numbered_tile_has_neighbor(cnt_table, t)) {
				continue;
			}
		}

		++cnt_table[t];
		work_state.count = 0;
		int temp = basic_form_shanten_recursively(cnt_table, false, static_cast<uint16_t>(fixed_cnt), 0,
			fixed_cnt, &work_path, &work_state);
		if (temp < result) {
			(*useful_table)[t] = true;  // 标记为有效牌
		}
		--cnt_table[t];
	}

	return result;
}

// 基本和型上听数
int basic_form_shanten(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *useful_table) {
	if (standing_tiles == nullptr || (standing_cnt != 13
		&& standing_cnt != 10 && standing_cnt != 7 && standing_cnt != 4 && standing_cnt != 1)) {
		return std::numeric_limits<int>::max();
	}

	// 对立牌的种类进行打表
	tile_table_t cnt_table;
	map_tiles(standing_tiles, standing_cnt, &cnt_table);

	if (useful_table != nullptr) {
		memset(*useful_table, 0, sizeof(*useful_table));
	}
	return basic_form_shanten_from_table(cnt_table, (13 - standing_cnt) / 3, useful_table);
}

// 基本和型判断1张是否听牌
static bool is_basic_form_wait_1(tile_table_t &cnt_table, useful_table_t *waiting_table) {
	for (int i = 0; i < 34; ++i) {
		tile_t t = all_tiles[i];
		if (cnt_table[t] != 1) {
			continue;
		}

		// 单钓将
		cnt_table[t] = 0;
		if (std::all_of(std::begin(cnt_table), std::end(cnt_table), [](int n) { return n == 0; })) {
			cnt_table[t] = 1;
			if (waiting_table != nullptr) {  // 不需要获取听牌张，则可以直接返回
				(*waiting_table)[t] = true;
			}
			return true;
		}
		cnt_table[t] = 1;
	}

	return false;
}

// 基本和型判断2张是否听牌
static bool is_basic_form_wait_2(const tile_table_t &cnt_table, useful_table_t *waiting_table) {
	bool ret = false;
	for (int i = 0; i < 34; ++i) {
		tile_t t = all_tiles[i];
		if (cnt_table[t] < 1) {
			continue;
		}
		if (cnt_table[t] > 1) {
			if (waiting_table != nullptr) {  // 获取听牌张
				(*waiting_table)[t] = true;  // 对倒
				ret = true;
				continue;
			}
			else {  // 不需要获取听牌张，则可以直接返回
				return true;
			}
		}
		if (is_numbered_suit_quick(t)) {  // 数牌搭子
			rank_t r = tile_get_rank(t);
			if (r > 1 && cnt_table[t - 1]) {  // 两面或者边张
				if (waiting_table != nullptr) {  // 获取听牌张
					if (r < 9) (*waiting_table)[t + 1] = true;
					if (r > 2) (*waiting_table)[t - 2] = true;
					ret = true;
					continue;
				}
				else {  // 不需要获取听牌张，则可以直接返回
					return true;
				}
			}
			if (r > 2 && cnt_table[t - 2]) {  // 嵌张
				if (waiting_table != nullptr) {  // 获取听牌张
					(*waiting_table)[t - 1] = true;
					ret = true;
					continue;
				}
				else {  // 不需要获取听牌张，则可以直接返回
					return true;
				}
			}
		}
	}
	return ret;
}

// 基本和型判断4张是否听牌
static bool is_basic_form_wait_4(tile_table_t &cnt_table, useful_table_t *waiting_table) {
	bool ret = false;
	// 削减雀头
	for (int i = 0; i < 34; ++i) {
		tile_t t = all_tiles[i];
		if (cnt_table[t] < 2) {
			continue;
		}
		// 削减雀头，递归
		cnt_table[t] -= 2;
		if (is_basic_form_wait_2(cnt_table, waiting_table)) {
			ret = true;
		}
		// 还原
		cnt_table[t] += 2;
		if (ret && waiting_table == nullptr) {  // 不需要获取听牌张，则可以直接结束递归
			return true;
		}
	}

	return ret;
}

// 递归计算基本和型是否听牌
static bool is_basic_form_wait_recursively(tile_table_t &cnt_table, intptr_t left_cnt, useful_table_t *waiting_table) {
	if (left_cnt == 1) {
		return is_basic_form_wait_1(cnt_table, waiting_table);
	}

	bool ret = false;
	if (left_cnt == 4) {
		ret = is_basic_form_wait_4(cnt_table, waiting_table);
		if (ret && waiting_table == nullptr) {  // 不需要获取听牌张，则可以直接结束递归
			return true;
		}
	}

	for (int i = 0; i < 34; ++i) {
		tile_t t = all_tiles[i];
		if (cnt_table[t] < 1) {
			continue;
		}

		// 刻子
		if (cnt_table[t] > 2) {
			// 削减这组刻子，递归
			cnt_table[t] -= 3;
			if (is_basic_form_wait_recursively(cnt_table, left_cnt - 3, waiting_table)) {
				ret = true;
			}
			// 还原
			cnt_table[t] += 3;
			if (ret && waiting_table == nullptr) {  // 不需要获取听牌张，则可以直接结束递归
				return true;
			}
		}

		// 顺子（只能是数牌）
		if (is_numbered_suit(t)) {
			// 顺子t t+1 t+2，显然t不能是8点以上的数牌
			if (tile_get_rank(t) < 8 && cnt_table[t + 1] && cnt_table[t + 2]) {
				// 削减这组顺子，递归
				--cnt_table[t];
				--cnt_table[t + 1];
				--cnt_table[t + 2];
				if (is_basic_form_wait_recursively(cnt_table, left_cnt - 3, waiting_table)) {
					ret = true;
				}
				// 还原
				++cnt_table[t];
				++cnt_table[t + 1];
				++cnt_table[t + 2];
				if (ret && waiting_table == nullptr) {  // 不需要获取听牌张，则可以直接结束递归
					return true;
				}
			}
		}
	}

	return ret;
}

// 基本和型是否听牌
// 这里之所以不用直接调用上听数计算函数，判断其返回值为0的方式
// 是因为前者会削减搭子，这个操作在和牌判断中是没必要的，所以单独写一套更快逻辑
bool is_basic_form_wait(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *waiting_table) {
	// 对立牌的种类进行打表
	tile_table_t cnt_table;
	map_tiles(standing_tiles, standing_cnt, &cnt_table);

	if (waiting_table != nullptr) {
		memset(*waiting_table, 0, sizeof(*waiting_table));
	}
	return is_basic_form_wait_recursively(cnt_table, standing_cnt, waiting_table);
}

// 基本和型2张能否和牌
static bool is_basic_form_win_2(const tile_table_t &cnt_table) {
	// 找到未使用的牌
	typedef std::remove_all_extents<tile_table_t>::type table_elem_t;
	const table_elem_t *it = std::find_if(std::begin(cnt_table), std::end(cnt_table), [](table_elem_t n) { return n > 0; });
	// 存在且张数等于2
	if (it == std::end(cnt_table) || *it != 2) {
		return false;
	}
	// 还有其他未使用的牌
	return std::none_of(it + 1, std::end(cnt_table), [](int n) { return n > 0; });
}

// 递归计算基本和型是否和牌
// 这里之所以不用直接调用上听数计算函数，判断其返回值为-1的方式，
// 是因为前者会削减搭子，这个操作在和牌判断中是没必要的，所以单独写一套更快逻辑
static bool is_basic_form_win_recursively(tile_table_t &cnt_table, intptr_t left_cnt) {
	if (left_cnt == 2) {
		return is_basic_form_win_2(cnt_table);
	}

	for (int i = 0; i < 34; ++i) {
		tile_t t = all_tiles[i];
		if (cnt_table[t] < 1) {
			continue;
		}

		// 刻子
		if (cnt_table[t] > 2) {
			// 削减这组刻子，递归
			cnt_table[t] -= 3;
			bool ret = is_basic_form_win_recursively(cnt_table, left_cnt - 3);
			// 还原
			cnt_table[t] += 3;
			if (ret) {
				return true;
			}
		}

		// 顺子（只能是数牌）
		if (is_numbered_suit(t)) {
			// 顺子t t+1 t+2，显然t不能是8点以上的数牌
			if (tile_get_rank(t) < 8 && cnt_table[t + 1] && cnt_table[t + 2]) {
				// 削减这组顺子，递归
				--cnt_table[t];
				--cnt_table[t + 1];
				--cnt_table[t + 2];
				bool ret = is_basic_form_win_recursively(cnt_table, left_cnt - 3);
				// 还原
				++cnt_table[t];
				++cnt_table[t + 1];
				++cnt_table[t + 2];
				if (ret) {
					return true;
				}
			}
		}
	}

	return false;
}

// 基本和型是否和牌
bool is_basic_form_win(const tile_t *standing_tiles, intptr_t standing_cnt, tile_t test_tile) {
	// 对立牌的种类进行打表
	tile_table_t cnt_table;
	map_tiles(standing_tiles, standing_cnt, &cnt_table);
	++cnt_table[test_tile];  // 添加测试的牌
	return is_basic_form_win_recursively(cnt_table, standing_cnt + 1);
}

//-------------------------------- 七对 --------------------------------

// 七对上听数
int seven_pairs_shanten(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *useful_table) {
	if (standing_tiles == nullptr || standing_cnt != 13) {
		return std::numeric_limits<int>::max();
	}

	// 对牌的种类进行打表，并统计对子数
	int pair_cnt = 0;
	tile_table_t cnt_table = { 0 };
	for (intptr_t i = 0; i < standing_cnt; ++i) {
		tile_t tile = standing_tiles[i];
		++cnt_table[tile];
		if (cnt_table[tile] == 2) {
			++pair_cnt;
			cnt_table[tile] = 0;
		}
	}

	// 有效牌
	if (useful_table != nullptr) {
		std::transform(std::begin(cnt_table), std::end(cnt_table), std::begin(*useful_table), [](int n) { return n != 0; });
	}
	return 6 - pair_cnt;
}

// 七对是否听牌
bool is_seven_pairs_wait(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *waiting_table) {
	// 直接计算其上听数，上听数为0即为听牌
	if (waiting_table == nullptr) {
		return (0 == seven_pairs_shanten(standing_tiles, standing_cnt, nullptr));
	}

	useful_table_t useful_table;
	if (0 == seven_pairs_shanten(standing_tiles, standing_cnt, &useful_table)) {
		memcpy(*waiting_table, useful_table, sizeof(*waiting_table));
		return true;
	}
	return false;
}

// 七对是否和牌
bool is_seven_pairs_win(const tile_t *standing_tiles, intptr_t standing_cnt, tile_t test_tile) {
	useful_table_t useful_table;
	return (0 == seven_pairs_shanten(standing_tiles, standing_cnt, &useful_table)
		&& useful_table[test_tile]);
}

//-------------------------------- 十三幺 --------------------------------

// 十三幺上听数
int thirteen_orphans_shanten(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *useful_table) {
	if (standing_tiles == nullptr || standing_cnt != 13) {
		return std::numeric_limits<int>::max();
	}

	// 对牌的种类进行打表
	tile_table_t cnt_table;
	map_tiles(standing_tiles, standing_cnt, &cnt_table);

	bool has_pair = false;
	int cnt = 0;
	for (int i = 0; i < 13; ++i) {
		int n = cnt_table[standard_thirteen_orphans[i]];
		if (n > 0) {
			++cnt;  // 幺九牌的种类
			if (n > 1) {
				has_pair = true;  // 幺九牌对子
			}
		}
	}

	// 当有对子时，上听数为：12-幺九牌的种类
	// 当没有对子时，上听数为：13-幺九牌的种类
	int ret = has_pair ? 12 - cnt : 13 - cnt;

	if (useful_table != nullptr) {
		// 先标记所有的幺九牌为有效牌
		memset(*useful_table, 0, sizeof(*useful_table));
		std::for_each(std::begin(standard_thirteen_orphans), std::end(standard_thirteen_orphans),
			[useful_table](tile_t t) {
			(*useful_table)[t] = true;
		});

		// 当有对子时，已有的幺九牌都不需要了
		if (has_pair) {
			for (int i = 0; i < 13; ++i) {
				tile_t t = standard_thirteen_orphans[i];
				int n = cnt_table[t];
				if (n > 0) {
					(*useful_table)[t] = false;
				}
			}
		}
	}

	return ret;
}

// 十三幺是否听牌
bool is_thirteen_orphans_wait(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *waiting_table) {
	// 直接计算其上听数，上听数为0即为听牌
	if (waiting_table == nullptr) {
		return (0 == thirteen_orphans_shanten(standing_tiles, standing_cnt, nullptr));
	}

	useful_table_t useful_table;
	if (0 == thirteen_orphans_shanten(standing_tiles, standing_cnt, &useful_table)) {
		memcpy(*waiting_table, useful_table, sizeof(*waiting_table));
		return true;
	}
	return false;
}

// 十三幺是否和牌
bool is_thirteen_orphans_win(const tile_t *standing_tiles, intptr_t standing_cnt, tile_t test_tile) {
	useful_table_t useful_table;
	return (0 == thirteen_orphans_shanten(standing_tiles, standing_cnt, &useful_table)
		&& useful_table[test_tile]);
}

//-------------------------------- “组合龙+面子+雀头”和型 --------------------------------

// 以表格为参数计算组合龙是否听牌
static bool is_knitted_straight_wait_from_table(const tile_table_t &cnt_table, intptr_t left_cnt, useful_table_t *waiting_table) {
	// 匹配组合龙
	const tile_t (*matched_seq)[9] = nullptr;
	tile_t missing_tiles[9];
	int missing_cnt = 0;
	for (int i = 0; i < 6; ++i) {  // 逐个组合龙测试
		missing_cnt = 0;
		for (int k = 0; k < 9; ++k) {
			tile_t t = standard_knitted_straight[i][k];
			if (cnt_table[t] == 0) {  // 缺失的
				missing_tiles[missing_cnt++] = t;
			}
		}
		if (missing_cnt < 2) {  // 缺2张或以上的肯定没听
			matched_seq = &standard_knitted_straight[i];
			break;
		}
	}

	if (matched_seq == nullptr || missing_cnt > 2) {
		return false;
	}

	if (waiting_table != nullptr) {
		memset(*waiting_table, 0, sizeof(*waiting_table));
	}

	// 剔除组合龙
	tile_table_t temp_table;
	memcpy(&temp_table, &cnt_table, sizeof(temp_table));
	for (int i = 0; i < 9; ++i) {
		tile_t t = (*matched_seq)[i];
		if (temp_table[t]) {
			--temp_table[t];
		}
	}

	if (missing_cnt == 1) {  // 如果缺一张，那么除去组合龙之后的牌应该是完成状态才能听牌
		if (left_cnt == 10) {
			if (is_basic_form_win_recursively(temp_table, 2)) {
				if (waiting_table != nullptr) {  // 获取听牌张，听组合龙缺的一张
					(*waiting_table)[missing_tiles[0]] = true;
				}
				return true;
			}
		}
		else {
			if (is_basic_form_win_recursively(temp_table, 5)) {
				if (waiting_table != nullptr) {  // 获取听牌张，听组合龙缺的一张
					(*waiting_table)[missing_tiles[0]] = true;
				}
				return true;
			}
		}
	}
	else if (missing_cnt == 0) {  // 如果组合龙齐了，那么除去组合龙之后的牌要能听，整手牌才能听
		if (left_cnt == 10) {
			return is_basic_form_wait_1(temp_table, waiting_table);
		}
		else {
			return is_basic_form_wait_recursively(temp_table, 4, waiting_table);
		}
	}

	return false;
}

// 基本和型包含主番的上听数，可用于计算三步高 三同顺 龙等三组面子的番种整个立牌的上听数
static int basic_form_shanten_specified(const tile_table_t &cnt_table, const tile_t *main_tiles, int main_cnt,
	intptr_t fixed_cnt, useful_table_t *useful_table) {

	tile_table_t temp_table;
	memcpy(&temp_table, &cnt_table, sizeof(temp_table));
	int exist_cnt = 0;

	// 统计主番的牌
	for (int i = 0; i < main_cnt; ++i) {
		tile_t t = main_tiles[i];
		int n = cnt_table[t];
		if (n > 0) {  // 有，削减之
			++exist_cnt;
			--temp_table[t];
		}
	}

	// 记录有效牌
	if (useful_table != nullptr) {
		memset(*useful_table, 0, sizeof(*useful_table));

		// 统计主番缺失的牌
		for (int i = 0; i < main_cnt; ++i) {
			tile_t t = main_tiles[i];
			int n = cnt_table[t];
			if (n <= 0) {
				(*useful_table)[t] = true;
			}
		}
	}

	// 余下牌的上听数
	int result = basic_form_shanten_from_table(temp_table, fixed_cnt + main_cnt / 3, useful_table);

	// 上听数=主番缺少的张数+余下牌的上听数
	return (main_cnt - exist_cnt) + result;
}

// 组合龙上听数
int knitted_straight_shanten(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *useful_table) {
	if (standing_tiles == nullptr || (standing_cnt != 13 && standing_cnt != 10)) {
		return std::numeric_limits<int>::max();
	}

	// 打表
	tile_table_t cnt_table;
	map_tiles(standing_tiles, standing_cnt, &cnt_table);

	int ret = std::numeric_limits<int>::max();

	// 需要获取有效牌时，计算上听数的同时就获取有效牌了
	if (useful_table != nullptr) {
		memset(*useful_table, 0, sizeof(*useful_table));

		useful_table_t temp_table;

		// 6种组合龙分别计算
		for (int i = 0; i < 6; ++i) {
			int fixed_cnt = (13 - static_cast<int>(standing_cnt)) / 3;
			int st = basic_form_shanten_specified(cnt_table, standard_knitted_straight[i], 9, fixed_cnt, &temp_table);
			if (st < ret) {  // 上听数小的，直接覆盖数据
				ret = st;
				memcpy(*useful_table, temp_table, sizeof(*useful_table));  // 直接覆盖原来的有效牌数据
			}
			else if (st == ret) {  // 两种不同组合龙上听数如果相等的话，直接合并有效牌
				std::transform(std::begin(*useful_table), std::end(*useful_table), std::begin(temp_table),
					std::begin(*useful_table), [](bool u, bool t) { return u || t; });
			}
		}
	}
	else {
		// 6种组合龙分别计算
		for (int i = 0; i < 6; ++i) {
			int fixed_cnt = (13 - static_cast<int>(standing_cnt)) / 3;
			int st = basic_form_shanten_specified(cnt_table, standard_knitted_straight[i], 9, fixed_cnt, nullptr);
			if (st < ret) {
				ret = st;
			}
		}
	}

	return ret;
}

// 组合龙是否听牌
bool is_knitted_straight_wait(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *waiting_table) {
	if (standing_tiles == nullptr || (standing_cnt != 13 && standing_cnt != 10)) {
		return false;
	}

	// 对立牌的种类进行打表
	tile_table_t cnt_table;
	map_tiles(standing_tiles, standing_cnt, &cnt_table);

	return is_knitted_straight_wait_from_table(cnt_table, standing_cnt, waiting_table);
}

// 组合龙是否和牌
bool is_knitted_straight_win(const tile_t *standing_tiles, intptr_t standing_cnt, tile_t test_tile) {
	useful_table_t waiting_table;
	return (is_knitted_straight_wait(standing_tiles, standing_cnt, &waiting_table)
		&& waiting_table[test_tile]);
}

//-------------------------------- 全不靠/七星不靠 --------------------------------

// 1种组合龙的全不靠上听数
static int honors_and_knitted_tiles_shanten_1(const tile_t *standing_tiles, intptr_t standing_cnt, int which_seq, useful_table_t *useful_table) {
	if (standing_tiles == nullptr || standing_cnt != 13) {
		return std::numeric_limits<int>::max();
	}

	// 对牌的种类进行打表
	tile_table_t cnt_table;
	map_tiles(standing_tiles, standing_cnt, &cnt_table);

	int cnt = 0;

	// 统计组合龙部分的数牌
	for (int i = 0; i < 9; ++i) {
		tile_t t = standard_knitted_straight[which_seq][i];
		int n = cnt_table[t];
		if (n > 0) {  // 有，增加计数
			++cnt;
		}
	}

	// 统计字牌
	for (int i = 6; i < 13; ++i) {
		tile_t t = standard_thirteen_orphans[i];
		int n = cnt_table[t];
		if (n > 0) {  // 有，增加计数
			++cnt;
		}
	}

	// 记录有效牌
	if (useful_table != nullptr) {
		memset(*useful_table, 0, sizeof(*useful_table));

		// 统计组合龙部分缺失的数牌
		for (int i = 0; i < 9; ++i) {
			tile_t t = standard_knitted_straight[which_seq][i];
			int n = cnt_table[t];
			if (n <= 0) {
				(*useful_table)[t] = true;
			}
		}

		// 统计缺失的字牌
		for (int i = 6; i < 13; ++i) {
			tile_t t = standard_thirteen_orphans[i];
			int n = cnt_table[t];
			if (n <= 0) {
				(*useful_table)[t] = true;
			}
		}
	}

	// 上听数=13-符合牌型的计数
	return 13 - cnt;
}

// 全不靠上听数
int honors_and_knitted_tiles_shanten(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *useful_table) {
	int ret = std::numeric_limits<int>::max();

	// 需要获取有效牌时，计算上听数的同时就获取有效牌了
	if (useful_table != nullptr) {
		memset(*useful_table, 0, sizeof(*useful_table));

		useful_table_t temp_table;

		// 6种组合龙分别计算
		for (int i = 0; i < 6; ++i) {
			int st = honors_and_knitted_tiles_shanten_1(standing_tiles, standing_cnt, i, &temp_table);
			if (st < ret) {  // 上听数小的，直接覆盖数据
				ret = st;
				memcpy(*useful_table, temp_table, sizeof(*useful_table));  // 直接覆盖原来的有效牌数据
			}
			else if (st == ret) {  // 两种不同组合龙上听数如果相等的话，直接合并有效牌
				std::transform(std::begin(*useful_table), std::end(*useful_table), std::begin(temp_table),
					std::begin(*useful_table), [](bool u, bool t) { return u || t; });
			}
		}
	}
	else {
		// 6种组合龙分别计算
		for (int i = 0; i < 6; ++i) {
			int st = honors_and_knitted_tiles_shanten_1(standing_tiles, standing_cnt, i, nullptr);
			if (st < ret) {
				ret = st;
			}
		}
	}
	return ret;
}

// 全不靠是否听牌
bool is_honors_and_knitted_tiles_wait(const tile_t *standing_tiles, intptr_t standing_cnt, useful_table_t *waiting_table) {
	// 直接计算其上听数，上听数为0即为听牌
	if (waiting_table == nullptr) {
		return (0 == honors_and_knitted_tiles_shanten(standing_tiles, standing_cnt, nullptr));
	}

	useful_table_t useful_table;
	if (0 == honors_and_knitted_tiles_shanten(standing_tiles, standing_cnt, &useful_table)) {
		memcpy(*waiting_table, useful_table, sizeof(*waiting_table));
		return true;
	}
	return false;
}

// 全不靠是否和牌
bool is_honors_and_knitted_tiles_win(const tile_t *standing_tiles, intptr_t standing_cnt, tile_t test_tile) {
	useful_table_t useful_table;
	if (0 == honors_and_knitted_tiles_shanten(standing_tiles, standing_cnt, &useful_table)) {
		return useful_table[test_tile];
	}
	return false;
}

//-------------------------------- 所有情况综合 --------------------------------

bool is_waiting(const hand_tiles_t &hand_tiles, useful_table_t *useful_table) {
	bool spcial_waiting = false, basic_waiting = false;
	useful_table_t table_special, table_basic;

	if (hand_tiles.tile_count == 13) {
		if (is_thirteen_orphans_wait(hand_tiles.standing_tiles, 13, &table_special)) {
			spcial_waiting = true;
		}
		else if (is_honors_and_knitted_tiles_wait(hand_tiles.standing_tiles, 13, &table_special)) {
			spcial_waiting = true;
		}
		else if (is_seven_pairs_wait(hand_tiles.standing_tiles, 13, &table_special)) {
			spcial_waiting = true;
		}
		else if (is_knitted_straight_wait(hand_tiles.standing_tiles, 13, &table_special)) {
			spcial_waiting = true;
		}
	}
	else if (hand_tiles.tile_count == 10) {
		if (is_knitted_straight_wait(hand_tiles.standing_tiles, 10, &table_special)) {
			spcial_waiting = true;
		}
	}

	if (is_basic_form_wait(hand_tiles.standing_tiles, hand_tiles.tile_count, &table_basic)) {
		basic_waiting = true;
	}

	if (useful_table != nullptr) {
		if (spcial_waiting && basic_waiting) {
			std::transform(std::begin(table_special), std::end(table_special), std::begin(table_basic), std::begin(*useful_table),
				[](bool a, bool b) { return a || b; });
		}
		else if (basic_waiting) {
			memcpy(*useful_table, table_basic, sizeof(table_basic));
		}
		else if (spcial_waiting) {
			memcpy(*useful_table, table_special, sizeof(table_special));
		}
	}

	return (spcial_waiting || basic_waiting);
}

//-------------------------------- 枚举打牌 --------------------------------

// 枚举打哪张牌1次
static bool enum_discard_tile_1(const hand_tiles_t *hand_tiles, tile_t discard_tile, uint8_t form_flag,
	void *context, enum_callback_t enum_callback) {
	enum_result_t result;
	result.discard_tile = discard_tile;
	result.form_flag = FORM_FLAG_BASIC_FORM;
	result.shanten = basic_form_shanten(hand_tiles->standing_tiles, hand_tiles->tile_count, &result.useful_table);
	if (result.shanten == 0 && result.useful_table[discard_tile]) {  // 0上听，并且打出的牌是有效牌，则修正为和了
		result.shanten = -1;
	}
	if (!enum_callback(context, &result)) {
		return false;
	}

	// 立牌有13张时，才需要计算特殊和型
	if (hand_tiles->tile_count == 13) {
		if (form_flag | FORM_FLAG_SEVEN_PAIRS) {
			result.form_flag = FORM_FLAG_SEVEN_PAIRS;
			result.shanten = seven_pairs_shanten(hand_tiles->standing_tiles, hand_tiles->tile_count, &result.useful_table);
			if (result.shanten == 0 && result.useful_table[discard_tile]) {  // 0上听，并且打出的牌是有效牌，则修正为和了
				result.shanten = -1;
			}
			if (!enum_callback(context, &result)) {
				return false;
			}
		}

		if (form_flag | FORM_FLAG_THIRTEEN_ORPHANS) {
			result.form_flag = FORM_FLAG_THIRTEEN_ORPHANS;
			result.shanten = thirteen_orphans_shanten(hand_tiles->standing_tiles, hand_tiles->tile_count, &result.useful_table);
			if (result.shanten == 0 && result.useful_table[discard_tile]) {  // 0上听，并且打出的牌是有效牌，则修正为和了
				result.shanten = -1;
			}
			if (!enum_callback(context, &result)) {
				return false;
			}
		}

		if (form_flag | FORM_FLAG_HONORS_AND_KNITTED_TILES) {
			result.form_flag = FORM_FLAG_HONORS_AND_KNITTED_TILES;
			result.shanten = honors_and_knitted_tiles_shanten(hand_tiles->standing_tiles, hand_tiles->tile_count, &result.useful_table);
			if (result.shanten == 0 && result.useful_table[discard_tile]) {  // 0上听，并且打出的牌是有效牌，则修正为和了
				result.shanten = -1;
			}
			if (!enum_callback(context, &result)) {
				return false;
			}
		}
	}

	// 立牌有13张或者10张时，才需要计算组合龙
	if (hand_tiles->tile_count == 13 || hand_tiles->tile_count == 10) {
		if (form_flag | FORM_FLAG_KNITTED_STRAIGHT) {
			result.form_flag = FORM_FLAG_KNITTED_STRAIGHT;
			result.shanten = knitted_straight_shanten(hand_tiles->standing_tiles, hand_tiles->tile_count, &result.useful_table);
			if (result.shanten == 0 && result.useful_table[discard_tile]) {  // 0上听，并且打出的牌是有效牌，则修正为和了
				result.shanten = -1;
			}
			if (!enum_callback(context, &result)) {
				return false;
			}
		}
	}

	return true;
}

// 枚举打哪张牌
void enum_discard_tile(const hand_tiles_t *hand_tiles, tile_t serving_tile, uint8_t form_flag,
	void *context, enum_callback_t enum_callback) {
	// 先计算摸切的
	if (!enum_discard_tile_1(hand_tiles, serving_tile, form_flag, context, enum_callback)) {
		return;
	}

	if (serving_tile == 0) {
		return;
	}

	// 将立牌打表
	tile_table_t cnt_table;
	map_tiles(hand_tiles->standing_tiles, hand_tiles->tile_count, &cnt_table);

	// 复制一份手牌
	hand_tiles_t temp;
	memcpy(&temp, hand_tiles, sizeof(temp));

	// 依次尝试打手中的立牌
	for (int i = 0; i < 34; ++i) {
		tile_t t = all_tiles[i];
		if (cnt_table[t] && t != serving_tile && cnt_table[serving_tile] < 4) {
			--cnt_table[t];  // 打这张牌
			++cnt_table[serving_tile];  // 上这张牌

			// 从table转成立牌
			table_to_tiles(cnt_table, temp.standing_tiles, temp.tile_count);

			// 计算
			if (!enum_discard_tile_1(&temp, t, form_flag, context, enum_callback)) {
				return;
			}

			// 复原
			--cnt_table[serving_tile];
			++cnt_table[t];
		}
	}
}

}

/*** End of inlined file: shanten.cpp ***/

//Dangerous

using namespace std;

void MahjongInit();

vector<pair<int, string> > MahjongFanCalculator(
	vector<pair<string, pair<string, int> > > pack,
	vector<string> hand,
	string winTile,
	int flowerCount,
	bool isZIMO,
	bool isJUEZHANG,
	bool isGANG,
	bool isLAST,
	int menFeng,
	int quanFeng);

#endif

/*** End of inlined file: MahjongGB.h ***/


#endif

using namespace std;

//手牌得分用于出牌时的决策，通过比较出掉某一张牌后剩余13张牌的得分，可得到最优的出牌
//只考虑了自己怎么能赢，而没考虑与对手的博弈，这是一版极其自闭的评估函数。

//如何使用(仅供参考)：
//1.出牌时通过比较出掉某一张牌后剩余13张牌的得分与风险系数的乘积(用于评估对手对该牌的需要程度),得到最优出牌
//2.决策杠、吃、碰时通过比较操作前后得分的变化决定是否进行该操作.

class Calculator{
public:
	//返回一副牌的得分(番数得分和手牌得分的加权和)
	static double MajangScoreCalculator(
		vector<pair<string, Majang> > pack,
		//pack:玩家的明牌，每组第一个string为"PENG" "GANG" "CHI" 三者之一，第二个为牌（吃牌表示中间牌）
		vector<Majang> hand,
		//hand:玩家的暗牌
		int flowerCount,
		//flowerCount:补花数
		StateContainer state
		//StateContainer:牌库状态
	);

	//利用算番器计算番数得分
	static double FanScoreCalculator(
		vector<pair<string, Majang> > pack,
		vector<Majang> hand,
		int flowerCount,
		Majang winTile,
		StateContainer state
	);

	//一副牌的番数得分
	static double MajangFanScore(
		vector<pair<string, Majang> > pack,
		vector<Majang> hand,
		int flowerCount,
		StateContainer state,
		int depth //迭代深度
	);

	//一副牌的手牌得分(赋予顺子、刻子、杠、碰、吃相应的得分)
	static double MajangHandScore(
		vector<pair<string, Majang> > pack,
		vector<Majang> hand
	);

	static double HandScoreCalculator(
		int TileAmount[70]
	);
};

#endif
/*** End of inlined file: ScoreCalculator.h ***/


/*** Start of inlined file: ScoreCalculator.cpp ***/

/*** Start of inlined file: ScoreCalculator.h ***/
#ifndef _BOTZONE_ONLINE
#pragma once
#endif

#ifndef SCORECALCULATOR_H
#define SCORECALCULATOR_H

#include <string>
#include <cstring>
#include <vector>
#include <utility>


/*** Start of inlined file: Majang.h ***/
#ifndef _BOTZONE_ONLINE
#pragma once
#endif

#ifndef MAJANG_H
#define MAJANG_H

#include <string>
//#include <string_view>

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
	TILE_T_SIZE  // 以便循环使用
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
	bool operator == (const Majang& other);

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
/*** End of inlined file: Majang.h ***/


/*** Start of inlined file: StateContainer.h ***/
#ifndef _BOTZONE_ONLINE
#pragma once
#endif

#ifndef STATECONTAINER_H
#define STATECONTAINER_H

#include <valarray>
#include <vector>
#include <algorithm>

// 使用Majang类

/*** Start of inlined file: Majang.h ***/
#ifndef _BOTZONE_ONLINE
#pragma once
#endif

#ifndef MAJANG_H
#define MAJANG_H

#include <string>
//#include <string_view>

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
	TILE_T_SIZE  // 以便循环使用
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
	bool operator == (const Majang& other);

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
/*** End of inlined file: Majang.h ***/


using namespace std;

//typedef pair<char, int> Majang; // 所有麻将牌均以“大写字母+数字”组合表示

// 从题目的输入request的0~9可知，在输入环节我们可以得到的信息有：
// 0. 我们的位置、当前的风圈
// 1. 我们的起始手牌、四名玩家各人的花牌
// 2. 当前是哪个玩家的回合（可以通过各个摸牌操作来判断）
// 3. 各个玩家的鸣牌（可以通过吃碰杠来获得）
// 4. "弃牌堆"中的牌（被打出之后没有被吃碰杠、点炮的牌）

// 用于存放当前的局面
// 由于该部分很多函数很简单，就不费笔墨写注释了，也没有将实现分离到cpp中
class StateContainer {
private:
	int curPosition;                    // “我们”所处的位置，0是庄家。同样也可以在博弈树节点使用以判断敌我
	int curTurnPlayer;                  // 当前是哪个玩家的回合
//    valarray<Majang> inHand;           // 用于存储手牌
//    valarray<Majang> flowerTilesOf[4]; // 用于存储花牌，分别对应4个玩家
//    valarray<Majang> chiOf[4];         // 某个玩家鸣牌中的所有“吃”,存放中间那张牌即可
//    valarray<Majang> pengOf[4];        // 某个玩家鸣牌中的所有“碰”，存放其中一张即可（因为三张一模一样
//    valarray<Majang> gangOf[4];        // 某个玩家鸣牌中的所有“杠”，存放其中一张即可
////    valarray<Majang> discards;       // 用于存放弃牌堆
//    valarray<Majang> tilePlayedOf[4];  // 用于记录某个玩家曾经都打出过哪些卡牌，无论是否被吃、碰还是杠
	vector<Majang> inHand;           // 用于存储手牌
	vector<Majang> flowerTilesOf[4]; // 用于存储花牌，分别对应4个玩家
	vector<Majang> chiOf[4];         // 某个玩家鸣牌中的所有“吃”,存放中间那张牌即可
	vector<Majang> pengOf[4];        // 某个玩家鸣牌中的所有“碰”，存放其中一张即可（因为三张一模一样
	vector<Majang> gangOf[4];        // 某个玩家鸣牌中的所有“杠”，存放其中一张即可
//    valarray<Majang> discards;       // 用于存放弃牌堆
	vector<Majang> tilePlayedOf[4];  // 用于记录某个玩家曾经都打出过哪些卡牌，无论是否被吃、碰还是杠
	int secretGangCntOf[4];           // 用于记录"暗杠"的数量，通过输入数据我们可以判断出某名玩家有几个暗杠，但我们不知道暗杠的是什么
	// 下面这个lastPlayed还没确定好到底怎么用，想好的时候再改吧
	Majang lastPlayed;                 // 用于记录上个回合被打出的麻将牌，如果不是麻将牌类型的话则为其他操作（具体见RequestReader::readRequest
	int tileLeft[70];                   // 用于记录各种类型牌所剩余的没出现的数量
	int totalLeft;                      // 没出现过的牌的总数（初始144）
	int inHandCnt[4];                   // 用于记录四名玩家的手牌数量(虽然不知道有没有用)

public:
	static int quan;                    // 圈风。因为在一把botzone游戏中，只考虑国标麻将的一局游戏，所以圈风应该是不变的
	static int lastRequest;             // 上回合的操作,用于算番器的isGANG,采取博弈算法时应换一种存储方式

	explicit StateContainer(int curP=0, int curT=0);
	StateContainer(const StateContainer& other);

//    [[nodiscard]] valarray<Majang>& getInHand();                               // 获取手牌
//    [[nodiscard]] valarray<Majang>& getFlowerTilesOf(int idx);                 // 获取花牌
//    [[nodiscard]] valarray<Majang>& getChiOf(int idx);                         // 获取鸣牌中的“吃"
//    [[nodiscard]] valarray<Majang>& getPengOf(int idx);                        // 获取鸣牌中的“碰"
//    [[nodiscard]] valarray<Majang>& getGangOf(int idx);                        // 获取鸣牌中的“杠”
////    [[nodiscard]] valarray<Majang>& getDiscards();                             // 获取弃牌堆
//    [[nodiscard]] valarray<Majang>& getTilePlayedOf(int idx);                  // 获取某名玩家打过的所有牌
//
//    [[nodiscard]] const valarray<Majang>& getInHand() const;                   //  获取手牌的常引用，下同上
//    [[nodiscard]] const valarray<Majang>& getFlowerTilesOf(int idx) const;
//    [[nodiscard]] const valarray<Majang>& getChiOf(int idx) const;
//    [[nodiscard]] const valarray<Majang>& getPengOf(int idx) const;
//    [[nodiscard]] const valarray<Majang>& getGangOf(int idx) const;
////    [[nodiscard]] const valarray<Majang>& getDiscards() const;
//    [[nodiscard]] const valarray<Majang>& getTilePlayedOf(int idx) const;

	[[nodiscard]] vector<Majang>& getInHand();                               // 获取手牌
	[[nodiscard]] vector<Majang>& getFlowerTilesOf(int idx);                 // 获取花牌
	[[nodiscard]] vector<Majang>& getChiOf(int idx);                         // 获取鸣牌中的“吃"
	[[nodiscard]] vector<Majang>& getPengOf(int idx);                        // 获取鸣牌中的“碰"
	[[nodiscard]] vector<Majang>& getGangOf(int idx);                        // 获取鸣牌中的“杠”
	[[nodiscard]] vector<Majang>& getTilePlayedOf(int idx);                  // 获取某名玩家打过的所有牌

	[[nodiscard]] const vector<Majang>& getInHand() const;                   //  获取手牌的常引用，下同上
	[[nodiscard]] const vector<Majang>& getFlowerTilesOf(int idx) const;
	[[nodiscard]] const vector<Majang>& getChiOf(int idx) const;
	[[nodiscard]] const vector<Majang>& getPengOf(int idx) const;
	[[nodiscard]] const vector<Majang>& getGangOf(int idx) const;
	[[nodiscard]] const vector<Majang>& getTilePlayedOf(int idx) const;

	void decTileLeft(int idx);                                                  // 在减少idx对应的牌的数量的同时，减少总数的数量
	void decTileLeft(Majang mj);                                               // 同上
	[[nodiscard]] const int & getTileLeft(int idx) const;                       // 获得idx对应的牌的剩余数量
	[[nodiscard]] const int & getTotalLeft() const;                             // 获得所有牌的剩余数量

	void incSecretGangCntOf(int idx);                                           // 给某名玩家的暗杠数量+1
	[[nodiscard]] int getSecretGangCntOf(int idx) const;                        // 获取某名玩家的暗杠数量

	void setCurPosition(int curP);                                              // 设置“我们"当前的编号（座位
	[[nodiscard]] int getCurPosition() const;                                   // 获得我们当前的编号
	void setCurTurnPlayer(int curTP);                                           // 设置当前回合行动的玩家
	[[nodiscard]] int getCurTurnPlayer() const;                                 // 获得当前回合行动的玩家的编号
	void setLastPlayed(const Majang& lastTile);                                // 设置上一个被打出来的麻将
	[[nodiscard]] const Majang& getLastPlayed() const;                         // 获得上一个被打出来的麻将的常引用
	void setInHandCntOf(int idx, int cnt);                                      // 将idx号玩家的手牌数量设置为cnt
	[[nodiscard]] int getInHandCntOf(int idx) const;                            // 获取idx号玩家的手牌数量
	void incInHandCntOf(int idx);                                               // 给idx号玩家的手牌数量+1
	void decInHandCntOf(int idx);                                               // 给idx号玩家的手牌数量-1

	void deleteFromInHand(const Majang& toDelete);                             // 从手牌中去除toDelete   //? 可能是一个优化点

	void nxtPosition();                                                         // 将当前的编号（座位）移动到下一个，！应该不常用
	void nxtTurn();                                                             // 进入下一回合
};

#endif
/*** End of inlined file: StateContainer.h ***/

// 直接使用botzone上的内置算番器（因为我实在不知道怎么配置了
#ifdef _BOTZONE_ONLINE
#include "MahjongGB/MahjongGB.h"
#else

#endif

using namespace std;

//手牌得分用于出牌时的决策，通过比较出掉某一张牌后剩余13张牌的得分，可得到最优的出牌
//只考虑了自己怎么能赢，而没考虑与对手的博弈，这是一版极其自闭的评估函数。

//如何使用(仅供参考)：
//1.出牌时通过比较出掉某一张牌后剩余13张牌的得分与风险系数的乘积(用于评估对手对该牌的需要程度),得到最优出牌
//2.决策杠、吃、碰时通过比较操作前后得分的变化决定是否进行该操作.

class Calculator{
public:
	//返回一副牌的得分(番数得分和手牌得分的加权和)
	static double MajangScoreCalculator(
		vector<pair<string, Majang> > pack,
		//pack:玩家的明牌，每组第一个string为"PENG" "GANG" "CHI" 三者之一，第二个为牌（吃牌表示中间牌）
		vector<Majang> hand,
		//hand:玩家的暗牌
		int flowerCount,
		//flowerCount:补花数
		StateContainer state
		//StateContainer:牌库状态
	);

	//利用算番器计算番数得分
	static double FanScoreCalculator(
		vector<pair<string, Majang> > pack,
		vector<Majang> hand,
		int flowerCount,
		Majang winTile,
		StateContainer state
	);

	//一副牌的番数得分
	static double MajangFanScore(
		vector<pair<string, Majang> > pack,
		vector<Majang> hand,
		int flowerCount,
		StateContainer state,
		int depth //迭代深度
	);

	//一副牌的手牌得分(赋予顺子、刻子、杠、碰、吃相应的得分)
	static double MajangHandScore(
		vector<pair<string, Majang> > pack,
		vector<Majang> hand
	);

	static double HandScoreCalculator(
		int TileAmount[70]
	);
};

#endif
/*** End of inlined file: ScoreCalculator.h ***/

#include <iostream>
using namespace std;

//最终在决策时还应乘上出相应牌的风险系数(用于评估对手对该牌的需要程度)
double Calculator::MajangScoreCalculator(
	vector<pair<string, Majang> > pack,
	vector<Majang> hand,
	int flowerCount,
	StateContainer state
){
	//参数实际应按游戏回合分段，这里先随便写了一个
	double k1=0.5;    // 手牌得分所占权重
	double k2=0.3;    // 自摸番数得分所占权重
	double k3=0.2;    // 点炮番数得分所占权重
	//freopen("D://out.txt","a",stdout);
	double r1=MajangHandScore(pack,hand);
	double r2=MajangFanScore(pack,hand,flowerCount,state,0);
	//cout<<r1<<" "<<r2<<endl;
	//计算点炮番数得分时，出牌的概率应考虑到博弈，还没有想清楚，先用自摸胡的算法计算点炮胡
	return r1*k1+r2*(k2+k3);
}

//参数c是用来使番数得分与手牌得分的数值相当
double Calculator::FanScoreCalculator(
	vector<pair<string, Majang> > pack,//似乎可以直接用两位整数直接作为代表Majang的参数，从而节省时间与空间
	vector<Majang> hand,//似乎可以直接用两位整数直接作为代表Majang的参数，从而节省时间与空间
	int flowerCount,
	Majang winTile,
	StateContainer state
){
	double k4=70.0;    //将Majang类调整为适用于算番器的接口
	vector <pair<string,pair<string,int> > > p;
	for(unsigned int i=0;i<pack.size();++i){
		p.push_back(make_pair(pack[i].first,make_pair(pack[i].second.getTileString(),1)));
	}
	vector <string> h;
	for(unsigned int i=0;i<hand.size();++i){
		h.push_back(hand[i].getTileString());
	}
	//算番器啥时候初始化呢？
	MahjongInit();
	try{
		bool isJUEZHANG=state.getTileLeft(winTile.getTileInt())==0;
		bool isGANG=(StateContainer::lastRequest==36);
		bool isLast=(state.getTotalLeft()-state.getTileLeft(0)-state.getTileLeft(1)-state.getTileLeft(2)-state.getTileLeft(3)-state.getSecretGangCntOf(0)-state.getSecretGangCntOf(1)-state.getSecretGangCntOf(2)-state.getSecretGangCntOf(3))==0;
		auto re=MahjongFanCalculator(p,h,winTile.getTileString(),flowerCount,1,isJUEZHANG,isGANG,isLast,state.getCurPosition(),StateContainer::quan);//算番器中有许多我未理解的参数,先用0代入——wym
		int r=0;
		for(unsigned int i=0;i<re.size();i++) r+=re[i].first;//这里暂且暴力地以求和的方式作为番数得分的计算公式
		return r*k4;
	}
	catch(const string &error){
		return 0;
	}
}

double Calculator::MajangFanScore(
	vector<pair<string, Majang> > pack,
	vector<Majang> hand,
	int flowerCount,
	StateContainer state,
	int depth
){
	double r=0;
	for(int i=11;i<=19;i++){
		if(state.getTileLeft(i)){
			StateContainer newstate(state);
			newstate.decTileLeft(i);
			r+=(double)state.getTileLeft(i)/state.getTotalLeft()*FanScoreCalculator(pack,hand,flowerCount,Majang(i),newstate);
		}
	}
	for(int i=21;i<=29;i++){
		if(state.getTileLeft(i)){
			StateContainer newstate(state);
			newstate.decTileLeft(i);
			r+=(double)state.getTileLeft(i)/state.getTotalLeft()*FanScoreCalculator(pack,hand,flowerCount,Majang(i),newstate);
		}
	}
	for(int i=31;i<=39;i++){
		if(state.getTileLeft(i)){
			StateContainer newstate(state);
			newstate.decTileLeft(i);
			r+=(double)state.getTileLeft(i)/state.getTotalLeft()*FanScoreCalculator(pack,hand,flowerCount,Majang(i),newstate);
		}
	}
	for(int i=41;i<=44;i++){
		if(state.getTileLeft(i)){
			StateContainer newstate(state);
			newstate.decTileLeft(i);
			r+=(double)state.getTileLeft(i)/state.getTotalLeft()*FanScoreCalculator(pack,hand,flowerCount,Majang(i),newstate);
		}
	}
	for(int i=51;i<=53;i++){
		if(state.getTileLeft(i)){
			StateContainer newstate(state);
			newstate.decTileLeft(i);
			r+=(double)state.getTileLeft(i)/state.getTotalLeft()*FanScoreCalculator(pack,hand,flowerCount,Majang(i),newstate);
		}
	}
	if(depth>=1) return r;
	for(int i=61;i<=68;i++){
	  if(state.getTileLeft(i)){
		   StateContainer newstate(state);
		   newstate.decTileLeft(i);
		   r+=(double)state.getTileLeft(i)/state.getTotalLeft()*MajangFanScore(pack,hand,flowerCount+1,newstate,depth+1);
	   }
	}
	return r;
}

//这里采用了将手牌hand和明牌pack合并起来计算的方式,若有必要,可以分开计算并赋上权值
//参数c是用来使番数得分与手牌得分的数值相当
double Calculator::MajangHandScore(
	vector<pair<string, Majang> > pack,
	vector<Majang> hand
){
	double c=1;
	int tileAmount[70];
	memset(tileAmount,0,sizeof(tileAmount));
	for(unsigned int i=0;i<hand.size();i++){
		tileAmount[hand[i].getTileInt()]++;
	}
	for(unsigned int i=0;i<pack.size();i++){
		if(pack[i].first=="GANG") tileAmount[pack[i].second.getTileInt()]=4;
		else if(pack[i].first=="PENG") tileAmount[pack[i].second.getTileInt()]=3;
		else{
			int TileN=pack[i].second.getTileInt();
			tileAmount[TileN-1]++;
			tileAmount[TileN]++;
			tileAmount[TileN+1]++;
		}
	}
	double result=HandScoreCalculator(tileAmount);
	return result*c;
}

//得分计算方法：对于每一张牌，若有手牌满足与之相隔,则+1;相邻,则+2;2张相同,则+2,3张相同,则+3,4张相同,则+4;
//未考虑缺色操作（若有某一花色的数量显然少于其他花色,则应直接打出此花色牌;正确性仍有待商榷,但在决策出牌时应考虑这一点)
double Calculator::HandScoreCalculator(
	int tileAmount[70]
){
	double valueW=0,valueB=0,valueT=0,valueF=0,valueJ=0;
	int sumW=0,sumB=0,sumT=0,sumF=0,sumJ=0;
	double r=0;
	for(int i=11;i<=19;i++){
		if(tileAmount[i]){
			double singleValue=0;
			if(i>=13) singleValue+=tileAmount[i-2]*1;
			if(i>=12) singleValue+=tileAmount[i-1]*2;
			if(i<=17) singleValue+=tileAmount[i+2]*1;
			if(i<=18) singleValue+=tileAmount[i+1]*2;
			if(tileAmount[i]==2) singleValue+=2;
			else if(tileAmount[i]==3) singleValue+=3;
			else if(tileAmount[i]==4) singleValue+=4;
			valueW+=tileAmount[i]*singleValue;
			sumW+=tileAmount[i];
		}
	}
	for(int i=21;i<=29;i++){
		if(tileAmount[i]){
			double singleValue=0;
			if(i>=23) singleValue+=tileAmount[i-2]*1;
			if(i>=22) singleValue+=tileAmount[i-1]*2;
			if(i<=27) singleValue+=tileAmount[i+2]*1;
			if(i<=28) singleValue+=tileAmount[i+1]*2;
			if(tileAmount[i]==2) singleValue+=2;
			else if(tileAmount[i]==3) singleValue+=3;
			else if(tileAmount[i]==4) singleValue+=4;
			valueB+=tileAmount[i]*singleValue;
			sumB+=tileAmount[i];
		}
	}
	for(int i=31;i<=39;i++){
		if(tileAmount[i]){
			double singleValue=0;
			if(i>=33) singleValue+=tileAmount[i-2]*1;
			if(i>=32) singleValue+=tileAmount[i-1]*2;
			if(i<=37) singleValue+=tileAmount[i+2]*1;
			if(i<=38) singleValue+=tileAmount[i+1]*2;
			if(tileAmount[i]==2) singleValue+=2;
			else if(tileAmount[i]==3) singleValue+=3;
			else if(tileAmount[i]==4) singleValue+=4;
			valueT+=tileAmount[i]*singleValue;
			sumT+=tileAmount[i];
		}
	}
	//箭牌和风牌可能要有特殊的地位*
	for(int i=41;i<=44;i++){
		if(tileAmount[i]){
			double singleValue=0;
			// if(i>=43) singleValue+=tileAmount[i-2]*1;
			// if(i>=42) singleValue+=tileAmount[i-1]*2;
			// if(i<=42) singleValue+=tileAmount[i+2]*1;
			// if(i<=43) singleValue+=tileAmount[i+1]*2;
			if(tileAmount[i]==2) singleValue+=2;
			else if(tileAmount[i]==3) singleValue+=3;
			else if(tileAmount[i]==4) singleValue+=4;
			valueF+=tileAmount[i]*singleValue;
			sumF+=tileAmount[i];
		}
	}
	for(int i=51;i<=53;i++){
		if(tileAmount[i]){
			double singleValue=0;
			// if(i>=53) singleValue+=tileAmount[i-2]*1;
			// if(i>=52) singleValue+=tileAmount[i-1]*2;
			// if(i<=51) singleValue+=tileAmount[i+2]*1;
			// if(i<=52) singleValue+=tileAmount[i+1]*2;
			if(tileAmount[i]==2) singleValue+=2;
			else if(tileAmount[i]==3) singleValue+=3;
			else if(tileAmount[i]==4) singleValue+=4;
			valueJ+=tileAmount[i]*singleValue;
			sumJ+=tileAmount[i];
		}
	}
	//手牌张数加成
	int sum=sumW+sumB+sumT+sumF+sumJ;
	valueW*=(1+(double)sumW/sum);
	valueB*=(1+(double)sumB/sum);
	valueT*=(1+(double)sumT/sum);
	valueF*=(1+(double)sumF/sum);
	valueJ*=(1+(double)sumJ/sum);
	r=valueW+valueB+valueT+valueF+valueJ;
	return r;
}

/*** End of inlined file: ScoreCalculator.cpp ***/


/*** Start of inlined file: ResponseOutput.h ***/
#ifndef _BOTZONE_ONLINE
#pragma once
#endif

#ifndef RESPONSEOUTPUT_H
#define RESPONSEOUTPUT_H

#include <string>
#include <cstring>
#include <vector>


/*** Start of inlined file: Majang.h ***/
#ifndef _BOTZONE_ONLINE
#pragma once
#endif

#ifndef MAJANG_H
#define MAJANG_H

#include <string>
//#include <string_view>

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
	TILE_T_SIZE  // 以便循环使用
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
	bool operator == (const Majang& other);

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
/*** End of inlined file: Majang.h ***/


/*** Start of inlined file: StateContainer.h ***/
#ifndef _BOTZONE_ONLINE
#pragma once
#endif

#ifndef STATECONTAINER_H
#define STATECONTAINER_H

#include <valarray>
#include <vector>
#include <algorithm>

// 使用Majang类

/*** Start of inlined file: Majang.h ***/
#ifndef _BOTZONE_ONLINE
#pragma once
#endif

#ifndef MAJANG_H
#define MAJANG_H

#include <string>
//#include <string_view>

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
	TILE_T_SIZE  // 以便循环使用
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
	bool operator == (const Majang& other);

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
/*** End of inlined file: Majang.h ***/


using namespace std;

//typedef pair<char, int> Majang; // 所有麻将牌均以“大写字母+数字”组合表示

// 从题目的输入request的0~9可知，在输入环节我们可以得到的信息有：
// 0. 我们的位置、当前的风圈
// 1. 我们的起始手牌、四名玩家各人的花牌
// 2. 当前是哪个玩家的回合（可以通过各个摸牌操作来判断）
// 3. 各个玩家的鸣牌（可以通过吃碰杠来获得）
// 4. "弃牌堆"中的牌（被打出之后没有被吃碰杠、点炮的牌）

// 用于存放当前的局面
// 由于该部分很多函数很简单，就不费笔墨写注释了，也没有将实现分离到cpp中
class StateContainer {
private:
	int curPosition;                    // “我们”所处的位置，0是庄家。同样也可以在博弈树节点使用以判断敌我
	int curTurnPlayer;                  // 当前是哪个玩家的回合
//    valarray<Majang> inHand;           // 用于存储手牌
//    valarray<Majang> flowerTilesOf[4]; // 用于存储花牌，分别对应4个玩家
//    valarray<Majang> chiOf[4];         // 某个玩家鸣牌中的所有“吃”,存放中间那张牌即可
//    valarray<Majang> pengOf[4];        // 某个玩家鸣牌中的所有“碰”，存放其中一张即可（因为三张一模一样
//    valarray<Majang> gangOf[4];        // 某个玩家鸣牌中的所有“杠”，存放其中一张即可
////    valarray<Majang> discards;       // 用于存放弃牌堆
//    valarray<Majang> tilePlayedOf[4];  // 用于记录某个玩家曾经都打出过哪些卡牌，无论是否被吃、碰还是杠
	vector<Majang> inHand;           // 用于存储手牌
	vector<Majang> flowerTilesOf[4]; // 用于存储花牌，分别对应4个玩家
	vector<Majang> chiOf[4];         // 某个玩家鸣牌中的所有“吃”,存放中间那张牌即可
	vector<Majang> pengOf[4];        // 某个玩家鸣牌中的所有“碰”，存放其中一张即可（因为三张一模一样
	vector<Majang> gangOf[4];        // 某个玩家鸣牌中的所有“杠”，存放其中一张即可
//    valarray<Majang> discards;       // 用于存放弃牌堆
	vector<Majang> tilePlayedOf[4];  // 用于记录某个玩家曾经都打出过哪些卡牌，无论是否被吃、碰还是杠
	int secretGangCntOf[4];           // 用于记录"暗杠"的数量，通过输入数据我们可以判断出某名玩家有几个暗杠，但我们不知道暗杠的是什么
	// 下面这个lastPlayed还没确定好到底怎么用，想好的时候再改吧
	Majang lastPlayed;                 // 用于记录上个回合被打出的麻将牌，如果不是麻将牌类型的话则为其他操作（具体见RequestReader::readRequest
	int tileLeft[70];                   // 用于记录各种类型牌所剩余的没出现的数量
	int totalLeft;                      // 没出现过的牌的总数（初始144）
	int inHandCnt[4];                   // 用于记录四名玩家的手牌数量(虽然不知道有没有用)

public:
	static int quan;                    // 圈风。因为在一把botzone游戏中，只考虑国标麻将的一局游戏，所以圈风应该是不变的
	static int lastRequest;             // 上回合的操作,用于算番器的isGANG,采取博弈算法时应换一种存储方式

	explicit StateContainer(int curP=0, int curT=0);
	StateContainer(const StateContainer& other);

//    [[nodiscard]] valarray<Majang>& getInHand();                               // 获取手牌
//    [[nodiscard]] valarray<Majang>& getFlowerTilesOf(int idx);                 // 获取花牌
//    [[nodiscard]] valarray<Majang>& getChiOf(int idx);                         // 获取鸣牌中的“吃"
//    [[nodiscard]] valarray<Majang>& getPengOf(int idx);                        // 获取鸣牌中的“碰"
//    [[nodiscard]] valarray<Majang>& getGangOf(int idx);                        // 获取鸣牌中的“杠”
////    [[nodiscard]] valarray<Majang>& getDiscards();                             // 获取弃牌堆
//    [[nodiscard]] valarray<Majang>& getTilePlayedOf(int idx);                  // 获取某名玩家打过的所有牌
//
//    [[nodiscard]] const valarray<Majang>& getInHand() const;                   //  获取手牌的常引用，下同上
//    [[nodiscard]] const valarray<Majang>& getFlowerTilesOf(int idx) const;
//    [[nodiscard]] const valarray<Majang>& getChiOf(int idx) const;
//    [[nodiscard]] const valarray<Majang>& getPengOf(int idx) const;
//    [[nodiscard]] const valarray<Majang>& getGangOf(int idx) const;
////    [[nodiscard]] const valarray<Majang>& getDiscards() const;
//    [[nodiscard]] const valarray<Majang>& getTilePlayedOf(int idx) const;

	[[nodiscard]] vector<Majang>& getInHand();                               // 获取手牌
	[[nodiscard]] vector<Majang>& getFlowerTilesOf(int idx);                 // 获取花牌
	[[nodiscard]] vector<Majang>& getChiOf(int idx);                         // 获取鸣牌中的“吃"
	[[nodiscard]] vector<Majang>& getPengOf(int idx);                        // 获取鸣牌中的“碰"
	[[nodiscard]] vector<Majang>& getGangOf(int idx);                        // 获取鸣牌中的“杠”
	[[nodiscard]] vector<Majang>& getTilePlayedOf(int idx);                  // 获取某名玩家打过的所有牌

	[[nodiscard]] const vector<Majang>& getInHand() const;                   //  获取手牌的常引用，下同上
	[[nodiscard]] const vector<Majang>& getFlowerTilesOf(int idx) const;
	[[nodiscard]] const vector<Majang>& getChiOf(int idx) const;
	[[nodiscard]] const vector<Majang>& getPengOf(int idx) const;
	[[nodiscard]] const vector<Majang>& getGangOf(int idx) const;
	[[nodiscard]] const vector<Majang>& getTilePlayedOf(int idx) const;

	void decTileLeft(int idx);                                                  // 在减少idx对应的牌的数量的同时，减少总数的数量
	void decTileLeft(Majang mj);                                               // 同上
	[[nodiscard]] const int & getTileLeft(int idx) const;                       // 获得idx对应的牌的剩余数量
	[[nodiscard]] const int & getTotalLeft() const;                             // 获得所有牌的剩余数量

	void incSecretGangCntOf(int idx);                                           // 给某名玩家的暗杠数量+1
	[[nodiscard]] int getSecretGangCntOf(int idx) const;                        // 获取某名玩家的暗杠数量

	void setCurPosition(int curP);                                              // 设置“我们"当前的编号（座位
	[[nodiscard]] int getCurPosition() const;                                   // 获得我们当前的编号
	void setCurTurnPlayer(int curTP);                                           // 设置当前回合行动的玩家
	[[nodiscard]] int getCurTurnPlayer() const;                                 // 获得当前回合行动的玩家的编号
	void setLastPlayed(const Majang& lastTile);                                // 设置上一个被打出来的麻将
	[[nodiscard]] const Majang& getLastPlayed() const;                         // 获得上一个被打出来的麻将的常引用
	void setInHandCntOf(int idx, int cnt);                                      // 将idx号玩家的手牌数量设置为cnt
	[[nodiscard]] int getInHandCntOf(int idx) const;                            // 获取idx号玩家的手牌数量
	void incInHandCntOf(int idx);                                               // 给idx号玩家的手牌数量+1
	void decInHandCntOf(int idx);                                               // 给idx号玩家的手牌数量-1

	void deleteFromInHand(const Majang& toDelete);                             // 从手牌中去除toDelete   //? 可能是一个优化点

	void nxtPosition();                                                         // 将当前的编号（座位）移动到下一个，！应该不常用
	void nxtTurn();                                                             // 进入下一回合
};

#endif
/*** End of inlined file: StateContainer.h ***/


/*** Start of inlined file: ScoreCalculator.h ***/
#ifndef _BOTZONE_ONLINE
#pragma once
#endif

#ifndef SCORECALCULATOR_H
#define SCORECALCULATOR_H

#include <string>
#include <cstring>
#include <vector>
#include <utility>


/*** Start of inlined file: Majang.h ***/
#ifndef _BOTZONE_ONLINE
#pragma once
#endif

#ifndef MAJANG_H
#define MAJANG_H

#include <string>
//#include <string_view>

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
	TILE_T_SIZE  // 以便循环使用
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
	bool operator == (const Majang& other);

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
/*** End of inlined file: Majang.h ***/


/*** Start of inlined file: StateContainer.h ***/
#ifndef _BOTZONE_ONLINE
#pragma once
#endif

#ifndef STATECONTAINER_H
#define STATECONTAINER_H

#include <valarray>
#include <vector>
#include <algorithm>

// 使用Majang类

/*** Start of inlined file: Majang.h ***/
#ifndef _BOTZONE_ONLINE
#pragma once
#endif

#ifndef MAJANG_H
#define MAJANG_H

#include <string>
//#include <string_view>

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
	TILE_T_SIZE  // 以便循环使用
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
	bool operator == (const Majang& other);

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
/*** End of inlined file: Majang.h ***/


using namespace std;

//typedef pair<char, int> Majang; // 所有麻将牌均以“大写字母+数字”组合表示

// 从题目的输入request的0~9可知，在输入环节我们可以得到的信息有：
// 0. 我们的位置、当前的风圈
// 1. 我们的起始手牌、四名玩家各人的花牌
// 2. 当前是哪个玩家的回合（可以通过各个摸牌操作来判断）
// 3. 各个玩家的鸣牌（可以通过吃碰杠来获得）
// 4. "弃牌堆"中的牌（被打出之后没有被吃碰杠、点炮的牌）

// 用于存放当前的局面
// 由于该部分很多函数很简单，就不费笔墨写注释了，也没有将实现分离到cpp中
class StateContainer {
private:
	int curPosition;                    // “我们”所处的位置，0是庄家。同样也可以在博弈树节点使用以判断敌我
	int curTurnPlayer;                  // 当前是哪个玩家的回合
//    valarray<Majang> inHand;           // 用于存储手牌
//    valarray<Majang> flowerTilesOf[4]; // 用于存储花牌，分别对应4个玩家
//    valarray<Majang> chiOf[4];         // 某个玩家鸣牌中的所有“吃”,存放中间那张牌即可
//    valarray<Majang> pengOf[4];        // 某个玩家鸣牌中的所有“碰”，存放其中一张即可（因为三张一模一样
//    valarray<Majang> gangOf[4];        // 某个玩家鸣牌中的所有“杠”，存放其中一张即可
////    valarray<Majang> discards;       // 用于存放弃牌堆
//    valarray<Majang> tilePlayedOf[4];  // 用于记录某个玩家曾经都打出过哪些卡牌，无论是否被吃、碰还是杠
	vector<Majang> inHand;           // 用于存储手牌
	vector<Majang> flowerTilesOf[4]; // 用于存储花牌，分别对应4个玩家
	vector<Majang> chiOf[4];         // 某个玩家鸣牌中的所有“吃”,存放中间那张牌即可
	vector<Majang> pengOf[4];        // 某个玩家鸣牌中的所有“碰”，存放其中一张即可（因为三张一模一样
	vector<Majang> gangOf[4];        // 某个玩家鸣牌中的所有“杠”，存放其中一张即可
//    valarray<Majang> discards;       // 用于存放弃牌堆
	vector<Majang> tilePlayedOf[4];  // 用于记录某个玩家曾经都打出过哪些卡牌，无论是否被吃、碰还是杠
	int secretGangCntOf[4];           // 用于记录"暗杠"的数量，通过输入数据我们可以判断出某名玩家有几个暗杠，但我们不知道暗杠的是什么
	// 下面这个lastPlayed还没确定好到底怎么用，想好的时候再改吧
	Majang lastPlayed;                 // 用于记录上个回合被打出的麻将牌，如果不是麻将牌类型的话则为其他操作（具体见RequestReader::readRequest
	int tileLeft[70];                   // 用于记录各种类型牌所剩余的没出现的数量
	int totalLeft;                      // 没出现过的牌的总数（初始144）
	int inHandCnt[4];                   // 用于记录四名玩家的手牌数量(虽然不知道有没有用)

public:
	static int quan;                    // 圈风。因为在一把botzone游戏中，只考虑国标麻将的一局游戏，所以圈风应该是不变的
	static int lastRequest;             // 上回合的操作,用于算番器的isGANG,采取博弈算法时应换一种存储方式

	explicit StateContainer(int curP=0, int curT=0);
	StateContainer(const StateContainer& other);

//    [[nodiscard]] valarray<Majang>& getInHand();                               // 获取手牌
//    [[nodiscard]] valarray<Majang>& getFlowerTilesOf(int idx);                 // 获取花牌
//    [[nodiscard]] valarray<Majang>& getChiOf(int idx);                         // 获取鸣牌中的“吃"
//    [[nodiscard]] valarray<Majang>& getPengOf(int idx);                        // 获取鸣牌中的“碰"
//    [[nodiscard]] valarray<Majang>& getGangOf(int idx);                        // 获取鸣牌中的“杠”
////    [[nodiscard]] valarray<Majang>& getDiscards();                             // 获取弃牌堆
//    [[nodiscard]] valarray<Majang>& getTilePlayedOf(int idx);                  // 获取某名玩家打过的所有牌
//
//    [[nodiscard]] const valarray<Majang>& getInHand() const;                   //  获取手牌的常引用，下同上
//    [[nodiscard]] const valarray<Majang>& getFlowerTilesOf(int idx) const;
//    [[nodiscard]] const valarray<Majang>& getChiOf(int idx) const;
//    [[nodiscard]] const valarray<Majang>& getPengOf(int idx) const;
//    [[nodiscard]] const valarray<Majang>& getGangOf(int idx) const;
////    [[nodiscard]] const valarray<Majang>& getDiscards() const;
//    [[nodiscard]] const valarray<Majang>& getTilePlayedOf(int idx) const;

	[[nodiscard]] vector<Majang>& getInHand();                               // 获取手牌
	[[nodiscard]] vector<Majang>& getFlowerTilesOf(int idx);                 // 获取花牌
	[[nodiscard]] vector<Majang>& getChiOf(int idx);                         // 获取鸣牌中的“吃"
	[[nodiscard]] vector<Majang>& getPengOf(int idx);                        // 获取鸣牌中的“碰"
	[[nodiscard]] vector<Majang>& getGangOf(int idx);                        // 获取鸣牌中的“杠”
	[[nodiscard]] vector<Majang>& getTilePlayedOf(int idx);                  // 获取某名玩家打过的所有牌

	[[nodiscard]] const vector<Majang>& getInHand() const;                   //  获取手牌的常引用，下同上
	[[nodiscard]] const vector<Majang>& getFlowerTilesOf(int idx) const;
	[[nodiscard]] const vector<Majang>& getChiOf(int idx) const;
	[[nodiscard]] const vector<Majang>& getPengOf(int idx) const;
	[[nodiscard]] const vector<Majang>& getGangOf(int idx) const;
	[[nodiscard]] const vector<Majang>& getTilePlayedOf(int idx) const;

	void decTileLeft(int idx);                                                  // 在减少idx对应的牌的数量的同时，减少总数的数量
	void decTileLeft(Majang mj);                                               // 同上
	[[nodiscard]] const int & getTileLeft(int idx) const;                       // 获得idx对应的牌的剩余数量
	[[nodiscard]] const int & getTotalLeft() const;                             // 获得所有牌的剩余数量

	void incSecretGangCntOf(int idx);                                           // 给某名玩家的暗杠数量+1
	[[nodiscard]] int getSecretGangCntOf(int idx) const;                        // 获取某名玩家的暗杠数量

	void setCurPosition(int curP);                                              // 设置“我们"当前的编号（座位
	[[nodiscard]] int getCurPosition() const;                                   // 获得我们当前的编号
	void setCurTurnPlayer(int curTP);                                           // 设置当前回合行动的玩家
	[[nodiscard]] int getCurTurnPlayer() const;                                 // 获得当前回合行动的玩家的编号
	void setLastPlayed(const Majang& lastTile);                                // 设置上一个被打出来的麻将
	[[nodiscard]] const Majang& getLastPlayed() const;                         // 获得上一个被打出来的麻将的常引用
	void setInHandCntOf(int idx, int cnt);                                      // 将idx号玩家的手牌数量设置为cnt
	[[nodiscard]] int getInHandCntOf(int idx) const;                            // 获取idx号玩家的手牌数量
	void incInHandCntOf(int idx);                                               // 给idx号玩家的手牌数量+1
	void decInHandCntOf(int idx);                                               // 给idx号玩家的手牌数量-1

	void deleteFromInHand(const Majang& toDelete);                             // 从手牌中去除toDelete   //? 可能是一个优化点

	void nxtPosition();                                                         // 将当前的编号（座位）移动到下一个，！应该不常用
	void nxtTurn();                                                             // 进入下一回合
};

#endif
/*** End of inlined file: StateContainer.h ***/

// 直接使用botzone上的内置算番器（因为我实在不知道怎么配置了
#ifdef _BOTZONE_ONLINE
#include "MahjongGB/MahjongGB.h"
#else

#endif

using namespace std;

//手牌得分用于出牌时的决策，通过比较出掉某一张牌后剩余13张牌的得分，可得到最优的出牌
//只考虑了自己怎么能赢，而没考虑与对手的博弈，这是一版极其自闭的评估函数。

//如何使用(仅供参考)：
//1.出牌时通过比较出掉某一张牌后剩余13张牌的得分与风险系数的乘积(用于评估对手对该牌的需要程度),得到最优出牌
//2.决策杠、吃、碰时通过比较操作前后得分的变化决定是否进行该操作.

class Calculator{
public:
	//返回一副牌的得分(番数得分和手牌得分的加权和)
	static double MajangScoreCalculator(
		vector<pair<string, Majang> > pack,
		//pack:玩家的明牌，每组第一个string为"PENG" "GANG" "CHI" 三者之一，第二个为牌（吃牌表示中间牌）
		vector<Majang> hand,
		//hand:玩家的暗牌
		int flowerCount,
		//flowerCount:补花数
		StateContainer state
		//StateContainer:牌库状态
	);

	//利用算番器计算番数得分
	static double FanScoreCalculator(
		vector<pair<string, Majang> > pack,
		vector<Majang> hand,
		int flowerCount,
		Majang winTile,
		StateContainer state
	);

	//一副牌的番数得分
	static double MajangFanScore(
		vector<pair<string, Majang> > pack,
		vector<Majang> hand,
		int flowerCount,
		StateContainer state,
		int depth //迭代深度
	);

	//一副牌的手牌得分(赋予顺子、刻子、杠、碰、吃相应的得分)
	static double MajangHandScore(
		vector<pair<string, Majang> > pack,
		vector<Majang> hand
	);

	static double HandScoreCalculator(
		int TileAmount[70]
	);
};

#endif
/*** End of inlined file: ScoreCalculator.h ***/

using namespace std;

class Output{
public:
	static void Response(int request,StateContainer state);     //由局面状态(state)和上一步操作(request)得到输出
	static bool judgeHu(vector<pair<string,Majang> > pack,vector<Majang> hand,const Majang& winTile,StateContainer state,bool isZIMO);   //判断是否胡了
	static bool judgeGang(int tileAmout[70],vector<pair<string,Majang> > pack,vector<Majang> hand,const Majang& newTile,StateContainer state,int status);    //判断能否杠,status=2表示为摸牌后，status=3表示对手出牌后;如果能,再判断是否要杠
	static bool judgeBuGang(StateContainer state,vector<pair<string,Majang> > pack,vector<Majang> hand,const Majang& newTile);   //摸牌后判断能否补杠,如果能,再判断是否要杠
	static bool judgePeng(int tileAmout[70], const Majang& newTile);    //对手出牌后判断能否碰
	static int judgeChi(int tileAmout[70], const Majang& newTile);     //对手出牌后判断能否吃,返回值1,2,3分别表示表示吃的牌是组成刻子中的第1,2,3张.
	static const pair<double,Majang> getBestPlay(StateContainer state,vector<pair<string,Majang> > pack,vector<Majang> hand);   //返回最优的出牌及此时的评估值
	static const Majang getBestCP(StateContainer state,vector<pair<string,Majang> > pack,vector<Majang> hand,const Majang& newTile,int pos); //判断是否要吃(c)碰(p),若要则返回之后打出的Majang,否则Majang值为1;pos为0表示要进行的操作为碰或杠,否则表示吃时newTile的位置
};

#endif
/*** End of inlined file: ResponseOutput.h ***/


/*** Start of inlined file: ResponseOutput.cpp ***/

/*** Start of inlined file: ResponseOutput.h ***/
#ifndef _BOTZONE_ONLINE
#pragma once
#endif

#ifndef RESPONSEOUTPUT_H
#define RESPONSEOUTPUT_H

#include <string>
#include <cstring>
#include <vector>


/*** Start of inlined file: Majang.h ***/
#ifndef _BOTZONE_ONLINE
#pragma once
#endif

#ifndef MAJANG_H
#define MAJANG_H

#include <string>
//#include <string_view>

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
	TILE_T_SIZE  // 以便循环使用
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
	bool operator == (const Majang& other);

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
/*** End of inlined file: Majang.h ***/


/*** Start of inlined file: StateContainer.h ***/
#ifndef _BOTZONE_ONLINE
#pragma once
#endif

#ifndef STATECONTAINER_H
#define STATECONTAINER_H

#include <valarray>
#include <vector>
#include <algorithm>

// 使用Majang类

/*** Start of inlined file: Majang.h ***/
#ifndef _BOTZONE_ONLINE
#pragma once
#endif

#ifndef MAJANG_H
#define MAJANG_H

#include <string>
//#include <string_view>

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
	TILE_T_SIZE  // 以便循环使用
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
	bool operator == (const Majang& other);

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
/*** End of inlined file: Majang.h ***/


using namespace std;

//typedef pair<char, int> Majang; // 所有麻将牌均以“大写字母+数字”组合表示

// 从题目的输入request的0~9可知，在输入环节我们可以得到的信息有：
// 0. 我们的位置、当前的风圈
// 1. 我们的起始手牌、四名玩家各人的花牌
// 2. 当前是哪个玩家的回合（可以通过各个摸牌操作来判断）
// 3. 各个玩家的鸣牌（可以通过吃碰杠来获得）
// 4. "弃牌堆"中的牌（被打出之后没有被吃碰杠、点炮的牌）

// 用于存放当前的局面
// 由于该部分很多函数很简单，就不费笔墨写注释了，也没有将实现分离到cpp中
class StateContainer {
private:
	int curPosition;                    // “我们”所处的位置，0是庄家。同样也可以在博弈树节点使用以判断敌我
	int curTurnPlayer;                  // 当前是哪个玩家的回合
//    valarray<Majang> inHand;           // 用于存储手牌
//    valarray<Majang> flowerTilesOf[4]; // 用于存储花牌，分别对应4个玩家
//    valarray<Majang> chiOf[4];         // 某个玩家鸣牌中的所有“吃”,存放中间那张牌即可
//    valarray<Majang> pengOf[4];        // 某个玩家鸣牌中的所有“碰”，存放其中一张即可（因为三张一模一样
//    valarray<Majang> gangOf[4];        // 某个玩家鸣牌中的所有“杠”，存放其中一张即可
////    valarray<Majang> discards;       // 用于存放弃牌堆
//    valarray<Majang> tilePlayedOf[4];  // 用于记录某个玩家曾经都打出过哪些卡牌，无论是否被吃、碰还是杠
	vector<Majang> inHand;           // 用于存储手牌
	vector<Majang> flowerTilesOf[4]; // 用于存储花牌，分别对应4个玩家
	vector<Majang> chiOf[4];         // 某个玩家鸣牌中的所有“吃”,存放中间那张牌即可
	vector<Majang> pengOf[4];        // 某个玩家鸣牌中的所有“碰”，存放其中一张即可（因为三张一模一样
	vector<Majang> gangOf[4];        // 某个玩家鸣牌中的所有“杠”，存放其中一张即可
//    valarray<Majang> discards;       // 用于存放弃牌堆
	vector<Majang> tilePlayedOf[4];  // 用于记录某个玩家曾经都打出过哪些卡牌，无论是否被吃、碰还是杠
	int secretGangCntOf[4];           // 用于记录"暗杠"的数量，通过输入数据我们可以判断出某名玩家有几个暗杠，但我们不知道暗杠的是什么
	// 下面这个lastPlayed还没确定好到底怎么用，想好的时候再改吧
	Majang lastPlayed;                 // 用于记录上个回合被打出的麻将牌，如果不是麻将牌类型的话则为其他操作（具体见RequestReader::readRequest
	int tileLeft[70];                   // 用于记录各种类型牌所剩余的没出现的数量
	int totalLeft;                      // 没出现过的牌的总数（初始144）
	int inHandCnt[4];                   // 用于记录四名玩家的手牌数量(虽然不知道有没有用)

public:
	static int quan;                    // 圈风。因为在一把botzone游戏中，只考虑国标麻将的一局游戏，所以圈风应该是不变的
	static int lastRequest;             // 上回合的操作,用于算番器的isGANG,采取博弈算法时应换一种存储方式

	explicit StateContainer(int curP=0, int curT=0);
	StateContainer(const StateContainer& other);

//    [[nodiscard]] valarray<Majang>& getInHand();                               // 获取手牌
//    [[nodiscard]] valarray<Majang>& getFlowerTilesOf(int idx);                 // 获取花牌
//    [[nodiscard]] valarray<Majang>& getChiOf(int idx);                         // 获取鸣牌中的“吃"
//    [[nodiscard]] valarray<Majang>& getPengOf(int idx);                        // 获取鸣牌中的“碰"
//    [[nodiscard]] valarray<Majang>& getGangOf(int idx);                        // 获取鸣牌中的“杠”
////    [[nodiscard]] valarray<Majang>& getDiscards();                             // 获取弃牌堆
//    [[nodiscard]] valarray<Majang>& getTilePlayedOf(int idx);                  // 获取某名玩家打过的所有牌
//
//    [[nodiscard]] const valarray<Majang>& getInHand() const;                   //  获取手牌的常引用，下同上
//    [[nodiscard]] const valarray<Majang>& getFlowerTilesOf(int idx) const;
//    [[nodiscard]] const valarray<Majang>& getChiOf(int idx) const;
//    [[nodiscard]] const valarray<Majang>& getPengOf(int idx) const;
//    [[nodiscard]] const valarray<Majang>& getGangOf(int idx) const;
////    [[nodiscard]] const valarray<Majang>& getDiscards() const;
//    [[nodiscard]] const valarray<Majang>& getTilePlayedOf(int idx) const;

	[[nodiscard]] vector<Majang>& getInHand();                               // 获取手牌
	[[nodiscard]] vector<Majang>& getFlowerTilesOf(int idx);                 // 获取花牌
	[[nodiscard]] vector<Majang>& getChiOf(int idx);                         // 获取鸣牌中的“吃"
	[[nodiscard]] vector<Majang>& getPengOf(int idx);                        // 获取鸣牌中的“碰"
	[[nodiscard]] vector<Majang>& getGangOf(int idx);                        // 获取鸣牌中的“杠”
	[[nodiscard]] vector<Majang>& getTilePlayedOf(int idx);                  // 获取某名玩家打过的所有牌

	[[nodiscard]] const vector<Majang>& getInHand() const;                   //  获取手牌的常引用，下同上
	[[nodiscard]] const vector<Majang>& getFlowerTilesOf(int idx) const;
	[[nodiscard]] const vector<Majang>& getChiOf(int idx) const;
	[[nodiscard]] const vector<Majang>& getPengOf(int idx) const;
	[[nodiscard]] const vector<Majang>& getGangOf(int idx) const;
	[[nodiscard]] const vector<Majang>& getTilePlayedOf(int idx) const;

	void decTileLeft(int idx);                                                  // 在减少idx对应的牌的数量的同时，减少总数的数量
	void decTileLeft(Majang mj);                                               // 同上
	[[nodiscard]] const int & getTileLeft(int idx) const;                       // 获得idx对应的牌的剩余数量
	[[nodiscard]] const int & getTotalLeft() const;                             // 获得所有牌的剩余数量

	void incSecretGangCntOf(int idx);                                           // 给某名玩家的暗杠数量+1
	[[nodiscard]] int getSecretGangCntOf(int idx) const;                        // 获取某名玩家的暗杠数量

	void setCurPosition(int curP);                                              // 设置“我们"当前的编号（座位
	[[nodiscard]] int getCurPosition() const;                                   // 获得我们当前的编号
	void setCurTurnPlayer(int curTP);                                           // 设置当前回合行动的玩家
	[[nodiscard]] int getCurTurnPlayer() const;                                 // 获得当前回合行动的玩家的编号
	void setLastPlayed(const Majang& lastTile);                                // 设置上一个被打出来的麻将
	[[nodiscard]] const Majang& getLastPlayed() const;                         // 获得上一个被打出来的麻将的常引用
	void setInHandCntOf(int idx, int cnt);                                      // 将idx号玩家的手牌数量设置为cnt
	[[nodiscard]] int getInHandCntOf(int idx) const;                            // 获取idx号玩家的手牌数量
	void incInHandCntOf(int idx);                                               // 给idx号玩家的手牌数量+1
	void decInHandCntOf(int idx);                                               // 给idx号玩家的手牌数量-1

	void deleteFromInHand(const Majang& toDelete);                             // 从手牌中去除toDelete   //? 可能是一个优化点

	void nxtPosition();                                                         // 将当前的编号（座位）移动到下一个，！应该不常用
	void nxtTurn();                                                             // 进入下一回合
};

#endif
/*** End of inlined file: StateContainer.h ***/


/*** Start of inlined file: ScoreCalculator.h ***/
#ifndef _BOTZONE_ONLINE
#pragma once
#endif

#ifndef SCORECALCULATOR_H
#define SCORECALCULATOR_H

#include <string>
#include <cstring>
#include <vector>
#include <utility>


/*** Start of inlined file: Majang.h ***/
#ifndef _BOTZONE_ONLINE
#pragma once
#endif

#ifndef MAJANG_H
#define MAJANG_H

#include <string>
//#include <string_view>

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
	TILE_T_SIZE  // 以便循环使用
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
	bool operator == (const Majang& other);

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
/*** End of inlined file: Majang.h ***/


/*** Start of inlined file: StateContainer.h ***/
#ifndef _BOTZONE_ONLINE
#pragma once
#endif

#ifndef STATECONTAINER_H
#define STATECONTAINER_H

#include <valarray>
#include <vector>
#include <algorithm>

// 使用Majang类

/*** Start of inlined file: Majang.h ***/
#ifndef _BOTZONE_ONLINE
#pragma once
#endif

#ifndef MAJANG_H
#define MAJANG_H

#include <string>
//#include <string_view>

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
	TILE_T_SIZE  // 以便循环使用
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
	bool operator == (const Majang& other);

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
/*** End of inlined file: Majang.h ***/


using namespace std;

//typedef pair<char, int> Majang; // 所有麻将牌均以“大写字母+数字”组合表示

// 从题目的输入request的0~9可知，在输入环节我们可以得到的信息有：
// 0. 我们的位置、当前的风圈
// 1. 我们的起始手牌、四名玩家各人的花牌
// 2. 当前是哪个玩家的回合（可以通过各个摸牌操作来判断）
// 3. 各个玩家的鸣牌（可以通过吃碰杠来获得）
// 4. "弃牌堆"中的牌（被打出之后没有被吃碰杠、点炮的牌）

// 用于存放当前的局面
// 由于该部分很多函数很简单，就不费笔墨写注释了，也没有将实现分离到cpp中
class StateContainer {
private:
	int curPosition;                    // “我们”所处的位置，0是庄家。同样也可以在博弈树节点使用以判断敌我
	int curTurnPlayer;                  // 当前是哪个玩家的回合
//    valarray<Majang> inHand;           // 用于存储手牌
//    valarray<Majang> flowerTilesOf[4]; // 用于存储花牌，分别对应4个玩家
//    valarray<Majang> chiOf[4];         // 某个玩家鸣牌中的所有“吃”,存放中间那张牌即可
//    valarray<Majang> pengOf[4];        // 某个玩家鸣牌中的所有“碰”，存放其中一张即可（因为三张一模一样
//    valarray<Majang> gangOf[4];        // 某个玩家鸣牌中的所有“杠”，存放其中一张即可
////    valarray<Majang> discards;       // 用于存放弃牌堆
//    valarray<Majang> tilePlayedOf[4];  // 用于记录某个玩家曾经都打出过哪些卡牌，无论是否被吃、碰还是杠
	vector<Majang> inHand;           // 用于存储手牌
	vector<Majang> flowerTilesOf[4]; // 用于存储花牌，分别对应4个玩家
	vector<Majang> chiOf[4];         // 某个玩家鸣牌中的所有“吃”,存放中间那张牌即可
	vector<Majang> pengOf[4];        // 某个玩家鸣牌中的所有“碰”，存放其中一张即可（因为三张一模一样
	vector<Majang> gangOf[4];        // 某个玩家鸣牌中的所有“杠”，存放其中一张即可
//    valarray<Majang> discards;       // 用于存放弃牌堆
	vector<Majang> tilePlayedOf[4];  // 用于记录某个玩家曾经都打出过哪些卡牌，无论是否被吃、碰还是杠
	int secretGangCntOf[4];           // 用于记录"暗杠"的数量，通过输入数据我们可以判断出某名玩家有几个暗杠，但我们不知道暗杠的是什么
	// 下面这个lastPlayed还没确定好到底怎么用，想好的时候再改吧
	Majang lastPlayed;                 // 用于记录上个回合被打出的麻将牌，如果不是麻将牌类型的话则为其他操作（具体见RequestReader::readRequest
	int tileLeft[70];                   // 用于记录各种类型牌所剩余的没出现的数量
	int totalLeft;                      // 没出现过的牌的总数（初始144）
	int inHandCnt[4];                   // 用于记录四名玩家的手牌数量(虽然不知道有没有用)

public:
	static int quan;                    // 圈风。因为在一把botzone游戏中，只考虑国标麻将的一局游戏，所以圈风应该是不变的
	static int lastRequest;             // 上回合的操作,用于算番器的isGANG,采取博弈算法时应换一种存储方式

	explicit StateContainer(int curP=0, int curT=0);
	StateContainer(const StateContainer& other);

//    [[nodiscard]] valarray<Majang>& getInHand();                               // 获取手牌
//    [[nodiscard]] valarray<Majang>& getFlowerTilesOf(int idx);                 // 获取花牌
//    [[nodiscard]] valarray<Majang>& getChiOf(int idx);                         // 获取鸣牌中的“吃"
//    [[nodiscard]] valarray<Majang>& getPengOf(int idx);                        // 获取鸣牌中的“碰"
//    [[nodiscard]] valarray<Majang>& getGangOf(int idx);                        // 获取鸣牌中的“杠”
////    [[nodiscard]] valarray<Majang>& getDiscards();                             // 获取弃牌堆
//    [[nodiscard]] valarray<Majang>& getTilePlayedOf(int idx);                  // 获取某名玩家打过的所有牌
//
//    [[nodiscard]] const valarray<Majang>& getInHand() const;                   //  获取手牌的常引用，下同上
//    [[nodiscard]] const valarray<Majang>& getFlowerTilesOf(int idx) const;
//    [[nodiscard]] const valarray<Majang>& getChiOf(int idx) const;
//    [[nodiscard]] const valarray<Majang>& getPengOf(int idx) const;
//    [[nodiscard]] const valarray<Majang>& getGangOf(int idx) const;
////    [[nodiscard]] const valarray<Majang>& getDiscards() const;
//    [[nodiscard]] const valarray<Majang>& getTilePlayedOf(int idx) const;

	[[nodiscard]] vector<Majang>& getInHand();                               // 获取手牌
	[[nodiscard]] vector<Majang>& getFlowerTilesOf(int idx);                 // 获取花牌
	[[nodiscard]] vector<Majang>& getChiOf(int idx);                         // 获取鸣牌中的“吃"
	[[nodiscard]] vector<Majang>& getPengOf(int idx);                        // 获取鸣牌中的“碰"
	[[nodiscard]] vector<Majang>& getGangOf(int idx);                        // 获取鸣牌中的“杠”
	[[nodiscard]] vector<Majang>& getTilePlayedOf(int idx);                  // 获取某名玩家打过的所有牌

	[[nodiscard]] const vector<Majang>& getInHand() const;                   //  获取手牌的常引用，下同上
	[[nodiscard]] const vector<Majang>& getFlowerTilesOf(int idx) const;
	[[nodiscard]] const vector<Majang>& getChiOf(int idx) const;
	[[nodiscard]] const vector<Majang>& getPengOf(int idx) const;
	[[nodiscard]] const vector<Majang>& getGangOf(int idx) const;
	[[nodiscard]] const vector<Majang>& getTilePlayedOf(int idx) const;

	void decTileLeft(int idx);                                                  // 在减少idx对应的牌的数量的同时，减少总数的数量
	void decTileLeft(Majang mj);                                               // 同上
	[[nodiscard]] const int & getTileLeft(int idx) const;                       // 获得idx对应的牌的剩余数量
	[[nodiscard]] const int & getTotalLeft() const;                             // 获得所有牌的剩余数量

	void incSecretGangCntOf(int idx);                                           // 给某名玩家的暗杠数量+1
	[[nodiscard]] int getSecretGangCntOf(int idx) const;                        // 获取某名玩家的暗杠数量

	void setCurPosition(int curP);                                              // 设置“我们"当前的编号（座位
	[[nodiscard]] int getCurPosition() const;                                   // 获得我们当前的编号
	void setCurTurnPlayer(int curTP);                                           // 设置当前回合行动的玩家
	[[nodiscard]] int getCurTurnPlayer() const;                                 // 获得当前回合行动的玩家的编号
	void setLastPlayed(const Majang& lastTile);                                // 设置上一个被打出来的麻将
	[[nodiscard]] const Majang& getLastPlayed() const;                         // 获得上一个被打出来的麻将的常引用
	void setInHandCntOf(int idx, int cnt);                                      // 将idx号玩家的手牌数量设置为cnt
	[[nodiscard]] int getInHandCntOf(int idx) const;                            // 获取idx号玩家的手牌数量
	void incInHandCntOf(int idx);                                               // 给idx号玩家的手牌数量+1
	void decInHandCntOf(int idx);                                               // 给idx号玩家的手牌数量-1

	void deleteFromInHand(const Majang& toDelete);                             // 从手牌中去除toDelete   //? 可能是一个优化点

	void nxtPosition();                                                         // 将当前的编号（座位）移动到下一个，！应该不常用
	void nxtTurn();                                                             // 进入下一回合
};

#endif
/*** End of inlined file: StateContainer.h ***/

// 直接使用botzone上的内置算番器（因为我实在不知道怎么配置了
#ifdef _BOTZONE_ONLINE
#include "MahjongGB/MahjongGB.h"
#else

#endif

using namespace std;

//手牌得分用于出牌时的决策，通过比较出掉某一张牌后剩余13张牌的得分，可得到最优的出牌
//只考虑了自己怎么能赢，而没考虑与对手的博弈，这是一版极其自闭的评估函数。

//如何使用(仅供参考)：
//1.出牌时通过比较出掉某一张牌后剩余13张牌的得分与风险系数的乘积(用于评估对手对该牌的需要程度),得到最优出牌
//2.决策杠、吃、碰时通过比较操作前后得分的变化决定是否进行该操作.

class Calculator{
public:
	//返回一副牌的得分(番数得分和手牌得分的加权和)
	static double MajangScoreCalculator(
		vector<pair<string, Majang> > pack,
		//pack:玩家的明牌，每组第一个string为"PENG" "GANG" "CHI" 三者之一，第二个为牌（吃牌表示中间牌）
		vector<Majang> hand,
		//hand:玩家的暗牌
		int flowerCount,
		//flowerCount:补花数
		StateContainer state
		//StateContainer:牌库状态
	);

	//利用算番器计算番数得分
	static double FanScoreCalculator(
		vector<pair<string, Majang> > pack,
		vector<Majang> hand,
		int flowerCount,
		Majang winTile,
		StateContainer state
	);

	//一副牌的番数得分
	static double MajangFanScore(
		vector<pair<string, Majang> > pack,
		vector<Majang> hand,
		int flowerCount,
		StateContainer state,
		int depth //迭代深度
	);

	//一副牌的手牌得分(赋予顺子、刻子、杠、碰、吃相应的得分)
	static double MajangHandScore(
		vector<pair<string, Majang> > pack,
		vector<Majang> hand
	);

	static double HandScoreCalculator(
		int TileAmount[70]
	);
};

#endif
/*** End of inlined file: ScoreCalculator.h ***/

using namespace std;

class Output{
public:
	static void Response(int request,StateContainer state);     //由局面状态(state)和上一步操作(request)得到输出
	static bool judgeHu(vector<pair<string,Majang> > pack,vector<Majang> hand,const Majang& winTile,StateContainer state,bool isZIMO);   //判断是否胡了
	static bool judgeGang(int tileAmout[70],vector<pair<string,Majang> > pack,vector<Majang> hand,const Majang& newTile,StateContainer state,int status);    //判断能否杠,status=2表示为摸牌后，status=3表示对手出牌后;如果能,再判断是否要杠
	static bool judgeBuGang(StateContainer state,vector<pair<string,Majang> > pack,vector<Majang> hand,const Majang& newTile);   //摸牌后判断能否补杠,如果能,再判断是否要杠
	static bool judgePeng(int tileAmout[70], const Majang& newTile);    //对手出牌后判断能否碰
	static int judgeChi(int tileAmout[70], const Majang& newTile);     //对手出牌后判断能否吃,返回值1,2,3分别表示表示吃的牌是组成刻子中的第1,2,3张.
	static const pair<double,Majang> getBestPlay(StateContainer state,vector<pair<string,Majang> > pack,vector<Majang> hand);   //返回最优的出牌及此时的评估值
	static const Majang getBestCP(StateContainer state,vector<pair<string,Majang> > pack,vector<Majang> hand,const Majang& newTile,int pos); //判断是否要吃(c)碰(p),若要则返回之后打出的Majang,否则Majang值为1;pos为0表示要进行的操作为碰或杠,否则表示吃时newTile的位置
};

#endif
/*** End of inlined file: ResponseOutput.h ***/

#include <iostream>
using namespace std;

void Output::Response(int request, StateContainer state){

	//接口不同,把valarray转化vector(优化后去掉此步骤)
	vector<Majang> hand;
	for(size_t i=0;i<state.getInHand().size();i++) hand.push_back(state.getInHand()[i]);
	vector<pair<string,Majang> > pack;
	for(size_t i=0;i<state.getChiOf(state.getCurPosition()).size();i++) pack.push_back(make_pair("CHI",state.getChiOf(state.getCurPosition())[i]));
	for(size_t i=0;i<state.getPengOf(state.getCurPosition()).size();i++) pack.push_back(make_pair("PENG",state.getPengOf(state.getCurPosition())[i]));
	for(size_t i=0;i<state.getGangOf(state.getCurPosition()).size();i++) pack.push_back(make_pair("GANG",state.getGangOf(state.getCurPosition())[i]));

	//注意：若此回合为抽牌后,此时应比正常情况多出1张手牌
	int tileAmount[70];
	memset(tileAmount,0,sizeof(tileAmount));
	//! 这里显然可以优化，可能还有很多相似的地方，我就先不找了
//    for(size_t i=0;i<hand.size();i++){
	for(const auto& item: hand)
		tileAmount[item.getTileInt()]++;

	//如果是抽牌
	if(request==2){
		//此时手牌中最后一个元素即为抽到的牌
		if(judgeHu(pack,hand,hand.back(),state,true)){
			printf("HU");
		}
		else if(judgeBuGang(state,pack,hand,hand.back())){
			printf("BUGANG %s",hand.back().getTileString().c_str());
		}
		else if(judgeGang(tileAmount,pack,hand,hand.back(),state,2)){
			printf("GANG %s",hand.back().getTileString().c_str());
		}
		else{
			Majang Tileplay=getBestPlay(state,pack,hand).second;
			printf("PLAY %s",Tileplay.getTileString().c_str());
		}
	}

	//如果有别人打出的牌
	else if((request==32||request==33||request==34)&&state.getCurTurnPlayer() != state.getCurPosition()){
		Majang lastTile=state.getLastPlayed();//被打出的牌
		int chi=judgeChi(tileAmount,lastTile);
		//HU
		if(judgeHu(pack,hand,lastTile,state,false)){
			printf("HU");
		}
		//GANG
		else if(judgeGang(tileAmount,pack,hand,lastTile,state,3)){
			printf("GANG");
		}
		//PENG
		else if(judgePeng(tileAmount,lastTile)){
			Majang MajangPlay = getBestCP(state,pack,hand,lastTile,0);
			if(MajangPlay.getTileInt()==1){
				printf("PASS");
			}
			else{
				printf("PENG %s",MajangPlay.getTileString().c_str());
			}
		}
		//chi
		else if((state.getCurTurnPlayer()+1)%4==state.getCurPosition()&&chi){
			Majang MajangPlay=getBestCP(state,pack,hand,lastTile,chi);
			if(MajangPlay.getTileInt()==1){
				printf("PASS");
			}
			else{
				if(chi==1) printf("CHI %s %s",lastTile.getNxtMajang().getTileString().c_str(),MajangPlay.getTileString().c_str());
				else if(chi==2) printf("CHI %s %s",lastTile.getTileString().c_str(),MajangPlay.getTileString().c_str());
				else printf("CHI %s %s",lastTile.getPrvMajang().getTileString().c_str(),MajangPlay.getTileString().c_str());
			}
		}
		else{
			printf("PASS");
		}
	}

	//抢杠和
	else if(request==36&&judgeHu(pack,hand,state.getLastPlayed(),state,false)){
		printf("HU");
	}

	//其余情况直接输出"pass"即可
	else{
		printf("PASS");
	}
}

bool Output::judgeHu(
	vector<pair<string,Majang> > pack,
	vector<Majang> hand,
	const Majang& winTile,
	StateContainer state,
	bool isZIMO
){
	//cout << "[DEBUG] judgingHu\n";
	//再次转换接口(可优化)
	vector <pair<string,pair<string,int> > > p;
	for(unsigned int i=0;i<pack.size();++i){
		p.push_back(make_pair(pack[i].first,make_pair(pack[i].second.getTileString(),1)));
	}
	//cout << "[DEBUG] p Generate Successed.\n";
	vector <string> h;
	//如果是摸牌,要把手牌中已经加入的摸牌去掉
	if(isZIMO){
		for(unsigned int i=0;i<hand.size()-1;++i){
			h.push_back(hand[i].getTileString());
		}
	}
	else{
		for(unsigned int i=0;i<hand.size();++i){
			h.push_back(hand[i].getTileString());
		}
	}
	//cout << "[DEBUG] h Generate Successed.\n";
	//算番器啥时候初始化呢？
	MahjongInit();
	//cout << "[DEBUG] Mahjong Init Successed.\n";
	try{
		bool isJUEZHANG=state.getTileLeft(winTile.getTileInt())==0;
		bool isGANG=(StateContainer::lastRequest==36);
		bool isLast=(state.getTotalLeft()-state.getTileLeft(0)-state.getTileLeft(1)-state.getTileLeft(2)-state.getTileLeft(3)-state.getSecretGangCntOf(0)-state.getSecretGangCntOf(1)-state.getSecretGangCntOf(2)-state.getSecretGangCntOf(3))==0;
		auto re=MahjongFanCalculator(p,h,winTile.getTileString(),0,isZIMO,isJUEZHANG,isGANG,isLast,state.getCurPosition(),StateContainer::quan);
		int r=0;
		//cout << "[DEBUG] judgeHu Successed!\n";
		for(unsigned int i=0;i<re.size();i++) {
			r+=re[i].first;
			// cout << "[DEBUG] " << re[i].second << " | " << re[i].first << endl;
		}
		return r >= 8;  // 这里简化了一下
	}catch(const string &error){
		return false;
	}
}

int Output::judgeChi(
	int TileAmount[70],
	const Majang& newTile
){
	if(newTile.getTileInt()/10<=3){
		if(newTile.getTileNum()<=7&&TileAmount[newTile.getTileInt()+1]&&TileAmount[newTile.getTileInt()+2]) return 1;
		else if(newTile.getTileNum()>=2&&newTile.getTileNum()<=8&&TileAmount[newTile.getTileInt()-1]&&TileAmount[newTile.getTileInt()+1]) return 2;
		else if(newTile.getTileNum()>=3&&TileAmount[newTile.getTileInt()-1]&&TileAmount[newTile.getTileInt()-2]) return 3;
		else return 0;
	}
	//风牌、箭牌不能吃，吗？
	else
		return 0;
}

bool Output::judgePeng(
	int tileAmout[70],
	const Majang& newTile
){
	if(tileAmout[newTile.getTileInt()]==2) return true;
	else return false;
}

bool Output::judgeGang(
	int tileAmout[70],
	vector<pair<string,Majang> > pack,
	vector<Majang> hand,
	const Majang& newTile,
	StateContainer state,
	int status
){
	//cout << "[DEBUG] judgingGang\n";    // 没位置加判断是否成功
	if(status==3){
		if(tileAmout[newTile.getTileInt()]==3){
			//先得到不杠时的评估值
			double maxResult1=Calculator::MajangScoreCalculator(pack,hand,state.getFlowerTilesOf(state.getCurPosition()).size(),state);
			//杠后修改pack,hand;
			for(unsigned int i=0;i<hand.size();i++){
				if(hand[i].getTileInt()==newTile.getTileInt()){
					hand.erase(hand.begin()+i);
					i--;
			}
		}
			pack.push_back(make_pair("GANG",newTile));
			double maxResult2=Calculator::MajangScoreCalculator(pack,hand,state.getFlowerTilesOf(state.getCurPosition()).size(),state);
			if(maxResult2-maxResult1>=1e-5) return true;
			else return false;
		}
		else return false;
	}
	else if(status==2){
		if(tileAmout[newTile.getTileInt()]==4){
			//如果不杠,则要打出一张牌,找到所有出牌中的评估最大值
			double maxResult1=getBestPlay(state,pack,hand).first;
			//杠后修改pack,hand;
			for(unsigned int i=0;i<hand.size();i++){
				if(hand[i].getTileInt()==newTile.getTileInt()){
					hand.erase(hand.begin()+i);
					i--;
			}
			pack.push_back(make_pair("GANG",newTile));
			double maxResult2=Calculator::MajangScoreCalculator(pack,hand,state.getFlowerTilesOf(state.getCurPosition()).size(),state);
			if(maxResult2-maxResult1>=1e-5) return true;
			else return false;
			}
		}
		else return false;
	}
	return false;
}

bool Output::judgeBuGang(
	StateContainer state,
	vector<pair<string,Majang> > pack,
	vector<Majang> hand,
	const Majang& newTile
){
	//cout << " judgingBuGang\n";
	for(unsigned int i=0;i<pack.size();i++){
		if(pack[i].first=="PENG"&&pack[i].second.getTileInt()==newTile.getTileInt()){
			//如果不杠,则要打出一张牌,找到所有出牌中的评估最大值
			double maxResult1=getBestPlay(state,pack,hand).first;
			//如果杠,先把手牌中的这张牌去掉,再在pack中去掉peng,增加gang
			for(unsigned int k=0;k<hand.size();k++){
				if(hand[k].getTileInt()==newTile.getTileInt()){
					hand.erase(hand.begin()+k);
					break;
				}
			}
			pack.erase(pack.begin()+i);
			pack.push_back(make_pair("GANG",newTile));
			double maxResult2=Calculator::MajangScoreCalculator(pack,hand,state.getFlowerTilesOf(state.getCurPosition()).size(),state);
			//cout << "[DEBUG] judgeBuGang Successed!\n";
			if(maxResult2-maxResult1>=1e-5) return true;
			else return false;
		}
	}
	return false;
}

const pair<double,Majang> Output::getBestPlay(
	StateContainer state,
	vector<pair<string,Majang> > pack,
	vector<Majang> hand
){
	int bestChoice=0;
	double maxResult=-1e5;
	for(unsigned int i=0;i<hand.size();i++){
		vector<Majang> newHand(hand);
		newHand.erase(newHand.begin()+i);//从手牌中打出这一张牌
		double ans=Calculator::MajangScoreCalculator(pack,newHand,state.getFlowerTilesOf(state.getCurPosition()).size(),state);
		if(ans>maxResult){
			maxResult=ans;
			bestChoice=i;
		}
	}
	return make_pair(maxResult,hand[bestChoice]);
}

const Majang Output::getBestCP(
	StateContainer state,
	vector<pair<string,Majang> > pack,
	vector<Majang> hand,
	const Majang& newTile,
	int pos
){
	//先得到不进行操作时最优得分
	double maxResult1=Calculator::MajangScoreCalculator(pack,hand,state.getFlowerTilesOf(state.getCurPosition()).size(),state);
	//进行操作,改变hand和pack；若考虑到博弈过程，同时要修改state,在这里未对state进行修改.
	if(pos==0){
		for(unsigned int i=0;i<hand.size();i++){
			if(hand[i].getTileInt()==newTile.getTileInt()){
				hand.erase(hand.begin()+i);
				i--;
			}
		}
			pack.push_back(make_pair("PENG",newTile));
	}
	else{
		//把吃掉的牌从手牌hand中去掉,再把顺子加到pack中
		if(pos==1){
			int k1=1,k2=1;
			unsigned int i=0;
			while((k1||k2)&&i<hand.size()){
				if(k1&&hand[i].getTileInt()==newTile.getTileInt()+1){
					k1--;
					hand.erase(hand.begin()+i);
				}
				else if(k2&&hand[i].getTileInt()==newTile.getTileInt()+2){
					k2--;
					hand.erase(hand.begin()+i);
				}
				else{
					i++;
				}
			}
			pack.push_back(make_pair("CHI",newTile.getNxtMajang()));
		}
		else if(pos==2){
			int k1=1,k2=1;
			unsigned int i=0;
			while((k1||k2)&&i<hand.size()){
				if(k1&&hand[i].getTileInt()==newTile.getTileInt()-1){
					k1--;
					hand.erase(hand.begin()+i);
				}
				else if(k2&&hand[i].getTileInt()==newTile.getTileInt()+1){
					k2--;
					hand.erase(hand.begin()+i);
				}
				else{
					i++;
				}
			}
			pack.push_back(make_pair("CHI",newTile));
		}
		else{
			int k1=1,k2=1;
			unsigned int i=0;
			while((k1||k2)&&i<hand.size()){
				if(k1&&hand[i].getTileInt()==newTile.getTileInt()-1){
					k1--;
					hand.erase(hand.begin()+i);
				}
				else if(k2&&hand[i].getTileInt()==newTile.getTileInt()-2){
					k2--;
					hand.erase(hand.begin()+i);
				}
				else{
					i++;
				}
			}
			pack.push_back(make_pair("CHI",newTile.getPrvMajang()));
		}
	}
	//得到操作过后的最优解
	pair<double,Majang> r=getBestPlay(state,pack,hand);
	double maxResult2=r.first;
	if(maxResult2-maxResult1>=1e-5){
		return r.second;
	}
	else return Majang(1);
}
/*** End of inlined file: ResponseOutput.cpp ***/

#include <iostream>

int StateContainer::quan=0;
int StateContainer::lastRequest=0;
int main() {
	int turnID; Reader::readIn(turnID);
	string tmp;
	int lastRequest;
	StateContainer basicState;
	for(int i=1; i<turnID; i++) {
		lastRequest = Reader::readRequest(basicState);
		getline(cin, tmp);   // 过滤掉我们发出的无用的信息
//        vector<Majang> & tmpM=basicState.getInHand();
//        for(auto & mahjong:tmpM){
//            cout<<mahjong.getTileString()<<" ";
//        }
//        cout<<endl;
	}
	StateContainer::lastRequest=lastRequest;
	int t=Reader::readRequest(basicState);
//        vector<Majang> & tmpM=basicState.getInHand();
//        for(auto & mahjong:tmpM){
//            cout<<mahjong.getTileString()<<" ";
//        }
//        cout<<endl;
	Output::Response(t, basicState);
	return 0;
}
