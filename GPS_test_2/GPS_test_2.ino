String gpsData;
String LATval = "######";
String LNGval = "######";
char inChar;

String latt;
String la;
String lonn;
String lo;
float lattt;
float lonnn;
int latDeg;
int lonDeg;
float latMin;
float lonMin;
float latttt;
float lonnnn;
String sGPRMC;
void setup() {
   Serial.begin(9600);
}

void loop() {

  while (Serial.available()) {
    inChar = Serial.read();
    gpsData += inChar;
    if (inChar == '$') {
      gpsData = Serial.readStringUntil('\n');
      break;
    }
  }

  Serial.println(gpsData);
  sGPRMC = gpsData.substring(0, 5);
  if (sGPRMC == "GPRMC") {
    Serial.flush();
    latt = gpsData.substring(18, 28);
    la = gpsData.substring(29, 30);
    lonn = gpsData.substring(31, 42);
    lo = gpsData.substring(43, 44);
    Serial.print("latt:");
    Serial.println(latt);
    Serial.print("la:");
    Serial.println(la);
    Serial.print("lonn:");
    Serial.println(lonn);
    Serial.print("lo:");
    Serial.println(lo);
    lattt = latt.toFloat();
    lonnn = lonn.toFloat();
    Serial.print("lattt:");
    Serial.println(lattt);
    Serial.print("lonnn:");
    Serial.println(lonnn);

    //if (la == "S" and lo == "E") {

      latDeg = float(int(lattt / 100));
      latMin = float(lattt - (latDeg * 100));
      latMin = latMin / 60;
        
      lonDeg = float(int(lonnn / 100));
      lonMin = float(lonnn - (lonDeg * 100));
      lonMin = lonMin / 60;
          
      latttt = latDeg + latMin;
      lonnnn = lonDeg + lonMin;
      LATval = String(latttt);
      LNGval = String(lonnnn);
      Serial.print("latDeg:");
      Serial.println(latDeg);
      Serial.print("latMin:");
      Serial.println(latMin);
      Serial.print("lonDeg:");
      Serial.println(lonDeg);
      Serial.print("lonMin:");
      Serial.println(lonMin);
      Serial.print("LATval:");
      Serial.println(LATval);
      Serial.print("LNGval:");
      Serial.println(LNGval);
 //   }
  }
}
