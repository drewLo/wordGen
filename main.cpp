/*
  Word Gen v1.0
  Author: Drew Lough <drew.lough@gmail.com>
  A procedural word generator.
*/


//#include "phonemes.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <random>

using std::vector;
using std::string;

namespace settings
{
  struct option {
    int length;
  };
  struct state {
    int current_phoneme_type;
    bool previous;
  };
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

int get_random_value(const int& min, const int& max)
{
  std::random_device r;
  std::default_random_engine eng(r());
  return std::uniform_int_distribution<int> {min, max} (eng);
}

string random_consonant()
{
  return consonant.at(get_random_value(0,consonant.size() - 1));
}

string random_vowel()
{
  return vowel.at(get_random_value(0,vowel.size() -1));
}

string get_first()
{
  string first_phoneme;
  int flip = get_random_value(1,2);
  if (flip == 1) {
    first_phoneme = random_consonant();
  } else if (flip == 2) {
    first_phoneme = random_vowel();
  }
  return first_phoneme;
}

string get_random_phoneme(settings::state& s)
{
  string phoneme;
  if (s.previous) {
    phoneme = random_consonant();
    s.previous = false;
  } else {
    phoneme = random_vowel();
    s.previous = true;
  }
  return phoneme;
}

vector<string> gen_word(const settings::option& o,
                        settings::state& s)
{
  vector<string> word;
  string phoneme;
  for (int i = 0; i < o.length; ++i){
    phoneme = get_random_phoneme(s);
    word.push_back(phoneme);
  }
  return word;
}

void print(vector<string>& word){
  for (size_t i; i < word.size(); ++i) {
    std::cout << word.at(i);
  }
  std::cout << '\n';
}

int main() {
  settings::option opt;
  settings::state state;
  opt.length = get_random_value(2,7);
  auto word = gen_word(opt, state);
  print(word);
  return 0;
}
