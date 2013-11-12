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
#include <unistd.h>
#include "../common/queue.h"

using namespace std;

typedef unsigned short Chess;
typedef unsigned short* BoardInfo;
typedef unsigned short Pos;
typedef unsigned int SeqId;

struct ChessBd {

    BoardInfo info;
    Pos zeroPos;
};

struct Path {

    SeqId father;
    SeqId son;
};

void play();
Pos getZeroPos(ChessBd*);
void forward(SeqId);
ChessBd* initBd(ChessBd*);
Path& initPath(SeqId, SeqId);
void up(ChessBd*);
void down(ChessBd*);
void left(ChessBd*);
void right(ChessBd*);
void deleteBd(ChessBd*);
SeqId Bd2SeqId(ChessBd*);
ChessBd* SeqId2Bd(SeqId);
bool isExisted(SeqId);
size_t getLowerCount(Chess, set<Chess>&);
size_t factorial(size_t);
void print(ChessBd*, string);
Chess getChess(size_t, set<Chess>&);
void printPath(SeqId);
SeqId getFatherId(SeqId);
void addBd(SeqId, ChessBd*);

Queue<SeqId> queue;
vector<Path> pathList;
set<SeqId> record;
vector<SeqId> result;
const size_t NUM = 9;
const unsigned short LINE_NUM = 3;
SeqId startId;
bool isRun = true;

void play() {

    time_t time1, time2;
    time(&time1);
    while (isRun) {
        if (queue.size() != 0) {
            SeqId seqId = queue.remove();
            forward(seqId);
        } else {
            cout<<"no result..."<<endl;
            exit(0);
        }
    }
    time(&time2);
    time2 -= time1;
    cout<<"Used Time: "<<time2<<"s"<<endl;
    sleep(3);
}

Pos getZeroPos(ChessBd* chessBd) {

    for (size_t i = 0; i < NUM; ++i) {
        if (chessBd->info[i] == 0) {
            return i;
        }
    }
}

void forward(SeqId fatherId) {

    ChessBd* chessBd = SeqId2Bd(fatherId);
    chessBd->zeroPos = getZeroPos(chessBd);
    // UP
    if (chessBd->zeroPos >= LINE_NUM) {
        ChessBd* chessBdUp = initBd(chessBd);
        chessBdUp->zeroPos = getZeroPos(chessBdUp);
        up(chessBdUp);
        addBd(fatherId, chessBdUp);
    }
    // LEFT
    if (chessBd->zeroPos % LINE_NUM != 0) {
        ChessBd* chessBdLeft = initBd(chessBd);
        chessBdLeft->zeroPos = getZeroPos(chessBdLeft);
        left(chessBdLeft);
        addBd(fatherId, chessBdLeft);
    }
    // RIGHT
    if ((chessBd->zeroPos + 1) % LINE_NUM != 0) {
        ChessBd* chessBdRight = initBd(chessBd);
        chessBdRight->zeroPos = getZeroPos(chessBdRight);
        right(chessBdRight);
        addBd(fatherId, chessBdRight);
    }
    // DOWN
    if (chessBd->zeroPos < NUM - LINE_NUM) {
        ChessBd* chessBdDown = initBd(chessBd);
        chessBdDown->zeroPos = getZeroPos(chessBdDown);
        down(chessBdDown);
        addBd(fatherId, chessBdDown);
    }
    deleteBd(chessBd);
}

void addBd(SeqId fatherId, ChessBd* sonBd) {

    SeqId sonId = Bd2SeqId(sonBd);
    if (record.count(sonId) == 0) {
        Path path = initPath(fatherId, sonId);
        pathList.push_back(path);
        record.insert(sonId);
        if (sonId == 0) {
            printPath(0);
            isRun = false;
        }
        queue.push(sonId);
    }
    deleteBd(sonBd);
}

ChessBd* initBd(ChessBd* father) {

    ChessBd* son = new ChessBd;
    son->info = new Chess[NUM];
    Chess test;
    memcpy(son->info, father->info, sizeof(test) * NUM);
    return son;
}

void deleteBd(ChessBd* chessBd) {

    delete(chessBd->info);
    delete(chessBd);
}

Path& initPath(SeqId father, SeqId son) {

    Path* path = new Path;
    path->father = father;
    path->son = son;
    return *path;
}

void up(ChessBd* chessBd) {

    chessBd->info[chessBd->zeroPos]
        = chessBd->info[chessBd->zeroPos - LINE_NUM];
    chessBd->zeroPos -= LINE_NUM;
    chessBd->info[chessBd->zeroPos] = 0;
}

void down(ChessBd* chessBd) {

    chessBd->info[chessBd->zeroPos]
        = chessBd->info[chessBd->zeroPos + LINE_NUM];
    chessBd->zeroPos += LINE_NUM;
    chessBd->info[chessBd->zeroPos] = 0;
}

void left(ChessBd* chessBd) {

    chessBd->info[chessBd->zeroPos]
        = chessBd->info[chessBd->zeroPos - 1];
    chessBd->zeroPos -= 1;
    chessBd->info[chessBd->zeroPos] = 0;
}

void right(ChessBd* chessBd) {

    chessBd->info[chessBd->zeroPos]
        = chessBd->info[chessBd->zeroPos + 1];
    chessBd->zeroPos += 1;
    chessBd->info[chessBd->zeroPos] = 0;
}

SeqId Bd2SeqId(ChessBd* chessBd) {

    SeqId seqId = 0;
    set<Chess> tmpSet;
    for (size_t i = 0; i < NUM; ++i) {
        Chess chess = chessBd->info[i];
        tmpSet.insert(chess);
        seqId += getLowerCount(chess, tmpSet) * factorial(NUM - 1 - i);
    }
    return seqId;
}

ChessBd* SeqId2Bd(SeqId seqId) {

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
    return chessBd;
}

Chess getChess(size_t count, set<Chess>& tmpSet) {

    Chess chess = 0;
    size_t tmp = 0;
    for (size_t i = 0; i < NUM; ++i) {
        if (tmpSet.count(i) == 0) {
            if (tmp == count) {
                tmpSet.insert(i);
                return i;
            }
            ++tmp;
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
    return count;
}

size_t factorial (size_t num) {

    size_t result = num;
    while (num != 1 && num != 0) {
        result *= --num;
    }
    return result;
}

void print(ChessBd* chessBd, string title) {

    cout<<endl<<"==========="<<title<<"==========="<<endl;
    cout<<"chess board: "<<endl;
    for (size_t i = 0; i < NUM; ++i) {
        cout<<chessBd->info[i]<<" "<<ends;
        if ((i + 1) % LINE_NUM == 0)
            cout<<endl;
    }
    cout<<"ZeroPosition: "<<chessBd->zeroPos<<endl;
}

void printPath(SeqId sonId) {

    result.push_back(sonId);
    SeqId fatherId = getFatherId(sonId);
    if (sonId != startId) {
        printPath(fatherId);
    }
}

SeqId getFatherId(SeqId sonId) {

    for (vector<Path>::iterator iter = pathList.begin();
            iter != pathList.end(); ++iter) {
        if (iter->son == sonId) {
            return iter->father;
        }
    }
}

void printResult() {

    for (vector<SeqId>::iterator iter = result.end() - 1;
            iter != result.begin() - 1; --iter) {
        ChessBd* chessBd = SeqId2Bd(*iter);
        print(chessBd, "");
        cout<<"SeqId: "<<*iter<<endl;
        cout<<"\n     ||      "<<endl;
        cout<<"    \\  /     "<<endl;
        cout<<"     \\/      "<<endl;
    }
    cout<<"\n========Finish!========"<<endl;
}

int main () {

    Chess init[NUM];
    for (size_t i = 0; i < NUM; ++i) {
        cin>>init[i];
    }
    ChessBd chessBd;
    chessBd.info = init;
    startId = Bd2SeqId(&chessBd);
    queue.push(startId);
    cout<<"\nRunning..."<<endl;
    play();
    printResult();
    return 0;
}
