#include <cmath>
#include <bit>
#include <cassert>
#include "rapl-read.h"


#define PI std::bit_cast<double>(0x401921fb54442d18ull)

struct cs_t
{
	double cos_val, sin_val;
};

//cos   sin
cs_t table[] = {
		{std::bit_cast<double>(0x3fe6a09e667f3bcdull),  std::bit_cast<double>(0x3fe6a09e667f3bcdull)}, //  PI / 4
		{std::bit_cast<double>(0x3fed906bcf328d46ull),  std::bit_cast<double>(0x3fd87de2a6aea963ull)}, //  PI / 8
		{std::bit_cast<double>(0x3fef6297cff75cb0ull),  std::bit_cast<double>(0x3fc8f8b83c69a60aull)}, //  PI / 16
		{std::bit_cast<double>(0x3fefd88da3d12526ull),  std::bit_cast<double>(0x3fb917a6bc29b42cull)}, //  PI / 32
		{std::bit_cast<double>(0x3feff621e3796d7eull),  std::bit_cast<double>(0x3fa91f65f10dd814ull)}, //  PI / 64
		{std::bit_cast<double>(0x3feffd886084cd0dull),  std::bit_cast<double>(0x3f992155f7a3667eull)}, //  PI / 128
		{std::bit_cast<double>(0x3fefff62169b92dbull),  std::bit_cast<double>(0x3f8921d1fcdec784ull)}, //  PI / 256
		{std::bit_cast<double>(0x3fefffd8858e8a92ull),  std::bit_cast<double>(0x3f7921f0fe670071ull)}, //  PI / 512
		{std::bit_cast<double>(0x3feffff621621d02ull),  std::bit_cast<double>(0x3f6921f8becca4baull)}, //  PI / 1024
		{std::bit_cast<double>(0x3feffffd88586ee6ull),  std::bit_cast<double>(0x3f5921faaee6472dull)}, //  PI / 2048
		{std::bit_cast<double>(0x3fefffff62161a34ull),  std::bit_cast<double>(0x3f4921fb2aecb360ull)}, //  PI / 4096
		{std::bit_cast<double>(0x3fefffffd8858675ull),  std::bit_cast<double>(0x3f3921fb49ee4ea6ull)}, //  PI / 8192
		{std::bit_cast<double>(0x3feffffff621619cull),  std::bit_cast<double>(0x3f2921fb51aeb57bull)}, //  PI / 16384
		{std::bit_cast<double>(0x3feffffffd885867ull),  std::bit_cast<double>(0x3f1921fb539ecf31ull)}, //  PI / 32768
		{std::bit_cast<double>(0x3fefffffff62161aull),  std::bit_cast<double>(0x3f0921fb541ad59eull)}, //  PI / 65536
		{std::bit_cast<double>(0x3fefffffffd88586ull),  std::bit_cast<double>(0x3ef921fb5439d73aull)}, //  PI / 131072
		{std::bit_cast<double>(0x3feffffffff62162ull),  std::bit_cast<double>(0x3ee921fb544197a0ull)}, //  PI / 262144
		{std::bit_cast<double>(0x3feffffffffd8858ull),  std::bit_cast<double>(0x3ed921fb544387baull)}, //  PI / 524288
		{std::bit_cast<double>(0x3fefffffffff6216ull),  std::bit_cast<double>(0x3ec921fb544403c1ull)}, //  PI / 1.04858e+06
		{std::bit_cast<double>(0x3fefffffffffd886ull),  std::bit_cast<double>(0x3eb921fb544422c2ull)}, //  PI / 2.09715e+06
		{std::bit_cast<double>(0x3feffffffffff621ull),  std::bit_cast<double>(0x3ea921fb54442a83ull)}, //  PI / 4.1943e+06
		{std::bit_cast<double>(0x3feffffffffffd88ull),  std::bit_cast<double>(0x3e9921fb54442c73ull)}, //  PI / 8.38861e+06
		{std::bit_cast<double>(0x3fefffffffffff62ull),  std::bit_cast<double>(0x3e8921fb54442cefull)}, //  PI / 1.67772e+07
		{std::bit_cast<double>(0x3fefffffffffffd9ull),  std::bit_cast<double>(0x3e7921fb54442d0eull)}, //  PI / 3.35544e+07
		{std::bit_cast<double>(0x3feffffffffffff6ull),  std::bit_cast<double>(0x3e6921fb54442d15ull)}, //  PI / 6.71089e+07
		{std::bit_cast<double>(0x3feffffffffffffeull),  std::bit_cast<double>(0x3e5921fb54442d17ull)}, //  PI / 1.34218e+08
		{std::bit_cast<double>(0x3fefffffffffffffull),  std::bit_cast<double>(0x3e4921fb54442d18ull)}, //  PI / 2.68435e+08
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3e3921fb54442d18ull)}, //  PI / 5.36871e+08
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3e2921fb54442d18ull)}, //  PI / 1.07374e+09
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3e1921fb54442d18ull)}, //  PI / 2.14748e+09
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3e0921fb54442d18ull)}, //  PI / 4.29497e+09
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3df921fb54442d18ull)}, //  PI / 8.58993e+09
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3de921fb54442d18ull)}, //  PI / 1.71799e+10
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3dd921fb54442d18ull)}, //  PI / 3.43597e+10
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3dc921fb54442d18ull)}, //  PI / 6.87195e+10
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3db921fb54442d18ull)}, //  PI / 1.37439e+11
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3da921fb54442d18ull)}, //  PI / 2.74878e+11
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3d9921fb54442d18ull)}, //  PI / 5.49756e+11
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3d8921fb54442d18ull)}, //  PI / 1.09951e+12
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3d7921fb54442d18ull)}, //  PI / 2.19902e+12
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3d6921fb54442d18ull)}, //  PI / 4.39805e+12
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3d5921fb54442d18ull)}, //  PI / 8.79609e+12
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3d4921fb54442d18ull)}, //  PI / 1.75922e+13
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3d3921fb54442d18ull)}, //  PI / 3.51844e+13
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3d2921fb54442d18ull)}, //  PI / 7.03687e+13
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3d1921fb54442d18ull)}, //  PI / 1.40737e+14
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3d0921fb54442d18ull)}, //  PI / 2.81475e+14
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3cf921fb54442d18ull)}, //  PI / 5.6295e+14
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3ce921fb54442d18ull)}, //  PI / 1.1259e+15
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3cd921fb54442d18ull)}, //  PI / 2.2518e+15
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3cc921fb54442d18ull)}, //  PI / 4.5036e+15
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3cb921fb54442d18ull)}, //  PI / 9.0072e+15
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3ca921fb54442d18ull)}, //  PI / 1.80144e+16
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3c9921fb54442d18ull)}, //  PI / 3.60288e+16
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3c8921fb54442d18ull)}, //  PI / 7.20576e+16
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3c7921fb54442d18ull)}, //  PI / 1.44115e+17
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3c6921fb54442d18ull)}, //  PI / 2.8823e+17
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3c5921fb54442d18ull)}, //  PI / 5.76461e+17
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3c4921fb54442d18ull)}, //  PI / 1.15292e+18
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3c3921fb54442d18ull)}, //  PI / 2.30584e+18
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3c2921fb54442d18ull)}, //  PI / 4.61169e+18
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3c1921fb54442d18ull)}, //  PI / 9.22337e+18
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3c0921fb54442d18ull)}, //  PI / 1.84467e+19
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3bf921fb54442d18ull)}, //  PI / 3.68935e+19
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3be921fb54442d18ull)}, //  PI / 7.3787e+19
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3bd921fb54442d18ull)}, //  PI / 1.47574e+20
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3bc921fb54442d18ull)}, //  PI / 2.95148e+20
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3bb921fb54442d18ull)}, //  PI / 5.90296e+20
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3ba921fb54442d18ull)}, //  PI / 1.18059e+21
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3b9921fb54442d18ull)}, //  PI / 2.36118e+21
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3b8921fb54442d18ull)}, //  PI / 4.72237e+21
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3b7921fb54442d18ull)}, //  PI / 9.44473e+21
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3b6921fb54442d18ull)}, //  PI / 1.88895e+22
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3b5921fb54442d18ull)}, //  PI / 3.77789e+22
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3b4921fb54442d18ull)}, //  PI / 7.55579e+22
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3b3921fb54442d18ull)}, //  PI / 1.51116e+23
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3b2921fb54442d18ull)}, //  PI / 3.02231e+23
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3b1921fb54442d18ull)}, //  PI / 6.04463e+23
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3b0921fb54442d18ull)}, //  PI / 1.20893e+24
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3af921fb54442d18ull)}, //  PI / 2.41785e+24
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3ae921fb54442d18ull)}, //  PI / 4.8357e+24
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3ad921fb54442d18ull)}, //  PI / 9.67141e+24
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3ac921fb54442d18ull)}, //  PI / 1.93428e+25
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3ab921fb54442d18ull)}, //  PI / 3.86856e+25
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3aa921fb54442d18ull)}, //  PI / 7.73713e+25
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3a9921fb54442d18ull)}, //  PI / 1.54743e+26
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3a8921fb54442d18ull)}, //  PI / 3.09485e+26
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3a7921fb54442d18ull)}, //  PI / 6.1897e+26
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3a6921fb54442d18ull)}, //  PI / 1.23794e+27
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3a5921fb54442d18ull)}, //  PI / 2.47588e+27
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3a4921fb54442d18ull)}, //  PI / 4.95176e+27
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3a3921fb54442d18ull)}, //  PI / 9.90352e+27
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3a2921fb54442d18ull)}, //  PI / 1.9807e+28
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3a1921fb54442d18ull)}, //  PI / 3.96141e+28
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x3a0921fb54442d18ull)}, //  PI / 7.92282e+28
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x39f921fb54442d18ull)}, //  PI / 1.58456e+29
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x39e921fb54442d18ull)}, //  PI / 3.16913e+29
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x39d921fb54442d18ull)}, //  PI / 6.33825e+29
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x39c921fb54442d18ull)}, //  PI / 1.26765e+30
		{std::bit_cast<double>(0x3ff0000000000000ull),  std::bit_cast<double>(0x39b921fb54442d18ull)} //  PI / 2.5353e+30
};

cs_t  multiple_1(const cs_t* table_row, cs_t old_val, bool clockwise)
{
	if (!clockwise)
		return cs_t{
			table_row->cos_val * old_val.cos_val - table_row->sin_val * old_val.sin_val,
			table_row->sin_val * old_val.cos_val + table_row->cos_val * old_val.sin_val
		};
	else
		return cs_t{
			 table_row->cos_val * old_val.cos_val + table_row->sin_val * old_val.sin_val,
			-table_row->sin_val * old_val.cos_val + table_row->cos_val * old_val.sin_val
		};
}

cs_t cordic_cs_N(double x, size_t N = sizeof(table) / sizeof(table[0]))
{
	double angle = 0;
	double delta = 0.7853981633974483;
	cs_t result = { 1, 0 };
	assert(N <= sizeof(table) / sizeof(table[0]));
	for (unsigned i = 0; i < N; ++i)
	{
		if (x < angle)
		{
			result = multiple_1(&table[i], result, 1);
			angle -= delta;
			delta /= 2;
		}
		else
		{
			result = multiple_1(&table[i], result, 0);
			angle += delta;
			delta /= 2;
		}
	}
	return result;
}

cs_t cordic_cs(double x)
{
	return cordic_cs_N(x);
}

double error_ulp(double x_approx, double x_true)
{
	double absolute_error = fabs(x_approx - x_true);
	int exp;
	frexp(x_approx, &exp);
	double ulp = ldexp(1.0, exp - 52 - 1);
	return absolute_error / ulp;
}

#include <stdio.h>
#include <bit>
#include <chrono>
#include <vector>

//ïîáèòîâîå ïðèâåäåíèå ÷èñëà ñ ïëàâ. òî÷êîé â öåëî÷èñëåííîå 
unsigned long long from_double(double x)
{
	return std::bit_cast<unsigned long long>(x);
}

double to_double(unsigned long long x)
{
	return std::bit_cast<double>(x);
}

static unsigned row;

//âûâîä çíà÷åíèÿ íà ýêðàí (çàãîëîâîê)

void display_row_header()
{
	row = 0;
	printf("Iter.\tApprox. value\t\tTrue value\t\tError value, ulp\n");
}

//âûâîä çíà÷åíèÿ íà ýêðàí (òàáëèöà çíà÷åíèé â 16 ññ)
void display_row(double approx_val, double true_val)
{
	printf("%d\t%llx\t%llx\t%g\n", ++row, std::bit_cast<unsigned long long>(approx_val), std::bit_cast<unsigned long long>(true_val), error_ulp(approx_val, true_val));
}

//âûâîä çíà÷åíèÿ íà ýêðàí (òàáëèöà çíà÷åíèé â 10 ññ)
void display_row_dec(double approx_val, double true_val)
{
	printf("%d\t%.13g\t%.13g\t%g\n", ++row, approx_val, true_val, error_ulp(approx_val, true_val));
}

//ðåàëèçàöèÿ òî÷íîñòè è âûâîä íà ýêðàí (èçìåðåíèå òî÷íîñòè)
void measure_cordic_accuracy()
{
	double arg = 1;
	double angle = 0;
	double delta = std::scalbn(PI, -2);
	cs_t result = {1, 0};
	cs_t cs_val;
	double true_cos_1 = std::bit_cast<double>(0x3FE14A280FB5068Bull);
	double true_sin_1 = std::bit_cast<double>(0x3FEAED548F090CEEull);

	std::vector<cs_t> results;
		
	for (unsigned int i = 1; i <= 100; ++i)
	{
		cs_val.cos_val = std::cos(delta);
		cs_val.sin_val = std::sin(delta);
		if (arg < angle)
		{
			result = multiple_1(&cs_val, result, 1);
			angle -= delta;
			delta /= 2;
		}else
		{
			result = multiple_1(&cs_val, result, 0);
			angle += delta;
			delta /= 2;
		}
		results.push_back(result);
		
	}
	printf("==Sine==\n");
	display_row_header();
	for (auto result:results)
		display_row_dec(result.sin_val, true_sin_1);
	printf("==Cosine==\n");
	display_row_header();
	for (auto result:results)
		display_row_dec(result.cos_val, true_cos_1);
}

#include <chrono>
#include <iostream>

#ifdef __GNUC__
#include <x86intrin.h>
#define rdtsc() ((long long) _rdtsc())
#elif defined(_MSC_VER)
#include <intrin.h>
#define rdtsc() ((long long) __rdtsc())
#endif

void measure_cordic_time()
{
	int cpu_model;
	cpu_model=detect_cpu();
	detect_packages();

	for (unsigned exp_count = 1; exp_count <= 100; ++exp_count)
	{
		// auto tm1 = rdtsc();
		cs_t result = cordic_cs_N(1, exp_count);
		// auto tm2 = rdtsc();
		std::cout << "Result: " << result.cos_val << ", energy consumption: \n";
		performance_measurement();
		std::cout << std::endl;
	}
}

void measure_cordic_accuracy2()
{
	double arg = 1;
	double angle = 0;
	double delta = 0.7853981633974483;
	cs_t result = { 1, 0 };
	cs_t cs_val;
	double true_cos_1 = std::bit_cast<double>(0x3FE14A280FB5068Bull);
	double true_sin_1 = std::bit_cast<double>(0x3FEAED548F090CEEull);

	std::vector<cs_t> results;

	for (unsigned i = 0; i < sizeof(table) / sizeof(table[0]); ++i)
	{
		cs_val = table[i];

		if (arg < angle)
		{
			result = multiple_1(&cs_val, result, 1);
			angle -= delta;
			delta /= 2;
		}
		else
		{
			result = multiple_1(&cs_val, result, 0);
			angle += delta;
			delta /= 2;
		}
		results.push_back(result);

	}
	printf("==Sine==\n");
	display_row_header();
	for (auto result : results)
		display_row_dec(result.sin_val, true_sin_1);
	printf("==Cosine==\n");
	display_row_header();
for (auto result : results)
	display_row_dec(result.cos_val, true_cos_1);
}

double ave_seq(const int * A, std::size_t n)
{
	double r = 0.0;
	for (std::size_t i = 0; i < n; ++i)
		r += A[i];
	return r / n;
}

#include <omp.h>
double ave_par(const int * A, std::size_t n)
{
	double r = 0.0;
	#pragma omp parallel
	{
		double lr = 0.0;
		for (std::size_t i = omp_get_thread_num(); i < n; i+= omp_get_num_threads())
			lr += A[i];
#pragma omp critical
		{
			r += lr;
		}
	}
	return r / n;
}

#include <memory>
extern std::unique_ptr<int[]> data_buffer; 
int main(int, char**)
{
	double x = 1;
	unsigned long long true_sin_binary = 0x3FEAED548F090CEEull;
	double true_sin = to_double(true_sin_binary);
	cs_t cs = cordic_cs(x);
	printf("x = %g\n", x);
	printf("expect = 0x%08llX = %.15g\n", true_sin_binary, true_sin);  
	printf("expect = 0x%08llX = %.15g\n", true_sin_binary, true_sin);
	printf("sin(x) = 0x%08llX = %.15g\n", from_double(cs.sin_val), cs.sin_val);
	printf("cos(x) = 0x%08llX = %.15g\n", from_double(cs.cos_val), cs.cos_val);
	measure_cordic_accuracy2();
	measure_cordic_time();

	auto data = data_buffer.get();
	constexpr std::size_t n = 1ull << 28;
	double ave_seq_result = ave_seq(data, n);
	printf("Average: %g\n", ave_seq_result);
	double ave_par_result = ave_par(data, n);
	printf("Average: %g\n", ave_par_result);

	return 0;
}
