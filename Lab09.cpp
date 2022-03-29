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
        string constructorInput {"Unset"};
        for(int i = 0; i < numSongs; i++){
            // Get initial song titles
            cout << "Enter song title for Song #" << i + 1 << ": ";
            getline(cin, constructorInput);
            cin.clear();
            this->savedSongs[i].songTitle = constructorInput;

            // Get the artist for the song that was just entered
            cout << "Enter artist that sings " << savedSongs[i].songTitle << ": ";
            getline(cin, constructorInput);
            cin.clear();
            this->savedSongs[i].artist = constructorInput;
        }
    }
    void displaySongs();
    int mp3Menu();

    //Menu methods
    void addSong();
    
};


int posIntegerConvert(string);


int main(int argc, char* argv[]) {
    string userInput {"Unset"};
    int numberOfSongs {0};

    do{
        cout << "\nHow many songs would you like to initially put on your MP3 player? (maximum of 100)" << endl
            << "Selection:";
        getline(cin, userInput);
        cin.clear();
        numberOfSongs = posIntegerConvert(userInput);
    }while (numberOfSongs <= 0 || numberOfSongs > 100);
    userInput.clear();

    // Saving the new MP3 object as myMP3
    MP3 *myMP3 = new MP3(numberOfSongs);

    myMP3->displaySongs();
    myMP3->mp3Menu();
    myMP3->addSong();
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

int MP3::mp3Menu() {
    string menuInputRaw {"Unset"};
    int menuInput{0};

    do{
        cout << "==================================================================================" << endl 
             << "Make one of the following selections with the number on the right of each option." << endl
             << "Options:" << endl
             << "1.) Add a Song (You can add " << 100 - numberOfSongs << " more songs)" << endl
             << "2.) Delete a Song" << endl
             << "3.) Display my Songs by Artist name" << endl
             << "4.) Display my Songs by Song title" << endl
             << "5.) I'm done with this MP3 Player (exit)" << endl
             << "My Selection: ";
        getline(cin, menuInputRaw);
        cin.clear();
        menuInput = posIntegerConvert(menuInputRaw);
        // no input < 1  or  no input > 5 or no input == 1 if at than 100 songs
    }while(menuInput < 1 || menuInput > 5 || (menuInput == 1 && numberOfSongs >= 100));
    
    return menuInput;
}

void MP3::addSong() {
    string response {"Unset"};
    do{
        string newSongTitle {"Unset"};
        string newSongArtist {"Unset"};
        cout << "======================================" << endl
             << "            Adding a Song             " << endl
             << "======================================" << endl
             << "Song title: ";
        getline(cin,newSongTitle);
        cin.clear();
        cout << "Artist: ";
        getline(cin,newSongArtist);
        cin.clear();
        // I'm surprised I didn't have to offset numberOFSongs by 1 here, but this is what works
        savedSongs[numberOfSongs].songTitle = newSongTitle;
        savedSongs[numberOfSongs].artist = newSongArtist;
        numberOfSongs++; //Tracking that a new song was added
        
        do{ //Making sure they actually respond y or n
            cout << "Add another song (y/n)? ";
            getline(cin, response);
            cin.clear();
        }while(response != "Y" && response != "y" && response != "N" && response != "n");
        
    }while(response == "Y" || response == "y"); //repeat if y
}