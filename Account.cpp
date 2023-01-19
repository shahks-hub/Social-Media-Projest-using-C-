/****************************************************************************************************************************
Title         :   Account.hpp
Author        :   modified by Kasaf Shah
Description   :   header/interface files for Account class
Date          :   12/09/2022
****************************************************************************************************************************/

#include "Account.hpp"

//default constructor
//@post:  set username and password to ""
//        creates an empty vector of post objects to store into feed_
Account::Account()
{
    username_ = "";
    password_ = "";
    posts_ = LinkedList<Post*>();
    following_ = {};
}


/**
    Parameterized Constructor
    @param username  : username of the account, stored into username_
    @param password  : password of the account, stored into password_
    @post:             sets the private members to the value of the parameters
*/
Account::Account(std::string username, std::string password) : username_(username), password_(password), posts_(LinkedList<Post*>()), following_({}), net_(nullptr) { }

/**
  @return:     the username of the Account
*/
std::string Account::getUsername() const { return username_; }


/**
  @param:     a reference to the username of the Account
  @psot:      sets the parameter to the value of the private member
*/
void Account::setUsername(const std::string& username) { username_ = username; }


/**
  @return:     the password of the Account
*/
std::string Account::getPassword() const { return password_; }


/**
  @param a reference to the password of the Account
  @post:      sets the private member to the value of the parameter
*/
void Account::setPassword(const std::string& password) { password_ = password; }


/**
      Accessor function
      @return           :   the pointer to the Network the account is in
   */
Network<Account>* Account::getNetwork() const { return net_; }


/**
      Mutator function
      @param            :   a pointer to a Network
      @post             :   the Network pointer private member points to the input Network
   */
void Account::setNetwork(Network<Account>* network) { net_ = network; }


/**
    @param newPost   : The pointer to the Post object that will be added to its list
    @return          : Will return true if a post gets added sucesfully to the vector

    @post:           " Adds post to posts_ and its Networks feed_. Additionally adds posts
                       to a stack and sorts them according to likes. 
*/
bool Account::addPost(Post* newPost){
posts_.insert(newPost, 0);
    
    net_->addToFeed(newPost);

if(max_stack.empty() && min_stack.empty()){
        max_stack.push(newPost);                                           
        min_stack.push(newPost);                                            
    }

    else{
        std::stack<Post*> temp_max;                                       
        std::stack<Post*> temp_min;
        
                                                     
        // deal with the max_stack
        while(!max_stack.empty() && max_stack.top()->getLikes() >= newPost->getLikes() ){                               
                temp_max.push(max_stack.top());
                max_stack.pop();
            }
        max_stack.push(newPost);  

        while(!temp_max.empty())
        {
         max_stack.push(temp_max.top());
         temp_max.pop();
        }
                 //deal with min stack
          
          while(!min_stack.empty()&& min_stack.top()->getLikes() < newPost->getLikes()){                      
                temp_min.push(min_stack.top());
                min_stack.pop();                     
        }
       min_stack.push(newPost); 
        
        while(!temp_min.empty())                   
        {
        min_stack.push(temp_min.top());
        temp_min.pop();
        }
    } 

    return true; 


}



/*
    @post:      Prints the feed_ that contains the post objects by calling their display function
*/
void Account::viewPosts() const {

    Node<Post*>* itt = posts_.getHeadPtr();

    while (itt != nullptr) {
        itt->getItem()->displayPost();
        itt = itt->getNext();
    }

}



/**
      @param            :   the username of the Account to follow
      @return           :   true if the account was successfully able to follow, false otherwise
      @post             :   adds the username to the vector of following accounts only if
                            it is affiliated to a Network AND it is not already following an account
                            with the same username.
   */
bool Account::followAccount(const std::string username){

    bool exists = false;

    for(std::string un : following_) {
        if(un == username) {
            exists = true;
        }
    }

    if(!exists && net_ != nullptr) {
        following_.push_back(username);
        return true;
    }

    return false;
}


/**
      @return           :   the vector of usernames the Account is following
   */
std::vector<std::string> Account::viewFollowing() const {
    return following_;
}


/**
  @return           :  true if account has same private members as parameter,
                       false otherwise
*/
bool Account::operator==(const Account &acc) const {
    if(acc.getUsername() == this->username_ && acc.getPassword() == this->password_) {
        return true;
    }

    return false;
}



/*
@param            :   A pointer to a Post
@return           :   True iff the Post was successfully found and removed,
                      false othewise.
@post             :   Removes the given Post from its list
                      as well as from the Network's feed. Additionaly the post is removed from the stack 
                      as well based on the way it is sorted
*/
bool Account::removePost(Post* post){
   int postPosition = posts_.getIndexOf(post);

    if (postPosition > -1) {
        posts_.remove(postPosition);
        net_->removePostFromFeed(post);
    
    if(max_stack.empty() && min_stack.empty()){

        return false; 
    }
    else{
    std::stack<Post*> temp; 
    std::stack<Post*> temp2;
    bool removed= true; 
    

    while(!min_stack.empty() && removed){ 
    if(min_stack.top() != post){
        temp.push(min_stack.top()); 
        min_stack.pop();
    
    }
    else {
        min_stack.pop(); 
        removed=false;
        
    }

    }
    removed=true; 
    while(!max_stack.empty() && removed){ 
    if(max_stack.top() != post){
        temp2.push(max_stack.top()); 
        max_stack.pop();

    }
    else {
        max_stack.pop(); 
        removed=false;  
    }

    }

    while(!temp2.empty() && !temp.empty()){
        max_stack.push(temp2.top());
        temp2.pop(); 

    }

    while(!temp.empty())
    {
        min_stack.push(temp.top()); 
        temp.pop();
    }

    }
    return true; 
    }
}

/*
@param            :   Pointer to a Post object
@param            :   The new title of the Post (or an empty string if you do not
                      want to change it)
@param            :   The new body of the Post (or an empty string if you do not
                      want to change it)

@post            :   This function will take the Post and given the new title and body,
                     update the Posts title and body as appropriate. It will also update
                     the `timestamp_` to the current time of the update. This function should then
                     update the location of the Post in its list of `posts_` to the front of the list
                     as well as utilizing its Network pointer to do the same in the `feed_`.
*/
void Account::updatePost(Post* post, std::string new_title, std::string new_body) {
    if(new_title != "") { post->setTitle(new_title); }

    if(new_body != "") { post->setBody(new_body); }

    post->updateTimeStamp();
    removePost(post);
    addPost(post);

}

/*
    @return           :  a pointer to the Post with least likes
    
*/
Post* Account::getMinLikes(){
if(min_stack.empty())                       
        return nullptr;

    return min_stack.top(); 
    
                  
}


/*
    @return           :  a pointer to the Post with most likes

  
*/
Post* Account::getMaxLikes(){
if(max_stack.empty())
        return nullptr;

    return max_stack.top();

}


/*
    @return           :  a vector of pointers to Post
    @post             :  the order of the Posts in the vector is by increasing
                         priority, and within each priority class, from oldest
                         to newest

*/
std::vector<Post*> Account::increasingPriorityOldestToNewest(){
 std::stack<Post*> high, medium, low;                                

    Node<Post*>* itt = posts_.getHeadPtr();                             
                                                                        
    while (itt != nullptr) {
        if(itt->getItem()->getPriority() == Post::HIGH)                 
            high.push(itt->getItem());
        else if(itt->getItem()->getPriority() == Post::MEDIUM)
            medium.push(itt->getItem());
        else
            low.push(itt->getItem());
        itt = itt->getNext();                                           
    }

    std::vector<Post*> result;
    while(!low.empty()) {                                               
        result.push_back(low.top());
        low.pop();
    }

    while(!medium.empty()) {                                           
        result.push_back(medium.top());
        medium.pop();
    }

    while(!high.empty()) {                                             
        result.push_back(high.top());
        high.pop();
    }
    return result;                                                      
}
                                     


/*
@return           :  a vector of pointers to Post
@post             :  the order of the Posts in the vector is by increasing
                     priority, and within each priority class, from newest
                     to oldest

*/
std::vector<Post*> Account::increasingPriorityNewestToOldest(){
std::queue<Post*> high, medium, low;                                

    Node<Post*>* itt = posts_.getHeadPtr();                             
                                                                        
    while (itt != nullptr) {
        if(itt->getItem()->getPriority() == Post::HIGH)                 
            high.push(itt->getItem());
        else if(itt->getItem()->getPriority() == Post::MEDIUM)
            medium.push(itt->getItem());
        else
            low.push(itt->getItem());
        itt = itt->getNext();                                           
    }

    std::vector<Post*> result;
    while(!low.empty()) {                                               
        result.push_back(low.front());
        low.pop();
    }
    
    while(!medium.empty()) {
        result.push_back(medium.front());
        medium.pop();
    }

    while(!high.empty()) {
        result.push_back(high.front());
        high.pop();
    }
    return result;
}
   


/*
    @return           :  a vector of pointers to Post
    @post             :  the order of the Posts in the vector is by decreasing
                         priority, and within each priority class, from oldest
                         to newest

*/
std::vector<Post*> Account::decreasingPriorityOldestToNewest(){
std::stack<Post*> high, medium, low;

    Node<Post*>* itt = posts_.getHeadPtr();                                 
                                                                           
    while (itt != nullptr) {
        if(itt->getItem()->getPriority() == Post::HIGH)                     
            high.push(itt->getItem());
        else if(itt->getItem()->getPriority() == Post::MEDIUM)
            medium.push(itt->getItem());
        else
            low.push(itt->getItem());
        itt = itt->getNext();
    }

    std::vector<Post*> result;
    while(!high.empty()) {                                                  
        result.push_back(high.top());
        high.pop();
    }

    while(!medium.empty()) {
        result.push_back(medium.top());
        medium.pop();
    }

    while(!low.empty()) {
        result.push_back(low.top());
        low.pop();
    }
    return result;
}
   


/*
@return           :  a vector of pointers to Post
@post             :  the order of the Posts in the vector is by decreasing
                     priority, and within each priority class, from newest
                     to oldest

*/
std::vector<Post*> Account::decreasingPriorityNewestToOldest(){
std::queue<Post*> high, medium, low;

    Node<Post*>* itt = posts_.getHeadPtr();                                 

    while (itt != nullptr) {
        if(itt->getItem()->getPriority() == Post::HIGH)
            high.push(itt->getItem());
        else if(itt->getItem()->getPriority() == Post::MEDIUM)
            medium.push(itt->getItem());
        else
            low.push(itt->getItem());
        itt = itt->getNext();
    }

    std::vector<Post*> result;                                              
    while(!high.empty()) {
        result.push_back(high.front());
        high.pop();
    }

    while(!medium.empty()) {
        result.push_back(medium.front());
        medium.pop();
    }

    while(!low.empty()) {
        result.push_back(low.front());
        low.pop();
    }
    return result;
  
}


