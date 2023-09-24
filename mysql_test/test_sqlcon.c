#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <mysql/mysql.h>

#define TMP_BUFLEN 1024

bool check_key_is_valid(MYSQL* mysql, const char* const key) {
    // create query
    char query[TMP_BUFLEN] = {0};
    snprintf(query, TMP_BUFLEN, "SELECT COUNT(*) > 0 FROM __keys__ WHERE __key__='%s' AND __active__=0", key);
    
    if (mysql_query(mysql, query) != 0) {
        printf("Error: %s\n", mysql_error(mysql));
        return false;
    }

    MYSQL_RES *res = mysql_store_result(mysql);
    if (res == NULL) {
        printf("Error: %s\n", mysql_error(mysql));
        return false;
    }

    int res_num_fields = mysql_num_fields(res);
    assert(res_num_fields == 1);
    MYSQL_ROW row;
    row = mysql_fetch_row(res);
    assert(row != NULL);
    if (row[0][0] == '1') return true;
    mysql_free_result(res);
    
    return false;
}

bool update_key_used(MYSQL* mysql, const char *const key) {
    // create query
    char query[TMP_BUFLEN] = {0};
    snprintf(query, TMP_BUFLEN, "UPDATE __keys__ SET __active__=1 WHERE __key__='%s'", key);
    
    if (mysql_query(mysql, query) != 0) {
        printf("Error: %s\n", mysql_error(mysql));
        return false;
    }
    return true;
}

int main(const int argc, const char *argv[]) {
    if (argc < 4) {
        printf("USAGE: ./test_sqlcon [dbname] [username] [password]\n");
        return 0;
    }
    printf("launching...\n");

    // prep
    const char *const dbname = argv[1];
    const char *const username = argv[2];
    const char *const password = argv[3];

    // init
    MYSQL mysql;
    if (mysql_init(&mysql) == NULL) {
        printf("Error: cannot init MySQL.\n");
        exit(1);
    }
    
    // get mysql info
    mysql_real_connect(&mysql, "sql12.freemysqlhosting.net", username, password, dbname, 0, NULL, 0);
    printf("Client version: %s\n", mysql_get_client_info());
    printf("Server version: %s\n", mysql_get_server_info(&mysql));
    
    // check that key exists and isn't used
    assert(check_key_is_valid(&mysql, "abc123"));
    assert(check_key_is_valid(&mysql, "abc456"));
    assert(check_key_is_valid(&mysql, "abc789"));
    
    // update key (it is used now)
    assert(update_key_used(&mysql, "abc123"));
    assert(update_key_used(&mysql, "abc789"));

    // check that key is invalid (it is used) 
    assert(!check_key_is_valid(&mysql, "abc123"));
    assert(check_key_is_valid(&mysql, "abc456"));
    assert(!check_key_is_valid(&mysql, "abc789"));
    
    //if (mysql_query(&mysql, "SELECT * FROM __keys__") != 0) {
    /*if (mysql_query(&mysql, "SELECT COUNT(*) > 0 FROM __keys__ WHERE __key__='abc123' AND __active__=0") != 0) {
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
    }*/

    // shutdown
shutdown:
    mysql_close(&mysql);
    printf("quitting... done.\n");
    return 0;
}


