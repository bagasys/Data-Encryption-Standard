#include <bits/stdc++.h>
using namespace std;

string hex_to_bin(string hex){
  unordered_map <char, string> hex_to_bin_map;
  hex_to_bin_map['0'] = "0000";
  hex_to_bin_map['1'] = "0001";
  hex_to_bin_map['2'] = "0010";
  hex_to_bin_map['3'] = "0011";
  hex_to_bin_map['4'] = "0100";
  hex_to_bin_map['5'] = "0101";
  hex_to_bin_map['6'] = "0110";
  hex_to_bin_map['7'] = "0111";
  hex_to_bin_map['8'] = "1000";
  hex_to_bin_map['9'] = "1001";
  hex_to_bin_map['A'] = "1010";
  hex_to_bin_map['B'] = "1011";
  hex_to_bin_map['C'] = "1100";
  hex_to_bin_map['D'] = "1101";
  hex_to_bin_map['E'] = "1110";
  hex_to_bin_map['F'] = "1111";
  string bin = "";
  for(int i = 0; i < hex.size(); i++){
    bin += hex_to_bin_map[hex[i]];
  }
  return bin;
}

string bin_to_hex(string bin){
  unordered_map<string, string> bin_to_hex_map;
  bin_to_hex_map["0000"] = "0";
  bin_to_hex_map["0001"] = "1";
  bin_to_hex_map["0010"] = "2";
  bin_to_hex_map["0011"] = "3";
  bin_to_hex_map["0100"] = "4";
  bin_to_hex_map["0101"] = "5";
  bin_to_hex_map["0110"] = "6";
  bin_to_hex_map["0111"] = "7";
  bin_to_hex_map["1000"] = "8";
  bin_to_hex_map["1001"] = "9";
  bin_to_hex_map["1010"] = "A";
  bin_to_hex_map["1011"] = "B";
  bin_to_hex_map["1100"] = "C";
  bin_to_hex_map["1101"] = "D";
  bin_to_hex_map["1110"] = "E";
  bin_to_hex_map["1111"] = "F";
  string hex = "";
  for(int i = 0; i < bin.length(); i+=4){
    string key = "";
    for(int j = i; j < i+4; j++){
      key += bin[i];
    }
    hex += bin_to_hex_map[key];
  }
  return hex;
}

string permutate(string s, int* permutation_table, int n){
  string res="";
  for (int i = 0; i < n; i++){
    res += s[arr[i]-1]
  }
  return res;
}

string shift_left(string s, int n_shifts){
  for (int i = 0; i < n_shifts; i++){
    string tmp = "";
    for(int j = 1; j < 28; j++){
      tmp += s[j];
    }
    tmp += s[0];
    s = tmp;
  }
  return s;
}



string encrypt(string plain_text, vector<string> round_key_bin, vector<string> round_key_hex){
  plain_text = hex_to_bin(plain_text);

  int initial_permutation_table[64] = {
    58,50,42,34,26,18,10,2, 
		60,52,44,36,28,20,12,4, 
		62,54,46,38,30,22,14,6, 
		64,56,48,40,32,24,16,8, 
		57,49,41,33,25,17,9,1, 
		59,51,43,35,27,19,11,3, 
		61,53,45,37,29,21,13,5, 
		63,55,47,39,31,23,15,7
  };

  plain_text = permutate(plain_text, initial_permutation_table, 64);

  string left_plain_text = plain_text.substr(0, 32);
  string right_plain_text = plain_text.substr(32,32);

  int expansion_permutation_table[48]= {
    32,1,2,3,4,5,4,5, 
		6,7,8,9,8,9,10,11, 
		12,13,12,13,14,15,16,17, 
		16,17,18,19,20,21,20,21, 
		22,23,24,25,24,25,26,27, 
		28,29,28,29,30,31,32,1 
	};

  int s_box_table[8][4][16]= 
	{{ 
		14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7, 
		0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8, 
		4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0, 
		15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13 
	}, 
	{ 
		15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10, 
		3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5, 
		0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15, 
		13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9 
	}, 


	{ 
		10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8, 
		13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1, 
		13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7, 
		1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12 
	}, 
	{ 
		7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15, 
		13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9, 
		10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4, 
		3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14 
	}, 
	{ 
		2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9, 
		14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6, 
		4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14, 
		11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3 
	}, 
	{ 
		12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11, 
		10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8, 
		9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6, 
		4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13 
	}, 
	{ 
		4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1, 
		13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6, 
		1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2, 
		6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12 
	}, 
	{ 
		13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7, 
		1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2, 
		7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8, 
		2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11 
	}};

  //Straight Permutation Table 
	int straight_permutation_table[32]= 
	{ 16,7,20,21, 
		29,12,28,17, 
		1,15,23,26, 
		5,18,31,10, 
		2,8,24,14, 
		32,27,3,9, 
		19,13,30,6, 
		22,11,4,25 
	}; 

  for (int i = 0; i < 16; i++){
    string right_expanded = permutate(right_plain_text, expansion_permutation_table, 48);

    string x = xor_operation(round_key_bin[i], right_expanded);

    
  }


}






int main(){
  string plain_text, key;

  plain_text = "123456ABCD123456";
  key = "AABB09182736CCDD";

  key = hex_to_bin(key);
  cout << key;
  int initial_permutation_table[64] = {
    58,50,42,34,26,18,10,2, 
		60,52,44,36,28,20,12,4, 
		62,54,46,38,30,22,14,6, 
		64,56,48,40,32,24,16,8, 
		57,49,41,33,25,17,9,1, 
		59,51,43,35,27,19,11,3, 
		61,53,45,37,29,21,13,5, 
		63,55,47,39,31,23,15,7
  }


  //dari 64bits key, diambil 56 bits (tanpa 8 parity bits)
  key = permutate(key, initial_permutation_table, 56)
  
  //tabel jumlah shift bit untuk tiap ronde
  int shift_per_round_table[16] = {
    1, 1, 2, 2, 
		2, 2, 2, 2, 
		1, 2, 2, 2, 
		2, 2, 2, 1 
  };

  //table untuk memilih 48 bits dari 56 bits kunci
  int key_compression_table[48] = {
    14,17,11,24,1,5, 
		3,28,15,6,21,10, 
		23,19,12,4,26,8, 
		16,7,27,20,13,2, 
		41,52,31,37,47,55, 
		30,40,51,45,33,48, 
		44,49,39,56,34,53, 
		46,42,50,36,29,32 
  };

  string left_key = key.substr(0, 28); // idx 0 - 27
  string right_key = key.substr(28, 28) // idx 28 - 55
  
  vector <string> round_key_bin;
  vector <string> round_key_hex;

  //pre compute key untuk ronde-ronde
  for ( int i = 0; i < 16; i++){
    left_key = shift_left(left_key, shift_per_round_table[i]);
    right_key = shift_left(right_key, shift_per_round_table[i]);

    string left_right_key = left_key + right_key;

    string round_key = permutate(left_right_key, key_compression_table, 48);

    round_key_bin.push(round_key);
    round_key_hex.push(bin_to_hex(round_key));
  }

  string cipher_text = encrypt(plain_text, round_key_bin, round_key_hex);

  return 0 ;
}