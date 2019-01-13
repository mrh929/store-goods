#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX 100//�����Ʒ���� 
int CurrentCnt = 0;//��ǰ��Ʒ���� 

#define MAX_ID_LEN 30
#define MAX_NAME_LEN 30
#define MAX_PRICE_LEN 30
#define MAX_DISCOUNT_LEN 30
typedef struct{//��Ʒ��Ϣ�ṹ 
    char	good_id[MAX_ID_LEN];
    char	good_name[MAX_NAME_LEN];
    int  	good_price;
    char	good_discount[MAX_DISCOUNT_LEN];
    int		good_amount;
    int		good_remain;
}GoodInfo;

typedef struct node{//��Ʒ������ 
    GoodInfo data;
    struct node *next;
}GoodList;

FILE *fp;//�ļ�ָ�����������ļ� 
int file_read(){
	fp = fopen("goodinfo.txt", "r");//��ȡ�ļ� 
	return fp != NULL;
}

void file_write(){
	fp= fopen("goodinfo.txt", "w");//д�ļ� 
}

void file_close(){
	fclose(fp);	//�ر��ļ� 
}

void pause(){
	system("pause");//��ͣ���밴��������� 
	system("cls");
}

bool check_nullfile(){//�����Ʒ�ļ��Ƿ���ڻ����Ƿ�Ϊ��
	if(file_read() && fgetc(fp) != EOF) return 0;//�ҵ��ļ� 
	else{
		file_write(); file_close();
		file_read();
		return 1;//û���ҵ��ļ� 
	}
}

//--------------------------------------------------------------------
//����һ����Ʒ��¼
//--------------------------------------------------------------------
GoodList* good_find(GoodList *L,char *p){//Ѱ��ĳ����Ʒ��Ϣ�����ҷ��ظ���Ʒ��ָ�� 
	while(L)
		if(strcmp(L->data.good_id, p) == 0) return L;
		else L = L->next;
	return NULL;//û�ҵ� 
}

void info_change(GoodList *L) {//������Ʒ��Ϣ 
	printf("�������µ���Ʒ��Ϣ��\n");
	printf("��ƷID��"); scanf("%s",L->data.good_id);
	printf("��Ʒ���ƣ�"); scanf("%s",L->data.good_name);
	printf("��Ʒ�۸�"); scanf("%d",&(L->data.good_price));
	printf("��Ʒ�ۿۣ�"); scanf("%s",L->data.good_discount);
	printf("��Ʒ������"); scanf("%d",&(L->data.good_amount));
	printf("��Ʒʣ�ࣺ"); scanf("%d",&(L->data.good_remain));
	return;
}

void info_change_NoRepeat(GoodList *p,GoodList *L) {//������Ʒ��Ϣ���������ظ� 
	printf("�������µ���Ʒ��Ϣ��\n");//pΪ������ָ�� �� LΪ�����ͷָ�� 
	printf("��ƷID��"); scanf("%s",p->data.good_id);
	while(good_find(L,p->data.good_id) != NULL){
		printf("��ƷID�Ѵ��ڣ����������룺\n");
		printf("��ƷID��"); scanf("%s",p->data.good_id);
	}
	
	printf("��Ʒ���ƣ�"); scanf("%s",p->data.good_name);
	printf("��Ʒ�۸�"); scanf("%d",&(p->data.good_price));
	printf("��Ʒ�ۿۣ�"); scanf("%s",p->data.good_discount);
	printf("��Ʒ������"); scanf("%d",&(p->data.good_amount));
	printf("��Ʒʣ�ࣺ"); scanf("%d",&(p->data.good_remain));
	return;
}


void Goodprint(GoodList *p){//��ӡ������Ʒ����ڵ����Ϣ 
	printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("ID:%s\t����:%s\t�۸�:%d\t�ۿ�:%s\t����:%d\tʣ��:%d\n",p->data.good_id,p->data.good_name,p->data.good_price,p->data.good_discount,p->data.good_amount,p->data.good_remain);
    printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
}

void info_init(GoodList **L){//��ȡ��Ʒ�ļ�goodinfo.txt������,����������L
	*L = NULL;
	CurrentCnt=0;
	
	if(check_nullfile())//����Ƿ�Ϊ�� 
		printf("��Ʒ�ļ������ڻ�Ϊ�գ����½�\n");
	else{
		GoodList *p, *now = NULL;
		while (!feof(fp)){//һֱѭ��ֱ�����ļ�����
			if(feof(fp)) break;
			p = (GoodList*) malloc(sizeof(GoodList));
			if(*L == NULL){//���p�ǵ�һ���ǿսڵ� 
				*L = p;
				now = p;//�ݴ�֮ǰ�Ľڵ� 
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
		if(now != NULL)	now->next = NULL;//��β�ڵ��е�ָ����0 
		
	}
	file_close();
}

void DelAll(GoodList **L){//ɾ����Ʒ�ļ��Լ���Ʒ�����е�������Ϣ
	char str[MAX_ID_LEN];
	printf("������������ļ�������ȷ���𣿣�Y/N����");
	scanf("%s",str);
	if(strcmp(str, "Y") != 0 && strcmp(str, "y") != 0){
		printf("������ȡ��\n\n");
		return; 
	}
	printf("�ٴ�ѯ�ʣ��⽫������ݵĶ�ʧ��ȷ���𣿣�Y/N����");
	scanf("%s",str);
	if(strcmp(str, "Y") != 0 && strcmp(str, "y") != 0){
		printf("������ȡ��\n\n");
		return; 
	}
	
	
	GoodList *p = *L, *now;
	while(p != NULL){//freeָ�� 
		now = p->next;
		free(p);
		p = now;
	}
	
	remove("goodinfo.txt");//��д�ļ�
	printf("�ɹ�ɾ����������\n\n");
	info_init(L);
}



//--------------------------------------------------------------------
//����ǰ��Ʒ�����е����ݴ�����Ʒ�ļ�goodinfo.txt�����̺���������L
//--------------------------------------------------------------------
void info_flush(GoodList **L){
	if(*L == NULL){
		remove("goodinfo.txt");//��д�ļ�
		return;//�������Ϊ�գ���ֱ��ɾ���ļ� 
	}
	file_write();
	GoodList *p = *L, *now;
	while(p != NULL){//freeָ��
		fprintf(fp, "%s\t%s\t%d\t%s\t%d\t%d",p->data.good_id,p->data.good_name,p->data.good_price,p->data.good_discount,p->data.good_amount,p->data.good_remain);
		now = p->next;
		if(now != NULL)
			fprintf(fp, "\n");
		free(p);
		p = now;
	}
	
}

void OutputAll(GoodList *L){//����Ļ�����������Ʒ��Ϣ
	while(L){
		Goodprint(L);
	    L = L -> next;
	}
}

void info_insert(GoodList **L) {//���뺯�� 
	GoodList *p = (GoodList*) malloc(sizeof(GoodList));
	GoodList *now = *L;
	
	int CHOICE;
	printf("��ѡ����뷽����\n");
	printf("\t1.ͷ�巨��\n");
	printf("\t2.β�巨��\n");
	printf("\t3.�м���룺\n\n");
	printf("��������ѡ��"); 
	
	scanf("%d",&CHOICE);
	switch(CHOICE){
		case 1:{//ͷ�巨 
			info_change_NoRepeat(p, *L);
			p->next = *L;
			*L = p;
			CurrentCnt++;
			printf("����ɹ���\n\n");
			break;
		}
		
		case 2:{//β�巨 
			info_change_NoRepeat(p, *L);
			if(*L == NULL) *L=p;
			else{
				while(now->next != NULL) now = now->next;
				now->next = p;
				p->next = NULL;//β�巨 
			}
			CurrentCnt++;
			printf("����ɹ���\n\n");
			break;
		}
		
		case 3:{//ѡ��λ�ò��� 
			char ID[MAX_ID_LEN];
			info_change_NoRepeat(p, *L);
			OutputAll(*L);
			printf("���ݿ�����ʾ\n");
			printf("������Ҫ������Ϣ���뵽�ĸ�ID���棺");
			
			scanf("%s",ID);
			
			GoodList *now;
			now=good_find(*L, ID);
			while(now == NULL){
				printf("û���ҵ���ID������������ID��");
				scanf("%s",ID);
				now=good_find(*L, ID);
			}
			p->next = now->next;
			now->next = p;
			
			printf("����ɹ���\n\n");
			CurrentCnt++;
			break;
		}
		
		
		
	} 
	return;
}

//--------------------------------------------------------------------
//ɾ��һ����Ʒ��¼
//--------------------------------------------------------------------
void info_dele(GoodList **L) {
	char ID[MAX_ID_LEN];
	GoodList *p;
	printf("������Ҫɾ������ƷID��");
	scanf("%s",ID);
	p = good_find(*L, ID);
	while(p == NULL){
		printf("δ�ҵ�����Ʒ������������ID��");
		scanf("%s",ID);
		p = good_find(*L, ID);
	}
	
	printf("\n��ȷ��Ҫɾ������Ʒ��Ĭ�Ϸ񣩣�(Y/N)��");
	scanf("%s",ID);//����ѡ�� 
	if(strcmp(ID, "Y") == 0||strcmp(ID, "y") == 0){
		if(*L == p){
			*L = p->next;
			free(p);
		}else{
			GoodList* now = *L;//Ѱ��p��Ʒ֮ǰ���Ǹ���� 
			while(now->next != p) now = now->next;
			now->next = p->next;
			free(p);
		}
		CurrentCnt--;
		printf("��ɾ��\n\n");
	}else printf("��ȡ��\n\n");
	return;
}


void menu_print(){
	printf("��Ʒ�������ļ��ѽ�������%d����Ʒ��¼\n", CurrentCnt);
	printf("****************************************\n");
	printf("1.��ʾ������Ʒ����Ϣ��\n");
	printf("2.�޸�ĳ����Ʒ����Ϣ��\n");
	printf("3.����ĳ����Ʒ����Ϣ��\n");
	printf("4.ɾ��ĳ����Ʒ����Ϣ��\n");
	printf("5.����ĳ����Ʒ����Ϣ��\n");
	printf("6.��Ʒ���̲��˳�ϵͳ��\n");
	printf("7.����Ʒ�۸��������\n");
	printf("8.(����)ɾ���������ݣ�\n");
	printf("�����������̲��˳�ϵͳ��\n");
	printf("****************************************\n");
	printf("��������ѡ��");
}

void good_swap(GoodList* a,GoodList* b){//����������Ʒ��λ�� 
	GoodList a_ = *a, b_ = *b;
	*a = b_;
	*b = a_;
	a->next = a_.next;
	b->next = b_.next;
	return;
}

void bubble_sort(GoodList **L){//ð������ 
    printf("����ð������...\n");
    for(int i=1;i<=CurrentCnt-1;i++){//һ����CurrentCnt��Ԫ�أ�Ҫð��n-1�� 
    	GoodList* now = *L;
    	while(now->next != NULL){
    		if(now->data.good_price > now->next->data.good_price)
    			good_swap(now, now->next);
    		now = now->next;
    	}
    	
    }
    printf("������ɣ�\n");
    OutputAll(*L);
}


int main(){
	char str[MAX_ID_LEN];
    int CHOICE;
    GoodList *Head,*p;
    Head=NULL;
    
    info_init(&Head);//��ȡ�ļ�
    
	do{
		printf("������Ʒ����ϵͳ\n");
		CHOICE=0;
		menu_print();//�˵� 
		
		scanf("%d",&CHOICE);//����ѡ�� 
		switch(CHOICE){
			case 1:{
				OutputAll(Head);
				pause();
				break;
			}
			
			case 2:{
				int ok=0;
				do{
					printf("��������Ҫ�޸ĵ���ƷID������-1�˳���:"); 
					scanf("%s",str);
					if(strcmp(str,"-1") == 0) break;
					p = good_find(Head, str);
					if(p == NULL) printf("\n�Բ���û���ҵ�����Ʒ������������:\n");
					else Goodprint(p),ok=1;
				}while(!p);
				
				if(ok){
					info_change(p);
					printf("\n�޸ĳɹ�!\n\n");
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
				printf("��������Ҫ��ѯ����ƷID:"); 
				scanf("%s",str);
				p = good_find(Head, str);
				if(p == NULL) printf("\n�Բ���û���ҵ�����Ʒ\n\n");
				else Goodprint(p);
				
				pause();
				break;
			}
			
			
			case 6:{
				char str[MAX_ID_LEN];
				printf("ȷ��Ҫ�����𣿣�Y/N����");
				scanf("%s",str);
				
				if(strcmp(str, "Y") == 0||strcmp(str, "y") == 0){
					info_flush(&Head);
					printf("����ɹ��������˳�ϵͳ\n");
					CHOICE=0;//�˳��ź� 
				}else{
					printf("��ȡ��\n");
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
				CHOICE=0;//�˳��ź� 
				printf("\n���������̲��˳�ϵͳ\n\n\n\n");
			}
		}
	}while(CHOICE);
		
	system("pause");
    return 0;
    
}

