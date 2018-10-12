#include "bigint.h"
#include <sstream>
#include <bitset>

template<size_t _Bits>
long long rget(std::bitset<_Bits> a, int start, int count) {
	if (count > 1) {
		long long num = 0;
		int end = start + count;
		while (start < end) {
			num |= ((a[(_Bits - 1 - (start++))]) ? 1 : 0);
			num <<= 1;
		}
		return (num >> 1);
	}
	else if (count < 1) {
		return 0;
	}
	else {
		return a[(_Bits - (start))];
	}
}

namespace BigInt {

	//Constructor
	Bigint::Bigint() {
		positive = true;
		base = Bigint::default_base;
		skip = 0;
	}
	Bigint::Bigint(const Bigint &b)
		: number(b.number),
		positive(b.positive),
		base(b.base),
		skip(b.skip) {
	}
	Bigint::Bigint(const Bigint &&b)
		: number(b.number),
		positive(b.positive),
		base(b.base),
		skip(b.skip) {
	}
	Bigint::Bigint(long double value) : Bigint((double)value) {}
	Bigint::Bigint(float value) {
		auto t__ = (unsigned long long *)(&value);
		std::bitset<32> n(*t__);
		base = Bigint::default_base;
		skip = 0;
		//std::cout << n << std::endl;
		positive = !(n[31]);

		int e = (int)(rget(n, 1, 8) - 127);
		if (e == 0) {
			number.push_back(1);
		}
		else if (e > 0) {
			int a = (((23) < (e)) ? (23) : (e));
			long long m = (1ULL << a) | rget(n, 9, a);
			while (m) {
				number.push_back((int)(m % base));
				m /= base;
			}
			if (e > a) {
				*this *= Bigint(2).pow((unsigned int)(e - a));
			}
		}

		//while (value) {
		//	number.push_back((int)(value % base));
		//	value /= base;
		//}
	}
	Bigint::Bigint(double value) {
		auto t__ = (unsigned long long *)(&value);
		std::bitset<64> n(*t__);
		base = Bigint::default_base;
		skip = 0;
		//std::cout << n << std::endl;
		positive = !(n[63]);

		int e = (int)(rget(n, 1, 11) - 1023);
		if (e == 0) {
			number.push_back(1);
		}
		else if (e > 0) {
			int a = (((52) < (e)) ? (52) : (e));
			long long m = (1ULL << a) | rget(n, 12, a);
			while (m) {
				number.push_back((int)(m % base));
				m /= base;
			}
			if (e > a) {
				*this *= Bigint(2).pow((unsigned int)(e - a));
			}
		}

		//while (value) {
		//	number.push_back((int)(value % base));
		//	value /= base;
		//}
	}
	Bigint::Bigint(long long value) {
		base = Bigint::default_base;
		skip = 0;
		if (value < 0) {
			positive = false;
			value *= -1;
		}
		else {
			positive = true;
		}

		while (value) {
			number.push_back((int)(value % base));
			value /= base;
		}
	}
	Bigint::Bigint(unsigned long long value) {
		base = Bigint::default_base;
		skip = 0;
		positive = true;

		while (value) {
			number.push_back((int)(value % base));
			value /= base;
		}
	}
	Bigint::Bigint(int value) {
		base = Bigint::default_base;
		skip = 0;
		if (value < 0) {
			positive = false;
			value *= -1;
		}
		else {
			positive = true;
		}

		while (value) {
			number.push_back((int)(value % base));
			value /= base;
		}
	}

	Bigint operator "" _Bigint(const char * str) {
		return Bigint(str);
	}
	Bigint operator "" _Bigint(const unsigned long long str) {
		return Bigint(str);
	}
	Bigint operator "" _Bigint(const long double str) {
		return Bigint(str);
	}
	
	Bigint::Bigint(std::string stringInteger) {
		int size = stringInteger.length();

		base = Bigint::default_base;
		skip = 0;
		positive = (stringInteger[0] != '-');

		while (true) {
			if (size <= 0) break;
			if (!positive && size <= 1) break;

			int length = 0;
			int num = 0;
			int prefix = 1;
			for (int i(size - 1); i >= 0 && i >= size - 9; --i) {
				if (stringInteger[i] < '0' || stringInteger[i] > '9') break;
				num += (stringInteger[i] - '0') * prefix;
				prefix *= 10;
				++length;
			}
			number.push_back(num);
			size -= length;
		}
	}

	//Adding
	Bigint Bigint::operator+(Bigint const &b) const {
		Bigint c = *this;
		c += b;

		return c;
	}

	Bigint &Bigint::operator+=(Bigint const &b) {
		if (!b.positive) {
			return *this -= b;
		}
		std::vector<int>::iterator
			it1 = number.begin();
		std::vector<int>::const_iterator
			it2 = b.number.begin();
		int sum = 0;
		while (it1 != number.end() || it2 != b.number.end()) {
			if (it1 != number.end()) {
				sum += *it1;
			}
			else {
				number.push_back(0);
				it1 = number.end() - 1;
			}
			if (it2 != b.number.end()) {
				sum += *it2;
				++it2;
			}
			*it1 = sum % base;
			++it1;
			sum /= base;
		}
		if (sum) number.push_back(1);

		return *this;
	}

	Bigint Bigint::operator+(long long const &b) const {
		Bigint c = *this;
		c += b;

		return c;
	}

	Bigint &Bigint::operator+=(long long b) {
		std::vector<int>::iterator it = number.begin();
		if (skip > number.size()) {
			number.insert(number.end(), skip - number.size(), 0);
		}
		it += skip;
		bool initial_flag = true;
		while (b || initial_flag) {
			initial_flag = false;
			if (it != number.end()) {
				*it += b % base;
				b /= base;
				b += *it / base;
				*it %= base;
				++it;
			}
			else {
				number.push_back(0);
				it = number.end() - 1;
			}
		}

		return *this;
	}

	Bigint &Bigint::operator++() {
		*this += 1;
		return *this;
	}

	Bigint Bigint::operator++(int) {
		auto temp(*this);
		++*this;
		return temp;
	}

	Bigint operator+(long long const &b, Bigint c) {
		c += b;
		return c;
	}

	//Subtraction
	Bigint Bigint::operator-(Bigint const &b) const {
		Bigint c = *this;
		c -= b;

		return c;
	}

	Bigint &Bigint::operator-=(Bigint const &b) {
		std::vector<int>::iterator
			it1 = number.begin();
		std::vector<int>::const_iterator
			it2 = b.number.begin();
		int dif = 0;
		while (it1 != number.end() || it2 != b.number.end()) {
			if (it1 != number.end()) {
				dif += *it1;
				++it1;
			}
			if (it2 != b.number.end()) {
				dif -= *it2;
				++it2;
			}
			if (dif < 0) {
				*(it1 - 1) = dif + base;
				dif = -1;
			}
			else {
				*(it1 - 1) = dif % base;
				dif /= base;
			}
		}
		if (dif < 0) positive = false;

		if (number.size() > 1) {
			do {
				it1 = number.end() - 1;
				if (*it1 == 0) number.pop_back();
				else break;
			} while (number.size() > 1);
		}

		return *this;
	}

	Bigint &Bigint::operator--() {
		*this -= 1;
		return *this;
	}

	Bigint Bigint::operator--(int) {
		auto temp(*this);
		--*this;
		return temp;
	}

	Bigint operator-(long long const &b, Bigint c) {
		return (Bigint(b) -= c);
	}

	//Multiplication
	Bigint Bigint::operator*(Bigint const &b) const {
		std::vector<int>::const_iterator it1;
		std::vector<int>::const_iterator it2;
		Bigint c;
		for (it1 = number.begin(); it1 != number.end(); ++it1) {
			for (it2 = b.number.begin(); it2 != b.number.end(); ++it2) {
				c.skip = (unsigned int)(it1 - number.begin()) + (it2 - b.number.begin());
				c += (long long)(*it1) * (*it2);
			}
		}
		c.skip = 0;

		return c;
	}

	Bigint &Bigint::operator*=(Bigint const &b) {
		*this = *this * b;

		return *this;
	}

	Bigint Bigint::operator*(long long const &b) const {
		Bigint c = *this;
		c *= Bigint(b);

		return c;
	}

	Bigint &Bigint::operator*=(int const &b) {
		std::vector<int>::iterator it = number.begin();
		long long sum = 0;
		while (it != number.end()) {
			sum += (long long)(*it) * b;
			*it = (int)(sum % base);
			sum /= base;
			++it;
		}
		if (sum) number.push_back((int)sum);

		return *this;
	}

	Bigint Bigint::operator/(int const &b) const {
		Bigint c = *this;
		c /= b;

		return c;
	}

	Bigint & Bigint::operator/=(int const &b) {
		long long dif = 0;
		for (auto it1 = number.rbegin(); it1 != number.rend(); ++it1) {
			dif *= base;
			dif += *it1;
			*it1 = (int)(dif / b);
			dif = dif % b;
		}

		if (number.size() > 1) {
			do {
				auto && it1 = number.end() - 1;
				if (*it1 == 0) number.pop_back();
				else break;
			} while (number.size() > 1);
		}

		return *this;
	}

	Bigint Bigint::operator/(Bigint const & b) const {

		// TODO
		return Bigint();
	}

	Bigint & Bigint::operator/=(Bigint const & b) {

		// TODO
		return *this;
	}

	Bigint Bigint::operator%(int const & b) const {
		Bigint c = *this;
		c %= b;

		return c;
	}

	Bigint & Bigint::operator%=(int const & b) {
		long long dif = 0;
		for (auto it1 = number.rbegin(); it1 != number.rend(); ++it1) {
			dif *= base;
			dif += *it1;
			*it1 = (int)(dif / b);
			dif = dif % b;
		}
		number.clear();
		skip = 0;
		number.push_back((int)dif);
		return *this;
	}

	Bigint Bigint::operator%(Bigint const & b) const {

		// TODO
		return Bigint();
	}

	Bigint & Bigint::operator%=(Bigint const & b) {

		// TODO
		return *this;
	}

	//Left Shift
	Bigint Bigint::operator<<(unsigned int const & b) const {
		return *this / (2_Bigint).pow(b);
	}

	Bigint & Bigint::operator<<=(unsigned int const & b) {
		return *this /= (2_Bigint).pow(b);
	}

	//Right Shift
	Bigint Bigint::operator>>(unsigned int const & b) const {
		return *this * (2_Bigint).pow(b);
	}

	Bigint & Bigint::operator>>=(unsigned int const & b) {
		return *this *= (2_Bigint).pow(b);
	}

	Bigint operator*(long long const &b, Bigint c) {
		return c * Bigint(b);
	}

	//Power
	/*
	Bigint Bigint::pow(int const &power, std::map<int, Bigint> &lookup) {
		if (power == 1) return *this;
		if (lookup.count(power)) return lookup[power];

		int closestPower = 1;
		while (closestPower < power) closestPower <<= 1;
		closestPower >>= 1;

		if (power == closestPower) {

		}
		else lookup[power] = pow(closestPower, lookup) * pow(power - closestPower, lookup);

		return lookup[power];
	}

	Bigint &Bigint::pow(int power) {
		std::map<int, Bigint> lookup;
		if (power % 2 == 0 && !positive) {
			positive = true;
		}
		*this = pow(power, lookup);

		return *this;
	}
	*/

	Bigint &Bigint::pow(unsigned int power) {
		if (power % 2 == 0 && !positive) {
			positive = true;
		}
		if (power == 0) {
			*this = 1;
		}
		const int bits = 8 * sizeof(int);
		std::bitset<bits> p(power);
		int maxbit = 0;
		for (int i = bits - 1; i >= 0; i--) {
			if (p[i]) {
				maxbit = i;
				break;
			}
		}
		++maxbit;

		std::vector<Bigint> lookup;
		lookup.resize(maxbit);
		lookup[0] = *this;

		for (int i = 1; i < maxbit; i++) {
			auto && temp = lookup[i - 1];
			lookup[i] = temp * temp;
		}

		*this = lookup[--maxbit];
		for (int i = maxbit - 1; i >= 0; i--) {
			if (p[i]) *this *= lookup[i];
		}

		return *this;
	}
	Bigint &Bigint::pow(unsigned long long power) {
		if (power % 2 == 0 && !positive) {
			positive = true;
		}
		if (power == 0) {
			*this = 1;
		}
		const int bits = 8 * sizeof(long long);
		std::bitset<bits> p(power);
		int maxbit = 0;
		for (int i = bits - 1; i >= 0; i--) {
			if (p[i]) {
				maxbit = i;
				break;
			}
		}
		++maxbit;

		std::vector<Bigint> lookup;
		lookup.resize(maxbit);
		lookup[0] = *this;

		for (int i = 1; i < maxbit; i++) {
			auto && temp = lookup[i - 1];
			lookup[i] = temp * temp;
		}

		*this = lookup[--maxbit];
		for (int i = maxbit - 1; i >= 0; i--) {
			if (p[i]) *this *= lookup[i];
		}

		return *this;
	}
	Bigint pow(Bigint a, unsigned int power) {
		if (power % 2 == 0 && !a.positive) {
			a.positive = true;
		}
		if (power == 0) {
			return 1;
		}
		const int bits = 8 * sizeof(int);
		std::bitset<bits> p(power);
		int maxbit = 0;
		for (int i = bits - 1; i >= 0; i--) {
			if (p[i]) {
				maxbit = i;
				break;
			}
		}
		++maxbit;

		std::vector<Bigint> lookup;
		lookup.resize(maxbit);
		lookup[0] = a;

		for (int i = 1; i < maxbit; i++) {
			auto && temp = lookup[i - 1];
			lookup[i] = temp * temp;
		}

		Bigint result(lookup[--maxbit]);
		for (int i = maxbit - 1; i >= 0; i--) {
			if (p[i]) result *= lookup[i];
		}

		return result;
	}
	Bigint pow(Bigint a, unsigned long long power) {
		if (power % 2 == 0 && !a.positive) {
			a.positive = true;
		}
		if (power == 0) {
			return 1;
		}
		const int bits = 8 * sizeof(long long);
		std::bitset<bits> p(power);
		int maxbit = 0;
		for (int i = bits - 1; i >= 0; i--) {
			if (p[i]) {
				maxbit = i;
				break;
			}
		}
		++maxbit;

		std::vector<Bigint> lookup;
		lookup.resize(maxbit);
		lookup[0] = a;

		for (int i = 1; i < maxbit; i++) {
			auto && temp = lookup[i - 1];
			lookup[i] = temp * temp;
		}

		Bigint result(lookup[--maxbit]);
		for (int i = maxbit - 1; i >= 0; i--) {
			if (p[i]) result *= lookup[i];
		}

		return result;
	}

	//Compare
	int Bigint::compare(const Bigint &a) const //0 this == a || -1 this < a || 1 this > a
	{
		if (positive && !a.positive) return 1;
		if (!positive && a.positive) return -1;

		int check = 1;
		if (!positive && !a.positive) check = -1;

		if (number.size() < a.number.size()) return -1 * check;
		if (number.size() > a.number.size()) return check;
		for (size_t i(number.size()); i > 0; --i) {
			if (number[i - 1] < a.number[i - 1]) return -1 * check;
			if (number[i - 1] > a.number[i - 1]) return check;
		}

		return 0; // ==
	}

	bool Bigint::operator<(Bigint const &b) const {
		return compare(b) == -1;
	}

	bool Bigint::operator<=(const Bigint &b) const {
		int compared = compare(b);

		return compared == 0 || compared == -1;
	}

	bool Bigint::operator>(const Bigint &b) const {
		return compare(b) == 1;
	}

	bool Bigint::operator>=(const Bigint &b) const {
		int compared = compare(b);

		return compared == 0 || compared == 1;
	}

	bool Bigint::operator==(Bigint const &b) const {
		return compare(b) == 0;
	}

	bool Bigint::operator!=(Bigint const &b) const {
		return !(*this == b);
	}

	//Allocation
	Bigint Bigint::operator=(const long long &a) {
		number.clear();
		long long t = a;
		do {
			number.push_back((int)(t % base));
			t /= base;
		} while (t != 0);

		return *this;
	}

	Bigint Bigint::operator=(const Bigint & b) {
		number = b.number;
		positive = b.positive;
		base = b.base;
		skip = b.skip;
		return *this;
	}

	Bigint Bigint::operator=(const Bigint && b) {
		number = b.number;
		positive = b.positive;
		base = b.base;
		skip = b.skip;
		return *this;
	}

	//Access
	int Bigint::operator[](int const &b) {
		if (positive)
			return to_string(*this)[b] - '0';
		else
			return to_string(*this)[b + 1] - '0';
	}

	int Bigint::at(int const &b) {
		if (positive)
			return to_string(*this).at(b) - '0';
		else
			return to_string(*this).at(b + 1) - '0';
	}

	size_t Bigint::size() const {
		auto && s = number.size();
		if (s == 0)return 0;
		--s;
		return (s * default_base_bit) + segment_length(number.at(s));
	}

	size_t Bigint::length() const {
		auto && s = number.size();
		if (s == 0)return 0;
		--s;
		return (s * default_base_bit) + segment_length(number.at(s));
	}

	bool Bigint::isNegative() {
		return !positive;
	}

	bool Bigint::isPositive() {
		return positive;
	}

	//Factorial
	Bigint & Bigint::fact() {
		for (Bigint i = *this - 1; i > 1; --i) {
			*this *= i;
		}
		return *this;
	}

	Bigint fact(Bigint b) {
		for (Bigint i = b - 1; i > 1; --i) {
			b *= i;
		}
		return b;
	}

	//Trivia
	int Bigint::digits() const {
		int segments = number.size();

		if (segments == 0) return 0;

		int digits = 9 * (segments - 1);
		digits += segment_length(number.back());

		return digits;
	}

	int Bigint::trailing_zeros() const {
		if (number.empty() || (number.size() == 1 && number[0] == 0)) return 1;

		int zeros = 0;
		std::vector<int>::const_iterator it = number.begin();
		if (number.size() > 1) {
			for (; it != number.end() - 1 && *it == 0; ++it) {
				zeros += 9;
			}
		}
		int a = *it;
		while (a % 10 == 0 && a) {
			++zeros;
			a /= 10;
		}

		return zeros;
	}

	int Bigint::toInt() const {
		if (number.size() > 0) {
			return number[0];
		}
		else {
			return 0;
		}
	}

	long long Bigint::toLL() const {
		if (number.size() > 1) {
			return number[1] * default_base + number[0];
		}
		else if (number.size() > 0) {
			return number[0];
		}
		else {
			return 0;
		}
	}
	//Helpers
	void Bigint::clear() {
		number.clear();
		positive = true;
		skip = 0;
	}

	Bigint &Bigint::abs() {
		positive = true;

		return *this;
	}

	//Input&Output
	std::ostream &BigInt::operator<<(std::ostream &out, Bigint const &a) {
		if (!a.number.size()) return out << 0;
		int i = a.number.size() - 1;
		for (; i >= 0 && a.number[i] == 0; --i);

		if (i == -1) return out << 0;
		if (!a.positive) out << '-';

		std::vector<int>::const_reverse_iterator it = a.number.rbegin() + (a.number.size() - i - 1);

		out << *it++;
		for (; it != a.number.rend(); ++it) {
			for (int i(0), len = a.segment_length(*it); i < 9 - len; ++i) out << '0';
			if (*it) out << *it;
		}

		return out;
	}

	std::istream &BigInt::operator>>(std::istream &in, Bigint &a) {
		std::string str;
		in >> str;

		a = str;

		return in;
	}

	int Bigint::segment_length(int segment) const {
		int length = 0;
		while (segment) {
			segment /= 10;
			++length;
		}

		return length;
	}

	Bigint abs(Bigint value) {
		return value.abs();
	}

	std::string to_string(Bigint const &value) {
		std::ostringstream stream;
		stream << value;

		return stream.str();
	}

	Bigint factorial(int n) {
		Bigint result = 1;
		if (n % 2) {
			result = n;
			--n;
		}
		int last = 0;
		for (; n >= 2; n -= 2) {
			result *= n + last;
			last += n;
		}

		return result;
	}

}

