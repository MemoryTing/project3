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
			//if can make opponent explode?!!!
				vector<int> temp1;
				temp1.clear();
				for (int i=0 ; i<5 ; i++){
					for (int j=0 ; j<6 ; j++){
						if(sub[i][j] == 1 && is_oppon(color[i][j] , inputColor)){
							if(find(i , j , 1 , color, inputColor , sub)) return;
						}
						else if(sub[i][j] == 1){
							temp1.push_back(i);
							temp1.push_back(j);
						}
					}
				}
			//if my ball is going to explode?
				if(!temp1.empty()){
					x = temp1[0];
					y = temp1[1];
					return;
				}
			//if there any possible to make opponent's ball explode in steps?
				for (int i=0 ; i<5 ; i++){
					for (int j=0 ; j<6 ; j++){
						if(sub[i][j] != 0){
							if(color[i][j] == inputColor || color[i][j] == White){
								if(find(i , j , sub[i][j] , color, mmm(inputColor) , sub)){
									x = i;
									y = j;
									return;
								}
							}
							else if(color[i][j] != Black){
								if(find(i , j , sub[i][j] , color, inputColor , sub)){
									return;
								}
							}
						}
					}
				}
			//just find an available place
				int abc[4];
				abc[0] = 6;
				abc[1] = 6;
				abc[2] = 6;
				abc[3] = 6;
				for (int i=4 ; i>-1 ; i--){
					for (int j=5 ; j>-1 ; j--){
						if(color[i][j] == White || color[i][j] == inputColor){
							if(sub[i][j] == 4){
								x = i;
								y = j;
								return;
							}
							else if(sub[i][j] == 3){
								abc[0] = i;
								abc[1] = j;
							}
							else {
								abc[2] = i;
								abc[3] = j;
							}
						}
					}
				}
				if(abc[0] != 6){
					x = abc[0];
					y = abc[1];
					return;
				}
				else {
					x = abc[2];
					y = abc[3];
					return;
				}
			}
        }
        // Any Code You Want to Add
        bool is_good(){
        	if()
		}
		Color mmm(Color mine){
        	if(mine == Blue) return Red;
        	else return Blue;
		}
        bool is_oppon(Color need_check , Color inputColor){
        	if(need_check != inputColor && need_check != White && need_check != Black) return true;
        	else return false;
		}
		bool find(int i , int j , int now_check , Color color[5][6], Color inputColor , int sub[5][6]){
			if(i > 0){
				if(sub[i-1][j] == now_check && color[i-1][j] == inputColor){
					x = i-1;
					y = j;
					return true;
				}
			}
			if(i < 4){
				if(sub[i+1][j] == now_check && color[i+1][j] == inputColor){
					x = i+1;
					y = j;
					return true;
				}
			}
			if(j > 0){
				if(sub[i][j-1] == now_check && color[i][j-1] == inputColor){
					x = i;
					y = j-1;
					return true;
				}
			}
			if(j < 5){
				if(sub[i][j+1] == now_check && color[i][j+1] == inputColor){
					x = i;
					y = j+1;
					return true;
				}
			}
			return false;
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
