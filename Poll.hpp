//Created by Kasaf Shah on September 23 2022
//Poll.hpp class 

#ifndef Poll_hpp
#define Poll_hpp

#include "Post.hpp"
#include <string>
#include <vector>
#include <iostream>



class Poll:public Post{ //class Poll inherits from base class Post
        
private:
        
        
        std::vector<std::string> poll_options_;  //vector to store the options for the poll
        std::vector<int> number_of_votes; //vector to store the number of votes each option receives
          
    
    public:
    Poll(std::string name,std::string body,std::string username,
     std::vector<std::string>poll_options); //parametrized constructor
     bool votePoll(const int& options);  //votes per poll
     void changePollOption(const std::string& npoll, const int& options);  //changing the option in the poll
      void getPollOptions()const;  //getting the poll options
       int getPollVotes(int options)const; //getting the votes
       virtual void displayPost()const override; //displaying the whole result of the poll
}; 
#endif