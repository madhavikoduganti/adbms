void createTable(char * dbName,char * tableName,struct StringList * attrList){
/*	if(dbName==NULL){
		
	}
	struct Tables *table = (struct Tables *) malloc (sizeof(struct Tables));
	table->tableName = (char *)malloc(sizeof(char)*20);
	strcpy(table->tableName,tablename);
	table->next=NULL;

	if(tableHead==NULL){
		tableHead = table;
	}else{
		struct Tables * temp=tableHead;
		do{
			if(!strcmp(temp->tableName, table->tableName)){
				printf("table already exists!\n");
				break;
			}
			temp = temp->next;
		}while(temp->next);
		temp->next = table;
	}
*/	
	printf("table created\n");
}

void createDb(char * dbName){
	char path[100];
	FILE * fp;
//-------------------------check for existence of the database previously

	strcpy(path,root);
	int len;
	DIR * dirp;
	struct dirent * dp;
	len = strlen(dbName);
	dirp = opendir(root);
	while ((dp = readdir(dirp)) != NULL){
			if ( !strcmp(dp->d_name, dbName)) {
			(void)closedir(dirp);
			printf("Database already exists.\n");
			return;
		}
	}
	(void)closedir(dirp);
//-------------------------check for database completed


//-------------------------creation of database
	path[0]='\0';strcpy(path,root);
	int result = mkdir(strcat(path, dbName), 0777);	
	printf("Database-%s created.\n", dbName);
	path[0]='\0'; strcpy(path,root);strcat(path,dbName);strcat(path,"/metadata-tables.txt");
	fp =(FILE *) fopen( path,"a");
	fclose(fp);	
	path[0]='\0'; strcpy(path,root);strcat(path,dbName);strcat(path,"/metadata-users.txt");
	fp = fopen( path,"a");
	fclose(fp);		
//------------------------creation of database completed



//------------------------addition to metadata of root
	path[0]='\0';strcpy(path,root);strcat(path,"metadata_db.txt");
	fp = fopen(path ,"a");
	fputs( dbName, fp );
	fputs("\n",fp);
	fclose(fp);
	path[0]='\0';
//------------------------added to metadata of root
}

void useDb(char * dbName){

}

struct StringList * makeStringNode(char * string1, char * string2){
	struct StringList * node = (struct StringList *) malloc(sizeof(struct StringList));
	node->string1 = (char *) malloc(sizeof(char)* (strlen(string1)+1));
	strcpy(node->string1,string1);
	node->string2 = (char *) malloc(sizeof(char)* (strlen(string2)+1));
	strcpy(node->string2,string2);
	node->next=NULL;
	return node;
}


void makeStringList(struct StringList * head, struct StringList * rest){
	head->next=rest;
}

void printyoo(struct StringList * temp){
	while(temp){
		printf("%s -- %s\n",temp->string1,temp->string2);
		temp=temp->next;
	}
}
