//
// Created by Mike Bui on 09/12/2015.
//

#ifndef ATOMAS_ATOM_H
#define ATOMAS_ATOM_H

#include <iostream>

using namespace std;
struct node {
    int value;
    struct node *prev;
    struct node *next;
};


class Atom {
public:
    void addAdtomLast(int value) {
        struct node *s, *temp;
        temp = new(struct node);
        temp->value = value;
        temp->next = nullptr;
        if (start == nullptr)
        {
            temp->prev = nullptr;
            start = temp;
        }
        else
        {
            s = start;
            while (s->next != nullptr)
                s = s->next;
            s->next = temp;
            temp->prev = s;
        }
    }
    /*
 * Insertion at the beginning
 */
    void addAtomBegin(int value)
    {
        if (start == NULL)
        {
            cout<<"First Create the list."<<endl;
            return;
        }
        struct node *temp;
        temp = new(struct node);
        temp->prev = NULL;
        temp->value = value;
        temp->next = start;
        start->prev = temp;
        start = temp;
        cout<<"Element Inserted"<<endl;
    }

/*
 * Insertion of element at a particular position
 */
    void addAtomAfter(int value, int pos)
    {
        if (start == NULL)
        {
            cout<<"First Create the list."<<endl;
            return;
        }
        struct node *tmp, *q;
        int i;
        q = start;
        for (i = 0;i < pos - 1;i++)
        {
            q = q->next;
            if (q == NULL)
            {
                cout<<"There are less than ";
                cout<<pos<<" elements."<<endl;
                return;
            }
        }
        tmp = new(struct node);
        tmp->value = value;
        if (q->next == NULL)
        {
            q->next = tmp;
            tmp->next = NULL;
            tmp->prev = q;
        }
        else
        {
            tmp->next = q->next;
            tmp->next->prev = tmp;
            q->next = tmp;
            tmp->prev = q;
        }
        cout<<"Element Inserted"<<endl;
    }

/*
 * Deletion of element from the list
 */
    void deleteAtom(int pos)
    {
        struct node *tmp, *q;
        if (start == NULL)
        {
            cout<<"Empty List"<<endl;
            return;
        }
        int i;
        q = start;
        for (i = 0;i < pos - 1;i++)
        {
            q = q->next;
            if (q == NULL)
            {
                cout<<"There are less than ";
                cout<<pos<<" elements."<<endl;
                return;
            }
        }
        tmp = q->next;
        q->next = tmp->next;
        tmp->next->prev = q;
        cout<<"Element Deleted"<<endl;
        free(tmp);
        return;
    }
    int getAtom(int pos){
        struct node *temp = start;
        for (int i = 0;i < pos - 1;i++)
        {
            temp = temp->next;
            if (temp == NULL)
            {
                cout<<"There are less than ";
                cout<<pos<<" elements."<<endl;
                return -10;
            }
        }
        return temp->value;
    }
    /*void search_element(int value);
    void display_dlist();
    void count();
    void reverse();*/
    Atom()
    {
        start = nullptr;
    }
private:
    struct node *start;
};


#endif //ATOMAS_ATOM_H
