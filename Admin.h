#pragma once
#include"DateTime.h"
#include<fstream>
#define FileName "birth_date.txt"
class Admin
{
public:
    Admin();
    void show_menu();                             //打印菜单
    void calculate_date_after_day();              //计算查询日期多少天之后的日期
    void calculate_date_before_day();             //计算查询日期多少天之前的日期。
    void print_daynum_between();                  //计算两个日期相差的天数
    void calculate_date_pos();                    //计算时期所在的位置
    void Exit();                                  //退出窗口
    void print_Secondnum_between();                //计算两个时间相差多少秒
    void calculate_date_after_second();             //计算查询日期多少秒之后的日期
    void cal_date_before();
    void cal_date_after();
    void calculate_date_before_second();             //计算查询日期多少秒前的日期
    DateTime cin_date_ymd();               //从键盘端接收并返回一个datetime(只有年月日)类型。
    DateTime cin_date_all();                   //从键盘端接收并返回一个datetime(精确到second)类型。
    void modify_birth_date();                     //改变出生年月

private:
    DateTime *p;
};

Admin::Admin()
    {
        ifstream ifs;
        ifs.open(FileName,ios::in);
        if(!ifs.is_open())
        {
            cout<<"（暂时尚未定义出生年月！）"<<endl;
        }
        else
        {
            int year,month,day;
            ifs>>year>>month>>day;
            cout<<"出生年月为:"<<year<<"年"<<month<<"月"<<day<<"日"<<endl;
            ifs.close();
        }
    }


void Admin::modify_birth_date()                    //改变生日
{
    cout<<"请输入出生的年月日"<<endl;
    int year,month,day;
    cin>>year>>month>>day;
    ofstream ofs;
    ofs.open(FileName,ios::trunc|ios::out);
    ofs<<year<<" "<<month<<" "<<day<<endl;
    ofs.close();
    cout<<"修改成功！"<<endl;
    int cursor;
    cout<<"按任意键继续!"<<endl;
    cin>>cursor;
    system("clear");
}
void pause()          //停滞界面函数   mac里面没有system("pause")的语法，所以自己写了一个类似的
{
    int cursor;
    cout<<"按任意键继续!"<<endl;
    cin>>cursor;
    system("clear");
}

void Admin::show_menu()
{
    cout << "---------------------------欢迎使用时间计算器-------------------------------"<<endl;
    cout << "----------------------请根据如下提示输入相应编号选择功能-------------------"<<endl;
	cout << "--------------------------------------------------------------------------"<<endl;
    cout << "----------------------  1.计算此天多少天之后的日期   -------------------------"<<endl;
	cout << "----------------------  2.计算此天多少天之前的日期   -------------------------"<<endl;
	cout << "----------------------  3.打印两个日期中间相隔天数和秒数   ------------------"<<endl;
    cout << "----------------------  4.计算当前时间的位置        -------------------------"<<endl;
	cout << "----------------------  5.修改出生年月              -------------------------"<<endl;
    cout << "----------------------  0.退出                    -------------------------"<<endl;
    cout << "---------------------------------------------------------------------------"<<endl;
    DateTime now_time;
    cout<<"当前本地时间:"<<endl;
    now_time.Print_time();
}

void Admin::cal_date_before()
{
    cout<<"1.查询即将输入日期几秒钟前的日期\n2.查询即将输入日期几天前的日期"<<endl;
    cout<<"请选择:"<<endl;
    int cursor;
    cin>>cursor;
    switch(cursor)
    {
        case 1: calculate_date_before_second();break;
        case 2: calculate_date_before_day();break;
        default:cout<<"输入错误!"<<endl;return;
    }
}
void Admin::cal_date_after()
{
    cout<<"1.查询即将输入日期几秒钟后的日期\n2.查询即将输入日期几天后的日期"<<endl;
    cout<<"请选择:"<<endl;
    int cursor;
    cin>>cursor;
    switch(cursor)
    {
        case 1: calculate_date_after_second();break;
        case 2: calculate_date_after_day();break;
        default:cout<<"输入错误!"<<endl;return;
    }
}

DateTime Admin::cin_date_ymd()
{
    int year,month,day;
    cin>>year>>month>>day;
    while(year<=0||month>12||month<=0||day>31||day<0)
    {
        cout<<"输入错误!请重新输入年、月、日"<<endl;
        cin>>year>>month>>day;
    }
    DateTime cinday(year,month,day);
    return cinday;
}
DateTime Admin::cin_date_all()                   //从键盘端接收并返回一个datetime(精确到second)类型。
{
    int year,month,day,hour, minute, second;
    cin>>year>>month>>day>>hour>>minute>>second;
    while(year<=0||month>12||month<=0||day>31||day<0||hour>24||hour<0||minute>60||minute<0||second>60||second<0)
    {
        cout<<"输入错误!请重新依次输入年、月、日、小时、分钟、秒"<<endl;
        cin>>year>>month>>day>>hour>>minute>>second;
    }
    DateTime cinday(year,month,day,hour,minute,second);
    return cinday;
}
void Admin::calculate_date_after_second()             //计算查询日期多少秒之后的日期
{
    cout<<"请依次输入开始日期的年、月、日、小时、分钟、秒(中间以空格隔开):"<<endl;
    DateTime cin_day1=cin_date_all();
    cout<<"请输入秒数，系统将自动计算n秒后的日期"<<endl;
    long int second;
    cin>>second;
    DateTime target=cin_day1+second;
    target.Print_time();
    pause();
}

void Admin::calculate_date_before_second()             //计算查询日期多少秒前的日期
{
    cout<<"请依次输入开始日期的年、月、日、小时、分钟、秒(中间以空格隔开):"<<endl;
    DateTime cin_day1=cin_date_all();
    cout<<"请输入秒数，系统将自动计算n秒前的日期";
    long int second;
    cin>>second;
    DateTime target=cin_day1-second;
    target.Print_time();
    pause();
}
void Admin::calculate_date_after_day()
{
    cout<<"请依次输入开始或者询问日期的年月日(中间以空格隔开):"<<endl;
    DateTime cin_day=cin_date_ymd();
    int n;
    cout<<"请输入天数n（此天的n天之后）,系统将自动计算n天之后的日期:"<<endl;
    cin>>n;
    DateTime target_day;
    target_day=cin_day+n;
    cout<<"n天之后的日期为："<<endl;
    target_day.Print_date();
    pause();
}
void Admin::calculate_date_before_day()
{
    cout<<"请依次输入开始或者询问日期的年月日(中间以空格隔开):"<<endl;
    DateTime cin_day=cin_date_ymd();
    int n;
    cout<<"请输入天数n（此天的n天之前）,系统将自动计算n天之后的日期:"<<endl;
    cin>>n;
    DateTime target_day;
    target_day=cin_day-n;
    cout<<"n天之前的日期为："<<endl;
    target_day.Print_date();
    pause();
}

void Admin::print_daynum_between()                //计算两个时间相差多少秒
{
    cout<<"请依次输入第一个日期的年、月、日、小时、分钟、秒(中间以空格隔开):"<<endl;
    DateTime cin_day1=cin_date_all();
    cout<<"请依次输入第二个日期的年、月、日、小时、分钟、秒(中间以空格隔开):"<<endl;
    DateTime cin_day2=cin_date_all();
    long int second=cin_day1-cin_day2;
    int day=cin_day1.cal_date_daynum()-cin_day2.cal_date_daynum();
    if(day<0) day=-day;
    cout<<"两个日期相差了"<<day<<"天"<<",相差了"<<second<<"秒"<<endl;
    pause();
}



void Admin::calculate_date_pos()
{
    cout<<"请依次输入查找日期的年、月、日"<<endl;
    DateTime cin_day=cin_date_ymd();
    DateTime day_1(cin_day.get_year(),1,1);
    int day_year=cin_day.cal_date_daynum()-day_1.cal_date_daynum();
    cout<<"该日期是该年的第"<<day_year<<"天;";
    int day_week=day_year/7;
    cout<<"第"<<day_week<<"个星期!"<<endl;
    pause();
}
void Admin::Exit()
{
    int cursor;
    cout<<"确定退出？"<<endl;
    cout<<"1.确定退出"<<endl;
    cout<<"2.返回主界面"<<endl;
    cin>>cursor;
    system("clear");
    switch(cursor)
    {
        case 1:cout<<"退出成功！欢迎下次使用！";exit(0);break;
        case 2:return;break;
        default:cout<<"输入错误！自动返回主菜单"<<endl;return;break;
    }
    

}

