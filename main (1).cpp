#include <iostream>
#include <vector>

class Solution {
public:
    int maxProfit(std::vector<int>& prices) {
        int n = prices.size();
        if (n <= 1) {
            return 0;
        }

        // Инициализация массивов для отслеживания прибыли после первой и второй транзакций
        std::vector<int> firstTransaction(n, 0);
        std::vector<int> secondTransaction(n, 0);

        // Находим максимальную прибыль после первой транзакции
        int minPrice = prices[0];
        for (int i = 1; i < n; ++i) {
            minPrice = std::min(minPrice, prices[i]);
            firstTransaction[i] = std::max(firstTransaction[i - 1], prices[i] - minPrice);
        }

        // Находим максимальную прибыль после второй транзакции
        int maxPrice = prices[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            maxPrice = std::max(maxPrice, prices[i]);
            secondTransaction[i] = std::max(secondTransaction[i + 1], maxPrice - prices[i]);
        }

        // Находим максимальную общую прибыль с двумя транзакциями
        int maxProfit = 0;
        for (int i = 0; i < n; ++i) {
            maxProfit = std::max(maxProfit, firstTransaction[i] + secondTransaction[i]);
        }

        return maxProfit;
    }
};

int main() {
    // Пример использования:
    std::vector<int> prices = {3, 3, 5, 0, 0, 3, 1, 4};

    Solution solution;
    int result = solution.maxProfit(prices);

    std::cout << "Maximum profit with two transactions: " << result << std::endl;

    return 0;
}