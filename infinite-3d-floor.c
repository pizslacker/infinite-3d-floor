#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

// Global Screen Dimensions
int screen_w = 1280;
int screen_h = 720;
bool fullscreen = false;

// Compact 8x8 ASCII Font (Characters 32 to 95)
const uint8_t font8x8[64][8] = {
    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, {0x18,0x3c,0x3c,0x18,0x18,0x00,0x18,0x00}, {0x6c,0x6c,0x6c,0x00,0x00,0x00,0x00,0x00}, {0x6c,0x6c,0xfe,0x6c,0xfe,0x6c,0x6c,0x00},
    {0x18,0x3e,0x60,0x3c,0x06,0x7c,0x18,0x00}, {0x00,0xc6,0xcc,0x18,0x30,0x66,0xc6,0x00}, {0x38,0x6c,0x6c,0x38,0x6d,0x66,0x3b,0x00}, {0x18,0x18,0x18,0x00,0x00,0x00,0x00,0x00},
    {0x0c,0x18,0x30,0x30,0x30,0x18,0x0c,0x00}, {0x30,0x18,0x0c,0x0c,0x0c,0x18,0x30,0x00}, {0x00,0x66,0x3c,0xff,0x3c,0x66,0x00,0x00}, {0x00,0x18,0x18,0x7e,0x18,0x18,0x00,0x00},
    {0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x30}, {0x00,0x00,0x00,0x7e,0x00,0x00,0x00,0x00}, {0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00}, {0x06,0x0c,0x18,0x30,0x60,0xc0,0x80,0x00},
    {0x3c,0x66,0x6e,0x76,0x66,0x66,0x3c,0x00}, {0x18,0x38,0x58,0x18,0x18,0x18,0x7e,0x00}, {0x3c,0x66,0x06,0x0c,0x30,0x60,0x7e,0x00}, {0x3c,0x66,0x06,0x1c,0x06,0x66,0x3c,0x00},
    {0x0c,0x1c,0x3c,0x6c,0x7e,0x0c,0x0c,0x00}, {0x7e,0x60,0x7c,0x06,0x06,0x66,0x3c,0x00}, {0x3c,0x66,0x60,0x7c,0x66,0x66,0x3c,0x00}, {0x7e,0x06,0x0c,0x18,0x30,0x30,0x30,0x00},
    {0x3c,0x66,0x66,0x3c,0x66,0x66,0x3c,0x00}, {0x3c,0x66,0x66,0x3e,0x06,0x66,0x3c,0x00}, {0x00,0x18,0x18,0x00,0x00,0x18,0x18,0x00}, {0x00,0x18,0x18,0x00,0x00,0x18,0x18,0x30},
    {0x06,0x0c,0x18,0x30,0x18,0x0c,0x06,0x00}, {0x00,0x00,0x7e,0x00,0x7e,0x00,0x00,0x00}, {0x60,0x30,0x18,0x0c,0x18,0x30,0x60,0x00}, {0x3c,0x66,0x06,0x0c,0x18,0x00,0x18,0x00},
    {0x3c,0x66,0x6e,0x6e,0x60,0x66,0x3c,0x00}, {0x18,0x3c,0x66,0x66,0x7e,0x66,0x66,0x00}, {0x7c,0x66,0x66,0x7c,0x66,0x66,0x7c,0x00}, {0x3c,0x66,0x60,0x60,0x60,0x66,0x3c,0x00},
    {0x78,0x6c,0x66,0x66,0x66,0x6c,0x78,0x00}, {0x7e,0x60,0x60,0x7c,0x60,0x60,0x7e,0x00}, {0x7e,0x60,0x60,0x7c,0x60,0x60,0x60,0x00}, {0x3c,0x66,0x60,0x6e,0x66,0x66,0x3e,0x00},
    {0x66,0x66,0x66,0x7e,0x66,0x66,0x66,0x00}, {0x3c,0x18,0x18,0x18,0x18,0x18,0x3c,0x00}, {0x06,0x06,0x06,0x06,0x06,0x66,0x3c,0x00}, {0x66,0x6c,0x78,0x70,0x78,0x6c,0x66,0x00},
    {0x60,0x60,0x60,0x60,0x60,0x60,0x7e,0x00}, {0x63,0x77,0x7f,0x6b,0x63,0x63,0x63,0x00}, {0x66,0x76,0x7e,0x7e,0x6e,0x66,0x66,0x00}, {0x3c,0x66,0x66,0x66,0x66,0x66,0x3c,0x00},
    {0x7c,0x66,0x66,0x7c,0x60,0x60,0x60,0x00}, {0x3c,0x66,0x66,0x66,0x6a,0x6c,0x36,0x00}, {0x7c,0x66,0x66,0x7c,0x6c,0x66,0x66,0x00}, {0x3c,0x66,0x60,0x3c,0x06,0x66,0x3c,0x00},
    {0x7e,0x18,0x18,0x18,0x18,0x18,0x18,0x00}, {0x66,0x66,0x66,0x66,0x66,0x66,0x3c,0x00}, {0x66,0x66,0x66,0x66,0x66,0x3c,0x18,0x00}, {0x63,0x63,0x63,0x6b,0x7f,0x77,0x63,0x00},
    {0x66,0x66,0x3c,0x18,0x3c,0x66,0x66,0x00}, {0x66,0x66,0x66,0x3c,0x18,0x18,0x18,0x00}, {0x7e,0x06,0x0c,0x18,0x30,0x60,0x7e,0x00}, {0x3c,0x30,0x30,0x30,0x30,0x30,0x3c,0x00},
    {0x60,0x30,0x18,0x0c,0x06,0x03,0x01,0x00}, {0x3c,0x0c,0x0c,0x0c,0x0c,0x0c,0x3c,0x00}, {0x00,0x00,0x3c,0x66,0x00,0x00,0x00,0x00}, {0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00}
};

// Generate Infinite 3D Checkerboard Floor Texture using raycasting
void update_floor_texture(SDL_Texture* texture, float t, int w, int h) {
    int pitch;
    void* pixels;
    SDL_LockTexture(texture, NULL, &pixels, &pitch);
    Uint32* dst = (Uint32*)pixels;

    float angle = t * 0.4f;
    float cos_a = cosf(angle);
    float sin_a = sinf(angle);
    float scroll_speed = t * 300.0f;
    float camera_height = 8000.0f;

    for (int y = 0; y < h; y++) {
        float current_y = (float)(y + 1); // 1 to h (horizon down to bottom)
        float z = camera_height / current_y;
        float wy = z;
        
        float wy_sin = wy * sin_a;
        float wy_cos = wy * cos_a;
        
        float shade = current_y / (float)h;
        if (shade > 1.0f) shade = 1.0f;

        for (int x = 0; x < w; x++) {
            float screen_x = (float)(x - w / 2);
            float wx = screen_x * z / 250.0f;

            // Apply 3D rotation and translation
            float u = (wx * cos_a - wy_sin) + scroll_speed;
            float v = (wx * sin_a + wy_cos) + scroll_speed;

            // Generate Amiga XOR Texture Pattern
            int u_int = (int)u >> 5;
            int v_int = (int)v >> 5;
            int tex_val = (u_int ^ v_int) & 1;

            // Colors: Neon Blue & Magenta grid
            Uint8 r = tex_val ? 0 : 180;
            Uint8 g = tex_val ? 150 : 0;
            Uint8 b = tex_val ? 255 : 100;

            // Apply Depth Shading
            r = (Uint8)(r * shade);
            g = (Uint8)(g * shade);
            b = (Uint8)(b * shade);

            dst[y * (pitch / 4) + x] = (255 << 24) | (r << 16) | (g << 8) | b;
        }
    }
    SDL_UnlockTexture(texture);
}

// Hardware-accelerated text scroller with translucent rippling water reflection
void render_scroller(SDL_Renderer* renderer, float t, const char* text) {
    float scale = 8.0f;                       
    float base_y = screen_h - 180.0f;         
    float speed = 220.0f;                     
    
    int len = strlen(text);
    float char_width = 8.0f * scale;
    float total_width = len * char_width;
    float offset = screen_w - fmodf(t * speed, total_width);

    SDL_Rect rects[400]; 
    int rect_count = 0;

    // --- PASS 1: WATER REFLECTION (TRANSLUCENT) ---
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    for (int row = 0; row < 8; row++) {
        float fade = (row + 1) / 8.0f;
        Uint8 ref_r = (Uint8)(15 * fade);
        Uint8 ref_g = (Uint8)(60 * fade);
        Uint8 ref_b = (Uint8)(120 * fade);
        
        SDL_SetRenderDrawColor(renderer, ref_r, ref_g, ref_b, 128);

        for (int i = 0; i < len * 2; i++) {
            char c = text[i % len];
            if (c < 32 || c > 95) c = 32; 
            uint8_t glyph_row = font8x8[c - 32][row];
            
            for (int col = 0; col < 8; col++) {
                if (glyph_row & (1 << (7 - col))) {
                    float px = offset + (i * char_width) + (col * scale);
                    
                    if (px > -scale - 40.0f && px < screen_w + 40.0f) {
                        int reflected_row = 7 - row;
                        float gap = 4.0f;
                        float ref_py_base = base_y + (8.0f * scale) + gap + (reflected_row * scale);
                        
                        float ripple_amp_x = (reflected_row + 1) * 3.0f;
                        float ripple_amp_y = (reflected_row + 1) * 1.5f;
                        
                        float water_x = px + sinf(ref_py_base * 0.05f + t * 5.0f) * ripple_amp_x;
                        float water_y = ref_py_base + cosf(px * 0.05f + t * 4.0f) * ripple_amp_y;
                        
                        rects[rect_count].x = (int)water_x;
                        rects[rect_count].y = (int)water_y;
                        rects[rect_count].w = (int)scale;
                        rects[rect_count].h = (int)scale;
                        rect_count++;

                        if (rect_count == 400) {
                            SDL_RenderFillRects(renderer, rects, rect_count);
                            rect_count = 0;
                        }
                    }
                }
            }
        }
        if (rect_count > 0) {
            SDL_RenderFillRects(renderer, rects, rect_count);
            rect_count = 0;
        }
    }

    // --- PASS 2: MAIN FOREGROUND TEXT (SOLID COPPER) ---
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

    for (int row = 0; row < 8; row++) {
        float phase = row * 0.4f - t * 4.0f;
        Uint8 cr = (Uint8)((sinf(phase + 0.0f) + 1.0f) * 127.5f);
        Uint8 cg = (Uint8)((sinf(phase + 2.0f) + 1.0f) * 127.5f);
        Uint8 cb = (Uint8)((sinf(phase + 4.0f) + 1.0f) * 127.5f);
        SDL_SetRenderDrawColor(renderer, cr, cg, cb, 255);
        
        for (int i = 0; i < len * 2; i++) {
            char c = text[i % len];
            if (c < 32 || c > 95) c = 32; 
            uint8_t glyph_row = font8x8[c - 32][row];
            
            for (int col = 0; col < 8; col++) {
                if (glyph_row & (1 << (7 - col))) {
                    float px = offset + (i * char_width) + (col * scale);
                    
                    if (px > -scale && px < screen_w) {
                        float py = base_y + (row * scale);
                        
                        rects[rect_count].x = (int)px;
                        rects[rect_count].y = (int)py;
                        rects[rect_count].w = (int)scale;
                        rects[rect_count].h = (int)scale;
                        rect_count++;

                        if (rect_count == 400) {
                            SDL_RenderFillRects(renderer, rects, rect_count);
                            rect_count = 0;
                        }
                    }
                }
            }
        }
        if (rect_count > 0) {
            SDL_RenderFillRects(renderer, rects, rect_count);
            rect_count = 0;
        }
    }
}

// Generate the 3D rotating Boing Ball texture using CPU pixel manipulation
void update_boing_ball_texture(SDL_Texture* texture, float t) {
    int pitch;
    void* pixels;
    SDL_LockTexture(texture, NULL, &pixels, &pitch);
    Uint32* dst = (Uint32*)pixels;
    
    int R = 50;
    float rot_u = t * 2.5f;
    float rot_v = sinf(t * 1.5f) * 0.5f;
    float tiles = 3.5f;

    for (int y = -R; y < R; y++) {
        for (int x = -R; x < R; x++) {
            int r_sq = x*x + y*y;
            int idx = (y + R) * (pitch / 4) + (x + R);
            
            if (r_sq <= R*R) {
                float z = sqrtf((float)(R*R - r_sq));
                float u = atan2f((float)x, z);
                float v = asinf((float)y / R);
                
                // Checkerboard Math (absolute value to prevent C modulo issues)
                int val = (int)floorf((u + rot_u) * tiles) + (int)floorf((v + rot_v) * tiles);
                int check = abs(val) % 2;

                Uint8 cr = check ? 255 : 190;
                Uint8 cg = check ? 30 : 190;
                Uint8 cb = check ? 30 : 190;

                // 3D Volume Shading
                float shade = z / (float)R;
                cr = (Uint8)(cr * shade);
                cg = (Uint8)(cg * shade);
                cb = (Uint8)(cb * shade);

                // ARGB8888 Pixel format
                dst[idx] = (255 << 24) | (cr << 16) | (cg << 8) | cb;
            } else {
                dst[idx] = 0; // Transparent background
            }
        }
    }
    SDL_UnlockTexture(texture);
}

// Draw a filled ellipse for the Boing Ball ground shadow
void fill_ellipse(SDL_Renderer* renderer, int cx, int cy, int rx, int ry, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    for (int y = -ry; y <= ry; y++) {
        float dx = (float)rx * sqrtf(1.0f - (float)(y*y)/(float)(ry*ry));
        SDL_Rect rect = { cx - (int)dx, cy + y, (int)dx * 2, 1 };
        SDL_RenderFillRect(renderer, &rect);
    }
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
}

#define TEX_SIZE 256

// Helper to burn the 8x8 font directly into the badge pixel buffer
void draw_text_to_buffer(Uint32* buffer, const char* text, int x, int y, int scale, Uint32 color) {
    int len = strlen(text);
    for (int i = 0; i < len; i++) {
        char c = text[i];
        if (c >= 'a' && c <= 'z') c -= 32;
        if (c < 32 || c > 95) c = 32;
        
        for (int row = 0; row < 8; row++) {
            uint8_t glyph = font8x8[c - 32][row];
            for (int col = 0; col < 8; col++) {
                if (glyph & (1 << (7 - col))) {
                    for (int dy = 0; dy < scale; dy++) {
                        for (int dx = 0; dx < scale; dx++) {
                            int px = x + (i * 8 + col) * scale + dx;
                            int py = y + row * scale + dy;
                            if (px >= 0 && px < TEX_SIZE && py >= 0 && py < TEX_SIZE) {
                                buffer[py * TEX_SIZE + px] = color;
                            }
                        }
                    }
                }
            }
        }
    }
}

// Generates the glassy checkerboard "k ! M" badge rotozoomer
SDL_Texture* create_roto_badge(SDL_Renderer* renderer) {
    Uint32* pixels = (Uint32*)malloc(TEX_SIZE * TEX_SIZE * sizeof(Uint32));

    for (int y = -128; y < 128; y++) {
        for (int x = -128; x < 128; x++) {
            int dist_sq = x*x + y*y;
            int py = y + 128;
            int px = x + 128;
            
            if (dist_sq <= 120 * 120) {
                int check = ((px >> 4) ^ (py >> 4)) & 1;
                Uint8 cr = check ? 0x99 : 0x33;
                Uint8 cg = 0x00;
                Uint8 cb = check ? 0x33 : 0x11;
                pixels[py * TEX_SIZE + px] = (255 << 24) | (cr << 16) | (cg << 8) | cb;
            } else {
                pixels[py * TEX_SIZE + px] = 0; // Transparent edges
            }
        }
    }

    int scale = 3;
    int tx = (TEX_SIZE - (5 * 8 * scale)) / 2;
    int ty = (TEX_SIZE - (8 * scale)) / 2;
    
    // Draw Drop Shadow (Black)
    draw_text_to_buffer(pixels, "k ! M", tx + 3, ty + 3, scale, (255 << 24) | (0 << 16) | (0 << 8) | 0);
    // Draw Main Text (Cyan)
    draw_text_to_buffer(pixels, "k ! M", tx, ty, scale, (255 << 24) | (0 << 16) | (255 << 8) | 255);

    SDL_Texture* tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, TEX_SIZE, TEX_SIZE);
    SDL_UpdateTexture(tex, NULL, pixels, TEX_SIZE * sizeof(Uint32));
    SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);
    
    free(pixels);
    return tex;
}

void print_help() {
    printf("Usage: ./infinite-3d-floor [options]\n");
    printf("Options:\n");
    printf("  -w <width>       Set screen width (default: 1280)\n");
    printf("  -h <height>      Set screen height (default: 720)\n");
    printf("  -f, --fullscreen Enable fullscreen mode\n");
    printf("  --help           Show this help message and exit\n");
}

int main(int argc, char* argv[]) {
    // Parse Command Line Arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-w") == 0 && i + 1 < argc) {
            screen_w = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-h") == 0 && i + 1 < argc) {
            screen_h = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--fullscreen") == 0) {
            fullscreen = true;
        } else if (strcmp(argv[i], "--help") == 0) {
            print_help();
            return 0;
        }
    }

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("SDL could not initialize! Error: %s\n", SDL_GetError());
        return 1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2024) < 0) {
        printf("SDL_mixer could not initialize! Mix_Error: %s\n", Mix_GetError());
    }

    Mix_Music* bgm = Mix_LoadMUS("i3df.mp3");
    if (bgm == NULL) {
        bgm = Mix_LoadMUS("i3df.mp3"); // Fallback
    }
    if (bgm != NULL) {
        Mix_FadeInMusic(bgm, -1, 2000);
    } else {
        printf("Warning: Could not load BGM audio! SDL_mixer Error: %s\n", Mix_GetError());
    }

    Uint32 window_flags = SDL_WINDOW_SHOWN;
    if (fullscreen) {
        window_flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    }

    SDL_Window* window = SDL_CreateWindow("C Demoscene - Infinite 3D Floor & Boing Ball", 
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                          screen_w, screen_h, window_flags);
    
    if (fullscreen) {
        SDL_GetWindowSize(window, &screen_w, &screen_h);
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Texture buffer for the Infinite Floor
    int floor_h = screen_h - (screen_h / 2);
    SDL_Texture* floor_tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, 
                                               SDL_TEXTUREACCESS_STREAMING, screen_w, floor_h);
    SDL_SetTextureBlendMode(floor_tex, SDL_BLENDMODE_NONE);

    // Texture buffer for the Rotozoomer Badge
    SDL_Texture* badge_tex = create_roto_badge(renderer);

    // Texture buffer for the Boing Ball
    SDL_Texture* boing_tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, 
                                               SDL_TEXTUREACCESS_STREAMING, 100, 100);
    SDL_SetTextureBlendMode(boing_tex, SDL_BLENDMODE_BLEND);

    bool running = true;
    SDL_Event event;

    float start_time = SDL_GetTicks() / 1000.0f;
    const char* msg = " *** C DEMOSCENE RULES *** THE PIXELS ARE BENDING *** HARDWARE ACCELERATED IN C AND SDL2 *** DRONING IS LOOPING *** THE FLOOR IS INFINITE *** OUR FATHER *** WHO ART IN SBIN *** INIT IS THY NAME *** THY PID IS 1 *** THY CHILDREN RUN IN USER SPACE *** GIVE US THIS DAY OUR DAILY RAM *** AND FORGIVE US OUR BAD CODE *** AS WE FORGIVE THOSE WHO FORK OUR CODE *** LEAD US NOT INTO SEGMENTATION FAULT *** BUT DELIVER US FROM SIGKILL *** SUDO *** ";

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                running = false; 
            }
        }

        float current_time = SDL_GetTicks() / 1000.0f; 
        float t = current_time - start_time;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // 1. Classic Amiga Raster Bars (Copper Bars) in the sky
        int sky_h = screen_h / 2;
        for (int i = 0; i < 3; i++) {
            float bar_center = (sky_h / 2.0f) + sinf(t * 1.5f + i * 2.0f) * (sky_h * 0.4f);
            int bar_thickness = 30;
            for (int line = -bar_thickness; line < bar_thickness; line += 2) {
                int y_pos = (int)(bar_center + line);
                if (y_pos >= 0 && y_pos < sky_h) {
                    float intensity = 1.0f - (fabsf((float)line) / (float)bar_thickness);
                    Uint8 r = 0, g = 0, b = 0;
                    if (i == 0) { r = 0; g = (Uint8)(120 * intensity); b = (Uint8)(255 * intensity); }
                    else if (i == 1) { r = (Uint8)(255 * intensity); g = 0; b = (Uint8)(180 * intensity); }
                    else { r = 0; g = (Uint8)(255 * intensity); b = (Uint8)(150 * intensity); }
                    
                    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
                    SDL_Rect rct = {0, y_pos, screen_w, 2};
                    SDL_RenderFillRect(renderer, &rct);
                }
            }
        }

        // 2. Foreground Infinite 3D Raycasted Checkerboard Floor 
        update_floor_texture(floor_tex, t, screen_w, floor_h);
        SDL_Rect floor_rect = { 0, sky_h, screen_w, floor_h };
        SDL_RenderCopy(renderer, floor_tex, NULL, &floor_rect);

        // 3. Amiga Boing Ball w/ Motion Blur & Ground Shadow
        float floor_z = (screen_h / 2.0f) + 120.0f + sinf(t * 0.8f) * 80.0f;
        float ball_x = (screen_w / 2.0f) + sinf(t * 1.3f) * cosf(t * 0.7f) * (screen_w * 0.4f);
        
        int shadow_w = (int)(40.0f + fabsf(sinf(t * 3.5f)) * 40.0f);
        int shadow_h = (int)(15.0f + fabsf(sinf(t * 3.5f)) * 15.0f);
        Uint8 shadow_alpha = (Uint8)(180.0f - fabsf(sinf(t * 3.5f)) * 140.0f);
        fill_ellipse(renderer, (int)ball_x, (int)floor_z, shadow_w / 2, shadow_h / 2, 10, 5, 15, shadow_alpha);

        for (int i = 5; i >= 0; i--) {
            float trail_t = t - (i * 0.04f);
            
            float t_floor_z = (screen_h / 2.0f) + 120.0f + sinf(trail_t * 0.8f) * 80.0f;
            float t_ball_x = (screen_w / 2.0f) + sinf(trail_t * 1.3f) * cosf(trail_t * 0.7f) * (screen_w * 0.4f);
            float t_bounce = 120.0f + sinf(trail_t * 1.1f) * 40.0f;
            float t_ball_y = t_floor_z - fabsf(sinf(trail_t * 3.5f)) * t_bounce - 50.0f; 
            
            update_boing_ball_texture(boing_tex, trail_t);
            
            Uint8 alpha = (i > 0) ? (Uint8)(255 - (i * 45)) : 255;
            SDL_SetTextureAlphaMod(boing_tex, alpha);
            
            SDL_Rect dst_rect = { (int)t_ball_x - 50, (int)t_ball_y - 50, 100, 100 };
            SDL_RenderCopy(renderer, boing_tex, NULL, &dst_rect);
        }

        // --- 3.5 ROTOZOOMER BADGE ---
        // Calculate degrees for SDL_RenderCopyEx (Pygame used degrees natively)
        float angle_deg = t * 1.5f * (180.0f / 3.14159265f); 
        float zoom = 1.0f + sinf(t * 2.0f) * 0.4f;
        
        float badge_cx = (screen_w / 2.0f) + sinf(t * 1.5f) * 150.0f;
        float badge_cy = (screen_h / 2.0f) - 50.0f + sinf(t * 2.2f) * 80.0f;
        
        // Scale the destination rectangle for zooming
        int bw = (int)(TEX_SIZE * zoom);
        int bh = (int)(TEX_SIZE * zoom);
        SDL_Rect badge_rect = { (int)badge_cx - bw / 2, (int)badge_cy - bh / 2, bw, bh };
        
        // Set 50% translucency (128 out of 255)
        SDL_SetTextureAlphaMod(badge_tex, 128); 
        
        // Render it with hardware-accelerated rotation (Negative angle to match Python's rotation direction)
        SDL_RenderCopyEx(renderer, badge_tex, NULL, &badge_rect, -angle_deg, NULL, SDL_FLIP_NONE);

        // 4. Water-Reflecting Text Scroller
        render_scroller(renderer, t, msg);

        SDL_RenderPresent(renderer);
    }

    if (bgm != NULL) {
        Mix_HaltMusic();
        Mix_FreeMusic(bgm);
        bgm = NULL;
    }

    Mix_CloseAudio();
    Mix_Quit();
    SDL_DestroyTexture(floor_tex);
    SDL_DestroyTexture(boing_tex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}
