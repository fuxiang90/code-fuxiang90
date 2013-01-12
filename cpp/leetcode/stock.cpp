#include<string>
#include<iostream>
#include<fstream>
#include <map>
#include <queue>
//#include <deque>
using namespace std;


class SolutionSlow {
public:
	int maxProfit(vector<int> &prices) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		int profit = 0;

		int len = prices.size();
		for(int i = 0 ; i < len ; i ++){
			for(int j = i + 1 ; j < len ; j ++){
				if(prices[j] - prices[i] > profit)
					profit = prices[j] - prices[i];
			}
		}

		return profit;

	}
};


class Solution {
public:
	int maxProfit(vector<int> &prices) {
		// Start typing your C/C++ solution below
		// DO NOT write int main() function
		int profit = 0;
        int len = prices.size();
        vector<int> data(prices.size() ,0 );
        for(int i = 0 ; i < len - 1 ; i ++){
            int t = prices[i+1] - prices[i];
            data[i] = t;
        }
		int maxprofit = 0;
		for(int i = 0 ; i < len -1 ; i ++){
            profit += data[i];
            if(profit > maxprofit){
                maxprofit = profit;
            }
            if(profit < 0 ) profit = 0;
		}

		return maxprofit;

	}
};


int main()
{


	return 0;
}
