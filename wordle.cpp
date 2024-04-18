#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <unordered_map>
#include <vector>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordleHelp(const std::string& in, std::string& floating, const set<string>& dict, unsigned int n, string curr, std::set<std::string>& ans, int filled);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string>ans;
    string floatingReference = floating;
    int filled = in.size() - std::count(in.begin(), in.end(), '-');
    wordleHelp(in, floatingReference, dict, 0, in, ans, filled);
    return ans;

}
//helper function to find words
void wordleHelp(const std::string& in, std::string& floating, const set<string>& dict, unsigned int n, string curr, std::set<std::string>& ans, int filled)
{
    //base case if word is complete
    if(n == curr.size())
    {
        //check if word is in dictionary
        if(!(dict.find(curr) != dict.end()))
        {
            return;
        }
        else if(floating.empty())
        {
            ans.insert(curr);
            return;
        }
        return;
    }
    //base case if it exceeds space return
    if(floating.size() + filled > (in.size()-n))
    {
        return;
    }
    
    if(curr[n] != '-')
    {
        wordleHelp(in, floating, dict, n+1, curr, ans, filled-1);
    }
    else
    {
        //iterate over letters
        for(char letter = 'a'; letter <= 'z'; ++letter)
        {
            size_t position = floating.find(letter);
            if(position != std::string::npos)
            {
                string newFloatingLetter = floating;
                newFloatingLetter.erase(position, 1);
                curr[n] = letter;
                wordleHelp(in, newFloatingLetter, dict, n+1, curr, ans, filled);
            }
            curr[n] = letter;
            //recur with unchanged floating laters
            wordleHelp(in, floating, dict, n+1, curr, ans, filled);
        }
    }
}


