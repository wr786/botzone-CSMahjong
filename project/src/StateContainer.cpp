#include "StateContainer.h"
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






