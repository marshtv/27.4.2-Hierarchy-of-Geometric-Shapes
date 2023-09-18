#include <iostream>
#include <string>
#include <cassert>
#include <cmath>

enum class colors {
	NONE,
	RED,
	GREEN,
	BLUE,
	YELLOW,
	WHITE
};

struct Grid {
	double x = 0.00;
	double y = 0.00;
};

class Shape {
public:
	Grid position = {0.00, 0.00};
	colors color = colors::NONE;

	Shape(double in_pos_x, double in_pos_y) {
		assert(!(in_pos_x < 0.00));
		this->position.x = in_pos_x;
		assert(!(in_pos_y < 0.00));
		this->position.y = in_pos_y;
	}

	Grid getPosition() {
		return this->position;
	}

	colors getColor() {
		return this->color;
	}
};

class Highlight: public Shape {
public:
	double width = 0;
	double height = 0;

	Highlight(double in_pos_x, double in_pos_y, double in_width, double in_height)
		: Shape(in_pos_x, in_pos_y) {
		assert(!(in_width < 0));
		this->width = in_width;
		assert(!(in_height < 0));
		this->height = in_height;
		this->color = colors::NONE;
	}

	double getWidth() {
		return this->width;
	}

	double getHeight() {
		return this->height;
	}

	double getArea() {
		return this->width * this->height;
	}

	void showInfo() {
		std::cout << "Highlight rectangle Info:" << std::endl;
		std::cout << "Width: " << this->width << "Height: " << this->height << std::endl;
		std::cout << "Area: " << this->getArea() << std::endl;
		std::cout << "Position: " << this->position.x << ", " << this->position.y << std::endl;
	}
};

class Circle: public Shape {
public:
	double radius = 0.00;
	Highlight* highlight = nullptr;

	Circle(double in_pos_x, double in_pos_y, double in_radius)
		: Shape(in_pos_x, in_pos_y) {
		assert(!(in_radius < 0));
		this->radius = in_radius;
		this->color = colors::RED;
		this->highlight = new Highlight(in_pos_x, in_pos_y,in_radius + 0.01,in_radius + 0.01);
	}

	double getRadius() {
		return this->radius;
	}

	double getArea() {
		return atan(1) * 4 * radius;
	}
};

class EgilTriangle: public Shape {
	public:
	double side = 0.00;
	Highlight* highlight = nullptr;

	EgilTriangle(double in_pos_x, double in_pos_y, double in_side)
		: Shape(in_pos_x, in_pos_y) {
		assert(!(in_side < 0));
		this->side = in_side;
		this->color = colors::GREEN;
		this->highlight = new Highlight(in_pos_x, in_pos_y,in_side + 0.01,in_side + 0.01);
	}

	double getSide() {
		return this->side;
	}

	double getArea() {
		return side * side * std::sqrt(3) / 4;
	}
};

class Square: public Shape {
	public:
	double side = 0.00;
	Highlight* highlight = nullptr;

	Square(double in_pos_x, double in_pos_y, double in_side)
		: Shape(in_pos_x, in_pos_y) {
		assert(!(in_side < 0));
		this->side = in_side;
		this->color = colors::BLUE;
		this->highlight = new Highlight(in_pos_x, in_pos_y,
						std::sqrt(in_side * in_side + in_side * in_side) + 0.01,
						std::sqrt(in_side * in_side + in_side * in_side) + 0.01);
	}

	double getSide() {
		return this->side;
	}

	double getArea() {
		return side * side;
	}
};

class Rectangle: public Shape {
	public:
	double width = 0.00;
	double height = 0.00;
	Highlight* highlight = nullptr;

	Rectangle(double in_pos_x, double in_pos_y, double in_width, double in_height)
		: Shape(in_pos_x, in_pos_y) {
		assert(!(in_width < 0));
		this->width = in_width;
		assert(!(in_height < 0));
		this->height = in_height;
		this->color = colors::WHITE;
		this->highlight = new Highlight(in_pos_x, in_pos_y,
						std::sqrt(in_width * in_width + in_height * in_height) + 0.01,
						std::sqrt(in_width * in_width + in_height * in_height) + 0.01);
	}

	double getWidth() {
		return this->width;
	}

	double getHeight() {
		return this->height;
	}

	double getArea() {
		return this->width * this->height;
	}
};

std::string inputCommand() {
	std::string in_command;
	std::cout << "Input command (circle/triangle/square/rectangle):";
	std::cin >> in_command;
	return in_command;
}

bool checkValidCommand(std::string check_command) {
	if (check_command != "circle" && check_command != "triangle" &&
		check_command != "square" && check_command != "rectangle" &&
		check_command != "exit")
		return false;
	else
		return true;
}

void inputPosition(double& in_pos_x, double& in_pos_y) {
	std::cout << "Input position (X Y):";
	std::cin >> in_pos_x >> in_pos_y;
	assert(!(in_pos_x < 0) && !(in_pos_y < 0));
}

std::string displayColor(colors in_color) {
	switch ((int)in_color) {
		case 0:
			return "NONE";
		case 1:
			return "RED";
		case 2:
			return "GREEN";
		case 3:
			return "BLUE";
		case 4:
			return "YELLOW";
		case 5:
			return "WHITE";
	}
}

int main() {
	std::cout << "You have 4 commands to create shape:" << std::endl;
	std::cout 	<< '"' << "circle" << '"' << ", " << '"' << "triangle" << '"' << ", "
				<< '"' << "square" << '"' << ", " << '"' << "rectangle" << '"'
				<< '"' << "exit" << '"' << " - for exit program." << std::endl;
	std::cout << "-------------------------------------------" << std::endl;
	std::string command = inputCommand();
	while (!checkValidCommand(command)) {
		command = inputCommand();
	}
	std::cout << "-------------------------------------------" << std::endl;
	while (command != "exit") {
		double in_pos_x, in_pos_y;
		if (command == "circle") {
			inputPosition(in_pos_x, in_pos_y);
			std::cout << "Input radius:";
			double in_radius;
			std::cin >> in_radius;
			assert(!(in_radius < 0));
			auto* circle = new Circle(in_pos_x, in_pos_y, in_radius);
			std::cout << "Color: " << displayColor(circle->getColor()) << std::endl;
			std::cout << "Area: " << circle->getArea() << std::endl;
			circle->highlight->showInfo();

			delete circle;
		}
		if (command == "triangle") {
			inputPosition(in_pos_x, in_pos_y);
			std::cout << "Input side:";
			double in_side;
			std::cin >> in_side;
			assert(!(in_side < 0));
			auto* triangle = new EgilTriangle(in_pos_x, in_pos_y, in_side);
			std::cout << "Color: " << displayColor(triangle->getColor()) << std::endl;
			std::cout << "Area: " << triangle->getArea() << std::endl;
			triangle->highlight->showInfo();

			delete triangle;
		}
		if (command == "square") {
			inputPosition(in_pos_x, in_pos_y);
			std::cout << "Input side:";
			double in_side;
			std::cin >> in_side;
			assert(!(in_side < 0));
			auto* square = new Square(in_pos_x, in_pos_y, in_side);
			std::cout << "Color: " << displayColor(square->getColor()) << std::endl;
			std::cout << "Area: " << square->getArea() << std::endl;
			square->highlight->showInfo();

			delete square;
		}
		if (command == "rectangle") {
			inputPosition(in_pos_x, in_pos_y);
			std::cout << "Input width and height:";
			double in_width, in_height;
			std::cin >> in_width >> in_height;
			assert(!(in_width < 0) && !(in_height < 0));
			auto* rectangle = new Rectangle(in_pos_x, in_pos_y, in_width, in_height);
			std::cout << "Color: " << displayColor(rectangle->getColor()) << std::endl;
			std::cout << "Area: " << rectangle->getArea() << std::endl;
			rectangle->highlight->showInfo();

			delete rectangle;
		}
	}
	std::cout << "-------------------------------------------" << std::endl;
	std::cout << "Exit program. Good by." << std::endl;
	
	return 0;
}
