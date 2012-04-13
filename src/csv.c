#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "misc.h"
#include "sql.h"

void convert_csv(SQL_ROW *rows, char *filename)
{
    SQL_ROW *row;
    SQL_COL *col;
    FILE *fp;
    char *p;
    int firstcol;

    fp = fopen(filename, "w");
    if (!(fp)) {
        perror("[-] Cannot open CSV file for writing");
        return;
    }

    for (row = rows; row != NULL; row = row->next) {
        firstcol = 1;
        for (col = row->cols; col != NULL; col = col->next) {
            if (!(col->data))
                continue;

            fprintf(fp, "%s\"", (firstcol) ? "" : ",");
            for (p = col->data; *p != 0x00; p++) {
                switch (*p) {
                    case '"':
                        fprintf(fp, "\"\"");
                        break;
                    default:
                        fprintf(fp, "%c", *p);
                        break;
                }
            }
            fprintf(fp, "\"");
            firstcol = 0;
        }
        fprintf(fp, "\n");
    }

    fclose(fp);

    sqldb_free_rows(rows);
}
