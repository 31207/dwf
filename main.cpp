#include "dwf.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>   //用于计时

using namespace std;

std::vector<std::string> splitWithStl(const std::string& str, const std::string& pattern)
{
    std::vector<std::string> resVec;
    if ("" == str)
    {
        return resVec;
    }
    //方便截取最后一段数据
    std::string strs = str + pattern;
    size_t pos = strs.find(pattern);
    size_t size = strs.size();
    while (pos != std::string::npos)
    {
        std::string x = strs.substr(0, pos);
        resVec.push_back(x);
        strs = strs.substr(pos + 1, size);
        pos = strs.find(pattern);
    }
    return resVec;
}



/* 用于测试我自己写的大数类计算速度
int main()
{
    std::string data;
    std::fstream file;
    std::vector<std::string> datas;
    file.open("./data.txt", std::ios::in);
    while (getline(file, data))
    {
        datas.push_back(data);
    }
    dwf::Bigint* a = new dwf::Bigint[datas.size()];
    dwf::Bigint* b = new dwf::Bigint[datas.size()];
    dwf::Bigint* res = new dwf::Bigint[datas.size()];
    dwf::Bigint* res2 = new dwf::Bigint[datas.size()];

	string* a_str = new string[datas.size()];
    string* b_str = new string[datas.size()];
    string* res_str = new string[datas.size()];
    string* res2_str = new string[datas.size()];
    int j = 0;
    for (auto i = datas.begin(); i != datas.end(); ++i,++j)
    {
        std::vector<std::string> tmp = splitWithStl(*i, " ");
        a[j] = dwf::Bigint(tmp[0]);
        b[j] = dwf::Bigint(tmp[1]);
        res[j] = dwf::Bigint(tmp[2]);
        a_str[j] = tmp[0];
        b_str[j] = tmp[1];
        res_str[j] = tmp[2];
    }
    auto start = std::chrono::high_resolution_clock::now();

	//for (int i = 0; i < datas.size(); i++)  //执行相乘
 //   {
 //       res2[i] = a[i] * b[i];
 //   }

    for (int i = 0; i < datas.size(); i++)
    {
        res2_str[i] = KaratsubaMultiply(a_str[i], b_str[i]);
    }

    auto end = std::chrono::high_resolution_clock::now();
    double duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000000.0;
    std::cout << std::to_string(datas.size()) + "个数据用时：" + std::to_string(duration) + "秒" << std::endl;
    //验证答案
  //  for (int i = 0; i < datas.size(); i++)
  //  {
		//if (res[i].tostring() != res2[i].tostring())
  //      {
  //          std::cout << "有错误答案！" << std::endl;
  //          break;
  //      }
  //  }

    
     const int a = rand();
     std::string line;
     std::getline(std::cin,line);
     for(char c : line)
     {
         std::cout<<c<<std::endl;
     }
    

    return 0;
}
*/

int main()    //测试二叉树
{
    //int nums[] = {9,4,1,0,6,9};
    srand(time(0));
    vector<int> nums;
    for(int i=0;i<20;i++)
    {
        nums.push_back(rand()%1000);
    }


    dwf::BinaryTree t(nums);
    t.preOrder();
    //t.setNodeVal(0, 10000);
    cout << endl;
    t.inOrder();
    cout << endl;
    //t.insert(5);
    t.postOrder();
    cout << endl;
    t.layerOrder();
    return 0;
}

//
//int main()
//{
//    ifstream file("./data2.txt", ios::in);
//    if (!file.is_open())
//    {
//        cout << "failed";
//        return -1;
//    }
//    vector<int> datas;
//    string data;
//    while (getline(file, data))
//    {
//      
//        datas.push_back(atoi(data.data()));
//    }
//    int* nums = new int[datas.size()];
//    for (size_t i = 0; i < datas.size(); i++)
//    {
//        nums[i] = datas[i];
//    }
//    auto start = std::chrono::high_resolution_clock::now();
//    //sort(datas.begin(), datas.end());
//    //dwf::bubbleSort(nums, datas.size());
//    dwf::fastSort(nums, datas.size());
//    auto end = std::chrono::high_resolution_clock::now();
//    double duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000000.0;
//    std::cout << std::to_string(datas.size()) + "个数据用时：" + std::to_string(duration) + "秒" << std::endl;
//    vector<int> res;
//    for (size_t i = 0; i < datas.size(); i++)
//    {
//        res.push_back(nums[i]);
//    }
//
//    return 0;
//}
