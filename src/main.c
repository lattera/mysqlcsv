#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "misc.h"
#include "sql.h"
#include "csv.h"

void usage(char *name)
{
    fprintf(stderr, "USAGE: %s <filename> <query>\n", name);
    exit(1);
}

int main(int argc, char *argv[])
{
    SQL_CTX *ctx;
    SQL_ROW *rows;

    if (argc != 3)
        usage(argv[0]);

    ctx = init_sql(DBHOST, DBUSER, DBPASSWORD, DBDATABASE);
    if (!(ctx)) {
        fprintf(stderr, "[-] Could not init MySQL. Exiting.\n");
        exit(1);
    }

    rows = runsql(ctx, argv[2]);
    if (!(rows))
        fprintf(stderr, "[-] Empty Set. Skipping CSV generation.\n");
    else
        convert_csv(rows, argv[1]);

    close_sql(ctx, 1, 1);

    return 0;
}
