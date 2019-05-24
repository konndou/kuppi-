
#define BOSS_SIZE_X 256
#define BOSS_SIZE_Y 256

#define BOSS_MAX 1



void BossSystemInit(void);
void BossInit(void);
void BossUpdate(void);
void BossDraw(void);

bool BossHitCheck(XY sPos, XY sSize);
