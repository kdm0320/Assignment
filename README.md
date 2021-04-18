# Assignment

### 몬스터와의 전투에서 승리하여 마지막에 보스전까지 승리하면 되는 게임입니다.

### 턴제이며 등장하는 몬스터의 순서, 스킬발현, 회복까지 모두 무작위로 진행됩니다.

### 설정할수있는 플레이어및 몬스터들의 최대체력은 200이며 현재는 플레이어는 180으로 설정되어있습니다.

### 난이도는 전투횟수와 스킬들의 데미지, 체력, 힐량 으로 조정가능합니다

### 전투횟수는 설정한 수 + 1 만큼 실행됩니다.

### 사운드가 있으니 소리에 주의해주세요.

# 전투횟수 조정 = countFight 변수 숫자 조정
# 플레이어 체력 조정 = 마우스 콜백함수 object==nextButton[2]에서 createPlayerHp 인수 조정
#                      - changePlayerHP에서 ps->hp 조정

# 몬스터 체력 조정 = createMonsters에서 setMonsterHp 인수 조정
# 보스 체력 조정 = setBoss에서 setMonsterHp 인수 조정
# 스킬데미지 조정 = magicionSkill1, monsterSkill, bossSkill에서 데미지 조정
# 힐 = Heal 함수에서 ps->hp 조정
