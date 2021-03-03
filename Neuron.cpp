#include "stdafx.h"

double Neuron::Emin = 0.1;
int Neuron::max_cycles = 500;
bool Neuron::shuffle = 1;

Matrix Neuron::preGeneratedW;
Matrix Neuron::preGeneratedV;
std::vector<double> Neuron::preGeneratedB;
std::vector<double> Neuron::preGeneratedC;

Neuron::Neuron(double eta, double lambda, int j)
{
	this->eta = eta;
	this->lambda = lambda;
	this->j = j;

	std::vector<double> temp;

	for (int j = 0; j < this->j; j++) { //pobranie z uprzednio wygenerowanych danych wektora odchyle� B i macierzy wag W:
		this->B.push_back(preGeneratedB[j]);
		for (int n = 0; n < this->n; n++) {
			temp.push_back(preGeneratedW.matrix[j][n]);
		}
		this->W.matrix.push_back(temp);
		temp.clear();
	}
	for (int k = 0; k < this->k; k++) { // macierz V i wektor C):
		this->C.push_back(preGeneratedC[k]);
		for (int j = 0; j < this->j; j++) {
			temp.push_back(preGeneratedV.matrix[k][j]);
		}
		this->V.matrix.push_back(temp);
		temp.clear();
	}
}

Neuron::~Neuron()
{
}

void Neuron::setShuffle(bool flag)
{
	Neuron::shuffle = flag;
}

void Neuron::generateNetwork(int size)
{
	std::vector<double> temp;

	//losowanie wag z przedzia�u (-1,1):
	srand(static_cast <unsigned> (time(0))); //inicjalizacja generatora liczb pseudolosowych

	for (int j = 0; j < size; j++) { //inicjalizacja wektora odchyle� B i macierzy wag W (parametr size okre�la maksymaln� wielko�� warstwy ukrytej):
		Neuron::preGeneratedB.push_back(Statistics::randomNumber(-1, 1));
		for (int n = 0; n < Neuron::n; n++) {
			temp.push_back(Statistics::randomNumber(-1, 1));
		}
		Neuron::preGeneratedW.matrix.push_back(temp);
		temp.clear();
	}
	for (int k = 0; k < Neuron::k; k++) { //wektor C i macierz V:
		Neuron::preGeneratedC.push_back(Statistics::randomNumber(-1, 1));
		for (int j = 0; j < size; j++) {
			temp.push_back(Statistics::randomNumber(-1, 1));
		}
		Neuron::preGeneratedV.matrix.push_back(temp);
		temp.clear();
	}
}

std::vector<double> Neuron::netJ(std::vector<double> X) //��czna warto�� pobudzenia wynosi netY=W*X+B
{
	std::vector<double> netY;
	netY = this->W * X;
	netY = Matrix::add(netY, this->B);
	return netY;
}

std::vector<double> Neuron::netK(std::vector<double> Y) //��czna warto�� pobudzenia wynosi netZ=V*Y+C
{
	std::vector<double> netZ;
	netZ = this->V * Y;
	netZ = Matrix::add(netZ, this->C);
	return netZ;
}

std::vector<double> Neuron::f(std::vector<double> net) //funkcja aktywacji (sigmoidalna unipolarna)
{
	double euler = std::exp(1.0);
	for (int i = 0; i < net.size(); i++)
			net[i] = 1 / (1 + std::pow(euler, (this->lambda * net[i] * (-1))));
	return net;
}

std::vector<double> Neuron::derivateF(std::vector<double> net) //pochodna funkcji aktywacji
{
	net = f(net);
	for (int i = 0; i < net.size(); i++)
			net[i] = this->lambda * net[i] * (1 - net[i]);
	return net;
}

std::vector<double> Neuron::delta(std::vector<double> Z, std::vector<double> D, std::vector<double> derivativeF)
{
	std::vector<double> delta;
	for (int k = 0; k < D.size(); k++)
		delta.push_back(derivativeF[k] * (D[k] - Z[k]));
	return delta;
}

std::vector<double> Neuron::rho(std::vector<double> delta, std::vector<double> derivativeF)
{
	std::vector<double> rho;
	double temp;
	for (int j = 0; j < this->j; j++) {
		temp = 0.0;
		for (int k = 0; k < Neuron::k; k++) {
			temp += this->V.matrix[k][j] * delta[k];
			rho.push_back(derivativeF[k] * temp);
		}
	}
	return rho;
}

void Neuron::updateWeights(std::vector<double> delta, std::vector<double> rho, std::vector<double> X, std::vector<double> Y)
{
	double temp;
	//aktualizacja macierzy V i wektora C:
	for (int k = 0; k < Neuron::k; k++) {
		temp = this->eta * delta[k];
		for (int j = 0; j < this->V.matrix[0].size(); j++) {
			this->V.matrix[k][j] += temp * Y[j]; //macierz V
		}
		this->C[k] += temp; //wektor C
	}
	//aktualizacja macierzy W i wektora B:
	for (int j = 0; j < this->j; j++) {
		temp = this->eta * rho[j];
		for (int n = 0; n < this->W.matrix[0].size(); n++)
			this->W.matrix[j][n] += temp * X[n]; //macierz W
		this->B[j] += temp; //wektor B
	}
}

double Neuron::errorFunction(Matrix allZ, bool flag, double& efficiency, double& bit_efficiency) //E=0.5 sum(i->winelist.size)(sum(j->number of outputs)(d[i][j]-y[i][j])^2))
{
	//flaga na 1 - tryb uczenia, flaga na 0 - tryb testowania
	std::vector<Wine> samples;
	if (flag) samples = Wine::trainingData;
	else samples = Wine::testData;

	efficiency = 0.0;
	bit_efficiency = 0.0;
	double E = 0.0;
	for (int i = 0; i < samples.size(); i++) {
		if (samples[i].typeInt == Statistics::outputAsNumber(allZ.matrix[i])) efficiency += 1; //sprawdzenie efektywno�ci sieci
		else efficiency += 0.0;
		for (int j = 0; j < Neuron::k; j++) {
			if (samples[i].type[j] == std::round(allZ.matrix[i][j])) bit_efficiency += 1;
			else bit_efficiency += 0.0;
			E += std::pow((samples[i].type[j] - allZ.matrix[i][j]), 2);
		}
	}
	efficiency /= samples.size();
	efficiency *= 100;

	bit_efficiency /= samples.size();
	bit_efficiency *= 50; //2 bity na przyk�ad, wi�c /2 i *100, bo 100%
	return E/2;
}

void Neuron::learn(std::string nazwa_pliku)
{
	//Otwarcie pliku do zapisu danych:
	std::ofstream plik(nazwa_pliku.c_str());
	if (!plik) throw "plik sie nie otworzyl";

	plik << "Parametry neuronu: lambda = " << this->lambda << ", wsp. uczenia = " << this->eta << ", liczba neuronow = " << this->j << std::endl;

	//inicjalizacja zmiennych pomocniczych:
	std::vector<double> Y, Z; //wektory wyj�ciowe poszczeg�lnych warstw
	Matrix allZ; //wektor wszystkich odpowiedzi z danej epoki
	double E, E_before, E_after; //warto�ci funkcji b��du - dla danych treningowych, dla testowych przed epok� i dla testowych po epoce uczenia
	std::vector<double> delta, rho; //warto�ci b��d�w poszczeg�lnych warstw
	std::vector<double> derivativeF, netK; //pochodna funkcji aktywacji i warto�� pobudzenia dla warstwy wyj�ciowej
	Matrix W_old, V_old; //stare warto�ci w macierzach wag - do por�wnania czy spe�niaj� warunek ko�ca uczenia
	int x = 0; //licznik epok uczenia
	bool flag = false; //flaga pomocnicza dla p�tli while
	double efficiency, bit_efficiency; //efektywno�� w rozpoznawaniu typu i konkretnych bit�w

	//funkcja b��du dla danych testowych przed rozpocz�ciem nauki:
	for (int i = 0; i < Wine::testData.size(); i++) {
		Y = Neuron::f(Neuron::netJ(Wine::testData[i].parameters)); //wyj�cie warstwy ukrytej
		Z = Neuron::f(Neuron::netK(Y)); //wyj�cie sieci
		allZ.matrix.push_back(Z);
	}
	E_before = errorFunction(allZ, 0, efficiency, bit_efficiency);
	allZ.matrix.clear();

	plik << "Efektywnosc rozpoznawania typu i bitowa przed nauka: " << efficiency << " i " << bit_efficiency << std::endl;
	plik << "Wartosc funkcji bledu dla danych testowych przed rozpoczeciem nauki: " << E_before << std::endl;
	plik << "Wartosc funkcji bledu dla danych treningowych:" << std::endl;

	//rozpocz�cie nauki:
	do {
		for (int i = 0; i < Wine::trainingData.size(); i++) { //dla ka�dego przyk�adu treningowego: <- ta p�tla to jedna pe�na epoka uczenia
			Y = Neuron::f(Neuron::netJ(Wine::trainingData[i].parameters)); //wyj�cie warstwy ukrytej
			netK = Neuron::netK(Y);
			derivativeF = Neuron::derivateF(netK);
			Z = Neuron::f(netK); //wyj�cie sieci
			allZ.matrix.push_back(Z); //zapis wynik�w do macierzy pomocniczej
			delta = Neuron::delta(Z, Wine::trainingData[i].type, derivativeF); //wyznaczanie b��du warstwy wyj�ciowej
			rho = Neuron::rho(delta, derivativeF); //wyznaczenie b��du warstwy ukrytej (propagacja)
			updateWeights(delta, rho, Wine::trainingData[i].parameters, Y);
		}
		allZ.matrix.clear();
		//funkcja b��du dla danych treningowych
		for (int i = 0; i < Wine::trainingData.size(); i++) {
			Y = Neuron::f(Neuron::netJ((Wine::trainingData[i]).parameters)); //wyj�cie warstwy ukrytej
			Z = Neuron::f(Neuron::netK(Y)); //wyj�cie sieci
			allZ.matrix.push_back(Z);
		}
		E = errorFunction(allZ, 1, efficiency, bit_efficiency);

		plik << E << " " << efficiency << " " << bit_efficiency << " ";

		x++; //liczba przeprowadzonych epok
		if(this->shuffle) Statistics::shuffleTrainingData(); //przetasowanie danych treningowych
		allZ.matrix.clear(); //zerowanie wynik�w

		//funkcja b��du dla danych testowych po zako�czeniu epoki:
		for (int i = 0; i < Wine::testData.size(); i++) {
			Y = Neuron::f(Neuron::netJ((Wine::testData[i]).parameters)); //wyj�cie warstwy ukrytej
			Z = Neuron::f(Neuron::netK(Y)); //wyj�cie sieci
			allZ.matrix.push_back(Z);
		}
		E_after = errorFunction(allZ, 0, efficiency, bit_efficiency);

		plik << E_after << " " << efficiency << " " << bit_efficiency << std::endl;

		//sprawdzenie, czy zmieni�y si� wagi:
		if (W != W_old || V != V_old) flag = true;
	} while (E >= Neuron::Emin && !flag && x < this->max_cycles); //warunki zako�czenia uczenia

	std::cout << "Wartosc bledu przed rozpoczeciem uczenia wynosila: " << E_before << std::endl;
	std::cout << "Zakonczono nauke po: " << x << " epokach" << std::endl;
	std::cout << "E = " << E << std::endl;
	std::cout << "Blad po zakonczeniu uczenia: " << E_after << std::endl;
	std::cout << "j = " << this->j << " lambda = " << this->lambda << " eta = " << this->eta << std::endl;

	plik << x;
	plik.close(); //zamkni�cie pliku po zapisie wszystkich danych
	//KONIEC NAUKI
}
