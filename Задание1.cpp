#include <iostream>
#include <vector>
#include <queue>

class MedianFinder {
private:
    std::priority_queue<int> small;  // Максимальная куча для хранения меньшей половины чисел
    std::priority_queue<int, std::vector<int>, std::greater<int>> large;  // Минимальная куча для хранения большей половины чисел

public:
    MedianFinder() {
    }

    void addnum(int num) {
        if (small.empty() || num <= small.top()) {
            small.push(num);
        } else {
            large.push(num);
        }

        // Балансировка размеров куч, чтобы обеспечить правильную медиану
        if (small.size() > large.size() + 1) {
            large.push(small.top());
            small.pop();
        } else if (large.size() > small.size()) {
            small.push(large.top());
            large.pop();
        }
    }

    double findmedian() {
        if (small.size() == large.size()) {
            return (double)(small.top() + large.top()) / 2;
        } else {
            return small.top();
        }
    }
};

int main() { // Пример использования
    MedianFinder mf;
    std::vector<int> nums = {1, 2, 3};

    for (int num : nums) {
        mf.addnum(num);
        std::cout << "Median: " << mf.findmedian() << std::endl;
    }

    return 0;
}