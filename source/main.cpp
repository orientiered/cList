#include <stdio.h>
#include <stdlib.h>
#include <list>
#include "error_debug.h"
#include "logger.h"
#include "cList.h"

int main() {
    logOpen("log.txt", L_HTML_MODE);
    setLogLevel(L_EXTRA);
    logDisableBuffering();
    cList_t list = {0};
    listCtor(&list, sizeof(int));
    listDump(&list);
    int a = 2, b = 3, c = 4;
    listPushBack(&list, &c);
    listDump(&list);

    listPushFront(&list, &a);
    listDump(&list);

    listPushFront(&list, &b);
    listDump(&list);

    for (listIterator_t it = listFront(&list); it != NULL_LIST_IT; it = listNext(&list, it)) {
        printf("it = %ld: %d\n", it, *(int *)listGet(&list, it));
    }

    listPopBack(&list);
    listDump(&list);

    for (listIterator_t it = listFront(&list); it != NULL_LIST_IT; it = listNext(&list, it)) {
        printf("it = %ld: %d\n", it, *(int *)listGet(&list, it));
    }

    listPopBack(&list);
    listDump(&list);

    for (listIterator_t it = listFront(&list); it != NULL_LIST_IT; it = listNext(&list, it)) {
        printf("it = %ld: %d\n", it, *(int *)listGet(&list, it));
    }

    listPopBack(&list);
    listDump(&list);

    for (listIterator_t it = listFront(&list); it != NULL_LIST_IT; it = listNext(&list, it)) {
        printf("it = %ld: %d\n", it, *(int *)listGet(&list, it));
    }

    listPopBack(&list);
    listDump(&list);

    listDtor(&list);

    logClose();
    return 0;
}
