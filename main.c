#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "car.h"
#include <python.h>


int main(int argc, char *argv[]) {
    Cartype *head1 = (Cartype *) malloc(sizeof(Cartype));
    Car *head2 = (Car *) malloc(sizeof(Car));
    Carorder *head3 = (Carorder *) malloc(sizeof(Carorder));
    head1->next_type = NULL;
    head2->next_Car = NULL;
    FILE *a=stdin;
    Car *search_result = (Car *) malloc(sizeof(Car));
    int op = 1;
    int count = 0;
    char name[30] = "";
    Py_SetPythonHome(L"/Users/xiayifan/anaconda3");
    while (op) {
        printf("      	                                 汽车租赁管理系统 			        	\n");
        printf("-----------------------------------------------------------------------------------------\n");
        printf("|    	  1. 加载车辆信息            2. 加载车辆类型 		 |              数据统计           | \n");
        printf("|    	  3. 加载订单     	       4. 增加车辆类型		 |       22.按类型统计租用情况       |\n");
        printf("|    	  5. 删除车辆类型            6.修改车辆类型          |      23.统计本月利润            |\n");
        printf("|    	  7. 增加车辆               8. 删除车辆            |       24.统计当年车辆利润        |\n");
        printf("|    	  9. 修改车辆               10.增加订单            |       25.统计年度十佳车          | \n");
        printf("|    	  11.删除订单               12.修改订单            |                               | \n");
        printf("|    	  13.  查询订单(顾客信息）    14. 查询车辆（通过类型） |                               | \n");
        printf("|    	  15. 查询车辆(通过车辆信息)   16. 查询订单（车辆信息  |                               | \n");
        printf("|    	  17. 存储车辆类型数据 	   18.存储车辆信息数据     |                               | \n");
        printf("|    	  19. 存储车辆订单数据 	   20.查看所有信息        |                               | \n");
        printf("|    	  21. 查询订单（通过日期）	   0. Exit              |                               | \n");
        printf("|    	  				       	                        |                               | \n");
        printf("-----------------------------------------------------------------------------------------\n");
        printf("    请选择你的操作[0~25]:");
        scanf("%d", &op);
        setbuf(stdin, NULL);
        int i;
        switch (op) {
            case 1://加载车辆信息
                Car_load(head2);
                show_car(head2);
                printf("已加载，输入任意键继续。。。");
                getchar();
                break;
            case 2://加载车辆类型
                Cartype_load(head1);
                show_type(head1);
                printf("已加载，输入任意键继续。。。");
                getchar();
                break;
            case 3://加载订单
                Carorder_load(head2);
                head3 = CarorderList2(head1, head2);
                show_carorder(head3);
                printf("已加载，输入任意键继续。。。");getchar();
                break;
            case 4://增加车辆类型
                printf("请输入类型名称");
                scanf("%s", name);
                printf("请输入该类型车辆数量");
                scanf("%d", &count);
                getchar();
                Cartype_Add(head1, name, count);
                printf("输入任意键继续。。。");
                setbuf(stdin, NULL);getchar();
                break;
            case 5://删除车辆类型
                printf("输入车辆类型名称");
                scanf("%s", name);
                getchar();
                Cartype_Delete(head1, name);
                printf("输入任意键继续。。。");
                getchar();
                break;
            case 6://修改车辆类型
                printf("请输入车辆类型名称\n");
                scanf("%s", name);
                Cartype_name_Edit(head1, name);
                printf("输入任意键继续。。。");
                getchar();
                break;
            case 7://增加车辆
                Car_Add(head1, head2);
                getchar();
                printf("输入任意键继续。。。");
                getchar();
                break;
            case 8://删除车辆
                printf("请输入车辆编号");
                scanf("%d", &count);
                getchar();
                Car_Delete(head2, count);
                printf("输入任意键继续。。。");
                setbuf(stdin, NULL);getchar();
                break;
            case 9://修改车辆
                printf("请输入车辆编号");
                scanf("%d", &count);
                getchar();
                Car_Edit(head2, count);
                printf("输入任意键继续。。。");
                getchar();
                break;
            case 10:
                Carorder_add(head1, head2);
                getchar();
                head3 = CarorderList2(head1, head2);
                printf("输入任意键继续。。。");
                getchar();
                break;
            case 11:
                printf("请输入订单编号");
                scanf("%s", name);
                getchar();
                Carorder_delete(head2, name);
                head3 = CarorderList2(head1, head2);
                printf("输入任意键继续。。。");
                setbuf(stdin, NULL);getchar();
                break;
            case 12:
                printf("请输入订单编号");
                scanf("%s", name);
                getchar();
                Carorder_edit(head2, name);
                getchar();
                printf("输入任意键继续。。。");
                getchar();break;
            case 13:
                head3 = (Carorder *) malloc(sizeof(Carorder));
                head3 = CarorderList2(head1, head2);
                head3 = Carorder_search_guest(head3);
                printf("车辆编号\t车牌号\t车辆类型编码\t车辆名称\t排挡方式\t每日租金（元\t出租状态\n");
                show_carorder(head3);
                printf("输入任意键继续。。。");
                getchar();
                getchar();
                break;
            case 14:
                search_result = Cartype_search(head1, head2);
                getchar();
                show_car(search_result);
                printf("输入任意键继续。。。");
                getchar();
                break;
            case 15:
                search_result = Car_search(head1, head2);
                getchar();
                show_car(search_result);
                printf("输入任意键继续。。。");
                getchar();
                break;
            case 16:
                head3 = (Carorder *) malloc(sizeof(Carorder));
                head3 = CarorderList2(head1, head2);
                head3 = Carorder_search_Car(head2);
                show_carorder(head3);
                printf("输入任意键继续。。。");
                getchar();
                getchar();
                break;
            case 17:
                Cartype_store(head1);
                getchar();
                printf("输入任意键继续。。。");
                getchar();
                break;
            case 18:
                Car_store(head2);
                getchar();
                printf("输入任意键继续。。。");
                getchar();
                break;
            case 19:
                Carorder_store(head2);
                getchar();
                printf("输入任意键继续。。。");
                getchar();
                break;
            case 20:
                show_type(head1);
                show_car(head2);
                head3 = CarorderList2(head1, head2);
                show_carorder(head3);
                printf("输入任意键继续。。。");
                getchar();
                break;
            case 21:
                head3 = (Carorder *) malloc(sizeof(Carorder));
                head3 = CarorderList2(head1, head2);
                head3 = Carorder_search_date(head3);
                show_carorder(head3);
                printf("输入任意键继续。。。");
                getchar();
                getchar();
                break;
            case 22:
                Calculate_Cartype(head1,head2);
                printf("输入任意键继续。。。");
                getchar();break;
            case 23:
                Py_Initialize();
                Calculate_profit(head1,head2);
                printf("输入任意键继续。。。");
                getchar();break;
            case 24:
                Calculate_Carprofit(head2);
                printf("输入任意键继续。。。");
                getchar();break;
            case 25:
                Calculate_mvp(head2);
                printf("输入任意键继续。。。");
                getchar();break;
            case 0:
                break;
        }//end of switch
    }//end of while
    printf("欢迎下次再使用本系统！\n");Py_Finalize();
}
//end of main()
/*Cartype *p=head1;
while(p->next_type!=NULL)
{printf("%d,%s,%d\n",p->next_type->typecode,p->next_type->name,p->next_type->num);
    p=p->next_type;}
Cartype_Add(head1,"摩托车",1);
//Cartype_Delete(head1,"摩托车");
Car_Add(3,head1,head2);
Carorder_add(head1,head2);
Cartype_store(head1);
Car_store(head2);
Carorder_store(head2);*/

