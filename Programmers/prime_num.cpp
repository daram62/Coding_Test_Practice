// 프로그래머스 소수 만들기 문제

#include <vector>
#include <iostream>
using namespace std;

bool isprime(int num)
{
    bool result = true;

    if (num == 1)
        result = false;
    else if (num == 2 || num == 3)
        result = true;
    else 
    {
        for (int i = 2; i < num; i++)
            {
                if (num % i == 0)
                    result = false;
            }
    }
    return result;
}

int solution(vector<int> nums) 
{
    int answer = 0;    
    int len = nums.size();

    for (int i = 0; i < len; i++)
    {
        for (int j = i+1; j < len; j++)
        {
            for (int k = j+1; k < len; k++)
            {
                int num = nums[i] + nums[j] + nums[k];
                if (isprime(num))
                    answer ++;
            }
        }
    }
    return answer;
}