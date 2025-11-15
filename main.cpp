#include "matplot/matplot.h"
#include <vector>
#include <random>
#include <numeric>
#include <cmath>

using namespace matplot;

std::vector<double> simulate_prices(int days, double start = 100.0) {
	std::vector<double> prices(days);
	std::default_random_engine eng((unsigned)time(NULL));
	std::normal_distribution<double> dist(0.0, 0.01);
	
	double price = start;
	for (int i = 0; i < days; i++) {
		price *= 1.0 + dist(eng);
		prices[i] = price;
	}
	return prices;
}

std::vector<double> moving_average(const std::vector<double>& data, int window) {
	std::vector<double> out(data.size(), NAN);
	if (window > data.size()) return out;
	
	double sum = 0.0;
	for (int i = 0; i < window; i++)
		sum += data[i];
	out[window - 1] = sum / window;
	
	for (int i = window; i < data.size(); i++) {
		sum += data[i] - data[i - window];
		out[i] = sum / window;
	}
	return out;
}

int main() {
	const int DAYS = 300;
	
	auto prices = simulate_prices(DAYS);
	auto ma9    = moving_average(prices, 9);
	auto ma21   = moving_average(prices, 21);
	auto ma200  = moving_average(prices, 200);
	
	std::vector<double> x(DAYS);
	for (int i = 0; i < DAYS; i++) x[i] = i;
	
	matplot::plot(x, prices)->display_name("Price");
	hold(on);
	matplot::plot(x, ma9)->display_name("MA9");
	matplot::plot(x, ma21)->display_name("MA21");
	matplot::plot(x, ma200)->display_name("MA200");
	
	matplot::legend();
	matplot::show();
	
	return 0;
}

