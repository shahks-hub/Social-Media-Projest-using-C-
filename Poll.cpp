//Created by Kasaf Shah on September 23 2022
//Poll.cpp class 


#include "Poll.hpp"
        

       /* Parameterized constructor.
        namepoll    : The title (name) of the Poll post (a string)
        bodypoll    : The question (body) of the Poll post (a string)
        username    : : The username of the Account that added this poll (a string)
        poll_options    : A vector of options for the Poll post

        @post     :Sets the title, body and username of the Poll post to the value of the parameters.
                   It will also generate the current time and store it and will initialize
                   the vectors of options and their respective number of votes*/
Poll::Poll(std::string name,std::string body,std::string username, std::vector<std::string>poll_options):Post(name,body,username){
            
            for(int i = 0; i < poll_options.size();  i++){
            poll_options_.push_back(poll_options[i]);
           number_of_votes.push_back(0); 
            
        } }
        
        /*options     : a reference to int between 0 < number of options
         @return    : True if index is within range and we can vote for a poll,
                      false otherwise
         @post      : Increments the poll votes based on the index which
                      will refer to the index in the poll options*/
bool  Poll::votePoll(const int& options){
        
        if(options<poll_options_.size()){

         number_of_votes[options] +=1; 
                return true;

        }
          return false; }

               
                
        
    
  /*Mutator function used to either add a poll or change one of the poll options
         npoll     : A reference to the new poll option
         options     : A reference to int that can either represent the index of the
                      existing option that will be replaced
                      or if choice_number > current number of options,
                      it will add this new option to the poll.

        @post       : Resets the number of votes for this option.*/
void Poll::changePollOption(const std::string& npoll, const int& options){ 
    if(number_of_votes.size()>options){
         poll_options_[options]=npoll; 
         number_of_votes[options]=0;           
          }
          else{
            poll_options_.push_back(npoll); 
            number_of_votes.push_back(0);
          } 
        
                 }
    
   /*prints the reaction of the posts base on the number of votes for each poll/ options*/
void Poll::getPollOptions()const{
        

        for (int i=0; i <= poll_options_.size() -1; i++) {
        std::cout << number_of_votes[i] << " votes for: " << poll_options_[i] << std::endl;
    }
    std::cout << std::endl;
}
    
        
   /*Accessor function
      options      : The index of the option
      @return     : returns the number of votes for a given option
   */
int Poll::getPollVotes(int options)const{
        return number_of_votes[options];
    }
    
    //call the display function for the base class along with the function in this class  to print out
void Poll::displayPost()const {
    std::cout << '\n' << getTitle() << " at ";
    getTimeStamp();
    std::cout << getBody() << std::endl;
    getPollOptions();

                        } 
    

    