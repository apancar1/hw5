#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void recursecombos(set<string>& allcombos, string& temp, const string& in, string& floating, size_t index, const set<string>& dict);
set<string> check(const set<string>& allcombos, const set<string>& dict); 


/**
 * @brief Returns the list of all legal words in the provided dictionary
 *        that meet the criteria provided in the `in` and `floating`
 *        inputs.
 * 
 * @param [in] in - string of fixed, correct characters and `-`s to indicate
 *                  the length of string and locations that must be filled in
 * @param [in] floating  - Characters that must be used somewhere in the word
 * @param [in] dict - Dictionary of strings of legal words
 * @return std::set<std::string> - Set of all words that meet the criteria
 */

// Definition of primary wordle function
// NOT PROVIDED: a list of gray letters (those not in the word)

// approach: 
// generate all possible strings of lower-case, alpha chracters 
// contains the fixed characters (in their locations) & floating (any loc) & rest of word filled in 
// then check if any of these are english language words --> this can be helper function 

// requirements: 
// use recursive approach to find all combinations of letters to form length -n word 
// basically: have 1-2 loops to help set characters in any given location 
// maybe 1-2 other loops to help with constraint checks 
// DO NOT BRUTE FORCE THE SOLUTIONS 
// use AT MOST 5 loops 
// dont need to implement backtracking approach 
// instead, just generate all possible strings then check if each word is in dict after it has all the letters 

// hints: 
// generating all combinations 
// use recursion to build up a combinaion 1 "place" at a time 
// each recursion is responsible for 1 "place/location" of the combination 
// for that place, each recursion should try all the "options", recurse after each one 
// upon return, undo and try the next option to get multiple solutions 
// think abt "options" to try at each loc - what are limitations of letter usage 
// then lastly just check if the combinations are valid english words 


// idea: 
// recursion w one of the checks being if there is already a char in the loc 
// limitations to consider: 
// floating letter doesnt mean it is the only case of that letter 
// could create another func to handle the recursion? 
// case to stop recursion = temp word is full (there are no '-')
// get length variable 
// temp variable 
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
	// size_t len = in.length(); 
	// string temp = nullptr; 

	// declare variables 
	set<string> allcombos; 
	// set to hold all the combos (used to temp hold the answer up until check)
	string temp = in; 
	// temp variable (imp for recursion) 
	string updatedFloat = floating; 
	// need this var to keep track 

	recursecombos(allcombos, temp, in, updatedFloat, 0, dict); 
	// first call --> will produce final once returned. indexing and temp added to assist in recursion here 

	return check(allcombos, dict);
	// return the result from check 
	// check ensures that all the words that are returned are in the dictionary 
}

// Define any helper functions here
// helper functions: one to recurse and one to check in the end 

void recursecombos(set<string>& allcombos, string& temp, const string& in, string& floating, size_t index, const set<string>& dict){
	// general recursion & combinations approach: 

	// string alphabet = "abcdefghijklmnopqrstuvwxyz";
	// data to iterate through all possible characters 

	// string temp = nullptr; 
	// need some array/vector/string to store partial answer as it is being built 

	// need to track the locations that are empty 

	// base case can stop when all n locations are set: 
	if (index == in.size()){
		// need to find out how many spots need to be filled: 
		size_t emptyCount = count(temp.begin(), temp.end(), '-');
		// to determine if it is full (index number will be the goal size at this point)
		if (floating.empty() && dict.find(temp) != dict.end() && emptyCount == 0){
			allcombos.insert(temp);
		}
		return; 
		
		// before adding to the allcombos, make sure to ensure that all the characters in floating are used 
		// code to handle that: 
		// variable to hold the word to iterate through 
		// now loop through all characters in the floating  
		// for (char c : cur){
		// 	// get position of where the floasting is 
		// 	size_t pos = copy.find(c);
		// 	size_t ind = cur.find(c); 
		// 	if (pos == string::npos){
		// 		return; 
		// 		// if it is not a position, that means this word is not valid since the floating letter is not in the word 
		// 	}
		// 	cur.erase(ind,1);
		// 	copy.erase(pos,1);
			// erase that floating letter from the word to update 

		// // this part can just be replaced with an if statement if it is hanfled below: 
		// if (dict.find(temp) == dict.end()){
		// 	return; 
		// }
	}

	// 	if (cur.empty()){
	// 		allcombos.insert(temp);
	// 		return; 
	// 		// extra check for the duplicates since tests not passing 
	// 	}

	// 	// add to final variable and return so recursion can continue 
	// 	return; 
	// 	// string curr = temp; 
	// 	// for (char c : floating){
	// 	// 	size_t pos = curr.find(c);
	// 	// 	if (pos == string::npos){
	// 	// 		return; 
	// 	// 	}
	// 	// 	curr.erase(pos,1);
	// 	// }
	// 	// allcombos.insert(temp);
	// 	// return; 
	// }

	// then recurse to handle all remaining locations (i+1 to n)
	// upon return, try another option value & recurse again 
	// recursive case returns after trying all options 

	// else{
		// if not base case 
		// first check to make sure that the spot is open 
		// if spot is not open, recurse so you can move on to the next pos 
		if (temp[index] != '-'){
			recursecombos(allcombos, temp, in, floating, index + 1, dict);
		}
		else{
			// recount empty spots 
			size_t emptyCount = count(temp.begin() + index, temp.end(), '-');
		// make sure solution is even possible by checking to make sure there are not more floating chars
		if (floating.size() > emptyCount){
			return; 
		}

		// PROBLEM IN MY CODE: DOES NOT ACCOUNT FOR REPEATING IN FLOATING 
		// solution: keep a set to see if it is used 
		
		// loop through floating first is solution 
		for (size_t i = 0; i < floating.size(); i++){
			string next = temp; 
			next[index] = floating[i]; 

			string updated = floating; 
			updated.erase(i,1);
			recursecombos(allcombos, next, in, updated, index+1, dict);
		}
		
			// this means that the spot is empty 
			// to keep track of what is empty: 
			// int empty = count(temp.begin() + index, temp.end(), '-');
			// if (empty < static_cast<int>(floating.size())){
			// 	return; 
			// }
			// function iteratively (loop) try each optiion in set of values by setting loc i to current option 
			// iterate through alphabet - for loop of all chars a-z 
		if (floating.length() < emptyCount){
			for (char letter = 'a'; letter <= 'z'; letter++){
				// each recursive call is responsible for one of the n "places" (ex: location i)
				// if you go through this loop, it will handle all the floating characters 
				// only issue is to update the floating characters 
				// same approach as base case 

				// first set the letter 
				string next = temp; 
				next[index] = letter; 
				recursecombos(allcombos, next, in, floating, index+1, dict);

				// int empty = count(temp.begin() + index + 1, temp.end(), '-');
				// if (empty < static_cast<int>(floating.size())){
				// 	if (check){
				// 		floating.insert(floating.begin() + ind, letter);
				// 	}
				// 	continue; 
				// }
				
				// call recursion on the next i pos at this point! 
				// but all options of the current i have not executed yet ...
				//recursecombos(allcombos, temp, in, floating, index+1, dict);
				// recursive call with new floating set (inserted)

				// if (check){
				// 	floating.insert(floating.begin() + ind, letter); 
				// }
			}
		}
	}
}

set<string> check(const set<string>& allcombos, const set<string>& dict){
	set<string> result; 
	// variable to hold what will be returned 
	for (const string& word : allcombos){
		// loop through all words in the allcombos (this type of iteration is easier to handle)
		if (dict.find(word) != dict.end()){
			// if word is in the dictionary, add it into the result 
			result.insert(word);
		}
	}
	return result; 
	// return the result (this is the final answer)
}