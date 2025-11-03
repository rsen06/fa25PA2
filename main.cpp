//
// Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "../input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("../input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}

// Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

// Step 3: Build the encoding tree using heap operations
int buildEncodingTree(int nextFree) {
    MinHeap heap;
    if (nextFree == 0) return -1;

    for (int i = 0; i < nextFree; ++i) {
        heap.push(i, weightArr);
    }

    if (heap.size == 1) {
        return heap.data[0];
    }

    while (heap.size > 1) {
        int a = heap.pop(weightArr);
        int b = heap.pop(weightArr);

        if (nextFree >= MAX_NODES) {
            cerr << "Too many nodes.\n";
            exit(1);
        }
        int p = nextFree++;

        leftArr[p]   = a;
        rightArr[p]  = b;
        weightArr[p] = weightArr[a] + weightArr[b];
        charArr[p]   = '\0';

        heap.push(p, weightArr);
    }
    return heap.data[0];
}

// Step 4: Use an STL stack to generate codes
void generateCodes(int root, string codes[]) {
    for (int i = 0; i < 26; ++i) codes[i].clear();
    if (root == -1) return;

    stack<int> ns;
    stack<string> ps;

    ns.push(root);
    ps.push("");

    while (!ns.empty()) {
        int node = ns.top(); ns.pop();
        string path = ps.top(); ps.pop();

        bool isLeaf = (leftArr[node] == -1 && rightArr[node] == -1);

        if (isLeaf) {
            if (path.empty()) path = "0";
            char c = charArr[node];
            if (c >= 'a' && c <= 'z') {
                codes[c - 'a'] = path;
            }
        } else {
            if (rightArr[node] != -1) {
                ns.push(rightArr[node]);
                ps.push(path + "1");
            }
            if (leftArr[node] != -1) {
                ns.push(leftArr[node]);
                ps.push(path + "0");
            }
        }
    }
}

// Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}