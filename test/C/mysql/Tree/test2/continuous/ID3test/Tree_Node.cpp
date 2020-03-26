#include "Tree_Node.h"
#include <math.h>
#include <sstream>
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>

Tree_Node::Tree_Node(map<string, vector<string>> temp_Table,vector<string> temp_Attribute, map<string, vector<string>> data_AttValues, vector<string> temp_remain)
{
	//ȫ������,�������
	data_Attribute = temp_Attribute;
	//���Ը��������������
	attribute_Num = (int)temp_Attribute.size() - 1;
	//�����Զ�Ӧ������ֵ
	this->data_AttValues = data_AttValues;
	//���Ա�
	MyDateTable = temp_Table;
	//ʣ�����Լ�
	remain_Attributes = temp_remain;
}

void Tree_Node::generate_ChildNode()
{
	//��������
	int N = (int)MyDateTable[data_Attribute[0]].size();
    cout << N << endl;
	
	//�����ݼ�������������������map���棬ֻ���ж����һ�м���
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

	//��һ�����
	//ֻ��һ����𣬱��ΪҶ�ڵ�
	if (1 == category.size())
	{
		map<string, int>::iterator it = category.begin();
		node_Attribute = it->first;
		return;
	}
	//�ڶ������
	//���ж����������Ƿ�ȡ��ֵͬ
	bool isAllSame = false;
	for (int i = 0; i < remain_Attributes.size(); i++)
	{
		isAllSame = true;
		vector<string> temp;
		temp = MyDateTable[remain_Attributes[i]];
		for (int j = 1; j < temp.size(); j++)
		{
			//ֻҪ��һ����ͬ�������˳�
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
	//�����Լ�Ϊ�ջ��������е�ȫ������ȡֵ��ͬ
	if (remain_Attributes.empty()||isAllSame)
	{
		//�ҳ����������������ֵĸ����������ýڵ���Ϊ����
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
	//���������
	//��remian_attributes�л�����������
	string best_Attribute = findBestAttribute();
	//�����ڵ�����Ϊ��������
	node_Attribute = best_Attribute;
	//���������Ե�ÿ������ֵ
	int checkcon = 0;
    if(node_Attribute == "�ܶ�" || node_Attribute == "������")
        checkcon = 1;
    if(checkcon == 1)
    {
        double temp_t = findBestT(node_Attribute);//���t��findAtt����ȡ��
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
        cout << "�м�㡣�����ָ���" << endl;
        for(auto iter = sub_DataTableLess.rbegin();iter != sub_DataTableLess.rend();iter++)
        {
            cout <<"first" <<iter->first <<endl;
            for(auto it=(iter->second).begin();it != (iter->second).end();it++)
                cout <<*it << " ";
            cout << endl;
        }
        cout << "�ڶ����ָ��ߡ�������������"<< endl;
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
            //�����ӽ�
            Tree_Node * p = new Tree_Node(sub_DataTablePlus, data_Attribute, data_AttValues, remain_Attributes);
	    	//�ҳ����������࣬��Ϊ�ӽڵ������
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
			//������Ҷ�ڵ�����
            p->set_NodeAttribute(childNode_Attribute);
    		cout<< "�м�sub_DataTablePlusΪempty������"<< endl;
            //���ӽڵ����childNode��Ԥ��������ʱ����õ�
    		childNode[best_AttValues] = p;
        }
    	else//����Ϊ�գ����ʣ������ֵ�޳������ԣ�����generate_ChildNode��������ϸ��
    	{
            string plus = ">";
            string t_string;
            stringstream ss;
            ss << temp_t;
            ss >> t_string;
            string best_AttValues = plus + t_string;
			vector<string> child_RemainAtt;
            child_RemainAtt = remain_Attributes;
    		//�ҳ�child_RemainAtt�е�������������ȵ�����
    		vector<string>::iterator it = child_RemainAtt.begin();
			for (; it != child_RemainAtt.end(); it++)
            {
    			if (*it == best_Attribute)
    			{
					break;
                }
 			}
            //ɾ��
    		child_RemainAtt.erase(it);
            cout << "��sub_DataTablePlus��Ϊempty������"<< endl;

    		//�����ӽڵ�
    		Tree_Node * pt = new Tree_Node(sub_DataTablePlus, data_Attribute, data_AttValues, child_RemainAtt);
			//���ӽڵ����childNode
            childNode[best_AttValues] = pt;
			//�ӽڵ��ٵ���generate_ChildNode����
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
            //�����ӽ�
            Tree_Node * p = new Tree_Node(sub_DataTableLess, data_Attribute, data_AttValues, remain_Attributes);
	    	//�ҳ����������࣬��Ϊ�ӽڵ������
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
            cout<<"sub_DataTableLessΪempty�������"<< endl;
			//������Ҷ�ڵ�����
            p->set_NodeAttribute(childNode_Attribute);
    		//���ӽڵ����childNode��Ԥ��������ʱ����õ�
    		childNode[best_AttValues] = p;
        }
    	else//����Ϊ�գ����ʣ������ֵ�޳������ԣ�����generate_ChildNode��������ϸ��
    	{
            string plus = "<";
            string t_string;
            stringstream ss;
            ss << temp_t;
            ss >> t_string;
            string best_AttValues = plus + t_string;
			vector<string> child_RemainAtt;
            child_RemainAtt = remain_Attributes;
    		//�ҳ�child_RemainAtt�е�������������ȵ�����
    		vector<string>::iterator it = child_RemainAtt.begin();
			for (; it != child_RemainAtt.end(); it++)
            {
    			if (*it == best_Attribute)
    			{
					break;
                }
 			}
            //ɾ��
    		child_RemainAtt.erase(it);
            cout << "��sub_DataTableLess��Ϊempty������"<< endl;
    		//�����ӽڵ�
    		Tree_Node * pt = new Tree_Node(sub_DataTableLess, data_Attribute, data_AttValues, child_RemainAtt);
			//���ӽڵ����childNode
            childNode[best_AttValues] = pt;
			//�ӽڵ��ٵ���generate_ChildNode����
            //
            pt->generate_ChildNode();
    	}
    }
    else
    {
        for (int i = 0; i < data_AttValues[best_Attribute].size(); i++)
	    {
		    string best_AttValues = data_AttValues[best_Attribute][i];
		    //�������Զ�Ӧ�����ݼ�D
		    //����map������Ÿ�����ֵ�µ������Ӽ�
		    map<string, vector<string>> sub_DataTable;
		    for (int j = 0; j < MyDateTable[best_Attribute].size(); j++)
		    {
			    //Ѱ���������������ݼ�������ֵ��ͬ����������
			    if (best_AttValues == MyDateTable[best_Attribute][j])
			    {
				    //�ҵ���Ӧ�����ݼ��������Ӽ���sub_DataTable����������ȫ�����Զ�Ҫ���룩
				    for (int k = 0; k < data_Attribute.size(); k++)
				    {
					    sub_DataTable[data_Attribute[k]].push_back(MyDateTable[data_Attribute[k]][j]);
				    }
			    }
	    	}
		    //���Ӽ�Ϊ�գ�����֧�ڵ㣨�ӽڵ㣩���ΪҶ�ڵ㣬���ΪMyDateTable����������
		    if (sub_DataTable.empty())
		    {
    			//�����ӽڵ�
	    		Tree_Node * p = new Tree_Node(sub_DataTable, data_Attribute, data_AttValues, remain_Attributes);
		    	//�ҳ����������࣬��Ϊ�ӽڵ������
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
    			//������Ҷ�ڵ�����
		    	p->set_NodeAttribute(childNode_Attribute);
    			//���ӽڵ����childNode��Ԥ��������ʱ����õ�
    			childNode[best_AttValues] = p;
	    	}
    		else//����Ϊ�գ����ʣ������ֵ�޳������ԣ�����generate_ChildNode��������ϸ��
    		{
    			vector<string> child_RemainAtt;
    			child_RemainAtt = remain_Attributes;
    			//�ҳ�child_RemainAtt�е�������������ȵ�����
    			vector<string>::iterator it = child_RemainAtt.begin();
    			for (; it != child_RemainAtt.end(); it++)
    			{
    				if (*it == best_Attribute)
    				{
    					break;
    				}
    			}
    			//ɾ��
    			child_RemainAtt.erase(it);

    			//�����ӽڵ�
    			Tree_Node * pt = new Tree_Node(sub_DataTable, data_Attribute, data_AttValues, child_RemainAtt);
    			//���ӽڵ����childNode
    			childNode[best_AttValues] = pt;
    			//�ӽڵ��ٵ���generate_ChildNode����
    			pt->generate_ChildNode();
    		}
    	}
    }
}

//Ѱ�����Ż���
string Tree_Node::findBestAttribute()
{
	//��������
	int N = (int)MyDateTable[data_Attribute[0]].size();
	//�������ڴ����������
	string best_Attribute;
	//��Ϣ����
	double gain = 0;
    map<string,double> Attribute_Gain;
    map<string,double> Attribute_Gratio;
	//��ÿ��ʣ������
	for (int i = 0; i < remain_Attributes.size(); i++)
	{
		//������Ϣ���棬ѡȡ�����������������ּ�Ϊ���Ż���
		double temp_Gain = calc_Entropy(MyDateTable);//���ݹ�ʽ�Ƚ����ڵ����Ϣ�س�ʼ��������
		cout << "first Ent(D):" << temp_Gain<< endl;
        int checkcon = 0;
        //�Ը����Ե����ݼ����з��ࣨ��ȡ������ֵ�������Ӽ���
		string temp_Att = remain_Attributes[i];//����ѡȡ������
        //string temp_Att = "�ܶ�";
        if(temp_Att == "�ܶ�" || temp_Att == "������")
            checkcon = 1;
        vector<string> remain_AttValues;//���Կ��ܵ�ȡֵ
		if(checkcon == 1)//ִ������ֵGain����
        {
            double temp_t = 0.0;
            string temp_sAttValue;
            double temp_AttValue;
            double ttemp_Gain;
            double max_Gain = 0;
            vector<double> remain_AttValues;
            vector<double> remain_tempt;
            map<double,string> table_con;
            //����������ֵѹ��remain_AttValues;
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
            //���������Gain�Լ���Ӧ��t
            for(int j = 0; j < remain_tempt.size(); j++)
            {
                temp_t = remain_tempt[j];
                temp_Gain = calc_Entropy(MyDateTable);
                //������Ŷ�Ӧ������
                double temp_con;
                int sample_Numplus = 0;//����t������Ŀ
                int sample_Numless = 0;//С��t������Ŀ
                map<string, vector<string>>sub_DataTablePlus;
                map<string, vector<string>>sub_DataTableLess;
                //����tС�Ĵ���less����t���ֵ����plus
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

        //ִ�з�����ֵGain����
        else
        {
            for (int j = 0; j < data_AttValues[temp_Att].size(); j++)
		    {
			    remain_AttValues.push_back(data_AttValues[temp_Att][j]);
		    }
		
		    //��ÿ������ֵ����Ϣ��
		    for (int k = 0; k < remain_AttValues.size(); k++)
		    {
			    //����ֵ
			    string temp_AttValues = remain_AttValues[k];
			    int sample_Num = 0;//������ֵ��Ӧ��������
			    //����map������Ÿ�����ֵ�µ������Ӽ�
			    map<string, vector<string>>sub_DataTable;
			    for (int l = 0; l < MyDateTable[temp_Att].size(); l++)
			    {
				    if (temp_AttValues == MyDateTable[temp_Att][l])
				    {
					    sample_Num++;
					    //������������ѵ��������sub_DataTable
					    for (int m = 0; m < data_Attribute.size(); m++)
					    {
						    sub_DataTable[data_Attribute[m]].push_back(MyDateTable[data_Attribute[m]][l]);
					    }
				    }
			    }
			    //�ۼ�ÿ����ֵ����Ϣ��
                temp_Gain -= (double)sample_Num / N * calc_Entropy(sub_DataTable);
                cout << "sample_Num" << sample_Num << endl;
		    }
        }
		//�Ƚ�Ѱ�����Ż�������
		cout << "temp_Gain:" << temp_Gain << "temp_Att:"<< temp_Att<< endl;
        if (temp_Gain > gain)
		{
			gain = temp_Gain;
			best_Attribute = temp_Att;
		}
	}
	return best_Attribute;
}

//������Ϣ��
double Tree_Node::calc_Entropy(map<string, vector<string>> temp_Table)
{
	map<string, vector<string>> table = temp_Table;
	//���ݼ�������������
	int sample_Num = (int)temp_Table[data_Attribute[0]].size();
	//�������ݼ��е��������
	map<string, int> class_Map;
	for (int i = 0; i < sample_Num; i++)
	{
		//data_Attribute[attribute_Num]��Ӧ�ľ������ݼ������
		string class_String = table[data_Attribute[attribute_Num]][i];
		class_Map[class_String]++;
	}

    for(auto iter = class_Map.rbegin();iter != class_Map.rend();iter++)
        cout <<"string :" << iter->first << "int :" << iter->second << endl;
	map<string, int>::iterator it = class_Map.begin();
	//���������Ӧ������
	//vector<string> m_Class;
	vector<int> n_Class;
	
	for (; it != class_Map.end(); it++)
	{
		//m_Class.push_back(it->first);
		n_Class.push_back(it->second);
	}
	//������Ϣ��
	double Ent = 0;
	for (int k = 0; k < class_Map.size(); k++)
	{
		//����
		double p = (double) n_Class[k] / sample_Num;
		if (p == 0)
		{
			//�涨��p=0ʱ��plogp=0
			continue;
		}
		//c++��ֻ��log��ln�������ҪӦ�û��׹�ʽ
		Ent -= p * (log(p) / log(2));//��Ϣ��
	}
	cout << "Ent" << Ent<<endl;
	return Ent;
}

void Tree_Node::set_NodeAttribute(string attribute)
{
	//���ýڵ������
	this->node_Attribute = attribute;
}

//����Ϊ��Ԥ���������������Լ���
string Tree_Node::findClass(vector<string> attributes)
{
	//�������ӽڵ�
	if (childNode.size() != 0)
	{
		//�ҳ�������������뱾�ڵ����Զ�Ӧ������ֵ���Ա�Ѱ���¸��ڵ㣬ֱ���ҵ�Ҷ�ڵ�
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
				//data_AttValues[node_Attribute]Ϊ����node_Attribute��Ӧ�����п��ܵ�ȡֵ����
				if (attributes[j] == data_AttValues[node_Attribute][i])
				{
					//�ҵ���������Ӧ������ֵ
					attribute_Value = attributes[j];
                    cout << "��������������:"<< attribute_Value << endl;
					break;
				}
			}
			//�ҵ����û��Ҫ����ѭ����
			if (!attribute_Value.empty())
			{
				break;
			}
		}
		//�ҳ�������ֵ��Ӧ���ӽڵ�ĵ�ַ���Ա���з���
		Tree_Node *p = childNode[attribute_Value];
		return p->findClass(attributes);//�ݹ�Ѱ�ң�ֱ���ҵ�Ҷ�ڵ�Ϊֹ
	}
	else//�������ӽڵ�˵���Ѿ��ҵ����࣬���Ϊ���ڵ��node_Attribute
	{
		return node_Attribute;
	}
}
double Tree_Node::findBestT(string Att)
{
    double max_t = 0;
	//��������
	int N = (int)MyDateTable[data_Attribute[0]].size();
	//�������ڴ����������
	string best_Attribute;
	//��Ϣ����
    map<string,double> Attribute_Gain;
    map<string,double> Attribute_Gratio;
	//��ÿ��ʣ������
	double temp_Gain = calc_Entropy(MyDateTable);//���ݹ�ʽ�Ƚ����ڵ����Ϣ�س�ʼ��������
	cout << "first Ent(D):" << temp_Gain<< endl;
    int checkcon = 0;
    //�Ը����Ե����ݼ����з��ࣨ��ȡ������ֵ�������Ӽ���
	string temp_Att = Att;//����ѡȡ������
    //string temp_Att = "�ܶ�";
    if(temp_Att == "�ܶ�" || temp_Att == "������")
        checkcon = 1;
    vector<string> remain_AttValues;//���Կ��ܵ�ȡֵ
	if(checkcon == 1)//ִ������ֵGain����
    {
        double temp_t = 0.0;
        string temp_sAttValue;
        double temp_AttValue;
        double ttemp_Gain;
        double max_Gain = 0;
        vector<double> remain_AttValues;
        vector<double> remain_tempt;
        map<double,string> table_con;
        //����������ֵѹ��remain_AttValues;
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
        //���������Gain�Լ���Ӧ��t
        for(int j = 0; j < remain_tempt.size(); j++)
        {
            temp_t = remain_tempt[j];
            temp_Gain = calc_Entropy(MyDateTable);
            //������Ŷ�Ӧ������
            double temp_con;
            int sample_Numplus = 0;//����t������Ŀ
            int sample_Numless = 0;//С��t������Ŀ
            map<string, vector<string>>sub_DataTablePlus;
            map<string, vector<string>>sub_DataTableLess;
            //����tС�Ĵ���less����t���ֵ����plus
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
