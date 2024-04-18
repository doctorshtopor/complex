#pragma once
#include <iostream>
#include <xkeycheck.h>
using namespace std;

template<typename T>
class cmplx
{
	T re, im;
public:

	cmplx(const T& real = T{}, const T& image = T{}) : re{real}, im{image} {}//������� �����������

	cmplx(const cmplx&) = default;//������������� ����������� �����������

	template <typename X>
	cmplx(const cmplx<X>& c) : re{ c.real() }, im{ c.image() } {}//��������� ����������� �����������

	//�� ����������� �������� ��������� ����������� �� ������������ ��� ��������� ����������� ������������,
	// ��� ��� ���� ����� ����������� ��� ����������� ������������ �����������, �� �� �� ��������� �� ��������.
	//���������� ���������� ������������ (���� ����� � ����), ������������ ������������ � ������������ ������������ 
	// ������ ������������ ��� ����������� ��������
	//��� �� ����� ������������� ������������� ������

	~cmplx() {}//���������� - �� ����� ���� ��������� 

	cmplx<T> conj() const { return{ re, -im }; }

	double cabs() const { return{ sqrt(re * re + im * im) }; }

	T real() const { return re; }//�������������� �����
	void real(T r) { re = r; }

	T image() const { return im; }//������ ����� 
	void image(T i) { im = i; }

	//��������� 

	friend bool operator!= <>(const cmplx& lhs, const cmplx& rhs);

	friend bool operator== <>(const cmplx& lhs, const cmplx& rhs);

	friend bool operator>= <>(const cmplx& lhs, const cmplx& rhs);

	friend bool operator<= <>(const cmplx& lhs, const cmplx& rhs);

	friend bool operator> <>(const cmplx& lhs, const cmplx& rhs);

	friend bool operator< <>(const cmplx& lhs, const cmplx& rhs);

	cmplx<T>& operator=(const cmplx<T>& c) { re = c.re; im = c.im; return *this; }//������������� �������� ������������

	template <typename X>
	cmplx<T>& operator=(const cmplx<X>& c) { re = c.real(); im = c.image(); return *this; }//��������� �������� ������������ 

	cmplx<T>& operator=(const T& c) { re = c; im = 0; return *this; }//�������� ������������ ��� ������ ����� 

	template <typename X>
	cmplx<T>& operator=(const X& c) { re = c; im = 0; return *this; }

	template <typename X>
	cmplx<T>& operator+=(const X& c) { re += c; im += 0; return *this; }

	template <typename X>
	cmplx<T>& operator+=(const cmplx<X>& c) { re += c.real(); im += c.image(); return *this; }

	template <typename X>
	cmplx<T>& operator-=(const X& c) { re -= c; im += 0; return *this; }

	template <typename X>
	cmplx<T>& operator-=(const cmplx<X>& c) { re -= c.real(); im -= c.image(); return *this; }

	template <typename X>
	cmplx<T>& operator*=(const X& c) { re *= c; im *= c; return *this; }

	template <typename X>
	cmplx<T>& operator*=(const cmplx<X>& c)
	{
		re = re * c.real() - im * c.image();
		im = im * c.real() + re * c.image();
		return *this;
	}

	template <typename X>
	cmplx<T>& operator/=(const X& c) 
	{ 
		if (c != 0) { re /= c; im /= c; return *this; }
		else try
		{
			throw string{"You can't divide by zero:" };
		}
		catch (string error_message)
		{
			cout << error_message << "\ ";
		}
	}

	template <typename X>
	cmplx<T>& operator/=(const cmplx<X>& c)
	{
		if (c.real() != 0 && c.image() != 0)
		{
			re = (re * c.real() - im * c.image()) /
				(c.real() * c.real() + c.image() * c.image());
			im = (im * c.real() - re * c.image()) /
				(c.real() * c.real() + c.image() * c.image());
			return *this;
		}
		else try
		{
			throw string{"You can't divide by zero:" };
		}
		catch (string error_message)
		{
			cout << error_message << "\ ";
		}
	}


	template <typename X>
	cmplx<T> operator+(const cmplx<X>& c) const 
	{
		cmplx<T> result(*this);
		result += c;
		return result;
	}

	template <typename X>
	cmplx<T> operator-(const cmplx<X>& c) const
	{
		cmplx<T> result(*this);
		result -= c;
		return result;
	}

	template <typename X>
	cmplx<T> operator*(const cmplx<X>& c) const
	{
		cmplx<T> result(*this);
		result *= c;
		return result;
	}

	template <typename X>
	cmplx<T> operator/(const cmplx<X>& c) const
	{
		cmplx<T> result(*this);
		result /= c;
		return result;
	}

	template <typename X>
	cmplx<T> operator+(const X& c) const
	{
		cmplx<T> result(*this);
		result += c;
		return result;
	}

	template <typename X>
	cmplx<T> operator-(const X& c) const
	{
		cmplx<T> result(*this);
		result -= c;
		return result;
	}

	template <typename X>
	cmplx<T> operator*(const X& c) const
	{
		cmplx<T> result(*this);
		result *= c;
		return result;
	}

	template <typename X>
	cmplx<T> operator/(const X& c) const
	{
		cmplx<T> result(*this);
		result /= c;
		return result;
	}
	
	friend ostream& operator<< (std::ostream& os, const cmplx <T>& c)
	{
		os << '(' << c.re << ',' << ' ' << c.im << ')';
		return os;
	}
};

template <typename T, typename X>
bool operator==(const cmplx<T>& lhs, const cmplx<X>& rhs)
{
	if (lhs.cabs() == rhs.cabs()) return true;
	else return false;
}

template <typename T, typename X>
bool operator!=(const cmplx<T>& lhs, const cmplx<X>& rhs)
{
	if (lhs.cabs() != rhs.cabs()) return true;
	else return false;
}

template <typename T, typename X>
bool operator<=(const cmplx<T>& lhs, const cmplx<X>& rhs)
{
	if (lhs.cabs() <= rhs.cabs()) return true;
	else return false;
}

template <typename T, typename X>
bool operator>=(const cmplx<T>& lhs, const cmplx<X>& rhs)
{
	if (lhs.cabs() >= rhs.cabs()) return true;
	else return false;
}

template <typename T, typename X>
bool operator>(const cmplx<T>& lhs, const cmplx<X>& rhs)
{
	if (lhs.cabs() > rhs.cabs()) return true;
	else return false;
}

template <typename T, typename X>
bool operator<(const cmplx<T>& lhs, const cmplx<X>& rhs)
{
	if (lhs.cabs() < rhs.cabs()) return true;
	else return false;
}