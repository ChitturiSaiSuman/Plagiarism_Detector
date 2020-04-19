//*************************************       PLAGIARISM DETECTOR               *****************************
//*************         A Mini Project by Sai Suman Chitturi and Praneeth Kapila        *********************
//*************         This application detects Plagiarism Among set of C codes        *********************
//*************                 Licensed under GNU General Public License - GitHub      *********************
//*************                 Hope this application is used for good purposes         *********************
//*************   Sometimes you gotta Run before you can Walk :) Number of Lines: 1024  *********************
//***********************************************************************************************************
#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<ctype.h>
#include<limits.h>
#include<sys/types.h>
#include<errno.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<dirent.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<pthread.h>
#define or ||
#define and &&
#define not !
#define number_of_functions_matching_limit 2
#define number_of_lines_matching_limit 8
#define number_of_scan_matching_limit 2
#define number_of_print_matching_limit 2
#define number_of_for_matching_limit 2
#define number_of_while_matching_limit 2
#define number_of_if_matching_limit 2
#define number_of_else_matching_limit 2
#define number_of_else_if_matching_limit 2
#define number_of_break_matching_limit 2
#define number_of_int_matching_limit 1
#define number_of_float_matching_limit 1
#define number_of_char_matching_limit 1
#define number_of_long_matching_limit 1
#define number_of_double_matching_limit 1
#define number_of_bool_matching_limit 1
#define number_of_include_matching_limit 0
#define number_of_define_matching_limit 2
#define number_of_struct_matching_limit 0
#define number_of_typedef_matching_limit 2
#define number_of_void_functions_matching_limit 1
#define number_of_int_functions_matching_limit 1
#define number_of_float_functions_matching_limit 1
#define number_of_char_functions_matching_limit 1
#define number_of_bool_functions_matching_limit 1
#define number_of_long_functions_matching_limit 1
#define number_of_double_functions_matching_limit 1
#define function_match_percentage_limit 85
#define cumulative_match_percentage_limit 90
void strlwr(char *string)
{
    for(int i=0;i<strlen(string);i++)
        string[i]=tolower(string[i]);
}
int max(int a, int b)
{
    return (a>b?a:b);
}
int min(int a, int b)
{
    return (a<b?a:b);
}
typedef struct Function
{
    char name[128];
    char return_type[16];
    int number_of_arguments;
    int number_of_int_arguments;
    int number_of_char_arguments;
    int number_of_float_arguments;
    int number_of_bool_arguments;
    int number_of_long_arguments;
    int number_of_double_arguments;
    int number_of_int_variables;
    int number_of_float_variables;
    int number_of_char_variables;
    int number_of_double_variables;
    int number_of_long_variables;
    int number_of_bool_variables;
    int number_of_print_statements;
    int number_of_scan_statements;
    int number_of_for_loops;
    int number_of_while_loops;
    int number_of_if;
    int number_of_else_if;
    int number_of_else;
    int number_of_break;
    int number_of_continue;
    int number_of_statements;
}Function;
typedef struct File_Data
{
    char name_of_file[32];
    Function function[16];
    int number_of_functions;
    int number_of_lines;
    int number_of_scan;
    int number_of_print;
    int number_of_for;
    int number_of_while;
    int number_of_if;
    int number_of_else;
    int number_of_else_if;
    int number_of_break;
    int number_of_int;
    int number_of_float;
    int number_of_char;
    int number_of_long;
    int number_of_double;
    int number_of_bool;
    int number_of_include;
    int number_of_define;
    int number_of_struct;
    int number_of_typedef;
    int number_of_void_functions;
    int number_of_int_functions;
    int number_of_float_functions;
    int number_of_char_functions;
    int number_of_bool_functions;
    int number_of_long_functions;
    int number_of_double_functions;
    char line[256][192];
}data;
void clrscr()
{
    system("clear");
}
void newline(int n)
{
    while(n--)
        printf("\n");
}
void tab(int n)
{
    while(n--)
        printf("\t");
}
void space(int n)
{
    while(n--)
        printf(" ");
}
void raw_input()
{
    char ch;
    system("/bin/stty raw");
    ch=getchar();
    system("/bin/stty cooked");
    clrscr();
}
static bool part_of_comment;
bool write_results(data *source_data, data *destination, bool success,float parameters_matching_percentage,float function_matching_percentage,float statement_matching_percentage)
{
    FILE *fptr;
    chdir("..");
    chdir("Results");
    char file_name[96];
    strcpy(file_name,"Result_");
    strcat(file_name,source_data->name_of_file);
    strcat(file_name,"_");
    strcat(file_name,destination->name_of_file);
    strcat(file_name,"_");
    strcat(file_name,".txt");
    fptr=fopen(file_name,"w");
    if(fptr==NULL)
        return false;
    fprintf(fptr,"\n\n\t\t\t");
    if(success)
        fprintf(fptr,"SUCCESS LOG! ");
    else
        fprintf(fptr,"FAILURE LOG! ");
    fprintf(fptr,"Details");
    fprintf(fptr,"\n\n");
    float cumulative_matching_percentage=parameters_matching_percentage+function_matching_percentage+statement_matching_percentage;
    cumulative_matching_percentage/=3;
    fprintf(fptr,"\tCumulative Matching Percentage: %.2f\n",cumulative_matching_percentage);
    fprintf(fptr,"\tParameter Matching Percentage: %.2f\n",parameters_matching_percentage);
    fprintf(fptr,"\tFunction Matching Percentage: %.2f\n",function_matching_percentage);
    fprintf(fptr,"\tStatement Matching Percentage: %.2f\n",statement_matching_percentage);
    fprintf(fptr,"\n");
    fprintf(fptr,"\tDetails of Source File\n\n");
    fprintf(fptr,"Name of File: %s\n",source_data->name_of_file);
    fprintf(fptr,"Number of Functions: %d\n",source_data->number_of_functions);
    fprintf(fptr,"Function Wise Details\n");
    for(int i=0;i<source_data->number_of_functions;i++)
    {
        fprintf(fptr,"Function %d\n",i+1);
        fprintf(fptr,"Name of Function: %s\n",source_data->function[i].name);
        fprintf(fptr,"Return Type: %s\n",source_data->function[i].return_type);
        fprintf(fptr,"Number of Arguments: %d\n",source_data->function[i].number_of_arguments);
        fprintf(fptr,"Number of int arguments: %d\n",source_data->function[i].number_of_int_arguments);
        fprintf(fptr,"Number of char arguments: %d\n",source_data->function[i].number_of_char_arguments);
        fprintf(fptr,"Number of float Arguments: %d\n",source_data->function[i].number_of_float_arguments);
        fprintf(fptr,"Number of bool Arguments: %d\n",source_data->function[i].number_of_bool_arguments);
        fprintf(fptr,"Number of long Arguments: %d\n",source_data->function[i].number_of_long_arguments);
        fprintf(fptr,"Number of double Arguments: %d\n",source_data->function[i].number_of_double_arguments);
        fprintf(fptr,"Number of int Variables: %d\n",source_data->function[i].number_of_int_variables);
        fprintf(fptr,"Number of char Variables: %d\n",source_data->function[i].number_of_char_variables);
        fprintf(fptr,"Number of float Variables: %d\n",source_data->function[i].number_of_float_variables);
        fprintf(fptr,"Number of bool Variables: %d\n",source_data->function[i].number_of_bool_variables);
        fprintf(fptr,"Number of long Variables: %d\n",source_data->function[i].number_of_long_variables);
        fprintf(fptr,"Number of double Variables: %d\n",source_data->function[i].number_of_double_variables);
        fprintf(fptr,"Number of printf Statements: %d\n",source_data->function[i].number_of_print_statements);
        fprintf(fptr,"Number of scanf Statements: %d\n",source_data->function[i].number_of_scan_statements);
        fprintf(fptr,"Number of for loops: %d\n",source_data->function[i].number_of_for_loops);
        fprintf(fptr,"Number of while loops: %d\n",source_data->function[i].number_of_while_loops);
        fprintf(fptr,"Number of if Statements: %d\n",source_data->function[i].number_of_if);
        fprintf(fptr,"Number of else if Statements: %d\n",source_data->function[i].number_of_else_if);
        fprintf(fptr,"Number of else Statements: %d\n",source_data->function[i].number_of_else);
        fprintf(fptr,"Number of break Statements: %d\n",source_data->function[i].number_of_break);
        fprintf(fptr,"Number of continue Statements: %d\n",source_data->function[i].number_of_continue);
        fprintf(fptr,"Total Number of Lines: %d\n",source_data->function[i].number_of_statements);
        fprintf(fptr,"\n");
    }
    fprintf(fptr,"\tProgram Details Continued...\n");
    fprintf(fptr,"Number of Lines: %d\n",source_data->number_of_lines);
    fprintf(fptr,"Number of scanf Statements: %d\n",source_data->number_of_scan);
    fprintf(fptr,"Number of printf Statements: %d\n",source_data->number_of_print);
    fprintf(fptr,"Number of for loops: %d\n",source_data->number_of_for);
    fprintf(fptr,"Number of while loops: %d\n",source_data->number_of_while);
    fprintf(fptr,"Number of if Statements: %d\n",source_data->number_of_if);
    fprintf(fptr,"Number of else Statements: %d\n",source_data->number_of_else);
    fprintf(fptr,"Number of else if Statements: %d\n",source_data->number_of_else_if);
    fprintf(fptr,"Number of break Statements: %d\n",source_data->number_of_break);
    fprintf(fptr,"Number of int Variables: %d\n",source_data->number_of_int);
    fprintf(fptr,"Number of float Variables: %d\n",source_data->number_of_float);
    fprintf(fptr,"Number of char Variables: %d\n",source_data->number_of_char);
    fprintf(fptr,"Number of long Variables: %d\n",source_data->number_of_long);
    fprintf(fptr,"Number of double Variables: %d\n",source_data->number_of_double);
    fprintf(fptr,"Number of bool Variables: %d\n",source_data->number_of_bool);
    fprintf(fptr,"Number of Included Header Files: %d\n",source_data->number_of_include);
    fprintf(fptr,"Number of #define pre-processors: %d\n",source_data->number_of_define);
    fprintf(fptr,"Number of Structures: %d\n",source_data->number_of_struct);
    fprintf(fptr,"Number of typedef: %d\n",source_data->number_of_typedef);
    fprintf(fptr,"Number of void Functions: %d\n",source_data->number_of_void_functions);
    fprintf(fptr,"Number of int Functions: %d\n",source_data->number_of_int_functions);
    fprintf(fptr,"Number of float Functions: %d\n",source_data->number_of_float_functions);
    fprintf(fptr,"Number of char Functions: %d\n",source_data->number_of_char_functions);
    fprintf(fptr,"Number of bool Functions: %d\n",source_data->number_of_bool_functions);
    fprintf(fptr,"Number of long Functions: %d\n",source_data->number_of_long_functions);
    fprintf(fptr,"Number of double Functions: %d\n\n\n",source_data->number_of_double_functions);
    fprintf(fptr,"\tDetails of Destination File\n\n");
    fprintf(fptr,"Name of File: %s\n",destination->name_of_file);
    fprintf(fptr,"Number of Functions: %d\n",destination->number_of_functions);
    fprintf(fptr,"Function Wise Details\n");
    for(int i=0;i<destination->number_of_functions;i++)
    {
        fprintf(fptr,"Function %d\n",i+1);
        fprintf(fptr,"Name of Function: %s\n",destination->function[i].name);
        fprintf(fptr,"Return Type: %s\n",destination->function[i].return_type);
        fprintf(fptr,"Number of Arguments: %d\n",destination->function[i].number_of_arguments);
        fprintf(fptr,"Number of int arguments: %d\n",destination->function[i].number_of_int_arguments);
        fprintf(fptr,"Number of char arguments: %d\n",destination->function[i].number_of_char_arguments);
        fprintf(fptr,"Number of float Arguments: %d\n",destination->function[i].number_of_float_arguments);
        fprintf(fptr,"Number of bool Arguments: %d\n",destination->function[i].number_of_bool_arguments);
        fprintf(fptr,"Number of long Arguments: %d\n",destination->function[i].number_of_long_arguments);
        fprintf(fptr,"Number of double Arguments: %d\n",destination->function[i].number_of_double_arguments);
        fprintf(fptr,"Number of int Variables: %d\n",destination->function[i].number_of_int_variables);
        fprintf(fptr,"Number of char Variables: %d\n",destination->function[i].number_of_char_variables);
        fprintf(fptr,"Number of float Variables: %d\n",destination->function[i].number_of_float_variables);
        fprintf(fptr,"Number of bool Variables: %d\n",destination->function[i].number_of_bool_variables);
        fprintf(fptr,"Number of long Variables: %d\n",destination->function[i].number_of_long_variables);
        fprintf(fptr,"Number of double Variables: %d\n",destination->function[i].number_of_double_variables);
        fprintf(fptr,"Number of printf Statements: %d\n",destination->function[i].number_of_print_statements);
        fprintf(fptr,"Number of scanf Statements: %d\n",destination->function[i].number_of_scan_statements);
        fprintf(fptr,"Number of for loops: %d\n",destination->function[i].number_of_for_loops);
        fprintf(fptr,"Number of while loops: %d\n",destination->function[i].number_of_while_loops);
        fprintf(fptr,"Number of if Statements: %d\n",destination->function[i].number_of_if);
        fprintf(fptr,"Number of else if Statements: %d\n",destination->function[i].number_of_else_if);
        fprintf(fptr,"Number of else Statements: %d\n",destination->function[i].number_of_else);
        fprintf(fptr,"Number of break Statements: %d\n",destination->function[i].number_of_break);
        fprintf(fptr,"Number of continue Statements: %d\n",destination->function[i].number_of_continue);
        fprintf(fptr,"Total Number of Lines: %d\n",destination->function[i].number_of_statements);
        fprintf(fptr,"\n");
    }
    fprintf(fptr,"Number of Lines: %d\n",destination->number_of_lines);
    fprintf(fptr,"Number of scanf Statements: %d\n",destination->number_of_scan);
    fprintf(fptr,"Number of printf Statements: %d\n",destination->number_of_print);
    fprintf(fptr,"Number of for loops: %d\n",destination->number_of_for);
    fprintf(fptr,"Number of while loops: %d\n",destination->number_of_while);
    fprintf(fptr,"Number of if Statements: %d\n",destination->number_of_if);
    fprintf(fptr,"Number of else Statements: %d\n",destination->number_of_else);
    fprintf(fptr,"Number of else if Statements: %d\n",destination->number_of_else_if);
    fprintf(fptr,"Number of break Statements: %d\n",destination->number_of_break);
    fprintf(fptr,"Number of int Variables: %d\n",destination->number_of_int);
    fprintf(fptr,"Number of float Variables: %d\n",destination->number_of_float);
    fprintf(fptr,"Number of char Variables: %d\n",destination->number_of_char);
    fprintf(fptr,"Number of long Variables: %d\n",destination->number_of_long);
    fprintf(fptr,"Number of double Variables: %d\n",destination->number_of_double);
    fprintf(fptr,"Number of bool Variables: %d\n",destination->number_of_bool);
    fprintf(fptr,"Number of Included Header Files: %d\n",destination->number_of_include);
    fprintf(fptr,"Number of #define pre-processors: %d\n",destination->number_of_define);
    fprintf(fptr,"Number of Structures: %d\n",destination->number_of_struct);
    fprintf(fptr,"Number of typedef: %d\n",destination->number_of_typedef);
    fprintf(fptr,"Number of void Functions: %d\n",destination->number_of_void_functions);
    fprintf(fptr,"Number of int Functions: %d\n",destination->number_of_int_functions);
    fprintf(fptr,"Number of float Functions: %d\n",destination->number_of_float_functions);
    fprintf(fptr,"Number of char Functions: %d\n",destination->number_of_char_functions);
    fprintf(fptr,"Number of bool Functions: %d\n",destination->number_of_bool_functions);
    fprintf(fptr,"Number of long Functions: %d\n",destination->number_of_long_functions);
    fprintf(fptr,"Number of double Functions: %d\n",destination->number_of_double_functions);
    fprintf(fptr,"\n\n\t\t\t\t*****End of Log*****");
    fclose(fptr);
    chdir("..");
    chdir("Files_to_be_checked");
    return true;
}
int display_files(char *folder_name)
{
    newline(2);
    tab(3);
    int number_of_files=0;
    struct dirent **name_list;
    int n;
    int i=0;
    int j=0;
    n = scandir(folder_name, &name_list,NULL,alphasort);
    printf("Current Directory:\t%s",getcwd(NULL,0));
    newline(2);
    tab(5);
    printf("Files Present in Current Directory");
    newline(3);
    int number_of_columns=4;
    int column_length=30;
    tab(1);
    while(i<n)
    {
        if(strcmp(name_list[i]->d_name,"..")==0 || strcmp(name_list[i]->d_name,".")==0)
        {
            free(name_list[i]);
            ++i;
            continue;
        }
        printf("%s", name_list[i]->d_name);
        space(column_length-(strlen(name_list[i]->d_name)));
        free(name_list[i]);
        ++i;
        ++j;
        if(j%number_of_columns==0)
        {
            newline(2);
            tab(1);
        }
    }
    free(name_list);
    newline(3);
    tab(3);
    return (n-2);
}
void display_introduction()
{
    FILE *fptr;
    fptr=fopen("Introduction.txt","r");
    char ch;
    clrscr();
    while(fscanf(fptr,"%c",&ch)!=EOF)
        printf("%c",ch);
    fclose(fptr);
    newline(2);
    tab(3);
    printf("Press any key to Continue...");
    raw_input();
}
void display_conclusion()
{
    FILE *fptr;
    fptr=fopen("Conclusion.txt","r");
    char ch;
    clrscr();
    while(fscanf(fptr,"%c",&ch)!=EOF)
        printf("%c",ch);
    fclose(fptr);
    newline(2);
    tab(3);
    printf("Press any key to Quit...");
    raw_input();
}
bool prompt_continue()
{
    clrscr();
    newline(3);
    tab(3);
    printf("Would you like to Continue..?\t\t");
    char ch;
    system("/bin/stty raw");
    ch=getchar();
    system("/bin/stty cooked");
    return (ch=='Y' or ch=='y');
}
int count_number_of_variables(char line[])
{
    int count=0;
    for(int i=0;i<strlen(line);i++)
        if(line[i]==',')
            count+=1;
    return count+1;
}
void get_function_details(Function * function,char line[256][192], const int pos)
{
    int i=pos;
    int j=0;
    while(line[i][j]!='\0' and line[i][j]!=' ')
        j++;
    j++;
    char name[128];
    int index=0;
    while(line[i][j]!='\0' and line[i][j]!='(')
    {
        name[index]=line[i][j];
        index++;
        j++;
    }
    name[index]='\0';
    int param_pos=j;
    strcpy(function->name,name);
    if(strstr(line[i],"void"))
        strcpy(function->return_type,"void");
    else if(strstr(line[i],"int"))
        strcpy(function->return_type,"int");
    else if(strstr(line[i],"float"))
        strcpy(function->return_type,"float");
    else if(strstr(line[i],"double"))
        strcpy(function->return_type,"double");
    else if(strstr(line[i],"long"))
        strcpy(function->return_type,"long");
    else if(strstr(line[i],"char"))
        strcpy(function->return_type,"char");
    j=0;
    int number_of_arguments=0;
    while(j<strlen(line[i]))
    {
        if(line[i][j]==',')
            number_of_arguments+=1;
        j+=1;
    }
    function->number_of_arguments=(number_of_arguments+1);
    int count;
    j=param_pos;
    count=0;
    while(j<=strlen(line[i])-strlen("int"))
    {
        if(line[i][j]=='i' and line[i][j+1]=='n' and line[i][j+2]=='t')
            count+=1;
        j+=1;
    }
    function->number_of_int_arguments=count;
    count=0;
    j=param_pos;
    while(j<=strlen(line[i])-strlen("char"))
    {
        if(line[i][j]=='c' and line[i][j+1]=='h' and line[i][j+2]=='a' and line[i][j+3]=='r')
            count+=1;
        j+=1;
    }
    function->number_of_char_arguments=count;
    j=param_pos;
    count=0;
    while(j<=strlen(line[i])-strlen("float"))
    {
        if(line[i][j]=='f' and line[i][j+1]=='l' and line[i][j+2]=='o' and line[i][j+3]=='a' and line[i][j+4]=='t')
            count+=1;
        j+=1;
    }
    function->number_of_float_arguments=count;
    j=param_pos;
    count=0;
    while(j<=strlen(line[i])-strlen("bool"))
    {
        if(line[i][j]=='b' and line[i][j+1]=='o' and line[i][j+2]=='o' and line[i][j+3]=='l')
            count+=1;
        j+=1;
    }
    function->number_of_bool_arguments=count;
    j=param_pos;
    count=0;
    while(j<=strlen(line[i])-strlen("long"))
    {
        if(line[i][j]=='l' and line[i][j+1]=='o' and line[i][j+2]=='n' and line[i][j+3]=='g')
            count+=1;
        j+=1;
    }
    function->number_of_long_arguments=count;
    j=param_pos;
    count=0;
    while(j<=strlen(line[i])-strlen("double"))
    {
        if(line[i][j]=='d' and line[i][j+1]=='o' and line[i][j+2]=='u' and line[i][j+3]=='b' and line[i][j+4]=='l' and line[i][j+5]=='e')
            count+=1;
        j+=1;
    }
    function->number_of_double_arguments=count;
    count=0;
    int number_of_statements=0;
    int balanced=0;
    function->number_of_print_statements=0;
    function->number_of_scan_statements=0;
    function->number_of_for_loops=0;
    function->number_of_while_loops=0;
    function->number_of_if=0;
    function->number_of_else_if=0;
    function->number_of_else=0;
    function->number_of_break=0;
    function->number_of_continue=0;
    function->number_of_statements=0;
    i=pos+1;
    do
    {
        if(strstr(line[i],"{"))
            balanced++;
        if(strstr(line[i],"}"))
            balanced--;
        if(strstr(line[i],"printf("))
            function->number_of_print_statements+=1;
        if(strstr(line[i],"scanf("))
            function->number_of_scan_statements+=1;
        if(strstr(line[i],"for("))
            function->number_of_for_loops+=1;
        if(strstr(line[i],"while("))
            function->number_of_while_loops+=1;
        if(strstr(line[i],"if("))
            function->number_of_if+=1;
        if(strstr(line[i],"else if("))
            function->number_of_else_if+=1;
        else if(strstr(line[i],"else"))
            function->number_of_else+=1;
        if(strstr(line[i],"break;"))
            function->number_of_break+=1;
        if(strstr(line[i],"continue;"))
            function->number_of_continue+=1;
        function->number_of_statements+=1;
        i++;
    }
    while(balanced>0);
    function->number_of_int_variables=0;
    function->number_of_float_variables=0;
    function->number_of_char_variables=0;
    function->number_of_bool_variables=0;
    function->number_of_double_variables=0;
    function->number_of_long_variables=0;
    for(i=pos;i<pos+function->number_of_statements;i++)
    {
        if(strstr(line[i],"int") and strstr(line[i],";"))
            function->number_of_int_variables+=count_number_of_variables(line[i]);
        else if(strstr(line[i],"float") and strstr(line[i],";"))
            function->number_of_float_variables+=count_number_of_variables(line[i]);
        else if(strstr(line[i],"char") and strstr(line[i],";"))
            function->number_of_char_variables+=count_number_of_variables(line[i]);
        else if(strstr(line[i],"double") and strstr(line[i],";"))
            function->number_of_double_variables+=count_number_of_variables(line[i]);
        else if(strstr(line[i],"long") and strstr(line[i],";"))
            function->number_of_long_variables+=count_number_of_variables(line[i]);
        else if(strstr(line[i],"bool") and strstr(line[i],";"))
            function->number_of_bool_variables+=count_number_of_variables(line[i]);
    }
}
bool not_part_of_comment(char line[])
{
    if(strstr(line,"//"))
        return false;
    else if(strstr(line,"/*"))
    {
        part_of_comment=true;
        if(strstr(line,"*/"))
            part_of_comment=false;
        return false;
    }
    else if(strstr(line,"*/"))
    {
        part_of_comment=false;
        return false;
    }
    else if(part_of_comment)
        return false;
    return true;
}
data * get_complete_details(char name_of_file_given_as_input[])
{
    char name_of_file[16];
    strcpy(name_of_file,name_of_file_given_as_input);
    FILE *source=fopen(name_of_file,"r");
    data *source_data=(data *)malloc(sizeof(data));
    int i=0;
    char trash;
    int number_of_lines=0;
    char line[192];
    clrscr();
    part_of_comment=false;
    while(fgets(source_data->line[i],192,source))
    {
        if(not_part_of_comment(source_data->line[i]))
            number_of_lines+=1;
        else
            --i;
        i+=1;
    }
    fclose(source);
    name_of_file[strlen(name_of_file)-4]='\0';
    strcpy(source_data->name_of_file,name_of_file);
    source_data->number_of_lines=number_of_lines;
    source_data->number_of_scan=0;
    source_data->number_of_print=0;
    source_data->number_of_for=0;
    source_data->number_of_while=0;
    source_data->number_of_if=0;
    source_data->number_of_else=0;
    source_data->number_of_else_if=0;
    source_data->number_of_int=0;
    source_data->number_of_float=0;
    source_data->number_of_char=0;
    source_data->number_of_bool=0;
    source_data->number_of_long=0;
    source_data->number_of_double=0;
    source_data->number_of_include=0;
    source_data->number_of_define=0;
    source_data->number_of_struct=0;
    source_data->number_of_typedef=0;
    source_data->number_of_void_functions=0;
    source_data->number_of_int_functions=0;
    source_data->number_of_float_functions=0;
    source_data->number_of_char_functions=0;
    source_data->number_of_bool_functions=0;
    source_data->number_of_long_functions=0;
    source_data->number_of_double_functions=0;
    source_data->number_of_functions=0;
    i=0;
    int number_of_functions=0;
    while(i<source_data->number_of_lines)
    {
        strcpy(line,source_data->line[i]);
        int length=strlen(line)-2;
        line[length]='\0';
        if(line[length-1]==')')
        {
            if(strstr(line,"void")==line)
            {
                source_data->number_of_functions+=1;
                source_data->number_of_void_functions+=1;
                get_function_details(&(source_data->function[number_of_functions]),source_data->line,i);
                number_of_functions+=1;
            }
            else if(strstr(line,"int")==line)
            {
                source_data->number_of_functions+=1;
                source_data->number_of_int_functions+=1;
                get_function_details(&(source_data->function[number_of_functions]),source_data->line,i);
                number_of_functions+=1;
            }
            else if(strstr(line,"float")==line)
            {
                source_data->number_of_functions+=1;
                source_data->number_of_float_functions+=1;
                get_function_details(&(source_data->function[number_of_functions]),source_data->line,i);
                number_of_functions+=1;
            }
            else if(strstr(line,"char")==line)
            {
                source_data->number_of_functions+=1;
                source_data->number_of_char_functions+=1;
                get_function_details(&(source_data->function[number_of_functions]),source_data->line,i);
                number_of_functions+=1;
            }
            else if(strstr(line,"bool")==line)
            {
                source_data->number_of_functions+=1;
                source_data->number_of_bool_functions+=1;
                get_function_details(&(source_data->function[number_of_functions]),source_data->line,i);
                number_of_functions+=1;
            }
            else if(strstr(line,"long")==line)
            {
                source_data->number_of_functions+=1;
                source_data->number_of_long_functions+=1;
                get_function_details(&(source_data->function[number_of_functions]),source_data->line,i);
                number_of_functions+=1;
            }
            else if(strstr(line,"double")==line)
            {
                source_data->number_of_functions+=1;
                source_data->number_of_double_functions+=1;
                get_function_details(&(source_data->function[number_of_functions]),source_data->line,i);
                number_of_functions+=1;
            }
        }
        else if(strstr(line,"scanf("))
            source_data->number_of_scan+=1;
        else if(strstr(line,"printf("))
            source_data->number_of_print+=1;
        else if(strstr(line,"for("))
            source_data->number_of_for+=1;
        else if(strstr(line,"while("))
            source_data->number_of_while+=1;
        else if(strstr(line,"if("))
            source_data->number_of_if+=1;
        else if(strstr(line,"else if("))
            source_data->number_of_else_if+=1;
        else if(strstr(line,"else"))
            source_data->number_of_else+=1;
        else if(strstr(line,"break;"))
            source_data->number_of_break+=1;
        else if(strstr(line,"#include"))
            source_data->number_of_include+=1;
        else if(strstr(line,"#define"))
            source_data->number_of_define+=1;
        else if(strstr(line,"struct"))
            source_data->number_of_struct+=1;
        else if(strstr(line,"typedef"))
            source_data->number_of_typedef+=1;
        else if(strstr(line,"int") and strstr(line,";"))
            source_data->number_of_int+=count_number_of_variables(line);
        else if(strstr(line,"float") and strstr(line,";"))
            source_data->number_of_float+=count_number_of_variables(line);
        else if(strstr(line,"char") and strstr(line,";"))
            source_data->number_of_char+=count_number_of_variables(line);
        else if(strstr(line,"bool") and strstr(line,";"))
            source_data->number_of_bool+=count_number_of_variables(line);
        else if(strstr(line,"long") and strstr(line,";"))
            source_data->number_of_long+=count_number_of_variables(line);
        else if(strstr(line,"double") and strstr(line,";"))
            source_data->number_of_double+=count_number_of_variables(line);
        i+=1;
    }
    return source_data;
}
int function_compare(Function *function1, Function *function2)
{
    int number_of_matching=0;
    strlwr(function1->name);
    strlwr(function2->name);
    if(strcmp(function1->name,function2->name)==0)
        number_of_matching+=1;
    if(strcmp(function1->return_type,function2->return_type)==0)
        number_of_matching+=1;
    if(function1->number_of_arguments==function2->number_of_arguments)
        number_of_matching+=1;
    if(function1->number_of_int_arguments==function2->number_of_int_arguments)
        number_of_matching+=1;
    if(function1->number_of_char_arguments==function2->number_of_char_arguments)
        number_of_matching+=1;
    if(function1->number_of_float_arguments==function2->number_of_float_arguments)
        number_of_matching+=1;
    if(function1->number_of_bool_arguments==function2->number_of_bool_arguments)
        number_of_matching+=1;
    if(function1->number_of_long_arguments==function2->number_of_long_arguments)
        number_of_matching+=1;
    if(function1->number_of_double_arguments==function2->number_of_double_arguments)
        number_of_matching+=1;
    if(function1->number_of_int_variables==function2->number_of_int_variables)
        number_of_matching+=1;
    if(function1->number_of_float_variables==function2->number_of_float_variables)
        number_of_matching+=1;
    if(function1->number_of_char_variables==function2->number_of_char_variables)
        number_of_matching+=1;
    if(function1->number_of_double_variables==function2->number_of_double_variables)
        number_of_matching+=1;
    if(function1->number_of_long_variables==function2->number_of_long_variables)
        number_of_matching+=1;
    if(function1->number_of_bool_variables==function2->number_of_bool_variables)
        number_of_matching+=1;
    if(function1->number_of_print_statements==function2->number_of_print_statements)
        number_of_matching+=1;
    if(function1->number_of_scan_statements==function2->number_of_scan_statements)
        number_of_matching+=1;
    if(function1->number_of_for_loops==function2->number_of_for_loops)
        number_of_matching+=1;
    if(function1->number_of_while_loops==function2->number_of_while_loops)
        number_of_matching+=1;
    if(function1->number_of_if==function2->number_of_if)
        number_of_matching+=1;
    if(function1->number_of_else_if==function2->number_of_else_if)
        number_of_matching+=1;
    if(function1->number_of_else==function2->number_of_else)
        number_of_matching+=1;
    if(function1->number_of_break==function2->number_of_break)
        number_of_matching+=1;
    if(function1->number_of_continue==function2->number_of_continue)
        number_of_matching+=1;
    if(function1->number_of_statements==function2->number_of_statements)
        number_of_matching+=1;
    return number_of_matching;
}
int longest_common_subseqence( char *string1, char *string2, int m, int n)
{
    int l[m+1][n+1];
    int i,j;
    for(i=0;i<=m;i++)
    {
        for(j=0;j<=n;j++)
        {
            if(i==0 or j==0)
                l[i][j]=0;
            else if(string1[i-1]==string2[j-1])
                l[i][j]=l[i-1][j-1]+1;
            else
                l[i][j]=max(l[i-1][j],l[i][j-1]);
        }
    }
    return l[m][n];
}
float statement_compare(data *source_data, data *destination)
{
    float statement_matching_percentage;
    int number_of_statements_matching=0;
    int source_line,destination_line;
    int maximum_lines=max(source_data->number_of_lines,destination->number_of_lines);
    if(maximum_lines==0)
        return 0;
    for(source_line=0;source_line<source_data->number_of_lines;source_line++)
    {
        for(destination_line=0;destination_line<destination->number_of_lines;destination_line++)
        {
            int length1=strlen(source_data->line[source_line]);
            int length2=strlen(destination->line[destination_line]);
            int maximum=max(length1,length2);
            if(longest_common_subseqence(source_data->line[source_line],destination->line[destination_line],length1,length2)>=(maximum-(0.1*maximum)))
            {
                number_of_statements_matching+=1;
                break;
            }
        }
    }
    statement_matching_percentage=(100*number_of_statements_matching)/maximum_lines;
    return statement_matching_percentage;
}
void deep_compare(data *source_data, data *destination)
{
    clrscr();
    newline(3);
    tab(3);
    printf("Comparing %s and %s.....",source_data->name_of_file,destination->name_of_file);
    int total_parameters=27;
    int number_of_matching_parameters=0;
    if(abs(source_data->number_of_functions-destination->number_of_functions)<=number_of_functions_matching_limit)
        number_of_matching_parameters+=1;
    if(abs(source_data->number_of_lines-destination->number_of_lines)<=number_of_lines_matching_limit)
        number_of_matching_parameters+=1;
    if(abs(source_data->number_of_scan-destination->number_of_scan)<=number_of_scan_matching_limit)
        number_of_matching_parameters+=1;
    if(abs(source_data->number_of_print-destination->number_of_print)<=number_of_print_matching_limit)
        number_of_matching_parameters+=1;
    if(abs(source_data->number_of_for-destination->number_of_for)<=number_of_for_matching_limit)
        number_of_matching_parameters+=1;
    if(abs(source_data->number_of_while-destination->number_of_while)<=number_of_while_matching_limit)
        number_of_matching_parameters+=1;
    if(abs(source_data->number_of_if-destination->number_of_if)<=number_of_if_matching_limit)
        number_of_matching_parameters+=1;
    if(abs(source_data->number_of_else-destination->number_of_else)<=number_of_else_matching_limit)
        number_of_matching_parameters+=1;
    if(abs(source_data->number_of_else_if-destination->number_of_else_if)<=number_of_else_if_matching_limit)
        number_of_matching_parameters+=1;
    if(abs(source_data->number_of_break-destination->number_of_break)<=number_of_break_matching_limit)
        number_of_matching_parameters+=1;
    if(abs(source_data->number_of_int-destination->number_of_int)<=number_of_int_matching_limit)
        number_of_matching_parameters+=1;
    if(abs(source_data->number_of_float-destination->number_of_float)<=number_of_float_matching_limit)
        number_of_matching_parameters+=1;
    if(abs(source_data->number_of_char-destination->number_of_char)<=number_of_char_matching_limit)
        number_of_matching_parameters+=1;
    if(abs(source_data->number_of_long-destination->number_of_long)<=number_of_long_matching_limit)
        number_of_matching_parameters+=1;
    if(abs(source_data->number_of_double-destination->number_of_double)<=number_of_double_matching_limit)
        number_of_matching_parameters+=1;
    if(abs(source_data->number_of_bool-destination->number_of_bool)<=number_of_bool_matching_limit)
        number_of_matching_parameters+=1;
    if(abs(source_data->number_of_include-destination->number_of_include)<=number_of_include_matching_limit)
        number_of_matching_parameters+=1;
    if(abs(source_data->number_of_define-destination->number_of_define)<=number_of_define_matching_limit)
        number_of_matching_parameters+=1;
    if(abs(source_data->number_of_struct-destination->number_of_struct)<=number_of_struct_matching_limit)
        number_of_matching_parameters+=1;
    if(abs(source_data->number_of_typedef-destination->number_of_typedef)<=number_of_typedef_matching_limit)
        number_of_matching_parameters+=1;
    if(abs(source_data->number_of_void_functions-destination->number_of_void_functions)<=number_of_void_functions_matching_limit)
        number_of_matching_parameters+=1;
    if(abs(source_data->number_of_int_functions-destination->number_of_int_functions)<=number_of_int_functions_matching_limit)
        number_of_matching_parameters+=1;
    if(abs(source_data->number_of_float_functions-destination->number_of_float_functions)<=number_of_float_functions_matching_limit)
        number_of_matching_parameters+=1;
    if(abs(source_data->number_of_char_functions-destination->number_of_char_functions)<=number_of_char_functions_matching_limit)
        number_of_matching_parameters+=1;
    if(abs(source_data->number_of_bool_functions-destination->number_of_bool_functions)<=number_of_bool_functions_matching_limit)
        number_of_matching_parameters+=1;
    if(abs(source_data->number_of_long_functions-destination->number_of_long_functions)<=number_of_long_functions_matching_limit)
        number_of_matching_parameters+=1;
    if(abs(source_data->number_of_double_functions-destination->number_of_double_functions)<=number_of_double_functions_matching_limit)
        number_of_matching_parameters+=1;
    float parameters_matching_percentage = ((float)((float)(100*number_of_matching_parameters))/((float)(total_parameters)));
    int total_matching_functions=0;
    int total_function_parameters=25;
    int max_of_functions=max(source_data->number_of_functions,destination->number_of_functions);
    for(int i=0;i<source_data->number_of_functions;i++)
    {
        for(int j=0;j<destination->number_of_functions;j++)
        {

            int matching_function_parameters=function_compare(&(source_data->function[i]),&(destination->function[j]));
            float current_matching_percentage=(float)(100*matching_function_parameters/total_function_parameters);
            if(current_matching_percentage>function_match_percentage_limit)
            {
                total_matching_functions+=1;
                break;
            }
        }
    }
    float function_matching_percentage=0;
    float statement_matching_percentage=0;
    float cumulative_matching_percentage=0;
    if(max_of_functions==0);
    else
    {
        function_matching_percentage=(float)((total_matching_functions*100)/max_of_functions);
        statement_matching_percentage=statement_compare(source_data,destination);
        cumulative_matching_percentage=parameters_matching_percentage+function_matching_percentage+statement_matching_percentage;
        cumulative_matching_percentage/=3;
    }
    newline(3);
    tab(4);
    if(cumulative_matching_percentage>cumulative_match_percentage_limit)
    {
        printf("PLAGIARISM ACTIVITY CONFIRMED!!!");
        newline(2);
        tab(3);
        printf("Would you like to Write Results to a File?(Y/N)\t");
        char choice;
        system("/bin/stty raw");
        choice=getchar();
        system("/bin/stty cooked");
        if(choice=='Y' or choice=='y')
        {
            printf("Writing the Result...");
            newline(2);
            tab(3);
            if(write_results(source_data,destination,true,parameters_matching_percentage,function_matching_percentage,statement_matching_percentage))
                printf("Results written Successfully!!!");
            else
                printf("Failure in Writing Results!!!");
        }
    }
    else
    {
        printf("SIMILARITIES AMONG DOCUMENTS IS LESS THAN SPECIFIED THRESHOLD");
        newline(2);
        tab(3);
        printf("Would you like to Write Results to a File?(Y/N)\t");
        char choice;
        system("/bin/stty raw");
        choice=getchar();
        system("/bin/stty cooked");
        if(choice=='Y' or choice=='y')
        {
            newline(2);
            tab(3);
            if(write_results(source_data,destination,false,parameters_matching_percentage,function_matching_percentage,statement_matching_percentage))
                printf("Results Written Successfully!!!");
            else
                printf("Failure in Writing Results!!!");
        }
    }
    newline(2);
    tab(3);
    printf("Press any key to Continue...");
    raw_input();
}
void report_plagiarism(char name_of_source[], int number_of_files)
{
    data *source = get_complete_details(name_of_source);
    char name_of_destination[]="file01.txt";
    for(int i=1;i<=number_of_files;i++)
    {
        if(strcmp(name_of_source,name_of_destination)!=0)
        {
            data *destination = get_complete_details(name_of_destination);
            deep_compare(source,destination);
            free(destination);
        }
        if(name_of_destination[5]=='9')
        {
            name_of_destination[5]='0';
            name_of_destination[4]+=1;
        }
        else
        {
            name_of_destination[5]+=1;
        }
    }
}
int main()
{
    clrscr();
    display_introduction();
    bool flag=true;
    int number_of_files;
    chdir("Files_to_be_checked");
    char name_of_file[100];
    while(flag)
    {
        clrscr();
        newline(3);
        tab(4);
        printf("This Application detects Plagiarism among Set of Programming Codes");
        newline(2);
        tab(4);
        printf("Choose a file to search for Plagiarised Content among others");
        number_of_files=display_files(".");
        printf("Enter the name of the File to be checked:\t");
        scanf("%s",name_of_file);
        char trash;
        scanf("%c",&trash);
        report_plagiarism(name_of_file,number_of_files);
        flag=prompt_continue();
    }
    chdir("..");
    display_conclusion();
    return 0;
}//********************     Programming is an Art...    HOPE YOU LIKE IT    **************************