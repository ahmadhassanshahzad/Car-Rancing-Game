#include<iostream>
#include<conio.h>
#include<windows.h>
/* This header file is included for the purpose of cursor shifting and to move the objects    */
#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70 

using namespace std; 
 
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int enemyY[3];
int enemyX[3];
int enemyFlag[3];
//Here we are declaring 3 integer arrays   
char car[4][4] = { {' ','*','*',' '}, 
					{'+','+','+','+'}, 
					{' ','*','*',' '},
					{'!','-','-','!'} }; 
    //This is a 2D array in which our car is initialized
						
int carPos = WIN_WIDTH/2;
int score = 0;
int *ptrScore= &score; 
//This pointer store address of Score 

void transferXY(int x, int y){
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}//This user-define function set the cursor at our desired location 

void setcursor(bool visible, DWORD size) {
	if(size == 0)
		size = 20;	
	
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}
int lvldifficulty(int difficulty)
{
	difficulty-=2;
	if(difficulty<20)
	return 20;
	else if(difficulty>=20)
	return difficulty;
}//This function changes the speed to make game more difficuilt
void drawBorder(){  
	for(int i=0; i<SCREEN_HEIGHT; i++){
		for(int j=0; j<17; j++){
			transferXY(0+j,i); cout<<"+";
			transferXY(WIN_WIDTH-j,i); cout<<"+";
		}
	} 
	for(int k=0; k<SCREEN_HEIGHT; k++){
		transferXY(SCREEN_WIDTH,k); cout<<"+";
	} //This function draws the border for our game
}
void genEnemy(int ind){
	enemyX[ind] = 17 + rand()%(33);  
}//This function generates the enemy at random position
void drawEnemy(int ind){
	if( enemyFlag[ind] == true ){
		transferXY(enemyX[ind], enemyY[ind]);   cout<<"****";  
		transferXY(enemyX[ind], enemyY[ind]+1); cout<<" ** "; 
		transferXY(enemyX[ind], enemyY[ind]+2); cout<<"****"; 
		transferXY(enemyX[ind], enemyY[ind]+3); cout<<" ** ";  
	} 
}
void eraseEnemy(int ind){
	if( enemyFlag[ind] == true ){
		transferXY(enemyX[ind], enemyY[ind]);   cout<<"    ";  
		transferXY(enemyX[ind], enemyY[ind]+1); cout<<"    "; 
		transferXY(enemyX[ind], enemyY[ind]+2); cout<<"    "; 
		transferXY(enemyX[ind], enemyY[ind]+3); cout<<"    "; 
	} 
}
void resetEnemy(int ind){
	eraseEnemy(ind);
	enemyY[ind] = 1;
	genEnemy(ind);
}

void drawCar(){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			transferXY(j+carPos, i+22); cout<<car[i][j];
		}
	}
}
void eraseCar(){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			transferXY(j+carPos, i+22); cout<<" ";
		}
	}
}
 
int collision(){
	if( enemyY[0]+4 >= 23 ){
		if( enemyX[0] + 4 - carPos >= 0 && enemyX[0] + 4 - carPos < 9  ){
			return 1;
		}
	}
	return 0;
} 
void gameover(){
	system("cls");
	cout<<endl;
	cout<<"\t\t--------------------------"<<endl;
	cout<<"\t\t-------- Game Over -------"<<endl;
	cout<<"\t\t---- Your Score : "<<*ptrScore<<" ------"<<endl;
 cout<<"\t\t--------------------------"<<endl<<endl;

	cout<<"\t\tPress any key to go back to menu.";
	getch();
}
void updateScore(){
	transferXY(WIN_WIDTH + 7, 5);cout<<"Score: "<<*ptrScore<<endl;
}

void instructions(){
	
	system("cls");
	cout<<"Instructions";
	cout<<"\n----------------";
	cout<<"\n Avoid Cars by moving left or right. ";
	cout<<"\n\n Press 'a' to move left";
	cout<<"\n Press 'd' to move right";
	cout<<"\n Press 'escape' to exit";
	cout<<"\n\nPress any key to go back to menu";
	getch();
}

void play(){
	int difficulty=100;
	int totalCount=0;
	carPos = carPos-1;
	score = 0;
	ptrScore= &score; 
	enemyFlag[0] = 1;
	
	enemyY[0] = 1;
	  
	system("cls"); 
	drawBorder(); 
	updateScore();
	genEnemy(0);
	
	
	transferXY(WIN_WIDTH + 7, 2);cout<<"Car Game";
	transferXY(WIN_WIDTH + 6, 4);cout<<"----------";
	transferXY(WIN_WIDTH + 6, 6);cout<<"----------";
	transferXY(WIN_WIDTH + 7, 12);cout<<"Control ";
	transferXY(WIN_WIDTH + 7, 13);cout<<"-------- ";
	transferXY(WIN_WIDTH + 2, 14);cout<<" A Key - Left";
	transferXY(WIN_WIDTH + 2, 15);cout<<" D Key - Right"; 
	
	transferXY(18, 5);cout<<"Press any key to start";
	getch();
	transferXY(18, 5);cout<<"                      ";
	
	while(1){
		if(kbhit()){
			char ch = getch();
			if( ch=='a' || ch=='A' ){
				if( carPos > 18 )
					carPos -= 4;
			}
			if( ch=='d' || ch=='D' ){
				if( carPos < 50 )
					carPos += 4;
			} 
			
		} 
		
		drawCar(); 
		drawEnemy(0); 
		 
		if( collision() == 1  ){
			gameover();
			return;
			
		} 
		totalCount++;
		if(totalCount==2)
		{
		difficulty=lvldifficulty(difficulty);
		totalCount=0;
	}
		
		Sleep(difficulty);
		
		
		
		eraseCar();
		eraseEnemy(0);
		  
		
		if( enemyY[0] == 10 && enemyFlag[1] == 0 ){
				enemyFlag[1] = 1;
			}
		
		if( enemyFlag[0] == 1 ){
			enemyY[0] += 1;
		}
		
		
		 
		if( enemyY[0] > SCREEN_HEIGHT-4 ){
			resetEnemy(0);
			score++;
			updateScore();
		}
		
	}
}

int main()
{
	setcursor(0,0); 

	 
	do{
		system("cls");
		transferXY(10,5); cout<<" -------------------------- "; 
		transferXY(10,6); cout<<" |        Car Game        | "; 
		transferXY(10,7); cout<<" --------------------------";
		transferXY(10,9); cout<<"1. Start Game";
		transferXY(10,10); cout<<"2. Instructions";	 
		transferXY(10,11); cout<<"3. Quit";
		transferXY(10,13); cout<<"Select option: ";
		char op = getche(); 
		/* This built-in function stores the value of chatacter from keyboard   */

		if( op=='1') play();
		else if( op=='2') instructions();
		else if( op=='3') exit(0);
		
	}while(1);
	
return 0;
}
