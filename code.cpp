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
			else {
			//check every point still need how many steps to explode 
				int sub[5][6];
				for (int i=0 ; i<5 ; i++){
					for (int j=0 ; j<6 ; j++){
						sub[i][j] = Max[i][j] - Record[i][j];
					}
				}
				int next_step[5][6];
				int biggest=0 , next_x , next_y;
				for (int i=0 ; i<5 ; i++){
					for (int j=0 ; j<6 ; j++){
						if(color[i][j] == White || color[i][j] == inputColor){
							int now_sub[5][6];
							Color now_color[5][6];
							for (int a=0 ; a<5 ; a++){
								for (int b=0 ; b<6 ; b++){
									now_sub[a][b] = sub[a][b];
									now_color[a][b] = color[a][b];
								}
							}
							int p , q;
							go_through(i , j , now_sub , now_color , inputColor);//next
							step(now_sub , now_color , colorrr(inputColor));
							go_through(x , y , now_sub , now_color , colorrr(inputColor));//oppo_next
							step(now_sub , now_color , inputColor);
							go_through(x , y , now_sub , now_color , inputColor);//next_next
							step(now_sub , now_color , colorrr(inputColor));
							go_through(x , y , now_sub , now_color , colorrr(inputColor));//oppo_next_next
							int my_step = 0;
							for (int a=0 ; a<5 ; a++){
								for (int b=0 ; b<6 ; b++){
									if(now_color[a][b] == inputColor || now_color[a][b] == White){
										my_step += now_sub[a][b];
									}
								}
							}
							next_step[i][j] = my_step;
							if(my_step > biggest){
								biggest = my_step;
								next_x = i;
								next_y = j;
							}
						}
					}
				}
				x = next_x;
				y = next_y;
				return;
        	}
    	}
        // Any Code You Want to Add
        void step(int sub[5][6] , Color color[5][6] , Color inputColor){
        	int next_steps[5][6] , next_next_step[5][6];
			int the_biggest=0 , count=0;
			for (int i=0 ; i<5 ; i++){
				for (int j=0 ; j<6 ; j++){
					if(color[i][j] == inputColor || color[i][j] == White){
						next_steps[i][j] = stil_have_how_many_steps_(0, i , j , sub , color , inputColor);
						next_next_step[i][j] = stil_have_how_many_steps_(1, i , j , sub , color , inputColor);
						next_steps[i][j] = next_steps[i][j] - next_next_step[i][j];
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
			if(count > 1){
				for (int i=0 ; i<5 ; i++){
					if(count == 0) break;
					for (int j=0 ; i<6 ; i++){
						if(count == 0) break;
						if(next_steps[i][j] == the_biggest && check(i , j , color , inputColor , sub)){
							x = i;
							y = j;
							return;
						}
					}
				}
			}
			else if(count == 1) return;
			
			for(int i=4 ; i>-1 ; i--){
				for (int j=5 ; j>-1 ; j--){
					if(color[i][j] == inputColor){
						x = i;
						y = j;
						return;
					}
				}
			}
		}
        
		Color colorrr(Color mine){
        	if(mine == Blue) return Red;
        	else return Blue;
		}
		bool check(int i , int j , Color color[5][6] , Color inputColor , int sub[5][6]){
			if(i > 0){
				if(color[i-1][j] == colorrr(inputColor) && sub[i][j] > sub[i-1][j]) return false;
			}
			if(i < 4){
				if(color[i+1][j] == colorrr(inputColor) && sub[i][j] > sub[i+1][j]) return false;
			}
			if(j > 0){
				if(color[i][j-1] == colorrr(inputColor) && sub[i][j] > sub[i][j-1]) return false;
			}
			if(j < 5){
				if(color[i][j+1] == colorrr(inputColor) && sub[i][j] > sub[i][j+1]) return false;
			}
			return true;
		}
		void go_through(int i , int j , int sub[5][6] , Color color[5][6] , Color inputColor){
			sub[i][j]--;
			color[i][j] = inputColor;
			if(sub[i][j] == 0){
				color[i][j] = Black;
				if(i > 0){
					color[i-1][j] = inputColor;
					if(sub[i-1][j] == 1) go_through(i-1 , j , sub , color , inputColor);
					else if(sub[i-1][j] > 0) sub[i-1][j]--;
					else color[i-1][j] = Black;
				}
				if(i < 5){
					color[i+1][j] = inputColor;
					if(sub[i+1][j] == 1) go_through(i+1 , j , sub , color , inputColor);
					else if(sub[i+1][j] > 0) sub[i+1][j]--;
					else color[i+1][j] = Black;
				}
				if(j > 0){
					color[i][j-1] = inputColor;
					if(sub[i][j-1] == 1) go_through(i , j-1 , sub , color , inputColor);
					else if(sub[i][j-1] > 0) sub[i][j-1]--;
					else color[i][j-1] = Black;
				}
				if(j < 6){
					color[i][j+1] = inputColor;
					if(sub[i][j+1] == 1) go_through(i , j+1 , sub , color , inputColor);
					else if(sub[i][j+1] > 0) sub[i][j+1]--;
					else color[i][j+1] = Black;
				}
			}
			return;
		}
		int stil_have_how_many_steps_(int round , int i , int j , int sub[5][6] , Color color[5][6] , Color inputColor){
			if(round == 0){
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
				if(my_steps > oppo_steps) return my_steps - oppo_steps;
				else return oppo_steps - my_steps;
			}
			else {
				int now_sub[5][6];
				Color now_color[5][6];
				for (int a=0 ; a<5 ; a++){
					for (int b=0 ; b<6 ; b++){
						now_sub[a][b] = sub[a][b];
						now_color[a][b] = color[a][b];
					}
				}
				go_through(i , j , now_sub , now_color , inputColor);
				int biggest=0;
				for(int i=0 ; i<5 ; i++){
					for(int j=0 ; j<6 ; j++){
						int temp = stil_have_how_many_steps_(0 , i , j , now_sub , now_color , colorrr(inputColor));
						if(temp > biggest) biggest = temp;
					}
				}
				return biggest;
			}
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
