#pragma once

#ifndef MAHJONG_H
#define MAHJONG_H

// 为了节省内存，用一个int来存麻将的信息
// 由botzone所给的表示法：
// > “W4”表示“四万”，“B6”表示“六筒”，“T8”表示“8条”
// > “F1”～“F4”表示“东南西北”，“J1”～“J3”表示“中发白”，“H1”～“H8”表示“春夏秋冬梅兰竹菊”
// 注意到数字位最多只会出现1~9，所以可以用个位来存数字位
// 而以十位来存牌的种类，其中:
// 1 => W, 2 => B, 3 => T
// 4 => F, 5 => J, 6 => H
typedef int TILE;

class Mahjong {
private:
    TILE type;
public:
    // 这里应有不少实用的方法，有空再写（或者有个人来写也挺好的
};

#endif