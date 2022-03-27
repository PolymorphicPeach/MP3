#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

int posIntegerConvert(string);


int main(int argc, char* argv[]) {
    string userInput {"Unset"};
    int numberOfSongs {0};

    do{
        cout << "\nHow many songs would you like to put on your MP3 player?" << endl
            << "Selection:";
        getline(cin, userInput);
        numberOfSongs = posIntegerConvert(userInput);
    }while (numberOfSongs <= 0);
    

    
    
    
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