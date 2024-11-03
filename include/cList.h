#ifndef C_LIST_H
#define C_LIST_H

#include <stdint.h>

const int64_t LIST_POISON = 0x0FACEFABDDFAC;
const size_t MIN_LIST_RESERVED = 10;
const size_t SIZE_MULTIPLIER = 2;
enum listStatus {
    LIST_SUCCESS = 0,
    LIST_ERROR   = 1,
    LIST_MEMORY_ERROR,
    LIST_SIZE_ERROR,

    LIST_NEXT_LINK_ERROR,  ///< Wrong linking in next array
    LIST_FREE_LINK_ERROR,  ///< Wrong linking in free array

    LIST_PREV_LINK_ERROR,  ///< Wrong linking in prev array

    LIST_HEAD_ERROR,
    LIST_TALE_ERROR,
    LIST_FREE_ERROR,
};

typedef int32_t listIterator_t;
const listIterator_t INVALID_LIST_IT = -1;
const listIterator_t NULL_LIST_IT = 0;
typedef struct cList {
    int32_t  size;
    int32_t  reserved;

    int32_t  elemSize;
    void    *data;

    int32_t *next;
    int32_t *prev;

    int32_t free;
} cList_t;

enum listStatus listCtor(cList_t *list, size_t elemSize);
enum listStatus listDtor(cList_t *list);

enum listStatus listClear(cList_t *list);

enum listStatus listVerify(cList_t *list);
enum listStatus listDump(cList_t *list);

listIterator_t  listFront(cList_t *list);
listIterator_t  listBack(cList_t *list);

listIterator_t  listNext(cList_t *list, listIterator_t iter);
listIterator_t  listPrev(cList_t *list, listIterator_t iter);

listIterator_t  listPushFront(cList_t *list, const void *elem);
listIterator_t  listPushBack(cList_t *list, const void *elem);

listIterator_t listPopFront(cList_t *list);
listIterator_t listPopBack(cList_t *list);

enum listStatus listRemove(cList_t *list, listIterator_t iter);
listIterator_t listFind(cList_t *list, const void *elem);

/// @brief insert After iterator, return iterator to inserted elem
listIterator_t listInsertAfter(cList_t *list, listIterator_t iter, const void *elem);

/// @brief insert Before iterator, return iterator to inserted elem
listIterator_t listInsertBefore(cList_t *list, listIterator_t iter, const void *elem);

void *listGet(cList_t *list, listIterator_t iter);

#define LIST_ASSERT(list)                                                                            \
    do {                                                                                            \
        enum listStatus status = listVerify(list);                                                   \
        if (status != LIST_SUCCESS) {                                                               \
            logPrint(L_ZERO, 1, "%s:%d, %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);            \
            logPrint(L_ZERO, 1, "List[%p] error occurred. Error code = %d\n", list, status);         \
            listDump(list);                                                                          \
            return status;                                                                          \
        }                                                                                           \
    } while(0)

/// @brief List assert used in functions returning custom error values
#define LIST_CUSTOM_ASSERT(list, ERR_VALUE)                                                          \
    do {                                                                                            \
        enum listStatus status = listVerify(list);                                                   \
        if (status != LIST_SUCCESS) {                                                               \
            logPrint(L_ZERO, 1, "%s:%d, %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);            \
            logPrint(L_ZERO, 1, "List[%p] error occurred. Error code = %d\n", list, status);         \
            listDump(list);                                                                          \
            return ERR_VALUE;                                                                       \
        }                                                                                           \
    } while(0)

#endif
