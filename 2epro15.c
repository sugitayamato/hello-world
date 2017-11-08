#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<string.h>  //実行時点で2つのファイルと一緒に実行する。

int a[10];
int b[10];
int c[10];
int d[10];
int i=0,h=0,t,death1=0,death2=0,death3=0,death4=0;
int recovery1,recovery2,n1=0,n2=0,run1,run2,value1=0,value2=0;

struct status{
	char name[20];
	int hp;
	int kougeki;
	int bougyo;
	int majic;
	int subayasa;};

int damage(struct status, struct status);
int mjc_dmg(struct status, struct status);
void new_line_breaker(char* str);
void uptake(char* fliename1, char* filename2);

int main(int argc, char **argv) {
	char name1[20],name2[20];
		int command1,command2,select1,select2,dead1=0,dead2=0,dead3=0,dead4=0; //dead=1の時死亡
	int j,k,c,r,count_damage1=0,count_damage2=0,count_damage3=0,count_damage4=0;
	int hp1_default,hp2_default,hp3_default,hp4_default;

	srand(time(NULL));
	uptake(argv[1], argv[2]);
	printf("プレイヤー1の名前を入力：");
	fgets(name1,sizeof(name1),stdin);
	new_line_breaker(name1);
	printf("プレイヤー2の名前を入力：");
	fgets(name2,sizeof(name2),stdin);
	new_line_breaker(name2);

	struct status player[2]={
		{"name1",b[0],b[1],b[2],b[3],b[4]},
		{"name2",b[5],b[6],b[7],b[8],b[9]}};
	struct status enemy[2]={
		{"dragon",d[0],d[1],d[2],d[3],d[4]},
		{"slime",d[5],d[6],d[7],d[8],d[9]}};

	for(h=0;h<2;h++){
		if(player[h].hp<=0||enemy[h].hp<=0){
			player[h].hp+=100;
			enemy[h].hp+=100;
		}
	}

	hp1_default=player[0].hp;
	hp2_default=player[1].hp;
	hp3_default=enemy[0].hp;
	hp4_default=enemy[1].hp;
	printf("---------------------------------------------------------------\n");
	printf("\n1.攻撃：回数制限無し\n2.魔法：回数制限あり(敵は回数制限無し)\n3.体力回復：回数制限有り(敵は回数制限無し)\n4.逃げる：成功は低確率(敵には実装していない)\nファイルバトラー形式\n\n");

	printf("---------------------------------------------------------------\n");
//戦闘
	for(;;){
		//printf("\x1b[2J");//画面クリア
		//体力表示
		for(h=0;h<2;h++){
			if(player[h].hp<0){
				player[h].hp=0;
			}
			if(enemy[h].hp<0){
				enemy[h].hp=0;
			}
		}

		printf("------------------------------------------------------------\n");
		printf("++++++++++味方プレーヤー++++++++++\n");
		printf("%s : HP %d/%d\n\n",name1,player[0].hp,hp1_default);
		printf("%s : HP %d/%d\n\n",name2,player[1].hp,hp2_default);
		printf("++++++++++敵プレーヤー++++++++++\n");
		printf("dragon : HP %d/%d\n\n",enemy[0].hp,hp3_default);
		printf("slime : HP %d/%d\n",enemy[1].hp,hp4_default);
		printf("------------------------------------------------------------\n");

		//name1のコマンド
		for(;;){
			//初期化
			//int command1=0,select1=0;
			//ここまで
			if(dead3==1){break;}
			printf("%sは何をする？\n\n",name1);
			printf("1:攻撃    2:魔法\n3:体力回復    4:逃げる\n\n→");
			scanf("%d",&command1);
			if(command1>4||command1<1){
				printf("\n規定外の入力です。\n");}
			else{
				if(command1==1||command1==2){
					if(enemy[0].hp<=0&&enemy[1].hp>0){
						select1=2;
						break;
					}
					else if(enemy[1].hp<=0&&enemy[0].hp>0){
						select1=1;
						break;
					}
					else{
						printf("\nどちらを攻撃する？\ndragon→1\nslime→2\n\n→");
						scanf("%d",&select1);
						if(select1==1||select1==2){break;}
						else{
							printf("\n規定外の入力です。\n");
						}
					}
				}
				else{break;}
			}
		}
		//name2のコマンド
		for(;;){
			//初期化
			//ここまで
			if(dead4==1){break;}
			printf("%sは何をする？\n",name2);
			printf("1:攻撃    2:魔法\n3:体力回復    4:逃げる\n\n→");
			scanf("%d",&command2);
			if(command2>4||command2<1){
				printf("\n規定外の入力です。\n");}
			else{
				if(command2==1||command2==2){
					if(enemy[0].hp<=0&&enemy[1].hp>0){
						select2=2;
						break;
					}
					else if(enemy[1].hp<=0&&enemy[0].hp>0){
						select2=1;
						break;
					}
					else{
						printf("\nどちらを攻撃する？\ndragon→1\nslime→2\n\n→");
						scanf("%d",&select2);
						if(select2==1||select2==2){break;}
						else{
							printf("\n規定外の入力です。\n");
						}
					}
				}
				else{break;}
			}
		}
		printf("\n-----------------------------------------\n");

		//バトル
		//name1の戦い
		if(command1==1){ //攻撃
			if(select1==1){
				count_damage1=damage(player[0],enemy[0]);
			}else{}
			if(select1==2){
				count_damage2=damage(player[0],enemy[1]);
			}else{}
		}
		if(command1==2){ //魔法
			if(select1==1&&value1<3){
				count_damage1=mjc_dmg(player[0],enemy[0]);
				value1++;
				printf("\n魔法攻撃成功！\n");
				printf("\n残り%d回、魔法攻撃が使えます\n",3-value1);
			}
			if(select1==2&&value1<3){
				count_damage2=mjc_dmg(player[0],enemy[1]);
				value1++;
				printf("\n魔法攻撃成功！\n");
				printf("\n残り%d回、魔法攻撃が使えます\n",3-value1);
			}
			else if(value1>=3){
				printf("\n魔力が足りないので攻撃できません\n");
			}
		}
		if(command1==3){
			recovery1=rand()%10;
			if(recovery1>6&&n1<2){
				player[0].hp+=10;
				n1++;
			}
			else{
				printf("\n回復に失敗\n");
			}
			printf("\n残り%d回、回復できる\n",2-n1);
		}
		if(command1==4){
			if(player[0].subayasa>=(enemy[0].subayasa+enemy[1].subayasa)/2){
				printf("\n逃走に成功！\n");
				run1=1;
				dead3=1;
				death3++;
			}
			else{
				printf("\n逃走に失敗...\n");
			}
		}

		//name2の戦い
		if(command2==1){ //攻撃
			if(select2==1){
				count_damage1=damage(player[1],enemy[0]);
			}else{}
			if(select2==2){
				count_damage2=damage(player[1],enemy[1]);
			}else{}
		}
		if(command2==2){ //魔法
			if(select2==1&&value2<3){
				count_damage1=mjc_dmg(player[1],enemy[0]);
				value2++;
				printf("\n魔法攻撃成功！\n");
				printf("\n残り%d回、魔法攻撃が使えます\n",3-value2);
			}
			if(select2==2&&value2<3){
				count_damage2=mjc_dmg(player[1],enemy[1]);
				value2++;
				printf("\n魔法攻撃成功！\n");
				printf("\n残り%d回、魔法攻撃が使えます\n",3-value2);
			}
			else if(value2>=3){
				printf("\n魔力が足りないので攻撃できません\n");
			}
		}
		if(command2==3){
			recovery2=rand()%10;
			if(recovery2>6&&n2<2){
				player[1].hp+=10;
				n2++;
			}
			else{
				printf("\n回復に失敗\n");
			}
			printf("\n残り%d回、回復できる\n",2-n1);
		}
		if(command2==4){
			if(player[1].subayasa>=(enemy[0].subayasa+enemy[1].subayasa)/2){
				printf("\n逃走に成功！\n");
				run2=1;
				dead4=1;
				death4++;
			}
			else{
				printf("\n逃走に失敗...\n");
			}
		}

//---------------------体力計算
		enemy[0].hp-=count_damage1;
		enemy[1].hp-=count_damage2;
		if(enemy[0].hp<=0&&death1==0){
			printf("\ndragonは%dのダメージ！\n",count_damage1);
			printf("dragonを倒した！\n");
			dead1=1;
			death1++;
		}
		if(enemy[1].hp<=0&&death2==0){
			printf("\nslimeは%dのダメージ！\n",count_damage2);
			printf("slimeを倒した！\n");
			dead2=1;
			death2++;
		}
//--------------------敵の状態を出力
		if(dead1!=1){
			printf("\ndragonに%dダメージ！\n",count_damage1);
		}
		if(dead2!=1){
			printf("\nslimeに%dダメージ！\n",count_damage2);
		}
//--------------------敵の攻撃
		if(dead1==1&&dead2!=1){
			h=1;
			i=2;
		}
		else if(dead2==1&&dead1!=1){
			h=0;
			i=1;
		}
		else if(dead1!=1&&dead2!=1){
			h=0;
			i=2;
		}
		else{
			h=0;
			i=0;
		}
		for(c=h;c<i;c++){
			r=rand()%50;
			j=rand()%2;
			k=rand()%2;
			if(r<11){
				count_damage3=damage(enemy[c],player[j]);
				printf("\n%sの攻撃！\n",enemy[c].name);
			}
			else if(10<r&&r<22){
				count_damage4=damage(enemy[c],player[k]);
				printf("\n%sの攻撃！\n",enemy[c].name);
			}
			else if(21<r&&r<33){
				count_damage3=mjc_dmg(enemy[c],player[j]);
				printf("\n%sの魔法攻撃！\n",enemy[c].name);
			}
			else if(32<r&&r<44){
				count_damage4=damage(enemy[c],player[k]);
				printf("\n%sの魔法攻撃！\n",enemy[c].name);
			}
			else{
				enemy[c].hp+=15;
				printf("\n%sは回復に成功(+15)\n",enemy[c].name);
			}
		}
//------------敵の攻撃を表示
//------------体力計算
		player[0].hp-=count_damage3;
		player[1].hp-=count_damage4;
		if(player[0].hp<=0&&death3==0){
			printf("\n%sは%dのダメージ！\n",name1,count_damage3);
			printf("%sは倒された...\n",name1);
			dead3=1;
			death3++;
		}
		if(player[1].hp<=0&&death4==0){
			printf("\n%sは%dのダメージ！\n",name2,count_damage4);
			printf("%sは倒された...\n",name2);
			dead4=1;
			death4++;
		}
//-------------------
		if(dead3!=1){
			printf("\n%sは%dのダメージ...\n",name1,count_damage3);
		}
		if(dead4!=1){
			printf("\n%sは%dのダメージ...\n",name2,count_damage4);
		}
		//---------------
		//敵、味方の体力表示
		//---------------
		if(enemy[0].hp<=0&&enemy[1].hp<=0){
			printf("\n\ndragonとslimeを両方倒した！\n");
			break;
		}
		else if(player[0].hp<=0&&player[1].hp<=0){
			printf("\n\n%sと%sは倒された...\n",name1,name2);
			break;
		}
		else if(run1==1&&run2==1){
			printf("\n\n逃走成功で戦闘終了しました\n");
			break;
		}
		else{
		}
		//printf("\x1b[2J");
//メモ：魔法を使いたい（回数制限あり）//a=kougeki,b=bougyo
	}
	return 0;
}
//関数作成---------------------
int damage(struct status a, struct status b){
	int attack_point,sign,midway_point;
	srand(time(NULL));
	midway_point=rand()%(a.kougeki/5-b.bougyo/8);
	sign=rand()%10;
	if(sign<5){
		attack_point=a.kougeki/6+midway_point;
	}
	else{
		attack_point=a.kougeki/4-midway_point;
	}
	return attack_point;
}

int mjc_dmg(struct status a, struct status b){
	int attack_point,midway_point,sign;
	srand(time(NULL));
	midway_point=rand()%(a.majic/2-b.bougyo/10);
	sign=rand()%10;
	if(sign>4){
		attack_point=midway_point*2+a.majic/2;
	}
	if(sign<=4){
		attack_point=0;
	}
	return attack_point;
}

void uptake(char* filename1, char* filename2){
	FILE *f1;
	FILE *f2;
	f1=fopen(filename1,"r");
	f2=fopen(filename2,"r");
	if(f1==NULL||f2==NULL){
		printf("ファイルが開けない\n");
		exit(-1);
	}
	for(i=0;i<10;i++){
		for(h=0;h<10;h++){
			a[h]=fgetc(f1);
			c[h]=fgetc(f2);
			if(h==9){
				for(t=0;t<9;t++){
					b[i]=a[t]+a[t+1];
					d[i]=c[t]+a[t+1];
				}
			}
		}
	}
	fclose(f1);
	fclose(f2);
}

//改行コード削除 
void new_line_breaker(char* str){
	int q;
	q=0;
	for(;;){
		if(str[q]=='\n'){
			str[q]='\0';
			break;
		}
		q++;
	}
}
