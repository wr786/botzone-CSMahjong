#ifdef _BOTZONE_ONLINE
#include "MahjongGB/MahjongGB.h"
#endif


/*** Start of inlined file: Majang.h ***/
//#pragma once

#ifndef MAJANG_H
#define MAJANG_H

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
	explicit Majang(string_view strExpr);                                  // 通过string直接创建Majang

	Majang& operator = (const Majang& other);
	bool operator == (const Majang& other);

	void resetFromString(string_view strExpr);                              // 由此将string转换为string_view，提高速度

	static TILE_T getTileTypeFromChar(char ch);                             // 从char得到麻将牌的类型
	static int parseTileType(string_view strExpr);                          // 从string得到麻将牌的类型
	static int parseTileNum(string_view strExpr);                           // 从string得到麻将牌的数字
	static TILE parseTile(string_view strExpr);                             // 从string得到麻将牌（用TILE表示）
	[[nodiscard]] char getTileType() const;                                 // 获得麻将牌的类型
	[[nodiscard]] int getTileNum() const;                                   // 获得麻将牌的数字
	[[nodiscard]] TILE getTileInt() const;                                  // 获得麻将牌的innerType
	[[nodiscard]] bool isFlowerTile() const;                                // 判断当前这张牌是否是花牌
	[[nodiscard]] string getTileString() const;                             // 获取麻将牌的代码(botzone表示法),用于算番器——wym

	[[nodiscard]] Majang getNxtMajang();                                  // 获得下一个麻将，比如W2的下一个麻将就是W3
	[[nodiscard]] Majang getPrvMajang();                                  // 获得上一个麻将，比如W2的上一个麻将就是W1
};

#endif
/*** End of inlined file: Majang.h ***/


/*** Start of inlined file: Majang.cpp ***/
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

int Majang::parseTileType(string_view strExpr) {
	return getTileTypeFromChar(strExpr[0]);
}

int Majang::parseTileNum(string_view strExpr) {
	return strExpr[1] - '0';
}

TILE Majang::parseTile(string_view strExpr) {
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
Majang::Majang(string_view strExpr) {
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

void Majang::resetFromString(string_view strExpr) {
	innerType = parseTile(strExpr);
}

char Majang::getTileType() const {
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
	r=r+getTileType()+(char)getTileNum();
	return r;
}

Majang Majang::getNxtMajang() {
	//! 并不保证一定是合法的麻将，这一点在使用时需要注意！一般是在CHI中使用
	return Majang(innerType + 1);
}

Majang Majang::getPrvMajang() {
	//! 并不保证一定是合法的麻将，这一点在使用时需要注意！一般是在CHI中使用
	return Majang(innerType - 1);
}

/*** End of inlined file: Majang.cpp ***/


/*** Start of inlined file: StateContainer.h ***/
//#pragma once

#ifndef STATECONTAINER_H
#define STATECONTAINER_H

#include <valarray>
#include <algorithm>

// 使用Majang类

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
	valarray<Majang> inHand;           // 用于存储手牌
	valarray<Majang> flowerTilesOf[4]; // 用于存储花牌，分别对应4个玩家
	int curTurnPlayer;                  // 当前是哪个玩家的回合
	valarray<Majang> chiOf[4];         // 某个玩家鸣牌中的所有“吃”,存放中间那张牌即可
	valarray<Majang> pengOf[4];        // 某个玩家鸣牌中的所有“碰”，存放其中一张即可（因为三张一模一样
	valarray<Majang> gangOf[4];        // 某个玩家鸣牌中的所有“杠”，存放其中一张即可
//    valarray<Majang> discards;       // 用于存放弃牌堆
	valarray<Majang> tilePlayedOf[4];  // 用于记录某个玩家曾经都打出过哪些卡牌，无论是否被吃、碰还是杠
	int secretGangCntOf[4]{};           // 用于记录"暗杠"的数量，通过输入数据我们可以判断出某名玩家有几个暗杠，但我们不知道暗杠的是什么
	// 下面这个lastPlayed还没确定好到底怎么用，想好的时候再改吧
	Majang lastPlayed;                 // 用于记录上个回合被打出的麻将牌，如果不是麻将牌类型的话则为其他操作（具体见RequestReader::readRequest
	int tileLeft[70];                   // 用于记录各种类型牌所剩余的没出现的数量
	int totalLeft;                      // 没出现过的牌的总数（初始144）
	int inHandCnt[4];                   // 用于记录四名玩家的手牌数量(虽然不知道有没有用)

public:
	static int quan;                    // 圈风。因为在一把botzone游戏中，只考虑国标麻将的一局游戏，所以圈风应该是不变的

	explicit StateContainer(int curP=0, int curT=0);
	StateContainer(const StateContainer& other);

	[[nodiscard]] valarray<Majang>& getInHand();                               // 获取手牌
	[[nodiscard]] valarray<Majang>& getFlowerTilesOf(int idx);                 // 获取花牌
	[[nodiscard]] valarray<Majang>& getChiOf(int idx);                         // 获取鸣牌中的“吃"
	[[nodiscard]] valarray<Majang>& getPengOf(int idx);                        // 获取鸣牌中的“碰"
	[[nodiscard]] valarray<Majang>& getGangOf(int idx);                        // 获取鸣牌中的“杠”
//    [[nodiscard]] valarray<Majang>& getDiscards();                             // 获取弃牌堆
	[[nodiscard]] valarray<Majang>& getTilePlayedOf(int idx);                  // 获取某名玩家打过的所有牌

	[[nodiscard]] const valarray<Majang>& getInHand() const;                   //  获取手牌的常引用，下同上
	[[nodiscard]] const valarray<Majang>& getFlowerTilesOf(int idx) const;
	[[nodiscard]] const valarray<Majang>& getChiOf(int idx) const;
	[[nodiscard]] const valarray<Majang>& getPengOf(int idx) const;
	[[nodiscard]] const valarray<Majang>& getGangOf(int idx) const;
//    [[nodiscard]] const valarray<Majang>& getDiscards() const;
	[[nodiscard]] const valarray<Majang>& getTilePlayedOf(int idx) const;

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
#include <cassert>

StateContainer::StateContainer(int curP, int curT) :  curPosition(curP), inHand(13), curTurnPlayer(curT), totalLeft(144) {
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

valarray<Majang> &StateContainer::getInHand() { return inHand; }
valarray<Majang> &StateContainer::getFlowerTilesOf(int idx) { return flowerTilesOf[idx]; }
valarray<Majang> &StateContainer::getChiOf(int idx) { return chiOf[idx]; }
valarray<Majang> &StateContainer::getPengOf(int idx) { return pengOf[idx]; }
valarray<Majang> &StateContainer::getGangOf(int idx) { return gangOf[idx]; }
//valarray<Majang> &StateContainer::getDiscards() { return discards; }
valarray<Majang> &StateContainer::getTilePlayedOf(int idx) { return tilePlayedOf[idx]; }

const valarray<Majang> &StateContainer::getInHand() const { return inHand; }
const valarray<Majang> &StateContainer::getFlowerTilesOf(int idx) const { return flowerTilesOf[idx]; }
const valarray<Majang> &StateContainer::getChiOf(int idx) const { return chiOf[idx]; }
const valarray<Majang> &StateContainer::getPengOf(int idx) const { return pengOf[idx]; }
const valarray<Majang> &StateContainer::getGangOf(int idx) const { return gangOf[idx]; }
//const valarray<Majang> &StateContainer::getDiscards() const { return discards; }
const valarray<Majang> &StateContainer::getTilePlayedOf(int idx) const { return tilePlayedOf[idx]; }

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
//#pragma once

#ifndef REQUESTREADER_H
#define REQUESTREADER_H

#include <cstdio>
#include <cctype>
#include <string>
#include <cstring>
#include <valarray>
#include <cassert>

#include "MahjongGB/MahjongGB.h"

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
				readIn(state.getInHand()[i]);
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
			valarray<Majang>& tmpInHand = state.getInHand();
			int pos = tmpInHand.size();
			tmpInHand.resize(pos+1);
			readIn(tmpInHand[pos]);
			state.setLastPlayed("D6"); // D6 -> Draw!
			state.incInHandCntOf(state.getCurPosition());
			state.setCurTurnPlayer(state.getCurPosition());
			state.decTileLeft(tmpInHand[pos]);
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
				valarray<Majang> &tmpHana = state.getFlowerTilesOf(playerID);
				int pos = tmpHana.size();
				tmpHana.resize(pos + 1);
				readIn(tmpHana[pos]);
				state.decTileLeft(tmpHana[pos]);
				state.setLastPlayed("D8");  // D8 -> 补花（8 => HAna)
			} else if (op == "DRAW") {
				ret += 1;
				state.incInHandCntOf(playerID);
				state.setLastPlayed("D0");  // D0 -> 其他玩家抽牌
			} else if (op == "PLAY") {
				Majang tmpPlayed; readIn(tmpPlayed);
				state.setLastPlayed(tmpPlayed);
				state.decInHandCntOf(playerID);
				valarray<Majang>& tmpTilePlayed = state.getTilePlayedOf(playerID);
				int pos = tmpTilePlayed.size();
				tmpTilePlayed.resize(pos + 1);
				tmpTilePlayed[pos] = tmpPlayed;
				state.decTileLeft(tmpPlayed);
				if(playerID == state.getCurPosition()) {
					// 是我们打出的这张牌,这时需要从我们的手牌中去除这张牌
					state.deleteFromInHand(tmpPlayed);
				}
				ret += 2;
			} else if (op == "PENG") {
				Majang tmpPlayed; readIn(tmpPlayed);
				Majang pengTile = state.getLastPlayed();   // 碰的牌为上一回合打出的牌
				valarray<Majang>& tmpPengOf = state.getPengOf(playerID);
				int pos = tmpPengOf.size();
				tmpPengOf.resize(pos + 1);
				tmpPengOf[pos] = tmpPlayed;
				state.decTileLeft(pengTile);    // 被碰的牌又会打出两张
				state.decTileLeft(pengTile);
				valarray<Majang>& tmpTilePlayed = state.getTilePlayedOf(playerID);
				pos = tmpTilePlayed.size();
				tmpTilePlayed.resize(pos + 1);
				tmpTilePlayed[pos] = tmpPlayed;
				state.decTileLeft(tmpPlayed);     // 打出的牌也是知道的
				state.setLastPlayed(tmpPlayed);
				state.setInHandCntOf(playerID, state.getInHandCntOf(playerID)-3);  // 减少了三张牌
				if(playerID == state.getCurPosition()) {
					// 是我们进行的碰的操作,这时需要从我们的手牌中去除这三张牌
					state.deleteFromInHand(pengTile);
					state.deleteFromInHand(pengTile);
					state.deleteFromInHand(tmpPlayed);
				}
				ret += 3;
			} else if (op == "CHI") {
				Majang tmpCHI, tmpPlayed;
				readIn(tmpCHI); readIn(tmpPlayed);
				valarray<Majang>& tmpChiOf = state.getChiOf(playerID);
				int pos = tmpChiOf.size();
				tmpChiOf.resize(pos + 1);
				tmpChiOf[pos] = tmpCHI;
				// 这里需要判断出该玩家为了吃打出来的是哪两张牌
				Majang tmpCHIprv = tmpCHI.getPrvMajang();
				Majang tmpCHInxt = tmpCHI.getNxtMajang();
				const Majang& lastPlayed = state.getLastPlayed();
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
				valarray<Majang>& tmpTilePlayed = state.getTilePlayedOf(playerID);
				pos = tmpTilePlayed.size();
				tmpTilePlayed.resize(pos + 1);
				tmpTilePlayed[pos] = tmpPlayed;
				state.decTileLeft(tmpPlayed);
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
					valarray<Majang>& tmpGangOf = state.getGangOf(playerID);
					int pos = tmpGangOf.size();
					tmpGangOf.resize(pos + 1);
					tmpGangOf[pos] = gangTile;
					// 因为要打出三张gangTile
					state.decTileLeft(gangTile);
					state.decTileLeft(gangTile);
					state.decTileLeft(gangTile);
					if(playerID == state.getCurPosition()) {
						state.deleteFromInHand(gangTile);
						state.deleteFromInHand(gangTile);
						state.deleteFromInHand(gangTile);
					}
				}
				ret += 5;
			} else if (op == "BUGANG") {
				Majang tmpBuGang; readIn(tmpBuGang);
				valarray<Majang>& tmpGangOf = state.getGangOf(playerID);
				int pos = tmpGangOf.size();
				tmpGangOf.resize(pos + 1);
				tmpGangOf[pos] = tmpBuGang;
				// 同时还要从碰中去除
				valarray<Majang>& tmpPengOf = state.getPengOf(playerID);
				int lim = tmpPengOf.size();
				for(int i=0; i<lim; i++) {
					if(tmpPengOf[i] == tmpBuGang) {
						swap(tmpPengOf[i], tmpPengOf[lim-1]);
						break;
					}
				}
				tmpPengOf.resize(lim-1);
				state.decTileLeft(tmpBuGang);
				if(playerID == state.getCurPosition()) {
					state.deleteFromInHand(tmpBuGang);
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
//#pragma once

#ifndef SCORECALCULATOR_H
#define SCORECALCULATOR_H

#include <string>
#include <cstring>
#include <vector>
#include <utility>

// 直接使用botzone上的内置算番器（因为我实在不知道怎么配置了
#ifdef _BOTZONE_ONLINE
#include "MahjongGB/MahjongGB.h"
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
		Majang winTile
	);

	//一副牌的番数得分
	static double MajangFanScore(
		vector<pair<string, Majang> > pack,
		vector<Majang> hand,
		int flowerCount,
		StateContainer state
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
//最终在决策时还应乘上出相应牌的风险系数(用于评估对手对该牌的需要程度)
double Calculator::MajangScoreCalculator(
	vector<pair<string, Majang> > pack,
	vector<Majang> hand,
	int flowerCount,
	StateContainer state
){
	//参数实际应按游戏回合分段，这里先随便写了一个
	int k1=0.5;    // 手牌得分所占权重
	int k2=0.3;    // 自摸番数得分所占权重
	int k3=0.2;    // 点炮番数得分所占权重
	double r1=MajangHandScore(pack,hand);
	double r2=MajangFanScore(pack,hand,flowerCount,state);
	//计算点炮番数得分时，出牌的概率应考虑到博弈，还没有想清楚，先用自摸胡的算法计算点炮胡
	return r1*k1+r2*(k2+k3);
}

//参数c是用来使番数得分与手牌得分的数值相当
double Calculator::FanScoreCalculator(
	vector<pair<string, Majang> > pack,//似乎可以直接用两位整数直接作为代表Majang的参数，从而节省时间与空间
	vector<Majang> hand,//似乎可以直接用两位整数直接作为代表Majang的参数，从而节省时间与空间
	int flowerCount,
	Majang winTile
){
	double c=1;
	//将Majang类调整为适用于算番器的接口
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
	auto re=MahjongFanCalculator(p,h,winTile.getTileString(),1,flowerCount,1,0,0,0,0);//算番器中有许多我未理解的参数,先用0代入——wym
	int r=0;
	for(unsigned int i=0;i<re.size();i++) r+=re[i].first;//这里暂且暴力地以求和的方式作为番数得分的计算公式
	return r*c;
}

double Calculator::MajangFanScore(
	vector<pair<string, Majang> > pack,
	vector<Majang> hand,
	int flowerCount,
	StateContainer state
){
	double r=0;
	for(int i=11;i<=19;i++){
		if(state.getTileLeft(i)){
			r+=(double)state.getTileLeft(i)/state.getTotalLeft()*FanScoreCalculator(pack,hand,flowerCount,Majang(i));
		}
	}
	for(int i=21;i<=29;i++){
		if(state.getTileLeft(i)){
			r+=(double)state.getTileLeft(i)/state.getTotalLeft()*FanScoreCalculator(pack,hand,flowerCount,Majang(i));
		}
	}
	for(int i=31;i<=39;i++){
		if(state.getTileLeft(i)){
			r+=(double)state.getTileLeft(i)/state.getTotalLeft()*FanScoreCalculator(pack,hand,flowerCount,Majang(i));
		}
	}
	for(int i=41;i<=44;i++){
		if(state.getTileLeft(i)){
			r+=(double)state.getTileLeft(i)/state.getTotalLeft()*FanScoreCalculator(pack,hand,flowerCount,Majang(i));
		}
	}
	for(int i=51;i<=53;i++){
		if(state.getTileLeft(i)){
			r+=(double)state.getTileLeft(i)/state.getTotalLeft()*FanScoreCalculator(pack,hand,flowerCount,Majang(i));
		}
	}
	for(int i=61;i<=68;i++){
		if(state.getTileLeft(i)){
			StateContainer newstate=state;//摸到花牌后state应发生修改,应在StateContainer.h里提供相应的修改方法——wym
//            newstate.getTileLeft(i)--;
//            newstate.getTotalLeft()--;
			newstate.decTileLeft(i);
			r+=(double)state.getTileLeft(i)/state.getTotalLeft()*MajangFanScore(pack,hand,flowerCount+1,newstate);
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
			if(i>=43) singleValue+=tileAmount[i-2]*1;
			if(i>=42) singleValue+=tileAmount[i-1]*2;
			if(i<=42) singleValue+=tileAmount[i+2]*1;
			if(i<=43) singleValue+=tileAmount[i+1]*2;
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
			if(i>=53) singleValue+=tileAmount[i-2]*1;
			if(i>=52) singleValue+=tileAmount[i-1]*2;
			if(i<=51) singleValue+=tileAmount[i+2]*1;
			if(i<=52) singleValue+=tileAmount[i+1]*2;
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
//#pragma once

#ifndef RESPONSEOUTPUT_H
#define RESPONSEOUTPUT_H

#include <string>
#include <cstring>
#include <vector>

using namespace std;

class Output{
public:
	static void Response(StateContainer state,int request);     //由局面状态(state)和上一步操作(request)得到输出
	static bool judgeHu(vector<pair<string,Majang> > pack,vector<Majang> hand,Majang winTile);   //判断是否胡了
	static bool judgeGang(int tileAmout[70],vector<pair<string,Majang> > pack,vector<Majang> hand,Majang newTile,StateContainer state,int status);    //判断能否杠,status=2表示为摸牌后，status=3表示对手出牌后;如果能,再判断是否要杠
	static bool judgeBuGang(StateContainer state,vector<pair<string,Majang> > pack,vector<Majang> hand,Majang newTile);   //摸牌后判断能否补杠,如果能,再判断是否要杠
	static bool judgePeng(int tileAmout[70],Majang newTile);    //对手出牌后判断能否碰
	static int judgeChi(int tileAmout[70],Majang newTile);     //对手出牌后判断能否吃,返回值1,2,3分别表示表示吃的牌是组成刻子中的第1,2,3张.
	static const pair<double,Majang> getBestPlay(StateContainer state,vector<pair<string,Majang> > pack,vector<Majang> hand);   //返回最优的出牌及此时的评估值
	static const Majang getBestCP(StateContainer state,vector<pair<string,Majang> > pack,vector<Majang> hand,Majang newTile,int pos); //判断是否要吃(c)碰(p),若要则返回之后打出的Majang,否则Majang值为1;pos为0表示要进行的操作为碰或杠,否则表示吃时newTile的位置
};

#endif
/*** End of inlined file: ResponseOutput.h ***/


/*** Start of inlined file: ResponseOutput.cpp ***/
void Output::Response(StateContainer state,int request){

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
		if(judgeHu(pack,hand,hand.back())){
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
	else if(request==32||request==33||request==34){
		Majang lastTile=state.getLastPlayed();//被打出的牌
		int chi=judgeChi(tileAmount,lastTile);
		//HU
		if(judgeHu(pack,hand,lastTile)){
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
		else if(chi){
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
	else if(request==36){
		if(judgeHu(pack,hand,state.getLastPlayed())){
			printf("HU");
		}
	}

	//其余情况直接输出"pass"即可
	else{
		printf("PASS");
	}
}

bool Output::judgeHu(
	vector<pair<string,Majang> > pack,
	vector<Majang> hand,
	//! 优化? The parameter 'winTile' is copied for each invocation but only used as a const reference; consider making it a const reference
	Majang winTile
){
	//再次转换接口(可优化)
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
	auto re=MahjongFanCalculator(p,h,winTile.getTileString(),1,0,0,0,0,0,0);//此时不用考虑补花
	int r=0;
	for(unsigned int i=0;i<re.size();i++) r+=re[i].first;
	return r >= 8;  // 这里简化了一下
}

int Output::judgeChi(
	int TileAmount[70],
	Majang newTile
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
	Majang newTile
){
	if(tileAmout[newTile.getTileInt()]==2) return true;
	else return false;
}

bool Output::judgeGang(
	int tileAmout[70],
	vector<pair<string,Majang> > pack,
	vector<Majang> hand,
	Majang newTile,
	StateContainer state,
	int status
){
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
	Majang newTile
){
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
	Majang newTile,
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
			while(k1&&k2&&i<hand.size()){
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
			while(k1&&k2&&i<hand.size()){
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
			while(k1&&k2&&i<hand.size()){
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

int StateContainer::quan=0;
int main() {
	int turnID; Reader::readIn(turnID);
	StateContainer basicState;
	for(int i=1; i<turnID; i++) {
		Reader::readRequest(basicState);
	}
	Output::Response(basicState, Reader::readRequest(basicState));
	return 0;
}
