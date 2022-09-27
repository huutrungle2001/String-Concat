#include "ConcatStringList.h"

ConcatStringList::ReferencesList ConcatStringList::refList = ConcatStringList::ReferencesList();
ConcatStringList::DeleteStringList ConcatStringList::delStrList = ConcatStringList::DeleteStringList();

class CharALNode {
   public:
    string data;
    CharALNode* next;

    CharALNode(const char* s) {
        data.append(s);
        next = NULL;
    }
};

ConcatStringList::ConcatStringList(const char* s) {
    head = new CharALNode(s);
    tail = head;
    len = head->data.length();
}

ConcatStringList::~ConcatStringList() {
    CharALNode* it = head;

    CharALNode* next = it;
    while (it != tail->next && it != NULL) {
        next = it->next;
        // delete it;
        it = next;
    }
}

int ConcatStringList::length() const {
    return len;
}

char ConcatStringList::get(int index) const {
    if (index < 0 || index >= len) {
        throw out_of_range("Index of string is invalid");
    }
    CharALNode* it = head;

    while (index > it->data.length()) {
        // Trừ đi độ dài của 1 node
        index -= it->data.length();
        it = it->next;
    }

    return it->data[index];
}

int ConcatStringList::indexOf(char target) const {
    int index = 0;
    CharALNode* it = head;
    while (it != tail->next) {
        for (char c : it->data) {
            if (c == target) return index;
            index++;
        }

        it = it->next;
    }

    return -1;
}

string ConcatStringList::toString() const {
    string s = "";
    CharALNode* it = head;
    while (it != tail->next) {
        s += it->data;
        it = it->next;
    }

    return s;
}

ConcatStringList ConcatStringList::concat(const ConcatStringList& otherS) const {
    tail->next = otherS.head;
    ConcatStringList new_list = *this;
    new_list.tail = otherS.tail;

    new_list.len = len + otherS.len;

    return new_list;
}

ConcatStringList ConcatStringList::subString(int from, int to) const {
    if (from < 0 || to < 0 || from >= len || to >= len) {
        throw out_of_range("Index of string is invalid");
    }
    if (from >= to) {
        throw logic_error("Invalid range");
    }

    int sub_str_len = to - from;
    int index = from;
    CharALNode* it = head;

    // Get the index of 'from' in a node
    while (index > it->data.length()) {
        index -= it->data.length();
        it = it->next;
    }

    // Generate the head node of the substring
    string s = "";
    int char_left = sub_str_len;
    for (; (index < it->data.length() && char_left > 0); index++) {
        s += it->data[index];
        char_left--;
    }

    ConcatStringList sub_str(s.c_str());
    CharALNode* sub_str_it = sub_str.head;
    while (char_left > 0) {
        s.clear();
        for (; (index < it->data.length() && char_left > 0); index++) {
            s += it->data[index];
            char_left--;
        }

        index = 0;
        it = it->next;

        CharALNode* new_node = new CharALNode(s.c_str());
        sub_str_it->next = new_node;
        sub_str_it = new_node;

        sub_str.len += s.length();
    }
    sub_str.tail = sub_str_it;

    return sub_str;
}

string revString(string s) {
    return string(s.rbegin(), s.rend());
}

ConcatStringList ConcatStringList::reverse() const {
    ConcatStringList rev_str(revString(tail->data).c_str());
    rev_str.tail = new CharALNode(revString(head->data).c_str());
    CharALNode* it = head->next;
    CharALNode* rev_it = rev_str.head;

    while (it != tail) {
        rev_it->next = new CharALNode(revString(it->data).c_str());
        rev_it = rev_it->next;
        it = it->next;
    }

    rev_it->next = rev_str.tail;
    rev_str.len = len;

    return rev_str;
}

class refNode {
   public:
    CharALNode* node;
    int ref_count;
    refNode* next;

    refNode(CharALNode* n) {
        node = n;
        ref_count = 0;
        next = NULL;
    }
};

void ConcatStringList::ReferencesList::addRef(CharALNode* node) {
    if (refList.size() == 0) {
        refNode* new_ref = new refNode(node);
        refList.head = new_ref;
    } else {
        refNode* it = refList.head;
        do {
        } while (it != NULL);
    }
}
