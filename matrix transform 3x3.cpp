#include <bits/stdc++.h>

using namespace std;

struct Point {
    double e[4] = {0, 0, 0, 1};

    Point(double x = 0, double y = 0, double z = 0) {
        e[0] = x;
        e[1] = y;
        e[2] = z;
        e[3] = 1;
    }
};

struct Matrix {
    double m[4][4] = {0};

    Matrix() {
        for (int i = 0; i < 4; i++)
            m[i][i] = 1;
    }

    Matrix operator*(const Matrix &second) {
        Matrix result;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                result.m[i][j] = 0;
                for (int k = 0; k < 4; k++) {
                    result.m[i][j] += m[i][k] * second.m[k][j];
                }
            }
        }
        return result;
    }

    Point operator*(const Point &p) {
        Point result;
        for (int i = 0; i < 4; i++) {
            result.e[i] = 0;
            for (int j = 0; j < 4; j++) {
                result.e[i] += m[i][j] * p.e[j];
            }
        }
        return result;
    }

    static Matrix translation(double tx, double ty, double tz) {
        Matrix result;
        result.m[0][3] = tx;
        result.m[1][3] = ty;
        result.m[2][3] = tz;
        return result;
    }

    static Matrix scaling(double sx, double sy, double sz) {
        Matrix result;
        result.m[0][0] = sx;
        result.m[1][1] = sy;
        result.m[2][2] = sz;
        return result;
    }

    static Matrix rotationX(double angle) {
        Matrix result;
        double c = cos(angle), s = sin(angle);
        result.m[1][1] = c; result.m[1][2] = -s;
        result.m[2][1] = s; result.m[2][2] = c;
        return result;
    }

    static Matrix rotationY(double angle) {
        Matrix result;
        double c = cos(angle), s = sin(angle);
        result.m[0][0] = c; result.m[0][2] = s;
        result.m[2][0] = -s; result.m[2][2] = c;
        return result;
    }

    static Matrix rotationZ(double angle) {
        Matrix result;
        double c = cos(angle), s = sin(angle);
        result.m[0][0] = c; result.m[0][1] = -s;
        result.m[1][0] = s; result.m[1][1] = c;
        return result;
    }
};

ostream &operator<<(ostream &os, const Matrix &matrix) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            os << matrix.m[i][j] << " ";
        }
        os << endl;
    }
    return os;
}

ostream &operator<<(ostream &os, const Point &p) {
    os << "( " << p.e[0] << "," << p.e[1] << "," << p.e[2] << " )" << endl;
    return os;
}

int main()
{
Point p(1, 2, 3);

    Matrix translate = Matrix::translation(3, 4, 5);
    Matrix scale = Matrix::scaling(2, 2, 2);
    Matrix rotateX = Matrix::rotationX(M_PI / 4);
    Matrix rotateY = Matrix::rotationY(M_PI / 4);
    Matrix rotateZ = Matrix::rotationZ(M_PI / 4);

    cout << "tocka " << p << endl;

    Point p_translated = translate * p;
    cout << "translacija (3,4,5) " << p_translated << endl;

    Point p_scaled = scale * p;
    cout << "skaliranje (2,2,2) " << p_scaled << endl;

    Point p_rotatedX = rotateX * p;
    cout << "rotacija okolu x za pi/4  " << p_rotatedX << endl;

    Point p_rotatedY = rotateY * p;
    cout << "rotacija okolu y za pi/4  " << p_rotatedY << endl;

    Point p_rotatedZ = rotateZ * p;
    cout << "rotacija okolu z za pi/4  " << p_rotatedZ << endl;



       Point p1(1, 2, 3);
    cout << "tocka " << p1;


    Matrix translate1 = Matrix::translation(3, 4, 5);
    cout << "translacija (3,4,5) \n" << translate1;


    Point p_translated1 = translate * p1;
    cout << "tocka po translacija " << p_translated;


    Matrix scale1 = Matrix::scaling(2, 3, 4);
    cout << "skaliranje (2,3,4)\n" << scale1;


    Point p_scaled1 = scale * p_translated;
    cout << "po skaliranje " << p_scaled1;


    Matrix rotateZ1 = Matrix::rotationZ(M_PI / 2);
    cout << "rotacija x (Z-oska, 90 stepeni):\n" << rotateZ1;


    Point p_rotated1 = rotateZ * p_scaled1;
    cout << "po rotacija " << p_rotated1;


    Matrix combined1 = translate * scale * rotateZ;
    cout << "kombinirani transformacii \n" << combined1;


    Point p_final = combined1 * p1;
    cout << "tocka po kombinirani " << p_final;

    return 0;
}
