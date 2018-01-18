#define latchPin 7           // Shift register latch pin (pin 12, ST_CP)
#define clockPin 8           // Shift register clock pin (pin 11, SH_CP)
#define dataPin 6            // Shift register data pin (pin 14, DS - Serial Out)
#define dimmPin 9            // Shift register brightness (pin 13, OutputEnable) (Optional)
#define numOfRegisters 3     // Number of shift registers in use
int lednum = 8 * numOfRegisters;  // Calculate number of LEDs (presuming 8 per register)
byte* registerState;

int effectId = 0;            // Current running effect
int effectPrev = 0;          // Previous effect (so we don't double)
int effectRepeat = 0;        // Times to repeat effect
int effectSpeed = 0;         // Speed of effect

void setup() {
	//Initialize array
	registerState = new byte[numOfRegisters];
	for (size_t i = 0; i < numOfRegisters; i++) {
		registerState[i] = 0;
	}

	//set pins to output so you can control the shift register
	pinMode(latchPin, OUTPUT);
	pinMode(clockPin, OUTPUT);
	pinMode(dataPin, OUTPUT);
	pinMode(dimmPin, OUTPUT);
	analogWrite(dimmPin, 100); // Set brightness (255 = Off, 0 = Full)
}

void loop() {
	// Set a random effect
	do {
		effectId = random(5);
	} while (effectId == prevEffect);
	prevEffect = effectId;

	// Set random repeat of effect
	switch (effectId) {
	case 2:
		effectRepeat = random(1, 5);
		break;
	default:
		effectRepeat = random(1, 2);
		break;
	}

	for (int i = 0; i < effectRepeat; i++) {
		// Set random speed for effect
		effectSpeed = random(10, 90);

		switch (effectId) {
		case 0:
			effectA();
			break;
		case 1:
			effectB();
			break;
		case 3:
			effectC();
			break;
		case 4:
			effectD();
			break;
		case 6:
			effectE();
			break;
		}
	}
}

void effectA() {
	for (int i = 0; i < lednum; i++) {
		for (int k = i; k < lednum; k++) {
			regWrite(k, HIGH);
			delay(effectSpeed);
			regWrite(k, LOW);
		}
		regWrite(i, HIGH);
	}
}

void effectB() {
	for (int i = lednum; i >= 0; i--) {
		for (int k = 0; k < i; k++){
			regWrite(k, HIGH);
			delay(effectSpeed);
			regWrite(k, LOW);
		}
		if (i != lednum) regWrite(i, HIGH);
	}
}

void effectC() {
	int prevI = 0;
	for (int i = 0; i < lednum; i++) {
		regWrite(prevI, LOW);
		regWrite(i, HIGH);
		prevI = i;
		delay(effectSpeed);
	}
	for (int i = (lednum - 1); i >= 0; i--) {
		regWrite(prevI, LOW);
		regWrite(i, HIGH);
		prevI = i;
		delay(effectSpeed);
	}
}

void effectD() {
	for (int i = 0; i < lednum / 2; i++) {
		for (int k = i; k < lednum / 2; k++) {
			regWrite(k, HIGH);
			regWrite(lednum - 1 - k, HIGH);
			delay(effectSpeed);
			regWrite(k, LOW);
			regWrite(lednum - 1 - k, LOW);
		}
		regWrite(i, HIGH);
		regWrite(lednum - 1 - i, HIGH);
	}
}

void effectE() {
	for (int i = (lednum / 2) - 1; i >= 0; i--) {
		for (int k = 0; k <= i; k++) {
			regWrite(k, HIGH);
			regWrite(lednum - 1 - k, HIGH);
			delay(effectSpeed);
			regWrite(k, LOW);
			regWrite(lednum - 1 - k, LOW);
		}

		regWrite(i, HIGH);
		regWrite(lednum - 1 - i, HIGH);
	}
}

void regWrite(int pin, bool state){
	//Determines register
	int reg = pin / 8;
	//Determines pin for actual register
	int actualPin = pin - (8 * reg);
	//Begin session
	digitalWrite(latchPin, LOW);
	for (int i = 0; i < numOfRegisters; i++){
		//Get actual states for register
		byte* states = &registerState[i];
		//Update state
		if (i == reg){
			bitWrite(*states, actualPin, state);
		}
		//Write
		shiftOut(dataPin, clockPin, MSBFIRST, *states);
	}
	//End session
	digitalWrite(latchPin, HIGH);
}
