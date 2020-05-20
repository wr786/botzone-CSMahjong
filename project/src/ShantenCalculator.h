
#pragma once

#ifndef Shanten_Calculator_H
#define Shanten_Calculator_H

#ifndef _PREPROCESS_ONLY
// #include <fstream>
// #include <vector>
// #include <algorithm>
// #include <numeric>
#include <bits/stdc++.h>
#include <sys/stat.h>
#endif

#ifdef _BOTZONE_ONLINE
#ifndef _PREPROCESS_ONLY
#include "MahjongGB/MahjongGB.h"
#include "stringify.cpp"
#include "tile.h"
#include "shanten.h"
#endif
#else
#include "../utils/MahjongGB/MahjongGB.h"
#include "../utils/ChineseOfficialMahjongHelper/Classes/mahjong-algorithm/stringify.cpp"
#endif

using TileTableT = mahjong::tile_table_t;
using UsefulTableT = mahjong::useful_table_t;
using TileT = mahjong::tile_t;

inline bool file_exists(const char name[]) {
    struct stat buffer;
    return stat(name,&buffer)==0;
}

int CountUsefulTiles(const TileTableT& used_table, const UsefulTableT& useful_table) {
    int cnt = 0;
    for (int i = 0; i < 34; ++i) {
        TileT t = mahjong::all_tiles[i];
        if (useful_table[t]) {
            cnt += 4 - used_table[t];
        }
    }
    return cnt;
}

void ShantenTest()
{
    auto str = "[111m]5m12p1569sSWP";

    using namespace mahjong;
    hand_tiles_t hand_tiles;
    tile_t serving_tile;
    long ret = string_to_tiles(str, &hand_tiles, &serving_tile);
    if (ret != 0) {
        printf("error at line %d error = %ld\n", __LINE__, ret);
        return;
    }

    char buf[20];
    ret = hand_tiles_to_string(&hand_tiles, buf, sizeof(buf));
    for (size_t i = 0; i < ret; i++) {
        cout << buf[i];
    }
    cout << endl;

    auto display = [](const hand_tiles_t* hand_tiles, useful_table_t& useful_table) {
        char buf[64];
        for (tile_t t = TILE_1m; t < TILE_TABLE_SIZE; ++t) {
            if (useful_table[t]) {
                tiles_to_string(&t, 1, buf, sizeof(buf));
                printf("%s ", buf);
            }
        }

        tile_table_t cnt_table;
        map_hand_tiles(hand_tiles, &cnt_table);

        printf("%d", CountUsefulTiles(cnt_table, useful_table));
    };

    puts(str);
    useful_table_t useful_table/* = {false}*/;
    int ret0;
    ret0 = thirteen_orphans_shanten(hand_tiles.standing_tiles, hand_tiles.tile_count, &useful_table);
    printf("13 orphans ===> %d shanten\n", ret0); // 十三幺
    if (ret0 != std::numeric_limits<int>::max()) display(&hand_tiles, useful_table);

    ret0 = seven_pairs_shanten(hand_tiles.standing_tiles, hand_tiles.tile_count, &useful_table);
    printf("7 pairs ===> %d shanten\n", ret0); // 七对
    if (ret0 != std::numeric_limits<int>::max()) display(&hand_tiles, useful_table);

    ret0 = honors_and_knitted_tiles_shanten(hand_tiles.standing_tiles, hand_tiles.tile_count, &useful_table);
    printf("honors and knitted tiles ===> %d shanten\n", ret0); // 全不靠
    if (ret0 != std::numeric_limits<int>::max()) display(&hand_tiles, useful_table);

    ret0 = knitted_straight_shanten(hand_tiles.standing_tiles, hand_tiles.tile_count, &useful_table);
    printf("knitted straight in basic form ===> %d shanten\n", ret0); // 组合龙
    if (ret0 != std::numeric_limits<int>::max()) display(&hand_tiles, useful_table);
    puts("\n");

    ret0 = basic_form_shanten(hand_tiles.standing_tiles, hand_tiles.tile_count, &useful_table);
    printf("basic form ===> %d shanten\n", ret0); // 普通情形
    if (ret0 != std::numeric_limits<int>::max()) display(&hand_tiles, useful_table);
    puts("\n");
}

string tileToStr(const Majang& t)
{
    auto& h = t;
    auto tileType = TILE_T(h.getTileInt() / 10);
    string s;
    switch (tileType) {
    case WANN:
    case BING:
    case TIAO:
        s.push_back('0' + h.getTileNum());
    }
    switch (tileType) {
    case WANN: s += 'm'; break;
    case BING: s += 'p'; break;
    case TIAO: s += 's'; break;
    case FENG:
        switch (h.getTileNum()) {
        case 1:
            return "E";
        case 2:
            return "S";
        case 3:
            return "W";
        case 4:
            return "N";
        }
    case JIAN:
        switch (h.getTileNum()) {
        case 1:
            return "C";
        case 2:
            return "F";
        case 3:
            return "P";
        }
    }
    return s;
}

int ComplicatedShantenCalc(const vector<pair<string, Majang> >& pack,
    const vector<Majang>& hand
){
    int shanten = std::numeric_limits<int>::max();

    using namespace mahjong;
    hand_tiles_t hand_tiles;
    tile_t serving_tile;

#pragma region 转换成字符串
    string s;
    for (size_t i = 0; i < pack.size(); i++) {
        auto& m = pack[i].second;
        auto& t = pack[i].first;
        auto tileType = TILE_T(m.getTileInt() / 10);
        s += '[';
        if (t == "CHI") {
            s += tileToStr(m.getPrvMajang());
            s += tileToStr(m);
            s += tileToStr(m.getNxtMajang());
        }
        else if (t == "PENG" || t == "GANG") {
            s += tileToStr(m);
            s += tileToStr(m);
            s += tileToStr(m);
            if (t == "GANG") {
                s += tileToStr(m);
            }
        }
        s += ']';
    }
    for (size_t i = 0; i < hand.size(); i++) {
        s += tileToStr(hand[i]);
    }
#pragma endregion

#pragma region 字符串再转换成库中的表示形式
    size_t len = s.size();

    pack_t packs[4];
    intptr_t pack_cnt = 0;
    tile_t standing_tiles[14];
    intptr_t standing_cnt = 0;

    bool in_brackets = false;
    tile_t temp_tiles[14];
    intptr_t temp_cnt = 0;
    intptr_t max_cnt = 14;
    uint8_t offer = 0;

    tile_table_t cnt_table = { 0 };

    const char* p = s.c_str();
    while (char c = *p) {
        const char* q;
        switch (c) {
        case ',': {
            offer = static_cast<uint8_t>(*++p - '0');
            q = ++p;
            break;
        }
        case '[': {  // 开始一组副露
            if (temp_cnt > 0) {  // 处理[]符号外面的牌
                // 放到立牌中
                memcpy(&standing_tiles[standing_cnt], temp_tiles, temp_cnt * sizeof(tile_t));
                standing_cnt += temp_cnt;
                temp_cnt = 0;
            }

            q = ++p;
            in_brackets = true;
            offer = 0;
            max_cnt = 4;  // 副露的牌组最多包含4张牌
            break;
        }
        case ']': {  // 结束一副副露
            // 生成副露
            intptr_t ret = make_fixed_pack(temp_tiles, temp_cnt, &packs[pack_cnt], offer);
            if (ret < 0) {
                return ret;
            }

            q = ++p;
            temp_cnt = 0;
            in_brackets = false;
            ++pack_cnt;
            max_cnt = 14 - standing_cnt - pack_cnt * 3;  // 余下立牌数的最大值
            break;
        }
        default: {  // 牌
            // 解析max_cnt张牌
            intptr_t ret = parse_tiles_impl(p, temp_tiles, max_cnt, &temp_cnt);
            // 对牌打表
            for (intptr_t i = 0; i < temp_cnt; ++i) {
                ++cnt_table[temp_tiles[i]];
            }
            q = p + ret;
            break;
        }
        }
        p = q;
    }

    max_cnt = 14 - pack_cnt * 3;
    if (temp_cnt > 0) {  // 处理[]符号外面的牌
        // 放到立牌中
        memcpy(&standing_tiles[standing_cnt], temp_tiles, temp_cnt * sizeof(tile_t));
        standing_cnt += temp_cnt;
    }

    // 无错误时再写回数据
    tile_t last_tile = 0;
    if (standing_cnt == max_cnt) {
        memcpy(hand_tiles.standing_tiles, standing_tiles, (max_cnt - 1) * sizeof(tile_t));
        hand_tiles.tile_count = max_cnt - 1;
        last_tile = standing_tiles[max_cnt - 1];
    }
    else {
        memcpy(hand_tiles.standing_tiles, standing_tiles, standing_cnt * sizeof(tile_t));
        hand_tiles.tile_count = standing_cnt;
    }

    memcpy(hand_tiles.fixed_packs, packs, pack_cnt * sizeof(pack_t));
    hand_tiles.pack_count = pack_cnt;
    serving_tile = last_tile;
#pragma endregion

    useful_table_t useful_table = {false};
    int ret0;
    ret0 = thirteen_orphans_shanten(hand_tiles.standing_tiles, hand_tiles.tile_count, &useful_table);
    shanten = min(shanten, ret0);

    ret0 = seven_pairs_shanten(hand_tiles.standing_tiles, hand_tiles.tile_count, &useful_table);
    shanten = min(shanten, ret0);

    ret0 = honors_and_knitted_tiles_shanten(hand_tiles.standing_tiles, hand_tiles.tile_count, &useful_table);
    shanten = min(shanten, ret0);

    ret0 = knitted_straight_shanten(hand_tiles.standing_tiles, hand_tiles.tile_count, &useful_table);
    shanten = min(shanten, ret0);

    ret0 = basic_form_shanten(hand_tiles.standing_tiles, hand_tiles.tile_count, &useful_table);
    shanten = min(shanten, ret0);

    return shanten;
}

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
// h 不会是花牌
Majang MahjongToMajang(mahjong::tile_t h) {
    using namespace mahjong;
    auto tileType = h / 16;
    auto num = h % 16;
    int ret = 0;
    switch (tileType)
    {
    case 1:
    case 2:
    case 3:
        ret = num;
        break;
    }
    switch (tileType)
    {
    case 1:
        ret += WANN * 10;
        break;
    case 2:
        ret += TIAO * 10;
        break;
    case 3:
        ret += BING * 10; 
        break;
    case 4:
        switch (h)
        {
        case TILE_E:
            ret = FENG * 10 + 1;
            break;
        case TILE_S:
            ret = FENG * 10 + 2;
            break;
        case TILE_W:
            ret = FENG * 10 + 3;
            break;
        case TILE_N:
            ret = FENG * 10 + 4;
            break;
        case TILE_C:
            ret = JIAN * 10 + 1;
            break;
        case TILE_F:
            ret = JIAN * 10 + 2;
            break;
        case TILE_P:
            ret = JIAN * 10 + 3;
            break;
        default:
            assert(false);
        }
        break;
    default:
        assert(false);
    }
    return Majang(ret);
}

mahjong::tile_t MajangToMahjong(const Majang& h){
    using namespace mahjong;
    auto tileType = TILE_T(h.getTileInt() / 10);
    tile_t ret = 0;
    switch (tileType) {
    case WANN:
    case BING:
    case TIAO:
        ret = h.getTileNum();
    }
    switch (tileType) {
    case WANN: ret |= 0x10; break;
    case BING: ret |= 0x30; break;
    case TIAO: ret |= 0x20; break;
        // SetSuitForNumbered(tileType << 2); break;
    case FENG:
        switch (h.getTileNum()) {
        case 1:
            ret = TILE_E; break;
        case 2:
            ret = TILE_S; break;
        case 3:
            ret = TILE_W; break;
        case 4:
            ret = TILE_N; break;
        default:
            assert(false);
        }
        break;
    case JIAN:
        switch (h.getTileNum()) {
        case 1:
            ret = TILE_C; break;
        case 2:
            ret = TILE_F; break;
        case 3:
            ret = TILE_P; break;
        default:
            assert(false);
        }
        break;
    }
    return ret;
}

void ClearTable(mahjong::useful_table_t& ut) {
    memset(ut, 0, sizeof(bool) * 72);
}

int CountTable(mahjong::useful_table_t& ut) {
    int etc = 0;
    for (auto tile : ut)
        if (tile)
            etc++;
    return etc;
}


double ProbabilityCalc(const StateContainer& state,
    const Majang& aim
){
    const int playerIdx = state.getCurTurnPlayer();

    int OtherMingTilesCnt = 0;
    for (int i = 0; i < 4; ++i) {
        if (i != playerIdx) {
            // 他人鸣牌总数
            OtherMingTilesCnt += state.getPengOf(i).size() * 3;
            OtherMingTilesCnt += state.getChiOf(i).size() * 3;
            OtherMingTilesCnt += state.getGangOf(i).size() * 4;
        }
    }
    int allSecretCnt = 136 - OtherMingTilesCnt - 14;

    int thisMjCnt = 0;
    auto& MyMj = state.getInHand();
    for (auto& mj : MyMj) {
        // 自己手中的该麻将
        if (mj == aim)
            thisMjCnt++;
    }
    for (int i = 0; i < 4; ++i) {
        if (i != playerIdx) {
            // 他人鸣牌中的该麻将
            for (auto& mj : state.getPengOf(i)) {
                if (mj == aim)
                    thisMjCnt += 3;
            }
            for (auto& mj : state.getChiOf(i)) {
                if (mj == aim
                    || mj.getPrvMajang() == aim
                    || mj.getNxtMajang() == aim) {
                    thisMjCnt++;
                }
            }
            for (auto& mj : state.getGangOf(i)) {
                if (mj == aim)
                    thisMjCnt += 4;
            }
        }
    }

    double pRet = (4 - thisMjCnt) / (double)allSecretCnt;
    return pRet;
}

// 这是单层的，改进空间是升级成多层
double SimilarityCalc(const StateContainer& state,
    const UsefulTableT& aim
){
    using namespace mahjong;
    vector<Majang> vct;
    for (tile_t i = 0; i < TILE_TABLE_SIZE; ++i)
    {
        if (aim[i])
        {
            auto mj = MahjongToMajang(i);
            vct.push_back(mj);
        }
    }
    double sim = 0;
    for (size_t i = 0; i < vct.size(); i++)
    {
        sim += ProbabilityCalc(state, vct[i]);
    }
    return sim;
}

double SimilarityCalc(const StateContainer& state,
    const int aim[70]
){

    vector<Majang> vct;
    for (int i = 0; i < 70; ++i)
    {
        if (aim[i])
        {
            auto mj = Majang(i);
            vct.push_back(mj);
        }
    }
    double sim = 0;
    for (size_t i = 0; i < vct.size(); i++)
    {
        sim += ProbabilityCalc(state, vct[i]);
    }
    return sim;
}

pair<mahjong::tile_t,pair<int,double> > ShantenJudge(
    const vector<pair<string, Majang> >& pack,
    const vector<Majang>& hand,
    const StateContainer& state,
    mahjong::useful_table_t useful_table = nullptr
){
    using namespace mahjong;

    hand_tiles_t hand_tiles; // 牌，包括standing_tiles和fixed_packs
    // tile_t serving_tile;

    pack_t packs[4];
    intptr_t pack_cnt = 0;
    tile_t standing_tiles[14];
    intptr_t standing_cnt = 0;

    // tile_table_t cnt_table = { 0 };

    const int offer = 0; // const 0

    for (size_t i = 0; i < pack.size(); i++) {
        auto& m = pack[i].second;
        auto& t = pack[i].first;
        auto tileType = TILE_T(m.getTileInt() / 10);
        auto tt = MajangToMahjong(m);
        if (t == "CHI") {
            packs[pack_cnt] = make_pack(offer, PACK_TYPE_CHOW, tt);
        }
        else if (t == "PENG") {
            packs[pack_cnt] = make_pack(offer, PACK_TYPE_PUNG, tt);
        }
        else if (t == "GANG") {
            packs[pack_cnt] = make_pack(offer, PACK_TYPE_KONG, tt);
        }
        ++pack_cnt;
    }

    for (size_t i = 0; i < hand.size(); i++) {
        standing_tiles[standing_cnt] = MajangToMahjong(hand[i]);
        ++standing_cnt;
    }


    memcpy(hand_tiles.standing_tiles, standing_tiles, (standing_cnt) * sizeof(tile_t));
    hand_tiles.tile_count = standing_cnt;

    memcpy(hand_tiles.fixed_packs, packs, pack_cnt * sizeof(pack_t));
    hand_tiles.pack_count = pack_cnt;

    useful_table_t useful_table_ret = { false };
    useful_table_t temp_table = { false };
    int ret0;
    int effectiveTileCount = 0;
    double similarity= 0;
    tile_t form_flag=0x01;

    int ret_shanten = std::numeric_limits<int>::max();

    auto Check = [&](tile_t cur_form_flag) -> void {
        if (ret0 == std::numeric_limits<int>::max())
            return;
        if (ret0 < ret_shanten) {
            // 上听数小的，直接覆盖数据
            ret_shanten = ret0;
            memcpy(useful_table_ret, temp_table, sizeof(useful_table_ret));
            double cur_similarity=SimilarityCalc(state, useful_table_ret);
            form_flag=cur_form_flag;
            similarity=cur_similarity;
        }
        else if (ret_shanten == ret0) {
            // 上听数相等的，选择Similarity小
            double cur_similarity=SimilarityCalc(state, useful_table_ret);
            if(cur_similarity<similarity){
                similarity=cur_similarity;
                memcpy(useful_table_ret, temp_table, sizeof(useful_table_ret));
                form_flag=cur_form_flag;
            }
        }
    };

    // 注意：无有效tile时有的函数有时会置useful_table为全1而不是全0

    /*
    #define FORM_FLAG_BASIC_FORM                0x01  ///< 基本和型
    #define FORM_FLAG_SEVEN_PAIRS               0x02  ///< 七对
    #define FORM_FLAG_THIRTEEN_ORPHANS          0x04  ///< 十三幺
    #define FORM_FLAG_HONORS_AND_KNITTED_TILES  0x08  ///< 全不靠
    #define FORM_FLAG_KNITTED_STRAIGHT          0x10  ///< 组合龙   
    #define FORM_FLAG_ALL                       0xFF  ///< 全部和型
    */
    ret0 = thirteen_orphans_shanten(hand_tiles.standing_tiles, hand_tiles.tile_count, &temp_table);
    Check(0x04);

    ret0 = seven_pairs_shanten(hand_tiles.standing_tiles, hand_tiles.tile_count, &temp_table);
    Check(0x02);

    ret0 = honors_and_knitted_tiles_shanten(hand_tiles.standing_tiles, hand_tiles.tile_count, &temp_table);
    Check(0x08);

    ret0 = knitted_straight_shanten(hand_tiles.standing_tiles, hand_tiles.tile_count, &temp_table);
    Check(0x10);


    effectiveTileCount = CountTable(useful_table_ret);
    if (useful_table != nullptr)
        memcpy(useful_table, useful_table_ret, sizeof(useful_table_ret));

    return {form_flag,{ret_shanten,similarity}};    
}


// 返回值的first为shanten，second为effective tiles count
// useful_table_ret!=nullptr时作为out参数
// 我发现useful_table很重要啊 --DRZ
pair<int, int> ShantenCalc(
    const vector<pair<string, Majang> >& pack,
    const vector<Majang>& hand,
    mahjong::useful_table_t useful_table = nullptr,
    mahjong::tile_t form_flag=0x01
) {
    using namespace mahjong;

    hand_tiles_t hand_tiles; // 牌，包括standing_tiles和fixed_packs
    // tile_t serving_tile;

    pack_t packs[4];
    intptr_t pack_cnt = 0;
    tile_t standing_tiles[14];
    intptr_t standing_cnt = 0;

    // tile_table_t cnt_table = { 0 };

    const int offer = 0; // const 0

    for (size_t i = 0; i < pack.size(); i++) {
        auto& m = pack[i].second;
        auto& t = pack[i].first;
        auto tileType = TILE_T(m.getTileInt() / 10);
        auto tt = MajangToMahjong(m);
        if (t == "CHI") {
            packs[pack_cnt] = make_pack(offer, PACK_TYPE_CHOW, tt);
        }
        else if (t == "PENG") {
            packs[pack_cnt] = make_pack(offer, PACK_TYPE_PUNG, tt);
        }
        else if (t == "GANG") {
            packs[pack_cnt] = make_pack(offer, PACK_TYPE_KONG, tt);
        }
        ++pack_cnt;
    }

    for (size_t i = 0; i < hand.size(); i++) {

        /*
        auto& h = hand[i];
        auto tileType = TILE_T(h.getTileInt() / 10);
        switch (tileType) {
        case WANN:
        case BING:
        case TIAO:
            temp_tiles[tile_cnt++] = h.getTileNum();
        }
        switch (tileType) {
        case WANN: SetSuitForNumbered(0x10); break;
        case BING: SetSuitForNumbered(0x30); break;
        case TIAO: SetSuitForNumbered(0x20); break;
            // SetSuitForNumbered(tileType << 2); break;
        case FENG:
            switch (h.getTileNum()) {
            case 1:
                temp_tiles[tile_cnt++] = TILE_E; break;
            case 2:
                temp_tiles[tile_cnt++] = TILE_S; break;
            case 3:
                temp_tiles[tile_cnt++] = TILE_W; break;
            case 4:
                temp_tiles[tile_cnt++] = TILE_N; break;
            }
        case JIAN:
            switch (h.getTileNum()) {
            case 1:
                temp_tiles[tile_cnt++] = TILE_C; break;
            case 2:
                temp_tiles[tile_cnt++] = TILE_F; break;
            case 3:
                temp_tiles[tile_cnt++] = TILE_P; break;
            }
        }
        */

        // 对牌打表
        // for (intptr_t i = 0; i < temp_cnt; ++i) {
           // ++cnt_table[temp_tiles[i]];
        //}

        standing_tiles[standing_cnt] = MajangToMahjong(hand[i]);
        ++standing_cnt;
    }

    // 写入数据
    // tile_t last_tile = 0;
    // assert(standing_cnt == max_cnt);

    memcpy(hand_tiles.standing_tiles, standing_tiles, (standing_cnt) * sizeof(tile_t));
    hand_tiles.tile_count = standing_cnt;
    // last_tile = standing_tiles[max_cnt - 1];

    memcpy(hand_tiles.fixed_packs, packs, pack_cnt * sizeof(pack_t));
    hand_tiles.pack_count = pack_cnt;
    // serving_tile = last_tile;

    useful_table_t useful_table_ret = { false };
    useful_table_t temp_table = { false };
    int ret0;
    int effectiveTileCount = 0;

    int ret_shanten = std::numeric_limits<int>::max();

    auto Check = [&]() -> void {
        if (ret0 == std::numeric_limits<int>::max())
            return;
        if (ret0 < ret_shanten) {
            // 上听数小的，直接覆盖数据
            ret_shanten = ret0;
            memcpy(useful_table_ret, temp_table, sizeof(useful_table_ret));
        }
        else if (ret_shanten == ret0) {
            // 上听数相等的，合并有效牌
            std::transform(std::begin(useful_table_ret), std::end(useful_table_ret),
                std::begin(temp_table),
                std::begin(useful_table_ret),
                [](bool u, bool t) { return u || t; });
        }
    };

    // 注意：无有效tile时有的函数有时会置useful_table为全1而不是全0

    if(form_flag==0x04||form_flag==0x01){
        ret0 = thirteen_orphans_shanten(hand_tiles.standing_tiles, hand_tiles.tile_count, &temp_table);
        Check();
    }

    if(form_flag==0x02||form_flag==0x01){
        ret0 = seven_pairs_shanten(hand_tiles.standing_tiles, hand_tiles.tile_count, &temp_table);
        Check();
    }

    if(form_flag==0x08||form_flag==0x01){
        ret0 = honors_and_knitted_tiles_shanten(hand_tiles.standing_tiles, hand_tiles.tile_count, &temp_table);
        Check();
    }

    if(form_flag==0x10||form_flag==0x01){
        ret0 = knitted_straight_shanten(hand_tiles.standing_tiles, hand_tiles.tile_count, &temp_table);
        Check();
    }

    if(form_flag==0x01){
        ret0 = basic_form_shanten(hand_tiles.standing_tiles, hand_tiles.tile_count, &temp_table);
        Check();
    }

    effectiveTileCount = CountTable(useful_table_ret);
    if (useful_table != nullptr)
        memcpy(useful_table, useful_table_ret, sizeof(useful_table_ret));

    return { ret_shanten, effectiveTileCount };
}



struct specialShanten{
    int formFlag;//表示某一种番型
    string tileForm;//表示具体的牌组成
};
/*
Case 1:三色三步高
Case 2:三色三同顺
Case 3:花龙
Case 4:清龙
Case 5:一色三步高
*/
double k[8]={0,5.16,2.96,2.88,4.32,2.56};//权重（百局内胡的局数/100*番数）

//第一项表示得到的shanten数最小番型，第二项为shanten数，第三项为相似度
pair<specialShanten, pair<int,double> > specialShantenCalc(
    const vector<pair<string, Majang> >& pack,
    const vector<Majang>& hand,
    const StateContainer& state
) {
    int ntileAmount[70]={0};
    int useful_table[70];
    int tileAmount[70]={0};
    for(auto i:pack) ntileAmount[i.second.getTileInt()]++;
    for(auto i:hand) ntileAmount[i.getTileInt()]++;
    
    string input;
    specialShanten r;//用来标记现在是哪一种番型,比如1是三色三步高        
    int flag;
    int minShanten=5;
    double maxSimilarity=0;
    // bool try1 = file_exists("./data/specialShanten.txt");
    // bool try2 = file_exists("/data/specialShanten.txt");
    // bool try3 = file_exists(".\\data\\specialShanten.txt");
    // bool try4 = file_exists("./specialShanten.txt");
    // bool try5 = file_exists("..\\data\\specialShanten.txt");
    // cout << try1 << try2 << try3 << try4 << try5 << endl;
    freopen("./data/specialShanten.txt","r",stdin);

    while(true){    
        Reader::readIn(input);   
        if(input=="Over") {
            break;
        }
        memset(useful_table,0,sizeof(useful_table));
        memcpy(tileAmount,ntileAmount,70*4);
        int shanten=0;
        double similarity=0;
        if(input[0]=='C') {
            // flag=input[4]-'0';
            Reader::readIn(flag);
            continue;
        }
        else{
            for(int i=0;i<9;i++){
                int num=(input[i*2]-'0')*10+input[i*2+1]-'0';
                if(!tileAmount[num]){
                    shanten++;
                    useful_table[num]++;
                } else {
                    tileAmount[num]--;
                }
                if(shanten>=5) break;
            }
        }
        if(shanten>=5){continue;}
        similarity=SimilarityCalc(state,useful_table);
        if(shanten<minShanten){
            r.formFlag=flag;
            r.tileForm=input;
            minShanten=shanten;
            maxSimilarity=similarity;
        }
        else if(shanten==minShanten&&maxSimilarity*k[r.formFlag]<similarity*k[flag]){
            r.formFlag=flag;
            r.tileForm=input;
            minShanten=shanten;
            maxSimilarity=similarity;            
        }
        if(minShanten==0) break;
    }
    fclose(stdin);
    return {r,{minShanten,maxSimilarity}};
}

int specialShantenCalc(
    const vector<pair<string, Majang> >& pack,
    const vector<Majang>& hand,
    string target
) {
    int tileAmount[70]={0};
    int useful_table[70];
    for(auto i:pack) tileAmount[i.second.getTileInt()]++;
    for(auto i:hand) tileAmount[i.getTileInt()]++;

    int shanten=0;
    for(int i=0;i<9;i++){
        int num=(target[i*2]-'0')*10+target[i*2+1]-'0';
        if(!tileAmount[num]){
            shanten++;
            useful_table[num]++;
        } else {
            tileAmount[num]--;
        }
        if(shanten>=5) break;
    }   
    return shanten;
}

#endif // !Shanten_Calculator_H
