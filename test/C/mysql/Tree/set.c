#include<set>    
#include<iostream>    
using namespace std;
int main()
{
    set<int>s;
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        int x;
        cin>>x;
        s.insert (x);
    }
    set<int>::iterator it;
    for(it=s.begin ();it!=s.end ();it++)
    {
        printf("%d\n",*it); 
    }
    
    //s.end()没有值
     cout<<"s.begain()   "<<*s.begin ()<<endl;
    //lower_bound()--返回指向大于（或等于）某值的第一个元素的迭代器
    cout<<"lower_buond  3  "<<*s.lower_bound (3)<<endl;
    
    //upper_bound()--返回大于某个值元素的迭代器
    cout<<"upper_bound  3  "<<*s.upper_bound (3)<<endl;

    //find()--返回一个指向被查找到元素的迭代器
    cout<<"find()  3   "<<*s.find (3)<<endl;

    cout<<"s.size()  "<<s.size ()<<endl;
    return 0;
}
