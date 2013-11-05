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
#include <vector>

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
void forward(SeqId);
ChessBd& initBd(ChessBd&);
Path& initPath(SeqId, SeqId);
void up(ChessBd&);
void down(ChessBd&);
void left(ChessBd&);
void right(ChessBd&);
void deleteBd(ChessBd&);
SeqId Bd2SeqId(ChessBd&);
ChessBd& SeqId2Bd(SeqId);
bool isExisted(SeqId);
size_t getLowerCount(Chess, set<Chess>&);
size_t factorial(size_t);
void print(ChessBd&, string);
Chess getChess(size_t, set<Chess>&);

Queue<SeqId> queue;
vector<Path> pathList;
const size_t NUM = 9;
const size_t LINE_NUM = 3;

void play() {

    SeqId seqId = queue.remove();
    forward(seqId);
}

Pos getZeroPos(ChessBd& chessBd) {

    for (size_t i = 0; i< NUM; ++i) {
        cout<<chessBd.info[i]<<endl;
        if (chessBd.info[i] == 0) {
            return i;
        }
    }
}

void forward(SeqId fatherId) {

    ChessBd chessBd = SeqId2Bd(fatherId);
    print(chessBd, "round");//TODO FT
    chessBd.zeroPos = getZeroPos(chessBd);
    if (chessBd.zeroPos >= LINE_NUM) {
        ChessBd chessBdUp = initBd(chessBd);
        up(chessBdUp);
        SeqId seqId = Bd2SeqId(chessBdUp);
        if (seqId == 0) {
            print(chessBdUp, "Finish!");
            exit(0);
        }
        if (!isExisted(seqId)) {
            queue.push(seqId);
            Path path = initPath(fatherId, seqId);
            pathList.push_back(path);
        }
        deleteBd(chessBdUp);
    }
    if (chessBd.zeroPos % LINE_NUM != 0) {
        ChessBd chessBdLeft = initBd(chessBd);
        left(chessBdLeft);
        SeqId seqId = Bd2SeqId(chessBdLeft);
        if (seqId == 0) {
            print(chessBdLeft, "Finish!");
            exit(0);
        }
        if (!isExisted(seqId)) {
            queue.push(seqId);
            Path path = initPath(fatherId, seqId);
            pathList.push_back(path);
        }
        deleteBd(chessBdLeft);
    }
    if ((chessBd.zeroPos + 1) % LINE_NUM != 0) {
        ChessBd chessBdRight = initBd(chessBd);
        right(chessBdRight);
        SeqId seqId = Bd2SeqId(chessBdRight);
        if (seqId == 0) {
            print(chessBdRight, "Finish!");
            exit(0);
        }
        if (!isExisted(seqId)) {
            queue.push(seqId);
            Path path = initPath(fatherId, seqId);
            pathList.push_back(path);
        }
        deleteBd(chessBdRight);
    }
    if (chessBd.zeroPos < NUM - LINE_NUM) {
        ChessBd chessBdDown = initBd(chessBd);
        down(chessBdDown);
        SeqId seqId = Bd2SeqId(chessBdDown);
        if (seqId == 0) {
            print(chessBdDown, "Finish!");
            exit(0);
        }
        if (!isExisted(seqId)) {
            queue.push(seqId);
            Path path = initPath(fatherId, seqId);
            pathList.push_back(path);
        }
        deleteBd(chessBdDown);
    }
    deleteBd(chessBd);
}

ChessBd& initBd(ChessBd& father) {

    ChessBd* son = new ChessBd;
    son->info = new Chess[NUM];
    Chess test;
    memcpy(son->info, father.info, sizeof(test) * NUM);
    return *son;
}

Path& initPath(SeqId father, SeqId son) {

    Path* path = new Path;
    path->father = father;
    path->son = son;
    return *path;
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
    chessBd->zeroPos = 0;
    set<Chess> tmpSet;
    for (int i = 0; i < NUM; ++i) {
        size_t count = 0;
        if (i != NUM -1) {
            count = seqId / factorial(NUM - 1 - i);
        }
        if (count != 0) {
            seqId -= count * factorial(NUM - 1 -i);
        }
        Chess chess = getChess(count, tmpSet);
        chessBd->info[i] = chess;
    }
    return *chessBd;
}

Chess getChess(size_t count, set<Chess>& tmpSet) {

    Chess chess = 0;
    for (size_t i = 0; i < NUM; ++i) {
        if (tmpSet.count(i) == 0) {
            chess = i + count;
            tmpSet.insert(chess);
            return chess;
        }
    }
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

    for(vector<Path>::iterator iter = pathList.begin();
            iter != pathList.end(); ++iter) {
        if (iter->son == seqId) {
            return true;
        }
    }
    return false;
}

void print (ChessBd &chessBd, string title) {

    cout<<endl<<"============="<<title<<"============="<<endl;
    cout<<"chess board: "<<endl;
    for (size_t i = 0; i < NUM; ++i) {
        cout<<chessBd.info[i]<<" "<<ends;
        if ((i + 1) % LINE_NUM == 0)
            cout<<endl;
    }
    cout<<"ZeroPosition: "<<chessBd.zeroPos<<endl;
}

int main () {

    Chess init[NUM];
    for (size_t i = 0; i < NUM; ++i) {
        cin>>init[i];
    }
    ChessBd chessBd;
    chessBd.info = init;
    queue.push(Bd2SeqId(chessBd));
    play();
    return 0;
}
