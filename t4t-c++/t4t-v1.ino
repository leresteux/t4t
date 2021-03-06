/* t4t v1.0 par leresteux julien

mode normal = 
brossage de durée egal chaque partie
accélération reculiere

mode random = 
brossage de durée egal chaque partie
cycle de brossage irréculier

mode hardcore = 
brossage totalement hasardeux
---
mode d'emploi

choix du mode
  Rester appuyé jusqu'à obtention du mode désiré  :
    1 led mode normal
    2 leds mode random
    3 leds mode hardcore
    puis reviens à 1 led etc

Mettre en pause ou en veille
  Appuyer sur le btn > les leds clignotent
  pour redémarer rappuyer jusqu'à ce que les leds effectuent un decompte
  si à la fin du decompte le bouton est toujours enfoncé le T4T se met en veille



  
*/
const int led[] = {12, 11, 10, 9, 8, 7}; // pins led
const int tempsLedChargement = 100;//durée d'eclairage des leds lors du "menu"
const int btn = 4;
const int tempsCracha = 6000;
int ob[] = {9, 9, 9, 9, 9, 9}; //stockage des LEDs

int randTemps, sec , R, r, c;

boolean ok = false, waiting = true,  etatBtn;

int phase = 0;

unsigned long duree = 0;
int modeMenu = 0;

//LES MODES
void normalMode() {
  Serial.print("normalMode");
  delay(100);

  for (int i = 0; i < 3; i++) {
    blinkAll (0);
  };
  delay(1000);

  //2 cycles led de 30 sec
  for (int i = 0; i < 2; i++) {

    ordreBrossage ();
    lumiere(5000);//6*2*5000= 60sec
  };
  //pause cracha
  cracha();
  blinkAll(0);

  //2 cycles led de 24 sec
  for (int i = 0; i < 2; i++) {

    ordreBrossage ();
    lumiere(4000);//6*2*4000= 48sec -108
  };
  //pause cracha
  cracha();
  blinkAll(0);

  //3 cycles led de 18 sec
  for (int i = 0; i < 3; i++) {


    ordreBrossage ();
    lumiere(3000);//6*3*3000= 54sec -162
  };
  //2 cycles led de 12 sec
  for (int i = 0; i < 2; i++) {
    ordreBrossage ();
    lumiere(2000);//6*2*2000= 24 sec -186
  };

  //cycle led de 6 sec
  for (int i = 0; i < 1; i++) {
    ordreBrossage ();
    lumiere(1000);//6*1*1000= 6 sec -192 soit 3min et 12sec
  };
  //cycle led de fin
  for (int i = 0; i < 3; i++) {
    blinkAll (0);
  }
  Serial.println(":D");
  modeMenu = 0;
waiting =true;

}

void randomMode() {
  Serial.println("random Mode");
  for (int i = 0; i < 3; i++) {
    blinkAll (1);
  }// les leds clignotent de facon hasardeuse
  delay(2000);
  bool cracha1 = false;
  bool cracha2 = false;
  delay(1000);
  duree = 0;
  while (duree < 190000) {
    Serial.print("duree = ");
    Serial.println(duree);
    int randomSec = (random(1, 5) * 1000); //entre 1 et5
    Serial.print("time ="); Serial.println(randomSec);
    delay(2);
    ordreBrossage ();
    lumiere(randomSec);
    if (duree >= 60000 && cracha1 == false) {
      cracha();
      cracha1 = true;
    }
    else if (duree >= 120000 && cracha2 == false) {
      cracha();
      cracha2 = true;
    }

  };
  Serial.println("random Mode Over");
  modeMenu = 0;
  blinkAll(1);
waiting =true;
}
void harcoreRandomMode() {
  Serial.println("harcoreRandomMode Mode");
  for (int i = 0; i < 10; i++) {
    blinkAll (1);
  }// les leds clignotent de facon hasardeuse
  delay(2000);
  bool cracha1 = false;
  bool cracha2 = false;
  delay(1000);
  duree = 0;
  while (duree < 190000) {

    int etatBtn = digitalRead(btn);
    //petite vérification si btn appuyé
    if (!etatBtn) {
      pausse();
      /*//ancien code ok 
      blinkAll(0);
      waiting = true;
      modeMenu = 0;
      start();*/
      break;
    }
    Serial.print("duree = ");
    Serial.println(duree);
    int randomSec = (random(1, 5) * 1000); //entre 1 et5
    Serial.print("time ="); Serial.println(randomSec);
    delay(2);
    R = random(0, 6);

    Serial.print("n°led  ="); Serial.println(led[R]);
    digitalWrite(led[R], HIGH);
    delay(randomSec);
    duree = duree + randomSec;
    digitalWrite(led[R], LOW);

    if (duree >= 60000 && cracha1 == false) {
      cracha();
      cracha1 = true;
    }
    else if (duree >= 120000 && cracha2 == false) {
      cracha();
      cracha2 = true;
    }

  };
  Serial.println("random Mode Over");
  modeMenu = 0;
  blinkAll(1);

}
// mini fonctions
void pausse() {

  while (etatBtn) {
    for (int i = 0; i < 6; i++) {
      digitalWrite(led[i], HIGH);
    }
    delay(1000);
    for (int i = 0; i < 6; i++) {
      digitalWrite(led[i], LOW);
      delay(1000);

    }
    etatBtn = digitalRead(btn);
    delay(10);
  }
  for (int j = 0; j < 10; j++) {//petit show de led pour prevenir du choix
    for (int i = 0; i < 6; i++) {
      digitalWrite(led[i], HIGH);
    }
    delay(100);
    for (int i = 0; i < 6; i++) {
      digitalWrite(led[i], LOW);
      delay(100);

    }
  }
  etatBtn = digitalRead(btn);
  delay(10);
  if (!etatBtn) {
    modeMenu = 0;
    start();
  }
}

void blinkAll (int mode) {
  Serial.println("blinAll");

  //mode random ==led clignote hasardeusement
  if (mode == 1) {//hasard
    ordreBrossage();
    delay(50);
    lumiere(tempsLedChargement);

  }
  //mode normal
  else if (mode == 0) { //chenillard
    for (int i = 0; i < 6; i++) {
      digitalWrite(led[i], HIGH);
      delay(tempsLedChargement);
      digitalWrite(led[i], LOW);
      delay(tempsLedChargement);

    }
  }
}

//ordre hasardeux du brossage  des dents
void ordreBrossage() {
  //remplit un array de 6 cases avec 012345 en evitant les doublons
  for (c = 0; c < 6; c++) {
    ok = false;
    while (ok == false) {
      ok = true;

      R = random(0, 6);
      for (int j = 0; j < c; j++) {
        if (R == ob[j]) {
          ok = false;
        };
      };
    };
    ob[c] = R;
  };
  //print les led allumées
  for (int a = 0; a < 6; a++) {
    Serial.print(ob[a]);
  };
}

void lumiere(int Time) {
  for (int z = 0; z < 6; z++) {
    int etatBtn = digitalRead(btn);
    //petite vérification si btn appuyé
    if (!etatBtn) {
      pausse();

      /*//ancien code ok
      blinkAll(0);
      waiting = true;
      modeMenu = 0;
      start();*/
      break;
    }
    //on allume et étends led
    int ledaallumer = ob[z];
    digitalWrite(led[ledaallumer], HIGH);
    delay(Time);
    duree = duree + Time;
    digitalWrite(led[ledaallumer], LOW);
  }
}

void cracha() {
  for (int i = 0; i < 6; i++) {
    digitalWrite(led[i], HIGH);
  }
  delay(tempsCracha);
  for (int i = 0; i < 6; i++) {
    digitalWrite(led[i], LOW);
  }
}


void start () {
  Serial.print("start");
  while (waiting) {
    etatBtn = digitalRead(btn);
    Serial.println(etatBtn);
    if (!etatBtn)

    { modeMenu = 1;
      digitalWrite(led[0], HIGH); // led 1 == lancement menu de selection
      delay(1000);
      etatBtn = digitalRead(btn);//apres 1 sec si encore appuyé choix randomMode sinon normalMode
    
    if (!etatBtn)
    { modeMenu = 2;
      digitalWrite(led[1], HIGH);
      delay(2000);
      etatBtn = digitalRead(btn);
      if (!etatBtn)
      { modeMenu = 3;
        digitalWrite(led[2], HIGH);
        delay(2000);
        etatBtn = digitalRead(btn);

        if (!etatBtn)//apres 2 sec si appuyé annule choix mode - relance la loop
        {
          digitalWrite(led[0], LOW);
          digitalWrite(led[1], LOW);
          digitalWrite(led[2], LOW);
          modeMenu = 0;
          delay(2000);
        }

      }
    }
}
      switch (modeMenu) {
        case 1:

          digitalWrite(led[0], LOW);
          waiting = false;
          normalMode();
          break;
        case 2:
          digitalWrite(led[0], LOW);
          digitalWrite(led[1], LOW);
          waiting = false;
          randomMode();
          break;
        case 3:
          digitalWrite(led[0], LOW);
          digitalWrite(led[1], LOW);
          digitalWrite(led[2], LOW);
          waiting = false;
          harcoreRandomMode();
          break;
        default:
          digitalWrite(led[0], LOW);
          digitalWrite(led[1], LOW);
          digitalWrite(led[2], LOW);
          waiting = true;
          break;
      }
    }
  }



void setup() {
  for (int i = 0; i < 6; i++) {
    pinMode(led[i], OUTPUT);
  };

  pinMode(btn, INPUT);
  Serial.begin(9600);
  Serial.println("welcome");
}

//au demarrage du arduino
void loop() {
  Serial.print (".");
  R = random(0, 6); //lancement du random pour led permettant ainsi d'avoir un "vrai" random
  if (waiting) start();

}

