#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;


void rref(vector<vector<double>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    int lead = 0;
    for (int r = 0; r < rows; r++) {
        if (cols <= lead) {
            break;
        }

        int i = r;
        while (matrix[i][lead] == 0) {
            i++;
            if (rows == i) {
                i = r;
                lead++;
                if (cols == lead) {
                    break;
                }
            }
        }

        for (int j = 0; j < cols; j++) {
            swap(matrix[i][j], matrix[r][j]);
        }

        double div = matrix[r][lead];
        for (int j = 0; j < cols; j++) {
            matrix[r][j] /= div;
        }

        for (int i = 0; i < rows; i++) {
            if (i != r) {
                double factor = matrix[i][lead];
                for (int j = 0; j < cols; j++) {
                    matrix[i][j] -= factor * matrix[r][j];
                }
            }
        }

        lead++;
    }
}

// Function to calculate the rank of a matrix
int r(const vector<vector<double>>& matrix) {
    int rank1 = 0;
    for (const auto& row : matrix) {
        for (double element : row) {
            if (element != 0) {
                rank1++;
                break;
            }
        }
    }
    return rank1;
}

// Function to print a matrix
void printMatrix(const vector<vector<double>>& matrix) {
    for (const auto& row : matrix) {
        for (double element : row) {
            cout << element << "\t";
        }
        cout << endl;
    }
}
int main(int argc, char* argv[]) {
    
    const char* filename = argv[1];

    
    ifstream file(filename);

   
    if (!file.is_open()) {
        cerr << "0" << filename << endl;
        return 1; // Return an error code
    }

   
    vector<vector<double>> matrix;
    string line;

    while (getline(file, line)) {
        istringstream iss(line);
        vector<double> row;

       
        double value;
        while (iss >> value) {
            row.push_back(value);

            
            if (iss.peek() == ',')
                iss.ignore();
        }

      
        matrix.push_back(row);
    }
    file.close();
    rref(matrix);
    printMatrix(matrix);
    int a = r(matrix);
    cout << "\nRank (Ab): " << a << endl;
    return 0; 
}
