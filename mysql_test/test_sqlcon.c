#include <stdio.h>
#include <mysql/mysql.h>

int main(void) {
    printf("launching...\n");

    // init
    MYSQL mysql;
    if (mysql_init(&mysql) == NULL) {
        printf("Error: cannot init MySQL.\n");
        exit(1);
    }
    
    // get mysql info
    mysql_real_connect(&mysql, "sql12.freemysqlhosting.net", "sql12648003", "JkuvVu9JjH", "sql12648003", 0, NULL, 0);
    printf("Client version: %s\n", mysql_get_client_info());
    printf("Server version: %s\n", mysql_get_server_info(&mysql));
    
    // query data
    //if (mysql_query(&mysql, "SELECT * FROM __keys__") != 0) {
    if (mysql_query(&mysql, "SELECT COUNT(*) > 0 FROM __keys__ WHERE __key__='abc123' AND __active__=0") != 0) {
        printf("Error: %s\n", mysql_error(&mysql));
        goto shutdown;
    }

    // retrieve results
    MYSQL_RES *res = mysql_store_result(&mysql);
    if (res == NULL) {
        printf("Error: %s\n", mysql_error(&mysql));
        goto shutdown;
    }

    int res_num_fields = mysql_num_fields(res);
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res)) != NULL) {
        for (int i = 0; i < res_num_fields; i++) {
            printf("%s ", row[i] ? row[i] : "NULL");
        }
        printf("\n");
    }
    mysql_free_result(res);
    
    if (mysql_query(&mysql, "UPDATE __keys__ SET __active__=1 WHERE __key__='abc123'") != 0) {
        printf("Error: %s\n", mysql_error(&mysql));
        goto shutdown;
    }

    // shutdown
shutdown:
    mysql_close(&mysql);
    printf("quitting... done.\n");
    return 0;
}


