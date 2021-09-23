#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define pr printf
#define sc scanf
#define USER "admin"
#define PWD "admin"

void welcome();
void administrator_block();
void employer_block();
int user_check();
void add_emp();
void return_menu();
void not_valid();
void delete_emp();
void search_emp();
int search();

void main()
{
        int ch;
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
                default : pr("\nInvalid entry\n");
        }
}

void welcome()
{
        system("clear");

        pr("\t\tWELCOME\n");
        pr("\n\n\tPAYROLL MANAGEMENT SYSTEM\n");
        pr("\n\t___________________________________\n\n\n");
        pr("\n1. Administrator Login \n");
        pr("\n2. Employee Login \n\n\n");
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

        pr("\n\tMENU\n");
        pr("\n\t=========\n");
        pr("\n\n1. Add Employee Details");
        pr("\n2. Delete  Employee Details");
        pr("\n3. Search Employee Details");
        pr("\n4. Edit Employee Details");
        pr("\n5. Display Employee Details");
        pr("\n6. Display Report");
        pr("\n7. Log Out ");

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
//                case 4 : edit_emp();
  //                       break;
          //              case 5 : disp_emp();
          //                       break;
          //              case 6 : disp_report();
          //                       break;
                case 7 : main();
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
        pr("\n\nPress 1 to return to MAIN MENU");
        sc("%d",&enter);
        if(enter)
        {
                administrator_block();
        }
}

void employer_block()
{
        int reply,flag=0;
        char search_id[7];
        system("clear");

        getchar();
        pr("Employee ID >> ");
        gets(search_id);

        char name[30];
        char address[30];
        char id[7];
        float salary;
        float hours;
        FILE *fp;
        fp = fopen("empdata.txt","r");

        do
        {
                fscanf(fp,"%[^/]%*c%[^/]%*c%[^/]%*c%f%f",name,address,id,&salary,&hours);
                if(strcmp(id,search_id) == 0)
                {
                        flag = 1;
                        break;
                }
                if(feof(fp))
                {
                        break;
                }
        }while(!(feof(fp)));

        if(flag == 0)
        {
                system("clear");
                pr("\nEmployer doesn't exist");
                pr("\n\n1.Main menu");
                pr("\n2.Re-enter ID");
                pr("\n\nChoice : ");
                scanf("%d",&reply);
                switch(reply)
                {
                        case 1 : main();
                                  break;
                        case 2 : employer_block();
                                  break;
                        default : pr("Invalid choice");
                }
        }
        else
        {
                system("clear");
                pr("\n1.Display details");
                pr("\n2.Print Salary Slip");
                pr("\n\nChoice :");
                sc("%d",&reply);
        /*      switch(reply)
                {
                        case 1 :
                                  break;
                        case 2 : print_slip()
                                  break;
                        default : pr("\nInvalid Choice");
                }*/
        }
}

void add_emp()
{
        char name[30];
        char address[60];
        char id[7];
        char dept[10];
        char uni[4];
        long int mobile;
        float salary;
        float leave = 0,hrs = 0,rei = 0;
        FILE *fp;
        fp=fopen("empdata.txt","a");

        system("clear");
        pr("\nAdd Employee details");

        getchar();
        pr("\n\nName: ");
        gets(name);
        fflush(stdin);

        pr("\nAddress: ");
        gets(address);
        fflush(stdin);

        pr("\nID: ");
        gets(id);
        fflush(stdin);

        pr("\nDepartment :");
        gets(dept);
        fflush(stdin);

        pr("\nUnion(y/n) :");
        gets(uni);
        fflush(stdin);

        pr("\nMobile :");
        sc("%ld",&mobile);
        fflush(stdin);

        pr("\nSalary: ");
        scanf("%f",&salary);
        fflush(stdin);

        fprintf(fp,"%s/%s/%s/%s/%s/%ld %.2f %.1f %.2f %.2f\n",name,address,id,dept,uni,mobile,salary,leave,hrs,rei);
        fflush(fp);
        fclose(fp);

        system("clear");
        pr("\nDone entering new details ");
        return_menu();
}

void delete_emp()
{
        char name[30];
        char address[60];
        char id[7];
        char dept[10];
        char uni[4];
        long int mobile;
        char iddel[7];
        float salary,leave,hrs,rei;
        int reply;
        char line[100];
        FILE *fp1;
        FILE *fp2;

        fp1=fopen("empdata.txt","r");
        fp2=fopen("tempempdata.txt","w");
        system("clear");

        pr("\nDelete Employee");
        getchar();
        pr("\nEnter employee id to delete: ");
        gets(iddel);
        fflush(stdin);

       do
        {
                fscanf(fp1,"%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%ld %f %f %f %f%*c",name,address,id,dept,uni,&mobile,&salary,&leave,&hrs,&rei);
                if(feof(fp1))
                {
                        break;
                }
                if((strcmp(id,iddel))!=0)
                {
                        fprintf(fp2,"%s/%s/%s/%s/%s/%ld %.2f %.1f %.2f %.2f\n",name,address,id,dept,uni,mobile,salary,leave,hrs,rei);
                }
        }while(!(feof(fp1)));
        fflush(fp2);
        fclose(fp1);
        fclose(fp2);
        remove("empdata.txt");
        rename("tempempdata.txt","empdata.txt");
        system("clear");
        pr("\nDeleting Done ");
        fflush(stdin);
        return_menu();
}


void search_emp()
{
        char id[10];
        char name[50];
        char address[50];
        char dept[10];
        char uni[4];
        long int mobile;
        char idsearch[5];
        float salary;
        int flag = 0;
        char reply;

        system("clear");
        FILE *fp;
        fp=fopen("empdata.txt","r");
        getchar();
        pr("Enter the employee id to search: ");
        gets(idsearch);
        fflush(stdin);
        do
        {
                fscanf(fp,"%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%ld%*c",name,address,id,dept,uni,&mobile);
                if(feof(fp))
                {
                        break;
                }
                if((strcmp(id,idsearch))==0)
                {
                        flag = 1;
                        pr("\nEmployee Exists");
                        getchar();
                        pr("\nDo you wish to display details ?(y/n)");
                        sc("%c",&reply);
                        if(reply == 'y')
                        {
                                pr("\nId : %s",id);
                                pr("\nName : %s",name);
                                pr("\nAddress : %s",address);
                                pr("\nDepartment : %s",dept);
                                pr("\nMobile : %ld",mobile);
                                return_menu();
                                break;
                        }
                        else
                        {
                                return_menu();
                                break;
                        }
                }
        }while(!(feof(fp)));
        if(flag == 0)
        {
                pr("\nEmployee Doesn't exist");
                return_menu();
        }
        fclose(fp);

}
