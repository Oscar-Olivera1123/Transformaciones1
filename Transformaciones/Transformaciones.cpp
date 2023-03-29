##include <iostream>
#include <GL/glut.h>
#include <math.h>

using namespace std;
#define PI 3,1416
int ancho = 800, alto = 800;
double Figura[4][3] = { {100,300,1}, {300,300,1}, {300,100,1}, {100,100,1} }, escale[4][3], Aux[4][3], Aux2[4][3];
double pivote_x = Figura[0][0], pivote_p = Figura[0][0], pivote_y = Figura[0][1];
void PintaPixel(int x, int y) {
	glPointSize(3);
	glColor3f(0, 1, 1);
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
	glFlush();

}
void Pasar() {
	for (int a = 0; a < 4; a++) {
		Aux[a][0] = Figura[a][0];
		Aux[a][1] = Figura[a][1];
		Aux[a][2] = Figura[a][2];
		Aux2[a][0] = Figura[a][0];
		Aux2[a][1] = Figura[a][1];
		Aux2[a][2] = Figura[a][2];

	}
}
void PintaLinea(int cx1, int cy1, int cx2, int cy2) {
	int dx, dy, x, y;
	float m, b;
	dx = cx2 - cx1;
	dy = cy2 - cy1;
	if (dx == 0) {
		if (cy1 <= cy2) {
			for (y = cy1; y <= cy2; y++) {
				PintaPixel(cx1, y);
			}
		}
		else {
			for (y = cy2; y <= cy1; y++) {
				PintaPixel(cx1, y);
			}

		}
	}
	if (dy == 0) {
		if (cx1 <= cx2) {
			for (x = cx1; x <= cx2; x++) {
				PintaPixel(x, cy1);
			}
		}
		else {
			for (x = cx2; x <= cx1; x++) {
				PintaPixel(x, cy1);

			}
		}
	}
	else {
		m = (float)dy / (float)dx;
		b = cy1 - (m * cx1);
		if (abs(dx) >= abs(dy)) {
			if (cx1 <= cx2) {
				for (x = cx1; x <= cx2; x++) {
					y = (m * x) + b;
					PintaPixel(x, y);
				}
			}
			else {
				for (x = cx2; x <= cx1; x++) {
					y = (m * x) + b;
					PintaPixel(x, y);

				}
			}
		}
		else {
			if (cy1 <= cy2) {
				for (y = cy1; y <= cy2; y++) {
					x = (y - b) / m;
					PintaPixel(x, y);
				}
			}
			else {
				for (y = cy2; y <= cy1; y++) {
					x = (y - b) / m;
					PintaPixel(x, y);

				}
			}
		}
	}

}
void Multiplicar(double matriz_a[4][3], double matriz_b[3][3]) {
	for (int v = 0; v < 4; v++) {
		for (int j = 0; j < 3; j++) {
			Aux2[v][j] = Aux[v][j];
		}
	}
	for (int v = 0; v < 4; v++) {
		for (int j = 0; j < 3; j++) {
			Aux[v][j] = (matriz_a[v][0] * matriz_b[0][j] * matriz_a[v][1] * matriz_b[1][j]) + (matriz_a[v][2] * matriz_b[2][j]);

		}
	}
	pivote_x = Aux[0][0];
}
void Construir(double Matrizc[4][3]) {
	glClear(GL_COLOR_BUFFER_BIT);
	for (int a = 0; a < 3; a++) {
		PintaLinea(Matrizc[a][0], Matrizc[a][1], Matrizc[a + 1][0], Matrizc[a + 1][1]);
	}
	PintaLinea(Matrizc[3][0], Matrizc[3][1], Matrizc[0][0], Matrizc[0][1]);
}
void Traslacion() {
	double trasla_x = 0, trasla_y = 0, trasla[3][3] = { {1, 0, 0}, {0,1,0}, {trasla_x,trasla_y, 1} };
	for (int v = 0; v < 4; v++) {
		trasla_x = -90;
		trasla_y = 0;
		trasla[2][0] = trasla_x;
		trasla[2][1] = trasla_y;
		Multiplicar(Aux2, trasla);
		Construir(Aux);

	}
	for (int v = 0; v < 4; v++) {
		trasla_x = 0;
		trasla_y = -90;
		trasla[2][0] = trasla_x;
		trasla[2][1] = trasla_y;
		Multiplicar(Aux2, trasla);
		Construir(Aux);
	}
	for (int v = 0; v < 4; v++) {
		trasla_x = 90;
		trasla_y = 0;
		trasla[2][0] = trasla_x;
		trasla[2][1] = trasla_y;
		Multiplicar(Aux2, trasla);
		Construir(Aux);
	}
	for (int v = 0; v < 4; v++) {
		trasla_x = 0;
		trasla_y = 90;
		trasla[2][0] = trasla_x;
		trasla[2][1] = trasla_y;
		Multiplicar(Aux2, trasla);
		Construir(Aux);
	}
}
void escala() {
	for (float a = 0.1; a < 0.4; a += 0.1) {
		escale[0][0] = Figura[0][0] - (Figura[0][0] * a);
		escale[0][1] = Figura[0][1] + (Figura[0][1] * a);
		escale[0][2] = Figura[0][2];
		escale[1][0] = Figura[1][0] + (Figura[1][0] * a);
		escale[1][1] = Figura[1][1] + (Figura[1][1] * a);
		escale[1][2] = Figura[1][2];
		escale[2][0] = Figura[2][0] + (Figura[2][0] * a);
		escale[2][1] = Figura[2][1] - (Figura[2][1] * a);
		escale[2][2] = Figura[2][2];
		escale[3][0] = Figura[3][0] - (Figura[3][0] * a);
		escale[3][1] = Figura[3][1] - (Figura[3][1] * a);
		escale[3][2] = Figura[3][2];
		Construir(escale);
	}
}
void escalaneg() {
	for (float a = 0.1; a < 0.4; a += 0.5) {
		escale[0][0] = Figura[0][0] + (Figura[0][0] * a);
		escale[0][1] = Figura[0][1] - (Figura[0][1] * a);
		escale[0][2] = Figura[0][2];
		escale[1][0] = Figura[1][0] - (Figura[1][0] * a);
		escale[1][1] = Figura[1][1] - (Figura[1][1] * a);
		escale[1][2] = Figura[1][2];
		escale[2][0] = Figura[2][0] - (Figura[2][0] * a);
		escale[2][1] = Figura[2][1] + (Figura[2][1] * a);
		escale[2][2] = Figura[2][2];
		escale[3][0] = Figura[3][0] + (Figura[3][0] * a);
		escale[3][1] = Figura[3][1] + (Figura[3][1] * a);
		escale[3][2] = Figura[3][2];
		Construir(escale);
	}
}
void Rotacion() {
	double angulo = 0, matriz_r[3][3] = { {cos(angulo), -sin(angulo),1},{ sin(angulo),cos(angulo),1 },{0,0,1} };
	pivote_p = Aux[0][0];
	do {
		angulo = (15 * PI) / 180;
		matriz_r[0][0] = cos(angulo);
		matriz_r[0][1] = -sin(angulo);
		matriz_r[1][0] = sin(angulo);
		matriz_r[1][1] = cos(angulo);
		Multiplicar(Aux2, matriz_r);
		Construir(Aux);
	} while (round(pivote_x) != round(pivote_p));
}
void reflectX1() {
	double Figurac2[4][3] = { {-100, 300,1,},
		{-300, 300,1},
		{-300, 100,1},
		{-100, 100,1} };
	Construir(Figurac2);
}
void reflectX2() {
	double Figurac3[4][3] = { {-100, -300,1,},
		{-300, -300,1},
		{-300, -100,1},
		{-100, -100,1} };
	Construir(Figurac3);
}
void reflectX3() {
	double Figurac4[4][3] = { {100, -300,1,},
		{300, -300,1},
		{300, -100,1},
		{ 100, -100,1} };
	Construir(Figurac4);
}
void Display() {
	Pasar();
	Construir(Figura);
}
void Teclado(unsigned char k, int x, int y) {
	switch (k)
	{
	case 't':
		Traslacion();
		break;
	case 'r':
		Rotacion();
		break;
	case 'e':
		escala();
		break;
	case 'u':
		escalaneg();
		break;
	case 'v':
		reflectX1();
		break;
	case 'f':
		reflectX2();
		break;
	case 'h':
		reflectX3();
		break;
	case 'd':
		Construir(Figura);
		break;
	default:
		break;
	}
}
int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutInitWindowSize(ancho, alto);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Transformaciones");
	gluOrtho2D(-ancho / 2, ancho / 2, -alto / 2, alto / 2);
	glutDisplayFunc(Display);
	glutKeyboardFunc(Teclado);
	glutMainLoop();
	return 0;
}