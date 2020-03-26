#include <iostream>  
enum DAY
{
      MON,TUE, WED, THU, FRI, SAT, SUN
} day;
int main()
{
    // 遍历枚举元素
    day = MON;
    printf("枚举元素：%d \n", day);
}
