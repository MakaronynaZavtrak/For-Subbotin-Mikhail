#include <iostream>
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

		//случай, если атом не долетел до границы куба в момент T
		if (currentTime + 1 - t >= T)
		{
			point = sub(newPosition, mulByScalar(currentTime + 1 - t - T, speed));
			break;
		}


		Vectors normal;
		//проверка на соударения
		//проверка на удары об угол
		if (!newPosition.x && !newPosition.y && !newPosition.z)
			normal = Vectors(1, 1, 1);
		else if (newPosition.x == 1 && !newPosition.y && !newPosition.z)
			normal = Vectors(-1, 1, 1);
		else if (!newPosition.x && newPosition.y == 1 && !newPosition.z)
			normal = Vectors(1, -1, 1);
		else if (!newPosition.x && !newPosition.y && newPosition.z == 1)
			normal = Vectors(1, 1, -1);
		else if (newPosition.x == 1 && !newPosition.y && newPosition.z == 1)
			normal = Vectors(-1, 1, -1);
		else if (newPosition.x == 1 && newPosition.y == 1 && !newPosition.z)
			normal = Vectors(-1, -1, 1);
		else if (!newPosition.x && newPosition.y == 1 && newPosition.z == 1)
			normal = Vectors(1, -1, -1);
		else if (newPosition.x == 1 && newPosition.y == 1 && newPosition.z == 1)
			normal = Vectors(-1, -1, -1);
		//проверка на ударения об рёбра
		//по координате y
		else if (!newPosition.x && newPosition.y > 0 && newPosition.y < 1 && !newPosition.z)
			normal = Vectors(1, 0, 1);
		else if (!newPosition.x && newPosition.y > 0 && newPosition.y < 1 && newPosition.z == 1)
			normal = Vectors(1, 0, -1);
		else if (newPosition.x == 1 && newPosition.y > 0 && newPosition.y < 1 && !newPosition.z)
			normal = Vectors(-1, 0, 1);
		else if (newPosition.x == 1 && newPosition.y > 0 && newPosition.y < 1 && newPosition.z == 1)
			normal = Vectors(-1, 0, -1);
		//по координате x
		else if (newPosition.x > 0 && newPosition.x < 1 && !newPosition.y && !newPosition.z)
			normal = Vectors(0, 1, 1);
		else if (newPosition.x > 0 && newPosition.x < 1 && newPosition.y == 1 && !newPosition.z)
			normal = Vectors(0, -1, 1);
		else if (newPosition.x > 0 && newPosition.x < 1 && !newPosition.y && newPosition.z == 1)
			normal = Vectors(0, 1, -1);
		else if (newPosition.x > 0 && newPosition.x < 1 && newPosition.y == 1 && newPosition.z == 1)
			normal = Vectors(0, -1, -1);
		//по координате z
		else if (!newPosition.x && !newPosition.y && newPosition.z > 0 && newPosition.z < 1)
			normal = Vectors(1, 1, 0);
		else if (!newPosition.x && newPosition.y == 1 && newPosition.z > 0 && newPosition.z < 1)
			normal = Vectors(1, -1, 0);
		else if (newPosition.x == 1 && !newPosition.y && newPosition.z > 0 && newPosition.z < 1)
			normal = Vectors(-1, 1, 0);
		else if (newPosition.x == 1 && !newPosition.y == 1 && newPosition.z > 0 && newPosition.z < 1)
			normal = Vectors(-1, -1, 0);
		//случаи удара об стенку
		else if (!newPosition.x && newPosition.y > 0 && newPosition.y < 1 && newPosition.z > 0 && newPosition.z < 1)
			normal = Vectors(1, 0, 0);
		else if (newPosition.x == 1 && newPosition.y > 0 && newPosition.y < 1 && newPosition.z > 0 && newPosition.z < 1)
			normal = Vectors(-1, 0, 0);
		else if (newPosition.x > 0 && newPosition.x < 1 && newPosition.y > 0 && newPosition.y < 1 && !newPosition.z)
			normal = Vectors(0, 0, 1);
		else if (newPosition.x > 0 && newPosition.x < 1 && newPosition.y > 0 && newPosition.y < 1 && newPosition.z == 1)
			normal = Vectors(0, 0, -1);
		else if (newPosition.x > 0 && newPosition.x < 1 && !newPosition.y && newPosition.z > 0 && newPosition.z < 1)
			normal = Vectors(0, 1, 0);
		else if (newPosition.x > 0 && newPosition.x < 1 && newPosition.y == 1 && newPosition.z > 0 && newPosition.z < 1)
			normal = Vectors(0, -1, 0);

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
