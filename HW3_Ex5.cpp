//Name: Nguyễn Thị Thu Uyên
//Student's ID: 22521643
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <limits>

using namespace std;
struct StockPrice {
    string date;
    double open;
    double high;
    double low;
    double close;
    long volume;
};

class StockTracker {
private:
    map<string, StockPrice> priceHistory;
    string symbol;
    double currentPrice;
    vector<double> priceMovingAverage;
    
public:
    StockTracker(const string& sym) : symbol(sym), currentPrice(0.0) {}

    void loadHistoricalData(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        string line;
        getline(file, line);

        while (getline(file, line)) {
            stringstream ss(line);
            string item;
            vector<string> row;
            while (getline(ss, item, ',')) {
                row.push_back(item);
            }

            if (row.size() < 7) {
                continue; 
            }
            if (row[0] == symbol) {
                StockPrice price;
                price.date = row[1];
                price.open = stod(row[2]);
                price.high = stod(row[3]);
                price.low = stod(row[4]);
                price.close = stod(row[5]);
                price.volume = stol(row[6]);
                
                priceHistory[price.date] = price;
                currentPrice = price.close;
            }
        }

        file.close();
        updateMovingAverage();
    }
    void updatePrice(const string& date, double price) {
        if (priceHistory.find(date) != priceHistory.end()) {
            priceHistory[date].close = price;
            priceHistory[date].high = max(priceHistory[date].high, price);
            priceHistory[date].low = min(priceHistory[date].low, price);
        } else {
            StockPrice newPrice;
            newPrice.date = date;
            newPrice.open = price;
            newPrice.high = price;
            newPrice.low = price;
            newPrice.close = price;
            newPrice.volume = 0; 
            priceHistory[date] = newPrice;
        }
        currentPrice = price;
        updateMovingAverage();
    }
    vector<StockPrice> getPriceRange(const string& startDate, const string& endDate) {
        vector<StockPrice> result;
        auto start = priceHistory.lower_bound(startDate);
        auto end = priceHistory.upper_bound(endDate);

        for (auto it = start; it != end; ++it) {
            result.push_back(it->second);
        }
        return result;
    }
    void updateMovingAverage() {
        const int period = 20;
        priceMovingAverage.clear();
        if (priceHistory.size() < period) return;

        vector<double> closes;
        for (const auto& entry : priceHistory) {
            closes.push_back(entry.second.close);
        }

        for (size_t i = period - 1; i < closes.size(); ++i) {
            double sum = 0.0;
            for (size_t j = i - period + 1; j <= i; ++j) {
                sum += closes[j];
            }
            priceMovingAverage.push_back(sum / period);
        }
    }
    void printStats() {
        cout << "\nStock: " << symbol << endl;
        cout << "Current Price: $" << fixed << setprecision(2) << currentPrice << endl;

        if (!priceHistory.empty()) {
            double highestPrice = 0.0, lowestPrice = numeric_limits<double>::max();
            for (const auto& price : priceHistory) {
                highestPrice = max(highestPrice, price.second.high);
                lowestPrice = min(lowestPrice, price.second.low);
            }

            cout << "52-Week High: $" << highestPrice << endl;
            cout << "52-Week Low: $" << lowestPrice << endl;

            if (!priceMovingAverage.empty()) {
                cout << "20-Day Moving Average: $" << fixed << setprecision(2) << priceMovingAverage.back() << endl;
            }
        }
    }
};

int main() {
    StockTracker tracker("BID");
    tracker.loadHistoricalData("BID.csv");
    tracker.printStats();
    cout << "\nSimulating real-time updates..." << endl;
    tracker.updatePrice("20210626", 45.75);
    tracker.updatePrice("20210627", 46.20);
    tracker.updatePrice("20210628", 45.90);
    tracker.printStats();
    cout << "\nGetting price range for June 2021..." << endl;
    auto priceRange = tracker.getPriceRange("20210601", "20210630");
    for (const auto& price : priceRange) {
        cout << price.date << ": Open $" << price.open 
             << " Close $" << price.close << endl;
    }

    return 0;
}