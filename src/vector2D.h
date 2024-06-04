#pragma once
struct Vector2D
{
	int x{};
	int y{};
	Vector2D(int fila=0, int columna=0) :x(fila), y(columna) {}

	// asignación
	Vector2D operator=(const Vector2D& v) {
		x = v.x;
		y = v.y;
		return *this;
	}
	// comparación
	bool operator==(const Vector2D& v) {
		return (x == v.x && y == v.y ? true : false);
	}
	// suma
	Vector2D operator+(const Vector2D& v) {
		return Vector2D(x + v.x, y + v.y);
	}
	// resta
	Vector2D operator-(const Vector2D& v) {
		return Vector2D(x - v.x, y - v.y);
	}

};
