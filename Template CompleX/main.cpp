#define _SILENCE_NONFLOATING_COMPLEX_DEPRECATION_WARNING
#include <iostream>
#include "cmplx.h"
#include <complex>
#include <random>
#include <functional>

using namespace std;


class rand_d//класс случайных чисел
{
public:
	rand_d()
	{
		random_device system_rand;
		int seed = system_rand();
		srand(seed);
	}
	int randomInt() { return rand(); }

	int randomInt(int a, int b)
	{
		if (a > b)
			return randomInt(b, a);
		if (a == b)
			return a;
		return a + (rand() % (b - a));
	}

	double randomDouble()
	{
		return (double)(rand()) / (double)(RAND_MAX);
	}

	double Rand_double(int a, int b)
	{
		if (a > b)
			return Rand_double(b, a);
		if (a == b)
			return a;

		return (double)randomInt(a, b) + randomDouble();
	}
};


template <class T, size_t N>
constexpr size_t arr_length(cmplx<T> (&)[N]) 
{
	return N;
}


template<typename X, size_t N>
auto fillrca(cmplx<X> (&s)[N])//заполнение массива случайными комплексными числами
{
	rand_d r;
	for (size_t i = 0; i < N; i++)
	{
		s[i].real(r.Rand_double(0, 1));
		s[i].image(r.Rand_double(0, 1));
	}
}

template<typename X, size_t N>
auto fillrca(X (&s)[N])
{
	rand_d r;
	for (size_t i = 0; i < N; i++)
	{
		s[i]=(r.Rand_double(0, 1));
	}
}

template<typename X, size_t N>
void proprint(cmplx<X>(&s)[N], ostream& o = cout)
{
	for (size_t i = 0; i <= N - 1; i++)
	{
		o << i+1 << ". " << s[i] << "  abs = " << s[i].cabs() << "\n";
	}
	o << "\n";
	
}

template<typename X, size_t N>
void caprint(cmplx<X> (&s)[N], ostream& o = cout)//обычный вывод массива
{
	o << "{";
	for (size_t i = 0; i < N-1; i++)
	{
		o << s[i] << ", ";
	}
	o << s[N-1] << "}\n";
}

template<typename X, size_t N>
void caprint(X (&s)[N], ostream& o = cout)
{
	o << "{";
	for (size_t i = 0; i < N - 1; i++)
	{
		o << s[i] << ", ";
	}
	o << s[N - 1] << "}\n";
}

//сортировка
template <typename X, int M>
auto csort(cmplx<X> (&s)[M])
{
	size_t M1 = M;
	while(M1--)
	{
		bool swapped = false;
		for (size_t K = 0; K < M-1; K++)
		{
			if (s[K + 1] > s[K])
			{
				swap(s[K], s[K + 1]);
				swapped = true;
			}
		}
		if (swapped == false) break;
	}
	return s;
}

int main()
{ 
	setlocale(LC_ALL, "Russian");
	
	
	//демонстрация того к чему мы стремимся
	complex <float> a (5.6, 8.2);
	complex <int> b (4, 1);
	complex<double> A(6.234, 9.11);
	b /= a;
	cout << a<<endl;

	cout << "демонстрация окончена" << endl;

	//демонстрация шаблонного класса

	cmplx<double> f;
	cout << f << endl;

	cmplx<double> F {5, 2}, K{7, 12};
	K += F;
	cout << K << endl;
	
	cmplx<float> cf{5, 2};
	cmplx<double> cd;
	cmplx<double> dc{16, 4};
	cd = dc;
	cout << cd << endl;
	//cd += 5.34;
	cout << cd << endl;
	cf = cd;
	cout << cf << endl;

	cmplx<float> ls{19.86, 5.71};
	cmplx<double> kd{ls};
	cout << kd << endl;
	cout << kd.cabs() << endl;
	cout << kd.conj() << endl;
	cmplx<double> jj{5.43872, 7.123};
	jj += ls;
	cout << jj << endl;
	jj *= ls;
	cout << jj << endl;

	cout << jj << endl;

	cmplx<double> yy;
	yy = jj + ls;
	cout << yy << endl << jj << endl;
	yy = jj + yy;
	cout << yy << endl;

	yy = yy * 2;
	cout << yy << endl;

	cmplx<int> qq{8, 3};
	cmplx<double> uu(7.52, 1.34);
	cmplx<float> pp;
	pp = uu + qq;
	cout << pp << endl;
	pp = qq/uu;
	cout << pp << endl;
	cmplx <double> o;
	pp = pp / o;
	cout << pp << endl;
	pp = pp / 0;
	cout << pp << endl;
	
	
	cmplx<char> Q1;
	cmplx<char> Q2;

	cmplx<string> AA{"lol", "uwu"};
	cmplx<string> B{"another one", "keks"};
	cmplx<string> l;

	l = AA+B;
	cout << l << endl;
	cout << (Q1 == Q2) << endl;
	cout << (Q1 != Q2) << endl;

	cmplx<double> Q3{5.12, 7.89};
	cmplx<double> Q4;

	cout << (Q3 >= Q4) << endl;

	cout << (Q3 <= Q4) << endl;

	


	//случайные числа 
	cmplx<double> serrrr[5];
	fillrca(serrrr);
	caprint(serrrr);

	cmplx<double> ll[5];
	fillrca(ll);
	caprint(ll);

	cmplx<double> twww[10];
	fillrca(twww);
	
	proprint(twww);

	cmplx<double> tt[10];
	fillrca(tt);
	csort(tt);
	proprint(tt);

}


