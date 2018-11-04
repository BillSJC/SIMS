/*
made by SJC in 2018.10.19
last edit 2018.10.20
for class 数据结构 only
*/

#define FILEPATH "D:\\数据结构\\第一次大作业\\src\\data.csv"
#define STRING_MAXLEN 200

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

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
    int   scoreChinese;
    //scoreMath
    int   scoreMath;
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
Student initStudent(char* stuno,char* name,int sex,char* phone,int scoreChinese,int scoreMath){
    Student stu;
    //if memory not enogh then return NULL
    char* stunoc = (char*)malloc(sizeof(char)*STRING_MAXLEN);
    strcpy(stunoc,stuno);
    char* namec = (char*)malloc(sizeof(char)*STRING_MAXLEN);
    strcpy(namec,name);
    char* phonec = (char*)malloc(sizeof(char)*STRING_MAXLEN);
    strcpy(phonec,phone);
    stu.stuno          = stunoc;
    stu.name           = namec;
    stu.phone          = phonec;
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
Head* insertNodeAtEnd(Head* head,Student data){
    Node* pn;
    pn = head->next;
    if(pn == NULL){
        head->next = initNode(data);
        head->next->last = NULL;
        return head;
    }
    while(pn->next != NULL){
        pn = pn->next;
    }
    pn->next = initNode(data);
    pn->next->last = pn;
    return head;
}

char*  strReplace(char* str){
    int i = 0;
    while(str[i]!='\0'){
        if(str[i]==','){
            str[i] = ' ';
        }
        i++;
    }
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
    int scoreC = 0;
    int scoreM = 0;
    Head* head = initEmptyList();
    FILE* fp ;
    fp = fopen(FILEPATH,"r");
    if(fp == NULL){
        head->next = NULL;
        return head;
    }
    while(!feof(fp)){
        fscanf(fp,"%s\n",temp);
        temp = strReplace(temp);
        sscanf(temp,"%s %s %s %d %d %d",stuno,name,phone,&sex,&scoreC,&scoreM);
        head = insertNodeAtEnd(head,initStudent(stuno,name,sex,phone,scoreC,scoreM));
    }
    fclose(fp);
    return head;
}

char* sexTransfer(int input){
    if(input){
        return "男";
    }else{
        return "女";
    }
}

void showStudentList(Head* head){
    int id = 0;
    printf("%6s|%10s|%10s|%15s|%5s|%10s|%10s\n","id","学号","姓名","手机","性别","语文","数学");
    Node* np = head->next;
    while(np != NULL){
        id++;
        printf("-------------------------------------------------------------------------------\n");
        printf("%6d|%10s|%10s|%15s|%5s|%10d|%10d\n",id,np->data.stuno,np->data.name,np->data.phone,sexTransfer(np->data.sex),np->data.scoreChinese,np->data.scoreMath);
        np = np->next;
    }
    char temp = getch();
}

void delSuccess(){
    printf("\n==================== 删除学生 ====================\n\n"
    "              删除成功，按任意键继续"
    "\n"
    "==================================================\n\n\n");
    getch();
    return;
}

void delFaild(){
    printf("\n==================== 删除学生 ====================\n\n"
    "              删除失败，按任意键继续"
    "\n"
    "==================================================\n\n\n");
    getch();
    return;
}

void deleteStudent(Head* head){
    system("cls");
    printf("\n==================== 删除学生 ====================\n\n"
    "              请输入要删除的id,并按回车键"
    "\n"
    "==================================================\n\n\n");
    showStudentList(head);
    int delid = 0;
    int i=0;
    int flag = 0;
    scanf("%d",&delid);
    Node* np = head->next;
    i = 1;
    if(delid == 1){
        if(head->next->next == NULL){
            head->next = NULL;
            delSuccess();
            return;
        }else{
            head->next = head->next->next;
            head->next->last = NULL;
            delSuccess();
            return;
        }
    }
    while(np != NULL){
        if(i == delid){
            if(np->next == NULL){
                np->last->next = NULL;
                delSuccess();
                return;
            }else{
                np->next->last = np->last;
                np->last->next = np->next;
                delSuccess();
                return;
            }
        }
        i++;
        np = np->next;
    }
    delFaild();
    return;
}

void addStudentMenu(Head* head){
    system("cls");
    printf("\n==================== 添加学生 ====================\n\n"
    "              请按照以下格式输入要添加的学生信息"
    "\n"
    "        学号,姓名,手机号,性别,语文成绩,数学成绩\n"
    "\n             输入完成后请按回车键，输入#返回上级菜单\n"
    "\n"
    "==================================================\n\n\n");
    char* stuno = (char*)malloc(sizeof(char)*STRING_MAXLEN);
    char* name = (char*)malloc(sizeof(char)*STRING_MAXLEN);
    char* phone = (char*)malloc(sizeof(char)*STRING_MAXLEN);
    int sex = 0;
    int temp = 0;
    char* temps = (char*)malloc(sizeof(char)*STRING_MAXLEN*5);
    int chinese = 0;
    int math = 0;
    while(1){
        scanf("%s",temps);
        if(strcmp(temps,"#")==0){
            return;
        }
        temps = strReplace(temps);
        temp = sscanf(temps,"%s %s %s %d %d %d",stuno,name,phone,&sex,&chinese,&math);\
        if(temp == 6){
            break;
        }
    }
    insertNodeAtEnd(head,initStudent(stuno,name,sex,phone,chinese,math));
    system("cls");
    printf("\n==================== 添加学生 ====================\n\n"
    "                   添加成功，按任意键返回"
    "\n"
    "==================================================\n\n\n");
    getch();
    return;
}

void showAllStuList(Head* head){
    while(1){
        system("cls");
        printf("\n==================== 学生列表 ====================\n\n"
        "                     1、列表排序\n"
        "                     2、修改信息\n"
        "                     3、添加学生\n"
        "                     4、删除学生\n\n"
        "                     0、返回\n"
        "==================================================\n\n\n");
        showStudentList(head);
        char temp = (char)getch();
        switch(temp){
            case '0':{
                system("cls");
                return;
            }
            case '1':{
                break;
            }
            case '2':{
                break;
            }
            case '3':{
                addStudentMenu(head);
                break;
            }
            case '4':{
                deleteStudent(head);
                break;
            }
        }
    }
    

}

void sortMenu(Head* head){
    char input;
    while(1){
        system("cls");
        printf("\n==================== 排序菜单 ====================\n\n"
        "                     1、学号升序\n"
        "                     2、学号降序\n"
        "                     3、语文升序\n"
        "                     4、语文降序\n"
        "                     5、数学升序\n"
        "                     6、数学降序\n\n"
        "                     0、返回\n"
        "==================================================\n\n\n");
        input = (char)getch();
        switch(input){
            case '1':{
                break;
            }
            case '2':{
                break;
            }
            case '3':{
                break;
            }
            case '4':{
                break;
            }
            case '5':{
                break;
            }
            case '6':{
                break;
            }
            case '0':{
                return;
            }
        }
    }
}

void saveToFile(Head* head){
    remove(FILEPATH);
    FILE* fp = fopen(FILEPATH,"w+");
    if(head->next == NULL){
        fclose(fp);
    }else{
        Node* np = head->next;
        while(np != NULL){
            fprintf(fp,"%s,%s,%s,%d,%d,%d",np->data.stuno,np->data.name,np->data.phone,np->data.sex,np->data.scoreChinese,np->data.scoreMath);
            if(np->next != NULL){
                fprintf(fp,"\n");
            }
            np = np->next;
        }
        fclose(fp);
    }
    return;
}

void mainMenu(Head* head){
    char input;
    int temp;
    while(1){
    system("cls");
    printf("==================== 学生信息管理系统 ====================\n"
"\n"
"                     1、学生列表\n"
"                     2、学生查询\n"
"                     3、添加学生\n"
"                     \n"
"                     0、退出系统\n");

    input = (char)getch();
    switch(input){
        case '1':{
            showAllStuList(head);
            break;
        };
        case '2':{
            break;
        }
        case '3':{
            addStudentMenu(head);
            break;
        }
        case '0':{
            saveToFile(head);
            exit(0);
        }
        default:{
            break;
        }
    }
    
    }
}

/* main
    the main function
*/
int main(){
    //system("chcp 65001"); //set output charset as GBK
    Head* stuList = readFromCSV();
    mainMenu(stuList);
    system("pause");
}