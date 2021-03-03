#pragma once
class Neuron
{
private:
	static Matrix preGeneratedW, preGeneratedV; //uprzednio wygenerowane macierze wag o wielko�ci Jmax x N i K x Jmax
	static std::vector<double> preGeneratedB, preGeneratedC; //b Jmax x 1, c Kx1 - wektory odchyle�
	Matrix W, V; //W -> JxN, V -> KxJ - macierze wag
	std::vector<double> B, C; //wektory odchyle� B Jx1, C Kx1
	double eta; //wsp�czynnik uczenia
	static const int k = 2, n = 13; //k = liczba wyj�� n = liczba wej��
	int j; //wielko�� warstwy ukrytej
	double lambda; //wsp�czynnik funkcji sigmoidalnej
	static double Emin; //warto�� progowa funkcji b��du
	static int max_cycles; //maksymalna ilo�� epok
	static bool shuffle; //parametr odpowiadaj�cy za losowanie danych treningowych po ka�dej epoce
public:
	static void setShuffle(bool flag); //ustawienie losowania
	static void generateNetwork(int size); //losowanie pocz�tkowych macierzy wag i wektor�w odchyle�
	std::vector<double> netJ(std::vector<double> X); //��czny sygna� pobudzenia warstwy ukrytej
	std::vector<double> netK(std::vector<double> Y); //��czny sygna� pobudzenia warstwy wyj�ciowej
	std::vector<double> f(std::vector<double> net); //funkcja aktywacji
	std::vector<double> derivateF(std::vector<double> net); //pochodna funkcji aktywacji
	std::vector<double> delta(std::vector<double> Z, std::vector<double> D, std::vector<double> derivativeF); //wyznaczenie b��du warstwy wyj�ciowej
	std::vector<double> rho(std::vector<double> delta, std::vector<double> derivativeF); //wyznaczenie b��du warstwy ukrytej
	void updateWeights(std::vector<double> delta, std::vector<double> rho, std::vector<double> X, std::vector<double> Y);
	double errorFunction(Matrix allZ, bool flag, double& efficiency, double& bit_efficiency); //funkcja b��du, wymaga wszystkich odpowiedzi z danej epoki (wektor macierzy Z). Flaga na 1 - tryb uczenia, flaga na 0 - tryb testowania
	void learn(std::string nazwa_pliku); //funkcja rozpoczynaj�ca proces uczenia (wszystkie przewidziane epoki)

	Neuron(double eta, double lambda, int j); //zaludnianie macierzy wag i wektor�w odchyle� wygenerowanymi danymi
	~Neuron();
};