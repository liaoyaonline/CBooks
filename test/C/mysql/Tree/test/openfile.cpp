#include <iostream>
#include <fstream>
using namespace std;
int main()
{
    int N;
    string input_Line,temp_Attributes;
    ifstream infile;
    infile.open("test.txt");
    cout<< "Reading from the file" <<endl;
    getline(infile,input_Line);
    infile >> N;
    cout << input_Line <<endl;
    for(int i = 0; i < N; i++)
    {
        getline(infile,input_Line);
        cout << input_Line <<endl;
    }
    cout << input_Line <<endl;
    cout << N <<endl;
    infile.close();
    return 0;
}

