#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
using namespace std;
struct Space
{
	int index;//The index of the piece that occupies the space
	bool dan[4];//For different boolean values used to determine the conditions for checkmate
	int all;//The alliance of the piece that occupies the space
};
/*
Dan[0] and Dan[1] these are the possible spaces a corresponding player can attack in their next turn; this will help
determine where a player's king can move and it will also help identify if a king or the last moved piece is in danger
Dan[2] this indicates where a given piece can move in its next turn
Dan[3] this is a special case used only for the last moved piece and honestly I dont think I can explain this using only words
I will reserve this explaination f
*/

class Piece
{
	protected:
		char name;
		bool alliance;
		bool danger;
		bool dead;
		bool fake;
		bool moved;
		int x;
		int y;
	public:	
		Piece(char c,bool a,int X,int Y)
		{
			
			alliance = a;
			name = c;
			x = X;
			y = Y;
			fake = 0;
			moved = 0;
			dead = 0;
		}
		Piece(char c,bool a,int X,int Y,bool d,bool m)
		{
			alliance = a;
			name = c;
			x = X;
			y = Y;
			fake = 0;
			dead = d;				
			moved = m;
			cout<<name<<": allies: "<<alliance<<" Xpos: "<<x<<" Ypos: "<<y<< " dead?: "<<dead<<" moved?: "<< moved<<endl;
		}
		Piece(){fake = 1;}
		virtual void cast(Space s[][8],int e) = 0;
		virtual void move(int Y,int X)
		{
			y = Y;
			x = X;
		}
		void Defeat()
		{
			dead = 1;
		}
		virtual bool checkMate(Space s[][8]) = 0;
		void Endanger(bool a)
		{
			danger = a;
		}
		char Name()
		{
			return name;
		}
		bool getAll()
		{
			return alliance;
		}
		int getX()
		{
			return x;
		}
		int getY()
		{
			return y;
		}
		bool getDan()
		{
			return danger;
		}
		bool getDead()
		{
			return dead;
		}
		bool getMoved()
		{
			return moved;
		}
		bool Fake()
		{
			return fake;
		}
		void Moved()
		{
			moved = 1;
		}
		void revive()
		{
			dead = 0;
		}
		
		virtual bool Promote(){return 0;}
};
class Rook:public Piece
{
	public:
		Rook(char c,bool a,int X,int Y):Piece(c,a,X,Y){}
		Rook(char c,bool a,int X,int Y,bool d,bool m):Piece(c,a,X,Y,d,m){}
		void cast(Space s[][8],int e)
		{
			int i = 1;               
			while(((x-i)>-1&&s[y][x-i].all==-1&&(e!=3||!s[y][x-i].dan[2]))||(e==3&&s[y][x-i].index==16*(!alliance))){s[y][x-i].dan[e] = 1;i++;}
			if((x-i>-1)){s[y][x-i].dan[e]=(e!=2||s[y][x-i].all!=alliance)&&(e!=3||!s[y][x-i].dan[2]);}
			i = 1;
			while(((y-i)>-1&&s[y-i][x].all==-1&&(e!=3||!s[y-i][x].dan[2]))||(e==3&&s[y-i][x].index==16*(!alliance))){s[y-i][x].dan[e] = 1;i++;}
			if((y-i>-1)){s[y-i][x].dan[e]=(e!=2||s[y-i][x].all!=alliance)&&(e!=3||!s[y-i][x].dan[2]);}
			i = 1;
			while(((x+i)<8&&s[y][x+i].all==-1&&(e!=3||!s[y][x+i].dan[2]))||(e==3&&s[y][x+i].index==16*(!alliance))){s[y][x+i].dan[e] = 1;i++;}
			if((x+i<8)){s[y][x+i].dan[e]=(e!=2||s[y][x+i].all!=alliance)&&(e!=3||!s[y][x+i].dan[2]);}
			i = 1;
			while(((y+i)<8&&s[y+i][x].all==-1&&(e!=3||!s[y+i][x].dan[2]))||(e==3&&s[y+i][x].index==16*(!alliance))){s[y+i][x].dan[e] = 1;i++;}
			if((y+i<8)){s[y+i][x].dan[e]=(e!=2||s[y+i][x].all!=alliance)&&(e!=3||!s[y+i][x].dan[2]);}	
		}
		bool checkMate(Space s[][8])
		{
			return 0;
		}
};
class Bishop:public Piece
{
	public:
		Bishop(char c,bool a,int X,int Y):Piece(c,a,X,Y){}
		Bishop(char c,bool a,int X,int Y,bool d,bool m):Piece(c,a,X,Y,d,m){}
		void cast(Space s[][8],int e)
		{
			int i = 1;              
			while(((x-i)>-1&&(y-i)>-1&&s[y-i][x-i].all==-1&&(e!=3||!s[y-i][x-i].dan[2]))||(e==3&&s[y-i][x-i].index==16*(!alliance))){s[y-i][x-i].dan[e] = 1;i++;}
			if((x-i)>-1&&(y-i)>-1){s[y-i][x-i].dan[e]=(e!=2||s[y-i][x-i].all!=alliance)&&(e!=3||!s[y-i][x-i].dan[2]);}
			i = 1;
			while(((x-i)>-1&&(y+i)<8&&s[y+i][x-i].all==-1&&(e!=3||!s[y+i][x-i].dan[2]))||(e==3&&s[y+i][x-i].index==16*(!alliance))){s[y+i][x-i].dan[e] = 1;i++;}
			if((x-i)>-1&&(y+i)<8){s[y+i][x-i].dan[e]=(e!=2||s[y+i][x-i].all!=alliance)&&(e!=3||!s[y+i][x-i].dan[2]);}
			i = 1;
			while(((x+i)<8&&(y+i)<8&&s[y+i][x+i].all==-1&&(e!=3||!s[y+i][x+i].dan[2]))||(e==3&&s[y+i][x+i].index==16*(!alliance))){s[y+i][x+i].dan[e] = 1;i++;}
			if((x+i)<8&&(y+i)<8){s[y+i][x+i].dan[e]=(e!=2||s[y+i][x+i].all!=alliance)&&(e!=3||!s[y+i][x+i].dan[2]);}
			i = 1;
			while(((x+i)<8&&(y-i)>-1&&s[y-i][x+i].all==-1&&(e!=3||!s[y-i][x+i].dan[2]))||(e==3&&s[y-i][x+i].index==16*(!alliance))){s[y-i][x+i].dan[e] = 1;i++;}
			if((x+i)<8&&(y-i)>-1){s[y-i][x+i].dan[e]=(e!=2||s[y-i][x+i].all!=alliance)&&(e!=3||!s[y-i][x+i].dan[2]);}
		}
		bool checkMate(Space s[][8])
		{
			return 0;
		}
};
class Queen:public Piece
{
	public:
		Queen(char c,bool a,int X,int Y):Piece(c,a,X,Y){}
		Queen(char c,bool a,int X,int Y,bool d,bool m):Piece(c,a,X,Y,d,m){}
		void cast(Space s[][8],int e)
		{	
			int i = 1;               
			while(((x-i)>-1&&s[y][x-i].all==-1&&(e!=3||!s[y][x-i].dan[2]))||(e==3&&s[y][x-i].index==16*(!alliance))){s[y][x-i].dan[e] = 1;i++;}
			if((x-i>-1)){s[y][x-i].dan[e]=(e!=2||s[y][x-i].all!=alliance)&&(e!=3||!s[y][x-i].dan[2]);}
			i = 1;
			while(((y-i)>-1&&s[y-i][x].all==-1&&(e!=3||!s[y-i][x].dan[2]))||(e==3&&s[y-i][x].index==16*(!alliance))){s[y-i][x].dan[e] = 1;i++;}
			if((y-i>-1)){s[y-i][x].dan[e]=(e!=2||s[y-i][x].all!=alliance)&&(e!=3||!s[y-i][x].dan[2]);}
			i = 1;
			while(((x+i)<8&&s[y][x+i].all==-1&&(e!=3||!s[y][x+i].dan[2]))||(e==3&&s[y][x+i].index==16*(!alliance))){s[y][x+i].dan[e] = 1;i++;}
			if((x+i<8)){s[y][x+i].dan[e]=(e!=2||s[y][x+i].all!=alliance)&&(e!=3||!s[y][x+i].dan[2]);}
			i = 1;
			while(((y+i)<8&&s[y+i][x].all==-1&&(e!=3||!s[y+i][x].dan[2]))||(e==3&&s[y+i][x].index==16*(!alliance))){s[y+i][x].dan[e] = 1;i++;}
			if((y+i<8)){s[y+i][x].dan[e]=(e!=2||s[y+i][x].all!=alliance)&&(e!=3||!s[y+i][x].dan[2]);}
			i = 1;            
			while(((x-i)>-1&&(y-i)>-1&&s[y-i][x-i].all==-1&&(e!=3||!s[y-i][x-i].dan[2]))||(e==3&&s[y-i][x-i].index==16*(!alliance))){s[y-i][x-i].dan[e] = 1;i++;}
			if((x-i)>-1&&(y-i)>-1){s[y-i][x-i].dan[e]=(e!=2||s[y-i][x-i].all!=alliance)&&(e!=3||!s[y-i][x-i].dan[2]);}
			i = 1;
			while(((x-i)>-1&&(y+i)<8&&s[y+i][x-i].all==-1&&(e!=3||!s[y+i][x-i].dan[2]))||(e==3&&s[y+i][x-i].index==16*(!alliance))){s[y+i][x-i].dan[e] = 1;i++;}
			if((x-i)>-1&&(y+i)<8){s[y+i][x-i].dan[e]=(e!=2||s[y+i][x-i].all!=alliance)&&(e!=3||!s[y+i][x-i].dan[2]);}
			i = 1;
			while(((x+i)<8&&(y+i)<8&&s[y+i][x+i].all==-1&&(e!=3||!s[y+i][x+i].dan[2]))||(e==3&&s[y+i][x+i].index==16*(!alliance))){s[y+i][x+i].dan[e] = 1;i++;}
			if((x+i)<8&&(y+i)<8){s[y+i][x+i].dan[e]=(e!=2||s[y+i][x+i].all!=alliance)&&(e!=3||!s[y+i][x+i].dan[2]);}
			i = 1;
			while(((x+i)<8&&(y-i)>-1&&s[y-i][x+i].all==-1&&(e!=3||!s[y-i][x+i].dan[2]))||(e==3&&s[y-i][x+i].index==16*(!alliance))){s[y-i][x+i].dan[e] = 1;i++;}
			if((x+i)<8&&(y-i)>-1){s[y-i][x+i].dan[e]=(e!=2||s[y-i][x+i].all!=alliance)&&(e!=3||!s[y-i][x+i].dan[2]);}
		}
		bool checkMate(Space s[][8])
		{
			return 0;
		}
};
class Knight:public Piece
{
	public:
		Knight(char c,bool a,int X,int Y):Piece(c,a,X,Y){}
		Knight(char c,bool a,int X,int Y,bool d,bool m):Piece(c,a,X,Y,d,m){}
		void cast(Space s[][8],int e)//complete
		{
			if(x+1<8&&y+2<8&&((s[y+2][x+1].all!=alliance)||(s[y+2][x+1].all==alliance&&e!=2)))	 	
			{                    //| |
				s[y+2][x+1].dan[e] = !s[y+2][x+1].dan[2]||e!=3; 		
			}
			if(x-1>-1&&y+2<8&&((s[y+2][x-1].all!=alliance)||(s[y+2][x-1].all==alliance&&e!=2)))
			{
				s[y+2][x-1].dan[e] = !s[y+2][x-1].dan[2]||e!=3;
			}
			if(x+2<8&&y+1<8&&((s[y+1][x+2].all!=alliance)||(s[y+1][x+2].all==alliance&&e!=2)))
			{
				s[y+1][x+2].dan[e] = !s[y+1][x+2].dan[2]||e!=3;
			}
			if(x+2<8&&y-1>-1&&((s[y-1][x+2].all!=alliance)||(s[y-1][x+2].all==alliance&&e!=2)))
			{
				s[y-1][x+2].dan[e] = !s[y-1][x+2].dan[2]||e!=3;
			}
			if(x-2>-1&&y+1<8&&((s[y+1][x-2].all!=alliance)||(s[y+1][x-2].all==alliance&&e!=2)))
			{
				s[y+1][x-2].dan[e] = !s[y+1][x-2].dan[2]||e!=3;
			}
			if(x-2>-1&&y-1>-1&&((s[y-1][x-2].all!=alliance)||(s[y-1][x-2].all==alliance&&e!=2)))
			{
				s[y-1][x-2].dan[e] = !s[y-1][x-2].dan[2]||e!=3;
			}
			if(x+1<8&&y-2>-1&&((s[y-2][x+1].all!=alliance)||(s[y-2][x+1].all==alliance&&e!=2)))
			{
				s[y-2][x+1].dan[e] = !s[y-2][x+1].dan[2]||e!=3;
			}
			if(x-1>-1&&y-2>-1&&((s[y-2][x-1].all!=alliance)||(s[y-2][x-1].all==alliance&&e!=2)))
			{
				s[y-2][x-1].dan[e] = !s[y-2][x-1].dan[2]||e!=3;
			}
		}
		bool checkMate(Space s[][8])
		{
			return 0;
		}
};
class Pawn:public Piece
{	
	public:
		Pawn(char c,bool a,int X,int Y):Piece(c,a,X,Y){}
		Pawn(char c,bool a,int X,int Y,bool d,bool m):Piece(c,a,X,Y,d,m){}
		Pawn(int a):Piece(){}
		void cast(Space s[][8],int e)//direction depends on alliance
		{
			
			if(!(y==7||y==0))
			{
				if(s[y-(2*alliance)+1][x].all == -1&&e == 2)
				{
					s[y-(2*alliance)+1][x].dan[e] = 1;	
				}
				if(x+1<8&&(s[y-(2*alliance)+1][x+1].all == !alliance||e != 2))//attack
				{
					s[y-(2*alliance)+1][x+1].dan[e] = !s[y-(2*alliance)+1][x+1].dan[2]||e!=3;
				}
				if(x-1>-1&&(s[y-(2*alliance)+1][x-1].all == !alliance||e != 2))//attack
				{
					s[y-(2*alliance)+1][x-1].dan[e] = !s[y-(2*alliance)+1][x-1].dan[2]||e!=3;
				}
				if(s[y-(4*alliance)+2][x].all == -1&&!moved&&e == 2)
				{
					s[y-(4*alliance)+2][x].dan[e] = 1;	
				} 
			}
		}
		void move(int Y,int X)
		{
			y = Y;
			x = X;
		}
		bool checkMate(Space s[][8])
		{
			return 0;
		}
		bool Promote()
		{
			return y == !(alliance)*7;
		}
};
class King:public Piece
{
	private:
		bool check[8];
	public:
		King(char c,bool a,int X,int Y):Piece(c,a,X,Y){}
		King(char c,bool a,int X,int Y,bool d,bool m):Piece(c,a,X,Y,d,m){}
		void cast(Space s[][8],int e)
		{
			if(y+1<8&&x-1>-1){s[y+1][x-1].dan[e] = ((!s[y+1][x-1].dan[!alliance]&&s[y+1][x-1].all!=alliance)||e!=2);check[2] = !s[y+1][x-1].dan[e];}	
			if(y+1<8&&x+1<8){s[y+1][x+1].dan[e] = ((!s[y+1][x+1].dan[!alliance]&&s[y+1][x+1].all!=alliance)||e!=2);check[0] = !s[y+1][x+1].dan[e];}
			if(y-1>-1&&x-1>-1){s[y-1][x-1].dan[e] = ((!s[y-1][x-1].dan[!alliance]&&s[y-1][x-1].all!=alliance)||e!=2);check[1] = !s[y-1][x-1].dan[e];}//			
			if(y-1>-1&&x+1<8){s[y-1][x+1].dan[e] = ((!s[y-1][x+1].dan[!alliance]&&s[y-1][x+1].all!=alliance)||e!=2);check[3] = !s[y-1][x+1].dan[e];}//
			if(x-1>-1){s[y][x-1].dan[e] = ((!s[y][x-1].dan[!alliance]&&s[y][x-1].all!=alliance)||e!=2);check[4] = !s[y][x-1].dan[e];}
			if(x+1<8){s[y][x+1].dan[e] = ((!s[y][x+1].dan[!alliance]&&s[y][x+1].all!=alliance)||e!=2);check[5] = !s[y][x+1].dan[e];}
			if(y+1<8){s[y+1][x].dan[e] = ((!s[y+1][x].dan[!alliance]&&s[y+1][x].all!=alliance)||e!=2);check[6] = !s[y+1][x].dan[e];}			
			if(y-1>-1){s[y-1][x].dan[e] = ((!s[y-1][x].dan[!alliance]&&s[y-1][x].all!=alliance)||e!=2);check[7] = !s[y-1][x].dan[e];}
		}
		void move(int Y,int X)
		{
			y = Y;
			x = X;
		}
		bool checkMate(Space s[][8])
		{
			
			int a = 0; 
			cast(s,2);
			if(y+1<8&&x+1<8){a = a+(s[y+1][x+1].dan[3]||check[0]);}else{a = a+1;}
			
			if(y-1>-1&&x-1>-1){a = a+(s[y-1][x-1].dan[3]||check[1]);}else{a = a+1;}  
			
			if(y+1<8&&x-1>-1){a = a+(s[y+1][x-1].dan[3]||check[2]);}else{a = a+1;}
		
			if(y-1>-1&&x+1<8){a = a+(s[y-1][x+1].dan[3]||check[3]);}else{a = a+1;} 
			
			if(x-1>-1){a = a+(s[y][x-1].dan[3]||check[4]);}else{a = a+1;} 
		
			if(x+1<8){a = a+(s[y][x+1].dan[3]||check[5]);}else{a = a+1;}    
			 
			if(y+1<8){a = a+(s[y+1][x].dan[3]||check[6]);}else{a = a+1;}   
		 
			if(y-1>-1){a = a+(s[y-1][x].dan[3]||check[7]);}else{a = a+1;}
			
			if(a == 8){cout<<"mate, ";}
			return a == 8;	
		}
};
class Player
{
	private:
		string name;
		bool alliance;	
	public:	
		Player(string n, bool a)
		{
			name = n;
			alliance = a;
		}
		Player(){}
		string getName()
		{
			return name;
		}
		bool getAll()
		{
			return alliance;
		}
};
class Board
{
	private:
		Space space[8][8];
		Piece* piece[32];
		Player player[2];
		bool save; 
	public:
		Board(){}
		Board(string n1,string n2)
		{
			player[0] = Player(n1,0);
			player[1] = Player(n2,1);
			int i;
			piece[0] = new King('*',0,4,0);
			piece[1] = new Queen('Q',0,3,0);
			piece[2] = new Bishop('B',0,5,0);
			piece[3] = new Bishop('B',0,2,0);
			piece[4] = new Knight('K',0,6,0);
			piece[5] = new Knight('K',0,1,0);
			piece[6] = new Rook('R',0,7,0);
			piece[7] = new Rook('R',0,0,0);
			for(i = 8;i<16;i++)
			{
				piece[i] = new Pawn('P',0,i-8,1);
			}
			piece[16] = new King('+',1,4,7);
			piece[17] = new Queen('q',1,3,7);
			piece[18] = new Bishop('b',1,5,7);
			piece[19] = new Bishop('b',1,2,7);
			piece[20] = new Knight('k',1,6,7);
			piece[21] = new Knight('k',1,1,7);
			piece[22] = new Rook('r',1,7,7);
			piece[23] = new Rook('r',1,0,7);
			for(i = 24;i<32;i++)
			{
				piece[i] = new Pawn('p',1,i-24,6);
			}
			SetBoard();
		}
		void SetBoard()
		{
			save = 0;
			int i;
			int j;
			for(i = 0;i<8;i++)
			{
				for(j =0;j<8;j++)
				{
					space[i][j].index = 32;
				}
			}
			for(i=0;i<32;i++)
			{
				if(!piece[i]->Fake()&&!piece[i]->getDead())
				{
					space[piece[i]->getY()][piece[i]->getX()].index = i;
				}
			}
			Clear();
			for(i = 0;i<8;i++)
			{
				for(j =0;j<8;j++)
				{
					if(space[i][j].index == 32)
					{
						space[i][j].all = -1;	
					}
					else
					{
						space[i][j].all = piece[space[i][j].index]->getAll();
					}
				}
			}
		}
		string getName(int i)
		{
			return player[i].getName();
		}
		bool getSave()
		{
			return save;
		}
		void Save(bool turn)
		{
			ofstream FILE("SaveFile.txt");
			if(!FILE.is_open())
			{
				cout<<"Cannot open save file";
			}
			FILE<<getName(0)<<endl;
			for(int i = 0;i<16;i++)
			{
				FILE<<piece[i]->Name()<<piece[i]->getX()<<piece[i]->getY()<<piece[i]->getDead()<<piece[i]->getMoved()<<endl;
			}
			FILE<<getName(1)<<endl;
			for(int i = 16;i<32;i++)
			{
				FILE<<piece[i]->Name()<<piece[i]->getX()<<piece[i]->getY()<<piece[i]->getDead()<<piece[i]->getMoved()<<endl;
			}
			FILE<<turn<<endl;
			FILE.close();
		}
		bool Reconstruct(string fileName, int* a)//implement bool[] dead
		{
			int i;
			char buffer[20];
			ifstream FILE("SaveFile.txt");
			if(!FILE.is_open())
			{
				cout<<"Cannot open "<<fileName;
				return 0;
			}
			else
			{
				FILE.getline(buffer,19);
				
				player[0] = Player(buffer,0);
				for(i = 0;i<16;i++)
				{
					FILE.getline(buffer,7);
					cout<<buffer[2]<<buffer[3];
					switch (buffer[0])
					{	
						case '*':
							piece[i] = new King('*',0,(int)buffer[1]-48,(int)buffer[2]-48,(int)buffer[3]-48,(int)buffer[4]-48);
							break;		
						case 'Q':
							piece[i] = new Queen('Q',0,(int)buffer[1]-48,(int)buffer[2]-48,(int)buffer[3]-48,(int)buffer[4]-48);
							break;	
						case 'K':
							piece[i] = new Knight('K',0,(int)buffer[1]-48,(int)buffer[2]-48,(int)buffer[3]-48,(int)buffer[4]-48);
							break;	
						case 'R':
							piece[i] = new Rook('R',0,(int)buffer[1]-48,(int)buffer[2]-48,(int)buffer[3]-48,(int)buffer[4]-48);
							break;	
						case 'B':
							piece[i] = new Bishop('B',0,(int)buffer[1]-48,(int)buffer[2]-48,(int)buffer[3]-48,(int)buffer[4]-48);
							break;	
						case 'P': 	
							piece[i] = new Pawn('P',0,(int)buffer[1]-48,(int)buffer[2]-48,(int)buffer[3]-48,(int)buffer[4]-48);
							break;	
						case 'X':
							piece[i] = new Pawn(i);
							break;		
					}
				}
				FILE.getline(buffer,19);
				player[1] = Player(buffer,1);
				for(i = 16;i<32;i++)
				{
					FILE.getline(buffer,7);
					switch (buffer[0])
					{
						case '+':
							piece[i] = new King('+',1,(int)buffer[1]-48,(int)buffer[2]-48,(int)buffer[3]-48,(int)buffer[4]-48);	
							break;	
						case 'q':
							piece[i] = new Queen('q',1,(int)buffer[1]-48,(int)buffer[2]-48,(int)buffer[3]-48,(int)buffer[4]-48);
							break;	
						case 'k':
							piece[i] = new Knight('k',1,(int)buffer[1]-48,(int)buffer[2]-48,(int)buffer[3]-48,(int)buffer[4]-48);
							break;	
						case 'r':
							piece[i] = new Rook('r',1,(int)buffer[1]-48,(int)buffer[2]-48,(int)buffer[3]-48,(int)buffer[4]-48);
							break;	
						case 'b':
							piece[i] = new Bishop('b',1,(int)buffer[1]-48,(int)buffer[2]-48,(int)buffer[3]-48,(int)buffer[4]-48);
							break;	
						case 'p': 	
							piece[i] = new Pawn('p',1,(int)buffer[1]-48,(int)buffer[2]-48,(int)buffer[3]-48,(int)buffer[4]-48);
							break;	
						case 'X':
							piece[i] = new Pawn(i);
							break;		
					}
				}
				FILE.getline(buffer,2);
				*a = (int)buffer[0] - 48;
				SetBoard();
				FILE.close();
				return 1;
			}
		}
		bool move(bool a)
		{
			cout<<"It is your turn, "<<player[a].getName()<<endl;
			string ans;
			bool b = 0;//Is the turn valid?
			bool moved = 0;//Has the player passed the moving phase?
			bool picked = 0;//Has the player picked a piece yet?
			int startPos;//Which space has the piece you wish to move?
			int endPos;//Where do you wish to move that piece?
			int pieceID;//What is the ID of the piece you wish to move?
			int promotion;//In the case that a pawn reaches the end of board, which piece do you wish to promote it to?
			int targetID;
			int i;
			while(!b&&!save)
			{
				picked = 0;
				while(!picked&&!save)
				{
					Clear();
					moved = 0;
					cout<<"Choose a piece to move: [enter 'save' to save and quit]"<<endl;
					cin>>ans;
					//Converts A1 format move into a number from 0 to 63 used to represent each space
					startPos = Index(ans);
					
					if(startPos != -1&&ans != "save")
					{
						cout<<"when this happen";
						//The piece ID or the number corresponding to the piece as it appears in the array 
						//can be found in the space the piece is on.
						pieceID = space[startPos/8][startPos%8].index;
						if(pieceID == 32)
						{
							cout<<"That space is empty"<<endl;
						}
						else
						{
							if(piece[pieceID]->getAll() == a)
							{
								piece[pieceID]->cast(space,2);
								//Sets the dan[2] of each space the piece can move on to 2
								while(!moved)
								{
									cout<<"Move it where?[X to cancel]"<<endl;
									cin>>ans;
									//This if else statement accounts for the possibllity that a player may decide to 
									//move another piece after selecting the first; the input for cancelling is "x"
									if(!(ans == "X"||ans == "x"))
									{
										endPos = Index(ans);
										if(endPos != -1)
										{
											if(space[endPos/8][endPos%8].dan[2])
											{
												moved = 1;
												picked = 1;
												targetID = space[endPos/8][endPos%8].index;
												Move(startPos,endPos,pieceID,targetID);
											}
											else
											{
												cout<<"That is not a space to which "<<piece[pieceID]->Name()<<" can move.";
											}
										}
										else
										{
											cout<<"That space does not exist.";
										}
									}
									else
									{
										moved = 1;
									}
								}	
							}
							else
							{
								cout<<"That is not a piece you control."<<endl;	
							}
						}
					}
					else if(ans == "save")
					{
						save = 1;
					}
				}
				if(!save)
				{
					Update(pieceID);
					//If your king is still in danger after a move, that move is deemed invalid and is reset
					if(piece[a*16]->getDan())
					{
						cout<<"That is not a valid move";
						Move(endPos,startPos,pieceID,targetID);
						Revive(targetID);
					}
					else
					{
						b = 1;
					}
				}
			}
			if(save)
			{
				Save(a);
				return 0;
			}
			else
			{
				//indicates that the piece has moved 
				if(piece[pieceID]->Promote())
				{
					Promotion(pieceID,a);
				}
				piece[pieceID]->Moved();
				Print();
				//Start at the opponents first piece and end at their final piece
				for(i = !a*16+1;i<16+!a*16;i++)
				{
					//If an opponents piece is on the board then find where that piece can move to obstruct 
					//path of the last moved piece
					if(!piece[i]->getDead()&&!piece[i]->Fake())
					{
						piece[i]->cast(space,2);
					}
				}
				//If it is not possible to capture the last moved piece in the next turn, its
				//threat must be analyzed check conditions for checkmate
				if(!piece[pieceID]->getDan())
				{
					piece[pieceID]->cast(space,3);	
				}
				//If the opponents king is in danger, call check
				if(piece[!a*16]->getDan())
				{	
					//This is where the cast(space,3) comes in handy; if there is nothing your opponent can do
					//to save the king outside of moving the king, then the conditions of checkmate
					//will be based soley on whether or not the king can move out of the way
					if(space[piece[!a*16]->getY()][piece[!a*16]->getX()].dan[3])
					{
						return piece[(!a)*16]->checkMate(space);
					}
				}
				return 0;
			}
		}
		void Revive(int target)
		{
			space[piece[target]->getX()][piece[target]->getY()].index = target;
			space[piece[target]->getX()][piece[target]->getY()].all = piece[target]->getAll(); 
			piece[target]->revive();	
		}
		void Move(int start, int end,int moved,int target)
		{
			piece[moved]->move(end/8,end%8);
			space[start/8][start%8].index = 32;
			space[start/8][start%8].all = -1;
			if(space[end/8][end%8].index != 32)
			{
				piece[target]->Defeat();
			}
			space[end/8][end%8].index = moved;
			space[end/8][end%8].all = piece[moved]->getAll();
		}
	 	void Update(int ID)//Clear then cast all pieces
		{	
			Clear();
			for(int i = 0;i<32;i++)
			{
				if(!piece[i]->getDead()&&!piece[i]->Fake())
				{
					piece[i]->cast(space,(int)piece[i]->getAll());	
				}	
			} 
			//at the end of a move, check the danger status of both kings and the last moved piece 
			piece[ID]->Endanger(space[piece[ID]->getY()][piece[ID]->getX()].dan[!piece[ID]->getAll()]);
			piece[0]->Endanger(space[piece[0]->getY()][piece[0]->getX()].dan[!piece[0]->getAll()]);
			piece[16]->Endanger(space[piece[16]->getY()][piece[16]->getX()].dan[!piece[16]->getAll()]);	
		}
		void Promotion(int ID,bool a)
		{
			int i;
			int ans;
			int newRank;
			int NumDead = 0;
			bool chosen = 0;
			while(!chosen)
			{	
				cout<<"Which piece do you wish promote your pawn to?"<<endl;
				cout<<"0. cancel"<<endl;
				for(i = a*16;i<8+a*16;i++)
				{
					if(piece[i]->getDead()&&!piece[i]->Fake())
					{
						NumDead++;
						cout<<piece[i]->Name()<<endl;
					}
				}	
				cin>>ans;
				if(ans == 0)
				{
					cout<<"Pawn was not promoted."<<endl;
					chosen = 1;
				}
				else if(ans > 0 && ans <= NumDead)
				{
					i = a*16;
					while(ans > 0)
					{
						i++;
						if(piece[i]->getDead())
						{
							ans--;
						}
					}
					piece[ID]->Defeat();
					piece[i]->move(piece[ID]->getY(),piece[ID]->getX());
					space[piece[i]->getY()][piece[i]->getX()].index = i;
					space[piece[i]->getY()][piece[i]->getX()].all = a;
					piece[i]->revive();
					chosen = 1;
				}
				else
				{
					cout<<"That is not an option."<<endl;
				}	
			}
		}
		int Index(string ans)
		{
			ans.at(0) = toupper(ans.at(0));
			ans.at(1) = toupper(ans.at(1));
			string R = "ABCDEFGH12345678";
			int index = 0;
			if(R.find(ans.at(0))/8==1)
			{
				index = index + 8*(R.find(ans.at(0))%8);
				index = index + R.find(ans.at(1))%8;
				return index;
			}
			if(R.find(ans.at(1))/8==1)
			{
				index = index + 8*(R.find(ans.at(1))%8);
				index = index + R.find(ans.at(0))%8;
				return index;		
			}
			else
			{
				return -1;
			}
		}
		void Clear()
		{
			int i;
			int j;
			for(j = 0;j<8;j++)
			{
				for(i = 0;i<8;i++)
				{
					space[i][j].dan[0] = 0;
					space[i][j].dan[1] = 0;
					space[i][j].dan[2] = 0;
					space[i][j].dan[3] = 0;
				}
			}
		}
		void Print()
		{
			int i;
			int  j;
			cout<<" "+ player[0].getName()+"\n";
			cout<<" |---|---|---|---|---|---|---|---|"<<endl;
			for(i = 0;i<8;i++)
			{
				cout<<i+1<<"|";
				for(j = 0;j<8;j++)
				{	
					if(space[i][j].index != 32)
					{
						cout<<" "<<piece[space[i][j].index]->Name()<<" |";
					}
					else
					{
						cout<<"   |";
					}
				}
				cout<<endl<<" |---|---|---|---|---|---|---|---|"<<endl;
			}
			cout<<"   A   B   C   D   E   F   G   H  "<<endl;
			cout<<"                       "+player[1].getName()+"\n";           
		}
		void allPrint()
		{
			int i;
			int  j;
			cout<<" |---|---|---|---|---|---|---|---|"<<endl;
			for(i = 0;i<8;i++)
			{
				cout<<i+1<<"|";
				for(j = 0;j<8;j++)
				{	
						cout<<" "<<space[i][j].all<<" |";	
				}
				cout<<endl<<" |---|---|---|---|---|---|---|---|"<<endl;
			}
			cout<<"   A   B   C   D   E   F   G   H  "<<endl;
		}
		void castPrint(char n,int a)
		{
			int i;
			int  j;
			cout<<n<<"|---|---|---|---|---|---|---|---|"<<endl;
			for(i = 0;i<8;i++)
			{
				cout<<i+1<<"|";
				for(j = 0;j<8;j++)
				{	
						cout<<" "<<space[i][j].dan[a]<<" |";	
				}
				cout<<endl<<" |---|---|---|---|---|---|---|---|"<<endl;
			}
			cout<<"   A   B   C   D   E   F   G   H  "<<endl;
		}
};
main()
{
	int i = 0;
	bool a;
	string ans;
	string p1;
	string p2;
	Board board;
	cout<<"Load save file? y/n";
	cin>>ans;
	while(ans.at(0) == 'y')
	{
		cout<<"What is the name of the file?";
		cin>>ans;
		cout<<endl;
		if(board.Reconstruct(ans,&i))
		{
			cout<<"Save loaded successfully."<<endl;
			ans = '*';
		}
		else
		{
			do
			{
			cout<<"Load save file? y/n";
			cin>>ans;
			}while(ans.at(0) != 'y'&&ans.at(0) != 'n');
		}
	}
	if(ans.at(0) == 'n')
	{
		cout<<"Player one's name?";
		cin>>p1;
		cout<<"Player two's name?";
		cin>>p2;
		board = Board(p1,p2);
	}
	board.Print();
	bool c;
	while(!board.getSave()&&!board.move((bool)(i%2)))
	{
		i++;
	}
	if(board.getSave())
	{
		cout<<"Save complete.";
	}
	else
	{
		cout<<board.getName(i%2)<<" wins!";	
	}
}
