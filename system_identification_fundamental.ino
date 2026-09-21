
#define PWM_PIN 9
#define IN1_PIN 7
#define IN2_PIN 8
#define ENCODER_PIN 2

// Konfigurasi Motor & Encoder
const float PULSES_PER_REV = 360.0;
volatile long pulse_count = 0;

// Variabel Waktu (Ts = 50 ms)
unsigned long previous_millis = 0;
const unsigned long SAMPLE_TIME_MS = 50;

// Variabel PRBS PWM
const int PWM_MIN = 76;  // ~30% dari 255
const int PWM_MAX = 204; // ~80% dari 255
int current_pwm = PWM_MIN;

// ISR (Interrupt Service Routine) untuk membaca encoder
void IRAM_ATTR encoderISR() {
  pulse_count++;
}

void setup() {
  Serial.begin(115200);

  pinMode(PWM_PIN, OUTPUT);
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  pinMode(ENCODER_PIN, INPUT_PULLUP);

  // Set arah putaran motor (Forward)
  digitalWrite(IN1_PIN, HIGH);
  digitalWrite(IN2_PIN, LOW);

  // Attach Interrupt pada RISING edge
  attachInterrupt(digitalPinToInterrupt(ENCODER_PIN), encoderISR, RISING);

  // Header CSV
  Serial.println("t_ms,u_k,y_k");
  
  // Inisialisasi seed acak
  randomSeed(analogRead(0));
}

void loop() {
  unsigned long current_millis = millis();

  if (current_millis - previous_millis >= SAMPLE_TIME_MS) {
    previous_millis = current_millis;

    // 1. Ambil jumlah pulsa dan reset counter
    noInterrupts();
    long pulses = pulse_count;
    pulse_count = 0;
    interrupts();

    // 2. Hitung Kecepatan (y[k]) dalam RPM
    // RPM = (Pulsa / Pulsa_per_Putaran) * (60000 ms / Sample_Time_ms)
    float rpm = ((float)pulses / PULSES_PER_REV) * (60000.0 / SAMPLE_TIME_MS);

    // 3. Log Data ke Serial Monitor (CSV Format)
    Serial.print(current_millis);
    Serial.print(",");
    Serial.print(current_pwm);
    Serial.print(",");
    Serial.println(rpm, 2);

    // 4. Update Sinyal Penguji PRBS untuk sampel berikutnya
    // Peluang 30% untuk switch state PWM
    if (random(0, 100) < 30) {
      current_pwm = (current_pwm == PWM_MIN) ? PWM_MAX : PWM_MIN;
    }

    // Apply PWM ke Driver Motor
    analogWrite(PWM_PIN, current_pwm);
  }
}