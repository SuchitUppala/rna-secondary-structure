#include<iostream>
#include<vector>
#include<string>
#include<utility>
using namespace std;

/// Main class to calculate the final result
class RNAMolecule{

public:

    
    string molecule; //!< RNA molecule represented as a string
    int n; //!< Size of the molecule
    vector<vector<int>> opt; //!< Dp table. opt[i][j] = Maximum number of base pairs in substring (i, j)
    vector<pair<int,int>> secStr; //!< Array to hold secondary strucuture

    /// Default constructor
    RNAMolecule(){
        
    }

    /// Basic Constructor
    /// @param s RNA molecule
    RNAMolecule(string s){
        molecule = s;
        n = (int)s.size();
        opt = vector<vector<int>>(n, vector<int>(n));
    }

    /// Used to check for a valid pair present in RNA molecule
    /// @param a First base of the pair
    /// @param b Second base of the pair
    /// @returns True it's a valid pair, False otherwise
    bool match(char a, char b){
        if((a == 'A' && b == 'U') 
        || (a == 'U' && b == 'A')
        || (a == 'C' && b == 'G')
        || (a == 'G' && b == 'C')){
            return true;
        }
        
        return false;
    }


    /// Main algorithm where the opt table is filled
    void runAlgorithm(){

        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                opt[i][j] = 0;
            }
        }

        for(int k = 5; k <= n - 1; k++){
            for(int i = 0; i < n - k; i++){
                int j = i + k;
                opt[i][j] = opt[i][j-1];
                for(int t = i; t < j - 4; t++){
                    if(match(molecule[j], molecule[t])){
                        if(t != i)
                            opt[i][j] = max(opt[i][j], 1 + opt[i][t-1] + opt[t+1][j-1]);
                        else
                            opt[i][j] = max(opt[i][j], 1 + opt[i+1][j-1]);
                    }
                }
            }
        }

        cout << "Maximum number of base pairs in a secondary structure: " << opt[0][n-1] << endl;
    }

    /// Used to get the base pairs in substring (i, j)
    /// @param i Start index
    /// @param j End index
    void getBasePairs(int i, int j){
        if(j - i <= 4)
            return;
        if(opt[i+1][j] == opt[i][j]){
            getBasePairs(i+1, j);
            return;
        }
        else if(opt[i][j-1] == opt[i][j]){
            getBasePairs(i, j-1);
            return;
        }
        for(int t = i; t < j - 4; t++){
            if(match(molecule[j], molecule[t])){
                int x = 0, y = 0;
                if(t-1 >= 0)
                    x = opt[i][t-1];
                if(t+1 < n && j - 1 >= 0)
                    y = opt[t+1][j-1];
                if(1 + x + y == opt[i][j]){
                    secStr.push_back(make_pair(t, j));
                    cout << "(" << t << "-" << molecule[t] << ", " << j << "-" << molecule[j] << ")" << endl;
                    getBasePairs(i, t-1);
                    getBasePairs(t+1, j-1);
                    break;
                }
            }
        }
    }

};