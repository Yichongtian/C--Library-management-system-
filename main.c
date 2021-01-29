#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct bookInfo
{
	int No;          //�鼮���
	char name[20];   //����
	char writer[20]; //����
	float price;	 //�鼮�ļ۸�
	int year;		 //��������
	int num;         //ʣ������
}book;

struct Node
{
	book data;
	struct Node* next;
};

struct Node* createHead();												  			    //������ͷ
struct Node* createNode(book data);													    //�����ڵ� (�ڲ����µ�������ʹ��)
struct Node* searchByName(struct Node* headNode, char* fileName);					    //����
void printList(struct Node* headNode);												    //��ӡ����
void insertNodeByHead(struct Node* headNode, book data);								//�����µ�����
void deleteNodeByNo(struct Node* headNode, int bookNo);									//ɾ������
void sortNodeByPrice(struct Node* headNode);											//���ݼ۸�����
void saveInfoToFile(const char* filename, struct Node* headNode);						//���浽�ļ�
void readInfoFromFile(const char* filename, struct Node* headNode);						//��ȡ�ļ�
void makeMenu();																		//��ӡ�˵�
void keyDown();																			//���̲���

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

//��������
void makeMenu()
{
	printf("+--------------------------------------+\n");
	printf("|        20������1��ͼ�����ϵͳ       |\n");
	printf("+--------------------------------------+\n");
	printf("\t1.����鼮\n");
	printf("\t2.�Ǽ��鼮\n");
	printf("\t3.�����鼮\n");
	printf("\t4.�黹�鼮\n");
	printf("\t5.�鼮����\n");
	printf("\t6.ɾ���鼮\n");
	printf("\t7.��ѯ�鼮\n");
	printf("\t8.������\n");
	printf("\t0.�˳�ϵͳ\n");
	printf("---------------------------------------\n");
	printf("�����루0~8����\n");
}

//���̲���
void keyDown()
{
	int userkey = 0;
	book tempBook;
	struct Node* result = NULL;


	scanf("%d", &userkey);
	switch (userkey)
	{
	case 0:
		printf("�� �˳� ��\n");
		printf("�˳��ɹ���\n");
		system("pause");
		exit(0);
		break;
	case 1:
		printf("�� ��� ��\n");
		printList(list);
		break;
	case 2:
		printf("�� �Ǽ� ��\n");
		printf("�����鼮����Ϣ��No.,name,writer,price,time,num��:");
		scanf("%d %s %s %f %d %d", &tempBook.No, tempBook.name, tempBook.writer, &tempBook.price, &tempBook.year, &tempBook.num);
		insertNodeByHead(list, tempBook);
		saveInfoToFile("bookinfo.txt", list);
		printf("�Ǽǳɹ�\n");
		break;
	case 3:
		printf("�� ���� ��\n");
		printf("������Ҫ���ĵ��鼮����");
		scanf("%s", tempBook.name);
		result = searchByName(list, tempBook.name);
		if (result == NULL) {
			printf("û������鼮���޷�����!\n");
		}
		else {
			if (result->data.num >= 1) {
				result->data.num--;
				printf("���ĳɹ���\n");
			}
			else {
				printf("��ǰ�鼮�޿��,����ʧ�ܣ�\n");
			}
		}
		break;
	case 4:
		printf("�� �黹 ��\n");
		printf("������Ҫ�黹���鼮����");
		scanf("%s", tempBook.name);
		result = searchByName(list, tempBook.name);
		if (result == NULL) {
			printf("���鲻����������ߴ�����\n");
		}
		else{
			result->data.num++;
			printf("�黹�ɹ���\n");
		}

		break;
	case 5:
		printf("�� ���� ��\n");
		sortNodeByPrice(list);
		printList(list);
		break;
	case 6:
		printf("�� ɾ�� ��\n");
		printf("����Ҫɾ�����鼮���NO.��");
		scanf("%d", &tempBook.No);
		deleteNodeByNo(list, tempBook.No);
		break;
	case 7:
		printf("�� ���� ��\n");
		printf("������Ҫ���ҵ�������");
		scanf("%s", tempBook.name);
		result = searchByName(list, tempBook.name);
		if (result == NULL) {
			printf("û�ҵ���\n");
		}
		else {
			printf("���\t����\t\t\t����\t\t\t�۸�\t\t\t�������\t\tʣ������\n");
			printf("No.%d\t%-24s%-24s%.1f\t\t\t%d\t\t\t%d\n",result->data.No, result->data.name, result->data.writer,result->data.price, result->data.year,result->data.num);
		}
		break;
	case 8:
		printf("ȷ��Ҫ��������\n  1.YES\t2.NO\n");
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
			printf("ɾ���ɹ���");
			list = createHead();
			readInfoFromFile("bookinfo.txt", list);
		}
		else {
			printf("���ع��ܱ�\n");
		}
		break;
	default:
		printf(" error \n");
		break;
	}
}

//������ͷ
struct Node* createHead()
{
	struct Node* headNode = (struct Node*)malloc(sizeof(struct Node));
	//headNode->data = 0;
	headNode->next = NULL;
	return headNode;
}

//�������
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

//��ӡ�ִ�����
void printList(struct Node* headNode)
{
	struct Node* pMove = headNode->next;
	printf("���\t����\t\t\t����\t\t\t�۸�\t\t\t�������\t\tʣ������\n");
	while (pMove!=NULL)
	{
		printf("No.%d\t%-24s%-24s%.1f\t\t\t%d\t\t\t%d\n", pMove->data.No,pMove->data.name,pMove->data.writer,pMove->data.price,pMove->data.year,pMove->data.num);
		pMove = pMove->next;
	}
	printf("\n");
}

//�������ݣ���ͷ�����룩
void insertNodeByHead(struct Node* headNode, book data)
{
	struct Node* newNode = createNode(data);
	newNode->next = headNode->next;
	headNode->next = newNode;
}

//���ݱ��ɾ��
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
		printf("��Ǹ��û���ҵ��Ȿ��\n");
		return;
	}
	else
	{
		printf("ɾ���ɹ�\n");
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

//д���ļ�
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

//��ȡ�ļ�
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
