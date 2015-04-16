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
	path[0]='\0';	strcat(path,root);	strcat(path, "/");	strcat(path, dbName);	strcat(path,"/");	strcat(path, "metadata-tables.txt");
	fp =(FILE *) fopen(path,"a");
	fputs(tableName,fp);
	fputs("\n",fp);
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


void insert(char * tableName,struct StringList * columns,struct StringList * tuple){
	//1.see database in use
	//2.check if the table with tableName is present in database
	//3.check if columnnames are correct and note their respective datatypes
	//4.check if number of columns and dimension of tuple are one and the same
	//5.check if the tuples match their respective datatype
	//6.if yes insert.. if not leave an error message
	char path[100], tablename[100];	
	DIR * dirp;
	struct dirent * dp;
	//1.
	if(dbInUse[0]!='\0'){
		//2.

		path[0]='\0';	strcpy(path,root);	strcat(path, "/");	strcat(path, dbInUse);	strcat(path,"/");
		tablename[0]='\0';	strcpy(tablename,tableName);	strcat(tablename,".txt");
		int tableFlag=0;
		dirp = opendir(path);
		while ((dp = readdir(dirp)) != NULL){
			if ( !strcmp(dp->d_name, tablename)) {
				tableFlag=1;
				break;
			}
		}
		(void)closedir(dirp);
		if(tableFlag==0){
			printf("The table:%s doesnot exist in the database:%s.\n",tableName,dbInUse);
			return;
		}else{
			File * fp;
			path[0]='\0'; strcpy(path,root); strcat(path, "/"); strcat(path, dbInUse); strcat(path,"/"); strcat(path,tableName); strcat(path,"_metadata.txt");
			fp =(FILE *) fopen(path,"a");
			

		
		}
	
	}
	
	
	printf("tuple inserted\n");
}

struct StringList * makeStringNode(char * string1, char * string2){
	struct StringList * node = (struct StringList *) malloc(sizeof(struct StringList));
	if(string1!=NULL){
		node->string1 = (char *) malloc(sizeof(char)* (strlen(string1)+1));
		strcpy(node->string1,string1);
	}
	if(string2!=NULL){
		node->string2 = (char *) malloc(sizeof(char)* (strlen(string2)+1));
		strcpy(node->string2,string2);
	}
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
