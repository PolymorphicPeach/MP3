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
    void deleteSong();
    void sortByArtistName();
    void sortBySongTitle();
    
};

string lowerCaseConvert(string);
int posIntegerConvert(string);


int main(int argc, char* argv[]) {

    bool goAgain {false};
    
    do{
        string userInput {"Unset"};
        int numberOfSongs {0};
        string anotherMP3{"Unset"};
        bool exitMenu {false};
        

        do{
            cout << "\nHow many songs would you like to initially put on your MP3 player?" << endl
                 << "(maximum of 100)" << endl
                 << "Selection: ";
            getline(cin, userInput);
            cin.clear();
            numberOfSongs = posIntegerConvert(userInput);
        }while (numberOfSongs <= 0 || numberOfSongs > 100);
        userInput.clear();

        // Saving the new MP3 object as myMP3
        MP3 *myMP3 = new MP3(numberOfSongs);

        myMP3->displaySongs(); // To show what the user initially input

        //This works well as a switch statement - next time I might try to build this into the class itself instead of
        // the main function to try to make the objects more modular
        do{
            switch(myMP3->mp3Menu()){
            case 1 : myMP3->addSong();
                break;
            case 2 : myMP3->deleteSong();
                break;
            case 3 : myMP3->sortByArtistName();
                break;
            case 4 : myMP3->sortBySongTitle();
                break;
            case 5 :
                exitMenu = true;
                break;
            default : cout << "Critical ERROR" << endl;
            }
        }while(exitMenu == false);

        do{
            cout << endl
                 << "=================================================" << endl
                 << "Would you like to make another MP3 player? (y/n) " << endl
                 << "My selection: ";
            getline(cin,anotherMP3);
            cin.clear();
        }while(anotherMP3 != "Y" && anotherMP3 != "y" && anotherMP3 != "N" && anotherMP3 != "n");
        if(anotherMP3 == "Y" || anotherMP3 == "y"){
            goAgain = true;
        }
    }while(goAgain == true);
    
    
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
    cout << "==================================================================================" << endl;
    //                            + 6 to account for the '.)' and the extra space
    cout << std::left << std::setw(longestArtistName + 6) << "Artist Name" << "-  Song Title" << endl << endl;
    for(int i = 0; i < numberOfSongs; i++){
        cout << i + 1 << ".) " << std::left << std::setw(longestArtistName + 2)
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
        if(menuInput == 1 && numberOfSongs >= 100){
            cout << "\n\nERROR: At maximum number of songs - cannot add more" << endl;
        }
    }while(menuInput < 1 || menuInput > 5 || (menuInput == 1 && numberOfSongs >= 100));
    
    return menuInput;
}

void MP3::addSong() {
    string response {"Unset"};
    do{
        if(numberOfSongs >= 100){ //bugfix
            cout << endl << "ERROR: Cannot add more than 100 songs!!!" << endl << endl;
            break;
        }
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

// This method is mainly modeled after the addSong method
void MP3::deleteSong() {
    string response {"Unset"};
    string deleteThisRaw {"Unset"};
    int deleteThisIndex {-1};

    do{
        if(numberOfSongs <= 0){ //Realized that I needed this to prevent being trapped in this loop forever at 0 songs
            cout << "\nYou don't have any more songs to delete!!" << endl;
            break;
        }
        displaySongs();
        do{
            cout << "Choose the number on the left corresponding to the song you want to delete." << endl
                 << "Delete Song Number: ";
            getline(cin, deleteThisRaw);
            cin.clear();
            deleteThisIndex = (posIntegerConvert(deleteThisRaw) - 1); // It's easier for me to convert this to an index here
        }while(deleteThisIndex < 0 || deleteThisIndex >= numberOfSongs);

        // I don't think I can really delete the index that's allocated to the array, so I just reset the
        // songAndArtist struct back to "Unset" for its values and decrement from numberOfSongs
        savedSongs[deleteThisIndex].songTitle = "Unset";
        savedSongs[deleteThisIndex].artist = "Unset";
        numberOfSongs--;
        
        // This is still going to leave song1, song2, Unset, song3, song4 (for example)
        // So, I'll exchange the "Unset" songAndArtist until it's beyond numberOfSongs
        songAndArtist temporaryHolder;
        // It's going to swap values "down" until the "Unset" songAndArtist gets to the end
        for (int i = deleteThisIndex; i <= numberOfSongs; i++){
            if(i == 99){ // Bugfix to stop program from crashing if at 100 songs trying to put the object at index 100
                savedSongs[99].songTitle = "Unset";
                savedSongs[99].artist = "Unset";
                break;
            }
            temporaryHolder = savedSongs[i];
            savedSongs[i] = savedSongs[i+1];
            savedSongs[i+1] = temporaryHolder;
        }
        do{ //Making sure they actually respond y or n
            cout << "Delete another song (y/n)? ";
            getline(cin, response);
            cin.clear();
        }while(response != "Y" && response != "y" && response != "N" && response != "n");
        
    }while(response == "Y" || response == "y"); //repeat if y
    
}

//==========================================================================
//                        Sorting Methods
//==========================================================================
// Mostly using the inbuilt string1.compare(string2) method:
//  - returns -1 if string1 comes before string2 **alphabetically
//  - returns 1 if string2 comes before string1 **aphabetically 
//  - returns 0 if equal
//  - Numbers come before letters
//  - **ALL capital letters come before ALL lowercase letters (uh oh...), A-Z before a-z
//
// std::tolower( ) can be used on strings, but it only takes one character as a parameter, not the entire string
// std::tolower(string1) INCORRECT
// std::tolower(string1[i]) CORRECT
//
// I'll have to convert the original strings into all-lowercase versions by using std::tolower( ) to
// change each individual character.
// This seems to be worth making a function for alone

string lowerCaseConvert(string originalString) {
    string lowerCaseVersion; // Empty string initalized

    // Loops through the original and concatenates each character to the blank string above
    for (int i = 0; i < originalString.length(); i++){
        lowerCaseVersion += std::tolower(originalString[i]);
    }
    return lowerCaseVersion; 
}


void MP3::sortByArtistName() {
    bool doItAgain {false};
    songAndArtist temporaryHolder;
    
    // numberOfSongs - 1 because the loop will use i and i + 1 - I don't want to reach the very last song == i
    for(int i = 0; i < numberOfSongs - 1; i++){
        string lowerCaseArtist1; // These need to be initialized empty every loop
        string lowerCaseArtist2;
        lowerCaseArtist1 = lowerCaseConvert(savedSongs[i].artist);
        lowerCaseArtist2 = lowerCaseConvert(savedSongs[i+1].artist);

        // if lowerCaseArtist1 comes before lowerCaseArtist2, -1 will be returned
        // this loop iterates if lowerCaseArtist2 comes before lowerCaseArtist1
        //
        // lowerCaseArtist1 = savedSongs[i]  |  lowerCaseArtist2 = savedSongs[i + 1]
        if(lowerCaseArtist1.compare(lowerCaseArtist2) == 1){
            doItAgain = true;
            temporaryHolder = savedSongs[i];
            savedSongs[i] = savedSongs[i+1];
            savedSongs[i+1] = temporaryHolder;
        }
        else if(lowerCaseArtist1.compare(lowerCaseArtist2) == 0){ //Same artist different songs scenario
            string lowerCaseSong1;
            string lowerCaseSong2;
            lowerCaseSong1 = lowerCaseConvert(savedSongs[i].songTitle);
            lowerCaseSong2 = lowerCaseConvert(savedSongs[i+1].songTitle);
            if(lowerCaseSong1.compare(lowerCaseSong2) == 1){
                temporaryHolder = savedSongs[i];
                savedSongs[i] = savedSongs[i+1];
                savedSongs[i+1] = temporaryHolder;
            }
        }
    }
    // The function will call itself again if the comparison "if" statement was activated
    // the new order of savedSongs is "saved" because the object is its own scope in a way.
    // the actual array belonging to the object is modified not a copy.
    if(doItAgain){
        sortByArtistName(); //I'm not sure if this is considered recursion or not
                            // since the function *is* calling itself, *but* it's not
                            // taking itself as an argument.
    }
    else{
        // I realized this original "displaySongs" function could just be used here, which is nice
        cout << endl << "Sorting by Artist Name..." << endl;
        displaySongs();
    }
}


//Same function as above, but using Song title instead of artist name
void MP3::sortBySongTitle() {
    bool doItAgain {false};
    songAndArtist temporaryHolder;
    
    // numberOfSongs - 1 because the loop will use i and i + 1 - I don't want to reach the very last song == i
    for(int i = 0; i < numberOfSongs - 1; i++){
        string lowerCaseSong1; // These need to be initialized empty every loop
        string lowerCaseSong2;
        lowerCaseSong1 = lowerCaseConvert(savedSongs[i].songTitle);
        lowerCaseSong2 = lowerCaseConvert(savedSongs[i+1].songTitle);
        
        if(lowerCaseSong1.compare(lowerCaseSong2) == 1){
            doItAgain = true;
            temporaryHolder = savedSongs[i];
            savedSongs[i] = savedSongs[i+1];
            savedSongs[i+1] = temporaryHolder;
        }
        else if(lowerCaseSong1.compare(lowerCaseSong2) == 0){ //Same song different artist scenario
            string lowerCaseArtist1;
            string lowerCaseArtist2;
            lowerCaseArtist1 = lowerCaseConvert(savedSongs[i].artist);
            lowerCaseArtist2 = lowerCaseConvert(savedSongs[i+1].artist);
            if(lowerCaseArtist1.compare(lowerCaseArtist2) == 1){
                temporaryHolder = savedSongs[i];
                savedSongs[i] = savedSongs[i+1];
                savedSongs[i+1] = temporaryHolder;
            }
        }
    }
    if(doItAgain){
        sortBySongTitle();

    }
    else{
        cout << endl << "Sorting by Song Title..." << endl;
        displaySongs();
    }
}