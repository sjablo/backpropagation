#pragma once
class Statistics
{
public:
	static double randomNumber(int min, int max); //generowanie liczb losowych
	static void shuffleWines(); //rozlosowanie zbiorów treningowego i testowego
	static void shuffleTrainingData(); //tasowanie zbioru treningowego po ka¿dej epoce uczenia
	static unsigned short int outputAsNumber(std::vector<double> outputVector); //konwersja wyjœcia sieci neuronowej na liczbê ca³kowit¹

	Statistics();
	~Statistics();
};