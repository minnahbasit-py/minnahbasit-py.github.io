
// Complete me
#include "customparser.h"
#include <iostream>
#include <sstream>

using namespace std;

const char* error_msg_1 = "Cannot read integer n";
const char* error_msg_2 = "Error in content parsing";
const char* error_msg_3 = "Error in user parsing";

// To Do - Complete this function
void CustomFormatParser::parse(std::istream& is, std::vector<Content*>& content, std::vector<User*>& users)
{
    // Erase any old contents
    content.clear();
    users.clear();

    // TO DO - Add your code below.
    int num_media = 0;
    int watching_limit = 0;
    is >> num_media;
    if (is.fail()) {
      // number of shows/movies
      throw ParserError(error_msg_1);
    }
    for (size_t i = 0; i < num_media; i++) {
      int content_id, content_type, num_episodes = 0;
      string name;
      if (is.fail()) {
        throw ParserError(error_msg_1);
        // do we need this check later
      }
      int num_reviews, total_stars, rating = 0;
      if (!(is >> content_id >> content_type)) {
        // 0 content id, content type 0 (data1 file)
        // content id and type read error
        throw ParserError(error_msg_2);
      }
      getline(is,name);
      if (is.fail()) {
        throw ParserError(error_msg_2);
      }
      is.get();
      getline(is,name);
      /// clear newline after reading content id and type
      // get black panther line
      
      // get name
      is >> num_reviews;
      if (is.fail()) {
        throw ParserError(error_msg_2);
      }
      is >> total_stars;
      // 4 : num reviews , 18 : stars, 3: rating
      if (is.fail()) {
        throw ParserError(error_msg_2);
      }
      is >> rating;
      if (is.fail()) {
        throw ParserError(error_msg_2);
      }
      // if (content_type == 1) {
      //   is >> numEpisodes;
      // }
      
      Content* content_;
      if (content_type == 0) {
        content_ = new Movie(content_id, name, num_reviews, total_stars, rating);
      }
      else {
        is >> num_episodes;
        if (is.fail()) {
          throw ParserError(error_msg_2);
        }
        content_ = new Series(content_id, name, num_reviews, total_stars, rating, num_episodes);
        // stranger things has 8 episodes
      }
      string viewers;
      getline(is, viewers);
      // user 1
      getline(is,viewers);
      // user 2
      stringstream s(viewers);
      // put viewers in string stream
      string user;
      while (s >> user) {
        // user 1 and user 2 are added to viewers
        content_->addViewer(user);
      }
      // pushback viewers 
      content.push_back(content_);
    }
    string uname;
    string temp;
    // user name 
    while (is >> uname >> watching_limit){
      //is >> watching_limit;
      // get username and watching limit : user1, 3
      if (is.fail()) {
        throw ParserError(error_msg_3);
      }
      User* user = new User(uname, watching_limit);
      getline(is,temp);
      if (is.fail()) {
        throw ParserError(error_msg_3);
      }
      getline(is,uname);
      if (is.fail()) {
        throw ParserError(error_msg_3);
      }
      stringstream ss2(uname);
      string content_watched;
      while (ss2 >> content_watched) {
        cout << "content watched" <<  content_watched << endl;
        int content_history = stoi(content_watched);
        user->addToHistory(content_history);
      }
      users.push_back(user);
    }
    for (size_t i = 0; i < users.size(); i++) {
      cout << users[i] << endl;
    }

}

