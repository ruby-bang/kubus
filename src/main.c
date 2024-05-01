#include <raylib.h>
#include <stdbool.h>
#include <stdlib.h>

#define STAR_LEVEL 1

#define WINDOW_HIEGHT 720
#define WINDOW_WIDTH 1200
#define MAX_RECTANGLES 10
#define MAX_LEVEL 5
#define GROUND_COLOR (Color){39, 59, 72, 255};
#define CARACTER_COLOR (Color){255, 145, 8, 255};

#define TEXT_DEFAULT_COLOR                                                                                             \
  (Color)                                                                                                              \
  {                                                                                                                    \
    39, 59, 72, 255                                                                                                    \
  }
#define BG_COLOR                                                                                                       \
  (Color)                                                                                                              \
  {                                                                                                                    \
    123, 209, 237, 255                                                                                                 \
  }

typedef struct
{
  float x;
  float y;
  int height;
  int width;
  bool is_falling;
  Color color;
  int jumping_count;
  int level;
  int life;
  bool is_hit;
  bool can_move;
} Player;

typedef struct
{
  float min;
  float max;
} Limit;

typedef struct
{
  Rectangle rect;
  Color color;
  float rounded;
  Vector2 moving_speed;
  Limit limit;
} Platform;

typedef struct
{
  Vector2 p1;
  Vector2 p2;
  Vector2 p3;
  Vector2 moving_speed;
} Traps;

void ResetPlatforms(Platform platforms[], int numPlatforms)
{
  for (int i = 0; i < numPlatforms; i++) {
    platforms[i].rect = (Rectangle){0};
    platforms[i].color = BLANK;
  }
}

void platforms_maker(Platform platforms[], Traps traps[], int *num_of_trap, int *num_of_platform, int level)
{
  ResetPlatforms(platforms, *num_of_platform);
  (*num_of_platform) = 0;
  (*num_of_trap) = 0;
  switch (level) {
  case 1:

    /*start point*/
    platforms[0].rect = (Rectangle){WINDOW_WIDTH * 0.25 - 25, WINDOW_HIEGHT * 0.8 - 40, 45, 70};
    platforms[0].color = GROUND_COLOR;
    platforms[0].rounded = 0;
    (*num_of_platform)++;

    /*Platform*/
    {
      /*platforms*/

      /*main ground*/
      platforms[1].rect = (Rectangle){WINDOW_WIDTH * 0.2, WINDOW_HIEGHT * 0.8, WINDOW_WIDTH * 0.6, WINDOW_HIEGHT * 0.3};
      platforms[1].color = GROUND_COLOR;
      platforms[1].rounded = 0.1;
      platforms[1].moving_speed = (Vector2){0, 0};
      (*num_of_platform)++;
    }
    /*portal*/
    platforms[*num_of_platform].rect =
        (Rectangle){(platforms[1].rect.x + platforms[1].rect.width) * 0.93, platforms[1].rect.y - 55, 35, 70};
    platforms[*num_of_platform].color = WHITE;
    platforms[*num_of_platform].rounded = 1.0;
    platforms[*num_of_platform].moving_speed = (Vector2){0, 0};
    (*num_of_platform)++;

    /*border*/
    platforms[*num_of_platform].rect =
        (Rectangle){platforms[*num_of_platform - 1].rect.x - 5, platforms[*num_of_platform - 1].rect.y - 5, 45, 80};
    platforms[*num_of_platform].color = GROUND_COLOR;
    platforms[*num_of_platform].rounded = 1.0;
    platforms[*num_of_platform].moving_speed = (Vector2){0, 0};
    (*num_of_platform)++;

    /*portal point*/
    platforms[*num_of_platform].rect =
        (Rectangle){platforms[*num_of_platform - 1].rect.x + platforms[*num_of_platform - 1].rect.width - 10,
                    platforms[*num_of_platform - 1].rect.y + 30,
                    10,
                    30};
    platforms[*num_of_platform].color = RED;
    platforms[*num_of_platform].moving_speed = (Vector2){0, 0};
    (*num_of_platform)++;

    /*trap */
    /*traps[0].p1 = (Vector2){platforms[*num_of_platform].rect.x + 300, platforms[*num_of_platform - 1].rect.y - 15};*/
    /*traps[0].p2 = (Vector2){platforms[*num_of_platform].rect.x + 285, platforms[*num_of_platform - 1].rect.y};*/
    /*traps[0].p3 = (Vector2){platforms[*num_of_platform].rect.x + 315, platforms[*num_of_platform - 1].rect.y};*/
    /*(*num_of_trap)++;*/

    break;
  case 2:

    /*start point*/
    platforms[0].rect = (Rectangle){WINDOW_WIDTH * 0.75 - 25, WINDOW_HIEGHT * 0.8 - 40, 45, 70};
    platforms[0].color = GROUND_COLOR;
    (*num_of_platform)++;

    /*Platform*/
    {
      platforms[1].rect = (Rectangle){550, 300, 150, 30};
      platforms[1].color = GROUND_COLOR;
      platforms[1].rounded = 0.3;
      platforms[*num_of_platform].moving_speed = (Vector2){0, 0};
      (*num_of_platform)++;

      platforms[2].rect = (Rectangle){230, 400, 150, 30};
      platforms[2].color = GROUND_COLOR;
      platforms[2].rounded = 0.3;
      platforms[*num_of_platform].moving_speed = (Vector2){0, 0};
      (*num_of_platform)++;

      /*main ground*/
      platforms[3].rect = (Rectangle){WINDOW_WIDTH * 0.2, WINDOW_HIEGHT * 0.8, WINDOW_WIDTH * 0.3, WINDOW_HIEGHT * 0.3};
      platforms[3].color = GROUND_COLOR;
      platforms[3].rounded = 0.1;
      platforms[3].moving_speed = (Vector2){0, 0};
      (*num_of_platform)++;

      platforms[4].rect = (Rectangle){WINDOW_WIDTH * 0.7, WINDOW_HIEGHT * 0.8, WINDOW_WIDTH * 0.2, WINDOW_HIEGHT * 0.3};
      platforms[4].color = GROUND_COLOR;
      platforms[4].rounded = 0.1;
      platforms[4].moving_speed = (Vector2){0, 0};
      (*num_of_platform)++;
    }

    /*portal*/
    platforms[*num_of_platform].rect =
        (Rectangle){(platforms[1].rect.x + platforms[1].rect.width) * 0.93, platforms[1].rect.y - 55, 35, 70};
    platforms[*num_of_platform].color = WHITE;
    platforms[*num_of_platform].rounded = 1.0;
    platforms[*num_of_platform].moving_speed = (Vector2){0, 0};
    (*num_of_platform)++;

    /*border*/
    platforms[*num_of_platform].rect =
        (Rectangle){platforms[*num_of_platform - 1].rect.x - 5, platforms[*num_of_platform - 1].rect.y - 5, 45, 80};
    platforms[*num_of_platform].color = GROUND_COLOR;
    platforms[*num_of_platform].rounded = 1.0;
    platforms[*num_of_platform].moving_speed = (Vector2){0, 0};
    (*num_of_platform)++;

    /*portal point*/
    platforms[*num_of_platform].rect =
        (Rectangle){platforms[*num_of_platform - 1].rect.x + platforms[*num_of_platform - 1].rect.width - 10,
                    platforms[*num_of_platform - 1].rect.y + 30,
                    10,
                    30};
    platforms[*num_of_platform].color = RED;
    platforms[*num_of_platform].moving_speed = (Vector2){0, 0};
    (*num_of_platform)++;

    traps[0].p1 = (Vector2){(platforms[2].rect.x + 60) + 15, platforms[2].rect.y - 15};
    traps[0].p2 = (Vector2){(platforms[2].rect.x + 60) + 0, platforms[2].rect.y};
    traps[0].p3 = (Vector2){(platforms[2].rect.x + 60) + 30, platforms[2].rect.y};
    (*num_of_trap)++;

    traps[1].p1 = (Vector2){(platforms[3].rect.x + platforms[3].rect.width * 0.8) + 15, platforms[3].rect.y - 15};
    traps[1].p2 = (Vector2){(platforms[3].rect.x + platforms[3].rect.width * 0.8) + 0, platforms[3].rect.y};
    traps[1].p3 = (Vector2){(platforms[3].rect.x + platforms[3].rect.width * 0.8) + 30, platforms[3].rect.y};
    (*num_of_trap)++;

    break;
  case 3:
    /*start point*/
    platforms[0].rect = (Rectangle){WINDOW_WIDTH * 0.25 - 25, WINDOW_HIEGHT * 0.8 - 40, 45, 70};
    platforms[0].color = GROUND_COLOR;
    (*num_of_platform)++;

    /*Platform*/
    {
      platforms[1].rect = (Rectangle){550, 300, 150, 30};
      platforms[1].color = GROUND_COLOR;
      platforms[1].rounded = 0.3;
      /*platforms[1].moving_speed.x = 2;*/
      /*platforms[1].limit.min = 100;*/
      platforms[1].limit.max = (WINDOW_WIDTH - platforms[1].rect.width) - 500;
      (*num_of_platform)++;

      platforms[2].rect = (Rectangle){230, 400, 150, 30};
      platforms[2].color = GROUND_COLOR;
      platforms[2].rounded = 0.3;
      platforms[2].moving_speed.x = -3;
      platforms[2].limit.min = 100;
      platforms[2].limit.max = 400;
      (*num_of_platform)++;

      platforms[3].rect = (Rectangle){750, 110, 150, 30};
      platforms[3].color = GROUND_COLOR;
      platforms[3].rounded = 0.3;
      platforms[3].moving_speed.y = -1;
      platforms[3].limit.min = 100;
      platforms[3].limit.max = 205;
      (*num_of_platform)++;

      /*main ground*/
      platforms[4].rect = (Rectangle){WINDOW_WIDTH * 0.2, WINDOW_HIEGHT * 0.8, WINDOW_WIDTH * 0.3, WINDOW_HIEGHT * 0.1};
      platforms[4].color = GROUND_COLOR;
      platforms[4].rounded = 0.1;
      platforms[4].moving_speed = (Vector2){0, 0};
      (*num_of_platform)++;
    }

    /*portal*/
    platforms[*num_of_platform].rect = (Rectangle){platforms[3].rect.x + 100, platforms[3].rect.y - 55, 35, 70};
    platforms[*num_of_platform].color = WHITE;
    platforms[*num_of_platform].rounded = 1.0;
    (*num_of_platform)++;

    /*border*/
    platforms[*num_of_platform].rect =
        (Rectangle){platforms[*num_of_platform - 1].rect.x - 5, platforms[*num_of_platform - 1].rect.y - 5, 45, 80};
    platforms[*num_of_platform].color = GROUND_COLOR;
    platforms[*num_of_platform].rounded = 1.0;
    (*num_of_platform)++;

    /*portal point*/
    platforms[*num_of_platform].rect =
        (Rectangle){platforms[*num_of_platform - 2].rect.x + platforms[*num_of_platform - 2].rect.width - 10,
                    platforms[*num_of_platform - 2].rect.y + 45,
                    10,
                    10};
    platforms[*num_of_platform].color = RED;
    (*num_of_platform)++;

    /*traps[0].p1 = (Vector2){(platforms[1].rect.x + 60) + 15, platforms[1].rect.y - 15};*/
    /*traps[0].p2 = (Vector2){(platforms[1].rect.x + 60) + 0, platforms[1].rect.y};*/
    /*traps[0].p3 = (Vector2){(platforms[1].rect.x + 60) + 30, platforms[1].rect.y};*/
    /*traps[0].moving_speed = platforms[1].moving_speed;*/
    /*(*num_of_trap)++;*/

    traps[0].p1 = (Vector2){(platforms[2].rect.x + platforms[2].rect.width * 0.3) + 15, platforms[2].rect.y - 15};
    traps[0].p2 = (Vector2){(platforms[2].rect.x + platforms[2].rect.width * 0.3) + 0, platforms[2].rect.y};
    traps[0].p3 = (Vector2){(platforms[2].rect.x + platforms[2].rect.width * 0.3) + 30, platforms[2].rect.y};
    traps[0].moving_speed = platforms[2].moving_speed;
    (*num_of_trap)++;

    /*traps[2].p1 = (Vector2){(platforms[3].rect.x + platforms[3].rect.width * 0.3) + 15, platforms[3].rect.y - 15};*/
    /*traps[2].p2 = (Vector2){(platforms[3].rect.x + platforms[3].rect.width * 0.3) + 0, platforms[3].rect.y};*/
    /*traps[2].p3 = (Vector2){(platforms[3].rect.x + platforms[3].rect.width * 0.3) + 30, platforms[3].rect.y};*/
    /*traps[2].moving_speed = platforms[3].moving_speed;*/
    /*(*num_of_trap)++;*/

    break;
  case 4:
    /*start point*/
    platforms[0].rect = (Rectangle){WINDOW_WIDTH * 0.25 - 25, WINDOW_HIEGHT * 0.8 - 40, 45, 70};
    platforms[0].color = GROUND_COLOR;
    (*num_of_platform)++;

    /*Platform*/
    {
      platforms[1].rect = (Rectangle){150, 300, 150, 30};
      platforms[1].color = GROUND_COLOR;
      platforms[1].rounded = 0.3;
      /*platforms[1].moving_speed.x = 2;*/
      /*platforms[1].limit.min = 100;*/
      platforms[1].limit.max = (WINDOW_WIDTH - platforms[1].rect.width) - 500;
      (*num_of_platform)++;

      platforms[2].rect = (Rectangle){430, 400, 150, 30};
      platforms[2].color = GROUND_COLOR;
      platforms[2].rounded = 0.3;
      platforms[2].moving_speed.x = -3;
      platforms[2].limit.min = 200;
      platforms[2].limit.max = 440;
      (*num_of_platform)++;

      platforms[3].rect = (Rectangle){200, 110, 150, 30};
      platforms[3].color = GROUND_COLOR;
      platforms[3].rounded = 0.3;
      platforms[3].moving_speed.y = -1;
      platforms[3].limit.min = 100;
      platforms[3].limit.max = 205;
      (*num_of_platform)++;

      /*main ground*/
      platforms[4].rect = (Rectangle){WINDOW_WIDTH * 0.2, WINDOW_HIEGHT * 0.8, WINDOW_WIDTH * 0.3, WINDOW_HIEGHT * 0.1};
      platforms[4].color = GROUND_COLOR;
      platforms[4].rounded = 0.1;
      platforms[4].moving_speed = (Vector2){0, 0};
      (*num_of_platform)++;
    }

    /*portal*/
    platforms[*num_of_platform].rect = (Rectangle){platforms[3].rect.x + 100, platforms[3].rect.y - 55, 35, 70};
    platforms[*num_of_platform].color = WHITE;
    platforms[*num_of_platform].rounded = 1.0;
    (*num_of_platform)++;

    /*border*/
    platforms[*num_of_platform].rect =
        (Rectangle){platforms[*num_of_platform - 1].rect.x - 5, platforms[*num_of_platform - 1].rect.y - 5, 45, 80};
    platforms[*num_of_platform].color = GROUND_COLOR;
    platforms[*num_of_platform].rounded = 1.0;
    (*num_of_platform)++;

    /*portal point*/
    platforms[*num_of_platform].rect =
        (Rectangle){platforms[*num_of_platform - 2].rect.x + platforms[*num_of_platform - 2].rect.width - 10,
                    platforms[*num_of_platform - 2].rect.y + 45,
                    10,
                    10};
    platforms[*num_of_platform].color = RED;
    (*num_of_platform)++;

    /*traps[0].p1 = (Vector2){(platforms[1].rect.x + 60) + 15, platforms[1].rect.y - 15};*/
    /*traps[0].p2 = (Vector2){(platforms[1].rect.x + 60) + 0, platforms[1].rect.y};*/
    /*traps[0].p3 = (Vector2){(platforms[1].rect.x + 60) + 30, platforms[1].rect.y};*/
    /*traps[0].moving_speed = platforms[1].moving_speed;*/
    /*(*num_of_trap)++;*/

    traps[0].p1 = (Vector2){(platforms[2].rect.x + platforms[2].rect.width * 0.3) + 15, platforms[2].rect.y - 15};
    traps[0].p2 = (Vector2){(platforms[2].rect.x + platforms[2].rect.width * 0.3) + 0, platforms[2].rect.y};
    traps[0].p3 = (Vector2){(platforms[2].rect.x + platforms[2].rect.width * 0.3) + 30, platforms[2].rect.y};
    traps[0].moving_speed = platforms[2].moving_speed;
    (*num_of_trap)++;

    /*traps[2].p1 = (Vector2){(platforms[3].rect.x + platforms[3].rect.width * 0.3) + 15, platforms[3].rect.y - 15};*/
    /*traps[2].p2 = (Vector2){(platforms[3].rect.x + platforms[3].rect.width * 0.3) + 0, platforms[3].rect.y};*/
    /*traps[2].p3 = (Vector2){(platforms[3].rect.x + platforms[3].rect.width * 0.3) + 30, platforms[3].rect.y};*/
    /*traps[2].moving_speed = platforms[3].moving_speed;*/
    /*(*num_of_trap)++;*/

    break;
  }
}

void start_beginig(Player *player,
                   float *jump_speed,
                   float *gravity,
                   float *falling_speed,
                   float platformsX,
                   float platformsY,
                   bool *pause,
                   bool *game_start)
{
  player->x = platformsX;
  player->y = platformsY + 40;
  player->is_hit = false;
  player->is_falling = false;
  player->level = STAR_LEVEL;
  player->life = 3;
  player->jumping_count = 0;
  *gravity = 0.0f;
  *falling_speed = 0;
  *game_start = false;
  *pause = true;
  *jump_speed = -15;
}

int main(void)
{
  Player *player = (Player *)malloc(sizeof(Player));

  Platform platforms[MAX_RECTANGLES] = {0};
  Traps traps[10] = {0};
  Vector2 text_level = {25, 20};

  int num_of_platform = 0;
  int num_of_trap = 0;
  float gravity = 0.0f, jump_speed;
  float falling_speed = gravity;
  int hit_count = 0;
  int hit_direc = 5;
  bool pause, game_start;
  bool portal_col = false;
  player->can_move = true;
  int which_plat;

  player->height = 40;
  player->width = player->height;
  player->color = CARACTER_COLOR;
  player->is_hit = false;
  player->is_falling = false;
  player->level = STAR_LEVEL;
  player->life = 3;
  player->jumping_count = 0;

  platforms_maker(platforms, traps, &num_of_trap, &num_of_platform, player->level);
  start_beginig(player,
                &jump_speed,
                &gravity,
                &falling_speed,
                platforms[0].rect.x,
                platforms[0].rect.y,
                &pause,
                &game_start);

  InitWindow(WINDOW_WIDTH, WINDOW_HIEGHT, "Platform");
  SetTargetFPS(60);

  Font QuincyFont = LoadFontEx("./resource/font/Peter.otf", 82, 0, 250);
  Image heart_img = LoadImage("./resource/icon/heart.png");
  Texture2D heart = LoadTextureFromImage(heart_img);
  UnloadImage(heart_img);

  while (!WindowShouldClose()) {
    ClearBackground(BG_COLOR);

    Rectangle player_rec = {
        player->x,
        player->y,
        player->height,
        player->width,
    };

    if (IsKeyPressed(KEY_SPACE)) {
      pause = !pause;
      if (!game_start)
        game_start = true;
    }

    if (!pause) {
      for (int i = 1; i < num_of_platform - 3; i++) {

        if (CheckCollisionRecs(platforms[num_of_platform - 3].rect, platforms[i].rect) && !portal_col) {
          which_plat = i;
          portal_col = true;
        }
        if (platforms[i].rect.x >= platforms[i].limit.max || platforms[i].rect.x <= platforms[i].limit.min) {
          platforms[i].moving_speed.x *= -1;
        }
        if (platforms[i].rect.y >= platforms[i].limit.max || platforms[i].rect.y <= platforms[i].limit.min) {
          platforms[i].moving_speed.y *= -1;
        }
        if (platforms[i].moving_speed.x != 0.0) {
          platforms[i].rect.x += platforms[i].moving_speed.x;
        }
        if (platforms[i].moving_speed.y != 0.0) {
          platforms[i].rect.y += platforms[i].moving_speed.y;
        }
        for (int j = 0; j <= num_of_trap; j++) {
          if (traps[j].moving_speed.x != 0 && traps[j].p2.y == platforms[i].rect.y) {
            traps[j].p1.x += platforms[i].moving_speed.x;
            traps[j].p2.x += platforms[i].moving_speed.x;
            traps[j].p3.x += platforms[i].moving_speed.x;
          }
          if (traps[j].moving_speed.y != 0 && traps[j].p2.y >= platforms[i].rect.y - 20) {
            traps[j].p1.y += platforms[i].moving_speed.y;
            traps[j].p2.y += platforms[i].moving_speed.y;
            traps[j].p3.y += platforms[i].moving_speed.y;
          }
        }
      }

      if (portal_col) {
        platforms[num_of_platform - 3].rect.x += platforms[which_plat].moving_speed.x;
        platforms[num_of_platform - 3].rect.y += platforms[which_plat].moving_speed.y;
        platforms[num_of_platform - 2].rect.x += platforms[which_plat].moving_speed.x;
        platforms[num_of_platform - 2].rect.y += platforms[which_plat].moving_speed.y;
        platforms[num_of_platform - 1].rect.x += platforms[which_plat].moving_speed.x;
        platforms[num_of_platform - 1].rect.y += platforms[which_plat].moving_speed.y;
      }

      for (int i = 1; i < num_of_platform - 3; i++) {
        if (CheckCollisionRecs(player_rec, platforms[i].rect)) {

          if (player->y >= platforms[i].rect.y + (platforms[i].rect.height - 15)) {
            jump_speed = 0;
          } else if ((player->y + player->height >= platforms[i].rect.y + 20 &&
                      player->y <= platforms[i].rect.y + (platforms[i].rect.height * 0.9)) &&
                     (player->x >= platforms[i].rect.x + platforms[i].rect.width - 10 ||
                      player->x <= platforms[i].rect.x + 10)) {
            if (player->x >= platforms[i].rect.x + platforms[i].rect.width - 20) {
              player->x = platforms[i].rect.x + platforms[i].rect.width + 5;
            } else if (player->x + player->width <= platforms[i].rect.x + 20) {
              player->x = platforms[i].rect.x - player->width;
            }
          } else if (player->y + player->height <= platforms[i].rect.y + 40 &&
                     player->x <= platforms[i].rect.x + platforms[i].rect.width - 5 &&
                     player->x + player->width >= platforms[i].rect.x + 5) {
            player->jumping_count = 0;
            player->y = platforms[i].rect.y - player->height + platforms[i].moving_speed.y;

            if ((!IsKeyDown(KEY_LEFT) || !IsKeyDown(KEY_RIGHT)) && player->can_move) {
              if (platforms[i].rect.x >= platforms[i].limit.max || platforms[i].rect.x <= platforms[i].limit.min) {
                player->x += platforms[i].moving_speed.x * -2;
              }
              player->x += platforms[i].moving_speed.x;
            }
            player->is_falling = false;
            break;
          }
        }
        player->is_falling = true;
      }

      if (player->is_falling) {
        gravity += 0.07;
        falling_speed += gravity;
        player->y += falling_speed;
      } else {
        falling_speed = 0;
        gravity = 0;
      }

      if ((IsKeyPressed(KEY_UP) && player->jumping_count < 2) || (player->is_hit && hit_count < 2)) {
        jump_speed = 0;
        player->can_move = true;
        falling_speed = 0;
        if (player->jumping_count > 0) {
          jump_speed += -11;
        } else {
          jump_speed += -13;
        }
        gravity = 0.07;
        player->jumping_count++;
      }

      player->y += jump_speed;

      if (jump_speed < 0)
        jump_speed += gravity;

      if (IsKeyDown(KEY_RIGHT) && !player->is_hit && player->can_move) {
        player->x += 6;
        if (player->is_falling) {
          player->x += 1;
        }
      }

      if (IsKeyDown(KEY_LEFT) && !player->is_hit && player->can_move) {
        player->x -= 6;
        if (player->is_falling) {
          player->x -= 1;
        }
      }

      if (player->is_hit) {
        if (hit_count == 15) {
          player->life--;
          player->is_hit = false;
          hit_count = 0;
        }

        if (player->y >= WINDOW_HIEGHT) {
          player->x = platforms[0].rect.x;
          player->y = platforms[0].rect.y + 60;
          hit_count = 14;
        }

        player->x += hit_direc;
        hit_count++;
      }

      if (CheckCollisionRecs(player_rec, platforms[num_of_platform - 1].rect) && player->level < MAX_LEVEL) {
        player->level += 1;
        portal_col = false;
        platforms_maker(platforms, traps, &num_of_trap, &num_of_platform, player->level);
        player->x = platforms[0].rect.x;
        player->y = platforms[0].rect.y;
      }

      if (player->y > WINDOW_HIEGHT)
        player->is_hit = true;
    }

    BeginDrawing();

    for (int i = 0; i < player->life; i++) {
      DrawTexture(heart, 200 + (45 * i), 25, WHITE);
    }

    for (int i = 0; i < num_of_trap; i++) {
      DrawTriangle(traps[i].p1, traps[i].p2, traps[i].p3, RED);
      if (CheckCollisionPointRec(traps[i].p1, player_rec)) {
        player->is_hit = true;
        hit_direc = -5;
      } else if (CheckCollisionPointRec(traps[i].p2, player_rec)) {
        player->is_hit = true;
        hit_direc = -5;
      } else if (CheckCollisionPointRec(traps[i].p3, player_rec)) {
        player->is_hit = true;
        hit_direc = +5;
      }
    }

    DrawTextEx(QuincyFont, TextFormat("level %d", player->level), text_level, 40, 1, TEXT_DEFAULT_COLOR);

    for (int i = num_of_platform; i > num_of_platform - 4; i--) {
      DrawRectangleRounded(platforms[i].rect, platforms[i].rounded, 5, platforms[i].color);
    }
    if (player->x != 0) {
      DrawRectangleRec(player_rec, player->color);
    }
    for (int i = num_of_platform - 4; i > 0; i--) {
      DrawRectangleRounded(platforms[i].rect, platforms[i].rounded, 5, platforms[i].color);
    }

    if (player->life <= 0 || player->level == MAX_LEVEL)
      pause = true;

    if (pause && player->life > 0 && game_start && player->level != MAX_LEVEL) {
      DrawTextEx(QuincyFont, "pause", (Vector2){WINDOW_WIDTH * 0.38, WINDOW_HIEGHT * 0.42}, 80, 1, YELLOW);
    } else if (!game_start) {
      DrawTextEx(QuincyFont, "START", (Vector2){WINDOW_WIDTH * 0.38, WINDOW_HIEGHT * 0.42}, 80, 1, TEXT_DEFAULT_COLOR);
      DrawTextEx(QuincyFont,
                 "SPACE To Start Game",
                 (Vector2){WINDOW_WIDTH * 0.38, WINDOW_HIEGHT * 0.52},
                 20,
                 1,
                 TEXT_DEFAULT_COLOR);
    } else if (player->life < 1) {
      DrawTextEx(QuincyFont, "GAME OVER", (Vector2){WINDOW_WIDTH * 0.35, WINDOW_HIEGHT * 0.42}, 80, 1, RED);
      if (IsKeyPressed(KEY_SPACE)) {
        pause = false;
        player->level = STAR_LEVEL;
        portal_col = false;

        platforms_maker(platforms, traps, &num_of_trap, &num_of_platform, player->level);
        start_beginig(player,
                      &jump_speed,
                      &gravity,
                      &falling_speed,
                      platforms[0].rect.x,
                      platforms[0].rect.y,
                      &pause,
                      &game_start);
      }
    } else if (player->level >= MAX_LEVEL) {
      DrawTextEx(QuincyFont, "TAMAT", (Vector2){WINDOW_WIDTH * 0.38, WINDOW_HIEGHT * 0.42}, 80, 1, TEXT_DEFAULT_COLOR);
      DrawTextEx(QuincyFont,
                 "SPACE To Continue",
                 (Vector2){WINDOW_WIDTH * 0.39, WINDOW_HIEGHT * 0.52},
                 20,
                 3,
                 TEXT_DEFAULT_COLOR);
      if (IsKeyPressed(KEY_SPACE)) {
        player->level = STAR_LEVEL;
        portal_col = false;

        platforms_maker(platforms, traps, &num_of_trap, &num_of_platform, player->level);
        start_beginig(player,
                      &jump_speed,
                      &gravity,
                      &falling_speed,
                      platforms[0].rect.x,
                      platforms[0].rect.y,
                      &pause,
                      &game_start);
      }
    }
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
