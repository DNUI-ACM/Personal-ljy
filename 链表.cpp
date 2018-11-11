#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <math.h>

typedef struct Node {
    int nodeValue;
    struct Node* next;
    // struct Node* prev;
} Node;

typedef struct List {
    Node* first;
    Node* last;
    int size;
} List;

Node* CreateNode(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->nodeValue = value;
    node->next = NULL;
    return node;
}

bool FreeNode(Node* node) {
    free(node);
    return true;
}

List* CreateList(void) {
    List* l = (List*)malloc(sizeof(List));
    l->size = 0;
    l->first = l->last = NULL;
    return l;
}

inline bool IsEmpty(List* l) {
    return l->size == 0;
}

inline size_t Size(List* l) {
    return l->size;
}

inline bool insertOnlyFirst(List* l, int value) {
    Node* node = CreateNode(value);
    l->first = node;
    l->last = node;
    l->size = 1;
    return true;
}

bool push_front(List* l, int value) {
    if (IsEmpty(l))
        return insertOnlyFirst(l, value);

    Node* node = CreateNode(value);
    node->next = l->first;
    l->first = node;
    l->size++;
    return true;
}

bool push_back(List* l, int value) {
    if (IsEmpty(l))
        return insertOnlyFirst(l, value);
    Node* node = CreateNode(value);
    l->last->next = node;
    l->last = node;
    l->size++;
    return true;
}

bool insert(List* l, Node* pos, int value) {
    if (pos == l->first) {
        return push_front(l, value);
    }
    if (pos == NULL) {
        return push_back(l, value);
    }

    Node* iter = l->first;
    Node* node = CreateNode(value);
    while (iter) {
        if (iter->next == pos) {
            node->next = iter->next;
            iter->next = node;
            l->size++;
            return true;
        }
        iter = iter->next;
    }
    return false;
}

bool pop_front(List* l) {
    if (IsEmpty(l))
        return false;
    if (Size(l) == 1) {
        FreeNode(l->first);
        l->first = l->last = NULL;
        l->size = 0;
        return true;
    }
    Node* willFree = l->first;
    l->first = willFree->next;
    l->size--;
    FreeNode(willFree);
    return true;
}

bool pop_back(List* l) {
    if (IsEmpty(l))
        return false;
    if (Size(l) == 1) {
        FreeNode(l->first);
        l->first = l->last = NULL;
        l->size = 0;
        return true;
    }

    Node* pNode = l->first;
    while(pNode) {
        if(pNode->next == l->last) {
            l->last = pNode;
            l->size--;
            FreeNode(pNode->next);
            pNode->next = NULL;
        }
        pNode = pNode->next;
    }
    return false;
}

bool erase(List* l, Node* pos) {
    if (pos == l->first) {
        return pop_front(l);
    }
    if (pos == l->last) {
        return pop_back(l);
    }
    Node* pNode = l->first;
    while(pNode) {
        if(pNode->next == pos) {
            Node* willNode = pos;
            pNode->next = pos->next;
            l->size--;
            FreeNode(willNode);
            return true;
        }
        pNode = pNode->next;
    }
    return false;
}

Node* find(List* l, int value) {
    Node* pNode = l->first;
    while(pNode) {
        if (pNode->nodeValue == value) {
            return pNode;
        }
        pNode = pNode->next;
    }
    return NULL;
}

bool clear(List* l) {
    while(!IsEmpty(l)) {
        pop_front(l);
    }
    return true;
}

bool FreeList(List* l) {
    clear(l);
    free(l);
    return true;
}

bool Merge(List* l1, List* l2) {
    l1->last->next = l2->first;
    l1->size += l2->size;
    l1->last = l2->last;
    l2->first = l2->last = NULL;
    l2->size = 0;
    return true;
}

int fornt(List* l) {
    if(IsEmpty(l)) {
        printf("None");
        exit(-1);
    }
    return l->first->nodeValue;
}

int back(List* l) {
    if(IsEmpty(l)) {
        printf("None");
        exit(-1);
    }
    return l->last->nodeValue;
}

int main(void) {
    List* l = CreateList();
    printf("l: size: %d\n", (int)Size(l));

    for (int i = 0; i < 100; i++) {
        push_back(l, i);
    }

    for (int i = 0; i < 100; i++) {
        Node* pNode = find(l, i);
        if (pNode) {
            printf("Node: %p -> %d\n", pNode, pNode->nodeValue);
        }
        int insertNumber = rand() % 700;
        insert(l, pNode, insertNumber);
    }
    Node* pNode = l->first;
    while (pNode) {
        printf("Node: %p -> %d\n", pNode, pNode->nodeValue);
        pNode = pNode->next;
    }
    clear(l);
    printf("l: size: %d\n", (int)Size(l));
    FreeList(l);
    return 0;
}

