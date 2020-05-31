#include <iostream>
#include<fstream>
#include<string>
#include<Windows.h>
#include<conio.h>
#include<cstdlib>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
int error;
int rec_flag_book=0,no_book=0;
char rec_ind_book[5];
int update_stocks;
bool flag=false;
void Login(string& admin ,string& password);
void staff(string& user ,string& pass1);

struct Book
{
 char title[20];
 char author[20];
 char bookid[20];
 char publication[20];
 char price[20];
 char stock[20];
 char year[20];
 char ind[5];

}BookData[30];

struct index
{
char bookid[20],indbook[5];
}inbook[20],tempbook;

//For Background
void color()
{
    int col;
    cout<<"\n\n\t1.Black and White Theme"<<endl;
    cout<<"\n\t2.White and Black Theme"<<endl;
    cout<<"\n\t3.Yellow and Red Theme"<<endl;
    cout<<"\n\t4.Purple and White Theme "<<endl;
    cout<<"\n\t5.Aqua and Black Theme \n\n\t0.Return"<<endl;

    do{
        do
        {
            error=0;
            cout<<"\n\n\tEnter your selection here:\t";
            cin>>col;
            if(cin.fail())
            {
                cout<<"\n\tPlease Enter a valid option\t"<<endl;
                error=1;
                cin.clear();
                cin.ignore(80,'\n');
            }
        }while(error == 1);
        if(col==1)
        {
            system("color 0F");
            system("cls");
            return;
        }
        else if(col==2)
        {
            system("color F0");
            system("cls");
            return;
        }
        else if(col==3)
        {
            system("color E4");
            system("cls");
            return;
        }
         else if(col==4)
        {
            system("color D7");
            system("cls");
            return;
        }
        else if(col==5)
        {
            system("color B0");
            system("cls");
            return;
        }
    }while(col!=0);
     system("cls");
     return;
}

//For Password
string getpass(const char *prompt, bool show_asterisk=true)
{
  const char BACKSPACE=8;
  const char RETURN=13;

  string password;
  unsigned char ch=0;

  cout <<"\n\t"<<prompt;

  DWORD con_mode;
  DWORD dwRead;

  HANDLE hIn=GetStdHandle(STD_INPUT_HANDLE);

  GetConsoleMode( hIn, &con_mode );
  SetConsoleMode( hIn, con_mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT) );

  while(ReadConsoleA( hIn, &ch, 1, &dwRead, NULL) && ch !=RETURN)
    {
       if(ch==BACKSPACE)
         {
            if(password.length()!=0)
              {
                 if(show_asterisk)
                     cout <<"\b\b";
                 password.resize(password.length()-1);
              }
         }
       else
         {
             password+=ch;
             if(show_asterisk)
                 cout <<'*';
         }
    }
  cout <<endl;
  return password;
}


void sort_index_book()
{
int i,j;
for(i=0;i<no_book-1;i++)
for(j=0;j<no_book-i-1;j++)
if(strcmp(inbook[j].bookid,inbook[j+1].bookid)>0)
{
tempbook=inbook[j];
inbook[j]=inbook[j+1];
inbook[j+1]=tempbook;
}
}

void retrive_record_book(char *ind)
{
for(int i=0;i<no_book;i++)
{
if(strcmp(BookData[i].ind,ind)==0)
{
strcpy(rec_ind_book,ind);
rec_flag_book=1;
cout<<"\n\n\t--------------------------------------------------------------------------------------------------------";
cout<<"\n\tIndex |   Title      |     Author     | Book_Id | Publication       |  Price  | Stock | Published year   ";
cout<<"\n\t---------------------------------------------------------------------------------------------------------\n";
cout<<"\n\n\t"<<BookData[i].ind<<"\t"<<" "<<BookData[i].title<<"\t"<<" "<<BookData[i].author<<"\t"<<" "<<BookData[i].bookid<<"\t"<<" "<<" "<<BookData[i].publication<<"\t"<<"\t"<<BookData[i].price<<"\t"<<" "<<BookData[i].stock<<"\t"<<" "<<BookData[i].year<<"\n";
return;
}
}
system("pause");
}

int search_index_book(char *bookid)
{
int f=0;
for(int i=0;i<no_book;i++)
{
if(strcmp(inbook[i].bookid,bookid)==0)
{
retrive_record_book(inbook[i].indbook);
update_stocks=i;
f=1;
}
}
if(f)
return 1;
else
return -1;
}

int search_id_book(char *bookid,int j)
{
int f=0;
for(int i=0;i<j;i++)
{
if(strcmp(BookData[i].bookid,bookid)==0)
{
f=1;
break;
}
}
if(f)
return 1;
else
return -1;
}
void delete_book(char *st_bookid)
{
rec_flag_book=0;
int fr=0;
search_index_book(st_bookid);
if(!rec_flag_book)
{
cout<<"\n\ntDeletion failed.Record not found\n";
system("pause");
return;

}
for(int i=0;i<no_book;i++)
{
if(strcmp(BookData[i].ind,rec_ind_book)==0)
{
fr=i;
break;
}
}
for(int i=fr;i<no_book-1;i++)
{
BookData[i]=BookData[i+1];
char str[3];
sprintf(str,"%d",i);
strcpy(BookData[i].ind,str);
}
no_book--;
fstream f1,f2;
f1.open("book_details.txt",ios::out);
f2.open("index_book.txt",ios::out);
for(int i=0;i<no_book;i++)
{
strcpy(inbook[i].bookid,BookData[i].bookid);
strcpy(inbook[i].indbook,BookData[i].ind);
}
sort_index_book();
for(int i=0;i<no_book;i++)
{
f1<<BookData[i].ind<<"|"<<BookData[i].title<<"|"<<BookData[i].author<<"|"<<BookData[i].bookid<<"|"<<BookData[i].publication<<"|"<<BookData[i].price<<"|"<<BookData[i].stock<<BookData[i].year<<"\n";
f2<<inbook[i].bookid<<"|"<<inbook[i].indbook<<"\n";
}
f1.close();
f2.close();
cout<<"\n\n\tDeletion successful\n";
system("pause");
}

void update_stock(char *id ,char *p)
{

    for (int k = 0;k<no_book;k++)
    {
        if(strcmp(BookData[k].bookid,id)==0)
        {

                strcpy(BookData[k].stock,p);
        }
    }
    fstream f1;
f1.open("book_details.txt",ios::out);
    for(int k = 0;k<no_book;k++ )
    {

        f1<<BookData[k].ind<<"|"<<BookData[k].title<<"|"<<BookData[k].author<<"|"<<BookData[k].bookid<<"|"<<BookData[k].publication<<"|"<<BookData[k].price<<"|"<<BookData[k].stock<<"|"<<BookData[k].year<<"\n";
    }
    f1.close();
    cout<<"\n\n\tUpdation successful\n";
    cout<<"\n\n\t**********************************************************************************************************";
    cout<<"\n\t\t\t\t\t\tUpdated Book Stock ";
    cout<<"\n\t*************************************************************************************************************\n\n";
    cout<<"\n\n\t--------------------------------------------------------------------------------------------------------";
    cout<<"\n\tIndex |   Title      |     Author     | Book_Id | Publication       |  Price  | Stock | Published year   ";
    cout<<"\n\t---------------------------------------------------------------------------------------------------------\n";
    for (int x=0;x<no_book;x++)
    {
       cout<<"\n\n\t"<<BookData[x].ind<<"\t"<<" "<<BookData[x].title<<"\t"<<" "<<BookData[x].author<<"\t"<<" "<<BookData[x].bookid<<"\t"<<" "<<" "<<BookData[x].publication<<"\t"<<"\t"<<BookData[x].price<<"\t"<<" "<<BookData[x].stock<<"\t"<<" "<<BookData[x].year<<"\n";
    }
   system("pause");
}

//Function to change Font Size
/*void fontsize()
{
    short font,x,y;
    do
    {
        error=0;
        cout<<"\n\tEnter Font Size:";
        cin>>font;
        if(font>=25 || font<=5)
        {
            cout<<"Please Enter Font Size Less Than 25 & Greater Than 5..."<<endl;
            error=1;
            cin.clear();
            cin.ignore(80,'\n');
        }
        if(cin.fail())
        {
            cout<<"\tPlease Enter a valid input....."<<endl;
            error=1;
            cin.clear();
            cin.ignore(80,'\n');
        }
    }while(error==1);
    x=font;
    y=2*x;
    HANDLE Hout=::GetStdHandle(STD_OUTPUT_HANDLE);
    COORD fsize={x,y};
    CONSOLE_FONT_INFOEX Font={sizeof(Font)};
    ::GetCurrentConsoleFontEx(Hout,false,&Font);

    Font.dwFontSize=fsize;
    SetCurrentConsoleFontEx(Hout,0,&Font);
    cin.clear();
    system("cls");
    }*/

int main()//main function
{
    fstream ff,fi;
    ff.open("book_details.txt",ios::in);
    for(int i=0;i<500;i++)
    {
    ff.getline(BookData[i].ind,5,'|');
    if(strcmp(BookData[i].ind,"")==0)
    break;
    ff.getline(BookData[i].title,20,'|');
    ff.getline(BookData[i].author,20,'|');
    ff.getline(BookData[i].bookid,20,'|');
    ff.getline(BookData[i].publication,20,'|');
    ff.getline(BookData[i].price,20,'|');
    ff.getline(BookData[i].stock,20,'|');
    ff.getline(BookData[i].year,20,'\n');
     int m=atoi(BookData[i].ind);
   //  cout<<"m"<<m<<endl;
    if(i==m)
    {
         no_book++;
    }
    else
        break;
    }
    ff.close();
    fi.open("index_book.txt",ios::out|ios::app);
    for(int i=0;i<no_book;i++)
    {
    strcpy(inbook[i].bookid,BookData[i].bookid);
    strcpy(inbook[i].indbook,BookData[i].ind);
    }
    sort_index_book();
    for(int i=0;i<no_book;i++)
    {
    fi<<inbook[i].bookid<<"|"<<inbook[i].indbook<<"\n";
    }
    fi.close();
    char title[20];
    char author[20];
    char bookid[20];
    char st_bookid[20];
    char publication[20];
    char price[20];
    char stock[20];
    char year[20];
    char ind_book[5];
    int choice;
    string User,password;
    do{
        cin.clear();
        cout<<"\n\n\t-----------------------------------------------------------------------------------------";
        cout<<"\n\t\t\t\t\tWelcome To Book Store";
        cout<<"\n\t-----------------------------------------------------------------------------------------";
        cout<<"\n\n\tPlease select an option from the given below\n\n";
        cout<<"\n\t1.Admin Login \n\n\t2.Staff Login \n\n\t3.Guest Login \n\n\t4.Change Theme \n\n\t5.Exit\n";
        do{
            error=0;
            cout<<"\n\t Please Enter Your Selection:";
            cin>>choice;
            if(cin.fail())
            {
                cout<<"\n\tPlease Enter a valid input"<<endl;
                error=1;
                cin.clear();
                cin.ignore(80,'\n');
            }
            }while(error==1);
            switch(choice)
            {
            case 1:
                {
                    cout<<"\n\n\t-----------------------------------------------------------------------------------------";
                    cout<<"\n\t\t\t\t\t\tPlease Login ";
                    cout<<"\n\t-----------------------------------------------------------------------------------------\n\n";
                    cout<<"\n\tPlease Enter The Admin Username:";
                    cin>>User;
                    //cout<<"\n\tPlease Enter The Password: ";
                    //cin>>password
                    password=getpass("\n\tPlease Enter The Password: ",true);
                    Login(User,password);
                    if(flag==true)
                    {
                       // cin.clear();
                        system("pause");
                        int con=0;
                        do
                        {
                            fstream file1;
                            int n;
                            int i=0,j;
                            char ch;
                            cout<<"\n\t-----------------------------------------------------------------------------------------";
                            cout<<"\n\t\t\t\t\tWelcome to Administration Menu";
                            cout<<"\n\t-----------------------------------------------------------------------------------------\n\n";
                            cout<<"\n\n\t1.Add a book\n\n\t2.Search a book\n\n\t3.Remove a book \n\n\t4.Update a book stock\n\n\t5.Display all book\n\n\t6.Exit\n\n\tEnter what do you want to do?\t";
                            cin>>ch;
                            switch(ch) {
                                    case '1'://Insert data
                                    {
                                    file1.open("book_details.txt",ios::out|ios::app);

                                    while(ch!='n')
                                    {

                                    if((ch=='y')||(ch=='Y')||(ch=='1'))
                                    {

                                        cout<<"\n\n\tEnter the No of Books:\t";
                                        cin>>n;
                                        cout<<"\n\n\tEnter the details\n";
                                        for(i = no_book;i<no_book+n;i++)
                                      {
                                        label: cout<<"\n\n\tEnter "<<i+1<<" Book details:\n";
                                        cout<<"\n\n\tEnter Title : ";
                                        cin>>BookData[i].title;
                                        cout<<"\n\n\tEnter Author : ";
                                        cin>>BookData[i].author;
                                        cout<<"\n\n\tEnter BookId : ";
                                        cin>>BookData[i].bookid;
                                        cout<<"\n\n\tEnter Publication : ";
                                        cin>>BookData[i].publication;
                                        cout<<"\n\n\tEnter Price : ";
                                        cin>>BookData[i].price;
                                        cout<<"\n\n\tEnter Stock: ";
                                        cin>>BookData[i].stock;
                                        cout<<"\n\n\tEnter published year:";
                                        cin>>BookData[i].year;
                                        int q = search_id_book(BookData[i].bookid,i);
                                        if(q==1)
                                        {
                                        cout<<"\n\n\tDuplicate value\n";
                                        cout<<"\n\n\tEnter Again:\n";
                                        goto label;
                                        }
                                        file1<<i<<"|"<<BookData[i].title<<"|"<<BookData[i].author<<"|"<<BookData[i].bookid<<"|"<<BookData[i].publication<<"|"<<BookData[i].price<<"|"<<BookData[i].stock<<"|"<<BookData[i].year<<"\n";

                                        }
                                        no_book=no_book+n;
                                        cout<<"\n\n\tDo you want to enter more data?\n ";
                                        cout<<"\n\n\tPress Y for Continue and N to Finish:  ";
                                        cin>>ch;
                                            }
                                        }
                                        file1.close();
                                        fstream file1,file2;
                                        file1.open("book_details.txt",ios::in);
                                        file2.open("index_book.txt",ios::out);
                                        for(int i=0;i<no_book;i++)
                                        {
                                        file1.getline(ind_book,5,'|');
                                        file1.getline(title,20,'|');
                                        file1.getline(author,20,'|');
                                        file1.getline(bookid,20,'|');
                                        file1.getline(publication,20,'|');
                                        file1.getline(price,20,'|');
                                        file1.getline(stock,20,'|');
                                        file1.getline(year,20,'\n');
                                        strcpy(BookData[i].ind,ind_book);
                                        strcpy(inbook[i].bookid,bookid);
                                        strcpy(inbook[i].indbook,ind_book);
                                        }
                                        sort_index_book();
                                        for(int i=0;i<no_book;i++)
                                        {
                                        file2<<inbook[i].bookid<<"|"<<inbook[i].indbook<<"\n";
                                        }
                                        file1.close();
                                        file2.close();

                            }continue;
                            case '2'://search data
                                    {
                                    cout<<"\n\n\tEnter the Id of the book whose record is to be searched:\t";
                                    cin>>st_bookid;
                                    int q = search_index_book(st_bookid);
                                    if(q==1)
                                    {
                                    cout<<"\n\n\tRecord found:";
                                    system("pause");
                                    }
                                    else{
                                    cout<<"\n\n\tBook Id not found\n";
                                    system("pause");
                                    }
                                    }
                                   continue;
                            case '3':
                                    {
                                     cout<<"\n\n\tEnter the Id of the Book whose record is to be deleted:\t";
                                    cin>>st_bookid;
                                    delete_book(st_bookid);
                                        }
                                    continue;
                            case '4'://update stock
                                    {
                                     char id[20];
                                     char p[20];

                                    cout<<"\n\n\tEnter the Id of the book whose status you want to update:";
                                    cin>>id;
                                    cout<<"\n\n\tEnter the book stock:";
                                    cin>>p;
                                    update_stock(id,p);
                                    }
                               continue;
                                case '5'://display all data
                                    {
                                    fstream f1;
                                    f1.open("book_details.txt",ios::in);
                                    if(!f1)
                                    {
                                    cout<<"Error!!!";
                                    exit(0);
                                    }
                                    int x=0;
                                    //cout<<"book"<<no_book<<endl;
                                  cout<<"\n\n\t--------------------------------------------------------------------------------------------------------";
                                  cout<<"\n\tIndex |   Title      |     Author     | Book_Id | Publication       |  Price  | Stock | Published year   ";
                                  cout<<"\n\t---------------------------------------------------------------------------------------------------------\n";
                                          //cout<<no_book;
                                    while(x!=no_book)
                                    {
                                       cout<<"\n\n\t"<<BookData[x].ind<<"\t"<<" "<<BookData[x].title<<"\t"<<" "<<BookData[x].author<<"\t"<<" "<<BookData[x].bookid<<"\t"<<" "<<" "<<BookData[x].publication<<"\t"<<"\t"<<BookData[x].price<<"\t"<<" "<<BookData[x].stock<<"\t"<<" "<<BookData[x].year<<"\n";
                                       x++;
                                    }
                                    f1.close();
                                    system("pause");
                                    }
                                  continue;
                                    case '6':
                                    {
                                    con=1;
                                    }

                        }
                     }while(con!=1);
                   }
                }break;

                case 2:
                     {
                    cout<<"\n\n\t-----------------------------------------------------------------------------------------";
                    cout<<"\n\t\t\t\t\t\tPlease Login";
                    cout<<"\n\t-----------------------------------------------------------------------------------------\n\n";
                    cout<<"\n\tPlease Enter The Staff Username:";
                    cin>>User;
                    password=getpass("\n\tPlease Enter The Password: ",true);
                    staff(User,password);
                     if(flag==true)
                    {
                        cin.clear();
                        system("pause");
                        int con=0;
                        do
                        {
                             int i;
                             char ch;
                             cout<<"\n\t-----------------------------------------------------------------------------------------";
                             cout<<"\n\t\t\t\t\tWelcome to Staff Menu";
                             cout<<"\n\t-----------------------------------------------------------------------------------------\n\n";
                             cout<<"\n\n\t1.Search a book\n\n\t2.Update a book stock\n\n\t3.Display all book\n\n\t4.Exit\n\n\tEnter what do you want to do?\t";
                             cin>>ch;
                            switch(ch) {
                            case '1'://search data
                                    {
                                    cout<<"\n\n\tEnter the Id of the book whose record is to be searched:\t";
                                    cin>>st_bookid;
                                    int q = search_index_book(st_bookid);
                                    if(q==1){
                                    cout<<"\n\n\tSearch successful\n";
                                    system("pause");
                                    }
                                    else{
                                    cout<<"\n\n\tSearch unsuccessful\n";
                                    system("pause");
                                    }
                                    }
                                    continue;
                            case '2'://update stock
                                    {
                                     char u_bookid[20];
                                    int number;
                                    cout<<"\n\n\tEnter the Book_id:\t";
                                    cin>>u_bookid;
                                    int q = search_index_book(u_bookid);
                                    if(q==1)
                                    {
                                     cout<<"\n\n\tEnter the copies sold:\t";
                                     cin>>number;
                                     fstream ff;
                                     ff.open("book_details.txt",ios::in);
                                     for(int i=0;i<no_book;i++)
                                        {
                                        ff.getline(BookData[i].ind,5,'|');
                                        if(strcmp(BookData[i].ind,"")==0)
                                        break;
                                        ff.getline(BookData[i].title,20,'|');
                                        ff.getline(BookData[i].author,20,'|');
                                        ff.getline(BookData[i].bookid,20,'|');
                                        ff.getline(BookData[i].publication,20,'|');
                                        ff.getline(BookData[i].price,20,'|');
                                        ff.getline(BookData[i].stock,20,'|');
                                        ff.getline(BookData[i].year,20,'\n');
                                        int m=atoi(BookData[update_stocks].stock);
                                        if(m-number>0)
                                        {
                                        number=m-number;
                                        cout<<number;
                                        int k=update_stocks;
                                        snprintf(BookData[k].stock, sizeof(BookData[k].stock), "%d", number);
                                       //itoa(number,BookData[k].stock,10);
                                        /*char letter = "0";
                                        for(int x = 0; x < number; x++)
                                           letter++;*/
                                        //BookData[k].stock=number;
                                        ff<<BookData[k].ind<<"|"<<BookData[k].title<<"|"<<BookData[k].author<<"|"<<BookData[k].bookid<<"|"<<BookData[k].publication<<"|"<<BookData[k].price<<"|"<<BookData[k].stock<<"|"<<BookData[k].year<<"\n";
                                        }
                                        else
                                        {
                                            cout<<"\n\n\tInvalid input\n";
                                            break;
                                        }
                                    }
                                    }
                                    else
                                    {
                                        cout<<"\n\n\tBook Id not found\n";
                                    }
                                    }
                                    continue;
                                case '3'://display all data
                                    {
                                    fstream f1;
                                    f1.open("book_details.txt",ios::in);
                                    if(!f1)
                                    {
                                    cout<<"Error!!!";
                                    exit(0);
                                    }
                                    int x=0;
                                  cout<<"\n\n\t--------------------------------------------------------------------------------------------------------";
                                  cout<<"\n\tIndex |   Title      |     Author     | Book_Id | Publication       |  Price  | Stock | Published year   ";
                                  cout<<"\n\t---------------------------------------------------------------------------------------------------------\n";
                                    while(x!=no_book)
                                    {
                                       cout<<"\n\n\t"<<BookData[x].ind<<"\t"<<" "<<BookData[x].title<<"\t"<<" "<<BookData[x].author<<"\t"<<" "<<BookData[x].bookid<<"\t"<<" "<<" "<<BookData[x].publication<<"\t"<<"\t"<<BookData[x].price<<"\t"<<" "<<BookData[x].stock<<"\t"<<" "<<BookData[x].year<<"\n";
                                       x++;
                                    }
                                    f1.close();
                                    system("pause");
                                    }
                                    continue;
                                    case '4':
                                    {
                                    con=1;
                                    }

                        }
                     }while(con!=1);
                   }
                    }break;

                case 3:
                     {
                         User="Guest";
                         password="guest2";
                         staff(User,password);
                         if(flag==true)
                       {
                        cin.clear();
                        system("pause");
                        int con=0;
                        do
                        {
                             int i;
                             char ch;
                            cout<<"\n\t-----------------------------------------------------------------------------------------";
                            cout<<"\n\t\t\t\t\tWelcome to Guest Menu";
                            cout<<"\n\t-----------------------------------------------------------------------------------------\n\n";
                            cout<<"\n\n\t1.Display all book\n\n\t2.Exit\n\n\tEnter what do you want to do?\t";
                             cin>>ch;
                            switch(ch) {
                                case '1'://display all data
                                    {
                                    fstream f1;
                                    f1.open("book_details.txt",ios::in);
                                    if(!f1)
                                    {
                                    cout<<"Error!!!";
                                    exit(0);
                                    }
                                    int x=0;
                                  cout<<"\n\n\t--------------------------------------------------------------------------------------------------------";
                                  cout<<"\n\tIndex |   Title      |     Author     | Book_Id | Publication       |  Price  | Stock | Published year   ";
                                  cout<<"\n\t---------------------------------------------------------------------------------------------------------\n";
                                    while(x!=no_book)
                                    {
                                       cout<<"\n\n\t"<<BookData[x].ind<<"\t"<<" "<<BookData[x].title<<"\t"<<" "<<BookData[x].author<<"\t"<<" "<<BookData[x].bookid<<"\t"<<" "<<" "<<BookData[x].publication<<"\t"<<"\t"<<BookData[x].price<<"\t"<<" "<<BookData[x].stock<<"\t"<<" "<<BookData[x].year<<"\n";
                                       x++;
                                    }
                                    f1.close();
                                    system("pause");
                                    }
                                    continue;
                                    case '2':
                                    {
                                    con=1;
                                    }

                        }
                     }while(con!=1);
                   }

                  }break;

                /*case 4: setConsole(); break;*/
                case 4:  color();break;
                case 5:
                    {
                       cout<<"\n\n\t Thank You Using this software...............\n\n\n";
                       cout<<"**************************************#Devolped by @Piyush#********************************************"<<endl;
                       cout<<"\n\n";
                       choice=5;

                    }
            }

        }while(choice!=5);

    return 0;
}


//login function for admin
void Login(string& admin ,string& password)
{
    string Users[200];
    string Pass[200];
    bool valid=false;

    int x=0;
    ifstream Usfile;
    Usfile.open("admin.txt");
    Usfile>>Users[x] >>Pass[x];
    while(Usfile)//read user name and password from file
    {
        x++;
        if(x>=200)
            break;
        Usfile>>Users[x]>>Pass[x];
    }
    for (int a=0;a<x;a++)
    {
        if(admin==Users[a] && password==Pass[a])//match user name and password
        {
         flag=true;
          cout<<"\n\n\tSuccessfully logged into admin account"<<endl;
          valid=true;
          break;
        }
    }
    if(!valid)
    {
        cout<<"\n\n\tUsername & Password is invalid try again\t\t\n\n";
        system("pause");
    }
}
//Login Function for Staffs
void staff(string& user ,string& pass1)
{
    string Users[200];
    string Pass[200];
    bool valid=false;

    int x=0;
    ifstream Usfile;
    Usfile.open("user.txt");
    char choice;
    Usfile>>Users[x] >>Pass[x];
    while(Usfile)//read user name and password from file
    {
        x++;
        if(x>=200)
            break;
        Usfile>>Users[x]>>Pass[x];
    }
    for (int a=0;a<x;a++)
    {
        if(user==Users[a] && pass1==Pass[a])//match user name and password
        {
          cout<<"\n\n\tSuccessfully logged into Staff account"<<endl;
          flag=true;
          valid=true;
          break;
        }
    if(user=="Guest" & pass1=="guest2")
    {
        cout<<"\n\n\tSuccessfully logged into Guest account"<<endl;
        flag=true;
          valid=true;
          break;
    }
    }
    if(!valid)
    {
        cout<<"\n\n\tUsername & Password is invalid try again\n";
        system("pause");
    }
}
