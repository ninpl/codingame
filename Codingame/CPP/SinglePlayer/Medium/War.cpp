#include <iostream>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;
//declarations
class Game{

    enum Suit{D, H, C, S};
    enum VAL{J = 11, Q, K, A};
    
    struct Card{
        Suit suit;
        int value;
    };
    
    public:
        Game();
        ~Game();
        void addCard(string, bool = false);
        void playRound();
        bool isFinished();
        string result();
    private:
        int rounds;
        bool isPat;
        queue<Card*>* player1;
        queue<Card*>* player2;
        queue<Card*>* pile1;
        queue<Card*>* pile2;
        
        Card* converCard(string);
        string printCard(Card*);
        inline Card* getCard(queue<Card*>*);
        inline void returnCardTo(queue<Card*>*);
        void battle();
        void war();
        
        
};

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    auto game = new Game();
    int n; // the number of cards for player 1
    cin >> n; cin.ignore();
    for (int i = 0; i < n; i++) {
        string cardp1; // the n cards of player 1
        cin >> cardp1; cin.ignore();
        game->addCard( cardp1, true );
    }
    // cerr << endl;
    
    int m; // the number of cards for player 2
    cin >> m; cin.ignore();
    for (int i = 0; i < m; i++) {
        string cardp2; // the m cards of player 2
        cin >> cardp2; cin.ignore();
        game->addCard( cardp2 );
    }
    // cerr << endl;
    
    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    while(!game->isFinished()){
        game->playRound();
    }
    cout << game->result() << endl;
    delete game;
}

//implementation
Game::Game():player1(new queue<Card*>), player2(new queue<Card*>), pile1(new queue<Card*>), pile2(new queue<Card*>), rounds(0){}
Game::~Game(){
    delete this->player1;
    delete this->player2;
    delete this->pile1;
    delete this->pile2;
}

Game::Card* Game::converCard(string cardString){
    //conver input to card
    Card* card = new Card{};
    int n = cardString.size();
    for(int i = 0; i < n; ++i){
        char c = cardString.at(i);
        switch(c){
            case 'D': card->suit = D; break;
            case 'H': card->suit = H; break;
            case 'C': card->suit = C; break;
            case 'S': card->suit = S; break;
            //
            case 'J': card->value = J; break;
            case 'Q': card->value = Q; break;
            case 'K': card->value = K; break;
            case 'A': card->value = A; break;
            case '0': card->value = 10; break;
            default:
                card->value = c - '0';//conver char to int
                break;
        }
    }
    return card;
}

string Game::printCard(Card* card)
{
    string cardString;
    switch(card->value){
        case J: cardString = "J";break;
        case Q: cardString = "Q";break;
        case K: cardString = "K";break;
        case A: cardString = "A";break;
        default: cardString = to_string(card->value); break;
    }
    cardString += card->suit == D ? "D" : card->suit == H ? "H" : 
        card->suit == C ? "C" : "S";
        
   return cardString;
}

void Game::addCard(string cardString, bool toFirst){
    queue<Card*>* player = toFirst ? player1 : player2;
    player->push( this->converCard(cardString) );
}

void Game::playRound(){
    this->rounds++;
    this->battle();
}

inline Game::Card* Game::getCard(queue<Card*>* player){
    Card* card = player->front();
    queue<Card*>* pile = player == this->player1 ? this->pile1 : this->pile2;
    pile->push(card);
    player->pop();
    return card;
}

inline void Game::returnCardTo(queue<Card*>* player){
    queue<Card*>* pile = this->pile1;
    while(!pile->empty()){
        player->push(pile->front());
        pile->pop();
    }
    
    pile = this->pile2;
    while(!pile->empty()){
        player->push(pile->front());
        pile->pop();
    }
}

void Game::battle(){
    Card* c1 = this->getCard(this->player1);
    Card* c2 = this->getCard(this->player2);
    
    if(c1->value > c2->value){
        this->returnCardTo(this->player1);
    }else if(c1->value < c2->value){
        this->returnCardTo(this->player2);
    }else{
        this->war();
    }
}

void Game::war(){
    // cerr << "war" << endl;
    if(this->player1->size() < 3 || this->player2->size() < 3){
        isPat = true;
        return;
    }
    
    for(int i = 0; i < 3; ++i)
        this->getCard(this->player1);
    for(int i = 0; i < 3; ++i)
        this->getCard(this->player2);
    this->battle();
}

bool Game::isFinished(){
    return this->player1->empty() || this->player2->empty();
}
string Game::result(){
    if(this->isPat)return "PAT";
    return to_string(this->player1->empty() ? 2 : 1) + " " + to_string(this->rounds);
}