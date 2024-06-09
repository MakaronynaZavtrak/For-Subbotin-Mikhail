#include <iostream>
#include <limits>
#include "Vectors.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "RUS");
	std::cout << "Введите координаты начальной точки" << endl;
	double x, y, z;
	cin >> x >> y >> z;

	while (x < 0 || x > 1 || y < 0 || y > 1 || z < 0 || z > 1)
	{
		std::cout << "Ошибка! Точка находится вне куба! Попробуйте еще раз!" << endl;
		cin >> x >> y >> z;
	}

	Vectors point(x, y, z);

	std::cout << "Введите вектор скорости" << endl;
	double speedX, speedY, speedZ;
	cin >> speedX >> speedY >> speedZ;

	std::cout << "Введите время T большое" << endl;
	double T;
	cin >> T;

	if (!speedX && !speedY && !speedZ)
	{
		std::cout << "Положение куба в момент T:" << '(' << x << ", " << y << ", " << z << ')';
		return 0;
	}

	Vectors speed(speedX, speedY, speedZ);
	double currentTime = 0;
	Vectors newPosition;
	double t = 0;
	double Epsilon = numeric_limits<double>::epsilon() * pow(10, 10);

	while (currentTime < T)
	{
		newPosition = add(point, speed);

		//в данном блоке ветвлений находится максимальное значене для переменной  t
		//она отвечает за время полёта атома за границей куба
		if (newPosition.x > 1)
			if ((newPosition.x - 1) / speed.x > t)
			{
				t = (newPosition.x - 1) / speed.x;
			}
		if (newPosition.x < 0)
			if (newPosition.x / speed.x > t)
			{
				t = newPosition.x / speed.x;
			}
		if (newPosition.y > 1)
			if ((newPosition.y - 1) / speed.y > t)
			{
				t = (newPosition.y - 1) / speed.y;
			}
		if (newPosition.y < 0)
			if (newPosition.y / speed.y > t)
			{
				t = newPosition.y / speed.y;
			}
		if (newPosition.z > 1)
			if ((newPosition.z - 1) / speed.z > t)
			{
				t = (newPosition.z - 1) / speed.z;
			}
		if (newPosition.z < 0)
			if (newPosition.z / speed.z > t)
			{
				t = newPosition.z / speed.z;
			}

		newPosition = sub(newPosition, mulByScalar(t, speed));

		if (newPosition.x - Epsilon <= 0)
			newPosition.x = 0;

		if (newPosition.x + Epsilon >= 1)
			newPosition.x = 1;

		if (newPosition.y - Epsilon <= 0)
			newPosition.y = 0;

		if (newPosition.y + Epsilon >= 1)
			newPosition.y = 1;

		if (newPosition.z - Epsilon <= 0)
			newPosition.z = 0;

		if (newPosition.z + Epsilon >= 1)
			newPosition.z = 1;


		//случай, если атом не долетел до границы куба в момент T
		if (currentTime + 1 - t >= T)
		{
			point = sub(newPosition, mulByScalar(currentTime + 1 - t - T, speed));

			if (point.x - Epsilon <= 0)
				point.x = 0;

			if (point.x + Epsilon >= 1)
				point.x = 1;

			if (point.y - Epsilon <= 0)
				point.y = 0;

			if (point.y + Epsilon >= 1)
				point.y = 1;

			if (point.z - Epsilon <= 0)
				point.z = 0;

			if (point.z + Epsilon >= 1)
				point.z = 1;

			break;
		}

		Vectors normal = add(mulByScalar(newPosition.x == 0, Vectors(1, 0, 0)), add(mulByScalar(newPosition.x == 1, Vectors(-1, 0, 0)), add(mulByScalar(newPosition.y == 0, Vectors(0, 1, 0)), add(mulByScalar(newPosition.y == 1, Vectors(0, -1, 0)), add(mulByScalar(newPosition.z == 0, Vectors(0, 0, 1)), mulByScalar(newPosition.z == 1, Vectors(0, 0, -1)))))));

		if (!speed.x)
			normal.x = 0;
		if (!speed.y)
			normal.y = 0;
		if (!speed.z)
			normal.z = 0;

		if (vectorLength(normal) > 1)
			normal = normalize(normal);

		/*Vectors proj = mulByScalar(normal, scalMul(normal, speed));*/
		//Vectors rej = sub(speed, proj);// = sub(speed, mulByScalar(normal, scalMul(normal, speed)))
		//Vectors reflect = sub(mulByScalar(2, rej), speed);// = sub()


		speed = sub(mulByScalar(2, sub(speed, mulByScalar(normal, scalMul(normal, speed)))), speed);
		
		//выражение ниже тоже является верным в нахождении отражения вектора скорости
		/*speed = sub(speed, mulByScalar(normal, 2 * scalMul(speed, normal)));*/


		currentTime += 1 - t;
			

		t = 0;
		point = newPosition;
	}

	std::cout << "Положение атома в момент T:" << '(' << point.x << ", " << point.y << ", " << point.z << ')';

	return 0;
}
