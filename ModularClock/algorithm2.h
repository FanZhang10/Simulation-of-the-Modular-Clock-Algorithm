#ifndef ALGORITHM_H
#define ALGORITHM_H


class Algorithm
{
public:
    Algorithm();
    ~Algorithm();

	void randomAlgoritm(int m);
    void jumpStayAlgorithm(int m);
    void modularClockAlgorithm(int m);

    void match();

    void setDelay(int d);
    void setIsSynch(bool s);
    void setNumberOfChannels(int m);

    void generateUser();
    int  findPrime (int m);
    bool isPrime (int number);

private:
	int generateRandom(int lower, int uper);

    bool isSynch;
    int delay;
    int numberOfChannels;
    int* userOne ;
    int* userTwo ;
    int matchIndex [];

};

#endif // ALGORITHM_H
