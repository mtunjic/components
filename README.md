## STL++ 
Algorithms, Containers &amp; Iterator Adaptors

### Algorithms

- [x] binary_counter (by A. Stepanov)
- [x] split, join
- [x] random
- [ ] slice
- [x] random_iota
- [x] apply
- [ ] apply_until
- [x] find_all
- [x] find_if_n
- [ ] find_if_n_backward
- [x] find_backward
- [ ] find_if_backward
- [ ] find_if_not_backward
- [x] remove_if_not 
- [ ] remove_if_not_backward
- [x] reverse_n (by A. Stepanov)
- [x] reverse_until
- [x] reverse_n_with_buffer
- [x] swap_ranges_n
- [x] partition_point_n
- [x] stable_partition_position
- [x] copy_n (fixed interface)
- [x] copy_n_with_buffer
- [x] slide (by Sean Parent)
- [x] gather (by Marshall Clow)
- [ ] min_max (by A. Stepanov and I. Pohl)
- [ ] stein_gcd (by A. Stepanov)
- [ ] extended_gcd (by A. Stepanov)
- [ ] psort (hybrid, parallel and adaptive)
- [ ] partial_bucketsort (hybrid with dual graphics cards)
- [ ] binary_insertion_sort_n (by A. Stepanov)
- [ ] upper_bound_n
- [ ] sort_sums (Lambert)
- [x] sort_subrange
- [ ] median_sort
- [ ] zip, unzip, zip_with, zip_n
- [ ] skip, skip_while 
- [ ] take, take_while
- [ ] pairwise 
- [ ] concat
- [ ] transpose
- [ ] intercalate
- [ ] group
- [ ] lines, unlines
- [ ] words, unwords
- [ ] starts_with, end_with
- [ ] shift_by
- [ ] border
- [ ] matches (Knuth–Morris–Pratt)


### Containers
- [ ] Tape
- [ ] Rope
- [ ] Slice
- [ ] Htable
- [ ] Grid
- [ ] Vector2D, Vector3D
- [ ] Graph
- [ ] DynamicPQueue
- [ ] Quadtree

### Iterator Adaptors
- [ ] numeric_iterator
- [ ] step_iterator
- [ ] edge_iterator

### Functors
- [x] conversion
- [x] square_root
- [x] vowel
- [x] multiplies
- [x] divides
- [x] cube_root_pow
- [x] root
- [x] norm
- [x] digit
- [x] plus
- [x] minimum
- [x] less_than, greater_than
- [x] to_lower, to_upper, non_letter
- [x] is_zero
- [x] is_positive, halve_non_negative
- [x] is_odd, is_even
- [x] modulo_multiply
- [x] identity_element

### Vector ext
- [x] keep_if, keep_if_not
- [x] delete_if, delete_if_not
- [x] distinct
- [x] fast_erase
- [x] read, read_nums

### String ext
- [x] trim
- [x] trim_left, trim_right
- [x] trim_right_if, trim_left_if
- [ ] trim_left_copy, trim_right_copy
- [ ] trim_left_copy_if, trim_right_copy_if
- [ ] left_pad, right_pad, center
- [x] to_lower, to_title, to_upper
- [x] to_upper_copy, to_lower_copy
- [ ] chop, chomp
- [x] count, repeat
- [ ] replace, replace_copy  
- [x] reverse, reverse_copy
- [ ] gsub, gsub_copy
- [ ] contains, contains_any
- [x] to, from_string, to_string, to_int, to_single, to_double
- [x] remove, remove_if, remove_if_not, remove_copy_if_not
- [x] has_prefix, has_suffix
- [x] is_digit, is_palindrome, is_alpha, 
- [x] compare_by, eq_ignore_case
- [ ] pluralize
- [x] split, split_copy
- [x] join, join_copy
- [x] has_char, repeat_char, to_chars
- [x] random_string
- [x] setdelim (configure delimiters in the streams)
- [x] letters_copy, numbers_copy, floats_copy (extract values out of a string)

- [x] count_digits, count_letters
- [x] sanitize, sanitize_copy, capitalize
- [x] strip, strip_copy
- [ ] crypt

### Utils
- [ ] to_map, to_list, to_array
- [x] stopwatch
- [x] print_range, print_pair, print_map, print_queue
- [ ] print_tree, print_graph, print_matrix
- [ ] digit_sum
- [x] randomize, pick_a_number
- [x] wait

```sh
> c++ -O3 -std=c++14 main.cpp -o main && ./main
> c++ -O3 -std=c++14 bench.cpp -o bench && ./bench
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

// stable_partition_position
int  a[] = { 1, 2, 3, 4, 5, 5, 4, 3, 2, 1 }; 
bool b[] = { 0, 1, 0, 1, 0, 0, 1, 0, 1, 0 }; // mask for every even 

// divide the even(upfront) and odd(at the end) numbers 
auto pos = mt::stable_partition_position(std::begin(a), std::end(a), [&](auto i) {
	return *(std::begin(b) + (i - std::begin(a)));
});
for (auto f = std::begin(a), l = pos; f != l; ++f) 
	std::cout << *f << " ";
std::cout << "^ ";
for (auto f = pos, l = std::end(a); f != l; ++f) 
	std::cout << *f << " ";
std::cout << std::endl;
// 2 4 4 2 ^ 1 3 5 5 3 1

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
#### String ext
```cpp
// trim_right_if
std::string  s  = "woow!!!!";
std::wstring ws = L"Awesome........";
std::string  sp = "lot of space       ";
trim_right_if(s, '!');   // woow
trim_right_if(sp, ' ');  // Awesome
trim_right_if(ws, L'.'); // lot of space

std::string s1 {"';;;'yep..'';"};s2 = trim_right_if(s1, is_any_of(";,.'")); // yep
s3 = trim_left_if(trim_copy(s1), is_any_of(' '));

std::wstring badstr {L"some,12<script>-1=1test29710-1---,.1888Osss"};
sanitize(badstr); 	 // =>  some12script11test2971011888osss
digits_copy(badstr); // =>  1211297101188810
digits_copy(badstr); // =>  somescripttestOsss

// prefix suffix
std::string uristr {"https://www.google.com"};
	
if (has_prefix(uristr, "https://")) {
	std::cout << "yes!" << std::endl;
}
	
if (has_suffix(uristr, ".com")) {
	std::cout << "yes!" << std::endl;
}


//find
std::string fs {"-some1+2"};
auto p = find_if_backward(fs.begin(), fs.end(), 
						[](const char c) {return c == '+';});
if (p != fs.end())
	std::cout << "\nfound " << *p << "at " 
	          << std::distance(begin(fs), p) << '\n';	
// found + at 6

```

 

