#include <stdio.h>
#include <stdarg.h>  // ten plik jest wymagany przy wypsiywaniu funkcji o zmiennej liczbie parametrow ( lub roznej liczbie argumentow)
#include <iostream>
#define ILEMIEJSC 8

int Printf( const char* sFormat, ... );    //<zdeklarowac parametry>
int PrintfV( const char* sFormat, va_list arg_list );

void outDec( int );       // znakowo wypisuje liczbe calk
void outChar( char );     // wypisuje znak  // putchar()
void outStr(  char* );     // wypisuje zanakowo string
void outDouble( double ); // wypisuje znakowow liczbe double    0.
void outNum( int x );     // wypisuje znakowo liczbe int >0     rekurencyjnie

//----------------------------------
int main( int argc, char* argv[] )
{
  int n = -2;
  char c = '$';
  double x = 12000000.34050000012;     // .0000012 <=1e-5
  double y = -.12;
  double z = -0.5;
  char* str = ( char* ) "to jest string";

  Printf( "%s\n%f%c  n=%d \\ % /\ny=%f ` ` z=%f\n\n\%", str, x, c, n, y, z );  // ` -> '
  return 0;
}
// implementacja uproszczonej funkcji "Printf": %c %d %f %s oraz    // drukowanie liczb ze znakie, bez, double itp 
// zamienia `(klawisz ~) na '( klawisz ")
// do wypisywania mozna uzyc JEDYNIE outChar() -

// wywolanie putchar z parametrem ktory przesle 
//

//-----------------------------------------------
int Printf(const char* sFormat,... )
{
 
  // Initialize variable arguments
  va_list args;
  // set the pointer at the beggining of the arg list and get the first argument from the args list
  va_start( args, sFormat );
 /// int res = ;
  int res = PrintfV( sFormat, args );
    // Reset variable arguments
  va_end( args );
   /// return res;
  return res;
  
}
//-----------------------------------------------
int PrintfV( const char* sFormat, va_list arg_list )
{
  char c;
  int res = 0;
  while( c=*sFormat++ )  //c = *ptr++
  {
    switch( c )
    {
    case '%':
      switch( c = *sFormat++ )
      {
      case 'd': res++, outDec( va_arg( arg_list, int ) ); break;
      case 'f':res++, outDouble( va_arg( arg_list, double ) ); break;
      case 's':res++, outStr( va_arg( arg_list,  char* ) ); break;
      case 'c':res++, outChar( va_arg( arg_list, char ) ); break;
      default: outChar( '%' ); if( c ) outChar( c ); else sFormat--;
      }
      break;
      /*   switch( c = znak_z_we_stringu )
         {
           case 'd':
           case 'f':
           case 's':
           case 'c':
           default:
         }
       */
    case '`':  c = '\'';  //podstawic normalny apostrof
    default: outChar( c ); /* wypisanie c; */ break;
    
    }
  }
  return res;
}


//-----------------------------------------------
void outChar( char c )
{
  putchar( c );
}
//-----------------------------------------------
void outStr( char* pStr )
{
  while( *pStr )outChar( *pStr++ );
}
//-----------------------------------------------
void outDec( int x ) // wypisuje outNum ale jesli x<0 to najpioerw znak - outChar
{
  
  if( x < 0 )
  {
    outChar( '-' );
    x = -x;
  }
  outNum(x);
  
}

//-----------------------------------------------
void outDouble( double x )  // wypisuje znakowow liczbe double    0.
{/*
 
  for( int i = 0; i < ILEMIEJSC && ( ( x - int( x ) ) >1e-5 ); i++ )
  {

    outChar( int( x *= 10 ) % 10 + '0' );
    x = x * 10;
    double liczba = (int)x % 10;
    outChar( liczba + '0' );
  }*/
  
  if( x < 0 )
  {
    outChar( '-' );
    x = -x;
  }
  outNum( int( x ) );
  outChar( '.' );
  double liczba = x - ( int ) x;
  for( int i = 0; ( i < ILEMIEJSC) && ( liczba - ( int ) liczba ) > 1e-5; i++ )
  {
    liczba *= 10;
    outChar( ( int ) liczba % 10 + '0' );
  }
}
//-----------------------------------------------
void outNum( int x ) //rekurencyjny
{

  if( x < 10 )
  {
    outChar( x + '0' );
    return;
  }

  int value = x % 10;
  x = x / 10;

  outNum( x );
  outChar( value + '0' );

}