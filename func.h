void createTable(char * dbName,char * tableName,struct StringList * attrList){
	FILE * fp;
	if(dbName==NULL){
		dbName = (char *)malloc(sizeof(char)*(1+strlen(dbInUse)));
		strcpy(dbName,dbInUse);
	}else{
		int dbFlag=0;
		DIR * dirp;
		struct dirent * dp;
		dirp = opendir(root);
		while ((dp = readdir(dirp)) != NULL){
				if ( !strcmp(dp->d_name, dbName)) {
				dbFlag=1;
				break;
			}
		}
		(void)closedir(dirp);
		if(!dbFlag){
			printf("Database:%s doesnot exist.\n",dbName);
			return;
		}
	}
	char path[100], tablename[100];
	strcpy(path,root);	strcat(path, "/");	strcat(path, dbName);	strcat(path,"/");
	strcpy(tablename,tableName);	strcat(tablename,".txt");
	DIR * dirp;
	struct dirent * dp;
	dirp = opendir(path);
	while ((dp = readdir(dirp)) != NULL){
		if ( !strcmp(dp->d_name, tablename)) {
			printf("Table:%s already exists in Database:%s.\n",tableName,dbName);
			(void)closedir(dirp);
			return;
		}
	}
	(void)closedir(dirp);

	path[0]='\0';	strcat(path,root);	strcat(path, "/");	strcat(path, dbName);	strcat(path,"/");	strcat(path, tableName);	strcat(path,".txt");
	fp =(FILE *) fopen( path,"a");
	fclose(fp);	
	path[0]='\0';	strcat(path,root);	strcat(path, "/");	strcat(path, dbName);	strcat(path,"/");strcat(path, tableName);strcat(path,"_metadata.txt");
	fp =(FILE *) fopen( path,"a");
	while(attrList){
		fputs(attrList->string1,fp);	fputs(":",fp);	fputs(attrList->string2,fp);	fputs("\t",fp);
		attrList = attrList->next;
	}
	fputs("\n",fp);
	fputs("0",fp);
	fclose(fp);	
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
	printf("Database-%s created succesfully.\n", dbName);
}

void useDb(char * dbName){
	dbInUse[0]='\0';
	strcpy(dbInUse,dbName);
	
	int flag=0;
	int len;
	DIR * dirp;
	struct dirent * dp;
	len = strlen(dbName);
	dirp = opendir(root);
	while ((dp = readdir(dirp)) != NULL){
			if ( !strcmp(dp->d_name, dbName)) {
			flag=1;
			break;
		}
	}
	if(!flag){
		printf("No Database with the name \"%s\" exists!\n" , dbName);
	}else{
		printf("Current database in use:%s\n",dbName);
	}
	(void)closedir(dirp);
	
	
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
