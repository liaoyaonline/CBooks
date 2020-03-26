#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include <set>
#include <string>
using namespace std;
//存储所有属性
vector<string> data_Attributes;
//存放每个属性对应的可能的值
map<string, vector<string>> data_AttValues;
vector<string> remain_Attributes;
//存放数据表
map<string, vector<string>> data_Table;
void generate_ChildNode();
void data_Input()
{
    int N;
    ifstream infile;
    infile.open("test.txt");
    string input_Line,temp_Attributes;
    cout << "请输入属性:" <<endl;
    getline(infile,input_Line);
    cout <<"属性:\n"<<input_Line<<endl;
    istringstream input_Attributes(input_Line);
    while(input_Attributes >> temp_Attributes)
        data_Attributes.push_back(temp_Attributes);
    for(auto it = data_Attributes.begin();it != data_Attributes.end();it++)
        cout << *it << " ";
    remain_Attributes = data_Attributes;
    remain_Attributes.pop_back();
    for(auto it = data_Attributes.begin();it != data_Attributes.end();it++)
        cout << *it << " ";
    cout << " 请输入样本数目"<<endl;
    infile >> N;
    //infile >> a;
    //cin.ignore(1024,'\n');
    cout << N << endl;
    getline(infile,input_Line);
    cout << "请输入样本:" <<endl;
    input_Line = "";
    temp_Attributes = "";
    //将所有样本数据存入Data_table
    for(int i = 0 ; i < N; i++)
    {
        getline(infile,input_Line);
        cout << input_Line << endl;
        istringstream input_Attributesc(input_Line);
        for(int i = 0; i < data_Attributes.size();i++)
        {
            input_Attributesc >> temp_Attributes;
            data_Table[data_Attributes[i]].push_back(temp_Attributes);
            cout << data_Attributes[i] << temp_Attributes;
        }
        cout << endl;
    }
    //map<string,vector<string>>::reverse_iterator iter;
    for(auto iter = data_Table.rbegin();iter != data_Table.rend();iter++)
    {
        cout << iter->first <<endl;
        for(auto it=(iter->second).begin();it != (iter->second).end();it++)
            cout <<*it << " ";
        cout << endl;
    }
    //将属性和属性里面的可能值存入data_AttValues
    for(auto iter = data_Table.rbegin();iter != data_Table.rend();iter++)
    {
        set<string> attValues;
        for(auto it=(iter->second).begin();it != (iter->second).end();it++)
            attValues.insert(*it);
        for(auto it=attValues.begin();it != attValues.end();it++)
            data_AttValues[iter->first].push_back(*it);
        cout << endl;
    }
    for(auto iter = data_AttValues.rbegin();iter != data_AttValues.rend();iter++)
    {
        cout << iter->first <<endl;
        for(auto it=(iter->second).begin();it != (iter->second).end();it++)
            cout <<*it << " ";
        cout << endl;
    }
}
int main()
{
    data_Input();
    generate_ChildNode();
    //输入数据
    //进行训练
    //进行预测
}
void generate_ChildNode()
{
    int attribute_Num = remain_Attributes.size();
    int N = (int)data_Table[data_Attributes[0]].size();
    map<string,int> category;
    for(int i = 0; i < N; i++)
    {
        vector<string> temp_Class;
        temp_Class = data_Table[data_Attributes[attribute_Num]];
        category[temp_Class[i]]++;
    }
    for(auto iter = category.rbegin();iter != category.rend();iter++)
    {
        cout << iter->first << ":"<< iter->second<<endl;
        cout << endl;
    }
}
