#include <GL/glut.h>
#include<iostream>
using namespace std;

void displayMatrix(GLdouble* m) {
    int incr = 4;
    for (int col = 0; col < 4; col++)
    {
        for (int row = 0; row < 4; row++)
        {
            cout << m[col + row * incr] << " ";
        }
        cout << endl;
    }
    cout << endl;   
}
void peekAtMatrixCT(void) {
    
    
    GLdouble CT[16];

    glGetDoublev(GL_MODELVIEW_MATRIX, CT);
    displayMatrix(CT);
    return;
}
int main(int argc, char** argv){
    peekAtMatrixCT();
}