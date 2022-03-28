#include <iostream>
#include <string>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;
using std::string;

struct songAndArtist{
    string songTitle {"Unset"};
    string artist {"Unset"};
};


class MP3{
private:
    songAndArtist savedSongs[100];
    int numberOfSongs {0};
    
public:
    MP3(int &numSongs) {
        //On creation, the MP3 object will have a savedSongs array of songAndArtist structs
        this->numberOfSongs = numSongs;
    }
    void displaySongs();

    
};


int posIntegerConvert(string);


int main(int argc, char* argv[]) {
    string userInput {"Unset"};
    int numberOfSongs {0};

    do{
        cout << "\nHow many songs would you like to put on your MP3 player? (maximum of 100)" << endl
            << "Selection:";
        getline(cin, userInput);
        cin.clear();
        numberOfSongs = posIntegerConvert(userInput);
    }while (numberOfSongs <= 0 || numberOfSongs > 100);
    userInput.clear();

    // Saving the new MP3 object as myMP3
    MP3 *myMP3 = new MP3(numberOfSongs);

    myMP3->displaySongs();
    
    
    return 0;
}

int posIntegerConvert(string userInput){
    if (userInput.empty()){
        cout << "\nInput failed! Please enter something!" << endl;
        return -1;
    }
    
    // Since this function only makes sure an integer is returned, only whole numbers are allowed.
    for (int i {0}; i < userInput.length(); i++){
        if (userInput[0] == '-'){
            cout << "\nInput failed! Please enter a positive number (exclude the '+')." << endl;
            return -1;
        }
        if ( !isdigit(userInput[i]) ){
            cout << "\nInput failed! Please only use numbers." << endl;
            return -1;
        }
    }
    // userInput should be able to convert to int now without error, if it skips the previous two "if" statements
    return std::stoi(userInput);
}

void MP3::displaySongs() {
    int longestArtistName {0};
    
    //Finding the longest artist name to know what width to set for output
    for(int i = 0; i < numberOfSongs; i++){
        if(savedSongs[i].artist.length() > longestArtistName){
            longestArtistName = savedSongs[i].artist.length();
        }
    }
    
    for(int i = 0; i < numberOfSongs; i++){
        cout << std::left << std::setw(longestArtistName + 2)
             << savedSongs[i].artist << "-  " << savedSongs[i].songTitle << endl;
        
    }
}