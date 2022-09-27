#ifndef __CONCAT_STRING_LIST_H__
#define __CONCAT_STRING_LIST_H__

#include "main.h"

class CharALNode;
class refNode;
class delNode;

class ConcatStringList {
   public:
    class ReferencesList;    // forward declaration
    class DeleteStringList;  // forward declaration

   public:
    static ReferencesList refList;
    static DeleteStringList delStrList;

    // TODO: may provide some attributes
   private:
    CharALNode* head;
    CharALNode* tail;
    int len;

   public:
    ConcatStringList(const char*);
    int length() const;
    char get(int index) const;
    int indexOf(char c) const;
    std::string toString() const;
    ConcatStringList concat(const ConcatStringList& otherS) const;
    ConcatStringList subString(int from, int to) const;
    ConcatStringList reverse() const;
    ~ConcatStringList();

   public:
    class ReferencesList {
        // TODO: may provide some attributes
        refNode* head;
        int len = 0;

       public:
        // Add a node to the list to track
        void addRef(CharALNode* node);

        int size() const;
        int refCountAt(int index) const;
        std::string refCountsString() const;
    };

    class DeleteStringList {
        // TODO: may provide some attributes

       public:
        int size() const;
        std::string totalRefCountsString() const;
    };
};

#endif  // __CONCAT_STRING_LIST_H__