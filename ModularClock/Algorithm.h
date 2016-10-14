#pragma once
class Algorithm
{
public:
	Algorithm();
	~Algorithm();

	void randomAlgoritm(int m);
	void jumpStayAlgorithm(int m);
	void modularClockAlgorithm(int m);

	bool match();

	void setDelay(int d);
	void setIsSynch(bool s);
	void setNumberOfChannels(int m);
	int getMatchIndex();

	void generateUser(int userIndex);
	int  findPrime(int m);
	bool isPrime(int number);

	int userOne[256];
	int userTwo[256];

private:
	int randInt(int lower, int uper);

	bool isSynch;
	int delay;
	int numberOfChannels;

	int buffer[256];
	
	int matchIndex;
	int prevRandom;
};

