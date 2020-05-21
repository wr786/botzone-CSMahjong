
#pragma once

#ifndef Shanten_Calculator_H
#define Shanten_Calculator_H

#ifndef _PREPROCESS_ONLY
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <ctime>
#include <unordered_set>
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

const string innerTable[200] = {"Case1",
"111213222324333435",
"121314232425343536",
"131415242526353637",
"141516252627363738",
"151617262728373839",
"111213323334232425",
"121314333435242526",
"131415343536252627",
"141516353637262728",
"151617363738272829",
"212223121314333435",
"222324131415343536",
"232425141516353637",
"242526151617363738",
"252627161718373839",
"212223323334131415",
"222324333435141516",
"232425343536151617",
"242526353637161718",
"252627363738171819",
"313233121314232425",
"323334131415242526",
"333435141516252627",
"343536151617262728",
"353637161718272829",
"313233222324131415",
"323334232425141516",
"333435242526151617",
"343536252627161718",
"353637262728171819",
"Case2",
"111213212223313233",
"121314222324323334",
"131415232425333435",
"141516242526343536",
"151617252627353637",
"161718262728363738",
"171819272829373839",
"Case3",
"111213242526373839",
"111213272829343536",
"141516212223373839",
"141516272829313233",
"171819212223343536",
"171819242526313233",
"Case4",
"111213141516171819",
"212223242526272829",
"313233343536373839",
"Case5",
"111213121314131415",
"121314131415141516",
"131415141516151617",
"141516151617161718",
"212223222324232425",
"222324232425242526",
"232425242526252627",
"242526252627262728",
"313233323334333435",
"323334333435343536",
"333435343536353637",
"343536353637363738",
"111213131415151617",
"121314141516161718",
"212223232425252627",
"222324242526262728",
"313233333435353637",
"323334343536363738",
"Case6",
"111111222222333333",
"121212232323343434",
"131313242424353535",
"141414252525363636",
"151515262626373737",
"111111323232232323",
"121212333333242424",
"131313343434252525",
"141414353535262626",
"151515363636272727",
"212121121212333333",
"222222131313343434",
"232323141414353535",
"242424151515363636",
"252525161616373737",
"212121323232131313",
"222222333333141414",
"242424353535161616",
"252525363636171717",
"313131121212232323",
"323232131313242424",
"333333141414252525",
"343434151515262626",
"353535161616272727",
"313131222222131313",
"323232232323141414",
"333333242424151515",
"343434252525161616",
"353535262626171717",
"Case7",
"111213111213111213",
"121314121314121314",
"131415131415131415",
"141516141516141516",
"151617151617151617",
"212223212223212223",
"222324222324222324",
"232425232425232425",
"242526242526242526",
"252627252627252627",
"313233313233313233",
"323334323334323334",
"333435333435333435",
"343536343536343536",
"353637353637353637",
"Case8",
"111213121314131415141516",
"121314131415141516151617",
"131415141516151617161718",
"141516151617161718171819",
"212223222324232425242526",
"222324232425242526252627",
"232425242526252627262728",
"242526252627262728272829",
"313233323334333435343536",
"323334333435343536353637",
"333435343536353637363738",
"343536353637363738373839",
"111213131415151617171819",
"212223232425252627272829",
"313233333435353637373839",
"Over"};


unordered_map<int, unordered_set<string> > specialShantenForPack; 
// Case1
void specialShantenInit(){
    specialShantenForPack[111213].insert({"3233342324251","2223243334351"});
    specialShantenForPack[222324].insert({"1314153435361","3334351415161","3132331314151","1112133334351"});
    specialShantenForPack[333435].insert({"2223241415161","2425261516171","1213142425261","2122231213141","1112132223241","1415162526271"});
    specialShantenForPack[121314].insert({"2324253435361","2122233334351","3132332324251","3334352425261"});
    specialShantenForPack[232425].insert({"3435361516171","1112133233341","3233341415161","1415163536371","3132331213141","1213143435361"});
    specialShantenForPack[343536].insert({"2324251516171","1314152526271","1213142324251","2526271617181","2223241314151","1516172627281"});
    specialShantenForPack[131415].insert({"3435362526271","3132332223241","3233342425261","2223243435361","2425263536371","2122233233341"});
    specialShantenForPack[242526].insert({"1314153536371","1516173637381","1213143334351","3334351516171","3233341314151","3536371617181"});
    specialShantenForPack[353637].insert({"2324251415161","2627281718191","1415162627281","2425261617181","1314152425261","1617182728291"});
    specialShantenForPack[141516].insert({"2223243334351","2324253536371","3233342324251","2526273637381","3334352526271","3536372627281"});
    specialShantenForPack[252627].insert({"1617183738391","1314153435361","1415163637381","3637381718191","3435361617181","3334351415161"});
    specialShantenForPack[363738].insert({"1516172728291","1415162526271","2526271718191","2425261516171"});
    specialShantenForPack[151617].insert({"2324253435361","3637382728291","2425263637381","2627283738391","3435362627281","3334352425261"});
    specialShantenForPack[262728].insert({"3536371718191","1516173738391","3435361516171","1415163536371"});
    specialShantenForPack[373839].insert({"1516172627281","2526271617181"});
    specialShantenForPack[323334].insert({"1112132324251","2122231314151","1314152425261","2324251415161"});
    specialShantenForPack[272829].insert({"1516173637381","3536371617181"});
    specialShantenForPack[212223].insert({"3233341314151","1213143334351"});
    specialShantenForPack[161718].insert({"2425263536371","2526273738391","3435362526271","3536372728291"});
    specialShantenForPack[171819].insert({"2526273637381","3536372627281"});
    specialShantenForPack[313233].insert({"1213142324251","2223241314151"});
    // Case2
    specialShantenForPack[111213].insert({"2122233132332"});
    specialShantenForPack[212223].insert({"1112133132332"});
    specialShantenForPack[313233].insert({"1112132122232"});
    specialShantenForPack[121314].insert({"2223243233342"});
    specialShantenForPack[222324].insert({"1213143233342"});
    specialShantenForPack[323334].insert({"1213142223242"});
    specialShantenForPack[131415].insert({"2324253334352"});
    specialShantenForPack[232425].insert({"1314153334352"});
    specialShantenForPack[333435].insert({"1314152324252"});
    specialShantenForPack[141516].insert({"2425263435362"});
    specialShantenForPack[242526].insert({"1415163435362"});
    specialShantenForPack[343536].insert({"1415162425262"});
    specialShantenForPack[151617].insert({"2526273536372"});
    specialShantenForPack[252627].insert({"1516173536372"});
    specialShantenForPack[353637].insert({"1516172526272"});
    specialShantenForPack[161718].insert({"2627283637382"});
    specialShantenForPack[262728].insert({"1617183637382"});
    specialShantenForPack[363738].insert({"1617182627282"});
    specialShantenForPack[171819].insert({"2728293738392"});
    specialShantenForPack[272829].insert({"1718193738392"});
    specialShantenForPack[373839].insert({"1718192728292"});
    // Case3
    specialShantenForPack[111213].insert({"2425263738393","2728293435363"});
    specialShantenForPack[242526].insert({"1718193132333","1112133738393"});
    specialShantenForPack[373839].insert({"1112132425263","1415162122233"});
    specialShantenForPack[272829].insert({"1415163132333","1112133435363"});
    specialShantenForPack[343536].insert({"1112132728293","1718192122233"});
    specialShantenForPack[141516].insert({"2122233738393","2728293132333"});
    specialShantenForPack[212223].insert({"1718193435363","1415163738393"});
    specialShantenForPack[313233].insert({"1415162728293","1718192425263"});
    specialShantenForPack[171819].insert({"2425263132333","2122233435363"});
    // Case4
    specialShantenForPack[111213].insert({"1415161718194"});
    specialShantenForPack[141516].insert({"1112131718194"});
    specialShantenForPack[171819].insert({"1112131415164"});
    specialShantenForPack[212223].insert({"2425262728294"});
    specialShantenForPack[242526].insert({"2122232728294"});
    specialShantenForPack[272829].insert({"2122232425264"});
    specialShantenForPack[313233].insert({"3435363738394"});
    specialShantenForPack[343536].insert({"3132333738394"});
    specialShantenForPack[373839].insert({"3132333435364"});
    // Case5
    specialShantenForPack[111213].insert({"1314151516175","1213141314155"});
    specialShantenForPack[121314].insert({"1415161617185","1314151415165","1112131314155"});
    specialShantenForPack[131415].insert({"1112131213145","1213141415165","1112131516175","1415161516175"});
    specialShantenForPack[141516].insert({"1213141617185","1516171617185","1314151516175","1213141314155"});
    specialShantenForPack[151617].insert({"1415161617185","1112131314155","1314151415165"});
    specialShantenForPack[161718].insert({"1213141415165","1415161516175"});
    specialShantenForPack[212223].insert({"2223242324255","2324252526275"});
    specialShantenForPack[222324].insert({"2324252425265","2425262627285","2122232324255"});
    specialShantenForPack[232425].insert({"2122232223245","2122232526275","2223242425265","2425262526275"});
    specialShantenForPack[242526].insert({"2223242324255","2223242627285","2324252526275","2526272627285"});
    specialShantenForPack[252627].insert({"2324252425265","2425262627285","2122232324255"});
    specialShantenForPack[262728].insert({"2223242425265","2425262526275"});
    specialShantenForPack[313233].insert({"3233343334355","3334353536375"});
    specialShantenForPack[323334].insert({"3435363637385","3334353435365","3132333334355"});
    specialShantenForPack[333435].insert({"3132333233345","3132333536375","3435363536375","3233343435365"});
    specialShantenForPack[343536].insert({"3233343334355","3536373637385","3233343637385","3334353536375"});
    specialShantenForPack[353637].insert({"3435363637385","3334353435365","3132333334355"});
    specialShantenForPack[363738].insert({"3233343435365","3435363536375"});
    // Case6
    specialShantenForPack[111111].insert({"2222223333336","3232322323236"});
    specialShantenForPack[222222].insert({"3333331414146","3131311313136","1111113333336","1313133434346"});
    specialShantenForPack[333333].insert({"2424241515156","2222221414146","1414142525256","1212122424246","1111112222226","2121211212126"});
    specialShantenForPack[121212].insert({"3333332424246","3131312323236","2121213333336","2323233434346"});
    specialShantenForPack[232323].insert({"3131311212126","1212123434346","1111113232326","3232321414146","1414143535356"});
    specialShantenForPack[343434].insert({"1212122323236","2525251616166","1515152626266","2222221313136","1313132525256"});
    specialShantenForPack[131313].insert({"3434342525256","2424243535356","3131312222226","2222223434346","2121213232326","3232322424246"});
    specialShantenForPack[242424].insert({"3232321313136","3333331515156","3535351616166","1212123333336","1515153636366","1313133535356"});
    specialShantenForPack[353535].insert({"1414142626266","2626261717176","2323231414146","1616162727276","2424241616166","1313132424246"});
    specialShantenForPack[141414].insert({"3232322323236","2525253636366","2222223333336","3333332525256","2323233535356","3535352626266"});
    specialShantenForPack[252525].insert({"1414143636366","3434341616166","3636361717176","1616163737376","3333331414146","1313133434346"});
    specialShantenForPack[363636].insert({"1414142525256","2424241515156","2525251717176","1515152727276"});
    specialShantenForPack[151515].insert({"2626263737376","3333332424246","3636362727276","2424243636366","3434342626266"});
    specialShantenForPack[262626].insert({"1414143535356","1515153737376","3434341515156","3535351717176"});
    specialShantenForPack[373737].insert({"1515152626266","2525251616166"});
    specialShantenForPack[323232].insert({"2121211313136","1313132424246","2323231414146","1111112323236"});
    specialShantenForPack[272727].insert({"1515153636366","3535351616166"});
    specialShantenForPack[212121].insert({"3232321313136","1212123333336"});
    specialShantenForPack[161616].insert({"2525253737376","3535352727276","2424243535356","3434342525256"});
    specialShantenForPack[171717].insert({"3535352626266","2525253636366"});
    specialShantenForPack[313131].insert({"1212122323236","2222221313136"});
    // Case7
    specialShantenForPack[111213].insert({"1112131112137"});
    specialShantenForPack[121314].insert({"1213141213147"});
    specialShantenForPack[131415].insert({"1314151314157"});
    specialShantenForPack[141516].insert({"1415161415167"});
    specialShantenForPack[151617].insert({"1516171516177"});
    specialShantenForPack[212223].insert({"2122232122237"});
    specialShantenForPack[222324].insert({"2223242223247"});
    specialShantenForPack[232425].insert({"2324252324257"});
    specialShantenForPack[242526].insert({"2425262425267"});
    specialShantenForPack[252627].insert({"2526272526277"});
    specialShantenForPack[313233].insert({"3132333132337"});
    specialShantenForPack[323334].insert({"3233343233347"});
    specialShantenForPack[333435].insert({"3334353334357"});
    specialShantenForPack[343536].insert({"3435363435367"});
    specialShantenForPack[353637].insert({"3536373536377"});
    // Case8
    specialShantenForPack[111213].insert({"1314151516171718198","1213141314151415168"});
    specialShantenForPack[121314].insert({"1112131314151415168","1314151415161516178"});
    specialShantenForPack[131415].insert({"1415161516171617188","1112131213141415168","1213141415161516178","1112131516171718198"});
    specialShantenForPack[141516].insert({"1516171617181718198","1213141314151516178","1314151516171617188","1112131213141314158"});
    specialShantenForPack[151617].insert({"1415161617181718198","1314151415161617188","1112131314151718198","1213141314151415168"});
    specialShantenForPack[161718].insert({"1415161516171718198","1314151415161516178"});
    specialShantenForPack[171819].insert({"1415161516171617188","1112131314151516178"});
    specialShantenForPack[212223].insert({"2223242324252425268","2324252526272728298"});
    specialShantenForPack[222324].insert({"2122232324252425268","2324252425262526278"});
    specialShantenForPack[232425].insert({"2122232223242425268","2122232526272728298","2425262526272627288","2223242425262526278"});
    specialShantenForPack[242526].insert({"2223242324252526278","2324252526272627288","2526272627282728298","2122232223242324258"});
    specialShantenForPack[252627].insert({"2223242324252425268","2324252425262627288","2425262627282728298","2122232324252728298"});
    specialShantenForPack[262728].insert({"2324252425262526278","2425262526272728298"});
    specialShantenForPack[272829].insert({"2122232324252526278","2425262526272627288"});
    specialShantenForPack[313233].insert({"3233343334353435368","3334353536373738398"});
    specialShantenForPack[323334].insert({"3334353435363536378","3132333334353435368"});
    specialShantenForPack[333435].insert({"3435363536373637388","3132333536373738398","3233343435363536378","3132333233343435368"});
    specialShantenForPack[343536].insert({"3132333233343334358","3334353536373637388","3536373637383738398","3233343334353536378"});
    specialShantenForPack[353637].insert({"3132333334353738398","3334353435363637388","3435363637383738398","3233343334353435368"});
    specialShantenForPack[363738].insert({"3334353435363536378","3435363536373738398"});
    specialShantenForPack[373839].insert({"3435363536373637388","3132333334353536378"});
}
// Over

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
   // double pRet=state.getTileLeft(aim.getTileInt())/state.getTotalLeft();
    double pRet = (4 - thisMjCnt) / (double)allSecretCnt;
    return pRet;
}

// 这是单层的，改进空间是升级成多层
// 对于全不靠这些，当牌库中没有必要牌时，相似度应为0
double SimilarityCalc(const StateContainer& state,
    const UsefulTableT& aim,
    mahjong::tile_t form_flag=0x01
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
        if(form_flag==0x08&&vct[i].getTileInt()>=41&&state.getTileLeft(vct[i].getTileInt())==0){
            return 0;
        }
        sim += state.getTileLeft(vct[i].getTileInt())/(double)state.getTotalLeft();

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
        sim += state.getTileLeft(vct[i].getTileInt())/(double)state.getTotalLeft();
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
            double cur_similarity=SimilarityCalc(state, useful_table_ret,cur_form_flag);
            form_flag=cur_form_flag;
            similarity=cur_similarity;
        }
        else if (ret_shanten == ret0) {
            // 上听数相等的，选择Similarity小
            double cur_similarity=SimilarityCalc(state, useful_table_ret,cur_form_flag);
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
Case 4:清龙 (权重从4.32降低至3.5)
Case 5:一色三步高
Case 6:三色三节高
Case 7:一色三同顺
Case 8:一色四步高
*/

double k[20]={1,5.16,2.96,2.88,3.50,2.56,0.1024,0.0216,0.144};//权重（百局内胡的局数/100*番数）

//第一项为shanten数，第二项为相似度
 pair<int,double> specialShantenCalc(
    const vector<pair<string, Majang> >& pack,
    const vector<Majang>& hand,
    const StateContainer& state
) {
    int ntileAmount[70]={0};
    int tileAmount[70]={0};
    int useful_table[70]={0};
    int allCHI[10]={0};
    int chisum=0;
    for(auto i:pack) {
        if(i.first=="CHI"){
            //ntileAmount[i.second.getTileInt()]++;
            //ntileAmount[i.second.getTileInt()+1]++;
            //ntileAmount[i.second.getTileInt()-1]++;
            allCHI[chisum++]=(i.second.getTileInt()-1)*10000+(i.second.getTileInt())*100+(i.second.getTileInt()+1);
        }
        //else if(i.first=="PENG"){
        //    ntileAmount[i.second.getTileInt()]+=3;
        //}
        //else {
        //    ntileAmount[i.second.getTileInt()]+=4;
        //}
    }
    for(auto i:hand) ntileAmount[i.getTileInt()]++;

    string input;
    specialShanten r;//用来标记现在是哪一种番型,比如1是三色三步高        
    int flag;
    int minShanten=5;
    double maxSimilarity=0;
    double prt=100;
    //freopen("D://specialShanten.txt","r",stdin);
    // freopen("./data/specialShanten.txt","r",stdin);
    //clock_t start=clock();
    int idx = 0;
    if(chisum==0){
        while(true){    
            // Reader::readIn(input);        
            input = innerTable[idx++];
            if(input=="Over"){
                break;
            }
            memset(useful_table,0,sizeof(useful_table));
            memcpy(tileAmount,ntileAmount,70*4);
            int shanten=0;
            double similarity=0;
            if(input[0]=='C') {flag=input[4]-'0';continue;}
            else{
                int len = input.length();
                for(int i=0;i<len/2;i++){
                    int num=(input[i*2]-'0')*10+input[i*2+1]-'0';
                    if(!tileAmount[num]){
                        shanten++;
                        useful_table[num]++;
                    }
                    else{
                        tileAmount[num]--;
                    }
                    if(shanten>=5) break;
                }
            }
            if(shanten>=5||shanten>=hand.size()){continue;}
            similarity=SimilarityCalc(state,useful_table);
            /*double cnt = shanten - 1 - log(similarity)/k[flag];
            if(cnt<prt||shanten==0){
                prt=cnt;
                minShanten=shanten;
                maxSimilarity=similarity;
                r.formFlag=flag;
                r.tileForm=input;
            }
            */
            if(shanten<minShanten){
                minShanten=shanten;
                maxSimilarity=similarity;
            }
            else if(shanten==minShanten){
                maxSimilarity+=similarity*k[flag];            
            }
            if(minShanten==0) break;
        }
    }
    //如果已经有了一个吃,就围绕这个吃来打
    else if(chisum==1){            
        int myPack=allCHI[0];
        auto t=specialShantenForPack.find(myPack);
        if(t==specialShantenForPack.end()) return {100,0};;//找不到
        for(auto input: t->second){    
            // Reader::readIn(input);        
            flag=input[input.length()-1]-'0';
            memset(useful_table,0,sizeof(useful_table));
            memcpy(tileAmount,ntileAmount,70*4);

            int shanten=0;
            double similarity=0;
            int len = input.length()-1;
            for(int i=0;i<len/2;i++){
                int num=(input[i*2]-'0')*10+input[i*2+1]-'0';
                if(!tileAmount[num]){
                    shanten++;
                    useful_table[num]++;
                }
                else{
                    tileAmount[num]--;
                }
                if(shanten>=5) break;
            }
            if(shanten>=5||shanten>=hand.size()){continue;}
            similarity=SimilarityCalc(state,useful_table);

            if(shanten<minShanten){
                minShanten=shanten;
                maxSimilarity=similarity;
            }
            else if(shanten==minShanten){
                maxSimilarity+=similarity*k[flag];            
            }
            if(minShanten==0) break;
        }
    }
    else{
        //尽管有多个吃，但仍以第一个为核心
        for(int i=1;i<chisum;i++){
            ntileAmount[allCHI[i]/10000]++;
            ntileAmount[(allCHI[i]/100)%100]++;
            ntileAmount[allCHI[i]%100]++;
        }
       
        int myPack=allCHI[0];
        auto t=specialShantenForPack.find(myPack);
        if(t==specialShantenForPack.end()) return {100,0};;//找不到
        for(auto input: t->second){    
            // Reader::readIn(input);        
            flag=input[input.length()-1]-'0';
            memset(useful_table,0,sizeof(useful_table));
            memcpy(tileAmount,ntileAmount,70*4);

            int shanten=0;
            double similarity=0;
            int len = input.length()-1;
            for(int i=0;i<len/2;i++){
                int num=(input[i*2]-'0')*10+input[i*2+1]-'0';
                if(!tileAmount[num]){
                    shanten++;
                    useful_table[num]++;
                }
                else{
                    tileAmount[num]--;
                }
                if(shanten>=5) break;
            }
            if(shanten>=5||shanten>=hand.size()){continue;}
            similarity=SimilarityCalc(state,useful_table);
            if(shanten<minShanten){
                minShanten=shanten;
                maxSimilarity=similarity;
            }
            else if(shanten==minShanten){
                maxSimilarity+=similarity*k[flag];            
            }
            if(minShanten==0) break;
        }        
    }
    //clock_t end=clock();
    //cout<<end-start<<endl;
    return {minShanten,maxSimilarity};
}

//第一项表示得到的shanten数最小番型，第二项为shanten数，第三项为相似度
pair<specialShanten, pair<int,double> > specialShantenJudge(
    const vector<pair<string, Majang> >& pack,
    const vector<Majang>& hand,
    const StateContainer& state
) {
    int ntileAmount[70]={0};
    int tileAmount[70]={0};
    int useful_table[70]={0};
    int allCHI[10]={0};
    int chisum=0;
    for(auto i:pack) {
        if(i.first=="CHI"){
            //ntileAmount[i.second.getTileInt()]++;
            //ntileAmount[i.second.getTileInt()+1]++;
            //ntileAmount[i.second.getTileInt()-1]++;
            allCHI[chisum++]=(i.second.getTileInt()-1)*10000+(i.second.getTileInt())*100+(i.second.getTileInt()+1);
        }
        //else if(i.first=="PENG"){
        //    ntileAmount[i.second.getTileInt()]+=3;
        //}
        //else {
        //    ntileAmount[i.second.getTileInt()]+=4;
        //}
    }
    for(auto i:hand) ntileAmount[i.getTileInt()]++;

    string input;
    specialShanten r;//用来标记现在是哪一种番型,比如1是三色三步高        
    int flag;
    int minShanten=5;
    double maxSimilarity=0;
    double prt=100;
    //freopen("D://specialShanten.txt","r",stdin);
    // freopen("./data/specialShanten.txt","r",stdin);
    //clock_t start=clock();
    int idx = 0;
    if(chisum==0){
        while(true){    
            // Reader::readIn(input);        
            input = innerTable[idx++];
            if(input=="Over"){
                break;
            }
            memset(useful_table,0,sizeof(useful_table));
            memcpy(tileAmount,ntileAmount,70*4);
            int shanten=0;
            double similarity=0;
            if(input[0]=='C') {flag=input[4]-'0';continue;}
            else{
                int len = input.length();
                for(int i=0;i<len/2;i++){
                    int num=(input[i*2]-'0')*10+input[i*2+1]-'0';
                    if(!tileAmount[num]){
                        shanten++;
                        useful_table[num]++;
                    }
                    else{
                        tileAmount[num]--;
                    }
                    if(shanten>=5) break;
                }
            }
            if(shanten>=5||shanten>=hand.size()){continue;}
            similarity=SimilarityCalc(state,useful_table);
            double cnt = shanten - 1 - log(similarity)/k[flag];
            if(cnt<prt||shanten==0){
                prt=cnt;
                minShanten=shanten;
                maxSimilarity=similarity;
                r.formFlag=flag;
                r.tileForm=input;
            }
            //cout<<k[-16]<<Endl;
            //if(shanten<minShanten){
            //    r.formFlag=flag;
            //    r.tileForm=input;
            //    minShanten=shanten;
            //    maxSimilarity=similarity;
            //}
            //else if(shanten==minShanten&&maxSimilarity*k[r.formFlag]<similarity*k[flag]){
            //    r.formFlag=flag;
            //   r.tileForm=input;
            //    minShanten=shanten;
            //    maxSimilarity=similarity;            
            //}
            if(minShanten==0) break;
        }
    }
    //如果已经有了一个吃,就围绕这个吃来打
    else if(chisum==1){            
        int myPack=allCHI[0];
        auto t=specialShantenForPack.find(myPack);
        if(t==specialShantenForPack.end()) return {r,{minShanten,maxSimilarity}};;//找不到
        for(auto input: t->second){    
            // Reader::readIn(input);        
            flag=input[input.length()-1]-'0';
            memset(useful_table,0,sizeof(useful_table));
            memcpy(tileAmount,ntileAmount,70*4);

            int shanten=0;
            double similarity=0;
            int len = input.length()-1;
            for(int i=0;i<len/2;i++){
                int num=(input[i*2]-'0')*10+input[i*2+1]-'0';
                if(!tileAmount[num]){
                    shanten++;
                    useful_table[num]++;
                }
                else{
                    tileAmount[num]--;
                }
                if(shanten>=5) break;
            }
            if(shanten>=5||shanten>=hand.size()){continue;}
            similarity=SimilarityCalc(state,useful_table);
            double cnt = shanten - 1 - log(similarity)/k[flag];
            if(cnt<prt||shanten==0){
                prt=cnt;
                minShanten=shanten;
                maxSimilarity=similarity;
                r.formFlag=flag;
                r.tileForm=to_string(myPack)+input.substr(0,len);
            }
            //cout<<k[-16]<<Endl;
            //if(shanten<minShanten){
            //    r.formFlag=flag;
            //    r.tileForm=input;
            //    minShanten=shanten;
            //    maxSimilarity=similarity;
            //}
            //else if(shanten==minShanten&&maxSimilarity*k[r.formFlag]<similarity*k[flag]){
            //    r.formFlag=flag;
            //   r.tileForm=input;
            //    minShanten=shanten;
            //    maxSimilarity=similarity;            
            //}
            if(minShanten==0) break;
        }
    }
    else{
        //尽管有多个吃，但仍以第一个为核心
        for(int i=1;i<chisum;i++){
            ntileAmount[allCHI[i]/10000]++;
            ntileAmount[(allCHI[i]/100)%100]++;
            ntileAmount[allCHI[i]%100]++;
        }
       
        int myPack=allCHI[0];
        auto t=specialShantenForPack.find(myPack);
        if(t==specialShantenForPack.end()) return {r,{minShanten,maxSimilarity}};;//找不到
        for(auto input: t->second){    
            // Reader::readIn(input);        
            flag=input[input.length()-1]-'0';
            memset(useful_table,0,sizeof(useful_table));
            memcpy(tileAmount,ntileAmount,70*4);

            int shanten=0;
            double similarity=0;
            int len = input.length()-1;
            for(int i=0;i<len/2;i++){
                int num=(input[i*2]-'0')*10+input[i*2+1]-'0';
                if(!tileAmount[num]){
                    shanten++;
                    useful_table[num]++;
                }
                else{
                    tileAmount[num]--;
                }
                if(shanten>=5) break;
            }
            if(shanten>=5||shanten>=hand.size()){continue;}
            similarity=SimilarityCalc(state,useful_table);
            double cnt = shanten - 1 - log(similarity)/k[flag];
            if(cnt<prt||shanten==0){
                prt=cnt;
                minShanten=shanten;
                maxSimilarity=similarity;
                r.formFlag=flag;
                r.tileForm=to_string(myPack)+input.substr(0,len);
            }
            //cout<<k[-16]<<Endl;
            //if(shanten<minShanten){
            //    r.formFlag=flag;
            //    r.tileForm=input;
            //    minShanten=shanten;
            //    maxSimilarity=similarity;
            //}
            //else if(shanten==minShanten&&maxSimilarity*k[r.formFlag]<similarity*k[flag]){
            //    r.formFlag=flag;
            //   r.tileForm=input;
            //    minShanten=shanten;
            //    maxSimilarity=similarity;            
            //}
            if(minShanten==0) break;
        }        
    }
    //clock_t end=clock();
    //cout<<end-start<<endl;
    return {r,{minShanten,maxSimilarity}};
}

int specialShantenCalc(
    const vector<pair<string, Majang> >& pack,
    const vector<Majang>& hand,
    string target
) {
    int tileAmount[70]={0};
    int useful_table[70];
    /*for(auto i:pack) {
        if(i.first=="CHI"){
            tileAmount[i.second.getTileInt()]++;
            tileAmount[i.second.getTileInt()+1]++;
            tileAmount[i.second.getTileInt()-1]++;
        }
        else if(i.first=="PENG"){
            tileAmount[i.second.getTileInt()]+=3;
        }
        else {
            tileAmount[i.second.getTileInt()]+=4;
        }
    }
    */
    for(auto i:hand) tileAmount[i.getTileInt()]++;
    int shanten=0;
    int len = target.length();
    //先看pack
    vector<string> targetPart;
    for(int i=0;i<len/6;i++){
        targetPart.push_back(target.substr(i*6,6));
    }
    for(auto i:pack){
        if(i.first=="CHI"){
            string chi=to_string(i.second.getTileInt()-1)+to_string(i.second.getTileInt())+to_string(i.second.getTileInt()+1);
            for(auto j=targetPart.begin();j!=targetPart.end();j++){
                if((*j)==chi){targetPart.erase(j);break;}
            }
        }
    }

    target="";
    for(auto i:targetPart){
        target+=i;
    }
    len=target.length();

    for(int i=0;i<len/2;i++){
        int num=(target[i*2]-'0')*10+target[i*2+1]-'0';
        if(!tileAmount[num]){
            shanten++;
            useful_table[num]++;
        }
        else{
            tileAmount[num]--;
        }
            if(shanten>=5) break;
        }
    return shanten;
}

#endif // !Shanten_Calculator_H
