#include <stdio.h>
#include <stdlib.h>
#include <list>
#include "error_debug.h"
#include "logger.h"
#include "cList.h"

int doublePrint(char *buffer, const void* a) {
    return sprintf(buffer, "%.3g", *(const double *)a);
}

int main() {
    logOpen("log.txt", L_HTML_MODE);
    setLogLevel(L_EXTRA);
    logDisableBuffering();
    cList_t list = {0};
    listCtor(&list, sizeof(double), doublePrint);
    LIST_DUMP(&list, "First dump");
    double a = 2.4, b = 3.2, c = 4.123;
    listClear(&list);

    listPushFront(&list, &b);
    listPushFront(&list, &c);
    LIST_DUMP(&list, "Pushed 2 elems");

    listPushBack(&list, &a);
    listInsertAfter(&list, 1, &a);

    LIST_DUMP(&list, "Some inserts");

    listIterator_t it = listFind(&list, &b);
    listInsertBefore(&list, it, &c);
    LIST_DUMP(&list, "Ded lox");

    listRemove(&list, 3);
    LIST_DUMP(&list, "Remove test");
    list.next[2] = 500;
    LIST_DUMP(&list, "List is broken here");

    listClear(&list);
    LIST_DUMP(&list, "Final goodbye");

    listDtor(&list);

    logClose();
    return 0;
}
