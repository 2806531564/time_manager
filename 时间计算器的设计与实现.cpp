#include"DateTime.h"
#include"Admin.h"
int main()
{
    system("clear");
    Admin ad1;
    int cursor=1;
    while(true)
    {
        ad1.show_menu();
        cout<<"请输入想要进行的功能的编号:"<<endl;
        cin>>cursor;
        switch(cursor)
        {
            case 1:ad1.cal_date_after();break;
            case 2:ad1.cal_date_before();break;
            case 3:ad1.print_daynum_between();break;
            case 4:ad1.calculate_date_pos();break;
            case 5:ad1.modify_birth_date();break;
            case 0:ad1.Exit();break;
            default:cout<<"输入错误!!!"<<endl;pause();break;
        }
    }
    
}