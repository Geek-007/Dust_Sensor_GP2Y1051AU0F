
//HardwareSerial Serial2(2);

#define RXD2 16
#define TXD2 17

float pm25, pm10, pm25_test, pm10_test;

void getDust(boolean disp) {
  uint8_t mData = 0;
  uint8_t mPkt[10] = {0};
  uint8_t mCheck = 0;

  while ( Serial1.available() > 0 ) {
    for ( int i = 0; i < 10; ++i ) {
      mPkt[i] = Serial1.read();
    }
    if ( 0xC0 == mPkt[1] ) {
      // Read dust density.
      // Check
      uint8_t sum = 0;
      for ( int i = 2; i <= 7; ++i ) {
        sum += mPkt[i];
      }
      if ( sum == mPkt[8] ) {
        uint8_t pm25Low   = mPkt[2];
        uint8_t pm25High  = mPkt[3];
        uint8_t pm10Low   = mPkt[4];
        uint8_t pm10High  = mPkt[5];

        pm25 = ( ( pm25High * 256.0 ) + pm25Low ) / 10.0;
        pm10 = ( ( pm10High * 256.0 ) + pm10Low ) / 10.0;

      }
    }
    Serial1.flush();
  }
  Serial.print("PM2.5="); Serial.print(pm25);
  Serial.print("  PM10="); Serial.println(pm10);
  Serial.println("");
  Serial.println("");
}

void setup() {
  Serial.begin(115200);
  Serial1.begin(9600, SERIAL_8N1, RXD2, TXD2);
}

uint32_t pevTime = 0;

void loop() {
  if (millis() - pevTime >= 1000) {
    getDust(1);
    pevTime = millis();
  }

}
