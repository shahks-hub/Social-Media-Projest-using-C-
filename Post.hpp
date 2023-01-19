/****************************************************************************************************************************
Title         :   Post.hpp
Author        :   Modified by Kasaf Shah
Description   :   header/interface for Post class
Date Modified :   12/09/2022
****************************************************************************************************************************/

#ifndef POST_
#define POST_

#include <iostream>
#include <string>
#include <time.h>

class Post {
   
public:

enum priority{
    LOW,
    MEDIUM,
    HIGH
   }; 
  /**
     Parameterized constructor.
     @param      : The title of the post (a string)
     @param      : The body content of the post (a string)
     @param      : The username of the Account that added this post (a string)

     @post         : Sets the title, body and username to the value of the parameters
                     It will also generate the current time and store it
  */
    Post(std::string title, std::string body, std::string username);


    /**
       @return : the title of the Post
    */
    std::string getTitle() const;


    /**
      @param  : a reference to title of the Post
      @post   : sets the private data member to the value of the parameter
    */
    void setTitle(const std::string& title);


    /**
       @return : the body of the Post
    */
    std::string getBody() const;

    /**
       @param  : a reference to body of the Post
       @post   : sets the private data member to the value of the parameter
    */

    void setBody(const std::string& body);

    /*
       Accessor Function
       @return       : username associated with this Post
    */
    std::string getUsername() const;



    /*
       Mutator Function
       @param        : a reference to the username associated with this Post
       @post   : sets the private data member to the value of the parameter
    */
    void setUsername(const std::string& username);

    /**
       @post   : prints the time the Post was created to the standard output as asctime(localtime(&time_stamp_))
    */
    void getTimeStamp() const;

    /*
       Mutator Function
       @post   : sets the private data member to the current time
    */
    void updateTimeStamp();


    void virtual displayPost() = 0;
    /*
    @param            :   The Post object to compare

    @return           :   true if this Post's username is less than the parameter
                          Post username, false otherwise
*/
    bool operator<(const Post& object)const; 
    /*
    @param            :   The Post object to compare

    @return           :   true if this Post's username is greater than the
                          parameter Post username, false otherwise
*/
    bool operator>(const Post& object)const; 

    //@post             :  increments the likes_ private member

    void like(); 

     //@return             : the value of the likes_ private member
    int getLikes(); 


    /*@priority           :  a priority value
    @post             :  sets the priority_id_ to the value of the parameter*/
    void setPriority(const priority); 

   // @return             :  the value of the priority_id_ data member
    priority getPriority(); 


private:
    std::string post_title_;
    std::string post_body_;
    time_t time_stamp_;
    std::string username_;
    int likes_;  //an integer that keeps track of the number of likes the post received
    
    /*a variable of enum type 'priority': {LOW, MEDIUM, HIGH}, by default
     MEDIUM. This enum is defined within the public section of the Post class.*/
    priority priority_id_=MEDIUM;  



};//end Post

#endif
