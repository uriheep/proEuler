#include <cstdio>
#include <iostream>

#include <thread>
#include <ctime>
#include <chrono>


static
int
getSumMultiples( const int&  upperBound,
                 const int&  mul
               ) noexcept
{
  int  result  =  0;
  if ( upperBound >= mul )
  {
    for ( int i = 1; i <= upperBound / mul; ++i )
      if ( upperBound > mul * i )
        result  +=  mul * i;
  }
  return  result;
}

static
int
getSumTwoMultiples( const int&  upperBound,
                    const int&  mul1,
                    const int&  mul2
                  ) noexcept
{
  int  result  =  0;
  if ( upperBound >= ( mul1 < mul2 ? mul2 : mul1 ) )
  {
    for ( int i = 1; i <= upperBound / ( mul1 < mul2 ? mul1 : mul2 ); ++i )
    {
      if ( upperBound > mul1 * i
        && 0 != mul1 * i % mul2
         )
      {
        result  +=  i * mul1;
      }
      if ( upperBound > mul2 * i )
        result  +=  i * mul2;
    }
  }
  return  result;
}


int main() {

  constexpr int  upperB  =  1000;
  constexpr int  mul1  =  3;
  constexpr int  mul2  =  5;

  int  result1  =  0;
  int  result2  =  0;

  const auto    chronoStart1  =  std::chrono::steady_clock::now();
  const time_t  start1  =  clock();
  std::thread  t1( [ & ] { result1 = getSumMultiples( upperB, mul1 ); } );
  std::thread  t2( [ & ] { result2 = getSumMultiples( upperB, mul2 ); } );

  t1.join();
  t2.join();

  const time_t  end1  =  clock();
  const double  time1  =  ( ( double( end1 ) - double( start1 ) ) / CLOCKS_PER_SEC );
  const auto    chronoEnd1  =  std::chrono::steady_clock::now();
  const std::chrono::duration<double>  chronoTime1  =  chronoEnd1 - chronoStart1;


  const auto    chronoStart2  =  std::chrono::steady_clock::now();
  const time_t  start2  =  clock();
  const int  result3  =  getSumMultiples( upperB, mul1 );
  const int  result4  =  getSumMultiples( upperB, mul2 );
  const int  result5  =  result3 + result4;
  const time_t  end2  =  clock();
  const double  time2  =  ( ( double( end2 ) - double( start2 ) ) / CLOCKS_PER_SEC );
  const auto    chronoEnd2  =  std::chrono::steady_clock::now();
  const std::chrono::duration<double>  chronoTime2  =  chronoEnd2 - chronoStart2;


  int  result  =  result1 + result2;
  printf( "%d\n", result );
  printf( "time1 = %f\n", time1 );
  std::cout << "chrono time1 = " << chronoTime1.count() << std::endl;

  printf( "%d\n", result5 );
  printf( "time2 = %f\n", time2 );
  std::cout << "chrono time2 = " << chronoTime2.count() << std::endl;

  const int  resultProblem1  =  getSumTwoMultiples( upperB, mul1, mul2 );
  printf( "project Euler problem 1 answer : %d\n", resultProblem1 );

  return 0;
}
