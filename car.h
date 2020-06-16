//
// Created by 夏亦凡 on 2020/6/2.
//

#ifndef UNTITLED_CAR_H
#define UNTITLED_CAR_H

#include <stddef.h>
#include <python.h>

typedef struct Car {//结构体：具体车辆
    int rank;//车辆编号
    char car_number[10];//车牌号
    int typecode;//类型编号
    char carname[20];//车名
    char carspt[20];//挂挡类型
    float fare;//费用
    char situation;//是否被租
    struct Car *next_Car;
    struct Carorder *next_Carorder;
} Car;

typedef struct Cartype {//结构体：车辆类型
    char name[20];//类型名
    int typecode;//类型编号
    int num;//剩余数量
    struct Cartype *next_type;//下一种类
} Cartype;


typedef struct Carorder {
    char order_num[20];//订单号
    char id[20];//租车人身份证号
    char name[20];//租车人姓名
    char phone_num[20];//租车人电话号码
    int rank;//车辆编号
    char out_time[18];//租车时间
    char date_in_time[18];//预约还车时间
    float guarantee;//保证金
    char actual_in_time[18];//实际还车时间
    float predict_fare;//预约费用
    float actual_fare;//实际费用
    struct Carorder *next_Carorder;
} Carorder;

void count(Cartype *head1, Car *head2);

int vague_search(char *subject, char *object) {
    int len1 = strlen(subject);
    int len2 = strlen(object);
    int flag = 0;
    if (len2 > len1)return 0;
    for (int i = 0; i < (len1 - len2 + 1); i++)
        for (int j = 0; j < len2; j++) {
            if (subject[i + j] != object[j])
                break;
            if (j == len2 - 1)
                flag = 1;
        }
    return flag;
}


void Cartype_Add(Cartype *p, char *name, int num) {//增加一个车类
    while (p->next_type != NULL) {
        p = p->next_type;//找到尾节点
        if (!(strcmp(p->name, name))) {
            printf("已存在\n");
            return;
        }
    }
    p->next_type = (Cartype *) malloc(sizeof(Cartype));//分配
    if (p->typecode < 10 && p->typecode > 0)
        p->next_type->typecode = p->typecode + 1;//编号+1
    else
        p->typecode = 1;
    p->next_type->num = num;
    strcpy(p->next_type->name, name);//使用strcpy实现将参数中的字符串赋给该车类型的名称
}

void Cartype_Delete(Cartype *head, char *p) {
    Cartype *q = head;
    while (q->next_type != NULL && strcmp(q->next_type->name, p))//strcmp搜索参数中的类型名
        q = q->next_type;//定位所删除的车辆类型的前一个类型
    if (q->next_type == NULL)//没找到
    {
        printf("not found!");
        return;
    }
    q->next_type = q->next_type->next_type;//将head->next变为next->next即删除中间的类型
}

void Cartype_name_Edit(Cartype *head, char *p)//没写完
{
    while (head->next_type != NULL && strcmp(head->next_type->name, p))
        head = head->next_type;
    if (head->next_type != NULL) {
        char newname[20]={};
        printf("请修改类型名称\n");
        scanf("%s", newname);
        strcpy(head->next_type->name, newname);
        printf("请修改所属车辆数量");
        scanf("%d",&(head->next_type->num));
    } else
        printf("not found\n");getchar();
}

void Car_Add(Cartype *head1, Car *head) {
    Car *newcar = (Car *) malloc(sizeof(Car));
    printf("添加新车\n");
    printf("请输入车名\n");
    scanf("%s", newcar->carname);
    printf("请输入车牌号\n");
    scanf("%s", newcar->car_number);
    printf("请输入挂档类型\n");
    scanf("%s", newcar->carspt);
    printf("请输入日租\n");
    scanf("%f", &(newcar->fare));
    printf("请输入车辆类型编号\n");
    scanf("%d", &(newcar->typecode));
    printf("请输入车辆租用状态\n");
    getchar();
    scanf("c", &(newcar->situation));
    newcar->situation = 'n';
    newcar->next_Car = NULL;
    newcar->next_Carorder = NULL;
    Car *p=head;
    while (p->next_Car != NULL)
        p = p->next_Car;
    newcar->rank = p->rank + 1;
    p->next_Car = newcar;
    count(head1, head);
}

void Car_Delete(struct Car *head, int rank) {
    Car *p = head;
    Carorder* m=NULL;
    while (p->next_Car != NULL && p->next_Car->rank != rank)
        p = p->next_Car;
    if (p->next_Car == NULL) {
        printf("not found");
        return;
    } else {
        Car *q = p->next_Car;
        p->next_Car = p->next_Car->next_Car;
        free(q);
        while(p->next_Car!=NULL)
        {
            p->next_Car->rank-=1;
            m=p->next_Car->next_Carorder;
            while(m!=NULL)
            {m->rank-=1;
            m=m->next_Carorder;}
            p=p->next_Car;
        }
    }
}

void Car_Edit(Car *head, int rank) {
    Car *q = head->next_Car;
    while (q != NULL && q->rank!=rank)
        q = q->next_Car;
    if (q) {
        printf("你想要修改什么?1.租用状态 2.日租费用 3.车辆名称 4.车牌号 5.挂挡类型 6.车辆类型编码 \n");
        int flag;
        scanf("%d", &flag);
        a:while(flag>6||flag<1)scanf("%d", &flag);
        switch (flag) {
            case 1:
                printf("更新租用状态\n");getchar();
                scanf("%c", &(q->situation));
                break;
            case 2:
                printf("更新日租\n");
                scanf("%f", &(q->fare));
                break;
            case 3:
                printf("更新车辆名称\n");
                scanf("%s", q->carname);
                break;
            case 4:
                printf("更新车牌号\n");
                scanf("%s", q->car_number);
                break;
            case 5:
                printf("更新挂挡类型\n");
                scanf("%s", q->carspt);
                break;
            case 6:
                printf("更新车辆类型编码\n");
                scanf("%s", &(q->typecode));
                break;
        }printf("你想要继续修改么?1.租用状态 2.日租费用 3.车辆名称 4.车牌号 5.挂挡类型 6.车辆类型编码 0.退出 \n");
        scanf("%d",&flag);
        if(flag!=0)goto a;
    } else printf("not found");
}


void Cartype_load(Cartype *head) {if (head->next_type != NULL){printf("已加载过\n");return;}
    FILE *fp = NULL;
    char filename[200]="/Users/xiayifan/Desktop/程序设计综合课程设计(2020春)/程序设计综合课程设计(2020春)/任务二数据/¥Ú∞¸/车辆类型.csv";
    //printf("请输入文件路径\n");
    //scanf("%s",filename);getchar();
    fp = fopen(filename, "r");
    if(fp==NULL){printf("未找到文件\n");return;}
    char s[50];
    fscanf(fp, "%s", s);
    Cartype *p = head;
    while (p->next_type = (Cartype *) malloc(sizeof(Cartype))) {
        if (fscanf(fp, "%d", &(p->next_type->typecode)) == EOF) {
            p->next_type = NULL;
            break;
        }
        fgetc(fp);
        for (int i = 0;; i++) {
            fscanf(fp, "%c", &(p->next_type->name[i]));
            if (p->next_type->name[i] == ',') {
                p->next_type->name[i] = NULL;
                break;
            }
        }
        fscanf(fp, "%d", &(p->next_type->num));
        fgetc(fp);
        fgetc(fp);
        p->next_type->next_type = NULL;
        p = p->next_type;
    }
    fclose(fp);
}

void Car_load(Car *head) {
    if (head->next_Car != NULL){printf("已加载过\n");return;}
    FILE *fp = NULL;
    char filename[200]="/Users/xiayifan/Desktop/程序设计综合课程设计(2020春)/程序设计综合课程设计(2020春)/任务二数据/¥Ú∞¸/车辆基本信息.csv";
    //printf("请输入文件路径\n");
    //scanf("%s",filename);getchar();
    fp = fopen(filename, "r");
    if(fp==NULL){printf("未找到文件\n");return;}
    char s[200] = "";
    fscanf(fp, "%s", s);
    Car *p = head;
    if (head->next_Car != NULL)return;
    while (1) {
        Car *new_car = (Car *) malloc(sizeof(Car));
        if (fscanf(fp, "%d", &(new_car->rank)) == EOF)
            break;
        fgetc(fp);
        for (int i = 0;; i++) {
            fscanf(fp, "%c", &(new_car->car_number[i]));
            if (new_car->car_number[i] == ',') {
                new_car->car_number[i] = NULL;
                break;
            }
        }
        fscanf(fp, "%d", &(new_car->typecode));
        fgetc(fp);
        for (int i = 0;; i++) {
            fscanf(fp, "%c", &(new_car->carname[i]));
            if (new_car->carname[i] == ',') {
                new_car->carname[i] = NULL;
                break;
            }
        }
        for (int i = 0;; i++) {
            fscanf(fp, "%c", &(new_car->carspt[i]));
            if (new_car->carspt[i] == ',') {
                new_car->carspt[i] = NULL;
                break;
            }
        }
        fscanf(fp, "%f", &(new_car->fare));
        fgetc(fp);
        fscanf(fp, "%c", &(new_car->situation));
        fgetc(fp);
        fgetc(fp);
        new_car->next_Car = NULL;
        new_car->next_Carorder = NULL;
        p->next_Car = new_car;
        p = p->next_Car;
    }
    fclose(fp);
}

void Carorder_load(Car *head) {
    if (head->next_Car->next_Carorder != NULL){printf("已加载过\n");return;}
    FILE *fp = NULL;
    char filename[200]="/Users/xiayifan/Desktop/程序设计综合课程设计(2020春)/程序设计综合课程设计(2020春)/任务二数据/¥Ú∞¸/订单信息.csv";
    //printf("请输入文件路径\n");
    //scanf("%s",filename);getchar();
    fp = fopen(filename, "r");
    if(fp==NULL){printf("未找到文件\n");return;}
    char s[500] = "";
    fscanf(fp, "%s", s);fgetc(fp);fgetc(fp);
    Car *p = head;
    while (1) {
        Carorder *new_carorder = (Carorder *) malloc(sizeof(Carorder));
        new_carorder->next_Carorder=NULL;
        if (fscanf(fp, "%c", &(new_carorder->order_num[0])) == EOF)//判断文件尾
            break;
        else
            for (int i = 1;; i++)//读订单编号
            {
                fscanf(fp, "%c", &(new_carorder->order_num[i]));
                if (new_carorder->order_num[i] == ',') {
                    new_carorder->order_num[i] = NULL;
                    break;
                }
            }
        for (int i = 0;; i++)//读身份证号
        {
            fscanf(fp, "%c", &(new_carorder->id[i]));
            if (new_carorder->id[i] == ',') {
                new_carorder->id[i] = NULL;
                break;
            }
        }
        for (int i = 0;; i++)//读租车人姓名
        {
            fscanf(fp, "%c", &(new_carorder->name[i]));
            if (new_carorder->name[i] == ',') {
                new_carorder->name[i] = NULL;
                break;
            }
        }
        for (int i = 0;; i++)//读租车人电话
        {
            fscanf(fp, "%c", &(new_carorder->phone_num[i]));
            if (new_carorder->phone_num[i] == ',') {
                new_carorder->phone_num[i] = NULL;
                break;
            }
        }
        fscanf(fp, "%d", &(new_carorder->rank));
        fgetc(fp);
        for (int i = 0;; i++)//取车时间
        {
            fscanf(fp, "%c", &(new_carorder->out_time[i]));
            if (new_carorder->out_time[i] == ',') {
                new_carorder->out_time[i] = NULL;
                break;
            }
        }
        for (int i = 0;; i++)//预约还车时间
        {
            fscanf(fp, "%c", &(new_carorder->date_in_time[i]));
            if (new_carorder->date_in_time[i] == ',') {
                new_carorder->date_in_time[i] = NULL;
                break;
            }
        }
        fscanf(fp, "%f", &(new_carorder->guarantee));
        fgetc(fp);
        for (int i = 0;; i++)//real还车时间
        {
            fscanf(fp, "%c", &(new_carorder->actual_in_time[i]));
            if (new_carorder->actual_in_time[i] == ',') {
                new_carorder->actual_in_time[i] = NULL;
                break;
            }
        }
        fscanf(fp, "%f", &(new_carorder->predict_fare));
        fgetc(fp);
        fscanf(fp, "%f", &(new_carorder->actual_fare));
        fgetc(fp);
        fgetc(fp);
        Carorder *m = NULL;
        while (p->next_Car != NULL && p->rank != new_carorder->rank)
            p = p->next_Car;
        if (p->next_Carorder == NULL)
            p->next_Carorder = new_carorder;
        else {
            m = p->next_Carorder;
            while (m->next_Carorder != NULL)
                m = m->next_Carorder;
            m->next_Carorder = new_carorder;
        }
        p=head->next_Car;
    }
    fclose(fp);
}

void count(Cartype *head1, Car *head2) {
    Cartype *p = head1;
    Car *q = head2;
    int typecode;
    while (p->next_type != NULL) {
        p = p->next_type;
        p->num = 0;
    }
    p = head1;
    while (q->next_Car != NULL) {
        q = q->next_Car;
        while (p->next_type != NULL) {
            p = p->next_type;
            if (p->typecode == q->typecode) {
                p->num += 1;
                p = head1;
                break;
            }
        }
    }
}

void Carorder_add(Cartype *head1, Car *head) {
    Carorder *new_order = (Carorder *) malloc(sizeof(Carorder));
    printf("输入订单号\n");
    scanf("%s", new_order->order_num);
    printf("输入身份证号\n");
    scanf("%s", new_order->id);
    printf("输入租车人姓名\n");
    scanf("%s", new_order->name);
    printf("输入租车人手机号\n");
    scanf("%s", new_order->phone_num);
    printf("输入车辆编号\n");
    scanf("%d", &(new_order->rank));
    printf("输入取车时间\n");
    scanf("%s", new_order->out_time);
    printf("输入预约还车时间\n");
    scanf("%s", new_order->date_in_time);
    printf("输入保证金\n");
    scanf("%f", &(new_order->guarantee));
    printf("输入实际还车时间\n");
    scanf("%s", new_order->actual_in_time);
    printf("输入预计费用\n");
    scanf("%f", &(new_order->predict_fare));
    printf("输入实际费用\n");
    scanf("%f", &(new_order->actual_fare));
    Car *p = head;
    Carorder *m = NULL;
    while (p->next_Car != NULL && p->rank != new_order->rank)
        p = p->next_Car;
    if (p->next_Carorder == NULL)
        p->next_Carorder = new_order;
    else {
        m = p->next_Carorder;
        while (m->next_Carorder != NULL)
            m = m->next_Carorder;
        m->next_Carorder = new_order;
    }
    count(head1, head);
}

void Carorder_delete(Car *head,char *ordernum)
{
    Car *p=head->next_Car;
    Carorder *q=(Carorder*)malloc(sizeof(Carorder));
    while(p!=NULL)
    {
        q=p->next_Carorder;
        if(q==NULL){p=p->next_Car;
            continue;}
        if(!strcmp(q->order_num,ordernum))
            {p->next_Carorder=p->next_Carorder->next_Carorder;return;}
        else
            while(q->next_Carorder!=NULL&&strcmp(q->next_Carorder->order_num,ordernum))
                q=q->next_Carorder;
         if(q->next_Carorder!=NULL)   {q->next_Carorder=q->next_Carorder->next_Carorder;return;}
         p=p->next_Car;
    }
    printf("not found");return;
}

void Carorder_edit(Car *head,char *ordernum){
    Car *p=head->next_Car;
    Carorder *q=(Carorder*)malloc(sizeof(Carorder));
    int op=0;
    while(p!=NULL)
    {
        q=p->next_Carorder;
        if(q==NULL){p=p->next_Car;
            continue;}
        if(!strcmp(q->order_num,ordernum))
        {   printf("请输入需要编辑的订单内容：1.订单编号 2.身份证号 3.客人姓名 4.手机号码 5.租用车辆编号 6.取车时间 7.预约还车时间 8.押金 "
                   "9.实际还车时间 10.应缴费用 11.实缴费用\n");
            while(scanf("%d",&op)&&op!=0){
            switch(op){
                case 1:
                printf("输入订单号\n");
                scanf("%s", q->order_num);
                break;
                case 2:
                printf("输入身份证号\n");
                scanf("%s", q->id);
                break;
                case 3:
                printf("输入租车人姓名\n");
                scanf("%s", q->name);
                    break;
                case 4:
                printf("输入租车人手机号\n");
                scanf("%s", q->phone_num);
                    break;
                case 5:
                printf("输入车辆编号\n");
                scanf("%d", &(q->rank));
                    break;
                case 6:
                printf("输入取车时间\n");
                scanf("%s", q->out_time);
                    break;
                case 7:
                printf("输入预约还车时间\n");
                scanf("%s", q->date_in_time);
                    break;
                case 8:
                printf("输入保证金\n");
                scanf("%f", &(q->guarantee));
                    break;
                case 9:
                printf("输入实际还车时间\n");
                scanf("%s", q->actual_in_time);
                    break;
                case 10:
                printf("输入预计费用\n");
                scanf("%f", &(q->predict_fare));
                    break;
                case 11:
                printf("输入实际费用\n");
                scanf("%f", &(q->actual_fare));
                    break;
            }
            printf("1.订单编号 2.身份证号 3.客人姓名 4.手机号码 5.租用车辆编号 6.取车时间 7.预约还车时间 8.押金 \"\n"
                   "                   \"9.实际还车时间 10.应缴费用 11.实缴费用停止修改请输入0");}
            return;}
        else
            while(q->next_Carorder!=NULL&&strcmp(q->next_Carorder->order_num,ordernum))
                q=q->next_Carorder;
        if(q->next_Carorder!=NULL)   {
            {   printf("请输入需要编辑的订单内容：1.订单编号 2.身份证号 3.客人姓名 4.手机号码 5.租用车辆编号 6.取车时间 7.预约还车时间 8.押金 "
                       "9.实际还车时间 10.应缴费用 11.实缴费用 0.结束修改\n");
                while(scanf("%d",&op)&&op!=0){
                    switch(op){
                        case 0:
                            return;
                        case 1:
                            printf("输入订单号\n");
                            scanf("%s", q->next_Carorder->order_num);
                            break;
                        case 2:
                            printf("输入身份证号\n");
                            scanf("%s", q->next_Carorder->id);
                            break;
                        case 3:
                            printf("输入租车人姓名\n");
                            scanf("%s", q->next_Carorder->name);
                            break;
                        case 4:
                            printf("输入租车人手机号\n");
                            scanf("%s", q->next_Carorder->phone_num);
                            break;
                        case 5:
                            printf("输入车辆编号\n");
                            scanf("%d", &(q->next_Carorder->rank));
                            break;
                        case 6:
                            printf("输入取车时间\n");
                            scanf("%s", q->next_Carorder->out_time);
                            break;
                        case 7:
                            printf("输入预约还车时间\n");
                            scanf("%s", q->next_Carorder->date_in_time);
                            break;
                        case 8:
                            printf("输入保证金\n");
                            scanf("%f", &(q->next_Carorder->guarantee));
                            break;
                        case 9:
                            printf("输入实际还车时间\n");
                            scanf("%s", q->next_Carorder->actual_in_time);
                            break;
                        case 10:
                            printf("输入预计费用\n");
                            scanf("%f", &(q->next_Carorder->predict_fare));
                            break;
                        case 11:
                            printf("输入实际费用\n");
                            scanf("%f", &(q->next_Carorder->actual_fare));
                            break;
                    }
                    printf("\"请输入需要编辑的订单内容：1.订单编号 2.身份证号 3.客人姓名 4.手机号码 5.租用车辆编号 6.取车时间 7.预约还车时间 8.押金 "
                           "9.实际还车时间 10.应缴费用 11.实缴费用 0.结束修改\n");}
                return;}

    }p=p->next_Car;
}
if(p==NULL)
printf("not found\n");}

void Cartype_store(Cartype *head) {
    FILE *fp = NULL;
    char filename[200]="";
    printf("请输入文件路径\n");
    scanf("%s",filename);
    fp = fopen(filename, "w");
    fprintf(fp, "车辆类型编码,车辆类型名称,库存数量,\n");
    Cartype *p = head->next_type;
    while (p != NULL) {
        fprintf(fp, "%d,", p->typecode);
        fprintf(fp, "%s,", p->name);
        fprintf(fp, "%d,\n", p->num);
        p = p->next_type;
    }
    fclose(fp);
}

void Car_store(Car *head) {
    Car *p = head->next_Car;
    FILE *fp = NULL;
    char filename[200]="";
    printf("请输入文件路径\n");
    scanf("%s",filename);
    fp = fopen(filename, "w");
    fprintf(fp, "车辆编号,车牌号,车辆类型编码,车辆名称,排挡方式,每日租金（元）,出租状态,\n");
    while (p != NULL) {
        fprintf(fp, "%d,", p->rank);
        fprintf(fp, "%s,", p->car_number);
        fprintf(fp, "%d,", p->typecode);
        fprintf(fp, "%s,", p->carname);
        fprintf(fp, "%s,", p->carspt);
        fprintf(fp, "%f,", p->fare);
        fprintf(fp, "%c,\n", p->situation);
        p = p->next_Car;
    }
    fclose(fp);
}

void Carorder_store(Car *head) {
    Car *p = head->next_Car;
    Carorder *q = NULL;
    FILE *fp = NULL;
    char filename[200]="";
    printf("请输入文件路径\n");
    scanf("%s",filename);
    fp = fopen(filename, "w");
    fprintf(fp, "订单编号,身份证号,客人姓名,手机号码,租用车辆编号,取车时间,预约还车时间,押金（元）,实际还车时间,应缴费用（元）,实缴费用（元）,\n");
    while (p != NULL) {
        q = p->next_Carorder;
        while (q != NULL) {
            fprintf(fp, "%s,", q->order_num);
            fprintf(fp, "%s,", q->id);
            fprintf(fp, "%s,", q->name);
            fprintf(fp, "%s,", q->phone_num);
            fprintf(fp, "%d,", q->rank);
            fprintf(fp, "%s,", q->out_time);
            fprintf(fp, "%s,", q->date_in_time);
            fprintf(fp, "%f,", q->guarantee);
            fprintf(fp, "%s,", q->actual_in_time);
            fprintf(fp, "%f,", q->predict_fare);
            fprintf(fp, "%f,\n", q->actual_fare);
            q = q->next_Carorder;
        }
        p = p->next_Car;
    }
    fclose(fp);
}

Car *Cartype_search(Cartype *head1, Car *head2) {
    Cartype *q = head1->next_type;
    Car *p = head2->next_Car;
    Car *result = (Car *) malloc(sizeof(Car));
    result->next_Car = (Car *) malloc(sizeof(Car));
    Car *interval_result = result->next_Car;
    char s[10][20] = {};//存放待搜索车辆类型名称
    printf("请输入需要搜索的车辆类型（如无需添加请输入0）");
    int i = 0, j = 0;
    while (i < 10) {
        scanf("%s", s[i]);
        if (*(s[i++]) == '0')
            break;
        printf("继续添加或输入0以结束\n");
    }
    for (j = 0; j < i; j++)//对每个类型搜索对应车辆
    {
        if (!strcmp(s[j], "0"))break;
        int typecode = 0;
        char (*compare)[20] = s[j];
        while (q != NULL && !vague_search(q->name, compare))//查询类型编码
            q = q->next_type;
        if (q == NULL) {
            printf("not found %s!", s[j]);
            continue;
        } else
            typecode = q->typecode;//查询结束
        while (p != NULL)//搜索对应车辆
        {
            if (p->typecode == typecode) {
                interval_result->typecode = p->typecode;
                interval_result->next_Car = (Car *) malloc(sizeof(Car));
                interval_result->next_Carorder = p->next_Carorder;
                interval_result->situation = p->situation;
                strcpy(interval_result->carspt, p->carspt);
                strcpy(interval_result->carname, p->carname);
                strcpy(interval_result->car_number, p->car_number);
                interval_result->rank = p->rank;
                interval_result->fare = p->fare;
                interval_result = interval_result->next_Car;
            }
            p = p->next_Car;
        }
        q = head1->next_type;
        p = head2->next_Car;//重置
    }
    p=result;
    while(p->next_Car->rank!=0)
        p=p->next_Car;
    p->next_Car=NULL;
    return result;
}

Car *Car_search(Cartype *head1, Car *head2) {
    Car *p = head2->next_Car;
    Car *result = (Car *) malloc(sizeof(Car));
    result->next_Car = (Car *) malloc(sizeof(Car));
    Car *interval_result = result->next_Car;
    char s[3][40] = {};//存放待搜索检索信息名称
    int i = 0;
    printf("请输入车牌信息，若不限请输入0");
    scanf("%s", s[0]);
    printf("请输入车辆名称信息，若不限请输入0");
    scanf("%s", s[1]);
    printf("请输入租用状态信息（y or n)，若不限请输入0");
    scanf("%s", s[2]);
    if (strcmp(s[0], "0"))//若输入了车牌信息
    {
        while (p != NULL) {
            if (vague_search(p->car_number, s[0])) {
                interval_result->typecode = p->typecode;
                interval_result->next_Car = (Car *) malloc(sizeof(Car));
                interval_result->next_Carorder = p->next_Carorder;
                interval_result->situation = p->situation;
                strcpy(interval_result->carspt, p->carspt);
                strcpy(interval_result->carname, p->carname);
                strcpy(interval_result->car_number, p->car_number);
                interval_result->rank = p->rank;
                interval_result->fare = p->fare;
                interval_result = interval_result->next_Car;
            }
            p = p->next_Car;
        }
        if (strcmp(s[1], "0")||strcmp(s[2], "0"))
        {p = result->next_Car;
        result = (Car *) malloc(sizeof(Car));
        result->next_Car = (Car *) malloc(sizeof(Car));
        interval_result = result->next_Car;}
    }
    if (strcmp(s[1], "0"))//若输入了车牌信息
    {
        while (p != NULL) {
            if (vague_search(p->carname, s[1])) {
                interval_result->typecode = p->typecode;
                interval_result->next_Car = (Car *) malloc(sizeof(Car));
                interval_result->next_Carorder = p->next_Carorder;
                interval_result->situation = p->situation;
                strcpy(interval_result->carspt, p->carspt);
                strcpy(interval_result->carname, p->carname);
                strcpy(interval_result->car_number, p->car_number);
                interval_result->rank = p->rank;
                interval_result->fare = p->fare;
                interval_result = interval_result->next_Car;
            }
            p = p->next_Car;
        }
        if (strcmp(s[2], "0"))
        {p = result->next_Car;
        Car *result = (Car *) malloc(sizeof(Car));
        result->next_Car = (Car *) malloc(sizeof(Car));
        Car *interval_result = result->next_Car;}
    }
    if (s[2][0] != '0')//若输入了车牌信息
    {
        while (p != NULL) {
            if (p->situation == s[2][0]) {
                interval_result->typecode = p->typecode;
                interval_result->next_Car = (Car *) malloc(sizeof(Car));
                interval_result->next_Carorder = p->next_Carorder;
                interval_result->situation = p->situation;
                strcpy(interval_result->carspt, p->carspt);
                strcpy(interval_result->carname, p->carname);
                strcpy(interval_result->car_number, p->car_number);
                interval_result->rank = p->rank;
                interval_result->fare = p->fare;
                interval_result = interval_result->next_Car;
            }
            p = p->next_Car;
        }
    }
    p=result;
    while(p->next_Car->rank!=0)
        p=p->next_Car;
    p->next_Car=NULL;
    return result;
}

Carorder *CarorderList2(Cartype *head1, Car *head2) {
    Car *p = head2->next_Car;
    Carorder *result = (Carorder *) malloc(sizeof(Carorder));
    result->next_Carorder = (Carorder *) malloc(sizeof(Carorder));
    Carorder *interval_result = result->next_Carorder;
    Carorder *q = (Carorder *) malloc(sizeof(Carorder));
    while (p != NULL) {
        q = p->next_Carorder;
        while (q != NULL) {
            interval_result->next_Carorder = (Carorder *) malloc(sizeof(Carorder));
            interval_result->guarantee = q->guarantee;
            strcpy(interval_result->id, q->id);
            strcpy(interval_result->order_num, q->order_num);
            strcpy(interval_result->phone_num, q->phone_num);
            strcpy(interval_result->name, q->name);
            strcpy(interval_result->out_time, q->out_time);
            strcpy(interval_result->date_in_time, q->date_in_time);
            strcpy(interval_result->actual_in_time, q->actual_in_time);
            interval_result->actual_fare = q->actual_fare;
            interval_result->predict_fare = q->predict_fare;
            interval_result->rank= q->rank;
            interval_result = interval_result->next_Carorder;
            q = q->next_Carorder;
        }
        p = p->next_Car;
    }
    q=result;
    while(q->next_Carorder!=NULL&&strcmp(q->next_Carorder->id,"")&&q->next_Carorder->rank!=0&&strcmp(q->next_Carorder->order_num,""))
        q=q->next_Carorder;
    q->next_Carorder=NULL;
    return result;
}

Carorder *Carorder_search_guest(Carorder *head){
    Carorder *p=head->next_Carorder;
    Carorder *result = (Carorder *) malloc(sizeof(Carorder));
    result->next_Carorder = (Carorder *) malloc(sizeof(Carorder));
    Carorder *interval_result=result->next_Carorder;
    char s[2][40] = {};//存放待搜索检索信息名称
    printf("请输入客人身份证号，若不限请输入0");
    scanf("%s", s[0]);
    printf("请输入客人手机号，若不限请输入0");
    scanf("%s", s[1]);
    if (strcmp(s[0], "0"))//若输入了车牌信息
    {
        while (p != NULL) {
            if (!strcmp(p->id,s[0])) {
                interval_result->rank = p->rank;
                interval_result->next_Carorder = (Carorder *) malloc(sizeof(Carorder));
                interval_result->predict_fare = p->predict_fare;
                interval_result->actual_fare = p->actual_fare;
                interval_result->guarantee = p->guarantee;
                strcpy(interval_result->name, p->name);
                strcpy(interval_result->id, p->id);
                strcpy(interval_result->phone_num, p->phone_num);
                strcpy(interval_result->order_num, p->order_num);
                strcpy(interval_result->out_time, p->out_time);
                strcpy(interval_result->date_in_time, p->date_in_time);
                strcpy(interval_result->actual_in_time, p->actual_in_time);
                interval_result->rank = p->rank;
                interval_result = interval_result->next_Carorder;
            }
            p = p->next_Carorder;
        }
        if (strcmp(s[1], "0"))
        {   p = result->next_Carorder;
            result = (Carorder *) malloc(sizeof(Carorder));
            result->next_Carorder = (Carorder *) malloc(sizeof(Carorder));
            interval_result = result->next_Carorder;}
    }
    if (s[1][0] != '0')//若输入了车牌信息
    {
        while (p != NULL) {
            if (!strcmp(p->phone_num,s[1])) {
                interval_result->rank = p->rank;
                interval_result->next_Carorder = (Carorder *) malloc(sizeof(Carorder));
                interval_result->predict_fare = p->predict_fare;
                interval_result->actual_fare = p->actual_fare;
                interval_result->guarantee = p->guarantee;
                strcpy(interval_result->name, p->name);
                strcpy(interval_result->id, p->id);
                strcpy(interval_result->phone_num, p->phone_num);
                strcpy(interval_result->order_num, p->order_num);
                strcpy(interval_result->out_time, p->out_time);
                strcpy(interval_result->date_in_time, p->date_in_time);
                strcpy(interval_result->actual_in_time, p->actual_in_time);
                interval_result->rank = p->rank;
                interval_result = interval_result->next_Carorder;
            }
            p = p->next_Carorder;
        }
    }
    p=result;
    while(p->next_Carorder!=NULL&&strcmp(p->next_Carorder->id,"")&&p->next_Carorder->rank!=0&&strcmp(p->next_Carorder->order_num,""))
        p=p->next_Carorder;
    p->next_Carorder=NULL;
    return result;
}

Carorder *Carorder_search_Car(Car *head) {
    Car *p = head->next_Car;
    Carorder *result = (Carorder *) malloc(sizeof(Carorder));
    result->next_Carorder = (Carorder *) malloc(sizeof(Carorder));
    Carorder *interval_result = result->next_Carorder;
    Carorder* q=NULL;
    char s[2][40] = {};//存放待搜索检索信息名称
    printf("请输入车牌信息，若不限请输入0");
    scanf("%s", s[0]);
    if (strcmp(s[0], "0"))//若输入了车牌信息
    {
        while (p != NULL) {
            if (vague_search(p->car_number, s[0])) {
                q=p->next_Carorder;
                while(q!=NULL)
                {
                    interval_result->rank = q->rank;
                    interval_result->next_Carorder = (Carorder *) malloc(sizeof(Carorder));
                    interval_result->predict_fare = q->predict_fare;
                    interval_result->actual_fare = q->actual_fare;
                    interval_result->guarantee = q->guarantee;
                    strcpy(interval_result->name, q->name);
                    strcpy(interval_result->id, q->id);
                    strcpy(interval_result->phone_num, q->phone_num);
                    strcpy(interval_result->order_num, q->order_num);
                    strcpy(interval_result->out_time, q->out_time);
                    strcpy(interval_result->date_in_time, q->date_in_time);
                    strcpy(interval_result->actual_in_time, q->actual_in_time);
                    interval_result->rank = q->rank;
                    interval_result = interval_result->next_Carorder;
                    q=q->next_Carorder;
                }
            }
            p=p->next_Car;
            }
        q=result;
        while(q->next_Carorder!=NULL&&strcmp(q->next_Carorder->id,"")&&q->next_Carorder->rank!=0&&strcmp(q->next_Carorder->order_num,""))
            q=q->next_Carorder;
        q->next_Carorder=NULL;
        return result;
       }
    printf("请输入车辆名称信息，若不限请输入0");
    scanf("%s", s[1]);
    if (strcmp(s[1], "0"))//若输入了车辆名称
    {while (p != NULL) {
            if (vague_search(p->carname, s[1])) {
                q=p->next_Carorder;
                while(q!=NULL)
                {
                    interval_result->rank = q->rank;
                    interval_result->next_Carorder = (Carorder *) malloc(sizeof(Carorder));
                    interval_result->predict_fare = q->predict_fare;
                    interval_result->actual_fare = q->actual_fare;
                    interval_result->guarantee = q->guarantee;
                    strcpy(interval_result->name, q->name);
                    strcpy(interval_result->id, q->id);
                    strcpy(interval_result->phone_num, q->phone_num);
                    strcpy(interval_result->order_num, q->order_num);
                    strcpy(interval_result->out_time, q->out_time);
                    strcpy(interval_result->date_in_time, q->date_in_time);
                    strcpy(interval_result->actual_in_time, q->actual_in_time);
                    interval_result->rank = q->rank;
                    interval_result = interval_result->next_Carorder;
                    q=q->next_Carorder;
                }
            }
            p=p->next_Car;
        }
        q=result;
        while(q->next_Carorder!=NULL&&strcmp(q->next_Carorder->id,"")&&q->next_Carorder->rank!=0&&strcmp(q->next_Carorder->order_num,""))
            q=q->next_Carorder;
        q->next_Carorder=NULL;
        return result;}
}

int datecmp(char *date1,char *date2)
{
    if(strlen(date1)!=16||strlen(date2)!=16)
        return 0;
    int i=0;
    for(;i<16;i++)
    {
        if(date1[i]>date2[i]) return 1;
        else if(date1[i]<date2[i]) return 2;
    }
    return 1;
}

Carorder *Carorder_search_date(Carorder *head){
    Carorder *p=head->next_Carorder;
    Carorder *result = (Carorder *) malloc(sizeof(Carorder));
    result->next_Carorder = (Carorder *) malloc(sizeof(Carorder));
    Carorder *interval_result=result->next_Carorder;
    char s[2][40] = {};//存放待搜索检索信息名称
    printf("请输入起始日期，格式为XXXX/XX/XX-XX:XX");
    scanf("%s", s[0]);
    printf("请输入截止日期，格式为XXXX/XX/XX-XX:XX");
    scanf("%s", s[1]);
    while(p!=NULL)
    {if(datecmp(p->out_time,s[0])==1&&datecmp(p->out_time,s[1])==2)
        {interval_result->rank = p->rank;
        interval_result->next_Carorder = (Carorder *) malloc(sizeof(Carorder));
        interval_result->predict_fare = p->predict_fare;
        interval_result->actual_fare = p->actual_fare;
        interval_result->guarantee = p->guarantee;
        strcpy(interval_result->name, p->name);
        strcpy(interval_result->id, p->id);
        strcpy(interval_result->phone_num, p->phone_num);
        strcpy(interval_result->order_num, p->order_num);
        strcpy(interval_result->out_time, p->out_time);
        strcpy(interval_result->date_in_time, p->date_in_time);
        strcpy(interval_result->actual_in_time, p->actual_in_time);
        interval_result->rank = p->rank;
        interval_result = interval_result->next_Carorder;
    }   p=p->next_Carorder;
}
    p=result;
    while(p->next_Carorder!=NULL&&strcmp(p->next_Carorder->id,"")&&p->next_Carorder->rank!=0&&strcmp(p->next_Carorder->order_num,""))
        p=p->next_Carorder;
    p->next_Carorder=NULL;
    if(result->next_Carorder==NULL)
        printf("未搜索到结果\n");
    return result;
}

void Calculate_Cartype(Cartype *head1,Car *head2){
    Cartype *p=head1->next_type;
    Car *q=head2->next_Car;
    int usable=0,unusable=0;
    printf("车辆类型       车辆总数    已出租数    未出租数\n");
    while(p!=NULL)
    {
        while(q!=NULL)
           {if(q->typecode==p->typecode&&q->situation=='n')
                usable+=1;
            if(q->typecode==p->typecode&&q->situation=='y')
                unusable+=1;
            q=q->next_Car;}
         printf("%-10s%10d%10d%10d\n",p->name,usable+unusable,unusable,usable);
         p=p->next_type;
         q=head2->next_Car;usable=0;unusable=0;
    }
}

void show_type(Cartype *head) {
    while (head->next_type != NULL) {
        printf("%-5d%s  \t%d\n", head->next_type->typecode, head->next_type->name, head->next_type->num);
        head = head->next_type;
    }
}

void show_car(Car *head) {
    while (head->next_Car != NULL) {
        printf("%d\t%s\t%d\t%s\t%s\t%g\t%c\n", head->next_Car->rank, head->next_Car->car_number,
               head->next_Car->typecode,
               head->next_Car->carname, head->next_Car->carspt, head->next_Car->fare, head->next_Car->situation);
        head = head->next_Car;
    }
}

void show_carorder(Carorder *head) {
    while (head->next_Carorder != NULL) {
        printf("%s\t%s\t%s\t%s\t%d\t%s\t%s\t%g\t%s\t%g\t%g\n", head->next_Carorder->order_num,
                head->next_Carorder->id,head->next_Carorder->name,head->next_Carorder->phone_num,
                head->next_Carorder->rank, head->next_Carorder->out_time,head->next_Carorder->date_in_time,head->next_Carorder->guarantee,
                head->next_Carorder->actual_in_time,head->next_Carorder->predict_fare,head->next_Carorder->actual_fare);
        head = head->next_Carorder;
    }
}

void Calculate_profit(Cartype *head1,Car *head2){
    if(head1->next_type==NULL||head2->next_Car==NULL){printf("未找到数据\n");return;}
    FILE *fp=NULL;
    char month[20]="";
    printf("请输入月份，格式XXXX/XX");
    scanf("%s",month);getchar();
    fp=fopen("/Users/xiayifan/Desktop/程序设计综合课程设计(2020春)/程序设计综合课程设计(2020春)/任务二数据/¥Ú∞¸/profit.csv","w");
    fprintf(fp,"车辆类型,营业额,\n");
    Cartype *p=head1->next_type;
    Car *q=head2->next_Car;
    Carorder *m=NULL;
    float profit=0;
    while(p!=NULL)
    {
        while(q!=NULL)
        {
            if(q->typecode==p->typecode)
            {
                m=q->next_Carorder;
                while(m!=NULL)
                {if(vague_search(m->actual_in_time,month))
                    profit+=m->actual_fare;
                m=m->next_Carorder;}
            }
            q=q->next_Car;
        }
        fprintf(fp,"%s,%g,\n",p->name,profit);
        p=p->next_type;q=head2->next_Car;profit=0;
    }
    fclose(fp);
    char filename[] = "/Users/xiayifan/filex/show.py";
    FILE* fp1;

    PyObject *obj = Py_BuildValue("s", filename);
    FILE *file = _Py_fopen_obj(obj, "r+");
    if(file != NULL) {
        PyRun_SimpleFile(file, filename);
    }
    return;
}

void Calculate_Carprofit(Car *head){
        Car *p=head->next_Car;
        Carorder *q=NULL;
        char year[10]="";
        printf("请输入年份\n");
        scanf("%s",year);getchar();
        printf("车牌号              车辆名称       营业额       租用率\n");
        float profit=0;
        float rate=0;
        while(p!=NULL)
        {   q=p->next_Carorder;
            while(q!=NULL)
            {
                if(vague_search(q->actual_in_time,year))
                profit+=q->actual_fare;
                q=q->next_Carorder;
            }
            rate=(profit/p->fare)/365;
            printf("%-20s%-10s\t%7g    %10g\n",p->car_number,p->carname,profit,rate);
            p=p->next_Car;profit=0;rate=0;
        }
}

void Calculate_mvp(Car *head){
    typedef struct mvp{
        char carname[20];
        char carnumber[10];
        float profit;
        int day;
        float rate;
        float fare;
        struct mvp *next_mvp;
    }mvp;
    mvp *head1=(mvp*)malloc(sizeof(mvp));
    head1->next_mvp=NULL;
    mvp *interval=head1;
    mvp *m=(mvp*)malloc(sizeof(mvp));
    Car *p=head->next_Car;
    Carorder *q=NULL;
    char year[10]="";
    printf("请输入年份\n");
    scanf("%s",year);getchar();
    printf("车牌号              车辆名称    累计出租天数   营业额       租用率\n");
    float profit=0;
    int day=0;
    while(p!=NULL)
    {   q=p->next_Carorder;
        while(q!=NULL)
        {
            if(vague_search(q->actual_in_time,year))
                profit+=q->actual_fare;
            q=q->next_Carorder;
        }
        day=profit/p->fare;
        m->fare=p->fare;
        m->profit=profit;
        m->next_mvp=NULL;
        m->day=day;
        m->rate=1.0*day/365;
        strcpy(m->carname,p->carname);
        strcpy(m->carnumber,p->car_number);
        while(interval->next_mvp!=NULL&&interval->next_mvp->day>m->day)
            interval=interval->next_mvp;
        m->next_mvp=interval->next_mvp;
        interval->next_mvp=m;
        p=p->next_Car;profit=0;day=0;interval=head1;m=(mvp*)malloc(sizeof(mvp));
    }
    for(int i=0;i<10&&head1->next_mvp!=NULL&&head1->next_mvp->day!=0;i++)
    {printf("%s\t\t%s\t\t%d\t%f\t%f\n",head1->next_mvp->carnumber,head1->next_mvp->carname,head1->next_mvp->day,head1->next_mvp->profit,head1->next_mvp->rate);
        head1=head1->next_mvp;}
}
/*  char s[6][40] = {};//存放待搜索检索信息名称
    printf("请输入客人身份证号，若不限请输入0");
    scanf("%s",s[0]);
    printf("请输入客人手机号，若不限请输入0");
    scanf("%s",s[1]);
    printf("请输入车牌号，若不限请输入0");
    scanf("%s",s[2]);
    printf("请输入车辆名称，若不限请输入0");
    scanf("%s",s[3]);
    printf("请输入车辆名称，若不限请输入0");
    scanf("%s",s[4]);
    printf("请输入租车时间区间，若不限请输入0");
    scanf("%s",s[5]);interval_result->rank=q->rank;
interval_result->next_Carorder=(Carorder*)malloc(sizeof(Carorder));
interval_result->guarantee=q->guarantee;
strcpy(interval_result->id,q->id);
strcpy(interval_result->order_num,q->order_num);
strcpy(interval_result->phone_num,q->phone_num);
strcpy(interval_result->name,q->name);
strcpy(interval_result->out_time,q->out_time);
strcpy(interval_result->date_in_time,q->date_in_time);
strcpy(interval_result->actual_in_time,q->actual_in_time);
interval_result->actual_fare=q->actual_fare;
interval_result->predict_fare=q->predict_fare;
interval_result=interval_result->next_Carorder;*/

#endif //UNTITLED_CAR_H