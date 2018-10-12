#ifndef DODECAHEDRON_BIGINT_H_
#define DODECAHEDRON_BIGINT_H_

#include <vector>
#include <iostream>
#include <map>

namespace BigInt {

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
		Bigint(unsigned long long);
		Bigint(long long);
		Bigint(long double);
		Bigint(double);
		Bigint(float);
		Bigint(int);
		Bigint(std::string);
		Bigint(const Bigint &);
		Bigint(const Bigint &&);

		//Literal operator
		friend Bigint operator "" _Bigint(const char *);
		friend Bigint operator "" _Bigint(const unsigned long long);
		friend Bigint operator "" _Bigint(const long double);

		//Negative
		Bigint &operator-();

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

		//Left Shift
		Bigint operator<<(int const &) const;
		Bigint & operator<<=(int const &);

		//Right Shift
		Bigint operator>>(int const &) const;
		Bigint & operator>>=(int const &);

		//Compare
		bool operator<(const Bigint &) const;
		bool operator>(const Bigint &) const;
		bool operator<=(const Bigint &) const;
		bool operator>=(const Bigint &) const;
		bool operator==(const Bigint &) const;
		bool operator!=(const Bigint &) const;

		//Allocation
		Bigint operator=(const long long &);
		Bigint operator=(const Bigint &);
		Bigint operator=(const Bigint &&);

		//Access
		int operator[](int const &);
		int at(int const &);
		bool isNegative();
		bool isPositive();

		//Input&Output
		friend std::istream &operator>>(std::istream &, Bigint &);
		friend std::ostream &operator<<(std::ostream &, Bigint const &);

		//Helpers
		void clear();
		Bigint &abs();

		//Power
		Bigint &pow(int);
		Bigint &pow(long long);
		friend Bigint pow(Bigint, int);
		friend Bigint pow(Bigint, long long);

		//Factorial
		Bigint &fact();
		friend Bigint fact(Bigint);

		//Trivia
		int digits() const;
		size_t size() const;
		size_t length() const;
		int trailing_zeros() const;

		int toInt() const;
		long long toLL() const;
	private:
		int segment_length(int) const;
		// Bigint pow(int const &, std::map<int, Bigint> &);
		int compare(Bigint const &) const; //0 a == b, -1 a < b, 1 a > b
	};

	Bigint operator "" _Bigint(const char *);
	Bigint operator "" _Bigint(const unsigned long long);
	Bigint operator "" _Bigint(const long double);
	std::istream &operator>>(std::istream &, Bigint &);
	std::ostream &operator<<(std::ostream &, Bigint const &);
	Bigint pow(Bigint, int);
	Bigint pow(Bigint, long long);
	Bigint fact(Bigint);
	Bigint abs(Bigint);
	std::string to_string(Bigint const &);
	Bigint factorial(int);
	Bigint operator+(long long const &, Bigint);
	Bigint operator-(long long const &, Bigint);
	Bigint operator*(long long const &, Bigint);
	

}

#endif
