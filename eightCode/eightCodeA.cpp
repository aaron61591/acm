/*************************************************************************
    > File Name: eightCode.cpp
    > Author: Aaron
    > Mail: Aaron@gmail.com 
    > Created Time: 2013年10月19日 星期六 14时46分11秒
 ************************************************************************/
#include <unistd.h>
#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>

#include "queue.h"

using namespace std;

typedef unsigned short* chess;
typedef unsigned short dis;
typedef unsigned short pos;

struct ChessBd {

    chess status;
    dis distance;
    pos zeroPos;
};

void print(ChessBd&, string);
void play();
dis getDistance(ChessBd&);
void forward(ChessBd&);
size_t getZeroPos(ChessBd&);
void up(ChessBd&);
void down(ChessBd&);
void left(ChessBd&);
void right(ChessBd&);
bool fun(ChessBd&, ChessBd&);
ChessBd& initBd(ChessBd&);

Queue<ChessBd> queue;
const size_t NUM = 9;
const size_t LINE_NUM = 3;

void play () {

    ChessBd chessBd = queue.remove();
    chessBd.zeroPos = getZeroPos(chessBd);
    print(chessBd, "get a board from queue");
    forward(chessBd);
}

void forward(ChessBd &chessBd) {

    if (chessBd.zeroPos >= LINE_NUM) {
        //TODO 可上移
        ChessBd chessBdUp = initBd(chessBd);
        up(chessBdUp);
        chessBdUp.distance = getDistance(chessBdUp);
        if (fun(chessBd, chessBdUp)) {
            queue.push(chessBdUp);
            print(chessBdUp, "up, push a board in queue");
            sleep(1);
        }
    }
    if (chessBd.zeroPos % LINE_NUM != 0) {
        //TODO 可左移
        ChessBd chessBdLeft = initBd(chessBd);
        left(chessBdLeft);
        chessBdLeft.distance = getDistance(chessBdLeft);
        if (fun(chessBd, chessBdLeft)) {
            queue.push(chessBdLeft);
            print(chessBdLeft, "left, push a board in queue");
            sleep(1);
        }
    }
    if ((chessBd.zeroPos + 1) % LINE_NUM != 0) {
        //TODO 可右移
        cout<<"can right"<<endl;
        ChessBd chessBdRight = initBd(chessBd);
        right(chessBdRight);
        chessBdRight.distance = getDistance(chessBdRight);
        if (fun(chessBd, chessBdRight)) {
            queue.push(chessBdRight);
            print(chessBdRight, "right, push a board in queue");
            sleep(1);
        }
    }
    if (chessBd.zeroPos < NUM - LINE_NUM) {
        //TODO 可下移
        cout<<"can down"<<endl;
        ChessBd chessBdDown = initBd(chessBd);
        down(chessBdDown);
        chessBdDown.distance = getDistance(chessBdDown);
        if (fun(chessBd, chessBdDown)) {
            queue.push(chessBdDown);
            print(chessBdDown, "down, push a board in queue");
            sleep(1);
        }
    }
}

ChessBd& initBd(ChessBd &father) {

    ChessBd* son = new ChessBd;
    son->status = new unsigned short[NUM];
    unsigned short tmp;
    memcpy(son->status, father.status, sizeof(tmp) * NUM);
    return *son;
}

void up(ChessBd &chessBd) {

    chessBd.zeroPos = getZeroPos(chessBd);
    chessBd.status[chessBd.zeroPos]
        = chessBd.status[chessBd.zeroPos - LINE_NUM];
    chessBd.zeroPos -= LINE_NUM;
    chessBd.status[chessBd.zeroPos] = 0;
}

void down(ChessBd &chessBd) {

    unsigned short tmp = chessBd.status[chessBd.zeroPos + LINE_NUM];
    chessBd.status[chessBd.zeroPos] = tmp;
    chessBd.zeroPos += LINE_NUM;
    chessBd.status[chessBd.zeroPos] = 0;
}

void left(ChessBd &chessBd) {

    unsigned short tmp = chessBd.status[chessBd.zeroPos - 1];
    chessBd.status[chessBd.zeroPos] = tmp;
    chessBd.zeroPos -= 1;
    chessBd.status[chessBd.zeroPos] = 0;
}

void right(ChessBd &chessBd) {

    unsigned short tmp = chessBd.status[chessBd.zeroPos + 1];
    chessBd.status[chessBd.zeroPos] = tmp;
    chessBd.zeroPos += 1;
    chessBd.status[chessBd.zeroPos] = 0;
}

bool fun(ChessBd &father, ChessBd &son) {
    if(father.distance >= son.distance - 2)
        return true;
    else
        return false;
}

size_t getZeroPos(ChessBd &chessBd) {

    for (size_t i = 0; i < NUM; ++i)
        if (chessBd.status[i] == 0)
            return i;
}

void print (ChessBd &chessBd, string title) {

    cout<<endl<<"============="<<title<<"============="<<endl;
    cout<<"chess board: "<<endl;
    for (size_t i = 0; i < NUM; ++i) {
        cout<<chessBd.status[i]<<" "<<ends;
        if ((i + 1) % LINE_NUM == 0)
            cout<<endl;
    }
    cout<<"Distance: "<<chessBd.distance<<endl;
    cout<<"ZeroPosition: "<<chessBd.zeroPos<<endl;
}

dis getDistance(ChessBd &chessBd) {

    dis distance = 0;
    for (size_t i = 0; i < NUM; ++i)
        if (i == NUM - 1) {
            if (chessBd.status[i] != 0)
                ++distance;
        } else if (chessBd.status[i] != i + 1)
            ++distance;
    return distance;
}

int main () {

    unsigned short a[NUM];
    for (size_t i = 0; i < NUM; ++i)
        cin>>a[i];
    ChessBd chessBd;
    chessBd.status = a;
    chessBd.distance = getDistance(chessBd);
    queue.push(chessBd);
    //while(true)
        play();
}
