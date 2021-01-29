#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct bookInfo
{
	int No;          //书籍编号
	char name[20];   //书名
	char writer[20]; //作者
	float price;	 //书籍的价格
	int year;		 //购买日期
	int num;         //剩余数量
}book;

struct Node
{
	book data;
	struct Node* next;
};

struct Node* createHead();												  			    //创建表头
struct Node* createNode(book data);													    //创建节点 (在插入新的数据中使用)
struct Node* searchByName(struct Node* headNode, char* fileName);					    //搜索
void printList(struct Node* headNode);												    //打印链表
void insertNodeByHead(struct Node* headNode, book data);								//插入新的数据
void deleteNodeByNo(struct Node* headNode, int bookNo);									//删除数据
void sortNodeByPrice(struct Node* headNode);											//根据价格排序
void saveInfoToFile(const char* filename, struct Node* headNode);						//保存到文件
void readInfoFromFile(const char* filename, struct Node* headNode);						//读取文件
void makeMenu();																		//打印菜单
void keyDown();																			//键盘操作

struct Node* list = NULL;

int main()
{
	list = createHead();
	readInfoFromFile("bookinfo.txt", list);

	while (1)
	{
		makeMenu();
		keyDown();
		system("pause");
		system("cls");
	}

	system("pause");
	return 0;
}

//交互界面
void makeMenu()
{
	printf("+--------------------------------------+\n");
	printf("|        20级计算1班图书管理系统       |\n");
	printf("+--------------------------------------+\n");
	printf("\t1.浏览书籍\n");
	printf("\t2.登记书籍\n");
	printf("\t3.借阅书籍\n");
	printf("\t4.归还书籍\n");
	printf("\t5.书籍排序\n");
	printf("\t6.删除书籍\n");
	printf("\t7.查询书籍\n");
	printf("\t8.清空书库\n");
	printf("\t0.退出系统\n");
	printf("---------------------------------------\n");
	printf("请输入（0~8）：\n");
}

//键盘操作
void keyDown()
{
	int userkey = 0;
	book tempBook;
	struct Node* result = NULL;


	scanf("%d", &userkey);
	switch (userkey)
	{
	case 0:
		printf("【 退出 】\n");
		printf("退出成功！\n");
		system("pause");
		exit(0);
		break;
	case 1:
		printf("【 浏览 】\n");
		printList(list);
		break;
	case 2:
		printf("【 登记 】\n");
		printf("输入书籍的信息（No.,name,writer,price,time,num）:");
		scanf("%d %s %s %f %d %d", &tempBook.No, tempBook.name, tempBook.writer, &tempBook.price, &tempBook.year, &tempBook.num);
		insertNodeByHead(list, tempBook);
		saveInfoToFile("bookinfo.txt", list);
		printf("登记成功\n");
		break;
	case 3:
		printf("【 借阅 】\n");
		printf("请输入要借阅的书籍名：");
		scanf("%s", tempBook.name);
		result = searchByName(list, tempBook.name);
		if (result == NULL) {
			printf("没有相关书籍，无法借阅!\n");
		}
		else {
			if (result->data.num >= 1) {
				result->data.num--;
				printf("借阅成功！\n");
			}
			else {
				printf("当前书籍无库存,借阅失败！\n");
			}
		}
		break;
	case 4:
		printf("【 归还 】\n");
		printf("请输入要归还的书籍名：");
		scanf("%s", tempBook.name);
		result = searchByName(list, tempBook.name);
		if (result == NULL) {
			printf("该书不属于这里，你走错啦！\n");
		}
		else{
			result->data.num++;
			printf("归还成功！\n");
		}

		break;
	case 5:
		printf("【 排序 】\n");
		sortNodeByPrice(list);
		printList(list);
		break;
	case 6:
		printf("【 删除 】\n");
		printf("输入要删除的书籍编号NO.：");
		scanf("%d", &tempBook.No);
		deleteNodeByNo(list, tempBook.No);
		break;
	case 7:
		printf("【 查找 】\n");
		printf("请输入要查找的书名：");
		scanf("%s", tempBook.name);
		result = searchByName(list, tempBook.name);
		if (result == NULL) {
			printf("没找到！\n");
		}
		else {
			printf("编号\t书名\t\t\t作者\t\t\t价格\t\t\t购买年份\t\t剩余数量\n");
			printf("No.%d\t%-24s%-24s%.1f\t\t\t%d\t\t\t%d\n",result->data.No, result->data.name, result->data.writer,result->data.price, result->data.year,result->data.num);
		}
		break;
	case 8:
		printf("确定要清空书库吗？\n  1.YES\t2.NO\n");
		int answer;
		scanf("%d", &answer);
		if (answer == 1) {
			remove("bookinfo.txt");
			struct Node* p = list,*q=list;
			while (p!= NULL) {
				q = p->next;
				free(p);
				p = q;
			}
			list->next = NULL;
			printf("删除成功！");
			list = createHead();
			readInfoFromFile("bookinfo.txt", list);
		}
		else {
			printf("返回功能表\n");
		}
		break;
	default:
		printf(" error \n");
		break;
	}
}

//创建表头
struct Node* createHead()
{
	struct Node* headNode = (struct Node*)malloc(sizeof(struct Node));
	//headNode->data = 0;
	headNode->next = NULL;
	return headNode;
}

//创建结点
struct Node* createNode(book data)
{
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

struct Node* searchByName(struct Node* headNode, char* bookName)
{
	struct Node* posNode = headNode->next;
	while (posNode != NULL && strcmp(posNode->data.name, bookName)) {
		posNode = posNode->next;
	}
	return posNode;
}

//打印现存链表
void printList(struct Node* headNode)
{
	struct Node* pMove = headNode->next;
	printf("编号\t书名\t\t\t作者\t\t\t价格\t\t\t购买年份\t\t剩余数量\n");
	while (pMove!=NULL)
	{
		printf("No.%d\t%-24s%-24s%.1f\t\t\t%d\t\t\t%d\n", pMove->data.No,pMove->data.name,pMove->data.writer,pMove->data.price,pMove->data.year,pMove->data.num);
		pMove = pMove->next;
	}
	printf("\n");
}

//插入数据（表头法插入）
void insertNodeByHead(struct Node* headNode, book data)
{
	struct Node* newNode = createNode(data);
	newNode->next = headNode->next;
	headNode->next = newNode;
}

//根据编号删除
void deleteNodeByNo(struct Node* headNode, int bookNo)
{
	struct Node* posLeftNode = headNode;
	struct Node* posNode = headNode->next;
	while (posNode!=NULL&&bookNo!=posNode->data.No)
	{
		posLeftNode = posNode;
		posNode = posNode->next;
	}
	if (posNode == NULL) {
		printf("抱歉，没有找到这本书\n");
		return;
	}
	else
	{
		printf("删除成功\n");
		posLeftNode->next = posNode->next;
		free(posNode);
		posNode = NULL;
	}
}

void sortNodeByPrice(struct Node* headNode)
{
	struct Node *p,*q;
	for (p = headNode->next; p != NULL; p = p->next) {
		for (q = headNode->next; q->next!=NULL; q = q->next) {
			if (q->data.price > q->next->data.price) {
				book tempbook = q->data;
				q->data = q->next->data;
				q->next->data = tempbook;
			}
		}
	}
}

//写入文件
void saveInfoToFile(const char* filename, struct Node* headNode)
{
	FILE* fp = fopen(filename, "w");
	struct Node* pMove = headNode->next;
	while (pMove != NULL) {
		fprintf(fp, "%d\t%-24s%-24s%.1f\t\t\t%d\t\t\t%d\n", pMove->data.No,pMove->data.name, pMove->data.writer,pMove->data.price, pMove->data.year,pMove->data.num);
		pMove = pMove->next;
	}
	fclose(fp);
}

//读取文件
void readInfoFromFile(const char* filename, struct Node* headNode)
{
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		fp = fopen(filename, "w+");
	}
	struct bookInfo tempData;
	while (fscanf(fp, "%d\t%s%s\t\t\t%f\t\t\t%d\t\t\t%d\n", &tempData.No,tempData.name, tempData.writer,&tempData.price, &tempData.year,&tempData.num) != EOF) {
		insertNodeByHead(list, tempData);
	}
	fclose(fp);
}
