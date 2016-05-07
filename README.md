## STL++ 
Algorithms &amp; Iterator Adaptors

### Algorithms

* split
* random
* slice
* random_iota
* apply
* apply_until
* find_all
* find_if_n
* find_if_n_backward
* find_backward
* find_if_backward
* find_if_not_backward
* remove_if_not 
* remove_if_not_backward
* reverse_n (by A. Stepanov)
* reverse_n (recursive, for foward iter)
* reverse_until
* reverse_n_with_buffer
* swap_ranges_n
* partition_point_n
* copy_n (fixed interface)
* copy_n_with_buffer
* keep_if, delete_if
* slide (by Sean Parent)
* gather (by Sean Parent)
* min_max (by A. Stepanov and I. Pohl)
* stein_gcd (by A. Stepanov)
* extended_gcd (by A. Stepanov)
* psort (hybrid, parallel and adaptive)
* partial_bucketsort (hybrid with dual graphics cards)
* zip, unzip, zip_with
* concat
* transpose
* intercalate
* group
* lines, unlines
* words, unwords
* starts_with, end_with
* shift_by
* border
* matches (Knuth–Morris–Pratt)
* sortsums (Lambert)

### Data Structures
* tape
* rope
* slice
* htable
* grid
* graph
* dynamic_pqueue

### Iterator Adaptors
* numeric_iterator
* step_iterator

### Functors
* conversion
* square_root
* vowel
* multiplies
* cube_root_pow
* root
* norm

### String Utils
* trim, trim_left, trim_right
* left_pad, right_pad, center
* capitalize, to_lower, to_title, to_upper
* to_chars
* chop, chomp
* count, repeat
* replace, reverse
* gsub
* to, from_string, to_string
* remove_block

### Utils
* to_map, to_list, to_array
* stopwatch
* print_range
* digit_sum
* randomize, pick_a_number
* fast_erase
* wait

```sh
> c++ -O3 -std=c++14 main.cpp -o main && ./main
```

``` cpp
// gather
std::array<int, 10> a10{9,0,1,4,4,0,7,7,8,0};
auto insertPos = std::begin(a10) + 4;

mt::gather(std::begin(a10), std::begin(a10)+10, insertPos, less_than<int>{2});

/*
	Before gather:
  	[ 9, 0, 1, 4, 4, 0, 7, 7, 8, 0 ]
  	After we gather all less than 2:
  	[ 9, 4, 0, 1, 0, 0, 4, 7, 7, 8 ]
 */

// remove_if_not
std::vector<int> v1 {9,0,1,4,4,0,7,7,8,0};
// mark for deletion
auto p = mt::remove_if_not(std::begin(v1), std::end(v1), less_than<int>{5});
v1.erase(p, v1.end());

/* 
	Before remove:
	[ 9, 0, 1, 4, 4, 0, 7, 7, 8, 0 ]
	After remove not less than 5:
	[ 0, 1, 4, 4, 0, 0 ]
*/

// keep_if
std::vector<int> v2 {9,0,1,4,4,0,7,7,8,0};
mt::keep_if(v2, less_than<int>{8});

/*
	Before:
	[ 9, 0, 1, 4, 4, 0, 7, 7, 8, 0 ]
	After keep all less than 8:
	[ 0, 1, 4, 4, 0, 7, 7, 0 ]
*/


// random
using card = int;
std::array<card, 52> deck{};
std::iota(begin(deck), end(deck), 0);
// Shuffle the deck:
mt::randomize(deck);
print(deck);

int rInt = mt::pick_a_number(5, 15);
double rDouble = mt::pick_a_number(0.5, 5.0);


// random range
std::vector<double> rd(15);
mt::random(rd, 5.0, 0.5); // gen radnom range with min and max limit
// [ 5.14483, 4.66518, 4.48297, 5.51647, 4.95101 ]

// split
std::string line {"man,meal,moon;fat,food,feel;cat,coat,cook;love,leg,lunch"};

// split string to any container
std::vector<std::string> vec_words;
std::list<std::string> list_words;

mt::split(line, ";", vec_words);
mt::split(line, ",;.", list_words);

/*

	[ man,meal,moon, 
	fat,food,feel, 
	cat,coat,cook, 
	love,leg,lunch ]

	[ man, meal, moon, fat, food, feel, cat, coat, cook, love, leg, lunch ]
*/

``` 

