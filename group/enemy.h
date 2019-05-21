
#define ENEMY1_SIZE_X 32
#define ENEMY1_SIZE_Y 32
#define ENEMY_MAX 30

enum ENEMY_TYPE
{
	ENEMY_TYPE_BOAR,
	ENEMY_TYPE_CROW
};

void EnemySystemInit(void);
void EnemyInit(int i);
void EnemyUpdate(int i);
void EnemyDraw(int i);

<<<<<<< HEAD
enum ENEMY_TYPE
{
	ENEMY_TYPE_BOAR,
	ENEMY_TYPE_CROW
};


=======
bool EnemyHitCheck(XY sPos, XY sSize);
>>>>>>> 089080dbbb8f5c2118173d5d57ae01c516ede1df

CHARACTER GetEnemyPos(int i);
