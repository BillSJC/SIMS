/*
made by SJC in 2018.10.19
last edit 2018.10.20
for class 数据结构 only
*/

#define FILEPATH "data.csv"
#define STRING_MAXLEN 200

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

    /* student
        the struct of student infomation
        每个学生的信息包括：学号、姓名、性别、手机号码、数学分数、语文分数
    */
typedef struct Stu Student;
struct Stu{
    //stuno string
    char*   stuno;
    //name string
    char*   name;
    //sex int 1-man 0-women
    int     sex;
    //phoneNum string
    char*   phone;
    //scoreChinese float.2
    float   scoreChinese;
    //scoreMath
    float   scoreMath;
};


typedef struct node Node;
typedef Node Head;  //Head of swqlist
    /* node 
        the node struct of list
    */
struct node{
   Student data;
   //next node,end with NULL
   Node*    next;
   //last node,start with NULL
   Node*    last;
};

/* initStudent
    declear a new student student and give it value
*/
Student initStudent(char* stuno,char* name,int sex,char* phone,float scoreChinese,float scoreMath){
    Student stu;
    //if memory not enogh then return NULL
    stu.stuno          = stuno;
    stu.name           = name;
    stu.phone          = phone;
    stu.sex            = sex;
    stu.scoreChinese   = scoreChinese;
    stu.scoreMath      = scoreMath;
    return stu;
}

/* initEmptyList
    init an empty list and return Node*
*/
Head* initEmptyList(){
    Head* h =  (Head*)malloc(sizeof(Head));
    h->next = NULL;
    return h;
}

Node* initNode(Student st){
    Node* np = (Node*)malloc(sizeof(Node));
    np->data = st;
    np->next = NULL;
    np->last = NULL;
    return np;
}

/* insertNodeAtEnd
    insert a new node after current node and give it data
*/
int insertNodeAtEnd(Head* head,Student data){
    Node* pnp;
    pnp = initNode(data);
    Node* pn;
    pn = head->next;
    if(pn == NULL){
        head->next = pnp;
        head->next->last = NULL;
        return 2;
    }
    while(pn->next != NULL){
        pn = pn->next;
    }
    pn->next = pnp;
    pn->next->last = pn;
    return 1;
}

char*  strReplace(char* str){
    int i = 0;
    printf("RAW:%s\n",str);
    while(str[i]!='\0'){
        if(str[i]==','){
            str[i] = ' ';
        }
        i++;
    }
    printf("NOW:%s\n",str);
    return str;
}

/* readFromCSV
    open the csv files and read the data to the list
*/
Head* readFromCSV(){
    char* name = (char*)malloc(sizeof(char)*STRING_MAXLEN);
    char* stuno = (char*)malloc(sizeof(char)*STRING_MAXLEN);
    char* phone = (char*)malloc(sizeof(char)*STRING_MAXLEN);
    char* temp = (char*)malloc(sizeof(char)*STRING_MAXLEN*5);
    int sex = 0;
    float scoreC = 0.0;
    float scoreM = 0.0;
    Head* head = initEmptyList();
    FILE* fp ;
    fp = fopen("D:\\数据结构\\第一次大作业\\src\\data.csv","r");
    if(fp == NULL){
        printf("file poninter error,system will exit\n");
        system("pause");
        exit(0);
        
    }
    while(!feof(fp)){
        fscanf(fp,"%s\n",temp);
        temp = strReplace(temp);
        sscanf(temp,"%s %s %s %d %lf %lf",stuno,name,phone,&sex,&scoreC,&scoreM);
        insertNodeAtEnd(head,initStudent(stuno,name,sex,phone,scoreC,scoreM));
    }
    return head;
}

/* main
    the main function
*/
int main(){
    system("chcp 65001"); //set output charset as GBK
    Head* stuList = readFromCSV();
    int i = 0;
    Node* np = stuList->next;
    if(np != NULL){
        printf("%d:%s\n",i,np->data.name);
        np = np->next;
    }
    system("pause");
}