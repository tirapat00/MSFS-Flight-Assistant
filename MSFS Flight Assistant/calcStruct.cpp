int progress = 0;

void increaseProgress() {
	progress++;
}

int getProgress(){
	return progress;
}

void setProgress(int progressGiven){
	progress = progressGiven;
}

/* 
* 0 = inital starting monitor (show data)
* 1 = cabin check
* 2 = right Wing check
* 4 = nose check
* 5 = left Wing check
* 6 = preStart Engine
* 7 = startEngine + RPM in correct area
* 8 = startEngine + RPM too low
* 9 = startEngine + RPM too high
* 10 = taxi + gain speed; 10+11 part of brake check
* 11 = taxi + brake
* 12 = pre take off
* 13 = pre take off wrong RPM
* 14 = take off
* 15 = take off adjust Speed
* 16 = take off hold Speed
* 17 = climb
* 18 = climb + speed too low
* 19 = climb + hold speed
* 20 = climb + decrease speed
* 21 = climb + altitude reached 
* 22 = cruse
* 23 = flight Mode (show data and flight class ...)
* 24 = before landing
* 25 = landing
* 26 = landing + adjust speed
* 27 = landing + hold speed
* 28 = after landing
* 29 = shutdown
* 30 = shutdown + RPM too high
* 31 = shutdown + hold RPM below 1000
* 32 = shutdown engine
* 33 = shutdown complete
* 34 = finish screen
*/
