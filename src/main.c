#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "misc.h"
#include "sql.h"
#include "linkedlist.h"
#include "ini.h"
#include "csv.h"

void usage(char *name)
{
    fprintf(stderr, "USAGE: %s <ini> <filename> <query>\n", name);
    exit(1);
}

int main(int argc, char *argv[])
{
    INI *ini;
    SQL_CTX *ctx;
    SQL_ROW *rows;
    SECTION *db;

    if (argc != 4)
        usage(argv[0]);

    ini = parse_ini(argv[1]);
    if (!(ini)) {
        fprintf(stderr, "[-] Could not open INI file. Exiting.\n");
        exit(1);
    }
    db = get_section(ini, "db");
    if (!(db)) {
        fprintf(stderr, "[-] No db section in INI file. Exiting.\n");
        exit(1);
    }

    ctx = init_sql(get_section_var(db, "host"),
            get_section_var(db, "user"),
            get_section_var(db, "password"),
            get_section_var(db, "db")
            );

    if (!(ctx)) {
        fprintf(stderr, "[-] Could not init MySQL. Exiting.\n");
        exit(1);
    }

    rows = runsql(ctx, argv[3]);
    if (!(rows))
        fprintf(stderr, "[-] Empty Set. Skipping CSV generation.\n");
    else
        convert_csv(rows, argv[2]);

    close_sql(ctx, 1, 1);
    free_ini(ini);

    return 0;
}
