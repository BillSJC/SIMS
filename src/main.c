/*
made by SJC in 2018.10.19
last edit 2018.10.20
for class 数据结构 only
*/

#include<stdio.h>
#include<stdlib.h>

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
}Stu;


typedef struct node Node;
    /* node 
        the node struct of list
    */
struct node{
   Student data;
   //next node,end with NULL
   Node*    next;
   //last node,start with NULL
   Node*    last;
}node;

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
Node* initEmptyList(){
    return (Node*)malloc(sizeof(Node));
}

/* insertNodeAtNext
    insert a new node after current node and give it data
*/
int insertNodeAtEnd(Node* pn,Student data){
    //Node* pn = n;
    while(pn->next == NULL){
        pn = pn->next;
    }
    pn->next = (Node*)malloc(sizeof(Node));
    pn = pn->next;
    pn->next = NULL;
    pn->data = data;
}



/* main
    the main function
*/
int main(){
    Node* stuList = (Node*)malloc(sizeof(Node));
    insertNodeAtEnd(stuList,initStudent("17051823","SJC",1,"18258462816",80.0,85.0));
    printf("%s\n",stuList->next->data.name);
    system("pause");
}