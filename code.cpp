class Student{
    public:
        void makeMove(int Record[5][6], int Max[5][6], Color color[5][6], Color inputColor){
            if(color[0][0] == White){
            	x = 0;
            	y = 0;
            	return;
			}
			else if(color[4][0] == White){
				x = 4;
            	y = 0;
            	return;
			}
			else if(color[0][5] == White){
            	x = 0;
            	y = 5;
            	return;
			}
			else if(color[4][5] == White){
				x = 4;
            	y = 5;
            	return;
			}
			else if(color[2][0] == White){
            	x = 2;
            	y = 0;
            	return;
			}
			else if(color[2][5] == White){
				x = 2;
            	y = 5;
            	return;
			}
			else if(color[0][2] == White){
            	x = 0;
            	y = 2;
            	return;
			}
			else if(color[4][3] == White){
				x = 4;
            	y = 3;
            	return;
			}
			else {
				for (int i=0 ; i<5 ; i++){
					for (int j=0 ; j<6 ; j++){
						int sub = Max[i][j] - Record[i][j];
						if(sub == 1 && color[i][j] == inputColor){
							x = i;
							y = j;
							return;
						}
						else if(sub == 1){
							if(i<4 && color[i+1][j] == inputColor){
								x = i+1;
								y = j;
								return;
							}
							else if(i>0 && color[i-1][j] == inputColor){
								x = i-1;
								y = j;
								return;
							}
							else if(j>0 && color[i][j-1] == inputColor){
								x = i;
								y = j-1;
								return;
							}
							else if(j<5 && color[i][j+1] == inputColor){
								x = i;
								y = j+1;
								return;
							}
						}
						else if(color[i][j] == White){
							x = i;
							y = j;
							return;
						}
					}
				}
				for (int i=0 ; i<5 ; i++){
					for (int j=0 ; j<6 ; j++){
						if(color[i][j] == inputColor){
							x = i;
							y = j;
							return;
						}
					}
				}
			}
        }
        // Any Code You Want to Add
        int getX(){
            return x;
        }
        int getY(){
            return y;
        }
    private:
        int x;
        int y;
};
