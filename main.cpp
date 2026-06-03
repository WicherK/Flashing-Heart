#define CLOCK 2
#define LATCH 1
#define DATA 0

#define MODE_BUTTON 3

uint32_t leds = 0xFFFFFFFF;

uint8_t mode = 0;


// Timers
bool lastButtonState = HIGH;
unsigned long animationTimer = 0;


// Animation states
bool blinkState = false;

uint8_t circlePhase = 0;

uint8_t circleIndex = 31;

uint8_t heartbeatStep = 0;

void turnOnLed(uint8_t index);
void turnOffLed(uint8_t index);
void turnOffAll();
void turnOnAll();
void sendLeds();

// Animations
void BlinkAnimation();
void CircleAnimation();
void HeartbeatAnimation();

void setup()
{
    pinMode(CLOCK, OUTPUT);
    pinMode(LATCH, OUTPUT);
    pinMode(DATA, OUTPUT);

    pinMode(MODE_BUTTON, INPUT_PULLUP);

    turnOffAll();
}

void loop()
{
    // Button handling
    bool currentButtonState = digitalRead(MODE_BUTTON);

    if(lastButtonState == HIGH && currentButtonState == LOW)
    {
        delay(20);

        if(digitalRead(MODE_BUTTON) == LOW)
        {
            mode++;

            if(mode > 3)
            {
                mode = 0;
            }

            turnOffAll();

            blinkState = false;

            circlePhase = 0;
            circleIndex = 31;

            heartbeatStep = 0;

            animationTimer = millis();
        }
    }

    lastButtonState = currentButtonState;


    // Modes
    if(mode == 0)
    {
        turnOnAll();
    }
    else if(mode == 1)
    {
        BlinkAnimation();
    }
    else if(mode == 2)
    {
        CircleAnimation();
    }
    else if(mode == 3)
    {
        HeartbeatAnimation();
    }
}

// MODE 1 - Blink
void BlinkAnimation()
{
    if(millis() - animationTimer >= 1500)
    {
        animationTimer = millis();

        blinkState = !blinkState;

        if(blinkState)
        {
            turnOnAll();
        }
        else
        {
            turnOffAll();
        }
    }
}


// MODE 2 - Circle
void CircleAnimation()
{
    // =========================
    // PHASE 0
    // Single moving LED
    // =========================

    if(circlePhase == 0)
    {
        if(millis() - animationTimer >= 250)
        {
            animationTimer = millis();

            turnOffAll();

            turnOnLed(circleIndex);

            if(circleIndex == 0)
            {
                circleIndex = 31;
                circlePhase = 1;
            }
            else
            {
                circleIndex--;
            }
        }
    }

    // PHASE 1
    else if(circlePhase == 1)
    {
        if(millis() - animationTimer >= 50)
        {
            animationTimer = millis();

            turnOnLed(circleIndex);

            if(circleIndex == 0)
            {
                circlePhase = 2;
                animationTimer = millis();
            }
            else
            {
                circleIndex--;
            }
        }
    }

    // PHASE 2
    else if(circlePhase == 2)
    {
        if(millis() - animationTimer >= 10000)
        {
            turnOffAll();

            circleIndex = 31;

            circlePhase = 0;

            animationTimer = millis();
        }
    }
}

// MODE 3 - Heartbeat
void HeartbeatAnimation()
{
    switch(heartbeatStep)
    {
        // first beat ON
        case 0:
            turnOnAll();
            animationTimer = millis();
            heartbeatStep = 1;
            break;

        // first beat OFF
        case 1:
            if(millis() - animationTimer >= 220)
            {
                turnOffAll();
                animationTimer = millis();
                heartbeatStep = 2;
            }
            break;

        // pause
        case 2:
            if(millis() - animationTimer >= 180)
            {
                turnOnAll();
                animationTimer = millis();
                heartbeatStep = 3;
            }
            break;

        // second beat OFF
        case 3:
            if(millis() - animationTimer >= 320)
            {
                turnOffAll();
                animationTimer = millis();
                heartbeatStep = 4;
            }
            break;

        // long pause
        case 4:
            if(millis() - animationTimer >= 1200)
            {
                heartbeatStep = 0;
            }
            break;
    }
}

// ======================================================

void turnOnLed(uint8_t index)
{
    if(index >= 32) return;

    bitClear(leds, index);

    sendLeds();
}

void turnOffLed(uint8_t index)
{
    if(index >= 32) return;

    bitSet(leds, index);

    sendLeds();
}

void turnOffAll()
{
    leds = 0xFFFFFFFF;

    sendLeds();
}

void turnOnAll()
{
    leds = 0x00000000;

    sendLeds();
}

void sendLeds()
{
    digitalWrite(LATCH, LOW);

    shiftOut(DATA, CLOCK, MSBFIRST, (leds >> 24) & 0xFF);
    shiftOut(DATA, CLOCK, MSBFIRST, (leds >> 16) & 0xFF);
    shiftOut(DATA, CLOCK, MSBFIRST, (leds >> 8) & 0xFF);
    shiftOut(DATA, CLOCK, MSBFIRST, leds & 0xFF);

    digitalWrite(LATCH, HIGH);
}