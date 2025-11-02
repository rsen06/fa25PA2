//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() { size = 0; }

    void push(int idx, int weightArr[]) {
        if (size >= 64) {
            cerr << "Heap is full" << endl;
            return;
        }
        data[size] = idx;
        upheap(size, weightArr);
        size++;
    }

    int pop(int weightArr[]) {
        if (size == 0) {
            cerr << "Heap is empty" << endl;
            return -1;
        }
        int top = data[0];
        size--;
        if (size > 0) {
            data[0] = data[size];
            downheap(0, weightArr);
        }
        return top;
    }

    void upheap(int pos, int weightArr[]) {
        while (pos > 0) {
            int par = (pos - 1) / 2;
            int curidx = data[pos];
            int paridx = data[par];

            bool sm = (weightArr[curidx] < weightArr[paridx] || weightArr[curidx] == weightArr[paridx] && curidx < paridx);
            if (sm) {
                int temp = data[pos];
                data[pos] = data[par];
                data[par] = temp;
                pos = par;
            } else {
                break;
            }
        }
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
    }
};

#endif