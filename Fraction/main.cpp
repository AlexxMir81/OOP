//#pragma warning (disable: 4326)
#include<iostream>
using namespace std;
#define tab "\t"
#define delimiter "\n----------------------------------------------\n"

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
	explicit Fraction(int integer)
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
	//     Type-cast operators	
	explicit operator int()const
	{
		return integer;
	}
	operator double()const
	{		
		return integer + (double)numenator/denominator;
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

bool operator==(Fraction left, Fraction right)
{
	return left.to_improper().get_numenator() * right.to_improper().get_denominator() ==
		right.to_improper().get_numenator() * left.to_improper().get_denominator();
	return (double)left == right;
}

bool operator!=(const Fraction& left, const Fraction& right)
{
	return !(left == right);
}

bool operator>(Fraction left, Fraction right)
{
	return 
		left.to_improper().get_numenator() * right.get_denominator() >
		right.to_improper().get_numenator() * left.get_denominator();
}
bool operator<(const Fraction& left, const Fraction& right)
{
	return (double)left < right;
}

bool operator>=(const Fraction& left, const Fraction& right)
{
	return left > right || left == right;
	return!(left < right);
}

bool operator<=(const Fraction& left, const Fraction& right)
{
	return!(left > right);
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
	const int SIZE = 80;
	char sz_buffer[SIZE] = {};
	is.getline(sz_buffer, SIZE);
	char sz_delimiters[] = "/() ";
	char* value[3] = {};
	int n = 0;
	for(char* pch = strtok(sz_buffer, sz_delimiters); pch; pch = strtok(NULL, sz_delimiters))
	{
		value[n++]=pch;
	}
	//for(int i = 0; i < 3; i++)
	//{
	//	cout << values[i] << tab;
	//}
	//cout << endl;
	obj = Fraction();
	switch (n)
	{
	case 1: obj.set_integer(atoi(value[0]));
		break;
	case 2: 
		obj.set_numenator(atoi(value[0]));
		obj.set_denominator(atoi(value[1]));
		break;
	case 3: 
		obj.set_integer(atoi(value[0]));
		obj.set_numenator(atoi(value[1]));
		obj.set_denominator(atoi(value[2]));
		break;
	}
	return is;
}

//#define CONSTRUCTORS_CHECK
//#define ARITHMETICAL_OPERATORS_CHECK
//#define CONVERTIONS_FROM_OTHER_TO_CLASS
//#define CONVERSION_FROM_CLASS_TO_OTHER
//#define CONPARISON_OPERATORS_CHECK

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
	//Fraction C(23, 3);
	//(C - A).print();
	//A.print();
	//C.print();

	//A.print();
	//A *= B;
	//A.print();
	//if (A >= C)
	//{
	//	cout << "верно" << endl;
	//}
	//else
	//{
	//	cout << "не верно" << endl;
	//}

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

	//Fraction P;
	////A(7, 2, 3);
	//cin >> P;
	//cout << P << endl;
#ifdef CONVERTIONS_FROM_OTHER_TO_CLASS



	int a = 2; //no conversions
	double b = 3;  //from less to more
	double c = 2.5; //no conversion
	int d = b; //from more to less whthout data loss
	int e = 4.5; //from more to less with data loss
	Fraction A(5);  //from int to Fracrion (Single-argument constructor
	cout << A << endl;
	Fraction B; //default constructor
	cout << delimiter << endl;
	//B = 8;   // Assigment operator
	B = (Fraction)8; //C-like notation
	B = Fraction(8); //Functional notation (здесь явно вызываем конструктор с 1 параметром)
	// в этом выражении вызывается конструктор с одним параметром и создает 
	// временный безымянный объект для того,
	// чтобы преобразовать 8 во Fraction 
	// Этот временный безымянный объект будет удален по завершении выражения
	cout << delimiter << endl;
	cout << B << endl;
#endif // CONVERTIONS_FROM_OTHER_TO_CLASS
#ifdef CONVERSION_FROM_CLASS_TO_OTHER


	Fraction A(5);
	cout << A << endl;
	int a = (int)A;
	cout << a << endl;

	Fraction B(2, 3, 4);
	cout << B << endl;
	double b = (double)B;
	cout << b << endl;
#endif // CONVERSION_FROM_CLASS_TO_OTHER

#ifdef CONPARISON_OPERATORS_CHECK

	cout << (Fraction(2,1, 2) < Fraction(2, 5, 11)) << endl;
#endif // CONPARISON_OPERATORS_CHECK

	Fraction A(22, 33, 55);
	cout << "Введите дробь: "; 
	cin >> A;
	cout << A << endl;

}