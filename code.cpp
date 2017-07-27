
/* 
 * Copyright (C) 2015 Artur Szajdecki <artur.szajdecki@yandex.ru>
 * 
 * Dany program został napisany na potrzeby Projektu indywidualnego.
 * 
 * Działanie programu jest następujące, pierw program wymaga żeby 
 * użytkownik podał współrzędne początkowe linii 3D,
 * współrzędne końcowe linii 3D, później pogram w terminalu wyświetla
 * po kolej zmienne punktów które są odpowiedzialne za tworzenie
 * linii, po zakończeniu wyświetlania w terminalu, program wygenerował,
 * obrazek o nazwie 'Graph.png', na której jest dokładnie narysowana 
 * linia w 3W w przestrzeni barw RGB.
 * 
 * Program używa do wygenerowania obrazka bibliotek MathGL 2.3.1
 * (dokumentacja jest zawarta z plikiem), oraz są używane std
 * biblioteki strumieni i ciągów tekstowych.
 * 
 * Strona MathGL: 
 * http://mathgl.sourceforge.net/doc_en/Main.html
 * 
 * Z tej strony można pobrać MathGL:
 * http://mathgl.sourceforge.net/doc_en/Download.html 
 * 
 * Kod programu był kompilowany, kompilatorem GCC G++ 4.8.3 Linux.
 * Oraz uruchamiany na Dystrybucji GNU Ubuntu 14.04.
 * 
 */
 
// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

#include <mgl2/mgl.h>
#include <iostream> 
#include <string>
#include <sstream>
using namespace std;




/* Deklaracja obiektu typu mglGraph z biblioteki mgl (MathGL),
 * ten obiekt prezentuje układ 3W przestrzeni barw RGB.*/
mglGraph graph;
/* Deklaracja obiektów typu mglData które mają służyć jako
 * punkty układu 3W. */
mglData x(1);
mglData y(1);
mglData z(1);
/* Deklaracja obiektu mglData, który służy do ustalania rozmiaru
 * punktów */
mglData size(1);


/* Jest to procedura inicjalizująca układ 3W przestrzeni barw, posługująca sie
 * funkcjami z biblioteki MathGL, argumenty ten funkcji prezentują
 * wielkość układu w 3W. */
void InitMGLRGB(const int x1, const int y1, const int z1, const int x2, const int y2, const int z2)
{
	// metoda SetRangers ustala przedziały dla wykresu 3W
	graph.SetRanges(mglPoint(x1, y1, z1), mglPoint(x2, y2, z2));
	// metoda Rotate 'obraca' wykresem, żebyśmy mogli zobaczyć
	// układ z perspektywy 3 Wymiarów
	//! Jesli bedzie potrzeba ukladu w 2 Wymiarach co pokazuja tylko x
	//! i y i wystarczy skomentowac graph.Rotate(50, 50);
	graph.Rotate(50, 50);
	// metoda Axis, nakłada układy osie
	graph.Axis("x", "r");
	graph.Axis("y", "g");
	graph.Axis("z", "b");
	// metody Label ustalają etykietki dla róźnych osi
	graph.Label('x', "R", 0);
	graph.Label('y', "G", 0);
	graph.Label('z', "B", 0);
}

// Funkcja sluży do konwertowania wartości int na string
std::string ConvertIntToHex(int to_convert)
{
    std::string result;
    std::stringstream ss;
    ss << std::hex <<to_convert;
    ss >> result;
    return result;
}


/* Jest to procedura służąca do zaznaczania punktów na układzie 3W,
 * przestrzeni barw, argumentem jest tablica point, prezentująca punkty
 * przestrzeni barw. */
void Zaznacz_Na_Przestrzeni_Barw (int point[3])
{
	/* operacja dodawania łańcuchów tekstowych dla ustalenia koloru,
	 * dla punkta. */
	std::string str1 = ConvertIntToHex(point[0]);
	std::string str2 = ConvertIntToHex(point[1]);
	std::string str3 = ConvertIntToHex(point[2]);
	if ( str1.size() < 2 ) str1 = "0"+str1;
	if ( str2.size() < 2 ) str2 = "0"+str2;
	if ( str3.size() < 2 ) str3 = "0"+str3;
	std::string rgb = "o!{x"+str1+str2+str3+"}";
	/* metoda Put, służy do wkładanie wartość do obiektów mglData,
	 * w tym przypadku te wartości to są współrzędne układu. */
	x.Put (point[0], 0);
	y.Put (point[1], 0);
	z.Put (point[2], 0);
	size.Put (1.0, 0);
	/* metoda Mark, służy do zaznaczania, punktów na układzie 3W,
	 * punkty są łatwe do przedytowania, zmienne x, y, z są punktami,
	 * danymi do układu, size oznacza rozmiar takich punktów, za to
	 * clr jest to kolor, punkta. */
	graph.Mark(x, y, z, size, rgb.c_str());
	/* dzięki strumieniu cout, możemy pokażywać jak współrzędne się
	 * zmieniają */
	cout << " R: " << point[0]; 
	cout << " G: " << point[1];
	cout << " B: " << point[2] << '\n';
}


/* Procedura, która się wywołuje kiedy dla RE_PYRAMID dla wartości 
 * dx > dy > dz, dzięki d_xy i d_xz, wiemy kiedy powiekszyc punkty
 * o posInc_xy, posInc_xz oraz kiedy dekrementowac o negInc_xy,
 * negInc_xz. */
void RE_LO1(int point[], int d_xy, int d_xz, int posInc_xy, int posInc_xz, int negInc_xy, int negInc_xz, int x2, int y2, int z2)
{
	while ( point[0] < x2 )
	{
		if (d_xy <= 0)
		{
			d_xy = d_xy + posInc_xy;
			if ( d_xz <= 0)
			{
				d_xz = d_xz + posInc_xz;
			}
			else
			{
				d_xz = d_xz + negInc_xz;
				point[2] = point[2] + 1;
			}
		}
		else
		{
			d_xy = d_xy + negInc_xy;
			if ( d_xz <= 0 )
			{
				d_xz = d_xz + posInc_xz;
			}
			else
			{
				d_xz = d_xz + negInc_xz;
				point[2] = point[2] + 1;
			}
			point[1] = point[1] + 1;
		}
		point[0]++;
		// funkcja ktora zaznacza punkty na przestrzeni barw
		Zaznacz_Na_Przestrzeni_Barw(point);
	}
}

/* Procedura, która się wywołuje kiedy dla RE_PYRAMID dla wartości 
 * dx > dz > dy, dzięki d_xy i d_xz, wiemy kiedy powiekszyc punkty
 * o posInc_xy, posInc_xz oraz kiedy dekrementowac o negInc_xy,
 * negInc_xz. */
void RE_LO2(int point[], int d_xy, int d_xz, int posInc_xy, int posInc_xz, int negInc_xy, int negInc_xz, int x2, int y2, int z2)
{
	while ( point[0] < x2 )
	{
		if (d_xz <= 0)
		{
			d_xz = d_xz + posInc_xz;
			if ( d_xy <= 0)
			{
				d_xy = d_xy + posInc_xy;
			}
			else
			{
				d_xy = d_xy + negInc_xy;
				point[1] = point[1] + 1;
			}
		}
		else
		{
			d_xz = d_xz + negInc_xz;
			if ( d_xy <= 0 )
			{
				d_xy = d_xy + posInc_xy;
			}
			else
			{
				d_xy = d_xy + negInc_xy;
				
				point[1] = point[1] + 1;
			}
			point[2] = point[2] + 1;
		}
		point[0]++;
		// funkcja ktora zaznacza punkty na przestrzeni barw
		Zaznacz_Na_Przestrzeni_Barw(point);
	}
}


/* Procedura, która się wywołuje kiedy dla RE_PYRAMID dla wartości 
 * dy > dx > dz, dzięki d_yx i d_yz, wiemy kiedy powiekszyc punkty
 * o posInc_xy, posInc_xz oraz kiedy dekrementowac o negInc_yx,
 * negInc_yz. */
void RE_LO3(int point[], int d_yx, int d_yz, int posInc_yx, int posInc_yz, int negInc_yx, int negInc_yz, int x2, int y2, int z2)
{
	while ( point[1] < y2 )
	{
		if (d_yz <= 0)
		{
			d_yz = d_yz + posInc_yz;
			if ( d_yx <= 0)
			{
				d_yx = d_yx + posInc_yx;
			}
			else
			{
				d_yx = d_yx + negInc_yx;
				point[0] = point[0] + 1;
			}
		}
		else
		{
			d_yz = d_yz + negInc_yz;
			if ( d_yx <= 0)
			{
				d_yx = d_yx + posInc_yx;
			}
			else
			{
				d_yx = d_yx + negInc_yx;
				point[0] = point[0] + 1;
			}
			point[2] = point[2] + 1;
		}
		point[1]++;
		// funkcja ktora zaznacza punkty na przestrzeni barw
		Zaznacz_Na_Przestrzeni_Barw(point);
	}
}

/* Procedura, która się wywołuje kiedy dla RE_PYRAMID dla wartości 
 * dy > dz > dx, dzięki d_yx i d_yz, wiemy kiedy powiekszyc punkty
 * o posInc_xy, posInc_xz oraz kiedy dekrementowac o negInc_yx,
 * negInc_yz. */
void RE_LO4(int point[], int d_yx, int d_yz, int posInc_yx, int posInc_yz, int negInc_yx, int negInc_yz, int x2, int y2, int z2)
{
	while ( point[1] < y2 )
	{
		if (d_yx <= 0)
		{
			d_yx = d_yx + posInc_yx;
			if ( d_yz <= 0)
			{
				d_yz = d_yz + posInc_yz;
			}
			else
			{
				d_yz = d_yz + negInc_yz;
				point[2] = point[2] + 1;
			}
		}
		else
		{
			d_yx = d_yx + negInc_yx;
			if ( d_yz <= 0)
			{
				d_yz = d_yz + posInc_yz;
			}
			else
			{
				d_yz = d_yz + negInc_yz;
				point[2] = point[2] + 1;
			}
			point[0] = point[0] + 1;
		}
		point[1]++;
		// funkcja ktora zaznacza punkty na przestrzeni barw
		Zaznacz_Na_Przestrzeni_Barw(point);
	}
}


/* Procedura, która się wywołuje kiedy dla RE_PYRAMID dla wartości 
 * dz > dx > dy, dzięki d_zx i d_zy, wiemy kiedy powiekszyc punkty
 * o posInc_zy, posInc_zx oraz kiedy dekrementowac o negInc_zy,
 * negInc_zx. */
void RE_LO5(int point[], int d_zx, int d_zy, int posInc_zx, int posInc_zy, int negInc_zx, int negInc_zy, int x2, int y2, int z2)
{
	while ( point[2] < z2 )
	{
		if (d_zx <= 0)
		{
			d_zx = d_zx + posInc_zx;		
			if ( d_zy <= 0)
			{
				d_zy = d_zy + posInc_zy;
			}
			else
			{
				d_zy = d_zy + negInc_zy;
				point[1] = point[1] + 1;
			}
		}
		else
		{
			d_zx = d_zx + negInc_zx;
			if ( d_zy <= 0)
			{
				d_zy = d_zy + posInc_zy;
			}
			else
			{
				d_zy = d_zy + negInc_zy;
				point[1] = point[1] + 1;
			}
			point[0] = point[0] + 1;
		}
		point[2]++;
		// funkcja ktora zaznacza punkty na przestrzeni barw
		Zaznacz_Na_Przestrzeni_Barw(point);
	}
}


/* Procedura, która się wywołuje kiedy dla RE_PYRAMID dla wartości 
 * dz > dy > dx, dzięki d_zx i d_zy, wiemy kiedy powiekszyc punkty
 * o posInc_zy, posInc_zx oraz kiedy dekrementowac o negInc_zy,
 * negInc_zx. */
void RE_LO6(int point[], int d_zx, int d_zy, int posInc_zx, int posInc_zy, int negInc_zx, int negInc_zy, int x2, int y2, int z2)
{
	while ( point[2] < z2 )
	{
		if (d_zy <= 0)
		{
			d_zy = d_zy + posInc_zy;		
			if ( d_zx <= 0)
			{
				d_zx = d_zx + posInc_zx;
			}
			else
			{
				d_zx = d_zx + negInc_zx;
				point[0] = point[0] + 1;
			}
		}
		else
		{
			d_zy = d_zy + negInc_zy;
			if ( d_zx <= 0)
			{
				d_zx = d_zx + posInc_zx;
			}
			else
			{
				d_zx = d_zx + negInc_zx;
				point[0] = point[0] + 1;
			}
			point[1] = point[1] + 1;
		}
		point[2]++;
		// funkcja ktora zaznacza punkty na przestrzeni barw
		Zaznacz_Na_Przestrzeni_Barw(point);
	}
}

/* Jest to procedura która generuje linie prostą w przestrzeni barw
 * RGB. Algorytm tworzy 26-connected line, pierwsze 3 argumenty,
 * prezentują punkt pocżatkowy przestrzeni barw, a trzy pozostałe
 * punkty odpowiadają punktowi koncowemu. */
void RE_PYRAMID(int x1, int y1, int z1, const int x2, const int y2, const int z2)
{ 
	//Deklaracja zmiennych
	int dx, dy, dz;
	int l, m, n;
	int point[3];
	
	//Inicjalizacja tablicy w której będą przechowywane punkty osi
	point[0] = x1;
	point[1] = y1;
	point[2] = z1;
	//Inicjalizacja róźnicy między punktami osi
	dx = x2 - x1;
	dy = y2 - y1;
	dz = z2 - z1; 
	
	//Zaznaczamy pierwszy punkt na przestrzeni barw
	Zaznacz_Na_Przestrzeni_Barw(point);
	
	/* Algorytm na początku sprawdza która z zmiennych l, m, n jest
	 * największą lub równą innej zmiennej, jeśli została ustalona,
	 * takowa zmienna, to instrukcja warunkowa wybierają 
	 * odpowiedni blok. */
	 
	/* Algorytm minimalnie się róźni od algorytmu orginalne, ale 
	 * generuje 26-connected line.*/
	 
	if ((dx >= dy) && (dx >= dz)) //BLOK 1
	{
		// inicjalizacja zmiennych dla największej roznicy dx
		int d_xy = 2*dy - dx; int posInc_xy = 2*dy; int negInc_xy = 2*(dy-dx);
		int d_xz = 2*dz - dx; int posInc_xz = 2*dz; int negInc_xz = 2*(dz-dx);
		// wywołanie procedur do generowania punktów
		if (m >= n) { RE_LO1(point, d_xy, d_xz, posInc_xy, posInc_xz, negInc_xy, negInc_xz, x2, y2, z2); }
		else { RE_LO2(point, d_xy, d_xz, posInc_xy, posInc_xz, negInc_xy, negInc_xz, x2, y2, z2); }
	} 
	else if (dy >= dz) //BLOK 2
	{
		// inicjalizacja zmiennych dla największej roznicy dy
		int d_yx = 2*dx - dy; int posInc_yx = 2*dx; int negInc_yx = 2*(dx-dy);
		int d_yz = 2*dz - dy; int posInc_yz = 2*dz; int negInc_yz = 2*(dz-dy);
		// wywołanie procedur do generowania punktów
		if (l >= n) { RE_LO3(point, d_yx, d_yz, posInc_yx, posInc_yz, negInc_yx, negInc_yz, x2, y2, z2); }
		else { RE_LO4(point, d_yx, d_yz, posInc_yx, posInc_yz, negInc_yx, negInc_yz, x2, y2, z2); }
	} 
	else //BLOK 3
	{
		// inicjalizacja zmiennych dla największej roznicy dz
		int d_zx = 2*dx - dz; int posInc_zx = 2*dx; int negInc_zx = 2*(dx-dz);
		int d_zy = 2*dy - dz; int posInc_zy = 2*dy; int negInc_zy = 2*(dy-dz);
		// wywołanie procedur do generowania punktów
		if (l >= m) { RE_LO5(point, d_zx, d_zy, posInc_zx, posInc_zy, negInc_zx, negInc_zy, x2, y2, z2); }
		else { RE_LO6(point, d_zx, d_zy, posInc_zx, posInc_zy, negInc_zx, negInc_zy, x2, y2, z2); }
	}
	/* Koniec algorytmu */
} 


int main()
{
	unsigned short dane[6]; //x1, y1, z1, x2, y2, z2; 
	string rgb;
	
	/* Obsługa programu */
	/* Uwaga! prosze podawac odpowiednie dane, nie ma obsługi błedu. */
	cout << "\n Witam, Prosze podac wspolrzedne poczatkowe linii:\n";
	cout << "X: "; cin >> dane[0];
	cout << "Y: "; cin >> dane[1];
	cout << "Z: "; cin >> dane[2];
	cout << "\n Prosze teraz podac wspolrzedne koncowe linii:\n";
	cout << "X: "; cin >> dane[3];
	cout << "Y: "; cin >> dane[4];
	cout << "Z: "; cin >> dane[5];
	cout << "\n\nPunkty linii 3D:\n";
	
	// Sprawdzanie danych
	for ( int i = 0; i < 6; i++ ){ if ( dane[i] >= 256 ) return(-1); }
	for ( int i = 0; i < 3; i=i+2 ){ if ( dane[i] >= dane[i+3] ) return(-1);  }
	
	// Instrukcje warunkowe szukające największego i najmiejszego
	int max = dane[0];
	int min = dane[0];
	for ( int i = 1; i < 6; i++ ){ if ( dane[i] > max ) max = dane[i]; }
	for ( int i = 1; i < 6; i++ ){ if ( dane[i] < min ) min = dane[i]; }
	
	// Inicjalizacja układu 3W przestrzeni barw RGB
	InitMGLRGB (min, min, min, max, max, max);
		
	// Rysowanie linii na układzie 3W przestrzeni barw RGB
	RE_PYRAMID (dane[0], dane[1], dane[2], dane[3], dane[4], dane[5]);
	
	// metoda Title ustala tytuł dla wykresu
	string title = "RE PYRAMID ("+to_string(dane[0])+", "+to_string(dane[1])+", "+to_string(dane[2])+", "+to_string(dane[3])+", "+to_string(dane[4])+", "+to_string(dane[5])+")";
	graph.Title(title.c_str());
		
	/* metoda WritePNG Generuje cały ten układ który został stworzony 
	 * do obrazka o nazwie "Graph" i rozszerzeniu png. */
	graph.WritePNG ("Graph.png");
	
	cout << "\nKoniec programu.";
	
	return(0);
}
