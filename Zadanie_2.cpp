//Michał Korzeniewski

#include <iostream>
#include <fstream>
#include <vector>

using namespace::std;

// Struct dp przechowywania punktu
struct Point {
    double x;
    double y;
};

// Iloczyn wektorowy dla wektorów dwuwymiarowych
double cross_product(const Point &O, const Point &A, const Point &B) 
{
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

// Funckja wyszukująca punkty tworzące otoczkę 
vector<Point> find_outer_points(vector<Point> &points) 
{
    vector<Point> result;

    // Znalezienie punktu o największej składowej y
    int top = 0;
    for (int i = 1; i < points.size(); ++i) {
        if (points[i].y > points[top].y) {
            top = i;
        }
    }

    // Tworzenie otoczki rozpoczyna się od "najwyższego" punktu
    int p = top;
    do 
    {
        result.push_back(points[p]);

        // Wybranie następnego punktu do sprawdzenia jako pierwszy w nowym powtórzeniu, mógłby być losowy
        int next = (p + 1) % points.size();
        // Sprawdzenie wszystkich punktów
        for (int i = 0; i < points.size(); ++i) {
            // iloczyn wektorowy: O-ostatni znaleziony punkt, A-najlepszy kandydat, B-następny sprawdzany punkt
            // Jeśli A = B iloczyn = 0 - Nie trzeba dodawać specjalnego warunku
            if (cross_product(points[p], points[next], points[i]) > 0) 
            {
                next = i;
            }
        }
        p = next;

    } 
    // Pętla powtarza się do póki nie wróci do punktu początkowego zamykając otoczkę
    while (p != top);

    return result;
}

int main() 
{
    // Stworzenie strumienia do wczytania pliku - domyślnie o nazwie "input"
    ifstream input("input.txt");
    if (!input) {
        cout<<"Error opening file!"<<endl;
        return 1;
    }

    // Wczytanie liczby punktów
    int p_count;
    input >> p_count;

    vector<Point> points(p_count);

    // Wczytanie punktów
    for (int i = 0; i < p_count; ++i) {
        input >> points[i].x >> points[i].y;
    }

    input.close();

    // Wykonanie głównej funkcji
    vector<Point> result = find_outer_points(points);

    // Wypisanie wyników
    for (int i = 0; i < result.size(); i++) 
    {
        cout << "(" << result[i].x << ", " << result[i].y << ")"<<endl;
    }

    return 0;
}
