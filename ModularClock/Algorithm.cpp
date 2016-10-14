#include "stdafx.h"
#include "Algorithm.h" 

Algorithm::Algorithm()
{
	numberOfChannels = 0;
	prevRandom = -1;

	for (int i = 0; i < 256; i++)
	{
		buffer[i] = -1;
	}
}


Algorithm::~Algorithm()
{
}


void Algorithm::randomAlgoritm(int m)
{
	int i = 0;
	int j = 0;
	int c = 0;

	while(i < 4*m)
	{
		j = randInt(0, m - 1);
		c = j % m;
		buffer[i] = c;
		i++;
	}
	

}

void Algorithm::jumpStayAlgorithm(int m)
{
	int j = 0; //current index
	int t = 0; //time
	int c = 0;
	int p = findPrime(m);
	int i = randInt(0, p - 1); //start index
	int r = randInt(0, m-1);//channel indeices range from zero to m-1
	
	while (prevRandom == r){
		r = randInt(0, m - 1);
	}
	prevRandom = r;

	while (t <= (3*p - 1))
	{
		if (i >= p)
		{
			i = 0;
		}

		j = (i + t*r) % p;
		c = j % m;
		buffer[t] = c;
		i++;
		t++;
	}

	while (t >= (3 * p) && t <= (4 * p - 1))
	{
		j = r;
		c = j % m;
		buffer[t] = c;	
		t++;
	}

}

void Algorithm::modularClockAlgorithm(int m)
{
	int c = 0;	
	int j = 0; //current index
	int t = 0; //time
	int p = findPrime(m);
	int i = randInt(0, p - 1); // start index
	int r1 = randInt(0, p - 1);
	int r2 = randInt(0, p - 1);
	
	while (t <= (2*p - 1))
	{

		if (i >= p)
		{
			i = 0;
		}

		j = (i + t*r1) % p;
		c = j % m;
		buffer[t] = c;
		i++;
		t++;

	}

	while (t >= (2*p) && t <= (4*p - 1))
	{

		if (i >= p)
		{
			i = 0;
		}

		j = (i + t*r2) % p;
		c = j % m;
		buffer[t] = c;
		i++;
		t++;
	}

}

bool Algorithm::match()
{
	for(int i = 0; i < 256; i++) {
		if (userOne[i] < 0 || userTwo[i] < 0) {
			break;
		}

		if (userOne[i] == userTwo[i])
		{
			matchIndex = i;
			return true;
		}	
	} 
	return false;
}

int Algorithm::randInt(int lower, int uper)
{
	return lower + rand() % uper;
}

int Algorithm::findPrime(int m)
{
	int temp = m;
	while (true){

		if (isPrime(temp))
		{
			return temp;
		}
		temp++;
	}
}

bool Algorithm::isPrime(int num)
{
	if (num <= 1)
		return false;
	else if (num == 2)
		return true;
	else if (num % 2 == 0)
		return false;
	else
	{
		bool prime = true;
		int divisor = 3;
		double num_d = static_cast<double>(num);
		int upperLimit = static_cast<int>(sqrt(num_d) + 1);

		while (divisor <= upperLimit)
		{
			if (num % divisor == 0)
				prime = false;
			divisor += 2;
		}
		return prime;
	}
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
	for (int i = 0; i < 256; i++)
	{
		buffer[i] = -1;
	}

	numberOfChannels = m;
}

int Algorithm::getMatchIndex()
{
	return matchIndex;
}

void Algorithm::generateUser(int userIndex)
{
	if (userIndex == 1){
		int i = 0;
		while (i < 256){
			userOne[i] = buffer[i];
			i++;
		}
	}
	else if (userIndex == 2){
		int i = 0;
		while (i < 256){
			userTwo[i] = buffer[i];
			i++;
		}
	}
			
}


