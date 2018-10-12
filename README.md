# <center>Bigint</center><br />

* [Introduction](#Introduction)
* [Operators](#Operators)
  * [Negative](#Negative)(`-`)
  * [Addition](#Addition)(`+`,`+=`,`++`)
  * [Subtraction](#Subtraction)(`-`,`-=`,`--`)
  * [Multiplication](#Multiplication)(`*`,`*=`)
  * [Division](#Division)(`/`,`/=`)
  * [Modulus](#Modulus)(`%`,`%=`)
  * [Left Shift](#LeftShift)(`<<`,`<<=`)
  * [Right Shift](#RightShift)(`>>`,`>>=`)
  * [Allocation](#Allocation)(`=`)
  * [Comparison](#Comparison)(`<`,`<=`,`>`,`>=`,`!=`,`==`)
  * [Access](#Access)(`[]`)
  * [Streaming operators](#Streamingoperators)(`<<`,`>>`)
  * [Literal operators](#Literaloperators)(`_Bigint`)
* [Methods](#Methods)
  * [Constructors](#Constructors)
  * [abs](#abs)
  * [at](#at)
  * [clear](#clear)
  * [digits](#digits)
  * [fact](#fact)
  * [size](#size)
  * [length](#length)
  * [isNegative](#isNegative)
  * [isPositive](#isPositive)
  * [pow](#pow)
  * [toInt](#toInt)
  * [toLL](#toLL)
  * [trailing_zeros](#trailing_zeros)
* [Functions](#Functions)
  * [abs](#abs)
  * [pow](#pow)
  * [to_string](#to_string)
  * [fact](#fact)
  * [factorial](#factorial)

<a id="Introduction"></a>
## Introduction
Bigint class provides math operations for arbitrarily large numbers. You know the limit is reached when your computer freezes.

<a id="Operators"></a>
## Operators

<a id="Negative"></a>
### Negative
```
BigInt::Bigint a,b;
b = -a;
```

<a id="Addition"></a>
### Addition
```
BigInt::Bigint a,b,c;
c = a + b;
c += a;
c = a + 6;
c += 6;
```

<a id="Subtraction"></a>
### Subtraction
```
BigInt::Bigint a,b,c;
c = a - b;
c -= a;
```

<a id="Multiplication"></a>
### Multiplication
```
Dodecahedron::Bigint a,b,c;
c = a * b;
c *= a;
c = a * 6;
c *= 6;
```

<a id="Division"></a>
### Division
```
Dodecahedron::Bigint a,b,c;
c = a / b;
c /= a;
c = a / 6;
c /= 6;
```

<a id="Modulus"></a>
### Modulus
```
Dodecahedron::Bigint a,b,c;
c = a % b;
c %= a;
c = a % 6;
c %= 6;
```

<a id="LeftShift"></a>
### Left Shift
```
Dodecahedron::Bigint a,b;
b = a << 3;
b <<= 4;
```

<a id="RightShift"></a>
### Right Shift
```
Dodecahedron::Bigint a,b;
b = a >> 3;
b >>= 4;
```

<a id="Allocation"></a>
### Allocation
```
Dodecahedron::Bigint a = 12345;
Dodecahedron::Bigint b;
b = 159753;
```

<a id="Comparison"></a>
### Comparison
```
Dodecahedron::Bigint a = 159753;
Dodecahedron::Bigint b = 1634687496;

if(a == b) cout << "A is the same as B";
if(a < b) cout << "A is less than B";
if(a > b) cout << "A is larger than B";
if(a >= b) cout << "A is larger than B or equal to it";
if(a <= b) cout << "A is smaller than B or equal to it";
```

<a id="Access"></a>
### Access
```
Dodecahedron::Bigint a = 159753;
a.pow(15); //a^15, 1126510743106482...
cout << a[3]; // 6 is the 4th digit
```

<a id="Streamingoperators"></a>
### Streaming operators
```
Dodecahedron::Bigint a,b;
cin >> a >> b;
cout << a*b;
```

<a id="Literaloperators"></a>
### Literal operators
```
cout << "4558"_Bigint .pow(486);  // ~1.46 * 10^1778
cout << 4558_Bigint .pow(486);  // ~1.46 * 10^1778
cout << 4.558e3_Bigint .pow(486);  // ~1.46 * 10^1778
// Remember to write a space after _Bigint
```


<a id="Methods"></a>
## Methods

<a id="Constructors"></a>
### Constructors() +9
```
Dodecahedron::Bigint a0(); //void
Dodecahedron::Bigint a1(Dodecahedron::Bigint(1)); //Right value
Dodecahedron::Bigint a2(a1); //Left value
Dodecahedron::Bigint a3(1); //int
Dodecahedron::Bigint a4(4558LL); //long long
Dodecahedron::Bigint a5(4558e123); //double
Dodecahedron::Bigint a6(4.558f); //float
Dodecahedron::Bigint a7("4558"); //string
```

<a id="abs"></a>
### abs()
Absolute value.
```
Dodecahedron::Bigint a = -4558;
cout << a.abs() // 4558
```

<a id="at"></a>
### at(int)
return the nth digit
```
Dodecahedron::Bigint a = 159753;
a.pow(15); //a^15, 1126510743106482...
cout << a.at(3); // 6 is the 4th digit
```

<a id="clear"></a>
### clear()
Clears the Dodecahedron::Bigint, essentially making it equal to 0.
```
Dodecahedron::Bigint a = 4558;
cout << a.pow(486);  // ~1.46 * 10^1778
a.clear();
cout << a; //0
```

<a id="digits"></a>
### digits()
Returns the number of digits.
```
Dodecahedron::Bigint a = 4558;
cout << a.pow(486).digits(); // 4558^486 = 1779 digit number
```

<a id="fact"></a>
### fact()
factorial of an integer, aka n!
```
Bignum a(20000)
cout << a.fact(); //70`000+ digit number

```

<a id="size"></a>
### size()
Return the number of digits
```
Dodecahedron::Bigint a = 4558;
cout << a.pow(486).digits(); // 4558^486 = 1779 digit number
```

<a id="length"></a>
### length()
Return the number of digits
```
Dodecahedron::Bigint a = 4558;
cout << a.pow(486).digits(); // 4558^486 = 1779 digit number
```

<a id="isNegative"></a>
### isNegative()
```
Dodecahedron::Bigint a = -4558;
Dodecahedron::Bigint b = 4558;
if(a.isNegative()) cout << "A is Negative";
if(b.isNegative()) cout << "B is Negative";
```

<a id="isPositive"></a>
### isPositive()
```
Dodecahedron::Bigint a = -4558;
Dodecahedron::Bigint b = 4558;
if(a.isPositive()) cout << "A is Positive";
if(b.isPositive()) cout << "B is Positive";
```

<a id="pow"></a>
### pow(int) +1
Raises to the power of N.
```
Dodecahedron::Bigint a = 4558;
cout << a.pow(486); // ~1.46 * 10^1778
```

<a id="toInt"></a>
### toInt()
Returns this number if it smalll than 1000000000
```
Dodecahedron::Bigint a = 4558;
cout << a.pow(486).toInt(); // 618886144

```

<a id="toLL"></a>
### toLL()
Returns this number if it smalll than 1000000000000000000
```
Dodecahedron::Bigint a = 4558;
cout << a.pow(486).toInt(); // 834145742618886144
```

<a id="trailing_zeros"></a>
### trailing_zeros()
Returns the number of trailing zeros.
```
Dodecahedron::Bigint a = 4558;
a.pow(486);
cout << a.trailing_zeros(); //972
```



<a id="Functions"></a>
## Functions

<a id="abs"></a>
### abs(Bignum)
Same as abs, but returns a new instance;
```
Dodecahedron::Bigint a = -455897864531248;
cout << abs(a) // 455897864531248
```

<a id="pow"></a>
### pow(Bignum, int) +1
Same as pow, but returns a new instance;
```
Dodecahedron::Bigint a = 4558;
cout << pow(a, 486); // ~1.46 * 10^1778
```

<a id="to_string"></a>
### to_string(Bignum)
Converts the big integer to a string.
```
string str;
Dodecahedron::Bigint a = 455897864531248;
str = to_string(a);
```

<a id="fact"></a>
### fact(Bignum)
Returns a factorial of an integer, aka n!
```
cout << Dodecahedron::factorial(Bignum(20000)); //70`000+ digit number
```

<a id="factorial"></a>
### factorial(int)
Returns a factorial of an integer, aka n!
```
cout << Dodecahedron::factorial(20000); //70`000+ digit number
```


