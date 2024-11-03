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
    listClear(&list);

    listPushFront(&list, &b);
    listPushFront(&list, &c);
    listDump(&list);

    listPushBack(&list, &a);
    listInsertAfter(&list, 1, &a);

    listDump(&list);

    listIterator_t it = listFind(&list, &b);
    listInsertBefore(&list, it, &c);

    listDump(&list);

    listRemove(&list, 3);
    listDump(&list);

    listClear(&list);
    listDump(&list);

    listDtor(&list);

    logClose();
    return 0;
}
