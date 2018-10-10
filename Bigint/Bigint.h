#ifndef DODECAHEDRON_BIGINT_H_
#define DODECAHEDRON_BIGINT_H_

#include <vector>
#include <iostream>
#include <map>


class Bigint {
private:
	std::vector<int> number;
	bool positive;
	int base;
	unsigned int skip;
	static const int default_base = 1000000000;
	static const int default_base_bit = 9;
public:
	//Constructors
	Bigint();
	Bigint(long long);
	Bigint(std::string);
	Bigint(const Bigint& b);

	//Adding
	Bigint operator+(Bigint const &) const;
	Bigint &operator+=(Bigint const &);
	Bigint operator+(long long const &) const;
	Bigint &operator+=(long long);
	Bigint &operator++();
	Bigint operator++(int);

	//Subtraction
	Bigint operator-(Bigint const &) const;
	Bigint &operator-=(Bigint const &);
	Bigint &operator--();
	Bigint operator--(int);

	//Multiplication
	Bigint operator*(Bigint const &) const;
	Bigint &operator*=(Bigint const &);
	Bigint operator*(long long const &) const;
	Bigint &operator*=(int const &);

	//Division
	Bigint operator/(int const &) const;
	Bigint &operator/=(int const &);
	Bigint operator/(Bigint const &) const;
	Bigint &operator/=(Bigint const &);

	//Modulus
	Bigint operator%(int const &) const;
	Bigint &operator%=(int const &);
	Bigint operator%(Bigint const &) const;
	Bigint &operator%=(Bigint const &);


	//Compare
	bool operator<(const Bigint &) const;
	bool operator>(const Bigint &) const;
	bool operator<=(const Bigint &) const;
	bool operator>=(const Bigint &) const;
	bool operator==(const Bigint &) const;
	bool operator!=(const Bigint &) const;

	//Allocation
	Bigint operator=(const long long &);

	//Access
	int operator[](int const &);
	int at(int const &);
	size_t size();
	size_t length();
	bool isNegative();
	bool isPositive();

	//Input&Output
	friend std::istream &operator>>(std::istream &, Bigint &);
	friend std::ostream &operator<<(std::ostream &, Bigint const &);

	//Helpers
	void clear();
	Bigint &abs();

	//Power
	Bigint &pow(int const &);

	//Trivia
	int digits() const;
	int trailing_zeros() const;

	int toInt() const;
private:
	int segment_length(int) const;
	Bigint pow(int const &, std::map<int, Bigint> &);
	int compare(Bigint const &) const; //0 a == b, -1 a < b, 1 a > b
};

Bigint abs(Bigint);
std::string to_string(Bigint const &);
Bigint factorial(int);
Bigint operator+(long long const & b, Bigint c);
Bigint operator-(long long const & b, Bigint c);
Bigint operator*(long long const & b, Bigint c);


#endif
