#include "Tree_Node.h"
#include <math.h>
#include <sstream>
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>

Tree_Node::Tree_Node(map<string, vector<string>> temp_Table,vector<string> temp_Attribute, map<string, vector<string>> data_AttValues, vector<string> temp_remain)
{
	//全部属性,包括类别
	data_Attribute = temp_Attribute;
	//属性个数，不包括类别
	attribute_Num = (int)temp_Attribute.size() - 1;
	//各属性对应的属性值
	this->data_AttValues = data_AttValues;
	//属性表
	MyDateTable = temp_Table;
	//剩余属性集
	remain_Attributes = temp_remain;
}

void Tree_Node::generate_ChildNode()
{
	//样本个数
	int N = (int)MyDateTable[data_Attribute[0]].size();
    cout << N << endl;
	
	//将数据集中类别种类和数量放入map里面，只需判断最后一列即可
	map<string,int> category;
	for (int i = 0; i < N; i++)
	{	
		vector<string> temp_Class;
		temp_Class = MyDateTable[data_Attribute[attribute_Num]];
		category[temp_Class[i]]++;
	}
    for(auto iter = category.rbegin();iter != category.rend();iter++)
    {
        cout << iter->first << ":"<< iter->second<<endl;
        cout << endl;
    }

	//第一种情况
	//只有一个类别，标记为叶节点
	if (1 == category.size())
	{
		map<string, int>::iterator it = category.begin();
		node_Attribute = it->first;
		return;
	}
	//第二种情况
	//先判断所有属性是否取相同值
	bool isAllSame = false;
	for (int i = 0; i < remain_Attributes.size(); i++)
	{
		isAllSame = true;
		vector<string> temp;
		temp = MyDateTable[remain_Attributes[i]];
		for (int j = 1; j < temp.size(); j++)
		{
			//只要有一个不同，即可退出
			if (temp[0] != temp[j])
			{
				isAllSame = false;
				break;
			}
		}
		if (isAllSame == false)
		{
			break;
		}
	}
	//若属性集为空或者样本中的全部属性取值相同
	if (remain_Attributes.empty()||isAllSame)
	{
		//找出数量最多的类别及其出现的个数，并将该节点标记为该类
		map<string, int>::iterator it = category.begin();
		node_Attribute = it->first;
		int max = it->second;
		it++;
		for (; it != category.end(); it++)
		{
			int num = it->second;
			if (num > max)
			{
				node_Attribute = it->first;
				max = num;
			}
		}
		return;
	}
	//第三种情况
	//从remian_attributes中划分最优属性
	string best_Attribute = findBestAttribute();
	//将本节点设置为最优属性
	node_Attribute = best_Attribute;
	//对最优属性的每个属性值
	int checkcon = 0;
    if(node_Attribute == "密度" || node_Attribute == "含糖率")
        checkcon = 1;
    if(checkcon == 1)
    {
        double temp_t = findBestT(node_Attribute);//最佳t从findAtt里面取得
        double temp_con;
        map<string, vector<string>>sub_DataTablePlus;
        map<string, vector<string>>sub_DataTableLess;
        for(int l = 0; l < MyDateTable[best_Attribute].size();l++)
        {
            stringstream ss;
            ss <<  MyDateTable[best_Attribute][l];
            ss >> temp_con;
            cout << "temp_con:" << temp_con << endl;
            cout << "temp_t:" << temp_t << endl;
            if(temp_con <= temp_t)
            {
                for (int m = 0; m < data_Attribute.size(); m++)
                {
                    sub_DataTableLess[data_Attribute[m]].push_back(MyDateTable[data_Attribute[m]][l]);
                }
            }
            else
            {
                for (int m = 0; m < data_Attribute.size(); m++)
                {
                    sub_DataTablePlus[data_Attribute[m]].push_back(MyDateTable[data_Attribute[m]][l]);
                }
            }
        }
        cout << "中间点。。。分割线" << endl;
        for(auto iter = sub_DataTableLess.rbegin();iter != sub_DataTableLess.rend();iter++)
        {
            cout <<"first" <<iter->first <<endl;
            for(auto it=(iter->second).begin();it != (iter->second).end();it++)
                cout <<*it << " ";
            cout << endl;
        }
        cout << "第二道分割线。。。。。。。"<< endl;
        for(auto iter = sub_DataTablePlus.rbegin();iter != sub_DataTablePlus.rend();iter++)
        {
            cout << iter->first <<endl;
            for(auto it=(iter->second).begin();it != (iter->second).end();it++)
                cout <<*it << " ";
            cout << endl;
        }
        if (sub_DataTablePlus.empty())
        {
            string plus = ">";
            string t_string;
            stringstream ss;
            ss << temp_t;
            ss >> t_string;
            string best_AttValues = plus + t_string;
            //生成子节
            Tree_Node * p = new Tree_Node(sub_DataTablePlus, data_Attribute, data_AttValues, remain_Attributes);
	    	//找出样本最多的类，作为子节点的属性
		    map<string, int>::iterator it = category.begin();
            string childNode_Attribute = it->first;
            int max_Num = it->second;
    		it++;
            for (; it != category.end(); it++)
            {
		    	if (it->second > max_Num)
                {
    				max_Num = it->second;
					childNode_Attribute = it->first;
	    		}
            }
			//设置子叶节点属性
            p->set_NodeAttribute(childNode_Attribute);
    		cout<< "中间sub_DataTablePlus为empty处理方案"<< endl;
            //将子节点存入childNode，预测样本的时候会用到
    		childNode[best_AttValues] = p;
        }
    	else//若不为空，则从剩余属性值剔除该属性，调用generate_ChildNode继续往下细分
    	{
            string plus = ">";
            string t_string;
            stringstream ss;
            ss << temp_t;
            ss >> t_string;
            string best_AttValues = plus + t_string;
			vector<string> child_RemainAtt;
            child_RemainAtt = remain_Attributes;
    		//找出child_RemainAtt中的与该最佳属性相等的属性
    		vector<string>::iterator it = child_RemainAtt.begin();
			for (; it != child_RemainAtt.end(); it++)
            {
    			if (*it == best_Attribute)
    			{
					break;
                }
 			}
            //删除
    		child_RemainAtt.erase(it);
            cout << "若sub_DataTablePlus不为empty处理方案"<< endl;

    		//生成子节点
    		Tree_Node * pt = new Tree_Node(sub_DataTablePlus, data_Attribute, data_AttValues, child_RemainAtt);
			//将子节点存入childNode
            childNode[best_AttValues] = pt;
			//子节点再调用generate_ChildNode函数
            //
            pt->generate_ChildNode();
    	}
        if (sub_DataTableLess.empty())
        {
            string plus = "<";
            string t_string;
            stringstream ss;
            ss << temp_t;
            ss >> t_string;
            string best_AttValues = plus + t_string;
            //生成子节
            Tree_Node * p = new Tree_Node(sub_DataTableLess, data_Attribute, data_AttValues, remain_Attributes);
	    	//找出样本最多的类，作为子节点的属性
		    map<string, int>::iterator it = category.begin();
            string childNode_Attribute = it->first;
            int max_Num = it->second;
    		it++;
            for (; it != category.end(); it++)
            {
		    	if (it->second > max_Num)
                {
    				max_Num = it->second;
					childNode_Attribute = it->first;
	    		}
            }
            cout<<"sub_DataTableLess为empty处理策略"<< endl;
			//设置子叶节点属性
            p->set_NodeAttribute(childNode_Attribute);
    		//将子节点存入childNode，预测样本的时候会用到
    		childNode[best_AttValues] = p;
        }
    	else//若不为空，则从剩余属性值剔除该属性，调用generate_ChildNode继续往下细分
    	{
            string plus = "<";
            string t_string;
            stringstream ss;
            ss << temp_t;
            ss >> t_string;
            string best_AttValues = plus + t_string;
			vector<string> child_RemainAtt;
            child_RemainAtt = remain_Attributes;
    		//找出child_RemainAtt中的与该最佳属性相等的属性
    		vector<string>::iterator it = child_RemainAtt.begin();
			for (; it != child_RemainAtt.end(); it++)
            {
    			if (*it == best_Attribute)
    			{
					break;
                }
 			}
            //删除
    		child_RemainAtt.erase(it);
            cout << "若sub_DataTableLess不为empty处理方案"<< endl;
    		//生成子节点
    		Tree_Node * pt = new Tree_Node(sub_DataTableLess, data_Attribute, data_AttValues, child_RemainAtt);
			//将子节点存入childNode
            childNode[best_AttValues] = pt;
			//子节点再调用generate_ChildNode函数
            //
            pt->generate_ChildNode();
    	}
    }
    else
    {
        for (int i = 0; i < data_AttValues[best_Attribute].size(); i++)
	    {
		    string best_AttValues = data_AttValues[best_Attribute][i];
		    //计算属性对应的数据集D
		    //定义map用来存放该属性值下的数据子集
		    map<string, vector<string>> sub_DataTable;
		    for (int j = 0; j < MyDateTable[best_Attribute].size(); j++)
		    {
			    //寻找最优属性在数据集中属性值相同的数据样本
			    if (best_AttValues == MyDateTable[best_Attribute][j])
			    {
				    //找到对应的数据集，存入子集中sub_DataTable（该样本的全部属性都要存入）
				    for (int k = 0; k < data_Attribute.size(); k++)
				    {
					    sub_DataTable[data_Attribute[k]].push_back(MyDateTable[data_Attribute[k]][j]);
				    }
			    }
	    	}
		    //若子集为空，将分支节点（子节点）标记为叶节点，类别为MyDateTable样本最多的类
		    if (sub_DataTable.empty())
		    {
    			//生成子节点
	    		Tree_Node * p = new Tree_Node(sub_DataTable, data_Attribute, data_AttValues, remain_Attributes);
		    	//找出样本最多的类，作为子节点的属性
			    map<string, int>::iterator it = category.begin();
    			string childNode_Attribute = it->first;
    			int max_Num = it->second;
	    		it++;
		    	for (; it != category.end(); it++)
			    {
			    	if (it->second > max_Num)
				    {
    					max_Num = it->second;
	    				childNode_Attribute = it->first;
		    		}
	    		}
    			//设置子叶节点属性
		    	p->set_NodeAttribute(childNode_Attribute);
    			//将子节点存入childNode，预测样本的时候会用到
    			childNode[best_AttValues] = p;
	    	}
    		else//若不为空，则从剩余属性值剔除该属性，调用generate_ChildNode继续往下细分
    		{
    			vector<string> child_RemainAtt;
    			child_RemainAtt = remain_Attributes;
    			//找出child_RemainAtt中的与该最佳属性相等的属性
    			vector<string>::iterator it = child_RemainAtt.begin();
    			for (; it != child_RemainAtt.end(); it++)
    			{
    				if (*it == best_Attribute)
    				{
    					break;
    				}
    			}
    			//删除
    			child_RemainAtt.erase(it);

    			//生成子节点
    			Tree_Node * pt = new Tree_Node(sub_DataTable, data_Attribute, data_AttValues, child_RemainAtt);
    			//将子节点存入childNode
    			childNode[best_AttValues] = pt;
    			//子节点再调用generate_ChildNode函数
    			pt->generate_ChildNode();
    		}
    	}
    }
}

//寻找最优划分
string Tree_Node::findBestAttribute()
{
	//样本个数
	int N = (int)MyDateTable[data_Attribute[0]].size();
	//定义用于存放最优属性
	string best_Attribute;
	//信息增益
	double gain = 0;
    map<string,double> Attribute_Gain;
    map<string,double> Attribute_Gratio;
	//对每个剩余属性
	for (int i = 0; i < remain_Attributes.size(); i++)
	{
		//定义信息增益，选取增益最大的属性来划分即为最优划分
		double temp_Gain = calc_Entropy(MyDateTable);//根据公式先将本节点的信息熵初始化给增益
		cout << "first Ent(D):" << temp_Gain<< endl;
        int checkcon = 0;
        //对该属性的数据集进行分类（获取各属性值的数据子集）
		string temp_Att = remain_Attributes[i];//假设选取的属性
        //string temp_Att = "密度";
        if(temp_Att == "密度" || temp_Att == "含糖率")
            checkcon = 1;
        vector<string> remain_AttValues;//属性可能的取值
		if(checkcon == 1)//执行连续值Gain计算
        {
            double temp_t = 0.0;
            string temp_sAttValue;
            double temp_AttValue;
            double ttemp_Gain;
            double max_Gain = 0;
            vector<double> remain_AttValues;
            vector<double> remain_tempt;
            map<double,string> table_con;
            //将所有类别的值压入remain_AttValues;
            for(int j= 0;j< data_AttValues[temp_Att].size();j++)
            {
                stringstream ss;
                cout << " ko "<< data_AttValues[temp_Att][j] << endl;
                temp_sAttValue = data_AttValues[temp_Att][j];
                cout << " kotemp_snum "<<temp_AttValue << endl;
                ss << temp_sAttValue;
                ss >> temp_AttValue;
                remain_AttValues.push_back(temp_AttValue);
            }
            for(int j = 0; j < remain_AttValues.size(); j++)
                cout << "  "<< remain_AttValues[j] << endl;
            sort(remain_AttValues.begin(),remain_AttValues.end());
            cout << "\n\n" << endl;
            for(int j = 0; j < remain_AttValues.size(); j++)
                cout << "  "<< remain_AttValues[j] << endl;
            for(int i = 0; i < remain_AttValues.size() - 1;i++)
            {
                temp_t = (remain_AttValues[i] + remain_AttValues[i+1]) / 2;
                cout << " t: "<< temp_t << endl;
                remain_tempt.push_back(temp_t);
            }
            for(int j = 0; j < remain_tempt.size(); j++)
                cout << " tempt "<< remain_tempt[j] << endl;
            //计算出最大的Gain以及对应的t
            for(int j = 0; j < remain_tempt.size(); j++)
            {
                temp_t = remain_tempt[j];
                temp_Gain = calc_Entropy(MyDateTable);
                //用来存放对应的数据
                double temp_con;
                int sample_Numplus = 0;//大于t样本数目
                int sample_Numless = 0;//小于t样本数目
                map<string, vector<string>>sub_DataTablePlus;
                map<string, vector<string>>sub_DataTableLess;
                //将比t小的存入less将比t大的值存入plus
                for(int l = 0; l < MyDateTable[temp_Att].size();l++)
                {
                    stringstream ss;
                    ss <<  MyDateTable[temp_Att][l];
                    ss >> temp_con;
                    cout << "temp_con:" << temp_con << endl;
                    if(temp_con <= temp_t)
                    {
                        sample_Numless++;
                        for (int m = 0; m < data_Attribute.size(); m++)
                        {
                            sub_DataTableLess[data_Attribute[m]].push_back(MyDateTable[data_Attribute[m]][l]);
                        }
                    }
                    else
                    {
                        sample_Numplus++;
                        for (int m = 0; m < data_Attribute.size(); m++)
                        {
                            sub_DataTablePlus[data_Attribute[m]].push_back(MyDateTable[data_Attribute[m]][l]);
                        }
                    }
                }
                cout <<"sample_NUmplus :"<< sample_Numplus<< endl;
                cout <<"sample_NUmless :"<< sample_Numless<< endl;
                for(auto iter = sub_DataTableLess.rbegin();iter != sub_DataTableLess.rend();iter++)
                {
                    cout <<"first" <<iter->first <<endl;
                        for(auto it=(iter->second).begin();it != (iter->second).end();it++)
                            cout <<*it << " ";
                    cout << endl;
                }
                for(auto iter = sub_DataTablePlus.rbegin();iter != sub_DataTablePlus.rend();iter++)
                {
                    cout << iter->first <<endl;
                        for(auto it=(iter->second).begin();it != (iter->second).end();it++)
                            cout <<*it << " ";
                    cout << endl;
                }
                ttemp_Gain = temp_Gain - ((double)sample_Numplus / N * calc_Entropy(sub_DataTablePlus) + (double)sample_Numless / N * calc_Entropy(sub_DataTableLess));
                cout << "t:" << temp_t <<"Ent : "<< temp_Gain;
                cout << endl;
                if(ttemp_Gain >= max_Gain)
                {
                    max_Gain = ttemp_Gain;
                }
                ttemp_Gain = 0;
            }
            temp_Gain = max_Gain;
        }

        //执行非连续值Gain计算
        else
        {
            for (int j = 0; j < data_AttValues[temp_Att].size(); j++)
		    {
			    remain_AttValues.push_back(data_AttValues[temp_Att][j]);
		    }
		
		    //对每个属性值求信息熵
		    for (int k = 0; k < remain_AttValues.size(); k++)
		    {
			    //属性值
			    string temp_AttValues = remain_AttValues[k];
			    int sample_Num = 0;//该属性值对应样本数量
			    //定义map用来存放该属性值下的数据子集
			    map<string, vector<string>>sub_DataTable;
			    for (int l = 0; l < MyDateTable[temp_Att].size(); l++)
			    {
				    if (temp_AttValues == MyDateTable[temp_Att][l])
				    {
					    sample_Num++;
					    //将符合条件的训练集存入sub_DataTable
					    for (int m = 0; m < data_Attribute.size(); m++)
					    {
						    sub_DataTable[data_Attribute[m]].push_back(MyDateTable[data_Attribute[m]][l]);
					    }
				    }
			    }
			    //累加每个属值的信息熵
                temp_Gain -= (double)sample_Num / N * calc_Entropy(sub_DataTable);
                cout << "sample_Num" << sample_Num << endl;
		    }
        }
		//比较寻找最优划分属性
		cout << "temp_Gain:" << temp_Gain << "temp_Att:"<< temp_Att<< endl;
        if (temp_Gain > gain)
		{
			gain = temp_Gain;
			best_Attribute = temp_Att;
		}
	}
	return best_Attribute;
}

//计算信息熵
double Tree_Node::calc_Entropy(map<string, vector<string>> temp_Table)
{
	map<string, vector<string>> table = temp_Table;
	//数据集中样本的数量
	int sample_Num = (int)temp_Table[data_Attribute[0]].size();
	//计算数据集中的类别数量
	map<string, int> class_Map;
	for (int i = 0; i < sample_Num; i++)
	{
		//data_Attribute[attribute_Num]对应的就是数据集的类别
		string class_String = table[data_Attribute[attribute_Num]][i];
		class_Map[class_String]++;
	}

    for(auto iter = class_Map.rbegin();iter != class_Map.rend();iter++)
        cout <<"string :" << iter->first << "int :" << iter->second << endl;
	map<string, int>::iterator it = class_Map.begin();
	//存放类别及其对应的数量
	//vector<string> m_Class;
	vector<int> n_Class;
	
	for (; it != class_Map.end(); it++)
	{
		//m_Class.push_back(it->first);
		n_Class.push_back(it->second);
	}
	//计算信息熵
	double Ent = 0;
	for (int k = 0; k < class_Map.size(); k++)
	{
		//比例
		double p = (double) n_Class[k] / sample_Num;
		if (p == 0)
		{
			//规定了p=0时，plogp=0
			continue;
		}
		//c++中只有log和ln，因此需要应用换底公式
		Ent -= p * (log(p) / log(2));//信息熵
	}
	cout << "Ent" << Ent<<endl;
	return Ent;
}

void Tree_Node::set_NodeAttribute(string attribute)
{
	//设置节点的属性
	this->node_Attribute = attribute;
}

//输入为待预测样本的所有属性集合
string Tree_Node::findClass(vector<string> attributes)
{
	//若存在子节点
	if (childNode.size() != 0)
	{
		//找出输入的样例中与本节点属性对应的属性值，以便寻找下个节点，直到找到叶节点
		string attribute_Value;
        cout << "node_Attribute:"<< node_Attribute << endl;
        cout << data_AttValues[node_Attribute].size()<< endl;
        //for(auto it = node_AttValues.begin();it != node_AttValues.end();it++)
          //  cout <<"node_AttValues:"<< *it << " "<<endl;
        for (int i = 0; i < data_AttValues[node_Attribute].size(); i++)
            cout <<"data_AttValues"<< data_AttValues[node_Attribute][i];
		for (int i = 0; i < data_AttValues[node_Attribute].size(); i++)
		{
			for (int j = 0; j < attributes.size(); j++)
			{
				//data_AttValues[node_Attribute]为属性node_Attribute对应的所有可能的取值集合
				if (attributes[j] == data_AttValues[node_Attribute][i])
				{
					//找到了样例对应的属性值
					attribute_Value = attributes[j];
                    cout << "测试样本的属性:"<< attribute_Value << endl;
					break;
				}
			}
			//找到后就没必要继续循环了
			if (!attribute_Value.empty())
			{
				break;
			}
		}
		//找出该属性值对应的子节点的地址，以便进行访问
		Tree_Node *p = childNode[attribute_Value];
		return p->findClass(attributes);//递归寻找，直到找到叶节点为止
	}
	else//不存在子节点说明已经找到分类，类别为本节点的node_Attribute
	{
		return node_Attribute;
	}
}
double Tree_Node::findBestT(string Att)
{
    double max_t = 0;
	//样本个数
	int N = (int)MyDateTable[data_Attribute[0]].size();
	//定义用于存放最优属性
	string best_Attribute;
	//信息增益
    map<string,double> Attribute_Gain;
    map<string,double> Attribute_Gratio;
	//对每个剩余属性
	double temp_Gain = calc_Entropy(MyDateTable);//根据公式先将本节点的信息熵初始化给增益
	cout << "first Ent(D):" << temp_Gain<< endl;
    int checkcon = 0;
    //对该属性的数据集进行分类（获取各属性值的数据子集）
	string temp_Att = Att;//假设选取的属性
    //string temp_Att = "密度";
    if(temp_Att == "密度" || temp_Att == "含糖率")
        checkcon = 1;
    vector<string> remain_AttValues;//属性可能的取值
	if(checkcon == 1)//执行连续值Gain计算
    {
        double temp_t = 0.0;
        string temp_sAttValue;
        double temp_AttValue;
        double ttemp_Gain;
        double max_Gain = 0;
        vector<double> remain_AttValues;
        vector<double> remain_tempt;
        map<double,string> table_con;
        //将所有类别的值压入remain_AttValues;
        for(int j= 0;j< data_AttValues[temp_Att].size();j++)
        {
            stringstream ss;
            cout << " ko "<< data_AttValues[temp_Att][j] << endl;
            temp_sAttValue = data_AttValues[temp_Att][j];
            cout << " kotemp_snum "<<temp_AttValue << endl;
            ss << temp_sAttValue;
            ss >> temp_AttValue;
            cout << "temp_num:" << temp_AttValue << endl;
            //ss << data_AttValues[temp_Att][j];
            //ss >> temp_num;
            //remain_AttValues.push_back(con)
            //remain_AttValues.push_back(data_AttValues[temp_Att][j]);
            remain_AttValues.push_back(temp_AttValue);
        }
        for(int j = 0; j < remain_AttValues.size(); j++)
            cout << "  "<< remain_AttValues[j] << endl;
        sort(remain_AttValues.begin(),remain_AttValues.end());
        cout << "\n\n" << endl;
        for(int j = 0; j < remain_AttValues.size(); j++)
            cout << "  "<< remain_AttValues[j] << endl;
        for(int i = 0; i < remain_AttValues.size() - 1;i++)
        {
            temp_t = (remain_AttValues[i] + remain_AttValues[i+1]) / 2;
            cout << " t: "<< temp_t << endl;
            remain_tempt.push_back(temp_t);
        }
        for(int j = 0; j < remain_tempt.size(); j++)
            cout << " tempt "<< remain_tempt[j] << endl;
        //计算出最大的Gain以及对应的t
        for(int j = 0; j < remain_tempt.size(); j++)
        {
            temp_t = remain_tempt[j];
            temp_Gain = calc_Entropy(MyDateTable);
            //用来存放对应的数据
            double temp_con;
            int sample_Numplus = 0;//大于t样本数目
            int sample_Numless = 0;//小于t样本数目
            map<string, vector<string>>sub_DataTablePlus;
            map<string, vector<string>>sub_DataTableLess;
            //将比t小的存入less将比t大的值存入plus
            for(int l = 0; l < MyDateTable[temp_Att].size();l++)
            {
                stringstream ss;
                ss <<  MyDateTable[temp_Att][l];
                ss >> temp_con;
                cout << "temp_con:" << temp_con << endl;
                if(temp_con <= temp_t)
                {
                    sample_Numless++;
                    for (int m = 0; m < data_Attribute.size(); m++)
                    {
                        sub_DataTableLess[data_Attribute[m]].push_back(MyDateTable[data_Attribute[m]][l]);
                    }
                }
                else
                {
                    sample_Numplus++;
                    for (int m = 0; m < data_Attribute.size(); m++)
                    {
                        sub_DataTablePlus[data_Attribute[m]].push_back(MyDateTable[data_Attribute[m]][l]);
                    }
                }
            }
            cout <<"sample_NUmplus :"<< sample_Numplus<< endl;
            cout <<"sample_NUmless :"<< sample_Numless<< endl;
            for(auto iter = sub_DataTableLess.rbegin();iter != sub_DataTableLess.rend();iter++)
            {
                cout <<"first" <<iter->first <<endl;
                for(auto it=(iter->second).begin();it != (iter->second).end();it++)
                    cout <<*it << " ";
                cout << endl;
            }
            for(auto iter = sub_DataTablePlus.rbegin();iter != sub_DataTablePlus.rend();iter++)
            {
                cout << iter->first <<endl;
                for(auto it=(iter->second).begin();it != (iter->second).end();it++)
                    cout <<*it << " ";
                cout << endl;
            }
            ttemp_Gain = temp_Gain - ((double)sample_Numplus / N * calc_Entropy(sub_DataTablePlus) + (double)sample_Numless / N * calc_Entropy(sub_DataTableLess));
            cout << "t:" << temp_t <<"Ent : "<< ttemp_Gain;
            cout << endl;
            if(ttemp_Gain >= max_Gain)
            {
                max_t = temp_t;
                max_Gain = ttemp_Gain;
            }
            ttemp_Gain = 0;
        }
        temp_Gain = max_Gain;
    }
    cout << "best_Attribute:" << best_Attribute << endl;
	return max_t;
}


Tree_Node::~Tree_Node()
{
}
