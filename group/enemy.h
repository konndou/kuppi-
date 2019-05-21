
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

bool EnemyHitCheck(XY sPos, XY sSize);

CHARACTER GetEnemyPos(int i);
