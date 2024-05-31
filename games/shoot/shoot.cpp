#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>
#include <unistd.h>
using namespace std ;
int n, m ;
int playerx, playery ;
vector <bool> pressed(1003, 0) ;
vector <string> field, now, f2 ;
vector <pair<int,int>> enemy ;
vector <tuple<int,int,int>> bullet ;
int wave=1, health=1000, tme=0, bulletnumber=10, score=0, maxhealth=1000 ;
int colorreset=0 ;
bool damagecooldown=0 ;
int mode=1 ;
string modes[]={"","Super Easy", "Easy", "Normal", "Hard", "Impossible"} ;
void cs(){
  COORD pos={0,0} ;
  SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), pos );
  for (char i = 'A' ; i <= 'Z' ; i ++){
  	pressed[i]=GetAsyncKeyState(i) ;
	}
}
vector <string> buildfield(int type){
	if (type == 1){
		return {
			"#################################",
			"#                               #",
			"#                               #",
			"#                               #",
			"#                               #",
			"#                               #",
			"#                               #",
			"#                               #",
			"#                               #",
			"#                               #",
			"#                               #",
			"#                               #",
			"#                               #",
			"#                               #",
			"#                               #",
			"#                               #",
			"#                               #",
			"#                               #",
			"#                               #",
			"#                               #",
			"#################################",
		} ;
	}
	return {{}} ;
}
void generatemap(int type){
	if (type == 1){
		now=field ;
		now[playerx][playery]='X' ;
		for (int i=0 ; i < enemy.size() ; i ++){
			now[enemy[i].first][enemy[i].second]='O' ;
		}
		for (int i=0 ; i < bullet.size() ; i ++){
			if (get<2>(bullet[i]) == 1 || get<2>(bullet[i]) == 3) now[get<0>(bullet[i])][get<1>(bullet[i])]='|' ;
			else now[get<0>(bullet[i])][get<1>(bullet[i])]='-' ;
		}
	}
	else {
		f2=field ;
		f2[playerx][playery]='X' ;
		for (int i=0 ; i < enemy.size() ; i ++){
			f2[enemy[i].first][enemy[i].second]='O' ;
		}
	}
}
void checkdamage(){
	if (damagecooldown) return ;
	for (int i=0 ; i < enemy.size() ; i ++){
		int x=enemy[i].first, y=enemy[i].second ;
		if (enemy[i] == pair<int,int>{playerx,playery} && !damagecooldown) health -= 100, system("Color 0C"), damagecooldown=1, colorreset=tme+10 ;
	}
}
void checkedamage(){
	for (int i=0 ; i < enemy.size() ; i ++){
		int x=enemy[i].first, y=enemy[i].second ;
		bool die=0 ;
		for (int j=0 ; j < bullet.size() ; j ++){
			if (x==get<0>(bullet[j]) && y==get<1>(bullet[j])){
				die=1 ;
				break ;
			}
		}
		if (die){
			enemy.erase(enemy.begin()+i) ;
			i -- ;
			score ++ ;
		}
	}
}
void enemymove(){
	for (int i=0 ; i < enemy.size() ; i ++){
		int x=enemy[i].first, y=enemy[i].second ;
		vector <pair<int,int>> okpos ;
		if (x < playerx && y < playery) okpos.push_back({x+1,y+1}) ;
		if (x < playerx && y > playery) okpos.push_back({x+1,y-1}) ;
		if (x > playerx && y < playery) okpos.push_back({x-1,y+1}) ;
		if (x > playerx && y > playery) okpos.push_back({x-1,y-1}) ;
		if (x < playerx) okpos.push_back({x+1,y}) ;
		else if (x > playerx) okpos.push_back({x-1,y}) ;
		if (y < playery) okpos.push_back({x,y+1}) ;
		else if (y > playery) okpos.push_back({x,y-1}) ;
		bool ok=0 ;
		for (int j=0 ; j < okpos.size() ; j ++){
			if (f2[okpos[j].first][okpos[j].second] == ' ' || f2[okpos[j].first][okpos[j].second] == 'X'){
				f2[x][y]=' ' ;
				f2[okpos[j].first][okpos[j].second]='O' ;
				enemy[i]=okpos[j] ;
				ok=1 ;
				break ;
			}
		}
		if (enemy[i] == pair<int,int>{playerx,playery} && !damagecooldown) health -= 100, system("Color 0C"), damagecooldown=1, colorreset=tme+10 ;
	}
}
void generateenemy(){
	int x, y ;
	int t=0 ;
	while (1){
		x=rand()%(n-2)+1 ;
		y=rand()%(m-2)+1 ;
		if (f2[x][y]==' ' && abs(x-playerx)+abs(y-playery) > 10) break ;
		t ++ ;
		if (t > 100) return ;
	}
	f2[x][y]='O' ;
	enemy.push_back({x,y}) ;
}
void bulletmove(){
	for (int i = 0 ; i < bullet.size() ; i ++){
		int a=get<0>(bullet[i]), b=get<1>(bullet[i]), c=get<2>(bullet[i]) ;
		if (c == 1) a -- ;
		else if (c == 2) b ++ ;
		else if (c == 3) a ++ ;
		else b -- ;
		if (a <= 0 || a >= n || b <= 0 || b >= m){
			bullet.erase(bullet.begin()+i) ;
			i -- ;
			continue ;
		}
		bullet[i]=tuple<int,int,int>{a,b,c} ;
	}
}
void printrubbish(){
	cout << "                                   " ;
}
void printrubbishall(){
	for (int i = 0 ; i < 100 ; i ++) cout << "                                                              \n" ;
}
void die(){
	printrubbishall() ;
	cs() ;
	system("Color 0C") ;
	cout << "GAME OVER\n" ;
	cout << "Score            : " << score << endl ;
	cout << "Wave(s) survived : " << wave/2-1 << endl ;
	cout << "Mode : " ; cout << modes[mode] ; cout << endl ;
	
	sleep(1000), exit(0) ;
}
void win(){
	printrubbishall() ;
	cs() ;
	system("Color 0E") ;
	cout << "YOU HAVE WON THE GAME!!\n" ;
	cout << "Score            : " << score << endl ;
	cout << "Wave(s) survived : " << wave/2-1 << endl ;
	cout << "CONGRATS\n" ;
	cout << "(Mode : " ; cout << modes[mode] << ")" ; cout << endl ;
	sleep(1000), exit(0) ;
}
void printmap(){
	if (tme > colorreset) system("Color 0F"), colorreset=1e9, damagecooldown=0 ;
	if (health <= 0) die() ;
	for (int i=0 ; i < n ; i ++){
		cout << now[i] ; printrubbish() ;
		cout << endl ;
	}
	cout << "Health : " ; for (int i = 0 ; i < health/20 ; i ++) cout << char(219) ;for (int i = health/20 ; i < maxhealth/20 ; i ++) cout << char(176) ; printrubbish() ; cout << endl ; 
	cout << "Bullet : " ; for (int i = 0 ; i < bulletnumber ; i ++) cout << char(219) ; printrubbish() ; cout << endl ;
	cout << "Wave   : " ; for (int i = 0 ; i < wave ; i ++) cout << char(219) ; for (int i = wave ; i < 100 ; i ++) cout << char(176) ; printrubbish() ; cout << endl ;
	cout << "Score  : " ; cout << score ; printrubbish() ; cout << endl ;
	cout << "Mode   : " ; cout << modes[mode] ; printrubbish() ; cout << endl ;
	printrubbish() ; cout << endl ;
	cout << "Press R to pause" ; printrubbish() ; cout << endl ;
//	cout << health/20 << endl ;
}
void makebullet(int x, int y, int d){
	bullet.push_back(tuple<int,int,int>{x,y,d}) ;
}
void playermove(){
	if (pressed['W']) playerx -- ;
	if (pressed['S']) playerx ++ ;
	if (pressed['A']) playery -- ;
	if (pressed['D']) playery ++ ;
	if (playerx==0) playerx++ ;
	if (playery==0) playery++ ;
	if (playerx==n-1) playerx-- ;
	if (playery==m-1) playery-- ;
	if (bulletnumber>=1 && pressed['I']) makebullet(playerx,playery,1), bulletnumber-- ;
	if (bulletnumber>=1 && pressed['K']) makebullet(playerx,playery,3), bulletnumber-- ;
	if (bulletnumber>=1 && pressed['J']) makebullet(playerx,playery,4), bulletnumber-- ;
	if (bulletnumber>=1 && pressed['L']) makebullet(playerx,playery,2), bulletnumber-- ;
}
void menu(){
	cs() ;
	cout << "--------\n" ;
	cout << "Shoot the enemies and survive 100 waves to win!(although it seems impossible...)\n" ;
	cout << "Also don't let bullet runs out, or you will die easily!\n" ;
	cout << "--------\n" ;
	cout << "Controls :\n" ;
	cout << "WASD key to move\n" ;
	cout << "IJKL key to shoot bullets\n" ;
	cout << "--------\n" ;
	cout << "Choose the mode by pressing J and L, and start by pressing A\n" ;
	cout << "< " << modes[mode] << " >      \n" ;
}
void pause(){
	cs() ;
	printrubbishall() ;
	while (1){
		cs() ;
		cout << "--- Press T to resume ---\n" ;
		usleep(10000) ;
		if (pressed['T']) return ;
	}
}
void selectmode(){
	sleep(1) ;
	mode=3 ;
	int t=0 ;
	while (t < 500){
		t ++ ;
	}
	while (1){
		menu() ;
		if (pressed['A']) return ;
		if (pressed['J']) mode --,usleep(300000) ;
		if (pressed['L']) mode ++,usleep(300000) ;
		if (mode == 0) mode ++ ;
		if (mode == 6) mode -- ;
	}
}

int main(){
	ios::sync_with_stdio(), cin.tie(), cout.tie() ;
	srand((unsigned)time(0));
	selectmode() ;
//	getch() ;
	health=maxhealth ;
	field=buildfield(1) ;
	cs() ;
	printrubbish() ;printrubbish() ;printrubbish() ;printrubbish() ;printrubbish() ;printrubbish() ;
	for (int i = 0 ; i < field.size() ; i ++) for (int j = 0 ; j < field[i].size() ; j ++) if (field[i][j]=='#') field[i][j]=219 ;
	n=field.size() ;
	m=field[0].size() ;
	playerx=n/2, playery=m/2 ;
	while (1){
		usleep(10000) ;
		if (pressed['R']) pause() ;
		if (tme%100 == 0){
			generatemap(2) ;
			if (mode == 1) for (int i = 0 ; i < max(1.0, wave*0.1) ; i ++) generateenemy() ;
			if (mode == 2) for (int i = 0 ; i < wave ; i ++) generateenemy() ;
			if (mode == 3) for (int i = 0 ; i < wave*2 ; i ++) generateenemy() ;
			if (mode == 4) for (int i = 0 ; i < wave*4 ; i ++) generateenemy() ;
			if (mode == 5) for (int i = 0 ; i < wave*8 ; i ++) generateenemy() ;
			wave ++ ;
		}
		cs() ;
		bulletmove() ;
		if (tme%2==0) playermove() ;
		if (tme%10 == 0){
			generatemap(2) ;
			enemymove() ;
			bulletnumber ++ ;
		}
//		cout << "ok\n" ;
		generatemap(1) ;
		checkdamage() ;
		checkedamage() ;
		printmap() ;
		tme ++ ;
		if (tme > 10000) tme -= 10000 ;
		if (wave > 100) win() ;
	}
	return 0 ;
}
