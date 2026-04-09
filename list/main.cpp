#include <stdio.h>

#include "list.h"

int main()
{
    list_t list_1 = ListCtor(10);

    InsertAfter(&list_1, 0, "mama", 0);
    InsertAfter(&list_1, 1, "myla", 0);
    InsertAfter(&list_1, 2, "ramy", 0);

    for (int i = 1; i != 0; i = list_1.next[i])
        printf("[%c] ", list_1.data[i]);
    printf("\n\n");

    ListDump(&list_1, __FILE__, __FUNCTION__, __LINE__, "DUMP BEFORE INSERT");

    InsertAfter(&list_1, 2, "ochen", 0);
    InsertAfter(&list_1, 2, "dolgo", 0);
    InsertAfter(&list_1, 2, "aboba", 0);

    ListDump(&list_1, __FILE__, __FUNCTION__, __LINE__, "DUMP AFTER INSERT");

    return 0;
}
