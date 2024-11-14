
// Declare pins
const int ldrPin = A0;  // Pin for LDR sensor; no pinMode needed in setup

// Declare Global Constants and Variables
const int length = 10;         // Number of values to store for averaging
int readings[length] = { 0 };  // Array to store recent sensor values
int currentIndex = 0;          // Tracks the index for the next reading
int sum = 0;                   // Sum of the current readings to quickly compute mean

void setup() {
  Serial.begin(9600);  // Initialize Serial Monitor
}

void loop() {

  int raw = analogRead(ldrPin);
  int mean = updateMean();

  Serial.println(String(mean) + "   " + String(raw));  // print the latest mean and raw sensor reading

  delay(50);  // Small delay for stable readings
}

/**
 * updateMean - Updates the average (mean) of the most recent sensor readings.
 * 
 * This function maintains a rolling average of the last `length` readings
 * from the sensor. It works by using a circular buffer to store readings
 * in the `readings` array without shifting elements. The `sum` variable 
 * keeps a running total of the current values in the array, allowing us to 
 * efficiently compute the mean without re-summing all elements each time.
 */ 
int updateMean() {
  // Subtract the oldest reading from the sum
  sum -= readings[currentIndex];

  // Read the new sensor value and update the array and sum
  readings[currentIndex] = analogRead(ldrPin);
  sum += readings[currentIndex];

  // Move to the next index in a circular manner
  currentIndex = (currentIndex + 1) % length;

  // Calculate and return the mean value
  return sum / length;
}
