#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX 100//最大商品数量 
int CurrentCnt = 0;//当前商品数量 

#define MAX_ID_LEN 30
#define MAX_NAME_LEN 30
#define MAX_PRICE_LEN 30
#define MAX_DISCOUNT_LEN 30
typedef struct{//商品信息结构 
    char	good_id[MAX_ID_LEN];
    char	good_name[MAX_NAME_LEN];
    int  	good_price;
    char	good_discount[MAX_DISCOUNT_LEN];
    int		good_amount;
    int		good_remain;
}GoodInfo;

typedef struct node{//商品链表结点 
    GoodInfo data;
    struct node *next;
}GoodList;

FILE *fp;//文件指针用来操作文件 
int file_read(){
	fp = fopen("goodinfo.txt", "r");//读取文件 
	return fp != NULL;
}

void file_write(){
	fp= fopen("goodinfo.txt", "w");//写文件 
}

void file_close(){
	fclose(fp);	//关闭文件 
}

void pause(){
	system("pause");//暂停，请按任意键继续 
	system("cls");
}

bool check_nullfile(){//检查商品文件是否存在或者是否为空
	if(file_read() && fgetc(fp) != EOF) return 0;//找到文件 
	else{
		file_write(); file_close();
		file_read();
		return 1;//没有找到文件 
	}
}

//--------------------------------------------------------------------
//查找一条商品记录
//--------------------------------------------------------------------
GoodList* good_find(GoodList *L,char *p){//寻找某个商品信息，并且返回该商品的指针 
	while(L)
		if(strcmp(L->data.good_id, p) == 0) return L;
		else L = L->next;
	return NULL;//没找到 
}

void info_change(GoodList *L) {//更改商品信息 
	printf("请输入新的商品信息：\n");
	printf("商品ID："); scanf("%s",L->data.good_id);
	printf("商品名称："); scanf("%s",L->data.good_name);
	printf("商品价格："); scanf("%d",&(L->data.good_price));
	printf("商品折扣："); scanf("%s",L->data.good_discount);
	printf("商品数量："); scanf("%d",&(L->data.good_amount));
	printf("商品剩余："); scanf("%d",&(L->data.good_remain));
	return;
}

void info_change_NoRepeat(GoodList *p,GoodList *L) {//更改商品信息，不允许重复 
	printf("请输入新的商品信息：\n");//p为新增的指针 ， L为链表的头指针 
	printf("商品ID："); scanf("%s",p->data.good_id);
	while(good_find(L,p->data.good_id) != NULL){
		printf("商品ID已存在，请重新输入：\n");
		printf("商品ID："); scanf("%s",p->data.good_id);
	}
	
	printf("商品名称："); scanf("%s",p->data.good_name);
	printf("商品价格："); scanf("%d",&(p->data.good_price));
	printf("商品折扣："); scanf("%s",p->data.good_discount);
	printf("商品数量："); scanf("%d",&(p->data.good_amount));
	printf("商品剩余："); scanf("%d",&(p->data.good_remain));
	return;
}


void Goodprint(GoodList *p){//打印单个商品链表节点的信息 
	printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("ID:%s\t名称:%s\t价格:%d\t折扣:%s\t数量:%d\t剩余:%d\n",p->data.good_id,p->data.good_name,p->data.good_price,p->data.good_discount,p->data.good_amount,p->data.good_remain);
    printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
}

void info_init(GoodList **L){//读取商品文件goodinfo.txt的内容,并建立链表L
	*L = NULL;
	CurrentCnt=0;
	
	if(check_nullfile())//检查是否为空 
		printf("商品文件不存在或为空，已新建\n");
	else{
		GoodList *p, *now = NULL;
		while (!feof(fp)){//一直循环直到把文件读完
			if(feof(fp)) break;
			p = (GoodList*) malloc(sizeof(GoodList));
			if(*L == NULL){//如果p是第一个非空节点 
				*L = p;
				now = p;//暂存之前的节点 
			}else{ 
				now -> next = p;
				now = p;
			}
			
	    	fscanf(fp, "%s", p->data.good_id);
	    	fscanf(fp, "%s", p->data.good_name);
	    	fscanf(fp, "%d", &(p->data.good_price));
	    	fscanf(fp, "%s", p->data.good_discount);
	    	fscanf(fp, "%d", &(p->data.good_amount));
	    	fscanf(fp, "%d", &(p->data.good_remain));
	    	CurrentCnt++;
	    }
		if(now != NULL)	now->next = NULL;//把尾节点中的指针置0 
		
	}
	file_close();
}

void DelAll(GoodList **L){//删除商品文件以及商品链表中的所有信息
	char str[MAX_ID_LEN];
	printf("将会清除所有文件及链表，确定吗？（Y/N）：");
	scanf("%s",str);
	if(strcmp(str, "Y") != 0 && strcmp(str, "y") != 0){
		printf("操作已取消\n\n");
		return; 
	}
	printf("再次询问，这将造成数据的丢失，确定吗？（Y/N）：");
	scanf("%s",str);
	if(strcmp(str, "Y") != 0 && strcmp(str, "y") != 0){
		printf("操作已取消\n\n");
		return; 
	}
	
	
	GoodList *p = *L, *now;
	while(p != NULL){//free指针 
		now = p->next;
		free(p);
		p = now;
	}
	
	remove("goodinfo.txt");//重写文件
	printf("成功删除所有数据\n\n");
	info_init(L);
}



//--------------------------------------------------------------------
//将当前商品链表中的内容存入商品文件goodinfo.txt，存盘后销毁链表L
//--------------------------------------------------------------------
void info_flush(GoodList **L){
	if(*L == NULL){
		remove("goodinfo.txt");//重写文件
		return;//如果链表为空，就直接删除文件 
	}
	file_write();
	GoodList *p = *L, *now;
	while(p != NULL){//free指针
		fprintf(fp, "%s\t%s\t%d\t%s\t%d\t%d",p->data.good_id,p->data.good_name,p->data.good_price,p->data.good_discount,p->data.good_amount,p->data.good_remain);
		now = p->next;
		if(now != NULL)
			fprintf(fp, "\n");
		free(p);
		p = now;
	}
	
}

void OutputAll(GoodList *L){//在屏幕上输出所有商品信息
	while(L){
		Goodprint(L);
	    L = L -> next;
	}
}

void info_insert(GoodList **L) {//插入函数 
	GoodList *p = (GoodList*) malloc(sizeof(GoodList));
	GoodList *now = *L;
	
	int CHOICE;
	printf("请选择插入方法：\n");
	printf("\t1.头插法：\n");
	printf("\t2.尾插法：\n");
	printf("\t3.中间插入：\n\n");
	printf("输入您的选择："); 
	
	scanf("%d",&CHOICE);
	switch(CHOICE){
		case 1:{//头插法 
			info_change_NoRepeat(p, *L);
			p->next = *L;
			*L = p;
			CurrentCnt++;
			printf("插入成功！\n\n");
			break;
		}
		
		case 2:{//尾插法 
			info_change_NoRepeat(p, *L);
			if(*L == NULL) *L=p;
			else{
				while(now->next != NULL) now = now->next;
				now->next = p;
				p->next = NULL;//尾插法 
			}
			CurrentCnt++;
			printf("插入成功！\n\n");
			break;
		}
		
		case 3:{//选择位置插入 
			char ID[MAX_ID_LEN];
			info_change_NoRepeat(p, *L);
			OutputAll(*L);
			printf("数据库已显示\n");
			printf("请输入要将该信息插入到哪个ID后面：");
			
			scanf("%s",ID);
			
			GoodList *now;
			now=good_find(*L, ID);
			while(now == NULL){
				printf("没有找到该ID，请重新输入ID：");
				scanf("%s",ID);
				now=good_find(*L, ID);
			}
			p->next = now->next;
			now->next = p;
			
			printf("插入成功！\n\n");
			CurrentCnt++;
			break;
		}
		
		
		
	} 
	return;
}

//--------------------------------------------------------------------
//删除一条商品记录
//--------------------------------------------------------------------
void info_dele(GoodList **L) {
	char ID[MAX_ID_LEN];
	GoodList *p;
	printf("请输入要删除的商品ID：");
	scanf("%s",ID);
	p = good_find(*L, ID);
	while(p == NULL){
		printf("未找到该商品，请重新输入ID：");
		scanf("%s",ID);
		p = good_find(*L, ID);
	}
	
	printf("\n你确定要删除该商品吗（默认否）？(Y/N)：");
	scanf("%s",ID);//读入选项 
	if(strcmp(ID, "Y") == 0||strcmp(ID, "y") == 0){
		if(*L == p){
			*L = p->next;
			free(p);
		}else{
			GoodList* now = *L;//寻找p商品之前的那个结点 
			while(now->next != p) now = now->next;
			now->next = p->next;
			free(p);
		}
		CurrentCnt--;
		printf("已删除\n\n");
	}else printf("已取消\n\n");
	return;
}


void menu_print(){
	printf("商品的链表文件已建立，有%d个商品记录\n", CurrentCnt);
	printf("****************************************\n");
	printf("1.显示所有商品的信息：\n");
	printf("2.修改某个商品的信息：\n");
	printf("3.插入某个商品的信息：\n");
	printf("4.删除某个商品的信息：\n");
	printf("5.查找某个商品的信息：\n");
	printf("6.商品存盘并退出系统：\n");
	printf("7.对商品价格进行排序：\n");
	printf("8.(慎用)删除所有内容：\n");
	printf("其他，不存盘并退出系统：\n");
	printf("****************************************\n");
	printf("输入您的选择：");
}

void good_swap(GoodList* a,GoodList* b){//交换两个商品的位置 
	GoodList a_ = *a, b_ = *b;
	*a = b_;
	*b = a_;
	a->next = a_.next;
	b->next = b_.next;
	return;
}

void bubble_sort(GoodList **L){//冒泡排序 
    printf("正在冒泡排序...\n");
    for(int i=1;i<=CurrentCnt-1;i++){//一共有CurrentCnt个元素，要冒泡n-1次 
    	GoodList* now = *L;
    	while(now->next != NULL){
    		if(now->data.good_price > now->next->data.good_price)
    			good_swap(now, now->next);
    		now = now->next;
    	}
    	
    }
    printf("排序完成！\n");
    OutputAll(*L);
}


int main(){
	char str[MAX_ID_LEN];
    int CHOICE;
    GoodList *Head,*p;
    Head=NULL;
    
    info_init(&Head);//读取文件
    
	do{
		printf("超市商品管理系统\n");
		CHOICE=0;
		menu_print();//菜单 
		
		scanf("%d",&CHOICE);//输入选择 
		switch(CHOICE){
			case 1:{
				OutputAll(Head);
				pause();
				break;
			}
			
			case 2:{
				int ok=0;
				do{
					printf("请输入需要修改的商品ID（输入-1退出）:"); 
					scanf("%s",str);
					if(strcmp(str,"-1") == 0) break;
					p = good_find(Head, str);
					if(p == NULL) printf("\n对不起，没有找到该商品，请重新输入:\n");
					else Goodprint(p),ok=1;
				}while(!p);
				
				if(ok){
					info_change(p);
					printf("\n修改成功!\n\n");
				}
				pause();
				break;
			}
			
			case 3:{
				info_insert(&Head);
				pause();
				break;
			}
			
			case 4:{
				info_dele(&Head);
				pause();
				break;
			}
			
			case 5:{
				printf("请输入需要查询的商品ID:"); 
				scanf("%s",str);
				p = good_find(Head, str);
				if(p == NULL) printf("\n对不起，没有找到该商品\n\n");
				else Goodprint(p);
				
				pause();
				break;
			}
			
			
			case 6:{
				char str[MAX_ID_LEN];
				printf("确定要保存吗？（Y/N）：");
				scanf("%s",str);
				
				if(strcmp(str, "Y") == 0||strcmp(str, "y") == 0){
					info_flush(&Head);
					printf("保存成功，即将退出系统\n");
					CHOICE=0;//退出信号 
				}else{
					printf("已取消\n");
					pause();
				}
				break;
			}
			
			case 7:{
				bubble_sort(&Head);
				
				pause();
				break;
			}
			
			case 8:{
				DelAll(&Head);
				
				pause();
				break;
			}
			
			default:{
				CHOICE=0;//退出信号 
				printf("\n即将不存盘并退出系统\n\n\n\n");
			}
		}
	}while(CHOICE);
		
	system("pause");
    return 0;
    
}

