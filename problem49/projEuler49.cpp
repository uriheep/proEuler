#include <iostream>
#include <cmath>
#include <vector>
#include <new>

#include <limits>
#include <chrono>



static
std::vector<long>
getVectorPrimes( const long&  n ) noexcept;


static
std::vector<unsigned>
parsePrimeNum( const long&  primeNum ) noexcept;


static
bool
arePermutations( const std::vector<unsigned>&  vec1,
                 const std::vector<unsigned>&  vec2
               ) noexcept;


struct  Problem49Result {
  public:
    Problem49Result() noexcept : prime1( 0 ), prime2( 0 ), prime3( 0 ) { }
    Problem49Result( const long&  num1,
                     const long&  num2,
                     const long&  num3
                   ) noexcept : prime1( num1 ),
                                prime2( num2 ),
                                prime3( num3 )
    { }
  public:
    long  prime1;
    long  prime2;
    long  prime3;
};

static
Problem49Result
getProblem49Number() noexcept;

static
Problem49Result
getProblem49NumberSmart() noexcept;


int main() {


  const auto  start1  =  std::chrono::steady_clock::now();
  const Problem49Result  result  =  getProblem49Number();
  const auto  end1  =  std::chrono::steady_clock::now();
  const std::chrono::duration<double>  time1  =  end1 - start1;

  const auto  start2  =  std::chrono::steady_clock::now();
  const Problem49Result  resultSmart  =  getProblem49NumberSmart();
  const auto  end2  =  std::chrono::steady_clock::now();
  const std::chrono::duration<double>  time2  =  end2 - start2;

  std::cout << "getProblem49Number(): " << time1.count() << std::endl;
  std::cout << "getProblem49NumberSmart(): " << time2.count() << std::endl;

  if ( result.prime1 == resultSmart.prime1
    && result.prime2 == resultSmart.prime2
    && result.prime3 == resultSmart.prime3
     )
  {

    printf( "three primes are: %lu\t%lu\t%lu\n", result.prime1, result.prime2, result.prime3 );

    printf( "differences are: %lu\t%lu\n", result.prime2 - result.prime1, result.prime3 - result.prime2 );
  }

  return  0;
}


static
std::vector<long>
getVectorPrimes( const long&  n ) noexcept
{
  std::vector<long>  result;
  if ( 2 > n
    || std::numeric_limits<long>::max() / 2 < n
     )
    return  result;
  try
  {
    const unsigned long  m  =  std::sqrt( n );
    bool  *arr  =  new bool [ m ];
    for ( unsigned long i = 0; i < m; ++i )
      arr[ i ]  =  1;
    for ( unsigned long i = 2; i < std::sqrt( m ); ++i )
      if ( 1 == arr[ i ] )
        for ( unsigned long j = i * i; j < m; j += i )
          arr[ j ]  =  0;
    for ( unsigned long i = 0; i < m; ++i )
      if ( 1 == arr[ i ] )
        result.push_back( i );

    unsigned long  index  =  2;
    while ( ( unsigned long ) n >= index * m )
    {
      for ( unsigned long i = 0; i < m; ++i )
        arr[ i ]  =  1;
      const unsigned long  size  =  result.size();
      for ( unsigned long i = 0; i < size; ++i )
      {
        const unsigned long  prime  =  result[ i ];
        if ( 2 <= prime
          && prime <= std::sqrt( index * m ) )
        {
          unsigned long  j  =  2;
          while ( ( index - 1 ) * m > j * prime )  ++j;
          while ( index * m > j * prime )
          {
            const unsigned long  k  =  j * prime - ( index - 1 ) * m;
            arr[ k ]  =  0;
            ++j;
          }
        }
      }
      for ( unsigned long i = 0; i < m; ++i )
        if ( 1 == arr[ i ] )
        {
          const unsigned long  newPrime  =  ( index - 1 ) * m + i;
          result.push_back( newPrime );
        }
      ++index;
    }

    delete [] arr;
    arr  =  0;
  }
  catch( const std::bad_alloc&  ba )
    { printf( "%s\n", ba.what() ); }
  return  result;
}




static
std::vector<unsigned>
parsePrimeNum( const long&  primeNum ) noexcept
{
  std::vector<unsigned>  result;
  if ( 2 > primeNum )
    return  result;

  long  primeCopy  =  primeNum;
  while ( 0 != primeCopy / 10 )
  {
    const unsigned  digit  =  primeCopy % 10;
    result.push_back( digit );
    primeCopy /= 10;
  }
  result.push_back( primeCopy );
  return  result;
}

static
bool
arePermutations( const std::vector<unsigned>&  vec1,
                 const std::vector<unsigned>&  vec2
               ) noexcept
{
  if ( true == vec1.empty()
    || true == vec2.empty()
    || vec1.size() != vec2.size()
     )
  {
    return  false;
  }
  bool  result  =  false;
  const int  size  =  vec1.size();
  std::vector<unsigned>  vecDigits1( 10, 0 );
  std::vector<unsigned>  vecDigits2( 10, 0 );
  for ( int i = 0; i < size; ++i )
  {
    if ( 0 == vec1[ i ] )
      ++vecDigits1[ 0 ];
    if ( 1 == vec1[ i ] )
      ++vecDigits1[ 1 ];
    if ( 2 == vec1[ i ] )
      ++vecDigits1[ 2 ];
    if ( 3 == vec1[ i ] )
      ++vecDigits1[ 3 ];
    if ( 4 == vec1[ i ] )
      ++vecDigits1[ 4 ];
    if ( 5 == vec1[ i ] )
      ++vecDigits1[ 5 ];
    if ( 6 == vec1[ i ] )
      ++vecDigits1[ 6 ];
    if ( 7 == vec1[ i ] )
      ++vecDigits1[ 7 ];
    if ( 8 == vec1[ i ] )
      ++vecDigits1[ 8 ];
    if ( 9 == vec1[ i ] )
      ++vecDigits1[ 9 ];


    result  =  false;
    for ( int j = 0; j < size; ++j )
      if ( vec1[ i ] == vec2[ j ] )
      {  result  =  true; }
    if ( false == result )
      return  false;
  }
  for ( int i = 0; i < size; ++i )
  {
    if ( 0 == vec2[ i ] )
      ++vecDigits2[ 0 ];
    if ( 1 == vec2[ i ] )
      ++vecDigits2[ 1 ];
    if ( 2 == vec2[ i ] )
      ++vecDigits2[ 2 ];
    if ( 3 == vec2[ i ] )
      ++vecDigits2[ 3 ];
    if ( 4 == vec2[ i ] )
      ++vecDigits2[ 4 ];
    if ( 5 == vec2[ i ] )
      ++vecDigits2[ 5 ];
    if ( 6 == vec2[ i ] )
      ++vecDigits2[ 6 ];
    if ( 7 == vec2[ i ] )
      ++vecDigits2[ 7 ];
    if ( 8 == vec2[ i ] )
      ++vecDigits2[ 8 ];
    if ( 9 == vec2[ i ] )
      ++vecDigits2[ 9 ];

    result  =  false;
    for ( int j = 0; j < size; ++j )
      if ( vec2[ i ] == vec1[ j ] )
      {  result  =  true; }
    if ( false == result )
      return  false;
  }
  for ( int i = 0; i < 10; ++i )
    if ( vecDigits1[ i ] != vecDigits2[ i ] )
      return  false;

  return  result;
}



static
Problem49Result
getProblem49Number() noexcept
{
  Problem49Result  result;

  constexpr long  start  =  1000;//1487;
  constexpr long  end    =  10000;
  const std::vector<long>  vecPrimes  =  getVectorPrimes( end );


  for ( unsigned i = 0; i < vecPrimes.size() - 1; ++i )
    if ( start < vecPrimes[ i ]
      && end > vecPrimes[ i ]
       )
    {
      bool  permutations  =  false;
      long  num  =  0;
      const std::vector<unsigned>  vec1  =  parsePrimeNum( vecPrimes[ i ] );
      for ( unsigned j = i; j < vecPrimes.size(); ++j )
      {
        num  =  vecPrimes[ j ];
        const std::vector<unsigned>  vec2  =  parsePrimeNum( vecPrimes[ j ] );
        permutations  =  arePermutations( vec1, vec2 );
        if ( true == permutations
          && vecPrimes[ i ] != vecPrimes[ j ]
           )
          break;
      }
      if ( true == permutations
        && vecPrimes[ i ] != num
         )
      {
        const long  diff  =  num - vecPrimes[ i ];
        const long  newNumber  =  num + diff;
        const std::vector<unsigned>  vec2  =  parsePrimeNum( num );
        const std::vector<unsigned>  vec3  =  parsePrimeNum( newNumber );
        const bool  permutation  =  arePermutations( vec2, vec3 );
        if ( true == permutation )
        {
          for ( unsigned k = i; k < vecPrimes.size(); ++k )
            if ( newNumber == vecPrimes[ k ] )
            {
              result.prime1  =  vecPrimes[ i ];
              result.prime2  =  num;
              result.prime3  =  vecPrimes[ k ];
              return  result;
            }
//          printf( "%lu\t%lu\t%lu\t%lu\n", vecPrimes[ i ], num, newNumber, diff );
        }
      }
    }
  return  result;
}


static
Problem49Result
getProblem49NumberSmart() noexcept
{
  Problem49Result  result;

  constexpr long  start  =  1487;
  constexpr long  end    =  10000;
  constexpr long  diff   =  3330;
  const std::vector<long>  vecPrimes  =  getVectorPrimes( end );


  for ( unsigned i = 0; i < vecPrimes.size() - 1; ++i )
    if ( start < vecPrimes[ i ]
      && end > vecPrimes[ i ] + 2 * diff
       )
    {
      const long  secondNum  =  vecPrimes[ i ] + diff;
      const std::vector<unsigned>  vec1  =  parsePrimeNum( vecPrimes[ i ] );
      for ( unsigned j = i + 1; j < vecPrimes.size(); ++j )
      {
        if ( secondNum == vecPrimes[ j ] )
        {
          const std::vector<unsigned>  vec2  =  parsePrimeNum( vecPrimes[ j ] );
          const bool  permutations  =  arePermutations( vec1, vec2 );
          if ( true == permutations )
          {
            const long  thirdNum  =  vecPrimes[ i ] + 2 * diff;
            for ( unsigned k = i + 1; k < vecPrimes.size(); ++k )
            {
              if ( thirdNum == vecPrimes[ k ] )
              {
                const std::vector<unsigned>  vec3  =  parsePrimeNum( vecPrimes[ k ] );
                const bool  permutations  =  arePermutations( vec1, vec3 );
                if ( true == permutations
                  && vecPrimes[ j ] != vecPrimes[ k ]
                   )
                {
                  result.prime1  =  vecPrimes[ i ];
                  result.prime2  =  vecPrimes[ j ];
                  result.prime3  =  vecPrimes[ k ];
                }
              }
            } 
          }
        }
      }
    }
  return  result;
}
