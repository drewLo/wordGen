/*
  Word Gen v1.0
  Author: Drew Lough <drew.lough@gmail.com>
  A procedural word generator.
*/

/*
  Notes: at this time I'm going to get the generator working (ie. running the program outputs a procedurally generated word).

  TODO:
  - [ ] organize vowels and consonants into a data structure.
  - [ ] use random's facilities to:
      - [ ] get a number of phonemes to use:
      - 'syllables' are delimited by consonants: >1, <6.
      - [ ] 'randomly' start with a consonant or vowel
      - [ ] 'randomly' select from the pool of consonants or vowels.
      - [ ] ** optional: if the consonant or vowel is a dipthong, make it possible to to choose another vowel or consonant.
  - [ ] 
  - [ ] command line parsing tool
 */

//#include "phonemes.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <random>

using std::vector;
using std::string;

namespace wordgen {
  struct option {
    int length;
  };
  struct parameter {
    string current_phoneme_type;
  }
}

vector<string> consonant = {"b","c","ch","d",
                            "f","g","gh","h",
                            "j","k","l","m","n","ng"
                            "p","ph","qu","r","s","sh","t","th",
                            "v","w","x","y","z"};

vector<string> vowel = {"a","ae","ah","ai",
                        "e","ee","ei",
                        "i","ie",
                        "o","oh","oo",
                        "u"};

int get_random(const int& min, const int& max) {
  std::random_device r;
  std::default_random_engine eng(r());
  return std::uniform_int_distribution<int> {min, max} (eng);
}

string random_begin(){
  string beginning;
  int flip = get_random(1,2);
  if (flip == 1) beginning = "consonant";
  else if (flip == 2) beginning = "vowel";
  return beginning;
}

string random_consonant(){
  return consonant.at(get_random(0,consonant.size() - 1));
}

string random_vowel(){
  return vowel.at(get_random(0,vowel.size() -1));
}

string get_random_phoneme(){
  string begin = random_begin();
  if (begin == "consonant"){
    
  }

}


string gen_word(int length){
  string word;
  string phoneme;
  for (int i = 0; i < length; ++i){
    phoneme = get_random_phoneme();
    word.push_back(phoneme);
  }
  return word;
}


int main(){
  // for (int i = 0; i < vowel.size(); ++i) {
  //   std::cout << vowel.at(i) << " ";
  // }

  return 0;
}
