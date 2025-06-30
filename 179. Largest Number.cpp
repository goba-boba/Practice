#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

bool compare(const string& a, const string& b) {
	return a + b > b + a;
}

string largestCase(vector<int>& nums) {
	vector<string> strNums;
	for (int num : nums) {
		strNums.push_back(to_string(num));
	}
	sort(strNums.begin(), strNums.end(), compare);

	if (!strNums.empty() && strNums[0] == "0") return "0";


	string result;
	for (const string& s : strNums) {
		result += s;
	}
	return result;
}

int main(){
	setlocale(LC_ALL, "Russian");

	vector<int> nums;
	int n, num;

	cout << "Введите кол-во чисел: ";
	cin >> n;

	cout << "Введите числа (через пробел): ";
	for (int i = 0; i < n; i++) {
		cin >> num;
		nums.push_back(num);
	}
	cout << "Максимальное число = " << largestCase(nums) << endl;
	return 0;

}




