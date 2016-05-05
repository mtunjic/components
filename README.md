## STL++ 
 Algorithms &amp; Iterator Adaptors

### Algorithms

* split
* random
* randomize
* find_all
* random_iota
* apply
* find_backward
* find_if_backward
* find_if_not_backward
* remove_if_not 
* remove_if_not_backward
* keep_if
* slide (by Sean Parent)
* gather (by Sean Parent)
* min_max (by A. Stepanov and I. Pohl)

### Data Structures
* tape
* rope
* slice
* htable
* grid
* graph
* dynamic_pqueue

### Iterator Adaptors
* numeric_range
* step_range

### Functors
* conversion
* square_root
* vowel
* multiplies
* cube_root_pow
* root
* norm


``` cpp
// random
using card = int;
std::array<card, 52> deck{};
std::iota(begin(deck), end(deck), 0);
// Shuffle the deck:
mt::randomize(deck);
print(deck);
	
int rInt = mt::pick_a_number(5, 15);
double rDouble = mt::pick_a_number(0.5, 5.0);
std::cout << "Random int: " << rInt << "\nRandom double: " << rDouble << '\n';


// random range
std::vector<double> rd(15);
mt::random(rd, 5.0, 0.5); // gen radnom range with min and max limit
print(rd);

	
	
// split
std::string line {"man,meal,moon;fat,food,feel;cat,coat,cook;love,leg,lunch"};
	
// split string to any container
std::vector<std::string> vec_words;
std::list<std::string> list_words;
	
mt::split(line, ";", vec_words);
mt::split(line, ",;.", list_words);
	
print(vec_words);
print(list_words);

``` 

