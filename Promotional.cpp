//Created by Kasaf Shah on September 23 2022
//Promotional.cpp class 


#include "Promotional.hpp"
    



    /*Parameterized constructor.
         title       : The name of the Promotional post (a string)
         body      : The body of the Promotional post (a string)
         username   : : The username of the Account that added this post (a string)
         link       : The link of the Promotional post (a string)

        @post         : Sets the title, body, username and link (if it's a proper link otherwise "Broken Link")
                       of the Promotional to the value
                       of the parameters.
                       It will also generate the current time and store it.*/

Promotional::Promotional(std::string name,std::string description,std::string username,std::string link):Post(name,description,username){
                setLink(link);  
      
            }
    
     /*Accessor function
      @return         : Returns the post link*/
    
std::string Promotional::getLink()const{
        return url_post;
       
    }
   
      //not sure what to do here
 
bool Promotional::setLink(const std::string& link){
    const std::regex pattern("((http|https)://)(www.)[a-zA-Z0-9@:%._\\+~#?&//=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%._\\+~#?&//=]*)");
    if (regex_match(link,pattern)) {
        url_post = link;
        return true;
    }

   url_post = "Broken link";
    return false;
}
                  

  

                   //calling the Post functiona nd  displaying the post  
void Promotional::displayPost()const{
                        
    std::cout << '\n' << getTitle() << " at ";
    getTimeStamp();
    std::cout << getBody() << std::endl;
    std::cout << getLink() << std::endl;

                       
                    }






