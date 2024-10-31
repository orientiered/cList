#include <stdio.h>
#include <stdlib.h>
#include <list>
#include "error_debug.h"
#include "logger.h"
#include "cList.h"

int main() {
    logOpen();
    setLogLevel(L_EXTRA);
    logDisableBuffering();
    cList_t list = {0};
    listCtor(&list, sizeof(int));
    int a = 2, b = 3, c = 4;
    listPushBack(&list, &c);
    listPushFront(&list, &a);
    listPushFront(&list, &b);

    for (listIterator_t it = listFront(&list); it != NULL_LIST_IT; it = listNext(&list, it)) {
        printf("it = %ld: %d\n", it, *(int *)listGet(&list, it));
    }
    listDtor(&list);

    logClose();
    return 0;
}
