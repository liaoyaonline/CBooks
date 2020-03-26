#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <set>
#include <string>
#include "Tree_Node.h"
using namespace std;
//存储所有属性
vector<string> data_Attributes;
//存放每个属性对应的可能的值
map<string, vector<string>> data_AttValues;
//存放数据表
map<string, vector<string>> data_Table;
void data_Input()
{
    int N;
    string input_Line,temp_Attributes;
    cout << "请输入属性:" <<endl;
    getline(cin,input_Line);
    cout <<"属性:\n"<<input_Line<<endl;
    istringstream input_Attributes(input_Line);
    while(input_Attributes >> temp_Attributes)
        data_Attributes.push_back(temp_Attributes);
    for(auto it = data_Attributes.begin();it != data_Attributes.end();it++)
        cout << *it << " ";
    cout << " 请输入样本数目"<<endl;
    cin >> N;
    cin.ignore();
    cout << N << endl;
    cout << "请输入样本:" <<endl;
    for(int i = 0 ; i < N; i++)
    {
        getline(cin,input_Line);
        istringstream input_Attributes(input_Line);
        for(int i = 0; i < data_Attributes.size();i++)
        {
            input_Attributes >> temp_Attributes;
            data_Table[data_Attributes[i]].push_back(temp_Attributes);
            cout << data_Attributes[i] << endl;
        }
    }
    //map<string,vector<string>>::reverse_iterator iter;
    for(auto iter = data_Table.rbegin();iter != data_Table.rend();iter++)
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
    //Tree_Node myTree(data_Table, data_Attributes, data_AttValues, remain_Attributes);

    //输入数据
    //进行训练
    //进行预测
}
