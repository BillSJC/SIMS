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

void sortSuccess(){
    system("cls");
    printf("\n==================== 学生排序 ====================\n\n"
    "                   排序完成，按任意键返回"
    "\n"
    "==================================================\n\n\n");
    getch();
    return;
}

void sortByStuno(Head* head,int esc){
    Student temp;
    int flag;
    Node* np = head->next;
    Node* np2 = head->next;
    for(np=head->next;np->next!=NULL;np=np->next){
        for(np2=np->next;np2!=NULL;np2=np2->next){
            flag = 0;
            if(atoi(np->data.stuno) > atoi(np2->data.stuno)){
                flag = 1;
            }
            if(esc){
                flag = 1 - flag;
            }
            if(flag){
                temp = np->data;
                np->data = np2->data;
                np2->data = temp;
            }
        }
    }
    sortSuccess();
    return;
}


void countPeople(Head* head){
    int people=0,man=0,women=0;
    float manp = 0.0,womenp = 0.0;
    Node* np = head->next;
    while(np!= NULL){
        people++;
        if(np->data.sex){
            man++;
        }else{
            women++;
        }
        np = np->next;
    }
    manp = ((float)man/(float)people)*100.0;
    womenp = ((float)women/(float)people)*100.0;
    system("cls");
    printf("\n==================== 人数统计 ====================\n\n"
    "                     总人数:%d人\n"
    "                     男生人数:%d人，占比%.2lf\n"
    "                     男生人数:%d人，占比%.2lf\n\n"
    "                     按任意键继续\n"
    "==================================================\n\n\n",people,man,manp,women,womenp);
    getch();
    return;
}

void countChinese(Head* head){
    int score=0,sec=0;
    int stemp = 0;
    system("cls");
    while(1){
        printf("\n==================== 语文统计 ====================\n\n"
        "                       分段线：筛选成绩的分段线\n"
        "                       以上/以下:输出分段线上还是下的人数\n"
        "                       0-以下，1-以上\n"
        "                       请按以下格式输入需要的参数\n\n"
        "                       {分段线} {以上/以下}\n\n"
        "==================================================\n\n\n");
        stemp = scanf("%d %d",&score,&sec);
        if(stemp||(sec!=1&&sec!=0)){
            break;
        }
        system("cls");
        printf("输入格式错误，请重试！\n\n");
    }
    Head* result = initEmptyList();
    Node* np = head->next;
    int count = 0;
    int flag = 0;
    while(np!=NULL){
        if(np->data.scoreChinese == score){
            insertNodeAtEnd(result,np->data);
            count++;
            np = np->next;
            continue;
        }
        if(np->data.scoreChinese > score){
            flag = 1;
        }
        if(sec == 0){
            flag = 1-flag;
        }
        if(flag){
            insertNodeAtEnd(result,np->data);
            count++;
        }
        np = np->next;
    }
    system("cls");
    char* strc;
    if(sec){
        strc = "以上";
    }else{
        strc = "以下";
    }
    printf("\n==================== 语文统计 ====================\n\n"
    "              在%d分%s的人共有%d个，具体情况如下\n\n"
    "                       按任意键继续\n"
    "==================================================\n\n\n",score,strc,count);
    showStudentList(result);
    getch();
}

void countMath(Head* head){
    int score=0,sec=0;
    int stemp = 0;
    system("cls");
    while(1){
        printf("\n==================== 数学统计 ====================\n\n"
        "                       分段线：筛选成绩的分段线\n"
        "                       以上/以下:输出分段线上还是下的人数\n"
        "                       0-以下，1-以上\n"
        "                       请按以下格式输入需要的参数\n\n"
        "                       {分段线} {以上/以下}\n\n"
        "==================================================\n\n\n");
        stemp = scanf("%d %d",&score,&sec);
        if(stemp||(sec!=1&&sec!=0)){
            break;
        }
        system("cls");
        printf("输入格式错误，请重试！\n\n");
    }
    Head* result = initEmptyList();
    Node* np = head->next;
    int count = 0;
    int flag = 0;
    while(np!=NULL){
        if(np->data.scoreMath == score){
            insertNodeAtEnd(result,np->data);
            count++;
            np = np->next;
            continue;
        }
        if(np->data.scoreMath > score){
            flag = 1;
        }
        if(sec == 0){
            flag = 1-flag;
        }
        if(flag){
            insertNodeAtEnd(result,np->data);
            count++;
        }
        np = np->next;
    }
    system("cls");
    char* strc;
    if(sec){
        strc = "以上";
    }else{
        strc = "以下";
    }
    printf("\n==================== 数学统计 ====================\n\n"
    "              在%d分%s的人共有%d个，具体情况如下\n\n"
    "                       按任意键继续\n"
    "==================================================\n\n\n",score,strc,count);
    showStudentList(result);
    getch();
}


void countMenu(Head* head){
    char input;
    while(1){
        system("cls");
        printf("\n==================== 学生统计 ====================\n\n"
        "                     1、统计总人数、男女比例\n"
        "                     2、统计语文成绩区间\n"
        "                     3、统计数学成绩区间\n"
        "                     0、返回\n"
        "==================================================\n\n\n");
        input = (char)getch();
        switch(input){
            case '1':{
                countPeople(head);
                break;
            }
            case '2':{
                countChinese(head);
                break;
            }
            case '3':{
                countMath(head);
                break;
            }
            case '0':{
                return;
            }
        }
    }
}


void sortByMath(Head* head,int esc){
    Student temp;
    int flag;
    Node* np = head->next;
    Node* np2 = head->next;
    for(np=head->next;np->next!=NULL;np=np->next){
        for(np2=np->next;np2!=NULL;np2=np2->next){
            flag = 0;
            if(np->data.scoreMath > np2->data.scoreMath){
                flag = 1;
            }
            if(esc){
                flag = 1 - flag;
            }
            if(flag){
                temp = np->data;
                np->data = np2->data;
                np2->data = temp;
            }
        }
    }
    sortSuccess();
    return;
}

void sortByChinese(Head* head,int esc){
    Student temp;
    int flag;
    Node* np = head->next;
    Node* np2 = head->next;
    for(np=head->next;np->next!=NULL;np=np->next){
        for(np2=np->next;np2!=NULL;np2=np2->next){
            flag = 0;
            if(np->data.scoreChinese > np2->data.scoreChinese){
                flag = 1;
            }
            if(esc){
                flag = 1 - flag;
            }
            if(flag){
                temp = np->data;
                np->data = np2->data;
                np2->data = temp;
            }
        }
    }
    sortSuccess();
    return;
}

void sortMenu(Head* head){
    char input;
    while(1){
        system("cls");
        printf("\n==================== 排序菜单 ====================\n\n"
        "                     1、学号升序\n"
        "                     2、学号降序\n"
        "                     3、语文降序\n"
        "                     4、语文升序\n"
        "                     5、数学升序\n"
        "                     6、数学降序\n\n"
        "                     0、返回\n"
        "==================================================\n\n\n");
        input = (char)getch();
        switch(input){
            case '1':{
                sortByStuno(head,1);
                return;
            }
            case '2':{
                sortByStuno(head,0);
                return;
            }
            case '3':{
                sortByChinese(head,1);
                return;
            }
            case '4':{
                sortByChinese(head,0);
                return;
            }
            case '5':{
                sortByMath(head,1);
                return;
            }
            case '6':{
                sortByMath(head,0);
                return;
            }
            case '0':{
                return;
            }
        }
    }
}

void addStudentMenu(Head* head){
    system("cls");
    printf("\n==================== 添加学生 ====================\n\n"
    "              请按照以下格式输入要添加的学生信息\n"
    "\n"
    "        学号,姓名,手机号,性别,语文成绩,数学成绩\n"
    "\n             性别:0-女，1-男"
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
        "                     4、删除学生\n"
        "                     5、学生统计\n\n"
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
                sortMenu(head);
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
            case '5':{
                countMenu(head);
                break;
            }
        }
    }
    

}

/**
 * 

 * 
*/

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

void editMenu(Head* head){
    system("cls");
    printf("\n==================== 修改信息 ====================\n\n"
    "                   请输入要修改的学号\n"
    "==================================================\n\n\n");
    char* temp = (char*)malloc(sizeof(char)*STRING_MAXLEN);
    scanf("%s",temp);
    Head* rs = initEmptyList();
    Node* np = head->next;
    Node* tar;
    while(np != NULL){
        if(strcmp(temp,np->data.stuno)==0){
            insertNodeAtEnd(rs,np->data);
            tar = np;
            break;
        }
        np = np->next;
    }
    if(rs->next == NULL){
        system("cls");
        printf("\n==================== 修改信息 ====================\n\n"
        "                   学号不存在，按任意键继续\n"
        "==================================================\n\n\n");
        getch();
        return;
    }
    system("cls");
    printf("\n==================== 修改信息 ====================\n\n"
    "        查询结果如下，按照以下格式输入新的数据\n\n"
    "        学号,姓名,手机号,性别,语文成绩,数学成绩\n"
    "\n             性别:0-女，1-男"
    "\n             输入完成后请按回车键，输入#返回上级菜单\n"
    "==================================================\n\n\n");
    showStudentList(rs);
    char* stuno = (char*)malloc(sizeof(char)*STRING_MAXLEN);
    char* name = (char*)malloc(sizeof(char)*STRING_MAXLEN);
    char* phone = (char*)malloc(sizeof(char)*STRING_MAXLEN);
    int sex = 0;
    int tempi = 0;
    char* temps = (char*)malloc(sizeof(char)*STRING_MAXLEN*5);
    int chinese = 0;
    int math = 0;
    scanf("%s",temps);
    if(strcmp(temps,"#")==0){
        return;
    }
    temps = strReplace(temps);
    tempi = sscanf(temps,"%s %s %s %d %d %d",stuno,name,phone,&sex,&chinese,&math);\
    if(tempi != 6){
        system("cls");
        printf("\n==================== 修改信息 ====================\n\n"
        "                   格式错误，按任意键返回...\n"
        "==================================================\n\n\n");
        getch();
        return;
    }
    tar->data = initStudent(stuno,name,sex,phone,chinese,math);
        system("cls");
        printf("\n==================== 修改信息 ====================\n\n"
        "                   修改成功，按任意键返回...\n"
        "==================================================\n\n\n");
        getch();
        return;
}

void searchMenu(Head* head){
    char input;
    Head* result;
    char** conds= (char**)malloc(sizeof(char*)*20);
    char* temp = (char*)malloc(sizeof(char)*STRING_MAXLEN);
    int* condi= (int*)malloc(sizeof(int)*20);
    int* condb= (int*)malloc(sizeof(int)*20);
    int condsc = 0;
    int tempi = 0;
    int flag;
    int i;
    int condri;
    //while(1){
        system("cls");
        printf("\n==================== 查询 ====================\n\n"
        "               请输入查找关键字和查找项\n"
        "                     1-学号\n"
        "                     2-姓名\n"
        "                     3-手机号\n"
        "                     4-性别(0-女，1-男)\n\n"
        "                     1-与\n"
        "                     2-或\n"
        "                     3-非\n"
        "                     格式如下:\n\n"
        "                  {与或非},{查找项},{查找关键字}\n\n"
        "                   输入#结束输入\n"
        "==================================================\n\n\n");
        while(1){
            conds[condsc] = (char*)malloc(sizeof(char)*STRING_MAXLEN);
            scanf("%s",temp);
            temp = strReplace(temp);
            if(strcmp(temp,"#")==0){
                break;
            }
            tempi = sscanf(temp,"%d %d %s",&condb[condsc],&condi[condsc],conds[condsc]);
            if(tempi != 3){
                printf("条件输入错误，请重新输入\n");
                continue;
            }else{
                condsc++;
                printf("条件输入成功");
            }
        }
    if(condsc==0){
        return;
    }
    //searchBody
    result = initEmptyList();
    Node* np = head->next;
    while(np != NULL){
        condri = 1;
        tempi = 0;
        for(i=0;i<condsc;i++){
            switch(condi[i]){
                case 1 :{
                    if(strcmp(np->data.stuno,conds[i])==0){
                        flag = 1;
                    }else{
                        flag = 0;
                    }
                    break;
                }
                case 2 :{
                    if(strcmp(np->data.name,conds[i])==0){
                        flag = 1;
                    }else{
                        flag = 0;
                    }
                    break;
                }
                case 3 :{
                    if(strcmp(np->data.phone,conds[i])==0){
                        flag = 1;
                    }else{
                        flag = 0;
                    }
                    break;
                }
            }
            switch(condb[i]){
                case 1:{
                    condri = condri&&flag;
                    break;
                }
                case 2:{
                    condri = condri||flag;
                    break;
                }
                case 3:{
                    condri = condri&&(!flag);
                    break;
                }
            }
        }
        if(condri == 1){
            insertNodeAtEnd(result,np->data);
        }
        np = np->next;
    }

    system("cls");
    printf("==================== 搜索结果 ====================\n"
    "\n               按任意键继续...\n\n");
    showStudentList(result);
    getch();
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
"                     4、学生统计\n"
"                     5、修改信息\n"
"                     \n"
"                     0、退出系统\n");

    input = (char)getch();
    switch(input){
        case '1':{
            showAllStuList(head);
            break;
        };
        case '2':{
            searchMenu(head);
            break;
        }
        case '3':{
            addStudentMenu(head);
            break;
        }
        case '4':{
            countMenu(head);
            break;
        }
        case '5':{
            editMenu(head);
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