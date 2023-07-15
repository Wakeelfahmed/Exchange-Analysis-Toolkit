#include <iostream>
#include <vector>
#include<iomanip>
class Candlestick {
public:
	std::string date;
	double open;
	double high;
	double low;
	double close;

	Candlestick(const std::string& date, double open, double high, double low, double close)
		: date(date), open(open), high(high), low(low), close(close) {}
};

std::vector<Candlestick> computeCandlestickData(const std::vector<std::vector<double>>& inputData,
	const std::vector<std::string>& dates) {
	std::vector<Candlestick> candlesticks;

	for (size_t i = 0; i < inputData.size(); ++i) {
		const auto& data = inputData[i];
		double open = data[0];
		double close = data[data.size() - 1];
		double high = data[0];
		double low = data[0];

		for (size_t j = 0; j < data.size(); ++j) {
			if (data[j] > high)
				high = data[j];
			if (data[j] < low)
				low = data[j];
		}

		candlesticks.emplace_back(dates[i], open, high, low, close);
	}

	return candlesticks;
}

void generateCandlestickPlot(const std::vector<Candlestick>& candlesticks) {
	std::cout << "Candlestick Plot:" << std::endl;

	for (const auto& candlestick : candlesticks) {
		std::cout << "Date: " << candlestick.date << std::endl;
		std::cout << "High: ";
		for (int i = 0; i < candlestick.high; ++i) {
			std::cout << "-";
		}
		std::cout << std::endl;

		std::cout << "Open: ";
		for (int i = 0; i < candlestick.open; ++i) {
			std::cout << "-";
		}
		std::cout << std::endl;

		std::cout << "Close: ";
		for (int i = 0; i < candlestick.close; ++i) {
			std::cout << "-";
		}
		std::cout << std::endl;

		std::cout << "Low: ";
		for (int i = 0; i < candlestick.low; ++i) {
			std::cout << "-";
		}
		std::cout << std::endl;

		std::cout << std::endl;
	}
}

void generateVolumePlot(const std::vector<Candlestick>& candlesticks) {
	std::cout << "Volume Plot:" << std::endl;

	for (const auto& candlestick : candlesticks) {
		std::cout << candlestick.date << ": ";
		for (int i = 0; i < candlestick.high; ++i) {
			std::cout << "|";
		}
		std::cout << std::endl;
	}
}

void generateCandleChart(const std::vector<Candlestick>& data) {
	double maxPrice = 0.0;
	double minPrice = std::numeric_limits<double>::max();
	// Find the maximum and minimum prices in the data
	for (const Candlestick& candle : data) {
		maxPrice = std::max(maxPrice, candle.high);
		minPrice = std::min(minPrice, candle.low);
	}

	int chartHeight = 30; // Adjust the height of the chart as needed
	double priceRange = maxPrice - minPrice;
	//double priceInterval = 5;
	double priceInterval = priceRange / chartHeight;

	bool trend = 0;
	// Print the upper boundary


	// Print the price levels and candlesticks
	for (int i = chartHeight; i >= 0; --i) {
		double price = minPrice + (i * priceInterval);
		std::cout << "\x1B[38;5;255m";
		std::cout << "$" << std::setw(10) << std::fixed << std::setprecision(2) << price << "    |";
		for (const Candlestick& candle : data) {
			if (candle.open > candle.close) {
				trend = 0;  //RED dre
				std::cout << "\x1B[38;5;1m";
			}
			else {
				trend = 1;  //GREEN
				std::cout << "\x1B[38;5;2m";
			}

			if (candle.high >= price && candle.low <= price) {
				if (price == candle.close || price == candle.open)
					std::cout << '-';
				else if (price >= candle.open && price <= candle.close ||
					price >= candle.close && price <= candle.open) {
					std::cout << "@"; // In between the open and close
				}
				else {
					std::cout << "|"; // Outside of the open and close
				}
			}
			else {
				std::cout << " ";
			}
			// Add spacing between candles
			std::cout << std::setw(3) << "";
		}
		std::cout << "\x1B[38;5;255m";
		std::cout << "|" << std::endl;
	}

	// Print the lower boundary
	std::cout << "\x1B[38;5;255m";

	std::cout << "$" << std::setw(10) << std::fixed << std::setprecision(2) << minPrice << "    |";
	int chartWidth = static_cast<int>(data.size()) * 13; // Initialize chart width
	for (const Candlestick& candle : data) {
		chartWidth += std::max(static_cast<int>(candle.date.size()) - 12, 0); // Adjust chart width based on candle date length
	}
	for (int i = 0; i < data.size()*3; ++i) {
		std::cout << "-";
	}
	std::cout << "|" << std::endl;

	// Print the date labels
	bool alternate = 0, first = 1;
	//std::cout << std::setw(10) << "        |";

	for (size_t i = 0; i < data.size(); i += 2) {
		if (i == 0) {
			std::cout << "\t\t\b\b\b"; // Move cursor back to the left by one position
		}
		std::cout << data[i].date << "  ";
	}
	std::cout << "\n";
	for (size_t i = 1; i < data.size(); i += 2) {
		if (i == 1) {
			std::cout << "\t\t"; // Move cursor back to the left by one position
		}
		std::cout << data[i].date << "  ";
	}
	// Printing even-indexed elements

	//for (const Candlestick& candle : data) {
	//	alternate ? std::cout << "\x1B[38;5;5m" : std::cout << "\x1B[38;5;6m";
	//	alternate = !alternate;
	//	if (!first)
	//		std::cout << candle.date << " ";
	//	else
	//		std::cout << "\t\b" << candle.date << " ";
	//}
	std::cout << "\x1B[38;5;255m";
	std::cout << "|" << std::endl;
}
int main() {
	std::vector<Candlestick> data{
		{ "2/4/23", 250.0, 500.0, 200.0, 400.0 },
		{ "3/4/23", 200.0, 400.0, 100.0, 300.0 },
		{ "4/4/23", 300.0, 600.0, 250.0, 500.0 },
		{ "5/4/23", 350.0, 550.0, 300.0, 450.0 },
		{ "6/4/23", 550.0, 450.0, 350.0, 400.0 },
		{ "7/4/23", 100, 200, 50, 110 },
		{ "8/4/23", 100, 150, 50, 150 },
		{ "9/4/23", 500, 100, 10, 80 },
		{ "10/4/23", 200, 400, 50, 200 },
		{ "11/4/23", 700, 600, 150, 400 },
		{ "12/4/23", 400, 600, 0, 0 }
	};
	//open, high, low, close
	int choice;
	do {
		std::cout << "Menu:\n";
		std::cout << "1. Compute Candlestick Data\n";
		std::cout << "2. Generate Candlestick Plot\n";
		std::cout << "3. Generate Volume Plot\n";
		std::cout << "4. Exit\n";
		std::cout << "Enter your choice: ";
		std::cin >> choice;

		switch (choice) {
		case 1: {
			std::cout << "Candlestick Data:\n";
			for (const auto& candlestick : data) {
				std::cout << "Date: " << candlestick.date << ", Open: " << candlestick.open
					<< ", High: " << candlestick.high << ", Low: " << candlestick.low
					<< ", Close: " << candlestick.close << std::endl;
			}
			break;
		}
		case 2: {
			generateCandleChart(data);
			break;
		}
		case 3: {
			generateVolumePlot(data);
			break;
		}
		case 4:
			std::cout << "Exiting..." << std::endl;
			break;
		default:
			std::cout << "Invalid choice. Please try again." << std::endl;
		}

		std::cout << std::endl;
	} while (choice != 4);

	return 0;
}
