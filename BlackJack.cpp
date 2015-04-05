#include <iostream> 
#include <cstdlib>
#include <ctime>
using namespace std;

int s[4][13];                            //define a global array.

void shuffle() {                         //Shuffle the cards.

	for (int i=0;i<13;++i) {
		for (int j=0;j<4;++j) {
			s[j][i] = i+1;
		}
	}
}

void deal(int m, int *card, int &x) {     //Deal the cards.
    int a, b;
		
	srand(time(NULL));
	for (int i=0;i<m;++i) {
		a = rand()%4;
		b = rand()%13;
		
		if (s[a][b]>0) {
			card[x] = s[a][b];
			s[a][b] = -1;
			
			switch (a) {
				case 0: cout << "Spades"; break;
                case 1: cout << "Heart"; break;
                case 2: cout << "Diamond"; break;
                case 3: cout << "Club"; break;
			}
			if (card[x]>1&&card[x]<11) cout << card[x] << " ";
            if (card[x]==1) cout << "A" << " "; 
            if (card[x]==11) cout << "J" << " ";
            if (card[x]==12) cout << "Q" << " ";
            if (card[x]==13) cout << "K" << " "; 
            
			++x;
		}
		else {
			--i;
			continue;
		}		
	}	
}

int judge21(int *card, int x) {     //Judge whether the sum is great than 21.
	float sum=0;
	for(int i=0;i<x;++i) {
		if (card[i]>10&&card[i]<14) sum += 0.5;
	    else sum += card[i];  
    }
    return sum;	
}

enum WinOrLose{cond1, cond2, cond3, cond4, cond5, cond6};
WinOrLose judgeWin(int *card,int cn,int *p,int pn) {     //Judge whether the player wins or not. 
    int cns=judge21(card,cn);
    int pns=judge21(p,pn);
     
    if(pns>21&&cns>21) return cond1;
    if(pns>21&&cns<21) return cond2;
    if(pns<21&&cns>21) return cond3;
    if(pns>cns) return cond4;
    if(pns<cns) return cond5;
    
    else return cond6;  
}

int com[7] = {0};
int player[7] = {0};
int comN = 0;                //It represents the number of cards the computer has.
int plaN = 0;                //It represents the number of cards the player have.
void res() {
    switch(judgeWin(com,comN,player,plaN)) {    //Print out the result.
	    case cond6: {
	        if (comN<plaN) cout << "\nYour sum is the same as the computer's, but your number of cards is larger, so you are the winner!\n";
			if (comN>plaN) cout << "\nYour sum is the same as the computer's, but the computer's number of cards is larger, so you lose.\n";
			if (comN==plaN) cout << "\nThe sums and the numbers of cards are both the same, so it is a draw.\n"; 
			break;
		}
        case cond1: cout << "\n\n"; break;
        case cond2: cout << "\nYour sum is greater than 21, you lose.\n"; break;
        case cond3: cout << "\nThe computer's sum is greater than 21, you win!\n'"; break;
        case cond4: cout << "\nYour sum is greater than the computer's, you win!\n"; break;
        case cond5:	cout << "\nYour sum is less than the computer's, you lose.\n"; break;
    }
}
 
bool checkInput() {                 //Check whether the input is legal or not.
	char ch[2] = {'\0'};
	bool flag;
    cin>>ch;
    flag = true;
    
   	while (flag) {
		flag = false;
		try {
			if (ch[1] != '\0') throw 1;
			if (ch[0]!='y'&&ch[0]!='Y'&&ch[0]!='n'&&ch[0]!='N') throw 1;
		}
		catch (int){
			cout << "Illegal input. You must input 'y' or 'n': ";
			cin >> ch;
			flag=true;
		}
	}
	if (ch[0]=='Y'||ch[0]=='y') return true;
	else return false;
}
 
int playerConti() {                     //Whether the player choose to continue.
	cout << "\nDo you want to continue to deal the cards?";
    if (checkInput()) {
	    cout << "\nYou get a card:\n"; 
        deal(1,player,plaN);
        return 1;
    }
    else return 0;
}	

void comConti() {                       //Whether the computer chooses to continue or not.
     while ((judgeWin(com,comN,player,plaN)==cond4)) {
	     cout << "\nThe computer gets a card:\n"; 
         deal(1,com,comN);
     }
}

void printOut() {                        //Print out the cards the player and computer have.
     cout << "The cards of computer are:(1,11,12,13 represent A,J,Q,K)\n" ;
     for(int i=0;i<comN;++i)
     cout << com[i]<<'\t';
    
     cout << "\nThe cards of you are:(1,11,12,13 represent A,J,Q,K)\n";     
     for(int j=0;j<plaN;++j)
     cout << player[j]<<'\t'; 
     cout << endl;
}

int AskAgain() {
	char answer[2] = {'\0'};
	bool flag2;
	
	cout << "Would you like to play this game again?(Y/N)";
    cin >> answer;
    flag2 = true;
    
   	while (flag2) {
		flag2 = false;
		try {
			if (answer[1] != '\0') throw 1;
			if (answer[0]!='y'&&answer[0]!='Y'&&answer[0]!='n'&&answer[0]!='N') throw 1;
		}
		catch (int){
			cout << "Illegal input. You must input 'y' or 'n': ";
			cin >> answer;
			flag2=true;
		}
	}
	if (answer[0]=='Y'||answer[0]=='y') return true;
	else return false;
}

int main() {
    shuffle();
    cout << "Your turn:";
    cout << "\nYour two cards are:\n";
    deal(2, player, plaN);
    while(playerConti()) {
    	cout << "\n";
	} 
    
    cout << "The computer's turn:\n";
    cout << "The computer's two cards are:\n";
    deal(2, com, comN);
    comConti(); 
    cout<<"\n\n\n";
    
    printOut();
    res(); 
    
    if(AskAgain()) {
        enum WinOrLose{cond1, cond2, cond3, cond4, cond5, cond6};
        comN = 0;   
	plaN = 0; 
	main();         
	}
 
    return 0;
}
