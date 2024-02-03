Videojocs 23/24 Q1 - Exercici 2D:

Nom i cognoms dels integrants del grup
-------------------------------------

HAONAN JIN

JINHENG LING



Funcionalitats implementades
----------------------------

MENÚ PRINCIPAL:

- Menú de selecció per escollir inicialitzar el joc, veure instruccions o crédits.


PANTALLA INSTRUCCIONS:

- Pantalla que introdueix una explicació general i les instruccions del joc.


PANTALLA CREDITS:

- Pantalla que mostra els credits del videojoc.


PANTALLA ESCENA (NIVELL):

- El joc està format per dos nivells

- El personatge té inicialment 3 vides. Quan perd una vida, representa que mort i tornarà al punt inicial definit al nivell (respawn)

- El nivel comença amb 300 segons.

- El personatge pot recollir els power-ups: mushroom, star, cada power-up otorga una habilitat al personatge.

  -> En el cas de col·leccionar amb la moneda, el personatge aconsegueix punts determinat 
  -> Tambe aconsegueix punts al matar el enemics que son goomba i la tortuga

- El personatge perd una vida quan:
	- El temps del nivell s'acaba (el temps es reinicia a 300 segons).
	- Col·lisiona amb un enemic
	- Cau en les forats

- Hi ha 3 tipus d'enemics:

  -> MushMonster. El seu moviment és constant i es mou de dreta a esquerra i d'esquerra a dreta, comença amb una orientació predeterminada (cap a esquerra/dreta) i es mou a l'orientació dedicada, en el cas que col·lideix amb la paret o el personatge, o bé es troba a un objecte es mourà cap a l'orientació contrària. 
  -> Turtle. El seu moviment es casi exactament igual que el MushMonster    

- Quan la vida del personatge arriba a zero ens apareix una pantalla de GAME OVER i al cap d'un temps tornarà al menú inicial.

- Cada porta té una porta tancada i una clau. La clau apareixerà un cop s'activin totes les plataformes activables del nivell corresponent. Quan s'afagi la clau s'obrirà la porta.
  El nivell es completa quan el personatge entra a la porta. El temps restant es suma a la puntuació total.

- Quan el personatge entra a la porta es passa al següent nivell o bé es torna al menú principal en cas de ser l'últim nivell. En aquest últim cas apareixerà una pantalla de GAME COMPLETED i al cap d'un temps tornarà al menú principal.


Instruccions del joc
--------------------

MENÚ 

- Esc per finalitzar l'execució del joc

- Fletxes de dalt i de baix per seleccionar el submenú i el nivell al qual vulguem accedir

- Space per confirmar el submenú seleccionat i accedir-hi


SUBMENÚ INSTRUCCIONS

- ENTER per tornar al menú


SUBMENÚ CRÈDITS
- ENTER per tornar al menú


PANTALLES DEL JOC

- Esc per tornar al menú

- '1','2' per seleccionar nivell desitjat

- 'M' Converteix directament en supermario

- 'S' Converteix en invulnerable mario

- Fletxes d'esquerra i de dreta per moure

- Fletxa de dalt per saltar


EXECUTALBLE

El path del executable
SuperMarioBros\02-Bubble\02-Bubble
