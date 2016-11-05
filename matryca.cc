#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
#define FOR(x, b, e) for(int x = b; x <= (e); ++x)

int main() {
	ios_base::sync_with_stdio(false);
	string s;
	cin >> s;
	size_t length = s.length();
	size_t begin = s.find_first_not_of('*'), end = s.find_last_not_of('*');
	if(begin == string::npos || end == string::npos || begin == end)
		cout << 1;// << '\n';
	else {
		// co najmniej dwa znaki
		int last_character = s[begin], current_range = 0, minimum_range = length - 1;
		FOR(i, begin, end) {
			if(s[i] == '*')
				current_range++;
			else if(s[i] == last_character)
				current_range = 0;
			else {
				minimum_range = min(minimum_range, current_range);
				current_range = 0;
				last_character = s[i];
			}
		}
		cout << length - minimum_range;// << '\n';
	}

	return 0;
}