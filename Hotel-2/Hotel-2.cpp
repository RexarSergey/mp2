#include <iostream>
#include <time.h>
#include <thread>
#include <mutex>
#include <future>

/* Неугодников Сергей Игоревич
* БПИ 197
* 14 вариант
*/

using namespace std;

//Количество комнат за 200, 400 и 600
int room2 = 10, room4 = 10, room6 = 5;
//Мьютекс
mutex m;

/// <summary>
/// Метод заселения
/// </summary>
/// <param name="money"> деньги </param>
void settlement_to_hotel(int money, int number) {

	this_thread::sleep_for(chrono::milliseconds(500));
	
	//Начало критической секции
	m.lock();
	//Проверяем на наличие свободных комнат в отеле
	if (room2 == 0 && room4 == 0 && room6 == 0) {
		m.unlock();
		return;
	}

	//Проверяем сколько денег у туриста и выдаем вердикт.
	if (room6 != 0 && money >= 600)
	{
		cout << "Tourist " << number << " with " << money << " money took a room for 600.\n\n";
		cout << "There is " << --room6 << " rooms left for 600.\n";
		cout << "There is " << room4 << " rooms left for 400.\n";
		cout << "There is " << room2 << " rooms left for 200.\n\n";
	}
	else
		if (room4 != 0 && money >= 400)
		{
			cout << "Tourist " << number << " with " << money << " money took a room for 400.\n\n";
			cout << "There is " << room6 << " rooms left for 600.\n";
			cout << "There is " << --room4 << " rooms left for 400.\n";
			cout << "There is " << room2 << " rooms left for 200.\n\n";
		}
		else
			if (room2 != 0 && money >= 200)
			{
				cout << "Tourist " << number << " with " << money << " money took a room for 200.\n\n";
				cout << "There is " << room6 << " rooms left for 600.\n";
				cout << "There is " << room4 << " rooms left for 400.\n";
				cout << "There is " << --room2 << " rooms left for 200.\n\n";
			}
			else
			{
				cout << "Tourist " << number << " with " << money << " money went to find another hotel.\n\n";
				cout << "There is " << room6 << " rooms left for 600.\n";
				cout << "There is " << room4 << " rooms left for 400.\n";
				cout << "There is " << room2 << " rooms left for 200.\n\n";
			}
	cout << endl;

	//Конец кретической секции
	m.unlock();
}

/// <summary>
/// Основной код
/// </summary>
/// <returns></returns>
int main()
{
	srand(time(NULL));
	cout << "The hotel is open.\n\n";
	int j = 1;

	//Пока не заполним полностью отель
	while (room2 > 0 || room4 > 0 || room6 > 0)
	{
		//Запускаем по 5 туристов
		for (size_t i = 0; i < 5; i++)
		{
			int money = rand() % 1000 + 1;
			async(settlement_to_hotel, money, j++);
		}
		this_thread::sleep_for(chrono::milliseconds(250));
	}
}
