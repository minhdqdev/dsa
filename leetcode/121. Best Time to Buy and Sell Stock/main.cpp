class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.size() < 2) return 0;
        
        int pMax = 0;
        int n = prices.size();
        int maxValue = prices[n-1];
        
        for(int i=n-2; i>-1; i--){
            if(maxValue - prices[i] > pMax) pMax = maxValue - prices[i];
            if(prices[i] > maxValue) maxValue = prices[i];
        }
        
        return pMax;
    }
};