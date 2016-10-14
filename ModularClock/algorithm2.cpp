#include "algorithm.h"
#include "stdafx.h"

Algorithm::Algorithm()
{
}


Algorithm::~Algorithm()
{

}

void Algorithm::randomAlgoritm(int m)
{
    int randOne, randTwo;
    do{
		randOne = generateRandom(0, numberOfChannels - 1);
		randTwo = generateRandom(0, numberOfChannels - 1);
    }while(randOne != randTwo);

}

void Algorithm::jumpStayAlgorithm(int m)
{
    int i = 0; //index
    int j = 0; //current index
    int t = 0; //time
    int p = findPrime(m);  
    int r = generateRandom(1,m);

    while(t <= (3*p-1))
    {
        j = (i + t*r) % p;
        i++;
        t++;
    }

    while(t >= (3*p) && t <= (4*p-1))
    {
        j = r;
    }

}

void Algorithm::modularClockAlgorithm(int m)
{
    int i = 0; //index
    int j = 0; //current index
    int t = 0; //time
    int p = findPrime(m);
    int r1 = generateRandom(1,m);
    int r2 = generateRandom(1,m);



    while( r1 = r2)
    {
        int r = generateRandom(1,m);
        r2 = r;
    }

    while(t <= (2*p-1))
    {
        
        j = (i + t*r1) % p;
        i++;
        t++;
    }

    while(t >= (2*p) && t <=(4*p-1))
    {
       
        j = (i + t*r2) % p;
        i++;
        t++;
    }

}

void Algorithm::match()
{

}

int Algorithm::generateRandom(int lower, int uper)
{
    /* pick random number from 0 to range */
   // return lower+ (rand () % uper) ;
	return 0;
}

void Algorithm::setDelay(int d)
{
    delay = d;
}

void Algorithm::setIsSynch(bool s)
{
	isSynch = s;
}

void Algorithm::setNumberOfChannels(int m)
{
    numberOfChannels = m;
}


 void Algorithm::generateUser()
 {
      userOne = new int[4*numberOfChannels];
      userTwo = new int[4*numberOfChannels];
 }

 int Algorithm::findPrime(int m)
 {
     int temp = m;
     while ( true ){
         temp ++;
             if( isPrime ( temp ))
             {
             return temp;
         }
     }
 }

 bool Algorithm::isPrime (int number)
 {
     if ( ( (!( number & 1)) && number != 2 ) ||
         ( number < 2) || ( number % 3 == 0 && number != 3) )
            return false ;
     for ( int k = 1; 36* k*k -12* k < number ;++ k)
     {
         if ( ( number % (6*k +1) == 0) || ( number % (6*k -1) == 0) )
         return false ;
     }
     return true ;
 }
