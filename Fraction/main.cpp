#include<iostream>
using namespace std;

class Fraction;
Fraction operator*(Fraction left, Fraction right);
Fraction operator+(Fraction left, Fraction right);
Fraction operator/(Fraction left, Fraction right);
Fraction operator-(Fraction left, Fraction right);

class Fraction
{
	int integer; //целая часть
	int numenator; // числитель
	int denominator; // знаменатель

public:
	int get_integer()const
	{
		return integer;
	}
	int get_numenator()const
	{
		return numenator;
	}
	int get_denominator()const
	{
		return denominator;
	}
	void set_integer(int integer)
	{
		this->integer = integer;
	}
	void set_numenator(int numenator)
	{
		this->numenator = numenator;
	}
	void set_denominator(int denomenator)
	{
		if (denomenator == 0)denomenator = 1;
		this->denominator = denomenator;
	}

	//    constructors
	Fraction()
	{
		integer = numenator = 0;
		denominator = 1;
		cout << "DefaultConstructor:\t" << this << endl;
	}
	Fraction(int integer)
	{
		this->integer = integer;
		this->numenator = 0;
		this->denominator= 1;
		cout << "1argConstructor:\t" << this << endl;
	}
	Fraction(int numenator,  int denominator)
	{
		this->integer = 0;
		this->numenator = numenator;
		set_denominator(denominator);
		cout << "Constructor:\t\t" << this << endl;
	}

	Fraction(int integer, int numenator, int denominator)
	{
		this->integer = integer;
		this->numenator = numenator;
		set_denominator(denominator);  //когда нужна фильтрация данных, даже внутри класса лучше использовать set методы
		cout << "Constructor:\t\t" << this << endl;
	}

	Fraction(const Fraction& other)
	{
		this->integer = other.integer;
		this->numenator = other.numenator;
		this->denominator = other.denominator;
		cout << "CopyConstructor:\t" << this << endl;
	}

	~Fraction()
	{
		cout << "Destructor:\t\t" << this << endl;
	}

	// Operators
	Fraction& operator=(const Fraction& other)
	{
		this->integer = other.integer;
		this->numenator = other.numenator;
		this->denominator = other.denominator;
		cout << "CopyAssigment:\t\t" << this << endl;
		return *this;
	}

	Fraction& operator+=(const Fraction& other)
	{
		//this->integer += other.get_integer();
		//this->numenator += other.get_numenator();
		//this->denominator += other.get_denominator();
		return *this=*this+other;
	}
	Fraction& operator-=(const Fraction& other)
	{
		//this->integer += other.get_integer();
		//this->numenator += other.get_numenator();
		//this->denominator += other.get_denominator();
		return *this=*this-other;
	}
	Fraction& operator*=(const Fraction& other)
	{
		//this->integer *= other.get_integer();
		//this->numenator *= other.get_numenator();
		//this->denominator *= other.get_denominator();
		return *this=*this*other;
	}
	Fraction& operator/=(const Fraction& other)
	{
		//this->integer *= other.get_integer();
		//this->numenator *= other.get_numenator();
		//this->denominator *= other.get_denominator();
		return *this=*this/other;
	}
    //     increment/decrement
	Fraction& operator++()
	{
		integer++;
		return *this;
	}
	Fraction& operator--()
	{
		integer--;
		return *this;
	}

	Fraction operator++(int)
	{
		Fraction old = *this;
		integer++;
		return old;
	}
	Fraction operator--(int)
	{
		Fraction old = *this;
		integer--;
		return old;
	}

	Fraction& operator()(int integer, int numenator, int denominator)
	{
		set_integer(integer);
		set_numenator(numenator);
		set_denominator(denominator);
		return *this;
	}
	

	//     Methods

	Fraction& to_proper()
	{
		//Выделяет из неправильной дроби целую часть
		integer += numenator / denominator;
		numenator %= denominator;
		return *this;
	}
	Fraction& to_improper()
	{
		//целую часть интегрирует в числитель
		numenator += integer * denominator;
		integer = 0;
		return *this;
	}

	Fraction& invers()
	{
		to_improper();
		int buffer = numenator;
		numenator = denominator;
		denominator = buffer;
		return *this;
	}

	void print()const
	{
		if (integer)cout << integer;
		if (numenator)
		{
			if (integer)cout << "(";
			cout << numenator << "/" << denominator;
			if (integer) cout << ")";
		}
		if (integer == 0 && numenator == 0)cout << 0;
		cout << endl;
	}
	friend ostream& operator<<(ostream& os, Fraction& obj);
	friend istream& operator>>(istream& is, Fraction& obj);
};

Fraction operator*(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	//Fraction result(left.get_numenator() * right.get_numenator(), left.get_denominator() * right.get_denominator());
	/*result.set_numenator(left.get_numenator() * right.get_numenator());
	result.set_denominator(left.get_denominator() * right.get_denominator());*/
	//result.to_proper();
	//return result;
	return 
		Fraction
		(
		left.get_numenator() * right.get_numenator(),
		left.get_denominator() * right.get_denominator()
		).to_proper(); //явно вызываем конструктор
	// этот явно вызыванный конструктор, прямо в return создает временный безимянный объект типа Fraction и возвращает его на место вызова
}

Fraction operator/(Fraction left, Fraction right)
{
	//left.to_improper();
	//right.to_improper();
	//return
	//	Fraction
	//	(
	//		left.get_numenator() * right.get_denominator(),
	//		left.get_denominator() * right.get_numenator()
	//	).to_proper();
	return left * right.invers();
}

Fraction operator+(Fraction left, Fraction right)
{
	left.to_proper();
	right.to_proper();
	return Fraction
	(
		left.get_integer() + right.get_integer(),
		left.get_numenator() * right.get_denominator() + right.get_numenator() * left.get_denominator(),
		left.get_denominator() * right.get_denominator()

	).to_proper();
}
Fraction operator-(Fraction left, Fraction right)
{
	return Fraction
	(
		left.get_integer() - right.get_integer(),
		left.get_numenator() * right.get_denominator() - right.get_numenator() * left.get_denominator(),
		left.get_denominator() * right.get_denominator()

	).to_proper();
}

bool operator==(const Fraction left, const Fraction right)
{
	if ((left.get_integer() == right.get_integer()) && (left.get_numenator() == right.get_numenator()) && (left.get_denominator() == right.get_denominator()))
	{
		return true;
	}
	else
		return false;
}
bool operator!=(const Fraction left, const Fraction right)
{
	if ((left.get_integer() != right.get_integer()) || (left.get_numenator() != right.get_numenator()) || (left.get_denominator() != right.get_denominator()))
	{
		return true;
	}
	else
		return false;
}

bool operator>(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	
	if ((left.get_numenator()/left.get_denominator()) > (right.get_numenator()/right.get_denominator()))
	{
		return true;
	}
	else
		return false;
}
bool operator<(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	
	if ((left.get_numenator()/left.get_denominator()) < (right.get_numenator()/right.get_denominator()))
	{
		return true;
	}
	else
		return false;
}
bool operator>=(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	
	if ((left.get_numenator()/left.get_denominator()) >= (right.get_numenator()/right.get_denominator()))
	{
		return true;
	}
	else
		return false;
}
bool operator<=(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	
	if ((left.get_numenator()/left.get_denominator()) <= (right.get_numenator()/right.get_denominator()))
	{
		return true;
	}
	else
		return false;
}

ostream& operator<<(ostream& os, Fraction& obj)
{
	if (obj.integer)cout << obj.integer;
	if (obj.numenator)
	{
		if (obj.integer)cout << "(";
		cout << obj.numenator << "/" << obj.denominator;
		if (obj.integer) cout << ")";
	}
	if (obj.integer == 0 && obj.numenator == 0)cout << 0;
	return os;

}

istream& operator>>(istream& is, Fraction& obj)
{
	is >> obj.integer;
	is >> obj.numenator;
	is >> obj.denominator;

	return is;
}

//#define CONSTRUCTORS_CHECK
#define ARITHMETICAL_OPERATORS_CHECK
void main()
{
	setlocale(LC_ALL, "Russian");
#ifdef CONSTRUCTORS_CHECK
	Fraction A; //default constructor
	A.print();
	Fraction B = 5; //Single-argument constructor
	B.print();
	Fraction C(1, 2);
	C.print();
	Fraction D(2, 3, 4);
	D.print();
	Fraction E = D; //CopyConstructor
	E.print();
	Fraction F;
	F = D;
	F.print();


#endif // CONSTRUCTORS_CHECK
	//Fraction A(23, 3);
	//A.to_proper();
	//A.print();
	//A.to_improper();
	//A.print();



#ifdef ARITHMETICAL_OPERATORS_CHECK

	Fraction A(23, 3);
	A.print();
	Fraction B(8, 4, 5);
	B.print();
	//Fraction C = A * B;
	//C.print();
	//(A / B).print();
	//(A + B).print();
	//(A - B).print();

	//A--;
	//A.print();
	//A /= B;
	//A.print();
	Fraction C(23, 3);
	(C - A).print();
	//A.print();
	//C.print();

	//A.print();
	//A *= B;
	//A.print();
	if (A >= C)
	{
		cout << "верно" << endl;
	}
	else
	{
		cout << "не верно" << endl;
	}

	//cout << A << endl;
#endif // 

	//for (double i = .5; i < 10; i++)
	//{
	//	cout << i << "\t";
	//}
	//cout << endl;
	//for (Fraction A(1, 2); A.get_integer()<10; A++)
	//{
	//	cout << A << "\t";
	//}
	//cout << endl;

	Fraction P;
	//A(7, 2, 3);
	cin >> P;
	cout << P << endl;
}