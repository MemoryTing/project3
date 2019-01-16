class Student{
    public:
        void makeMove(int Record[5][6], int Max[5][6], Color color[5][6], Color inputColor){
			//get the corners
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
			else if(color[0][0] == inputColor){
            	x = 0;
            	y = 0;
            	return;
			}
			else if(color[4][0] == inputColor){
				x = 4;
            	y = 0;
            	return;
			}
			else if(color[0][5] == inputColor){
            	x = 0;
            	y = 5;
            	return;
			}
			else if(color[4][5] == inputColor){
				x = 4;
            	y = 5;
            	return;
			}
			else {
			//check every point still need how many steps to explode 
				int sub[5][6];
				for (int i=0 ; i<5 ; i++){
					for (int j=0 ; j<6 ; j++){
						sub[i][j] = Max[i][j] - Record[i][j];
					}
				}
			//
				int next_steps[5][6] , next_next_steps[5][6];
				int the_biggest=0 , count=0;
				for (int i=0 ; i<5 ; i++){
					for (int j=0 ; j<6 ; j++){
						if(color[i][j] == inputColor || color[i][j] == White){
							next_steps[i][j] = stil_have_how_many_steps_(0, i , j , sub , color , inputColor);
							if(next_steps[i][j] > the_biggest) {
								x = i;
								y = j;
								the_biggest = next_steps[i][j];
								count = 1;
							}
							else if(the_biggest == next_steps[i][j]) count++;
						}
						else next_steps[i][j] = 100;
					}
				}
				vector<int> pos_x;
				vector<int> pos_y;
				pos_x.clear();
				pos_y.clear();
				if(count > 1){
					for (int i=x ; i<5 ; i++){
						if(count == 0) break;
						for (int j=y ; i<6 ; i++){
							if(count == 0) break;
							if(next_steps[i][j] == the_biggest){
								if(i == 0 || i == 5 || j == 0 || j == 5){
									x = i;
									y = j;
									return;
								}
								pos_x.push_back(i);
								pos_y.push_back(j);
								count--;
							}
						}
					}
					x = pos_x[0];
					y = pos_y[0];
					return;
				}
				else if(count == 1) return;
			}
        }
        // Any Code You Want to Add
		Color colorrr(Color mine){
        	if(mine == Blue) return Red;
        	else return Blue;
		}
		void go_through(int i , int j , int sub[5][6] , Color color[5][6] , Color inputColor){
			sub[i][j]--;
			color[i][j] = inputColor;
			if(sub[i][j] == 0){
				color[i][j] = Black;
				if(i > 0){
					color[i-1][j] = inputColor;
					if(sub[i-1][j] == 1) go_through(i-1 , j , sub , color , inputColor);
					else if(color[i-1][j] > 0) sub[i-1][j]--;
					else color[i-1][j] = Black;
				}
				if(i < 5){
					color[i+1][j] = inputColor;
					if(sub[i+1][j] == 1) go_through(i+1 , j , sub , color , inputColor);
					else if(color[i+1][j] > 0) sub[i+1][j]--;
					else color[i+1][j] = Black;
				}
				if(j > 0){
					color[i][j-1] = inputColor;
					if(sub[i][j-1] == 1) go_through(i , j-1 , sub , color , inputColor);
					else if(color[i][j-1] > 0) sub[i][j-1]--;
					else color[i][j-1] = Black;
				}
				if(j < 6){
					color[i][j+1] = inputColor;
					if(sub[i][j+1] == 1) go_through(i , j+1 , sub , color , inputColor);
					else if(color[i][j+1] > 0) sub[i][j+1]--;
					else color[i][j+1] = Black;
				}
			}
			return;
		}
		int stil_have_how_many_steps_(int round , int i , int j , int sub[5][6] , Color color[5][6] , Color inputColor){
			int now_sub[5][6];
			Color now_color[5][6];
			for (int a=0 ; a<5 ; a++){
				for (int b=0 ; b<6 ; b++){
					now_sub[a][b] = sub[a][b];
					now_color[a][b] = color[a][b];
				}
			}
			go_through(i , j , now_sub , now_color , inputColor); //if choose [i][j] the map would be...
			int oppo_steps=0 , my_steps=0;
			for (int a=0 ; a<5 ; a++){
				for (int b=0 ; b<6 ; b++){
					if(color[a][b] == inputColor){
						my_steps += now_sub[a][b];
					}
					if(color[a][b] !=  White && color[a][b] != Black){
						oppo_steps += now_sub[a][b];
					}
				}
			}
			if(round == 0){
				int my_biggest = 0;
				int next_oppo_x , next_oppo_y;
				for (int a=0 ; a<5 ; a++){ //next next step
					for (int b=0 ; b<6 ; b++){
						if (now_color[5][6] == colorrr(inputColor)){
							int x = stil_have_how_many_steps_(1 , a , b , now_sub , now_color , colorrr(inputColor));
							if(x < my_biggest){
								my_biggest = x;
								next_oppo_x = a;
								next_oppo_y = b;
							}
						}
					}
				}
			}
			if(my_steps > oppo_steps) return my_steps - oppo_steps;
			else return oppo_steps - my_steps;
		}
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
