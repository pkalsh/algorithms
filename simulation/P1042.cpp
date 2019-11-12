#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

const auto DIVIDENUM = 1000000007;

string DNAsource;
int transform_num;
map<string, string> transform_map;
map<string, int> duplicated_check;
vector<vector<int> > all_index_combination;
vector<string> all_combination;
vector<string> all_amino_string;

void init() {
    cin >> DNAsource;
    cin >> transform_num;
    for (int i = 0; i < transform_num; i++) {
        string key, value;
        cin >> key >> value;
        transform_map.insert(make_pair(key, value));
    }
}
void makeCombinationForN(vector<int> indices, int n) {
    vector<int> flags;
    vector<int> index_comb;
    if (n == 0) {
        all_index_combination.push_back({});
        return;
    }

	for(int i = 0; i < n; i++){
		flags.push_back(1);
	}
	for(int i=0; i < indices.size() - n; i++){
		flags.push_back(0);
	}

    sort(flags.begin(), flags.end());

	do{
		for(int i=0; i<flags.size(); i++){
			if(flags[i] == 1){
                index_comb.push_back(indices[i]);
			}
		}
        all_index_combination.push_back(index_comb);
        index_comb = {};
	}while(next_permutation(flags.begin(), flags.end()));
}

void makeAllIndexCombination() {
    vector<int> indices;
    for (int i = 0; i < DNAsource.size(); i++) {
        indices.push_back(i);
    }
    for (int i = 0; i < DNAsource.size() - 2; i++) {
        makeCombinationForN(indices, i);
    }
}
string sliceByIndex(vector<int> indices, string src) {
    string ret = "";
    int indnum = indices.size();
    if (indnum == 0) return src;

    int total_len = src.length() - indnum;
	int last_len = total_len;
    for (int i = 0; i < indnum; i++) {
        if (last_len == 0) return ret;
        int start_idx = (i == 0) ? 0 : indices[i - 1] + 1;
        int slicing_len = (i == 0) ? indices[i] : indices[i] - indices[i - 1] - 1;
        ret += src.substr(start_idx, slicing_len);
        last_len -= slicing_len;
    }
    ret += src.substr(indices.back() + 1, last_len);
    
    return ret;
}

void makeAllCombination() {
    makeAllIndexCombination();

    for (int i = 0; i < all_index_combination.size(); i++) {
        string DNAsliced = sliceByIndex(all_index_combination[i], DNAsource);
        all_combination.push_back(DNAsliced);
    }

}
string transformToAmino(string dna) {
    string ret;
    int codon_num = dna.length() / 3;
    int is_remained = dna.length() % 3;
    if (!is_remained) {
        for (int i = 0; i < codon_num; i++) {
            string codon = dna.substr(3*i, 3);
            if (transform_map.find(codon) == transform_map.end()) {
                return "";
            }
            ret += transform_map.at(codon);
        }
    }
    return ret;
}

bool isNotDuplicated(string amino) {
    return duplicated_check.find(amino) == duplicated_check.end();
}

void transformAllCombination() {
    string amino_string;
    for (int i = 0; i < all_combination.size(); i++) {
        amino_string = transformToAmino(all_combination[i]);
        if (amino_string == "") 
            continue;
        if (isNotDuplicated(amino_string)) {
            all_amino_string.push_back(amino_string);
            duplicated_check.insert(make_pair(amino_string, 1));
        }
    }
}

void printTheCount() {
    cout << all_amino_string.size() % DIVIDENUM;
}

int main() {
    init();
    makeAllCombination();
    transformAllCombination();
    printTheCount();
    return 0;
}