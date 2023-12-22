#include<iostream>
#include<string>
#include<ctime>
using namespace std;

// ประกาศตัวแปร
string cardNames[] = {"","A","2","3","4","5","6","7","8","9","10","J","Q","K"};
int cardScores[] = {0,1,2,3,4,5,6,7,8,9,10,10,10,10};

// สุ่มการ์ด
int drawCard(void){
	return rand()%13 + 1;
}

// กรณีได้ J K Q
int calScore(int x,int y,int z){
    // ป๊อกเด้ง  ตัวแปลกนับ 10
	int sum;
    if(x>10) x = 10;
    if(y>10) y = 10;
    if(z>10) z = 10;
    sum = (x+y+z)%10;
    return sum;
}

// ไพ่ของ Yuki
int findYugiAction(int s){
     //ไพ่จะวางมืออัตโนมัติเมื่อได้ 9
	if(s == 9) return 2;
     //ไพ่จะจั่วเพิ่มอัตโนมัติเมื่อได้ 6
	else if(s < 6) return 1;
	else{
		//ถ้าได้ 6 7 8 จะมีโอกาศ 69% จั่วเพิ่ม และมีโอกาศ 31% ที่จะวางมือ
        int x = rand()%100;
        if(x<=69)return 1;
        else return 2;
	}
}

// กระบวนการคิดผลแพ้-ชนะ
void checkWinner(int p, int y){
	cout << "\n---------------------------------\n";
    // กรณี เสมอ
	if(p==y) cout <<   "|             Draw!!!           |";
    // กรณี Player มากกว่า Yuki
	if(p>y) cout <<   "|         Player wins!!!        |";
    // กรณี Player น้อยกว่า Yuki
	if(p<y) cout <<   "|          Yugi wins!!!         |";
	cout << "\n---------------------------------\n";
}

int main(){	

    // สุ่มการ์ด Player และ Yuki
    srand(time(0));
	int playerScore, yugiScore, playerAction, yugiAction;
	int playerCards[3] = {drawCard(), drawCard(), 0};
	int yugiCards[3] = {drawCard(), drawCard(), 0};
	
	// โชว์คะแนนการ์ด
	cout << "---------ORE NO TURN, DRAW!!!------------\n";
	cout << "Your cards: " << cardNames[playerCards[0]] << " " << cardNames[playerCards[1]] << "\n";
	playerScore = calScore(playerCards[0],playerCards[1],playerCards[2]);
	cout << "Your score: " << playerScore << "\n";

    // Player ตัดสินใจ
	do{
		cout << "(1) Destiny draw (2) Stay, SELECT: ";
		cin >> playerAction;
	}while(playerAction !=1 && playerAction !=2);

    // ถ้าจั่วเพิ่ม
	if(playerAction == 1){
		playerCards[2] = drawCard();
        playerScore = calScore(playerCards[0],playerCards[1],playerCards[2]);
		cout << "Player draws the 3rd card!!!" << "\n";
		cout << "Your 3rd card: " << cardNames[playerCards[2]] << "\n";
		cout << "Your new score: " << playerScore << "\n";
	}
	cout << "------------ Turn end -------------------\n\n";
	
	// ตา Yuki จั่ว
	cout << "---------YUGI'S TURN, DRAW!!!------------\n";
	cout << "Yugi's cards: " << cardNames[yugiCards[0]] << " " << cardNames[yugiCards[1]] << "\n";
	yugiScore = calScore(yugiCards[0],yugiCards[1],yugiCards[2]);
	cout << "Yugi's score: " << yugiScore << "\n";
	yugiAction = findYugiAction(yugiScore);
	if(yugiAction == 1){
        yugiCards[2] = drawCard();
        yugiScore = calScore(yugiCards[0],yugiCards[1],yugiCards[2]);
		cout << "Yugi draws the 3rd card!!!\n";
		cout << "Yugi's 3rd card: " << cardNames[yugiCards[2]] << "\n";
		cout << "Yugi's new score: " << yugiScore << "\n";
	}
	cout << "------------ Turn end -------------------\n";
	
	checkWinner(playerScore,yugiScore);
}