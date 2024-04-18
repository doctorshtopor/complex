#pragma once
#include <iostream>
#include <xkeycheck.h>
using namespace std;

template<typename T>
class cmplx
{
	T re, im;
public:

	cmplx(const T& real = T{}, const T& image = T{}) : re{real}, im{image} {}//базовый конструктор

	cmplx(const cmplx&) = default;//умолчательный конструктор копирования

	template <typename X>
	cmplx(const cmplx<X>& c) : re{ c.real() }, im{ c.image() } {}//шаблонный конструктор копирования

	//По техническим причинам шаблонный конструктор не используется для генерации копирующего конструктора,
	// так что если явное определение для копирующего конструктора отсутствует, то он по умолчанию не появится.
	//Аналогично копирующие присваивания (есть далее в коде), перемещающие конструкторы и перемещающие присваивания 
	// должны определяться как нешаблонные операции
	//или же будут сгенерированы умолчательные версии

	~cmplx() {}//деструктор - не может быть шаблонным 

	cmplx<T> conj() const { return{ re, -im }; }

	double cabs() const { return{ sqrt(re * re + im * im) }; }

	T real() const { return re; }//действительная часть
	void real(T r) { re = r; }

	T image() const { return im; }//мнимая часть 
	void image(T i) { im = i; }

	//операторы 

	friend bool operator!= <>(const cmplx& lhs, const cmplx& rhs);

	friend bool operator== <>(const cmplx& lhs, const cmplx& rhs);

	friend bool operator>= <>(const cmplx& lhs, const cmplx& rhs);

	friend bool operator<= <>(const cmplx& lhs, const cmplx& rhs);

	friend bool operator> <>(const cmplx& lhs, const cmplx& rhs);

	friend bool operator< <>(const cmplx& lhs, const cmplx& rhs);

	cmplx<T>& operator=(const cmplx<T>& c) { re = c.re; im = c.im; return *this; }//умолчательный оператор присваивания

	template <typename X>
	cmplx<T>& operator=(const cmplx<X>& c) { re = c.real(); im = c.image(); return *this; }//шаблонный оператор присваивания 

	cmplx<T>& operator=(const T& c) { re = c; im = 0; return *this; }//оператор присваивания для прочих типов 

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