void makeTable(char * tablename){

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
	
	printf("table created\n");
}
