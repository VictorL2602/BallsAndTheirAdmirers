**Balls and Their Admirers**
Dette program er skrevet i C med Raylib. Det viser en animation med mange kugler som bevæger sig rundt på skærmen.

**Funktionalitet**
-Der oprettes 100 kugler med tilfældig position, farve, hastighed og størrelse.
-Alle kugler følger en tilfældigt valgt leder.
-Kuglerne bevæger sig rundt, rammer kanterne og vender om.
-Der tegnes en linje mellem hver kugle og dens leder, så man kan se forbindelsen.

**Hvordan det virker**
-init_balls_random() laver kuglerne med tilfældige værdier.
-init_ball_random() vælger en kugle som leder, som alle andre følger.
-update_pos() opdaterer position, hastighed og håndterer vægge.
-balls_draw() tegner kuglerne og linjerne til lederen.
-main() starter vinduet og kører animationen.

## Bemærk at videoklippet er 4x hastighed, så man kan se en hel "cyklus" på 10 sekunder