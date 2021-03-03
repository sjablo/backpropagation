#pragma once
class Neuron
{
private:
	static Matrix preGeneratedW, preGeneratedV; //uprzednio wygenerowane macierze wag o wielkoœci Jmax x N i K x Jmax
	static std::vector<double> preGeneratedB, preGeneratedC; //b Jmax x 1, c Kx1 - wektory odchyleñ
	Matrix W, V; //W -> JxN, V -> KxJ - macierze wag
	std::vector<double> B, C; //wektory odchyleñ B Jx1, C Kx1
	double eta; //wspó³czynnik uczenia
	static const int k = 2, n = 13; //k = liczba wyjœæ n = liczba wejœæ
	int j; //wielkoœæ warstwy ukrytej
	double lambda; //wspó³czynnik funkcji sigmoidalnej
	static double Emin; //wartoœæ progowa funkcji b³êdu
	static int max_cycles; //maksymalna iloœæ epok
	static bool shuffle; //parametr odpowiadaj¹cy za losowanie danych treningowych po ka¿dej epoce
public:
	static void setShuffle(bool flag); //ustawienie losowania
	static void generateNetwork(int size); //losowanie pocz¹tkowych macierzy wag i wektorów odchyleñ
	std::vector<double> netJ(std::vector<double> X); //³¹czny sygna³ pobudzenia warstwy ukrytej
	std::vector<double> netK(std::vector<double> Y); //³¹czny sygna³ pobudzenia warstwy wyjœciowej
	std::vector<double> f(std::vector<double> net); //funkcja aktywacji
	std::vector<double> derivateF(std::vector<double> net); //pochodna funkcji aktywacji
	std::vector<double> delta(std::vector<double> Z, std::vector<double> D, std::vector<double> derivativeF); //wyznaczenie b³êdu warstwy wyjœciowej
	std::vector<double> rho(std::vector<double> delta, std::vector<double> derivativeF); //wyznaczenie b³êdu warstwy ukrytej
	void updateWeights(std::vector<double> delta, std::vector<double> rho, std::vector<double> X, std::vector<double> Y);
	double errorFunction(Matrix allZ, bool flag, double& efficiency, double& bit_efficiency); //funkcja b³êdu, wymaga wszystkich odpowiedzi z danej epoki (wektor macierzy Z). Flaga na 1 - tryb uczenia, flaga na 0 - tryb testowania
	void learn(std::string nazwa_pliku); //funkcja rozpoczynaj¹ca proces uczenia (wszystkie przewidziane epoki)

	Neuron(double eta, double lambda, int j); //zaludnianie macierzy wag i wektorów odchyleñ wygenerowanymi danymi
	~Neuron();
};