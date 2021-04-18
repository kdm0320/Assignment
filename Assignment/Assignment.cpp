#define _CRT_SECURE_NO_WARNINGS
#include <bangtal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

SceneID scene[12];
ObjectID button[3],nextButton[13],diceButton[2],goblin[2],magicianSkill[2],arrow,diceBox,click,
messageBox[5],damages[3],number[3],MONSTER_HP,PLAYER_HP,monsterSkills,HP[2],healObject[4],healing,
monsterName,warning;
TimerID firstTimer[10],secondTimer[10],thirdTimer[4],deleteName,warnSign[3],lastTimer,Show_Monster_Dice;
SoundID bgm[10],playerSkill[10],enemySkill[5],Boss_Skill[5];

int dices[7], Monster_Dice_Number[6],Heal_Dice[7],warnCount=2;
int countFight = 3; 
float  skillTimer = 1.0f; 
bool  IsonDice=true,IsonBoss=false, IsmessageOn=true;
char MonsterNumbers[50];

typedef struct _Status{ 
    int hp;
   
}playerStatus;

typedef struct __Status { 
    int hp;
    
}monsterStatus;
playerStatus* ps = (playerStatus*)malloc(sizeof(playerStatus));
monsterStatus* ms = (monsterStatus*)malloc(sizeof(playerStatus));



ObjectID createObject(const char* image, SceneID scene, int x, int y, bool shown) {
    ObjectID object = createObject(image);

    locateObject(object, scene, x, y);

    if (shown)
        showObject(object);


    return object;
}

void setTimer(TimerID*timers, int timerNumber, float time) {
    setTimer(timers[timerNumber], time);
    startTimer(timers[timerNumber]);
}

void createScene() { 
    scene[0] = createScene("start", "Images/scenes/start.png");
    scene[1] = createScene("second", "Images/scenes/choose.png");
    scene[2] = createScene("second", "Images/scenes/choose1.png");
    scene[3] = createScene("second", "Images/scenes/choose5.png");
    scene[4] = createScene("second", "Images/scenes/0.png");
    scene[5] = createScene("over", "Images/scenes/gameOver.png");
    char ending[50];
    for (int i = 6; i < 11; i++) {
        sprintf(ending, "Images/scenes/ending%d.png", i);
        scene[i] = createScene("end", ending);
 
    }


}
void createSound() {   
    bgm[0] = createSound("Images/sounds/start.mp3");
    bgm[1] = createSound("Images/sounds/death.mp3");
    bgm[2] = createSound("Images/sounds/healSound.mp3");
    bgm[3] = createSound("Images/sounds/warning.mp3");
    bgm[4] = createSound("Images/sounds/gameover.mp3");
    bgm[5] = createSound("Images/sounds/miss.mp3");
    bgm[6] = createSound("Images/sounds/bossDeath.mp3");
    bgm[7] = createSound("Images/sounds/cave.mp3");
    bgm[8] = createSound("Images/sounds/escape.mp3");
    bgm[9] = createSound("Images/sounds/dice.mp3");
    playerSkill[0] = createSound("Images/skills/magician/energyBolt0.mp3");
    playerSkill[1] = createSound("Images/skills/magician/energyBolt1.mp3");
    playerSkill[2] = createSound("Images/skills/magician/fireball0.mp3");
    playerSkill[3] = createSound("Images/skills/magician/fireball1.mp3");
    playerSkill[4] = createSound("Images/skills/magician/iceBall0.mp3");
    playerSkill[5] = createSound("Images/skills/magician/iceBall1.mp3");
    playerSkill[6] = createSound("Images/skills/magician/wind0.mp3");
    playerSkill[7] = createSound("Images/skills/magician/wind1.mp3");
    playerSkill[8] = createSound("Images/skills/magician/thunder1.mp3");
    playerSkill[9] = createSound("Images/skills/magician/sun1.mp3");
    char enemySkills[50];
    for (int i = 0; i <5 ; i++) {
        sprintf(enemySkills, "Images/skills/monsters/%d.mp3", i);
        enemySkill[i] = createSound(enemySkills);

    }
    char BossSkills[50];
    for (int i = 0; i < 5; i++) {
        sprintf(BossSkills, "Images/skills/monsters/boss/%d.mp3", i);
        Boss_Skill[i] = createSound(BossSkills);

    }



}
void createNextButton(int nextButtonNumber, int sceneNumber) {
    nextButton[nextButtonNumber] = createObject("Images/buttons/next.png", scene[sceneNumber], 1100, 50, true);

}


void magicionSkill0(int number) { 
    switch (number)
    {   case 0:
            return;
        case 1 :
            magicianSkill[0] = createObject("Images/skills/magician/energyBolt0.png", scene[4], 800, 100, true);
            playSound(playerSkill[0]);
            return;
        case 2 :
            magicianSkill[0] = createObject("Images/skills/magician/fireBall0.png", scene[4], 800, 100, true);
            playSound(playerSkill[2]);
            return;
        case 3 :
            magicianSkill[0] = createObject("Images/skills/magician/iceBall0.png", scene[4], 480, 250, true);
            playSound(playerSkill[4]);
            return;
        case 4 :
            magicianSkill[0] = createObject("Images/skills/magician/wind0.png", scene[4], 520, 200, true);
            playSound(playerSkill[6]);
            return;
        case 5 :
            magicianSkill[0] = createObject("Images/skills/magician/thunder0.png", scene[4], 330, 630, true);
            return;
        case 6 :
            magicianSkill[0] = createObject("Images/skills/magician/sun0.png", scene[4], 630, 400, true);
            return;
             
    }
    
}
void magicionSkill1(int number) { 
    switch (number)
    {
    case 0:
        return;
    case 1:
        magicianSkill[1] = createObject("Images/skills/magician/energyBolt1.png", scene[4], 510, 320, true);
        playSound(playerSkill[1]);
        damages[1] = createObject("Images/damages/10.png", scene[4], 822, 400, true);
        ms->hp = ms->hp - 10;
        return;
    case 2:
        magicianSkill[1] = createObject("Images/skills/magician/fireBall1.png", scene[4], 500, 280, true);
        playSound(playerSkill[3]);
        damages[1] = createObject("Images/damages/20.png", scene[4], 822, 400, true);
        ms->hp = ms->hp - 20;
        return;
    case 3:
        magicianSkill[1] = createObject("Images/skills/magician/iceBall1.png", scene[4], 400, 230, true);
        playSound(playerSkill[5]);
        damages[1] = createObject("Images/damages/30.png", scene[4], 822, 400, true);
        ms->hp = ms->hp - 30;
        return;
    case 4:
        magicianSkill[1] = createObject("Images/skills/magician/wind1.png", scene[4], 390, 200, true);
        playSound(playerSkill[7]);
        damages[1] = createObject("Images/damages/40.png", scene[4], 822, 400, true);
        ms->hp = ms->hp - 40;
        return;
    case 5:
        magicianSkill[1] = createObject("Images/skills/magician/thunder1.png", scene[4], 320, 0, true);
        playSound(playerSkill[8]);
        damages[1] = createObject("Images/damages/50.png", scene[4], 822, 400, true);
        ms->hp = ms->hp - 50;
        return;
    case 6:
        magicianSkill[1] = createObject("Images/skills/magician/sun1.png", scene[4], 190, 0, true);
        playSound(playerSkill[9]);
        damages[1] = createObject("Images/damages/60.png", scene[4], 822, 400, true);
        ms->hp = ms->hp - 60;
        return;

    }

}
void monsterSkill(int number) { 
    switch (number)
    {
    case 0:
        return;
    case 1:
        monsterSkills = createObject("Images/skills/monsters/0.png", scene[4], 520, 150, true);
        playSound(enemySkill[0]);
        damages[2] = createObject("Images/damages/5.png", scene[4], 750, 250, true);
        ps->hp = ps->hp - 5;
        return;
    case 2:
        monsterSkills = createObject("Images/skills/monsters/1.png", scene[4], 400, 80, true);
        playSound(enemySkill[1]);
        damages[2] = createObject("Images/damages/10.png", scene[4], 750, 250, true);
        ps->hp = ps->hp - 10;
        return;
    case 3:
        monsterSkills = createObject("Images/skills/monsters/2.png", scene[4], 400, 80, true);
        playSound(enemySkill[2]);
        damages[2] = createObject("Images/damages/15.png", scene[4], 750, 250, true);
        ps->hp = ps->hp - 15;
        return;
    case 4:
        monsterSkills = createObject("Images/skills/monsters/3.png", scene[4], 400, 80, true);
        playSound(enemySkill[3]);
        damages[2] = createObject("Images/damages/20.png", scene[4], 780, 270, true);
        ps->hp = ps->hp - 20;
        return;
    case 5:
        monsterSkills = createObject("Images/skills/monsters/4.png", scene[4], 300, 0, true);
        playSound(enemySkill[4]);
        damages[2] = createObject("Images/damages/25.png", scene[4], 870, 270, true);
        ps->hp = ps->hp - 25;
        return;

      }

}
void bossSkill(int number) { 
    switch (number)
    {
    case 0:
        return;
    case 1:
        monsterSkills = createObject("Images/skills/monsters/boss/0.png", scene[4], 400, 80, true);
        playSound(Boss_Skill[0]);
        damages[2] = createObject("Images/damages/20.png", scene[4], 780, 270, true);
        ps->hp = ps->hp - 20;
        return;
    case 2:
        monsterSkills = createObject("Images/skills/monsters/boss/1.png", scene[4], 300, 0, true);
        playSound(Boss_Skill[1]);
        damages[2] = createObject("Images/damages/25.png", scene[4], 870, 270, true);
        ps->hp = ps->hp - 25;
        return;
    case 3:
        monsterSkills = createObject("Images/skills/monsters/boss/2.png", scene[4], 450, 0, true);
        playSound(Boss_Skill[2]);
        damages[2] = createObject("Images/damages/30.png", scene[4], 870, 270, true);
        ps->hp = ps->hp - 30;
        return;
    case 4:
        monsterSkills = createObject("Images/skills/monsters/boss/3.png", scene[4], 500, 0, true);
        playSound(Boss_Skill[3]);
        damages[2] = createObject("Images/damages/35.png", scene[4], 870, 270, true);
        ps->hp = ps->hp - 35;
        return;
    case 5:
        monsterSkills = createObject("Images/skills/monsters/boss/4.png", scene[4], 350, 0, true);
        playSound(Boss_Skill[4]);
        damages[2] = createObject("Images/damages/40.png", scene[4], 950, 170, true);
        ps->hp = ps->hp - 40;
        return;

    }

}
void mixDice() { 
    int count = 100; 
    char numbers[50];
    for (int i = 0; i < 7; i++) {
        dices[i] = i;
    }
    for (int i = 0; i < count; i++) {
        int randNum1 = rand() % 7;
        int randNum2 = rand() % 7;
        int temp;
        temp = dices[randNum1];
        dices[randNum1] = dices[randNum2];
        dices[randNum2] = temp;
    }
   
    
    sprintf(numbers, "Images/dices/%d.png", dices[0]);
    
    number[1] = createObject(numbers, scene[4], 1050, 300, true);
        
}
void healDice() {
    int count = 60; 
    char numbers[50];
    for (int i = 0; i < 7; i++) {
        Heal_Dice[i] = i;
    }
    for (int i = 0; i < count; i++) {
        int randNum1 = rand() % 7;
        int randNum2 = rand() % 7;
        int temp;
        temp = Heal_Dice[randNum1];
        Heal_Dice[randNum1] = Heal_Dice[randNum2];
        Heal_Dice[randNum2] = temp;
    }


    sprintf(numbers, "Images/dices/%d.png", Heal_Dice[0]);

    number[2] = createObject(numbers, scene[4], 600, 350, true);

}
void monsterDice() {
    int count = 100;
    for (int i = 0; i < 6; i++) {
        Monster_Dice_Number[i] = i;
    }
    for (int i = 0; i < count; i++) {
        int randNum1 = rand() % 6;
        int randNum2 = rand() % 6;
        int temp;
        temp = Monster_Dice_Number[randNum1];
        Monster_Dice_Number[randNum1] = Monster_Dice_Number[randNum2];
        Monster_Dice_Number[randNum2] = temp;
    }
}


void createPlayerHp(int hp) { 
    ps->hp = hp;
    char playerHp[40];
    sprintf(playerHp, "Images/hp/%d.png", hp);
    HP[0]=createObject("Images/hp/hp.png", scene[4], 60, 650, true);
    PLAYER_HP=createObject(playerHp, scene[4], 140, 660, true);
}

void setMonsterHp(int hp) {
    ms->hp = hp;
    char monsterHp[40];
    sprintf(monsterHp, "Images/hp/%d.png", hp);
    HP[1]=createObject("Images/hp/hp.png", scene[4], 1050, 650, true);
    MONSTER_HP=createObject(monsterHp, scene[4], 1130, 660, true);
    
}
void setBoss() { 
    setMonsterHp(150);
    goblin[1] = createObject("Images/monsters/6.png", scene[4], 460, 100, true);
    monsterName = createObject("Images/monsters/name6.png", scene[4], 540, 50, true);

   
}
void changePlayerHp(int hp) {
    char playerHp[40];
    sprintf(playerHp, "Images/hp/%d.png", hp);
    if (ps->hp > 180) {     
        ps->hp = 180;
        setObjectImage(PLAYER_HP, "Images/hp/180.png");
    }
    else
        setObjectImage(PLAYER_HP, playerHp);


  
}
void changeMonsterHp(int hp) {
    char monsterHp[40];
    sprintf(monsterHp, "Images/hp/%d.png", hp);
    setObjectImage(MONSTER_HP, monsterHp);
    
}
void createMonsters(int x) {
    
    switch (x)
    {
    case 0:
        goblin[0] = createObject("Images/monsters/0.png", scene[4], 438, 200, true);
        monsterName = createObject("Images/monsters/name0.png", scene[4], 540, 130, true);
        setMonsterHp(100);
        return;
    case 1:
        goblin[0] = createObject("Images/monsters/1.png", scene[4], 438, 200, true);
        monsterName = createObject("Images/monsters/name1.png", scene[4], 550, 130, true);
        setMonsterHp(110);

        return;
    case 2:
        goblin[0] = createObject("Images/monsters/2.png", scene[4], 420, 150, true);
        monsterName = createObject("Images/monsters/name2.png", scene[4], 550, 100, true);
        setMonsterHp(120);

        return;
    case 3:
        goblin[0] = createObject("Images/monsters/3.png", scene[4], 438, 200, true);
        monsterName = createObject("Images/monsters/name3.png", scene[4], 540, 130, true);
        setMonsterHp(120);

        return;
    case 4:
        goblin[0] = createObject("Images/monsters/4.png", scene[4], 438, 200, true);
        monsterName = createObject("Images/monsters/name4.png", scene[4], 540, 130, true);
        setMonsterHp(130);

        return;
    case 5:
        goblin[0] = createObject("Images/monsters/5.png", scene[4], 438, 200, true);
        monsterName = createObject("Images/monsters/name5.png", scene[4], 540, 130, true);
        setMonsterHp(140);

        return;
    }
}
void Heal(int x) { 

    switch (x)
    {
    case 0:
        healing = createObject("Images/effects//heal/0.png", scene[4], 150, 620, true);
        return;
    case 1:
        healing = createObject("Images/effects//heal/10.png", scene[4], 150, 620, true);
        ps->hp = ps->hp + 10;
        changePlayerHp(ps->hp);
        return;
    case 2:
        healing = createObject("Images/effects//heal/20.png", scene[4], 150, 620, true);
        ps->hp = ps->hp + 20;
        changePlayerHp(ps->hp);

        return;
    case 3:
        healing = createObject("Images/effects//heal/30.png", scene[4], 150, 620, true);
        ps->hp = ps->hp + 30;
        changePlayerHp(ps->hp);

        return;
    case 4:
        healing = createObject("Images/effects//heal/40.png", scene[4], 150, 620, true);
        ps->hp = ps->hp + 40;
        changePlayerHp(ps->hp);

        return;
    case 5:
        healing = createObject("Images/effects//heal/50.png", scene[4], 150, 620, true);
        ps->hp = ps->hp + 50;
        changePlayerHp(ps->hp);
        return;
    case 6:
        healing = createObject("Images/effects//heal/60.png", scene[4], 150, 620, true);
        ps->hp = ps->hp + 60;
        changePlayerHp(ps->hp);
        return;

    }
    


}
void startTutorial() { 
    enterScene(scene[4]);
    createPlayerHp(100);
    createMonsters(0);
    arrow = createObject("Images/effects/arrow.png", scene[4], 790, 200, true);
    click = createObject("Images/effects/click.png", scene[4], 800, 265, true);
    diceBox = createObject("Images/effects/diceBox.png", scene[4], 982, 198, true);
    diceButton[1] = createObject("Images/buttons/dice0.png", scene[4], 990, 200, true);
    diceButton[0] = createObject("Images/buttons/dice0.png", scene[4], 990, 200, true);



}
void initialize() { 
    if (ps->hp <= 0) {
        enterScene(scene[5]);
        playSound(bgm[4]);
        hideObject(HP[0]);
        hideObject(HP[1]);
        hideObject(PLAYER_HP);
        hideObject(MONSTER_HP);
        hideObject(goblin[0]);
        hideObject(goblin[1]);
        hideObject(monsterName);
        IsonDice = true;
        IsonBoss = false;
        button[1] = createObject("Images/buttons/restart.png", scene[5], 550, 270, true);
        button[2] = createObject("Images/buttons/end.png", scene[5], 550, 170, true);

    }
  
}
void Create_Timer() { 
    for (int i = 0; i < 10; i++) {
        firstTimer[i] = createTimer(1);

    }
    for (int i = 0; i < 10; i++) {
        secondTimer[i] = createTimer(1.0f);

    }
    for (int i = 0; i < 3; i++) {
        secondTimer[i] = createTimer(1.0f);

    }
    for (int i = 0; i < 3; i++) {
        warnSign[i] = createTimer(1.0f);

    }
    for (int i = 0; i < 4; i++) {
        thirdTimer[i] = createTimer(1.0f);

    }
    Show_Monster_Dice = createTimer(1.0f);
    deleteName = createTimer(1.0f);
    lastTimer = createTimer(1.0f);
    hideTimer;
}

void createGame() {  
    createScene();
    createNextButton(0, 2);
    button[0] = createObject("Images/buttons/start.png", scene[0], 550, 270, true);
    Create_Timer();
    createSound(); 
    playSound(bgm[0], false);
    startGame(scene[0]);
}

void mouseCallback(ObjectID object, int x, int y, MouseAction) {
    if (object == button[0]) {      
        enterScene(scene[1]);
        setTimer(firstTimer,0, 0.7);
    }
    else if (object == nextButton[0]) {     
        enterScene(scene[3]);
        setTimer(firstTimer,1, 0.7);

    }
   
    else if (object == diceButton[1]) {    
        playSound(bgm[9]);
;         setObjectImage(diceButton[1], "Images/buttons/dice1.png");
         setTimer(firstTimer, 2, 0.5f);
        
    }
    else if (object == diceButton[0]) {     
        if (IsonDice) {
            playSound(bgm[9]);
            hideObject(arrow);
            hideObject(click);
            hideObject(diceBox);
            setObjectImage(diceButton[0], "Images/buttons/dice1.png");
            setTimer(firstTimer, 7, 0.5f);
            IsonDice = false;
        }
    }
    else if (object == nextButton[1]) { 
        hideObject(number[0]);
        hideObject(messageBox[0]);
        hideObject(diceButton[0]);
        hideObject(diceButton[1]);
        hideObject(nextButton[1]);
        magicionSkill0(1);
        setTimer(firstTimer, 9, skillTimer);

    }
    else if (object == nextButton[2]) {    
        hideObject(HP[0]);
        hideObject(PLAYER_HP);
        changeMonsterHp(100);
        createPlayerHp(180);              
        showObject(diceButton[1]);
        hideObject(nextButton[2]);
        hideObject(messageBox[1]);


    }
  
    
    else if (object == nextButton[3]) { 
        if (IsmessageOn) {
            healObject[0] = createObject("Images/effects/healObject0.png", scene[4], 200, 10, true);
            healObject[1] = createObject("Images/effects/healObject1.png", scene[4], 800, 50, true);
            healObject[2] = createObject("Images/effects/healObject2.png", scene[4], 390, 150, true);
            arrow = createObject("Images/effects/arrow.png", scene[4], 600, 50, true);
            click = createObject("Images/effects/click.png", scene[4], 430, 60, true);
            messageBox[2] = createObject("Images/effects/messageBox1.png", scene[4], 470, 300, true);
            IsmessageOn = false;
        }
        else {
            healObject[0] = createObject("Images/effects/healObject0.png", scene[4], 200, 10, true);
            healObject[1] = createObject("Images/effects/healObject1.png", scene[4], 800, 50, true);
            healObject[2] = createObject("Images/effects/healObject2.png", scene[4], 390, 150, true);
        }
        hideObject(nextButton[3]);
  
    }
    else if (object == healObject[1]) {    
        hideObject(arrow);
        hideObject(click);
        hideObject(messageBox[2]);
        setObjectImage(healObject[2], "Images/effects/healObject3.png");
        setTimer(secondTimer, 6, 0.8);
    }
    else if (object == nextButton[4]) { 
        hideObject(healObject[0]);
        hideObject(healObject[1]);
        hideObject(healObject[2]);
        healObject[3] = createObject("Images/effects/healEffect.png", scene[4], 0,0, true);
        playSound(bgm[2]);
        Heal(Heal_Dice[0]);
        setTimer(secondTimer,7,1.0f);
        hideObject(nextButton[4]);
    }
    else if (object == nextButton[5]) { 
        stopSound(bgm[2]);
        countFight--;
        if (countFight <= 0) {
            IsonBoss = true;
            hideObject(nextButton[5]);
            setTimer(warnSign,0, 0.8f);
           
           
        }
        else {
            monsterDice();
            createMonsters(Monster_Dice_Number[0]);
            showObject(diceButton[1]);
            hideObject(nextButton[5]);
        }
    }
    else if (object == nextButton[6]) {      
        playSound(bgm[7]);
        enterScene(scene[6]);
        createNextButton(7, 6);
        hideObject(nextButton[6]);
        
    }
    else if (object == nextButton[7]) {     
        enterScene(scene[7]);
        createNextButton(8, 7);
        hideObject(nextButton[7]);

    }
    else if (object == nextButton[8]) {    
    enterScene(scene[8]);
    createNextButton(9, 8);
    hideObject(nextButton[8]);

    }
    else if (object == nextButton[9]) {     
    enterScene(scene[9]);
    createNextButton(10, 9);
    hideObject(nextButton[9]);

    }
    else if (object == nextButton[10]) {    
        stopSound(bgm[7]);
        playSound(bgm[8]);
        enterScene(scene[10]);
        createNextButton(11, 10);
        hideObject(nextButton[10]);

    }
    else if (object == nextButton[11]) {    
    enterScene(scene[3]);
    setTimer(lastTimer, 1.0f);
    startTimer(lastTimer);
    
    }
   
    else if (object == button[1]) {         
        enterScene(scene[0]);
        stopSound(bgm[4]);
        playSound(bgm[0]);
       
    }
    else if (object == button[2]) {        
        free(ps);
        free(ms);
        endGame();
    }
    else if (object = nextButton[12]) {     
    hideObject(messageBox[3]);
    hideObject(nextButton[12]);
    setTimer(thirdTimer, 3, skillTimer);

    }

}
void timerCallback(TimerID timer) {
    
    if (timer == firstTimer[0]) { 
        enterScene(scene[2]);
    }
    else if (timer == firstTimer[1]) {     
        stopSound(bgm[0]);
        startTutorial();
    }
    else if (timer == firstTimer[7]) { 
        setObjectImage(diceButton[0], "Images/buttons/dice0.png");
        setTimer(firstTimer, 8, 0.3);
    }
    else if (timer == firstTimer[8]) { 
        number[0] = createObject("Images/dices/1.png", scene[4], 1050, 300, true);
        messageBox[0] = createObject("Images/effects/messageBox.png", scene[4], 954, 400, true);
        createNextButton(1, 4);

    }


    else if (timer == firstTimer[9]) {
        magicionSkill1(1);
        hideObject(magicianSkill[0]);
        setTimer(secondTimer, 0, skillTimer);

    }

    else if (timer == secondTimer[0]) {   
        hideObject(magicianSkill[1]);
        hideObject(damages[1]);
        changeMonsterHp(ms->hp);
        if (dices[0] == 6) {
            setTimer(thirdTimer, 0, 1.6f);

        }
        setTimer(thirdTimer, 0, skillTimer);

    }
    else if (timer == thirdTimer[0]) {      
        number[1] = createObject("Images/dices/1.png", scene[4], 200, 300, true);
        setTimer(thirdTimer, 1, skillTimer);

    }
    else if (timer == thirdTimer[1]) {      
        hideObject(number[1]);
        monsterSkill(1);
        setTimer(thirdTimer, 2, skillTimer);
    }
    else if (timer == thirdTimer[2]) {    
        hideObject(monsterSkills);
        hideObject(damages[2]);
        changePlayerHp(ps->hp);
        messageBox[3] = createObject("Images/effects/messageBox2.png", scene[4], 10, 420, true);
        createNextButton(12, 4);

    }
    else if (timer == thirdTimer[3]) {     
        messageBox[1] = createObject("Images/effects/messageBox0.png", scene[4], 400, 400, true);
        createNextButton(2, 4);

    }
    else if (timer == deleteName) {
        hideObject(monsterName);
    }
   
    else if (timer== firstTimer[2]) {        
        setObjectImage(diceButton[1], "Images/buttons/dice0.png");
               
        setTimer(firstTimer, 3, 0.3f);

    }
    else if (timer == firstTimer[3]) {     
        mixDice();
        setTimer(firstTimer, 4, 0.5f);

    }
    else if (timer == firstTimer[4]) {      
        hideObject(diceButton[1]);
        hideObject(number[1]);
        magicionSkill0(dices[0]);
        if (dices[0] == 0) {
            damages[0] = createObject("Images/damages/0.png", scene[4], 822, 400, true);
            playSound(bgm[5]);
            setTimer(secondTimer, 4, skillTimer);
        }
        else {
            setTimer(firstTimer, 5, skillTimer);
        }
    }

    else if (timer == firstTimer[5]) {      
        hideObject(magicianSkill[0]);
        magicionSkill1(dices[0]);
        setTimer(firstTimer, 6, skillTimer);
    }
    else if (timer == secondTimer[4]) {    
        hideObject(damages[0]);
        setTimer(secondTimer, 1, skillTimer);


    }
    else if (timer == firstTimer[6]) {     
        hideObject(magicianSkill[1]);
        hideObject(damages[1]); 
        changeMonsterHp(ms->hp);
        if (ms->hp <= 0) {
            if (IsonBoss == false) {
                playSound(bgm[1]);
            }
            setObjectImage(MONSTER_HP, "Images/hp/0.png");
            setTimer(secondTimer, 5, skillTimer);

        }
        else {
            setTimer(secondTimer,1, skillTimer);

        }
    }
       


    else if (timer == secondTimer[1]) {   
        monsterDice();
        sprintf(MonsterNumbers, "Images/dices/%d.png", Monster_Dice_Number[0]);
        number[1] = createObject(MonsterNumbers, scene[4], 200, 300, true);
        setTimer(Show_Monster_Dice, 0.5f);
        startTimer(Show_Monster_Dice);
       
    }
    else if (timer == Show_Monster_Dice) {
        hideObject(number[1]);
        if (Monster_Dice_Number[0] == 0) {
            damages[0] = createObject("Images/damages/0.png", scene[4], 800, 250, true);
            playSound(bgm[5]);
            setTimer(secondTimer, 9, skillTimer);

        }
        else {
            if (IsonBoss == false) {
                monsterSkill(Monster_Dice_Number[0]);
                setTimer(secondTimer, 2, skillTimer);
            }
            else {
                bossSkill(Monster_Dice_Number[0]);
                setTimer(secondTimer, 2, skillTimer);
            }
        }
    }
    else if (timer == secondTimer[9]) {    
        hideObject(damages[0]);
        setTimer(secondTimer, 3, skillTimer);
    }
    else if (timer == secondTimer[2]) {   
        hideObject(monsterSkills);
        hideObject(damages[2]);
        changePlayerHp(ps->hp);
        initialize();
        setTimer(secondTimer, 3, skillTimer);
    }
    else if (timer == secondTimer[3]) {    
        showObject(diceButton[1]);
    }

    else if (timer == secondTimer[5]) {     
        if (IsonBoss == false) {
            hideObject(HP[1]);
            hideObject(MONSTER_HP);
            hideObject(goblin[0]);
            hideObject(monsterName);
            createNextButton(3, 4);
        }
        else {
            playSound(bgm[6]);
            hideObject(HP[1]);
            hideObject(MONSTER_HP);
            hideObject(monsterName);
            hideObject(goblin[1]);
            createNextButton(6, 4);
        }
    }
    else if (timer == secondTimer[6]) {   
          healDice();
        createNextButton(4, 4);
    }
    else if (timer == secondTimer[7]) {   
    hideObject(healObject[3]);
    hideObject(number[2]);
    hideObject(healing);
    createNextButton(5, 4);
    }
    else if (timer == warnSign[0]) {    
    playSound(bgm[3]);
    warning = createObject("Images/effects/warning.png", scene[4], 300, 400, true);
    setTimer(warnSign,1, 0.5f);
    }
    else if (timer == warnSign[1]) {     
    warnCount--;
    hideObject(warning);
    for (int i = 0; i < warnCount; i++) {
        setTimer(warnSign,0, 0.5f);
   
    }
    if (warnCount == 0) {
        setTimer(warnSign, 2, 0.8f);
    }
    }
    else if (timer == warnSign[2]) {   
    stopSound(bgm[3]);
    setBoss();
    showObject(diceButton[1]);;
    
    }
    else if (timer == secondTimer[8]) {  
    hideObject(healObject[3]);
    hideObject(number[2]);
    hideObject(healing);
    createNextButton(5, 4);
    }
   
    else if (timer == lastTimer) {     
    free(ps);
    free(ms);
    endGame();
}
 
 
}

void settingGameOption() {       
    setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
    setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);
    setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
}
void setCallback() {            
    setMouseCallback(mouseCallback);
    setTimerCallback(timerCallback);
}

int main() {
    
    srand(time(NULL));
    setCallback();
    settingGameOption();
    createGame();
   
}
