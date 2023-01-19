//Created by Kasaf Shah on September 23 2022
//Promotional.hpp class 
#ifndef Promotional_hpp 
#define Promotional_hpp

#include "Post.hpp"



#include<iostream>
#include <string>
#include <regex>



class Promotional:public Post{ //promotional class inherits from base class Post
    
private:
    std::string url_post; //variable to store the link
    
public:
    Promotional(std::string name,std::string description,std::string username,std::string link); 

    std::string getLink()const; 
    bool setLink(const std::string& link); 
    
    virtual void displayPost()const override; }; 

    #endif