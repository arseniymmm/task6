#include <iostream>
#include<string.h>
#include <iomanip>
#include <fstream>

using namespace std;

typedef struct tree {
    char id;
    struct tree* l;
    struct tree* r;
};


tree* term(char s[], int* i);
tree* atom(char s[], int* i);
tree* form(char s[], int* i);


void print(tree*& head, int n)
{
    if (head != NULL)
    {
        print(head->l, n + 1);
        cout << setw(n * 3) << head->id << endl;
        print(head->r, n + 1);
    }
}
tree* form(char s[], int* i) {
    tree* t = new tree;
    t = term(s, i);
    int n = strlen(s);
    while (((*i) <= n) && (s[*i] == '+')) {
        tree* p = new tree;
        p->id = '+';
        p->l = t;
        ++(*i);
        p->r = term(s, i);
        t = p;
    }
    return t;
}

tree* term(char s[], int* i) {
    tree* t = new tree;
    t = atom(s, i);
    int n = strlen(s);
    while (((*i) <= n) && (s[*i] == '*')) {
        tree* p = new tree;
        p->id = '*';
        p->l = t;
        ++(*i);
        p->r = atom(s, i);
        t = p;
    }
    return t;
}

tree* atom(char s[], int* i) {
    tree* t = new tree;
    t->l = NULL;
    t->r = NULL;
    if ((s[*i] == '0') || (s[*i] == '1')) {
        t->id = s[*i];
        ++(*i);
    }
    else if (s[*i] == '!') {
        t->id = s[*i];
        ++(*i);
        t->l = atom(s, i);
        t->r = NULL;
    }
    else if (s[*i] == '(') {
        ++(*i);
        t = form(s, i);
        ++(*i);
    }
    return t;
}

bool count(tree* t) {
    bool x, y, z=0;
    if (t != NULL) {
        x = count(t->l);
        y = count(t->r);
        if (t->id == '+')
            z = x || y;
        else if (t->id == '*')
            z = x && y;
        else if (t->id == '!')
            z = !x;
        else if (t->id == '0')
            z = false;
        else if (t->id == '1')
            z = true;
    }
    return z;
}

int main()
{
    char  s[100];
    ifstream fin("input.txt");
    fin.getline(s, 100);
    fin.close();
    tree* h;
    int i = 0;
    h = form(s, &i);
    print(h, 1);
    return 0;
}