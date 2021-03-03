#pragma once
class Statistics
{
public:
	static double randomNumber(int min, int max); //generowanie liczb losowych
	static void shuffleWines(); //rozlosowanie zbior�w treningowego i testowego
	static void shuffleTrainingData(); //tasowanie zbioru treningowego po ka�dej epoce uczenia
	static unsigned short int outputAsNumber(std::vector<double> outputVector); //konwersja wyj�cia sieci neuronowej na liczb� ca�kowit�

	Statistics();
	~Statistics();
};