#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
//#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


#define BUTTON_PIN 35


// Thêm 'PROGMEM' để lưu vào bộ nhớ Flash, tiết kiệm RAM

const uint8_t SPRITE_TREX[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xfc, 0x00, 0x00, 0x0f, 0xfe, 0x00, 0x00, 0x0c, 0xfe, 0x00,
    0x00, 0x0f, 0xfe, 0x00, 0x00, 0x0f, 0xfe, 0x00, 0x00, 0x0f, 0xfe, 0x00, 0x00, 0x0f, 0xc0, 0x00,
    0x00, 0x0f, 0xf8, 0x00, 0x00, 0x0f, 0x80, 0x00, 0x40, 0x1f, 0x00, 0x00, 0x40, 0x7f, 0x80, 0x00,
    0x60, 0xff, 0xe0, 0x00, 0x71, 0xff, 0x20, 0x00, 0x7f, 0xff, 0x00, 0x00, 0x7f, 0xff, 0x00, 0x00,
    0x3f, 0xff, 0x00, 0x00, 0x1f, 0xfe, 0x00, 0x00, 0x07, 0xfc, 0x00, 0x00, 0x03, 0xf8, 0x00, 0x00,
    0x01, 0xd8, 0x00, 0x00, 0x01, 0x88, 0x00, 0x00, 0x01, 0x88, 0x00, 0x00, 0x01, 0x08, 0x00, 0x00,
    0x01, 0x8c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const uint8_t SPRITE_CACTUS1[] PROGMEM = {
    0x00, 0x00, 0x0e, 0x00, 0x0e, 0x00, 0x0e, 0x00, 0x0e, 0x00, 0x0e, 0x00, 0x4e, 0x40, 0x6e, 0x40,
    0x6e, 0x40, 0x6e, 0x40, 0x6e, 0x40, 0x6e, 0x40, 0x6e, 0x40, 0x7f, 0xc0, 0x3e, 0x00, 0x0e, 0x00,
    0x0e, 0x00, 0x0e, 0x00, 0x0e, 0x00, 0x0e, 0x00, 0x0e, 0x00, 0x0e, 0x00, 0x00, 0x00,
};

const uint8_t SPRITE_CACTUS2[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x18, 0x03, 0x80, 0x18, 0x03, 0x80, 0x18, 0x1b, 0x80, 0x1a,
    0x1b, 0x80, 0x1a, 0x1b, 0x90, 0x1a, 0x1b, 0x90, 0x5e, 0x1b, 0x90, 0x58, 0x1b, 0x90, 0x58, 0x8f,
    0x90, 0x58, 0x83, 0x90, 0x5a, 0xa3, 0xf0, 0x7a, 0xa3, 0x80, 0x3a, 0xa3, 0x80, 0x19, 0xe3, 0x80,
    0x18, 0x83, 0x80, 0x18, 0x83, 0x80, 0x18, 0x83, 0x80, 0x18, 0x83, 0x80, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00,
};

const uint8_t SPRITE_CACTUS3[] PROGMEM = {
    0x00, 0x00, 0x00, 0x0e, 0x03, 0x80, 0x0e, 0x03, 0x80, 0x0e, 0x0b, 0x90, 0x0e, 0xdb, 0x90, 0x0e,
    0xdb, 0x90, 0x4e, 0xdb, 0x90, 0x4e, 0xdb, 0x90, 0x4e, 0xdf, 0x90, 0x4e, 0xcf, 0x90, 0x4f, 0x83,
    0x90, 0x4f, 0x03, 0xf0, 0x7e, 0x03, 0xe0, 0x3e, 0x03, 0x80, 0x0e, 0x03, 0x80, 0x0e, 0x03, 0x80,
    0x0e, 0x03, 0x80, 0x0e, 0x03, 0x80, 0x0e, 0x03, 0x80, 0x0e, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00,
};

const uint8_t SPRITE_GROUND[] PROGMEM = {
    // Chỉ lấy một phần của mảng ground 1800-byte, vì 1200x3 là quá lớn
    // và logic lặp lại. Chúng ta sẽ vẽ nó lặp đi lặp lại.
    // Lấy 128 pixel đầu tiên để lặp lại.
    // 128 pixel * 3 pixel / 8 bit/pixel = 48 bytes.
    // Lấy mẫu từ mã của bạn (có vẻ thưa thớt)
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x01, 0xf8, 0x00, 0x01, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
    // ... Phần này đã được đơn giản hóa. Thay vì một bitmap 1200px, 
    // chúng ta sẽ vẽ một đường và lặp lại các mảng băm.
};

const uint8_t SPRITE_GAME_OVER[] PROGMEM = {
    0x7c, 0x03, 0x80, 0x66, 0x07, 0xf0, 0x00, 0x7c, 0x06, 0x60, 0x7f, 0x03, 0xe0, 0x7c, 0x07, 0xc0,
    0x7e, 0x07, 0xf0, 0x00, 0xfe, 0x06, 0x60, 0x7f, 0x03, 0xf0, 0xc0, 0x0c, 0xe0, 0x7e, 0x07, 0x00,
    0x00, 0xce, 0x06, 0x60, 0x70, 0x03, 0x30, 0xdc, 0x0c, 0xe0, 0x7e, 0x07, 0xe0, 0x00, 0xce, 0x07,
    0xe0, 0x7e, 0x03, 0x70, 0xcc, 0x0f, 0xe0, 0x7e, 0x07, 0x00, 0x00, 0xce, 0x03, 0xc0, 0x70, 0x03,
    0xe0, 0x7c, 0x0c, 0xe0, 0x66, 0x07, 0xf0, 0x00, 0xfe, 0x03, 0xc0, 0x7f, 0x03, 0x70, 0x7c, 0x0c,
    0xe0, 0x66, 0x07, 0xf0, 0x00, 0x7c, 0x01, 0x80, 0x7f, 0x03, 0x70,
};

// Sprite T-Rex chạy (2 frame)
const unsigned char PROGMEM trex_run1[] = {
  0x00,0x70,0xF8,0xFC,0xFC,0xFC,0xFC,0x78,
  0x78,0xF8,0xF8,0xF0,0x60,0x00,0x00,0x00
};

const unsigned char PROGMEM trex_run2[] = {
  0x00,0x70,0xF8,0xFC,0xFC,0xFC,0xFC,0x78,
  0x78,0xF8,0xF0,0x60,0xE0,0xE0,0x40,0x00
};

// Sprite T-Rex khi nhảy
const unsigned char PROGMEM trex_jump[] = {
  0x00,0x70,0xF8,0xFC,0xFC,0xFC,0xFC,0x78,
  0x78,0x78,0x70,0x30,0x00,0x00,0x00,0x00
};



// Trex: 25 x 26
const int TREX_WIDTH = 25;
const int TREX_HEIGHT = 26;
// Cactus1: 11 x 23
const int CACTUS1_WIDTH = 11;
const int CACTUS1_HEIGHT = 23;
// Cactus2: 21 x 23
const int CACTUS2_WIDTH = 21;
const int CACTUS2_HEIGHT = 23;
// Cactus3: 21 x 23
const int CACTUS3_WIDTH = 21;
const int CACTUS3_HEIGHT = 23;
// Game Over: 100 x 7
const int GAMEOVER_WIDTH = 100;
const int GAMEOVER_HEIGHT = 7;



// --- Hằng số Game  ---
const int GROUND_Y = 54;
const int TREX_X = 10;
const int TREX_GROUND_Y = GROUND_Y - TREX_HEIGHT + 2; // Điều chỉnh cho sprite
const int TREX_MIN_Y = 3;
const int CACTUS_Y = GROUND_Y - CACTUS1_HEIGHT + 2; // Điều chỉnh cho sprite cao nhất

const int TREX_VELOCITY = -7;  // Vận tốc nhảy (đi lên)
const int GRAVITY = 5;         // Trọng lực (đi xuống)
const int OBSTACLE_VELOCITY = -2; // Tốc độ di chuyển của thế giới (thay vì -12, giảm tốc độ)
const int OBSTACLE_GAP = 100;

// Vòng lặp game (thay thế Timer::after_millis)
//const int FRAME_DELAY = 15; // ~66 FPS (1000 / 15)
const int FRAME_DELAY = 25;          // Giảm FPS xuống khoảng 40 FPS
unsigned long lastFrameTime = 0;

// --- Định nghĩa logic Game (States & Classes) ---


enum GameState {
  PLAYING,
  GAME_OVER
};


enum TrexState {
  RUNNING,
  JUMPING,
  xFALLING
};


class Trex {
    public:
    int x, y;
    float velocityY;  // vận tốc dọc
    TrexState state;

    Trex() {
        x = TREX_X;
        y = TREX_GROUND_Y;
        velocityY = 0;
        state = TrexState::RUNNING;
    }

    void jump() {
        if (state == TrexState::RUNNING) {
            velocityY = TREX_VELOCITY;   
            state = TrexState::JUMPING;
        }
    }

    void updateState() {
        switch (state) {
        case TrexState::JUMPING:
        case TrexState::xFALLING:
            y += velocityY;
            velocityY += (float)GRAVITY / 10.0;   // dùng GRAVITY (chia 10 để hợp lý)
            if (y >= TREX_GROUND_Y) {
                y = TREX_GROUND_Y;
                velocityY = 0;
                state = TrexState::RUNNING;
            }
            break;
        }
    }


    void draw() {
        display.drawBitmap(x, y, SPRITE_TREX, TREX_WIDTH, TREX_HEIGHT, SH110X_WHITE);
    }

    int16_t getX() { return x; }
    int16_t getY() { return y; }
    int16_t getWidth() { return TREX_WIDTH - 8; }
    int16_t getHeight() { return TREX_HEIGHT - 4; }
};


class Obstacle {
public:
  int x;
  const uint8_t* sprite;
  int w, h;

  Obstacle() {
    x = SCREEN_WIDTH + OBSTACLE_GAP; // Bắt đầu ngoài màn hình
    randomize();
  }

  // Đặt lại và chọn ngẫu nhiên một sprite mới
  void randomize() {
    x = SCREEN_WIDTH + random(OBSTACLE_GAP, OBSTACLE_GAP * 2);
    int type = random(0, 3);
    switch (type) {
      case 0:
        sprite = SPRITE_CACTUS1;
        w = CACTUS1_WIDTH;
        h = CACTUS1_HEIGHT;
        break;
      case 1:
        sprite = SPRITE_CACTUS2;
        w = CACTUS2_WIDTH;
        h = CACTUS2_HEIGHT;
        break;
      case 2:
        sprite = SPRITE_CACTUS3;
        w = CACTUS3_WIDTH;
        h = CACTUS3_HEIGHT;
        break;
    }
  }

  void move() {
    x += OBSTACLE_VELOCITY;
    if (x < -w) { // Nếu ra khỏi màn hình
      randomize();
    }
  }

  void draw() {
    display.drawBitmap(x, CACTUS_Y, sprite, w, h, SH110X_WHITE);
  }

  // Lấy bounding box
  int16_t getX() { return x; }
  int16_t getY() { return CACTUS_Y; }
  int16_t getWidth() { return w; }
  int16_t getHeight() { return h; }
};


class Ground {
public:
  
  Ground() {}

  void draw() {
    display.drawFastHLine(0, GROUND_Y + 1, SCREEN_WIDTH, SH110X_WHITE);
  }

  void move() {
    // Không cần làm gì, đường kẻ là tĩnh
  }
};


// --- Lớp Game chính ---
class Game {
public:
  GameState state;
  Trex trex;
  Obstacle obstacles[2]; // Dùng 2 chướng ngại vật thay vì Queue
  Ground ground;
  unsigned long score;

  int restartClickCount;
  bool lastButtonState; // Để chống dội (debounce)

  Game() {
    // Constructor
  }

  void init() {
    state = GameState::PLAYING;
    score = 0;
    trex = Trex();
    ground = Ground();

    // Đặt lại vị trí chướng ngại vật
    obstacles[0] = Obstacle();
    obstacles[1] = Obstacle();
    obstacles[1].x = obstacles[0].x + SCREEN_WIDTH / 2 + OBSTACLE_GAP;

    restartClickCount = 0;
    lastButtonState = true; // true = thả
  }

  void drawScore() {
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(SCREEN_WIDTH - 70, 5);
    display.print("Score: ");
    display.print(score);
  }

  void drawGameOver() {
    int x = (SCREEN_WIDTH - GAMEOVER_WIDTH) / 2;
    int y = (SCREEN_HEIGHT - GAMEOVER_HEIGHT) / 2 - 10; // Dời lên 10 pixel
    if (y < 0) y = 0;
    display.drawBitmap(x, y, SPRITE_GAME_OVER, GAMEOVER_WIDTH, GAMEOVER_HEIGHT, SH110X_WHITE);
    }

  // Hàm kiểm tra va chạm 
  bool checkCollision() {
    for (int i = 0; i < 2; i++) {     
      if (trex.getX() < obstacles[i].getX() + obstacles[i].getWidth() &&
          trex.getX() + trex.getWidth() > obstacles[i].getX() &&
          trex.getY() < obstacles[i].getY() + obstacles[i].getHeight() &&
          trex.getY() + trex.getHeight() > obstacles[i].getY()) {
        return true;
      }
    }
    return false;
  }

  // Hàm update chính, gọi từ loop()
  void update(bool buttonPressed) {

    // Xử lý logic nhấn nút (chống dội đơn giản)
    // buttonPressed là `true` nếu nút đang được nhấn (LOW)
    bool buttonJustPressed = false;
    if (buttonPressed && lastButtonState) {
      buttonJustPressed = true;
      lastButtonState = false; // Nút đang được giữ
    } else if (!buttonPressed) {
      lastButtonState = true; // Nút đã được thả
    }


    if (state == GameState::GAME_OVER) {
      if (buttonJustPressed) {
        restartClickCount++;
      }
      // Logic khởi động lại (click > 2)
      if (restartClickCount > 2) {
        init(); // Khởi động lại game
      }
      return; // Dừng tại đây nếu game over
    }

    // --- Trạng thái PLAYING ---
    
    // Tăng điểm
    score++;

     // Tăng tốc dần theo điểm
    int dynamicVelocity = OBSTACLE_VELOCITY - (score / 500); // mỗi 500 điểm tăng 1 tốc độ
    for (int i = 0; i < 2; i++) {
        obstacles[i].x += dynamicVelocity;
        if (obstacles[i].x < -obstacles[i].w) obstacles[i].randomize();
    }

    // Xử lý nhảy
    if (buttonJustPressed) {
      trex.jump();
    }

    // Cập nhật và di chuyển thế giới
    trex.updateState();
    ground.move();
    for (int i = 0; i < 2; i++) {
      obstacles[i].move();
    }

    // Kiểm tra va chạm
    if (checkCollision()) {
      state = GameState::GAME_OVER;
    }
  }

  // Hàm draw chính, gọi từ loop()
  void draw() {
    display.clearDisplay();

    drawScore();
    ground.draw();
    trex.draw();
    for (int i = 0; i < 2; i++) {
      obstacles[i].draw();
    }

    if (state == GameState::GAME_OVER) {
      drawGameOver();
    }
    
    display.display(); // Gửi buffer lên màn hình
  }
};

// --- Biến toàn cục ---
Game game;

void setup() {
    Serial.begin(115200);
  Serial.println("ESP32-Rex-Game Starting...");

  pinMode(BUTTON_PIN, INPUT);

  if (!display.begin(0x3c, true)) {
    for (;;);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);
  display.println("Loading...");
  display.display();
  delay(1000);
  randomSeed(millis());
  // Khởi tạo game
  game.init();
  lastFrameTime = millis();
}

void loop() {
  // Tính toán thời gian cho vòng lặp game
  unsigned long currentTime = millis();
  if (currentTime - lastFrameTime < FRAME_DELAY) {
    return; // Chưa đến lúc, thoát và chờ
  }
  lastFrameTime = currentTime;

  // 1. Đọc Input
  bool buttonPressed = (digitalRead(BUTTON_PIN) == LOW);

  // 2. Cập nhật Logic Game
  game.update(buttonPressed);

  // 3. Vẽ lên màn hình
  game.draw();
}