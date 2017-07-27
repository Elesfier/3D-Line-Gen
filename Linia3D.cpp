
/* 
 * Autor: Artur Szajdecki
 * 
 * Dany program został napisany na potrzeby Projektu indywidualnego.
 * 
 * Program używa algorytmu Bresenham do wygenerowania linii 3D.
 * Działanie programu jest następujące, pierw program wymaga żeby 
 * użytkownik podał współrzędne początkowe linii 3D,
 * współrzędne końcowe linii 3D oraz podał kod RGB który prezentuje
 * kolor linii/punktów, później pogram w terminalu wyświetla
 * po kolej zmienne punktów które są odpowiedzialne za tworzenie
 * linii, po zakończeniu wyświetlania w terminalu, program wygenerował,
 * obrazek o nazwie 'Graph.png', na której jest dokładnie narysowana 
 * linia w 3W i o danym kolorze RGB.
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

#include <mgl2/mgl.h>
#include <iostream> 
#include <string>
using namespace std;

/* Deklaracja obiektu typu mglGraph z biblioteki mgl (MathGL),
 * ten obiekt prezentuje układ 3W.*/
mglGraph graph;
/* Deklaracja obiektów typu mglData które mają służyć jako
 * punkty układu 3W. */
mglData x(1);
mglData y(1);
mglData z(1);
/* Deklaracja obiektu mglData, który służy do ustalania rozmiaru
 * punktów */
mglData size(1);


/* Jest to procedura inicjalizująca układ 3W, posługująca sie
 * funkcjami z biblioteki MathGL, argumenty ten funkcji prezentują
 * wielkość układu w 3W. */
void InitMGL(const int x1, const int y1, const int z1, const int x2, const int y2, const int z2)
{
	// metoda SetRangers ustala przedziały dla wykresu 3W
	graph.SetRanges(mglPoint(x1, y1, z1), mglPoint(x2, y2, z2));
	// metoda Rotate 'obraca' wykresem, żebyśmy mogli zobaczyć
	// układ z perspektywy 3 Wymiarów
	//! Jesli bedzie potrzeba ukladu w 2 Wymiarach co pokazuja tylko x
	//! i y i wystarczy skomentowac graph.Rotate(50, 50);
	graph.Rotate(50, 50);
	// metoda Axis, nakłada układy osie
	graph.Axis();
	// metody Label ustalają etykietki dla róźnych osi
	graph.Label('x', "x", 0);
	graph.Label('y', "y", 0);
	graph.Label('z', "z", 0);
}

/* Jest to procedura służąca do zaznaczania punktów na układzie 3W,
 * argumentem ten funkcji jest tablica point, prezentująca punkty,
 * oraz parametr prezentujące kolor RGB. */
void Zaznacz_Na_Wykresie (int point[3], string rgb)
{
	/* operacja dodawania łańcuchów tekstowych dla ustalenia koloru,
	 * dla punktów. */
	rgb = "o!{x"+rgb+"}";
	/* metoda Put, służy do wkładanie wartość do obiektów mglData,
	 * w tym przypadku te wartości to są współrzędne układu. */
	x.Put (point[0], 0);
	y.Put (point[1], 0);
	z.Put (point[2], 0);
	size.Put (1.0, 0);
	/* metoda Mark, służy do zaznaczania, punktów na układzie 3W,
	 * punkty są łatwe do przedytowania, zmienne x, y, z są punktami,
	 * danymi do układu, size oznacza rozmiar takich punktów, za to
	 * clr jest to kolor, tych punktów, stała clr została wcześniej
	 * już zainicjalizowana. */
	graph.Mark(x, y, z, size, rgb.c_str());
	/* dzięki strumieniu cout, możemy pokażywać jak współrzędne się
	 * zmieniają */
	cout << " x: " << point[0]; 
	cout << " y: " << point[1];
	cout << " z: " << point[2] << '\n';
}


/* Algorytm linii 3W Bresenham */
/* Przyjmuje 6 parametrów, pierwsze 3 argumenty które trzeba podać,
 * oznaczają początkową pozycje linii w układzie 3W, a 3 następne
 * parametry oznaczają końcową pozycje linii w układzie 3W,
 * za to ostatni parametr prezentuje kolor RGB w zapisie HEX,
 * jest to troszeczkę uszczuplona wersja Bresenham'a, działa tylko
 * dla liczb całkowitych. */
void Linia3D(int x1, int y1, int z1, const int x2, const int y2, const int z2, string rgb)
{ 
	//Deklaracja zmiennych
	int i; 
	int dx, dy, dz;
	int l, m, n;
	int x_inc, y_inc, z_inc;
	int err_1, err_2;
	int dx2, dy2, dz2;
	int point[3];
	
	//Inicjalizacja tablicy w której będą przechowywane punkty osi
	point[0] = x1;
	point[1] = y1;
	point[2] = z1;
	//Inicjalizacja róźnicy między punktami osi
	dx = x2 - x1;
	dy = y2 - y1;
	dz = z2 - z1; 
	//zmienne _inc słuzą do dodawania do tablicy point[]
	//zmienne l, m, n są to wartości bezwględne różnic między punktami
	//użyto tutaj operatora trójargumentowy
	x_inc = (dx < 0) ? -1 : 1;
	l = (dx < 0) ? ((-1)*(dx)) : (dx);
	//l = abs(dx);
	y_inc = (dy < 0) ? -1 : 1;
	m = (dy < 0) ? ((-1)*(dy)) : (dy);
	//m = abs(dy);
	z_inc = (dz < 0) ? -1 : 1;
	n = (dz < 0) ? ((-1)*(dz)) : (dz);
	//n = abs(dz);
	//Inicjalizacja róźnicy 2, dzięki przesunięciu bitowym w lewo o 1,
	//na zmiennych l, m, n
	dx2 = l << 1;
	dy2 = m << 1;
	dz2 = n << 1;
	
	/* Algorytm na początku sprawdza która z zmiennych l, m, n jest
	 * największą lub równą innej zmiennej, jeśli została ustalona,
	 * takowa zmienna, to instrukcja warunkowa wybierają 
	 * odpowiedni blok. */
	 
	/* W Każdym bloku są na początku inicjalizowane zmienne,
	 * err_1 i err_2 są do różnice między dx2, dy2, dz2 a najwiekszą
	 * zmienna z l, m, n, i zależnie od bloku są róźne d2 używane np,
	 * kiedy m jest największą to err_1 będzie równy dx2 - m, a
	 * err_2 będzie równy dz2 - m.*/
	 
	/* Następnie mamy pętlę która się powtarza tyle ile wynosi 
	 * róźnica bezwzględna największej zmiennej,
	 * funkcja Zaznacz_Na_Wykresie() jak sama nazwa wskazuje służy do
	 * zaznaczania punktów na wykresie 3W, definicja funkcji posługuje
	 * się dodatkowymi bibliotekami do generowania grafiki 3D */
	 
	/* Dalej jest powtarzanie pętli, zmienne w tablicy point się
	 * zmieniają zależnie od err_1 i err_2, co później są znowu
	 * wyświetlane, aż pętla skończy się. */
	
	if ((l >= m) && (l >= n)) //BLOK 1
	{

		err_1 = dy2 - l;
		err_2 = dz2 - l;
		
		for (i = 0; i < l; i++) 
		{
			Zaznacz_Na_Wykresie(point, rgb);
			
			if (err_1 > 0) 
			{
				point[1] += y_inc;
				err_1 -= dx2;
			}
			
			if (err_2 > 0) 
			{
				point[2] += z_inc;
				err_2 -= dx2;
			}
			
			err_1 += dy2;
			err_2 += dz2;
			point[0] += x_inc;
		}
	} 
	else if ((m >= l) && (m >= n)) //BLOK 2
	{

		err_1 = dx2 - m;
		err_2 = dz2 - m;
		
		for (i = 0; i < m; i++) 
		{
			Zaznacz_Na_Wykresie(point, rgb);
			
			if (err_1 > 0) 
			{
				point[0] += x_inc;
				err_1 -= dy2;
			}
			
			if (err_2 > 0) 
			{
				point[2] += z_inc;
				err_2 -= dy2;
			}
			
			err_1 += dx2;
			err_2 += dz2;
			point[1] += y_inc;
		}
	} 
	else //BLOK 3
	{
		
		err_1 = dy2 - n;
		err_2 = dx2 - n;
		
		for (i = 0; i < n; i++) 
		{
			Zaznacz_Na_Wykresie(point, rgb);
			
			if (err_1 > 0) 
			{
				point[1] += y_inc;
				err_1 -= dz2;
			}
			
			if (err_2 > 0) 
			{
				point[0] += x_inc;
				err_2 -= dz2;
			}
			
			err_1 += dy2;
			err_2 += dx2;
			point[2] += z_inc;
		}
	}
	
	/* Na końcu jest zaznacza ostatni punkt linii. */
	Zaznacz_Na_Wykresie(point, rgb);
	/* Koniec algorytmu */
} 


int main()
{
	int x1, y1, z1, x2, y2, z2; 
	string rgb;
	
	/* Obsługa programu */
	/* Uwaga! prosze podawac odpowiednie dane, nie ma obsługi błedu. */
	cout << "\n Witam, Prosze podac wspolrzedne poczatkowe linii:\n";
	cout << "X: "; cin >> x1;
	cout << "Y: "; cin >> y1;
	cout << "Z: "; cin >> z1;
	cout << "\n Prosze teraz podac wspolrzedne koncowe linii:\n";
	cout << "X: "; cin >> x2;
	cout << "Y: "; cin >> y2;
	cout << "Z: "; cin >> z2;
	cout << "\n A teraz bym poprosil o podanie w HEX, koloru RGB";
	cout << "(może być na np. cd3333 odpowiadajacy czerwonemu):\n";
	cout << "RGB: "; cin >> rgb;
	cout << "\n\nPunkty linii 3D:\n";
	
	// Instrukcje warunkowe szukające największego i najmiejszego
	// posrod zmiennych x1, y1, z1, x2, y2, z2
	int max;
	int min;
	if ( x2 > y2 ){ if ( x2 > z2 ) max = x2; else max = z2; }
	else { if ( y2 > z2 ) max = y2; else max = z2; } 
	if ( x1 < y1 ){ if ( x1 < z1 ) min = x1; else min = z1; }
	else { if ( y1 < z1 ) min = y1; else min = z1; } 
	
	// Inicjalizacja układu 3W
	InitMGL (min-10, min-10, min-10, max+10, max+10, max+10);
		
	// Rysowanie linii na układzie 3W
	Linia3D (x1, y1, z1, x2, y2, z2, rgb);
	
	// metoda Title ustala tytuł dla wykresu
	string title = "Linia3D ("+to_string(x1)+", "+to_string(y1)+", "+to_string(z1)+", "+to_string(x2)+", "+to_string(y2)+", "+to_string(z2)+", "+rgb+")";
	graph.Title(title.c_str());
		
	/* metoda WritePNG Generuje cały ten układ który został stworzony 
	 * do obrazka o nazwie "Graph" i rozszerzeniu png. */
	graph.WritePNG ("Graph.png");
	
	cout << "\nKoniec programu.";
	system("pause");
	
	return(0);
}
