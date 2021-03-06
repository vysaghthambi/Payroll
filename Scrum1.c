#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>
#include<ctype.h>

#define pr printf
#define sc scanf
#define UNI_RATE 300
#define EPF_RATE 0.18
#define ETF_RATE 0.03
#define TOTAL_HRS (8*20)
#define WORK_DAYS 20
#define USER "admin"
#define PWD "admin"
#define EMP "empdata.txt"
#define TEMP "temp.txt"

struct employee
{
        char name[30];
        char address[60];
        char id[7];
        char dept[10];
        char uni[4];
        char mobile[15];
        float salary;
        float leave;
        float hrs;
        float rei;
        struct employee *link;
};

typedef struct employee emp;

emp *start,*temp,*newnode,*prev;

void copy_file();
void insert_at_end(emp *);
void welcome();
void administrator_block();
void employer_block();
int user_check();
void add_emp();
int name_valid(char*);
void return_menu();
void not_valid();
void delete_emp();
void search_emp();
int search();
void disp_emp();
void send_file();
void edit_emp();
void disp_payslip();
void disp_report();
int mobile_valid(char*);

void main()
{
        int ch;
        start = NULL;
        copy_file();
        system("clear");

        welcome();
        pr("Enter your choice :");
        sc("%d",&ch);

        switch(ch)
        {
                case 1 :if(user_check())
                        {
                                not_valid();
                        }
                        else
                        {
                                administrator_block();
                        }
                          break;
                case 2 : employer_block();
                          break;
                case 3 : break;
                default : system("clear");
                          pr("\nInvalid entry\n");
                          main();
        }
}

void copy_file()
{
        char name[30];
        char address[60];
        char id[7];
        char dept[10];
        char uni[4];
        char mobile[15];
        float salary;
        float leave;
        float hrs;
        float rei;

        FILE *fp;
        fp = fopen(EMP,"r");

        if(fp == NULL)
        {
                return;
        }
        else
        {
                do
                {
                        newnode = (emp *)malloc(sizeof(emp));
                        newnode->link = NULL;
                        fscanf(fp,"%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c %f %f %f %f%*c",name,address,id,dept,uni,mobile,&salary,&leave,&hrs,&rei);
                        strcpy(newnode->name,name);
                        strcpy(newnode->address,address);
                        strcpy(newnode->id,id);
                        strcpy(newnode->dept,dept);
                        strcpy(newnode->uni,uni);
                        strcpy(newnode->mobile,mobile);
                        newnode->salary = salary;
                        newnode->leave = leave;
                        newnode->hrs = hrs;
                        newnode->rei = rei;

                        insert_at_end(newnode);

                        if(feof(fp))
                        {
                                break;
                        }
                }while(!(feof(fp)));
        }
        fclose(fp);
}

void send_file()
{
        char name[30];
        char address[60];
        char id[7];
        char dept[10];
        char uni[4];
        char mobile[15];
        float salary;
        float leave;
        float hrs;
        float rei;

        FILE *fp;
        fp = fopen(TEMP,"w");

        temp = start;
        while(temp)
        {
                strcpy(name,temp->name);
                strcpy(address,temp->address);
                strcpy(id,temp->id);
                strcpy(dept,temp->dept);
                strcpy(uni,temp->uni);
                strcpy(mobile,temp->mobile);
                salary = temp->salary;
                leave = temp->leave;
                hrs = temp->hrs;
                rei = temp->rei;
                fprintf(fp,"\n%s/%s/%s/%s/%s/%s/ %.2f %.1f %.2f %.2f",name,address,id,dept,uni,mobile,salary,leave,hrs,rei);
                temp = temp->link;
        }
        fclose(fp);
        remove(EMP);
        rename(TEMP,EMP);
}


void insert_at_end(emp *newnode)
{
        if(start == NULL)
        {
                start = newnode;
        }
        else
        {
                temp = start;
                while(temp->link != NULL)
                {
                        temp = temp->link;
                }
                temp->link = newnode;
        }
}

void welcome()
{
        system("clear");

        pr("\t\tWELCOME\n");
        pr("\n\n\tPAYROLL MANAGEMENT SYSTEM\n");
        pr("\n\t_________________________\n\n\n");
        pr("\n1. Administrator Login \n");
        pr("\n2. Employee Login \n");
        pr("\n3. Exit \n\n\n");
}

void not_valid()
{
        int reply;
        system("clear");

        system("clear");
        pr("\nUsername or Password is not valid");
        pr("\n1.Main menu");
        pr("\n\nChoice : ");
        sc("%d",&reply);
        switch(reply)
        {
                case 1 : main();
                         break;
                default : pr("\nInvalid Entry");
                          main();
        }
}

void administrator_block()
{
        int reply;
        system("clear");

        pr("\n\t\tMain Menu");
        pr("\n\t     ***************\n");
        pr("\n\n1. Add Employee Details");
        pr("\n2. Delete  Employee Details");
        pr("\n3. Search Employee Details");
        pr("\n4. Modify Employee Details");
        pr("\n5. Display Employee Details");
        pr("\n6. Display Report");
        pr("\n7. Display Employee Payslip");
        pr("\n8. Log Out ");

        pr("\n\nEnter your choice : ");
        sc("%d",&reply);

        switch(reply)
        {
                case 1 : add_emp();
                         break;
                case 2 : delete_emp();
                         break;
                case 3 : search_emp();
                         break;
                case 4 : edit_emp();
                         break;
                case 5 : disp_emp();
                         return_menu();
                         break;
                case 6 : disp_report();
                         break;
                case 7 : disp_payslip();
                         return_menu();
                         break;
                case 8 : main();
                         break;
                default : pr("\nInvalid Entry !!!");
                          return_menu();
        }
}

int user_check()
{
         char username[10],password[10];
         system("clear");

         pr("\nUSERNAME >> ");
         sc("%s",username);
         pr("\nPASSWORD >> ");
         sc("%s",password);

         if(strcmp(username,USER) !=0 || strcmp(password,PWD) !=0)
                 return 1;
         else
                 return 0;
}

void return_menu()
{
        int enter;
        pr("\n\nPress 1 to return to MAIN MENU :");
        sc("%d",&enter);
        if(enter)
        {
                administrator_block();
        }
}

void employer_block()
{
        int reply,flag=0,ret;
        system("clear");

        pr("\n1.Display details");
        pr("\n2.Print Salary Slip");
        pr("\n\nChoice :");
        sc("%d",&reply);
        switch(reply)
        {
                case 1 : disp_emp();
                         pr("\nPress 1 to return to login page : ");
                         sc("%d",&ret);
                         if(ret)
                                 main();
                         break;
                case 2 : disp_payslip();
                         pr("\nPress 1 to return to login page : ");
                         sc("%d",&ret);
                         if(ret)
                                 main();
                         break;
                default : pr("\nInvalid Choice");
        }
}

void add_emp()
{
        char name[30];
        char address[60];
        char id[7];
        char dept[10];
        char uni[4];
        char mobile[15];
        float salary;
        float leave = 0,hrs = 0,rei = 0;

        system("clear");
        pr("\n\tAdd Employee details");
        pr("\n     **************************");

        getchar();
        pr("\n\nName: ");
        gets(name);
        fflush(stdin);

        if(name_valid(name))
        {
                system("clear");
                pr("\nEntered name is not valid.");
                return_menu();
        }

        pr("\nAddress: ");
        gets(address);
        fflush(stdin);

        pr("\nID: ");
        gets(id);
        fflush(stdin);

        temp = start;
        while(temp)
        {
                if(strcmp(temp->id,id) == 0)
                {
                        system("clear");
                        pr("\nEmployee with same Id exists. Please enter a new Id");
                        return_menu();
                        break;
                }
                temp = temp->link;
        }

        pr("\nDepartment :");
        gets(dept);
        fflush(stdin);

        if(name_valid(dept))
        {
                system("clear");
                pr("\nEnter a Valid Department");
                return_menu();
        }

        pr("\nUnion Status(yes/no) :");
        gets(uni);
        fflush(stdin);

        pr("\nMobile :");
        gets(mobile);
        fflush(stdin);

        if(mobile_valid(mobile))
        {
                system("clear");
                pr("\nMobile Number is not valid!!!");
                return_menu();
        }

        pr("\nSalary: ");
        scanf("%f",&salary);
        fflush(stdin);

        newnode = (emp *)malloc(sizeof(emp));
        newnode->link = NULL;
        strcpy(newnode->name,name);
        strcpy(newnode->address,address);
        strcpy(newnode->id,id);
        strcpy(newnode->dept,dept);
        strcpy(newnode->uni,uni);
        strcpy(newnode->mobile,mobile);
        newnode->salary = salary;
        newnode->leave = leave;
        newnode->hrs = hrs;
        newnode->rei = rei;

        insert_at_end(newnode);

        send_file();
        system("clear");
        pr("\nDone entering new details ");

        return_menu();
}

int name_valid(char name[])
{
        int flag = 0;
        for(int i=0;name[i]!='\0';i++)
        {
                if(!isalpha(name[i]))
                {
                        flag = 1;
                        break;
                }
        }
        if(flag == 1)
        {
                return 1;
        }
        else
        {
                return 0;
        }
}

int mobile_valid(char mobile[])
{
        int flag=0;
        for(int i=0;mobile[i]!='\0';i++)
        {
                if(isalpha(mobile[i]))
                {
                        flag = 1;
                        break;
                }
        }
        if(flag == 1)
        {
                return 1;
        }
        else
        {
                return 0;
        }
}

void delete_emp()
{
        char iddel[7];
        int flag = 0;
        system("clear");

        pr("\n\tDelete Employee");
        pr("\n     *********************");
        pr("\n\nEnter Employee Id to delete : ");
        getchar();
        gets(iddel);
        fflush(stdin);

        temp = start;
        while(temp)
        {
                if(strcmp(temp->id,iddel) == 0)
                {
                        flag = 1;
                        break;
                }
                prev = temp;
                temp = temp->link;
        }
        if(flag == 1)
        {
                if(temp == start && temp->link == NULL)
                {
                        start = NULL;
                        free(temp);
                }
                else if(temp == start && temp->link != NULL)
                {
                        start = temp->link;
                        free(temp);
                }
                else
                {
                        prev->link = temp->link;
                        free(temp);
                }
        }
        else
        {
                pr("\nEmployee doesn't exist. Please Enter a valid ID");
                return_menu();
        }


        send_file();
        system("clear");
        pr("\nDeleting Done ");
        fflush(stdin);
        return_menu();
}


void search_emp()
{
        int flag = 0;
        char idsearch[7],reply;

        system("clear");
        pr("\n\tSearch Employee");
        pr("\n     *********************");
        pr("\nEnter the employee id to search: ");
        getchar();
        gets(idsearch);
        fflush(stdin);

        temp = start;
        while(temp)
        {
                if(strcmp(temp->id,idsearch) == 0)
                {
                        flag = 1;
                        pr("\nEmployee Exists");
                        pr("\nDo you wish to display details ?(y/n)");
                        getchar();
                        sc("%c",&reply);
                        if(reply == 'y' || reply =='Y')
                        {
                                pr("\nId : %s",temp->id);
                                pr("\nName : %s",temp->name);
                                pr("\nAddress : %s",temp->address);
                                pr("\nDepartment : %s",temp->dept);
                                pr("\nUnion Status : %s",temp->uni);
                                pr("\nMobile : %s",temp->mobile);
                                return_menu();
                                break;
                        }
                        else
                        {
                                return_menu();
                                break;
                        }
                }
                temp = temp->link;
        }
        if(flag == 0)
        {
                pr("\nEmployee Doesn't exist. Please Enter a valid ID");
                return_menu();
        }
}

void disp_emp()
{
        int flag = 0;
        char idsearch[7],reply;

        system("clear");
        pr("\tDisplay Employee Details");
        pr("\n     ******************************");
        pr("\n\nEnter Employee Id to search : ");
        getchar();
        gets(idsearch);
        fflush(stdin);

        temp = start;
        while(temp)
        {
                if(strcmp(temp->id,idsearch) == 0)
                {
                        system("clear");
                        flag = 1;
                        pr("\n\tDetails of Employee");
                        pr("\n     _________________________");
                        pr("\n\nID : %s",temp->id);
                        pr("\nName : %s",temp->name);
                        pr("\nAddress : %s",temp->address);
                        pr("\nDepartment : %s",temp->dept);
                        pr("\nUnion Status : %s",temp->uni);
                        pr("\nMobile : %s",temp->mobile);
                        break;
                }
                temp = temp->link;
        }
        if(flag == 0)
        {
                printf("\nEmployee dosen't exist. Please enter a valid employee Id");
        }
        return;

}

void edit_emp()
{
        char address[60],dept[10],uni[4];
        char mobile[15];
        float salary,hrs,leave,rei;
        char idedit[7];
        int flag = 0,reply,ret;
        system("clear");

        pr("\nEnter ID of Employee to be modified : ");
        getchar();
        gets(idedit);

        temp = start;
        while(temp)
        {
                if(strcmp(temp->id,idedit) == 0)
                {
MODIFY:                 system("clear");
                        pr("\n\tModify Menu");
                        pr("\n     _________________");
                        pr("\n\n1.Change Address");
                        pr("\n2.Change Department");
                        pr("\n3.Change Mobile Number");
                        pr("\n4.Change Union Status");
                        pr("\n5.Change Basic Salary");
                        pr("\n6.Salary Management");
                        pr("\n7.Return to Main Menu");
                        pr("\n\nEnter your choice :");
                        sc("%d",&reply);

                        switch(reply)
                        {
                                case 1 : system("clear");
                                         pr("\tChange of Address");
                                         pr("\n     _______________________");
                                         pr("\n\nEnter new address :");
                                         getchar();
                                         gets(address);
                                         strcpy(temp->address,address);
                                         send_file();
                                         return_menu();
                                         break;
                                case 2 : system("clear");
                                         pr("\tChange of Department");
                                         pr("\n     _________________________");
                                         pr("\n\nEnter new Department :");
                                         getchar();
                                         gets(dept);
                                         strcpy(temp->dept,dept);
                                         send_file();
                                         return_menu();
                                         break;
                                case 3 : system("clear");
                                         pr("\tChange of Mobile Number");
                                         pr("\n     _____________________________");
                                         pr("\n\nEnter new Mobile Number :");
                                         getchar();
                                         gets(mobile);
                                         strcpy(temp->mobile,mobile);
                                         send_file();
                                         return_menu();
                                         break;
                                case 4 : system("clear");
                                         pr("\tChange in Union Status");
                                         pr("\n     ____________________________");
                                         pr("\n\nEnter Union Status(yes/no) :");
                                         getchar();
                                         gets(uni);
                                         strcpy(temp->uni,uni);
                                         send_file();
                                         return_menu();
                                         break;
                                case 5 : system("clear");
                                         pr("\tChange in Basic Salary");
                                         pr("\n     ____________________________");
                                         pr("\n\nEnter New Basic Salary :");
                                         getchar();
                                         sc("%f",&salary);
                                         temp->salary = salary;
                                         send_file();
                                         return_menu();
                                         break;
                                case 6 : system("clear");
                                         pr("\tSalary Management");
                                         pr("\n     _______________________");
                                         pr("\n\nEnter Overtime Hours :");
                                         getchar();
                                         sc("%f",&hrs);
                                         temp->hrs = hrs;
                                         pr("\n\nEnter Number of Leave Days :");
                                         sc("%f",&leave);
                                         temp->leave = leave;
                                         pr("\n\nEnter Amount of Reimbursement :");
                                         sc("%f",&rei);
                                         temp->rei = rei;
                                         send_file();
                                         return_menu();
                                         break;
                                case 7 : administrator_block();
                                         break;
                                default : system("clear");
                                          pr("\n\nInvalid Entry!!!");
                                          return_menu();
                        }
                }
                temp = temp->link;
        }
        if(flag == 0)
        {
                pr("Employee Doesn't Exist. Please Enter a valid ID!!!");
                return_menu();
        }
        return_menu();
}

void disp_payslip()
{
        float epf,etf,hrs_rate,ot_rate,rei,salary,net_sal = 0,leav_rate,day_rate,uni_rate;
        char idprint[7];
        int flag = 0,ret;

        system("clear");
        pr("\nEnter Employee ID to print Payslip :");
        getchar();
        gets(idprint);

        temp = start;
        while(temp)
        {
                if(strcmp(temp->id,idprint) == 0)
                {
                        flag = 1;
                        salary = temp->salary;

                        epf = salary * EPF_RATE;
                        etf = salary * ETF_RATE;

                        hrs_rate = salary / TOTAL_HRS;
                        day_rate = salary / WORK_DAYS;

                        ot_rate = temp->hrs * hrs_rate;

                        leav_rate = temp->leave * day_rate;
                        rei = temp->rei;
                        if(strcmp(temp->uni,"yes") == 0)
                        {
                                uni_rate = UNI_RATE;
                        }
                        else
                        {
                                uni_rate = 0;
                        }
                        net_sal = salary + (ot_rate + rei) - (epf + etf + uni_rate + leav_rate);
                        system("clear");
                        pr("\tPAYSLIP");
                        pr("\n     _____________");
                        pr("\n\nID          : %s",temp->id);
                        pr("\nGross Salary  :Rs. %.2f",salary);
                        pr("\nEPF           :Rs. %.2f",epf);
                        pr("\nETF           :Rs. %.2f",etf);
                        pr("\nUnion Charges :Rs. %.2f",uni_rate);
                        pr("\nLeave Charges :Rs. %.2f",leav_rate);
                        pr("\nOvertime Rate :Rs. %.2f",ot_rate);
                        pr("\nReimbursement :Rs. %.2f",rei);
                        pr("\nNet Salary    :Rs. %.2f",net_sal);
                }
                temp = temp->link;
        }
        if(flag == 0)
        {
                system("clear");
                pr("\nEmployee dosen't exist. Please enter a valid ID!!!");
        }
}

void disp_report()
{
        float epf,etf,hrs_rate,ot_rate,rei,salary,net_sal,leav_rate,day_rate,uni_rate;

        system("clear");
         temp = start;
         while(temp)
         {
                 salary = temp->salary;
                 epf = salary * EPF_RATE;
                 etf = salary * ETF_RATE;
                 hrs_rate = salary / TOTAL_HRS;
                 day_rate = salary / WORK_DAYS;
                 ot_rate = temp->hrs * hrs_rate;
                 leav_rate = temp->leave * day_rate;
                 rei = temp->rei;

                 if(strcmp(temp->uni,"yes") == 0)

                 {
                         uni_rate = UNI_RATE;

                 }

                 else
                 {
                         uni_rate = 0;
                 }
                 net_sal = salary + (ot_rate + rei) - (epf + etf + uni_rate + leav_rate);
                pr("%s %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f\n",temp->id,salary,epf,etf,uni_rate,leav_rate,ot_rate,rei,net_sal);
                temp = temp->link;
         }
         return_menu();
}
