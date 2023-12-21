#include "strmsrv.h"
#include <iostream>
#include <fstream>
using namespace std;

// To do - Complete this function
StreamService::StreamService()

{
    // Update as needed
    cUser_ = NULL;

}

// To do - Complete this function
StreamService::~StreamService()
{
  for (unsigned int i = 0; i < users_.size(); i++) {  
    delete users_[i];
  } 
  for (unsigned int i = 0; i < content_.size(); i++) {
    delete content_[i];
  }

}

// Complete - Do not alter
void StreamService::readAndParseData(std::istream& is, Parser& p)
{
    p.parse(is, content_, users_);
    cout << "Read " << content_.size() << " content items." << endl;
    cout << "Read " << users_.size() << " users." << endl;
}

// To do - Complete this function
void StreamService::userLogin(const std::string& uname)
{
  if (cUser_ != NULL) {
    throw runtime_error("Runtime error");
  }
  bool is_user = false;
  for (unsigned int i = 0; i < users_.size(); i++) {
    if (uname == users_[i] ->uname) {
      cUser_ = users_[i];
      is_user = true;
    }
  }
  if (!is_user) {
    throw std::invalid_argument("");
  }
}

// To do - Complete this function
void StreamService::userLogout()
{
  if (cUser_ == NULL) {
    return;
  }
  else {
    cUser_ = NULL;
  }
}

// To do - Complete this function
std::vector<CID_T> StreamService::searchContent(const std::string& partial) const
{
    std::vector<CID_T> results;
    for(size_t i = 0; i < content_.size(); i++){
        // TO DO - modify this to also push back when the string 'partial'
        //  is contained in the name of the current content. Lookup the string
        //  class documentation to find an appropriate function that can be used
        //  to do this simply.
        if(partial == "*" || content_[i] -> name().find(partial) != string::npos){
            results.push_back(i);
        }        
    }
    return results;
}

// Complete - Do not alter
std::vector<CID_T> StreamService::getUserHistory() const
{
    throwIfNoCurrentUser();
    return cUser_->history;
}

// To do - Complete this function
void StreamService::watch(CID_T contentID)
{
  throwIfNoCurrentUser();
  if (isValidContentID(contentID) == false) {
    cout << "throwing Range error" << endl;
    throw range_error("Range error");
  }
  if (content_[contentID] -> rating() > cUser_->ratingLimit) {
    throw RatingLimitError("Rating limit error");
  }
  content_[contentID]->addViewer(cUser_->uname);
  cUser_->addToHistory(contentID);
}

// To do - Complete this function
void StreamService::reviewShow(CID_T contentID, int numStars)
{
  throwIfNoCurrentUser();
  if(numStars > 5 || numStars < 0 || (isValidContentID(contentID) == false)) {
    throw ReviewRangeError("Review range error");
  }
  content_[contentID]->review(numStars);

}

// To do - Complete this function
CID_T StreamService::suggestBestSimilarContent(CID_T contentID) const
{
    // Change this when you are ready, but for now it is a 
    // dummy implementation
    throwIfNoCurrentUser();
    if (!(isValidContentID(contentID))) {
      throw std::invalid_argument("Watch: invalid contentID");
    }
    vector<CID_T>recommended;
    vector<int>users_viewed;
    vector<string>viewers = content_[contentID]->getViewers();
    //int user_index;
    for (int i = 0; i < viewers.size(); i++) {
      unsigned int loc;
      if (viewers[i] == cUser_->uname) {
        continue;
      }
      else if (viewers[i] !=cUser_->uname) {
        loc = getUserIndexByName(viewers[i]);
        if (loc == -1) {
          throw std::logic_error("not a user");
        }
        unsigned int size = users_[loc]->history.size();
        for (unsigned int j = 0; j < size; j++) {
          int curr = users_[loc]->history[j];
          if (content_[curr] ->hasViewed(cUser_->uname) == false) {
            bool already_rec = false;
            unsigned int updatedsize = recommended.size();
            for (unsigned int k = 0; k < updatedsize; k++) {
              if (recommended[k] == curr) {
                users_viewed[k] = users_viewed[k] + 1;
                already_rec = true;
              }
            }
            if (already_rec == false) {
              users_viewed.push_back(1);
              recommended.push_back(curr);
            }
          }
        }
      }
    }
    int max = 0; 
    if (users_viewed.empty()) {
      return -1;
    }
    for (size_t i = 0; i < users_viewed.size(); i++) {
      if (users_viewed[i] > users_viewed[max]) {
        if (recommended[i] != contentID) {
          max = i;
        }
      }
    }
    //max -= 1;
    return (users_viewed[max])+1;
}

// To do - Complete this function
void StreamService::displayContentInfo(CID_T contentID) const
{
    // Do not alter this
    if(! isValidContentID(contentID)){
        throw std::invalid_argument("Watch: invalid contentID");
    }

    // Call the display abitlity of the appropriate content object



}

// Complete - Do not alter
bool StreamService::isValidContentID(CID_T contentID) const
{
    return (contentID >= 0) && (contentID < (int) content_.size());
}

// Complete - Do not alter
void StreamService::throwIfNoCurrentUser() const
{
    if(cUser_ == NULL){
        throw UserNotLoggedInError("No user is logged in");
    }
}

// Complete - Do not alter
int StreamService::getUserIndexByName(const std::string& uname) const
{
    for(size_t i = 0; i < users_.size(); i++){
        if(uname == users_[i]->uname) {
            return (int)i;
        }
    }
    return -1;
}
