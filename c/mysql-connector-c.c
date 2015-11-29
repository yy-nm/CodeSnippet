/*
	- author: mardyu<michealyxd@hotmail.com
	- create date: 11/25/2015
	- mysql version: 5.7
	- mysql connector version: 6.1.6
	- 主要功能: 实现一次 mysql 数据库连接并执行一句 sql 语句并返回结构
	- 调用方式: ./a.out {mysql-server-ip} {mysql-server-port} {db-name} {sql-str}
		- ./a.out 127.0.0.1 3306 "information_schema" "select * from CHARACTER_SETS;"
 */


#include <mysql.h>
#include <stdio.h>
#include <string.h>


int main(int argc, void **args)
{
	if (argc != 5)
	{
		perror("must have 4 args\n");
		return -1;
	}
	char *ip = (char *)args[1];
	int port = *((int*)args[2]);
	char *db_name = (char *) args[3];
	char *sql = (char *)args[4];

	
	MYSQL mysql;
	mysql_library_init(0, NULL, NULL);
	mysql_init(&mysql);
	
	if (!mysql_real_connect(&mysql, "127.0.0.1", "root", "helloworld"
					, db_name, 3306, NULL, 0))     {
		fprintf(stderr, "failed to connect mysql: error: %s\n"
					, mysql_error(&mysql));
		return -2;
	}
	
	
	if (mysql_real_query(&mysql, sql, strlen(sql))) {
		fprintf(stderr, "failed to query: %s, error: %s\n"
					, sql
					, mysql_error(&mysql));
		return -3;
	}
	
	MYSQL_RES *result;
	result = mysql_store_result(&mysql);
	if (result) {
		unsigned int field_count = mysql_num_fields(result);
		my_ulonglong row_count = mysql_num_rows(result);
		fprintf(stdout, "result: get %ld rows\n", row_count);
		MYSQL_ROW row;
		int i;
		while((row = mysql_fetch_row(result))) {
			for (i = 0; i < field_count; ++i) {
					fprintf(stdout, "[%s]\t"
							, row[i] ? row[i] : NULL);
			}
			fprintf(stdout, "\n");
		}
		fprintf(stdout, "query done!\n");
		
	} else {
		if (0 == mysql_field_count(&mysql)) {
			fprintf(stdout, "effect rows: %ld\n"
					, mysql_affected_rows(&mysql));
		} else {
			fprintf(stderr, "error: %s\n"
						, mysql_error(&mysql));
			return -4;
		}
	}

	mysql_free_result(result);
	result = NULL;
	
	mysql_close(&mysql);
	mysql_library_end();

	return 0;
}
