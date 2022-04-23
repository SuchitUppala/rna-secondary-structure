#include<iostream>
#include<vector>
#include<string>
#include<utility>
#include"RNAMolecule.h"
using namespace std;



int main(){

    cout << "Enter RNA molecule: ";
    string s;
    cin >> s;

    RNAMolecule rna = RNAMolecule(s);

    rna.runAlgorithm();
    rna.getBasePairs(0, (int)s.size() - 1);
}