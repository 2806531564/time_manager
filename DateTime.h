#pragma once
#include<iostream>
#include<ctime>
using namespace std;
class DateTime
{
    friend DateTime operator + ( DateTime d1,DateTime d2);
    friend DateTime operator + ( DateTime d1,int day_num);
    friend DateTime operator - ( DateTime d1,int day_num);
    friend long int operator - ( DateTime d1,DateTime d2);
    friend DateTime operator - ( DateTime d1,long int second);
    friend DateTime operator + ( DateTime d1,long int second);
private:
    int Year;           
    int Month;          
    int Day;          
    int Hour;       
    int Minute;
    int Second;
    int Wday;           //范围是0-6，当Wday的值为0的时候代表的是周日。
    string s_wday;
public:
    bool leapYear(int y);            //判断是否是闰年
    DateTime();
    DateTime(const DateTime &a);
    DateTime(int year,int month,int day);
    DateTime(int year,int month,int day,int hour,int minute,int second);
    void Print_time();                  //打印精确到秒
    void calculate_wday();                
    void Print_date();                  //打印精确到日即可
    DateTime operator = (DateTime d1);
    int cal_date_daynum();       //计算今天这个日期的总的天数。
    int get_year();
    int get_month();
    int get_day();
    int get_hour();
    int get_minute();
    int get_second();
};
DateTime operator - ( DateTime d1,long int second)
{
    d1=d1+(-second);
    return d1;
}
DateTime operator + ( DateTime d1,long int second)
{
    int day_last=second/86400;
    int hour_last=(second%86400)/3600;
    int minute_last=((second%86400)%3600)/60;
    int second_last=((second%86400)%3600)%60;
    if(d1.Second+second_last>=60)
    {
        d1.Second=d1.Second+second_last-60;
        minute_last++;
    }
    else if(d1.Second+second_last<0)
    {
        d1.Second=60+d1.Second+second_last;
        minute_last--;
    }
    else
    {
        d1.Second+=second_last;
    }
    if(d1.Minute+minute_last>=60)
    {
        d1.Minute=d1.Minute+minute_last-60;
        hour_last++;
    }
    else if(d1.Minute+minute_last<0)
    {
        d1.Minute=60+d1.Minute+minute_last;
        hour_last--;
    }
    else
    {
        d1.Minute+=minute_last;
    }
    if(d1.Hour+hour_last>=24)
    {
        d1.Hour=d1.Hour+hour_last-24;
        day_last++;
    }
    else if(d1.Hour+hour_last<0)
    {
        d1.Hour=24+d1.Hour+hour_last;
        day_last++;
    }
    else
    {
        d1.Hour+=hour_last;
    }
    d1=d1+day_last;
    return d1;

}
void DateTime::Print_date()
{
    calculate_wday();
    cout<<Year<<"年"<<Month<<"月"<<Day<<"日"<<s_wday<<endl;
}   
bool DateTime::leapYear(int y)            //判断是否是闰年
{
    if(y % 4 == 0 && y % 100 != 0 || y % 400 == 0)
    {
        return 1;
    }
    return 0;
}
DateTime operator - ( DateTime d1,int day_num)
{
    DateTime d2=d1+(-day_num);
    return d2;
}

int DateTime::cal_date_daynum()       //计算今天这个日期的总的天数。
{
    int sum_day=0;
    int days_run=366;
    int days_ping=365;
    if(Year!=1){
        for(int i=1;i<Year;i++){
            if(leapYear(i)){
                sum_day+=days_run;
            }
            else{
                sum_day+=days_ping;
            }
        }
    }
    if(Month==1){
        sum_day+=Day;
    }
    else{
        switch(Month-1){
            case 11:
                sum_day+=30;
            case 10:
                sum_day+=31;
            case 9:
                sum_day+=30;
            case 8:
                sum_day+=31;
            case 7:
                sum_day+=31;
            case 6:
                sum_day+=30;
            case 5:
                sum_day+=31;
            case 4:
                sum_day+=30;
            case 3:
                sum_day+=31;
            case 2:
                if(leapYear(Year))sum_day+=29;
                else sum_day+=28;
            case 1:
                sum_day+=31;
                break;
        }
        sum_day+=Day;
    }
    return sum_day;
}

long int operator - ( DateTime d1,DateTime d2)
{
    int day_dif=d1.cal_date_daynum()-d2.cal_date_daynum();
    if(day_dif<0) return d2-d1;
    long int second=day_dif*24*60*60;
    long int hour_last=d1.Hour-d2.Hour;
    long int minute_last=d1.Minute-d2.Minute;
    long int second_last=d1.Second-d2.Second;
    second+=hour_last*60*60+minute_last*60+second_last;
    return second;

}

DateTime operator + ( DateTime d1,int day_num)
{
  
    int num1=d1.cal_date_daynum();
    DateTime d2(1,1,1);
    int num2=d2.cal_date_daynum();
    day_num=num1-num2+day_num;
    while(day_num>=365)
    {
        if(!d2.leapYear(d2.Year))
        {
            day_num-=365;
            d2.Year++;
        }
        else
        {
            if(day_num==365)
            {
                break;
            }
            else
            {
                day_num-=366;
                d2.Year++;
            }
        }
    }
    while(day_num!=0)
    {   
        switch(d2.Month)
        {
            case 1: if(day_num>=31)
            {
                day_num-=31;
                d2.Month++;
            } 
            else
            {
                d2.Day+=day_num;
                break;
            }
            case 2: if(!d2.leapYear(d2.Year))
            {
                if(day_num>=28)
                {
                    day_num-=28;
                    d2.Month++;
                }
                else
                {
                    d2.Day+=day_num;
                    break;
                }
            }
            else
            {
                if(day_num>=29)
                {
                    day_num-=29;
                    d2.Month++;
                }
                else
                {
                    d2.Day+=day_num;
                    break;
                }
            }
            case 3: if(day_num>=31)
            {
                day_num-=31;
                d2.Month++;
            } 
            else
            {
                d2.Day+=day_num;
                break;
            }
            case 4: if(day_num>=30)
            {
                day_num-=30;
                d2.Month++;
            } 
            else
            {
                d2.Day+=day_num;
                break;
            }
            case 5: if(day_num>=31)
            {
                day_num-=31;
                d2.Month++;
            } 
            else
            {
                d2.Day+=day_num;
                break;
            }
            case 6: if(day_num>=30)
            {
                day_num-=30;
                d2.Month++;
            } 
            else
            {
                d2.Day+=day_num;
                break;
            }
            case 7: if(day_num>=31)
            {
                day_num-=31;
                d2.Month++;
            } 
            else
            {
                d2.Day+=day_num;
                break;
            }
            case 8: if(day_num>=31)
            {
                day_num-=31;
                d2.Month++;
            } 
            else
            {
                d2.Day+=day_num;
                break;
            }
            case 9: if(day_num>=30)
            {
                day_num-=30;
                d2.Month++;
            } 
            else
            {
                d2.Day+=day_num;
                break;
            }
            case 10: if(day_num>=31)
            {
                day_num-=31;
                d2.Month++;
            } 
            else
            {
                d2.Day+=day_num;
                break;
            }
            case 11: if(day_num>=30)
            {
                day_num-=30;
                d2.Month++;
            } 
            else
            {
                d2.Day+=day_num;
                break;
            }
            case 12: if(day_num>=31)
            {
                day_num-=31;
                d2.Month++;
            } 
            else
            {
                d2.Day+=day_num;
                break;
            }
        }
        d2.Hour=d1.Hour;
        d2.Minute=d1.Minute;
        d2.Second=d1.Second;
        return d2;
    }
}

DateTime DateTime:: operator = (DateTime d1)
{
    this->Year=d1.Year;
    this->Month=d1.Month;
    this->Day=d1.Day;
    this->Hour=d1.Hour;
    this->Minute=d1.Minute;
    this->Second=d1.Second;
    return *this;
}

void DateTime::calculate_wday()
{
    //使用运用标准库提供的ctime头文件中的struct tm结构去计算wday
    
    time_t mytime = time(0);
    tm* mytm = localtime(&mytime);

    mytm->tm_mday=Day;
    mytm->tm_mon=Month-1;
    mytm->tm_year=Year-1900;
    
    time_t newtime = mktime(mytm);
    Wday= mytm->tm_wday;         //ctime里面的tm中的tm_wday的范围之0-6，0的时候自然是周日。
    switch(Wday)
    {
        case 0:s_wday="周日";break;
        case 1:s_wday="周一";break;
        case 2:s_wday="周二";break;
        case 3:s_wday="周三";break;
        case 4:s_wday="周四";break;
        case 5:s_wday="周五";break;
        case 6:s_wday="周六";break;
    }

}
DateTime::DateTime()
{
    //默认构造为本地时间;
    time_t now=time(0);
    tm *ltm=localtime(&now);
    Year=1900+ltm->tm_year;
    Month=1+ltm->tm_mon;
    Day=ltm->tm_mday;
    Hour=ltm->tm_hour;
    Minute=ltm->tm_min;
    Second=ltm->tm_sec;
    calculate_wday();

    
}
DateTime::DateTime(const DateTime &a)
{
    Year=a.Year;
    Month=a.Month;
    Day=a.Day;
    Hour=a.Hour;
    Minute=a.Minute;
    Second=a.Second;
    Wday=a.Wday;
}

DateTime::DateTime(int year,int month,int day)
{
    Year=year;
    Month=month;
    Day=day;
    calculate_wday();
}
void DateTime::Print_time()
{
    calculate_wday();
    cout<<Year<<"年"<<Month<<"月"<<Day<<"日"<<Hour<<"点"<<Minute<<"分"<<Second<<"秒"<<s_wday<<endl;
}
int DateTime::get_year()
{
    return Year;
}
int DateTime::get_month()
{
    return Month;
}
int DateTime::get_day()
{
    return Day;
}
int DateTime::get_hour()
{
    return Hour;
}
int DateTime::get_minute()
{
    return Minute;
}
int DateTime::get_second()
{
    return Second;
}
DateTime::DateTime(int year,int month,int day,int hour,int minute,int second)
{
    Year=year;
    Month=month;
    Day=day;
    Hour=hour;
    Minute=minute;
    Second=second;
}