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
typedef struct Student{
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
}Student;


    /* node 
        the node struct of list
    */
typedef struct Node{
   Student* data;
   //next node,end with NULL
   Node*    next;
   //last node,start with NULL
   Node*    last;
}Node;

/* initStudent
    declear a new student student and give it value
*/
Student* initStudent(char* stuno,char* name,int sex,char* phone,float scoreChinese,float scoreMath){
    Student* stu = (Student*)malloc(sizeof(Student));
    //if memory not enogh then return NULL
    if(stu == NULL){
        return stu;
    }
    stu->stuno          = stuno;
    stu->name           = name;
    stu->phone          = phone;
    stu->sex            = sex;
    stu->scoreChinese   = scoreChinese;
    stu->scoreMath      = scoreMath;
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
int insertNodeAtNext(Node* n,Student* data){
    Node* temp = NULL;
    //if this node is not the end of list then store it
    if(n->next != NULL){
        temp = n->next;
    }
    n->next = (Node*)malloc(sizeof(Node));
    //if memory not enough then return 0
    if(n->next == NULL){
        return 0;
    }
    n->next->data = initStudent(data->stuno,data->name,data->sex,data->phone,data->scoreChinese,data->scoreMath);
    n->next->last = n;
    //if the temp isn`t null then set it after n->next
    if(temp != NULL){
        temp->last = n->next;
        n->next->next = temp;
    }
    return 1;
}



/* main
    the main function
*/
int main(){
    Node* listHeaed = initEmptyList();

}