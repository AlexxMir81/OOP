#include<iostream>
using namespace std;

#define tab "\t"


//создание структуры
class Point
{
	double x;
	double y;
public:
	double get_x()const
	{
		return x;
	}
	double get_y()const
	{
		return y;
	}
	void set_x(double x)
	{
		this->x = x;
	}
	void set_y(double y)
	{
		this->y = y;
	}

	//        Constructors:
	/*Point()
	{
		x = y = 0;
		cout << "DefaultConstructor:\t" << this << endl;
	}*/
	Point(double x=0, double y=0)
	{
		this->x = x;
		this->y = y;
		cout << "Constructor:\t" << this << endl;
	}
	Point(const Point& other)
	{
		this->x = other.x;
		this->y = other.y;
		cout << "CopyConstructor:\t" << this << endl;
	}
	~Point()
	{
		cout << "Destructor:\t\t" << this << endl;
	}

	//        Methods:
	double distance(Point& other)const
	{
		double x_distance = this->x - other.x;
		double y_distance = this->y - other.y;
		double distance = sqrt(x_distance * x_distance + y_distance * y_distance);
		return distance;
	}

	void print() const
	{
		cout << "X=" << x << "\t" << "Y=" << y << endl;
	}
};


double distance(const Point& A,const Point& B);
//#define STRUCT_POINT
#define DISTANCE
//#define CONSTRUCTORS_CHECK
void main()
{
	setlocale(LC_ALL, "Russian");
#ifdef STRUCT_POINT

	Point A;  //создание объекта А структуры Point/ создание экземляра структуры Point
	A.x = 2;
	A.y = 3;
	cout << A.x << tab << A.y << endl;

	Point* pA = &A;
	cout << pA->x << tab << pA->y << endl;
	cout << (*pA).x << tab << (*pA).y << endl;
#endif

#ifdef DISTANCE

	Point A;
	A.set_x(2);
	A.set_y(3);

	cout << A.get_x() << "\t" << A.get_y() << endl;

	Point B;
	B.set_x(4);
	B.set_y(5);
	cout << "\n------------------------\n";
	cout << B.distance(A) << endl;
	cout << "\n------------------------\n";
	cout << A.distance(B) << endl;
	cout << "\n------------------------\n";
	cout << distance(A, B) << endl;
	cout << "\n------------------------\n";
	cout << distance(B, A) << endl;
#endif 

#ifdef CONSTRUCTORS_CHECK
	Point A;   //Default constuctor
	A.print();
	Point B(2,3);
	B.print();
	Point C = B;   //Copy constuctor
	C.print();
#endif // constructors_check
}

double distance(const Point& A, const Point& B)
{
	//double x_dist = A.get_x() - B.get_x();
	//double y_dist = A.get_y() - B.get_y();
	//return sqrt(pow(A.get_x() - B.get_x(),2) + pow(A.get_y() - B.get_y(),2));	
	return pow(pow(A.get_x() - B.get_x(),2) + pow(A.get_y() - B.get_y(),2),.5);

}