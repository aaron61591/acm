/*************************************************************************
    > File Name: eightCodeBFS.cpp
    > Author: Aaron
    > Mail: Aaron@gmail.com 
    > Created Time: 2013年10月27日 星期日 15时33分19秒
 ************************************************************************/

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <set>

#include "../common/queue.h"

using namespace std;

typedef unsigned short Chess;
typedef unsigned short* BoardInfo;
typedef unsigned short Pos;
typedef unsigned short SeqId;

struct ChessBd {

    BoardInfo info;
    Pos zeroPos;
};

struct Path {

    SeqId father;
    SeqId son;
};

void play();
Pos getZeroPos(ChessBd&);
void forward(ChessBd&);
ChessBd& initBd(ChessBd&);
void up(ChessBd&);
void down(ChessBd&);
void left(ChessBd&);
void right(ChessBd&);
void deleteBd(ChessBd&);
SeqId Bd2SeqId(ChessBd&);
ChessBd& SeqId2Bd(SeqId);
bool isExisted(SeqId);
size_t getLowerCount(Chess, set<Chess>&);
size_t factorial (size_t);

Queue<SeqId> queue;
const size_t NUM = 9;
const size_t LINE_NUM = 3;

void play() {

    SeqId seqId = queue.remove();
    ChessBd chessBd = SeqId2Bd(seqId);
    //forward(chessBd);
}


Pos getZeroPos(ChessBd& chessBd) {

    for (size_t i = 0; i< NUM; ++i) {
        if (chessBd.info[i] == 0) {
            return i;
        }
    }
}

void forward(ChessBd& chessBd) {

    chessBd.zeroPos = getZeroPos(chessBd);
    if (chessBd.zeroPos >= LINE_NUM) {
        ChessBd chessBdUp = initBd(chessBd);
        up(chessBdUp);
        //TODO
        SeqId seqId = Bd2SeqId(chessBdUp);
        if (!isExisted(seqId)) {
            queue.push(seqId);
        }
        deleteBd(chessBdUp);
    }
    if (chessBd.zeroPos % LINE_NUM != 0) {
        ChessBd chessBdLeft = initBd(chessBd);
        left(chessBdLeft);
        //TODO
        SeqId seqId = Bd2SeqId(chessBdLeft);
        if (!isExisted(seqId)) {
            queue.push(seqId);
        }
        deleteBd(chessBdLeft);
    }
    if ((chessBd.zeroPos + 1) % LINE_NUM != 0) {
        ChessBd chessBdRight = initBd(chessBd);
        right(chessBdRight);
        //TODO
        SeqId seqId = Bd2SeqId(chessBdRight);
        if (!isExisted(seqId)) {
            queue.push(seqId);
        }
        deleteBd(chessBdRight);
    }
    if (chessBd.zeroPos < NUM - LINE_NUM) {
        ChessBd chessBdDown = initBd(chessBd);
        down(chessBdDown);
        //TODO
        SeqId seqId = Bd2SeqId(chessBdDown);
        if (!isExisted(seqId)) {
            queue.push(seqId);
        }
        deleteBd(chessBdDown);
    }
}

ChessBd& initBd(ChessBd& father) {

    ChessBd* son = new ChessBd;
    son->info = new Chess[NUM];
    Chess test;
    memcpy(son->info, father.info, sizeof(test) * NUM);
    return *son;
}

void up(ChessBd& chessBd) {

    chessBd.zeroPos = getZeroPos(chessBd);
    chessBd.info[chessBd.zeroPos]
        = chessBd.info[chessBd.zeroPos - LINE_NUM];
    chessBd.zeroPos -= LINE_NUM;
    chessBd.info[chessBd.zeroPos] = 0;
}

void down(ChessBd& chessBd) {

    unsigned short tmp = chessBd.info[chessBd.zeroPos + LINE_NUM];
    chessBd.info[chessBd.zeroPos] = tmp;
    chessBd.zeroPos += LINE_NUM;
    chessBd.info[chessBd.zeroPos] = 0;
}

void left(ChessBd& chessBd) {

    unsigned short tmp = chessBd.info[chessBd.zeroPos - 1];
    chessBd.info[chessBd.zeroPos] = tmp;
    chessBd.zeroPos -= 1;
    chessBd.info[chessBd.zeroPos] = 0;
}

void right(ChessBd& chessBd) {

    unsigned short tmp = chessBd.info[chessBd.zeroPos + 1];
    chessBd.info[chessBd.zeroPos] = tmp;
    chessBd.zeroPos += 1;
    chessBd.info[chessBd.zeroPos] = 0;
}

void deleteBd(ChessBd& chessBd) {

    delete(chessBd.info);
    delete(&chessBd);
}

SeqId Bd2SeqId(ChessBd& chessBd) {

    SeqId seqId = 0;
    set<Chess> tmpSet;
    for (size_t i = 0; i < NUM; ++i) {
        Chess chess = chessBd.info[i];
        tmpSet.insert(chess);
        seqId += getLowerCount(chess, tmpSet) * factorial(NUM - 1 - i);
    }
    return seqId;
}

ChessBd& SeqId2Bd(SeqId seqId) {

    ChessBd* chessBd = new ChessBd;
    chessBd->info = new Chess[NUM];
    return *chessBd;
}

size_t getLowerCount(Chess chess, set<Chess>& tmpSet) {

    size_t count = 0;
    while (chess != 0) {
        if (tmpSet.count(--chess) == 0) {
            ++count;
        }
    }
    //cout<<"count: "<<count<<endl;
    return count;
}

size_t factorial (size_t num) {

    size_t result = num;
    while (num != 1 && num != 0) {
        result *= --num;
    }
    //cout<<"factorial: "<<result<<endl;
    return result;
}

bool isExisted(SeqId seqId) {

    return true;
}

int main () {

    Chess init[NUM];
    for (size_t i = 0; i < NUM; ++i) {
        cin>>init[i];
    }
    ChessBd chessBd;
    chessBd.info = init;
    cout<<Bd2SeqId(chessBd)<<endl;
    exit(0);
    queue.push(Bd2SeqId(chessBd));
    play();
    return 0;
}
